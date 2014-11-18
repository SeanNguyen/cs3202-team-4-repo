Update changes (18/11/2014)

Problems working on:
- Some queries containing Modifies and Uses does not return correctly (missing values for most cases)
- Some queries containing Affects, Affects* does not return 
correctly (missing value)
- TIMEOUT problem (queries containing Next*, Affect, Affect* and some others containing both Modifies and Uses)

Explainations/ Solutions:
- Problems related to Modifies an Uses might relate to QueryProcessor or Parser. We has fix some errors found but it is uncertain whether we fix all, since our test cases are too short to test all possible cases.
- Problem related to Affects might relate to Modifies and Uses relation, since the Next* relation works correctly. 
- TIMEOUT problem is mainly because of evaluation process. During evaluation, ResultTables are merged and extracted on the way. Our guess is that the cost for merging is so large that in query containing hard relation (i.e. 2 unknown arguments) the table's size can be up to 300-500 rows, thus it results in TIMEOUT.
Since this is related to the design/ algorithm we used for module QueryProcessor, it is unable to fix in a short amount of time.

Changes:
- Fix Uses error in handling procedure

To-do:
- Fix Modifies and Uses
- Work on TIMEOUT error. 
  