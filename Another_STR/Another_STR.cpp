// Another_STR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stack.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
stack<string> toantu;
stack<double> val;
vector<string> infix;

string trim( const string& s )
{
	string result( s );
	result.erase( result.find_last_not_of( " " ) + 1 );
	result.erase( 0, result.find_first_not_of( " " ) );
	return result;
}

bool IsOperator( string t ) 
{
	if (t=="+"||t=="-"||t=="*"||t=="%"||t=="/"||t=="^") return true ;
	return false;
};
int GetPriority( string t )
{
	if (t=="^") return 3;
	if (t=="*"||t=="/") return 2;
	if (t=="+"||t=="-") return 1;
	return 0;
};

vector<string> split2token( string s )
{
	vector<string> str;
	istringstream iss( s );
	string        token;
	int           cntr = 0;
	while (getline( iss, token , ' ' ))
	{
		str.push_back( trim ( token ) ) ;
	}
	return str;
}
string re_format(string s)
{
	s +=" ";
	string output;
	static int buff(0);
	int strlen=s.length();
	for(int i=0;i<strlen; )
	{
		if(!isdigit(s[i]))
		{
			if(buff!=0)

			{
				string str=s.substr(i-buff,buff);

				output.append(str).append(" ");

				buff = 0;
			};


			string ope(1,s[i]);
			output.append(ope).append(" ");

			i++;
		}
		else
		{
			buff++;
			i++;
		}
	};
	
	return output.substr(0,output.size()-2);
};
bool IsNumberic( string t )
{
	int strlen=t.length();
	for(int i=0;i<strlen;i++)
	{
		if(!isdigit(t[i])){return false;break;}
	};
	return true;
}
string infix2postfix(vector<string> infix)
{
	int size=infix.size();
	string postfix(" ");
	for(int i=0;i<size;i++)
	{
		if ( IsNumberic ( infix[i] ) )
			postfix.append(infix[i]).append(" ");
		else if (infix[i] == "(")
			toantu.push( infix[i] );
		else if (infix[i] == ")")
		{
			string x = toantu.pop();
			while (x != "(")
			{
				postfix.append(x).append(" ");
				x = toantu.pop();
			}
		}
		else// IsOperator(s)
		{
			while (!toantu.isempty() && GetPriority(infix[i]) <= GetPriority(toantu.topstack()))
				postfix.append(toantu.pop()).append(" ");
			toantu.push( infix [i] );
		}
	}

	while (!toantu.isempty())
		postfix.append(toantu.pop()).append(" ");

	return postfix;
}
double cal( vector<string> s )
{	
	int size=s.size();
	for (int i=0;i<size;i++)
	{
		if (IsNumberic ( s[i] ))
		{	
			double x = atof( s[i].c_str() );
			val.push(x);
		};
		if (IsOperator ( s[i] ))
		{
			double x,y,z;
			y = val.pop();
			x = val.pop();

			switch(*s[i].c_str())
			{
			case '+':	z=x+y;break;
			case '-':	z=x-y;break;
			case '*':	z=x*y;break;
			case '/':	z=x/y;break;
			case '^':	z=pow(x,y);break;
			default:;
			}
			val.push ( z ) ;
		}
	};
	return val.pop();
};
void main()
{
	string str;
	
	cout << "Input your math:\n>";
	cin  >> str ;
	string h = re_format(str);
	string k = infix2postfix( split2token(h) );
	cout << "Infix form:\n" << h <<endl;
	cout << "Postfix form:\n" << k <<endl;
	cout << "Result:\n"<<cal(split2token(k))<<endl;

	cout<<endl;
	system("pause");
}