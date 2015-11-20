# rshell
- CS100 Programming assignment
- Jimmy Tran
- Erin Mullally

##Functions
- Chained commands with or without space:
  - `$ ls && mkdir test || exit && uname -a`
  - `$ ls&&mkdir test|| exit &&uname -a`
- Throw parse errors if start or end with connectors
  - `$ &&top`
  - `$ lscpu||`
- Precedence using parenthesis
  - `$ (echo 1 || echo 2) && (echo 3 && echo 4)`
- Brackets for "test" command
  - `$ [ -d /bin ] && echo directory exists` 
- Error if there are adjacent connectors
  - `who || && whoami`
  - `who ;$$ whoami`
- Prompt
  - `jtran064@sandman$ `

##Design
###Parsing
- Parser takes input from the user and encapsulates the characters into either
command or connector objects. Both of these objects inherit from an abstract
base class, Runners
- If any errors are encountered, Parser will throw an exception that will bubble
up to main and eventually output to the user
- Runners are stored a vector of runner pointers
- All parse errors are thrown before execution. This may differ from bash which
  sometimes throw parse errors after execution.

###Execution
- An iterator iterates through the vector of pointers and calls the object's run
function
- Upon encountering a parenthesis a separate function, runParenthesis, is
called
  - runParenthesis recursively calls on itself when it encounters another
    parenthesis, allowing for nested parenthesis
- Open brackets are converted to a "test" command and will search for the closing bracket
  - If there are any connector before the closing bracket, an exception would throw

###Possible Improvements
- Instead of a vector, a tree container would be more intuitive and would simplify execution

##rshell arguments
- `TEST` prints out the entered the command. Used mostly for script runs
- `BOOLTEST` prints out parsed elements. Used for debugging

##Bugs
###rshell
- Limitations to # input length, argument character length, and argument length
- Brackets
  - Double brackets are not supported
  - Empty arguments are treated as errors

###Makefile
- Makefile is buggy. Need to clean and rebuild at every compilation

###Script test
- Script doesn't output the user in prompt
- Script tests loops infinitely on BOOLTEST mode
- Executing rshell in rshell forks a child process instead of returning to
parent

