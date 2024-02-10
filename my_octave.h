// Copyright Visanescu Bogdan-Emilian 313CA 2023-2024
#include <stdio.h>
#include <stdlib.h>
void build_M(int n, int ***M, int ***aux1, int ***aux2);
void free_matrix(int **matrix, int n);
void allocation_matrix(int n, int m, int ***arr);
// swap function
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// module function that esnure the int values of a matrix
int mod(int n)
{
	n = n % 10007;
	if (n < 0)
		n += 10007;
	return n;
}

// the sum of the terms of a matrix
void sum_term(int *n, int *m, int ***arr, int index, int *vect2)
{
	for (int i = 0; i <= index; i++) {
		for (int j = 0; j < n[i]; j++) {
			for (int k = 0; k < m[i]; k++)
				vect2[i] += arr[i][j][k];
		}
		vect2[i] = mod(vect2[i]);
	}
}

// returns the max value of two numbers
int max_numbers(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

// allocates one term for an array
int *allocation_nm(void)
{
	int *aux = (int *)malloc(1 * sizeof(int));
	if (!aux)
		exit(-1);
	return aux;
}

// realocates an array
int *reallocation_nm(int *nm, int capacitate)
{
	int *aux = (int *)realloc(nm, capacitate * sizeof(int));
	if (!aux)
		exit(-1);
	return aux;
}

// allocates an array of pointers
int ***allocation_array2(int n)
{
	int ***aux = (int ***)malloc(n * sizeof(int **));
	if (!aux)
		exit(-1);
	return aux;
}

// realocates an array
int ***reallocation_array(int ***arr, int capacitate)
{
	int ***aux = (int ***)realloc(arr, capacitate * sizeof(int **));
	if (!aux)
		exit(-1);
	return aux;
}

// reads a matrix n x m
void read_matrix(int n, int m, int **arr)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &arr[i][j]);
}

// prints a matrix n x m
void print_matrix(int n, int m, int **arr)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
}

// reads the dimenstions in vectors
void read_nm(int *n, int *m, int index)
{
	scanf("%d ", &n[index]);
	scanf("%d ", &m[index]);
}

// prints the dimensions of a matrix
void print_nm(int *n, int *m, int index)
{
	printf("%d ", n[index]);
	printf("%d\n", m[index]);
}

// allocates a vector of n ints
int *allocation_vector(int n)
{
	int *aux = (int *)calloc(n, sizeof(int));
	if (!aux)
		exit(-1);
	return aux;
}

// Reading and allocating new matrix command
void case_L(int *n, int *m, int ***arr, int *index)
{
	(*index)++;
	read_nm(n, m, *index);
	allocation_matrix(n[*index], m[*index], &arr[*index]);
	read_matrix(n[*index], m[*index], arr[*index]);
}

// printing the dimensions of a given matrix command
void case_D(int *n, int *m, int index)
{
	int k;
	scanf("%d", &k);
	if (k > index || k < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	print_nm(n, m, k);
}

// printing a given matrix command
void case_P(int *n, int *m, int ***arr, int index)
{
	int k;
	scanf("%d", &k);
	if (k > index || k < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	print_matrix(n[k], m[k], arr[k]);
}

// resizing of a given matrix
void case_C(int *n, int *m, int ***arr, int index)
{
	int **new_matrix, k;
	int nrlinii, nrcoloane;
	// scans the new dimensions and parameters of the matrix
	scanf("%d", &k);
	scanf("%d", &nrlinii);
	int *linii = allocation_vector(nrlinii);
	for (int i = 0; i < nrlinii; i++)
		scanf("%d", &linii[i]);
	scanf("%d", &nrcoloane);
	int *coloane = allocation_vector(nrcoloane);
	for (int i = 0; i < nrcoloane; i++)
		scanf("%d", &coloane[i]);
	if (k > index || k < 0) {
		printf("No matrix with the given index\n");
		free(linii);
		free(coloane);
		return;
	}
	// allocates the new size of the matrix
	allocation_matrix(nrlinii, nrcoloane, &new_matrix);
	// builds the new matrix
	for (int i = 0; i < nrlinii; i++)
		for (int j = 0; j < nrcoloane; j++)
			new_matrix[i][j] = arr[k][linii[i]][coloane[j]];
	// frees the old matrix
	free_matrix(arr[k], n[k]);
	// changes the matrix
	arr[k] = new_matrix;
	n[k] = nrlinii;
	m[k] = nrcoloane;
	free(linii);
	free(coloane);
}

// transpose of a given matrix
void case_T(int ***arr, int *n, int *m, int index)
{
	int k, **aux;
	scanf("%d", &k);
	if (k > index || k < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	// allocates a big size for the transpose
	int maxim = max_numbers(n[k], m[k]);
	allocation_matrix(maxim, maxim, &aux);
	// builds the transpose
	for (int i = 0; i < n[k]; i++)
		for (int j = 0; j < m[k]; j++)
			aux[j][i] = arr[k][i][j];
	// frees the old matrix and allocates the new one
	free_matrix(arr[k], n[k]);
	allocation_matrix(m[k], n[k], &arr[k]);
	// changes the matrix to its transpose
	for (int i = 0; i < m[k]; i++)
		for (int j = 0; j < n[k]; j++)
			arr[k][i][j] = aux[i][j];
	swap(&n[k], &m[k]);
	// frees the transpose
	free_matrix(aux, maxim);
}

// ascending sort by sum of terms
void case_O(int *n, int *m, int ***arr, int index)
{	// allocates 2 vectors
	int *vect1 = allocation_vector(index + 1);
	int *vect2 = allocation_vector(index + 1);
	// one of the vectors contains the indexes and the other one the sums
	for (int i = 0; i <= index; i++)
		vect1[i] = i;
	sum_term(n, m, arr, index, vect2);
	// sorting them both by the second one
	for (int i = 0; i <= index; i++) {
		for (int j = 0; j <= index - i - 1; j++) {
			if (vect2[j] > vect2[j + 1]) {
				swap(&vect2[j], &vect2[j + 1]);
				swap(&vect1[j], &vect1[j + 1]);
			}
		}
	}
	free(vect2);
	// building the new order
	int ***arr_nou = allocation_array2(index + 1);
	for (int i = 0; i <= index; i++)
		arr_nou[i] = arr[vect1[i]];
	for (int i = 0; i <= index; i++)
		arr[i] = arr_nou[i];
	int *n_nou = allocation_vector(index + 1);
	int *m_nou = allocation_vector(index + 1);
	for (int i = 0; i <= index; i++)
		n_nou[i] = n[vect1[i]];
	for (int i = 0; i <= index; i++)
		m_nou[i] = m[vect1[i]];
	for (int i = 0; i <= index; i++) {
		n[i] = n_nou[i];
		m[i] = m_nou[i];
	}
	// free all auxiliary things
	free(arr_nou);
	free(n_nou);
	free(m_nou);
	free(vect1);
}

// frees all the memory and closes the program
void case_Q(int *n, int *m, int ***arr, int index)
{
	for (int i = 0; i <= index; i++) {
		for (int j = 0; j < n[i]; j++)
			free(arr[i][j]);
		free(arr[i]);
	}
	free(arr);
	free(n);
	free(m);
	exit(0);
}

// multiplies 2 given matrixes
void case_M(int *n, int *m, int ***arr, int *index)
{
	int k1, k2, sum = 0;
	scanf("%d", &k1);
	scanf("%d", &k2);
	if (k1 > *index || k1 < 0 || k2 > *index || k2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (m[k1] != n[k2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	(*index)++;
	n[*index] = n[k1];
	m[*index] = m[k2];
	// allocates the new matrix
	allocation_matrix(n[k1], m[k2], &arr[*index]);
	// multiplies 2 matrixes and puts the result into the new one
	for (int i = 0; i < n[k1]; i++)
		for (int j = 0; j < m[k2]; j++) {
			for (int k = 0; k < n[k2]; k++)
				sum += mod(arr[k1][i][k] * arr[k2][k][j]);
			arr[*index][i][j] = mod(sum);
			sum = 0;
		}
}

// frees one matrix and move some of them to the left
void case_F(int *n, int *m, int ***arr, int *index)
{
	int k;
	scanf("%d", &k);
	if (k > *index || k < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	// frees the given matrix
	free_matrix(arr[k], n[k]);
	// moves the ones that are in the right one index to the left
	for (int i = k + 1; i <= *index; i++) {
		arr[i - 1] = arr[i];
		n[i - 1] = n[i];
		m[i - 1] = m[i];
	}
	(*index)--;
}

// logaritmic raise algoritm
void power(int n, int ***arr, int pow, int kr)
{	// allocates the result matrix and sets it to In
	int sum = 0;
	int **rezult = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++) {
		rezult[i] = (int *)calloc(n, sizeof(int));
		rezult[i][i] = 1;
	}
	// this is an auxiliary matrix
	int **rezult2 = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++)
		rezult2[i] = (int *)calloc(n, sizeof(int));
	// logaritmic raise algoritm for a number to a pow addapted for matrixes
	while (pow != 0) {
		if (pow % 2 != 0) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					for (int k = 0; k < n; k++)
						sum += mod(mod(rezult[i][k]) * mod(arr[kr][k][j]));
					rezult2[i][j] = mod(sum);
					sum = 0;
				}

			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
					rezult[i][j] = rezult2[i][j];
					rezult2[i][j] = 0;
				}
		}

		sum = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++)

					sum += mod(mod(arr[kr][i][k]) * mod(arr[kr][k][j]));
				rezult2[i][j] = mod(sum);
				sum = 0;
			}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				arr[kr][i][j] = rezult2[i][j];
				rezult2[i][j] = 0;
			}
		pow /= 2;
	}
	// putts the result in place and frees auxiliaries
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			arr[kr][i][j] = rezult[i][j];
		free(rezult[i]);
		free(rezult2[i]);
	}
	free(rezult);
	free(rezult2);
}

// raise a given matrix to a given power in logaritmic time
void case_R(int *n, int *m, int ***arr, int index)
{
	int kr, pow;
	scanf("%d", &kr);
	scanf("%d", &pow);
	if (kr > index || kr < 0) {
		printf("No matrix with the given index\n");
		return;
	}
	if (pow < 0) {
		printf("Power should be positive\n");
		return;
	}
	if (n[kr] != m[kr]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	power(n[kr], arr, pow, kr);
}

// allocates a matrix
void allocation_matrix(int n, int m, int ***arr)
{
	(*arr) = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++)
		(*arr)[i] = (int *)calloc(m, sizeof(int));
}

// frees a matrix
void free_matrix(int **matrix, int n)
{
	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

// adds or substracts 2 matrixes
void suma(int n, int **arr1, int **arr2, int ***s, int x)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (x == 0)
				(*s)[i][j] = arr1[i][j] + arr2[i][j];
			else
				(*s)[i][j] = arr1[i][j] - arr2[i][j];
		}
}

// algoritm of Strassen
int **S_recursiv(int n, int **A, int **B)
{
	if (n == 1) {
		int **C;
		allocation_matrix(1, 1, &C);
		C[0][0] = mod(mod(A[0][0]) * mod(B[0][0]));
		return C;
	}

	n /= 2;
	// allocates 2 auxiliary vectors of matrixes
	int ***aux1 = (int ***)calloc(4, sizeof(int **));
	int ***aux2 = (int ***)calloc(4, sizeof(int **));
	for (int i = 0; i < 4; i++) {
		allocation_matrix(n, n, &aux1[i]);
		allocation_matrix(n, n, &aux2[i]);
	}
	// splits the big matrixes into for blocks each
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < 4; k++) {
				aux1[k][i][j] = A[i + (k / 2) * n][j + (k % 2) * n];
				aux2[k][i][j] = B[i + (k / 2) * n][j + (k % 2) * n];
			}
	// this is a vector of matrixes that are used for the algoritm
	int ***M = (int ***)calloc(7, sizeof(int **));
	// this builds the auxiliary matrixes
	build_M(n, M, aux1, aux2);
	// frees the 8 blocks and their vectors
	for (int i = 0; i < 4; i++) {
		free_matrix(aux1[i], n);
		free_matrix(aux2[i], n);
	}
	free(aux1);
	free(aux2);
	// allocates the new matrix and the 4 blocks
	int **C, **C00, **C01, **C10, **C11;
	allocation_matrix(2 * n, 2 * n, &C);
	allocation_matrix(n, n, &C00);
	allocation_matrix(n, n, &C01);
	allocation_matrix(n, n, &C10);
	allocation_matrix(n, n, &C11);
	// allocates other auxiliaries
	int **maux1, **maux2;
	allocation_matrix(n, n, &maux1);
	allocation_matrix(n, n, &maux2);
	// builds the blocks of the future return matrix
	suma(n, M[0], M[3], &maux1, 0);
	suma(n, M[4], M[6], &maux2, 1);
	suma(n, maux1, maux2, &C00, 1);
	suma(n, M[2], M[4], &C01, 0);
	suma(n, M[1], M[3], &C10, 0);
	suma(n, M[0], M[1], &maux1, 1);
	suma(n, M[2], M[5], &maux2, 0);
	suma(n, maux1, maux2, &C11, 0);
	// frees auxiliaries
	for (int i = 0; i < 7; i++)
		free_matrix(M[i], n);
	free(M);
	free_matrix(maux1, n);
	free_matrix(maux2, n);
	// builds the returned matrix
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			C[i][j] = mod(C00[i][j]);
			C[i][j + n] = mod(C01[i][j]);
			C[i + n][j] = mod(C10[i][j]);
			C[i + n][j + n] = mod(C11[i][j]);
		}
	// frees all auxiliaries
	free_matrix(C00, n);
	free_matrix(C01, n);
	free_matrix(C10, n);
	free_matrix(C11, n);
	return C;
}

// builds matrixes for the algoritm of Strassen
void build_M(int n, int ***M, int ***aux1, int ***aux2)
{
	int **maux1, **maux2;
	allocation_matrix(n, n, &maux1);
	allocation_matrix(n, n, &maux2);

	suma(n, aux1[0], aux1[3], &maux1, 0);
	suma(n, aux2[0], aux2[3], &maux2, 0);
	M[0] = S_recursiv(n, maux1, maux2);

	suma(n, aux1[2], aux1[3], &maux1, 0);
	M[1] = S_recursiv(n, maux1, aux2[0]);

	suma(n, aux2[1], aux2[3], &maux2, 1);
	M[2] = S_recursiv(n, aux1[0], maux2);

	suma(n, aux2[2], aux2[0], &maux2, 1);
	M[3] = S_recursiv(n, aux1[3], maux2);

	suma(n, aux1[0], aux1[1], &maux1, 0);
	M[4] = S_recursiv(n, maux1, aux2[3]);

	suma(n, aux1[2], aux1[0], &maux1, 1);
	suma(n, aux2[0], aux2[1], &maux2, 0);
	M[5] = S_recursiv(n, maux1, maux2);

	suma(n, aux1[1], aux1[3], &maux1, 1);
	suma(n, aux2[2], aux2[3], &maux2, 0);
	M[6] = S_recursiv(n, maux1, maux2);

	free_matrix(maux1, n);
	free_matrix(maux2, n);
}

// multiplies 2 given matrixes using algoritm of Strassen
void case_S(int *n, int *m, int ***arr, int *index)
{
	int k1, k2;
	scanf("%d", &k1);
	scanf("%d", &k2);
	if (k1 > *index || k1 < 0 || k2 > *index || k2 < 0) {
		printf("No matrix with the given index\n");
		return;
	}

	if (m[k1] != n[k2]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	// saves the new matrix into the main vector of matrixes
	(*index)++;
	n[*index] = n[k1];
	m[*index] = n[k2];
	arr[*index] = S_recursiv(n[k1], arr[k1], arr[k2]);
}
