/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the implementation file for the validation and misc. functions.
********************/

#include "Validation.hpp"

//Two option menu with input validation
int menu(std::string * choiceArray, int numChoices)
{
	for(int i = 0; i < numChoices; i++)
	{
		std::cout << i + 1 << ". " << choiceArray[i] << std::endl;
	}
	std::cout << "Please enter your choice: ";
	return validatePositiveRange(1, numChoices);
}

//Function to get a user's input and check if it is a positive integer. It will return the integer if valid.
int validatePositive()
{
	std::string input;
	bool again;

	//Loop endlessly until user provides a valid input
	do
	{
		getline(std::cin, input);
		again = false;
		//If first character is 0 or the string is null, print error and have user re-enter input
		if (input.length() == 0 || input[0] == '0')
		{
			again = true;
		}

		//If any character is non-numerical, print error and have user re-enter input
		if (!again)
		{
			for (int i = 0; i < static_cast<int>(input.length()); i++)
			{
				if (!isdigit(input[i]))
				{
					again = true;
				}
			}
		}

		//If input passes all of the tests, return the input as an integer
		if (!again)
		{
			return stoi(input);
		}

		//If input did not pass all the tests, have user try again
		std::cout << "Invalid format- Please enter a positive integer: ";
	} while (again);

	//function should never reach here, but if it does restart
	return validatePositive();
}

//Validates an input is a positve integer within the specified range
int validatePositiveRange(int lower, int upper)
{
	int input;
	bool rangeAgain = true;

	//Loop endlessly until user provides a valid input
	do
	{
		//validate input is a positive integer
		input = validatePositive();

		//Return input if input is within range
		if (input >= lower && input <= upper)
		{
			return input;
		}

		//If not, display this error message and prompt the user to try again
		std::cout << "Not in range- Please enter an integer between " << lower << " and " << upper << ": ";
	} while (rangeAgain);

	//function should never reach here, but if it does restart
	return validatePositiveRange(lower, upper);
}