//============================================================================
// Name        : crc.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
#include<cstdlib>

#define MAX 1000
using namespace std;

class crc
{
	int dataword[MAX],codeword[MAX],dividend[MAX],f_code[MAX],n,k,r;
	int gen [4] = {1,0,1,1}, zero [4]={0,0,0,0}; //if generator of g length replace 4 with g everywhere
	int ptr1=4,ptr2=0;

public:
	crc(int d[],int dn)
{
		k=dn;	//length of data word
		for(int i=0;i<dn;i++)
		{
			dataword[i]=d[i];
			dividend[i]=d[i];
		}
		//n-k+1 = 4;	//4 = len of generator
		n = 3 + k; //length of code word
		r = n-k;

}
	bool check(const int array[])
	{
	    const int a0 = 0;

	    for (int i = 0; i < 4; i++)
	    {
	        if (array[i] != a0)
	            return false;
	    }
	    return true;
	}
	void receiver(int[],string);
	int* xoring(int[],int[]);
	void append()
	{
		for(int i=k;i<n;i++)
		{
			dividend[i]=0;
		}
	}
	void detection(string);
	void print()
	{
		cout<<"\nYour data word\n";
		for(int i=0;i<k;i++)
		{
			cout<<dataword[i]<<" ";
		}
		cout<<"\nGenerator\n";
		for(int i=0;i<4;i++)
		{
			cout<<gen[i]<<" ";
		}
		cout<<"\nDividend \n";
		for(int i=0;i<n;i++)
		{
			cout<<dividend[i]<<" ";
		}
		
	}

};

int* crc::xoring(int a[],int b[])
{
	int *result=new int[4];		//4 cuz length of generator is 4
	cout<<endl<<"a ";
	for(int i=0;i<4;i++)
				{
					cout<<a[i]<<" ";
				}
	cout<<endl<<"b ";
	for(int i=0;i<4;i++)
				{
					cout<<b[i]<<" ";
				}
	for(int i=0;i<3;i++)	//xoring only last 3 digits
	{
		if(a[i+1]==b[i+1])
		{
			result[i]=0;
		}
		else
		{
			result[i]=1;
		}
	}

	if(ptr1<n &&ptr2==0)
	{
		result[3]=dividend[ptr1];	//carry
		ptr1++;
	}
	if(ptr2<n && ptr2!=0)
	{
		result[3]=f_code[ptr2];	//carry
		ptr2++;
	}

	cout<<"\na xor b ";
	for(int i=0;i<4;i++)
	{
		cout<<result[i]<<" ";
	}
	return result;

}

void crc::detection(string dword)
{
	//performing modulo-2 division
	int a[4],b[4];

	memcpy(a,dividend,sizeof(a));	//copies array first four digits of dividend in array a


	for(int i=4;i<=n;i++)
	{
		if(a[0]==1)
		{
			memcpy(b,gen,sizeof(a));	//copies array gen in array b
		}
		else
		{
			memcpy(b,zero,sizeof(b));	//makes all elements of b zero
		}
		int *res=xoring(a,b);
		memcpy(a,res,sizeof(a));	//copying result into a

	}
	cout<<endl;
	cout<<"Remainder to be appended to dataword ";
	for(int i=0;i<r;i++)
	{
		cout<<a[i]<<" ";
	}
	for(int i=0;i<k;i++)		//copying dataword as it is in the code word
	{
		codeword[i]=dividend[i];
	}
	for(int i=k;i<n;i++)	//final codeword
	{
		codeword[i]=a[i-k];
	}
	
	cout<<"\nCodeword \n";
		for(int i=0;i<n;i++)
		{
			cout<<codeword[i]<<" ";
		}

	//sending to receiver

	memcpy(f_code,codeword,sizeof(codeword));
	int rand(),num,M=0;
	srand(time(0));
	num = M + rand()/(RAND_MAX/(n-M+1) + 1);
	cout<<"\n"<<num;
	cout<<"\nSending codeword to receiver\n";
	cout<<"Do you wish to manipulate bits?\n";
	char ch='n';
	cin>>ch;
	if(ch=='y')
	{
		if(f_code[num]==1)
		{
			f_code[num]=0;
		}
		else
		{
			f_code[num]=1;
		}
	}
	receiver(f_code,dword);
}

void crc::receiver(int code[],string word)
{
	//performing modulo-2 division
		int a[4],b[4];
		ptr2=4;
		for(int i=0;i<n;i++)
		{
			cout<<code[i]<<" ";
		}

		memcpy(a,code,sizeof(a));	//copies array first four digits of codeword in array a


		for(int i=4;i<=n;i++)
		{
			if(a[0]==1)
			{
				memcpy(b,gen,sizeof(a));	//copies array gen in array b
			}
			else
			{
				memcpy(b,zero,sizeof(b));	//makes all elements of b zero
			}
			int *res=xoring(a,b);
			memcpy(a,res,sizeof(a));	//copying result into a

		}


		if(check(a))
		{
			cout<<"No error detected\n";
			cout<<"CRC Passed!\n";
			cout<<"The word received is "<<word<<"\n";
		}
		else{
		cout<<"CRC Failed\n";
			cout<<"There's an error in the received string\n";
		}
}

int k=0;
void ascToBin(int character, int *ones)
    {

        if(character == 1)
        {
        	//cout<<"1";
        	// *ones+=1;
        	ones[k]=1; k++;
           return;
        }
        else
        {
            char out;
            if((character%2) == 0)
            {
                 out = '0';
                 character = character/2;
            }
            else
            {
                 out = '1';
                 character = character/2;

                // *ones+=1;
            }
            ascToBin(character, ones);
            ones[k]=out-'0'; k++;
           //putchar(out);
        }
    }

int main() {

	string dataword;

	int data[MAX],dn;
	cout<<"Enter dataword to be sent \n";
	cin>>dataword;
	dn=dataword.length();

	for(int i=0;i<dn;i++)
	{
		ascToBin(dataword[i],data);
	}
	for(int i=0;i<k;i++)
	{
		cout<<data[i];
	}
	crc e(data,k);
	e.append();
	e.print();
	e.detection(dataword);
	


	return 0;
}

