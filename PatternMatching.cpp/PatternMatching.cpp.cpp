// PatternMatching.cpp.cpp : Defines the entry point for the console application.
//
//Z-Array : longest substring startingat i which is also prefix of str[0..n-1]

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void generateZArray(string& s, int* Zarr)
{
	//Zarr[i] = longest substring starting at i which is also a prefix of s
	//[L R] maintains a window such that it is also a prefix of string
	int n = s.length();
	int L, R, k;
	L = R = 0;
	for (int i = 0; i < n; i++)
	{
		if (i > R)
		{
			//means current char is not part of the prefix hence re-calculate window
			L = R = i;
			while (R < n && s[R - L] == s[R])
			{
				R++;
			}
			Zarr[i] = R - L;
			R--;
		}
		else { //i << R ...means it is withing prefix
			k = i - L;
			if (Zarr[k] < (R - i + 1))
			{
				Zarr[i] = Zarr[k];
			}
			else {
				L = i;
				while (R < n && s[R - L] == s[R])
				{
					R++;
				}
				Zarr[i] = R - L;
				R--;
			}
		}
	}
}

void Z_Algo_Search(string& text, string& pattern)
{
	string s = pattern + "$" + text;
	int n = s.length();
	int* Zarr = new int[n];
	generateZArray(s, Zarr);
	int m = pattern.length();
	//whenever Z value is n means..there is substring at at idx i which is matching pattern
	int i = m;
	while (i < n)
	{
		if (Zarr[i] == m)
		{
			cout << "Pattern found at idx : " << (i - m-1) << endl;
		}
		i++;
	}
}

void generateLPS(string& s, int* LPS)
{
	int n = s.length();
	int len = 0;
	LPS[len] = 0;
	int i = 1;
	while (i < n)
	{
		if (s[i] == s[len])
		{
			LPS[i++] = ++len;
		}
		else {
			if (len != 0)
			{
				len = LPS[len - 1];
			}
			else {
				LPS[i++] = 0;
			}
		}
	}
}
void KMPSearch(string& text, string& pattern)
{
	//first create LPS array
	int m = pattern.length();
	int* LPS = new int[m];
	generateLPS(pattern, LPS);
	//Now start searching
	int n = text.length();
	int i = 0; //text
	int j = 0; //pattern 
	while (i < n) 
	{
		if (pattern[j] != text[i])
		{
			//pattern was matching till (j-1)..means LPS[j-1] char are still matching till (i-1)
			if (j != 0)
			{
				j = LPS[j - 1];
			}
			else {
				i++;
			}
		}
		if (pattern[j] == text[i])
		{
			i++; j++;

			if (j == m) //have match m character..means pattern found at i-m;
			{
				cout << "Pattern found at idx : " << (i - m) << endl;
				//setting j for next location of pattern in string
				j = LPS[j - 1];
			}
		}
	}
}

int main()
{
	cout << "Enter Text : ";
	string text;
	cin >> text;
	while (1)
	{
		cout << endl << "Enter patter to search : ";
		string pat;
		cin >> pat;
		cout << endl;

		cout << "###########............KMP ALGO.............################" << endl;
		KMPSearch(text, pat);
		cout << "########### --------END OF KMP ALGO---------################" << endl;

		cout << "###########............Z ALGO.............################" << endl;
		Z_Algo_Search(text, pat);
		cout << "########### --------END OF Z ALGO---------################" << endl;
	}
    return 0;
}

