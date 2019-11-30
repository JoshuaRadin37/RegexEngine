//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_AUTOMATON_H
#define REGEXENGINE_AUTOMATON_H


#include <evaluation/automaton/grouping/group_data.h>
#include "ruleset.h"

class automaton {
private:
	friend class automaton_factory;
	friend class ast_converter;
	ruleset* rules;
	int min_created_state = -1;
	
	group_data* g_data = new group_data();
	
	inline static bool any_reach_end(const std::string& str, std::vector<std::pair<int, int>> state_set) {
		return any_reach_end(str.size(), state_set);
	}
	static bool any_reach_end(int end, std::vector<std::pair<int, int>> state_set);

	int find_unused_state();
	bool has_epsilon_transitions();
	
	group * create_group() const;
	
protected:
	std::vector<int> get_used_states() const;
	int get_start_state() const;
	std::vector<int> get_accepting_states() const;
	
	
	
public:
	explicit automaton(ruleset *rules);
	
	void add_self_as_group();
	
	automaton() : automaton(new ruleset()) {}
	
	bool accept(const std::string &start_input, bool full_match);
	
	class automaton_state_transpose {
	public:
		const int initial_state;
		const std::vector<int> final_states;
		
		automaton_state_transpose(int initial_state, std::vector<int> final_states);
	};
	automaton::automaton_state_transpose add_automaton(const automaton &other);
	automaton::automaton_state_transpose add_automaton(const automaton &other, bool integrate);
	void integrate_group_data(group_data data, std::map<int, int> transpose);
	
	void print_info() const;
	
	group_data get_group_data() const;
	
	bool remove_epsilon_transitions();
	void reorder_states();
};


#endif //REGEXENGINE_AUTOMATON_H
