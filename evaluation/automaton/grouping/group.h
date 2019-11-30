//
// Created by jradi on 11/29/2019.
//

#ifndef REGEXENGINETEST_GROUP_H
#define REGEXENGINETEST_GROUP_H


#include <vector>
#include <string>

class group {
private:
	union {
		int id;
		std::string* name;
	};
	bool has_name;
	int start_state;
	std::vector<int> final_states;

public:
	
	
	group(int id, int start_state, const std::vector<int> &final_states);
	
	group(std::string* name, int start_state, std::vector<int> final_states);
	
	
	
	int get_start_state() const;
	
	void set_start_state(int start_state);
	
	const std::vector<int> &get_final_states() const;
	
	void set_final_states(const std::vector<int> &final_states);
	
	int get_id() const;
	
	std::string get_name() const;
	
	bool is_has_name() const;
	
	void set_id(int id);
	
	std::string to_string() const;
};


#endif //REGEXENGINETEST_GROUP_H
