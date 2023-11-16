#include<iostream>
#include"lexer.h"
#include"val.h"
#include"expression.h"
using namespace std;
int main() {
	setlevel();
	string a = "x=(-3+10*2)%5 y=-x*10.1";
	vector<token> tokens = lexer(a);
	expression(0, 11, tokens);
	cout << expression(12, 17, tokens);
}