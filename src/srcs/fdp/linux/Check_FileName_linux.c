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
		if (*name == 's' 
			&& *(name + 1) == 'd' 
			&& *(name + 4) == '\0' 
			&& *(name + 3) >= '0' 
			&& *(name + 3) <= '9') 
		{
			if (checkFileBytes(name, offset) == 0) return 1;
		}
		return 0;
}