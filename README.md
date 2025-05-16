Minishell – @42Born2Code

    As beautiful as a shell

About

Minishell is the second project of the Unix branch at 42. It is a minimum‑viable clone of a real Unix shell whose main goal is to give students a deep understanding of process creation, synchronisation, and file‑descriptor management in C.
Installation & Usage
Requirements

    GNU make ≥ 3.81

    GCC ≥ 4.2.1

(These are the versions used during development.)
Building the program


Main Project Instructions

Mandatory

Written only in C and built with a Makefile (make && ./minishell).

Must comply with the Norminette coding style.

No memory leaks (Valgrind must remain silent).

Handle program interruption (e.g. Ctrl+D).

Implement the following built‑ins: echo, pwd, cd, env, export, unset, exit.

Provide comprehensive error handling without relying on errno.

Allowed standard‑library calls (the usual 42 whitelist):

malloc, free

access

open, close, read, write

opendir, readdir, closedir

getcwd, chdir

stat, lstat, fstat

fork, execve

wait, waitpid, wait3, wait4

signal, kill

exit

The resulting binary must be named minishell.

You may link against your personal libft.

Bonuses

Signal management (Ctrl+C, SIGINT, etc.)

Robust PATH permission/error handling

Multiple commands via semicolons ;

Extra goodies: readline history, autocompletion, wildcard *, parentheses (), logical operators && / ||.

Architecture (High level)

Lexer → breaks user input into tokens (words, redirections, pipes…).

Parser → validates syntax & builds an AST.

Expander → resolves env vars, removes quotes, manages here‑docs.

Executor → spawns processes, wires pipes/redirections, runs built‑ins or external binaries, returns the exit code.

Notes

The entire codebase is fully commented for easier navigation.

Tabs are set to width 4 — any “weird” spacing is intentional.

Remember the strict function whitelist before suggesting alternative APIs. 😉

Sponsors

Enjoy! 🎉
