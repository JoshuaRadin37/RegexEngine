//
// Created by jradi on 11/29/2019.
//

#ifndef REGEXENGINETEST_VECTOR_PRINT_H
#define REGEXENGINETEST_VECTOR_PRINT_H

#include <vector>
#include <iostream>
#include <sstream>

template <typename T>
static std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector) {
	os << "[";
	bool first = true;
	for (const T &item : vector) {
		if(!first) os << ", ";
		else first = false;
		os << item;
	}
	os << "]";
	return os;
}

template <typename T>
static std::string operator+(const std::string& s, const std::vector<T>& vector) {
	std::string o;
	o += "[";
	bool first = true;
	for (const T &item : vector) {
		if(!first) o += ", ";
		else first = false;
		std::stringstream str;
		str << item;
		o += str.str();
	}
	o += "]";
	return s + o;
}


#endif //REGEXENGINETEST_VECTOR_PRINT_H
