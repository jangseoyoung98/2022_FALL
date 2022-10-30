// ★ ungetc() 변경!

#ifndef _FUNCTIONS_C_
#define _FUNCTIONS_C_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// getIntNum()
int getIntNum(char firstCharacter)
{
	int num = 0;
	int value;
	char ch;

	if (firstCharacter != '0') {				// 10진수
		ch = firstCharacter;
		do {
			num = 10 * num + (int)(ch - '0');
			ch = getchar();
		} while (isdigit(ch));
	}
	else {
		ch = getchar();
		if ((ch >= '0') && (ch <= '7'))			// 8진수
			do {
				num = 8 * num + (int)(ch - '0');
				ch = getchar();
			} while ((ch >= '0') && (ch <= '7'));
		else if ((ch == 'X') || (ch == 'x')) {	// 16진수
			while ((value = hexaValue(ch = getchar())) != -1)
				num = 16 * num + value;
		}
		else num = 0;
	}
	ungetc(ch, stdin);	
	return num;
}
int hexaValue(char ch)
{
	switch(ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return (ch - '0');

		case 'A': case 'B': case 'C': case'D': case 'E': case 'F':
			return (ch - 'A' + 10);
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			return (ch - 'a' + 10);
		default:
			return -1;
	}
}

// lexicalError()
void lexicalError(int n)
{
	printf(" *** Lexical Error : ");
	switch (n) {
	case 1:
		printf("an identifier length must be less than 12.\n");
		break;
	case 2:
		printf("next character must be &.\n");
		break;
	case 3:
		printf("next character must be |.\n");
		break;
	case 4:
		print("invlaid character!!\n");
		break;
	}
}

// superLetter()
int superLetter(char ch)
{
	if (isalpha(ch) || ch == '_') return 1;
	else return 0;
}

// superLetterOrDigit()
int superLetterOrDigit(char ch)
{
	if (isalnum(ch) || ch == '_') return 1;
	else return 0;
}

#endif