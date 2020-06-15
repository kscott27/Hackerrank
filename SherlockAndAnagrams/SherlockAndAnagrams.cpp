#include <bits/stdc++.h>

#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

using namespace std;


namespace helpers {
    typedef shared_ptr< vector<size_t> >      VectorPtr;
    typedef shared_ptr< vector<std::string> > StringVectorPtr;
    typedef std::map<char, VectorPtr>         IndexMap;
    typedef std::map<size_t, StringVectorPtr> StringMap;

    void createIndexMap( IndexMap&, std::string& );
    void refineIndexMap( IndexMap& );
    void createSortedIndexList( IndexMap&, VectorPtr& );
    void createSubStrMap( StringMap&, VectorPtr&, std::string& );
    void insertSubStr( StringMap&, std::string );
    size_t countAnagrams( StringMap& );
}

void helpers::createIndexMap( IndexMap& m, std::string& s ) {
    // Locate all characters that repeat (capable of creating potential
    // anagrams).
    for( size_t index = 0; index < s.size(); index++ ) {
        try {
            // Throws if the key does not exist.
            helpers::VectorPtr value = m.at(s[index]);

            value->push_back(index);
        }
        catch(...) {
            helpers::VectorPtr indexList(new std::vector<size_t>);
            indexList->push_back(index);
            std::pair<helpers::IndexMap::iterator, bool> result = m.insert({s[index], indexList});
        }
    }
}

// Remove all characters that do not repeat from the map.
void helpers::refineIndexMap( IndexMap& m ) {
    for( helpers::IndexMap::iterator it = m.begin(); it != m.end(); ) {
        if( it->second->size() < 2 ) {
            // Need to do some tip-toeing here to ensure that an
            // erased iterator does not receive an increment attempt.
            m.erase(it++);
        }
        else {
            it++;
        }
    }
}

void helpers::createSortedIndexList( IndexMap& iMap, VectorPtr& sortedList ) {
    for( auto& it : iMap ) {
        VectorPtr vec = it.second;
        for( auto& index : *vec ) {
            sortedList->push_back(index);
        }
    }

    std::sort(sortedList->begin(), sortedList->end());
}

void helpers::createSubStrMap( StringMap& sMap, VectorPtr& iList, std::string& s ) {
    for( auto& index : *iList ) {
        // Collect all substrings, iterating to the right
        for( size_t length = 1; length <= s.size() - index; length++ ) {
            std::string substr = s.substr(index, length);
            helpers::insertSubStr(sMap, substr);
        }

        // Collect all substrings, iterating to the left, avoiding any new substrings
        // resulting from a newly collected repeating character
        size_t length = 2;
        for( int startingIndex = index - 1; startingIndex >= 0; startingIndex-- ) {
            if( std::find(iList->begin(), iList->end(), startingIndex) == iList->end() ) {
                std::string substr = s.substr(startingIndex, length);
                helpers::insertSubStr(sMap, substr);
            }
            length++;
        }
    }
}

// Insert substrings into a map, with length as the key, after sorting
// each substring first.
void helpers::insertSubStr( StringMap& sMap, std::string subStr ) {
    try {
        // Throws if the key does not exist.
        helpers::StringVectorPtr value = sMap.at(subStr.size());
        std::sort(subStr.begin(), subStr.end());
        value->push_back(subStr);
    }
    catch(...) {
        helpers::StringVectorPtr subStrList(new std::vector<std::string>);
        std::sort(subStr.begin(), subStr.end());
        subStrList->push_back(subStr);
        std::pair<helpers::StringMap::iterator, bool> result = sMap.insert({subStr.size(), subStrList});
    }
}

size_t helpers::countAnagrams( StringMap& sMap ) {
    size_t totalAnagrams = 0;
    for( helpers::StringMap::iterator it = sMap.begin(); it != sMap.end(); it++ ) {
        if( it->first == sMap.size() ) {
            break;
        }
        StringVectorPtr stringList = it->second;
        for( size_t comparisonIndex = 0; comparisonIndex < stringList->size(); comparisonIndex++ ) {
            std::string comparison = stringList->at(comparisonIndex);
            for( size_t targetIndex = comparisonIndex + 1; targetIndex < stringList->size(); targetIndex++ ) {
                std::string target = stringList->at(targetIndex);
                std::string debugTarget = target;
                if( comparison.compare(target) == 0 ) {
                    totalAnagrams++;
                }
            }
        }
    }
    return totalAnagrams;
}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {
    helpers::IndexMap  indexMap;
    helpers::VectorPtr sortedIndexList( new vector<size_t> );

    helpers::createIndexMap(indexMap, s);
    helpers::refineIndexMap(indexMap);
    helpers::createSortedIndexList(indexMap, sortedIndexList);

    // Create map of potential anagram substrings with length as the key.
    helpers::StringMap stringMap;
    helpers::createSubStrMap(stringMap, sortedIndexList, s);

    return helpers::countAnagrams(stringMap);
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
