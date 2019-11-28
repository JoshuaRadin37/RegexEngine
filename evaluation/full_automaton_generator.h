//
// Created by jradi on 11/1/2019.
//

#ifndef REGEXENGINE_FULL_AUTOMATON_GENERATOR_H
#define REGEXENGINE_FULL_AUTOMATON_GENERATOR_H


#include <evaluation/automaton/automaton.h>
#include "ast_converter.h"

class full_automaton_generator {
public:
	static automaton* create(const std::string& str);
	static automaton* create(const std::string& str, ast_converter* converter);
};


#endif //REGEXENGINE_FULL_AUTOMATON_GENERATOR_H
