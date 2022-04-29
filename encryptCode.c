// ERROR: initial rand seed can write EOF or SUB_CHAR to file at beginning
// addRandTest: improve 'randomity' of the random value
             // based on rand() and data value

// checkStringEndsWith (replace "isTextFile()")

// always flip 5th bit of byte (create a ALWAYS_FLIP_STRING)
// never flip 3th bit of byte (create a NEVER_FLIP_STRING)

// create one (or more) characters that do not follow the same algorithm

// add additional random value to beginning of table


// create new form of character (non-ascii)
   // first ___ digits represent the manner that the bits are split in
      // apply other digits of the sin to represent this
   // first 2 digits represent type of data (letter, digit, punctuation, other)
   // if letter: next 6 bits represent letter *NEED TO MAKE USE OF ALL COMBINATIONS
   // if digit: next 4 bits represent digit * NEED TO MAKE USE OF ALL BIT COMBINATIONS
   // if punctuation: next 3? bits represent the punctuation character
   // otherwise: next 4? bits represent the punctuation character

      // create one or more common letters that do not follow the algorithm



///////////////////////// START OF PROGRAM ////////////////////////////////
// header files
#include<stdio.h>
#include<math.h>
#include "Console_IO_Utility.h"
#include "File_Input_Utility.h"
#include "File_Output_Utility.h"
#include <time.h> // for random seeding
#include <stdlib.h> // for abs()
#include <sys/time.h> // for time in miliseconds

// constants
typedef enum { DECRYPT, ENCRYPT } ControlCodes;
#define BITS_IN_BYTE 8
const int SEQUENCE_RESULT_LIMIT = 5;   // maximum value seed can be incremented by
const int CHARS_IN_BYTE = 256;         // all possible combinations in one byte
const char SUB_CHAR = 26;              // causes file to stop reading early
const int MATRIX_WIDTH = 3;
const int MATRIX_HEIGHT = 3;
const int BASE_FOR_EVALUATE = 9;       // base of the digits when evaluating matrix
const int MAX_ROWS_IN_ARR = 12;        // qunaitity of chars in bitArray
const int SHIFT_VAL = 2;               // for shiftData function: MUST BE 2

const int CHANGE_VAL = 68;             // for changing position in bitArray: MUST BE EVEN
const int CHANGE_VAL_BITS = 1;         // bits to shift char and potentially see CHANGE_VAL


typedef enum { SUBTRACTION, ADDITION } OPERATORS;

// forward declarations


/*
Name: 
Process: 
Function input/parameters: none
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
///////////////////////////// extraFunctions /////////////////////////////////

/*
Name: shiftData
Process: shifts odd values in a character in the direction specified SHIFT_VAL
         locations. Loops when index out of boundary. 
Function input/parameters: charVal (unsigned char), 
                           shiftDir (char *): "RIGHT" or "LEFT"
Function output/parameters: none
Function output/returned: charVal (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
unsigned char shiftData( unsigned char charVal, char *shiftDir );


/*
Name: getBitFromArray
Process: isolates desired character, gets the desired bit from that
Function input/parameters: bitArray (unsigned char *), charNum (int), bitNum (int)
Function output/parameters: none
Function output/returned: bitVal (int)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
int getBitFromArray( unsigned char *bitArray, int charNum, int bitNum );


/*
Name: moveToNextBitInArray
Process: uses diagonal algorithm to change the row and col indices
Function input/parameters: arrRowInd (int *), arrColInd (int *)
Function output/parameters: arrRowInd, arrColInd
Function output/returned: foundBit (bool)
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
bool moveToNextBitInArray( int *arrRowInd, int *arrColInd, unsigned char *bitArray );


/*
Name: placeBitInArray
Process: puts the inputed bit into the bit array
Function input/parameters: charNum (int), bitNum (int), bitVal (int)
Function output/parameters: bitArray (unsigned char *)
Function output/returned: value at the given location
Device input/keyboard: none
Device input/file: none
Dependencies: getBitFromArray
*/
void placeBitInArray( unsigned char *bitArray, int charNum, int bitNum, int bitVal );


/*
Name: printBitArray
Process: for every character in the array, prints binary representation of char
Function input/parameters: bitArray (unsigned char *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: array content
Dependencies: 
*/
void printBitArray( unsigned char *bitArray );

/*
Name: readBitArrayFromFile
Process: gets characters from file and inserts them into bitArray
Function input/parameters: none
Function output/parameters: bitArray (unsigned char *)
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
void readBitArrayFromFile( unsigned char *bitArray );


/*
Name: readNextBitFromFile
Process: finds the bit at current location, 
         moves to next location, 
         and gets another bitArray if necessary
Function input/parameters: bitArray (unsigned char *), arrRowIndex (int *), 
                           arrColIndex (int *)
Function output/parameters: none
Function output/returned: bitVal (int)
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
int readNextBitFromFile( unsigned char *bitArray, int *arrRowIndex, 
                                                            int *arrColIndex );

/*
Name: readRawCharacterFromFile
Process: fills one character with appropriate bits from file content
Function input/parameters: arrRowIndex (int *), arrColIndex (int *)
Function output/parameters: bitArray (unsigned char *)
Function output/returned: returnVal (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
unsigned char readRawCharacterFromFile( unsigned char *bitArray, 
                               int *arrRowIndex, int *arrColIndex );



/*
Name: writeBitArrayToFile
Process: gets character from bitArray and writes them to file
Function input/parameters: none
Function output/parameters: bitArray (unsigned char *)
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
void writeBitArrayToFile( unsigned char *bitArray );

/*
Name: writeNextBitToFile
Process: puts the bit into the corresponding location, 
         moves to next bit location
Function input/parameters: bitArray (unsigned char *), arrRowIndex (int *), 
                           arrColIndex (int *), bitVal (int)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
void writeNextBitToFile( unsigned char *bitArray, int *arrRowIndex, 
                         int *arrColIndex, int bitVal );


/*
Name: writeRawCharacterToFile
Process: puts character into corresponding elements of bitArray
Function input/parameters: bitArray (unsigned char *), arrRowIndex (int *), 
                           arrColIndex (int *), inChar (unsigned char)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/file: character content
Dependencies: 
*/
void writeRawCharacterToFile( unsigned char *bitArray, int *arrRowIndex, 
                              int *arrColIndex, unsigned char inChar );
///////////////////////////// extraFunctions // end ////////////////////////

/*
Name: decryptCharacterToFile
Process: Converts the character to non-ascii character, and combines with 
         function evaluated at the function seed. 
         Based on type of character, gets the spacing of the character. 
         Places bits of the non-ascii character into the file, placing random
         bits into the unused locations
Function input/parameters: stdChar (char), functionSeed (int *), bixIndex (int *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: srand, time, File_Input_Utility, File_Output_Utility, 
              encryptCharacterToFile, printf
*/
void decryptCharacterToFile( char fileChar, int *functionSeed, int *bitIndex, 
        int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter,
        unsigned char *bitArray, int *arrRowIndex, int *arrColIndex );

/*
Name: decryptFile
Process: decrypts the input file using algorithms. Writes results to output file
Function input/parameters: inputFileName (char *), outputFileName (char *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: encrypted message
Device output/file: decrypted message
Dependencies: getSeedFromFile, decryptCharacter, File_Input_Utility
*/
void decryptFile( char inputFileName[], char outputFileName[] );



/*
Name: encryptCharacterToFile
Process: Converts the character to non-ascii character, and combines with 
         function evaluated at the function seed. 
         Based on type of character, gets the spacing of the character. 
         Places bits of the non-ascii character into the file, placing random
         bits into the unused locations
Function input/parameters: stdChar (char), functionSeed (int *), bixIndex (int *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: srand, time, File_Input_Utility, File_Output_Utility, 
              encryptCharacterToFile, printf
*/
void encryptCharacterToFile( char fileChar, int *functionSeed, int *bitIndex, 
        int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter, 
        unsigned char *bitArray, int *arrRowIndex, int *arrColIndex );


/*
Name: encryptFile
Process: encodes a file using several algorithms
Function input/parameters: inputFileName (char *), outputFileName (char *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: input file contents
Device output/file: encoded document
Dependencies: 
*/
void encryptFile( char inputFileName[], char outputFileName[] );


/*
Name: evalueFunctionResult
Process: takes the function result, gets 9 digits (base 8) from the result, 
         stores them in 2D array, 
         evaluates the array as a matrix
Function input/parameters: functionResult (double)
Function output/parameters: none
Function output/returned: result of the matrix
Device input/keyboard: none
Device input/file: none
Dependencies: ???
*/
int evaluateFunctionResult( double functionResult );



/*
Name: evaluateFunctionSeed
Process: uses the seed to evaluate the hardcoded function
Function input/parameters: functionSeed (int)
Function output/parameters: none
Function output/returned: function result (double)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
double evaluateFunctionSeed( int *functionSeed, int *algorithmRowNum, 
                              int *algorithmSeriesNum, int *algorithmCounter );


/*
Name: findLastStringIndex
process: determines the last index of the string
Function input/parameters: string (char *)
Function output/parameters: none
Function output/returned: last index of the strings
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
int findLastStringIndex( char string[] );


/*
Name: formatFileCharacter
Process: switches bits in the file character if needed using the seeded function
Function input/parameters: fileChar (unsigned char), functionSeed (int)
Function output/parameters: none
Function output/returned: fileChar (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
unsigned char formatFileCharacter( unsigned char fileChar, int *functionSeed, 
        int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter );




/*
Name: getFileName
Process: prompts the user for a file name until they enter a .txt file
Function input/parameters: promptString (char *)
Function output/parameters: fileName (char *)
Function output/returned: none
Device input/keyboard: file name from user
Device input/file: none
Dependencies: Console_IO_Utility
*/
void getFileName( char promptString[], char fileName[] );


/*
Name: getHundrethsDigit
Process: 'shifts' the double parameter such that the hudreths place is in the one's
         converts digit to integer to remove values too low
         uses modulo operator to 
Function input/parameters: doubleVal (double)
Function output/parameters: none
Function output/returned: digitVal (int)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
int getHundrethsDigit( double doubleVal );


/*
Name: getNextFunctionSeedIncrementor
Process: finds the next term of the hardcoded pattern
Function input/parameters: rowNum (int), sequenceNum (int), counterVal (int)
Function output/parameters: none
Function output/returned: next term of the pattern algorithm
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
void getNextFunctionSeedIncrementor( int *rowNum, int *sequenceNum, 
                                                             int *counterVal );

/*
Name: getRandomBit
Process: uses the seeded function to create a random bit
Function input/parameters: functionSeed (int)
Function output/parameters: none
Function output/returned: zero or one (randomly)
Device input/keyboard: none
Device input/file: none
Dependencies: evaluateFunctionSeed
*/
int getRandomBit( int *functionSeed, int *algorithmRowNum, 
                              int *algorithmSeriesNum, int *algorithmCounter );


/*
Name: getSeedFromFile
Process: takes the first two characters in the file, 
         combines them to create the seed (integer)
Function input/parameters: none
Function output/parameters: none
Function output/returned: value of the seed (integer)
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
int getSeedFromFile();



/*
Name: getUserChoices
process: prompts user for choice of operations: encrypt or decrypt,
         processes answer and returns control code (ENCRYPT, DECRYPT)
         as appropriate,
         repeats prompt if incorrect user response
Function input/parameters: none
Function output/parameters: none
Function output/returned: encrypt or decrypt control code as specified
                          (ControlCodes)
Device input/file: none
Device output/monitor: none
Dependencies: Console I/O tools, isInString
*/
ControlCodes getUserChoice();


/*
Name: isInString
process: accepts a list of characters and one test character,
         reports if test character is in the given list
Function input/parameters: test string (const char []), test character (char)
Function output/parameters: none
Function output/returned: result of specified test (bool)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
bool isInString( const char testStr[], char testChar );

/*
Name: isTextFileName
Process: determines if the file name ends with .txt
Function input/parameters: fileName (char *)
Function output/parameters: none
Function output/returned: if the file ends with .txt (bool)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
bool isTextFileName( char fileName[] );



/*
Name: readEncryptedCharacterFromFile
Process: creates an integer to represent 24 bits in the file (3 characters), 
         reads the 3 characters from the file, and puts them into the integer
         identifies the value of the spacing bit markers, 
         uses spacing bit markers to located and put data bits into the 
                                                           encrypted character.
Function input/parameters: functionSeed (int), algorithmRowNum (int), 
                               algorithmSeriesNum (int), algorithmCounter (int)
Function output/parameters: none
Function output/returned: encryptedChar (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: ?
*/
unsigned char readEncryptedCharacterFromFile( int *functionSeed, 
        int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter, 
        unsigned char *bitArray, int *arrRowIndex, int *arrColIndex );


/*
Name: writeBinaryIntegerToFile
Process: converts the integer (16 bits) to two characters (8 bits each)
         writes both of the characters to the file
Function input/parameters: integer (int)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Device output/file: integer in binary (two characters) format
Dependencies: File_Input_Utility
*/
void writeBinaryIntegerToFile( int integer );


/*
Name: writeEncryptedCharacterToFile
Process: creates the randomized byte marker (for spacing), and writes it to the file
         iterates over two more characters,
         places encoded bits of the data where specified by byteMarker, 
         other locations are filled with random bits
Function input/parameters: encryptedByte (unsigned char), functionSeed (int)
        algorithmRowNum (int), algorithmSeriesnum (int), algorithmCounter (int)
Function output/parameters: none
Function output/returned: whether the encryption was successful
Device input/keyboard: none
Device input/file: none
Dependencies: File_Output_Utility
*/
bool writeEncryptedCharacterToFile( unsigned char encryptedByte, int *functionSeed, 
        int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter,
        unsigned char *bitArray, int *arrRowIndex, int *arrColIndex );


// main program
int main()
   {
    // initialize variables / function
       // initialize variables
    char inputFileName[ STD_STR_LEN ];
    char outputFileName[ STD_STR_LEN ];
    ControlCodes userChoice;


       // display the title
          // functions: printf()
    printf( "Decode and Encode Program\n" );
    printf( "=========================\n\n" );

    // get user input
       // ask user if they want to decode or encode
          // functions: getUserChoice()
    userChoice = getUserChoice();

       // check they want to decode
    if( userChoice == DECRYPT )
    {
          // ask for input file to be encoded
             // functions: getFileName()
       getFileName( "Enter the file containing encoded text: ", inputFileName );

          // ask for output file to be encoded to
             // functions: getFileName()
       getFileName( "Enter a file to write decoded text to: ", outputFileName );
    }

       // otherwise (encode)
    else
    {
          // ask for input file to be decoded
             // functions: getFileName()
       getFileName( "Enter the file containing standard text: ", inputFileName );

          // ask for output file to be decoded to
             // functions: getFileName()
       getFileName( "Enter a file to write encoded text to: ", outputFileName );
    }

    // skip a line
       // functions: printf
    printf( "\n" );

    // conduct processing

       // check user wanted to decrypt
    if( userChoice == DECRYPT )
    {
          // decrypt the file
             // functions: decryptFile()
       decryptFile( inputFileName, outputFileName );
    }

       // otherwise (encrypt)
    else
    {
          // encode the file
             // functions: encryptFile()
       encryptFile( inputFileName, outputFileName );
    }

    // display results

    // end program
       // tell user program ended
    printf( "Program End\n" );

       // return program success
    return 0;
   }

// OTHER FUNCTIONS: 








/*
Name: decryptFile
Process: decrypts the input file using algorithms. Writes results to output file
Function input/parameters: inputFileName (char *), outputFileName (char *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: encrypted message
Device output/file: decrypted message
Dependencies: getSeedFromFile, decryptCharacter, File_Input_Utility
*/
void decryptFile( char inputFileName[], char outputFileName[] )
   {
    // initialize variables
    unsigned char fileChar;
    int functionSeed, bitIndex, randomBitNum;
    int algorithmRowNum = 0, algorithmSeriesNum = 0, algorithmCounter = 0;
    unsigned char bitArray[ MAX_ROWS_IN_ARR ];
    int arrColIndex = 0, arrRowIndex = 0;

    // check input file opened successfully
       // functions: openInputFile()
    if( openInputFile( inputFileName ) )
    {
       // open the output file
          // functions: openOutputFile()
       openOutputFile( outputFileName );

       // get the function seed from the file
          // functions: getSeedFromFile()
       functionSeed = getSeedFromFile();

       // initialize the bit array
          // function: readBitArrayFromFile
       readBitArrayFromFile( bitArray );

       // tell user decrypting has begun
          // functions: printf()
       printf( "Decrypting %s to %s . . . ", inputFileName, outputFileName );

       // iterate to the end of the file
          // functions: checkForEndOfInputFile()
       while( !checkForEndOfInputFile() )
       {
          // read a character from the file
             // functions: readEncryptedCharacterFromFile()
          fileChar = readEncryptedCharacterFromFile( &functionSeed, 
                    &algorithmRowNum, &algorithmSeriesNum, &algorithmCounter, 
                    bitArray, &arrRowIndex, &arrColIndex );

          // decrypt the character to the file
             // functions: decryptCharacterToFile()
          decryptCharacterToFile( fileChar, &functionSeed, &bitIndex, 
                    &algorithmRowNum, &algorithmSeriesNum, &algorithmCounter, 
                    bitArray, &arrRowIndex, &arrColIndex );

          // iterate over bits that were generated to create byteMarker
          for( randomBitNum = 0; randomBitNum < BITS_IN_BYTE; randomBitNum++ )
          {
             // generate a random bit
             getRandomBit( &functionSeed, &algorithmRowNum, 
                                      &algorithmSeriesNum, &algorithmCounter );
          }


       }
 
       // close the input and output files
          // functions: closeInputFile(), closeOutputFile()
       closeInputFile();
       closeOutputFile();

       // tell user decrypting is done
          // functions: printf()
       printf( "done\n" );
    }

    // otherwise (unable to open input file)
    else
    {
       // tell user error (unable to open input file)
          // functions: printf()
       printf( "ERROR: unable to open \"%s\"\n", inputFileName );
    }

   }


/*
Name: decryptCharacterToFile
Process: Converts the character to non-ascii character, and combines with 
         function evaluated at the function seed. 
         Based on type of character, gets the spacing of the character. 
         Places bits of the non-ascii character into the file, placing random
         bits into the unused locations
Function input/parameters: stdChar (char), functionSeed (int), bixIndex (int *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: requires output file is open
Dependencies: formatFileCharacter, File_Output_Utility
*/
void decryptCharacterToFile( char fileChar, int *functionSeed, int *bitIndex, 
         int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter,
         unsigned char *bitArray, int *arrRowIndex, int *arrColIndex )
   {
    // initialize variables
    unsigned char unsignedFileChar;

    // convert to non-ascii format
       // functions: convertToNonAscii() // modify
    unsignedFileChar = fileChar;

    // format the file character
       // functions: formatFileCharacter()
    unsignedFileChar = formatFileCharacter( unsignedFileChar, functionSeed, 
                     algorithmRowNum, algorithmSeriesNum, algorithmCounter );

    // combine the bits to an array of 0s and 1s
       // functions: bitsToArray() // modify

    // if the character is not EOF and the file has not been ended yet
    if( unsignedFileChar != EOF + 256 && !checkForEndOfInputFile() )
    {
       // add the bits to the file
          // functions: writeBitsToFile() // modify
          // functions: writeCharacterToFile()
       writeCharacterToFile( unsignedFileChar );

    }
    else
    {
       
    }

   }


/*
Name: encryptCharacterToFile
Process: Converts the character to non-ascii character, and combines with 
         function evaluated at the function seed. 
         Based on type of character, gets the spacing of the character. 
         Places bits of the non-ascii character into the file, placing random
         bits into the unused locations
Function input/parameters: stdChar (char), functionSeed (int), bixIndex (int *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: requires output file is open
Dependencies: formatFileCharacter, File_Output_Utility
*/
void encryptCharacterToFile( char fileChar, int *functionSeed, int *bitIndex, 
         int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter, 
         unsigned char *bitArray, int *arrRowIndex, int *arrColIndex )
   {
    // initialize variables
// GUR: function that calls one function

    // convert to non-ascii format
       // functions: convertToNonAscii() // modify

    // format the file character
       // functions: formatFileCharacter()

    // get the spacing values // remember to include 'exceptions' // modify

    // calculate the quantity of random values needed // modify

    // calculate the total bits needed // modify

    // get the random bits // modify
       // functions: getRandomBit()

    // combine the bits to an array of 0s and 1s
       // functions: bitsToArray() // modify

    // add the bits to the file
       // functions: writEncryptedCharacterToFile()

    // write the encrypted character to the file
       // functions: writeEncryptedCharacterToFile()
    writeEncryptedCharacterToFile( fileChar, functionSeed, 
                      algorithmRowNum, algorithmSeriesNum, algorithmCounter, 
                      bitArray, arrRowIndex, arrColIndex );

   }









/*
Name: encryptFile
Process: encodes a file using several algorithms
Function input/parameters: inputFileName (char *), outputFileName (char *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: input file contents
Device output/file: encoded document
Dependencies: srand, time, File_Input_Utility, File_Output_Utility, 
              encryptCharacterToFile, printf
*/
void encryptFile( char inputFileName[], char outputFileName[] )
   {
    // initialize variables
    char fileChar;
    int functionSeed, bitIndex;
    int algorithmRowNum = 0, algorithmSeriesNum = 0, algorithmCounter = 0;
    unsigned char bitArray[ MAX_ROWS_IN_ARR ];
    int arrColIndex = 0, arrRowIndex = 0;

    // initialize the random seed for the function
       // functions: srand, rand, time
    srand( time(0) );
    functionSeed = rand();

    // check input file opened successfully
       // functions: openInputFile()
    if( openInputFile( inputFileName ) )
    {
       // tell user decrypting has begun
          // functions: printf()
       printf( "Encrypting %s to %s . . . ", inputFileName, outputFileName );

       // open the output file
          // functions: openOutputFile()
       openOutputFile( outputFileName );

       // write the initial function seed to the file
          // functions: writeBinaryIntegerToFile()
       writeBinaryIntegerToFile( functionSeed );

       // prime fileChar
       fileChar = readCharacterFromFile();

       // iterate to the end of the file
          // functions: checkForEndOfInputFile()
       while( !checkForEndOfInputFile() )
       {
          // encrypt the character to the file
             // functions: encryptCharacterToFile()
          encryptCharacterToFile( fileChar, &functionSeed, &bitIndex, 
                    &algorithmRowNum, &algorithmSeriesNum, &algorithmCounter, 
                    bitArray, &arrColIndex, &arrRowIndex );

          // read a character from the file
             // functions: readCharacterFromFile()
          fileChar = readCharacterFromFile();
       }

       // for every character in the bit array
       for( int count = 0; count < MAX_ROWS_IN_ARR / 2; count++ )
       {
          // encrypt EOF to file
          encryptCharacterToFile( EOF, &functionSeed, &bitIndex, 
                     &algorithmRowNum, &algorithmSeriesNum, &algorithmCounter, 
                     bitArray, &arrColIndex, &arrRowIndex );
       }

       // end the file
       writeCharacterToFile( EOF );

       // extra content in the bitArray does not matter. File already ended
 
       // close the input and output files
          // functions: closeInputFile(), closeOutputFile()
       closeInputFile();
       closeOutputFile();

       // tell user encrypting is done
          // functions: printf()
       printf( "done\n" );
    }

    // otherwise (unable to open input file)
    else
    {
       // tell user error (unable to open input file)
          // functions: printf()
       printf( "ERROR: unable to open \"%s\"\n", inputFileName );
    }

   }




/*
Name: evaluateFunctionResult
Process: takes the function result, gets 9 digits (base 9) from the result, 
         stores them in 2D array, 
         evaluates the array as a matrix
Function input/parameters: functionResult (double)
Function output/parameters: none
Function output/returned: result of the matrix
Device input/keyboard: none
Device input/file: none
Dependencies: ???
*/
int evaluateFunctionResult( double functionResult )
   {
    // initialize variables
    int digitNum, digitValue, rowNum = 0, colNum = 0;

// test
    int testReturn = 0;


    // get the absolute value of functionResult
    if( functionResult < 0 )
    {
       functionResult *= -1;
    }

    // for every digit  to be analyzed
    for( digitNum = 0; digitNum < MATRIX_WIDTH * MATRIX_HEIGHT; digitNum++ )
    {
       // get the digit from the result
          // move the targeted digit to the front of the decimal
       functionResult = BASE_FOR_EVALUATE * functionResult;

          // get the targeted digits
       digitValue = functionResult / 1;

          // remove the integer part from the function result
       functionResult = functionResult - digitValue;

       // increment the colIndex
       colNum++;

       // check the colIndex is too large
       if( colNum >= MATRIX_WIDTH )
       {
          // increment the rowIndex
          rowNum++;

          // reset the colIndex to 0
          colNum = 0;
       }

       testReturn += digitValue;			// altered function to only add 9 digits

    }

// test
    return testReturn;

   }



/*
Name: evaluateFunctionSeed
Process: uses the seed to evaluate the hardcoded function
Function input/parameters: functionSeed (int)
Function output/parameters: none
Function output/returned: function result (double)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
double evaluateFunctionSeed( int *functionSeed, int *algorithmRowNum, 
                               int *algorithmSeriesNum, int *algorithmCounter )
   {
    // initialize variables
    double result;

    // fid the result of the seeded function
    result = sin( *functionSeed );

    // get the next seed incrementor for the function
       // functions: getNextFunctionSeedIncrementor
    getNextFunctionSeedIncrementor( algorithmRowNum, algorithmSeriesNum, 
                                                            algorithmCounter );
    // increase the function seed
    *functionSeed = *functionSeed + *algorithmCounter % SEQUENCE_RESULT_LIMIT;

    // return the results of the function
    return result;
    
   }


/*
Name: findLastStringIndex
process: determines the last index of the string
Function input/parameters: string (char *)
Function output/parameters: none
Function output/returned: last index of the strings
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/
int findLastStringIndex( char string[] )
   {
    int index = 0;

    // iterate to end of string
    while( string[ index ] != '\0' )
    {
       // increase the count by 1
       index++;
    }

    // return the last index
    return index - 1;
   }


/*
Name: formatFileCharacter
Process: switches bits in the file character if needed using the seeded function
Function input/parameters: fileChar (unsigned char), functionSeed (int)
Function output/parameters: none
Function output/returned: fileChar (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: getRandomBit, (exclusive or, '^')
*/
unsigned char formatFileCharacter( unsigned char fileChar, int *functionSeed, 
         int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter )
   {
    // initialize variables
    int bitNum;
    unsigned char randomBit;

    // iterate over bits in the file character
    for( bitNum = 0; bitNum < BITS_IN_BYTE; bitNum++ )
    {
       // get a random bit
          // functions: getRandomBit()
       randomBit = getRandomBit( functionSeed, algorithmRowNum, 
                                        algorithmSeriesNum, algorithmCounter );

       // align the bit with the corresponding bit number (left to right)
       randomBit = randomBit << ( BITS_IN_BYTE - bitNum - 1 );

       // swap the bit if necessary // requires use of XOR
       fileChar = fileChar ^ randomBit;
    }

    // return the converted file character converted
    return fileChar;
   }




/*
Name: getFileName
Process: prompts the user for a file name until they enter a .txt file
Function input/parameters: promptString (char *)
Function output/parameters: fileName (char *)
Function output/returned: none
Device input/keyboard: file name from user
Device input/
Dependencies: Console_IO_Utility, printf
*/
void getFileName( char promptString[], char fileName[] )
   {
    // ask the user for a file name
       // functions: promptForString()
    promptForString( promptString, fileName );

    // while the file is not a text file
       // functions: isTextFileName()
    while( !isTextFileName( fileName ) )
    {
       // tell user invalid filename was offered
          // functions: printf()
       printf( "Invalid file name. Please enter a .txt file. \n" );
       
       // ask the user for a file name
          // functions: promptForString()
       promptForString( promptString, fileName );
    }
   }


/*
Name: getHundrethsDigit
Process: 'shifts' the double parameter such that the hudreths place is in the one's
         converts digit to integer to remove values too low
         uses modulo operator to 
Function input/parameters: doubleVal (double)
Function output/parameters: none
Function output/returned: digitVal (int)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
int getHundrethsDigit( double doubleVal )
   {
    // initialize variables
    int intVal;

    // shift double such that the hundreths is the in the ones place
    doubleVal = doubleVal * 100;

    // remove digits after the decimal
    intVal = doubleVal;

    // remove digits above the ones place
    intVal = intVal % 10; // GUR: magic value

    // return the integer value
    return abs( intVal );
   }



/*
Name: getNextFunctionSeedIncrementor
Process: finds the next term of the hardcoded pattern
Function input/parameters: rowNum (int), sequenceNum (int), counterVal (int)
Function output/parameters: all three
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
void getNextFunctionSeedIncrementor( int *rowNum, int *sequenceNum, 
                                                              int *counterVal )
   {
    // initialize variables
    int rowIncrementation, maxInRow, maxInSequence;

    // find the row incrementation
    rowIncrementation = *rowNum % ( SEQUENCE_RESULT_LIMIT - 1 ) + 1;

    // find the maximum value in the row
    maxInRow = *rowNum + SEQUENCE_RESULT_LIMIT - 1;

    // find the maximum value in the sequence
    maxInSequence = rowIncrementation * ( *sequenceNum + 1 );

    // find the new incremented value of the counter
    *counterVal = *counterVal + rowIncrementation;

    // check the new incremented value is too large for the sequence
    if( *counterVal > maxInSequence)
    {
       // increment the sequence number (by 1)
       *sequenceNum += 1;

       // check the new incremented value is too large for the row
       if( *counterVal > maxInRow )
       {
          // increment the row number
          *rowNum += 1;

          // reset the sequence number to 0
          *sequenceNum = 0;
       }

       // reset the new counter value to 0
       *counterVal = 0;
    }

   }


/*
Name: getRandomBit
Process: uses the seeded function to create a random bit
Function input/parameters: functionSeed (int)
Function output/parameters: none
Function output/returned: zero or one (randomly)
Device input/keyboard: none
Device input/file: none
Dependencies: evaluateFunctionSeed
*/
int getRandomBit( int *functionSeed, int *algorithmRowNum, 
                               int *algorithmSeriesNum, int *algorithmCounter )
   {
    // initialize variables
    double functionResult;
    int digitVal;

    // evaluate the function
       // functions: evaluateFunctionSeed()
    functionResult = evaluateFunctionSeed( functionSeed, algorithmRowNum, 
                                        algorithmSeriesNum, algorithmCounter );

    // get the hundreths place of the function
       // functions: getHundrethsDigit()
    digitVal = evaluateFunctionResult( functionResult );

    // check the digit's value is even
    if( digitVal % 2 == 0 )
    {
       // return 1
       return 1;
    }

    // return 0 (assume not even)
    return 0;
   }



/*
Name: getSeedFromFile
Process: takes the first two characters in the file, 
         combines them to create the seed (integer)
Function input/parameters: none
Function output/parameters: none
Function output/returned: value of the seed (integer)
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
int getSeedFromFile()
   {
    unsigned char firstChar, secondChar;
    int firstCharVal, secondCharVal;

    // get the first character from the file
    firstChar = readCharacterFromFile();

    // get the second character from the file
    secondChar = readCharacterFromFile();

    // convert the first and second characters to integers
    firstCharVal = firstChar;
    secondCharVal = secondChar;

    // find the weighted value for the first character
    firstCharVal = firstCharVal << BITS_IN_BYTE;

    // return the sum of the characters
    return firstCharVal + secondCharVal;
   }



/*
Name: getUserChoices
process: prompts user for choice of operations: encrypt or decrypt,
         processes answer and returns control code (ENCRYPT, DECRYPT)
         as appropriate,
         repeats prompt if incorrect user response // question
Function input/parameters: none
Function output/parameters: none
Function output/returned: encrypt or decrypt control code as specified
                          (ControlCodes)
Device input/file: none
Device output/monitor: none
Dependencies: Console I/O tools, isInString
*/
ControlCodes getUserChoice()
   {
    // initialize user input character
    char userChar;

    // get operation character from user
    userChar = promptForCharacter( "Operation: <D>ecrypt or <E>ncrypt? " ); // redundant?

    // as long as the user did not enter a valid operation:
    while( !isInString( "dDeE", userChar ) )
    {
       // get the next operation from user
          // functions: promptForCharacter()
       userChar = promptForCharacter( "Operation: <D>ecrypt or <E>ncrypt? " );
    }

    // check user intended decrypt
    if( userChar == 'd' || userChar == 'D' )
    {
       // return decrypt
       return DECRYPT;

    }

    // return encrypt (not decrypt)
    return ENCRYPT;

   }

/*
Name: isInString
process: accepts a list of characters and one test character,
         reports if test character is in the given list
Function input/parameters: test string (const char []), test character (char)
Function output/parameters: none
Function output/returned: result of specified test (bool)
Device input/file: none
Device output/monitor: none
Dependencies: none
*/
bool isInString( const char testStr[], char testChar )
   {
    // initialize variables
    int index = 0;
    char curChar;

    // prime current character
    curChar = testStr[ index ];

    // iterate to the end of the string
    while( testStr[ index ] != NULL_CHAR )
    {
       // check the corresponding character in testStr is the testChar
       if( curChar == testChar )
       {
          // return success
          return true;
       }

       // increase the index being analyzed
       index++;

       // get the next character (reprime)
       curChar = testStr[ index ];
    }

    // end for loop

    // return false (assume all tests failed)
    return false;
   }



/*
Name: isTextFileName
Process: determines if the file name ends with .txt
Function input/parameters: fileName (char *)
Function output/parameters: none
Function output/returned: if the file ends with .txt (bool)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
bool isTextFileName( char fileName[] )
   {
    // initialize variables
    int lastIndex;

    // find the last index of the fileName
    lastIndex = findLastStringIndex( fileName );

    // return file name is greater than 4 characters
    return lastIndex >= 4 // GUR: magic value (length of ".txt")

       // and last 4 characters are .txt
       && fileName[ lastIndex ] == 't'
       && fileName[ lastIndex - 1 ] == 'x'
       && fileName[ lastIndex - 2 ] == 't'
       && fileName[ lastIndex - 3 ] == '.'; // question: change to 'checkStringEndsWith' function?
   }


/*
Name: readEncryptedCharacterFromFile
Process: finds the spacing byte marker, 
         finds the next two characters containing data, 
         and combines them into a single integer
Function input/parameters: functionSeed (int), algorithmRowNum (int), 
                               algorithmSeriesNum (int), algorithmCounter (int)
Function output/parameters: none
Function output/returned: encryptedChar (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: File_Input_Utility, getRandomBit
*/
unsigned char readEncryptedCharacterFromFile( int *functionSeed, 
         int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter, 
         unsigned char *bitArray, int *arrRowIndex, int *arrColIndex )
   {
    // initialize variables
    unsigned char charOne, charTwo;
    int weightedCharOne, weightedCharTwo, dataInt, bitNum, bitIndex = 0;
    int dataBitVal, weightedBitVal;
    unsigned char returnChar = 0, shiftVal;

    // get the data characters from the file
       // functions: readCharacterFromFile()
    charOne = readRawCharacterFromFile( bitArray, arrRowIndex, arrColIndex );
    charTwo = readRawCharacterFromFile( bitArray, arrRowIndex, arrColIndex );

    // find the weighted values of the data characters
    weightedCharOne = charOne << BITS_IN_BYTE;
    weightedCharTwo = charTwo;

    // combine the data characters into a data integer
    dataInt = weightedCharOne + weightedCharTwo;

    // iterate over the spacing bits
    for( bitNum = 0; bitNum < BITS_IN_BYTE; bitNum++ )
    {
       // find the value of the bit at the bit index
       dataBitVal = dataInt >> ( 16 - bitIndex - 1 );
       dataBitVal %= 2;

       // find the weighted value of the bit (WRT result)
       weightedBitVal = dataBitVal << ( BITS_IN_BYTE - bitNum - 1 );

       // add the weighted value of the bit to the result
       returnChar += weightedBitVal;

       // find the shift value of the corresponding bit from byteMarker // GUR: outdated comment
       shiftVal = getRandomBit( functionSeed, algorithmRowNum, algorithmSeriesNum, 
                                                           algorithmCounter ) + 1;

       // find the index of the next data bit in the integer
       bitIndex = bitIndex + shiftVal;

    }

    // return the result (not failure)
    return returnChar;

   }


/*
Name: writeBinaryIntegerToFile
Process: converts the integer (16 bits) to two characters (8 bits each)
         writes both of the characters to the file
Function input/parameters: integer (int)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Device output/file: integer in binary (two characters) format
Dependencies: File_Input_Utility
*/
void writeBinaryIntegerToFile( int integer )
   {
    // initialize variables
    int firstCharVal, secondCharVal;
    unsigned char firstChar, secondChar;

    // calculate first character
    firstCharVal = integer >> BITS_IN_BYTE;

    // calculate second character
    secondCharVal = integer << BITS_IN_BYTE;
    secondCharVal = secondCharVal >> BITS_IN_BYTE;

    // convert characters to character format
    firstChar = firstCharVal;
    secondChar = secondCharVal;

    // write the characters to the file
       // functions: writeCharacterToFile()
    writeCharacterToFile( firstChar );
    writeCharacterToFile( secondChar );
   }


/*
Name: writeEncryptedCharacterToFile
Process: creates the randomized byte marker (for spacing), and writes it to the file
         iterates over two more characters,
         places encoded bits of the data where specified by byteMarker, 
         other locations are filled with random bits
Function input/parameters: encryptedByte (unsigned char), functionSeed (int)
        algorithmRowNum (int), algorithmSeriesnum (int), algorithmCounter (int)
Function output/parameters: none
Function output/returned: whether the encryption was successful
Device input/keyboard: none
Device input/file: none
Dependencies: File_Output_Utility
*/
bool writeEncryptedCharacterToFile( unsigned char encryptedByte, int *functionSeed, 
        int *algorithmRowNum, int *algorithmSeriesNum, int *algorithmCounter, 
        unsigned char *bitArray, int *arrRowIndex, int *arrColIndex )
   {
    // initialize variables
    int bitNum, randomBit, nextDataIndex = 0, encryptedCharIndex = 0;
    int transitionSpace, dataResult = 0, weightedBit;
    unsigned char byteMarker = 0, dataBit;
    unsigned char firstChar, secondChar;

    // geneate the byteMarker randomly
       // iterate over bits in byteMarker
    for( bitNum = 0; bitNum < BITS_IN_BYTE; bitNum++ )
    {
          // generate a random bit
             // functions: getRandomBit()
       randomBit = getRandomBit( functionSeed, algorithmRowNum, algorithmSeriesNum, 
                                                           algorithmCounter );

          // find the weighted value of the bit
       weightedBit = randomBit << ( BITS_IN_BYTE - bitNum - 1 );

          // add the weighted value of the bit to the byteMarker
       byteMarker += weightedBit;
    }

    encryptedByte = formatFileCharacter( encryptedByte, functionSeed, 
                       algorithmRowNum, algorithmSeriesNum, algorithmCounter );

    // iterate over bits in the dataInt
    for( bitNum = 0; bitNum < BITS_IN_BYTE * 2; bitNum++ ) // GUR: *2 is magic value?
    {
       // check the index is where the next data is located
       if( nextDataIndex == bitNum 

       // and encrypted character is not complete
       && encryptedCharIndex < BITS_IN_BYTE )

       {
          // get the next value of data
          dataBit = encryptedByte >> ( BITS_IN_BYTE - encryptedCharIndex - 1 );
          dataBit %= 2;

          // find the space to the next data
          transitionSpace = byteMarker >> ( BITS_IN_BYTE - encryptedCharIndex - 1 );
          transitionSpace = transitionSpace % 2 + 1;

          // find the index where the next data is located
          nextDataIndex += transitionSpace;

          // increment the encryptedCharIndex
          encryptedCharIndex++;
       }

       // otherwise (not data)
       else
       {
          // get a random value (store in dataBit)
             // functions: getRandomBit()
          dataBit = getRandomBit( functionSeed, algorithmRowNum, 
                                        algorithmSeriesNum, algorithmCounter );
// addRandTest
          dataBit = ( ( rand() >> 0 ) +             // sum a few digits of rand
                      ( rand() >> 3 ) + 
                      ( rand() >> 5 ) + 
                      ( rand() >> 6 ) + 
                        encryptedByte                 // include data
                        ) % 2;                          // range fit value to 0 or 1
// addRandTest
       }

       // find the weighted value of the bit
       weightedBit = dataBit << ( 16 - bitNum - 1 );

       // add the weighted value of the bit to the dataResult
       dataResult += weightedBit;
    }

    // find the first and second characters of the data result
    firstChar = dataResult >> BITS_IN_BYTE;
    secondChar = dataResult % CHARS_IN_BYTE;

    // display results and return success/failure

    // write the first and second result characters to the file
       // functions: rawCharacterToFile()		
    writeRawCharacterToFile( bitArray, arrRowIndex, arrColIndex, firstChar );
    writeRawCharacterToFile( bitArray, arrRowIndex, arrColIndex, secondChar );

    // return success
    return true;	// GUR: redundant

   }



//////////////////////////////// extraFunctions /////////////////////////////////
/*
Name: getBitFromArray
Process: isolates desired character, gets the desired bit from that
Function input/parameters: bitArray (unsigned char *), charNum (int), bitNum (int)
Function output/parameters: none
Function output/returned: bitVal (int)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
int getBitFromArray( unsigned char *bitArray, int charNum, int bitNum )
   {
    // initialize variables
    unsigned char targetChar;
    unsigned char returnBit;

    // find the character being isolated
    targetChar = bitArray[ charNum ];


    // isolate the bit
    returnBit = targetChar << ( bitNum );
    returnBit = returnBit >> ( BITS_IN_BYTE - 1 );

    // return the result
    return returnBit;
   }



/*
Name: moveToNextBitInArray
Process: uses diagonal algorithm to change the row and col indices
Function input/parameters: arrRowInd (int *), arrColInd (int *)
Function output/parameters: arrRowInd, arrColInd
Function output/returned: foundBit (bool)
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
bool moveToNextBitInArray( int *arrRowInd, int *arrColInd, unsigned char *bitArray )
   {
    // initialize variables
    int columnDifference;

    // check row and column values signify end of data
    if( *arrRowInd == MAX_ROWS_IN_ARR - 1 && *arrColInd == BITS_IN_BYTE - 1 )
      {
       // return failure
       return false;
      }

    // increment row index
    *arrRowInd += 1;

    // decrement column index
    *arrColInd -= 1;

    // check row index or column index is invalid
    if( *arrRowInd >= MAX_ROWS_IN_ARR || *arrColInd < 0 )
      {
       // check row index is less than BITS_IN_BYTE
       if( *arrRowInd < BITS_IN_BYTE 

         // AND
         &&

         // rowIndex is not too large
         *arrRowInd < MAX_ROWS_IN_ARR )

         {
          // set columnIndex to rowIndex
          *arrColInd = *arrRowInd;

          // reset rowIndex to 0
          *arrRowInd = 0;

         }

       // otherwise, check rowIndex is not too large
       else if( *arrRowInd < MAX_ROWS_IN_ARR )
         {
          // subtract BITS_IN_BYTE from the rowIndex
          *arrRowInd = *arrRowInd - BITS_IN_BYTE + 1;

          // set the column index to BITS_IN_BYTE - 1
          *arrColInd = BITS_IN_BYTE - 1;

         }

       // otherwise, assume top has been reached
       else
         {
          // calculate difference between BITS_IN_BYTE and colIndex
          columnDifference = BITS_IN_BYTE - *arrColInd - 2;

          // set rowInex to MAX_ROWS_IN_ARR - columnDifference
          *arrRowInd = MAX_ROWS_IN_ARR - columnDifference;

          // set colIndex to last column
          *arrColInd = BITS_IN_BYTE - 1;

         }
      }

    // check at last bit of character
    if( *arrColInd == BITS_IN_BYTE - 1 )
      {
       // check previous values represent potential EOF
       if( bitArray[ *arrRowInd ] == ( EOF + 256 - 1 ) ||
           bitArray[ *arrRowInd ] == ( EOF + 256 + 0 ) )   // GUR: not evidently clear
         {
// addRandTest
          // randomize the random seed twice
          rand();rand();
          // set the last bit to prevent EOF
          bitArray[ *arrRowInd ] = ( EOF - 1 );

          // instead, move to the next location
          return moveToNextBitInArray( arrRowInd, arrColInd, bitArray );

         }

       // check previous values represent potential SUB_CHAR
       if( bitArray[ *arrRowInd ] == ( SUB_CHAR + 0 ) ||
           bitArray[ *arrRowInd ] == ( SUB_CHAR + 1 ) )
         {
// addRandTest
          // randomize the random seed three times
          rand();rand();rand();

          // set the last bit to prevent SUB_CHAR
          bitArray[ *arrRowInd ] = SUB_CHAR + 1;

          // instead, move to the next location
          return moveToNextBitInArray( arrRowInd, arrColInd, bitArray );

         }

// addRandTest
          // check previous values represent chaneVal (first MAX digits) // assume CHANGE_VAL is even
          if( bitArray[ *arrRowInd ] >> CHANGE_VAL_BITS == ( CHANGE_VAL + 0 ) || 
              bitArray[ *arrRowInd ] >> CHANGE_VAL_BITS == ( CHANGE_VAL + 1 ) )
          {
             // place a random bit at the current location
             placeBitInArray( bitArray, *arrRowInd, *arrColInd, 
                              ( rand() + ( rand() >> 1 ) ) % 2 );

             // move to the next array, and return
             return moveToNextBitInArray( arrRowInd, arrColInd, bitArray );

          }

      }

    // return success
    return true;
   }




/*
Name: placeBitInArray
Process: puts the inputed bit into the bit array
Function input/parameters: charNum (int), bitNum (int), bitVal (int)
Function output/parameters: bitArray (unsigned char *)
Function output/returned: value at the given location
Device input/keyboard: none
Device input/file: none
Dependencies: getBitFromArray
*/
void placeBitInArray( unsigned char *bitArray, int charNum, int bitNum, int bitVal )
   {
    // initialize varaibles
    int resultVal;
    
    // find the value of the bit at the current location
    resultVal = getBitFromArray( bitArray, charNum, bitNum );

    // check bitVal is equal to resultVal
    if( bitVal == resultVal )
      {
       // assign resultVal to 0
       resultVal = 0;

      }

    // otherwise, check bitVal greater than resultVal
    else if( bitVal > resultVal )
      {
       // assign resultVal to 1
       resultVal = 1;

      }

    // otherwise (smaller than)
    else
      {
       // assign resultVal to -1
       resultVal = -1;

      }

    // align resultVal with correct bit
    resultVal = resultVal << ( BITS_IN_BYTE - 1 - bitNum );

    // add the value of the resultVal to the corresponding character
    bitArray[ charNum ] = bitArray[ charNum ] + resultVal;

   }


/*
Name: printBitArray
Process: for every character in the array, prints binary representation of char
Function input/parameters: bitArray (unsigned char *)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/monitor: array content
Dependencies: 
*/
void printBitArray( unsigned char *bitArray )
   {
    // initialize variables
    int charNum, bitNum;
    unsigned char bitVal;

    printf( "\n" );

    // for every character in the array
    for( charNum = 0; charNum < MAX_ROWS_IN_ARR; charNum++ )
      {
       // for every bit location in the array
       for( bitNum = 0; bitNum < BITS_IN_BYTE; bitNum++ )
         {
          // shift bit to the left
          bitVal = bitArray[ charNum ] << bitNum;

          // shift bit to the ones digit
          bitVal = bitVal >> ( BITS_IN_BYTE - 1 );

          // print the digit
             // function: printf
          printf( "%i", bitVal );
         }

       // signify end of character
          // function: printf
       printf( "\n" );
      }

    printf( "\n\n" );

   }

/*
Name: readBitArrayFromFile
Process: gets characters from file and inserts them into bitArray
Function input/parameters: none
Function output/parameters: bitArray (unsigned char *)
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
void readBitArrayFromFile( unsigned char *bitArray )
   {
    // initialize variables
    int charNum;

    // iterate over characters in bitArray
    for( charNum = 0; charNum < MAX_ROWS_IN_ARR; charNum++ )
      {
       // put character into corresponding index
       bitArray[ charNum ] = readCharacterFromFile();

      }

   }

/*
Name: readRawCharacterFromFile
Process: fills one character with appropriate bits from file content
Function input/parameters: arrRowIndex (int *), arrColIndex (int *)
Function output/parameters: bitArray (unsigned char *)
Function output/returned: returnVal (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
unsigned char readRawCharacterFromFile( unsigned char *bitArray, 
                               int *arrRowIndex, int *arrColIndex )
   {
    unsigned char bitVal, returnVal = 0;
    int bitNum;

    // iterate over bits in the character
    for( bitNum = 0; bitNum < BITS_IN_BYTE; bitNum++ )
      {
       // read a bit from the file
          // function: readNextBitFromFile
       bitVal = readNextBitFromFile( bitArray, arrRowIndex, arrColIndex );

       // find weighted value of the bit
       bitVal = bitVal << ( BITS_IN_BYTE - bitNum - 1 );

       // add weighted value of the bit to returnVal
       returnVal += bitVal;

      }

    // check the first bit of the data is 1
    if( returnVal >> ( BITS_IN_BYTE - 1 ) == 1 )
       {
        // shift the inChar to the left
        returnVal = shiftData( returnVal, "LEFT" );
       }

    // return the returnVal
    return returnVal;
   }


/*
Name: readNextBitFromFile
Process: finds the bit at current location, 
         moves to next location, 
         and gets another bitArray if necessary
Function input/parameters: bitArray (unsigned char *), arrRowIndex (int *), 
                           arrColIndex (int *)
Function output/parameters: none
Function output/returned: bitVal (int)
Device input/keyboard: none
Device input/file: none
Dependencies: getBitFromArray,moveToNextBitInArray
*/
int readNextBitFromFile( unsigned char *bitArray, int *arrRowIndex, 
                                                             int *arrColIndex )
   {
    // initialize variables
    int returnVal;

    // get bit from current location
       // function: getBitFromArray
    returnVal = getBitFromArray( bitArray, *arrRowIndex, *arrColIndex );

    // if unable to get next bit in array
       // function: moveToNextBitInArray
    if( !moveToNextBitInArray( arrRowIndex, arrColIndex, bitArray ) )
      {
       // get the bit array from the file
          // function: readBitArrayFromFile
       readBitArrayFromFile( bitArray );

       // set indices to 0
       *arrRowIndex = 0;
       *arrColIndex = 0;

      }

    // return the value
    return returnVal;

   }



/*
Name: writeBitArrayToFile
Process: gets character from bitArray and writes them to file
Function input/parameters: none
Function output/parameters: bitArray (unsigned char *)
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: 
*/
void writeBitArrayToFile( unsigned char *bitArray )
   {
    // initialize variables
    int charNum;

    // iterate over characters in bitArray
    for( charNum = 0; charNum < MAX_ROWS_IN_ARR; charNum++ )
      {
       // put character into corresponding index
       writeCharacterToFile( bitArray[ charNum ] );

      }

   }


/*
Name: writeNextBitToFile
Process: puts the bit into the corresponding location, 
         moves to next bit location
Function input/parameters: bitArray (unsigned char *), arrRowIndex (int *), 
                           arrColIndex (int *), bitVal (int)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
void writeNextBitToFile( unsigned char *bitArray, int *arrRowIndex, 
                         int *arrColIndex, int bitVal )
   {
    // put bitVal into bitArray
       // function: placeBitInArray
    placeBitInArray( bitArray, *arrRowIndex, *arrColIndex, bitVal );

    // if unable to move to next bit in array
       // function: moveToNextBitInArray
    if( !moveToNextBitInArray( arrRowIndex, arrColIndex, bitArray ) )
      {
       // write bit array to file
       writeBitArrayToFile( bitArray );

       // set indices to 0
       *arrRowIndex = 0;
       *arrColIndex = 0;

      }

   }


/*
Name: writeRawCharacterToFile
Process: puts character into corresponding elements of bitArray
Function input/parameters: bitArray (unsigned char *), arrRowIndex (int *), 
                           arrColIndex (int *), inChar (unsigned char)
Function output/parameters: none
Function output/returned: none
Device input/keyboard: none
Device output/file: character content
Dependencies: 
*/
void writeRawCharacterToFile( unsigned char *bitArray, int *arrRowIndex, 
                              int *arrColIndex, unsigned char inChar )
   {
    int bitNum;
    unsigned char bitVal;

    // check the first bit of the data is 1
    if( inChar >> ( BITS_IN_BYTE - 1 ) == 1 )
       {
        // shift the inChar to the right
        inChar = shiftData( inChar, "RIGHT" );
       }

    // iterate over bits in the character
    for( bitNum = 0; bitNum < BITS_IN_BYTE; bitNum++ ) 
      {
       // get the value of the bit
       bitVal = inChar << bitNum;
       bitVal = bitVal >> ( BITS_IN_BYTE - 1 );

       // write the bit to the file
          // function: writeNextBitToFile
       writeNextBitToFile( bitArray, arrRowIndex, arrColIndex, bitVal );

      }

   }




/*
Name: shiftData
Process: shifts odd values in a character in the direction specified SHIFT_VAL
         locations. Loops when index out of boundary. 
Function input/parameters: charVal (unsigned char), 
                           shiftDir (char *): "RIGHT" or "LEFT"
Function output/parameters: none
Function output/returned: charVal (unsigned char)
Device input/keyboard: none
Device input/file: none
Dependencies: none
*/
unsigned char shiftData( unsigned char charVal, char *shiftDir )
   {
    // initialize variables
    int bitCount = 0, bitIndex = 1;
    unsigned char bitVal, addVal;

    // check direction is RIGHT
    if( strcmp( shiftDir, "RIGHT" ) == 0 )
      {    
       // save rightmost odd bit in addVal
       addVal = ( charVal % 2 ) << ( BITS_IN_BYTE - 2 );
       
      }

    // otherwise
    else
      {
       // save leftmost odd bit in addVal
       addVal = charVal << 1;
       addVal = addVal >> ( BITS_IN_BYTE - 1 );
        
      }


    // iterate over odd indices
    while( bitCount < BITS_IN_BYTE / 2  - .001 )
      {
       // find the value of the bit at the index
       bitVal = charVal << bitIndex;
       bitVal = bitVal >> ( BITS_IN_BYTE - 1 );

       // weight the value of the bit
       bitVal = bitVal << ( BITS_IN_BYTE - 1 );
       bitVal = bitVal >> bitIndex;

       // subtract the bit value from charVal
       charVal -= bitVal;

       // check shiftDir is "RIGHT"
       if( strcmp( shiftDir, "RIGHT" ) == 0 )
         {
          // shift bit to right
          bitVal = bitVal >> SHIFT_VAL;

          // add SHIFT_VAL to the bitIndex
          bitIndex += SHIFT_VAL;          
          
         }

       // otherwise (assume shiftDir is "LEFT")
       else
         {
          // shift bit to left
          bitVal = bitVal << SHIFT_VAL;

          // add SHIFT_VAL to the bitIndex
          bitIndex += SHIFT_VAL;

         }

       // add the bit value to addVal
       addVal += bitVal;

       // increment the bitCount
       bitCount++;

      }

    // return the sum of charVal and addVal
    return charVal + addVal;
   }


