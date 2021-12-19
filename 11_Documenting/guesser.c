#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

#define _(STRING) gettext(STRING)


void usage(char* name) {
	printf(_("Usage: %s [OPTION...]\n"), name);
	printf(_("Try `%s --help' or `%s -?' for more information\n"), name, name);
}

void full_usage(char* name) {
	printf(_("Usage: %s [OPTION...]\n"), name);
	printf(_("Guesser -- a program which guesses number from 1 to 100\n\n"));
	printf(_("\t-r          Display numbers in Roman\n"));
	printf(_("\t--help      Give this help list\n"));
	printf("\t-?\n\n");
	printf(_("Report bugs to <nowhere@gmail.com\n"));
}

char* toRoman(int i) {
	static char * table[] = {"N", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};
	return table[i];
}

int guess(int a, int b, int roman) {
	if (a == b) {
		return a;
	}
	int half = (a + b + 1) / 2;
	if (roman) {
		printf(_("Is your number less then %s?\n"), toRoman(half));
	} else {
		printf(_("Is your number less then %d?\n"), half);
	}

	char answer[64];
	scanf("%s", answer);
	if (strcmp(answer, _("no")) == 0) {
		return guess(half, b, roman);
	} else {
		return guess(a, half - 1, roman);
	}
}

int main(int argc, char *argv[]) {

	int roman = 0;

	setlocale (LC_ALL, "");
	bindtextdomain ("guesser", "po");
	textdomain ("guesser");

	if (argc > 2) {
		usage(argv[0]);
		return 1;
	} else if (argc == 2) {
		if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0) {
			full_usage(argv[0]);
			return 0;
		} else if (strcmp(argv[1], "-r") == 0) {
			roman = 1;
		} else {
			usage(argv[0]);
			return 1;
		}
	}

	if (roman) {
		printf(_("I will try to guess a number from I to C\n"));
		printf(_("Your number is %s\n"), toRoman(guess(1, 100, roman)));
	} else {
		printf(_("I will try to guess a number from 1 to 100\n"));
		printf(_("Your number is %d\n"), guess(1, 100, roman));
	}

	return 0;
}
