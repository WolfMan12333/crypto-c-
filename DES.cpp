#include<iostream>

using namespace std;

class DES{
	public:
		int keyi[16][48], total[64], left[32], right[32], ck[28], dk[28], expansion[48], z[48], xor1[48], sub[32], p[32], xor2[32], temp[64], pc1[56], ip[64], inv[8][8];
		char final[1000];
		void keygen();
		void PermChoice1();
		void split_key();

		void PermChoice2();

		void IP();

		void Expansion();
		void xor_oneE(int);
		void substitution();
		void permutation();
		void xor_two();
		void inverse();
		void xor_oneD(int);
		char *Encrypt(char *);
		char *Decrypt(char *);
};

void DES::keygen(){
	PermChoice1();
	split_key();
	int noshift = 0,round;

	for(round = 1; round< = 16; round++){
		if(round == 1 || round == 2 || round == 9 || round == 16)
			noshift = 1;
		else
			noshift = 2;

		while(noshift>0){
			int t;
			t = ck[0];
			for(int i = 0; i<28; i++)
				ck[i] = ck[i+1];
			ck[27] = t;
			t = dk[0];
			for(int i = 0; i<28; i++)
					dk[i] = dk[i+1];
			dk[27] = t;
			noshift— ;
		}
		cout << endl << "round " << round << endl;
		PermChoice2();

		for(int i = 0; i<48; i++)
		keyi[round-1][i] = z[i];

	}

}

void DES::PermChoice1(){
	cout << "key: " << endl;
	for (int i = 0; i < 64; i++) {
		cout << key[i] << "\t";
		if (((i + 1)% 8) = = 0) cout << endl;
	}

	int k = 57,i;

	for(i = 0; i<28; i++){
		pc1[i] = key[k-1];
		if(k-8>0) k = k-8;
		else k = k+57;
	}

	k = 63;

	for(i = 28; i<52; i++){
		pc1[i] = key[k-1];
		if(k-8>0) k = k-8;
		else k = k+55;
	}

	k = 28;

	for(i = 52; i<56; i++){
		pc1[i] = key[k-1];
		k = k-8;
	}

	cout << endl << "After permutation choice 1:" << endl;

	for (i = 0; i < 56; i++){
		cout << pc1[i] << "\t";
		if (((i + 1)% 7) = = 0) cout << endl;
	}
}

void DES::split_key(){
	int i,k = 0;
	for(i = 0; i<28; i++){
4.		ck[i] = pc1[i];
5.			}
6.			
for(i = 28; i<56; i++){
7.				dk[k] = pc1[i];
8.				k++;
9.			}
10.			
cout << endl << "Print C0 " << endl;
11.			
for(i = 0; i<28; i++){ //left 28
bits of permuted 56 bit key
12.				
cout << ck[i] << "\t";
13.				
if (((i + 1)% 7) = = 0) cout
<< endl;
14.			}
15.			
cout << endl << "Print D0 " << endl;
16.			
for(i = 28; i<56; i++){ //right 28
bits of permuted 56 bit key
17.				
cout << dk[i] << "\t";
18.				
if (((i + 1)% 7) = = 0) cout
<< endl;
19.			}
20.
}

void DES::PermChoice2(){
2.			int per[56],i,k;
3.			
for(i = 0; i<28; i++) per[i] =
ck[i];
4.			
for(k = 0,i = 28; i<56; i++) per[i]
= dk[k++];
5.			
z[0] = per[13];
6.			
z[1] = per[16];
7.			
z[2] = per[10];
8.			
z[3] = per[23];
9.			
z[4] = per[0];
10.			
z[5] = per[4];
11.			
z[6] = per[2];
12.			
z[7] = per[27];
13.			
z[8] = per[14];
14.			
z[9] = per[5];
15.			
z[10] = per[20];
16.			
z[11] = per[9];
17.			
z[12] = per[22];
18.			
z[13] = per[18];
19.			
z[14] = per[11];
20.			
z[15] = per[3];
21.			
z[16] = per[25];
22.			
z[17] = per[7];
23.			
z[18] = per[15];
24.			
z[19] = per[6];
25.			
z[20] = per[26];
26.			
z[21] = per[19];
27.			
z[22] = per[12];
28.			
z[23] = per[1];
29.			
z[24] = per[40];
30.			
z[25] = per[51];
31.			
z[26] = per[30];
32.			
z[27] = per[36];
33.			
z[28] = per[46];
34.			
z[29] = per[54];
35.			
z[30] = per[29];
36.			
z[31] = per[39];
37.			
z[32] = per[50];
38.			
z[33] = per[46];
39.			
z[34] = per[32];
40.			
z[35] = per[47];
41.			
z[36] = per[43];
42.			
z[37] = per[48];
43.			
z[38] = per[38];
44.			
z[39] = per[55];
45.			
z[40] = per[33];
46.			
z[41] = per[52];
47.			
z[42] = per[45];
48.			
z[43] = per[41];
49.			
z[44] = per[49];
50.			
z[45] = per[35];
51.			
z[46] = per[28];
52.			
z[47] = per[31];
53.			
cout << endl << "After permutation
choice 2 " << endl;
54.			
for(int i = 0; i<48; i++){
//creates the 48 bits permutation
table(PC-2)
55.				
cout << z[i] << "\t";
56.				
if (((i + 1)% 6) = = 0) cout
<< endl;
57.			
}//for ends here
58.		
} //PermChoice2 function ends here

1.
char* DES::Encrypt(char *Text1){
2.				
int i,a1,j,nB,m,iB,k,K,B[8],n,
t,d,round, mc = 0;
3.				
char *Text = new char[1000];
4.				strcpy(Text,Text1);
5.				i = strlen(Text);
6.				a1 = i%8;
7.
8.				
if(a1 ! = 0)
9.					
for(j = 0; j<8-a1;
j++,i++) Text[i] = ' ';
					
//add padding bits with
space
10.				Text[i] = '\0';
11.				
for(iB = 0,nB = 0,m = 0;
m<(strlen(Text)/8); m++){
12.				
//Repeat for TextLength/8
times.
13.				
for(iB = 0,i = 0; i<8;
i++,nB++){
14.					n = (int)Text[nB];
15.					
cout << " n is " << n
<< endl;
16.					
for(K = 7; n> = 1; K— )
{
17.						B[K] = n%2;
						
//Converting
8-Bytes to
64-bit Binary
Format
18.						
cout << "B[" <<
K << "] is " <<
B[K] << endl;
19.						n/= 2;
20.					}
21.					
for(; K> = 0; K— ) B[K]
= 0;
22.					
for(K = 0; K<8;
K++,iB++) total[iB] =
B[K];
23.					
//Now 'total' contains
the 64-Bit binary
format of Bytes
24.				}
25.				IP();
26.				
for(i = 0; i<64; i++)
total[i] = ip[i];
				
//Store values of ip[64] into
total[64]
27.				
for(i = 0; i<32; i++) left[i]
= total[i];
28.				
for(; i<64; i++) right[i-32]
= total[i];
29.				
for(round = 1; round< = 16;
round++){
30.					
Expansion(); //E bit
selection
31.					
//Performing expansion
on 'right[32]' to get
'expansion[48]'
32.					xor_oneE(round);
33.					
//Performing XOR
operation on
expansion[48],z[48] to
get xor1[48]
34.					substitution();
35.					
//Perform substitution
on xor1[48] to get
sub[32]
36.					permutation();
37.					
//Performing
Permutation on sub[32]
to get p[32]
38.					
xor_two();
//xor with
32 bit L0 and f value
39.					
//Performing XOR
operation on
left[32],p[32] to get
xor2[32]
40.					
for(i = 0; i<32; i++)
left[i] = right[i];
41.					
//Dumping right[32]
into left[32]
42.					
for(i = 0; i<32; i++)
right[i] = xor2[i];
43.					
//Dumping xor2[32] into
right[32]
44.				}
45.				
for(i = 0; i<32; i++) temp[i]
= right[i];//Dumping—
>[swap32bit]
46.				
for(; i<64; i++) temp[i] =
left[i-32];//
left[32],right[32] into
temp[64]
47.				inverse();
48.				
//Inversing the bits of
temp[64] to get inv[8][8]
49.				
/* Obtaining the Cypher-Text
into final[1000]*/
50.				k = 128;
51.				d = 0;
52.				
for(i = 0; i<8; i++){
53.					
for(j = 0; j<8; j++){
54.						
d = d+inv[i]
[j]*k;
55.						k = k/2;
56.					}
57.					final[mc++] = (char)d;
58.					k = 128;
59.					d = 0;
60.				}
61.			
}//for loop ends here
62.			
final[mc] = '\0';
63.			return(final);
64.
}

1.
void DES::IP(){//Initial Permutation
2.			
int k = 58,i;
3.			
for(i = 0; i<32; i++){
4.				ip[i] = total[k-1];
5.				
if(k-8>0) k = k-8;
6.				
else k = k+58;
7.			}
8.			
k = 57;
9.			
for(i = 32; i<64; i++){
10.				ip[i] = total[k-1];
11.				
if(k-8>0) k = k-8;
12.				
else k = k+58;
13.			}
14.			
cout << "Actual bit sequence:"
<<endl;
for (int i = 0; i < 64; i++){
16.				
cout << total[i] << "\t";
17.				
if (((i + 1)% 8) = = 0) cout
<<endl;
18.			}
19.			
cout << endl;
20.			
cout << "After initial permutation:
" <<endl;
21.			
for (int i = 0; i < 64; i++){
22.				
cout << ip[i] << "\t";
23.				
if (((i + 1)% 8) = = 0) cout
<<endl;
24.			}
25.
}

void DES::Expansion(){//Expansion Function
applied on 'right' half
2.			int exp[8][6],i,j,k;
3.			
for(i = 0; i<8; i++){
4.				
for(j = 0; j<6; j++){
5.					
if((j! = 0)||(j! = 5)){
6.						k = 4*i+j;
7.						exp[i][j] = 		
						right[k-1];
8.					}
9.					
if(i ! = 0 && j = =0){
10.						k = 4*i;
11.						exp[i][j] = 		
						right[k-1];
12.					}
13.					
if(i ! = 7 && j = =5){
14.						k = 4*i+j;
15.						exp[i][j] = 		
						right[k-1];
16.					}
17.				}
}
19.			
exp[0][0] = right[31];
20.			
exp[7][5] = right[0];
21.			
k = 0;
22.			
for(i = 0; i<8; i++){
23.				
for(j = 0; j<6; j++)
expansion[k++] = exp[i][j];
24.			}
25.
}

1.
void DES::xor_oneE(int round){
2.		
//for Encrypt
3.		
int i;
4.		
for(i = 0; i<48; i++)
5.			
xor1[i] = expansion[i]^keyi[round-1]
[i];
6.
}

void DES::substitution(){
int s1[4][16] = {
14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
};
int s2[4][16] = {
15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
};
int s3[4][16] = {
10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
};
int s4[4][16] = {
7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
};
int s5[4][16] = {
2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
};
int s6[4][16] = {
12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
};
int s7[4][16] = {
4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
};
int s8[4][16] = {
13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
};
int a[8][6],k = 0,i,j,p,q,count = 0,g = 0,v;
for(i = 0; i<8; i++){
for(j = 0; j<6; j++){
a[i][j] = xor1[k++];
}
}
for(i = 0; i<8; i++){
p = 1;
q = 0;
k = (a[i][0]*2)+(a[i][5]*1);
j = 4;
29.
30.
31.
32.
33. while(j>0){
q = q+(a[i][j]*p);
p = p*2;
j— ;
}
34.
35.
36.
37.
38.
39.
40.
41.
42.
43.
44.
45.
46.
47.
48.
49.
50.
51.
52.
53.
54.
55.
56.
57.
58.
59.
60. count = i+1;
switch(count){
case 1:
v = s1[k][q];
break;
case 2:
v = s2[k][q];
break;
case 3:
v = s3[k][q];
break;
case 4:
v = s4[k][q];
break;
case 5:
v = s5[k][q];
break;
case 6:
v = s6[k][q];
break;
case 7:
v = s7[k][q];
break;
case 8:
v = s8[k][q];
break;
}
int d,i = 3,a[4];
while(v>0){
d = v%2;
a[i— ] = d;
v = v/2;
}
while(i> = 0){
a[i— ] = 0;
}
for(i = 0; i<4; i++)
sub[g++] = a[i];
}
}

void DES::permutation(){
p[0] = sub[15];
p[1] = sub[6];
p[2] = sub[19];
p[3] = sub[20];
p[4] = sub[28];
p[5] = sub[11];
p[6] = sub[27];
p[7] = sub[16];
p[8] = sub[0];
p[9] = sub[14];
p[10]
p[11]
p[12]
p[13]
p[14]
p[15]
p[16]
p[17]
p[18]
p[19]
p[20]
p[21]
p[22]
p[23]
p[24]
p[25]
p[26]
p[27]
p[28]
p[29]
p[30]
p[31]
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
=
sub[22];
sub[25];
sub[4];
sub[17];
sub[30];
sub[9];
sub[1];
sub[7];
sub[23];
sub[13];
sub[31];
sub[26];
sub[2];
sub[8];
sub[18];
sub[12];
sub[29];
sub[5];
sub[21];
sub[10];
sub[3];
sub[24];
}

void DES::xor_two(){
2.
int i;
3.
for(i = 0; i<32; i++){
4.		
xor2[i] = left[i]^p[i];
5.
}
6.
}

char * DES::Decrypt(char *Text1){
2.		
int i,a1,j,nB,m,iB,k,K,B[8],n,t,d,round;
3.		
char *Text = new char[1000];
4.		
unsigned char ch;
5.		 strcpy(Text,Text1);
6.		
i = strlen(Text);
7.		 //keygen();
8.		
int mc = 0;
9.		
for(iB = 0,nB = 0,m = 0;
m<(strlen(Text)/8); m++){
10.			
/*Repeat for TextLength/8 times*/
11.			
for(iB = 0,i = 0; i<8; i++,nB++){
12.				ch = Text[nB];
13.				n = (int)ch;//(int)Text[nB];
14.				
for(K = 7; n> = 1; K— ){
15.					
B[K] = n%2; //
Converting 8-Bytes to
64-bit Binary Format
16.					n/= 2;
17.				}
18.				
for(; K> = 0; K— ) B[K] = 0;
19.				
for(K = 0; K<8; K++,iB++)
total[iB] = B[K];
20.				
/*Now 'total' contains the
64-Bit binary format of
8-Bytes*/
21.			}
22.			IP();
23.			
for(i = 0; i<64; i++) total[i] =
ip[i];
24.			
for(i = 0; i<32; i++) left[i] =
total[i];
25.			
for(; i<64; i++) right[i-32] =
total[i];
26.			
for(round = 1; round< = 16; 		
				round++){
27.				Expansion();
28.				xor_oneD(round);
29.				substitution();
30.				permutation();
xor_two();
32.				
for(i = 0; i<32; i++) left[i]
= right[i];
33.				
for(i = 0; i<32; i++)
right[i] = xor2[i];
34.			
}//16 rounds end here
35.			
for(i = 0; i<32; i++) temp[i] =
right[i];
36.			
for(; i<64; i++) temp[i] =
left[i-32];
37.			inverse();
38.			
/* Obtaining the Cypher-Text into
final[1000]*/
39.			
k = 128;
40.			
d = 0;
41.			
for(i = 0; i<8; i++){
42.				
for(j = 0; j<8; j++){
43.					d = d+inv[i][j]*k;
44.					k = k/2;
45.				}
46.				final[mc++] = (char)d;
47.				k = 128;
48.				d = 0;
49.			}
50.		
}
//for loop ends here
51.		
final[mc] = '\0';
52.		
char *final1 = new char[1000];
53.		
for(i = 0,j = strlen(Text);
i<strlen(Text); i++,j++)
54.		
final1[i] = final[j];
55.		
final1[i] = '\0';
56.		
return(final);
57.
}

int main(){
2.		
DES d1;
3.		 d1.keygen();
4.		
char *str = new char[1000];
5.		
cout<<"\nEnter a string : ";
6.		
cin >> str;
7.		
char *str1 = new char[1000];
8.		
str1 = d1.Encrypt(str);
9.		
cout<<"\nEncrypted Text: "<<str1<<endl;
10.		
cout<<"\no/p Text: "<<d1.
Decrypt(str1)<<endl;
11.
}
