# assmebly.cpp 中使用四個函式庫:
- pass1_2.cpp

# pass1_2.cpp 中使用四個函式庫:
- iostream
- cstring
- algorithm 
- pass1_2.h
- function.cpp
- HashTable.cpp

# function.cpp 中使用四個函式庫:
- function.h

# HashTable.cpp 中使用四個函式庫:
- HashTable.h

# 程式流程:
- 使用 assmebly.cpp 檔案編譯產生 assmebly.exe 程式中先去引入函式 pass1_2.h 依照順序呼叫 pass1() pass2()
- Pass1 讀取 source.txt 產生 intermediate.txt 檔案和建立 OPTAB、SYMTAB HashTable
- Pass2 讀取 intermediate.txt 檔案和利用Pass1建立好的 OPTAB、SYMTAB HashTable 產生 object.txt