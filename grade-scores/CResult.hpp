#pragma once

#include <string>

namespace Results
{

    //=============================================================================
    // class CResult
    //
    // This class defines the result of an individual's test, including their name
    // and "score".
    //=============================================================================

    class CResult
    {
      public:

        CResult(const std::string& firstName,
                const std::string& surname,
                unsigned int       score);

        virtual ~CResult();

        CResult(const CResult&);
        CResult(const CResult&&) noexcept;

        CResult& operator=(const CResult&);
        CResult& operator=(const CResult&&) noexcept;

        std::string  firstName() const;
        std::string  surname()   const;
        unsigned int score()     const;

        std::string str() const;

        bool operator<(const CResult& otherResult) const;
        // Default comparator function, sorting in alphabetical order of surname
        // (case-insensitive), then alphabetical order of first name
        // (case-insensitive).
        //
        // Used by sortable containers with CResult elements.

      private:

        std::string  mFirstName;
        std::string  mSurname;
        unsigned int mScore;
    };

    //=============================================================================
    // class CResultHighestScoreAndNameComparator
    //
    // Alternate comparator function for CResult objects when they're elements of a
    // sortable collection.
    // Sorts in descending order of score, then alphabetical order of surname, then
    // alphabetical order of first name.
    //=============================================================================

    class CResultHighestScoreAndNameComparator
    {
      public:
        bool operator()(const CResult& l, const CResult& r) const;
    };

}  // namespace Results