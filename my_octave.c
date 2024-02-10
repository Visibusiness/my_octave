// Copyright Visanescu Bogdan-Emilian 313CA 2023-2024
#include <stdio.h>
#include <stdlib.h>
#include "my_octave.h"
int main(void)
{
	// variable for given command
	char c;
	// the array of matrixes
	int ***arr = allocation_array2(1);
	// the arrays of the dimensions of a matrix
	int *n = allocation_nm();
	int *m = allocation_nm();
	// index of a matrix
	// capacitate means the allocated number of matrixes
	int index = -1, capacitate = 1;
	while (1) {
		scanf(" %c", &c);
		// condition for reallocation
		if (index + 1 >= capacitate) {
			capacitate *= 2;
			n = (int *)reallocation_nm(n, capacitate);
			m = reallocation_nm(m, capacitate);
			arr = reallocation_array(arr, capacitate);
		}
		// given command
		switch (c) {
		case 'L':
			case_L(n, m, arr, &index);
			break;
		case 'D':
			case_D(n, m, index);
			break;
		case 'P':
			case_P(n, m, arr, index);
			break;
		case 'C':
			case_C(n, m, arr, index);
			break;
		case 'T':
			case_T(arr, n, m, index);
			break;
		case 'O':
			case_O(n, m, arr, index);
			break;
		case 'Q':
			case_Q(n, m, arr, index);
			break;
		case 'M':
			case_M(n, m, arr, &index);
			break;
		case 'F':
			case_F(n, m, arr, &index);
			break;
		case 'R':
			case_R(n, m, arr, index);
			break;
		case 'S':
			case_S(n, m, arr, &index);
			break;
		default:
			printf("Unrecognized command\n");
			break;
		}
	}
	return 0;
}
