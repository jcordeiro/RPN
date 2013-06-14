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

#define MAXLINES 50
float line[MAXLINES];
int stakptr = 0;

void push(float);
float pop(void);
int stakempt(void);
void printStack();
void clearStack();


// Pushes an item onto the stack
void push(float in) {
    if(stakptr>=MAXLINES){
        printf("Stack Overflow - Program terminated");
        exit(1);
    }
    printf("Value pushed: %g\n\n", in);
    line[stakptr] = in;
    stakptr++;
}

// Pops an item off the stack
float pop(void) {
    stakptr--;
    if(stakptr<0){
        printf("Nothing on Stack - Program terminated");
        exit(1);
    }
    return line[stakptr];
}

// Checks if the stack is empty
int stakempt(void) {
    return !stakptr;
}

// Prints out the values currently in the stack
void printStack() {
    
    if (stakptr == 0) {
        printf("Stack is empty");
    } else {
        for (int i = 0; i < stakptr; i++) {
            printf("%g ", line[i]);
        }
    }
    
    printf("\n\n");
}

// Clears the stack, pops every item off
void clearStack() {
    
    while (!stakempt()) {
        pop();
    }
    
    printf("Stack cleared\n\n");
}
