//
// Created by jradi on 10/28/2019.
//

#include "token.h"

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

