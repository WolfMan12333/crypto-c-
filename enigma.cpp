#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

typedef pair<int, int> Rotor_Pair;

class Enigma {
	public:
		void create_rotor(vector <Rotor_Pair>&rtq);
		void show_rotor(vector <Rotor_Pair>&rtq);
		void manage_rotors();
		void encrypt();
		void decrypt();
		char transpos_en(char ch);
		char transpos_de(char ch);
		void display_rotors();

	private:
		vector<Rotor_Pair> first_rotor;
		vector<Rotor_Pair> second_rotor;
		vector<Rotor_Pair> third_rotor;
		vector< vector <Rotor_Pair> > all_rotors;
		int count;
};

void Enigma::create_rotor(vector <Rotor_Pair>&rtq){
	vector<int> temp_q;

	int current = rand() % 26 + 1;
	int num = rand() % 26 + 1;

	rtq.push_back(make_pair(current, num));
	temp_q.push_back(num);

	for (int i = 0; i < 25; i++) {
		current = current % 26 + 1;
		bool exist = true;

		while(exist) {
			exist = false;
			num = rand() % 26 + 1;
			for(vector <int> :: iterator it = temp_q.begin(); it != temp_q.end(); it++){
				if((*it) == num) {
					exist = true;
					break;
				}
			}
		}

		temp_q.push_back(num);
		Rotor_Pair rp = make_pair(current, num);
		rtq.push_back(rp);
	}
}

void Enigma::show_rotor(vector <Rotor_Pair>&rtq) {
	vector<Rotor_Pair> temp_q;
	temp_q = rtq;
	cout << endl;

	for(unsigned int i = 0; i < 26; i++) {
		Rotor_Pair rp = rtq[i];
		cout << rp.first << "\t" << rp.second << endl;
	}
}

void Enigma::manage_rotors() {
	count = 0;
	srand(5);
	create_rotor(first_rotor);
	all_rotors.push_back(first_rotor);
	create_rotor(second_rotor);
	all_rotors.push_back(second_rotor);
	create_rotor(third_rotor);
	all_rotors.push_back(third_rotor);
}

void Enigma::display_rotors() {
	for (vector <vector<Rotor_Pair>> :: iterator it = all_rotors.begin(); it != all_rotors.end(); it++) {
		show_rotor(*it);
	}
}

char Enigma::transpos_en(char ch) {
	count++;
	ch = toupper(ch);
	int pos = ch - 65 + 1;
	int index = 0;

	for (vector <Rotor_Pair> :: iterator it = first_rotor.begin(); it != first_rotor.end(); it++) {
		if ((*it).second == pos) break;
		else index++;
	}

	Rotor_Pair trp = first_rotor.front();
	first_rotor.erase(first_rotor.begin());
	first_rotor.push_back(trp);

	pos = (second_rotor[index]).first;
	index = 0;

	for(vector<Rotor_Pair> :: iterator it = second_rotor.begin(); it != second_rotor.end(); it++) {
		if ((*it).second == pos) break;
		else index++;
	}

	if(count % 26 == 0) {
		Rotor_Pair trp = second_rotor.front();
		second_rotor.erase(second_rotor.begin());
		second_rotor.push_back(trp);
	}

	pos = (third_rotor[index]).first;
	index = 0;

	for(vector<Rotor_Pair> :: iterator it = third_rotor.begin(); it != third_rotor.end(); it++) {
		if ((*it).second == pos) break;
	}

	if (count % 676 == 0) {
		Rotor_Pair trp = third_rotor.front();
		third_rotor.erase(third_rotor.begin());
		third_rotor.push_back(trp);
	}

	ch = pos - 1 + 65;
	return tolower(ch);
}

void Enigma::encrypt() {
	cout << "Put a text to encrypt" << endl;
	string input, output;
	getline(cin, input);

	for (string :: iterator it = input.begin(); it != input.end(); it++) {
		if (isalpha(*it))
			output += transpos_en(*it);
		else output += 32;
	}

	cout << output << endl;
}

char Enigma::transpos_de(char ch) {
	count++;
	ch = toupper(ch);
	int pos = ch - 65 + 1;
	int index = 0;

	for(vector <Rotor_Pair> :: iterator it = third_rotor.begin(); it != third_rotor.end(); it++) {
		if ((*it).first == pos) break;
		else index++;
	}

	if (count % 676 == 0) {
		Rotor_Pair trp = third_rotor.front();
		third_rotor.erase(third_rotor.begin());
		third_rotor.push_back(trp);
	}

	pos = (second_rotor[index]).second;
	index = 0;

	for(vector <Rotor_Pair> :: iterator it = second_rotor.begin(); it != second_rotor.end(); it++) {
		if ((*it).first == pos) break;
		else index++;
	}

	if(count % 26 == 0) {
		Rotor_Pair trp = second_rotor.front();
		second_rotor.erase(second_rotor.begin());
		second_rotor.push_back(trp);
	}

	pos = (first_rotor[index]).second;
	index = 0;

	for(vector <Rotor_Pair> :: iterator it = first_rotor.begin(); it != first_rotor.end(); it++) {
		if ((*it).first == pos) break;
		else index++;
	}

	Rotor_Pair trp = first_rotor.front();
	first_rotor.erase(first_rotor.begin());
	first_rotor.push_back(trp);

	ch = pos - 1 + 65;
	return tolower(ch);
}

void Enigma::decrypt() {
	cout << "Put a text to decrypt" << endl;
	string input, output;
	getline(cin, input);

	int count = 0;
	for (vector < vector<Rotor_Pair>> :: iterator p = all_rotors.begin(); p != all_rotors.end(); p++) {
		if(count == 0 ) first_rotor = *p;
		else if (count == 1) second_rotor = *p;
		else third_rotor = *p;
		count ++;
	}

	display_rotors();

	for (string :: iterator it = input.begin(); it != input.end(); it++) {
		if (isalpha(*it))
			output += transpos_de(*it);
		else output += 32;
	}

	cout << output << endl;
}

int main() {
	Enigma enigma;
	enigma.manage_rotors();
	enigma.display_rotors();
	enigma.encrypt();
	enigma.decrypt();
	return 0;
}
