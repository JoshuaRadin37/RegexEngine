//
// Created by jradi on 10/30/2019.
//

#include <parser/token_node.h>
#include "ast_builder.h"

ast::ast_builder::ast_builder(parse_node *head) : head(head) {}

abstract_syntax_node *ast::ast_builder::get_output() const {
	if(!built) return nullptr;
	return output;
}

bool ast::ast_builder::build() {
	auto p_category_node = dynamic_cast<category_node *>(head);
	if(!p_category_node) {
		built = false;
		return false;
	}
	output = convert_category_node_to_ast_node(p_category_node);
	built = output != nullptr;
	return built;
}

binop_node *ast::ast_builder::create_binop_node(binop op, abstract_syntax_node *left, abstract_syntax_node *right) {
	return new binop_node(left, right, op);
}

uniop_node *ast::ast_builder::create_uniop_node(uniop op, abstract_syntax_node *affected) {
	return new uniop_node(affected, op);
}

atomic_node *ast::ast_builder::create_atomic_node(token tok) {
	return new atomic_node(tok);
}

abstract_syntax_node *ast::ast_builder::convert_category_node_to_ast_node(category_node *node) {
	std::string category = node->get_category();
	
	if(category == "atom") {
		return create_atomic_node(((token_node * )node->get_child(0))->get_my_token());
	}else if(category == "inter") {
		
		if(node->has_child_category("expression")) {
			uniop op = *(uniop *) category_to_operator(category);
			category_node* next = node->get_child("expression");
			return create_uniop_node(op, convert_category_node_to_ast_node(next));
		} else {
			return convert_category_node_to_ast_node(node->get_child("atom"));
		}
	}else if(category == "expression" && node->num_children() == 0)
			return create_atomic_node(token(token::type::t_special, "\\e", 0));
	
	abstract_syntax_node *inner_node_as_ast_node = convert_category_node_to_ast_node(
			(category_node *) node->get_child(0));
	
	if(category == "expression" ||
	   category == "group") {
		// potential binop
		
		if(node->num_children() == 2) { // is binop
			
			auto other_parse_node = (category_node *) ((category_node* )node->get_child(1))->get_child(0);
			auto other_as_ast_node = convert_category_node_to_ast_node(other_parse_node);
			binop op = *(binop *) category_to_operator(category);
			return create_binop_node(op, inner_node_as_ast_node, other_as_ast_node);
		} // skip to next
		else {
			return inner_node_as_ast_node;
		}
	} else if(category == "segment") {
		
		if(node->num_children() == 2) { // has duplication
			abstract_syntax_node* built = nullptr;
			std::vector<token> dup_tok_stack;
			category_node* ptr = node;
			do {
				try {
					ptr = ptr->get_child("segment_tail");
					token t = ((token_node *) ptr->get_child(0))->get_my_token();
					dup_tok_stack.push_back(t);
				} catch (const category_node::category_not_found_exception& e) {
					break;
				}
			} while(true);
			
			
			for (const auto &tok : dup_tok_stack) {
				
				uniop op = *(uniop *) category_to_operator(category, tok);
				if(built == nullptr) {
					built = create_uniop_node(op, inner_node_as_ast_node);
				} else {
					built = create_uniop_node(op, built);
				}
			}
			
			
			
			return built;
		}
		
		return inner_node_as_ast_node;
	}
	
	return nullptr;
}

op * ast::ast_builder::category_to_operator(const std::string &category, const token &tok) {
	if(category == "expression") {
		return binop::UNION;
	}
	if(category == "group") {
		return binop::CONCAT;
	}
	if(category == "segment" || category == "segment_tail") {
		if(tok.get_token_type() == token::type::t_star)
			return uniop::CLOSURE;
		if(tok.get_token_type() == token::type::t_question)
			return uniop::NONE_OR_ONE;
		if(tok.get_token_type() == token::type::t_plus)
			return uniop::ONE_OR_MORE;
	}
	if(category == "inter") {
		return uniop::CONTAINER;
	}
	return nullptr;
}

bool ast::ast_builder::is_built() const {
	return built;
}
