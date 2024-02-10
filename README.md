# Matrix Operations Program

The purpose of this program is to perform different operations with matrices that are allocated dynamically. For this program, a vector of matrices called "arr" is used.

## `my_octave.c`:

### MAIN

In Main, it declares a character called 'c' that is used to identify the command being used. `*n` and `*m` represent two vectors that contain the dimensions of all the matrices. 'index' represents the index of a matrix, and 'capacitate' represents the number of matrices that are already allocated. The entire program is in an infinite while loop and must end with the 'Q' command. Inside the while loop, the 'c' character is scanned at the beginning to determine the next command. The program always checks if there is or isn't any more allocated space, and if not, it allocates it automatically. After that, there is a switch that contains all commands: L, D, P, C, T, O, Q, M, F, R, and S. I've created a library called my_octave.h that contains all commands.

## `my_octave.h`:

The functions `swap`, `mod`, `sum_term`, `max_numbers`, `read`, `print`, `allocation`, and `reallocation` are simple and useful functions. `swap` swaps values of two variables, `mod` is a modulo 10007 function, `sum_term` calculates the sum of the terms of a matrix, `max_numbers` returns the max of two numbers, and the `read` and `print` functions read and print a matrix or the dimensions. `Allocation` and `reallocation` allocate and reallocate dynamic memory for matrices and vectors.

### Case_L:

The 'L' command reads the dimension of a matrix, allocates memory for it, and reads the matrix.

### Case_D:

The 'D' command prints the dimension of a matrix with a given index or prints a message if the matrix does not exist.

### Case_P:

The 'P' command prints the matrix with the given index or prints a message if it does not exist.

### Case_C:

The 'C' command resizes the matrix with the given index or prints a message. It uses two auxiliary vectors called 'linii' and 'coloane', where 'linii' represents the rows of a matrix, and 'coloane' represents the columns of a matrix. The parameters for redimension are scanned in 'linii' and 'coloane', then an auxiliary matrix called 'new_matrix' is allocated and built. After this, the old matrix is freed, and the matrix with the given index points to the 'new_matrix'. In the end, the program frees the auxiliaries.

### Case_T:

The 'T' command transposes the matrix with the given index and saves it in the same place. It allocates a matrix with the dimensions of the maximum of the dimensions of the old matrix, then builds the transpose in the auxiliary matrix, frees the old matrix, allocates the new one, and changes the matrix values to the transpose values. In the end, the program frees the auxiliaries.

### Case_O:

The 'O' command changes the order of the matrices in the vector. It sorts ascending all the matrices by the sum of terms. It allocates two auxiliary vectors: 'vect1' and 'vect2', where one of the vectors contains the indexes, and the other one contains the sums. The program sorts them both by the second one, frees the second one, and builds the new order of the matrices and their dimensions using 'vect1', which contains the indexes sorted. In the end, the program frees all auxiliaries.

### Case_Q:

The 'Q' command frees all the matrices and the vector of matrices in the reverse order of the allocation to avoid memory leaks, then closes the program with 'exit(0)'.

### Case_M:

The 'M' command multiplies two matrices with the given indexes and saves the result into a new location. The algorithm is a basic multiplication algorithm.

### Case_F:

The 'F' command frees a matrix and ensures that the others are saved at consecutive indexes by moving all the matrices that were to the right of the given matrix one index to the left and decrementing the index.

### Case_R:

The 'R' command raises a given matrix to a given positive integer power in logarithmic time. It uses the 'power' function, which is a logarithmic algorithm. This algorithm allocates the 'result' matrix and sets it to the neutral element of matrix multiplication, In. Then, it allocates an auxiliary matrix called 'result2' to avoid modifying the 'arr' value. If 'pow' is an odd number, it saves in 'result2' and then in 'result' the result obtained by multiplying 'result' and the given matrix/the base. Else if 'pow' is even, the base is raised to the power of 2, and then 'pow' is divided by 2.

### Case_S:

The 'S' command multiplies two matrices with two given indexes using the Strassen algorithm, function 'S_recursiv'. The Strassen algorithm multiplies two matrices by breaking them into blocks. Assuming the dimensions are equal and already a power of 2 (let's say the dimensions equal to 'n'), 'n' is always divided by 2, and the big matrices that must be multiplied are divided into 4 blocks of 'n/2' each and stacked in 'aux1' and 'aux2' matrices. 'aux1' and 'aux2' represent two vectors of 4 matrices each, the first one for the first big matrix and the second one for the second big matrix. 'M' represents a vector of 7 matrices used for calculating multiplication on blocks. In the 'build_M' function, the matrices inside 'M' are calculated recursively. After calling the 'build_M' function, the program frees all the block matrices from 'aux1' and 'aux2', allocates 4 matrices 'C00', 'C01', 'C10', 'C11', then builds them. The 4 matrices represent the blocks of the future return matrix called 'C', which is allocated and built after.
Copyright Visanescu Bogdan-Emilian 2023-2024
