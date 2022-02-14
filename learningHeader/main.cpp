#include <stdio.h>
#include <iostream>
#include "sqlite3.h"
#include "sqlite_orm.h"


//using this for now to make it quicker, will take out in final version
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


//begin ORM
struct Employee {
    int id;
    std::string name;
    int age;
    std::string address;
    double salary;
};

struct DetailedEmployee : public Employee {
    std::string birthDate;
};


//end ORM

//lets give this class a method by which it will ask for the data from the user, collect that data, create a database if none exists, and add the information collected to said database.
class Player {


    public:
     // for holding the SQlite formatted string.
    string stringSQL;
 //variables, eventually will need to specify different data types, for now, the strings are functional, but I want to be able to put in different data types. Not sure if that is possible - if sqlite requires char formats...
    string char_name;
    string char_level;
    string char_age;
    string char_realm;
    string char_class;

        //constructors

    Player (){
    std::cout << "Instance of class created!"<< std::endl;}

    Player(string name, string level, string age, string realm, string c_class)
    {
    char_name = name;
    char_level = level;
    char_age = age;
    char_realm = realm;
    char_class = c_class;
   std::cout << "Instance of constructed class created!"<< std::endl;

    stringSQL = "insert into myTable (CharName, Level, Age, Realm, Class) values ('" + char_name+ "', " + char_level + ", " + char_age + ", '" + char_realm + "', '" + char_class + "')";

// just a print test to make sure formatting is good.
    //cout << stringSQL << endl;

    //here is the additional code to enter the stuff into database.
    const int STATEMENTS = 2;
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
    //pSQL[2] = "select * from myTable";


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


    //this method is used to put in custom input
    void start(){


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
    //cout << stringSQL << endl;

    //here is the additional code to enter the stuff into database.
    const int STATEMENTS = 2;
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
    //pSQL[2] = "select * from myTable";


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

void getData(){
    const int STATEMENTS = 1;
    sqlite3* tom;
    char *zErrMsg = 0;
    const char *pSQL[STATEMENTS];
    int open = 0;
    open = sqlite3_open("riddle.db", &tom);

//test if the database is opened
    if (open) {

        std::cout << "DB Open Error: " << sqlite3_errmsg(tom) << std::endl;

    } else {

        std::cout << "Opened Database Successfully!" << std::endl;
    }

//selects the data so it can be gotten, and prints it to the screen.
    pSQL[0] = "select * from myTable";


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




//Do you want to make a character query
char createQuery;


std::cout << "Would you like to create a character? (y/n)"<< std::endl;
std::cin >> createQuery;




//ORM

using namespace sqlite_orm;
std::cout << "Would you like to get started? (y/n)"<< std::endl;
std::cin >> createQuery;

//testing to see if we can get the sqlite ORM working



    auto storage = make_storage("insert.sqlite",
                                make_table("COMPANY",
                                           make_column("ID",
                                                       &Employee::id,
                                                       primary_key()),
                                           make_column("NAME",
                                                       &Employee::name),
                                           make_column("AGE",
                                                       &Employee::age),
                                           make_column("ADDRESS",
                                                       &Employee::address),
                                           make_column("SALARY",
                                                       &Employee::salary)));
    storage.sync_schema();
    storage.remove_all<Employee>();

    Employee paul {
        -1,
        "Paul",
        32,
        "California",
        20000.00,
    };

    //  insert returns inserted id
    paul.id = storage.insert(paul);

    storage.insert(Employee{
        -1,
        "Allen",
        28,
        "Texas",
        15000.00,
    });

    storage.insert(Employee{
        -1,
        "APllen",
        28,
        "Texas",
        15000.00,
    });


    DetailedEmployee teddy;
    teddy.name = "Teddy";
    teddy.age = 23;
    teddy.address = "Norway";
    teddy.salary = 20000.00;

    //  to insert subclass object as a superclass you have to specify type explicitly
    teddy.id = storage.insert<Employee>(teddy);

    std::vector<Employee> otherEmployees;
    otherEmployees.push_back(Employee{
        -1,
        "Mark",
        25,
        "Rich-Mond",
        65000.00,
    });
    otherEmployees.push_back(Employee{
        -1,
        "David",
        27,
        "Texas",
        85000.00,
    });
    otherEmployees.push_back(Employee{
        -1,
        "Kim",
        22,
        "South-Hall",
        45000.00,
    });
    //  transaction is optional. It is used here to optimize sqlite usage - every insert opens
    //  and closes database. So triple insert will open and close the db three times.
    //  Transaction openes and closes the db only once.
    storage.transaction([&]{
        for(auto &employee : otherEmployees) {
            storage.insert(employee);
        }
        return true;
    });

    Employee james{
        -1,
        "James",
        24,
        "Houston",
        10000.00,
    };
    james.id = storage.insert(james);

    cout << "---------------------" << endl;

        cout << storage.dump(james) << endl;



//endORM



//switch (createQuery){
//case 'y':{
////delcaration of pointer variables
//Player *playerCharacter;
//playerCharacter = new Player;
//playerCharacter->start();
//delete playerCharacter;
//}
//break;
//case 'n':
//{
//Player *playerCharacter;
//playerCharacter = new Player("mr.Default3", "99", "103", "defaultia", "defaulter");
//delete playerCharacter;
//}
//break;
//default:
//std::cout << "if you don't enter the right character or response, then we are all just SOL you know. This program has no safety bumpers damn it." << std::endl;
//}
//
//
//
//// now for the get data prompt
//
//char getQuery;
//
//
//std::cout << "Would you like to see the database so far? (y/n)"<< std::endl;
//std::cin >> getQuery;
//
//switch (getQuery){
//case 'y':{
//Player dummy;
//dummy.getData();
//}
//break;
//case 'n':{
//std::cout << "Fine, be that way." << std::endl;
//}
//break;
//default:
//std::cout << "if you don't enter the right character or response, then we are all just SOL you know. This program has no safety bumpers damn it." << std::endl;
//}



    return (0);
}

