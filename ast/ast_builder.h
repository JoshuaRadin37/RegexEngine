//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_AST_BUILDER_H
#define REGEXENGINE_AST_BUILDER_H

#include <parser/parse_node.h>
#include <ast/nodes/abstract_syntax_node.h>
#include <ast/nodes/binop_node.h>
#include <ast/nodes/uniop_node.h>
#include <ast/nodes/atomic_node.h>
#include <parser/category_node.h>

namespace ast {
	
	class ast_builder {
	private:
		parse_node* head;
		bool built = false;
		abstract_syntax_node* output;
	
	public:
		explicit ast_builder(parse_node *head);
		
		bool build();
		
		abstract_syntax_node *get_output() const;
		
		bool is_built() const;
	
		
	private:
		binop_node* create_binop_node(binop op, abstract_syntax_node* left, abstract_syntax_node* right);
		uniop_node* create_uniop_node(uniop *op, abstract_syntax_node* affected);
		atomic_node* create_atomic_node(token tok);
		
		abstract_syntax_node* convert_category_node_to_ast_node(category_node* node);
		op *category_to_operator(const std::string &category, const token &tok = token::ERROR);
	};
	
}


#endif //REGEXENGINE_AST_BUILDER_H
