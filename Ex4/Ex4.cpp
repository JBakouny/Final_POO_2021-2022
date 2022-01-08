#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;

class Item {

public:
	virtual string toString() const = 0;
	virtual double size() const = 0;
	virtual Item* copy() const = 0;
	
	virtual ~Item() {
	}
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

	File* copy() const {
		return new File(*this);
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

	Directory(const Directory& d)
		:name(d.name), items(d.items.size())
	{
		for (size_t i = 0; i < items.size(); ++i) {
			items[i] = d.items[i]->copy();
		}
	}

	void add(const Item& item) {
		items.push_back(item.copy());
	}

	string toString() const {
		stringstream ss;
		ss << name;
		return ss.str();
	}

	Directory* copy() const {
		return new Directory(*this);
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

	Directory& operator= (Directory d) {
		swap(*this, d);
		return *this;
	}

	~Directory() {
		for (auto i : items) {
			delete i;
		}
	}

private:
	string name;
	vector<const Item *> items;
	friend void swap(Directory& d1, Directory& d2);
};

void swap(Directory& d1, Directory& d2) {
	using std::swap;
	swap(d1.name, d2.name);
	swap(d1.items, d2.items);
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

Directory createDirectory(const string& exerciceName) {
	const File excpp(exerciceName, "cpp", 12);
	const File exh(exerciceName, "h", 5);
	Directory ex(exerciceName);
	ex.add(excpp);
	ex.add(exh);
	return ex;
}

int main()
{
	Directory ex3 = createDirectory("Ex3");
	display(ex3);

	Directory ex4("Ex4");
	ex4 = createDirectory("Ex4");
	display(ex4);

	Directory d("Root");
	const File maincpp("main", "cpp", 7);
	d.add(ex3);
	d.add(ex4);
	d.add(maincpp);
	display(d);
	return 0;
}
