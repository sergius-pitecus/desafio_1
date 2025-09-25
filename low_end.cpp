#include <iostream>
#include <low-end.h>

unsigned char* simplify_mat( unsigned char** text, size_t size_first_dim, size_t size_second_dim, size_t used_size){
	unsigned char* simplified_text = new unsigned char[used_size];
	for( int block = 0 ; block < size_first_dim ; block++){
		for( int pos = 0 ; pos < size_second_dim ; pos++){
			if( (block*size_second_dim + pos) < used_size ) simplified_text[block*size_second_dim + pos] = text[block][pos];
		}
		delete[] text[block]; //liberacion de memoria de cada bloque
	} 
    delete[] text; //liberacion de memoria del arreglo de bloques
	return simplified_text;
}

void de_RLE(unsigned char* &text, size_t size){
	size_t de_size = 8, de_block_size = 256; //sizes de de_text
	size_t used_block_size = 0, block = 0; //variables de control de de_text
	size_t pos = 0; //variables de control de text
	unsigned char** de_text = new unsigned char*[de_size];
	if(de_text == nullptr){ //validacion de reserva
		std::cerr<<"ERROR: FAILED TO RESERVE MEMORY SPACE\n";
		return;
    }
	de_text[0] = new unsigned char[de_block_size];
	if(de_text[0] == nullptr){ //validacion de reserva
		std::cerr<<"ERROR: FAILED TO RESERVE MEMORY SPACE\n";
		return;
	}
	while(pos < size){
		int iterations = 0;
		while(('0' <= text[pos]) && (text[pos] <= '9')){ //construccion del numero de iteraciones del caracter
			iterations = iterations*10 + (text[pos] - '0');
			pos++;
		}
		if (pos < size){
			for(int c = 0 ; c < iterations ; c++){ //construccion de de_text
				if(block == de_size-1 && used_block_size == de_block_size){ //crecimiento de primera dimension
					unsigned char** aux_arr = new unsigned char*[de_size*2];
					for ( int i = 0; i < de_size ; i++ ) aux_arr[i] = de_text[i];
					delete[] de_text;
					de_text = aux_arr;
					de_size *= 2;  //transferencia lineal a arreglo de primera dimension mas grande
				}
				else if(used_block_size == de_block_size){ //crecimiento de segunda dimension
					block++;
					de_text[block] = new unsigned char[de_block_size];
					if(de_text[block] == nullptr){
						std::cerr<<"ERROR: FAILED TO RESERVE MEMORY SPACE";
						return;
					}
					used_block_size = 0;
				}
				de_text[block][used_block_size] = text[pos]; //asignacion de espacio dentro del arreglo
				used_block_size++;
			}
			pos++;
		}
	}

	delete[] text; //liberacion de memoria del arreglo original
	text = simplify_mat(de_text, de_size, de_block_size, (block*de_block_size + used_block_size) ); //simplificacion del arreglo
}

unsigned char rot_byte(unsigned char character, int n_rot) {
    for (int c = 0; c < n_rot; c++) {
        unsigned char lsb = character & 1;
        character = (character >> 1) | (lsb << 7);
    }
    return character;
}


unsigned char de_encryptation_byte(unsigned char character, int n_rot, int xor_mask){
	unsigned char xor_character = character ^ xor_mask;
	return rot_byte(xor_character, n_rot);
}

size_t size_text(const char* nom_texto){

    unsigned char caracter;

    std::ifstream archivo(nom_texto);            // aqui abrimos el archivo con el fstream

    if (archivo.is_open()) {
        size_t cont = 0;
        while (archivo.get(caracter)) cont++;       // pa cuando expongas recuerda que el .get si no hay errores retorna un true
        archivo.close();
    } else return 0;
    if (cont == 0) return 0;
    return cont;
}

unsigned char* extract_text(const char* nom_texto, int tam_texto) {

    int cont2 = 0;
    char caracter;

    std::ifstream archivo(nom_texto);                   //si todo salio bien viene lo que queremos y creamos el propio arreglo
    unsigned char* dm_texto = new unsigned char[tam_texto + 1];      //y le metemos el tama�o que conseguimos con el ciclo anterior

    if (archivo.is_open()) {

        while (archivo.get(caracter)) {
            dm_texto[cont2] = (unsigned char) caracter;
            cont2++;
        }
        dm_texto[cont2] = '\0';
        archivo.close();
    } else {
        delete[] dm_texto;                                 //en caso de que el archivo no abra borramos contenido y mandamos el error
        std::cerr << "\nERROR: FILE NOT FOUND" << std::endl;
        return nullptr;
    }
    return dm_texto;                             // profe, no sabe lo que me frusto poder llegar hasta aqui, retornamos el puntero del arreglo
}

