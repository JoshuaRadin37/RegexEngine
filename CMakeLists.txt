cmake_minimum_required(VERSION 3.10)
project(RegexEngine)


add_library(${PROJECT_NAME} scanner/token.cpp scanner/token.h
		scanner/lexer.cpp scanner/lexer.h parser/parser.cpp parser/parser.h parser/parse_node.cpp parser/parse_node.h parser/category_node.cpp parser/category_node.h parser/token_node.cpp parser/token_node.h
		ast/nodes/abstract_syntax_node.cpp ast/nodes/abstract_syntax_node.h ast/operators/binop.cpp
		ast/operators/binop.h ast/operators/uniop.cpp ast/operators/uniop.h ast/operators/op.h
		ast/ast_builder.cpp ast/ast_builder.h ast/nodes/atomic_node.cpp ast/nodes/atomic_node.h
		ast/nodes/binop_node.cpp ast/nodes/binop_node.h ast/nodes/uniop_node.cpp ast/nodes/uniop_node.h
		evaluation/rule.cpp evaluation/rule.h evaluation/rules/char_rule.cpp evaluation/rules/char_rule.h
		evaluation/rules/epsilon_rule.cpp evaluation/rules/epsilon_rule.h evaluation/automaton/ruleset.cpp
		evaluation/automaton/ruleset.h evaluation/automaton/automaton.cpp evaluation/automaton/automaton.h
		evaluation/rules/wrapper_rule.cpp evaluation/rules/wrapper_rule.h evaluation/automaton_factory.cpp
		evaluation/automaton_factory.h evaluation/ast_converter.cpp evaluation/ast_converter.h
		evaluation/full_automaton_generator.cpp evaluation/full_automaton_generator.h
		evaluation/rules/range_rule.cpp evaluation/rules/range_rule.h evaluation/rules/invert_rule.h
		evaluation/automaton/rule_requirement.cpp evaluation/automaton/rule_requirement.h
		regex.cpp regex.h evaluation/rules/character_class/character_class.cpp
		evaluation/rules/character_class/character_class.h
		evaluation/rules/character_class/fast_character_class_tester.cpp
		evaluation/rules/character_class/fast_character_class_tester.h
		evaluation/rules/character_class_rule.cpp evaluation/rules/character_class_rule.h
		evaluation/rules/inversions/invert_character_class.cpp
		evaluation/rules/inversions/invert_character_class.h
		evaluation/rules/character_class/comparable.h
		scanner/token_type_info.cpp scanner/token_type_info.h ast/operators/quantifier_info.cpp ast/operators/quantifier_info.h ast/operators/quantifier_op.cpp ast/operators/quantifier_op.h)

add_library(sub::lib ALIAS ${PROJECT_NAME})
include_directories(${PROJECT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME}
		PUBLIC
		${PROJECT_SOURCE_DIR}/
		)