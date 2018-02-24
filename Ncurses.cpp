#include <ncurses.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char* argv[])
{
   	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	
	use_default_colors();
	start_color();
	
	init_pair(1, COLOR_GREEN, -1); // data_types
    init_pair(2, COLOR_RED, -1); // keywords
    init_pair(3, COLOR_BLUE, -1); //  numbers
    init_pair(4, COLOR_YELLOW, -1); // strings
    init_pair(5, COLOR_MAGENTA, -1); // comments
    
    
    
    const char* data_types[]={"auto", "bool", "char", "char16_t", "char32_t", "const", "double", "explicit", "export", "extern", "float", "inline", "int", "long", "mutable", "register", "short", "signed", "static", "unsigned", "void", "volatile", "wchar_t"};
    
    const char* keywords[]={"alignas", "alignof", "and", "and_eq", "asm", "bitand", "bitor", "break", "case", "catch", "class", "compl", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "dynamic_cast", "else", "enum", "false", "for", "friend", "goto", "if", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "reinterpret_cast", "return", "sizeof", "static_assert", "static_cast", "struct", "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename", "union", "using", "virtual", "while", "xor", "xor_eq", "override", "final"};
    
    vector<string> lines;
    lines.push_back("Martin50 {15{28 52 int main(int argc, char* argv[]) {char* text=\"red, blue, green\"; return 0;}");
    lines.push_back("string=\"\\\"text\\\"\"\"red\"\"...; // white, black");
    lines.push_back("// red, blue, green");
    lines.push_back("int num=20; // this is a number");
    lines.push_back("22/*test*/1/*orange*/56");
    lines.push_back("int array[5]; /*this is an array*/");
    lines.push_back("/*this is an array*/ char array[5];");
    lines.push_back("/*this is an array char array[5];");
    
    for (size_t line_index=0; line_index < lines.size(); line_index++) {
        size_t pos=0;
        string line=lines[line_index];
        for (size_t i=0; i < line.length(); i++) {
            char c=line[i];
            if (c == '"') {
                pos=i;
                for (i=i+1; i < line.length(); i++) {
                    if (line[i] == '"' && line[i-1] != '\\') {
                        break;
                    }
                }
                attron(COLOR_PAIR(4));
                printw("%s", line.substr(pos, i-pos+1).c_str());
                attroff(COLOR_PAIR(4));
            }
            else if (c == '/' && i + 1 != line.length()) {
                if (line[i+1] == '/') {
                    attron(COLOR_PAIR(5));
                    printw("%s", line.substr(i).c_str());
                    attroff(COLOR_PAIR(5));
                    break;
                }
                else if (line[i+1] == '*') {
                    pos=i;
                    for (i=i+2; i < line.length() - 1; i++) {
                        if (line[i] == '*' && line[i+1] == '/') {
                            break;
                        }
                    }
                    i++;
                    attron(COLOR_PAIR(5));
                    printw("%s", line.substr(pos, i-pos+1).c_str());
                    attroff(COLOR_PAIR(5));
                }
            }
            else if (c >= '0' && c <= '9') {
                pos=i;
                for (i=i+1; i < line.length(); i++) {
                        if (line[i] < '0' || line[i] > '9') {
                            break;
                        }
                    }
                    attron(COLOR_PAIR(3));
                    printw("%s", line.substr(pos, i-pos).c_str());
                    attroff(COLOR_PAIR(3));
            }
            
            /*if (c == '{' || c == '*' || c == '(' || c == ' ' || i == line.length() - 1 || c == ';' || c == '"' || c == '=') {
                if (i == line.length() - 1) {
                    i++;
                }
                if (i > pos) {
                    string word=line.substr(pos, i-pos);
                    
                    if (word[0] >= '0' && word[0] <= '9') {
                        attron(COLOR_PAIR(3));
                        printw("%s", word.c_str());
                        attroff(COLOR_PAIR(3));
                    }
                    else {
                        bool word_found=false;
                        for (size_t j=0; j < sizeof(data_types)/sizeof(*data_types); j++) { 
                            if (word == data_types[j]) {
                                word_found=true;
                                attron(COLOR_PAIR(1));
                                printw("%s", word.c_str());
                                attroff(COLOR_PAIR(1));
                                break;
                            }
                        }
                        if (!word_found) {
                            for (size_t j=0; j < sizeof(keywords)/sizeof(*keywords); j++) {
                                if (word == keywords[j]) {
                                    word_found=true;
                                    attron(COLOR_PAIR(2));
                                    printw("%s", word.c_str());
                                    attroff(COLOR_PAIR(2));
                                    break;
                                }
                            }
                        }
                        if (!word_found) {
                            printw("%s", word.c_str());
                        }
                    }
                }
                if (i < line.length()) {
                    pos=i+1;
                    printw("%c", c);
                }
            }*/
        }
        printw("\n");
    }    
	
	/*string line="void int main () {string text=\"red,blue,green\"; return 0;}";
	init_pair(1, COLOR_GREEN, -1);
	attron(COLOR_PAIR(1));
	printw(line.c_str());
	attroff(COLOR_PAIR(1));
	
	size_t pos=0;
    //printw("%s", line.substr(26, 3).c_str());

	printw("\n");
	for (size_t i=0; i < line.length(); i++) {
	    char c=line.at(i);
	    if (c == ' ') {
	        string word=line.substr(pos, i-pos);
	        pos=i+1;
	        if (word == "int" || word == "void") {
	            attron(COLOR_PAIR(1));
	            printw("%s", word.c_str());
	            attroff(COLOR_PAIR(1));
	        }
	        else {
                printw("%s", word.c_str());
	        }
	        printw(" ");
	    }
    }*/
	
	getch();
	endwin();
	return 0;
	
	//init_color(COLOR_GREEN, 60, 60, 60);
	init_pair(1, COLOR_GREEN, -1);
	attron(COLOR_PAIR(1));
	
	printw("Hello World!\n");
	
	attroff(COLOR_PAIR(1));
	
	string text="blue red green";
	text=text.substr(0, 4);
	
	init_pair(2, COLOR_BLUE, -1);
	attron(COLOR_PAIR(2));
	
	printw("%s\n", text.c_str());
	
	attroff(COLOR_PAIR(2));
	//string left=text.substr(5);
	//printw("%s\n", left.c_str());
	
	//map<string, string> 
	
	getch();
	endwin();
	
	return 0;
}
