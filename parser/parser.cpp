//
// Created by jradi on 10/29/2019.
//

#include "parser.h"
#include "token_node.h"

#include <utility>

using type = token::type;

parser::parser(scanning::lexer *my_lexer) : lexer(my_lexer) {}

bool parser::match(type tok) {
	return lexer->get_current().is(tok);
}

bool parser::consume(type tok) {
	bool output = match(tok);
	if(output) ++(*lexer);
	return output;
}

bool parser::match(token::sub_type tok) {
	return lexer->get_current().is(tok);
}

bool parser::consume(token::sub_type tok) {
	bool output = match(tok);
	if(output) ++(*lexer);
	return output;
}

bool parser::match(std::string image, token::type t_type) {
	if(!match(t_type)) return false;
	auto current_image = lexer->get_current().get_image();
	return current_image == image;
}

bool parser::consume(std::string image, token::type t_type) {
	bool output = match(image, t_type);
	if(output) ++(*lexer);
	return output;
}

token parser::consume() {
	return (*lexer)++;
}

/*
E -> <G><ET>
ET -> | <E>
   -> eps
G -> <S><GT>
GT -> <G>
   -> eps
S -> <X><ST>
ST -> (*|?|+)<ST>
   -> <Q><ST>
   -> eps
X -> (<E>)
  -> <A>
A -> t_atom
  -> t_special
Q -> {n?(,n?)?}
*/
category_node *parser::parse_expression() {
	auto output = new category_node("expression");
	if(!parse_group(output)) return nullptr;
	if(!parse_expression_tail(output)) return nullptr;
	return output;
}

bool parser::parse_expression(category_node *parent) {
	auto child = new category_node("expression");
	switch (lexer->get_current().get_token_type()) {
		
		case token::type::t_char_class:
		case token::type::t_atom:
		case token::type::t_special:
		case token::type::t_lparen:
		{
			if(!parse_group(child)) return false;
			if(!parse_expression_tail(child)) return false;
			parent->add_child(child);
		}
			break;
		case token::type::t_EOF:
		case token::type::t_rparen:
			parent->add_child(child);
			break;
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_expression_tail(category_node *parent) {
	auto child = new category_node("expression_tail");
	switch (lexer->get_current().get_token_type()) {
		case token::type::t_union:
			consume(type::t_union);
			if(!parse_expression(child)) return false;
			parent->add_child(child);
		default:
			break;
	}
	
	return true;
}

bool parser::parse_group(category_node *parent) {
	auto child = new category_node("group");
	switch (lexer->get_current().get_token_type()) {
		
		case token::type::t_char_class:
		case token::type::t_atom:
		case token::type::t_special:
		case token::type::t_lparen:
		{
			if(!parse_segment(child)) return false;
			if(!parse_group_tail(child)) return false;
			parent->add_child(child);
		}
			break;
		
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_group_tail(category_node *parent) {
	auto child = new category_node("group_tail");
	switch (lexer->get_current().get_token_type()) {
		
		case token::type::t_char_class:
		case token::type::t_atom:
		case token::type::t_special:
		case token::type::t_lparen:
			if(!parse_group(child)) return false;
			parent->add_child(child);
		default:
			break;
	}
	
	return true;
}

/*
S -> <X><ST>
ST -> *<ST>
 */
bool parser::parse_segment(category_node *parent) {
	auto child = new category_node("segment");
	switch (lexer->get_current().get_token_type()) {
		
		case token::type::t_char_class:
		case token::type::t_atom:
		case token::type::t_special:
		case token::type::t_lparen:
		{
			if(!parse_X(child)) return false;
			if(!parse_segment_tail(child)) return false;
			parent->add_child(child);
		}
			break;
		
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_segment_tail(category_node *parent) {
	auto child = new category_node("segment_tail");
	switch (lexer->get_current().get_token_type()) {
		case token::type::t_star:
		case type::t_plus:
		case type::t_question: {
			const token &token = consume();
			auto node = new token_node(token);
			child->add_child(node);
			if (!parse_segment_tail(child)) return false;
			parent->add_child(child);
			break;
		}
		case type::t_lcurly: {
			if(!parse_quantifier(child)) return false;
			if(!parse_segment_tail(child)) return false;
			parent->add_child(child);
			break;
		}
		default:
			break;
	}
	
	return true;
}

bool parser::parse_quantifier(category_node *parent) {
	auto child = new category_node("quantifier");
	switch (lexer->get_current().get_token_type()) {
		case token::type::t_lcurly: {
			consume();
			if(!parse_int(child)) {
				if(!parse_quantifier_tail(child)) return false;
			}else{
				parse_quantifier_tail(child);
			}
			if(!consume(type::t_rcurly)) {
				return false;
			}
			parent->add_child(child);
			break;
		}
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_quantifier_tail(category_node *parent) {
	auto child = new category_node("quantifier_tail");
	
	switch (lexer->get_current().get_token_type()) {
		case token::type::t_atom:
			if(!consume(token::sub_type::s_comma)) return false;
			parse_int(child);
			parent->add_child(child);
			break;
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_X(category_node *parent) {
	auto child = new category_node("inter");
	switch (lexer->get_current().get_token_type()) {
		
		case token::type::t_char_class:
		case token::type::t_atom:
		case token::type::t_special:
		{
			if(!parse_atom(child)) return false;
			parent->add_child(child);
		}
			break;
		case token::type::t_lparen:
			consume(type::t_lparen);
			if(!parse_expression(child)) return false;
			if(!consume(type::t_rparen)) return false;
			parent->add_child(child);
			break;
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_atom(category_node *parent) {
	auto child = new category_node("atom");
	
	switch (lexer->get_current().get_token_type()) {
		case token::type::t_char_class:
		case token::type::t_atom:
		case token::type::t_special: {
			std::string terminals = lexer->get_current().get_image();
			auto terminals_node = new token_node(consume());
			child->add_child(terminals_node);
			parent->add_child(child);
		}
			break;
		default:
			return false;
	}
	
	return true;
}

bool parser::parse_int(category_node *parent) {
	
	std::string image;
	bool found_one = false;
	
	while(match(token::sub_type::s_digit)) {
		if(!found_one) found_one = true;
		char d = consume().get_image()[0];
		image += d;
	}
	
	if(found_one) {
		auto child = new category_node("int");
		child->add_child(new token_node(image));
		parent->add_child(child);
	}
	
	return found_one;
}
