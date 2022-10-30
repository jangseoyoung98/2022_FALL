// scanner() - the function to provide information about tokens using the formal language.
// input : perfect.mc
// output : token (number & value)

// ★ ungetc() 바꾸기!
#include "scanner.h"

struct tokenType scanner(/* perfect.mc를 입력으로!*/) {
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







