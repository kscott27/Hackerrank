#include <bits/stdc++.h>

#include <exception>

using namespace std;

vector<string> split_string(string);

namespace helpers {

    void tooChaotic() {
        throw exception();
    }

    // swaps the given index, i, with the index directly before it
    void swap( vector<int>& q, int i ) {
        int ogLocation = q[i];
        q[i] = q[i-1];
        q[i-1] = ogLocation;
    }

}

// Complete the minimumBribes function below.
// This is an Insertion Sort algorithm.
void minimumBribes(vector<int> q) {
    int n = q.size();

    try {
        // Verify that the leader of the line did not commit >2 bribes.
        if( q.front() > 3 ) {
            helpers::tooChaotic();
        }

        int numSwaps = 0;
        for( int i = 1; i < n; i++ ) {
            int ogLocation = q[i];

            // Verify that the current index did not commit >2 bribes.
            if( (ogLocation - (i+1)) > 2 ) {
                helpers::tooChaotic();
            }

            // Recurse toward the front to ensure everything in front is sorted.
            int recurser = i;
            while( q[recurser] < q[recurser-1] ) {
                helpers::swap(q, recurser);
                numSwaps++;
                recurser--;
            }
        }

        cout << numSwaps << endl;
    }
    catch( exception& ) {
        cout << "Too chaotic" << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
