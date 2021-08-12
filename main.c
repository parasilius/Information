#include <stdio.h>

struct Profile
{
    char id;
    char firstName[20];
    char lastName[20];
    char email[50];
    char password[60];
};

// use CharMap to store each record of `code.dat`
struct CharMap {
    char encoded;
    char decoded;
};

int loadCharMaps(char *codesFileLocation, struct CharMap **maps);
int decodePasswords(char *profileBinFileLocation, struct CharMap *maps, int mapsCount);
int makeTextFile(char *profileBinFileLocation, char *profileTextFileLocation);

int loadCharMaps(char* codesFileLocation, struct CharMap** mapsAddress)
{
    FILE* fptr;
    fptr = fopen(codesFileLocation, "rb");
    if (fptr == NULL)
        return 0;
    
    char count; // char is 1 byte
    fread(&count, 1, 1, fptr);
    *mapsAddress = (struct CharMap*)malloc(count);
    if (*mapsAddress == NULL)
        return 0;
    
    fread(*mapsAddress, sizeof(struct CharMap), count, fptr);
    close(fptr);
    return count;
}