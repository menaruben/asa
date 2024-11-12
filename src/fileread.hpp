#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

string read_file(const string &filename, string comment_delim) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file." << endl;
    return "";
  }

  stringstream ss;
  string line;
  while (getline(file, line)) {
    line = line.substr(0, line.find(comment_delim));
    ss << line << endl;
  }
  return ss.str();
}
