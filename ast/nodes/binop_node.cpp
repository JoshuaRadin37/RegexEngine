//
// Created by jradi on 10/30/2019.
//

#include "binop_node.h"

binop_node::binop_node(abstract_syntax_node *left, abstract_syntax_node *right,
					   const binop &op) : abstract_syntax_node(type::binop), left(left), right(right), op(op) {}

std::string binop_node::postfix() const {
	return left->postfix() + " " + right->postfix() + " " + op.to_string();
}

std::string binop_node::prefix() const {
	return op.to_string() + " " + left->prefix() + " " + right->prefix();
}

std::string binop_node::infix() const {
	return left->infix() + " " + op.to_string() + " " + right->infix();
}

std::vector<abstract_syntax_node *> binop_node::get_children() {
	return std::vector<abstract_syntax_node *>({left, right});
}

abstract_syntax_node *binop_node::get_left() const {
	return left;
}

abstract_syntax_node *binop_node::get_right() const {
	return right;
}

const binop &binop_node::get_op() const {
	return op;
}

