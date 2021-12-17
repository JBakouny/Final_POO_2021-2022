// Ex1.cpp : Defines the entry point for the application.
//

//#include "Ex1.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class File {

public:
	File(const string & name, 
		const string & extension, 
		double size)
		: name(name), extension(extension), size(size)
	{

	}

	string toString() const {
		stringstream ss;
		ss << "File: " << name << "." << extension << " (" << size << " KB)";
		return ss.str();
	}
	ostream& toOstream(ostream& out) const {
		return out
	}
private:
	string name;
	string extension;
	double size;
};

ostream& operator<< (ostream& out, const File& f) {
	out << f.toString();
	return out;
}

int main()
{
	const File f("main", "cpp", 17.3);
	cout << f.toString() << endl;
	return 0;
}
