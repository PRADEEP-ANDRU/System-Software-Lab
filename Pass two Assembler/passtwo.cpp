/*
**************************
@Author: Vishal P
@Lab: System Software Lab
Code of Niranjan-Ananth
**************************
Note: Incase of error in lab execute : $ g++ --std=c++11 Absolute_loader.cpp
*/


#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

int main(){
    ifstream input("input.txt");
    ofstream out("output.txt");
    ifstream sym("symtab.txt");
    ifstream optab("optab.txt");
    string address, label, opcode, operand, code, value;
    int addr;
    input >> label >> opcode >> operand;
   cout<<label<<" "<<opcode<<" "<<operand<<endl;
    out << label << " " << opcode << " " << operand << endl;
    input >> address >> label >> opcode >> operand;
    while(opcode!="END"){
        out << address << " " << label << " " << opcode << " " << operand << " ";
        if(opcode!="RESB" && opcode!="RESW" && opcode!="BYTE" && opcode!="WORD"){
            optab.clear();
            optab.seekg(0, ios::beg);
            optab >> code >> value;
            while(code != "END"){
                if(code == opcode){
                    out<< value;
                    break;
                }
                optab >> code >> value;
            }

            sym.clear();
            sym.seekg(0, ios::beg);
            sym >> code >> value;
	    if(operand[operand.size()-1]=='X'  && operand[operand.size()-2]==','){
		while(code!="END"){
		if(code== operand.substr(0,operand.find(","))){
			string x(1,value[0]);
			int ad;
			ad=stoi(x,nullptr,16);		
			out<<hex<<ad+8<<value[1]<<value[2]<<value[3];		
		}
		sym>>code>>value;
		}

	}
	else{
            while(code != "END"){
                if(code == operand){
                    out << value;
                    break;
                }
                sym >> code >> value;
            }
	}
        }
        if(opcode=="BYTE"){
            for(int i=2; i<operand.length()-1; i++){
                out << hex << (int)operand[i];
            }
        }

        if(opcode=="WORD"){
            int a = stoi(operand, nullptr, 16);
            out << setfill('0') << setw(6) <<a;
        }
        out<<endl;
        input >> address >> label >> opcode >> operand;
    }
    return 0;
}
