# ASCII_encoder_7_bits_to_8_bits
### ASCII encoder and decoder basic application and API

Task:
A library with the API specified below, and the application to test it. The project contains 2 source .c files, and a Makefile necessary to build it. The sources are buildable on any POSIX system.

The API:
int32_t text_7bit_encode(const char* txt_in, char* txt_out);
txt_in: null-terminated ASCII string to encode,
txt_out: 7-bit encoded string, null terminated (the implementation makes sure there is a \0 value at the end), the function returns the size of the output data (>0) or error (<0).

int32_t text_7bit_decode(const char* txt_in, char* txt_out);
txt_in: null-terminated 7-bit encoded string,
txt_out: null-terminated decoded ASCII string, the function returns the size of the output data (>0) or error (<0).
 
The functions checks the correctness of their parameters (NULL pointers, non-ASCII characters) and report the errors, but accepts and ignores the NULL as the second parameter. The encode function takes the 8-bit ASCII characters, and compress the string by removing the most significant bit and packing such 7-bit characters in the 8-bit bytes, so that all the bits are used (each 8 character sequence would then fit in 7 bytes) - for example:
for 2 characters in the original string, the 7 bits of the first byte of the encoded string would contain the 7 bits of the original ASCII character, the most significant bit of this first byte would be the least significant bit of the second ASCII character, and the second byte of the encoded string would contain the remaining 6 bits of the second ASCII character.
 
The decode function takes such a compressed string and "unpack" it, putting all the 7-bit characters back in their own bytes, with their most significant bit 0.
 
The testing application demonstrates the correctness of the implementation.

## How To Run the Application
1. In a POSIX system such as mac-os, using terminal go to the folder containing these files.
2. To compile the code, run the following `$make` or `$make build` or `$gcc -o main.out main.c`
3. To run the application, run the command `$./main.out` and the application will run asking you to enter data.
4. _optional_ To clean the compiled application, run in the terminal `$make clean`
