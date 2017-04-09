#include "stdafx.h"

#include "CResult.hpp"
#include "StringUtils.hpp"

#include <assert.h>
#include <sstream>

//=============================================================================
// class CResult
//=============================================================================

CResult::CResult(const std::string& firstName,
                 const std::string& surname,
                 unsigned int       score)
    : mFirstName(firstName)
    , mSurname(surname)
    , mScore(score)
{
}

CResult::~CResult()
{
}

CResult::CResult(const CResult& source)
    : mFirstName(source.mFirstName)
    , mSurname(source.mSurname)
    , mScore(source.mScore)
{
}

CResult::CResult(const CResult&& source) noexcept
    : mFirstName(std::move(source.mFirstName))
    , mSurname(std::move(source.mSurname))
    , mScore(source.mScore)
{
}

CResult& CResult::operator=(const CResult& source)
{
    if (this != &source)
    {
        mFirstName = source.mFirstName;
        mSurname = source.mSurname;
        mScore = source.mScore;
    }
    return *this;
}

CResult& CResult::operator=(const CResult&& source) noexcept
{
    assert(this != &source);

    mFirstName = std::move(source.mFirstName);
    mSurname = std::move(source.mSurname);
    mScore = source.mScore;

    return *this;
}

std::string CResult::firstName() const
{
    return mFirstName;
}

std::string CResult::surname() const
{
    return mSurname;
}

unsigned int CResult::score() const
{
    return mScore;
}

bool CResult::operator<(const CResult& otherResult) const
{
    std::string lLowercaseSurname(StringUtils::lowercase(mSurname));
    std::string rLowercaseSurname(StringUtils::lowercase(otherResult.mSurname));

    if (lLowercaseSurname < rLowercaseSurname)
    {
        return true;
    }

    return (lLowercaseSurname == rLowercaseSurname)
        && (StringUtils::lowercase(mFirstName)
                < StringUtils::lowercase(otherResult.mFirstName));
}

std::string CResult::str() const
{
    std::stringstream ss;
    ss << "(firstName=" << mFirstName
        << ", surname=" << mSurname
        << ", score=" << mScore
        << ")";
    return ss.str();
}

//=============================================================================
// class CResultHighestScoreAndNameComparator
//=============================================================================

bool 
CResultHighestScoreAndNameComparator::operator()
    (const CResult& lhs, const CResult& rhs) const
{
    if (lhs.score() > rhs.score())
    {
        return true;
    }
    return (lhs.score() == rhs.score())
        && (lhs < rhs);
}


