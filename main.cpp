#include <iostream>
#include <low_end.h>


int main(int num_arg, const char** conj_text){

	unsigned char* og_text = nullptr; //puntero al texto codificado
	unsigned char* clue = nullptr; //puntero a la pista
	size_t size_og_text, size_clue; 
	unsigned char steps[3]; //puntero a los pasos de desencriptacion
    // ^ 0: RLE o LZ78, 1: Rotacion, 2: XOR
	for( int current_text = 1 ; current_text <= num_arg ; current_text += 2){
		short unsigned int xor_key = 0;
		size_t used_de_text = 0;
        size_og_text = size_text(conj_text[current_text]);
		extract_text(conj_text[current_text], og_text, size_og_text);
        size_clue = size_text(conj_text[current_text+1]);
        extract_text(conj_text[current_text+1], clue, size_clue);
        unsigned char* de_text = new unsigned char[size_og_text]; //puntero al texto desencriptado
        if(de_text == nullptr){
            std::cerr<<"ERROR: FAILED TO RESERVE MEMORY SPACE\n";
            return -1;
        }
		if(size_og_text == 0) std::cerr<<"\nERROR: "<<conj_text[current_text]<<" FILE NOT FOUND OR VOID OF ANY MESSAGE\n";
		while (xor_key < 256){
			unsigned char current_byte;
			bool probLZ78 = false;
            signed char byte_rot = 7; //signed ya que al agotar rotaciones se vuelve -1
			while( used_de_text < size_og_text && byte_rot >= 0){
				current_byte = de_encryptation_byte(og_text[used_de_text], byte_rot, xor_key); //se me olvido por que es og_text[used_de_text], revisar
				if((current_byte >= 48&&current_byte <= 57)||(current_byte >=65&&current_byte<=90)||( current_byte>=97&&current_byte<=122)){
					//if()primer caracter es numero;
                    else if( used_de_text == 0 && current_byte == '0'){ //si el primer digito es un 0, es probable que sea LZ78
                        probLZ78 = true;
                        steps[0] = 1;
                    }
                    //else if() si es letra y el caracter anterior tambien es letra
                    else if( probLZ78 && current_byte == '0'){ //En caso de que el primer digito no sea 0 y despues se encuentre un 0
                        used_de_text = 0;
                        byte_rot--;
                        probLZ78 = false;
                    }
                    //else if probLZ78 y current_byte > used_de_text
                    //de_text[used_de_text] = current_byte;
                    //used_de_text++;
				}
                else{
                    //reinicio de variables
                    probLZ78 = false;
                    used_de_text = 0;
                    byte_rot--;
                }
            }
            //reinicio de variables
		    if(used_de_text == size_og_text){
			    if(probLZ78) de_LZ78(de_text, used_de_text);
			    else de_RLE(de_text, used_de_text);
                //se comprueba que el texto desencriptado contenga la pista
                if(contains_clue(de_text, used_de_text, clue, size_clue)){
                    steps[1] = abs(byte_rot-7);
                    steps[2] = xor_key;
                    //se guardan en el archivo respuesta.txt los pasos de desencriptacion
                }
                else{
                    //recreacion del texto descomprimido
                    delete[] de_text;
                    de_text = new unsigned char[size_og_text];
                    if(de_text == nullptr){
                        std::cerr<<"ERROR: FAILED TO RESERVE MEMORY SPACE\n";
                        return -1;
                    }
                    used_de_text = 0;
                    xor_key++;
		        }
            }
            else xor_key++;
	    }
    delete[] de_text;
    delete[] og_text;
    delete[] clue;
    }
}