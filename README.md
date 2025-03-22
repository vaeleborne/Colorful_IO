# 🎨 Colorful_IO

Colorful_IO is a custom C++ library (built as a DLL) that provides a clean and flexible way to enhance terminal-based applications with colorful, styled output and interactive utilities — perfect for making console tools more engaging and readable.

✅ Built as a dynamic library (DLL) with clean headers and source separation — not header-only!

##✨ Features

🌈 Colorful Output

Style your terminal output using ANSI escape codes
Functions return std::string so you can use any std::ostream (e.g., std::cout, std::ostringstream, file streams, etc.)
Works best in ANSI-compatible environments (Linux/macOS terminals, modern Windows terminals)
_Note: If using the Color output be sure your output stream supports ANSI escape codes, or handle it gracefully if it doesn’t._

🛠️ Helpful Terminal Utilities

Print section headings and dividers
Prompt users with yes/no questions
Wait for a key press with a custom message
Other utilities to streamline CLI UX

💡 Customizable
Designed with flexibility in mind — pass in your own streams and styles.

🔧 Modular & Reusable

Just include the header and link the DLL
Easy to integrate into any C++ project

#📦 Installation / Setup
Build the DLL (CMakeLists are included!)
Include the headers in your project
Link against the DLL import library

#🚀 Basic Usage

 ```cpp
#include <Colorful_IO.hpp>

int main()
{
	ColorfulIO::WriteHeading(std::cout, "EXAMPLE CODE", 60, 5, false, true, ColorfulIO::Colors::Foreground::BOLD_BLUE);

	if(ColorfulIO::AskYesNo(std::cin, std::cout, "Would you like to write a sample message in color?", false))
	{
		ColorfulIO::Write(std::cout, "Hello World! This is in Color!", true, true, ColorfulIO::Colors::Foreground::CYAN);
	}
	else
	{
		ColorfulIO::Write(std::cout, "Hello World! This is NOT in Color!");
	}

	ColorfulIO::WriteNewLines(std::cout, 3);
	ColorfulIO::PressAnyKeyAlert(std::cin, std::cout, false);	//Default message for alert, no new line or color
	
	//Write on one line to prompt user
	ColorfulIO::Write(std::cout, "Input Your Name: ", false);
	std::string user = ColorfulIO::GetTrimmedLineFromUser(std::cin);

	//Since we didn't end with a new line we need to add that here or call writenewlines to get one before next message
	ColorfulIO::Write(std::cout, "\nProcessing...", true);
	ColorfulIO::PauseForMilliseconds(50);
	ColorfulIO::Write(std::cout, "Sucess!", true, true, ColorfulIO::Colors::Foreground::GREEN);
	ColorfulIO::PressAnyKeyAlert(std::cin, std::cout, "Press Any Key To Exit!");	//Custom message for alert, defaults with no new line or color

}

```


#🔐 License
MIT License

