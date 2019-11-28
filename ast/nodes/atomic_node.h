//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_ATOMIC_NODE_H
#define REGEXENGINE_ATOMIC_NODE_H

#include "abstract_syntax_node.h"
class atomic_node : public abstract_syntax_node {
private:
	token tok;
public:
	atomic_node(const token &tok);
	
	virtual std::string postfix() const override;
	
	virtual std::string prefix() const override;
	
	virtual std::string infix() const override;
	
	virtual std::vector<abstract_syntax_node *> get_children() override;
	
	const token &get_tok() const;
};



#endif //REGEXENGINE_ATOMIC_NODE_H
