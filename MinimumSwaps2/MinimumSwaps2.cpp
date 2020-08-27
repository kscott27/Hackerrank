#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    int size = arr.size();
    vector<pair<int, int>> originalIdxs(size); 
    for(int i = 0; i < size; i++) {
        originalIdxs[i].first = arr[i];
        originalIdxs[i].second = i; 
    }

    sort(originalIdxs.begin(), originalIdxs.end());

    // Find strongly connected components of the now sorted
    // vector of value-original_idx pairs. The visited array is
    // used to determine when a strongly connected component has
    // been fully traversed. The number of swaps needed to sort
    // a strongly connected component is the size of the component
    // minus 1.
    vector<bool> visited(arr.size());
    int connections = 0;
    for(int i = 0; i < size; i++) {
        if(originalIdxs[i].second != i && visited[i] == false) {
            int connectionIdx = i;
            while(!visited[connectionIdx]) {
                connections++;
                visited[connectionIdx] = true;
                connectionIdx = originalIdxs[connectionIdx].second;
            }
            connections--;
        }
    }
    return connections;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    fout << res << "\n";

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
