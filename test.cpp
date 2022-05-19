#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"

#include <string>
#include <sstream>

using namespace std;

TEST(Not, NoApple) {
	Spreadsheet sheet;
	stringstream test;

	sheet.set_column_names({"Fruit", "Amount"});
	sheet.add_row({"Orange", "2"});
	sheet.add_row({"Apple", "5"});
	sheet.add_row({"Kiwi", "24"});

	//sheet.set_selection(new Select_Not(Select_Contains(&sheet, "Fruit", "Apple")));
	sheet.print_selection(test);
	EXPECT_EQ(test.str(), "Orange 2 \nKiwi 24 \n");
}

TEST(Not, EmptyString) {
	Spreadsheet sheet;
        stringstream test;

        sheet.set_column_names({"Fruit", "Amount"});
        sheet.add_row({"Orange", "2"});
        sheet.add_row({"Apple", "5"});
        sheet.add_row({"Kiwi", "24"});

       // sheet.set_selection(new Select_Not(Select_Contains(&sheet, "Fruit", "")));
        sheet.print_selection(test);
        EXPECT_EQ(test.str(), "");

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
