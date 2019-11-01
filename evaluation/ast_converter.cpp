//
// Created by jradi on 11/1/2019.
//

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
			default:
				break;
		}
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

ast_converter::ast_converter() : ast_converter(nullptr, nullptr) {
	auto bootstrap = new ast_converter(nullptr, nullptr);
	digit_automaton = full_automaton_generator::create(digit_regex, bootstrap);
	whitespace_automaton = full_automaton_generator::create(whitespace_regex, bootstrap);
}

ast_converter::ast_converter(automaton *digit_automaton, automaton *whitespace_automaton) : digit_automaton(
		digit_automaton), whitespace_automaton(whitespace_automaton) {}

std::string ast_converter::digit_regex = "0|1|2|3|4|5|6|7|8|9";
std::string ast_converter::whitespace_regex = "\t|\n|\v\f\r| ";

