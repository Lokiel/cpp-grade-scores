
#include "stdafx.h"

#include "CResults.hpp"

#include <iostream>
#include <fstream> 
#include <vector>

#include "StringUtils.hpp"

namespace Results
{
    //=============================================================================
    // class CResults
    //=============================================================================

    CResults::CResults(std::string inputFilePath)
    {
        std::ifstream file(inputFilePath);

        if (!file.is_open())
        {
            throw InputFileException("Failed to open file \"" + inputFilePath + "\"");
        }

        const char CSV_FILE_DELIMITER = ',';

        // Token indexes of inputFilePath fields when each line is tokenised using the
        // CSV_FILE_DELIMITER:
        const size_t FIRST_NAME = 0;
        const size_t SURNAME = 1;
        const size_t SCORE = 2;

        std::string line;
        int         lineNo = 1;
        std::vector<std::string> lineTokens;
        std::set<std::string>    studentsAlreadyProcessed;  // used to ignore duplicates

        while (getline(file, line))
        {
            lineTokens = StringUtils::tokens(line, CSV_FILE_DELIMITER);
            if (   (lineTokens.size() != 3)  // expected format is <FIRST_NAME>,[SURNAME],<SCORE>
                || (lineTokens[FIRST_NAME].length() == 0)  // <FIRST_NAME> is mandatory
                || (lineTokens[SCORE].length() == 0)       // <SCORE> is mandatory
                || !StringUtils::isPositiveInteger(lineTokens[SCORE]))  // <SCORE> must be a positive integer
            {
#ifdef _DEBUG
                std::cerr << "Ignoring invalid line "
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
                    std::cerr << "Ignoring duplicate student result at line "
                        << lineNo
                        << ": \""
                        << line
                        << "\"\n";
#endif
                }
                else
                {
                    mResults.emplace(lineTokens[FIRST_NAME],
                        lineTokens[SURNAME],
                        std::stoi(lineTokens[SCORE]));
                    studentsAlreadyProcessed.emplace(thisStudent);
                }
            }

            ++lineNo;
        }

        if (file.bad())
        { 
            throw InputFileException("Error reading file \"" + inputFilePath + "\"");
        }

        file.close();
    }
    //-------------------------------------------------------------------------
    CResults::~CResults()
    {
    }
    //-------------------------------------------------------------------------
    void CResults::save(std::string outputFilePath)
    {
        std::ofstream file(outputFilePath);

        if (!file.is_open())
        {
            throw OutputFileException("Failed to open file \"" + outputFilePath + "\"");
        }

        for (auto result : mResults)
        {
            file << result.surname()
                << ',' << result.firstName()
                << ',' << result.score()
                << std::endl;
            if (file.bad())
            {
                throw OutputFileException("Error writing file \"" + outputFilePath + "\"");
            }
        }
            
        file.close();
    }
    //-------------------------------------------------------------------------
    std::size_t CResults::size() const
    {
        return mResults.size();
    }
    //-------------------------------------------------------------------------
    CResult CResults::result(std::size_t index) const
    {
        if (index >= mResults.size())
        {
            throw IndexException();
        }

        // mResult is a set so must loop through it to find the required index 
        auto result = mResults.begin();
        for (std::size_t i = 0; i < index; i++)
            ++result;
        return *result;
    }

}  // namespace Results