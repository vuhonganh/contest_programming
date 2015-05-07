#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <cmath>

#define idx_char(charX) ( (int) (charX) - 65)
#define morse_of(charX) morse[idx_char(charX)]
using namespace std;

string morse[] = {".-", "-...", "-.-.", "-..",
		  ".", "..-.", "--.", "....",
		  "..", ".---", "-.-", ".-..",
		  "--", "-.", "---", ".--.",
		  "--.-", ".-.", "...", "-",
		  "..-", "...-", ".--", "-..-",
		  "-.--", "--.."};

map<string, int> vocab;
int max_length;

//turn string word (ABCDE par ex) into morse code and insert in vocab
void addWord(string &word)
{
  string morseRep;
  for(int i = 0; i < word.length(); ++i)
    {
      morseRep += morse_of(word[i]);
    }
  
  //check if the morse code representation of the word in the vocab already or not
  //if yes, increment its value
  if(vocab.count(morseRep) > 0)
    {
      vocab[morseRep] += 1;
    }
  else
    {
      vocab[morseRep] = 1;
    }

  max_length = max(max_length, (int) morseRep.length());
  //test
  //cout << word << " = " << morseRep << " times in the vocab = " << vocab[morseRep] <<  endl;
}

void calMatch(const string &morseCode, int matches[])
{
  //matches[i] = nb of combinations at the position i of morse code
  for(int i = 0; i < morseCode.length(); ++i)
    {
      int part_length = i+1;//bcz length = index + 1
      string part = morseCode.substr(0, part_length);
      if(i+1 <= max_length)
	{
	  if(vocab.count(part) > 0)
	    matches[i] += vocab[part];
	}

      for(int j = 1; j < part_length; ++j)
	{
	  string part_1 = part.substr(0, j);
	  string part_2 = part.substr(j, part_length - j);
	  if(vocab.count(part_2) > 0)
	    {
	      matches[i] += matches[j-1];
	    }
	}

      //cout << " matches[" << i << "] = " << matches[i] << endl;
    }
  
}

int main()
{
  //init max length word:
  max_length = 0;
  
  int nbCase;
  cin >> nbCase;

  for(int i = 0; i < nbCase; ++i)
    {
      vocab.clear();
      
      string morseCode;
      cin >> morseCode;

      int szVocab;
      cin >> szVocab;
      
      for(int j = 0; j < szVocab; ++j)
	{
	  string word;
	  cin >> word;
	  addWord(word);
	}      
      
      int arrLength = morseCode.length();
      int matches[arrLength];
      //init array to zero
      for(int k = 0; k < arrLength; ++k)
	matches[k] = 0;

      calMatch(morseCode, matches);      
      cout << matches[arrLength-1] << endl;
      if(i != nbCase-1)
	cout << "\n";
    }

  return 0;
  
}
