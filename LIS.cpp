#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int length = 0; //length of vector
ifstream in_stream; //input stream object

void getInput(vector <double>& X, vector <double>& L);

int findLength(vector <double>& X, vector <double>& L);

int main(){

	//declare vector for input
	vector <double> X;
	//declare array for tracking
	vector <double> L;

	//open and read file
	in_stream.open("incseq.txt");
	if (in_stream.fail()) {
		cout << "Unable to find input file" << endl;
		exit(1);
	}

	//apply values in file
	cout << "Input Sequence: ";
	getInput(X,L);
	cout << endl;


	int longestLength = findLength(X, L);
	cout << "longest increasing subsequence has length of: " << longestLength << endl;

	in_stream.close();
	return 0;

}

void getInput(vector <double>& X, vector <double>& L) { //loads vector with data from input file,make L the same length, prints sequence
	double next;
	while (in_stream >> next) {
		X.push_back(next);
		cout << next << " ";
		length = length + 1;
	}

	for (int i = 0; i < length; i++) {
		L.push_back(0);
	}
}

int findLength (vector <double>& X, vector <double>& L){ //find Longest increasing subsequence and its length
	L[0] = 1;
	int maxLength = 1;
	int endSeqIndex = 0;
	for (int i = 1; i < length; i++) {
		if (X[i] > X[endSeqIndex]) {
			L[i] = L[endSeqIndex] + 1;
			maxLength = L[i];
			endSeqIndex = i;
		}
		else if (X[i] > X[i - 1]) {
			L[i] = L[i - 1] + 1;
			if (L[i] > maxLength) {
				maxLength = L[i];
				endSeqIndex = i;
			}
		}
		else {
			L[i] = 1;
			for (int j = (i - 1); j >= 0; j--) {
				if (X[j] < X[i]) {
					if (L[j] >= L[i]) {
						L[i] = L[j] + 1;
					}
				}
			}
			if (L[i] > maxLength) {
				maxLength = L[i];
				endSeqIndex = i;
			}
		}
	}
	//print longest subsequence
	vector <double> longestSeq;
	longestSeq.push_back(X[endSeqIndex]);
	int tempMax = maxLength;
	for (int i = (endSeqIndex - 1); i >= 0; i--) {
		if (L[i] == (tempMax - 1)) {
			longestSeq.push_back(X[i]);
			tempMax = tempMax - 1;
		}

	}
	cout << "Longest increasing subsequence: ";
	for (int i = (maxLength - 1); i >= 0; i--) {
		cout << longestSeq[i] << " ";
	}
	cout << endl;

	return maxLength;



}