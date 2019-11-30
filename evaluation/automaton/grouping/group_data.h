//
// Created by jradi on 11/29/2019.
//

#ifndef REGEXENGINETEST_GROUP_DATA_H
#define REGEXENGINETEST_GROUP_DATA_H


#include <vector>
#include <map>
#include "group.h"

class group_data {
private:
	std::vector<group *>* groups;
	std::map<std::string, group *>* name_dict;
public:
	group_data(const std::vector<group *> &groups, const std::map<std::string, group *> &name_dict);
	
	group_data();
	
	std::vector<group *> *get_groups();
	
	const std::map<std::string, group *> * get_name_dict() const;
	
	
	void integrate_group_info(group_data info);
};


#endif //REGEXENGINETEST_GROUP_DATA_H
