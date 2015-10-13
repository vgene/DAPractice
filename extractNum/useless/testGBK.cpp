#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	fstream o;
	o.open("out.txt",ios::out);
	char ctr;
	string str;
	cin>>str;
	o<<str<<endl;
o.close();
	//cin>>ctr;
	// if (ctr=='i')
	// {
	// 	char c[2];
	// 	cin>>c[0]>>c[1];
	// 	cout<<hex<<short(c[0])<<hex<<' '<<short(c[1])<<endl;
	// }
	// else 
	//	if (ctr=='o')
	// {
	// 	// int x1,x2;
	// 	// char* ch;
	// 	// ch=new char[3];

	// 	// scanf("%x%x",&x1,&x2);
	// 	// ch[0]=x1;
	// 	// ch[1]=x2;
	// 	// ch[2]=0x83;

	// 	o<<"1234";//<<endl<<ch<<endl;

	// }
	//o.close();
	return 0;
}