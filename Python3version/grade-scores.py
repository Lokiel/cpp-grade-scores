#!/usr/bin/python3

# TransMax Software Developer Exercise.
#
# Refer to the printUsage(...) function for details.

import os
import sys

def printUsage():
    print('''Usage: %s <INPUT_FILE>
where
  <INPUT_FILE> is a .csv file with the format:
  
      <FIRST_NAME>,[SURNAME],<SCORE>

    The <FIRSTNAME> field is mandatory.
    The [SURNAME] field may be empty (eg. "Madonna" goes by one name).
    The <SCORE> field is mandatory and must be numeric.
    Duplicate <FIRSTNAME>+[SURNAME] combinations are reported and only the
    first occurrence is accepted.
    
Output is written to file <INPUT_FILE>-graded.txt with format:

    [SURNAME],<FIRSTNAME>,<SCORE>
  
The output is sorted by highest <SCORE> and alphabetically on
[SURNAME]+<FIRSTNAME> of students achieving that score.''' % sys.argv[0])
 
def printError(errorMsg):
    print('ERROR: %s\n' % errorMsg)
    printUsage()

if (len(sys.argv) == 1) or (sys.argv[1].lower() in ['-h','/h','--help','?','-?','/?']):
    printUsage()
    
elif len(sys.argv) != 2:
    printError('Only one input file expected!')
    sys.exit(1)

elif not os.path.exists(sys.argv[1]):
    printError('Specified file, "%s", does not exist!' % sys.argv[1])
    sys.exit(2)
    
else:
    # Token indexes of input file fields when each line is tokenised:
    FIRSTNAME = 0
    SURNAME   = 1
    SCORE     = 2
   
    results = {}  # Key=score, Contents=list of student names achieving score
    
    # Populate the results dictionary with the student results, formatting the
    # student names into the required "[SURNAME],<FIRSTNAME>" .csv format
    # to make subsequent sorting easier when outputting the results.
    #
    # Note: For ultimate speed, I could use pure-Python's 
    #       sortedcontainers.SortedDict and sortedcontainers.SortedList but
    #       that's overkill for this exercise.
    #--------------------------------------------------------------------------
    
    try:
        inputFile = open(sys.argv[1])
        lineNo = 1
        studentsAlreadyProcessed = []
        
        for line in inputFile:  # Append all student data to the results dictionary
            
            tokens = line[:-1].replace(' ', '').split(',')  
            # excludes newline character and trims whitespace
            
            if (   (len(tokens) != 3)  # Expected format is <FIRSTNAME>,[SURNAME],<SCORE>
                or (len(tokens[FIRSTNAME]) == 0)  # <FIRSTNAME> is mandatory
                or (len(tokens[SCORE]) == 0)      # <SCORE> is mandatory
                or not tokens[SCORE].isdigit()):  # <SCORE> must be numeric
                print('Ignoring invalid line %i: "%s"' % (lineNo, line[:-1]))
            
            else:
               
                score = int(tokens[SCORE])
                
                # Define thisStudent based on [SURNAME] and <FIRSTNAME>.
                # If the [SURNAME] token is null/empty, use a space character to
                # ensure that it will be the first sorted [SURNAME].
                if len(tokens[SURNAME]) == 0:
                    thisStudent = ' ,%s' % tokens[FIRSTNAME] # " ,<FIRSTNAME>"
                else:
                    thisStudent = '%s,%s' % (tokens[SURNAME], 
                                             tokens[FIRSTNAME]) # "[SURNAME],<FIRSTNAME>"
                
                lowercaseStudentName = thisStudent.lower()
                        
                if lowercaseStudentName in studentsAlreadyProcessed:
                    print('Ignoring duplicate student result at line %i: "%s"' % (lineNo, line[:-1]))
                
                else:  # update results with this student's result

                    if score in results:
                        results[score].append(thisStudent)
                    else:
                        results[score] = [thisStudent]
                        
                    studentsAlreadyProcessed.append(lowercaseStudentName)
                    
            lineNo += 1
        
        inputFile.close()
            
    except IOError:
        printError('Failed to read Results file "%s"!', sys.argv[1])
        sys.exit(3)
        
    # Write the results in .csv format, sorted on score, highest first, then
    # student name, in alphabetical order based on surname, with the score
    # appearing last.
    #-------------------------------------------------------------------------
        
    outputFileName = '%s-graded.txt' % os.path.splitext(sys.argv[1])[0]  
    # Note: "os.path.splitext(sys.argv[1])[0]" excludes the input file's suffix 
    # ie. If the command line's file name is "result.txt", the generated name is
    #     "results-graded.txt" rather than "results.txt-graded.txt"
    
    try:
        outputFile = open(outputFileName, 'w')

        for score in sorted(results.keys(), reverse=True): # process scores, highest first
            for student in sorted(results[score], key=str.lower):  # process sorted student names within this score
                #print('%s,%i' % (student.lstrip(' '), score))
                outputFile.write('%s,%i\n' % (student.lstrip(' '), score))
                # Note: ".lstrip(' ')" is used to eliminate a potential
                #       leading space that was added above to ensure
                #       correct sorting when [SURNAME] is null/empty
        
        outputFile.close()
        
        print('\n+++ Output written to "%s"' % outputFileName)
                    
    except IOError:
        printError('Failed to write file "%s"!', outputFileName)
        sys.exit(4)
