#include <gtest/gtest.h>
#include <iostream>
void Pause()
{
    std::cout << "\nPress The Enter Key To Continue...\n";
    std::cin.get();
}

//Entry Point for Google Test
int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    int tests = RUN_ALL_TESTS();
    Pause();
    return tests;
}