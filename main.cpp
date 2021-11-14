#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;




/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void ReadFile(string &A, string &B);

int main(int argc, char** argv) {
	string A;
	string B;
	ReadFile(A,B);
	return 0;
}

void ReadFile(string &A, string &B){
	fstream fi;
	fi.open("Text.txt");
	while(!fi.eof()){
		fi >> A; 
		cout << A;
		fi >> B;
		cout << B;
		cout << endl;
	}
	fi.close();

}

void Check(){
	cout << "success";
}
