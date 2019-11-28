//
// Created by jradi on 10/29/2019.
//

#include "token_node.h"

token_node::token_node(const token &my_token) : my_token(my_token) {}

std::string token_node::get_terminals() {
	return my_token.get_image();
}

std::string token_node::tree_form(int indent) {
	return create_indent(indent) + get_terminals() + "\n";
}

const token &token_node::get_my_token() const {
	return my_token;
}
