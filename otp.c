#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encipher(FILE* message_file, FILE* output_file, FILE* key_file){

    int code;
    int key;
    int enciphered_code;
    // Read the file until End Of File char (EOF)
    while( (code=fgetc(message_file)) != EOF ){
        key = rand(); // pick one use key with random
        enciphered_code = code ^ key; // code XOR key = enciphered_code
        // write output files
        fputc(key, key_file);
        fputc(enciphered_code, output_file);
    }

}

void decipher(FILE* message_file, FILE* output_file, FILE* key_file){

    int enciphered_code;
    int key;
    int code;
    // Read the file until End Of File (EOF)
    // Assuming that the Enciphered File (= E.F.) and Key File have
    // at least the same size, or E.F. smaller than Key File
    while ( (enciphered_code=fgetc(message_file)) != EOF ){
        key = fgetc(key_file);
        code = enciphered_code ^ key; // enciphered_code XOR key = code
        // Write output file
        fputc(code, output_file);
    }
}

void str_copy_with_size(char* dest, char* src, size_t size){
    int i;
    for (i = 0 ; i < size-1; i++){
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

void print_usage(){
    printf("\
Usage : otp <operation> <input> <key> [output]\n\
\n\
Arguments: :\n\
<operation>  L'opération à effectuer\n\
<input>      Le fichier sur lequel le programme travaillera\n\
<key>        Le fichier qui stocke la clé\n\
[output]     Le fichier qui contiendra le résultat\n\
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

    if (argc < 3){
        printf("Erreur : Vous n'avez pas donné assez d'arguments.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    int operation;
    char* input_filename = argv[2];
    char output_filename[50];
    char* key_filename = argv[3];

    if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encipher") == 0){
        operation = 1;
    } 
    else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decipher") == 0) {
        operation = 2;
    } else {
        operation = 0;
    }

    if (operation == 0) {
        printf("Erreur : Opération invalide.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    if (argc >= 5){
        str_copy_with_size(output_filename, argv[4], 50);
    } else {
        strcpy(output_filename, "message.out");
    }

    FILE* input = fopen(input_filename, "r"); // might not exists

    if (input == NULL){
        printf("Erreur : le fichier %s n'existe pas.\n", input_filename);
        return EXIT_FAILURE;
    }

    FILE* output = fopen(output_filename, "w");
    FILE* key_file;

    if (operation == 1){
        key_file = fopen(key_filename, "w");
        encipher(input, output, key_file);
    } else if (operation == 2) {
        key_file = fopen(key_filename, "r");
        if (key_file == NULL){
            printf("Erreur : le fichier %s n'existe pas.\n", key_filename);
            return EXIT_FAILURE;
        }
        decipher(input, output, key_file);
    }

    fclose(input);
    fclose(output);
    fclose(key_file);

    return EXIT_SUCCESS;
}