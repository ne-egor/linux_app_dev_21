bin_PROGRAMS=guesser

pkgdata_DATA=po/ru/LC_MESSAGES/guesser.mo

po/ru/LC_MESSAGES/guesser.mo: po/ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

all-local:	gen_man

gen_man: Doxyfile guesser
	doxygen $<


update_po: guesser.c
	xgettext --keyword=_ --language=C --add-comments -o po/guesser.pot $<
	msgmerge --update po/ru.po po/guesser.pot
	echo "Update completed. Don't forget to remove fuzzy if you are satisfied and to run 'make po/ru/LC_MESSAGES/guesser.mo'"

gitclean:
	git clean -fd


#messages.pot:	guesser.pot guesser.c
#	xgettext -k_ -c guesser.c -o messages.new.pot
#	cp guesser.pot messages.pot
#	msgmerge -U messages.pot messages.new.pot
