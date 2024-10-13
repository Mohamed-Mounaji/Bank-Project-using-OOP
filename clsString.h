#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
	string _Value;
public:
	clsString()
	{
		_Value = "";
	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	}
	short Length()
	{
		return Length(_Value);
	}

	static short CountWords(string S1)
	{
		string delim = " ";
		short Counter = 0;
		short DelPos = 0;
		string Word = "";
		while ((DelPos = S1.find(delim)) != string::npos)
		{
			Word = S1.substr(0, DelPos);
			if (Word != "")
				Counter++;
			S1.erase(0, DelPos + 1);
		}

		if (S1 != "")
			Counter++;
		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool isFirstLetter = true;
		for (char& Letter : S1)
		{
			if (Letter != ' ' && isFirstLetter)
				Letter = toupper(Letter);
			isFirstLetter = Letter == ' ';
		}
		return S1;
	}
	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool isFirstLetter = true;
		for (char& Letter : S1)
		{
			if (Letter != ' ' && isFirstLetter)
				Letter = tolower(Letter);
			isFirstLetter = Letter == ' ';
		}
		return S1;
	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1)
	{
		for (char& C : S1)
		{
			C = toupper(C);
		}
		return S1;
	}
	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1)
	{
		for (char& C : S1)
		{
			C = tolower(C);
		}
		return S1;
	}
	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char Letter)
	{
		return isupper(Letter) ? tolower(Letter) : toupper(Letter);
	}

	static string InvertAllLettersCase(string S1)
	{
		for (char& C : S1)
		{
			C = InvertLetterCase(C);
		}
		return S1;
	}
	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { SmallLetters = 1, CapitalLetters = 2, All = 0 };
	static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		switch (WhatToCount)
		{
		case enWhatToCount::SmallLetters:
			return CountSmallLetters(S1);
		case enWhatToCount::CapitalLetters:
			return CountCapitalLetters(S1);
		default:
			return S1.length();
		}
	}

	static short CountCapitalLetters(string S1)
	{
		short Counter = 0;
		for (char C : S1)
			if (isupper(C)) Counter++;
		return Counter;
	}
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string S1)
	{
		short Counter = 0;
		for (char& C : S1)
			if (islower(C)) Counter++;
		return Counter;
	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{
		short Counter = 0;
		for (char& C : S1)
		{
			if (MatchCase)
			{
				if (C == Letter) Counter++;
			}
			else
			{
				if (tolower(C) == tolower(Letter)) Counter++;
			}
		}
		return Counter;
	}
	short CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool isVowel(char Letter)
	{
		Letter = tolower(Letter);
		return Letter == 'a' || Letter == 'e' || Letter == 'u' || Letter == 'i' || Letter == 'o';
	}

	static short CountVowels(string S1)
	{
		short Counter = 0;
		for (char& Char : S1)
		{
			if (isVowel(Char)) Counter++;
		}
		return Counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static vector <string> Split(string S1, string Delim)
	{
		vector <string> vWords;
		short DelimPos = 0;
		string Word = "";
		while ((DelimPos = S1.find(Delim)) != string::npos)
		{
			Word = S1.substr(0, DelimPos);
			if (Word != "")
				vWords.push_back(Word);
			S1.erase(0, DelimPos + Delim.length());
		}
		if (S1 != "")
			vWords.push_back(S1);
		return vWords;
	}
	static vector <string> SplitDate(string S1, string Delim = "/")
	{
		vector <string> vWords;
		short DelimPos = 0;
		string Word = "";
		while ((DelimPos = S1.find(Delim)) != string::npos)
		{
			Word = S1.substr(0, DelimPos);
			if (Word != "")
				vWords.push_back(Word);
			S1.erase(0, DelimPos + Delim.length());
		}
		if (S1 != "")
			vWords.push_back(S1);
		return vWords;
	}
	vector <string> Split(string Delim)
	{
		return Split(_Value, Delim);
	}

	static string TrimLeft(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1)
	{
		for (int i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
				return S1.substr(0, i + 1);
		}
		return "";
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return TrimRight(TrimLeft(S1));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinWords(vector <string> vWords, string Delim)
	{
		string Text = "";
		for (string& Word : vWords)
			Text += Word + Delim;
		return Text.substr(0, Text.length() - Delim.length());
	}

	static string JoinWords(string Words[], string Delim)
	{
		string Result = "";
		for (int i = 0; i <= size(*Words); i++)
			Result += Words[i] + Delim;
		return Result.substr(0, Result.length() - Delim.length());
	}

	static string ReversWords(string S1)
	{
		vector <string> vWords = Split(S1, " ");
		string Result = "";

		vector <string>::iterator iter = vWords.end();
		while (iter != vWords.begin())
		{
			iter--;
			Result += *iter + " ";
		}
		return Result.substr(0, Result.length() - 1);
	}
	void ReversWords()
	{
		_Value = ReversWords(_Value);
	}



	static string ReplaceWord(string Text, string OrigWord, string NewWord, bool MatchCase)
	{
		vector <string> vWords = Split(Text, " ");
		for (string& Word : vWords)
		{
			if (MatchCase)
			{
				if (Word == OrigWord)
					Word = NewWord;
			}
			else
			{
				if (LowerAllString(Word) == LowerAllString(OrigWord))
					Word = NewWord;
			}
		}
		return JoinWords(vWords, " ");
	}
	string ReplaceWord(string OrigWord, string NewWord, bool MatchCase)
	{
		return ReplaceWord(_Value, OrigWord, NewWord, MatchCase);
	}

	static string RemovePunctuations(string Text)
	{
		string Result = "";
		for (char C : Text)
			if (!ispunct(C)) Result += C;
		return Result;
	}
	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}

};