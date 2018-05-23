#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class csvfile;

inline static csvfile& endrow(csvfile& file);
inline static csvfile& flush(csvfile& file);

class csvfile
{
	ofstream fs_;
	bool is_first_;
	const string separator_;
	const string escape_seq_;
	const string special_chars_;
public:
	csvfile(const string filename, const string separator = ";")
		: fs_()
		, is_first_(true)
		, separator_(separator)
		, escape_seq_("\"")
		, special_chars_("\"")
	{
		fs_.exceptions(ios::failbit | ios::badbit);
		fs_.open(filename);
	}

	~csvfile()
	{
		flush();
		fs_.close();
	}

	void flush()
	{
		fs_.flush();
	}

	void endrow()
	{
		fs_ << endl;
		is_first_ = true;
	}

	csvfile& operator << (csvfile& (*val)(csvfile&))
	{
		return val(*this);
	}

	csvfile& operator << (const char * val)
	{
		return write(escape(val));
	}

	csvfile& operator << (const string & val)
	{
		return write(escape(val));
	}

	template<typename T>
	csvfile& operator << (const T& val)
	{
		return write(val);
	}

private:
	template<typename T>
	csvfile& write(const T& val)
	{
		if (!is_first_)
		{
			fs_ << separator_;
		}
		else
		{
			is_first_ = false;
		}
		fs_ << val;
		return *this;
	}

	string escape(const string & val)
	{
		ostringstream result;
		result << '"';
		string::size_type to, from = 0u, len = val.length();
		while (from < len &&
			string::npos != (to = val.find_first_of(special_chars_, from)))
		{
			result << val.substr(from, to - from) << escape_seq_ << val[to];
			from = to + 1;
		}
		result << val.substr(from) << '"';
		return result.str();
	}
};


inline static csvfile& endrow(csvfile& file)
{
	file.endrow();
	return file;
}

inline static csvfile& flush(csvfile& file)
{
	file.flush();
	return file;
}
