# cpp-grade-scores
This is my solution to the following problem:

## .csv Test Result Exercise

Write a console app that:
* Takes as a parameter a string that represents a text file containing a list of student names, and their scores
* Orders the names by their score. If scores are the same, order by their last name followed by first name
* Creates a new text file called \<input-file-name\>-graded.txt with the list of sorted score and names.
* Takes a CSV input file with the format of First Name, Surname, Score
* Output file format is .csv format with the format of Surname, First Name, Score
* Shall be able to handle relative and full paths file inputs
* Output file shall be in the same folder as the input file
* Text ordering shall be case-insensitive
* The application name shall be grade-scores.exe
* Exceptions shall be handled appropriately
* Shall only output to the console when complied in a debug mode.
* Tests should be concise and appropriate
* Sorting score shall be descending order
* Sorting names shall be ascending order

Eg. If the input file (students.txt) contains:
```
TED, BUNDY, 88
ALLAN, SMITH , 85
MADISON , KING, 83
FRANCIS, SMITH, 85
```
Then the output file (students-graded.txt) would be:
```
BUNDY, TED, 88
SMITH, ALLAN, 85
SMITH, FRANCIS, 85
KING, MADISON, 83
```

## Notes

* I implemented the solution in C++ using Visual Studio 2017 and Python 3.
* The Visual Studio 2017 solution file is **grades-scores.sln** in the top-level directory.
* The Python 3 script can be found in **Python3version/grade-scores.py**.
* The C++ implementation was designed with testability in mind rather than brevity (eg. The **CResults** class could have been done away with and the functionality embedded in the **main** function of **grade-scores.cpp** but then that code would not have been automatically unit testable; automated regression tests should be used where possible).
* The test input file I used is **students.txt** and the generated file is **students-graded.txt**; both are in the top-level directory.
* I allowed for the case where a student has only one name, in which case it was assumed to be in the input file's "First Name" field and the "Surname" field is null/empty.
* Invalid input file lines (those not containing exactly 3 fields when delimited by a comma) were ignored.
* Duplicate student names were handled by ignoring duplicates.
* Console output, including error messages and duplicate students, is only generated for Debug builds (I found this an odd requirement given that for Release builds, the user would be unaware if the input file had any problems - possibly the requirement is not a practical one but more for the sake of the exercise).
* If the console application is successful, or the user has requested usage information, it returns with system status 0; if any errors occur, a non-zero system status is returned.

## To Do

* Write Unit tests for the CResults class. I attempted to do this but failed to determine how to import an input file into the test project (the constructor always failed because the file could not be found).
