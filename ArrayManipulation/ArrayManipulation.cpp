#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the arrayManipulation function below.
long arrayManipulation(int n, vector<vector<int>> queries) {
    std::map<long, long> operationMap;
    operationMap.insert({1, 0});

    int line = 2; // Used for debugging to correspond the iteration with the input line of the current operation

    for( auto& row : queries ) {
        int a = row[0];
        int b = row[1];
        int k = row[2];

        // For the starting index, add the delta between this index and the
        // preceding indexes.
        auto begin = operationMap.find(a);
        if( begin != operationMap.end() ) {
            begin->second = begin->second + k;
        }
        else {
            auto it = operationMap.lower_bound(a);
            if( it != operationMap.begin() ) {
                it--; // Decrement to the iterator that holds the value of the range
                      // our new index is in.
                operationMap.insert({a, k});
            }
            else {
                cout << "should never get here" << endl;
            }
        }

        // Subtract the value of k to signify the
        // delta between the preceding indexes that received the adding operation,
        // and the subsequent indexes, that did not.
        auto subsequent = operationMap.find(b+1);
        if( subsequent == operationMap.end() ) {
            auto it = operationMap.lower_bound(b+1);
            if( b+1 <= n ) {
                it--;
                operationMap.insert({b+1, -k}); // k was just added to the previous value, so subtract off to get the subsequent delta.
            }
        }
        else {
            subsequent->second = subsequent->second - k;
        }

        // Uncomment for debugging
        // for( auto&& p : operationMap ) {
        //     cout << "first: " << p.first << " second: " << p.second << endl;
        // }
        // cout << "line: " << line++ << endl;
    }

    // Sum all of the deltas and cache the maxValue.
    long maxValue = 0;
    long rollingValue = 0;
    for( auto&& op : operationMap ) {
        rollingValue = rollingValue + op.second;
        if( rollingValue > maxValue ) {
            maxValue = rollingValue;
        }
    }

    return maxValue;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = arrayManipulation(n, queries);

    fout << result << "\n";

    fout.close();

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
