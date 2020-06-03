#include <bits/stdc++.h>

#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

using namespace std;

bool checkAnagrams( string comparison, string target) {
    try {    
        // Check if the 'comparison' and 'target' substrings are anagrams.
        // Iterate through each character of 'comparison' substring.
        for( size_t internalCompIndex = 0; internalCompIndex < comparison.size(); internalCompIndex++ ) {
            // use std::string::find() to determine if that char exists in 'target' substring.
            // If it does, remove that char from 'target' substring and continue.
            // If it does not, end the search on that 'target' substring.
            char character = comparison[internalCompIndex];
            size_t indexFound = target.find(character);
            if( indexFound == std::string::npos ) {
                throw std::exception();
            }
            else {
                target.erase(target.begin() + indexFound);
            }
        }
    } 
    catch( std::exception& ) {
        cout << "no match" << endl;
        return false;
    }

    return true;
}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {
    cout << "begin" << endl;
    typedef unique_ptr< vector<string> > VectorPtr;
    std::map<size_t, VectorPtr> substrMap;

    int n = s.size();
    int total = 0;

    // Iterate through all sizes of substrings, from 1-char
    // to n-char.
    for( size_t substringSize = 1; substringSize < n; substringSize++ ) {

        // Iterate through each substring of the given size as the
        // 'comparison' substring.
        for( size_t startingCompIndex = 0; startingCompIndex + substringSize <= n; startingCompIndex++ ) {
            cout << "comparing..." << endl;
            string comparison = s.substr(startingCompIndex, substringSize);
            cout << comparison << endl;
            // Iterate through each subsequent 'target' substring from the
            // current 'comparison' substring
            for( size_t startingTargetIndex = startingCompIndex + 1; startingTargetIndex + substringSize <= n; startingTargetIndex++) {
                cout << "targeting..." << endl;
                string target = s.substr(startingTargetIndex, substringSize);
                cout << target << endl;
                if( checkAnagrams(comparison, target) ) {
                    // Add to the total anagram count.
                    total++;
                    cout << "it's a match! Total anagrams: " << total << endl;
                }
            }
        }
    }

    return total;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
