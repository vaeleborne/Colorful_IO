#include "../include/Colorful_IO.hpp"
#include <stdio.h>

//Includes dependent on build system
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

bool IsBetween(int number, int min, int max, bool maxInclusive = true, bool minInclusive = true)
{
    if (min > max)
    {
        int temp = min;
        min = max;
        max = temp;
    }

    if (min == max && !maxInclusive && !minInclusive)
    {
        throw std::invalid_argument("Error! Cannot find a number between the same number exclusively!");
    }

    if (!maxInclusive)
    {
        max--;
    }

    if (!minInclusive)
    {
        min++;
    }

    return number >= min && number <= max;
}
namespace ColorfulIO
{
    int GetKey(std::istream& input)
	{
#ifdef _WIN32

if (&input != &std::cin)
{
	//Non standard input stream, will just get a single character
	int c = input.get();
	return c;
}
else
{
	return getch();
}
#else
		if (&input != &std::cin)
		{
			//Non standard input stream, will just get a single character
			int c = input.get();
			return c;
		}

		termios oldt{}, newt{};
		int ch;

		// Get current terminal settings
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;

		// Disable canonical mode and echo
		newt.c_lflag &= ~(ICANON | ECHO);

		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		// Read single character
		ch = getchar();

		// Restore old settings
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

		return ch;
#endif
	}

	bool IsAlphaNumeric(const std::string& string)
	{
		if (string.length() == 0)
			return false;

		for (char c : string)
		{
			if (!std::isalnum(c))
				return false;
		}
		return true;
	}

	bool IsNumeric(const std::string& string)
	{
		if (string.length() == 0)
			return false;

		std::string testStr = string;
		if (string.length() > 1 && string[0] == '-')
		{
			//Can still be numeric, just a negative
			testStr = string.substr(1);
		}

		for (char c : testStr)
		{
			if (!std::isdigit(c))
				return false;
		}
		return true;
	}

	void ClearConsole(std::ostream& output)
	{

#ifdef _WIN32
		if (&output != &std::cout || system("cls") != 0)
		{
			output << "\x1b[2J\x1b[H";	//If clear fails, use ansi to 'clear' (scrolls down)
		}
#else
		if (&output != &std::cout || system("clear") != 0)
		{
			output << "\x1b[2J\x1b[H";	//If clear fails, use ansi to 'clear' (scrolls down)
		}
#endif // _WIN32

	}

	void WriteNewLines(std::ostream& output, unsigned int num)
	{
		if (num == 0)
			throw std::invalid_argument("Should not try to write 0 new lines!");

		for (int i = 0; i < num; i++)
			output << "\n";
	}

	void PressAnyKeyAlert(std::istream& input, std::ostream& output, const std::string& message, bool clearConsole, bool inColor, const std::string& color)
	{
		if (clearConsole)
		{
			ClearConsole(output);
		}

		if (message != "")
		{
			Write(output, message, true, inColor, color);
		}

		Write(output, "Press Any Key To Continue...", true, inColor, color);
		GetKey(input);
	}

	void PressAnyKeyAlert(std::istream& input, std::ostream& output, bool clearConsole, bool inColor, const std::string& color)
	{

		if (clearConsole)
		{
			ClearConsole(output);
		}

		Write(output, "Press Any Key To Continue...", true, inColor, color);
		GetKey(input);
	}

	bool AskYesNo(std::istream& input, std::ostream& output, const std::string& question, bool clearScreen, bool inColor, const std::string& color)
	{
		bool validInput = false;
		do
		{
			if (clearScreen)
				ClearConsole(output);

			Write(output, question + "\nInput (y/n): ", false, inColor, color);

			char inputKey = GetKey(input);

			if (std::isalpha(inputKey))
			{
				inputKey = std::tolower(inputKey);
				if (inputKey == 'y')
				{
					return true;
				}
				else if (inputKey == 'n')
				{
					return false;
				}
			}
			WriteNewLines(output);
			Write(output, "Invalid!", true, true, Colors::Foreground::RED);

		} while (!validInput);
	}

	int GetIntFromUser(std::istream& in, std::ostream& output, int min, int max,  std::string customMessage, bool clearConsole, bool inColor, const std::string& color)
	{
		int number = 0;
		bool valid = false;

		do
		{
			if (clearConsole)
				ClearConsole(output);
			if (inColor)
				output << color;

			if (customMessage == "")
				output << "Please enter a number between " << min << " and " << max << " inclusively: ";
			else
				output << customMessage;

			std::string input = "";
			std::getline(in, input);
			FlushInputBuffer(in);

			if (IsNumeric(input))
			{
				number = std::stoi(input);

				if (IsBetween(number, min, max))
				{
					valid = true;
				}
			}

			if (inColor)
				output << Colors::RESET;

		} while (!valid);

		return number;
	}

	void WriteHeading(std::ostream& output, const std::string& heading, int minimumLength, int minimumPadding, bool clearConsole, bool inColor, const std::string& color)
	{
		if (clearConsole)
			ClearConsole(output);

		int headingWidth = static_cast<int>(heading.length());

		int width = std::max(headingWidth + (2 * minimumPadding), minimumLength);
		std::string line(width, '-');

		int padding = (width - headingWidth) / 2;             //Padding amount for the left       

		Write(output, line, true, inColor, color);
		Write(output, std::string(padding, ' ') + heading + std::string(padding, ' '), true, inColor, color);
		Write(output, line, true, inColor, color);
	}

	void FlushInputBuffer(std::istream& input)
	{
		input.clear();
		input.ignore(input.rdbuf()->in_avail());
	}

	void Write(std::ostream& output, const std::string& message, bool newLine, bool inColor, const std::string& color)
	{
		if (inColor)
		{
			output << color << message << Colors::RESET;
		}
		else
		{
			output << message;
		}

		if (newLine)
			output << "\n";
	}

    std::string GetTrimmedLineFromUser(std::istream& input)
	{
		std::string untrimmed = "";
		std::getline(input, untrimmed);
		FlushInputBuffer(input);

		if (untrimmed.length() == 0)
		{
			throw std::invalid_argument("Cannot trim an empty string!");
		}

		int startIndex = 0;
		int endIndex = untrimmed.length() - 1;

		if (untrimmed.starts_with(' '))
		{
			for (int i = 0; i < untrimmed.length(); i++)
			{
				if (untrimmed[i] != ' ')
				{
					startIndex = i;
					break;
				}
			}
		}

		if (untrimmed.ends_with(' '))
		{
			for (int i = endIndex; i > 0; i--)
			{
				if (untrimmed[i] != ' ')
				{
					endIndex = i;
					break;
				}
			}
		}

		return untrimmed.substr(startIndex, (endIndex + 1) - startIndex);		
	}

	void PauseForSeconds(int seconds)
	{
		std::this_thread::sleep_for(std::chrono::seconds(seconds));
	}

	void PauseForMilliseconds(int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
}
