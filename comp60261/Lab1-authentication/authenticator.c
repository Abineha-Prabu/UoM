#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>  // needed to use crypt()

#define PASSWORD_HASH "$6$saltsalt$VEG7f44XjqiQeZMvzRMUwp4GKBUXea7E7.PoPcvtORyPuiLNY51CN..Qa6zZjz35Im4bEh.cEWLMiqAAsnsRn."// TODO complete here with the correct password in the
                      // format expected by crypt:
                      // <hash function id>$<salt>$<hash of the correct password>

int main() {
    char attempt[100];
    char *attempt_hash;
    
    printf("Please input your password: \n");
    char *r = fgets(attempt, sizeof(attempt), stdin);
    if(!r)
        return -1; // problem with fgets
    
    // remove the carriage return character from the attempt string
    attempt[strcspn(attempt, "\n")] = 0;

    // TODO complete here:
    // 1. Call crypt to compute the password attempt hash
    attempt_hash = crypt(attempt, "$6$saltsalt$");
    // 2. Call strcmp to compare it to the ground truth (PASSWORD_HASH)
    // 3. Use printf to print "Authentication successful!\n" if the correct
    //    password was entered, or "Wrong password.\n" if not
    if(strcmp(attempt_hash, PASSWORD_HASH) == 0) {
        printf("Authentication successful!\n");
    } else {
        printf("Wrong password.\n");
    }

    return 0;
}


