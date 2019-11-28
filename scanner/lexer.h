//
// Created by jradi on 10/28/2019.
//

#ifndef REGEXENGINE_LEXER_H
#define REGEXENGINE_LEXER_H


#include "token.h"
namespace scanning {
	class lexer {
	private:
		token current;
		int current_index = 0;
		std::string input;
		
		void create_next_token();
		
		inline char current_char() {
			return input[current_index];
		}
	
	public:
		lexer();
		
		lexer(const std::string &input);
		
		token get_current() const;
		
		const token &next();
		
		const token &operator++();
		
		const token operator++(int);
		
		const token &operator*();
	};
}

#endif //REGEXENGINE_LEXER_H
