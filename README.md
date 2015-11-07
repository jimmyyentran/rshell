# rshell
CS100 Programming assignment

##Functions
- Chained commands with or without space:
  - `$ ls && mkdir test || exit && uname -a`
  - `$ ls&&mkdir test|| exit &&uname -a`
- Throw parse errors if start or end with connectors
  - `$ &&top`
  - `$ lscpu||`
- Error if there are adjacent connectors
  - `who || && whoami`
  - `who ;$$ whoami`
- Prompt
  - `jtran064@sandman$ `

##rshell arguments
- `TEST` prints out the entered the command. Used mostly for script runs
- `BOOLTEST` prints out parsed elements. Used for debugging

##Bugs
###rshell
- `$ git status# comment here` is parsed to `git status` and `# comment here`
- `$ lscpu;;` still runs the command instead of exiting
- Lots of memory leaks
- Limitations to # input length, argument character length, and argument lenght

###Makefile
- Makefile is buggy. Need to clean and rebuild at every compilation

###Script test
- Script doesn't output the user in prompt
- Script tests loops infinitely on BOOLTEST mode
- Executing rshell in rshell forks a child process instead of returning to
  parent

