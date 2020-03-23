 /**
 * LICENSING INFO 
 *
 *****************************************************************************/
/**
 * @file encoding.c
 * @brief This file contains the source code for encoding and decoding APIs as well as its test routine
 * @author Fahad Rahim Bhatti
 * @date 23 March 2020
 *
 */


/* MACROS */ 

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


/**
 * @brief A 7bit ASCII encoder 
 *
 *The encode function takes the 8-bit ASCII characters, and compress the string by removing the most 
 significant bit and packing such 7-bit characters in the 8-bit bytes, so that all the bits are used 
 (each 8 character sequence would then fit in 7 bytes) 
 *
 * @param txt_in is a pointer to const char type array for data input to the encoder
 * @param txt_in is a pointer to char type array for data output from the encoder
 *
 * @return returns -1 in case of error else the size of the output string
 */

int32_t text_7bit_encode(const char* txt_in, char* txt_out);

/**
 * @brief A decoder from compressed 8 bits to 7bit ASCII characters 
 *
 The decode function take  a compressed string that is the output of text_7bit_encode and "unpack" it,
 putting all the 7-bit characters back in their own bytes, with their most significant bit 0.
 * @param txt_in is a pointer to const char type array for data input to the decoder
 * @param txt_in is a pointer to char type array for data output from the decoder
 *
 * @return returns -1 in case of error else the size of the output string
 */

int32_t text_7bit_decode(const char* txt_in, char* txt_out);

/**
 * @brief a test routine to check the correctness of encoder and decoder operation 
 *
 * This function compares the lenghts of the strings as well as the contents of an input that 
 is not encoded to the output of the decoder. If the passed parameters are the input that was given 
 to the encoder function, and the output of the decoder function, they'll be equal only if both the
 encoder and decoder have functioned correctly for the given data.
 *
 * @param encoder_input is a pointer to  char type array for data input to the encoder
 * @param decoder_output is a pointer to char type array for data output from the decoder
 *
 * @return returns 1 in case the test passed and -1 in case of failure
 */
int32_t test_correctness(char* encoder_input, char* decoder_output);

/*Below are the implementations of each routine defined above*/

int32_t text_7bit_encode(const char* txt_in, char* txt_out) {

	for (int i =0; i< strlen(txt_in); i++){

  		if(txt_in[i]>127 && txt_in[i]<=0) //Checks for the byte to be ASCII as well as not a NULL 
  		{
  			printf("Not an ASCII Value\n");
  			return -1; 
		}	
 	}
	
	int32_t input_length = strlen(txt_in);
	
	char input_array[100] = {0};

	for(int i = 0; i < input_length; i++) {  //copy the array elements into a temporary storage since txt_in is const 

    	input_array[i] = txt_in[i]; 
  	}

	char tempBits = 0;
	char tempByte = 0;
	int numberOfByteSkip =0; //number of times input byte was skipped/reduced/emptied due to encoding 
	int baseIndex=0;

	while (input_array[baseIndex + numberOfByteSkip ] != '\0') { //stop when null character is reached

		for (int i=0;i<7;i++) { //only seven & not eight because txt_out will be filled in 7 iterations

//printf("\n input_array[%d] :", (i+baseIndex + numberOfByteSkip)); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input_array[i+baseIndex+numberOfByteSkip]));

			txt_out[baseIndex + i] = input_array[baseIndex + numberOfByteSkip + i]; // first copy the existing byte of input_array into the next avaialbe byte in txt_out

//printf("\n txt_out[%d] :", (i+baseIndex)); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(txt_out[i+baseIndex]));

			tempBits =  (pow(2, i+1) -1); 	//next create a mask for the LSBs of the next input_array byte (2^n -1)
			tempBits &= input_array[baseIndex + numberOfByteSkip + i+1]; 	  //take the LSBs of next input_array byte 

//printf("\n tempBits in LSB:"); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(tempBits));
			
			tempBits = tempBits<<(8-(i+1)); //then convert these LSBs to MSBs 

//printf("\n tempBits to MSB:"); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(tempBits));
			
			txt_out[baseIndex + i] |=  tempBits ; //and copy into the available MSBs of txt_out byte

//printf("\n txt_out[%d] :", (i+baseIndex)); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(txt_out[i+baseIndex]));

			input_array[baseIndex + numberOfByteSkip + i+1] = input_array[baseIndex + numberOfByteSkip + i+1]>> (i+1); //finally right shift the next input_array byte whose LSBs were taken

//printf("\n input_array[%d] :", (i+1+baseIndex + numberOfByteSkip)); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(input_array[i+1+baseIndex + numberOfByteSkip]));
//printf("\n");

		}

	baseIndex += 7; //the txt_out has now 7 bytes already	
	numberOfByteSkip++; // one more byte is skipped/reduced from input_array because of the encoding
	}
	
	int32_t output_length = strlen(txt_out);

	return output_length;
}




int32_t text_7bit_decode(const char* txt_in, char* txt_out){


	int32_t input_length = strlen(txt_in);

	unsigned char tempBits = 0;
	unsigned char tempByte = 0;
	int numberOfByteAdd =0; //number of times input byte was skipped/reduced/emptied due to encoding 
	int baseIndex=0;
//	unsigned char tempBits2= 0;

	while (txt_in[baseIndex] != '\0') { //continue until NULL character is reached

		for (int i=0;i<7;i++) { //only seven & not eight because txt_in will create 8 txt_out bytes in 7 iterations

			if(i==0) {
			
				txt_out[baseIndex + numberOfByteAdd] = txt_in[baseIndex] & 0x7F; // copy the 7LSB of first byte in txt_out
			
			}

			else { //handling of bytes from i==1 to i==6
		
//printf("\n txt_in[%d]:", (i+baseIndex)); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(txt_in[i+baseIndex]));

				tempBits = txt_in[baseIndex + i-1]; //copy previous byte

//printf("\n tempBits:"); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(tempBits));

				tempBits =  tempBits >> (8-i);    //keep only the MSBs of the previous byte to make the LSBs for this byte

//printf("\n tempBits:"); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(tempBits));

				tempByte = (pow(2, (7-i)) -1);   //create a mask to read the byte

//printf("\n tempByte:"); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(tempByte));

				tempByte &= txt_in[baseIndex + i];			 //read the corresponding LSBs of the byte
				tempByte = tempByte << i;		 // left shift 

//printf("\n tempByte:"); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(tempByte));

				tempByte |= tempBits;			//combine to make the byte
				txt_out[baseIndex + numberOfByteAdd + i] = tempByte; 

//printf("\n txt_out[%d]:", (i+1+baseIndex+numberOfByteAdd)); printf(" "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(txt_out[i+1+baseIndex+numberOfByteAdd]));
			
			}
			if (i==6) { //do more for the 7th byte, it has full ASCII character in its MSB
				tempByte =0;
				tempByte = txt_in[baseIndex + i];
				txt_out[baseIndex + numberOfByteAdd + i+1 ] = tempByte >> 1;
			}
		}

		baseIndex += 7; //the txt_out has now 7 bytes already	
		numberOfByteAdd++; // one more byte is skipped/reduced from txt_in because of the encoding

	}

	int32_t output_length = strlen(txt_out);

	return output_length;
}


int32_t test_correctness(char* encoder_input, char* decoder_output){

	if(strlen(encoder_input)==strlen(decoder_output))
	{
		for (int i=0; i<strlen(encoder_input); i++)
		{
			if (decoder_output[i]!=encoder_input[i]){
				printf("\nError: encoder input and vecoder output values at index %d differ\n",i);
				return -1;
			}
		}
		printf("\nVoila! There was no difference between encoder input and decoder output.");
		return 1;
	}	
	else
	{
		printf("\nError: The lengths of encoder input and decoder output are not the same!");
		return -1;

	}

}




