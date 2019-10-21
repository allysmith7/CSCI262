# Readme

This program runs a simple personality test to determine which of the personality types you are according to the Myers Briggs test.
To run the test, simply run `proj1.cpp` and follow the prompts.

## File Verification
For the part of the project where I had to come up with a test to verify the format of the `questions.txt` file, I decided to ensure that the `YES_OPTION` and `NO_OPTION` where both legitimate.
To do this, I read in the letters from the file, looped through a vector containing all possible letters that they could be, and compared them.
In the one loop, I checked if each letter in the vector was the same as the letters from the file.
If they were, I stored the value in a `bool`.
After the loop has completed, the program verifies that both letters were inside the list.
If they are not, the program breaks the loop and the user is prompted to provide a different questions file.