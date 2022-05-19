#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"

#include <string>
#include <sstream>

using namespace std;

TEST(Spreadsheet, AddToSheet) {
	Spreadsheet sheet;
	stringstream test;
	
	sheet.set_column_names({"Name", "Age", "ID"});
	sheet.add_row({"Eden", "20", "173694"});

	sheet.print_selection(test);
	EXPECT_EQ(test.str(), "Eden 20 173694 \n");
}

TEST(Spreadsheet, EmptyRow) {
        Spreadsheet sheet;
        stringstream test;

        sheet.set_column_names({"Name", "Age", "ID"});
        sheet.add_row({"", "", ""});

        sheet.print_selection(test);
        EXPECT_EQ(test.str(), "   \n");

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
