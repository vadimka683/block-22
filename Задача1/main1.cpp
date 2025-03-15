#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

void new_tell(map<string, string>& book, string& answer) {
	stringstream answer_2(answer);
	string key, value;
	answer_2 >> key >> value;
	book.insert(make_pair(key,value));
}

void show_surname(map<string, string>& book, string& answer) {
	cout << book.find(answer)->second << "\n";
}	

void show_number(map<string, string>& book, string& answer) {
	for (map<string, string>::iterator it = book.begin(); it != book.end(); it++) {
		if (it->second == answer) {
			cout << it->first << " ";
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

void load(map<string, string>& book) {
	book.clear();
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
	}
}

int main() {
	map<string, string> book;
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
			new_tell(book, answer);
			print_book(book);
		}
		else if (count == 1) {
			if (answer == "load") {
				load(book);
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
				show_number(book, answer);
			}
		}
	} while (answer != "exit");
}