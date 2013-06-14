////////////////////////////////////////////////////////////////////////////
//                                             			 	  //
//                                 RPN                       	  	  //
//              A simple Reverse Polish Notation calulator        	  //
//                                           			  	  //
//         Written by Jonathan Cordeiro (http://joncordeiro.com)          //
//                                            			  	  //
//         June 11th, 2013                                  		  //
//                                              		 	  //
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"
#include "calculator.h"

#define BUFF_SIZE 25

int main(int argc, const char * argv[]) {
    
    char in[BUFF_SIZE];
    printf("*********** Reverse Polish Notation Calculator ***********\n");
    printf("You may enter \"quit\" to terminate this program at any time\n");
    printf("Default calculator mode is: %s\n", RADIANS);
    printf("Note: Any invalid input will be treated as the number 0\n");
    printf("The following commands are available: \n\n");
    printCommands();
    
    // Loops indefinitely
    // The user can exit the program by entering the "QUIT" command
    do {
        // Prompt user to enter their operator or operand
        printf("Current Mode: %s \nEnter and operator or an operand: ", mode);
        fgets(in, BUFF_SIZE, stdin);
        in[strlen(in)-1]='\0'; // Add null character to end of string
        
        if (!isCommand(in)) {
            
            // if input is not a command or operation, it must be a number
            // push this number onto the stack
            if (!isOperator(in)) {
                push(atof(in));
            } else {
                
                // Perform the mathematical operation, if the stack is not empty
                // Push the result onto the stack
                if (!stakempt()) {
                    
                    float result = 0;
                    
                    // Checks if the operation needs 1 or 2 operands
                    // If only one operand is needed, then '0' is passed in for the other
                    // if there is only 1 operand on the stack
                    // instead of popping a non-existent operand off of the stack
                    if (needsOneOperand(in) && stakptr <= 1) {
                        result = performOperation(pop(), 0, in);
                        push(result);
                    } else {
                        
                        // Only perform the operation if there are at least
                        // 2 operands on the stack
                        if (stakptr > 1) {
                            result = performOperation(pop(), pop(), in);
                            push(result);
                        } else {
                            printf("There are not enough operands in the stack for that operation\n\n");   }
                    }
                    
                } else {
                    printf("There is nothing on the stack. Please enter some operands\n\n");
                }
            }
            
        } else {
            performCommand(in);
        }
        
    } while (1);
    
    return 0;
}

// Prints out a list of commands available to the user
void printCommands() {
    printf("You can type \"commands\" to see this list at any time\n");
    printf("Commands are not case-sensitive\n\n");
    printf("Clear:\t\t\t C \t    Re-enter last number: LAST \n");
    printf("Change mode: \t M \t    Pi: \t\t\t\t  PI \n");
    printf("Addition:\t\t + \t    Subtraction:\t\t  - \n");
    printf("Multiplication:\t * \t    Division:\t\t\t  / \n");
    printf("Sine: \t\t\t SIN    Cosine: \t\t\t  COS \n");
    printf("Tangent: \t\t TAN    Arcsine: \t\t\t  ASIN \n");
    printf("Arcosine: \t\t ACOS   Arctangent: \t\t  ATAN \n");
    printf("Exponent (a^b):  ^ \t    Exponential (e^x): \t  E \n");
    printf("Square Root: \t SQ     Nautral Logarithm: \t  LOG10 \n");
    printf("Print stack: \t STACK  Quit program: \t\t  QUIT \n\n");
    
}


