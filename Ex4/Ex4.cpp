#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Item {

public:
	virtual string toString() const = 0;
	virtual double size() const = 0;

};

ostream& operator<< (ostream& out, const Item& item) {
	out << item.toString();
	return out;
}

class File : public Item {

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

class Directory : public Item {
public:
	Directory(const string& name)
		: name(name)
	{}

	void add(const Item& item) {
		items.push_back(&item);
	}

	string toString() const {
		stringstream ss;
		ss << name;
		return ss.str();
	}

	string showContents(string sep = "") const {
		if (items.size() == 0) {
			return "";
		}
		stringstream ss;
		ss << *items[0];
		for (size_t i = 1; i < items.size(); ++i) {
			ss << sep << " " << *items[i];
		}
		return ss.str();
	}

	double size() const {
		double res = 0;
		for (auto i : items) {
			res += i->size();
		}
		return res;
	}

private:
	string name;
	vector<const Item *> items;
};

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
		ss << "add_executable(" << contents << " " << contents.showContents() << ")" << endl;
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

void display(const Directory& d) {
	cout << "Directory: " << d << endl;
	cout << "Contents:  " << d.showContents() << endl;
	cout << "Contents with comma: " << d.showContents(",") << endl;
	cout << "Size:  " << d.size() << " KB" << endl << endl;
}

int main()
{
	const File ex3cpp("Ex3", "cpp", 12);
	const File ex3h("Ex3", "h", 5);
	Directory ex3("Ex3");
	ex3.add(ex3cpp);
	ex3.add(ex3h);
	display(ex3);

	const File ex4cpp("Ex4", "cpp", 15);
	const File ex4h("Ex4", "h", 5);
	Directory ex4("Ex4");
	ex4.add(ex4cpp);
	ex4.add(ex4h);
	display(ex4);

	Directory d("Root");
	const File maincpp("main", "cpp", 7);
	d.add(ex3);
	d.add(ex4);
	d.add(maincpp);
	display(d);
	return 0;
}