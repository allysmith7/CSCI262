Cole Smith
Lab 06 - 09/27/2019
Egyptian Multiplication

In this lab, the program prompts the user for two positive integers and mulitplies them together using the "Egyptian method."

The two unsigned ints are passed into a function called egyptianMultiplication() that first determines the greater of
the two variables and stores them in variables that are more easily read as such.

Then, the function repeatedly adds the values to a vector, each time dividing the lesser by 2 and multiplying the
by 2, before adding them again. This is repeated until the lesser variable == 1.

After this, the function loops through the left vector, checking each value to be even or odd. If it is even, an
iterator is made and incremented until it points to the even value we had found, aka it has a matching index.

This index is erased from both the right and left index in order to follow the rules of the Egyptian multiplication system.

After this, the values in the right vector are summed and the answer is printed.