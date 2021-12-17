// Ex1.cpp : Defines the entry point for the application.
//

//#include "Ex1.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class File {

public:
	File(const string & name, 
		const string & extension, 
		double fileSize)
		: name(name), extension(extension), fileSize(fileSize)
	{

	}

	string toString() const {
		stringstream ss;
		ss << name << "." << extension;
		return ss.str();
	}


	double size() const {
		return fileSize;
	}


private:
	string name;
	string extension;
	double fileSize;
};

ostream& operator<< (ostream& out, const File& f) {
	out << f.toString();
	return out;
}

int main()
{
	const File f("main", "cpp", 17.3);
	cout << f << endl;
	cout << f.size() << " KB" << endl;
	return 0;
}
