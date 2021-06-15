#include "CSVReader.h"
#include "CSVWriter.h"
#include <sstream>
#include <gtest/gtest.h>

TEST(CSVReader, BasicTest)
{
    // std::stringstream In("");
    // CCSVReader Reader(In);
    // std::vector<std::string> Row;

    // EXPECT_TRUE(Reader.ReadRow(Row));
    // EXPECT_EQ(Row.size(),5);
    // if(Row.size() >= 5)
    // {
    //     EXPECT_EQ(Row[0], "1");
    //     EXPECT_EQ(Row[1], "2");
    //     EXPECT_EQ(Row[2], "3");
    //     EXPECT_EQ(Row[3], "4");
    //     EXPECT_EQ(Row[4], "5");
    // }
}

TEST(CSVWriter, BasicTest)
{
    // std::stringstream Out;
    // CCSVWriter Writer(Out);
    // std::vector<std::string> Row{"1", "2", "3", "4","5"};

    // EXPECT_TRUE(Writer.WriteRow(Row));
    // EXPECT_EQ(Out.str(),"\"1\",\"2\",\"3\",\"4\",\"5\"\n");

}
