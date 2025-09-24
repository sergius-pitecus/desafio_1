#ifndef LOW_END_H
#define LOW_END_H

#include <cstddef>  // para size_t

// Convierte matriz de bloques a un arreglo lineal
unsigned char* simplify_mat(unsigned char** text, size_t size_first_dim, size_t size_second_dim, size_t used_size);

// Descomprime texto usando RLE
void de_RLE(unsigned char*& text, size_t size);

unsigned char rot_byte(unsigned char character, int n_rot);

unsigned char rot_byte(unsigned char character, int n_rot);

unsigned char de_encryptation_byte(unsigned char character, int n_rot, int xor_mask);

int size_text(const char* nom_texto);

unsigned char* into_text(const char* nom_texto, int tam_texto);

#endif // LOW_END_H