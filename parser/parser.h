//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_PARSER_H
#define REGEXENGINE_PARSER_H


#include "category_node.h"
#include "../scanner/lexer.h"

/*
Collation-related bracket symbols [==] [::] [..]

Escaped characters \

Character set (bracket expression) []

Grouping ()

Single-character-ERE duplication * + ? {m,n}

Concatenation

Anchoring ^$

Alternation |


E -> <G><ET>
  -> eps
ET -> | <E>
   -> eps
G -> <S><GT>
GT -> <G>
   -> eps
S -> <X><ST>
ST -> *<ST>
   -> eps
X -> (<E>)
  -> <A>
A -> t_atom
  -> t_special
*/

class parser {

private:
	scanning::lexer *lexer;

	bool parse_expression(category_node* parent);
	bool parse_expression_tail(category_node* parent);
	
	bool parse_group(category_node* parent);
	bool parse_group_tail(category_node* parent);
	
	bool parse_segment(category_node* parent);
	bool parse_segment_tail(category_node* parent);
	
	bool parse_X(category_node* parent);
	
	bool parse_atom(category_node* parent);
	
	bool match(token::type tok);
	bool consume(token::type tok);
	token consume();
public:
	
	parser(scanning::lexer *my_lexer);
	
	category_node* parse_expression();
	
};


#endif //REGEXENGINE_PARSER_H
