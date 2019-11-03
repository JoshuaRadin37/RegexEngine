//
// Created by jradi on 10/29/2019.
//

#include "uniop.h"

uniop::uniop(const std::string &operator_string) : op(1, operator_string) {

}


uniop* uniop::CLOSURE = new uniop("CLOSURE");
uniop* uniop::CONTAINER = new uniop("CONTAINER");
uniop* uniop::CHARACTER_CLASS = new uniop("CHARACTER_CLASS");