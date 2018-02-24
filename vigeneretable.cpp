#include <iostream>

using namespace std;

int main() {
	int alpha[26][26];
	for (int i=0; i < 26; i++){
		for(int j = 0; j < 26; j++) {
			alpha[i][j]=(i+j)+65;
			if(alpha[i][j]>=91){
				alpha[i][j]-=26;
			}
			cout <<'\''<<(char) alpha[i][j]<<'\''<<',';
		}
		cout <<endl;
	}
	return 0;
}
