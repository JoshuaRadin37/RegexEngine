//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_UNIOP_NODE_H
#define REGEXENGINE_UNIOP_NODE_H

#include <ast/operators/uniop.h>
#include "abstract_syntax_node.h"

class uniop_node : public abstract_syntax_node {
private:
	abstract_syntax_node* internal;
	uniop* op;
public:
	uniop_node(abstract_syntax_node *internal, uniop *op);
	
	virtual std::string postfix() const override;
	
	virtual std::string prefix() const override;
	
	virtual std::string infix() const override;
	
	virtual std::vector<abstract_syntax_node *> get_children() override;
	
	abstract_syntax_node *get_internal() const;
	
	uniop * get_op() const;
};



#endif //REGEXENGINE_UNIOP_NODE_H
