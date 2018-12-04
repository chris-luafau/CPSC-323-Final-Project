#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Language1 {
private:
	// Codex
	//  0 -> not valid
	// 10 -> TQ
	// 20 -> +TQ
	// 30 -> -TQ
	// 40 -> FR
	// 50 -> *FR
	// 60 -> /FR
	// 70 -> a
	// 80 -> (E)
	// 90 -> lamba
	int parsing_table[5][8] = { 10,  0,  0,  0,  0, 10,  0,  0,
							     0, 20, 30,  0,  0,  0, 90, 90,
							    40,  0,  0,  0,  0, 40,  0,  0,
								 0, 90, 90, 50, 60,  0, 90, 90,
							    70,  0,  0,  0,  0, 80,  0,  0 };
	vector <char>* stack;																// used to keep of states still need to be processed
	map <char, int> m = { {'E', 0}, {'Q', 1}, {'T', 2}, {'R', 3}, {'F', 4},				// Maps states to indexes in parsing table above
						  {'a', 0}, {'+', 1}, {'-', 2}, {'*', 3}, {'/', 4}, {'(', 5}, {')', 6}, {'$', 7} };

public:
	bool parse(string word);
};

class Language2 {
private:
	// Codex
	//  0 -> not valid
	// 10 -> a=E
	// 20 -> TQ
	// 25 -> +TQ
	// 30 -> -TQ
	// 40 -> FR
	// 45 -> *FR
	// 50 -> /FR
	// 60 -> a
	// 70 -> b
	// 80 -> (E)
	// 90 -> lambda
	int parsing_table[6][10] = { 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,
								 20, 20,  0,  0,  0,  0, 20,  0,  0,  0,
								  0,  0, 25, 30,  0,  0,  0, 90,  0, 90,
								 40, 40,  0,  0,  0,  0, 40,  0,  0,  0,
								  0,  0, 90, 90, 45, 50,  0, 90,  0, 90,
								 60, 70,  0,  0,  0,  0, 80,  0,  0,  0 };
	vector <char>* stack;
	map <char, int> m = { {'S', 0}, {'E', 1}, {'Q', 2}, {'T', 3}, {'R', 4}, {'F', 5},
						  {'a', 0}, {'b', 1}, {'+', 2}, {'-', 3}, {'*', 4}, {'/', 5}, {'(', 6}, {')', 7}, {'=', 8}, {'$', 9} };

public:
	bool parse(string word);
};

bool Language1::parse(string word) {
	char state;				// Current State
	char check = '/0';		// If state is terminal, checks if it matches char being read
	int parseId;			// Used for parsing table to figure out what to push

	stack = new vector<char>;

	// Initial states to push
	stack->push_back('$');
	cout << "push $\n";
	stack->push_back('E');
	cout << "push E\n";

	for (int i = 0; i < word.length(); i++) {
		cout << "read " << word[i] << endl;
		// If read letter is not a part of the language, reject
		if (word[i] != 'a' && word[i] != '+' && word[i] != '-' && word[i] != '*' && word[i] != '/' && word[i] != '(' && word[i] != ')' && word[i] != '$') {
			cout << word[i] << " is not a valid a letter in the language.\n";
			return false;
		}
		do {
			// Output contents of stack
			vector<char>::iterator j = stack->begin();

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
			if (state == 'E' || state == 'Q' || state == 'T' || state == 'R' || state == 'F') {
				int x = m.find(state)->second;
				int y = m.find(word[i])->second;
				parseId = parsing_table[x][y];

				// Get code from parsing table and push states onto the stack accordingly
				switch (parseId) {
				case 0:
					cout << "Unable to find a match\n";		// 0 means reject word
					return false;
				case 10:
					stack->push_back('Q');
					stack->push_back('T');
					cout << "push QT\n";
					break;
				case 20:
					stack->push_back('Q');
					stack->push_back('T');
					stack->push_back('+');
					cout << "push QT+\n";
					break;
				case 30:
					stack->push_back('Q');
					stack->push_back('T');
					stack->push_back('-');
					cout << "push QT-\n";
					break;
				case 40:
					stack->push_back('R');
					stack->push_back('F');
					cout << "push RF\n";
					break;
				case 50:
					stack->push_back('R');
					stack->push_back('F');
					stack->push_back('*');
					cout << "push RF*\n";
					break;
				case 60:
					stack->push_back('R');
					stack->push_back('F');
					stack->push_back('/');
					cout << "push RF/\n";
					break;
				case 70:
					stack->push_back('a');
					cout << "push a\n";
					break;
				case 80:
					stack->push_back(')');
					stack->push_back('E');
					stack->push_back('(');
					cout << "push )E(\n";
					break;
				case 90:			// 90 means lambda, continue and pop next state
					cout << "push lamba\n";
					break;
				default:
					break;
				}
			}
			// if state is terminal check if it matches read char
			else if (state == 'a' || state == '+' || state == '-' || state == '*' || state == '/' || state == '(' || state == ')' || state == '$') {
				check = state;
				if (check != word[i]) {
					cout << "Expected a " << check << " at this position.\n";
					return false;
				}
				cout << word[i] << " matches " << check << endl;
			}
		} while (check != word[i]);
	}

	// read $ push $ accepted
	if(stack->size() == 0){
		delete stack;
		return true;
	}
	else {
		delete stack;
		cout << "Forgot to put $ at the end!\n";
		return false;
	}
	delete stack;
	return false;
}

// same logic as above
bool Language2::parse(string word) {
	char state;
	char check = '/0';
	int parseId;

	stack = new vector<char>;

	stack->push_back('$');
	cout << "push $\n";
	stack->push_back('S');
	cout << "push S\n";

	for (int i = 0; i < word.length(); i++) {
		cout << "read " << word[i] << endl;
		if (word[i] != 'a' && word[i] != 'b' && word[i] != '+' && word[i] != '-' && word[i] != '*' && word[i] != '/' && word[i] != '(' && word[i] != ')' && word[i] != '=' && word[i] != '$') {
			cout << word[i] << " is not a valid a letter in the language.\n";
			return false;
		}
		do {

			vector<char>::iterator j = stack->begin();

			while (j != stack->end()) {
				cout << *j;
				j++;
			}
			cout << endl;

			state = stack->back();
			stack->pop_back();
			cout << "pop " << state << endl;

			if (state == 'S' || state == 'E' || state == 'Q' || state == 'T' || state == 'R' || state == 'F') {
				int x = m.find(state)->second;
				int y = m.find(word[i])->second;
				parseId = parsing_table[x][y];

				switch (parseId) {
				case 0:
					cout << "Unable to find a match\n";
					return false;
				case 10:
					stack->push_back('E');
					stack->push_back('=');
					stack->push_back('a');
					cout << "push E=a\n";
					break;
				case 20:
					stack->push_back('Q');
					stack->push_back('T');
					cout << "push QT\n";
					break;
				case 25:
					stack->push_back('Q');
					stack->push_back('T');
					stack->push_back('+');
					cout << "push QT+\n";
					break;
				case 30:
					stack->push_back('Q');
					stack->push_back('T');
					stack->push_back('-');
					cout << "push QT-\n";
					break;
				case 40:
					stack->push_back('R');
					stack->push_back('F');
					cout << "push RF\n";
					break;
				case 45:
					stack->push_back('R');
					stack->push_back('F');
					stack->push_back('*');
					cout << "push RF*\n";
					break;
				case 50:
					stack->push_back('R');
					stack->push_back('F');
					stack->push_back('/');
					cout << "push RF/\n";
					break;
				case 60:
					stack->push_back('a');
					cout << "push a\n";
					break;
				case 70:
					stack->push_back('b');
					cout << "push b\n";
					break;
				case 80:
					stack->push_back(')');
					stack->push_back('E');
					stack->push_back('(');
					cout << "push )E(\n";
					break;
				case 90:
					cout << "push lamba\n";
					break;
				default:
					break;
				}
			}
			else if (state == 'a' || state == 'b' || state == '+' || state == '-' || state == '*' || state == '/' || state == '(' || state == ')' || state == '=' || state == '$') {
				check = state;
				if (check != word[i]) {
					cout << "Expected a " << check << " at this position.\n";
					return false;
				}
				cout << word[i] << " matches " << check << endl;
			}
		} while (check != word[i]);
	}

	if (stack->size() == 0) {
		delete stack;
		return true;
	}
	else {
		delete stack;
		cout << "Forgot to put $ at the end!\n";
		return false;
	}
	delete stack;
	return false;
}

int main() {
	Language1 L1;
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
	} while (ans == "y");
		
	return 0;
}
