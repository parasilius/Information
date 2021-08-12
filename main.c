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