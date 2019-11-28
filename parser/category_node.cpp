//
// Created by jradi on 10/29/2019.
//

#include <stdexcept>
#include "category_node.h"

std::string category_node::get_terminals() {
	std::string output;
	for (const auto &child_node : *children) {
		output += child_node->get_terminals();
	}
	return output;
}

const std::string &category_node::get_category() const {
	return category;
}

const std::vector<parse_node *> &category_node::get_children() const {
	return *children;
}

void category_node::add_child(parse_node *other) {
	children->push_back(other);
}

unsigned int category_node::num_children() {
	return children->size();
}




const char *category_node::category_not_found_exception::what() const noexcept {
	std::string output = "category ";
	output += cat;
	output += " not found.";
	return output.c_str();
}

category_node::category_not_found_exception::category_not_found_exception(const std::string &cat) : cat(cat) {}

parse_node *category_node::get_child(int index) {
	return (*children)[index];
}

category_node *category_node::get_child(const std::string &category) {
	for (const auto &item : *children) {
		auto cat_node = dynamic_cast<category_node *>(item);
		if(cat_node) {
			if(cat_node->category == category) return cat_node;
		}
	}
	throw category_not_found_exception(category);
	
}

std::string category_node::tree_form(int indent) {
	std::string output = create_indent(indent);
	output += category + "\n";
	for (const auto &child : *children) {
		output += child->tree_form(indent + 1);
	}
	return output;
}

std::string category_node::tree_form() {
	return parse_node::tree_form();
}

category_node::category_node(const std::string &category) : category(category) {}

bool category_node::has_child_category(std::string cat) {
	for (const auto &child : *children) {
		auto cat_node = dynamic_cast<category_node *>(child);
		if(cat_node) {
			if(cat_node->category == cat) return true;
		}
	}
	return false;
}
