/* Mini C 관련 (교재 p148~150)*/
#ifndef _SCANNER_C_
#define _SCANNER_C_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ★ ungetc() 변경!

// (1) tsymbol
enum tsymbol {
	tnull = -1,
	tnot, tnotequ, tmod, tmodAssign, tident, tnumber,		// 0 ~ 5

	tand, tlparen, trparen, tmul, tmulAssign, tplus,		// 6 ~ 11

	tinc, taddAssign, tcomma, tminus, tdec, tsubAssign,		// 12 ~ 17

	tdiv, tdivAssign, tsemicolon, tless, tlesse, tassign,	// 18 ~ 23

	tequal, tgreat, tgreate, tlbracket, trbracket, teof,	// 24 ~ 29

	// ---------------- word symbols ----------------- //
	tconst, telse, tif, tint, treturn, tvoid,				// 30 ~ 35

	twhile, tlbrace, tor, trbrace							// 36 ~ 39
};

// (2) 매크로 상수
#define NO_KEYWORDS 7
#define ID_LENGTH 12

// (3) tokenType
struct tokenType {
	int number;		// token number
	union {
		char id[ID_LENGTH];
		int num;
	} value;		// token value
};

// (4) keyword
char* keyword[NO_KEYWORDS] = {
	"const", "else", "if", "int", "return", "void", "while"
};
enum tsymbol tnum[NO_KEYWORDS] = {
	tconst, telse, tif, tint, treturn, tvoid, twhile
};

// (5) 함수들
int getIntNum(char firstCharacter)	// getIntNum()
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
		else num = 0;	// zero
	}
	ungetc(ch, stdin);
	return num;
}
int hexaValue(char ch)
{
	switch (ch) {
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

void lexicalError(int n)	// lexicalError()
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
		printf("invlaid character!!\n");
		break;
	}
}

int superLetter(char ch)	// superLetter()
{
	if (isalpha(ch) || ch == '_') return 1;
	else return 0;
}

int superLetterOrDigit(char ch)	// superLetterOrDigit()
{
	if (isalnum(ch) || ch == '_') return 1;
	else return 0;
}


// scanner()
// input : perfect.mc
// output : token (number & value)
struct tokenType scanner() {
	struct tokenType token;
	int i, index;
	char ch, id[ID_LENGTH];

	token.number = tnull;

	do {
		while (isspace(ch = getchar()));	// state 1 : skip blank
		if (superLetter(ch)) {	// identifier or keyword
			i = 0;
			do {
				if (i < ID_LENGTH) id[i++] = ch;
				ch = getchar();
			} while (superLetterOrDigit(ch));

			if (i >= ID_LENGTH) lexicalError(1);
			id[i] = '\0';
			ungetc(ch, stdin);	// retract

			//find the identifier in the keyword table
			for (index = 0; index < NO_KEYWORDS; index++)
				if (!strcmp(id, keyword[index])) break;
			if (index < NO_KEYWORDS)	// found, keword exit
				token.number = tnum[index];
			else {						// not found, identifier exit
				token.number = tident;
				strcpy(token.value.id, id);
			}
		} // end of identifier or keyword

		else if (isdigit(ch)) {	// integer constant
			token.number = tnumber;
			token.value.num = getIntNum(ch);
		}

		else switch (ch) {	// special character
		case '/':	// state 10
			ch = getchar();
			if (ch == '*')	// text comment
				do {
					while (ch != '*')
						ch = getchar();
					ch = getchar();
				} while (ch != '/');
			else if (ch == '/')	// line comment
				while (getchar() != '\n');
			else if (ch == '=')
				token.number = tdivAssign;
			else {
				token.number = tdiv;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '!':	// state 17
			ch = getchar();
			if (ch == '=')
				token.number = tnotequ;
			else {
				token.number = tnot;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '%':	// state 20
			ch = getchar();
			if (ch == '=')
				token.number = tmodAssign;
			else {
				token.number = tmod;
				ungetc(ch, stdin);
			}
			break;

		case '&':	// state 23
			ch = getchar();
			if (ch == '&')
				token.number = tand;
			else {
				lexicalError(2);
				ungetc(ch, stdin);	// retract
			}
			break;

		case '*':	// state 25
			ch = getchar();
			if (ch == '=')
				token.number = tmulAssign;
			else {
				token.number = tmul;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '+':	// state 28
			ch = getchar();
			if (ch == '+')
				token.number = tinc;
			else if (ch == '=')
				token.number = taddAssign;
			else {
				token.number = tplus;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '-':	// state 32
			ch = getchar();
			if (ch == '-')
				token.number = tdec;
			else if (ch == '=')
				token.number = tsubAssign;
			else {
				token.number = tminus;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '<':	// state 36
			ch = getchar();
			if (ch == '=')
				token.number = tlesse;
			else {
				token.number = tless;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '=':	// state 39
			ch = getchar();
			if (ch == '=')
				token.number = tequal;
			else {
				token.number = tassign;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '>':	// state 42
			ch = getchar();
			if (ch == '=')
				token.number = tgreate;
			else {
				token.number = tgreat;
				ungetc(ch, stdin);	// retract
			}
			break;

		case '|':	// state 45
			ch = getchar();
			if (ch == '=')
				token.number = tor;
			else {
				lexicalError(3);
				ungetc(ch, stdin);	// retract
			}
			break;

		case '(': token.number = tlparen;		break;
		case ')': token.number = trparen;		break;
		case ',': token.number = tcomma;		break;
		case ';': token.number = tsemicolon;	break;
		case '[': token.number = tlbracket;		break;
		case ']': token.number = trbracket;		break;
		case '{': token.number = tlbrace;		break;
		case '}': token.number = trbrace;		break;
		case EOF: token.number = teof;			break;

		default: {
			printf("current character : %c", ch);
			lexicalError(4);
			break;
		}
		} // switch end

	} while (token.number == tnull);

	return token; // 토큰 (토큰 넘버+밸류) 리턴
} // end of scanner

#endif