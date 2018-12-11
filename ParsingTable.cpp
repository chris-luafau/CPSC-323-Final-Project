#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "p1.h"

using namespace std;
class Language {
private:
	// Codex
	// -1 -> not valid
	//  0 -> lambda
	//  1 -> program J ; var V begin Y end
	//  2 -> L K
	//  3 -> D K
	//  4 -> U : X ;
	//  5 -> J B
	//  6 -> , U
	//  7 -> integer
	//  8 -> Z H 
	//  9 -> Y
	// 10 -> W
	// 11 -> A
	// 12 -> show ( J ) ;
	// 13 -> J = E ;
// 14 -> TQ
// 15 -> +TQ
// 16 -> -TQ
// 17 -> FR
// 18 -> *FR
// 19 -> /FR
// 20 -> ( E )
// 21 -> N
// 22 -> J
// 23 -> S D M
// 24 -> D M
// 25 -> +
// 26 -> -
// 27 -> 0
// 28 -> 1
// 29 -> 2
// 30 -> 3
// 31 -> 4
// 32 -> 5
// 33 -> 6
// 34 -> 7
// 35 -> 8
// 36 -> 9
// 37 -> a
// 38 -> b
// 39 -> c
// 40 -> d
// 41 -> e
////   P   V   B   E   I   S   ,   :   ;   =   (   )   +   -   *   /   C   a   b   c   d   e
//int parsing_table[22][22] = {
//	01, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // P
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02, 02, 02, 02, 02,   // J
//	-1, -1, -1, -1, -1, -1, 00, 00, 00, 00, -1, 00, 00, 00, 00, 00, 03, 02, 02, 02, 02, 02,   // K
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 04, 04, 04, 04, 04,   // V
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 05, 05, 05, 05, 05,   // U	
//	-1, -1, -1, -1, -1, -1, 06, 00, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // B
//	-1, -1, -1, -1, 07, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // X
//	-1, -1, -1, -1, -1,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8,  8,  8,  8,  8,   // Y
//	-1, -1, -1, 00, -1,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  9,  9,  9,  9,  9,   // H
//	-1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, 11, 11, 11, 11,   // Z
//	-1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // W
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 13, 13, 13, 13,   // A
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, 14, 14, -1, -1, 14, 14, 14, 14, 14, 14,   // E
//	-1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 15, 16, -1, -1, -1, -1, -1, -1, -1, -1,   // Q
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, 17, 17, -1, -1, 17, 17, 17, 17, 17, 17,   // T
//	-1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 00, 00, 18, 19, -1, -1, -1, -1, -1, -1,   // R
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, 21, 21, -1, -1, 21, 22, 22, 22, 22, 22,   // F
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, 23, -1, -1, -1, -1, -1, -1, -1, -1,   // N
//	-1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 00, 00, 00, 00, 24, -1, -1, -1, -1, -1,   // M
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 26, -1, -1, 00, -1, -1, -1, -1, -1,   // S
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1,   // D
//	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, 38, 39, 40, 41 }; // L

//   P   V   B   E   I   S   ,   :   ;   =   (   )   +   -   *   /   C   a   b   c   d   e
int parsing_table[22][22] = {
	01, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // P
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02, 02, 02, 02, 02,   // J
	-1, -1, -1, -1, -1, -1, 00, 00, 00, 00, -1, 00, 00, 00, 00, 00, 03, 02, 02, 02, 02, 02,   // K
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 04, 04, 04, 04, 04,   // V
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 05, 05, 05, 05, 05,   // U	
	-1, -1, -1, -1, -1, -1, 06, 00, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // B
	-1, -1, -1, -1, 07, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // X
	-1, -1, -1, -1, -1,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8,  8,  8,  8,  8,   // Y
	-1, -1, -1, 00, -1,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  9,  9,  9,  9,  9,   // H
	-1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, 11, 11, 11, 11,   // Z
	-1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // W
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 13, 13, 13, 13,   // A
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, 14, 14, -1, -1, 14, 14, 14, 14, 14, 14,   // E
	-1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 15, 16, -1, -1, -1, -1, -1, -1, -1, -1,   // Q
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, 17, 17, -1, -1, 17, 17, 17, 17, 17, 17,   // T
	-1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 00, 00, 18, 19, -1, -1, -1, -1, -1, -1,   // R
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, 21, 21, -1, -1, 21, 22, 22, 22, 22, 22,   // F
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, 23, -1, -1, -1, -1, -1, -1, -1, -1,   // N
	-1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 00, 00, 00, 00, 24, -1, -1, -1, -1, -1,   // M
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 26, -1, -1, 00, -1, -1, -1, -1, -1,   // S
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1,   // D
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, 38, 39, 40, 41 }; // L



vector <string>* stack;																	// used to keep of states still need to be processed
map <string, int> m = { { "P", 0 },{ "J", 1 },{ "K", 2 },{ "V", 3 },{ "U", 4 },{ "B", 5 },{ "X", 6 },{ "Y", 7 },{ "H", 8 },{ "Z", 9 },{ "W", 10 },{ "A", 11 },{ "E", 12 },{ "Q", 13 },{ "T", 14 },{ "R", 15 },{ "F", 16 },{ "N", 17 },{ "M", 18 },{ "S", 19 },{ "D", 20 },{ "L", 21 },		// Maps states to indexes in parsing table above
{ "program", 0 },{ "var", 1 },{ "begin", 2 },{ "end", 3 },{ "integer", 4 },{ "show", 5 },
{ ",", 6 },{ ":", 7 },{ ";", 8 },{ "=", 9 },{ "(", 10 },{ ")", 11 },{ "+", 12 },{ "-", 13 },{ "*", 14 },{ "/", 15 },
{ "C", 16 },
{ "a", 17 },{ "b", 18 },{ "c", 19 },{ "d", 20 },{ "e", 21 } };

public:
	bool parse(string filename);
	bool error_check(string input_text);
	bool reserved_words_check(vector<string> tokens);
	bool comma_check(vector<string> tokens);
	bool parenthesis_check(vector<string> tokens);
	bool semicolons_check(string input_text);
	bool undefined_var_check(vector<string> tokens);
};

bool Language::reserved_words_check(vector<string> tokens) {
	std::vector<std::string> reserved{ "program", "var", "integer", "show", "begin", "end" };
	for (auto& key : reserved) {
		if ((find(tokens.begin(), tokens.end(), key)) == tokens.end()) {
			std::cout << key + " is expected.";
			return false;
		}
	}
	return true;
}

bool Language::comma_check(vector<string> tokens) {
	int var_index = 0;
	int integer_index = 0;

	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == "var") {
			var_index = i;
			break;
		}
	}
	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == "integer") {
			integer_index = i;
			break;
		}
	}

	for (int i = var_index+1; i < integer_index-1; ++i) {
		string curr_word = tokens[i];
		string next_word = tokens[i + 1];
		if ((curr_word != ",") && (curr_word != ":")) {
			if ((next_word != ",") && (next_word != ":")) {
				std::cout << ", is missing";
				return false;
			}
			else
				i += 1;
		}
	}

	return true;
}

bool Language::parenthesis_check(vector<string> tokens) {
	vector<string> st;
	for (auto& t : tokens) {
		if (t == "(")
			st.push_back(t);
		else if (t == ")") {
			if (st.empty() || (st.back() != "(")) {
				cout << "( is missing";
				return false;
			}
			else
				st.pop_back();
		}
	}
	if (!st.empty()) {
		cout << ") is missing";
		return false;
	}
	return true;
}

bool Language::semicolons_check(string input_text) {
	istringstream lines(input_text);
	string line;
	while (getline(lines, line)) {
		istringstream words(line);
		string word;
		vector<string> curr_line;
		while (words >> word) {
			curr_line.push_back(word);
		}
		if (curr_line[0] != "var" && curr_line[0] != "begin" && curr_line[0] != "end") {
			if (curr_line.back() != ";") {
				std::cout << "; is missing";
				return false;
			}
			else
				continue;
		}
	}
	return true;
}

bool Language::undefined_var_check(vector<string> tokens) {
	int var_index = 0;
	int integer_index = 0;
	int begin_index = 0;

	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == "var") {
			var_index = i;
			break;
		}
	}
	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == "integer") {
			integer_index = i;
			break;
		}
	}
	for (int i = 0; i < tokens.size(); ++i) {
		if (tokens[i] == "begin") {
			begin_index = i;
			break;
		}
	}
	vector<string> variables;
	for (int j = var_index + 1; j < integer_index - 1; ++j) {
		if (tokens[j] != "," && tokens[j] != ":")
			variables.push_back(tokens[j]);
	}

	vector<string> chars{ "a","b","c","d","e" };
	vector<string> reserved{ "program", "var", "integer", "show", "begin", "end" };

	vector<string> valid_input;
	valid_input.reserve(variables.size() + chars.size() + reserved.size());
	valid_input.insert(std::end(valid_input), std::begin(variables), std::end(variables));
	valid_input.insert(std::end(valid_input), std::begin(chars), std::end(chars));
	valid_input.insert(std::end(valid_input), std::begin(reserved), std::end(reserved));

	for (int i = begin_index; i < tokens.size(); ++i) {
		string curr_word = tokens[i];
		if (find(valid_input.begin(), valid_input.end(), curr_word) == valid_input.end() && 
			!(isdigit(curr_word[0])) && !(ispunct(curr_word[0]))) {
			std::cout << "undefined identifier " + curr_word;
			return false;
		}
	}

	return true;
}


bool Language::error_check(string input_text) {
	vector<string> tokens;
	istringstream lines(input_text);
	string line;
	while (getline(lines, line)) {
		istringstream words(line);
		string word;
		while (words >> word) {
			tokens.push_back(word);
		}
	}
	bool c = (reserved_words_check(tokens) && comma_check(tokens) && parenthesis_check(tokens) && semicolons_check(input_text) && undefined_var_check(tokens));
	return c;
}


bool Language::parse(string filename) {
	string state;				// Current State
	string check = "\0";		// If state is terminal, checks if it matches char being read
	int parseId;			    // Used for parsing table to figure out what to push
	std::vector<std::string> reserved{ "program", "var", "integer", "show", "begin", "end" };
	stack = new vector<string>;

	ifstream in_file(filename);
	string input_text;

	getline(in_file, input_text, '\0');

	if (!error_check(input_text))
		return false;

	// Initial states to push
	stack->push_back("P");
	std::cout << "push P\n";


	istringstream lines(input_text);
	string line;

	while (getline(lines, line)) {
		istringstream word(line);
		string curr_word;

		while (word >> curr_word) {
			std::cout << "read " << curr_word << endl;

			for (auto& c : curr_word) {
				if (!isalnum(c)) {
					if (c != ',' && c != ':' && c != ';' && c != '=' && c != '(' && c != ')' && c != '+' && c != '*' && c != '/') {
						std::cout << c << "is not a valid symbol in the language.\n";
						return false;
					}
				}
			}

			do {
				// Output contents of stack
				vector<string>::iterator j = stack->begin();

				while (j != stack->end()) {
					std::cout << *j;
					j++;
				}
				std::cout << endl;

				//if (curr_word.empty())
				//	break;

				// Pop State
				state = stack->back();
				stack->pop_back();
				std::cout << "pop " << state << endl;

				// Check if state is a reserved word. If it is, break so we can get the next word in the line.
				if (std::find(reserved.begin(), reserved.end(), state) != reserved.end()) {
					break;
				}


				// Check if state is terminal
				char c = state[0];
				vector<char> chars{ 'a','b','c','d','e' };
				if ((isdigit(c) || c == ',' || c == ':' || c == ';' || c == '=' ||
					c == '(' || c == ')' || c == '+' || c == '*' || c == '/' || 
					find(chars.begin(), chars.end(), c) != chars.end()) /*&& c == curr_word[0]*/)
				{
					// read from string
					if (c == curr_word[0])
						curr_word.erase(0, 1);
					//else {
					//	std::cout << c << " was expected";
					//	return false;
					//}
				}

				// If state is non-terminal
				else if (state == "P" || state == "J" || state == "K" || state == "V" || state == "U" || state == "B" || state == "X" || state == "Y" || state == "H" || state == "Z" || state == "W" || state == "A" || state == "E" || state == "Q" || state == "T" || state == "R" || state == "F" || state == "N" || state == "M" || state == "S" || state == "D" || state == "L") {
					int x = m.find(state)->second;
					string tmp = "";

					int y = 0;
					// if curr_word is a reserved word, pass it as is
					if (std::find(reserved.begin(), reserved.end(), curr_word) != reserved.end()) 
						y = m.find(curr_word)->second;

					// if curr_word is a variable name, pass it character by character. If the character is a digit, then we have to pass "C".
					else 
					{
						tmp = string(1, curr_word[0]);
						if (!isdigit(tmp[0])) {
							y = m.find(string(1, curr_word[0]))->second;
							//y = m.find("G")->second;
						}
						else
							y = m.find("C")->second;
					}

					parseId = parsing_table[x][y];
					string temp = "";
					int i = 0;
					// Get code from parsing table and push states onto the stack accordingly
					switch (parseId) {
					case -1:
						// -1 means reject word
						// cases not handled yet: 
						// missing operators (+ - * /)
						// missing operands i.e. x = 1 * ;
						if (state == "P")
							std::cout << "program is expected.";
						else if (state == "V")
							std::cout << "var is expected.";
						else if (state == "K") {
							if (curr_word == "integer")
								std::cout << ": is missing";
						}
						else if (state == "Y" && curr_word == "=")
							std::cout << "begin is expected.";
						else if (state == "X")
							std::cout << "integer is expected or misspelled.";
						else if (state == "H" && curr_word == "(")
							std::cout << "show is expected or misspelled.";
						else if ((state == "H" && curr_word == "=") || (state == "E" && curr_word == ";") || 
							(state == "J" && curr_word == ";"))
							std::cout << "invalid expression";
						else
							std::cout << "Unable to find a match\n";
						return false;
					case 0:										// 0 means lambda, continue and pop next state
						std::cout << "push lambda\n";
						break;
					case 1:
						stack->push_back("end");
						stack->push_back("Y");
						stack->push_back("begin");
						stack->push_back("V");
						stack->push_back("var");
						stack->push_back(";");
						stack->push_back("J");
						stack->push_back("program");
						std::cout << "push end Y begin V var ; J program\n";
						break;
					case 2:
						stack->push_back("K");
						stack->push_back("L");
						std::cout << "push K L\n";
						break;
					case 3:
						stack->push_back("K");
						stack->push_back("D");
						std::cout << "push K D\n";
						break;
					case 4:
						stack->push_back(";");
						stack->push_back("X");
						stack->push_back(":");
						stack->push_back("U");
						std::cout << "push ; X : U\n";
						break;
					case 5:
						stack->push_back("B");
						stack->push_back("J");
						std::cout << "push B J\n";
						break;
					case 6:
						stack->push_back("U");
						stack->push_back(",");
						std::cout << "push U ,\n";
						break;
					case 7:
						stack->push_back("integer");
						std::cout << "integer a\n";
						break;
					case 8:
						stack->push_back("H");
						stack->push_back("Z");
						std::cout << "push H Z\n";
						break;
					case 9:
						stack->push_back("Y");
						std::cout << "push Y\n";
						break;
					case 10:
						stack->push_back("W");
						std::cout << "push W\n";
						break;
					case 11:
						stack->push_back("A");
						std::cout << "push A\n";
						break;
					case 12:
						stack->push_back(";");
						stack->push_back(")");
						stack->push_back("J");
						stack->push_back("(");
						stack->push_back("show");
						std::cout << "push ; ) J ( show\n";
						break;
					case 13:
						stack->push_back(";");
						stack->push_back("E");
						stack->push_back("=");
						stack->push_back("J");
						std::cout << "push ; E = J\n";
						break;
					case 14:
						stack->push_back("Q");
						stack->push_back("T");
						std::cout << "push Q T\n";
						break;
					case 15:
						stack->push_back("Q");
						stack->push_back("T");
						stack->push_back("+");
						std::cout << "push Q T +\n";
						break;
					case 16:
						stack->push_back("Q");
						stack->push_back("T");
						stack->push_back("-");
						std::cout << "push Q T -\n";
						break;
					case 17:
						stack->push_back("R");
						stack->push_back("F");
						std::cout << "push R F\n";
						break;
					case 18:
						stack->push_back("R");
						stack->push_back("F");
						stack->push_back("*");
						std::cout << "push R F *\n";
						break;
					case 19:
						stack->push_back("R");
						stack->push_back("F");
						stack->push_back("/");
						std::cout << "push R F /\n";
						break;
					case 20:
						stack->push_back(")");
						stack->push_back("E");
						stack->push_back("(");
						std::cout << "push ) E (\n";
						break;
					case 21:
						stack->push_back("M");
						std::cout << "push M\n";
						break;
					case 22:
						stack->push_back("J");
						std::cout << "push J\n";
						break;
					case 23:
						stack->push_back("M");
						stack->push_back("D");
						stack->push_back("S");
						std::cout << "push M D S\n";
						break;
					case 24:
						stack->push_back("M");
						stack->push_back("D");
						std::cout << "push M D\n";
						break;
					case 25:
						stack->push_back("+");
						std::cout << "push +\n";
						break;
					case 26:
						stack->push_back("-");
						std::cout << "push -\n";
						break;
					case 27:
						while (isdigit(curr_word[i])) {
							temp.push_back(curr_word[i]);
							i += 1;
						}
						stack->push_back(temp);
						std::cout << "push " << temp << "\n";
						break;
					case 37:
						stack->push_back("a");
						std::cout << "push a\n";
						break;
					case 38:
						stack->push_back("b");
						std::cout << "push b\n";
						break;
					case 39:
						stack->push_back("c");
						std::cout << "push c\n";
						break;
					case 40:
						stack->push_back("d");
						std::cout << "push d\n";
						break;
					case 41:
						stack->push_back("e");
						std::cout << "push e\n";
						break;
					default:
						break;
					}
				}


				// TODO if we reach an identify check that it isnt a reserved word and that it uses all valid letters and symbols


				/*else if (state == 'a' || state == '+' || state == '-' || state == '*' || state == '/' || state == '(' || state == ')' || state == '$') {
				check = state;
				if (check != word[i]) {
				std::cout << "Expected a " << check << " at this position.\n";
				return false;
				}
				std::cout << word[i] << " matches " << check << endl;
				}*/
			} while (check != curr_word);
		}
	}

	// read end push end accepted
	if (stack->size() == 0) {
		delete stack;
		return true;
	}
	else {
		delete stack;
		std::cout << "Forgot to put end at the end!\n";
		return false;
	}
	delete stack;
	return false;
}

int main() {

	/* PART I */
	std::ifstream in_file("finalp1.txt");
	std::ofstream o_file;

	ParseTextFile(in_file, o_file);

	/*************************************************************************/

	/* PART II */
	Language lang;
	bool accepted = lang.parse("finalp2.txt");
	if (accepted)
		std::cout << "No error";

	std::cin.ignore();
	std::cin.get();
	return 0;
}
