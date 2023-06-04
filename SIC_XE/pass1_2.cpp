#include <iostream>
#include <cstring>
#include <algorithm> 
#include "pass1_2.h"
#include "HashTable.cpp"
#include "function.cpp"
#define MAX_LINE_LENGTH 256
// ----------------------------------------
// const size_t : TableSize
// HashTable : OPTAB
// HashTable : SYMTAB
// string : file_length
// string : start_address
// ----------------------------------------
const size_t TableSize = 10;
HashTable<string, string, TableSize> OPTAB;
HashTable<string, string, TableSize> SYMTAB;
string file_length;
string start_address; 

void pass1()
{
	// ----------------------------------------
	// build OPTAB
	// ----------------------------------------
	OPTAB_build(OPTAB);
	// ----------------------------------------
	// build register for SYMTAB
	// ----------------------------------------
	SYMTAB.insert("A","0");
	SYMTAB.insert("X","1");
	SYMTAB.insert("L","2");
	SYMTAB.insert("B","3");
	SYMTAB.insert("S","4");
	SYMTAB.insert("T","5");
	SYMTAB.insert("F","6");
	SYMTAB.insert("PC","8");
	SYMTAB.insert("SW","9");
	// ----------------------------------------
	// line array is used to store input a line from file 
	// ---------------------------------------- 
    char line[MAX_LINE_LENGTH];
    // ----------------------------------------
    // Open the file in read mode
    // read source.txt file
    // ----------------------------------------
    FILE* input = fopen("source.txt", "r");
    // ----------------------------------------
    // write intermediate.txt file
    // ----------------------------------------
    FILE* intermediate = fopen("intermediate.txt", "w");
    // ----------------------------------------
    // check if input and intermediate file are opened
    // ----------------------------------------
    if (input == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    if (intermediate == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    // ----------------------------------------
	// string : str
	// string : tmp
	// string : lables
	// string : mnemonic_operation_code;
	// string : symbolic_operands;
	// string : symbolic_operands1;
	// string : symbolic_operands2;
	// int : index
	// string : lOCCTR 
	// ----------------------------------------
	string str;
	string tmp = "";
	string lables;
	string mnemonic_operation_code;
	string symbolic_operands;
	string symbolic_operands1;
	string symbolic_operands2;
	string LOCCTR = "";
	// ----------------------------------------
	// get first line
	// ----------------------------------------
	fgets(line, sizeof(line), input);
	// ----------------------------------------
	// Remove the newline character from the line, if present
	// ----------------------------------------
    line[strcspn(line, "\n")] = '\0';
	// ----------------------------------------
	// string : lineStr
    // store the line in a string
    // ----------------------------------------
    string lineStr(line);
    // ----------------------------------------
    // get mnemonic_operation_code
    // ----------------------------------------
	mnemonic_operation_code = "";
	int i;
	// ----------------------------------------
	// check if exist a tab then no any lable 
	// ----------------------------------------
	if(lineStr[0] == '\t')
	{
		// ----------------------------------------
		// get mnemonic_operation_code
		// ----------------------------------------
		mnemonic_operation_code = "";
		for(i = 1 ; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				mnemonic_operation_code+= lineStr[i];
		}
	}
	else
	{
		// ----------------------------------------
		// get lables
		// ----------------------------------------
		lables = "";
		for(i = 0 ; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				lables+= lineStr[i];
		}
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		i++;
		// ----------------------------------------
		// get mnemonic_operation_code
		// ----------------------------------------
		mnemonic_operation_code = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				mnemonic_operation_code += lineStr[i];
		}
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		i++;
	}
	// ----------------------------------------
	// check if mnemonic_operation_code is "START"
	// ----------------------------------------
	if(mnemonic_operation_code == "START")
	{
		// ----------------------------------------
		// get symbolic_operands in first line
		// ----------------------------------------
		symbolic_operands = "";
		for(; i < lineStr.length() ; i++)
		{
			symbolic_operands += lineStr[i];
		}
		// ----------------------------------------
		// store symbolic_operands to LOCCOR and start_address
		// ----------------------------------------
		start_address = LOCCTR = symbolic_operands;
		// ----------------------------------------
		// write a line to intermediate file
		// ----------------------------------------
		fprintf(intermediate,"%04X\t%s\n", hexStringToInteger(LOCCTR),lineStr.c_str());
	}
	else
	{
		// ----------------------------------------
		// store "0" to LOCCOR and start_address
		// ----------------------------------------
		start_address = LOCCTR = "0000";
		// ----------------------------------------
		// write a line to intermediate file
		// ----------------------------------------
		fprintf(intermediate, (LOCCTR + "\t" + lineStr + "\n").c_str());
	}
	// ----------------------------------------
	// Read the input line by line
	// ----------------------------------------
    while (fgets(line, sizeof(line), input) != NULL) {
    	// ----------------------------------------
		// Remove the newline character from the line, if present
		// ----------------------------------------
		line[strcspn(line, "\n")] = '\0';
		// ----------------------------------------
		// string : lineStr
		// store the line in a string
		// ----------------------------------------
		lineStr;
		lineStr.assign(line);
		if(lineStr[0] == '\t')
		{
			// ----------------------------------------
			// store lables to "" because of no lables in a lineStr
			// ----------------------------------------
			lables = "";
			// ----------------------------------------
			// get mnemonic_operation_code
			// ----------------------------------------
			mnemonic_operation_code = "";
			for(i = 1 ; i < lineStr.length() ; i++)
			{
				// ----------------------------------------
				// stop when encounter \t
				// ----------------------------------------
				if(lineStr[i] == '\t')
					break;
				else
					mnemonic_operation_code+= lineStr[i];
			}
			// ----------------------------------------
			//  skip \t
			// ----------------------------------------
			i++;
		}
		else
		{
			// ----------------------------------------
			// get lables
			// ----------------------------------------
			lables = "";
			for(i = 0 ; i < lineStr.length() ; i++)
			{
				// ----------------------------------------
				// stop when encounter \t
				// ----------------------------------------
				if(lineStr[i] == '\t')
					break;
				else
					lables+= lineStr[i];
			}
			// ----------------------------------------
			//  skip \t
			// ----------------------------------------
			i++;
			// ----------------------------------------
			// get mnemonic_operation_code
			// ----------------------------------------
			mnemonic_operation_code = "";
			for(; i < lineStr.length() ; i++)
			{
				// ----------------------------------------
				// stop when encounter \t
				// ----------------------------------------
				if(lineStr[i] == '\t')
					break;
				else
					mnemonic_operation_code+= lineStr[i];
			}
			// ----------------------------------------
			//  skip \t
			// ----------------------------------------
			i++;
		}
		// ----------------------------------------
		// check if mnemonic_operation_code is "END"
		// ----------------------------------------
		if(mnemonic_operation_code == "END")
		{
			break;
		}
		// ----------------------------------------
		// get symbolic_operands1
		// ----------------------------------------
		symbolic_operands1 = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter ','
			// ----------------------------------------
			if(lineStr[i] == ',')
				break;
			else
			symbolic_operands1 += lineStr[i];
		}
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		i++;
		// ----------------------------------------
		// get symbolic_operands2
		// ----------------------------------------
		symbolic_operands2 = "";
		for(; i < lineStr.length() ; i++)
		{
			symbolic_operands2 += lineStr[i];
		}
		// ----------------------------------------
		// chectk if mnemonic_operation_code is "BASE"
		// ----------------------------------------
		if(mnemonic_operation_code == "BASE")
		{
			fprintf(intermediate,"\t%s\n", lineStr.c_str());
			continue;
		}
		// ----------------------------------------
		// chectk if lables is exist in a line
		// ----------------------------------------
		if(lables != "")
		{
			// ----------------------------------------
			// get address of symbolic_operands 
			// check if SYMTAB have lables
			// if True then store "error" to lables
			// if False then insert into SYMTAB
			// ----------------------------------------
			string address;
			if(SYMTAB.search(lables,address))
			{
				lables = "error";
			}
			else
			{
				SYMTAB.insert(lables,LOCCTR);
				printf("%04X %s\n",hexStringToInteger(LOCCTR),lables.c_str());
			}
		}
		string opcode;
		// ----------------------------------------
		// check whether is format4 or not
		// ----------------------------------------
		if(mnemonic_operation_code[0] == '+')
		{
			mnemonic_operation_code = mnemonic_operation_code.substr(1);
			fprintf(intermediate,"%04X\t%s\n", hexStringToInteger(LOCCTR),lineStr.c_str());
			if(OPTAB.search(mnemonic_operation_code,opcode))
			{
				LOCCTR = stringAddition(LOCCTR,"4");
			}
		}
		else
		{
			fprintf(intermediate,"%04X\t%s\n", hexStringToInteger(LOCCTR),lineStr.c_str());
			// ----------------------------------------
			// check whether is format1 or not
			// ----------------------------------------
			if(mnemonic_operation_code == "FIX" || mnemonic_operation_code == "FLOAT" || mnemonic_operation_code == "HIO" || mnemonic_operation_code == "NORM" || mnemonic_operation_code == "SIO" || mnemonic_operation_code == "TIO")
			{				LOCCTR = stringAddition(LOCCTR,"1");
			}
			// ----------------------------------------
			// check whether is format2 or not
			// ----------------------------------------
			else if(mnemonic_operation_code == "ADDR" || mnemonic_operation_code == "CLEAR" || mnemonic_operation_code == "COMPR" || mnemonic_operation_code == "DIVR" || mnemonic_operation_code == "MULR" || mnemonic_operation_code == "RMO" || mnemonic_operation_code == "SHIFTL" || mnemonic_operation_code == "SHIFTR" || mnemonic_operation_code == "SUBR" || mnemonic_operation_code == "TIXR")
			{
				if(mnemonic_operation_code == "ADDR" || mnemonic_operation_code == "COMPR" || mnemonic_operation_code == "DIVR" || mnemonic_operation_code == "MULR" || mnemonic_operation_code == "RMO" || mnemonic_operation_code == "SHIFTL" || mnemonic_operation_code == "SHIFTR" || mnemonic_operation_code == "SUBR")
				{
					LOCCTR = stringAddition(LOCCTR,"2");
				}
				else
				{
					LOCCTR = stringAddition(LOCCTR,"2");
				}		
			}
			// ----------------------------------------
			// is format3
			// ----------------------------------------
			// ----------------------------------------
			// check if mnemonic_operation_code is in OPTAB
			// ----------------------------------------
			else if(OPTAB.search(mnemonic_operation_code,opcode))
			{
				LOCCTR = stringAddition(LOCCTR,"3");
			}
			// ----------------------------------------
			// check if mnemonic_operation_code is "WORD"
			// ----------------------------------------
			else if (mnemonic_operation_code == "WORD")
			{
				LOCCTR = stringAddition(LOCCTR,"3");
			}
			// ----------------------------------------
			// check if mnemonic_operation_code is "RESW"
			// ----------------------------------------
			else if (mnemonic_operation_code == "RESW")
			{
				LOCCTR = stringAddition(LOCCTR,intToString(3 * hexStringToInteger(symbolic_operands1)));	
			}
			// ----------------------------------------
			// check if mnemonic_operation_code is "RESB"
			// ----------------------------------------
			else if (mnemonic_operation_code == "RESB")
			{
				LOCCTR = stringAddition(LOCCTR,decimalToHexString(symbolic_operands1));		
			}
			// ----------------------------------------
			// check if mnemonic_operation_code is "BYTE"
			// ----------------------------------------
			else if (mnemonic_operation_code == "BYTE")
			{
				// ----------------------------------------
				// check if symbolic_operands is like C'EOF'
				// ----------------------------------------
				if(symbolic_operands1[0] == 'C' && symbolic_operands1[1] == '\'')
				{
					symbolic_operands1= removeQuotes(symbolic_operands1);
					LOCCTR = stringAddition(LOCCTR,intToString(symbolic_operands1.length()));	
				}
				// ----------------------------------------
				// check if symbolic_operands is like X'1A'
				// ----------------------------------------
				else if (symbolic_operands1[0] == 'X' && symbolic_operands1[1] == '\'')
				{
					symbolic_operands1 = removeQuotes(symbolic_operands1);
					LOCCTR = stringAddition(LOCCTR,intToString(symbolic_operands1.length()/2));
				}
				// ----------------------------------------
				// symbolic_operands is like 1000
				// ----------------------------------------
				else
					LOCCTR = stringAddition(LOCCTR,decimalToHexString(symbolic_operands1));	
			}
		}
		
		
		
    }
	// ----------------------------------------
	// get symbolic_operands in last line
	// ----------------------------------------
    symbolic_operands1 = "";
	for(; i < lineStr.length() ; i++)
	{
		symbolic_operands1 += lineStr[i];
	}
	// ----------------------------------------
	// write a last line to intermediate file
	// ----------------------------------------
    fprintf(intermediate, ("\t" + lineStr).c_str());
    // ----------------------------------------
	// store file length from (LOCCTR - start_address) for pass2
	// ----------------------------------------
	file_length = decimalToHexString(intToString(hexStringToInteger(LOCCTR) - hexStringToInteger(start_address)));
	// ----------------------------------------
	// close input file and close intermediate file
	// ----------------------------------------
	fclose(input);	
	fclose(intermediate);
}
void pass2()
{
	// ----------------------------------------
	// line array is used to store input a line from file 
	// ---------------------------------------- 
    char line[MAX_LINE_LENGTH];
	// ----------------------------------------
    // Open the file in read mode
    // read intermediate.txt file
    // ----------------------------------------
    FILE* intermediate = fopen("intermediate.txt", "r");
	// ----------------------------------------
    // Open the file in write mode
    // read object.txt file
    // ----------------------------------------
    FILE* object_file = fopen("object.txt", "w");
	// ----------------------------------------
    // check if input and intermediate file are opened
    // ----------------------------------------
    if (intermediate == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    if (object_file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }
	// ----------------------------------------
	// string : str
	// string : tmp
	// string : lables
	// string : mnemonic_operation_code;
	// string : symbolic_operands;
	// string : symbolic_operands1;
	// string : symbolic_operands2;
	// int : index
	// string : lOCCTR 
	// ----------------------------------------
	string str;
	string tmp = "";
	string lables;
	string mnemonic_operation_code;
	string symbolic_operands;
	string symbolic_operands1;
	string symbolic_operands2;
	string data_constants;
	string LOCCTR = "";
	// ----------------------------------------
	// get first line
	// ----------------------------------------
	fgets(line, sizeof(line), intermediate);
	// ----------------------------------------
	// Remove the newline character from the line, if present
	// ----------------------------------------
    line[strcspn(line, "\n")] = '\0';
	// ----------------------------------------
	// string : lineStr
    // store the line in a string
    // ----------------------------------------
    string lineStr(line);
    // ----------------------------------------
    // get mnemonic_operation_code
    // ----------------------------------------
	mnemonic_operation_code = "";
	// ----------------------------------------
	// the index of lineStr string
	// ----------------------------------------
	int i;
	// ----------------------------------------
	// get LOCCTR in first line
	// ----------------------------------------
	LOCCTR = "";
	for(i = 0 ; i < lineStr.length() ; i++)
	{
		// ----------------------------------------
		// stop when encounter \t
		// ----------------------------------------
		if(lineStr[i] == '\t')
			break;
		else
			LOCCTR += lineStr[i];
	}
	// ----------------------------------------
	//  skip \t
	// ----------------------------------------
	i++;
	// ----------------------------------------
	// check if exist a tab then no any lable 
	// ----------------------------------------
	if(lineStr[i] == '\t')
	{
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		i++;
		// ----------------------------------------
		// get mnemonic_operation_code in first line
		// ----------------------------------------
		mnemonic_operation_code = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				mnemonic_operation_code+= lineStr[i];
		}
	}
	else
	{
		// ----------------------------------------
		// get lables in first line
		// ----------------------------------------
		lables = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				lables+= lineStr[i];
		}
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		while(lineStr[i] == '\t')
			i++;
		// ----------------------------------------
		// get mnemonic_operation_code in first line
		// ----------------------------------------
		mnemonic_operation_code = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				mnemonic_operation_code+= lineStr[i];
		}
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		while(lineStr[i] == '\t')
			i++;
	}
	// ----------------------------------------
	// check if mnemonic_operation_code is "START"
	// ----------------------------------------
	if(mnemonic_operation_code == "START")
	{
		// ----------------------------------------
		// store start_address to LOCCOR
		// ----------------------------------------
		LOCCTR = start_address;
		// ----------------------------------------
		// store append "0" to LOCCOR until length is 6
		// ----------------------------------------
		while(LOCCTR.length() < 6)
			LOCCTR = "0" + LOCCTR;
		// ----------------------------------------
		// store append "0" to file_length until length is 6
		// ----------------------------------------
		while(file_length.length() < 6)
			file_length = "0" + file_length;
		// ----------------------------------------
		// write a line to object_file file
		// ----------------------------------------
		fprintf(object_file,"%1s%-6s%6s%6s\n", "H", lables.c_str(), LOCCTR.c_str(), file_length.c_str());
	}
	// ----------------------------------------
	// Read the intermediate line by line
	// int : textlength
	// string : all_object
	// string : all_modification = "";
	// string : Indirect;
	// string : Immediate;
	// string : IsX;
	// string : Base;
	// string : IsB;
	// string : Program_Counter;
    // string : IsP;
	// ----------------------------------------
	int textlength = 0;
	string all_object = "";
	string all_modification = "";
	string Indirect;
	string Immediate;
	string IsX;
	string Base;
	string IsB;
	string Program_Counter;
    string IsP;
	while (fgets(line, sizeof(line), intermediate) != NULL) {
        // ----------------------------------------
		// Remove the newline character from the line, if present
		// ----------------------------------------
		line[strcspn(line, "\n")] = '\0';
		// ----------------------------------------
		// string : lineStr
		// store the line in a string
		// ----------------------------------------
        lineStr;
		lineStr.assign(line);
		// ----------------------------------------
		// get mnemonic_operation_code
		// ----------------------------------------
		LOCCTR = "";
		for(i = 0 ; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter \t
			// ----------------------------------------
			if(lineStr[i] == '\t')
				break;
			else
				LOCCTR += lineStr[i];
		}
		// ----------------------------------------
		//  skip \t
		// ----------------------------------------
		i++;
		if(lineStr[i] == '\t')
		{
			// ----------------------------------------
			//  skip \t
			// ----------------------------------------
			i++;
			lables = "";
			// ----------------------------------------
			// get mnemonic_operation_code
			// ----------------------------------------
			mnemonic_operation_code = "";
			for( ; i < lineStr.length() ; i++)
			{
				// ----------------------------------------
				// stop when encounter \t
				// ----------------------------------------
				if(lineStr[i] == '\t')
					break;
				else
					mnemonic_operation_code+= lineStr[i];
			}
			// ----------------------------------------
			//  skip \t
			// ----------------------------------------
			i++;
		}
		else
		{
			// ----------------------------------------
			// get lables
			// ----------------------------------------
			lables = "";
			for( ; i < lineStr.length() ; i++)
			{
				// ----------------------------------------
				// stop when encounter \t
				// ----------------------------------------
				if(lineStr[i] == '\t')
					break;
				else
					lables+= lineStr[i];
			}
			i++;
			// ----------------------------------------
			// get mnemonic_operation_code
			// ----------------------------------------
			mnemonic_operation_code = "";
			for(; i < lineStr.length() ; i++)
			{
				// ----------------------------------------
				// stop when encounter \t
				// ----------------------------------------
				if(lineStr[i] == '\t')
					break;
				else
					mnemonic_operation_code+= lineStr[i];
			}
			i++;
		}
		if(mnemonic_operation_code == "END")
		{
			break;
		}
		symbolic_operands1 = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter ','
			// ----------------------------------------
			if(lineStr[i] == ',')
				break;
			else
			symbolic_operands1 += lineStr[i];
		}
		i++;
		symbolic_operands2 = "";
		for(; i < lineStr.length() ; i++)
		{
			symbolic_operands2 += lineStr[i];
		}
		if(mnemonic_operation_code == "BASE")
		{
			SYMTAB.search(symbolic_operands1,Base);
			continue;
		}
		else if (mnemonic_operation_code == "NOBASE")
		{
			Base = "";
			continue;
		}
		// ----------------------------------------
		// check whether is format4 or not
		// ----------------------------------------
		string opcode = "";
		string operands = "";
		string object = "";
		if(mnemonic_operation_code[0] == '+')
		{
			mnemonic_operation_code = mnemonic_operation_code.substr(1);
			if(OPTAB.search(mnemonic_operation_code,opcode))
			{
				// ----------------------------------------
				// check if symbolic_operands1 is not empty
				// ----------------------------------------
				if(symbolic_operands1 != "")
				{
					// ----------------------------------------
					// check if address mode is Indirect
					// ----------------------------------------
					if(symbolic_operands1[0] == '@')
					{
						Indirect = "1";
						symbolic_operands1 = symbolic_operands1.substr(1);
					}
					else
					{
						Indirect = "0";
					}
					// ----------------------------------------
					// check if address mode is Immediate
					// ----------------------------------------
					if (symbolic_operands1[0] == '#')
					{
						Immediate = "1";
						symbolic_operands1 = symbolic_operands1.substr(1);
					}
					else
					{
						Immediate = "0";
					}
					// ----------------------------------------
					// check if address mode is simple
					// ----------------------------------------
					if(Indirect == "0" && Immediate == "0")
					{
						Indirect = Immediate = "1"; 
					}
					// ----------------------------------------
					// check if address mode is X
					// ----------------------------------------
					if (symbolic_operands2[0] == 'X')
					{
						IsX = "1";
					}
					else
					{
						IsX = "0";
					}
					// ----------------------------------------
					// check if symbolic_operands is in SYMTAB
					// and store address of it to operands string variable
					// ----------------------------------------
					if(SYMTAB.search(symbolic_operands1,operands))
					{
						string tmp = stringAddition(LOCCTR,"1");
						while(tmp.length() < 6)
						{
							tmp = "0" + tmp;
						}
						all_modification = all_modification + "M" + tmp + "05\n";
					}
					// ----------------------------------------
					// symbolic_operands is not in SYMTAB
					// ----------------------------------------
					else
					{
						operands = decimalToHexString(symbolic_operands1);
					}
					
				}
				// ----------------------------------------
				// symbolic_operands1 is empty
				// ----------------------------------------
				else
				{
					operands = "00000";
				}
				// ----------------------------------------
				// tranlate it to object code
				// ----------------------------------------
				string xbpe = decimalToHexString(intToString((IsX[0] - 48) * 8 + 1)) ;
				string opcodeni = stringAddition(opcode,(decimalToHexString(intToString(hexStringToInteger(Indirect) * 2 + hexStringToInteger(Immediate)))));
				while (opcodeni.length() < 2)
				{
					opcodeni = "0" + opcodeni;
				}
				while (operands.length() < 5)
				{
					operands = "0" + operands;
				}
				object = opcodeni + xbpe + operands;
				
			}
		}
		else
		{
			// ----------------------------------------
			// check whether is format1 or not
			// ----------------------------------------
			if(mnemonic_operation_code == "FIX" || mnemonic_operation_code == "FLOAT" || mnemonic_operation_code == "HIO" || mnemonic_operation_code == "NORM" || mnemonic_operation_code == "SIO" || mnemonic_operation_code == "TIO")
			{
				OPTAB.search(mnemonic_operation_code,opcode);
				object = opcode;
			}
			// ----------------------------------------
			// check whether is format2 or not
			// ----------------------------------------
			else if(mnemonic_operation_code == "ADDR" || mnemonic_operation_code == "CLEAR" || mnemonic_operation_code == "COMPR" || mnemonic_operation_code == "DIVR" || mnemonic_operation_code == "MULR" || mnemonic_operation_code == "RMO" || mnemonic_operation_code == "SHIFTL" || mnemonic_operation_code == "SHIFTR" || mnemonic_operation_code == "SUBR" || mnemonic_operation_code == "TIXR")
			{
				if(mnemonic_operation_code == "ADDR" || mnemonic_operation_code == "COMPR" || mnemonic_operation_code == "DIVR" || mnemonic_operation_code == "MULR" || mnemonic_operation_code == "RMO" || mnemonic_operation_code == "SHIFTL" || mnemonic_operation_code == "SHIFTR" || mnemonic_operation_code == "SUBR")
				{
					OPTAB.search(mnemonic_operation_code,opcode);
					SYMTAB.search(symbolic_operands1,operands);
					object = opcode + operands;
					SYMTAB.search(symbolic_operands2,operands);
					object = object + operands;
				}
				else
				{
					OPTAB.search(mnemonic_operation_code,opcode);
					SYMTAB.search(symbolic_operands1,operands);
					object = opcode + operands + "0";
				}		
			}
			// ----------------------------------------
			// check whether is format1 or not
			// ----------------------------------------
			else if(OPTAB.search(mnemonic_operation_code,opcode))
			{
				// ----------------------------------------
				// check if symbolic_operands1 is not empty
				// ----------------------------------------
				if(symbolic_operands1 != "")
				{
					// ----------------------------------------
					// check if address mode is Indirect
					// ----------------------------------------
					if(symbolic_operands1[0] == '@')
					{
						Indirect = "1";
						symbolic_operands1 = symbolic_operands1.substr(1);
					}
					else
					{
						Indirect = "0";
					}
					// ----------------------------------------
					// check if address mode is Immediate
					// ----------------------------------------
					if (symbolic_operands1[0] == '#')
					{
						Immediate = "1";
						symbolic_operands1 = symbolic_operands1.substr(1);
					}
					else
					{
						Immediate = "0";
					}
					// ----------------------------------------
					// check if address mode is simple
					// ----------------------------------------
					if(Indirect == "0" && Immediate == "0")
					{
						Indirect = Immediate = "1"; 
					}
					// ----------------------------------------
					// check if address mode is X
					// ----------------------------------------
					if (symbolic_operands2[0] == 'X')
					{
						IsX = "1";
					}
					else
					{
						IsX = "0";
					}
					// ----------------------------------------
					// check if symbolic_operands is in SYMTAB
					// and store address of it to operands string variable
					// ----------------------------------------
					if(SYMTAB.search(symbolic_operands1,operands))
					{
						int ret = hexStringToInteger(operands) - hexStringToInteger(stringAddition(LOCCTR,"3"));
						
						if(ret >= -2048 && ret <= 2047)
						{
							if(ret < 0)
							{
								ret = 0xFFF + ret + 1; 
							}
							operands = decimalToHexString(intToString(ret));
							IsP = "1";
							IsB = "0";
						}
						else if(Base != "")
						{
							ret = hexStringToInteger(operands) - hexStringToInteger(Base);
							if(ret >= 0 && ret <= 4095)
							{
								if(ret < 0)
								{
									ret = 0xFFF + ret + 1; 
								}
								
								operands = decimalToHexString(intToString(ret));
								IsP = "0";
								IsB = "1";
							}
							else
							{
								operands = "err"; // error for relative address
								IsP = "0";
								IsB = "0";
							}
						}
					}
					// ----------------------------------------
					// symbolic_operands is not in SYMTAB
					// ----------------------------------------
					else
					{
						operands = decimalToHexString(symbolic_operands1);
						while(operands.length() < 3)
						{
							operands = "0" + operands;
						}
						IsP = "0";
						IsB = "0";
					}
					
				}
				// ----------------------------------------
				// symbolic_operands1 is empty
				// ----------------------------------------
				else
				{
					IsP = "0";
					IsB = "0";
					operands = "000";
				}
				// ----------------------------------------
				// tranlate it to object code
				// ----------------------------------------
				string xbpe = decimalToHexString(intToString((IsX[0] - 48) * 8 + (IsB[0] - 48) * 4 + (IsP[0] - 48) * 2));
				string opcodeni = stringAddition(opcode,(decimalToHexString(intToString(hexStringToInteger(Indirect) * 2 + hexStringToInteger(Immediate)))));
				while (opcodeni.length() < 2)
				{
					opcodeni = "0" + opcodeni;
				}
				object = opcodeni + xbpe + operands;
				while (operands.length() < 3)
				{
					operands = "0" + operands;
				}
				object = opcodeni + xbpe + operands;
			}
			else if (mnemonic_operation_code == "BYTE" || mnemonic_operation_code == "WORD")
			{
				// ----------------------------------------
				// check if symbolic_operands is like C'EOF'
				// ----------------------------------------
				if(symbolic_operands1[0] == 'C' && symbolic_operands1[1] == '\'')
				{
					symbolic_operands1= removeQuotes(symbolic_operands1);
					for (i = 0 ; i < symbolic_operands1.length() ; i++)
						object += decimalToHexString(intToString(symbolic_operands1[i]));
				}
				// ----------------------------------------
				// check if symbolic_operands is like X'1A'
				// ----------------------------------------
				else if (symbolic_operands1[0] == 'X' && symbolic_operands1[1] == '\'')
				{
					symbolic_operands1 = removeQuotes(symbolic_operands1);
					object = symbolic_operands1;
				}
				else
				{
					// ----------------------------------------
					// if mnemonic_operation_code is BYTE
					// ----------------------------------------
					if(mnemonic_operation_code == "BYTE")
						object = decimalToHexString(symbolic_operands1);
					// ----------------------------------------
					// if mnemonic_operation_code is WORD
					// ----------------------------------------
					else
						object = decimalToHexString(symbolic_operands1);
					// ----------------------------------------
					// if length of object code is less than 6 then append "0" to object code
					// ----------------------------------------
					while(object.length() < 6)
					{
						object = "0" + object;
					}
				}
			}
		}
		if(textlength == 0)
		{
			// ----------------------------------------
			// append a object code to unfinished Text Record line
			// ----------------------------------------
			all_object += object;
			// ----------------------------------------
			// append "0" to a address of first object code in one line to unfinished Text Record line
			// ----------------------------------------
			while(LOCCTR.length() < 6)
				LOCCTR = "0" + LOCCTR;
			// ----------------------------------------
			// write "T" and address of Text Record line to object_file file
			// ----------------------------------------
			fprintf(object_file, ("T" + LOCCTR).c_str());
		}
		else
		{
			// ----------------------------------------
			// append a object code to unfinished Text Record line
			// ----------------------------------------
			all_object += object;
		}
		// ----------------------------------------
		// increase for every object code
		// ----------------------------------------
		textlength++;
		// ----------------------------------------
		// write a Text Record object code to object_file file when have ten object code
		// ----------------------------------------
		if(textlength == 10)
		{
			// ----------------------------------------
			// write a length of Text Record header line to object_file file
			// ----------------------------------------
			string all_object_length = decimalToHexString(intToString(all_object.length()/2));
			if(all_object_length.length() == 1)
				all_object_length = "0" + all_object_length;
			// ----------------------------------------
			// write length of all_object and all_object of Text Record to object_file file
			// ----------------------------------------
			fprintf(object_file, (all_object_length + all_object + "\n").c_str());
			// ----------------------------------------
			// reset length and object code
			// ----------------------------------------
			textlength = 0;
			all_object = "";
		}
    }
	// ----------------------------------------
	// write a last Text Record object code to object_file file when length is not equal to 0
	// ----------------------------------------
    if(textlength != 0)
    {
		// ----------------------------------------
		// write a length of Text Record header line to object_file file
		// ----------------------------------------
    	string all_object_length = decimalToHexString(intToString(all_object.length()/2));
		if(all_object_length.length() == 1)
			all_object_length = "0" + all_object_length;
		// ----------------------------------------
		// write length of all_object and all_object of Text Record to object_file file
		// ----------------------------------------
    	fprintf(object_file, (all_object_length + all_object + "\n").c_str());
	}
	// ----------------------------------------
	// write a Modification Record to object_file file
	// ----------------------------------------
	fprintf(object_file, (all_modification).c_str());
	// ----------------------------------------
	// append "0" to start_address when length of start_address is less than 6
	// write a END Record to object_file file
	// ----------------------------------------
	while(start_address.length() < 6)
		start_address = "0" + start_address;
    fprintf(object_file, ("E" + start_address).c_str());
	// ----------------------------------------
	// close intermediate file and close object_file file
	// ----------------------------------------
	fclose(intermediate);	
	fclose(object_file);
}
