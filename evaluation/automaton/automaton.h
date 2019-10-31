//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_AUTOMATON_H
#define REGEXENGINE_AUTOMATON_H


#include "ruleset.h"

class automaton {
private:
	ruleset* rules;

public:
	automaton(ruleset *rules);
	
	bool accept(const std::string& input);
};


#endif //REGEXENGINE_AUTOMATON_H
