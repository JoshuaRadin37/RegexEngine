//
// Created by jradi on 11/1/2019.
//

#ifndef REGEXENGINE_AUTOMATON_FACTORY_H
#define REGEXENGINE_AUTOMATON_FACTORY_H


#include <evaluation/automaton/automaton.h>

class automaton_factory {
public:
	static automaton* create_char_automaton(char c);
	static automaton* create_rule_automaton(rule* rule);
	static automaton* create_union_automaton(automaton* left, automaton* right);
	static automaton* create_concat_automaton(automaton* left, automaton* right);
	static automaton* create_concat_automaton(const std::vector<automaton *>& a);
	static automaton* create_closure_automaton(automaton* a);
	
};


#endif //REGEXENGINE_AUTOMATON_FACTORY_H
