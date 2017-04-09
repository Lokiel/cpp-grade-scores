#pragma once

// Generic string operations.

#include <string>
#include <vector>

namespace StringUtils
{
    std::string filenameOf(const std::string& fullPathName);
    // Returns the filename component of the fullPathName.
    // eg. 
    //    "\tmp\file.txt" returns "file.txt"
    //    "file.txt"      returns "file.txt"

    bool isPositiveInteger(const std::string& token);
    // Returns True if the token contains only digts.

    std::string lowercase(const std::string& text);
    // Returns the text string in lowercase.

    std::string newPath(const std::string& path, const std::string& newSuffix);
    // Returns a file path constructed from path and newSuffix.
    //
    // If path contains a suffix type, such as ".txt", ".dat", it is
    // stripped before the newSuffix is appended to it.

    std::vector<std::string> tokens(const std::string& line, char delimiter);
    // Returns a vector of tokens from the line, delimited by the delimiter character.
    // Tokens do not include leading and trailing whitespace.

     std::string trimmed(const std::string& token);
    // Returns token with any leading and trailing whitespace trimmed.
}
