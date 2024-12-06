// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
using namespace std;

void removeNonLetters(string& s);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets = 50000) : m_words(maxBuckets) {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    vector<list<string>> m_words;
};

void DictionaryImpl::insert(string word){
    removeNonLetters(word);
    
    //hashing
    string sorted = word;
    sort(sorted.begin(), sorted.end());
    unsigned int x = hash<string>()(sorted);
    unsigned int bucket_num = x%m_words.size();
    
    m_words[bucket_num].push_back(word);
}


void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;
    
    //hashing
    string sorted = letters;
    sort(sorted.begin(), sorted.end());
    unsigned int x = hash<string>()(sorted);
    unsigned int bucket_num = x%m_words.size();
    
    list<string> listofwords = m_words[bucket_num];
    
    if(listofwords.empty())
        return;
    
    for(list<string>::iterator p = listofwords.begin() ; p != listofwords.end(); p++){
        string sorted2 = *p;
        sort(sorted2.begin(), sorted2.end());
        if(sorted2 == sorted)
            callback(*p);
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}


//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
