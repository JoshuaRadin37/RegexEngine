//
// Created by Joshua on 11/28/2019.
//

#ifndef REGEXENGINETEST_QUANTIFIER_INFO_H
#define REGEXENGINETEST_QUANTIFIER_INFO_H


#include <scanner/token.h>

struct quantifier_info {
	const int min;
	const int max;
	const bool has_min;
	const bool has_max;

private:
	quantifier_info(int min, int max, bool has_min, bool has_max);
	
	static quantifier_info min_q(int min);
	static quantifier_info max_q(int max);
	static quantifier_info min_and_max_q(int min, int max);
	static quantifier_info none();
};

struct quantifier {
	union {
		token* tok;
		quantifier_info info;
	};
	bool is_tok;
	
	
	explicit quantifier(token* tok);
	
	quantifier(const quantifier_info &info);
};


#endif //REGEXENGINETEST_QUANTIFIER_INFO_H
