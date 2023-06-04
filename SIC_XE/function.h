// ----------------------------------------
// hex character to decimal integer
// ----------------------------------------
int hexCharToDecimal(char c);
// ----------------------------------------
// hex string to decimal integer
// ----------------------------------------
int hexStringToInteger(const string& hexString);
// ----------------------------------------
// decimal integer to hex character 
// ----------------------------------------
char intToHexChar(int n);
// ----------------------------------------
// hex string add hex string to hex string 
// ----------------------------------------
string stringAddition(const string& str1, const string& str2);
// ----------------------------------------
// integer to decimal string 
// ----------------------------------------
string intToString(int number);
// ----------------------------------------
// decimal string to integer
// ----------------------------------------
int customStoi(const string& decimalString);
// ----------------------------------------
// decimal string to hex string 
// ----------------------------------------
string decimalToHexString(const string& decimalString);
// ----------------------------------------
// remove X'' or C''
// ----------------------------------------
string removeQuotes(const string& str);
// ----------------------------------------
// build OPTAB for all mnemonic_operation_code
// ----------------------------------------
template<typename KeyType, typename ValueType, size_t TableSize, typename Hash>
void OPTAB_build(HashTable<KeyType, ValueType, TableSize, Hash>& OPTAB);
