#include <stdio.h>
#include <iostream>
#include <sqlite3.h>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		cout<<azColName[i]<<" = " << (argv[i] ? argv[i] : "NULL")<<"\n";
	}
	cout<<"\n";
	return 0;
}
int main()
{
    const int STATEMENTS = 8;
    sqlite3* tom;
    char *zErrMsg = 0;
    const char *pSQL[STATEMENTS];



    int open = 0;
    open = sqlite3_open("riddle.db", &tom);


    if (open) {

        std::cout << "DB Open Error: " << sqlite3_errmsg(tom) << std::endl;

    } else {

        std::cout << "Opened Database Successfully!" << std::endl;
    }


//here is where all the values that will be placed in the database are being initialized, and the user is asked for input. Eventually this will all be a function inside of an object... a method I believe it is called. For now, all the program will be proceedural.

    //intitializing the holder variable for the data that follows. This will be in a format that SQlite will understand.
    string stringSQL;

    string char_name;
    string char_level = "3";
    string char_age = "33";
    string char_realm = "third";
    string char_class = "triologist";
    cout << "Let's Make a Character! \n Enter your Character's Name:" << endl;
    cin >> char_name;
    cout << "What is their level?" << endl;
    cin >> char_level;
        cout << "How old are they?" << endl;
    cin >> char_age;
    cout << "From what realm do they haileth?" << endl;
    cin >> char_realm;
    cout << "And what is their occupation?" << endl;
    cin >> char_class;

    // now filling the variable so that its format is one that will make sense to the database.

stringSQL = "insert into myTable (CharName, Level, Age, Realm, Class) values ('" + char_name+ "', " + char_level + ", " + char_age + ", '" + char_realm + "', '" + char_class + "')";

// just a print test to make sure formatting is good. Will need
    cout << stringSQL << endl;


    //the table is created here, but I am still learning how to transfer the C variables into the database.

    pSQL[0] = "CREATE TABLE IF NOT EXISTS myTable (CharName varchar(30), Level smallint, Age smallint, Realm varchar(30), Class varchar(30))";

	pSQL[1] = "insert into myTable (CharName, Level, Age, Realm, Class) values ('Tom', 1, 22, 'Morland', 'Rogue, Haha')";

	pSQL[2] = "insert into myTable (CharName, Level, Age, Realm, Class) values ('Lucky', 1, 41, 'Weird', 'Chaos Priest')";


// here is the user entered information.
    pSQL[3] = stringSQL.c_str();

	pSQL[4] = "select * from myTable";

	//pSQL[5] = "delete from myTable";

	//pSQL[6] = "drop table myTable";

	for(int i = 0; i < STATEMENTS; i++)
	{
		open = sqlite3_exec(tom, pSQL[i], callback, 0, &zErrMsg);
		if( open!=SQLITE_OK )
		{
			cout<<"SQL error: "<<sqlite3_errmsg(tom)<<"\n";
			sqlite3_free(zErrMsg);
			break;
		}
	}



    // Close the connection
    sqlite3_close(tom);

    return (0);
}
