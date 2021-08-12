#include <stdio.h>
#include <malloc.h>

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

int main(void)
{
    struct CharMap* maps;
    int mapsCount = loadCharMaps("code.dat", &maps);
    if (!decodePasswords("profiles.dat", maps, mapsCount))
    {
        printf("Error in decoding passwords!\n");
        return 0;
    }
    if (!makeTextFile("profiles.dat", "profiles.txt"))
    {
        printf("Error in making text file!\n");
        return 0;
    }
    free(maps);
    return 0;
}

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

int decodePasswords(char* profileBinFileLocation, struct CharMap* maps, int mapsCount)
{
    FILE* fptr;
    fptr = fopen(profileBinFileLocation, "rb+");
    if (fptr == NULL)
        return 0;
    
    struct Profile profile;
    while (fread(&profile, sizeof(struct Profile), 1, fptr) != 0)
    {
        for (unsigned int i = 0; profile.password[i]; ++i)
            for (unsigned int j = 0; j < mapsCount; ++j)
                if (profile.password[i] == maps[j].encoded)
                {
                    printf("%c", maps[j].decoded);
                    profile.password[i] = maps[j].decoded;
                }
        fseek(fptr, -sizeof(struct Profile), SEEK_CUR);
        fwrite(&profile, sizeof(struct Profile), 1, fptr);
    }
    close(fptr);
    return 1;
}

int makeTextFile(char* profileBinFileLocation, char* profileTextFileLocation)
{
    FILE* bfptr;
    bfptr = fopen(profileBinFileLocation, "rb");
    if (bfptr == NULL)
        return 0;
    FILE* tfptr;
    tfptr = fopen(profileTextFileLocation, "w");
    if (tfptr == NULL)
        return 0;

    struct Profile profile;
    while (fread(&profile, sizeof(struct Profile), 1, bfptr) != 0)
        fprintf(tfptr, "%d %s %s %s %s\n", profile.id, profile.firstName, profile.lastName, profile.email, profile.password);
    close(tfptr);
    close(bfptr);
    return 1;
}