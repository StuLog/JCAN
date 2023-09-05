#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bits/stdc++.h>

using namespace std;

/** defining a map for the dbc information */
map<string, map<string, map<int, string>>> DBC_map;


/** This will be done with multithreading some day, currently this reads in all the info we need about the file*/
void read_in_dbc(string DBC_name) {
    string next_line;
    ifstream DBC_file(DBC_name);
    string message_name;
    int counter;
    int start, end = -1;
    int index = 1;
    while (getline(DBC_file, next_line)) {
        if (next_line.find("message('") != string::npos) {
            counter = 0;
            index = 1;
            do {
                start = end + 1;
                end = next_line.find("'", start);
                string current_info = next_line.substr(start, end - start);
                if (counter == 1) {
                    message_name = current_info;
                } else if (counter == 2) {
                    end = -1;
                    int sub_counter = 0;
                    do {
                        start = end + 1;
                        end = next_line.find(",", start);
                        string current_info = next_line.substr(start, end - start);
                        if (sub_counter == 3) {
                            DBC_map[DBC_name][message_name][0] = current_info;
                        }
                        sub_counter += 1;
                    } while (end != -1);
                }
                else if (counter > 2){
                    end = -1;
                }
                counter += 1;
            } while (end != -1);
        }
        else if (next_line.find("signal('") != string::npos) {
            counter = 0;
            end = -1;
            counter = 0;
            string start_end;
            do {
                start = end + 1;
                end = next_line.find(",", start);
                string current_info = next_line.substr(start, end - start);
                if (counter == 1) {
                    start_end += current_info;
                }
                else if(counter == 2){
                    start_end += current_info;
                    DBC_map[DBC_name][message_name][index] = start_end;
                    index += 1;
                }
                else if (counter > 2){
                    end = -1;
                }
                counter += 1;
            } while (end != -1);
        }
    }
    int f = 0;
}

int main() {
    clock_t start, end;start = clock();

    read_in_dbc("C://Users//Stuart//CLionProjects//untitled12//CE_dbc.txt");
    read_in_dbc("C://Users//Stuart//CLionProjects//untitled12//HS_dbc.txt");
    // Recording the end clock tick.
    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}
