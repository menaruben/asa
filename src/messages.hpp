#include <string>

using namespace std;
namespace msgs {

string 
expected_but_got_at_line_column(string expected, string got, int line, int column) {
    return "Expected " + expected + ", got " + got + " at line " 
    + to_string(line) + " column " + to_string(column);
}

string
expected_but_got_at_line(string expected, string got, int line) {
    return "Expected " + expected + ", got " + got + " at line " + to_string(line);
}

}