//
// Created by jradi on 10/28/2019.
//

#ifndef REGEXENGINE_TOKEN_H
#define REGEXENGINE_TOKEN_H


#include <string>
#include <map>


class token_type_info;

class token {
public:
	
	
	
	enum class type{
		t_atom, // has image
		t_special, // those in form of '\c'
		t_char_class,
		t_lparen,
		t_rparen,
		t_union,
		t_star,
		t_plus,
		t_question,
		t_langle,
		t_rangle,
		t_lcurly,
		t_rcurly,
		t_EOF,
		t_string
	};
	
	enum class sub_type {
		s_nil,
		s_comma,
		s_digit
	};


	

private:
	token::type token_type;
	token::sub_type sub_token_type = sub_type::s_nil;
	std::string image;
	unsigned int index;

	static std::map<sub_type, type> sub_type_parent;
	
	friend class constructor;
	
	struct constructor {
		constructor();
	};
	
	static constructor cons;
	
	
public:
	token(type token_type, unsigned int index);
	token(type token_type, std::string image,  unsigned int index);
	token(type token_type, sub_type sub, unsigned int index) : token(token_type, index) {
		sub_token_type = sub;
	}
	token(type token_type, sub_type sub, std::string image,  unsigned int index) : token(token_type, image, index) {
		sub_token_type = sub;
	}
	token();
	
	type get_token_type() const;
	
	sub_type get_sub_token_type() const;
	
	const std::string &get_image() const;
	unsigned int get_index() const;
	
	static token ERROR;
	
	bool operator==(const token &rhs) const;
	
	bool operator!=(const token &rhs) const;
	
	bool is(token_type_info inf);
	bool is(type t_type);
	bool is(sub_type s_type);
	
	inline bool is_error() {
		return *this == ERROR;
	}
};


#endif //REGEXENGINE_TOKEN_H
