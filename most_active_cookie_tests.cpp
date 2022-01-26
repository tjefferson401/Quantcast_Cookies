#include <stdio.h>  
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

// Test function definitions
void error_testing();
void corrupted_file_testing();
void random_testing();
vector<string> gen_ten_rand_cookie();
vector<string> list_most_frequent_cookies(map<string, int> cookie_map);

int main(int argc, char** argv) {
    // call testing functions
    error_testing();
    corrupted_file_testing();
    random_testing();
    return 0;
}

// These system calls should throw
void error_testing() {
    cout << "SHOULD OUT: Invalid Argument Count: " << endl;;
    system("./most_active_cookie");
    cout << endl;

    cout  << "SHOULD OUT: Invalid Argument Count: " << endl;;
    system("./most_active_cookie file date");
    cout << endl;

    cout <<  "SHOULD OUT: unequiped_filename cannot be opened: " << endl;
    system("./most_active_cookie unequiped_filename -d 2018-12-08");
    cout << endl;
}

// These system calls should match the suggested outputs
void corrupted_file_testing() {
    cout <<  "SHOULD OUT: 4sMM2LxV07bPJzwf, SAZuXPGUrfbcn5UA,fbcn5UAVanZf6UtG: " << endl;
    system("./most_active_cookie test_cookie_logs/cookie_log_broken_date.csv -d 2018-12-08");
    cout << endl;

    cout <<  "SHOULD OUT: AtY0laUfhglK3lC7, : " << endl;
    system("./most_active_cookie test_cookie_logs/cookie_log_broken_date.csv -d 2018-12-09");
    cout << endl;

    cout <<  "SHOULD OUT: 4sMM2LxV07bPJzwf, SAZuXPGUrfbcn5UA,fbcn5UAVanZf6UtG: " << endl;
    system("./most_active_cookie test_cookie_logs/cookie_log_broken_code.csv -d 2018-12-08");
    cout << endl;

    cout <<  "SHOULD OUT: AtY0laUfhglK3lC7, : " << endl;
    system("./most_active_cookie test_cookie_logs/cookie_log_broken_code.csv -d 2018-12-09");
    cout << endl;
}

// This function generates a random cookie log, prints the required output then prints the actual output. They should match
void random_testing() {
    // Creates ofstream and opens file
    ofstream cookie_log_rand;
    cookie_log_rand.open("cookie_log_rand.csv");
    // Gets list of ten random cookies to choose from
    vector<string> codes = gen_ten_rand_cookie();
    // init map, date array and filter date
    map<string,int> code_frequency_known;
    string dates[] = {"2018-12-09", "2018-12-08", "2018-12-09"};
    string date_filter = "2018-12-09";

    // write 100 logs to csv while also counting their frequency 
    cookie_log_rand << "cookie" << "," << "timestamp" << endl;
    for(int i = 0; i < 100; i ++) {
        // Pick a random date and code for the line
        string code = codes.at(rand() % (9));
        string date = dates[rand() % (3)];
        cookie_log_rand << code << "," << date << endl;
        if(date_filter == date) {
            if(code_frequency_known.find(code)->second < 1) {
                code_frequency_known[code] = 0;
            } else {
                code_frequency_known[code] ++;
            }
        }
    }
    // close the csv
    cookie_log_rand.close();
    // Get most frequently used cookies of filter date
    vector<string> most_frequent = list_most_frequent_cookies(code_frequency_known);

    // Output test and actual cookie code (they should be the same)  
    cout << "SHOULD OUT: " << endl;
    for(string i : most_frequent) {
        cout << i << endl;
    }
    cout << "ACTUAL OUTPUT: " << endl;
    system("./most_active_cookie cookie_log_rand.csv -d 2018-12-09");
}


// This function generates a list of ten cookie codes
vector<string> gen_ten_rand_cookie() {
    string alphanum = "0123ABCDabcd";
    string temp = "";
    vector<string> code_list;
    for(int j = 0; j < 10; j++) {
        for (int i = 0; i < 16; ++i) {
            temp += alphanum[rand() % (alphanum.length() - 1)];
        }
        code_list.push_back(temp);
        temp = "";
    }
    
    return code_list;
}

// This function gets the most frequently used cookie codes from the map of cookie frequencies
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
