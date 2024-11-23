#include <stdio.h>
#include <stdlib.h>

void encipher(FILE* secret_file, FILE* output_file, FILE* key_file){

    int code;
    int key;
    int enciphered_code;
    // Read the file until End Of File char (EOF)
    while( (code=fgetc(secret_file)) != EOF ){
        key = rand(); // pick one use key with random
        enciphered_code = code ^ key; // code XOR key = enciphered_code
        // write output files
        fputc(key, key_file);
        fputc(enciphered_code, output_file);
    }

}

void decipher(FILE* secret_file, FILE* output_file, FILE* key_file){

    int enciphered_code;
    int key;
    int code;
    // Read the file until End Of File (EOF)
    // Assuming that the Enciphered File (= E.F.) and Key File have
    // at least the same size, or E.F. smaller than Key File
    while ( (enciphered_code=fgetc(secret_file)) != EOF ){
        key = fgetc(key_file);
        code = enciphered_code ^ key; // enciphered_code XOR key = code
        // Write output file
        fputc(code, output_file);
    }
}

void print_usage(){
    printf("\
Usage : otp <operation> <input> <key> [output]\n\
\n\
Arguments: :\n\
<operation>  L'opération à effectuer\n\
<input>      Le fichier sur lequel le programme travaillera\n\
<key>        Le fichier qui stocke la clé\n\
\n\
Operations:\n\
-e, --encipher  Chiffer le fichier d'entrée\n\
-d, --decipher  Déchiffrer le fichier d'entrée\n\
\n");
}

int main(int argc, char* argv[]){

    if (argc == 1){
        printf("Erreur : Vous n'avez précisé aucune opération.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}