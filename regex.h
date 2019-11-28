//
// Created by jradi on 11/3/2019.
//

#ifndef REGEXENGINE_REGEX_H
#define REGEXENGINE_REGEX_H


#include <evaluation/automaton/automaton.h>

class regex {
	automaton* aut;
public:
	explicit regex(const std::string& expression);
};


#endif //REGEXENGINE_REGEX_H
