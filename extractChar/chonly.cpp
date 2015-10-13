#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<map>
using namespace std;
#define BANLIST_MAXLEN 10 
char temp[3]={};
char banlist[BANLIST_MAXLEN+2][3]={"¡¶","¡·","£¨","£©","¡¢","£¬","£»","£º","¡£","µÄ"};
char buffer[3000]={};
int cnt=0;
bool lastflag=true;
int main()
{
	freopen("data.csv","r",stdin);
	freopen("chonly.txt","w",stdout);
	while(gets(buffer)!=NULL)
	{
		cnt++;
		if(!(cnt%1000))cerr<<cnt<<endl;
		int len=strlen(buffer);
		for(int i=0;i<len-1;i++)
		{
			unsigned char c=buffer[i];
			if(c<160)
			{
				if(!lastflag)
				{
					cout<<endl;
					lastflag=true;
				}
				continue;
			}
			temp[0]=c;temp[1]=buffer[++i];
			bool flag=true;
			for(int j=0;j<BANLIST_MAXLEN;j++)
			{
				if(!strcmp(temp,banlist[j]))
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				lastflag=false;
				cout<<temp;
			}
			else 
				if(!lastflag)
				{
					cout<<endl;
					lastflag=true;
				}
		}
		cout<<endl;
	}
	
	return 0;
}

