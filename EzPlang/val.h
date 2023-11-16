#pragma once
#include<iostream>
#include<string>
#include<map>
using namespace std;
map<string, short> level;
void setlevel() {
	level["="] = 1; level["||"] = 2; level["&&"] = 3; level["|"] = 4; level["^"] = 5; level["&"] = 6;
	level["=="] = level["!="] = 7;
	level["<"] = level[">"] = level["<="] = level[">="] = 8;
	level["+"] = level["-"] = 9;
	level["*"] = level["/"] = level["%"] = 10;
	level["!"] = level["neg"] = level["pos"] = 11;
}
enum Type { INT, DOU, CHAR, NUM, KEYWORD, OPERATOR, VAL, STRING };
class def {
private:
	long long int_val;
	double dou_val;
	char char_val;
	unsigned long long address;
public:
	bool is_array;
	Type type;
	def() {}
	def(bool val) { int_val = val; type = INT; }
	def(long long val) { int_val = val; type = INT; }
	def(int val) { int_val = val; type = INT; }
	def(double val) { dou_val = val; type = DOU; }
	def(char val) { char_val = val; type = CHAR; }
	friend ostream & operator << (ostream& out, const def& x);
	friend def operator +(def a, def b);
	friend def operator -(def a, def b);
	friend def operator *(def a, def b);
	friend def operator /(def a, def b);
	friend def operator %(def a, def b);
	friend def operator &(def a, def b);
	friend def operator |(def a, def b);
	friend def operator ^(def a, def b);
	friend bool operator &&(def a, def b);
	friend bool operator ||(def a, def b);
	friend bool operator !=(def a, def b);
	friend bool operator ==(def a, def b);
	friend bool operator >(def a, def b);
	friend bool operator >=(def a, def b);
	friend bool operator <(def a, def b);
	friend bool operator <=(def a, def b);
	void reset() {
		int_val = 0;
		dou_val = 0;
		char_val = ' ';
	}
};
ostream& operator << (ostream& out, const def& x) {
	if (x.type == INT) cout << x.int_val;
	if (x.type == DOU) cout << x.dou_val;
	if (x.type == CHAR) cout << x.char_val;
	return out;
}
def operator + (def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val + b.int_val;
		else return a.int_val + b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val + b.int_val;
		else return a.dou_val + b.dou_val;
	}
}
def operator - (def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val - b.int_val;
		else return a.int_val - b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val - b.int_val;
		else return a.dou_val - b.dou_val;
	}
}
def operator * (def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val * b.int_val;
		else return a.int_val * b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val * b.int_val;
		else return a.dou_val * b.dou_val;
	}
}
def operator / (def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val / b.int_val;
		else return a.int_val / b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val / b.int_val;
		else return a.dou_val / b.dou_val;
	}
}
def operator % (def a, def b) {
	if (a.type == CHAR || b.type == CHAR || a.type == DOU || b.type == DOU) exit(1);
	return a.int_val % b.int_val;
}
def operator &(def a, def b) {
	if (a.type != INT || b.type != INT) exit(1);
	return a.int_val & b.int_val;
}
def operator |(def a, def b) {
	if (a.type != INT || b.type != INT) exit(1);
	return a.int_val | b.int_val;
}
def operator ^(def a, def b) {
	if (a.type != INT || b.type != INT) exit(1);
	return a.int_val ^ b.int_val;
}
bool operator &&(def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val && b.int_val;
		else return a.int_val && b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val && b.int_val;
		else return a.dou_val && b.dou_val;
	}
}
bool operator ||(def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val || b.int_val;
		else return a.int_val || b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val || b.int_val;
		else return a.dou_val || b.dou_val;
	}
}
bool operator !=(def a, def b) {
	if (a.type != b.type) return true;
	if (a.type == INT) return a.int_val != b.int_val;
	if (a.type == DOU) return a.dou_val != b.dou_val;
	if (a.type == CHAR) return a.char_val != b.char_val;
}
bool operator ==(def a, def b) {
	if (a.type != b.type) return false;
	if (a.type == INT) return a.int_val == b.int_val;
	if (a.type == DOU) return a.dou_val == b.dou_val;
	if (a.type == CHAR) return a.char_val == b.char_val;
}
bool operator >(def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val > b.int_val;
		return a.int_val > b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val > b.int_val;
		return a.dou_val > b.dou_val;
	}
}
bool operator >=(def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val >= b.int_val;
		return a.int_val >= b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val >= b.int_val;
		return a.dou_val >= b.dou_val;
	}
}
bool operator <(def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val < b.int_val;
		return a.int_val < b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val < b.int_val;
		return a.dou_val < b.dou_val;
	}
}
bool operator <=(def a, def b) {
	if (a.type == CHAR || b.type == CHAR) exit(1);
	if (a.type == INT) {
		if (b.type == INT) return a.int_val <= b.int_val;
		return a.int_val <= b.dou_val;
	}
	if (a.type == DOU) {
		if (b.type == INT) return a.dou_val <= b.int_val;
		return a.dou_val <= b.dou_val;
	}
}