#include <stdio.h>
#include <stdlib.h>

void encipher(FILE* secret_file, FILE* output_file, FILE* key_file){

    int code;
    int key;
    int enciphered_code;
    // Read the file until End Of File char (EOF)
    while( (code=fgetc(secret_file)) != EOF ){
        key = rand(); // pick one use key with random
        enciphered_code = code ^ key; // code XOR key
        // write output files
        fputc(key, key_file);
        fputc(enciphered_code, output_file);
    }

}

void decipher(FILE* secret_file, FILE* output_file, FILE* key_file);

int main(int argc, char* argv[]){
    return EXIT_SUCCESS;
}