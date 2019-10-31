//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_CATEGORY_NODE_H
#define REGEXENGINE_CATEGORY_NODE_H


#include <string>
#include "parse_node.h"

class category_node : public parse_node{
private:
	std::string category;
	std::vector<parse_node*> *children = new std::vector<parse_node*>();

public:
class category_not_found_exception : public std::exception {
private:
	std::string cat;
public:
	explicit category_not_found_exception(const std::string &cat);
	
	const char *what() const noexcept override;
};
	
	category_node(const std::string &category);
	
	std::string get_terminals() override;
	
	const std::string &get_category() const;
	const std::vector<parse_node*>& get_children() const;
	
	void add_child(parse_node* other);
	unsigned int num_children();
	
	parse_node* get_child(int index);
	category_node* get_child(const std::string& category) noexcept(false);
	
	virtual std::string tree_form(int indent) override;
	
	virtual std::string tree_form() override;
	
	bool has_child_category(std::string cat);
	
};


#endif //REGEXENGINE_CATEGORY_NODE_H
