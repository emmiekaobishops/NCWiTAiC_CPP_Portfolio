#include <iostream>
#include<sstream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<ctime>

using namespace std;

vector<string> splitString(string base_str){
    /* splits a string into a vector of words*/
    vector<string> ret_vect;
    int current_iter = 0;

    for(int i = 0; i < base_str.size(); i++){
        if(base_str[i] == ' ' || base_str[i] == '\n'){
            string add_str;
            for(int j = current_iter; j < i; j++){
                add_str += base_str[j];
            }
            ret_vect.push_back(add_str);
            current_iter = i + 1;
        }
    }

    string add_str;
    for(int i = current_iter; i < base_str.size(); i++){
                add_str += base_str[i];
            }
        ret_vect.push_back(add_str);

    return ret_vect;
}

string f_to_str(string file_str){
    /*makes an fstream into a string*/
    ifstream ret_fstr(file_str, ios::in);
    string ret_str;
    string line;

    while (getline(ret_fstr, line)) {
        ret_str += line + " \n";
    }
    ret_fstr.close();
    return ret_str;
}

string getLast(string input){
    /*get the last word in a string of words*/
    vector <string> split_words = splitString(input);
    if (!split_words.empty()) {
        return split_words.back();
    }
    return "";
}

int main(){
    srand(time(nullptr));
    map<string, vector<string>> ultimate_dict;
    vector<string> collected_words;
    string alice_str = f_to_str("alice.txt");
    vector<string> alice_v = splitString(alice_str);
    for(int i=0; i<alice_v.size() - 2; i++) {
        if (ultimate_dict.find(alice_v[i]) == ultimate_dict.end()){
            collected_words.push_back(alice_v[i]);
            vector<string> new_v;
            new_v.push_back(alice_v[i + 1] + " " + alice_v[i + 2]);
            ultimate_dict[alice_v[i]] = new_v;
        }
        else {
            ultimate_dict[alice_v[i]].push_back(alice_v[i + 1] + " " + alice_v[i + 2]);
        }
    }

    int counts = 0;
    bool first_word = true;
    string current_word;
    string last_word;
    while (counts < 20){
        if(first_word == true){
            current_word = "Alice was";
            last_word = "was";
            first_word = false;
        }
        else{
            vector<string>vect = ultimate_dict[last_word];
            // select random from vect
            int index = rand() % vect.size();
            current_word = vect[index];
            last_word = getLast(current_word);
            for(int i=0; i<current_word.size(); i++){
                if (current_word[i] == '.' || current_word[i] == '!' || current_word[i] == '?'){
                    counts ++;
                }
            }
        }
        cout << current_word << ' ';
    }
    return 0;
}