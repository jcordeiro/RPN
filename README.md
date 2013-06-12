Reverse Polish Notation (RPN) Calculator
===

This is a simple RPN calculator implement using C
* There are 20 valid commands, including 6 trigonometric functions
* Commands are not case-sensitive
* Both radians and degrees modes are supported
* Any invalid input (i.e letters) will be treated as the number 0

```
*********** Reverse Polish Notation Calculator ***********
You may enter "quit" to terminate this program at any time
Default calculator mode is: radians
Note: Any invalid input will be treated as the number 0
The following commands are available: 

You can type "commands" to see this list at any time
Commands are not case-sensitive

Clear:  		 C 	    Re-enter last number: LAST 
Change mode: 	 M 	    Pi: 				  PI 
Addition:		 + 	    Subtraction:		  - 
Multiplication:	 * 	    Division:			  / 
Sine: 			 SIN    Cosine: 			  COS 
Tangent: 		 TAN    Arcsine: 			  ASIN 
Arcosine: 		 ACOS   Arctangent: 		  ATAN 
Exponent (a^b):  ^ 	    Exponential (e^x): 	  E 
Square Root: 	 SQ     Nautral Logarithm: 	  LOG10 
Print stack: 	 STACK  Quit program: 		  QUIT
```

Operands are popped onto the stack as you enter them

When an operator is entered, it is performed. The result of the operator is pushed onto the stack

```
Current Mode: radians 
Enter and operator or an operand: 5
Value pushed: 5

Current Mode: radians 
Enter and operator or an operand: 4
Value pushed: 4

Current Mode: radians 
Enter and operator or an operand: 9
Value pushed: 9

Current Mode: radians 
Enter and operator or an operand: 5
Value pushed: 5

Current Mode: radians 
Enter and operator or an operand: +
Value pushed: 14
```


The contents of the stack can be printed

```
Current Mode: radians 
Enter and operator or an operand: stack
5 4 18 

```


The stack can be cleared

```
Current Mode: radians 
Enter and operator or an operand: c
Stack cleared

Current Mode: radians 
Enter and operator or an operand: stack
Stack is empty
```

Both radians and degrees modes are supported

Radians mode

```
Current Mode: radians 
Enter and operator or an operand: 23
Value pushed: 23

Current Mode: radians 
Enter and operator or an operand: sin
Value pushed: -0.84622
```
Change modes with the "m" command

```
Current Mode: radians 
Enter and operator or an operand: m
Mode is now: degrees
```

Degrees mode

```
Current Mode: degrees 
Enter and operator or an operand: 23
Value pushed: 23

Current Mode: degrees 
Enter and operator or an operand: sin
Value pushed: 0.390731
```

You can exit the program with the "quit" commands

```
Current Mode: degrees 
Enter and operator or an operand: quit

The program is exiting. Thank you!
```

<br>

If you have any comments, or suggestions, please feel free to [email me](mailto:github@joncordeiro.com) or contact me on [Twitter](http://twitter.com/JonCordeiro)
