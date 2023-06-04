#include <iostream>
#include <cstring>
#include <algorithm> 
#include "function.h"
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
	// string : lOCCTR 
	// ----------------------------------------
	string str;
	string tmp = "";
	string lables;
	string mnemonic_operation_code;
	string symbolic_operands;
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
	// the index of lineStr string
	// ----------------------------------------
	int i;
	// ----------------------------------------
	// check if exist a tab then no any lable 
	// ----------------------------------------
	if(lineStr[0] == '\t')
	{
		// ----------------------------------------
		// get mnemonic_operation_code in first line
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
		// get lables in first line
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
		fprintf(intermediate, (LOCCTR + "\t" + lineStr + "\n").c_str());
	}
	else
	{
		// ----------------------------------------
		// store "0" to LOCCOR and start_address
		// ----------------------------------------
		start_address = LOCCTR = "0";
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
		// get symbolic_operands
		// ----------------------------------------
		symbolic_operands = "";
		for(; i < lineStr.length() ; i++)
		{
			symbolic_operands += lineStr[i];
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
				cout << LOCCTR << " " << lables << "\n";
			}
		}
		// ----------------------------------------
		// write a line to intermediate file
		// ----------------------------------------
		fprintf(intermediate, (LOCCTR + "\t" + lineStr + "\n").c_str());
		// ----------------------------------------
		// check if mnemonic_operation_code is in OPTAB
		// ----------------------------------------
		string opcode;
		if(OPTAB.search(mnemonic_operation_code,opcode))
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
			LOCCTR = stringAddition(LOCCTR,intToString(3 * hexStringToInteger(symbolic_operands)));	
		}
		// ----------------------------------------
		// check if mnemonic_operation_code is "RESB"
		// ----------------------------------------
		else if (mnemonic_operation_code == "RESB")
		{
			LOCCTR = stringAddition(LOCCTR,decimalToHexString(symbolic_operands));		
		}
		// ----------------------------------------
		// check if mnemonic_operation_code is "BYTE"
		// ----------------------------------------
		else if (mnemonic_operation_code == "BYTE")
		{
			// ----------------------------------------
			// check if symbolic_operands is like C'EOF'
			// ----------------------------------------
			if(symbolic_operands[0] == 'C' && symbolic_operands[1] == '\'')
			{
				symbolic_operands= removeQuotes(symbolic_operands);
				LOCCTR = stringAddition(LOCCTR,intToString(symbolic_operands.length()));	
			}
			// ----------------------------------------
			// check if symbolic_operands is like X'1A'
			// ----------------------------------------
			else if (symbolic_operands[0] == 'X' && symbolic_operands[1] == '\'')
			{
				symbolic_operands = removeQuotes(symbolic_operands);
				LOCCTR = stringAddition(LOCCTR,intToString(symbolic_operands.length()/2));
			}
			// ----------------------------------------
			// symbolic_operands is like 1000
			// ----------------------------------------
			else
				LOCCTR = stringAddition(LOCCTR,decimalToHexString(symbolic_operands));	
		}
		
		
	}
	// ----------------------------------------
	// get symbolic_operands in last line
	// ----------------------------------------
	symbolic_operands = "";
	for(; i < lineStr.length() ; i++)
	{
		symbolic_operands += lineStr[i];
	}
	// ----------------------------------------
	// write a last line to intermediate file
	// ----------------------------------------
    fprintf(intermediate, ("\t" + lineStr + "\n").c_str());
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
	// string : lOCCTR 
	// ----------------------------------------
	string str;
	string tmp = "";
	string lables;
	string mnemonic_operation_code;
	string symbolic_operands;
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
	// the index of lineStr string
	// ----------------------------------------
	int i;
	// ----------------------------------------
	// get LOCCOR in first line
	// ----------------------------------------
	LOCCTR = "";
	for(i = 0 ; i < lineStr.length() ; i++)
	{
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
	// bool : is_X
	// ----------------------------------------
	int textlength = 0;
	string all_object = "";
	bool is_X;
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
		is_X = false;
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
		// get symbolic_operands
		// ----------------------------------------
		symbolic_operands = "";
		for(; i < lineStr.length() ; i++)
		{
			// ----------------------------------------
			// stop when encounter ','
			// ----------------------------------------
			if(lineStr[i] == ',')
			{
				// ----------------------------------------
				// set X to "1"
				// ----------------------------------------
				is_X = true;
				break;	
			}
			else
				symbolic_operands += lineStr[i];
		}
		// ----------------------------------------
		// check if mnemonic_operation_code is in OPTAB
		// and store opcode of it to opcode string variable 
		// ----------------------------------------
		string opcode = "";
		string operands = "";
		string object = "";
		if(OPTAB.search(mnemonic_operation_code,opcode))
		{
			// ----------------------------------------
			// check if symbolic_operands is not empty
			// ----------------------------------------
			if(symbolic_operands != "")
			{
				// ----------------------------------------
				// check if symbolic_operands is in SYMTAB
				// and store address of it to operands string variable
				// ----------------------------------------
				if(SYMTAB.search(symbolic_operands,operands));
				// ----------------------------------------
				// symbolic_operands is not in SYMTAB
				// ----------------------------------------
				else
				{
					operands = "0000";
				}
				// ----------------------------------------
				// check if X is "1"
				// ----------------------------------------
				if(is_X)
				{
					operands = stringAddition(operands, "8000");
				}
			}
			// ----------------------------------------
			// symbolic_operands is empty
			// ----------------------------------------
			else
			{
				operands = "0000";
			}
			// ----------------------------------------
			// tranlate it to object code
			// ----------------------------------------
			object = opcode + operands;
		}
		else if (mnemonic_operation_code == "BYTE" || mnemonic_operation_code == "WORD")
		{
			// ----------------------------------------
			// check if symbolic_operands is like C'EOF'
			// ----------------------------------------
			if(symbolic_operands[0] == 'C' && symbolic_operands[1] == '\'')
			{
				symbolic_operands= removeQuotes(symbolic_operands);
				for (i = 0 ; i < symbolic_operands.length() ; i++)
					object += decimalToHexString(intToString(symbolic_operands[i]));
			}
			// ----------------------------------------
			// check if symbolic_operands is like X'1A'
			// ----------------------------------------
			else if (symbolic_operands[0] == 'X' && symbolic_operands[1] == '\'')
			{
				symbolic_operands = removeQuotes(symbolic_operands);
				object = symbolic_operands;
			}
			else
			{
				// ----------------------------------------
				// if mnemonic_operation_code is BYTE
				// ----------------------------------------
				if(mnemonic_operation_code == "BYTE")
					object = decimalToHexString(symbolic_operands);
				// ----------------------------------------
				// if mnemonic_operation_code is WORD
				// ----------------------------------------
				else
					object = decimalToHexString(symbolic_operands);
				// ----------------------------------------
				// if length of object code is less than 6 then append "0" to object code
				// ----------------------------------------
				while(object.length() < 6)
				{
					object = "0" + object;
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
	// append "0" to start_address when length of start_address is less than 6
	// write a END Record to object_file file
	// ----------------------------------------
	while(start_address.length() < 6)
		start_address = "0" + start_address;
    fprintf(object_file, ("E" + start_address + "\n").c_str());
	// ----------------------------------------
	// close intermediate file and close object_file file
	// ----------------------------------------
	fclose(intermediate);	
	fclose(object_file);
}
