/********************
** Author: Kelvin Lu
** Date: 11/24/2017
** Description: This is the specification file for the validation and misc. functions.
********************/

#ifndef VALIDATION_HPP
#define VALIDATION_HPP

/********************
Clear screen function
** Description: Definition of clear screen function for all operating systems. Reference: Instructor's answer on @391 on Piazza (https://piazza.com/class/j6zp57dd1bh3uy?cid=391)
********************/
#ifdef _WIN32
#include <stdlib.h>
#define CLEAR()	system("CLS")
#elif __linux__
#include <stdio.h>
#define CLEAR()	printf("\033[2J\033[0;0H");
#else
#warning "Console clearing not supported for this operating system!"
#define CLEAR()	((void) 0)
#endif
/******************/

/********************
Delay function
** Description: Definition of delay function for all operating systems
********************/
#ifdef _WIN32
#include <windows.h>
#define SLEEP()	Sleep(3000);
#elif __linux__
#include <unistd.h>
#define SLEEP()	usleep(3000000);
#else
#warning "Delay not supported for this operating system!"
#define SLEEP()	((void) 0)
#endif
/******************/


#include <string>
#include <iostream>
#include <typeinfo>

//Two option menu with input validation
int menu(std::string *choiceArray, int numChoices);

//Get a user's input and check if it is a positive integer.
int validatePositive();

/*Function to get a user's input and check that it is >=lower and <=upper.
*It will return the integer if valid.
*Precondition: Lower < Upper
*/
int validatePositiveRange(int lower, int upper);

#endif
