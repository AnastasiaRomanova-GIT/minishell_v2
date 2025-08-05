
# 🧭 Minishell Merge Roadmap & Checklist

This document tracks the progress of merging and finalizing your minishell project using `miniShell_latestWorkingVersion` as the base.

---

## ✅ Phase 1: Establish Baseline Shell

- [ ] Build `minishell_merged` and confirm basic shell loop
- [ ] Run basic commands:
  - [ ] `ls`, `pwd`, `echo test`
  - [ ] `export VAR=hello` → `echo $VAR`
- [ ] Test builtins: `cd`, `env`, `unset`, `exit`
- [ ] Confirm signal handling (Ctrl+C)
- [ ] Verify correct exit codes (`$?`)

---

## 🟨 Phase 2: Merge & Test Incrementally

- [ ] Copy in `__incoming_from_test__/error_check.c` and test:
  - [ ] Unmatched quotes
  - [ ] Invalid redirection
- [ ] Compare and optionally merge:
  - [ ] `pipe_exec.c` → check redirection handling
  - [ ] `executors.c` and `exec_manager.c`
  - [ ] `token_processing/tokenise.c` vs current parser
- [ ] After each merge:
  - [ ] Rebuild and re-test previous working commands
  - [ ] Run manual test cases
  - [ ] Commit changes with message

---

## 🟥 Phase 3: Finalization

- [ ] Run 42 checker or custom test harness (`checker_minishell.py`)
- [ ] Validate all redirections:
  - [ ] `>`, `>>`, `<` + combinations with pipes
- [ ] Run `valgrind` on all test cases:
  - [ ] Check for memory leaks
  - [ ] Validate file descriptor cleanup
- [ ] Test unexpected inputs (e.g., `|`, `;;`, `>`, quotes)

---

## 🧼 Clean Up & Submission Prep

- [ ] Remove debug prints and test-only files
- [ ] Move unused test code from `__incoming_from_test__` to archive
- [ ] Final pass of header includes, consistent naming
- [ ] Document any known limitations in `README.md`

---

## 🗒️ Notes Log

Use this section to track daily merges or breakage fixes.

```md
2025-06-13: Created baseline with working signals and input loop
2025-06-14: Merged error_check.c — quote validation improved
2025-06-14: pipe_exec.c merged — broke redirection, reverted
...
```
