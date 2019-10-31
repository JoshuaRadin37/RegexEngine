//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_BINOP_NODE_H
#define REGEXENGINE_BINOP_NODE_H

#include "abstract_syntax_node.h"
#include "ast/operators/binop.h"

class binop_node : public abstract_syntax_node {
private:
	abstract_syntax_node* left;
	abstract_syntax_node* right;
	binop op;
public:
	binop_node(abstract_syntax_node *left, abstract_syntax_node *right, const binop &op);
	
	virtual std::string postfix() const override;
	
	virtual std::string prefix() const override;
	
	virtual std::string infix() const override;
	
	virtual std::vector<abstract_syntax_node *> get_children() override;
};



#endif //REGEXENGINE_BINOP_NODE_H
