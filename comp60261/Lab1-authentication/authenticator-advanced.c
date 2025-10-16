#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>  // needed to use crypt()
#include <termios.h>
#include <stdlib.h>

//TODO complete here with the correct password in the
                      // format expected by crypt:
                      // <hash function id>$<salt>$<hash of the correct password>

void disable_echo() {
    struct termios config;
    tcgetattr(STDIN_FILENO, &config);  
    config.c_lflag &= ~ECHO;           
    tcsetattr(STDIN_FILENO, TCSANOW, &config); 
}

void enable_echo() {
    struct termios config;
    tcgetattr(STDIN_FILENO, &config);   
    config.c_lflag |= ECHO;             
    tcsetattr(STDIN_FILENO, TCSANOW, &config); 
}

int main(int argc, char *argv[]) {
    if (argc != 3){
        fprintf(stderr, "Enter: %s <path to password file> <username> \n", argv[0]);
        return 1;
    }
    
    const char *file_path = argv[1];
    const char *username = argv[2];
    
    FILE *file = fopen(file_path, "r");
    
    if(!file){
        perror("Error opening password file.");
        return 1;
    }
    
    char line[512];
    char db_hash[256] = "";
    int auth = 0;
    
    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        
        char *file_username = strtok(line, ":");
        char *file_hash = strtok(NULL, ":");
        
        if(file_username && file_hash && strcmp(file_username, username) == 0){
            strcpy(db_hash, file_hash);
            auth = 1;
            break;
        }
    }
    
    fclose(file);
    
    if(!auth){
        printf("User %s is not found in Authentication Database.\n", username);
        return 1;
    }

    char attempt[100];
    
    printf("Please input your password: \n");
    
    disable_echo();
    char *r = fgets(attempt, sizeof(attempt), stdin);
    enable_echo();
    
    printf("\n");
    
    if(!r)
        return -1; // problem with fgets
    
    // remove the carriage return character from the attempt string
    attempt[strcspn(attempt, "\n")] = 0;

    // TODO complete here:
    // 1. Call crypt to compute the password attempt hash
    char *attempt_hash = crypt(attempt, db_hash);
    // 2. Call strcmp to compare it to the ground truth (PASSWORD_HASH)
    // 3. Use printf to print "Authentication successful!\n" if the correct
    //    password was entered, or "Wrong password.\n" if not
    if(strcmp(attempt_hash, db_hash) == 0) {
        printf("Authentication successful!\n");
    } else {
        printf("Wrong password.\n");
    }

    return 0;
}


