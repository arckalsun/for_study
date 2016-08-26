#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
using namespace std;
string ungarded_convert(const string &say)
{
  stringstream ss;
  string s;
  unsigned count = 0;
  char last = say[0];

  for (decltype(s.size()) index = 0; index <= say.size(); ++index)
    {
      if (say[index] == last)
	++count;
      else
	{
	  ss << count <<last;
	  count = 1;
	  last = say[index];
	}
    }
  ss >> s;
  return s;
}
string countAndSay(int n)
{
  if (n <= 0) return string ();
  string say = "1";
  for (int i = 1; i < n; ++i)
    {
      say = ungarded_convert(say);
    }
  return say;
}

int main(int argc, char** argv)
{
  unsigned n = 1;
  if (argc != 2){
    cout << "Usage: " << argv[0] << " "
	 << "n"<<endl;
    return -1;
  }
  
  if (!(n = atoi(argv[1])))
    return -1;
  cout << countAndSay(n) << endl;
  return 0;
}
