#pragma once
#include<iostream>
#include"val.h"
#include"lexer.h"
#include"ast.h"
using namespace std;
def expression(int start, int end, vector<token>& tokens) {
	while (val_st.size()) val_st.pop();
	while (op_st.size()) op_st.pop();
	for (int i = start; i <= end; i++) {
		if (tokens[i].type == INT || tokens[i].type == DOU || tokens[i].type == CHAR) val_st.push(new ast(tokens[i].num));
		if (tokens[i].type == VAL) val_st.push(new ast(tokens[i].val));
		if (tokens[i].type == OPERATOR) {
			if (tokens[i].op == "(") op_st.push("(");
			if (tokens[i].op == ")") {
				while (op_st.size() && op_st.top() != "(") addnode();
				op_st.pop();
			}
			if (tokens[i].op != "(" && tokens[i].op != ")") {
				while (op_st.size() && level[op_st.top()] >= level[tokens[i].op]) addnode();
				op_st.push(tokens[i].op);
			}
		}
	}
	while (op_st.size()) addnode();
	return val_st.top()->eval();
}