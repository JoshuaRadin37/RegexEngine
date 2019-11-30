//
// Created by jradi on 11/29/2019.
//

#include "group_data.h"

group_data::group_data() : groups(new std::vector<group *>()), name_dict(new std::map<std::string, group *>()){}
group_data::group_data(const std::vector<group *> &groups, const std::map<std::string, group *> &name_dict) : groups(
		new std::vector<group*>(groups)), name_dict(new std::map<std::string, group *>(name_dict)) {}


std::vector<group *> *group_data::get_groups() {
	return groups;
}

const std::map<std::string, group *>  * group_data::get_name_dict() const {
	return name_dict;
}


void group_data::integrate_group_info(group_data info) {
	for ( auto &get_group : *info.get_groups()) {
		this->groups->push_back(get_group);
	}
	
	for (const auto &kvp : *info.name_dict) {
		name_dict->emplace(kvp.first, kvp.second);
	}
}


