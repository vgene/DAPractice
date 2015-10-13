#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#define maxlen 10
using namespace std;
typedef pair<string,int> pp;
char temp[3]={};
unsigned char c1,c2;
map <string,int> a;
vector<pp> b;
int cnt=0;
bool comp(pp x, pp y)
{
	return x.second>y.second;
}
int main()
{
	freopen("chonly.txt","r",stdin);
	freopen("charfreq.txt","w",stdout);
	while(~scanf("%c",&c1))
	{
		cnt++;
		if(!(cnt%100000))cerr<<cnt<<endl;
		if(c1<160)continue;
		scanf("%c",&c2);
		temp[0]=c1;temp[1]=c2;
		string s=temp;
		a[s]++;
	}
	for(map<string,int>::iterator i=a.begin();i!=a.end();i++)
	{
		b.push_back(*i);
		//cout<<i->first<<" "<<i->second<<endl;
	}
	sort(b.begin(),b.end(),comp);
	for(vector<pp>::iterator i=b.begin();i!=b.end();i++)
	{
		cout<<i->first<<" "<<i->second<<" "<<(double)i->second/(double)cnt<<endl;
	}
	return 0;
}

