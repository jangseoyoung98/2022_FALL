/* Mini C 관련 (교재 p148~150)*/
#ifndef _MINIC_C_
#define _MINIC_C_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// (2) 
#define NO_KEYWORDS 7
#define ID_LENGTH 12

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

// (4) keyword
char* keyword[NO_KEYWORDS] = {
	"const", "else", "if", "int", "return", "void", "while"
};
enum tsymbol tnum[NO_KEYWORDS] = {
	tconst, telse, tif, tint, treturn, tvoid, twhile
};

// (3) tokenType
struct tokenType {
	int number;		// token number
	union {
		char id[ID_LENGTH];
		int num;
	} value;		// token value
};

#endif