#include <bits/stdc++.h>

using namespace std;

int prime[50];
int seive[50];
char keyTable[5][5];

int gcd(int x, int y) {
	if(y%x == 0)
		return x;

	return gcd(y%x, x);
}

int findgcd(int x) {
	int i = 2;
	while(1) {
		if(gcd(i, x) == 1){
			return i;
		}
		i++;
	}
}

int findA(int e, int m) {
	int n = 0;
	float temp;
	int temp2;
	while(1) {
		temp = (float)(1 + n*m) / (float)e;
		temp2 = (1 + n*m) / e;
		if(temp == temp2){
			return temp2;
		}
		n++;
	}
}

int findPow(int c, int a, int n) {
	long long int temp = c, temp2 = 1;

	while(a > 1){
		if(a%2 == 1){
			a--;
			temp2 = temp2*temp;
		}
		else{ 
			temp = (temp*temp)%n;
			a = a/2;
		}
	}
	
	return (temp2*temp)%n;
}

void rsaEncrypt(int count){
	int arrImp[10][3];
	int p, q;

	
	srand((unsigned)time(NULL));
	p = prime[rand()%count];
	q = p;

	while(q == p){
		srand((unsigned)time(NULL));
		q = prime[rand()%count];
	}

	long long int n = p*q, m = (p-1)*(q-1);

	long long int e = findgcd(m);
	long long int a = findA(e, m);

	char arr[1000];
	cout << "I would need the path to your file: ";
	scanf("%s", arr);
	fstream file;
	file.open(arr);

	if(!file) {
		cout << "\nSorry! Unable to open file.\n";
		cout << "Check the path/file name\n\n";
		return;
	}

	file.seekp(0, ios::beg);
	file.seekg(0, ios::beg);

	unsigned char fileChar;
	int tempFileChar, tempRes;

	srand((unsigned)time(NULL));
	int tempIndex = rand()%5;

	/*
	private n public
	103 143 7
	77 221 5
	75 145 3
	29 146 5
	101 203 5
	65 133 5
*/
	arrImp[0][0] = 103; arrImp[0][1] = 143; arrImp[0][2] = 7;
	arrImp[1][0] = 77; arrImp[1][1] = 221; arrImp[1][2] = 5;
	arrImp[2][0] = 75; arrImp[2][1] = 145; arrImp[2][2] = 3;
	arrImp[3][0] = 29; arrImp[3][1] = 146; arrImp[3][2] = 5;
	arrImp[4][0] = 101; arrImp[4][1] = 203; arrImp[4][2] = 5;
	arrImp[5][0] = 65; arrImp[5][1] = 133; arrImp[5][2] = 5;

	a = arrImp[tempIndex][0];
	n = arrImp[tempIndex][1];
	e = arrImp[tempIndex][2];

	while(file){
		file >> fileChar;
		tempFileChar = fileChar;
		tempRes = findPow(tempFileChar, e, n);
		file.seekp(-1, ios::cur);
		file.put((char)(tempRes));
		//cout << tempFileChar << " " << tempRes << endl;
	}

	file.close();
	cout << "\n";

	cout << "Remember these numbers: \n";
	cout << "Private key: " << a << endl;
	cout << "n: " << n << endl;
}

void rsaDecrypt(){
	char arr[100];
	cout << "\nEnter file address: ";
	scanf("%s", arr);
	cout << "We gave you two numbers to remember! We would need that.\n";
	int p, n;
	cout << "Enter private key: ";
	cin >> p;
	cout << "Enter n: ";
	cin >> n;

	fstream file;
	file.open(arr);
	if(!file) {
		cout << "\nSorry! Unable to open file.\n";
		cout << "Check the path/file name\n\n";
		return;
	}

	file.seekp(0, ios::beg);
	file.seekg(0, ios::beg);

	unsigned char fileChar;
	int tempFileChar, tempRes;

	cout << "\n";
	while(file){
		file >> fileChar;
		tempFileChar = fileChar;
		tempRes = findPow(tempFileChar, p, n);
		if(tempRes >= 65 && tempRes <= 122){
		}

		else {
			if(tempRes < 65)
				tempRes += n;
		}
		fileChar = (char)tempRes;
		file.seekp(-1, ios::cur);
		file.put(fileChar);
		//cout << tempFileChar << " " << tempRes << endl;
	}
	
	file.close();

	cout << "\n\nCheck your file and remember to re-encrypt it!!\n";
}

void rsaMain(){
	int i, j, count;

	seive[0] = seive[1] = 1;
	for(i = 2; i*i < 100; i++) {
		for(j = 2*i; j < 100; j+=i) {
			seive[j] = 1;
		}
	}

	for(i = 1; i < 100; i++){
		if(seive[i] == 0)
			prime[count++] = i;
	}

	rsaEncrypt(count);
}


void vignereEncrypt(){

	char fileName[100];
	string key;
	cout << "Enter file name: ";
	cin >> fileName;
	cout << "We would need a key for encrypting tree!\n";
	cout << "You must remember this key!\n";
	cout << "Enter a key sentence that is all in lowercase: ";
	cin >> key;

	fstream file;
	file.open(fileName);

	if(!file){
		cout << "Unable to open the file!\n\n";
		exit(1);
	}

	file.seekg(0, ios::beg);
	file.seekp(0, ios::beg);

	int keyIndex = 0;
	int keyLen = key.length();

	char ip, op;

	while(file){
		keyIndex++;
		if(keyIndex >= keyLen)
			keyIndex = 0;

		file.get(ip);
		op = ip + (key[keyIndex] - 'a');
		file.seekp(-1, ios::cur);
		file.put(op);
	}

}

void vignereDecrypt(){
	char fileName[100];
	string key;
	cout << "Enter file name: ";
	cin >> fileName;
	cout << "Enter the key you gave us: ";
	cin >> key;

	fstream file;
	file.open(fileName);

	if(!file){
		cout << "Unable to open the file!\n\n";
		exit(1);
	}

	file.seekg(0, ios::beg);
	file.seekp(0, ios::beg);

	int keyIndex = 0;
	int keyLen = key.length();

	char ip, op;

	while(file){
		keyIndex++;
		if(keyIndex >= keyLen)
			keyIndex = 0;

		file.get(ip);
		op = ip - (key[keyIndex] - 'a');
		file.seekp(-1, ios::cur);
		file.put(op);
	}
}

void caeserEncrypt(){
	char fileName[100];
	long long int key;
	cout << "Enter file name: ";
	cin >> fileName;
	cout << "Enter a numeric key that you need to remember: ";
	cin >> key;

	fstream file;
	file.open(fileName);

	if(!file){
		cout << "Unable to open the file!\n\n";
		exit(1);
	}

	file.seekg(0, ios::beg);
	file.seekp(0, ios::beg);

	char ip, op;
	int t = 1;

	while(file){
		file.get(ip);
		op = ip;
		t = 1;
		if(ip < 'A' || (ip > 'Z' && ip < 'a') || ip > 'z'){}
		else {
			while(t <= key) {
				op++;
				if(op > 'Z' && op < 'a')
					op = 'a';

				else if(op > 'z')
					op = 'A';
				t++;
			}
		}

		file.seekp(-1, ios::cur);
		file.put(op);
	}
}

void caeserDecrypt(){
	char fileName[100];
	long long int key;
	cout << "Enter file name: ";
	cin >> fileName;
	cout << "Enter the numeric key that you gave us: ";
	cin >> key;

	fstream file;
	file.open(fileName);

	if(!file){
		cout << "Unable to open the file!\n\n";
		exit(1);
	}

	file.seekg(0, ios::beg);
	file.seekp(0, ios::beg);

	char ip, op;
	int t = 1;

	while(file){
		file.get(ip);
		op = ip;
		t = 1;
		if(ip < 'A' || (ip > 'Z' && ip < 'a') || ip > 'z'){}
		else{
			while(t <= key) {
				op--;
				if(op < 'A')
					op = 'z';

				else if(op < 'a' && op > 'Z')
					op = 'Z';
				t++;
			}
		}
		
		file.seekp(-1, ios::cur);
		file.put(op);
	}
}

void playfairEncrypt(){
	char key[100];
	cout<<"Enter The Encryption Key : ";
	scanf("%s", key);
	int l=strlen(key);
	int i,j,p,q,t=0,c,flag=0;
	char chu = 'a';
	char ch=key[0];
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){ 
				
			if(t<l){
				c=0;
				while(c < t){
					if(ch == key[c]||(ch=='j'&&key[c]=='i')){
						flag=1;
						break;
					}
					else {
						flag=0;
					}
					c++;
				}

				if(flag==0){
					keyTable[i][j]=key[t];

					t++;
				}
				else{
					j--;
					t++;
				}
				ch=key[t];
			}
			else{
				int t = 0;
				while(t < l){
					if(key[t] == chu||(chu=='j'&&key[t]=='i'))
						break;
					t++;
				}
				
				if(t == l) {
					keyTable[i][j] = chu;
				}
				else 
					j--;
				chu++;
			}
		}
	}

	char fileName[100];
	cout << "Enter file name: ";
	cin >> fileName;

	fstream file;
	file.open(fileName);

	if(!file){
		cout << "Unable to open the file!\n\n";
		exit(1);
	}

	file.seekg(0, ios::beg);
	file.seekp(0, ios::beg);

	char a[2];
	int x[2],y[2];

	while(file){
		file.get(a[0]);
		file.get(a[1]);

		if(a[0] < 'a' || a[0] > 'z') {
			file.seekp(-2, ios::cur);
			file.put(a[0]);
			continue;
		}

		else if(a[1] < 'a' || a[1] > 'z') {
			file.seekp(-2, ios::cur);
			file.put(a[0]);
			file.put(a[1]);
			continue;
		}

		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				if(a[0]==keyTable[i][j])
				{ 
					x[0]=i;
					y[0]=j;
				}
				if(a[1]==keyTable[i][j])
				{
					x[1]=i;
					y[1]=j;
				}
			}
		}
		if(x[0]==x[1])
		{
			if(y[0]==4){
				a[0]=keyTable[x[0]][0];
			}
			else{
				a[0]=keyTable[x[0]][y[0]+1];
			}
			if(y[1]==4){
				a[1]=keyTable[x[1]][0];
			}
			else{
				a[1]=keyTable[x[1]][y[1]+1];
			}
		}
		else if(y[0]==y[1])
		{
			if(x[0]==4){
				a[0]=keyTable[0][y[0]];
			}
			else{
				a[0]=keyTable[x[0]+1][y[0]];
			}
			if(x[1]==4){
				a[1]=keyTable[0][y[1]];
			}
			else{
				a[1]=keyTable[x[1]+1][y[1]];
			}
		}
		else
		{
				a[0]=keyTable[x[0]][y[1]];
				a[1]=keyTable[x[1]][y[0]];		
		}

		file.seekp(-2, ios::cur);
		file.put(a[0]);
		file.put(a[1]);
	}
}

void playfairDecrypt(){
	char key[100];
	cout<<"Enter The Key : ";
	scanf("%s", key);
	int l = strlen(key);
	int i,j,p,q,t=0,c,flag=0;
	char chu = 'a';
	char ch=key[0];
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
				
			if(t<l){
				c=0;
				while(c < t){
					if(ch == key[c]||(ch=='j'&&key[c]=='i')){
						flag=1;
						break;
					}
					else {
						flag=0;
					}
					c++;
				}

				if(flag==0){
					keyTable[i][j]=key[t];

					t++;
				}
				else{
					j--;
					t++;
				}
				ch=key[t];
			}
			else{
				int t = 0;
				while(t < l){
					if(key[t] == chu||(chu=='j'&&key[t]=='i'))
						break;
					t++;
				}
				
				if(t == l) {
					keyTable[i][j] = chu;
				}
				else 
					j--;
				chu++;
			}
		}
	}
	
	char a[2];
	int x[2],y[2];

	char fileName[100];
	cout << "Enter file name: ";
	cin >> fileName;

	fstream file;
	file.open(fileName);

	if(!file){
		cout << "Unable to open the file!\n\n";
		exit(1);
	}

	file.seekg(0, ios::beg);
	file.seekp(0, ios::beg);

	while(file){
		file.get(a[0]);
		file.get(a[1]);

		if(a[0] < 'a' || a[0] > 'z') {
			file.seekp(-2, ios::cur);
			file.put(a[0]);
			continue;
		}

		else if(a[1] < 'a' || a[1] > 'z') {
			file.seekp(-2, ios::cur);
			file.put(a[0]);
			file.put(a[1]);
			continue;
		}

		for(i=0;i<5;i++){
			for(j=0;j<5;j++){
				if(a[0]==keyTable[i][j])
				{ 
					x[0]=i;
					y[0]=j;
				}
				if(a[1]==keyTable[i][j])
				{
					x[1]=i;
					y[1]=j;
				}
			}
		}
		if(x[0]==x[1])
		{
			if(y[0]==0){
				a[0]=keyTable[x[0]][4];
			}
			else{
				a[0]=keyTable[x[0]][y[0]-1];
			}
			if(y[1]==0){
				a[1]=keyTable[x[1]][4];
			}
			else{
				a[1]=keyTable[x[1]][y[1]-1];
			}
		}
		else if(y[0]==y[1])
		{
			if(x[0]==0){
				a[0]=keyTable[4][y[0]];
			}
			else{
				a[0]=keyTable[x[0]-1][y[0]];
			}
			if(x[1]==0){
				a[1]=keyTable[4][y[1]];
			}
			else{
				a[1]=keyTable[x[1]-1][y[1]];
			}
		}
		else
		{
				a[0]=keyTable[x[0]][y[1]];
				a[1]=keyTable[x[1]][y[0]];		
		}

		file.seekp(-2, ios::cur);
		file.put(a[0]);
		file.put(a[1]);
	}
}

void moreInfo(){
	cout << "\n---------------------------------------------------------\n\n";
	cout << "                 Details of algorithms!!";
	cout << "\n\n---------------------------------------------------------\n\n";
	cout << "RSA Algorithm: \n";
	cout << "RSA or Ridest Shamir Adleman algorithm is one of the first\n";
	cout << "In RSA algorithm the encryption key is public and decryption \n";
	cout << "key is private. The user gives a file and the algo returns a\n";
	cout << "private key and n that the user needs to use later to decrypt\n";
	cout << "the file.\n";

	cout << "\n----------------------------------------------------------\n";
	cout << "\nVignere Cipher: \n";
	cout << "It is a very basic method of encrypting alphabetic text. In \n";
	cout << "this cipher we take a string key from user and then using that\n";
	cout << "key encryption is performed. While decrypting the same key\n";
	cout << "must be provided bu the user for correct decryption\n";

	cout << "\n----------------------------------------------------------\n";
	cout << "\nCaesar Cipher: \n";
	cout << "It is the simplest and first cipher where encryption is\n";
	cout << "performed using a single numeric key. This key is essential\n";
	cout << "for decryption as well.\n";

	cout << "\n----------------------------------------------------------\n";
	cout << "\nPlayfair Cipher: \n";
	cout << "It also encrypts alphabetic text using a string as its key\n";
	cout << "It uses a tabular structure to perform the encryption and\n";
	cout << "decryption\n";

	cout << "\n----------------------------------------------------------\n\n";
}

int main(){
	cout << "---------------------------------------------------------\n";
	cout << "                   Encrypt - Decrypt\n";
	cout << "---------------------------------------------------------\n";

	int option = 0, algoOption;
	do {

		cout << "What do you want to do?\n";
		cout << "1. Encypt\n";
		cout << "2. Decrypt\n";
		cout << "3. Exit\n";
		cout << ">> ";
		cin >> option;

		if(option == 1){
			cout << "Okay then. I'll encrypt your file in a sec. Just one more question!\n";
			cout << "Which ALGORITHM would you like to use in encrypting your file.\n";
			cout << "Want to know about the algos write '6' when prompted\n";
			cout << "1. RSA Algorithm\n";
			cout << "2. Vignere Cipher\n";
			cout << "3. Caesar Cipher\n";
			cout << "4. Playfair Cipher\n";
			cout << ">> ";
			cin >> algoOption;

			switch(algoOption){
				case 1: rsaMain(); break;
				case 2: vignereEncrypt(); break;
				case 3: caeserEncrypt(); break;
				case 4: playfairEncrypt(); break;
				case 6: moreInfo(); break;
				default: cout << "Wasn't that an invalid option ;) \n";
			}
		}

		else if(option == 2){
			cout << "Which algorithm did you select while encrypting: \n\n";
			cout << "1. RSA algorithm\n";
			cout << "2. Vignere Cipher\n";
			cout << "3. Caesar Cipher\n";
			cout << "4. Playfair Cipher\n";
			cout << ">> ";
			cin >> algoOption;

			switch(algoOption) {
				case 1: rsaDecrypt(); break;
				case 2: vignereDecrypt(); break;
				case 3: caeserDecrypt(); break;
				case 4: playfairDecrypt(); break;
				default: cout << "Wasn't that an invalid option ;) \n\n";
			}
		}

		else if(option != 3){
			cout << "\nI don't think that is one of the options\n" << "Please try again\n\n";
		}

	} while(option != 3);

	cout << "Bye! Bye! See you soon ;)\n";
	return 0;
}

