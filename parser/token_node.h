//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_TOKEN_NODE_H
#define REGEXENGINE_TOKEN_NODE_H


#include "parse_node.h"
#include "../scanner/token.h"

class token_node : public parse_node {
private:
	token my_token;
public:
	token_node(const token &my_token);
	
	virtual std::string get_terminals() override;
	
	virtual std::string tree_form(int indent) override;
	
	const token &get_my_token() const;
};


#endif //REGEXENGINE_TOKEN_NODE_H
