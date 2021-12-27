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



    string char_name;
    string char_level = "3";
    string char_age = "33";
    string char_realm = "third";
    string char_class = "triologist";
    cout << "Let's Make a Character! \n Enter your Character's Name:" << endl;
    cin >> char_name;
    cout << "you entered " << char_name << endl;

    cout << "what follows is the table itself, which does not yet contain the values entered by the user" + char_name << endl;


    //the table is created here, but I am still learning how to transfer the C variables into the database.

    pSQL[0] = "create table myTable (CharName varchar(30), Level smallint, Age smallint, Realm varchar(30), Class varchar(30))";

	pSQL[1] = "insert into myTable (CharName, Level, Age, Realm, Class) values ('Tom', 1, 22, 'Morland', 'Rogue, Haha')";

	pSQL[2] = "insert into myTable (CharName, Level, Age, Realm, Class) values ('Lucky', 1, 41, 'Weird', 'Chaos Priest')";

//creating the user entry
    //creating a new string to hold the value.
    //string strSQL;
    //strSQL =
    //strSQL =  + char_name + "', " + char_level + ", " + char_age + ", '" + char_realm + "', '" + char_class +"')";
    string stringSQL;
    //stringSQL = "insert into myTable (CharName, Level, Age, Realm, Class) values ('" + char_name+ "', " + char_level + ", " + char_age + ", '" + char_realm + "', '" + char_class +"')";

    stringSQL = "insert into myTable (CharName, Level, Age, Realm, Class) values ('" + char_name+ "', " + char_level + ", " + char_age + ", '" + char_realm + "', '" + char_class + "')";

    cout << stringSQL << endl;
    pSQL[3] = stringSQL.c_str();

	pSQL[4] = "select * from myTable";

	pSQL[5] = "delete from myTable";

	pSQL[6] = "drop table myTable";

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
