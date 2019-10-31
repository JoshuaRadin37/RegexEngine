//
// Created by jradi on 10/30/2019.
//

#include "atomic_node.h"

atomic_node::atomic_node(const token &tok) : abstract_syntax_node(type::atom),
											 tok(tok) {}

std::string atomic_node::postfix() const {
	return tok.get_image();
}

std::string atomic_node::prefix() const {
	return tok.get_image();
}

std::string atomic_node::infix() const {
	return tok.get_image();
}

std::vector<abstract_syntax_node *> atomic_node::get_children() {
	return std::vector<abstract_syntax_node *>();
}
