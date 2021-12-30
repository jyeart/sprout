#include <stdio.h>
#include <iostream>
#include <sqlite3.h>


//using this for now to make it quicker, will take out in final version
using namespace std;

//
//class MyClass {        // The class
//  public:              // Access specifier
//    void myMethod() {  // Method/function defined inside the class
//      cout << "Hello World!";
//    }
//};
//
//int main() {
//  MyClass myObj;     // Create an object of MyClass
//  myObj.myMethod();  // Call the method
//  return 0;
//}


//SQlite callback function



//creation of the input class

//class MyClass {        // The class
//  public:              // Access specifier
//    void myMethod() {  // Method/function defined inside the class
//      cout << "Hello World!";
//    }
//};

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



//lets give this class a method by which it will ask for the data from the user, collect that data, create a database if none exists, and add the information collected to said database.
class player {

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




    public:

    void start(){
//code was moved into object.

    //creating an instance and calling the method
    //player tomRiddle;
    //tomRiddle.start();

      // for holding the SQlite formatted string.
    string stringSQL;
 //variables, eventually will need to specify different data types, for now, the strings are functional, but I want to be able to put in different data types. Not sure if that is possible - if sqlite requires char formats...
    string char_name;
    string char_level;
    string char_age;
    string char_realm;
    string char_class;



    //methods

    //changing the method to incorporate the database creation etc.


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

    //here is the additional code to enter the stuff into database.
    const int STATEMENTS = 3;
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

    pSQL[0] = "CREATE TABLE IF NOT EXISTS myTable (CharName varchar(30), Level smallint, Age smallint, Realm varchar(30), Class varchar(30))";
pSQL[1] = stringSQL.c_str();
    pSQL[2] = "select * from myTable";


    	for(int i = 0; i < STATEMENTS; i++)
	{
	//the exec statement takes the pSQL char const and inputs it into the database.
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

    //return stringSQL;


}

};

int main()
{


player tom;
tom.start();





    return (0);
}

