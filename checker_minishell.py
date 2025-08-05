import os
import subprocess

#usage: python3 checker_minishell.py
#requires commands_for_checker.txt file, which should contain all the commands 
# for tests, one command per line

def run_and_capture(command, shell_name="bash"):
    """Runs the command using the specified shell, silently captures output."""
    result = subprocess.run(
        [shell_name, "-c", command],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    return result.returncode, result.stdout.strip(), result.stderr.strip()


with open("commands_for_checker.txt", "r") as command_input:
    for command in command_input:
        command = command.strip()
        if not command or command.startswith('#'):
            continue

        print(f"\n*** Command ***\n {command}")

        bash_ret, bash_out, bash_err = run_and_capture(command, "bash")
        mini_ret, mini_out, mini_err = run_and_capture(command, "./minishell")

        if (bash_ret, bash_out, bash_err) == (mini_ret, mini_out, mini_err):
            print("✅ Outputs match")
        else:
            print("❌ Difference found!")
            print(f"  [bash] ret={bash_ret} out={bash_out!r} err={bash_err!r}")
            print(f"  [mini] ret={mini_ret} out={mini_out!r} err={mini_err!r}")

