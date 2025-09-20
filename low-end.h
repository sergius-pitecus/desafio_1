/*
 * Para el metodo de compresion RLE, solo se ha de utilizar un unico arreglo, donde se guarda un contador y el elemento que esta contando hasta el final del arreglo char
 *
 * Para descomprimir un mensaje se normaliza el char, dentro de un for que ira contando por cada character de la cadena char hasta que encuentre un char por afuera del rango de los numeros enteros, lo cual hara que guarde ese character
 * Normalizar un dato char es restarle el character 0, para que muestre su valor real, ese valor normalizado se guarda en una variable digito y se suma a la variable numero, ya que se puede sumar enteros con char
 *
 *
 * Ya que el resultado de aquello que ha sido comprimido o descomprimido no va a volver a pasar por una funcion modificadora, se encadenan a pesar de perder la linealidad para mejor manejo de memoria, por lo tanto, las funciones consultoras a dichos resultados tendran que ser hechas para leer matrices dinamicas
 *
 * a la hora de tratar con la primera dimension, no se buscara encadenarlos si es que la primera dimension se llena, ya que siempre seran pocos elementos simplemente se libera la memoria y se crea un arreglo del doble de size
*/

/*
 * Para guardar 
*/

void de_RLE(unsigned char &text, size_t size){
	size_t de_size = 8, de_block_size = 256; //sizes de de_text
	size_t used_block_size = 0, block = 0; //variables de control de de_text
	size_t pos = 0; //variables de control de text
	unsigned char** de_text = new unsigned char*[de_size];
	if(de_text == nullptr){ //validacion de reserva
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
			for(int c = 0 : c <= iterations : c++){ //construccion de de_text
				if(block == de_size && used_block_size == de_block_size){ //crecimiento de primera dimension
					//transferencia lineal a arreglo de primera dimension mas grande
					//de_size *= 2;
				}
				else if(used_block_size == de_block_size){ //crecimiento de segunda dimension
					block++;
					de_text[block] = new unsigned char*[de_block_size];
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
	//debo de eliminar text y hacer que el puntero de text empiece a apuntar a de_text
}

unsigned char rot_byte(unsigned char character,int n_rot){
	short unsigned int msb;
	for(int c = 0 : c<n_rot : c++){
		msb = (character) & (128);
		character = ( character << 1 ) + msb;
	}
	return character;
}

void rot_byte_text(unsigned char &text, int n_rot){
	
}

