//
// Created by Joshua on 11/28/2019.
//

#include "token_type_info.h"

token_type_info::token_type_info(const type &t) : t(t) {}

token_type_info::token_type_info(const type &t, const sub_type &s) : t(t), s(s) {}
