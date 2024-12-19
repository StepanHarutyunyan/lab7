#include <stdio.h>
#include <string.h>

void caesarEncrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= ' ' && text[i] <= '~') {  
            text[i] = ((text[i] - ' ') + shift) % 95 + ' ';
        }
    }
}

void runLengthEncode(const char *input, char *output) {
    int count;
    int i, j = 0;
    int length = strlen(input);

    for (i = 0; i < length; i++) {
        count = 1;
        while (i + 1 < length && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        j += sprintf(&output[j], "%c%d", input[i], count);
    }
    output[j] = '\0';
}

void encode(const char *input, char *output, int shift) {
    char encryptedText[100];
    strcpy(encryptedText, input); 

    caesarEncrypt(encryptedText, shift);

    runLengthEncode(encryptedText, output);
}

void runLengthDecode(const char *input, char *output) {
    int i = 0, j = 0;
    while (input[i] != '\0') {
        char character = input[i++];
        int count = 0;

        while (input[i] >= '0' && input[i] <= '9') {
            count = count * 10 + (input[i] - '0');
            i++;
        }

        
        for (int k = 0; k < count; k++) {
            output[j++] = character;
        }
    }
    output[j] = '\0'; 
}


void caesarDecrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= ' ' && text[i] <= '~') {  
            text[i] = ((text[i] - ' ') - shift + 95) % 95 + ' ';
        }
    }
}

void decode(const char *input, char *output, int shift) {
    char decodedText[100];

    runLengthDecode(input, decodedText);
    strcpy(output, decodedText);
    caesarDecrypt(output, shift);
}

int main() {
    char text[100];
    char encodedText[100];
    char decodedText[100];
    int shift;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    printf("Enter shift (1-94): ");
    scanf("%d", &shift);

    if (shift < 1 || shift > 94) {
        printf("Shift must be between 1 and 94.\n");
        return 1;
    }
    encode(text, encodedText, shift);
    printf("Encoded text: %s\n", encodedText);
    decode(encodedText, decodedText, shift);
    printf("Decoded text: %s\n", decodedText);

    return 0;
}
