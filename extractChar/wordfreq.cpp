#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#define maxlen 33
#define thr 5
using namespace std;
typedef pair <string,int> pp;
struct data
{
	string key;
	int freq;
	double weight;
	data(){}
	data(string _key,int _freq,double _weight):key(_key),freq(_freq),weight(_weight){}
	bool operator < (data oth) const
	{
		return weight<oth.weight;
	}
	bool operator > (data oth) const
	{
		return weight>oth.weight;
	}
};
char temp[100]={};
char buffer[3000]={};
map <string,data> chcount;
map <string,int> wordcount;
vector<data> wordcount_v;
int cnt=0,lcnt=0;
int main()
{
	unsigned char c1,c2;
	//readchfreq();
	freopen("chonly.txt","r",stdin);
	freopen("wordfreq.txt","w",stdout);
	while(gets(buffer)!=NULL)
	{
		lcnt++;
		if(!(lcnt%1000))
		cerr<<lcnt<<" "<<cnt<<endl;
		int len=strlen(buffer);
		cnt+=len;
		for(int j=2;j<=maxlen;j++)
		{
			for(int i=0;i<=len-2*j;i+=2)
			{
				memset(temp,0,sizeof(temp));
				for(int k=0;k<j*2;k++)
					temp[k]=buffer[i+k];
				string s=temp;
				wordcount[s]++;
			}
		}
	}
	cnt/=2;
	cerr<<"finish reading. pushing..."<<endl;
	for(map<string,int>::iterator i=wordcount.begin();i!=wordcount.end();i++)
	{
		double w=i->second;
		if(w<=thr)continue;
		wordcount_v.push_back(data(i->first,i->second,w));
	}
	cerr<<"sorting..."<<endl;
	sort(wordcount_v.begin(),wordcount_v.end(),greater<data>());
	cerr<<"sorted. printing..."<<endl;
	for(vector<data>::iterator i=wordcount_v.begin();i!=wordcount_v.end();i++)
	{
		
		cout<<i->key<<" "<<i->freq<<endl;
	}
	return 0;
}

