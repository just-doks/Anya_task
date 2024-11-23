#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "../../dataManagment/base_data.h"
#include "../fdp_header.h"

// Функция принимает на вход строку, проверяет по заданному правилу и возвращает:
// 1, если слово прошло по правилу
// 0, если не прошло 
int checkFileName(char* name) {
		UInt_8 offset = 0;
		if (name == NULL) {
			return 0;
		}
		if     (*name == 'd' 
			&& *(name + 1) == 'i'
			&& *(name + 2) == 's'
			&& *(name + 3) == 'k'
			&& *(name + 4) >= '0' 
			&& *(name + 4) <= '9'
			&& *(name + 5) == 's'
			&& *(name + 6) >= '0' 
			&& *(name + 6) <= '9'
			&& *(name + 7) == '\0') 
		{
			if (checkFileBytes(name, offset) == 0) return 1;
		}
		return 0;
}