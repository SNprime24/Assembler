#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <set>
#include <cmath>
#include <fstream>
using namespace std;

class registerType{
    private:
        string OPCODE = "0110011";
        string operation,rd,rs1,rs2;
        unordered_map<string,string>func={
            {"ADD", "0000000 000"},
            {"SLL", "0000000 001"},
            {"SLT", "0000000 010"},
            {"SLTU","0000000 011"},
            {"XOR", "0000000 100"},
            {"SRL", "0000000 101"},
            {"OR",  "0000000 110"},
            {"AND", "0000000 111"},
            
            {"SUB", "0100000 000"},
            {"SRA", "0100000 101"},
        };
    
    public:
        registerType(string arg1, string arg2, string arg3, string arg4){
            operation = arg1;
            rd = arg2;
            rs1 = arg3;
            rs2 = arg4;
        }
        
        string binaryInstruction(){
            string bin = "";
            bin +=func[operation].substr(0,7);
            bin +=rs2;
            bin +=rs1;
            bin +=func[operation].substr(8,3);
            bin +=rd;
            bin +=OPCODE;
            return bin;
        }
};

class immediateType{
    private:
        string OPCODE = "0010011";
        string operation,rd,rs1,imm;
        unordered_map<string,string>defaultImmediate={
            {"SLLI", "0000000"},
            {"SRLI", "0000000"},
            {"SRAI", "0100000"},
        };
        unordered_map<string,string>func3={
            {"ADDI", "000"},
            {"SLTI", "010"},
            {"XORI", "100"},
            {"ORI",  "110"},
            {"ANDI", "111"},
            
            {"SLLI", "001"},
            {"SRLI", "101"},
            {"SRAI", "101"},
        };
    
    public:
        immediateType(string arg1, string arg2, string arg3, string arg4){
            operation = arg1;
            rd = arg2;
            rs1 = arg3;
            imm = arg4;
        }
        
        string binaryInstruction(){
            string bin = "";
            if(defaultImmediate.find(operation)!=defaultImmediate.end()) bin+=defaultImmediate[operation];
            bin +=imm;
            bin +=rs1;
            bin +=func3[operation];
            bin +=rd;
            bin +=OPCODE;
            return bin;
        }
};

class loadType{
    private:
        string OPCODE = "0000011";
        string operation,rd,rs1,imm;
        unordered_map<string,string>func3={
            {"LB", "000"},
            {"LH", "001"},
            {"LW", "010"},
            {"LD", "011"},
            {"LBU","100"},
            {"LHU","101"},
            {"LWU","110"},
        };
    
    public:
        loadType(string arg1, string arg2, string arg3, string arg4){
            operation = arg1;
            rd = arg2;
            rs1 = arg3;
            imm = arg4;
        }
        
        string binaryInstruction(){
            string bin = "";
            bin +=imm;
            bin +=rs1;
            bin +=func3[operation];
            bin +=rd;
            bin +=OPCODE;
            return bin;
        }
};

class storeType{
    private:
        string OPCODE = "0100011";
        string operation,rs1,rs2,imm;
        unordered_map<string,string>func3={
            {"SB", "000"},
            {"SH", "001"},
            {"SW", "010"},
            {"SD", "011"},
        };
    
    public:
        storeType(string arg1, string arg2, string arg3, string arg4){
            operation = arg1;
            rs1 = arg2;
            rs2 = arg3;
            imm = arg4;
        }
        
        string binaryInstruction(){
            string bin = "";
            bin +=imm.substr(0,7);
            bin +=rs2;
            bin +=rs1;
            bin +=func3[operation];
            bin +=imm.substr(7,5);
            bin +=OPCODE;
            return bin;
        }
};

class branchType{
    private:
        string OPCODE = "1100011";
        string operation,rs1,rs2,imm;
        unordered_map<string,string>func3={
            {"BEQ", "000"},
            {"BNE", "001"},
            {"BLT", "100"},
            {"BGE", "101"},
        };
    
    public:
        branchType(string arg1, string arg2, string arg3, string arg4){
            operation = arg1;
            rs1 = arg2;
            rs2 = arg3;
            imm = arg4;
        }
        
        string binaryInstruction(){
            string bin = "";
            bin +=imm.substr(0,1);
            bin +=imm.substr(2,6);
            bin +=rs2;
            bin +=rs1;
            bin +=func3[operation];
            bin +=imm.substr(8,4);
            bin +=imm.substr(1,1);
            bin +=OPCODE;
            return bin;
        }
};

class jumpType{
    private:
        string OPCODE = "1101111";
        string operation,rd,imm;
    
    public:
        jumpType(string arg1, string arg2, string arg3){
            operation = arg1;
            rd = arg2;
            imm = arg3;
        }
        
        string binaryInstruction(){
            string bin = "";
            bin +=imm.substr(0,1);
            bin +=imm.substr(10,10);
            bin +=imm.substr(9,1);
            bin +=imm.substr(1,8);
            bin +=rd;
            bin +=OPCODE;
            return bin;
        }
};

class upperImmediateType{
    private:
        string operation,rd,imm;
        unordered_map<string,string>OPCODE={
            {"LUI",  "0110111"},
            {"AUIPC","0010111"},
        };
    
    public:
        upperImmediateType(string arg1, string arg2, string arg3){
            operation = arg1;
            rd = arg2;
            imm = arg3;
        }
        
        string binaryInstruction(){
            string bin = "";
            bin +=imm;
            bin +=rd;
            bin +=OPCODE[operation];
            return bin;
        }
};


class convertor{
    private:
        string instruction;
        
        const int BINARY_REG_SIZE = 5;
        const int IMMEDIATE_SIZE = 12;
        const int U_IMMEDIATE_SIZE = 20;
        
        //DON;T TOUCH UNLESS NEEDED...
        const int LOWER_REG_LIMIT = 0;
        const int UPPER_REG_LIMIT = pow(2,BINARY_REG_SIZE)-1;
        
        const int LOWER_IMMEDIATE_LIMIT = -pow(2,IMMEDIATE_SIZE-1);
        const int UPPER_IMMEDIATE_LIMIT = pow(2,IMMEDIATE_SIZE-1)-1;
        
        const int LOWER_U_IMMEDIATE_LIMIT = -pow(2,U_IMMEDIATE_SIZE-1);
        const int UPPER_U_IMMEDIATE_LIMIT = pow(2,U_IMMEDIATE_SIZE-1)-1;
        
        unordered_map<string,int>labelLocation;
        int line = 0;
        int binaryLine = 0;
        
        set<string>rtypeOperands = {"ADD","SLT","SLTU","AND","OR","XOR","SLL","SRL","SUB","SRA"};
        set<string>itypeOperands = {"ADDI","SLTI","ANDI","ORI","XORI"};
        set<string>itype2Operands = {"SLLI","SRLI","SRAI"};
        set<string>loadtypeOperands = {"LW","LD","LH","LB","LWU","LHU","LBU"};
        set<string>storetypeOperands = {"SD","SW","SHW","SB"};
        set<string>btypeOperands = {"BEQ","BNE","BLT","BGE"};
        set<string>utypeOperands = {"LUI","AUIPC"};
        set<string>jtypeOperands = {"JAL"};
        
        vector<string> EXTRACT(){
            vector<string>parts;
            string opr = "";
            for(auto i:instruction){
                if(i!=' ' && i!=',' && i!='(' && i!=')' && i!=':') opr.insert(opr.end(),i);
                else{
                    if(opr!="") parts.push_back(opr);
                    opr="";
                }
            }
            if(opr!="") parts.push_back(opr);
            return parts;
        }
        
        int stringToNumber (string str){
            int num=0;
            for(auto i:str){
                if(i!='x' && i!='X'){
                    num = num*10+(i-'0');
                }
            }
            return num;
        }
        
        string numberToBinary(int num, int flag){
            if(flag==0){
                if(num>=LOWER_REG_LIMIT && num<=UPPER_REG_LIMIT){
                    int ind = BINARY_REG_SIZE-1;
                    string binaryRes(BINARY_REG_SIZE,'0');
                    while(num!=0){
                        binaryRes[ind--]='0'+num%2;
                        num/=2;
                    }
                    return binaryRes;
                }
                else{
                    cerr<<"ERROR : REGISTER VALUE OUT OF LIMIT";
                    exit(0);
                }
            }
            else{
                int SIZE = IMMEDIATE_SIZE;
                int LOWER_LIMIT = LOWER_IMMEDIATE_LIMIT;
                int UPPER_LIMIT = UPPER_IMMEDIATE_LIMIT;
                if(flag==2){
                    SIZE = U_IMMEDIATE_SIZE;
                    LOWER_LIMIT = LOWER_U_IMMEDIATE_LIMIT;
                    UPPER_LIMIT = UPPER_U_IMMEDIATE_LIMIT;
                }
                else if(flag==3){
                    SIZE = BINARY_REG_SIZE;
                    LOWER_LIMIT = LOWER_REG_LIMIT;
                    UPPER_LIMIT = UPPER_REG_LIMIT;
                }
                
                if(num>=LOWER_LIMIT && num<=UPPER_LIMIT){
                    int temp = abs(num);
                    int ind = SIZE-1;
                    string binaryimm(SIZE,'0');
                    while(temp!=0){
                        binaryimm[ind--]='0'+temp%2;
                        temp/=2;
                    }
                    if(num<0){
                        for(int i=0; i<SIZE; i++){
                            if(binaryimm[i]=='1') binaryimm[i]='0';
                            else binaryimm[i]='1';
                        }
                        for(int i=SIZE-1; i>=0; i--){
                            if(binaryimm[i]=='1') binaryimm[i]='0';
                            else{
                                binaryimm[i]='1';
                                break;
                            }
                        }
                    }
                    return binaryimm;
                }
                else{
                    cerr<<"ERROR : IMMEDIATE VALUE OUT OF LIMIT"<<endl;
                    exit(0);
                }
            }
            return "";
        }
        
        string operatorMapping(vector<string>opr){
            string operation = "";
            for(auto i:opr[0]) operation +=toupper(i);
            // cout<<line<<endl;
            
            if(rtypeOperands.find(operation)!=rtypeOperands.end()){
                if(opr.size()!=4){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rd  = numberToBinary(stringToNumber(opr[1]),0);
                string rs1 = numberToBinary(stringToNumber(opr[2]),0);
                string rs2 = numberToBinary(stringToNumber(opr[3]),0);
                registerType instr(operation, rd, rs1, rs2);
                return instr.binaryInstruction();
            }
            else if(itype2Operands.find(operation)!=itype2Operands.end()){
                if(opr.size()!=4){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rd  = numberToBinary(stringToNumber(opr[1]),0);
                string rs1 = numberToBinary(stringToNumber(opr[2]),0);
                string imm = numberToBinary(stringToNumber(opr[3]),3);
                immediateType instr(operation, rd, rs1, imm);
                return instr.binaryInstruction();
            }
            else if(itypeOperands.find(operation)!=itypeOperands.end()){
                if(opr.size()!=4){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rd  = numberToBinary(stringToNumber(opr[1]),0);
                string rs1 = numberToBinary(stringToNumber(opr[2]),0);
                string imm = numberToBinary(stringToNumber(opr[3]),1);
                immediateType instr(operation, rd, rs1, imm);
                return instr.binaryInstruction();
            }
            else if(loadtypeOperands.find(operation)!=loadtypeOperands.end()){
                if(opr.size()!=4){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rd  = numberToBinary(stringToNumber(opr[1]),0);
                string imm = numberToBinary(stringToNumber(opr[2]),1);
                string rs1 = numberToBinary(stringToNumber(opr[3]),0);
                loadType instr(operation, rd, rs1, imm);
                return instr.binaryInstruction();
            }
            else if(storetypeOperands.find(operation)!=storetypeOperands.end()){
                if(opr.size()!=4){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rs2 = numberToBinary(stringToNumber(opr[1]),0);
                string imm = numberToBinary(stringToNumber(opr[2]),1);
                string rs1 = numberToBinary(stringToNumber(opr[3]),0);
                storeType instr(operation, rs1, rs2, imm);
                return instr.binaryInstruction();
            }
            else if(btypeOperands.find(operation)!=btypeOperands.end()){
                if(opr.size()!=4){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rs1 = numberToBinary(stringToNumber(opr[1]),0);
                string rs2 = numberToBinary(stringToNumber(opr[2]),0);
                string imm = numberToBinary(labelLocation[opr[3]]-binaryLine,1);
                
                //immediate Hndling
                int offset = labelLocation[opr[3]]-binaryLine;
                cout<<"Offset -> "<<offset<<endl;
                if(offset<0) imm = "1"+imm.substr(0,imm.size()-1);
                else imm = "0"+imm.substr(0,imm.size()-1);
                
                branchType instr(operation, rs1, rs2, imm);
                return instr.binaryInstruction();
            }
            else if(utypeOperands.find(operation)!=utypeOperands.end()){
                if(opr.size()!=3){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rd = numberToBinary(stringToNumber(opr[1]),0);
                string imm = numberToBinary(stringToNumber(opr[2]),2);
                upperImmediateType instr(operation, rd, imm);
                return instr.binaryInstruction();
            }
            else if(jtypeOperands.find(operation)!=jtypeOperands.end()){
                if(opr.size()!=3){
                    cerr<<"INVALID INSTRUCTION"<<endl;
                    exit(0);
                }
                string rd = numberToBinary(stringToNumber(opr[1]),0);
                string imm = numberToBinary(labelLocation[opr[2]]-binaryLine,2);
                
                //immediate Hndling
                int offset = labelLocation[opr[2]]-binaryLine;
                cout<<"Offset -> "<<offset<<endl;
                if(offset<0) imm = "1"+imm.substr(0,imm.size()-1);
                else imm = "0"+imm.substr(0,imm.size()-1);
                
                jumpType instr(operation, rd, imm);
                return instr.binaryInstruction();
            }
            cerr<<"ERROR : OPERAND NOT FOUND OR INVALID INSTRUCTION"<<endl;
            exit(0);
        }
        
        string convert(){
            vector<string> dividedParts = EXTRACT();
            return operatorMapping(dividedParts);
        }
    public:   
        convertor(string str){      //constructor
            instruction = str;
        }  
        
        convertor(string str, int num, int binaryNum){
            instruction = str;
            line = num;
            binaryLine = binaryNum;
        }
        
        convertor(string inputfile, string outputfile){
            ifstream inputFile(inputfile);
            ofstream outputFile(outputfile);
            
            if(!inputFile || !outputFile){
                cerr<<"ERROR : FILE OPENING ERROR"<<endl;
                exit(0);
            }
            
            string codeLine;
            int binaryLineNumber = 0;
            while(getline(inputFile,codeLine)){
                instruction = codeLine;
                vector<string>label = EXTRACT();
                
                if(label.size()==1) labelLocation.insert({label[0],binaryLineNumber});
                if(label.size()!=0 && label.size()!=1) binaryLineNumber++;
            }
            
            inputFile.clear();
            inputFile.seekg(0,ios::beg);
            
            
            
            int lineNumber = 1;
            binaryLineNumber = 0;
            while(getline(inputFile,codeLine)){
                instruction = codeLine;
                line = lineNumber;
                binaryLine = binaryLineNumber;
                
                vector<string>label = EXTRACT();
                lineNumber++;
                if(label.size()==0 || label.size()==1) continue;
                
                string binInstruction = printConvertedString();
                outputFile<<binInstruction<<endl;
                
                binaryLineNumber++;
            }
            
            inputFile.close();
            outputFile.close();
            cout<<"SUCCESS : Assembly code successfully converted to binary file ..."<<endl;
        }
        
        string printConvertedString(){
            return convert();
        }
};

int main(){
    convertor assembler("input.asm","output.bin");
    
    // convertor assembly ("    JAL x12   -4");
    // cout<<assembly.printConvertedString()<<endl;
}