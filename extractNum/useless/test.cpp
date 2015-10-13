#include <fstream>
using namespace std;

int main()
{
	fstream o("o.txt",ios::out);
	o<<"haha"<<endl;
	o.close();
	return 0;
}