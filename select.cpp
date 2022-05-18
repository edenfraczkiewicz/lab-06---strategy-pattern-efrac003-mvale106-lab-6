#include "select.hpp"

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//Select_Column
Select_Column(const Spreadsheet* sheet, const std::string& name) {
	column = sheet->get_column_by_name(name);
}

virtual bool select(const Spreadsheet* sheet, int row) const {
        return select(sheet->cell_data(row, column));
}

//Select_Contains


//Select_Not


//Select_And


//Select_Or
