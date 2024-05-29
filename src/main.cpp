#include <iostream>
#include <iomanip>
#include <curl/curl.h> 
#include "json.hpp"
/*  
    Notes:
        1. libcurl: This library handles netowrk operations specifically for 
            1a. Downloading files
            1b. Making HTTP requests
            1c. Interacting with web services.

        2. json.hpp: After receiving the data from the network operation 
        (which is often in JSON format), you use the json.hpp library 
        (nlohmann/json) to parse this JSON data. This allows you to easily
         access and manipulate the data within your C++ application.

        3. C-Make: whne we have alot of stuff that need to consitnelty write to the command line
        we have cmake so that we cna run it and automatily runs build files 

        To Build Project to Run: enure termins is in SRC folder 
            2. cmake ..  (we are in src folder )
            4. make
            5. ./MyProject

        To re-run build again 
            1. rm -r build 
            2. do steps again 
*/

using namespace std;

void printMenu();
void testingFunction();

int main()
{
    printMenu();
    cout << "Type your question and once done press enter to search. " << endl;
    cout << "Question: ";
    string userQuestion;
    getline(cin, userQuestion);
    testingFunction();

    return 0;
}

void printMenu()
{
    int titleWidth = 40;
    int titleLength = 12; // Length of "STACK SURFER"
    int leftPadding = (titleWidth - titleLength) / 2; // Calculate left padding

    cout << setw(titleWidth) << setfill('=') << "" << endl;
    cout << setw(leftPadding) << setfill(' ') << "" << "STACK SURFER" << setw(titleLength) << setfill(' ') << "" << endl;
    cout << setw(titleWidth) << setfill('=') << "" << endl;
}
void testingFunction()
{
    cout << "Entered Tester " << endl << endl;
    CURL* curl;
    // curl https://www.example.com/;
}