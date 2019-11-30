//
// Created by Joshua on 11/28/2019.
//

#ifndef REGEXENGINETEST_TOKEN_TYPE_INFO_H
#define REGEXENGINETEST_TOKEN_TYPE_INFO_H

#include "token.h"

using type = token::type;
using sub_type = token::sub_type;

class token_type_info {
public:
	const type t;
	const sub_type s = sub_type::s_nil;
	
	explicit token_type_info(const type &t);
	
	token_type_info(const type &t, const sub_type &s);
};


#endif //REGEXENGINETEST_TOKEN_TYPE_INFO_H
