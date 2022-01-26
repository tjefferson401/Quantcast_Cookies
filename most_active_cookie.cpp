#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

using namespace std;

// Method definitions
void parse_cookie_log(string filename, string filter_date = "");
map<string, int> populate_cookie_frequency(ifstream& fs, string filter_date);
vector<string> list_most_frequent_cookies(map<string, int> sampleMap);
vector<string> split_string(string to_split, char delimiter);
bool check_arg_count(int argc);
string get_date_from_timestamp(string utc_date_format);

/*
* main
* Parameters: int argc - amount of arguments, char** argv - array of arguments
* Purpose: Accepts arguments, checks amount of arguments is correct and delegates to the log parser. 
* Returns: Int - Exit
*/
int main(int argc, char** argv) {
    // Check if date is included in the arguments
    bool date = check_arg_count(argc);
    // if not, just pass through the filename, if yes pass through filename and date
    if(!date) {
        parse_cookie_log(argv[1]);
    } else {
        parse_cookie_log(argv[1], argv[3]);
    }
    return 0;
}


/*
* parse_cookie_log
* Parameters: string filename - name of cookielog file, string filterdate - date to retrieve, if any
* (date default to "" as per function definition)
* Purpose: Opens file, populates cookie frequency map with "populate_cookie_frequency", and outputs
* most frequent cookie
* Returns: Void
*/
void parse_cookie_log(string filename, string filter_date) {
    // init filestream and open file
    ifstream fs;
    fs.open(filename); 

    // check for file failure. If file fails to open, exit program, print error message
    if(fs.fail()) {
    cerr << filename << " cannot be opened" << endl;
    exit(EXIT_FAILURE);
    }

    // Populate cookie_frequency
    map<string, int> cookie_frequency = populate_cookie_frequency(fs, filter_date);

    // Get most frequently found cookies
    vector<string> list_of_cookies = list_most_frequent_cookies(cookie_frequency);

    // Loop through and print out most frequently used cookies
    for(string cookie : list_of_cookies) {
        cout << cookie << endl;
    }
}

/*
* populate_cookie_frequency
* Parameters: ifstream& fs - ref, string filterdate - date to retrieve, if any
* (date default to "" as per function definition)
* Purpose: This function creates a map where the key is the cookie code and the value 
* is the frequency of the cookie code in the chosen time period
* Returns: A map with a pair set <Cookie code, frequency>
*/
map<string, int> populate_cookie_frequency(ifstream& fs, string filter_date) {
    // init map and line string
    map<string, int> cookie_frequency;
    string cookie_ln = "";

    // get title line
    getline(fs, cookie_ln);

    // Loop through file
    while(not fs.eof()) {
        // get line
        getline(fs, cookie_ln);
        if(cookie_ln != "") {
            // Split line to get code and date
            vector<string> parsed_line = split_string(cookie_ln, ',');
            // Check that line is formatted correctly
            if(parsed_line.size() != 2) {
                cerr << "Cookie log contains invalid lines" << endl;
                exit(EXIT_FAILURE);
            }
            
            // Get cookie code and cookie date 
            string cookie = parsed_line.at(0);
            string curr_cookie_date = get_date_from_timestamp(parsed_line.at(1));


            // If current cookie code was from the same day as the filter date or if the filterdate is the default value,
            // add to map
            if(filter_date == curr_cookie_date || filter_date == "") {
                // If cookie code is in map, increment value, if not initiate key
                if(cookie_frequency.find(cookie)->second < 0) {
                    cookie_frequency[cookie] = 0;
                } else {
                    cookie_frequency[cookie] ++;
                }
            }
        }
    }

    // Map
    return cookie_frequency;
}


/*
* list_most_frequent_cookies
* Parameters: map<string, int> cookie_map - map containing cookies and frequency values
* Purpose: This function finds the cookie codes of highest value in the map of frequencies
* Returns: A list of cookie codes
*/
vector<string> list_most_frequent_cookies(map<string, int> cookie_map) {
    // Highest Number of codes seen
    int max_num = 0;
    // init vector of cookies
    vector<string> most_frequent_cookies;
    // create map iterator
    map<string, int>::iterator current_cookie;
    // Loop through map
    for (current_cookie = cookie_map.begin(); current_cookie != cookie_map.end(); ++current_cookie) {
        // if value of cookie is greater than previous max
        if (current_cookie->second > max_num) {
            // Update max
            max_num = current_cookie->second;
            // Clear list of less used cookies
            most_frequent_cookies.clear();
            // push current cookie code
            most_frequent_cookies.push_back(current_cookie->first);
        } else if (current_cookie->second == max_num) {
            // else if current cookie has frequency equal to max, push to list
            most_frequent_cookies.push_back(current_cookie->first);
        }
    }

    // return list
    return most_frequent_cookies;
}

/*
* check_arg_count
* Parameters: int argc - amount of args
* Purpose: Confirms that enough arguments have been given
* Returns: Boolean, true if args include date, false if not
*/
bool check_arg_count(int argc) {
    switch(argc) {
        case 2:
            // if 2 args, only filename is given
            return false;
        case 4:
            // if 4 args, date is included
            return true;
        default : 
            // if different value, call exit failure
            cerr << "Invalid Argument Count" << endl;
            exit(EXIT_FAILURE);
    }
    return false;
}


/*
* split_string
* Parameters: string to_split - string to be split, char split_by - character to split string by
* Purpose: Splits cookie log line (or any string). Similar in function to "Split()" in python
* Returns: List of strings that have been parsed
*/
vector<string> split_string(string to_split, char split_by){
    // init temporary string and vector of words
    string temp = "";
    vector<string> split_words;

    // loop through to_split
    for(int i=0; i< (int)to_split.length(); i++){
        // if current char is not split_by, add to temporary word, else push current temp to list and reset temp
        if(to_split[i] != split_by){
            temp += to_split[i];
        } else {
            split_words.push_back(temp);
            temp = "";
        }
    }
    // Push back last word
    split_words.push_back(temp);
    // Return list
    return split_words;
}


/*
* get_date_from_timestamp
* Parameters: string utc_date_format - timestamp from cookie log
* Purpose: Gets date from timestamp
* Returns: Date
*/
string get_date_from_timestamp(string utc_date_format) {
    // try to return date, if error, print that date is invalid
    try {
        return utc_date_format.substr(0, 10);
    } catch (int e) {
        cerr << "Invalid date format: " << e << endl;
    }

    return "X";
}
