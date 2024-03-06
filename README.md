# Practical implementation of algorithms
This repository contains the implementation of various algorithms.

## 1 - Sheduling with deadlines 
Job Sequencing with Deadlines is a problem to find the most optimal 
sequence of Jobs when executed in a single processor operating system,
to obtain the maximum profit.

### Problem:
Determine the schedule with maximum total profit given that each job
has a profit that will be obtained only if the job is scheduled by its deadline.

### Inputs:

_n_, the number of jobs, and array of integers _deadline_, indexed
from 1 to _n_, where _deadline[i]_ is the deadline of the _i-th_ job.
The array has been sorted in nonincreasing order according to the profits
associated with the jobs.

### Outputs:

an optimal sequnce J for the jobs.

### Solution:
1. Sort vector by decreasing order of profit
2. Find the value of the max deadline
3. Create vector to store results
4. Fill the vector with jobs, iterating through schedule vector, and trying to put the value to the
   maximum available slot in the result vector.
5. Print results

## 2 - Sheduling with deadlines using Disjoint Sets
The provided code implements a scheduling algorithm with deadlines, focusing on maximizing profit. It
employs a disjoint-set data structure to efficiently keep track of available slots for scheduling jobs,
considering their deadlines. The algorithm sorts the jobs in descending order of profit, initializes disjoint
sets for each deadline, and iterates through the jobs to allocate them to available slots while maximizing
profit.

### Steps in my algorithm:
1. Sort vector by decreasing order of profit
2. Find the value of the max deadline
3. Create disjoint sets from 0.. to max deadline + 1
4. Create vector to store results
5. Create a loop to traverse through vector
6. Find deadline in disjoint sets
7. If slot is avaible, union this set and previous
8. Add value to result vector
9. Print results

## 3 - Job Assignment Problem using Greedy Algorithm

The assignment problem is used to allocation a number of persons to a
number of jobs so that the total price of completion is minimized.
Although greedy algorithm has time complexity O(n^2) it may not find
the best solution, but only optimal.

## 4 - Job Assignment Problem using Hungarian Algorithm

Hungarian algorithm has worse time complexity,
but it always finds the best solution.

### How Hungarian algorithm is working:

At first for each row and then for each column its minimum element is subtracted from every element in
that row or column.
Then we’ll find the minimum number of lines that we need to cover all zeros.
Minimum number of lines to cover all zeros is equal to size of the
table, that means that the table is solved.
Minimum of the lines was searcher by algorithm, presented in
[https://en.wikipedia.org/wiki/Hungarian_algorithm](https://en.wikipedia.org/wiki/Hungarian_algorithm)

All zeros in the matrix must be covered by marking as few rows and/or columns as possible. Steps 1 and 2
form one way to accomplish this.
#### Step 1:
For each row, try to assign an arbitrary zero. Assigned tasks are represented by starring a zero. Note that
assignments can't be in the same row or column.
* We assign the first zero of Row 1. The second zero of Row 1 can't be assigned.
* We assign the first zero of Row 2. The second zero of Row 2 can't be assigned.
* Zeros on Row 3 and Row 4 can't be assigned, because they are on the same column as the zero
assigned on Row 1.
We could end with another assignment if we choose another ordering of the rows and columns.

#### Step 2:
Cover all columns containing a (starred) zero.

Find a non-covered zero and prime it. (If all zeroes are covered, skip to step 5.)
* If the zero is on the same row as a starred zero, cover the corresponding row, and uncover the
column of the starred zero.
* Then, GOTO "Find a non-covered zero and prime it."
  * Here, the second zero of Row 1 is uncovered. Because there is another zero starred on Row
1, we cover Row 1 and uncover Column 1.
  * Then, the second zero of Row 2 is uncovered. We cover Row 2 and uncover Column 2.
* Else the non-covered zero has no assigned zero on its row. We make a path starting from the zero
by performing the following steps:

  1. Find a starred zero on the corresponding column. If there is one, go to Substep 2,
   else, stop.
  2. Find a primed zero on the corresponding row (there should always be one). Go to
   Substep 1.
  
The zero on Row 3 is uncovered. We add to the path the first zero of Row 1, then the second zero of Row 1,
then we are done.
* (Else branch continued) For all zeros encountered during the path, star primed zeros and unstar
starred zeros. As the path begins and ends by a primed zero when swapping starred zeros, we have
assigned one more zero.
* (Else branch continued) Unprime all primed zeroes and uncover all lines.
* Repeat the previous steps (continue looping until the above "skip to step 5" is reached).
  * We cover columns 1, 2 and 3. The second zero on Row 2 is uncovered, so we cover Row 2
and uncover Column 2:
 
All zeros are now covered with a minimal number of rows and columns.

The aforementioned detailed description is just one way to draw the minimum number of lines to cover all
the 0s.

If number of lines less than size of the table, delete min value from every unmarked element and add it to
every element covered by two lines and repeat step 2-3.

#### Now we need to find the solution.
Solution will be searched that way:

At the start it will count zeros in each column and each row, and start to choose lines with minimum
number of zeros, and that block these zeros, and column with row in which this zero is. Then we continue
to do it, until all zeros is covered.

Summing up If you need only optimal solution but not the best, you’d better use Greedy approach as it’s
more effective and working faster.

But if you need to always to have the best solution you’d use Hungarian algorithm as it’ll guarantee that
you always find the best solution