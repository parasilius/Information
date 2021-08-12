# Information
In this problem we aim to extract the users' information and save it as text.
## Input files
Suppose these files are in the same directory as your executable program:  
+ `profiles.dat`: This is a binary file and each record in it corresponds to a 
specific user. Each record consists of:  
+ id(a 1 byte number)
+ first name(a 20 byte string)
+ last name(a 20 byte string)
+ email(a 50 byte string)
+ password(a 60 byte string)
+ `codes.dat`: This is a binary file. The first byte is a number which 
specifies the number of codes, and is followed by the codes themselves. 
Each code consists of:  
+ encoded(a character)
+ decoded(a character)
## Extracting & Saving Users' Information
First you have to read the users' information from `profiles.dat`. The users' 
passwords are decoded and so in order to decode them. you have to:  
+ Read the codes file and save it to the memory.
+ For all users, replace each character in password with its corresponding 
decoded character, if there exists one, else use the character itself.
+ Update each users' record in `profiles.dat`, so that their passwords are 
decoded.  
After doing the above steps, read the updated users' information from 
`profiles.dat` and save it as a text-file in a file named `profiles.txt`.  
## Implementation
YOu have to use the following functions and structures for implementing the 
program:  
```C
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
```
## Functions
+ `loadCharMaps`: This function reads the codes from the input file and saves 
them into the `maps` array. If there exists an error(such as in reading the 
file, dynamic memory allocation or...) returns 0, else returns the length of 
`maps`.
+ `decodePasswords`: This function reads each users' information, decodes their
 password and updates them in the same input file. If there exists an error 
returns 0, else returns 1. Note that after reading and decoding each record an
 update should be done before reading the next record.
+ `makeTextFile`: This function reads the updated users' information from the 
input file and saves it in another file. Same as above, if there exists an 
error returns 0, else returns 1.
## Extra Notes
+ You can define extra functions for the sake of your own convenience.
+ Use dynamic memory allocation to create the `CharMap` array and remember to 
free the allocated memory before the program terminates.
+ While reading the `profiles.dat` file the number of useres in it is unknows, 
so while there exists data to be read from the file, the program has to 
continue reading. For this you can make use of `fread`'s output which is a 
number of type `int`. If there was no data to be read, it returns 0. For more 
information refer to ![this link](https://en.cppreference.com/w/cpp/io/c/fread).
+ The `profiles.dat` file in this repository is not modified, i.e. it is the 
same original file before running the program.
## Sample Output
```
49 Jacob Allahyari jacoball@gmail.com vH#yRHcM#HNARRwo#d
50 Scarlett Mohammadpour sc.mohammadpour@gmail.com Akjd4qnR@oxi
51 Jane Salavati janesal@yahoo.com YHRYHRY12N
52 Samuel Shakeri samuel@aut.ac.ir 1N68RA@MHl
53 Gal Hooshmand hooshmand@aut.ac.ir iM@c49zH8N7Mqw
```
