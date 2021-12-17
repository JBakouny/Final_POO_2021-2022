#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class File {

public:
	File(const string& name,
		const string& extension,
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

class Directory {
public:
	Directory(const string& name)
		: name(name)
	{}

	void add(const File& f) {
		files.push_back(f);
	}

	string toString() const {
		stringstream ss;
		ss << name;
		return ss.str();
	}

	string showContents(string sep = "") const {
		if (files.size() == 0) {
			return "";
		}
		stringstream ss;
		ss << files[0];
		for (size_t i = 1; i < files.size(); ++i) {
			ss << sep << " " << files[i];
		}
		return ss.str();
	}

	double size() const {
		double res = 0;
		for (auto f : files) {
			res += f.size();
		}
		return res;
	}

private:
	string name;
	vector<File> files;
};


ostream& operator<< (ostream& out, const Directory& d) {
	out << d.toString();
	return out;
}


class Project {
public:
	Project(const string& name, int majorVersion, int minorVersion)
		: contents(name), majorVersion(majorVersion), minorVersion(minorVersion)
	{}

	void add(const File& f) {
		contents.add(f);
	}

	string toString() const {
		stringstream ss;
		ss << "cmake_minimum_required(VERSION " << majorVersion << "." << minorVersion << ")" << endl;
		ss << "project(" << contents << ")" << endl;
		ss << "add_executable(" << contents << contents.showContents() << ")" << endl;
		return ss.str();
	}

private:
	Directory contents;
	int majorVersion;
	int minorVersion;
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