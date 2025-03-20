#include <gtest/gtest.h>

//Entry Point for Google Test
int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    int tests = RUN_ALL_TESTS();
    system("Pause");
    return tests;
}