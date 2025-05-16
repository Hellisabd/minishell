# Minishell – @42Born2Code

> *As beautiful as a shell*

---

## About

**Minishell** is the second project of the Unix branch at 42. It is a *minimum-viable* clone of a real Unix shell whose main goal is to give students a deep understanding of **process creation**, **synchronisation**, and **file-descriptor management** in C.

---

## Installation & Usage

### Requirements

- **GNU make ≥ 3.81**
- **GCC ≥ 4.2.1**

*(These are the versions used during development.)*

### Building the program

```bash
# Clone the repository
git clone https://github.com/<user>/minishell.git

# Build from the project root
cd minishell
make
```

### Running the program

```bash
./minishell
```

---

## Main Project Instructions

### Mandatory

- Written **only in C** and built with a dedicated **Makefile** (`make && ./minishell`).
- Must comply with the **Norminette** coding style.
- **No memory leaks** (Valgrind must stay silent).
- Gracefully handle program interruption (e.g. `Ctrl+D`).
- Implement the following **built‑ins**:
  - `echo`
  - `pwd`
  - `cd`
  - `env`
  - `export`
  - `unset`
  - `exit`
- Provide comprehensive **error handling** without relying on global `errno` messages.
- Allowed standard‑library calls *(42 whitelist)*:
  - `malloc`, `free`
  - `access`
  - `open`, `close`, `read`, `write`
  - `opendir`, `readdir`, `closedir`
  - `getcwd`, `chdir`
  - `stat`, `lstat`, `fstat`
  - `fork`, `execve`
  - `wait`, `waitpid`, `wait3`, `wait4`
  - `signal`, `kill`
  - `exit`
- The resulting binary **must be named** `minishell`.
- Linking with your personal **libft** is allowed.

### Bonus

- Advanced **signal management** (`Ctrl+C`, `SIGINT`, etc.).
- Robust handling of **PATH** permissions and related errors.
- Support for **multiple commands** via semicolons `;`.
- Extras: `readline` history, autocompletion, wildcard `*`, parentheses `()`, logical operators `&&` / `||`.

---

## Architecture (High‑level)

1. **Lexer** – breaks user input into tokens (words, redirections, pipes…).
2. **Parser** – validates syntax & builds an AST.
3. **Expander** – resolves environment variables, removes quotes, handles *here-docs*.
4. **Executor** – spawns processes, sets up pipes/redirections, launches built‑ins or external binaries, returns the **exit status**.

---

## Notes

- The codebase is **fully commented** for easier navigation.  
- Tabs are set to width 4 — any “weird” spacing is intentional.  
- Before suggesting alternative APIs, remember the strict 42 whitelist. 😉

---

## Sponsors

<div align="center">
  <sup>*Sponsor*</sup>
</div>

---

Enjoy! 🎉
