//
// Created by jradi on 10/29/2019.
//

#ifndef REGEXENGINE_BINOP_H
#define REGEXENGINE_BINOP_H

#include <string>
#include "op.h"

class binop : public op{

protected:
	explicit binop(const std::string &operator_string);

public:
	
	
	
	static binop* CONCAT;
	static binop* UNION;
};



#endif //REGEXENGINE_BINOP_H
