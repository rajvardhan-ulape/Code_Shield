#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

int validateLogin(char *username, char *password) {
    char validUsername[] = "CodeShield";
    char validPassword[] = "030717";
    
    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0)
        return 1; // Successful login
    else if (strcmp(username, validUsername) != 0)
        return 0; // Invalid username
    else
        return -1; // Invalid password
}

void getPassword(char *password, int maxLength) {
#ifdef _WIN32
    int i = 0;
    while (i < maxLength - 1) {
        char c = _getch();
        if (c == '\r')
            break;
        else if (c == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if (c != '\b') {
            printf("*");
            password[i++] = c;
        }
    }
    password[i] = '\0';
#else
    char *pass = getpass("Enter your password (masked): ");
    strncpy(password, pass, maxLength - 1);
#endif
}

int main() {
    char username[20];
    char password[20];
    int loggedIn = 0;
    char inputFileName[100];
    long fileSize;

    while (!loggedIn) {
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        getPassword(password, sizeof(password));

        int loginStatus = validateLogin(username, password);
        if (loginStatus == 1) {
            printf("\n________Login Successful!________\n");
            loggedIn = 1;
        } else if (loginStatus == 0) {
            printf("\nInvalid username. Access denied.\n");
        } else {
            printf("\nInvalid password. Access denied.\n");
        }
    }

    while (loggedIn) {
        int x;
        printf("\nPlease choose following options:\n");
        printf("1 for Encoding The Message.\n");
        printf("2 for Decoding The Message.\n");
        printf("0 to Exit.\n");
        scanf("%d", &x);

        FILE *inputFile, *outputFile;

        switch (x) {
            case 1:
                printf("Enter the input file name From which data is encoded : ");
                scanf("%s", inputFileName);
                inputFile = fopen(inputFileName, "r");
                if (inputFile == NULL) {
                    printf("Error opening the input file.\n");
                    break;
                }

                fseek(inputFile, 0, SEEK_END);
                fileSize = ftell(inputFile);
                rewind(inputFile);

                char *str = (char *)malloc((fileSize + 1) * sizeof(char));
                if (str == NULL) {
                    printf("Memory allocation failed.\n");
                    fclose(inputFile);
                    break;
                }

                fgets(str, fileSize + 1, inputFile);
                fclose(inputFile);

                for (int i = 0; i < fileSize; i++)
                    str[i] = str[i] + 3;
                printf("\nEncoded message is : %s\n", str);

                outputFile = fopen("output.txt", "a");
                if (outputFile == NULL) {
                    printf("Error opening the output file.\n");
                    break;
                }

                fprintf(outputFile, "%s", str);
                fclose(outputFile);
                free(str);
                break;

            case 2:
                printf("Enter the input file name From which data is  decoded: ");
                scanf("%s", inputFileName);
                inputFile = fopen(inputFileName, "r");
                if (inputFile == NULL) {
                    printf("Error opening the input file.\n");
                    break;
                }

                fseek(inputFile, 0, SEEK_END);
                fileSize = ftell(inputFile);
                rewind(inputFile);

                char *str_decoded = (char *)malloc((fileSize + 1) * sizeof(char));
                if (str_decoded == NULL) {
                    printf("Memory allocation failed.\n");
                    fclose(inputFile);
                    break;
                }

                fgets(str_decoded, fileSize + 1, inputFile);
                fclose(inputFile);

                for (int i = 0; i < fileSize; i++)
                    str_decoded[i] = str_decoded[i] - 3;
                printf("\nDecoded Message is: %s\n", str_decoded);

                outputFile = fopen("output.txt", "a");
                if (outputFile == NULL) {
                    printf("Error opening the output file.\n");
                    break;
                }

                fprintf(outputFile, "%s", str_decoded);
                fclose(outputFile);
                free(str_decoded);
                break;

            case 0:
                loggedIn = 0;
                printf("________Logout Successful________\n");
                break;

            default:
                printf("\nError: Invalid choice\n");
        }
    }

    return 0;
}
