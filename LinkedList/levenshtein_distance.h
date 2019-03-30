#pragma once

#include "pch.h"
#include <string>
#include <algorithm>

static int matrix[100][100];

int levenshteinDistance(const std::string &s1, const std::string &s2) {
	
	const int len1 = strlen(s1.c_str());
	const int len2 = strlen(s2.c_str());

	if (len1 == 0) { return 0; }
	if (len2 == 0) { return 0; }

	/*int **matrix = new int*[(len1 + 1)];
	for (int i = 0; i <= len1; i++) {
		matrix[i] = new int[(len2 + 1)];
	}*/
	
	matrix[0][0] = 0;

	for (int i = 1; i <= len1; i++) { matrix[i][0] = i; }
	for (int j = 1; j <= len2; j++) { matrix[0][j] = j; }

	
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			matrix[i][j] = std::min({
				matrix[i - 1][j] + 1,
				matrix[i][j - 1] + 1,
				matrix[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1),
			});
		}
	}

	int result = matrix[len1][len2];

	/*for (int i = 0; i <= len1; i++) { delete[] matrix[i]; }
	delete[] matrix;*/

	return result;
}
