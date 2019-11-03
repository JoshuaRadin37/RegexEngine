//
// Created by jradi on 10/28/2019.
//

#include "lexer.h"

using namespace std;
using type = token::type;

scanning::lexer::lexer() : input("") { }

token scanning::lexer::get_current() const {
	return current;
}

const token & scanning::lexer::next() {
	create_next_token();
	return current;
}

void scanning::lexer::create_next_token() {
	std::string image;
	if(current_index == input.length()) {
		current = token(type::t_EOF, current_index);
		return;
	}
	char c = current_char();
	switch (c) {
		case '[': {
			int start_index = current_index;
			bool matched = false;
			while(!matched && current_index < input.size()) {
				image += current_char();
				if(current_char() == ']') matched = true;
				current_index++;
			}
			if(!matched || image == "[]") current = token::ERROR;
			else current = token(type::t_char_class, image, start_index);
		}
			break;
		case '(':
			current = token(type::t_lparen, current_index++);
			break;
		case ')':
			current = token(type::t_rparen, current_index++);
			break;
		case '|':
			current = token(type::t_union, current_index++);
			break;
		case '*':
			current = token(type::t_star, current_index++);
			break;
		case '\\': {
			int start_index = current_index;
			current_index++;
			char next = current_char();
			current_index++;
			image = string() + c + next;
			current = token(type::t_special, image, start_index);
			break;
		}
		default:
			image += c;
			current = token(type::t_atom, image, current_index++);
			break;
	}
}

/**
 * (*this)++
 * @return
 */
const token &scanning::lexer::operator++() {
	return next();
}

/**
 * ++(*this)
 * @return
 */
const token scanning::lexer::operator++(int) {
	const token output = current;
	create_next_token();
	return output;
}

const token &scanning::lexer::operator*() {
	return current;
}

scanning::lexer::lexer(const std::string &input) : input(input) {
	create_next_token();
}

