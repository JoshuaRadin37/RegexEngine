//
// Created by jradi on 10/28/2019.
//

#include "lexer.h"

using namespace std;
using type = token::type;
using sub_type = token::sub_type;

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
	image += c;
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
		case '<':
			current = token(type::t_langle, current_index++);
			break;
		case '>':
			current = token(type::t_rangle, current_index++);
			break;
		case '{':
			current = token(type::t_lcurly, current_index++);
			break;
		case '}':
			current = token(type::t_rcurly, current_index++);
			break;
		case '|':
			current = token(type::t_union, current_index++);
			break;
		case '+':
			current = token(type::t_plus, image,current_index++);
			break;
		case '?':
			current = token(type::t_question, image,current_index++);
			break;
		case '*':
			current = token(type::t_star, image,current_index++);
			break;
		case '\\': {
			int start_index = current_index;
			current_index++;
			char next = current_char();
			current_index++;
			image += next;
			current = token(type::t_special, image, start_index);
			break;
		}
		case ',': {
			current = token(type::t_atom, sub_type::s_comma, image, current_index++);
			break;
		}
		default:
			if(c >= '0' && c <= '9')
				current = token(type::t_atom, sub_type::s_digit, image, current_index++);
			else current = token(type::t_atom, image, current_index++);
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



static void replace(std::string& str, const std::string& from, const std::string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

scanning::lexer::lexer(const std::string &input) : input(input) {
	replace(this->input, std::string("()"), std::string("\\e"));
	replace(this->input, std::string("(|"), std::string("(\\e|"));
	replace(this->input, std::string("|)"), std::string("|\\e)"));
	create_next_token();
}

