#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;
int main()
{
	freopen("wordfreq.txt","r",stdin);
	freopen("usualword.txt","w",stdout);
	int i=1000000;
	char c;
	while(--i)
	{
		c=getchar();
		putchar(c);
	}
	return 0;
}

