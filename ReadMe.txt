// Quantcast initial take-home project //
Authored by Thomas Jefferson

Tutorial:
1. Clone the repository.
2. Enter into the directory (e.g. cd Quantcast_Cookies)
3. (Optional: Executables already contained) Compile "most_active_cookie.cpp" and/or "most_active_cookie_tests.cpp":
  - Program: $ g++ -std=c++11 most_active_cookie.cpp -o most_active_cookie 
  - Tests:   $ g++ -std=c++11 most_active_cookie_tests.cpp -o mac_tests
 4. Run programs:
  - Program: $ ./most_active_cookie test_cookie_logs/cookie_log_broken_date.csv -d 2018-12-08
  - Tests:   $ ./mac_tests

Testing:
There Within the repo, there is a directory called "test_cookie_logs".
This directory holds manually created files to test the program.
Two files were created to test inproper file format (cookie_log_broken_date.csv and cookie_log_broken_code.csv), and one file 
(cookie_log_ext.csv) was created to test a larger input size. These files should result in identical output to the original
"cookie_log.csv" which contains the log example from the spec.

cookie_log_rand.csv is a randomly generated cookie log file that is created when running the "most_active_cookie_tests.cpp" program.
The required output and actual output are compared when running ./mactests. As are other outputs pertaining to errors and the "broken"
files.

Thanks very much for the opportunity to work on this project. It was an interesting challenge for me to test my best practices.
