#include <bits/stdc++.h>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string s) {
  // Create matches map for stack unwinding comparisons
  unordered_map<char, char> matches;
  matches.insert({'(', ')'});
  matches.insert({'[', ']'});
  matches.insert({'{', '}'});

  int length = s.length();
  if(length % 2 != 0)
    return "NO";

  vector<char> stack;
  for(int i = 0; i < length; i++) {
    if( s[i] == '(' || s[i] == '[' || s[i] == '{' ) {
      stack.push_back(s[i]);
    }
    else if(stack.size() > 0 && matches[stack.back()] == s[i]) {
      stack.pop_back();
    }
    else {
      return "NO";
    }
  }
  return stack.size() > 0 ? "NO" : "YES";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);
        cout << result << endl;
        fout << result << "\n";
    }

    fout.close();

    return 0;
}
