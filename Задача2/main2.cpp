#include<iostream>
#include<string>
#include<fstream>
#include<map>

using namespace std;

void load(multimap<string, int>& queue) {
	ifstream load("Queue.BIN", ios::binary);
	if (!load.is_open()) {
		cout << "Error load queue.\n";
	}
	int count = 0;
	while (true) {
		count++;
		string temp;
		size_t temp_lenght;
		if (!load.read(reinterpret_cast<char*>(&temp_lenght), sizeof(temp_lenght))) {
			break;
		}
		temp.resize(temp_lenght);
		if (!load.read(&temp[0], temp_lenght)) {
			break;
		}
		queue.insert(make_pair(temp, count));
	}
}

void save(multimap<string, int>& queue) {
	ofstream save("Queue.BIN", ios::binary);
	for (map<string, int>::iterator it = queue.begin(); it != queue.end(); it++) {
		string surname = it->first;
		size_t surname_lenght = surname.length();
		save.write(reinterpret_cast<char*>(&surname_lenght), sizeof(surname_lenght));
		save.write(surname.data(), surname_lenght);
	}
}

void print_queue(multimap<string, int>& queue) {
	for (const auto& It : queue) {
		cout << It.first << "\n";
	}
}

void pushback_queue(multimap<string, int>& queue, string& surname, int& count) {
	count++;
	queue.insert(make_pair(surname, count));
}

void next(multimap<string, int>& queue) {
	map<string, int>::iterator itf = queue.begin();
	cout << itf->first << "\n";
	queue.erase(itf);
}

int main() {
	multimap<string, int> queue;
	int count_queue = 0;
	while (true) {
		cout << "Input command: ";
		string command;
		cin >> command;
		if (command == "save") {
			save(queue);
		}
		else if (command == "load") {
			load(queue);
		}
		else if (command == "print") {
			print_queue(queue);
		}
		else if (command == "next") {
			next(queue);
		}
		else if (command == "exit") {
			return 0;
		}
		else {
			pushback_queue(queue, command, count_queue);
		}
	}
}