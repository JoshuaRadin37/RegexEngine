//
// Created by jradi on 11/29/2019.
//

#include "group.h"
#include "../vector_print.h"

int group::get_start_state() const {
	return start_state;
}

void group::set_start_state(int start_state) {
	group::start_state = start_state;
}

const std::vector<int> &group::get_final_states() const {
	return final_states;
}

void group::set_final_states(const std::vector<int> &final_states) {
	group::final_states = final_states;
}

group::group(int id, int start_state, const std::vector<int> &final_states) : id(id), has_name(false), start_state(start_state),
																			  final_states(final_states) {}

group::group(std::string* name, int start_state, std::vector<int> final_states) : name(name),
																							   has_name(true),
																							   start_state(start_state),
																							   final_states(std::move(
																									   final_states)) {}

int group::get_id() const {
	return id;
}

std::string group::get_name() const {
	return *name;
}

bool group::is_has_name() const {
	return has_name;
}

void group::set_id(int id) {
	group::id = id;
}

std::string group::to_string() const {
	std::string range = std::to_string(start_state) + " -> " + get_final_states();
	
	
	if(is_has_name()) return std::string() + "{" + *name + "} " + std::to_string(start_state) + " -> " + get_final_states();
	return std::string() + "{" + std::to_string(this->id) + "} " + range;
	
}

