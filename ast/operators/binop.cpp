//
// Created by jradi on 10/29/2019.
//

#include "ast/nodes/abstract_syntax_node.h"
#include "binop.h"

binop* binop::CONCAT = new binop("CONCAT");
binop* binop::UNION = new binop("UNION");

binop::binop(const std::string &operator_string) : op(2, operator_string) {}

