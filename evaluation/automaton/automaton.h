//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_AUTOMATON_H
#define REGEXENGINE_AUTOMATON_H


#include "ruleset.h"

class automaton {
private:
	friend class automaton_factory;
	ruleset* rules;
	int min_created_state = -1;
	
	inline static bool any_reach_end(const std::string& str, std::vector<std::pair<int, int>> state_set) {
		return any_reach_end(str.size(), state_set);
	}
	static bool any_reach_end(int end, std::vector<std::pair<int, int>> state_set);

	int find_unused_state();
	bool has_epsilon_transitions();
protected:
	std::vector<int> get_used_states() const;
	int get_start_state() const;
	std::vector<int> get_accepting_states() const;
	
	
	
public:
	explicit automaton(ruleset *rules);
	
	automaton() : automaton(new ruleset()) {}
	
	bool accept(const std::string &start_input, bool full_match);
	
	class automaton_state_transpose {
	public:
		const int initial_state;
		const std::vector<int> final_states;
		
		automaton_state_transpose(int initial_state, std::vector<int> final_states);
	};
	automaton_state_transpose add_automaton(const automaton& other);
	
	void print_info() const;
	
	bool remove_epsilon_transitions();
};


#endif //REGEXENGINE_AUTOMATON_H
