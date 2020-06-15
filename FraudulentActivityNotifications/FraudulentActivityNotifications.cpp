#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    int numNotifications = 0;

    vector<int> lookbackExpenditures(d);
    for( size_t day = 0; day < d; day++ ) {
        lookbackExpenditures[day] = expenditure[day];
    }

    for( size_t day = d; day < expenditure.size(); day++ ) {
        // Sort all applicable indexes
        vector<int> sortedLookback(lookbackExpenditures);
        std::sort(sortedLookback.begin(), sortedLookback.end());

        int median;
        if( d % 2 == 0 ) { // even
            size_t upperIndex = d / 2;
            size_t lowerIndex = upperIndex - 1;

            median = sortedLookback[upperIndex] + sortedLookback[lowerIndex] / 2;
        }
        else { // odd
            size_t medianIndex = (d - 1) / 2;
            cout << "medIdx: " << medianIndex << endl;
            median = sortedLookback[medianIndex];
        }

        int potentialFraud = expenditure[day];
        cout << "pot: " << potentialFraud << " med: " << median << endl;
        if( potentialFraud >= 2*median ) {
            cout << "day: " << day << endl;
            numNotifications++;
        }

        lookbackExpenditures.erase(lookbackExpenditures.begin());
        lookbackExpenditures.push_back(potentialFraud);
    }
    return numNotifications;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

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
