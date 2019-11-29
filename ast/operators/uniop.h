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
	friend class quanfitier_op;
	
	static uniop* CLOSURE;
	static uniop* NONE_OR_ONE;
	static uniop* ONE_OR_MORE;
	static uniop* CONTAINER;
	static uniop* CHARACTER_CLASS;
};


#endif //REGEXENGINE_UNIOP_H
