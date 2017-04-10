// grade-scores.cpp : Defines the entry point for the console application.
//
// This is the "main" component of the TransMax Software Developer Exercise.
//
// Refer to the printUsage(...) function for details.

#include "stdafx.h"
#include <string>

#include <fstream>
#include <iostream>
#include <string>

#include "CResult.hpp"
#include "CResults.hpp"
#include "StringUtils.hpp"

const std::string OUTPUT_FILE_SUFFIX("-graded.txt");

//-----------------------------------------------------------------------------
void printUsage(const std::string& programName)
{
#ifdef _DEBUG
    std::cout << "Usage: " << programName << " <INPUT_FILE>\n"
		"where\n"
		"    <INPUT_FILE> is a .csv file with the format:\n"
		"\n"
		"    <FIRST_NAME>,[SURNAME],<SCORE>\n"
		"\n"
		"       The <FIRSTNAME> field is mandatory.\n"
		"       The [SURNAME] field may be empty (eg. \"Madonna\" goes by one name).\n"
		"       The <SCORE> field is mandatory and must be numeric.\n"
		"       Duplicate <FIRSTNAME>+[SURNAME] combinations are reported and only the\n"
		"       first occurrence is accepted.\n"
		"\n"
		"   Output is written to file <INPUT_FILE>" << OUTPUT_FILE_SUFFIX << " with format:\n"
		"\n"
		"      [SURNAME],<FIRSTNAME>,<SCORE>\n"
		"\n"
		"   The output is sorted by highest <SCORE> and alphabetically on\n"
		"   [SURNAME]+<FIRSTNAME> of students achieving that score.\n";
#endif
}
//-----------------------------------------------------------------------------
void printError(const std::string& programName, const std::string& errorMsg)
{
#ifdef _DEBUG
    std::cout << "ERROR: " << errorMsg << std::endl << std::endl;
	printUsage(programName);
#endif
}

//=============================================================================
// Main
//=============================================================================

int main(int argc, char* argv[])
{
    // Process command line parameters
    //--------------------------------

    const std::string EXECUTABLE_NAME(StringUtils::filenameOf(argv[0]));

    switch (argc)
    {
        case 1:
            printUsage(EXECUTABLE_NAME);
            exit(0);

        case 2:
        {
            // Print usage information if the argument is a "help flag":
            const std::set<std::string> HELP_FLAGS{ "-h","/h","--help","-?","/?" };
            if (HELP_FLAGS.find(argv[1]) != HELP_FLAGS.end())
            {
                printUsage(EXECUTABLE_NAME);
                exit(0);
            }
        }   break;

		default:
			printError(EXECUTABLE_NAME, "Only one input file expected!");
			exit(1);
	}

    // Process the input file, adding all valid entries to the results
    //--------------------=-------------------------------------------

    try
    {
        std::string outputFilePath
                        (StringUtils::newPath(argv[1], OUTPUT_FILE_SUFFIX));
        Results::CResults results(argv[1]);
        results.save(outputFilePath);

#ifdef _DEBUG
        std::cout << "\n+++ Output written to \"" << outputFilePath << "\"\n";
#endif
    }

    catch(Results::InputFileException e)
    {
#ifdef _DEBUG
        std::cerr << "\n*** " << e.what() << std::endl;
#endif
        exit(2);
    }

    catch(Results::OutputFileException e)
    {
#ifdef _DEBUG
        std::cerr << "\n*** " << e.what() << std::endl;
#endif
        exit(3);
    }

	return 0;
}

