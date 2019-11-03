//
// Created by jradi on 11/1/2019.
//

#include <parser/token_node.h>
#include <evaluation/rules/range_rule.h>
#include "ast_converter.h"
#include "automaton_factory.h"
#include "full_automaton_generator.h"


automaton *ast_converter::convert_node(abstract_syntax_node *node) {
	if(node == nullptr) return nullptr;
	switch (node->get_my_type()) {
		case abstract_syntax_node::type::binop:
			return convert_binop((binop_node*) node);
		case abstract_syntax_node::type::uniop:
			return convert_uniop((uniop_node *) node);
		case abstract_syntax_node::type::atom:
			return convert_atomic((atomic_node *) node);
	}
	
}

automaton *ast_converter::convert_binop(binop_node *node) {
	if(node->get_op() == *binop::CONCAT)
		return convert_concat(node);
	else if(node->get_op() == *binop::UNION)
		return convert_union(node);
	
	return nullptr;
}

automaton *ast_converter::convert_uniop(uniop_node *node) {
	if(node->get_op() == *uniop::CLOSURE)
		return convert_closure(node);
	else if(node->get_op() == *uniop::CONTAINER)
		return convert_container(node);
	
	return nullptr;
}

automaton *ast_converter::convert_atomic(atomic_node *node) {
	if(node->get_tok().get_token_type() == token::type::t_atom) {
		return automaton_factory::create_string_automaton(node->get_tok().get_image());
	} else if(node->get_tok().get_token_type() == token::type::t_special) {
		char special = node->get_tok().get_image()[1];
		switch (special) {
			case 'e':
				return automaton_factory::create_epsilon_automaton();
			case 'd':
				return new automaton(*digit_automaton);
			case 's':
				return new automaton(*whitespace_automaton);
			case 'w':
				return new automaton(*word_automaton);
			default:
				break;
		}
	} else if (node->get_tok().get_token_type() == token::type::t_char_class) {
		std::vector<automaton*> created;
		int index = 0;
		std::string character_class = node->get_tok().get_image().substr(1);
		character_class = character_class.substr(0, character_class.size() - 1);
		while(index < character_class.size()) {
			char c = character_class[index];
			if(c == '\\') {
				char special = character_class[++index];
				auto image = std::string() + c + special;
				auto new_token_node = new atomic_node(token(token::type::t_special, image, index-1));
				created.push_back(convert_atomic(new_token_node));
				++index;
			} else {
				if(index < character_class.size() - 2 && character_class[index+1] == '-') {
					char end_range = character_class[index+2];
					auto rules = new ruleset();
					auto rule = new range_rule(0, 1, c, end_range);
					rules->add_rule(rule);
					rules->set_start_state(0);
					rules->add_accepting_state(1);
					created.push_back(new automaton(rules));
					
					
					
					index += 3;
				} else {
					auto rules = new ruleset();
					rules->add_rule(0, c, 1);
					rules->set_start_state(0);
					rules->add_accepting_state(1);
					created.push_back(new automaton(rules));
					
					index++;
				}
			}
		}
		
		return automaton_factory::create_union_automaton(created);
	}
	
	return nullptr;
}

automaton *ast_converter::convert_concat(binop_node *node) {
	automaton* left = convert_node(node->get_left());
	automaton* right = convert_node(node->get_right());
	return automaton_factory::create_concat_automaton(left, right);
}

automaton *ast_converter::convert_union(binop_node *node) {
	automaton* left = convert_node(node->get_left());
	automaton* right = convert_node(node->get_right());
	return automaton_factory::create_union_automaton(left, right);
}

automaton *ast_converter::convert_closure(uniop_node *node) {
	automaton* next = convert_node(node->get_internal());
	return automaton_factory::create_closure_automaton(next);
}

automaton *ast_converter::convert_container(uniop_node *node) {
	return convert_node(node->get_internal());
}

automaton *ast_converter::convert_expression(abstract_syntax_node *node) {
	return convert_node(node);
}

ast_converter::ast_converter() {
	auto bootstrap = new ast_converter(0);
	digit_automaton = full_automaton_generator::create(digit_regex, bootstrap);
	whitespace_automaton = full_automaton_generator::create(whitespace_regex, bootstrap);
	word_automaton = full_automaton_generator::create(word_regex, bootstrap);
}

ast_converter::ast_converter(int i) {}

std::string ast_converter::digit_regex = "[0-9]";
std::string ast_converter::word_regex = "[a-zA-Z0-9_]";
std::string ast_converter::whitespace_regex = "\t|\n|\v\f\r| ";

