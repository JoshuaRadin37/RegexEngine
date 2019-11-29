//
// Created by Joshua on 11/28/2019.
//

#ifndef REGEXENGINETEST_QUANTIFIER_OP_H
#define REGEXENGINETEST_QUANTIFIER_OP_H


#include "uniop.h"
#include "quantifier_info.h"

class quantifier_op : public uniop {
private:
	quantifier_info info;
public:
	quantifier_op(const std::string &operator_string, const quantifier_info &info);
};


#endif //REGEXENGINETEST_QUANTIFIER_OP_H
