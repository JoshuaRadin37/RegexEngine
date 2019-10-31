//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_UNIOP_H
#define REGEXENGINE_UNIOP_H


#include <string>
#include "op.h"

class uniop : public op{

protected:
	explicit uniop(const std::string &operator_string);

public:
	
	
	static uniop* CLOSURE;
	static uniop* CONTAINER;
};


#endif //REGEXENGINE_UNIOP_H
