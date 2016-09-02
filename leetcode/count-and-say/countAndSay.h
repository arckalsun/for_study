#include<iostream>
#include<sstream>
#include<string>

using std::string;
using std::stringstream;

class Solution {

public:

  string countAndSay(int n) 

  {

    if (n<0) return string();

    string say = "1";

    for (int i=1;i<n;++i)

      say = ungarded_convert(say);

    return say;

  }

    

  string ungarded_convert(const string &say)

  {

    stringstream ss;

    int count = 0;

    char last = say[0];

        

    for (size_t i=0;i<=say.size();++i)

      {

	if (say[i] == last)

	  ++count;

	else

	  {

	    ss << count << last;

	    count = 1;

	    last = say[i];

	  }

      }

    return ss;

  }

};
