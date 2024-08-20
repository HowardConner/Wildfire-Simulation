/*****************************************************************************
**************
* Programmer: Conner Howard
* File: Helper Functions
* Date: 
* Description: Personally designed helper functions that assist with various
*   tasks for a custom string tokenizer to a string numeric check function.
*   Includes misc. functions using the Standard Template Library and some of
*   the STL methods
******************************************************************************
*************/
#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>

// maps a double value from one range to another range
inline double mapValuef(const double value, const double fromMin, const float fromMax, const double toMin, const double toMax)
{
	return (value - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}
// maps a integer value from one range to another range
inline int mapValueI(const int value, const int fromMin, const float fromMax, const int toMin, const int toMax)
{
	return (value - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}

namespace strhlp // for "string helper"
{
	// --------------------------------------------------------------------------------------------- //
	//								    Helper Function Definitions
	// --------------------------------------------------------------------------------------------- //
	/* Function Name: String Tokenizer
	* Description: Takes and inputed string and returns a string type token up to a delimiter or end
	*	of the string. Will modify and delete the returned elements from the source string
	* Inputs: Reference to string, Delim char
	* Preconditions:
	* Outputs: string from beginning of scorce to delim or end of string, whichever comes first,
	*	modified source string that has the above removed from it (including delim)
	* Returns: string from beginning of scorce to delim or end of string, whichever comes first.
	*	If delim found, removes the delim char
	* Postconditions:
	*/
	inline std::string stringTok(std::string &source, const std::string &delim);

	/* Function Name: String Token Substring
	* Description: Using the endDelim, function returns a copy of all elements in the 
	*	source string before the end deliminiter. If delim is not found, returns an empty
	*	string. If the delim is in the string multiple times (ie, single letter like "l" 
	*	source has a double 'l' in it), returns up to first delim. If delim is blank,
	*	returns a copy of the source
	*		Ex: source = "hello world", end delim = "or"
	*			return: "hello w"
	*		Ex: source = "hello world", end delim = "l"
	*			return: "he"
	*		Ex: source = "hello world", end delim = "z"
	*			return: ""
	*		Ex: source = "hello world", end delim = ""
	*			return: "hello world"
	* Inputs: String to create a token copy of, delim to cut the copy at
	* Preconditions:
	* Outputs: a string copy of all items before the delimeter, Empty if failed to find
	* Returns: a string copy of all items before the delimeter, Empty if failed to find
	* Postconditions:
	*/
	inline std::string stringSubString(const std::string &source, const std::string &enddelim);

	/* Function Name: String Token Substring
	* Description: Uses the begin and end delims to return a substring of any characters between
	*	those two deliminators, excluding them both. If one or more delims are blank, they are
	*	ignored. If one or both of the delims is not found in the source, returns an empty
	*	string copy. If delims overlap, then return empty string
	*	Behavior is highlighed in examples below 
	*	  Two delims
	*		Ex: source = "hello world", begin delim = "h", end delim = "or"
	*			return: "ello w"
	*	  Empty First Delim
	*		Ex: source = "hello world", begin delim = "", end delim = "l"
	*			return: "he"
	*	  Empty end delim
	*		Ex: source = "hello world", begin delim = "wo", end delim = ""
	*			return: "rld"
	*	  Both Empty Delims
	*		Ex: source = "hello world", begin delim = "", end delim = ""
	*			return: "hello world"
	*	  Begin delim not found (any end delim)
	*		Ex: source = "hello world", begin delim = "z", end delim = ""
	*			return: ""
	*	  End delim not found (any begin delim)
	*		Ex: source = "hello world", begin delim = "", end delim = "z"
	*			return: ""
	*	  Overlapping Delims
	*		Ex: source = "hello world", begin delim = "lo", end delim = "o w"
	*			return: ""
	* Inputs: String to create a token copy of, delim to cut the copy at
	* Preconditions:
	* Outputs: a string copy of all items before the delimeter, Empty if failed to find
	* Returns: a string copy of all items before the delimeter, Empty if failed to find
	* Postconditions:
	*/
	inline std::string stringSubString(const std::string &source, const std::string &begindelim, const std::string &enddelim);

	/* Function Name: Is String a Number
	* Description: Is the input string only numbers? Checks whole string searching for the first
	*   non-numeric character in the array. Returns false if at least one character found
	* Inputs: String to check against
	* Preconditions:
	* Outputs: True if string has only numbers in it, false otherwise
	* Returns: True if string has only numbers in it, false otherwise
	* Postconditions:
	*/
	inline bool isStrNum(const std::string& input);

	/* Function Name: String Match to List Algorithm
	* Description: Compares a input string (inStr) to a list of valid strings. This algorithm
	*	compares the input string with the bank (validList), and will return true if the input
	*	matches at least one of the strings in validList. This method has an option for case
	*	sensativity. If set to false, does not compare based on case (ie, A==a is true), but if
	*	sensitivity is set to true, will only match if strings are exactly the same, case considered
	* Inputs: String to check, Vector of valid strings to compare to
	* Preconditions: none
	* Outputs: true if inStr matches at least one item in the ValidList vector, false otherwise
	* Returns: true if inStr matches at least one item in the ValidList vector, false otherwise
	* Postconditions: none
	*/
	inline bool stringMatch(const std::string& inStr, const std::vector<std::string>& validList,
	const bool caseSensative);

	/* Function Name: String Match to a String (Single Valid String overload)
	* Description: Compares a input string (inStr) to a single valid string. This algorithm
	*	compares the input string with the validInput, and will return true if the input
	*	matches that element. This method has an option for case sensativity. If set to false, does
	*	not compare based on case (ie, A==a is true), but if sensitivity is set to true, will only
	*	match if strings are exactly the same, case considered
	*	This overload was written for conciseness with the above, vector-bank option
	* Inputs: String to check, Input String to compare to
	* Preconditions: none
	* Outputs: true if inStr matches validInput, false otherwise
	* Returns: true if inStr matches validInput, false otherwise
	* Postconditions: none
	*/
	inline bool stringMatch(const std::string& inStr, const std::string& validInput,
		const bool caseSensative = false);

	/* Function Name: String To Uppercase
	* Description: Converts all alphabetical characters into their Uppercase
	*	equivalent character. Only capitalizes lower-case characters, ignores
	*	all others
	* Inputs: const reference to an inString
	* Preconditions: none
	* Outputs: returned uppered string
	* Returns: returned uppered string
	* Postconditions: none
	*/
	inline std::string stringUpper(const std::string& inStr);

	/* Function Name: String To Lowercase
	* Description: Converts all alphabetical characters into their Lowercase
	*	equivalent character. Only lowers only upper-case characters, ignores
	*	all others
	* Inputs: cosnt reference to an inString
	* Preconditions: none
	* Outputs: returned lowered string
	* Returns: returned lowered string
	* Postconditions: none
	*/
	inline std::string stringLower(const std::string& inStr);
}

// --------------------------------------------------------------------------------------------- //
//								    Helper Function Implimentations
// --------------------------------------------------------------------------------------------- //
/* Function Name: String Tokenizer
* Description: Takes and inputed string and returns a string type token up to a delimiter or end
*	of the string. Will modify and delete the returned elements from the source string
* Inputs: Reference to string, Delim char
* Preconditions:
* Outputs: string from beginning of scorce to delim or end of string, whichever comes first,
*	modified source string that has the above removed from it (including delim)
* Returns: string from beginning of scorce to delim or end of string, whichever comes first.
*	If delim found, removes the delim char
* Postconditions:
*/
inline std::string strhlp::stringTok(std::string &source, const std::string &delim)
{
	// define variables
	size_t pos = 0;
	std::string token;

	// locate the first delim
	pos = source.find(delim);

	if (pos == std::string::npos)
	{
		// delim not found, return whole string and axe the source
		token = std::move(source);
		source.clear();
	}
	else
	{
		// delim found, generate temp substring
		token = source.substr(0, pos);
		source.erase(0, pos + delim.length());
	}

	return token;
};

/* Function Name: String Token Substring
* Description: Using the endDelim, function returns a copy of all elements in the 
*	source string before the end deliminiter. If delim is not found, returns an empty
*	string. If the delim is in the string multiple times (ie, single letter like "l" 
*	source has a double 'l' in it), returns up to first delim. If delim is blank,
*	returns a copy of the source
*		Ex: source = "hello world", end delim = "or"
*			return: "hello w"
*		Ex: source = "hello world", end delim = "l"
*			return: "he"
*		Ex: source = "hello world", end delim = "z"
*			return: ""
*		Ex: source = "hello world", end delim = ""
*			return: "hello world"
* Inputs: String to create a token copy of, delim to cut the copy at
* Preconditions:
* Outputs: a string copy of all items before the delimeter, Empty if failed to find
* Returns: a string copy of all items before the delimeter, Empty if failed to find
* Postconditions:
*/
inline std::string strhlp::stringSubString(const std::string& source, const std::string& enddelim)
{
	// define variables
	size_t pos = 0;
	std::string token;
	
	// check for empty delim, if so, return copy of source
	if(enddelim.empty())
	{
		return source;
	}

	// locate the first delim
	pos = source.find(enddelim);

	if (pos == std::string::npos)
	{
		// delim not found, return blank string
		token = "";
	}
	else
	{
		// delim found, generate temp substring
		token = source.substr(0, pos);
	}

	return token;
}

/* Function Name: String Token Substring
* Description: Uses the begin and end delims to return a substring of any characters between
*	those two deliminators, excluding them both. If one or more delims are blank, they are
*	ignored. If one or both of the delims is not found in the source, returns an empty
*	string copy. If delims overlap, then return empty string
*	Behavior is highlighed in examples below 
*	  Two delims
*		Ex: source = "hello world", begin delim = "h", end delim = "or"
*			return: "ello w"
*	  Empty First Delim
*		Ex: source = "hello world", begin delim = "", end delim = "l"
*			return: "he"
*	  Empty end delim
*		Ex: source = "hello world", begin delim = "wo", end delim = ""
*			return: "rld"
*	  Both Empty Delims
*		Ex: source = "hello world", begin delim = "", end delim = ""
*			return: "hello world"
*	  Begin delim not found (any end delim)
*		Ex: source = "hello world", begin delim = "z", end delim = ""
*			return: ""
*	  End delim not found (any begin delim)
*		Ex: source = "hello world", begin delim = "", end delim = "z"
*			return: ""
*	  Overlapping Delims
*		Ex: source = "hello world", begin delim = "lo", end delim = "o w"
*			return: ""
* Inputs: String to create a token copy of, delim to cut the copy at
* Preconditions:
* Outputs: a string copy of all items before the delimeter, Empty if failed to find
* Returns: a string copy of all items before the delimeter, Empty if failed to find
* Postconditions:
*/
inline std::string stringSubString(const std::string &source, const std::string &begindelim, const std::string &enddelim)
{
	// define variables
	size_t beginPos = 0,
			endPos = 0;
	std::string token = "";
	
	// check for empty delim, if so, return copy of source
	if(begindelim.empty())
	{
		// set begin position to zero (initial value)
		//beginPos = 0;
	}
	else
	{
		beginPos = source.find(begindelim);
	}

	// check for empty delim, if so, return copy of source
	if(enddelim.empty())
	{
		// set begin position to zero (initial value)
		//endPos = 0;
	}
	else
	{
		endPos = source.find(enddelim);
	}

	if (beginPos == std::string::npos)
	{
		// delim not found, set begin pos to start of source
		beginPos = 0;
	}
	else
	{
		// otherwise, offset the beginning position by the beginDelim length
		beginPos += begindelim.length();
	}

	if (endPos == std::string::npos)
	{
		// delim not found, set end pos to end(length) of source
		endPos = source.length();
	}

	// check if dont overlap
	if(beginPos < endPos)
	{
		// beginning is less than end position, substring source
		token = source.substr(beginPos, endPos);
	}

	return token;
}

/* Function Name: Is String a Number
* Description: Is the input string only numbers? Checks whole string searching for the first
*   non-numeric character in the array. Returns false if at least one character found
* Inputs: String to check against
* Preconditions:
* Outputs: True if string has only numbers in it, false otherwise
* Returns: True if string has only numbers in it, false otherwise
* Postconditions:
*/
inline bool strhlp::isStrNum(const std::string& input)
{
	// define variables

	// check if string is empty
	if(input.empty())
	{
		// string is empty, therefore, no number
		return false;
	}

	// loop through, checking for all characters to be digits
	for(size_t i = 0; i < input.size(); i++)
	{
		if(!std::isdigit(input[i]))
		{
			// a non-digit character was found, return false
			return false;
		}
	}
	
	// string has a size and contains only numbers
	return true;
}


/* Function Name: String Match to List Algorithm
* Description: Compares a input string (inStr) to a list of valid strings. This algorithm
*	compares the input string with the bank (validList), and will return true if the input
*	matches at least one of the strings in validList. This method has an option for case
*	sensativity. If set to false, does not compare based on case (ie, A==a is true), but if
*	sensitivity is set to true, will only match if strings are exactly the same, case considered
* Inputs: String to check, Vector of valid strings to compare to
* Preconditions: none
* Outputs: true if inStr matches at least one item in the ValidList vector, false otherwise
* Returns: true if inStr matches at least one item in the ValidList vector, false otherwise
* Postconditions: none
*/
inline bool strhlp::stringMatch(const std::string& inStr, const std::vector<std::string>& validList,
 const bool caseSensative)
 {
	// define variables
	std::string lowered(inStr);
	std::vector<std::string> loweredValidVec(validList);
	bool result = false;

	// check for case sensitivity. If not case sensative, lower all characters in both input
	//	and valid list
	if(!caseSensative)
	{
		// lower the input array
		lowered = stringLower(inStr);

		// convert all strings in the list bank to lowere
		for(size_t index = 0; index < validList.size(); index++)
		{
			for(size_t i = 0; i < inStr.size(); i++)
			{
				loweredValidVec.at(index) = stringLower(validList.at(index));
			}
		}
	}

	// check if the string matches any of the items in the validList vector
	for(size_t i = 0; i < loweredValidVec.size(); i++)
	{
		// check if matches any of the items in the vector
		if(lowered == loweredValidVec[i])
		{
			result = true;
			break;
		}
	}

	return result;
 }

// overload for single string
// precondition: assumes that validList is all lowercase if case-sensativity is off

/* Function Name: String Match to a String (Single Valid String overload)
* Description: Compares a input string (inStr) to a single valid string. This algorithm
*	compares the input string with the validInput, and will return true if the input
*	matches that element. This method has an option for case sensativity. If set to false, does
*	not compare based on case (ie, A==a is true), but if sensitivity is set to true, will only
*	match if strings are exactly the same, case considered
*	This overload was written for conciseness with the above, vector-bank option
* Inputs: String to check, Input String to compare to
* Preconditions: none
* Outputs: true if inStr matches validInput, false otherwise
* Returns: true if inStr matches validInput, false otherwise
* Postconditions: none
*/
inline bool strhlp::stringMatch(const std::string& inStr, const std::string& validInput,
 const bool caseSensative)
{
	// use built-in string comparison function of std::string
	std::string loweredInStr, loweredValid;

	if(caseSensative == true)
	{
		// lower both strings
		loweredInStr = strhlp::stringLower(inStr);
		loweredValid = strhlp::stringLower(inStr);

		// now compare
		return loweredValid.compare(loweredInStr);
	}
	else
	{
		return validInput.compare(inStr);
	}
}

/* Function Name: String To Uppercase
* Description: Converts all alphabetical characters into their Uppercase
*	equivalent character. Only capitalizes lower-case characters, ignores
*	all others
* Inputs: const reference to an inString
* Preconditions: none
* Outputs: returned uppered string
* Returns: returned uppered string
* Postconditions: none
*/
std::string strhlp::stringUpper(const std::string& inStr)
{
	// define variables
	std::string uppered(inStr);

	// for each character, call string up
	for (size_t i = 0; i < inStr.size(); i++)
	{
		// convert all LOWER CASE, ALPHABETICAL characters to UPPER form
		if(std::isalpha(inStr[i]) && std::islower(inStr[i]))
		{
			uppered[i] = std::toupper(inStr[i]);
		}
	}

	return uppered;
}

/* Function Name: String To Lowercase
* Description: Converts all alphabetical characters into their Lowercase
*	equivalent character. Only lowers only upper-case characters, ignores
*	all others
* Inputs: cosnt reference to an inString
* Preconditions: none
* Outputs: returned lowered string
* Returns: returned lowered string
* Postconditions: none
*/
std::string strhlp::stringLower(const std::string& inStr)
{
	// define variables
	std::string lowered(inStr);

	// for each character, call string up
	for (size_t i = 0; i < inStr.size(); i++)
	{
		// convert all LOWER CASE, ALPHABETICAL characters to UPPER form
		if(std::isalpha(inStr[i]) && std::isupper(inStr[i]))
		{
			lowered[i] = std::tolower(inStr[i]);
		}
	}

	return lowered;
}

// --------------------------------------------------------------------------------------------- //
//									Other Functions
// --------------------------------------------------------------------------------------------- //


/* mFunction Name:
* Description:
* Inputs:
* Outputs:
*/


/* Function Name:
* Description:
* Inputs:
* Preconditions:
* Outputs:
* Returns:
* Postconditions:
*/
#endif