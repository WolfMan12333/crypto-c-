#include <iostream>
#include <string>
#include <cmath>

using namespace std;

char vigenere_table[26][26] = {
'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A',
'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B',
'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C',
'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D',
'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E',
'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F',
'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G',
'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H',
'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I',
'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J',
'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K',
'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L',
'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M',
'O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
'P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
'Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
'R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
'S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
'T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S',
'U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
'W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
'X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W',
'Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X',
'Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y'
};

void Encrypt(string in, string &out, string k) {
	int i = 0;
	for(string::iterator it = in.begin(); it != in.end(); it++) {
		if(*it != ' ') {
			int row = toupper(*it) - 'A';
			int column = toupper(k[i%k.length()]) - 'A';
			out += vigenere_table[row][column];
		} else {
			out += ' ';
		}
		i++;
	}
}

void Decrypt (string in, string &out, string k) {
	int i = 0;
	for (string :: iterator it = in.begin(); it != in.end(); it++) {
		if(*it != ' ' ) {
			int column = toupper(k[i%k.length()]) - 'A';
			int row;
			for(row = 0; row < 26; row++) {
				if(vigenere_table[row][column] == *it) break;
			}
			out += 'A' + row;
		} else {
			out += ' ';
		}
		i++;
	}
}

int main() {
	string input, output, key;
	cout << "Put key value (put alphabets/words):";
	getline(cin, key);
	int choice = 0;

	while(choice != 3) {
		cout<<endl<<"Press 1: Encryption\nPress 2: Decryption\nPress 3: quit\n";

		try {
			cin >> choice;
			cin.ignore();
			if(choice != 1 && choice != 2 && choice != 3) throw "Incorrect Choice";
		} catch(const char* chc) {
			cerr << "INCORRECT CHOICE!!!"<<endl;
			return 1;
		}

		if(choice == 1 || choice ==2) {
			try{
				cout <<endl<<"Enter ciphertext(only alphabets) and press enter to continue:\n";
				getline(cin, input);

				for(int i = 0; i < input.size(); i++) {
					if((!(input[i] >= 'a' && input[i] <= 'z')) && (!(input[i] >= 'A' && input[i] <= 'Z')) && (!(input[i] == ' ')))
						throw "Incorrect string";
				}
			} catch(const char* str) {
				cerr << "YOUR STRING MAY HAVE DIGITS OR SPECIAL SYMBOLS !!!"<<endl;
				cerr<<"PLEASE PUT ONLY ALPHABETS!!!"<<endl;
				return 1;
			}
			if(choice ==1) {
				Encrypt(input, output, key);
				cout<<endl<<"Cipher text: " << output << endl;
			} else if(choice == 2) {
				input = output;
				output.clear();
				Decrypt(input, output, key);
				cout << endl << "Plain text: " << output << endl;
			}
		}
	}
	return 0;
}
