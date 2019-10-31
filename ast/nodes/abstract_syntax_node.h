//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_ABSTRACT_SYNTAX_NODE_H
#define REGEXENGINE_ABSTRACT_SYNTAX_NODE_H


#include <string>
#include <scanner/token.h>
#include <vector>


class abstract_syntax_node {
public:
	enum class type {
		binop,
		uniop,
		atom
	};

private:
	
	abstract_syntax_node::type my_type;

public:
	explicit abstract_syntax_node(type my_type);
	virtual std::string postfix() const = 0;
	virtual std::string prefix() const = 0;
	virtual std::string infix()const = 0;
	virtual std::vector<abstract_syntax_node *> get_children() = 0;
	
	
};


#endif //REGEXENGINE_ABSTRACT_SYNTAX_NODE_H
