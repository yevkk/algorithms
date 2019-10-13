# Polypase sort
A sorting algorithm that divides a source file (`const char SRC_NAME[]`) into sorted subsequences (sized by value of `const int MEMORY_SIZE`) that are put to files *A.bin*, *B.bin*, *C.bin* etc. (number of files is set as constant `int FILES`) and then merges subsequences to bigger sorted subsequences until only one sorted sequence, that includes all input numbers from source file, is left.

A function `create_source()` fills a source file with random numbers.

This implementation of algorithm allows to sort only non-negative int values (because it uses *-1* to mark the end of subsequence)  
