#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

ifstream trainData;
ofstream outputData;

string strLine;
stack<char> tmp;
int documentID;
unsigned long lineOffset=0;
unsigned long characterOffset;



void updateDocumentIDandLengthOffset(){
    unsigned long len=strLine.length();
    char firstChar=strLine[0];
    int ID=0;
    if (firstChar>'0' && firstChar<='9')
    {
        ID=firstChar-'0';
        int i=1;
        
        while (strLine[i]!=','&&i<len)
        {
            ID=ID*10+strLine[i]-'0';
            i++;
        }
        documentID=ID;
        lineOffset=0;
    }
    else
        lineOffset++;
}

unsigned long readLine(){
    unsigned long len;
    
    getline(trainData,strLine);
    len=strLine.length();
    
    if (len>0)
        updateDocumentIDandLengthOffset();
    
    return len;
}

int getOffset(){
    
    return 0;
}

//find yuan, if
unsigned long findYuan(){
    
    unsigned long len=strLine.length();

    if (len>2)
    for (unsigned long i=characterOffset+1;i<len-1;i++)
        if (strLine[i]==(char)0xd4 && strLine[i+1]==(char)0xaa)
            return i;
    
    return 0;
}

//find the number before "yuan"
string getPrevNum(){
    while (!tmp.empty()) tmp.pop();
    long pos=characterOffset;
    while (pos-->0 && (strLine[pos]>'9'|| strLine[pos]<'0'));
    
    char now=strLine[pos];
    while ((now>='0'&&now<='9')||now==','||now==(char)0xac ||now=='.')
    {
        // if comma
        if (now==(char)0xac)
        {
            if (strLine[pos-1]==(char)0xa3) pos--;
            else break;
        }
        if ((now>='0'&&now<='9')||now=='.')
            tmp.push(now);
        now=strLine[--pos];
    }
    
    string tmpStr="";
    while (!tmp.empty())
    {
        tmpStr+=tmp.top();
        tmp.pop();
    }
    
    //wan yuan
    if (tmpStr.length()>0 && strLine[characterOffset-1]==char(0xf2) && strLine[characterOffset-2]==char(0xcd))
    {
        double tempDouble;
        stringstream ss(tmpStr),ss2;
        ss>>tempDouble;
        tempDouble*=10000;
        ss2<<(unsigned long)tempDouble;
        return ss2.str();
    }
    return tmpStr;
}

int main(int argc, char *argv[])
{
    
	if (argc>2)
	{
        trainData.open(argv[1],ios::in);
   		outputData.open(argv[2],ios::out);
   	}
    
    while (!trainData.eof())
    {
        readLine();
        characterOffset=0;
        while ((characterOffset=findYuan())!=0)
        {
            string prevNum=getPrevNum();
            if (prevNum.length()>0)
            outputData<<documentID<<' '<<lineOffset<<' '<<characterOffset<<' '<<prevNum<<endl;
            //cout<<documentID<<' '<<lineOffset<<' '<<characterOffset<<endl;
        }
        
        
    }
    
    trainData.close();
    outputData.close();
    return 0;
    
}
