#include <cctype>
#include <iostream>
#include <string>
#include <vector>


/*
  Transform a single character into a string representation.
    
    If the input is a character, returns a upper case single-character.
    If the input is a number ('0'..'9'), returns the corresponding word in uppercase.
    For any other character, returns an empty std::string to omit.
 
    inputs: 
        in_char : character to be transformed
    returns:
        transformed string representation of the input character
 */
std::string transformChar(const char in_char){
    // Uppercase alphabetic characters
        if (std::isalpha(in_char)) {
            return std::string(1, std::toupper(in_char));
        }

        // Transliterate digits to English words
        switch (in_char) {
            case '0':
                return "ZERO";
            case '1':
                return "ONE";
            case '2':
                return "TWO";
            case '3':
                return "THREE";
            case '4':
                return "FOUR";
            case '5':
                return "FIVE";
            case '6':
                return "SIX";
            case '7':
                return "SEVEN";
            case '8':
                return "EIGHT";
            case '9':
                return "NINE";
        }

        // If the character isn't alphabetic or numeric, DONT add it
        return "";

}

/*
  Parse command-line options for the mpags-cipher program.
 
  Parses the provided argument vector starting at index 1 (skipping the program
  name), looking for these flags only:
    -h, --help        -> sets helpRequested to true
    --version         -> sets versionRequested to true
    -i <filename>     -> sets inputFile to the given filename
    -o <filename>     -> sets outputFile to the given filename

    inputs:
        cmdLineArgs      : vector of command-line arguments
        helpRequested    : reference to bool to be set if help requested
        versionRequested : reference to bool to be set if version requested
        inputFile       : reference to string to be set if input file specified
        outputFile      : reference to string to be set if output file specified
    returns:
        0 on success, 1 on failure
 */
bool processCommandLine(const std::vector<std::string>& cmdLineArgs, bool& helpRequested, bool& versionRequested, std::string& inputFile, std::string& outputFile){
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};

    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
                helpRequested = true;
            } else if (cmdLineArgs[i] == "--version") {
                versionRequested = true;
            } else if (cmdLineArgs[i] == "-i") {
                // Handle input file option
                // Next element is filename unless "-i" is the last argument
                if (i == nCmdLineArgs - 1) {
                    std::cerr << "[error] -i requires a filename argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return 1;
                } else {
                    // Got filename, so assign value and advance past it
                    inputFile = cmdLineArgs[i + 1];
                    ++i;
                }
            } else if (cmdLineArgs[i] == "-o") {
                // Handle output file option
                // Next element is filename unless "-o" is the last argument
                if (i == nCmdLineArgs - 1) {
                    std::cerr << "[error] -o requires a filename argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return 1;
                } else {
                    // Got filename, so assign value and advance past it
                    outputFile = cmdLineArgs[i + 1];
                    ++i;
                }
            } else {
                // Have an unknown flag to output error message and return non-zero
                // exit status to indicate failure
                std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                        << "'\n";
                return 1;
            }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    if (processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile) == 1){
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;


    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    // loop over each character from user input
    while (std::cin >> inputChar) {
        inputText += transformChar(inputChar);

        // If the character isn't alphabetic or numeric, DONT add it
    }

    // Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
