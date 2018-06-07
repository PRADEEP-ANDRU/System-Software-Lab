#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>

using namespace std;

struct deftab{
	string lab;
	string opc;
	string oper;
}d[10];

int main(){
	int lines=0,i;
	ifstream input("input_wopara.txt");
	ofstream output("output_wopara.txt");
	ofstream def("deftab.txt");
	ofstream arg("argtab.txt");
	string args[3];
	vector<string> v;
	map<string,string> m;
	int para=1;
	string label,opcode,operand,macroname;
	
	input>>label>>opcode>>operand;
	while(opcode !="END"){
		if(opcode=="MACRO"){
			if(operand=="-") {
			para=0;
			}
			macroname=label;

			if(para==1)
			{
			string token;
			istringstream ss(operand);
			while(getline(ss,token,','))
			{
			v.push_back(token);
				}
			}
			input>>label>>opcode>>operand;
			while(opcode!="MEND"){
				def<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
				
				d[lines].lab=label;
				d[lines].opc=opcode;
				d[lines].oper=operand;
				
				lines++;
				input>>label>>opcode>>operand;
			}
		}
		else if(opcode==macroname)
{
			if(para==1)
	    {
			string token;
			istringstream ss(operand);
			i=0;
		while(getline(ss,token,','))
			{
			m[v.at(i)]=token;
			arg<<token<<endl;
			i++;	
			}
		for(i=0;i<lines;i++)
		{
		output<<d[i].lab<<"\t"<<d[i].opc<<"\t"<<m[d[i].oper]<<endl;
		}	
	   }
	else
	{
		for(i=0;i<lines;i++)
		{
		output<<d[i].lab<<"\t"<<d[i].opc<<"\t"<<d[i].oper<<endl;
		}
	}

}
		else{
			output<<label<<"\t"<<opcode<<"\t"<<operand<<endl;
		}
		
		input>>label>>opcode>>operand;
	}
	return 0;
}

