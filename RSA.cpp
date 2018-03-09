#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cstring>

using namespace std;

bool CheckIsPrime(long int num)
{
	if(num< 2) return false;

	long int i = 2;

	while(i <= num/2)
	{
		if(!(num% i)) return false;
		i++;
	}

	return true;
}

long int Multiply(long int num1,long int num2)
{
	return num1 * num2;
}

bool CheckCoPrime (long int num1, long int num2) {
	long int lowest;

	if (num1 > num2) lowest = num2;
	else lowest = num1;

	long int i = 2;
	bool coprime = true;

	while (i< lowest) {
		if (!(num1% i) && !(num2% i)) coprime = false;
		i++;
	}
	return coprime;
}

long int FindE(long int phi_n)
{
	long int e = 0;

	do {
		cout<< "Choose an integer number e (e must be coprime of phi_n): ";
		cin>> e;
	} while (!CheckCoPrime(phi_n, e));
	return e;
}

long int FindD(long int phi_n, long int e)
{
	int a = phi_n, b = e;
	long int x = 0, y = 1, u = 1, v = 0, m, n, q, r;
	long int gcd = b;

	while (a != 0) {
		q = gcd/a;
		r = gcd% a;
		m = x - u * q;
		n = y - v * q;
		gcd = a;
		a = r;
		x = u;
		y = v;
		u = m;
		v = n;
	}

	if (y < 1) {
		cout<< "Choose a suitable \"e\" value" <<endl;
		e = FindE(phi_n);
		FindD(phi_n, e);
	}
	return y;
}

long int Encrypt_Decrypt(long int t, long int e, long int n)
{
	long int rem;
	long int x = 1;

	while (e != 0) {
		rem = e % 2;
		e = e/2;
		if (rem == 1) x = (x * t)% n;

		t = (t * t)% n;
	}
	return x;
}

void EncDecStr (long int e, long int n)
{
	char *str = new char[1000];
	char *str1 = new char[1000];
	cout<< "\nEnter a string: ";
	cin>>str;
	cout<< "Encrypting using Public Key: " <<endl;
	int i = 0;
	while (i != strlen(str)) {
		str1[i] = Encrypt_Decrypt(str[i], e, n);
		i++;
	}
	cout<< str1 <<endl;
}

void EncDecNum (long int n1, long int n2)
{
	long int pn;
	cout<< "\nEnter an integer number: ";
	cin>>pn;
	cout<<Encrypt_Decrypt(pn, n1, n2) <<endl;
}

void generate_key (long int&n, long int&e, long int&d)
{
	long int p, q, phi_n, pt, ct;
	do {
		cout<< "Enter a prime number: ";
		cin>> p;
	} while (!CheckIsPrime(p));
	do {
		cout<< "Enter another prime number: ";
		cin>> q;
	} while (!CheckIsPrime(q));
	n = Multiply(p,q);
	cout<< "n is " << n <<endl;
	phi_n = Multiply (p-1,q-1);
	cout<< "phi_n is " <<phi_n<<endl;
	e = FindE(phi_n);
	cout<< "e is " << e <<endl;
	if (!e) {
		cout<< "Choose two suitable prime number" <<endl;
		exit(1);
	}
	d = FindD(phi_n, e);
	cout<< "d is " << d <<endl;
}

int main() {
	cout<<endl<<endl<< "##IMPLEMENTATION OF R.S.A ALGORITHM USING C++##" <<endl<<endl;
	long int n, d = 0, e;
	generate_key(n, d, e);
	cout<< "Public Key : ("<<e<<","<<n<<")" <<endl;
	cout<< "Private Key : ("<<d<<","<<n<<")" <<endl;
	cout<<endl<< "Press 1: for encrypting numbers & 2: for encrypting string: ";
	int choice;
	cin>> choice;
	switch (choice) {
		case 1:
			EncDecNum(e, n);
			break;
		case 2:
			EncDecStr(e, n);
			break;
		default:
			cout<< "Wrong choice. Try again." <<endl;
			exit(1);
	}
	cout<<endl<< "Press 1: for decrypting numbers & 2: for decrypting string: ";
	cin>> choice;
	switch (choice) {
		case 1:
			EncDecNum(d, n);
			break;
		case 2:
			EncDecStr(d, n);
			break;
		default:
			cout<< "Wrong choice. Try again." <<endl;
			exit(1);
		}
	return 0;
}
