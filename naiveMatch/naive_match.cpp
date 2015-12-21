#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stack>
#include <cstring>

//#define TEST_INPUT
using namespace std;
const int MAX_VERI_NUM=40;
const int MAX_NUM_WORDLIST=200;
const int MAX_NUM_NUMLIST=60000;

//fstream
ifstream wordListData, numData, trainData;
ofstream outputData;

//wordList
string wordList[MAX_NUM_WORDLIST];
int wordListNum;

//numList
struct num_element{
	string number;
	unsigned long line;
	int id;
	int lineos;
	int charos;
};
num_element numList[MAX_NUM_NUMLIST];
int numListNum;
int numListNow=0;
int numListPrev=0;

//position
string strLine;
int documentID;
unsigned long lineOffset=0;
unsigned long characterOffset;
int lineTotal=0;
//importWordList and sort words by length
int CMP(const void*a,const void*b)
{
	string s1=*(string*)a;
	string s2=*(string*)b;
	return s2.length()-s1.length();
}

void importWordList(){
	wordListNum=0;
	while (!wordListData.eof())
		getline(wordListData,wordList[wordListNum++]);

	//sort
	qsort(wordList,wordListNum,sizeof(string),CMP);
	#ifdef TEST_INPUT
		for (int i=0;i<wordListNum;i++)
			cout<<wordList[i]<<endl;
	#endif
}

void importNumList(){
	numListNum=0;
	string tmpLine;

	while(!numData.eof()){
		getline(numData,tmpLine);
		stringstream ss(tmpLine);
		ss>>numList[numListNum].line>>numList[numListNum].id>>numList[numListNum].lineos;
		ss>>numList[numListNum].charos>>numList[numListNum].number;
		numListNum++;
	}

}
//Input line and deal with it
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
    lineTotal++;
    return len;
}

string matchNum(int wordPosStart, int wordPosEnd){
	int pos;
	int lineLength=strLine.length();
	numListNow=numListPrev;

	//std::cout<<lineTotal<<endl;

	if (numList[numListNow].line<lineTotal){
		while (numList[numListNow].line<lineTotal)
			numListNow++;
		numListPrev=numListNow;
	}
	while (numList[numListNow].line==lineTotal && numList[numListNow].charos<=wordPosEnd)
		numListNow++;

	//std::cout<<numList[numListNow].line<<' '<<numList[numListNow].charos<<' '<<wordPosEnd<<endl;

	if (numList[numListNow].line==lineTotal && numList[numListNow].charos-wordPosEnd<MAX_VERI_NUM){		
		std::cout<<numList[numListNow].line<<' '<<numList[numListNow].charos<<' '<<wordPosEnd<<endl;
		return numList[numListNow].number;
	}
	return "";
}

void findWordAndMatch(){
	string num;
	for (int i=0;i<wordListNum;i++){
		if (wordList[i].length()==0)
			continue;
		int pos=0;
		while ((pos=strLine.find(wordList[i],pos))!=string::npos){
			if ((num=matchNum(pos,pos+wordList[i].length()))!="")
				outputData<<documentID<<','<<wordList[i]<<','<<num<<'\r'<<'\n';
			pos++;
		}
	}
	numListPrev=numListNow;
}

int main(int argc, char *argv[])
{
    cout<<"Please input fileName of worldList, #trainData, #woldlist, #numlist, #output(default will be output.csv)"<<endl;
	if (argc>3){
		string defaultOutName="output.csv";
		if (argc>4)
			defaultOutName=argv[4];
		trainData.open(argv[1],ios::in);
        wordListData.open(argv[2],ios::in);
        numData.open(argv[3],ios::in);
   		outputData.open(defaultOutName,ios::out);
   		outputData<<"documentid,property,value"<<'\r'<<'\n';
   	}
   	else{
   		cout<<"ERROR: number of input files less than three"<<endl;
   		return -1;
   	}
    
	importWordList();
	importNumList();
    while (!trainData.eof())
    {
        readLine();
        findWordAndMatch();
    }
    std::cout<<numListNum<<' '<<wordListNum<<endl;
	wordListData.close();
	numData.close();
	outputData.close();
	return 0;
}
