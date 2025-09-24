#include <iostream>
#include <low_end.h>


int main(int num_arg, char** conj_text){

	new unsigned char* og_text_ptr = nullptr; //puntero al texto codificado
	new unsigned char* clue_ptr = nullptr; //puntero a la pista
	long size_t size_og_text, size_clue; 
	unsigned char** steps[3][1]; //puntero a los pasos de desencriptacion
	for( int current_text = 1 : current_text <= num_arg : current_text += 2){
		short unsigned int xor_key = 0, byte_rot = 7;
		long size_t used_de_text = 0;
		bool file_error;
		extract_text(conj_text[current_text], og_text_ptr, &size_og_text); //corregir argumentos
        extract_text(conj_text[current_text+1], clue_ptr, &size_clue)
		if(size_og_text == 0) std::cout<<"\nERROR: "<<conj_text[current_text]<<" FILE NOT FOUND OR VOID OF ANY MESSAGE\n";
		while (xor_key < 256){
			unsigned char current_byte;
			bool probLZ78 = false;
			while( used_de_text <= size_og_text && byte_rot > 0){
				current_byte = de_encryptation_byte(*og_text_ptr[used_de_text]) 
				if((current_byte >= 48&&current_byte <= 57)||(current_byte >=65&&current_byte<=90)||( current_byte>=97&&current_byte<=122)){
					if(used_de_text = 0 && current_byte = '0'){
					}
				}
			}
		    xor_key++;
		    if(used_de_text == size_og_text){
			    if(probLZ78) de_LZ78(de_text, used_de_text);
			    else de_RLE(de_text, used_de_text);
		    }
	    }
    }
}