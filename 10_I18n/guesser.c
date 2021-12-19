#include <stdio.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

int guess(int a, int b) {
	if (a == b) {
		return a;
	}
	int half = (a + b + 1) / 2;
	printf(_("Is your number less then %d?\n"), half);
	char answer[64];
	scanf("%s", answer);
	if (strcmp(answer, _("no")) == 0) {
		return guess(half, b);
	} else {
		return guess(a, half - 1);
	}


}

int main(int argc, char *argv[]) {
	/*
	char *dir;
	dir = dirname(realpath(argv[0], NULL));
	*/

	setlocale (LC_ALL, "");
	bindtextdomain ("guesser", "po");
	textdomain ("guesser");

	printf(_("I will try to guess a number from 1 to 100\n"));
	printf(_("Your number is %d\n"), guess(1, 100));
	return 0;
}
