#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h> 

#define DX 1

int main(int argc, char* argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Invalid number of params\n");
        return -1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error opening file '%s'\n", argv[1]);
        return -1;
    }

    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;

    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw(argv[1]);
    refresh();

    win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
    keypad(win, TRUE);
    scrollok (win, TRUE);
    box(win, 0, 0); 
    wmove(win, 1, 0); 

    line_size = getline(&line_buf, &line_buf_size, fp);

    // fill
    for (int i = 0; (i < LINES - 2 * DX - 2) && (line_size >= 0); ++i) {
        wprintw(win, "  %s", line_buf);
        box(win, 0, 0);
        wrefresh(win);
        line_size = getline(&line_buf, &line_buf_size, fp);
    }

    // scroll
    while((c = wgetch(win)) != 27) {
        if ((c == 32) && (line_size >= 0)) {
            wprintw(win, "  %s", line_buf);
            box(win, 0, 0);
            wrefresh(win);
            line_size = getline(&line_buf, &line_buf_size, fp);
        }
    }

    free(line_buf);

    endwin();
    fclose(fp);

    return 0;
}

