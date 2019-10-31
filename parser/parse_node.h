//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_PARSE_NODE_H
#define REGEXENGINE_PARSE_NODE_H


#include <string>
#include <vector>

class parse_node {
protected:
	static std::string indent_look;
	std::string create_indent(int size);
public:
	virtual std::string get_terminals() = 0;
	virtual inline std::string tree_form() { return tree_form(0); }
	virtual std::string tree_form(int indent) = 0;
};


#endif //REGEXENGINE_PARSE_NODE_H
