// grade-scores.cpp : Defines the entry point for the console application.
//
// This is the "main" component of the TransMax Software Developer Exercise.
//
// Refer to the printUsage(...) function for details.

#include "stdafx.h"
#include <string>

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "CResult.hpp"
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
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::string   outputFilePath;

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

            // Ensure that the argument is an existing file:
            inputFile.open(argv[1]);
            if (!inputFile.good())
            {
                printError(EXECUTABLE_NAME, 
                    "Specified file, \"" + std::string(argv[1]) + "\", does not exist!");
                exit(1);
            }

            // Ensure that the output file can be written:
            outputFilePath = StringUtils::newPath(argv[1], OUTPUT_FILE_SUFFIX);
            outputFile.open(outputFilePath);
            if (outputFile.fail())
            {
                printError(EXECUTABLE_NAME, 
                    "Failed to access \"" + outputFilePath + "\"!");
                inputFile.close();
                exit(2);
            }

        }   break;

		default:
			printError(EXECUTABLE_NAME, "Only one input file expected!");
			exit(3);
	}

    // Process the inputFile, adding all valid entries to the results
    //---------------------------------------------------------------

    std::set<CResult, CResultHighestScoreAndNameComparator> results;

    const char CSV_FILE_DELIMITER = ',';

    // Token indexes of inputFile fields when each line is tokenised using the
    // CSV_FILE_DELIMITER:
    const size_t FIRST_NAME = 0;
    const size_t SURNAME    = 1;
    const size_t SCORE      = 2;

    std::string line;
    int         lineNo = 1;
    std::vector<std::string> lineTokens;
    std::set<std::string>    studentsAlreadyProcessed;

    while (getline(inputFile, line))
    {
        lineTokens = StringUtils::tokens(line, CSV_FILE_DELIMITER);
        if (   (lineTokens.size() != 3)  // expected format is <FIRST_NAME>,[SURNAME],<SCORE>
            || (lineTokens[FIRST_NAME].length() == 0)  // <FIRST_NAME> is mandatory
            || (lineTokens[SCORE].length() == 0)       // <SCORE> is mandatory
            || !StringUtils::isPositiveInteger(lineTokens[SCORE]))  // <SCORE> must be a positive integer
        {
#ifdef _DEBUG
            std::cout << "Ignoring invalid line " 
                << lineNo 
                << ": \"" 
                << line 
                << "\"\n";
#endif
        }
        else  // add this Student's result to results if it's not a duplicate
        {
            std::string thisStudent(StringUtils::lowercase
                          (lineTokens[SURNAME] + ',' + lineTokens[FIRST_NAME]));
            if (studentsAlreadyProcessed.find(thisStudent) 
                    != studentsAlreadyProcessed.end())  // thisStudent already processed
            {
#ifdef _DEBUG
                std::cout << "Ignoring duplicate student result at line " 
                    << lineNo
                    << ": \"" 
                    << line 
                    << "\"\n";
#endif
            }
            else
            {
                results.emplace(lineTokens[FIRST_NAME],
                                lineTokens[SURNAME],
                                std::stoi(lineTokens[SCORE]));
                studentsAlreadyProcessed.emplace(thisStudent);
            }
        }

        ++lineNo;
    }
    
    inputFile.close();

    // Write the sorted results to the outputFile
    //-------------------------------------------

    for (auto result : results)
    {
        outputFile << result.surname()
            << ',' << result.firstName()
            << ',' << result.score()
            << std::endl;
    }

    outputFile.close();

#ifdef _DEBUG
    std::cout << "\n+++ Output written to \"" << outputFilePath << "\"\n";
#endif

	return 0;
}

