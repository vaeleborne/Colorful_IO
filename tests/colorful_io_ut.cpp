#include <gtest/gtest.h>
#include <sstream>
#include <chrono>
#include "../include/Colorful_IO.hpp"

namespace io = ColorfulIO;

// Example test case
//GET KEY TEST, USED IN SEVERAL OTHERS SO TESTING FIRST
TEST(InputTest, GetKey_ReturnsExpectedKey)
{
	std::istringstream mockInput(" ");
	EXPECT_EQ(0x20, io::GetKey(mockInput));

	mockInput.str("23");

	EXPECT_EQ(0x32, io::GetKey(mockInput));
}

TEST(InputTest, GetKey_ReturnsExpectedKeyWithinLoopedInput)
{
	std::istringstream mockInput("23a");
	EXPECT_EQ(0x32, io::GetKey(mockInput));
	EXPECT_EQ(0x33, io::GetKey(mockInput));
	EXPECT_EQ(0x61, io::GetKey(mockInput));
}


//LOGIC TESTING

TEST(LogicTests, IsAlphaNumeric_ReturnsExpectedValues)
{
	EXPECT_TRUE(io::IsAlphaNumeric("A"));
	EXPECT_TRUE(io::IsAlphaNumeric("b"));
	EXPECT_TRUE(io::IsAlphaNumeric("9"));
	EXPECT_TRUE(io::IsAlphaNumeric("9223372036854775807000")); //BIG NUMBER STILL NUMERIC EVEN IF GREATER THAN INT
	EXPECT_TRUE(io::IsAlphaNumeric("adfjsdkjkselkrFWASR11434353634"));	//LETTERS AND NUMBERS

	EXPECT_FALSE(io::IsAlphaNumeric(""));
	EXPECT_FALSE(io::IsAlphaNumeric("-"));
	EXPECT_FALSE(io::IsAlphaNumeric("-1"));			//NEGATIVE NUMBERS ARE NOT CONSIDERED ALPHA-NUMERIC, THEY ARE HOWEVER NUMERIC
	EXPECT_FALSE(io::IsAlphaNumeric("-23298"));
	EXPECT_FALSE(io::IsAlphaNumeric("!@"));
	EXPECT_FALSE(io::IsAlphaNumeric("123+"));
	EXPECT_FALSE(io::IsAlphaNumeric("Abc123*"));
}

TEST(LogicTests, IsNumeric_ReturnsExpectedValues)
{
	EXPECT_TRUE(io::IsNumeric("1"));
	EXPECT_TRUE(io::IsNumeric("-1"));
	EXPECT_TRUE(io::IsNumeric("9223372036854775807000")); //BIG NUMBER STILL NUMERIC EVEN IF GREATER THAN INT
	EXPECT_TRUE(io::IsNumeric("-9223372036854775807000"));

	EXPECT_FALSE(io::IsNumeric(""));
	EXPECT_FALSE(io::IsNumeric("-"));
	EXPECT_FALSE(io::IsNumeric("24a"));
	EXPECT_FALSE(io::IsNumeric("24a5"));
	EXPECT_FALSE(io::IsNumeric("a"));
	EXPECT_FALSE(io::IsNumeric("hello"));
}


//OUTPUT TESTING

TEST(OutputTests, Write_InColor_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		io::Write(std::cout, "Hello Unit Tests!", true, true, io::Colors::Foreground::BLUE);
	});
}

TEST(OutputTests, WriteHeading_InColor_ExpectNoFatalError) {
	EXPECT_NO_FATAL_FAILURE({
		io::WriteHeading(std::cout, "TEST HEADING", 50, 5, false, true, io::Colors::Foreground::HI_MAGENTA);
		});
}

TEST(OutputTests, Write_CorrectMessageGoesToOutput)
{
	std::stringstream actualOutput;
	std::stringstream expectedOutput;

	std::string message = "TESTING MESSAGE";

	expectedOutput << message;

	io::Write(actualOutput, message, false);

	EXPECT_EQ(expectedOutput.str(), actualOutput.str());
}

TEST(OutputTests, Write_InColor_CorrectMessageGoesToOutput_WithColorEscapeCodes_NoNewLine)
{
	std::stringstream actualOutput;
	std::stringstream expectedOutput;

	std::string color = io::Colors::Foreground::YELLOW;
	std::string message = "TESTING MESSAGE";

	expectedOutput << color << message << io::Colors::RESET;

	io::Write(actualOutput, message, false, true, color);

	EXPECT_EQ(expectedOutput.str(), actualOutput.str());
}

TEST(OutputTests, Write_InColor_CorrectMessageGoesToOutput_WithColorEscapeCodes_WithNewLine)
{
	std::stringstream actual;
	std::stringstream expected;

	std::string color = io::Colors::Foreground::HI_YELLOW;
	std::string message = "TESTING MESSAGE";

	expected << color << message << io::Colors::RESET << "\n";

	io::Write(actual, message, true, true, color);

	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, ClearConsole_SendsClearEscapeSequenceForNonNativeConsoleOutput)
{
	std::stringstream actualOutput;
	io::ClearConsole(actualOutput);

	EXPECT_EQ("\x1b[2J\x1b[H", actualOutput.str());
}

TEST(OutputTests, WriteNewLines_AddsOneNewLineByDefault)
{
	std::stringstream actual;
	std::stringstream expected;

	expected << "\n";

	io::WriteNewLines(actual);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, WriteNewLines_AddsCorrectNumberOfLinesWhenNumberPassedIn)
{
	std::stringstream actual;
	std::stringstream expected;

	expected << "\n\n\n\n";

	io::WriteNewLines(actual, 4);
	EXPECT_EQ(expected.str(), actual.str());
	expected << "\n\n";
	io::WriteNewLines(actual, 2);
	EXPECT_EQ(expected.str(), actual.str());

}

TEST(OutputTests, WriteNewLines_ThrowsErrorIfZeroIsPassedIn)
{
	EXPECT_THROW(io::WriteNewLines(std::cout, 0), std::invalid_argument);
}

TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_NoColor_NoClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::istringstream keyPress(" ");

	expected << "Press Any Key To Continue...\n";
	io::PressAnyKeyAlert(keyPress, actual, false);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_NoColor_WithClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::istringstream keyPress(" ");

	expected << "\x1b[2J\x1b[HPress Any Key To Continue...\n";
	io::PressAnyKeyAlert(keyPress, actual, true);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_WithColor_WithClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::istringstream keyPress(" ");

	expected << "\x1b[2J\x1b[H" << io::Colors::Foreground::BLUE <<  "Press Any Key To Continue..." << io::Colors::RESET << "\n";
	io::PressAnyKeyAlert(keyPress, actual, true, true, io::Colors::Foreground::BLUE);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PressAnyKeyAlert_NoAdditionalMessage_ShowsCorrectPrompt_WithColor_NoClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::istringstream keyPress(" ");

	expected << io::Colors::Foreground::BLUE << "Press Any Key To Continue..." << io::Colors::RESET << "\n";

	io::PressAnyKeyAlert(keyPress, actual, false, true, io::Colors::Foreground::BLUE);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_NoColor_NoClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::string message = "Unit Testing!";
	std::istringstream keyPress(" ");

	expected << message << "\nPress Any Key To Continue...\n";
	io::PressAnyKeyAlert(keyPress, actual, message, false);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_NoColor_WithClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::string message = "Unit Testing!";
	std::istringstream keyPress(" ");

	expected << "\x1b[2J\x1b[H" << message << "\nPress Any Key To Continue...\n";
	io::PressAnyKeyAlert(keyPress, actual, message, true);
	EXPECT_EQ(expected.str(), actual.str());

}

TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_WithColor_WithClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::string message = "Unit Testing!";
	std::istringstream keyPress(" ");

	expected << "\x1b[2J\x1b[H" << io::Colors::Foreground::YELLOW << message  << io::Colors::RESET << "\n" 
    << io::Colors::Foreground::YELLOW << "Press Any Key To Continue..." << io::Colors::RESET << "\n";

	io::PressAnyKeyAlert(keyPress, actual, message, true, true, io::Colors::Foreground::YELLOW);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PressAnyKeyAlert_CustomAdditionalMessage_ShowsCorrectPrompt_WithColor_NoClearConsole)
{
	std::stringstream actual;
	std::stringstream expected;
	std::string message = "Unit Testing!";
	std::istringstream keyPress(" ");

	expected << io::Colors::Foreground::YELLOW << message << io::Colors::RESET << "\n" << io::Colors::Foreground::YELLOW << "Press Any Key To Continue..." 
    << io::Colors::RESET << "\n";

	io::PressAnyKeyAlert(keyPress, actual, message, false, true, io::Colors::Foreground::YELLOW);
	EXPECT_EQ(expected.str(), actual.str());
}

TEST(OutputTests, PauseForSeconds_CorrectTimeWaited)
{
	const int pauseDuration = 1;
	const auto allowedMarginMs = 50;

	auto start = std::chrono::steady_clock::now();
	io::PauseForSeconds(pauseDuration);
	auto end = std::chrono::steady_clock::now();

	auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	EXPECT_GE(elapsedMs, pauseDuration * 1000);
	EXPECT_LE(elapsedMs, (pauseDuration * 1000) + allowedMarginMs);
}

TEST(OutputTests, PauseForMilliseconds_CorrectTimeWaited)
{
	const int pauseDuration = 200;
	const auto allowedMarginMs = 50;

	auto start = std::chrono::steady_clock::now();
	io::PauseForMilliseconds(pauseDuration);
	auto end = std::chrono::steady_clock::now();

	auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	EXPECT_GE(elapsedMs, pauseDuration);
	EXPECT_LE(elapsedMs, pauseDuration + allowedMarginMs);
}

//INPUT TESTING

TEST(InputTests, AskYesNo_ReturnsTrueWhenInputIsY)
{
	std::istringstream mockInput("y");
	std::stringstream out;
	EXPECT_TRUE(io::AskYesNo(mockInput, out, "Unit Test Answers y", false));

	mockInput.str("Y");
	EXPECT_TRUE(io::AskYesNo(mockInput, out, "Unit Test Answers Y", false));
}

TEST(InputTests, AskYesNo_ReturnsFalseWhenInputIsN)
{
	std::istringstream mockInput("n");
	std::stringstream out;

	EXPECT_FALSE(io::AskYesNo(mockInput, out, "Unit Test Answers n", false));

	mockInput.str("N");
	EXPECT_FALSE(io::AskYesNo(mockInput, out, "Unit Test Answers N", false));
}

TEST(InputTests, AskYesNo_AsksMoreThanOnceUntilValidInputIsGiven)
{
	std::istringstream mockInput("a23y");
	std::stringstream out;
	EXPECT_TRUE(io::AskYesNo(mockInput, out, "Unit Test Answers y", false));

	mockInput.str("j82!n");
	EXPECT_FALSE(io::AskYesNo(mockInput, out, "Unit Test Answers y", false));
}

TEST(InputTests, GetIntFromUser_ReturnsExpectedValues)
{
	std::istringstream mockInput("10\n");
	std::stringstream mockOutput;

	int expectedInt = 10;

	int actualInt = io::GetIntFromUser(mockInput, mockOutput, -10, 10);

	EXPECT_EQ(expectedInt, actualInt);

	expectedInt = -10;
	mockInput.clear();
	mockInput.str("-10\n");
	actualInt = io::GetIntFromUser(mockInput, mockOutput, -10, 10);
	EXPECT_EQ(expectedInt, actualInt);
}
