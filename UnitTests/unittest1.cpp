#include "stdafx.h"
#include "CppUnitTest.h"

#include <set>

#include "..\grade-scores\StringUtils.hpp"
#include "..\grade-scores\CResult.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
    TEST_CLASS(StringUtilsNamespace)
    {
    public:

        TEST_METHOD(Test_filenameOf)
        {
            const std::string SIMPLE_FILE_NAME("Test.txt");

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf(SIMPLE_FILE_NAME),
                L"Simple file name failed",
                LINE_INFO());

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf("\\" + SIMPLE_FILE_NAME),
                L"File name in root directory failed",
                LINE_INFO());

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf("\\testDir\\" + SIMPLE_FILE_NAME),
                L"Single absolute dir in path name failed",
                LINE_INFO());

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf("\\testDir\\childDir\\grandChildDir\\" + SIMPLE_FILE_NAME),
                L"Multiple absolute dirs in path name failed",
                LINE_INFO());

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf("testDir\\" + SIMPLE_FILE_NAME),
                L"Single relative dir in path name failed",
                LINE_INFO());

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf("testDir\\childDir\\grandChildDir\\" + SIMPLE_FILE_NAME),
                L"Multiple relative dirs in path name failed",
                LINE_INFO());

            Assert::AreEqual(SIMPLE_FILE_NAME,
                StringUtils::filenameOf("..\\..\\testDir\\childDir\\grandChildDir\\" + SIMPLE_FILE_NAME),
                L"Multiple relative dirs in path name failed",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_isPositiveInteger)
        {
            // Test valid positive integer strings:

            Assert::AreEqual(true,
                StringUtils::isPositiveInteger("4"),
                L"Single numeric failed",
                LINE_INFO());

            Assert::AreEqual(true,
                StringUtils::isPositiveInteger("9876543210"),
                L"Long numeric failed",
                LINE_INFO());

            // Test invalid positive integer strings:

            Assert::AreEqual(false,
                StringUtils::isPositiveInteger("x"),
                L"Single Non-numeric failed",
                LINE_INFO());

            Assert::AreEqual(false,
                StringUtils::isPositiveInteger("aFmqZ"),
                L"Long Non-numeric failed",
                LINE_INFO());

            Assert::AreEqual(false,
                StringUtils::isPositiveInteger(" 1234"),
                L"Integer with leading space string failed",
                LINE_INFO());

            Assert::AreEqual(false,
                StringUtils::isPositiveInteger("9876 "),
                L"Integer with trailing space string failed",
                LINE_INFO());

            Assert::AreEqual(false,
                StringUtils::isPositiveInteger("1234.5"),
                L"Float string failed",
                LINE_INFO());

            Assert::AreEqual(false,
                StringUtils::isPositiveInteger("-987"),
                L"Negative integer string failed",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_lowercase)
        {
            Assert::AreEqual(std::string("a"),
                StringUtils::lowercase("a"),
                L"Unrequired lowercase conversion failed",
                LINE_INFO());

            Assert::AreEqual(std::string(" az "),
                StringUtils::lowercase(" AZ "),
                L"Required lowercase conversion failed",
                LINE_INFO());

            Assert::AreEqual(std::string("  a bc def ghij  "),
                StringUtils::lowercase("  a BC def GHIJ  "),
                L"Lowercase conversion failed",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_newPath)
        {
            const std::string SIMPLE_FILE_NAME("Test.txt");
            const std::string NEW_SUFFIX("_Processed.dat");

            Assert::AreEqual(std::string("Test" + NEW_SUFFIX),
                StringUtils::newPath(SIMPLE_FILE_NAME, NEW_SUFFIX),
                L"Simple file name failed",
                LINE_INFO());

            Assert::AreEqual(std::string("\\Test" + NEW_SUFFIX),
                StringUtils::newPath("\\" + SIMPLE_FILE_NAME, NEW_SUFFIX),
                L"File name in root directory failed",
                LINE_INFO());

            Assert::AreEqual(std::string("\\testDir\\Test" + NEW_SUFFIX),
                StringUtils::newPath("\\testDir\\" + SIMPLE_FILE_NAME, NEW_SUFFIX),
                L"Single absolute dir in path name failed",
                LINE_INFO());

            Assert::AreEqual(std::string("\\Dir1\\Dir2\\..\\Dir3\\Test" + NEW_SUFFIX),
                StringUtils::newPath("\\Dir1\\Dir2\\..\\Dir3\\" + SIMPLE_FILE_NAME, NEW_SUFFIX),
                L"Multiple absolute dirs in path name failed",
                LINE_INFO());

            Assert::AreEqual(std::string("testDir\\Test" + NEW_SUFFIX),
                StringUtils::newPath("testDir\\" + SIMPLE_FILE_NAME, NEW_SUFFIX),
                L"Single relative dir in path name failed",
                LINE_INFO());

            Assert::AreEqual(std::string("..\\..\\testDir\\Test" + NEW_SUFFIX),
                StringUtils::newPath("..\\..\\testDir\\" + SIMPLE_FILE_NAME, NEW_SUFFIX),
                L"Multiple relative dirs in path name failed",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_tokens)
        {
            std::vector<std::string> tokens;

            tokens = StringUtils::tokens("", ',');
            Assert::AreEqual(std::size_t(1),
                tokens.size(),
                L"Empty string length test failed",
                LINE_INFO());
            Assert::AreEqual(std::string(""),
                tokens[0],
                L"Empty string test failed",
                LINE_INFO());

            tokens = StringUtils::tokens(" token\t ", ',');
            Assert::AreEqual(std::size_t(1),
                tokens.size(),
                L"Single token length test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("token"),
                tokens[0],
                L"Single token test failed",
                LINE_INFO());

            const std::string SENTENCE("The cat sat on the mat.");

            tokens = StringUtils::tokens(SENTENCE, '.');
            Assert::AreEqual(std::size_t(2),
                tokens.size(),
                L"Sentence length test1 failed",
                LINE_INFO());
            Assert::AreEqual(SENTENCE.substr(0, SENTENCE.length() - 1),
                tokens[0],
                L"Sentence test1 failed (1st token)",
                LINE_INFO());
            Assert::AreEqual(std::string(""),
                tokens[1],
                L"Sentence test1 failed (2nd token)",
                LINE_INFO());

            tokens = StringUtils::tokens(SENTENCE, ' ');
            Assert::AreEqual(std::size_t(6),
                tokens.size(),
                L"Sentence length test2 failed",
                LINE_INFO());
            Assert::AreEqual(std::string("The"),
                tokens[0],
                L"Sentence test3 failed (1st token)",
                LINE_INFO());
            Assert::AreEqual(std::string("cat"),
                tokens[1],
                L"Sentence test3 failed (2nd token)",
                LINE_INFO());
            Assert::AreEqual(std::string("sat"),
                tokens[2],
                L"Sentence test3 failed (3rd token)",
                LINE_INFO());
            Assert::AreEqual(std::string("on"),
                tokens[3],
                L"Sentence test3 failed (4th token)",
                LINE_INFO());
            Assert::AreEqual(std::string("the"),
                tokens[4],
                L"Sentence test3 failed (5th token)",
                LINE_INFO());
            Assert::AreEqual(std::string("mat."),
                tokens[5],
                L"Sentence test3 failed (6th token)",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_trimmed)
        {
            Assert::AreEqual(std::string("aB cD"),
                StringUtils::trimmed("aB cD"),
                L"No trimming necessary failed",
                LINE_INFO());

            Assert::AreEqual(std::string("aBcD"),
                StringUtils::trimmed("   aBcD"),
                L"Leading spaces trim failed",
                LINE_INFO());

            Assert::AreEqual(std::string("aBc D"),
                StringUtils::trimmed("\t\t\taBc D"),
                L"Leading tab trim failed",
                LINE_INFO());

            Assert::AreEqual(std::string("a Bc  D"),
                StringUtils::trimmed("a Bc  D    "),
                L"Trailing spaces trim failed",
                LINE_INFO());

            Assert::AreEqual(std::string("aB\tcD"),
                StringUtils::trimmed("aB\tcD\t\t\t"),
                L"Trailing tab trim failed",
                LINE_INFO());

            Assert::AreEqual(std::string("a Bc\t\tD"),
                StringUtils::trimmed(" \ta Bc\t\tD\t \t"),
                L"Leading and trailing tab/space trim failed",
                LINE_INFO());
        }
        
    };  // TEST_CLASS(StringUtilsNamespace)

    //=========================================================================

    TEST_CLASS(CResultClass)
    {
    public:

        TEST_METHOD(Test_CResult)
        {
            // Constructor test:
            CResult result("Joe", "Average", 50);
            Assert::AreEqual(std::string("Joe"),
                result.firstName(),
                L"First name test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("Average"),
                result.surname(),
                L"Surname test failed",
                LINE_INFO());
            Assert::AreEqual((unsigned int)50,
                result.score(),
                L"Score test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("(firstName=Joe, surname=Average, score=50)"),
                result.str(),
                L"Surname test failed",
                LINE_INFO());

            // Copy constructor test:
            CResult copyOfResult(result);
            Assert::AreEqual(std::string("Joe"),
                copyOfResult.firstName(),
                L"First name test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("Average"),
                copyOfResult.surname(),
                L"Surname test failed",
                LINE_INFO());
            Assert::AreEqual((unsigned int)50,
                copyOfResult.score(),
                L"Score test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("(firstName=Joe, surname=Average, score=50)"),
                copyOfResult.str(),
                L"Surname test failed",
                LINE_INFO());

            // Assignment operator test:
            CResult assignmentResult = result;
            Assert::AreEqual(std::string("Joe"),
                assignmentResult.firstName(),
                L"First name test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("Average"),
                assignmentResult.surname(),
                L"Surname test failed",
                LINE_INFO());
            Assert::AreEqual((unsigned int)50,
                assignmentResult.score(),
                L"Score test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("(firstName=Joe, surname=Average, score=50)"),
                assignmentResult.str(),
                L"Surname test failed",
                LINE_INFO());

            // Move constructor test:
            CResult moveConstructorResult(CResult("Salma", "Hayek", 100));
            Assert::AreEqual(std::string("Salma"),
                moveConstructorResult.firstName(),
                L"First name test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("Hayek"),
                moveConstructorResult.surname(),
                L"Surname test failed",
                LINE_INFO());
            Assert::AreEqual((unsigned int)100,
                moveConstructorResult.score(),
                L"Score test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("(firstName=Salma, surname=Hayek, score=100)"),
                moveConstructorResult.str(),
                L"Surname test failed",
                LINE_INFO());

            // Move assignment test:
            CResult moveAssignmentResult = CResult("John", "Monash", 99);
            Assert::AreEqual(std::string("John"),
                moveAssignmentResult.firstName(),
                L"First name test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("Monash"),
                moveAssignmentResult.surname(),
                L"Surname test failed",
                LINE_INFO());
            Assert::AreEqual((unsigned int)99,
                moveAssignmentResult.score(),
                L"Score test failed",
                LINE_INFO());
            Assert::AreEqual(std::string("(firstName=John, surname=Monash, score=99)"),
                moveAssignmentResult.str(),
                L"Surname test failed",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_CResultSortOperator)
        {
            std::set<CResult> results{ CResult("Joe", "Zenner", 50),
                CResult("Nozer", "Brown", 100),
                CResult("John", "Brown", 50),
                CResult("Joe", "Average", 50),
                CResult("Joe", "Adams", 70) };
            // Note: The retrieved order will be alphabetical order of surname
            //       and alphabetical order of first name within that surname.

            std::set<CResult>::iterator result(results.begin());

            Assert::AreEqual(std::string("Adams,Joe"),
                std::string(result->surname() + ',' + result->firstName()),
                L"1st student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Average,Joe"),
                std::string(result->surname() + ',' + result->firstName()),
                L"2nd student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Brown,John"),
                std::string(result->surname() + ',' + result->firstName()),
                L"3rd student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Brown,Nozer"),
                std::string(result->surname() + ',' + result->firstName()),
                L"4th student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Zenner,Joe"),
                std::string(result->surname() + ',' + result->firstName()),
                L"5th student test failed",
                LINE_INFO());
        }
        //---------------------------------------------------------------------
        TEST_METHOD(Test_CResultHighestScoreAndNameComparator)
        {
            std::set<CResult, CResultHighestScoreAndNameComparator> results{ 
                CResult("Joe", "Zenner", 50),
                CResult("Nozer", "Brown", 100),
                CResult("John", "Brown", 50),
                CResult("Joe", "Average", 50),
                CResult("Joe", "Adams", 70) };
            // Note: These are the same student results as in the previous
            //       test. The retrieved order will be be highest to lowest
            //       score, then surname within that score, then first name
            //       within that surname.

            std::set<CResult>::iterator result(results.begin());

            Assert::AreEqual(std::string("Brown,Nozer"),
                std::string(result->surname() + ',' + result->firstName()),
                L"1st student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Adams,Joe"),
                std::string(result->surname() + ',' + result->firstName()),
                L"2nd student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Average,Joe"),
                std::string(result->surname() + ',' + result->firstName()),
                L"3rd student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Brown,John"),
                std::string(result->surname() + ',' + result->firstName()),
                L"4th student test failed",
                LINE_INFO());

            ++result;
            Assert::AreEqual(std::string("Zenner,Joe"),
                std::string(result->surname() + ',' + result->firstName()),
                L"5th student test failed",
                LINE_INFO());
        }

    };  // TEST_CLASS(CResultClass)
}