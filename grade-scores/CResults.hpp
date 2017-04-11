#pragma once

// This class reads a .csv file of student results with format:
//
// 	    <FIRST_NAME>,[SURNAME],<SCORE>
//
//   The <FIRSTNAME> field is mandatory.
//   The [SURNAME] field may be empty (eg. \"Madonna\" goes by one name).
//   The <SCORE> field is mandatory and must be numeric.
//
//   Duplicate <FIRSTNAME>+[SURNAME] combinations are reported for Debug builds
//   to stderr (one requirement stated:
//
//     "Only output to the console when complied in a debug mode"
//
//   - an odd requirement since feedback is always good), and only the first
//   occurrence is accepted (Debug and Release builds).
//
//   Erroneously formatted lines are ignored but will be reported to stderr
//   for Debug builds due to the requirement mentioned above.
//
// Student results are sorted based on: 
//   1. descending   order of <SCORE>
//   2. alphabetical order of [SURNAME]
//   3. alphabetical order of <FIRST_NAME>
// 
// The sorted results can be saved to a file with the format:
//
//      [SURNAME],<FIRSTNAME>,<SCORE>

#include <string>
#include <set>

#include "CResult.hpp"

namespace Results
{
    class InputFileException : public std::exception
    {
      public:

        InputFileException(const std::string& msg) : mMessage(msg)
        {
        }

        const char* what() const throw ()
        {
            return mMessage.c_str();
        }

      private:

        std::string mMessage;
    };
    //-------------------------------------------------------------------------
    class OutputFileException : public std::exception
    {
      public:

        OutputFileException(const std::string& msg) : mMessage(msg)
        {
        }

        const char* what() const throw ()
        {
            return mMessage.c_str();
        }

      private:

        std::string mMessage;
    };
    //-------------------------------------------------------------------------
    class IndexException : public std::exception
    {
      public:
        const char* what() const throw ()
        {
            return "Index error";
        }
    };
    //-------------------------------------------------------------------------
    class CResults
    {
      public:

        CResults(std::string inputFilePath);
        // Exceptions:
        //   Throws InputFileException if there is an error reading inputFilePath.

        virtual ~CResults();

        void save(std::string outputFilePath);
        // Exceptions:
        //   Throws OutputFileException if there is an error writing outputFilePath.
 
        // The following operations were added to support unit testing:
        
        std::size_t size() const;
        // Number of valid results added by the constructor.
        
        CResult result(std::size_t index) const;
        // Returns the result at the specifed index.
        //
        // Exceptions:
        //   Throws IndexException if the index exceeds the available results.

      private:

        std::set<CResult, CResultHighestScoreAndNameComparator> mResults;
    };

}  // namespace Results
