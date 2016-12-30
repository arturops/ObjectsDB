
===== How to compile this program? ======================================================================

The Makefile allows an easy compilation. However, one needs to have installed 'SQlite3' database package.
Then, verify the Makefile is in the same folder where all source and header files are.

To start building/compiling the program type in terminal ~$make all

Once it is finished there will be an executable named 'ObjectDB'


===== How to run the executable? ========================================================================

To run the executable, ensure the terminal is in the folder where the executable is. 

Then, type in terminal ~$./ObjectDB [ProjectNumberID]


===== How to erase the database? ========================================================================

To delete the database the Makefile also provides a command ~$make cleanDB 
This command will delete all 'ObjectsDB.db' file


===== How to use SQLite from terminal to query database? =================================================
If the user wants to use the terminal sqlite database interface it is very easy to use:
1. In the terminal type ~$sqlite3

2. User will see something like ~$ sqlite> 

3. Attach the 'ObjectsDB.db' database to the sqlite3: ~$ sqlite> ATTACH 'ObjectsDB.db' as 'DB'

4. Configure the sqlite3 to show data in columns: ~$ sqlite> .mode columns

5. Configure the sqlite3 to show columns' headers: ~$ sqlite> .headers on

6. Query data, examples to see 
		+ All data: 
			~$ sqlite> SELECT * FROM STORED_OBJECTS;
		+ All data of a specific project(this case project 1) ordered by ID: 
			~$ sqlite> SELECT * FROM STORED_OBJECTS WHERE PROJECT_ID =1 ORDER BY ID;

7. After looking at the data simply exit: ~$ sqlite> .exit


===== IMPORTANT-Program brief description of Test ==========================================================

The [ProjectNumberID] is the number of the project in which two test will run. 

TESTS:
1.The first Test creates a number of objects and stores them into a database named 'ObjectsDB.db'*.
	*If the program has never been run before it will create the database and Table to store data. Otherwise, it will show messages from SQL saying that the Table has already been created.
	*The program will also show INSERT fails if a projectID is used to run the same program. Thus, because the primary Key of the DB is made of a PROJECT_ID and an OBJECT_NAME_ID. However, the second test will add a new record succesfully.

2.The second Test uses the same database 'ObjectsDB.db' to query the projectID given and load all data into a
project. Then use previous data to build a new object and store it. This is helpeful to keep developing after closing a project. However, there hasn't been implemented an UPDATE query to save changes of objects that are modified after loading a project.


BOTH Tests compare 2 objects to check if they are overlapping. 
An implementation using an interval tree/sweeping interval algorithm is proposed for a complex case of N rectangles intersection search.
However, here has only been implemented a simple comparison using 2 points of each rectangle.

