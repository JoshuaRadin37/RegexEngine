//
// Created by jradi on 10/29/2019.
//

#include "abstract_syntax_node.h"


abstract_syntax_node::abstract_syntax_node(abstract_syntax_node::type type) : my_type(type) {}

abstract_syntax_node::type abstract_syntax_node::get_my_type() const {
	return my_type;
}


