#include <stdio.h>
#include <math.h>
#include <string.h>

#pragma warning(disable : 4996) //Отключает предупреждение об устаревших функциях, переменных в библиотеке Visual Studio.
#pragma warning(disable : 6031) //Отключает предупреждение, что возвращаемое значение "scanf" пропущенно.

#define PI 3.14159265358979323846

char answer[6][25];
double l_border, r_border;

double calculate_by_rectangle_method(int parts) {
	double result = 0, sector;
	sector = (r_border - l_border) / parts;

	for (int i = 0; i < parts; i++) {
		result += sin(l_border + sector * (i + 0.5));
	}

	result *= sector;
	return result;
}

double calculate_by_simpsons_method(int parts) {
	double x, sector, integral;
	sector = (r_border - l_border) / 2 / parts;
	integral = sin(l_border) + sin(r_border);
	x = l_border + sector;
	for (int i = 1; i < 2 * parts; i++) {
		if (i % 2 == 0) integral += 2 * sin(x);
		else integral += 4 * sin(x);
		x += sector;
	}
	integral *= sector / 3;
	return integral;
}

void entering_numbers() {
	int borderA = 0, borderB = 0, borderAll = 0;
	while (!borderAll) {
		while (!borderA) {
			printf("Enter interval's left border: ");
			scanf("%lf", &l_border);
			if (l_border < 0) {
				printf("Error:Left border must be more than or equal to 0 \n");
				continue;
			}
			else if (l_border > PI) {
				printf("Error: Left border must be less than PI \n");
				continue;
			}
			borderA = 1;
		}
		while (!borderB) {
			printf("Enter interval's right border:");
			scanf("%lf", &r_border);
			if (r_border < 0) {
				printf("Error: Right border must be more than 0 \n");
				continue;
			}
			else if (r_border > PI) {
				printf("Error: Right border must be less than PI \n");
				continue;
			}
			if (l_border > r_border) {
				printf("Error: Right border must be more than left \n");
				continue;
			}
			borderB = 1;
		}
		borderAll = 1;
	}
}

void console(int array[]) {
	char intermediate_line[15];
	for (int i = 0; i < 6; i++) {
		double s, r;
		r = calculate_by_rectangle_method(array[i]);
		s = calculate_by_simpsons_method(array[i]);
		sprintf(intermediate_line, "%d", array[i]);
		strcat(answer[i], intermediate_line);
		strcat(answer[i], " ");
		sprintf(intermediate_line, "%2.5f", r);
		strcat(answer[i], intermediate_line);
		strcat(answer[i], " ");
		sprintf(intermediate_line, "%2.5f", s);
		strcat(answer[i], intermediate_line);
	}
}
int main() {
	int array[7] = { 6, 10, 20, 100, 500, 1000,};
	entering_numbers();
	console(array);
	for (int i = 0; i < 6; i++) {
		printf("%s\n", answer[i]);
	}
	return 0;
}
