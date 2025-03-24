#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

void new_tell(map<string, string>& book,map<string,vector<string>>& book_rev, string& answer) {
	stringstream answer_2(answer);
	string number, surname;
	answer_2 >> number >> surname;
	book.insert(make_pair(number,surname));
	if (book_rev.find(surname) != book_rev.end()) {
		book_rev.find(surname)->second.push_back(number);
	}
	else {
		vector<string> temp;
		temp.push_back(number);
		book_rev.insert(make_pair(surname, temp));
	}
}

void show_surname(map<string, string>& book, string& answer) {
	cout << book.find(answer)->second << "\n";
}	

void show_number(map<string,vector<string>>& book_rev, string& answer) {
	map<string, vector<string>>::iterator it = book_rev.find(answer);
	if (it != book_rev.end()) {
		for (size_t i = 0; i < it->second.size(); i++) {
			cout << it->second[i] << "\n";
		}
	}
}

void print_book(map<string, string>& book) {
	for (map<string, string>::iterator it = book.begin(); it != book.end(); it++) {
		cout << it->first << " " << it->second << "\n";
	}
}

void save(map<string, string>& book) {
	ofstream library("library.BIN", ios::binary);
	for (map<string, string>::iterator it = book.begin(); it != book.end(); ++it) {
		string temp;
		temp = it->first;
		size_t temp_lenght = temp.length();
		library.write(reinterpret_cast<char*>(&temp_lenght), sizeof(temp_lenght));
		library.write(temp.data(), temp_lenght);
		temp = it->second;
		temp_lenght = temp.length();
		library.write(reinterpret_cast<char*>(&temp_lenght), sizeof(temp_lenght));
		library.write(temp.data(), temp_lenght);
	}
}

void load(map<string, string>& book, map<string,vector<string>>& book_rev) {
	book.clear();
	book_rev.clear();
	ifstream library("library.BIN", ios::binary);
	if (!library.is_open()) {
		cout << "Error load";
		return;
	}
	string key, value;
	while (true) {
		size_t key_lenght;
		if (!library.read(reinterpret_cast<char*>(&key_lenght), sizeof(key_lenght))) {
			break;
		}
		key.resize(key_lenght);
		library.read(&key[0], key_lenght);
		size_t value_lenght;
		if (!library.read(reinterpret_cast<char*>(&value_lenght), sizeof(value_lenght))) {
			break;
		}
		value.resize(value_lenght);
		library.read(&value[0], value_lenght);
		book.insert(make_pair(key, value));
		map<string, vector<string>>::iterator it = book_rev.find(value);
		if (it == book_rev.end()) {
			vector<string> numbers;
			numbers.push_back(key);
			book_rev.insert(make_pair(value, numbers));
		}
		else {
			it->second.push_back(key);
		}
	}
}

int main() {
	map<string, string> book;
	map<string, vector<string>> book_revers;
	string answer;
	do{
		cout << "Input your request or save or load or print: ";
		getline(cin, answer);
		stringstream answer_1(answer);
		string temp;
		int count = 0;
		while (answer_1 >> temp) {
			count++;
		}
		if (count == 2) {
			new_tell(book,book_revers,answer);
			print_book(book);
		}
		else if (count == 1) {
			if (answer == "load") {
				load(book,book_revers);
			}
			else if (answer == "save") {
				save(book);
			}
			else if (answer == "print") {
				print_book(book);
			}
			else if (temp[0] >= '0' && temp[0] <= '9') {
				show_surname(book, answer);
			}
			else {
				show_number(book_revers, answer);
			}
		}
	} while (answer != "exit");
}