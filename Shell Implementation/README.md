# Shell Implementation

## Description

This project is aobut implementing shell. A shell is a program that allows a user to send commands to the operating system (OS)and allows the OS to respond to the user by printing output to the screen. The shell allows a simple character-oriented interface in which the user types a string of characters(terminated by pressing <ENTER>) and the OS responds by printing lines of characters back to the screen. It provides the typical shell interation. It prints "prompt >" to indicate that it is waiting for instructions, and the shell accepts a command from a user and shows the results of commands to the screen. There are two assumption under this project: 1. The user command is terminated with a <ENTER> character, 2. The form of command is [arg1] [arg2] [arg3]..., and each argument is seperated by space or tab chracters. Since it needs to be work as general shell, the shell continues to print prompts and accept commands until the shell receives a "quit" command. If user type "quit", it will terminates the shell.

The shell will support two types of commands. The one is **local executables**. These commands are the names of any compiled executable in the local directory. The other one is **built-in commands** which are performed directly by the shell.

## Local Executables in the Foreground

As mentioned above, the shell supports the execution of local executables as **foreground jobs**. A foreground job is one that blocks the shell process, causing it to wait until the foreground job is complete. Since ti blocks the shell process, the shell cannot accpet commands while a foreground job is executing. Due the the characteristic of forground job, only one job can run in the foreground state at a time. A forground job is started when the user simply enters the name of the executable program at the prompt.

    ```cpp
    prompt > hello
    Hello World!
    prompt >

If a foreground job is running and the user types **ctrl + C** into the shell, then the foreground job should be terminated. It is done by SIGINT handler in the shell.

    ```cpp
    prompt > counter
    counter: 0
    counter: 1
    counter: 2
    counter: 3
    counter: 4
    ^Cprompt >

## Local Executables as background jobs

Also as mentioned above, the shell supports the execution of local executables as **backbround jobs**. A background job is one that DOES NOT blocks the shell process. When user start a shell and enter an ampersand (&) symbol at the end of the command line, the shell starts excutable local file as background job. Since it does not block the shell process, the shell will print a new prompt and the user can enter new commands immediately after a background pogram is started.

    ```cpp
    prompt > hello &
    prompt >Hello World!

    or

    prompt > hello &
    Hello World!prompt>

The ampersand (&) symbol is a unique token, seperated from the text before it by one or more space characters. It is guaranteed that all child processes forked by the shell process is properly reaped after the child process is terminated.

## Built-in Commands / Job Control

The shell supports six built-in commands: **jobs**, **bg**, **fg**, **cd**, **pwd**, and **quit**. It keep printing the prompt "prompt >" and accept a command from the user.


 - **cd**: It changes the current working directory of the shell. If the given directory name is "**..**" then the working directory should go up on level of the directory tree.

 - **pwd**: It prints the name of the working directory.

 - **quit**: It ends the shell proecess.

 - **Ctrl + C**: If a foreground job is running and the user types ctrl-C into the shell, then the foreground job should be terminated. 

 - **Ctrl + Z**: If the user enters ctrl-Z into the shell while a foreground job is executing, the foreground job moves to the Stopped state.

 - **jobs**: A shell accpet the command "jobs". If user types "jobs" as commands, the shell shows a list of the status of jobs. Status can be "Running" (If it is in the Background/Running state) and "Stopped".

    ```cpp
    FROM : [<job_id>] (<pid>) <status> <command_line>
    EXAMPLE : 
    prompt > jobs
    [1] (30522) Running hello &
    [2] (30527) Stopped sleep

 - **bg**: The command is **bg <job_id|pid>**. If a user enters bg <job_id|pid> into the shell and the job indicated by <job_id|pid> is currently in the Stopped state, then it is moved to the Background/Running state. In order to move a process from              the Stopped state to the Background/Running state, the process must be restarted by sending it a SIGCONT signal using the kill() system call.
   
 - **fg**: The command is **fg <job_id|pid>**. If a user enters fg <job_id|pid> into the shell and the job indicated by <job_id|pid> is currently in the Stopped state or the Background/Running state, then it is moved to the Foreground/Running state.              In order to move a process from the Stopped state to the Foreground/Running state, the process must be restarted by sending it a SIGCONT signal using the kill() system call.

 - **kill**: The command is **kill <job_id|pid>**. If a user enters kill <job_id|pid> into the shell, then it terminates a job by sending it a SIGINT signal using the kill() system call.

## I/O Redirection

Most command line programs that display their results do so by sending their results to standard output (display). However, before a command is executed, its input and output may be redirected using a special notation interpreted by the shell. To redirect standard output to a file, the ">" character is used by following under rules.

**1.** To redirect standard output to a file, the ">" character is used like this:

    ```cpp
    prompt > jobs > file_list.txt

In this example, the ls command is executed and the results are written in a file named file_list.txt. Since the output of ls was redirected to the file, no results appear on the display. Each time the command above is repeated, file_list.txt is overwritten from the beginning with the output of the command ls

**2.** To redirectstandard input from a file instead of the keyboard, the "<" character is used like this:

    ```cpp
    prompt > sort < file_list.txt

In the example above, we used the sort command to process the contents of file_list.txt and the output is displayed as a standard output.

**3.** The results are output on the display since the standard output was not redirected. We could redirect standard output to another file like this:

    ```cpp
    prompt > add < number.txt > added_number.txt
   
**4.** The shell should also support the command to append to a file. It is virtually the same as standard output redirection except for the file to which the output was redirected to isn’t overwritten, instead, the incoming contents are simply appended to the end of the file. To redirect standard output and append to a file, use the “>>” string. For example:

    ```cpp
    prompt > jobs >> file_list.txt

**NOTE:**  Use both execvp() and execv() to allow either case. 
    **execvp()** : Linux commands{ls, cat, sort, ./hellp, ./slp}.
    **execv()** : Linux commands{/bin/ls,/bin/cat,/bin/sort, hello,slp}.
