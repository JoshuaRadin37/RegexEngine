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
	const bool exactly;
	quantifier_info(int min, int max, bool has_min, bool has_max, bool exactly);
	
	static quantifier_info exactly_q(int exact);
	static quantifier_info min_q(int min);
	static quantifier_info max_q(int max);
	static quantifier_info min_and_max_q(int min, int max);
	static quantifier_info none();
	
	std::string to_string() const;
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
