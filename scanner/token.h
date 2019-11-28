//
// Created by jradi on 10/28/2019.
//

#ifndef REGEXENGINE_TOKEN_H
#define REGEXENGINE_TOKEN_H


#include <string>

class token {
public:
	enum class type {
		t_atom, // has image
		t_special, // those in form of '\c'
		t_char_class,
		t_lparen,
		t_rparen,
		t_union,
		t_star,
		t_plus,
		t_question,
		t_EOF
	};

private:
	token::type token_type;
	std::string image;
	unsigned int index;

public:
	token(type token_type, unsigned int index);
	token(type token_type, std::string image,  unsigned int index);
	token();
	
	type get_token_type() const;
	const std::string &get_image() const;
	unsigned int get_index() const;
	
	static token ERROR;
	
	bool operator==(const token &rhs) const;
	
	bool operator!=(const token &rhs) const;
	
	inline bool is_error() {
		return *this == ERROR;
	}
};


#endif //REGEXENGINE_TOKEN_H
