#include <iostream>
#include <iomanip>
#include <curl/curl.h> 
#include "json.hpp"
#include "authentication.hpp" // Corrected include
#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

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
            1. mkdir build 
            2. cd mkdir 
            3. cmake ..  (we are now in mkdir directory)
            4. make
            5. ./MyProject

        to rerun project    
            1. rm -r build 
            2. redow steps above!

*/

using namespace std;

void printMenu();
void search(const string& url);
void printData(string readBuffer);
void viewMongoDBServer();
void searchDataInMongoDBServer();
string constructQuestion(string &userQuestion);


/*
    Write_callBack: Handles writing received data 
    ptr:Pointer to recieved data 
    size: size of each data elemetn 
    nmemb: number of elements 
    userData: Points to string object which contains our received data 
*/

size_t write_callback(char *ptr, size_t size, size_t nmemb, string *userdata) {
    userdata->append(ptr, size * nmemb);
    return size * nmemb;
}

int main()
{
    printMenu();
    //viewMongoDBServer();
    searchDataInMongoDBServer();
    // int result = authentication::menu();
    // switch(result)
    // {
    //     case 1:
    //         authentication::login();
    //         break;
        
    //     case 2:
    //         authentication::newMember();
    //         break;

    //     case 3:
    //         authentication::forgotPassword();
    //         break;
        
    //     case 4: 
    //         cout << "Good bye" << endl;
    //         exit(0);
    //         break;

    // }
    // cout << "Type your question and once done press enter to search. " << endl;
    // cout << "Question: ";
    // string userQuestion;
    // getline(cin, userQuestion);
    // string constructedString = constructQuestion(userQuestion);
    // search(constructedString);
    return 0;
}

void viewMongoDBServer()
{
    cout <<"Check Mongo Connection" << endl;
    // Establish an instance of mongocxx 
    mongocxx::instance instance{};

    // Connect to MongoDB server 
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);
    
    // Access database UserData
    mongocxx::database db = client["UserData"];

    // Access the specific collection
    mongocxx::collection collection = db["Users"];

    // Query the collection and iterate over the documents
    auto cursor = collection.find({});
    
    for (auto&& doc : cursor) {
        // Print each document
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}

void searchDataInMongoDBServer()
{
    cout << "Search MongoDB Connection" << endl;

    // establish instance of mongocxx
    mongocxx::instance instance{};

    // conect to mongo DB server as a client 
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);

    // Lets access a specific data base 
    mongocxx::database db = client["UserData"];

    // Now that we have access to the data base lets access a specific collectin 
    mongocxx::collection collection = db["Users"];

    // we now have access to the collection insdie of our database 
    findDocument(collection, "username", "dtalmood");
}

void findDocument(mongocxx::collection& collection, const string& key, const string& value) 
{
    auto filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;
    auto cursor = collection.find(filter.view());
    for (auto&& doc : cursor) {
        cout << bsoncxx::to_json(doc) << endl;
    }
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

void search(const string& url)
{
    CURL *curl;
    CURLcode res;
    string readBuffer;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Curl Option 1: 

        // CURLOPT_WRITEFUNCTION: Tells it that we are going to be writing data and we are specifying how to write it 
        // write_callback: this says this is the function that is going to be doing logic for writing 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        
        // Curl Option 2: 
        // here we are specifiying that we pass information url to a variable which in third paramater we specify variable to store
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // After we set up options for CURL we Perform the request below 
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) 
        {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } 
        else 
        {
            // Print the response data
            printData(readBuffer);
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();
}

string constructQuestion(string & userQuestion)
{
    //this base url is to need to access stack over API
    string baseURL = "https://api.stackexchange.com/2.3/search/advanced?";

    // we are encoding the user query 
    string encodedQuery = curl_easy_escape(nullptr, userQuestion.c_str(), userQuestion.length());
    
    // set Paramaters 
    baseURL += "order=desc&sort=relevance&q="+ encodedQuery;

    // Append the site parameter (e.g., Stack Overflow)
    baseURL += "&site=stackoverflow";

    // this is key generated from Stack Exchange, this key is what enable us to use the stack over flow API 
    string key = "OUgS5vV1jD7kdtN8*nYZKg((";
    baseURL += "&key=" + key;
    
    cout << "Constructed Stirng: " << baseURL << endl;
    return baseURL;
}

void printData(string readBuffer)
{
    //cout << "Response Data:" << endl;
    //cout << readBuffer << endl;
    auto json = nlohmann::json::parse(readBuffer);
    
    for(const auto& item: json["items"])
    {
        cout << "Title: " << item["title"] << endl;
        cout << "Creation Date: " << item["creation_date"] << endl;
    }

}
