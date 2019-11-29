//
// Created by jradi on 10/30/2019.
//

#include "uniop_node.h"

uniop_node::uniop_node(abstract_syntax_node *internal, uniop *op)
		: abstract_syntax_node(type::uniop), internal(internal), op(op) {}

std::string uniop_node::postfix() const {
	return internal->postfix() + " " + op->to_string();
}

std::string uniop_node::prefix() const {
	return op->to_string() + " " + internal->prefix();
}

std::string uniop_node::infix() const {
	return internal->infix() + " " + op->to_string();
}

std::vector<abstract_syntax_node *> uniop_node::get_children() {
	return std::vector<abstract_syntax_node *>({internal});
}

abstract_syntax_node *uniop_node::get_internal() const {
	return internal;
}

uniop * uniop_node::get_op() const {
	return op;
}
