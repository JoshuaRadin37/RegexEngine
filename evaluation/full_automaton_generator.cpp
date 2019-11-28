//
// Created by jradi on 11/1/2019.
//

#include <scanner/lexer.h>
#include <parser/parser.h>
#include <ast/ast_builder.h>
#include "full_automaton_generator.h"
#include "ast_converter.h"

automaton *full_automaton_generator::create(const std::string &str) {
	ast_converter *converter = new ast_converter();
	automaton *p_automaton = create(str, converter);
	delete converter;
	return p_automaton;
}

automaton *full_automaton_generator::create(const std::string &str, ast_converter *converter) {
	auto lex = new scanning::lexer(str);
	auto my_parser = new parser(lex);
	category_node *expression = my_parser->parse_expression();
	if (expression == nullptr)
		return nullptr;
	
	auto builder = new ast::ast_builder(expression);
	builder->build();
	if(!builder->is_built()) return nullptr;
	
	auto output = converter->convert_expression(builder->get_output());
	
	delete lex;
	delete my_parser;
	return output;
}
