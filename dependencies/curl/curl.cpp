// This files defines the methods for the Curl class
// Modified by: Dikshant Adhikari
// Modified from the Barbeque library by Grant McGovern found at https://github.com/g12mcgov/Barbeque
// New changes made by me include adding support for headers in GET requests and removing redundant get and post methods not
// used by this program

#include "curl.h"

using namespace std; 

// Constructor
Curl::Curl() = default;

// Destructor 
Curl::~Curl() = default;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/* GET method */
string Curl::get(string &url, map<string, string> &headers_map)
{
    // Clear out the HTTP status
    http_status = 0;

    // Define our "string-i-fied" response variable
    string readBuffer;
    string headers_data;

    curl = curl_easy_init();

    // This is how libcurl natively stores headers
    struct curl_slist *headers = nullptr;

    // Iterate through headers map and construct the headers string from it.
    for (auto &itr : headers_map)
        headers_data.append(itr.first + ": "+ itr.second);

    if(curl)
    {
        // Construct our headers
        headers = curl_slist_append(headers, headers_data.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        unsigned int http_code = 0;
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return nullptr;
        }
        // Get the response code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        http_status = http_code;

        // Assure it's an int by casting
        if(int(http_status) == 400)
            cout << "Response <" << http_status << "> thrown." << endl;

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

  return readBuffer;
}

/* POST method */
string Curl::post(string &url, map<string, string> &params, map<string, string> &headers_map)
{   
    curl = curl_easy_init();

    string parameters;
    string headers_data;

    // This is how libcurl natively stores headers
    struct curl_slist *headers = nullptr;

    string readBuffer;

    // Iterate through parameters map and construct a string from it.
    for (auto &param : params)
        parameters.append(param.first + "=" + param.second + "&");

    // Iterate through headers map and construct the headers string from it.
    for (auto &itr : headers_map)
        headers_data.append(itr.first + ": "+ itr.second);

    if(curl)
    {
        // Construct our headers
        headers = curl_slist_append(headers, headers_data.c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());

        // Make the call
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return nullptr;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}