//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_RULE_H
#define REGEXENGINE_RULE_H


class rule {

private:
	int start_state;
	int end_state;
	bool force_occur;
public:
	rule(int start_state, int end_state, bool force_occur);
	
	/**
	 * Checks whether the current input character matches the rule
	 * @param input a character, supplied by the automaton
	 * @return the amount of characters to consume
	 */
	virtual bool match(char input, int* chars_consumed_ptr, int* next_state_ptr) const = 0;
	
	int get_start_state() const;
	
	int get_end_state() const;
	
	bool is_force_occur() const;
};


#endif //REGEXENGINE_RULE_H
