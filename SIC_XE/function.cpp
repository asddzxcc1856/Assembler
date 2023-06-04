#include "function.h"
// ----------------------------------------
// hex character to decimal integer
// ----------------------------------------
int hexCharToDecimal(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else
        return -1;  // Invalid hex character
}
// ----------------------------------------
// hex string to decimal integer
// ----------------------------------------
int hexStringToInteger(const string& hexString) {
    int result = 0;

    for (int i = 0 ; i < hexString.length() ; i++) {
        int decimalValue = hexCharToDecimal(hexString[i]);
        if (decimalValue == -1) {
            cerr << "Invalid hex string: " << hexString << endl;
            return 0;  // Return a default value if conversion fails
        }
        result = result * 16 + decimalValue;
    }

    return result;
}
// ----------------------------------------
// decimal integer to hex character 
// ----------------------------------------
char intToHexChar(int n) {
    if (n >= 0 && n <= 9) {
        return '0' + n;
    } else if (n >= 10 && n <= 15) {
        return 'A' + (n - 10);
    }
    return '0';
}
// ----------------------------------------
// hex string add hex string to hex string 
// ----------------------------------------
string stringAddition(const string& str1, const string& str2) {
    // 轉換成整數
    int num1 = hexStringToInteger(str1);
    int num2 = hexStringToInteger(str2);

    // 相加
    int sum = num1 + num2;

    // 轉換回16進位字串
    string hexSum;
    while (sum > 0) {
        hexSum.push_back(intToHexChar(sum % 16));
        sum /= 16;
    }
    reverse(hexSum.begin(), hexSum.end());

    return hexSum;
}
// ----------------------------------------
// integer to decimal string 
// ----------------------------------------
string intToString(int number) {
    bool isNegative = false;
    if (number < 0) {
        isNegative = true;
        number = -number;
    }

    string result;
    if (number == 0) {
        result = "0";
    } else {
        while (number > 0) {
            char digit = '0' + (number % 10);
            result = digit + result;
            number /= 10;
        }
    }

    if (isNegative) {
        result = '-' + result;
    }

    return result;
}
// ----------------------------------------
// decimal string to integer
// ----------------------------------------
int customStoi(const string& decimalString) {
    int result = 0;
    bool isNegative = false;
    int i = 0;

    if (decimalString[0] == '-') {
        isNegative = true;
        i = 1;
    }

    for (; i < decimalString.length(); i++) {
        int digit = decimalString[i] - '0';
        result = result * 10 + digit;
    }

    return isNegative ? -result : result;
}
// ----------------------------------------
// decimal string to hex string 
// ----------------------------------------
string decimalToHexString(const string& decimalString) {
    int decimalValue = customStoi(decimalString);
    string hexString = "";

    while (decimalValue != 0) {
        int remainder = decimalValue % 16;
        char hexDigit = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
        hexString = hexDigit + hexString;
        decimalValue /= 16;
    }
	if(hexString == "") 
    	return "0";
	else
		return hexString;
}
// ----------------------------------------
// remove X'' or C''
// ----------------------------------------
string removeQuotes(const string& str) {
    return str.substr(2, str.length() - 3);
}
// ----------------------------------------
// build OPTAB for all mnemonic_operation_code
// ----------------------------------------
template<typename KeyType, typename ValueType, size_t TableSize, typename Hash>
void OPTAB_build(HashTable<KeyType, ValueType, TableSize, Hash>& OPTAB) 
{
	OPTAB.insert("ADD", "18");
	OPTAB.insert("ADDF", "58");
	OPTAB.insert("ADDR", "90");
	OPTAB.insert("AND", "40");
	OPTAB.insert("CLEAR", "B4");
	OPTAB.insert("COMP", "28");
	OPTAB.insert("COMPF", "88");
	OPTAB.insert("COMPR", "A0");
	OPTAB.insert("DIV", "24");
	OPTAB.insert("DIVF", "64");
	OPTAB.insert("DIVR", "9C");
	OPTAB.insert("FIX", "C4");
	OPTAB.insert("FLOAT", "C0");
	OPTAB.insert("HIO", "F4");
	OPTAB.insert("J", "3C");
	OPTAB.insert("JEQ", "30");
	OPTAB.insert("JGT", "34");
	OPTAB.insert("JLT", "38");
	OPTAB.insert("JSUB", "48");
	OPTAB.insert("LDA", "00");
	OPTAB.insert("LDB", "68");
	OPTAB.insert("LDCH", "50");
	OPTAB.insert("LDF", "70");
	OPTAB.insert("LDL", "08");
	OPTAB.insert("LDS", "6C");
	OPTAB.insert("LDT", "74");
	OPTAB.insert("LDX", "04");
	OPTAB.insert("LPS", "D0");
	OPTAB.insert("MUL", "20");
	OPTAB.insert("MULF", "60");
	OPTAB.insert("MULR", "98");
	OPTAB.insert("NORM", "C8");
	OPTAB.insert("OR", "44");
	OPTAB.insert("RD", "D8");
	OPTAB.insert("RMO", "AC");
	OPTAB.insert("RSUB", "4C");
	OPTAB.insert("SHIFTL", "A4");
	OPTAB.insert("SHIFTR", "A8");
	OPTAB.insert("SIO", "F0");
	OPTAB.insert("SSK", "EC");
	OPTAB.insert("STA", "0C");
	OPTAB.insert("STB", "78");
	OPTAB.insert("STCH", "54");
	OPTAB.insert("STF", "80");
	OPTAB.insert("STI", "D4");
	OPTAB.insert("STL", "14");
	OPTAB.insert("STS", "7C");
	OPTAB.insert("STSW", "E8");
	OPTAB.insert("STT", "84");
	OPTAB.insert("STX", "10");
	OPTAB.insert("SUB", "1C");
	OPTAB.insert("SUBF", "5C");
	OPTAB.insert("SUBR", "94");
	OPTAB.insert("SVC", "B0");
	OPTAB.insert("TD", "E0");
	OPTAB.insert("TIO", "F8");
	OPTAB.insert("TIX", "2C");
	OPTAB.insert("TIXR", "B8");
	OPTAB.insert("WD", "DC");
}
