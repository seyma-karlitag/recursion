#include <stdio.h>
#include <string.h>

#define INPUT_LEN 100 /* Max input length */

double object_cost(char *name);
double sum_cost();

int main(void)
{
	char inp[INPUT_LEN + 1];
	char *newline;
	double cost;

	printf("Define the object:\n");
	fgets(inp, INPUT_LEN + 1, stdin);

	/* Make sure the string ends without newline */
	newline = strchr(inp, '\n');
	if (newline != NULL) {
		*newline = '\0';
	}

	cost = object_cost(inp);
	printf("Total cost of %s is %.1f\n", inp, cost);

	return 0;
}

/* Returns the cost of recursively created object */
double object_cost(char *name)
{
	char inp[INPUT_LEN + 1];

	printf("What is %s?:\n", name);
	fgets(inp, INPUT_LEN + 1, stdin);

	return sum_cost(inp);
}

/* 
 * Returns the total cost of input. 
 * May call object_cost internally for more input.
 */
double sum_cost(char *input)
{
	double num;
	char part_name[INPUT_LEN];
	char *plus;
	int n;

	/* Find '+' and make sure the string ends there */
	plus = strchr(input, '+');
	if (plus != NULL) {
		*plus = '\0';
	}

	n = sscanf(input, "%lf *%s", &num, part_name);
	/* We have found the final cost */
	if (n == 1) {
		return num;
	/* Input has no meaning without both matches */
	} else if (n != 2) {
		return 0.0;
	}

	if (plus == NULL) {
		return num * object_cost(part_name);
	} else {
		return num * object_cost(part_name) + sum_cost(plus + 1);
	}
}
