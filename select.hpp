#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <string>
#include "spreadsheet.hpp"

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.

class Select_Construct_Helper : public Select
{
	public:
		virtual bool select(const Spreadsheet* sheet, int row) const
		{
			return 1;
		}
};

class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column
{
	protected:
		std::string search;
	public:
		Select_Contains(const Spreadsheet* sheet, const std::string& col, const std::string& s) : Select_Column(sheet, col), search(s) {}

	virtual bool select(const std:: string& s) const
	{
		if(s.find(Search) != std:String::npos) return 1;
		return 0;
	}
};

class Select_Not : public Select
{
	protected:
		Select* x;
	public:
		Select_Not(Select* input) : x(input) {}
		
		~Select_Not()
		{
			delete x;
		}

		virtual bool select(const Spreadsheet* sheet, int row) const
		{
			return !x->select(sheet, row);
		}
};

#endif //__SELECT_HPP__
