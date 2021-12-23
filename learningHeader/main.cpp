#include <iostream>
#include <sqlite3.h>



int main()
{

    sqlite3* tom;


    int open = 0;
    open = sqlite3_open("riddle.db", &tom);


    if (open) {

        std::cout << "DB Open Error: " << sqlite3_errmsg(tom) << std::endl;

    } else {

        std::cout << "Opened Database Successfully!" << std::endl;
    }

    // Close the connection
    sqlite3_close(tom);

    return (0);
}
