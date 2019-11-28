//
// Created by jradi on 11/4/2019.
//

#include "character_class.h"

character_class::iterator::iterator(const std::vector<range<char> * >& ranges) {
	for (range<char> *range : ranges) {
		for (const char &c : *range) {
			all_chars.push_back(c);
		}
	}
}

const char &character_class::iterator::operator*() {
	return all_chars[index];
}

character_class::iterator &character_class::iterator::operator++() {
	++index;
	return (*this);
}

const character_class::iterator character_class::iterator::operator++(int) {
	auto clone = character_class::iterator(*this);
	++index;
	return clone;
}

bool character_class::iterator::operator!=(character_class::iterator other) {
	return index != other.index;
}

void character_class::add_range(range<char> *r) {
	ranges.push_back(r);
}

character_class::character_class() {

}

void character_class::add_range(char min, char max) {
	auto r = new range<char>(min, max);
	add_range(r);
}

void character_class::add_char(char c) {
	auto r = new singleton<char>(c);
	add_range(r);
}

character_class::iterator character_class::begin() const {
	return character_class::iterator(ranges);
}

const character_class::iterator character_class::end() const {
	auto output = begin();
	output.index = output.all_chars.size();
	return output;
}

std::string character_class::to_string() const {
	std::string output = "[";
	for (const auto &item : ranges) {
		output += item->to_string();
	}
	return output + "]";
}
