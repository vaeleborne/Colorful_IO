#include <gtest/gtest.h>
#include "../include/Colorful_IO.hpp"

// Example test case
TEST(ColorfulIOTest, PrintColored) {
    EXPECT_NO_THROW(ColorfulIO::printColored("Test string"));
}