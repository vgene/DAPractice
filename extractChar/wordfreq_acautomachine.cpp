#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#define maxlen 12
#define thr 50
using namespace std;
typedef pair <string,int> pp;
struct node
{
    node* fail;
    node* next[260];
    node* father;
    int id;
}*root;
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
queue<node*>b,leaf;
bool vis[1010]={};
unsigned char temp[100]={};
unsigned char buffer[3000]={};
unsigned char dfs_buffer[100]={};
data chcount[66000]={};
vector<data> wordcount_v;
int cnt=0,lcnt=0;
double getweight(pp x)
{

	return (double)x.second;
}
void insert(unsigned char* key,int id)
{
    node* p=root;
    for(int i=0;key[i];i++)
    {
        if(!p->next[key[i]])
        {
            p->next[key[i]]=(node*)malloc(sizeof(node));
            memset(p->next[key[i]],0,sizeof(node));
            p->next[key[i]]->father=p;
        }
        p=p->next[key[i]];
    }
    p->id=id;
    return;
}
void build_ac()
{
    b.push(root);
    while(!b.empty())
    {
        node* temp=b.front();
        b.pop();
        for(int i=0;i<256;i++)
        {
            if(!temp->next[i])continue;
            if(temp==root)
            {
                b.push(temp->next[i]);
                temp->next[i]->fail=root;
                continue;
            }
            for(node* j=temp->fail;j;j=j->fail)
            {
                if(j->next[i])
                {
                    temp->next[i]->fail=j->next[i];
                    break;
                }
            }
            if(!temp->next[i]->fail)temp->next[i]->fail=root;
            b.push(temp->next[i]);
        }
    }
    return;
}
void dfs(node *p,int len)
{
	if(p->id>0)
	{
		dfs_buffer[len]='\0';
		string s=(char *)dfs_buffer;
		double w=getweight(make_pair(s,p->id));
		wordcount_v.push_back(data(s,p->id,w));
	}
	for(int i=0;i<256;i++)
	{
		if(p->next[i])
		{
			dfs_buffer[len]=i;
			dfs(p->next[i],len+1);
		}
	}
	return;
}
void bfs()
{
	node* p=root;
	while(!b.empty())b.pop();
	for(int i=0;i<256;i++)
	{
		if(p->next[i])b.push(p->next[i]);
	}
	while(!b.empty())
	{
		p=b.front();
		b.pop();
		if(p->id>0)
		{
			if(p->fail->id>(p->id*0.95))p->fail->id-=p->id;
		}
		if(p->id<0)p->id=0;
		bool flag=false;
		for(int i=0;i<256;i++)
			if(p->next[i])
			{
				b.push(p->next[i]);
				flag=true;
			}
		if(!flag)leaf.push(p);
	}
	while(!leaf.empty())
	{
		p=leaf.front();
		leaf.pop();
		int diff=p->id;
		while(p!=root)
		{
			p=p->father;
			p->id-=diff;
			if(p->id>0)diff+=p->id;
		}
	}
	dfs(root,0);
	/*p=root;
	while(!b.empty())b.pop();
	for(int i=0;i<256;i++)
		if(p->next[i])b.push(p->next[i]);
	while(!b.empty())
	{
		p=b.front();
		b.pop();
		for(int i=0;i<256;i++)
			if(p->next[i])
			{
				b.push(p->next[i]);
			}
		if(p->id>0)
		{
			string s=(char *)p->s;
			double w=getweight(make_pair(s,p->id));
			wordcount_v.push_back(data(s,p->id,w));
		}
		
	}*/	
}

void readchfreq()
{
	freopen("charfreq.txt","r",stdin);
	unsigned char c1,c2;
	int _cnt;
	double _freq;unsigned char temp[3]="";
	while(~scanf("%c%c%d%lf",&c1,&c2,&_cnt,&_freq))
	{
		temp[0]=c1;
		temp[1]=c2;
		string s=(char *)temp;
		chcount[c1*256+c2]=data(s,_cnt,_freq);
	}
}
int main()
{
	root=(node*)malloc(sizeof(node));
    memset(root,0,sizeof(node));
    unsigned char c1,c2;int tmpfreq;
	readchfreq();
	freopen("wordfreq.txt","r",stdin);
	freopen("wordfreq_acautomachine.txt","w",stdout);
	while(~scanf("%s%d",buffer,&tmpfreq))
	{
		cnt++;
		if(tmpfreq>thr)insert(buffer,tmpfreq);
		else 
		{
			string s=(char *)buffer;
			double w=getweight(make_pair(s,tmpfreq));
			wordcount_v.push_back(data(s,tmpfreq,w));
		}
	}
	build_ac();
	cerr<<"finish reading. pushing..."<<endl;
	bfs();
	cerr<<"sorting..."<<endl;
	sort(wordcount_v.begin(),wordcount_v.end(),greater<data>());
	cerr<<"sorted. printing..."<<endl;
	for(vector<data>::iterator i=wordcount_v.begin();i!=wordcount_v.end();i++)
	{
		if(i->freq<=1)break;
		cout<<i->key<<" "<<i->freq<<" "<<i->weight<<endl;
	}
    return 0;
}
