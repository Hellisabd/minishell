Minishell

    42 curriculum project: re‑implementing a minimal Unix shell in C.

TL;DR

Minishell pushes students to master:

    Process management (fork, execve, waitpid)

    File descriptors & redirections (dup2, <, >, >>, <<)

    Pipes to chain commands

    Environment handling ($PATH, variables, exit status)

… all while complying with the Norminette style guide and ensuring flawless memory management.
Context & Learning Goals

The assignment is to “re‑create our own little Bash”:
read a command line, lex it, parse it, then execute either an external binary or a built‑in (echo, cd, etc.).

Along the way you will learn:

    Process creation: fork, execve, waitpid

    FD duplication & pipeline creation: dup2, pipe

    The internal pipeline LEX ➜ PARSE ➜ EXPAND ➜ EXEC recommended by 42 Docs

Main Features
Feature	Implemented Details
Command execution	Relative paths, absolute paths, or resolution via $PATH.
Redirections	<, >, >>, heredoc <<.
Pipes	Chain `cmd1	cmd2	cmd3` with N‑1 pipes for N commands.
Expansions	Environment variables ($HOME) and exit code ($?).
Quoting	Correct handling of ' and " (except across newlines).
Signals	Ctrl‑C (SIGINT), Ctrl-\ (SIGQUIT), Ctrl‑D (EOF) handled gracefully.
Built‑ins	echo, pwd, cd, env, export, unset, exit.

    Optional bonuses: readline history, autocompletion, wildcard *, parentheses (), && / || operators.

Internal Architecture

    Lexer: splits user input into tokens (words, redirections, pipes…).

    Parser: checks grammar, builds an AST, detects syntax errors.

    Expander: resolves variables, removes quotes, handles here‑docs.

    Executor: spawns processes, sets up pipes/redirections, launches binaries & built‑ins, returns the exit status.

Technical Requirements (42)

    Language: ANSI C (C99), built with a Makefile

    Norminette: zero error / warning

    Allowed libraries: readline, standard libc functions

    Memory leaks: forbidden — Valgrind must stay silent

    Indicative workload: 4–6 weeks for a pair of students

Build & Run
# Clone and build
git clone https://github.com/<user>/minishell.git
cd minishell && make

# Launch the shell
./minishell

Examples:
> ls -la | grep ".c" > sources.txt
> export PATH=$PATH:/custom/bin
> echo "Last exit code = $?"
Experience & Soft Skills

    Pair programming: clear task split (e.g. parsing vs signals)

    Project management: modular design, git workflow, code reviews

    Advanced debugging: strace, valgrind, gdb to tame fork bombs and memory leaks

Screenshot

    (Add a GIF or image here to showcase the prompt — e.g. assets/minishell_demo.gif)

License

This repository includes the official 42 subject; the implementation is 100 % original.
Feel free to open an issue or a pull request!


