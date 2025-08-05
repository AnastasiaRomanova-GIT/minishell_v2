

 **6 weeks with 20 hours per week**  for a **minishell project**.
---

### **Week 1: Project Setup & Basic Prompt Implementation**

**Objective:** Set up the project structure, display a basic prompt, and capture user input.

#### **Person 1:**
- Set up Git repository and project directory.
- Implement `main.c` to display a prompt (`$`).
- Implement basic loop to capture user input using `getline()`.

#### **Person 2:**
- Set up a `Makefile` to compile the project.
- Write functions to strip newline characters and clean up input.

#### **Milestone 1 (End of Week 1):**
- Display prompt (`$`).
- User input is captured, and the shell should echo the command back to the user.

---

### **Week 2: Command Parsing & Execution**

**Objective:** Implement basic command parsing and execute simple commands using `fork()` and `execvp()`.

#### **Person 1:**
- Write `parse_input()` to split user input into individual commands and arguments.
- Implement `execute_command()` to use `fork()` and `execvp()` to run commands.

#### **Person 2:**
- Handle error cases (e.g., invalid commands).
- Modify `main.c` to integrate command parsing and execution functions.

#### **Milestone 2 (End of Week 2):**
- The shell executes commands like `ls`, `pwd`, etc.
- Error handling for invalid commands (e.g., "command not found").

---

### **Week 3: Implementing Built-in Commands (cd, exit)**

**Objective:** Implement built-in commands such as `cd` and `exit`.

#### **Person 1:**
- Implement `cd` command to change directories using `chdir()`.
- Modify `execute_command()` to check for built-in commands.

#### **Person 2:**
- Implement `exit` command to terminate the shell.
- Handle multiple built-in commands detection in the main loop.

#### **Milestone 3 (End of Week 3):**
- The shell supports `cd` and `exit` built-ins.
- All other commands are executed through `fork()` and `execvp()`.

---

### **Week 4: Advanced Features – Redirection**

**Objective:** Implement input/output redirection (e.g., `command > file.txt` or `command < file.txt`).

#### **Person 1:**
- Implement output redirection (`>`) to redirect stdout to a file.
- Handle input redirection (`<`) to read from a file instead of stdin.

#### **Person 2:**
- Modify `execute_command()` to handle redirection syntax and call `open()` to manipulate files.
- Handle edge cases where redirection is used incorrectly.

#### **Milestone 4 (End of Week 4):**
- The shell supports redirection:
  - `command > file.txt` for output redirection.
  - `command < file.txt` for input redirection.
- Handle incorrect redirection usage gracefully.

---

### **Week 5: Advanced Features – Piping**

**Objective:** Implement piping (e.g., `command1 | command2`) to connect multiple commands.

#### **Person 1:**
- Implement piping functionality (use `pipe()`, `dup2()`, and `fork()`).
- Modify `execute_command()` to detect and handle pipes in commands.

#### **Person 2:**
- Integrate piping into the command execution logic.
- Test the shell with multiple chained commands (e.g., `ls | grep file | sort`).

#### **Milestone 5 (End of Week 5):**
- The shell supports piping (`command1 | command2`).
- Multiple commands can be chained together using pipes.

---

### **Week 6: Final Refinements & Testing**

**Objective:** Refine the shell, implement background processes, handle signal interruptions, and conduct extensive testing.

#### **Person 1:**
- Implement background processes using `&` (e.g., `command &` runs in the background).
- Handle `Ctrl+C` signal interruption properly (use `signal()`).

#### **Person 2:**
- Conduct extensive testing of all shell features (commands, built-ins, piping, redirection, background processes).
- Fix any bugs or edge cases that arise during testing.
  
#### **Milestone 6 (End of Week 6):**
- The shell should be fully functional with the following features:
  - Prompt displays correctly.
  - Executes basic commands, supports built-in commands (`cd`, `exit`).
  - Supports piping (`|`), redirection (`>`, `<`), and background processes (`&`).
  - Signal handling for `Ctrl+C` interruptions.

---

### **Weekly Breakdown Summary**

| **Week** | **Person 1 Tasks**                                 | **Person 2 Tasks**                                 | **Milestones**                                      |
|----------|----------------------------------------------------|----------------------------------------------------|----------------------------------------------------|
| **Week 1** | Set up project, implement prompt (`main.c`)        | Set up `Makefile`, handle newline character removal | Display prompt, capture user input                 |
| **Week 2** | Implement `parse_input()` and `execute_command()`  | Handle error cases and integrate functions         | Execute simple commands (e.g., `ls`, `pwd`)         |
| **Week 3** | Implement `cd` command                             | Implement `exit` command                           | Support `cd` and `exit` built-ins                  |
| **Week 4** | Implement redirection (output and input)           | Handle redirection errors and edge cases           | Support redirection (`>`, `<`)                      |
| **Week 5** | Implement piping (`|`)                             | Integrate piping and test with multiple commands   | Support piping (`|`)                               |
| **Week 6** | Implement background processes and signal handling | Conduct testing and fix bugs                       | Fully functional minishell with advanced features |

---

### **Additional Notes:**

- **Testing and Debugging:** Spend the last few days of Week 6 thoroughly testing your shell. Check for edge cases, such as invalid redirection, incorrect piping syntax, background process handling, and more. Don't forget to test for memory leaks and resource handling.
  
- **Time Management:** With **20 hours/week** for each person, you'll have ample time to implement and test each feature. Make sure to regularly communicate progress and review each other's code to ensure consistency.

- **Future Extensions:** If you finish ahead of schedule, consider adding features like environment variable support (e.g., `echo $HOME`), signal handling for more complex cases, or implementing custom commands.

With this timeline, **6 weeks** gives you enough time to build, refine, and fully test the minishell, ensuring a robust and complete implementation.

-------------------------------------------------------------------------------------------------------------------------------------------------


### **Week 1: Project Setup & Basics**

**Understand Requirements:** Read project guidelines & understand expected features.

**Set Up Git & Repo:** Create a repository for version control.

**Basic Shell Execution:** Implement a basic loop (while), read user input, and print it back.

**Parsing & Tokenization:** Start working on splitting user input into commands & arguments.

**Deliverable:** Basic loop handling user input.

--------

### **Week 2: Command Execution & Builtins (Part 1)**

Execute Simple Commands: Implement execve() to run external commands (e.g., ls, pwd).

**Path Resolution:** Handle command paths by searching in $PATH.

**Basic Builtins:** Implement echo and cd.


**Deliverable:** Ability to execute external commands & basic builtins (echo, cd).

-------

### **Week 3: Environment Variables & Builtins (Part 2)**

**Environment Handling:** Implement access to **$HOME**, **$PWD**, and custom environment variables.

**More Builtins:** Implement pwd, export, unset.

**Signal Handling:** Handle signals **(Ctrl+C, Ctrl+D, Ctrl+\)**.


**Deliverable:** Shell supporting more builtins & basic signal handling.

-------

### **Week 4: Redirections & Pipes**

**Redirections:** Implement input (<), output (>), and append (>>) redirections.

**Pipes (|):** Implement piping between multiple commands.

**Deliverable: Support for redirections and piping.**

-------


### **Week 5: Advanced Features & Edge Cases**

**Exit Status Handling:** Ensure correct return values for commands.

**Wildcards & Quotes:** Handle * (wildcard expansion) and quoting (", ').

**Error Handling:** Proper error messages & handling edge cases.

**Deliverable: A robust shell with wildcard expansion and refined error handling.**

---------------

### **Week 6: Testing & Optimization**

**Extensive Testing:** Test for edge cases, memory leaks (using valgrind).

**Performance Optimization:** Improve efficiency where possible.

**Final Debugging & Documentation:** Clean up code, write README & final documentation.

**Deliverable: Fully functional & tested Minishell ready for submission.**