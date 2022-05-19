#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"

#include <string>
#include <sstream>

using namespace std;

TEST(Contains, True) {
	Spreadsheet sheet;
	stringstream test;

	sheet.set_column_names({"Name"," Age"});
	sheet.add_row({"Sam", "24"});
	sheet.add_row({"Jason", "15"});

	sheet.set_selection(new Select_Contains(&sheet, "Name", "Sam"));
	sheet.print_selection(test);
	EXPECT_EQ(test.str(), "Sam 24 \n");
}

TEST(Contains, False) {
	Spreadsheet sheet;
	stringstream test;

	sheet.set_column_names({"Name", "Age"});
	sheet.add_row({"Sam", "24"});
        sheet.add_row({"Jason", "15"});
	sheet.add_row({"Daniel", "34"});

        sheet.set_selection(new Select_Contains(&sheet, "Name", "Adam"));
        sheet.print_selection(test);
	EXPECT_EQ(test.str(), "");
}

TEST(Contains, ContainsA) {
	Spreadsheet sheet;
        stringstream test;

        sheet.set_column_names({"Name", "Age"});
        sheet.add_row({"Sam", "24"});
        sheet.add_row({"Jason", "15"});
        sheet.add_row({"Gilbert", "34"});

        sheet.set_selection(new Select_Contains(&sheet, "Name", "a"));
        sheet.print_selection(test);
        EXPECT_EQ(test.str(), "Sam 24 \nJason 15 \n");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
