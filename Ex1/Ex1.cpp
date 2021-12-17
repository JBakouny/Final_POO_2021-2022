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

class Project {
public:
	Project(const string& name, int majorVersion, int minorVersion)
		: name(name), majorVersion(majorVersion), minorVersion(minorVersion)
	{}

	void add(const File& f) {
		files.push_back(f);
	}

	string toString() const {
		stringstream ss;
		ss << "cmake_minimum_required(VERSION " << majorVersion << "." << minorVersion << ")" << endl;
		ss << "project(" << name << ")" << endl;
		ss << "add_executable(" << name;
		for (auto f : files) {
			ss << " " << f;
		}
		ss << ")" << endl;
		return ss.str();
	}

private:
	string name;
	int majorVersion;
	int minorVersion;
	vector<File> files;
};

ostream& operator<< (ostream& out, const Project& p) {
	out << p.toString();
	return out;
}

int main()
{
	File ex1cpp("Ex1", "cpp", 17.3);
	File ex1h("Ex1", "h", 5);

	Project p("MyProj", 3, 8);
	p.add(ex1cpp);
	p.add(ex1h);

	cout << p << endl;

	return 0;
}
