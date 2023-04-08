#include <iostream>
#include <ncurses.h>
#include <getopt.h>
#include <string>
#include <stdexcept>
#include <vector>

using std::string;
using std::stoi;
using std::cerr;
using std::cout;
using std::endl;
using std::invalid_argument;
using std::out_of_range;
using std::vector;

const int ERROR_BAD_TUTORIAL_NUMBER = 1;

void PrintHelp() {
    cerr << "Usage:\n";
    cerr << "-h    prints this help\n";
    cerr << "-t n  selects tutorial n - default is 0\n";
}

void HandleOptions(int argc, char ** argv, int & tutorial_number) {
    int c;
    while ((c = getopt(argc, argv, "ht:")) != -1) {
        switch (c) {
            case 'h':
                PrintHelp();
                exit(0);

            case 't':
                try {
                    tutorial_number = ::stoi(string(optarg));
                } catch (const invalid_argument & ia) {
                    cerr << "Cannot convert to integer: " << optarg;
                    cerr << endl;
					exit(ERROR_BAD_TUTORIAL_NUMBER);
				} catch (const out_of_range & oor) {
                    cerr << "Value too large: " << optarg;
                    cerr << endl;
                    exit(ERROR_BAD_TUTORIAL_NUMBER);
                }
                break;

            default:
                // Use default of tutorial number 0.
                break;
        }
    }
}

void T0();
void T1();
void T2();
void T3();
void T4();
void T5();
void T6();
void T7();
void RunTutorial(int);

vector<void (*)()> tutorials = {
    T0, T1, T2, T3, T4, T5,
    T6, T7
};

int main(int argc, char * argv[]) {
    int tutorial_number = 0;

    HandleOptions(argc, argv, tutorial_number);
    RunTutorial(tutorial_number);
    exit(0);
}

void RunTutorial(int tutorial_number) {
    if (tutorial_number < 0 || 
        tutorial_number >= int(tutorials.size())) {
        cerr << "Tutorial number must be in the range of 0 to ";
        cerr << tutorials.size() - 1 << endl;
        exit(ERROR_BAD_TUTORIAL_NUMBER);
	}
    tutorials[tutorial_number]();
}

void T0() {
    initscr();
    endwin();
    cout << "Nothing will have appeared to happen.\n";
}

void T1() {
    initscr();
    erase();
    endwin();
	cout << "Nothing will have appeared to happen.\n";
}

void T2() {
	initscr();
	erase();
    refresh();
	endwin();
	cout << "Nothing will have appeared to happen.\n";
}

void T3() {
	initscr();
	erase();
    addstr("Hit enter");
	refresh();
	getch();
	endwin();
    cout << "Screen will have erased and program will have waited\n";
    cout << "for you to hit enter.\n";
}

void T4() {
	initscr();
    box(stdscr, 0, 0);
	erase();
	addstr("Hit enter");
	refresh();
	getch();
	endwin();
	cout << "Screen will have erased and program will have waited\n";
	cout << "for you to hit enter. No box visible.\n";
}

void T5() {
	initscr();
	erase();
	box(stdscr, 0, 0);
	mvaddstr(0, 2, "Hit enter");
	refresh();
	getch();
	endwin();
	cout << "Screen will have:\n";
    cout << "* erased\n";
    cout << "* program will have waited for you to hit enter\n";
	cout << "* a box was visible.\n";
}

void T6() {
	initscr();
    curs_set(0);
	erase();
	box(stdscr, 0, 0);
	mvaddstr(0, 2, "Hit enter");
	refresh();
	getch();
	endwin();
	cout << "Screen will have:\n";
	cout << "* erased\n";
	cout << "* program will have waited for you to hit enter\n";
	cout << "* a box was visible\n";
    cout << "* cursor was invisible\n";
    cout << "* cursor came back when program ended\n";
}

void T7() {
	initscr();
    curs_set(0);
	erase();
	box(stdscr, 0, 0);
	mvaddstr(0, 2, "Hit enter");
	refresh();
	getch();
	endwin();
	cout << "Screen will have:\n";
	cout << "* erased\n";
	cout << "* program will have waited for you to hit enter\n";
	cout << "* a box was visible.\n";
}
