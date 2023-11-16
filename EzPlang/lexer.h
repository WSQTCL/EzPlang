#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"val.h"
using namespace std;
char op[100] = { '+','-','*','/','%','!','&','|','>','<','=',',',';','\n','\'','{','}','(',')','[',']','^','\"' };
string keyword[100] = { "def","while","if","else","intinput","charinput","douinput","output","break","continue" };
bool check_keyword(string s) {
	for (int i = 0; i < 99; i++) if (s == keyword[i]) return true;
	return false;
}
class token {
public:
	Type type;
	string str;
	string val;
	string keyword;
	def num;
	string op;
	char ch;
	token() {}
	token(char cha) { type = CHAR; ch = cha; }
	token(string ch) { type = STRING; str = ch; }
	token(string ch,int a) { type = OPERATOR; op = ch; }
	token(string ch,int a,int b) { type = VAL; val = ch; }
	token(string ch,int a,int b,int c) { type = KEYWORD; keyword = ch; }
	token(def x,double a) { type = NUM; num = x; }
	void reset() {
		val = "";
		keyword = "";
		num.reset();
		op = "";
		str = "";
	}
};
ostream& operator << (ostream& out, const token& x) {
	if (x.type == INT) cout << x.num << " " << x.type;
	if (x.type == DOU) cout << x.num << " " << x.type;
	if (x.type == NUM) cout << x.num << " " << x.type;
	if (x.type == VAL) cout << x.val << " " << x.type;
	if (x.type == KEYWORD) cout << x.keyword << " " << x.type;
	if (x.type == OPERATOR) cout << x.op << " " << x.type;
	if (x.type == CHAR) cout << x.ch << " " << x.type;
	if (x.type == STRING) cout << x.str << " " << x.type;
	return out;
}
bool is_op(char a) {
	for (int i = 0; i <= 22; i++) if (a == op[i]) return true;
	return false;
}
bool is_alpha(char a) {
	if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z') return true;
	return false;
}
bool is_digit(char a) {
	if (a >= '0' && a <= '9') return true;
	return false;
}
bool check_escape_character(char a) {
	if (a == 't' || a == '\\' || a == '\'' || a == '\"' || a == 'n') return true;
	return false;
}
vector<token> lexer(string s) {
	vector<token> ans;
	int len = s.length();
	for (int i = 0; i < len; i++) {
		if (s[i] == '\"') {
			ans.push_back(token("\"", 1));
			i++;
			string tmpstr;
			tmpstr = "";
			while (s[i] != '\"') {
				if (i >= len) exit(1);
				if (s[i] == '\\') {
					if (i + 1 >= len || !check_escape_character(s[i + 1])) exit(1);
					else {
						i++;
						if (s[i] == 't') tmpstr += '\t';
						if (s[i] == '\\') tmpstr += '\\';
						if (s[i] == '\'') tmpstr += '\'';
						if (s[i] == '\"') tmpstr += '\"';
						if (s[i] == 'n') tmpstr += '\n';
						i++;
						continue;
					}
				}
				else {
					tmpstr += s[i];
					i++;
					continue;
				}
			}
			ans.push_back(token(tmpstr));
			ans.push_back(token("\"", 1));
			continue;
		}
		if (s[i] == '\'') {
			if (i + 2 >= len) exit(1);
			if (s[i + 1] != '\\') {
				if (s[i + 2] != '\'') exit(1);
				ans.push_back(token("\'", 1));
				ans.push_back(token(s[i + 1]));
				ans.push_back(token("\'", 1));
				i += 2;
				continue;
			}
			if (s[i + 1] == '\\') {
				if (i + 3 >= len || s[i + 3] != '\'' || !check_escape_character(s[i + 2])) exit(1);
				ans.push_back(token("\'", 1));
				if (s[i + 2] == 't') ans.push_back(token('\t'));
				if (s[i + 2] == 'n') ans.push_back(token('\n'));
				if (s[i + 2] == '\'') ans.push_back(token('\''));
				if (s[i + 2] == '\"') ans.push_back(token('\"'));
				if (s[i + 2] == '\\') ans.push_back(token('\\'));
				ans.push_back(token("\'", 1));
				i += 3;
				continue;
			}
		}
		if (s[i] == ' ' || s[i] == '\t') continue;
		if (is_op(s[i])) {
			string tmpop;
			tmpop = "";
			tmpop += s[i];
			if (s[i] == '|' && s[i + 1] == '|') {
				tmpop += s[i + 1];
				i++;
			}
			if (s[i] == '&' && s[i + 1] == '&') {
				tmpop += s[i + 1];
				i++;
			}
			if (s[i] == '!' && s[i + 1] == '=') {
				tmpop += s[i + 1];
				i++;
			}
			if (s[i] == '=' && s[i + 1] == '=') {
				tmpop += s[i + 1];
				i++;
			}
			if (s[i] == '>' && s[i + 1] == '=') {
				tmpop += s[i + 1];
				i++;
			}
			if (s[i] == '<' && s[i + 1] == '=') {
				tmpop += s[i + 1];
				i++;
			}
			ans.push_back(token(tmpop, 1));
			continue;
		}
		string tmpalpha;
		tmpalpha = "";
		if (is_alpha(s[i]) || s[i] == '_') {
			tmpalpha += s[i];
			i++;
			while (is_alpha(s[i]) || s[i] == '_' || is_digit(s[i])) {
				tmpalpha += s[i];
				i++;
			}
			i--;
			ans.push_back(token(tmpalpha, 1, 2));
			continue;
		}
		string tmpdigit;
		tmpdigit = "";
		bool is_decima;
		is_decima = false;
		if (is_digit(s[i])) {
			tmpdigit += s[i];
			i++;
			while (is_digit(s[i]) || s[i] == '.') {
				if (s[i] == '.') is_decima = true;
				tmpdigit += s[i];
				i++;
			}
			i--;
			if (is_decima == true) ans.push_back(token(stof(tmpdigit),1.1));
			else ans.push_back(token(stoi(tmpdigit),1.1));
			continue;
		}
		exit(1);
	}
	for (int i = 0; i < ans.size(); i++) {
		if (ans[i].type == OPERATOR) {
			if (ans[i].op == "+" || ans[i].op == "-") {
				if (i == 0 || ans[i - 1].op == "(" || ans[i - 1].op == "=" || ans[i - 1].op == "\n") {
					if (ans[i].op == "+") ans[i].op = "pos";
					if (ans[i].op == "-") ans[i].op = "neg";
				}
			}
		}
		if (ans[i].type == NUM) {
			if (ans[i].num.type == INT) ans[i].type = INT;
			if (ans[i].num.type == DOU) ans[i].type = DOU;
		}
		if (ans[i].type == VAL && check_keyword(ans[i].val)) {
			ans[i].type = KEYWORD;
			ans[i].keyword = ans[i].val;
			ans[i].val = "";
		}
	}
	return ans;
}