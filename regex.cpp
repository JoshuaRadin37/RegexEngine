//
// Created by jradi on 11/3/2019.
//

#include "regex.h"
#include <evaluation/full_automaton_generator.h>

regex::regex(const std::string &expression) {
	aut = full_automaton_generator::create(expression);
}
