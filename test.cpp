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

TEST(Not, NoApple) {
	Spreadsheet sheet;
	stringstream test;

	sheet.set_column_names({"Fruit", "Amount"});
	sheet.add_row({"Orange", "2"});
	sheet.add_row({"Apple", "5"});
	sheet.add_row({"Kiwi", "24"});

	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Fruit", "Apple")));
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

        sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Fruit", "")));
        sheet.print_selection(test);
        EXPECT_EQ(test.str(), "");

}

TEST(Not, NoE) {
	Spreadsheet sheet;
        stringstream test;

        sheet.set_column_names({"Fruit", "Amount"});
        sheet.add_row({"Orange", "2"});
        sheet.add_row({"Apple", "5"});
        sheet.add_row({"Kiwi", "24"});
	sheet.add_row({"Banana", "13"});

	sheet.set_selection(new Select_Not(new Select_Contains(&sheet, "Fruit", "e")));
        sheet.print_selection(test);
        EXPECT_EQ(test.str(), "Kiwi 24 \nBanana 13 \n");
}

TEST(Select_And, BothTrue)
{
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Amanda"));
        ASSERT_TRUE(select->select(sheet,0));
        delete select;
}

TEST(Select_And, BothFalse)
{
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Jaskson"), new Select_Contains(sheet, "First", "Francine"));
        ASSERT_FALSE(select->select(sheet,0));
        delete select;
}

TEST(Select_And, OneTrueOneFalse)
{
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Francine"));
        ASSERT_FALSE(select->select(sheet,0));
        delete select;
        delete sheet;
}

TEST(Select_Or, BothTrue)
{
	Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Amanda"));
	ASSERT_TRUE(select->select(sheet,0));
	delete select;
}

TEST(Select_Or, BothFalse)
{
	Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Jaskson"), new Select_Contains(sheet, "First", "Francine"));
	ASSERT_FALSE(select->select(sheet,0));
	delete select;
}

TEST(Select_Or, OneTrueOneFalse)
{
	Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Francine"));
	ASSERT_TRUE(select->select(sheet,0));
	delete select;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
