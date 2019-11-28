//
// Created by jradi on 10/30/2019.
//

#ifndef REGEXENGINE_OP_H
#define REGEXENGINE_OP_H

#include <string>

class op {
private:
	int num_operands;
	std::string operator_string;
public:
	op(int num_operands, const std::string &operator_string) : num_operands(num_operands),
															   operator_string(operator_string) {}
	
	virtual std::string to_string() const {
		return operator_string;
	}
	
	int get_num_operands() const {
		return num_operands;
	}
	
	bool operator==(const op &rhs) const {
		return num_operands == rhs.num_operands &&
			   operator_string == rhs.operator_string;
	}
	
	bool operator!=(const op &rhs) const {
		return !(rhs == *this);
	}
	
};


#endif //REGEXENGINE_OP_H
