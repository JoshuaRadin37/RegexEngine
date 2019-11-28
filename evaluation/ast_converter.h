//
// Created by jradi on 11/1/2019.
//

#ifndef REGEXENGINE_AST_CONVERTER_H
#define REGEXENGINE_AST_CONVERTER_H


#include <evaluation/automaton/automaton.h>
#include <ast/nodes/abstract_syntax_node.h>
#include <ast/nodes/binop_node.h>
#include <ast/nodes/uniop_node.h>
#include <ast/nodes/atomic_node.h>

class ast_converter {



private:
	static std::string digit_regex;
	static std::string whitespace_regex;
	static std::string word_regex;
	
	const automaton* digit_automaton;
	const automaton* whitespace_automaton;
	const automaton* word_automaton;
	
	automaton* convert_node(abstract_syntax_node* node);
	
	automaton* convert_binop(binop_node* node);
	automaton* convert_uniop(uniop_node* node);
	automaton* convert_atomic(atomic_node* node);
	
	automaton* convert_concat(binop_node* node);
	automaton* convert_union(binop_node *node);
	automaton* convert_closure(uniop_node* node);
	automaton* convert_one_or_none(uniop_node* node);
	
	automaton* convert_one_or_more(uniop_node* node);
	automaton* convert_container(uniop_node* node);

public:
	explicit ast_converter(int i);

public:
	ast_converter();
	
	automaton* convert_expression(abstract_syntax_node* node);
};


#endif //REGEXENGINE_AST_CONVERTER_H
