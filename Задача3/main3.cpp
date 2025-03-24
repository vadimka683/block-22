#include<iostream>
#include<string>
#include<map>

using namespace std;

bool check_Anagram(string& first, string& second) {
	if (first.length() != second.length()) {
		return false;
	}
	map<char, int> book;
	int count = 1;
	for (int i = 0; i < first.length(); i++) {
		map<char, int>::iterator it = book.find(first[i]);
		if (it == book.end()) {
			book.insert(make_pair(first[i], count));
		}
		else {
			it->second++;
		}
	}
	for (int i = 0; i < second.length(); i++) {
		map<char, int>::iterator it = book.find(second[i]);
		if (it == book.end()) {
			return false;
		}
		else if (it->second > 1) {
			it->second--;
		}
		else {
			book.erase(it);
		}
	}
	return true;
}

int main() {
	string word_1, word_2;
	cout << "Input first word: ";
	cin >> word_1;
	cout << "Input second word: ";
	cin >> word_2;
	bool check = check_Anagram(word_1, word_2);
	if (check) {
		cout << "true";
	}
	else {
		cout << "false";
	}
}