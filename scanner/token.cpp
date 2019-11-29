//
// Created by jradi on 10/28/2019.
//

#include "token.h"
#include "token_type_info.h"

#include <utility>

token::token(token::type type, unsigned int index) : token_type(type), index(index), image("") { }

token::token(token::type token_type, std::string image, unsigned int index) : token_type(token_type),
																					 image(std::move(image)), index(index) {}

token::type token::get_token_type() const {
	return token_type;
}

const std::string &token::get_image() const {
	return image;
}

unsigned int token::get_index() const {
	return index;
}

token::token() : token(type::t_EOF, 0){ }
token token::ERROR = token();

bool token::operator==(const token &rhs) const {
	return token_type == rhs.token_type &&
		   image == rhs.image &&
		   index == rhs.index;
}

bool token::operator!=(const token &rhs) const {
	return !(rhs == *this);
}

bool token::is(token_type_info inf) {
	return this->token_type == inf.t && (inf.s == sub_type::s_nil || this->sub_token_type == inf.s);
}

std::map<sub_type, type> token::sub_type_parent = std::map<sub_type, type> ();
token::constructor token::cons = constructor();
token::constructor::constructor() {
	sub_type_parent.insert({sub_type::s_comma, type::t_atom});
	sub_type_parent.insert({sub_type::s_digit, type::t_atom});
}

bool token::is(type t_type) {
	return is(token_type_info(t_type));
}

bool token::is(sub_type s_type) {
	type t_type = token::sub_type_parent[s_type];
	return is(token_type_info(t_type, s_type));
}

sub_type token::get_sub_token_type() const {
	return sub_token_type;
}
