#pragma once
#include"ADTHelper.h"
ADTBEGIN
ADTSUBBEGIN(String)

struct String
{
	std::unique_ptr<char[]> _data = nullptr;
	size_t length = 0;
	char& operator[](size_t pos)
	{
		CHECK_BOUND_AND_THROW(pos, length);
	}
};

constexpr auto inline NoPos = std::size_t(-1);

Status StrAssign(String&S,const char* data)
{
	S._data = std::make_unique<char[]>(strlen(data) + 1);
	strcpy(S._data.get(), data);
	S.length = strlen(data);
	S._data[S.length] = '\0';
	return OK;
}

Status StrAssign(String&S,size_t count)
{
	S._data = std::make_unique<char[]>(count + 1);
	S.length = count;
	S._data[S.length] = '\0';
	return OK;
}

bool StrEmpty(String&S)
{
	return S.length == 0;
}

int StrComp(String const& lhs, String const& rhs)
{
	return strcmp(lhs._data.get(), rhs._data.get());
}

size_t StrLength(String const& S) { return S.length; }

void ClearStr(String& S)
{
	S._data.reset();
	S.length = 0;
}

void Concat(String& T, String const& S1, String const& S2)
{
	T._data = ASSIGNARRAY(char, S1.length + S2.length + 1);
	auto temp = T._data.release();
	strcpy(temp, S1._data.get());
	temp = strcat(temp, S2._data.get());
	temp[S1.length + S2.length] = '\0';
	T._data = std::unique_ptr<char[]>(temp);
	T.length = S1.length + S2.length;
}

bool SubString(String & Sub,String const& S,size_t pos,size_t len)
{
	if(pos>S.length)return false;
	if(pos+len>S.length)return false;
	Sub._data = std::make_unique<char[]>(len + 1);
	strncpy(Sub._data.get(), S._data.get() + pos - 1, len);
	Sub.length=len;
	Sub._data[Sub.length] = '\0';
	return true;
}

std::unique_ptr<size_t[]> get_next(String const&S) 
{
	auto p = std::make_unique<size_t[]>(S.length + 2); p[1] = 0;
	auto i = 2, j = 0;	//i is next[] index while j is S 's index
	while (i <= S.length)
	{
		//if(j==0||S._data[i]==S._data[j]){p[++i]=++j;}
		if (j == 0 || S._data[i-2] == S._data[j-1]) { j++; p[i++] = j; }
		//if the next ch S[i] equal to S[j] ,we make next[i++]=j++,it means we can join it to pre_fix directly;
		// while j==0 means no pre_fix;
		else { j = p[j]; }
		//if S[i]!=S[j],we expected longest S[0,...,j] pre_fix to fit S[i];as it equal to next[j];
		/*Example:
		* abaabc:
		* for start,i=1,j=0,so S[1]=b!=S[0]=a,means no pre_fix to fit it,so mark it next[2]=1;
		* then i++==2,move to S[2]=a,while S[j==1]=b.so we search longest pre_fix in S[0,1]=="ab",which is eqaul to next[1]==0;
		* then i++==3,move to S[3]=a,while S[j==1]=b,as previous comment,S[0,1]=="ab",next[3]=1;
		* then i++==4,move to S[4]=b,while S[j==1]=b,we can join it to pre_fix directly,so next[4]=j++==2;
		* then i++==5,move to S[5]=c,while S[j==2]=a,mismatch,so search pre_fix in S[0~2]="aba":
		* next[2]==1,S[1]==b,mismatch,continue! as we finally found next[5]=1;
		* but there is a exception:we expected that next[5]==2 but 1;
		* cause when i==k while T==S[0~k-1] but not S[0~k-2],which means index error while compare ch;
		* so we can say the comment code is wrong!
		*/
		/*if we let i=k while T=S[0~k-2],then:
		* i==1:No substring contains,let next[1]=0;
		* i==2:T="a",j==0,means there's no pre_fix,let next[2]=1;
		* i==3:j==1,T="ab",S[i-2]=='b' wait to be processed; S[j-1]=='a'!=S[i-2];so j=next[j]==0,means no pre_fix;
		* i==4:j==1,T="aba",S[i-2]=a==S[j-1]=a,so we can join it to pre_fix directly,next[4]=j+1==2;
		* i==5:j==2,T="abaa",S[i-2]=a!=S[j-1]=b,so search S[0~2]="aba" pre_fix=1,then S[j-1]==S[i],next[5]=next[2]+1==2
		* i==6:j==2,T="abaab",S[i-2]==b=S[j-1],as i==4 case:next[6]=j++==3;
		* <summary>
		* i			1	2	3	4	5	6
		* next[i]	0	1	1	2	2	3
		* <summary/>
		* as textbook expected
		* There is another example:
		* "abaabcac"
		* i==1:no substring contains,let next[1]=0;
		* i==2:T="a",j==0,as above,next[2]=1;
		* i==3:T="ab",j==1,S[i-2]=='b'!='a'==S[j-1],so search pre_fix in S[0,1]="ab",j=next[j]=0,means no pre_fix;
		* i==4:T="aba",j==1,S[i-2]=='a'==S[j-1],next[4]=++j;
		* i==5:T="abaa",j==2,S[i-2]=='a'!=S[j-1],search pre_fix in S[0~2]="aba" as above,j=next[j]==1,
		S[i-2]==S[j-1],next[5]=j++1==2;
		* i==6:T="abaab",j==2,S[i-2]==S[j-1],next[6]=++j;
		* i==7:T="abaabc",j==3,cause 'c'is not append before,expecte next[7]=1;
		* i==8:T="abaabca",j==1,S[i-2]==S[j-1],next[8]=2;
		* <summary>
		* i			1	2	3	4	5	6	7	8
		* next[i]	0	1	1	2	2	3	1	2
		* </summary>
		* as textbook expected
		*/
	}
	return p;
};

size_t Index(String const& S, String const& T, size_t pos)//return 1 base index,-1==npos
{
	size_t i = pos;//1 base
	size_t j = 1;//1 base
	auto next = get_next(T);
	/*for (int i = 1; i <= T.length; i++)
		std::cout << next[i] << " ";*/
	while (i <= S.length && j <= T.length)
	{
		if (j == 0 || S._data[i - 1] == T._data[j - 1]) { i++; j++; }
		//assume from 1 base,but str ch from 0 base;
		else { j = next[j]; }
		/*if (j == 0 || S._data[i] == T._data[j]) { i++; j++; }//assume from 1 base;
		else { j = next[j]; }*/
		/*the commened code is about index error
		* Example:
		* S="acabaabaabcacaabc",T="abaabcac"
		* i==1,j==1:match,i++,j++;
		* i==2,j==2:mismatch,i keeps 2,then j is about to be look back accroding to next[j];
		* as next[j]==1;
		* i==2,j==1:mismatch,j is about to be looked back,and finally,j==0,means S&T need to slide;
		* i==3,j==1:match ,i++,j++,continue;
		* ...;
		* i==8,j==6:mismatch,j is about to be looked back -> j=3,continue;
		* i==8,j==3:match,i++,j++,continue;
		* ...;
		* i==13,j==8:match,and j==T.length,continue;
		* i==14,j==9:j>T.length,break;
		*/
	}
	if (j > T.length)return i - T.length;
	return NoPos;
}

bool StrInsert(String& S, size_t begin, String const& replace) 
{
	CHECK_BOUND(begin, S.length);
	String temp;
	StrAssign(temp, S.length + replace.length);
	strncpy(temp._data.get(), S._data.get(), begin);
	strcat(temp._data.get(), replace._data.get());
	strncpy(temp._data.get()+begin+replace.length, S._data.get() + begin, S.length - begin);
	S = std::move(temp);
	return true;
};

bool Replace(String& S, size_t begin, String const& replace)
{
	CHECK_BOUND_WITH_LENGTH(begin, replace.length, S.length);
	strncpy(S._data.get() + begin - 1, replace._data.get(), replace.length);
	return true;
}

bool Replace(String& S, String const& target, String const& replace) 
{
	auto pos1 = Index(S, target, 1);
	if (pos1 == NoPos)return false;
	while (pos1 != NoPos)
	{
		if (!Replace(S, pos1, replace))return false;
		pos1 = Index(S, target, pos1 + target.length);
	}
	return true;
};

bool StrDelete(String &S,size_t pos,size_t len)
{
	CHECK_BOUND_WITH_LENGTH(pos, len, S.length);
	String temp;
	StrAssign(temp, S.length - len);
	strncpy(temp._data.get(), S._data.get(), pos);
	strncpy(temp._data.get(), S._data.get() + pos + len - 1, S.length - len);
	S = std::move(temp);
	return true;
}

void DestoryString(String& S)
{
	RELEASE_POINTER(S._data);
	S.length = 0;
}

ADTSUBEND;
ADTEND;