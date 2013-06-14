////////////////////////////////////////////////////////////////////////////
//                                             			 	              //
//                                 RPN                       	  	      //
//              A simple Reverse Polish Notation calulator        	      //
//                                           			  	              //
//         Written by Jonathan Cordeiro (http://joncordeiro.com)          //
//                                                                        //
//         June 11th, 2013                                  		      //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RADIANS "radians"
#define DEGREES "degrees"
#define CONVERT_TO_RADIANS(r) r * (180/ M_PI);
#define CONVERT_TO_DEGREES(d) d * (M_PI / 180.0);
char * mode = RADIANS; // Radians is the default calculator mode

void printCommands();
int isEqual(char *, char *);
int isTrigFunction(char *);
int isInverseTrigFunction(char *);
int isCommand(char *);
int isOperator(char *);
int needsOneOperand(char *);
void performCommand(char *);
float performOperation(float, float, char *);
float performTrigFunction(float, char *);
char *  changeMode(char *);

// Checks if 2 strings are equal, ignores case-sensitivity
// Returns 1 if strings are equal, 0 if unequal
int isEqual(char * str1, char * str2) {
    
    if ( !strcasecmp(str1, str2)) {
        return 1;
    } else {
        return 0;
    }
    
}

// Checks if the operator entered is one of the 6 trig functions
// Returns 1 if it's a trig function, 0 if it's not a trig function
int isTrigFunction(char *op) {
    
    if ( isEqual(op, "sin") || isEqual(op, "cos") || isEqual(op, "tan") ||
        isEqual(op, "asin") || isEqual(op, "acos") || isEqual(op, "atan") ) {
        return 1;
    } else {
        return 0;
    }
    
}

// Checks if trig function is an inverse function or not
// Return 1 if it's a trig function, 0 if it's not
int isInverseTrigFunction(char * op) {
    
    if (isEqual(op, "asin") || isEqual(op, "acos") || isEqual(op, "atan") ) {
        return 1;
    } else {
        return 0;
    }
    
}

// Checks if user input is a valid calculator command
// Returns 1 if input is valid command, 0 if invalid
int isCommand(char *op) {
    
    if ( isEqual(op, "c") || isEqual(op, "last") || isEqual(op, "m") ||
        isEqual(op, "stack") || isEqual(op, "commands") || isEqual(op, "pi") ||
        isEqual(op, "quit")) {
        return 1;
    } else {
        return 0;
    }
    
}

// Checks if user input is a mathematical operator
// returns 1 if 'c' is an operator, 0 if 'c' is not
int isOperator(char *op) {
    
    if ( isTrigFunction(op) ) {
        return 1;
    }
    else if ( isEqual(op, "+") ||  isEqual(op, "-") || isEqual(op, "*") ||
             isEqual(op, "/") || isEqual(op, "^") || isEqual(op, "e") ||
             isEqual(op, "sq") || isEqual(op, "log10")) {
        return 1;
    }
    else {
        return 0;
    }
}

// Checks if operation only needs one operand to be performed
// Returns 1 if operation only needs one operand, 0 if operation needs 2
int needsOneOperand(char * op) {
    
    if ( isEqual(op, "e") || isEqual(op, "sq") || isEqual(op, "log10") ||
        isTrigFunction(op)) {
        return 1;
    } else {
        return 0;
    }
    
}

// Performs the appropriate calculator command
void performCommand(char * c) {
    
    if ( isEqual(c, "c")) {
        clearStack();
    } else if ( isEqual(c, "last")) {
        push(line[stakptr-1]);
    } else if ( isEqual(c, "m")) {
        mode = changeMode(mode);
    } else if ( isEqual(c, "stack")) {
        printStack();
    }
    else if ( isEqual(c, "pi")) {
        push( M_PI );
    } else if ( isEqual(c, "commands")) {
        printCommands();
    } else if ( isEqual(c, "quit")) {
        printf("\nThe program is exiting. Thank you!\n");
        exit(1);
    }
}

// Performs the appropriate operation on 2 operands,
// or calls the performTrigFunction() function
// If mathematical function only requires 1 operand,
// the other is pushed back onto the stack
float performOperation (float operand1, float operand2, char * operation) {
    
    float result = 0;
    
    if (isTrigFunction(operation)) {
        push(operand2);
        result = performTrigFunction(operand1, operation);
        return result;
    }
    
	if ( isEqual(operation, "+") ) {
		result = operand2 + operand1;
	} else if ( isEqual(operation, "-") ) {
		result = operand2 - operand1;
	} else if ( isEqual(operation, "/") ) {
        
        // If the user tries to divide by zero
        // A warning is printed and the operands
        // are pushed back onto the stack
        if (operand1 != 0) {
            result = operand2  / operand1;
        } else {
            printf("Cannot divide by 0!\n\n");
            push(operand2);
        }
        
	} else if ( isEqual(operation, "*") ) {
		result = operand2 * operand1;
	} else if ( isEqual(operation, "^") ) {
        result = powf(operand2, operand1);
    } else if ( isEqual(operation, "e") ) {
        result = expf(operand1);
        push(operand2);
    } else if ( isEqual(operation, "sq") ) {
        
        
        // Computing the square root of a negative number
        // results in an error
        // the operand is returned and pushed back onto the stack
        if (operand1 >= 0) {
            result = sqrtf(operand1);
        } else {
            printf("You cannot take the square root of a negative number\n\n");
            result = operand1;
        }
        
        
        push(operand2);
        
    } else if ( isEqual(operation, "log10") ) {
        result = log10f(operand1);
        push(operand2);
    }
    
    return result;
}

// Performs appropriate trig function
float performTrigFunction(float operand, char *op) {
    
    float result = 0;
    
    // If the calculator is in degrees mode and the operation is
    // not an inverse function, the operand must be converted
    // before the operation
    if (!isInverseTrigFunction(op) && mode == DEGREES) {
        operand = CONVERT_TO_DEGREES(operand);
    }
    
    // If the operand isn't valid for ASIN or ACOS
    // The user is warned and the operand is returned to be pushed back onto the stack
    else if (isInverseTrigFunction(op) && !isEqual(op, "atan") && (operand < -1 || operand > 1) ) {
        printf("For ASIN and ACOS the operand must be in between -1 and 1\n\n");
        return operand;
    }
    
    // Inverse trig functions do not need
    // their input operand to be converted into degrees
    if (isEqual(op, "sin")) {
        result = sinf(operand);
    } else if (isEqual(op, "cos")) {
        result = cosf(operand);
    } else if (isEqual(op, "tan")) {
        result = tanf(operand);
        
        // Calling tanf() on values that should be undefined
        // results in the answer -22877332. We check against
        // this value to see whether or not tan is defined
        // If tan is undefined, we return the operand
        // so it can be pushed back onto the stack
        if (result == -22877332) {
            printf("TAN is not defined for that value\n\n");
            return operand;
        }
        
    } else if (isEqual(op, "asin")) {
        result = asinf(operand);
    } else if (isEqual(op, "acos")) {
        result = acosf(operand);
    } else if (isEqual(op, "atan")) {
        result = atanf(operand);
    }
    
    // If the calculator is in degrees mode and the operation is
    // an inverse function, the answer must be converted after the operation
    if (isInverseTrigFunction(op) && mode == DEGREES) {
        result = CONVERT_TO_RADIANS(result);
    }
    
    return result;
}

// Changes the calculator's mode from radians to degrees and vice-versa
char * changeMode(char * m) {
    
    char * mode;
    
    if ( isEqual(m, RADIANS)) {
        mode = DEGREES;
    } else {
        mode = RADIANS;
    }
    printf("Mode is now: %s\n\n", mode);
    
    return mode;
}
