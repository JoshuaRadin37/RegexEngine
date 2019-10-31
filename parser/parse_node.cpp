//
// Created by jradi on 10/29/2019.
//

#include "parse_node.h"
std::string parse_node::indent_look = "  ";
std::string parse_node::create_indent(int size) {
	std::string output;
	for (int i = 0; i < size; ++i) {
		output += indent_look;
	}
	return output;
}