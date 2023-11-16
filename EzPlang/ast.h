#pragma once
#include<iostream>
#include"val.h"
#include"lexer.h"
#include"expression.h"
#include<map>
#include<stack>
using namespace std;
map<string, def> mp_val;
stack<string> op_st;
class ast {
public:
	def x;
	string op;
	string val;
	Type type;
	ast* L;
	ast* R;
	ast() {};
	ast(ast* _L, string _op, ast* _R) {
		L = _L; R = _R; op = _op;
	}
	ast(string _val) {
		type = VAL;
		val = _val;
	}
	ast(def _x) {
		type = NUM;
		x = _x;
	}
	def eval() {
		if (type == NUM) return x;
		else if (type == VAL) return mp_val[val];
		if (op == "+") return L->eval() + R->eval();
		if (op == "-") return L->eval() - R->eval();
		if (op == "*") return L->eval() * R->eval();
		if (op == "/") return L->eval() / R->eval();
		if (op == "%") return L->eval() % R->eval();
		if (op == "|") return L->eval() | R->eval();
		if (op == "&") return L->eval() & R->eval();
		if (op == "^") return L->eval() ^ R->eval();
		if (op == ">") return L->eval() > R->eval();
		if (op == "<") return L->eval() < R->eval();
		if (op == ">=") return L->eval() >= R->eval();
		if (op == "<=") return L->eval() <= R->eval();
		if (op == "==") return L->eval() == R->eval();
		if (op == "!=") return L->eval() != R->eval();
		if (op == "&&") return L->eval() && R->eval();
		if (op == "||") return L->eval() || R->eval();
		if (op == "!") return !(R->eval() == 1);
		if (op == "neg") return L->eval() - R->eval();
		if (op == "pos") return L->eval() + R->eval();
		if (op == "="){
			mp_val[L->val] = R->eval();
			return R->eval();
		}
	}
};
stack<ast*> val_st;
void addnode() {
	string op;
	ast* L;
	ast* R;
	R = val_st.top(); val_st.pop();
	L = new ast(def(0));
	op = op_st.top(); op_st.pop();
	if (op == "!" || op == "neg" || op == "pos") {
		val_st.push(new ast(L, op, R));
	}
	else if (val_st.size()) {
		L = val_st.top();
		val_st.pop();
		val_st.push(new ast(L, op, R));
	}
}