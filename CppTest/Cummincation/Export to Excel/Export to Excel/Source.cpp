#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	ofstream outData;
	string s ="G kraft";
	int recvbuf;
	int recvold;
	int n[] = { 0 };
	while (recvold!=recvbuf)
	{
		n[]+recvbuf;
		recvold = recvbuf;

	}
	
	
	outData.open("outfile.csv", ios::app);
	system("pause");
	return 0;
}