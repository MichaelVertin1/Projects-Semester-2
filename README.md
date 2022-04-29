# Projects-Semester-2
Projects created during my second semester of experience coding. 

The intent of this project is to encrypt data in a way that every bit has a 50% chance of being 1 or 0. Due to seeding with time, there are 2^15, or 32768 unique encrypted forms of any given text file. I am planning to increase the number of possible forms.

1. Use of function with random starting seed. For every bit in the file, the bit is flipped if the hundredths place of the function result is odd.

2. Added a bit marker. Each character is now represented by two characters. The bit marker (not present in the file) is found by calling the function 8 times. Each call describes where one bit of data is located. Spaces unoccupied by data are filled with random bits, also using the function.

3. Created non-repeating pattern to increment the seed of the function. Previously the function's seed increased by one every call, which may cause repetition in the function's results.

4. Rather than reading and writing the decrypted characters directly to/from the file, applied diagonal reading idea introduced in CS136 course. Twelve characters are placed into an array, called bitArray, and values are read/written by moving diagonally down-left through the array.

Problems Encountered: EOF and substitute character were causing my code to stop reading early. During the first three steps, I used a FAIL_BYTE to replace these characters, and would regenerate the data randomly until a valid character was attained. On step 4, bits can be accounted for individually. On the last bit of each character in the bitArray, if the other 7 bits could result in EOF or SUB_CHAR, I inserted the bit that prevented this, and skipped over the value of that bit.

After these four steps, there is still a finite amount of function output combinations (determined by the first two characters of the file). With many encrypted files of the same time seed, a person/program could recognize that half the data (the randomly generated bits), are always the same, and identify the location of the data. To reduce this effect, I shifted odd bits if the first bit of the data is 1. However, this made the issue worse. Now there are two possible patterns, that can be combined to directly decrypt a large portion of the data. Noting that randomly generated bits are a major issue, I chose to use the rand() function to generate these bits. In order to prevent predictability of rand(), I called rand() in various manners (ie.( (rand()>>0+(rand()>>3)+(rand()>>5)+(rand()>>6)+encryptedByte) % 2; ), and when I encountered EOF and SUB_CHAR. I do not have experience in this subject, although it would appear to be significantly more difficult to decrypt.

There is the still the problem of having two encrypted text files with the same seed, and very similar original content. I have not yet accounted for this, although an idea I have is 'reseeding' the function several times within the encryption. I can attempt to create a time struct and access milliseconds from it after running short code segments that have inconsistent time durations. Additionally, because I need the code to last a significant time, I can implement rand() excessively throughout the segment.
