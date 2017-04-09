#include "stdafx.h"

#include "StringUtils.hpp"

#include <algorithm>
#include <cstring>
#include <locale>

namespace StringUtils
{
    std::string filenameOf(const std::string& path)
    {
        std::size_t lastDirDelimiter = path.find_last_of('\\');
        return (lastDirDelimiter == std::string::npos)
            ? path
            : path.substr(lastDirDelimiter + 1);
    }
    //-----------------------------------------------------------------------------
    bool isPositiveInteger(const std::string& token)
    {
        return token.find_first_not_of("0123456789") == std::string::npos;
    }
    //-----------------------------------------------------------------------------
    std::string lowercase(const std::string& text)
    {
        std::string lowercaseText(text);
        for (char& c : lowercaseText)
        {
            c = std::tolower(c, std::locale());
        }
        return lowercaseText;
    }
    //-----------------------------------------------------------------------------
    std::string newPath(const std::string& inputPath, const std::string& newSuffix)
    {
        std::size_t delimiterPos = inputPath.find_last_of('.');
        return (delimiterPos == std::string::npos)
            ? inputPath
            : inputPath.substr(0, delimiterPos) + newSuffix;
    }
    //-----------------------------------------------------------------------------
    std::vector<std::string> tokens(const std::string& line, char delimiter)
    {
        std::vector<std::string> lineTokens;
        std::string              remainingLine(line);

        // Add tokens from remainingLine to lineTokens, deleting any leading and
        // trailing spaces from the tokens:
        std::size_t delimiterPos = remainingLine.find(delimiter);
        while (delimiterPos != std::string::npos)
        {
            lineTokens.emplace_back(trimmed(remainingLine.substr(0, delimiterPos)));
            remainingLine.erase(0, delimiterPos + 1);
            delimiterPos = remainingLine.find(delimiter);
        }
        lineTokens.emplace_back(trimmed(remainingLine));  // adds last token

        return lineTokens;
    }
    //-------------------------------------------------------------------------
    std::string trimmed(const std::string& token)
    {
        const std::string WHITESPACE(" \t");

        const auto startPos = token.find_first_not_of(WHITESPACE);
        if (startPos == std::string::npos)  // token empty or only contains whitespace
        {
            return "";
        }

        return token.substr(startPos, 
                            token.find_last_not_of(WHITESPACE) - startPos + 1);
    }

}