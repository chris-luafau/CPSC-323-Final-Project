#include <iostream>
#include <vector>
#include <map>
#include <string>

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
							   // P   V   B   E   I   S   ,   :   ;   =   (   )   +   -   *   /   0   1   2   3   4   5   6   7   8   9   a   b   c   d   e
	int parsing_table[22][31] = { 01, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // P
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 02, 02, 02, 02, 02,   // J
								  -1, -1, -1, -1, -1, -1, 00, 00, 00, 00, -1, 00, 00, 00, 00, 00, 03, 03, 03, 03, 03, 03, 03, 03, 03, 03, 02, 02, 02, 02, 02,   // K
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 04, 04, 04, 04, 04,   // V
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 05, 05, 05, 05, 05,   // U	
								  -1, -1, -1, -1, -1, -1, 06, 00, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // B
								  -1, -1, -1, -1, 07, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // X
								  -1, -1, -1, -1, -1,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8,  8,  8,  8,  8,   // Y
								  -1, -1, -1, 00, -1,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  9,  9,  9,  9,  9,   // H
								  -1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, 11, 11, 11, 11,   // Z
								  -1, -1, -1, -1, -1, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // W
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 13, 13, 13, 13, 13,   // A
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14, -1, 14, 14, -1, -1, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,   // E
								  -1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 15, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // Q
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, 17, 17, -1, -1, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17,   // T
								  -1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 00, 00, 18, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // R
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, 21, 21, -1, -1, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22,   // F
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,   // N
								  -1, -1, -1, -1, -1, -1, -1, -1, 00, -1, -1, 00, 00, 00, 00, 00, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, -1, -1, -1, -1, -1,   // M
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 25, 26, -1, -1, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, -1, -1, -1, -1, -1,   // S
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, -1, -1, -1, -1, -1,   // D
								  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 37, 38, 39, 40, 41 }; // L

	vector <string>* stack;																	// used to keep of states still need to be processed
	map <string, int> m = { {"P", 0}, {"J", 1}, {"K", 2}, {"V", 3}, {"U", 4}, {"B", 5}, {"X", 6}, {"Y", 7}, {"H", 8}, {"Z", 9}, {"W", 10}, {"A", 11}, {"E", 12}, {"Q", 13}, {"T", 14}, {"R", 15}, {"F", 16}, {"N", 17}, {"M", 18}, {"S", 19}, {"D", 20}, {"L", 21},		// Maps states to indexes in parsing table above
							{"program", 0}, {"var", 1}, {"begin", 2}, {"end", 3}, {"show", 5},
							{",", 6}, {":", 7}, {";", 8}, {"=", 9}, {"(", 10}, {")", 11},{"+", 12},{"-", 13}, {"*", 15},
							{"0", 16}, {"1", 17}, {"2", 18}, {"3", 19}, {"4", 20}, {"5", 21}, {"6", 22}, {"7", 23}, {"8", 24}, {"9", 25},
							{"a", 26}, {"b", 27}, {"c", 28}, {"d", 29}, {"e", 30} };

public:
	bool parse(string word);
};

bool Language::parse(string word) {
	//TODO edit check for to check for reserved valid, valid IDs etc
	string state;				// Current State
	string check = "/0";		// If state is terminal, checks if it matches char being read
	int parseId;			    // Used for parsing table to figure out what to push

	stack = new vector<string>;

	// Initial states to push
	stack->push_back("end");
	cout << "push end\n";
	stack->push_back("P");
	cout << "push P\n";

	//TODO edit anything that uses word to a stream from a file
	//TODO this part needs to check reserved words and valid variables names I think
	for (int i = 0; i < word.length(); i++) {
		cout << "read " << word[i] << endl;
		// If read letter is not a part of the language, reject
		/*if (word[i] != "a" && word[i] != '+' && word[i] != '-' && word[i] != '*' && word[i] != '/' && word[i] != '(' && word[i] != ')' && word[i] != '$') {
			cout << word[i] << " is not a valid a letter in the language.\n";
			return false;
		}*/
		do {
			// Output contents of stack
			vector<string>::iterator j = stack->begin();

			while (j != stack->end()) {
				cout << *j;
				j++;
			}
			cout << endl;

			// Pop State
			state = stack->back();
			stack->pop_back();
			cout << "pop " << state << endl;

			// If state is non-terminal
			if (state == "P" || state == "J" || state == "K" || state == "V" || state == "U" || state == "B" || state == "X" || state == "Y" || state == "H" || state == "Z" || state == "W" || state == "A" || state == "E" || state == "Q" || state == "T" || state == "R" || state == "F" || state == "N" || state == "M" || state == "S" || state == "D" || state == "L" ) {
				int x = m.find(state)->second;
				int y = m.find("word[i]")->second;
				parseId = parsing_table[x][y];

				// Get code from parsing table and push states onto the stack accordingly
				switch (parseId) {
				case -1:
					cout << "Unable to find a match\n";		// -1 means reject word
					return false;
				case 0:										// 0 means lambda, continue and pop next state
					cout << "push lamba\n";
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
					cout << "push end Y begin V var ; J program\n";
					break;
				case 2:
					stack->push_back("K");
					stack->push_back("L");
					cout << "push K L\n";
					break;
				case 3:
					stack->push_back("K");
					stack->push_back("D");
					cout << "push K D\n";
					break;
				case 4:
					stack->push_back(";");
					stack->push_back("X");
					stack->push_back(":");
					stack->push_back("U");
					cout << "push ; X : U\n";
					break;
				case 5:
					stack->push_back("B");
					stack->push_back("J");
					cout << "push B J\n";
					break;
				case 6:
					stack->push_back("U");
					stack->push_back(",");
					cout << "push U ,\n";
					break;
				case 7:
					stack->push_back("integer");
					cout << "integer a\n";
					break;
				case 8:
					stack->push_back("H");
					stack->push_back("Z");
					cout << "push H Z\n";
					break;
				case 9:
					stack->push_back("Y");
					cout << "push Y\n";
					break;
				case 10:
					stack->push_back("W");
					cout << "push W\n";
					break;
				case 11:
					stack->push_back("A");
					cout << "push A\n";
					break;
				case 12:
					stack->push_back(";");
					stack->push_back(")");
					stack->push_back("J");
					stack->push_back("(");
					stack->push_back("show");
					cout << "push ; ) J ( show\n";
					break;
				case 13:
					stack->push_back(";");
					stack->push_back("E");
					stack->push_back("=");
					stack->push_back("J");
					cout << "push ; E = J\n";
					break;
				case 14:
					stack->push_back("Q");
					stack->push_back("T");
					cout << "push Q T\n";
					break;
				case 15:
					stack->push_back("Q");
					stack->push_back("T");
					stack->push_back("+");
					cout << "push Q T +\n";
					break;
				case 16:
					stack->push_back("Q");
					stack->push_back("T");
					stack->push_back("-");
					cout << "push Q T -\n";
					break;
				case 17:
					stack->push_back("R");
					stack->push_back("F");
					cout << "push R F\n";
					break;
				case 18:
					stack->push_back("R");
					stack->push_back("F");
					stack->push_back("*");
					cout << "push R F *\n";
					break;
				case 19:
					stack->push_back("R");
					stack->push_back("F");
					stack->push_back("/");
					cout << "push R F /\n";
					break;
				case 20:
					stack->push_back(")");
					stack->push_back("E");
					stack->push_back("(");
					cout << "push ) E (\n";
					break;
				case 21:
					stack->push_back("N");
					cout << "push M\n";
					break;
				case 22:
					stack->push_back("J");
					cout << "push J\n";
					break;
				case 23:
					stack->push_back("M");
					stack->push_back("D");
					stack->push_back("S");
					cout << "push M D S\n";
					break;
				case 24:
					stack->push_back("M");
					stack->push_back("D");
					cout << "push M D\n";
					break;
				case 25:
					stack->push_back("+");
					cout << "push +\n";
					break;
				case 26:
					stack->push_back("-");
					cout << "push -\n";
					break;
				case 27:
					stack->push_back("0");
					cout << "push 0\n";
					break;
				case 28:
					stack->push_back("1");
					cout << "push 1\n";
					break;
				case 29:
					stack->push_back("2");
					cout << "push 2\n";
					break;
				case 30:
					stack->push_back("3");
					cout << "push 3\n";
					break;
				case 31:
					stack->push_back("4");
					cout << "push 4\n";
					break;
				case 32:
					stack->push_back("5");
					cout << "push 5\n";
					break;
				case 33:
					stack->push_back("6");
					cout << "push 6\n";
					break;
				case 34:
					stack->push_back("7");
					cout << "push 7\n";
					break;
				case 35:
					stack->push_back("8");
					cout << "push 8\n";
					break;
				case 36:
					stack->push_back("9");
					cout << "push 9\n";
					break;
				case 37:
					stack->push_back("a");
					cout << "push a\n";
					break;
				case 38:
					stack->push_back("b");
					cout << "push b\n";
					break;
				case 39:
					stack->push_back("c");
					cout << "push c\n";
					break;
				case 40:
					stack->push_back("d");
					cout << "push d\n";
					break;
				case 41:
					stack->push_back("e");
					cout << "push e\n";
					break;
				default:
					break;
				}
			}

			// if state is terminal check if it matches read char
			// TODO this can be used for expected a reserved word or specific variable?
			/*else if (state == 'a' || state == '+' || state == '-' || state == '*' || state == '/' || state == '(' || state == ')' || state == '$') {
				check = state;
				if (check != word[i]) {
					cout << "Expected a " << check << " at this position.\n";
					return false;
				}
				cout << word[i] << " matches " << check << endl;
			}*/
		} while (check != "word[i]");
	}

	// read end push end accepted
	if (stack->size() == 0) {
		delete stack;
		return true;
	}
	else {
		delete stack;
		cout << "Forgot to put end at the end!\n";
		return false;
	}
	delete stack;
	return false;
}

int main() {
	/*Language1 L1;
	Language2 L2;
	string ans;
	int x;
	bool is_accepted;

	do {
		cout << "Please enter a word.\n";
		cin >> ans;
		cout << endl;

		do {
			cout << "Pick Language 1 (1) or Language 2 (2).\n";
			cin >> x;

			if (x != 1 && x != 2) {
				cout << "Invalid Answer! Pick 1 or 2!\n";
			}
		} while (x != 1 && x != 2);
		cout << endl;

		if (x == 1) {
			is_accepted = L1.parse(ans);
		}
		else {
			is_accepted = L2.parse(ans);
		}
		
		if (is_accepted) {
			cout << "\naccepted\n\n";
		}
		else {
			cout << "\nrejected\n\n";
		}
		cout << "Would you like to continue? y/n\n";
		cin >> ans;

		cout << endl;
	} while (ans == "y");*/
		
	return 0;
}
