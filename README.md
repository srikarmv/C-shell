# C-shell
1) Shell supports almost all commands which we can execute in original terminal.
2) Shell supports input/output redirection.
    For example :- ls < filename (output redirecton )
                   cat > filename ( input redirection)
    It also supports '>>' redirection also.
3) It also supports piping of the commands
    For example : cat filename | grep pattern | cut arguments.
4) It also supports combining of redirection and piping.
    For example :- cat < filename | grep pattern
5) It also supports backgrounding a process Example ;- emacs &
6) It also supports various commands like
        (i) "jobs" for showing all background processes.
        (ii) "killallbg" for killing all background processes.
        (iii) 'fg pid' to foreground a particular pid.
        (iv) 'kjobs pid signal' to give a certain signal to a particular pid.
7) Shell supports "quit" command to exit the shell
8) (i) ctrl + c for clear the command prompt
   (ii) ctrl + d for exiting the  present shell
9) Shell supports  all executable commands which we can run from normal terminal.
