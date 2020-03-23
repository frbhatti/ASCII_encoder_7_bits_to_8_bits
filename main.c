 /**
 * LICENSING INFO 
 *
 *****************************************************************************/
/**
 * @file main.c
 * @brief This file contains the application code for encoding and decoding APIs as well as its test routine	
 * @author Fahad Rahim Bhatti
 * @date 23 March 2020
 *
 */


#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <ctype.h>
#include "encoding.c"


int main(){
/* application data initialization */
	char input[100] = {0}; 			//keyboard input
	char encoded_txt[100] = {0};	//application memory to store the encoder output 
	char decoded_txt[100] = {0};	//application memory to store the decoder output	
	int32_t length_input_text=0;
	int32_t length_encoded_text = 0;
	int32_t length_decoded_text = 0;

/* taking input from the user */
	printf("\nEnter the text: ");
	fgets(input, sizeof(input), stdin); //reads keyboard input and ends with character \n 

	char *pos;
	if ((pos=strchr(input, '\n')) != NULL) // searches for the first occurrence of the character \n, since fgets() terminates with \n
    *pos = '\0'; 							//replace the end with NULL terminator

/* displaying the input */
	length_input_text = strlen(input);

	printf("Length of input text is %d: \n", length_input_text );

	for (int x=0; x<length_input_text; x++) { 
		printf("\n input[%d] :", x);	
		printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input[x]));
	}
	printf("\n");

/* running the encoder on user input */
	length_encoded_text = text_7bit_encode(input, encoded_txt);

	printf("\nLength of encoded text is %d: \n", length_encoded_text );

	for (int x=0; x<length_encoded_text; x++) {
	
		printf("\n encoded_txt[%d] :", x);
		printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(encoded_txt[x]));
	}
	printf("\n");

/*running the decoder on the encoder output*/
	length_decoded_text = text_7bit_decode(encoded_txt, decoded_txt);

	printf("\nLength of decoded text is %d: \n", length_decoded_text );

	for (int x=0; x<length_decoded_text; x++) {
	
		printf("\n decoded_txt[%d] :", x);
		printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(decoded_txt[x]));
	}
	printf("\n");

/*verifying the correctness of encoder and decoder operation*/
	if (test_correctness(input, decoded_txt)) {

		printf("\n All Tests Passed!\n");
	}
	
	return 0;	
}





