# Lecture Sheet: Managing the Machine

## Reviewing and Debugging AI Code

**Source deck:** *Applied AI_ Business to Build Course Curriculum.pdf*  
**Deck topic:** *Managing the Machine: Reviewing and Debugging AI Code*  
**Deck length:** 13 slides  
**Prepared:** 2026-10-05  
**Audience:** Students and solo developers using AI coding tools, especially in an existing codebase  
**Central idea:** Let an AI coding tool draft code at speed, while you define the task, constrain the change, verify its facts, reproduce failures, test the result, and keep control of the repository.

> **How to use this sheet:** It follows all 13 slides and expands them into an engineering workflow, a Codex-in-VS-Code practice, reusable prompt templates, a worked bug example, review checklists, exercises, and primary-source links. The PDF is image-based; its contents were captured using OCR and visual review. Statements such as “1,000 lines a minute” and “one or two files is a good patch” are treated as slide rhetoric or rough warning signs, not measured rules.

## 1. Learning objectives

By the end of this lesson, you should be able to:

1. Explain what an AI coding agent can speed up and what responsibility still belongs to the developer.
2. Review a proposed change in a useful order: scope, correctness, dependencies and APIs, simplicity, tests, and risk.
3. Distinguish a real warning sign from a simplistic rule such as “five changed files means panic.”
4. Reproduce a bug and describe its trigger, expected behavior, actual behavior, and evidence.
5. Give a coding agent bounded context and a verifiable acceptance condition.
6. Use logs and error messages safely, including redacting secrets and treating untrusted text as data.
7. Use Git checkpoints and recovery commands without erasing unrelated work.
8. Decide when a failure calls for a code fix, a better test, more context, a dependency check, or a revised specification.
9. Apply the workflow in a VS Code project using Codex or another coding agent.
10. Explain why an AI-generated patch is not ready to merge simply because it looks plausible or its author says tests passed.

## 2. The whole lesson in one workflow

~~~mermaid
flowchart TD
    A["Set task and safe baseline"] --> B["Reproduce the failure"]
    B --> C["Ask for a bounded diagnosis"]
    C --> D["Review scope and implementation diff"]
    D --> E["Verify APIs, dependencies, and behavior"]
    E --> F["Run tests and keep or recover"]
~~~

The developer’s work is not just “audit what the AI wrote.” It includes setting the requirement, choosing how much access the agent needs, recognizing whether the task is understood, evaluating the change, and deciding whether the code is safe to retain.

### A compact operating principle

| The agent can help with | The developer must own |
|---|---|
| Locating relevant code and explaining a flow | Deciding what problem should be solved |
| Drafting a patch or tests | Defining correct behavior and boundaries |
| Suggesting a root cause | Reproducing the issue and checking the evidence |
| Looking up patterns in the repository | Confirming external APIs, package names, versions, and security implications |
| Running tests when permitted | Confirming which tests matter and reading their actual results |
| Summarizing a diff | Reviewing what changed and accepting responsibility for it |

The “engineering intern” metaphor in the deck communicates the need for supervision. Use it as a metaphor only: a model does not have human intentions, judgment, or accountability. Treat it as a tool that can be useful and can also produce plausible errors. NIST describes confabulation as a known generative-AI risk in its [Generative AI Profile](https://www.nist.gov/publications/artificial-intelligence-risk-management-framework-generative-artificial-intelligence); OWASP documents risks such as nonexistent package suggestions in its [Secure Coding with AI guidance](https://cheatsheetseries.owasp.org/cheatsheets/Secure_Coding_with_AI_Cheat_Sheet.html). The practical response is evidence-based review, not blind trust or blanket distrust.

## 3. The deck’s three-step audit, expanded

The slides introduce three checks: **Check File Scope**, **Verify Facts & APIs**, and **Enforce Simplicity**. Keep those checks, then add behavior, testing, and security before accepting the result.

### Step 1 — Check the change boundary

Before reading every code line, find out what the agent changed and compare it with the task.

Ask:

- Which paths changed, were added, deleted, renamed, or generated?
- Did the change touch an area the task did not authorize?
- Did a manifest, lockfile, build script, CI file, environment file, database migration, or agent instruction file change?
- Does the change cross a security or data boundary, such as authentication, authorization, payments, file access, or network calls?
- Did the agent explain why each extra file is necessary?

A new file outside the agreed scope is a **pause and investigate** signal. First inspect the file list and a short diff summary; do not merge a patch you do not understand. Then ask the agent to explain the extra change or revise the patch. If a cross-file change is justified, explicitly expand the task boundary and review the connected behavior.

**Do not use a fixed file count as a pass/fail rule.** A legitimate API migration or shared type change can touch dozens of files. A dangerous change can be one line. File count tells you how much review may be needed; it does not determine whether the patch is correct.

Useful Git inspection commands:

~~~bash
git status --short
git diff --name-only
git diff --stat
git diff
git diff --check
~~~

These show local state, paths, approximate patch size, actual edits, and basic whitespace errors. They do not establish functional correctness.

### Step 2 — Verify facts, APIs, and dependencies

An AI-generated name in an import statement is a claim that needs checking.

For every new package, integration, command, API, or configuration option:

1. Confirm that the package or endpoint exists in the appropriate official registry or vendor documentation.
2. Check that the name is exact; look for similarly named packages that could be typosquats.
3. Verify the version and API signature against the version the project actually uses.
4. Check release notes or migration guides if the agent uses a newer API.
5. Inspect the dependency manifest and lockfile to understand what was added or changed.
6. Check maintenance, license, security advisories, and whether the dependency is truly needed.
7. Run the project’s normal dependency audit where available.

The slide says that if documentation cannot be found, the AI hallucinated the API. Treat that as a warning, not a proof: the API may be private, internal, newly released, renamed, or documented under another product/version. Search the vendor’s official documentation, the installed package source, and the project’s existing wrappers. If you still cannot verify it, do not merge it based on the agent’s confidence.

OWASP’s [secure-coding guidance for AI](https://cheatsheetseries.owasp.org/cheatsheets/Secure_Coding_with_AI_Cheat_Sheet.html) recommends verifying AI-suggested packages and auditing their versions before installation. Never run an install command just because a model suggested a package.

### Step 3 — Enforce understandable simplicity

The deck warns against over-engineering and asks for the thinnest working path. A useful standard is:

> The patch should solve the stated problem with the smallest understandable change that preserves required behavior and safety.

“Smallest” does not mean fewest lines at any cost. A one-line workaround that breaks accessibility, security, or error handling is not simple engineering. A multi-file change may be the simplest way to update a shared interface consistently.

Ask the agent to explain:

- What caused the failure?
- Which behavior changes?
- Why is each changed part necessary?
- Which edge cases are handled, and which are out of scope?
- Why is a new abstraction, dependency, or configuration option needed?
- What would break if this code were removed?

If the explanation is vague or conflicts with the code, investigate before accepting the patch.

### Add Step 4 — Verify behavior with tests

The three-slide audit is a useful screen, but it is incomplete without behavior checks.

- Reproduce the bug before changing the code.
- Add or identify a regression test for the trigger.
- Test the expected behavior, nearby valid cases, and the relevant failure case.
- Run the focused test first, then the project’s broader required checks.
- Check whether tests were deleted, weakened, skipped, or changed to assert less.
- Read the test output. A model’s statement that tests passed is not evidence that the command ran successfully.

A test passing on one path does not prove that all requirements are met. NIST’s [Secure Software Development Framework](https://csrc.nist.gov/pubs/sp/800/218/final) treats testing and prevention of recurring defects as part of the development lifecycle, not as a final cosmetic step.

### Add Step 5 — Review security and operational effects

Check any patch that handles credentials, user data, file paths, external requests, database writes, permissions, or deployment. Confirm that it does not expose secrets, broaden access, skip validation, disable tests, or weaken a security check to make a failure disappear.

If an AI agent reads issue text, error logs, README files, web pages, or repository instructions, treat that material as untrusted input. A malicious instruction can be embedded in content the agent is asked to inspect. Give the agent only the context and tools needed for the task, and examine its resulting changes after it reads external material.

## 4. Good-patch signals and panic-patch signals

The deck contrasts a good patch with a panic patch. Use the table as a set of review prompts, not an automatic scoring formula.

| Deck’s signal | What it may indicate | Better review question |
|---|---|---|
| Touches one or two files | The patch may be narrow | Does it change every required layer, and no unrelated layer? |
| Deletes more code than it adds | The patch may remove redundant logic | Is the deleted behavior truly unnecessary, and are callers/tests still correct? |
| Explains why old logic failed | It may have a causal hypothesis | Does the explanation match the reproducible failure and code path? |
| Uses existing tools and architecture | It may fit project conventions | Is that pattern appropriate for this requirement and still maintained? |
| Touches five or more files | Could be a broad change | Are the files connected to the requested behavior? Is the migration complete and tested? |
| Adds a new library | Could add complexity or supply-chain risk | Is it real, maintained, secure, version-compatible, and worth adding? |
| Adds complex branches | Could be a symptom of unclear requirements or overdesign | Which actual supported cases require each branch? |
| Rewrites an entire function | Could be needed for a real redesign | Is the rewrite necessary, behavior-preserving where required, and covered by tests? |
| Apologizes or sounds confident | Mostly a language-style signal | Ignore tone; inspect evidence, code, and test results |

Several slide rules are too absolute if read literally:

- A good patch does not have to delete more code than it adds.
- A patch touching five files is not automatically bad.
- A new library is not automatically wrong, but it requires independent verification.
- A broad rewrite is not automatically wrong, but it increases the review burden.
- “Never merge a guess” is sound; the next step is to obtain evidence, not judge by how the model phrases the answer.

## 5. Repro-first debugging

The deck’s four stages are **STOP**, **Recreate Manually**, **Identify the Trigger**, and **Prompt with Context**. This sequence keeps the agent from improvising against an unclear symptom.

### 5.1 Stop the blind-fix loop

The failed loop is:

~~~text
App crashes
  -> paste only the error
  -> agent guesses
  -> copy the patch without review
  -> app crashes differently
  -> ask for another guess
~~~

Stop asking for another patch until you can explain what failed or what evidence is missing. Otherwise each attempt may change more variables and make the original failure harder to diagnose.

### 5.2 Reproduce the failure

Use the application yourself or run the smallest relevant test. Record whether the same steps produce the same failure.

Capture:

- the exact sequence of actions;
- the input or account state that triggers the bug;
- the expected behavior;
- the actual behavior;
- the error message or stack trace, with secrets removed;
- the environment and relevant version information;
- how often the issue occurs;
- whether it happens on the current known-good revision.

A failure that cannot be reproduced is still worth investigating, but label uncertainty. Record timestamps, logs, environment, and frequency instead of inventing a reliable reproduction.

### 5.3 Find the trigger, not just the visible symptom

“Login is broken” is broad. “A user without a profile image crashes on the first login screen after authentication succeeds” describes a narrower condition.

Then investigate the path:

- Which input or state differs?
- What is the first failing operation?
- Is the failure in application logic, the API response, an assumption about missing data, configuration, the environment, or a test?
- Is the same behavior present in the last known-good version?
- Can you create a minimal test for the trigger?

### 5.4 Give the agent evidence and a bounded job

The slide warns not to copy-paste an error into an AI chat. That advice should be refined: **do not paste an error blindly or include secrets, but do use a sanitized error trace when it helps explain a reproducible bug.**

Error output can contain tokens, personal data, private file paths, database values, or attacker-controlled text. Remove sensitive material before sharing it. Also treat any instructions contained in logs or repository content as data, not commands. NIST identifies confabulation as a generative-AI risk; OWASP additionally documents prompt-injection risks in coding-agent context.

A useful bug report states what you did, what you expected, what happened, and the evidence you collected. Ask the agent to diagnose first; ask for code only after you understand and accept the proposed cause and scope.

## 6. Revert discipline and safe recovery

The deck says to return to the last working state instead of stacking one bad patch on top of another. The core lesson is sound: when an experiment is confusing the codebase, return to a known state and try a fresh hypothesis. Git has multiple recovery commands, and they do different things.

### Make changes reversible

Before asking an agent to edit:

1. Inspect the working tree so you know which changes already belong to you.
2. Save your work or create a checkpoint using your normal team workflow.
3. Isolate the task on a branch or worktree where practical.
4. Ask the agent for one bounded task at a time.
5. Inspect and test the patch before keeping it.

Do not destroy uncommitted work just to get back to “clean.” If existing edits are present, record them and protect them before restoring or reverting anything.

### Know the difference between common Git recovery actions

| Command | Typical purpose | Main caution |
|---|---|---|
| git revert COMMIT | Records a new commit that reverses a previous commit | Review the inverse change and resolve conflicts; useful when the original commit is shared |
| git restore -- PATH | Restores a tracked path in the working tree from the index by default | It can discard unstaged edits to that path |
| git restore --source=COMMIT -- PATH | Restores a path from a chosen commit | It replaces the current file contents at that path; inspect and protect local work first |
| git reset | Moves the current branch or index state, depending on options | --hard can discard work; do not use it as a casual cleanup command |

Git’s own documentation distinguishes reset, restore, and revert. The slide’s word “revert” is used colloquially for “go back,” but in Git, git revert creates a new commit that reverses an earlier commit. It is not the same as deleting local uncommitted changes. See the official docs for [git revert](https://git-scm.com/docs/git-revert), [git restore](https://git-scm.com/docs/git-restore), and [git reset](https://git-scm.com/docs/git-reset).

### A safe recovery decision

- **The patch is uncommitted and isolated:** inspect the diff and selectively restore only the agent’s unwanted paths after protecting other edits.
- **The patch was committed locally and is not shared:** decide whether a new inverse commit, branch reset, or a fresh branch best fits the repository workflow.
- **The patch is already shared:** prefer a transparent corrective commit or git revert; coordinate before rewriting shared history.
- **You are unsure which work belongs to the agent:** stop, save a copy or checkpoint, inspect status and diffs, and ask for help before running a destructive command.

## 7. When to rewrite the specification

The deck says that if the agent keeps failing the three-step audit, the bug may be in the instructions; it recommends reopening the one-page spec. That is sometimes right. First identify which kind of failure you have.

| Repeated symptom | Likely problem to investigate | Next action |
|---|---|---|
| Agent edits unrelated files | Scope instruction or task boundary is unclear, or agent ignored it | State allowed paths and required behavior; inspect changed paths and request a scoped revision |
| Agent contradicts the data model | Spec, repository model, or feature request conflicts | Clarify which requirement is authoritative and update the spec if the product decision changed |
| Agent uses a nonexistent API | Missing version context, mistaken assumption, or hallucinated API | Check installed version and official docs; provide correct API evidence |
| Agent cannot reproduce the bug | Environment or repro information may be incomplete | Recheck the trigger, test data, configuration, and baseline |
| Correct patch fails in CI only | Runtime, dependency, configuration, or environment difference | Compare local and CI versions and inspect the failing output |
| Tests pass but the bug remains | Test does not cover the trigger or checks the wrong behavior | Improve the test so it fails on the old behavior and checks the intended outcome |
| Patch solves one case but breaks another | Regression or incomplete behavioral specification | Add the missing case and clarify compatibility requirements |
| Same ambiguous result across different prompts | Spec or acceptance criteria may be underspecified | Rewrite the relevant requirement and provide examples of valid and invalid outcomes |

Do not rewrite the product spec every time an implementation is wrong. A coding mistake needs a code correction. A stale API needs documentation and version context. A test problem needs a stronger test. Rewrite the spec when it is missing, contradictory, or no longer describes the product decision.

### A quick spec diagnostic

Before editing the spec, answer:

1. What user-visible behavior should happen?
2. What does the current system do instead?
3. Which exact requirement is missing or contradictory?
4. What single example would remove the ambiguity?
5. What must remain unchanged?
6. How will we know the corrected implementation works?

## 8. A disciplined AI coding workflow

This procedure combines the deck’s audit, reproduce-first debugging, and revert discipline.

### Phase A — Prepare

- Read the task and relevant part of the project specification.
- Inspect the repository’s existing changes and branch.
- Identify the current test, build, and lint commands from project documentation or configuration.
- Keep secrets out of prompts and agent-readable context.
- Set the allowed task boundary: relevant paths, behaviors, and files that must not change.
- For a larger feature, first ask the agent to inspect and propose a plan without editing.

### Phase B — Reproduce

- Run the smallest existing test or manual steps that expose the issue.
- Record expected and actual behavior.
- Save a sanitized error trace and exact triggering input.
- Confirm whether the failure occurs on the current baseline.
- If it cannot be reproduced, ask the agent to help investigate evidence; do not ask it to invent a patch.

### Phase C — Diagnose

Ask for:

- the most likely cause and alternative explanations;
- the source path and function involved;
- the evidence in the code or output supporting the diagnosis;
- the smallest proposed change;
- files likely to change;
- a regression test plan;
- any new package, API, migration, or permission required.

Do not let the agent’s diagnosis become a fact until you have checked the evidence.

### Phase D — Implement

After approving the approach:

- keep the change focused on the acceptance criteria;
- require the agent to preserve existing interfaces unless the task authorizes a change;
- request an explanation for any file outside the original scope;
- require a regression test for the reported trigger when practical;
- stop if the implementation direction expands unexpectedly.

### Phase E — Review

Inspect the diff and ask:

- Does it implement the requested behavior?
- Are all changed files relevant?
- Is any code, test, permission, or validation removed?
- Are dependencies and APIs real and compatible?
- Are errors, empty values, and boundary cases handled?
- Are secrets, user data, or external side effects involved?
- Can you explain the new logic in plain language?
- Does the regression test fail against the old behavior and pass with the patch?

### Phase F — Verify and decide

Run the focused regression test, relevant test suite, and the project’s required checks. Record what passed, what failed, and what was not run. Keep the patch only when the evidence is sufficient. Otherwise, fix the specific problem or return to a known state.

## 9. Applying the lesson in VS Code with Codex

For an existing repository, treat the one-page product or bug spec as the contract and use Codex to explore, implement, and test in small steps. [OpenAI’s Codex guidance](https://openai.com/business/guides-and-resources/how-openai-uses-codex/) describes starting larger tasks with a plan, writing prompts like an issue with file paths and acceptance criteria, and maintaining repository context in an AGENTS.md file. These instructions improve context; they do not replace review.

### Step 1 — Inspect the current repository state

In the VS Code terminal, check your branch and working tree. Preserve your own edits before delegating. Do not ask the agent to overwrite or clean up unrelated files.

### Step 2 — Ask for inspection without edits

Use an analysis-only prompt:

~~~text
Do not edit files yet.

Task: [state the bug or feature in one sentence]

Expected behavior:
[what the program should do]

Observed behavior:
[what it does now]

Please inspect the relevant code and report:
1. likely cause, with the file and function involved;
2. evidence supporting that cause;
3. alternative explanations;
4. proposed files to change;
5. a minimal fix and regression-test plan;
6. any API, package, migration, permission, or data-model changes.

Do not invent a command or dependency. If you cannot verify a detail, say so.
~~~

Review the plan. If it is too broad, correct the scope before asking for implementation.

### Step 3 — Request a focused implementation

~~~text
Implement the approved fix only.

Scope:
- Expected files or areas: [list]
- Do not change: [list]
- Preserve: [existing interfaces, formats, or behavior]

Acceptance criteria:
1. [observable behavior]
2. [regression test]
3. [relevant existing cases still pass]

Constraints:
- Do not add a package unless you explain why it is necessary and verify it exists.
- Follow existing project patterns where they fit this behavior.
- Do not disable, weaken, or delete a failing test to make the task pass.

After editing, report every changed path, the reason for each change, the exact commands run, their actual results, and any remaining uncertainty.
~~~

### Step 4 — Review in the editor and terminal

Use VS Code’s Source Control view to inspect changed files and diffs. Also use the terminal to check the Git diff and test output. If the patch changed a dependency file, review the package and lockfile changes. If it changed agent instructions such as AGENTS.md, review those instructions as carefully as application code.

Do not merge or commit simply because the agent says “done.” Confirm the required behavior yourself or through a test that directly checks it.

### Step 5 — Keep a small, reviewable task size

OpenAI describes well-scoped coding tasks as easier for Codex to handle and review. Break a broad request into distinct tasks such as “diagnose,” “add one regression test,” and “implement the agreed fix.” Some legitimate changes are multi-file; the point is to make each change explainable and verifiable.

## 10. Worked debugging example: login fails for a user without a profile image

The deck’s example is specific: a user without a profile picture cannot log in. The slide identifies it as a trigger, but the root cause still needs evidence. Do not assume the login system itself is wrong; perhaps authentication succeeds and the profile-image rendering then crashes.

### Weak prompt

~~~text
Login is broken. Fix it.
~~~

This hides the trigger, expected behavior, environment, evidence, and allowed scope.

### Better diagnosis prompt

~~~text
Do not edit files yet.

Bug: a user account with no profile image fails during login.

Steps:
1. Sign in with a test account that has no profile_image value.
2. Wait for the first post-login screen.
3. Observe the page crash.

Expected: the user signs in successfully and the interface shows the existing default avatar.
Actual: [describe the observed failure and include a sanitized error/stack trace].

Environment:
- branch/commit: [value]
- app version or relevant runtime: [value]
- frequency: [every time / intermittent]

Please trace the failure from the login response to the first screen. Identify the first failing operation, show the evidence, and distinguish authentication failure from profile-image rendering failure. Propose the smallest code and test change. Do not edit files or add dependencies yet.
~~~

### A possible diagnosis path

An agent may report that a component assumes profile_image is always a URL and calls an image helper with a null value. Check the actual code and login response. If the evidence supports that cause, acceptance criteria might be:

- A user with a valid profile image still sees it.
- A user with no profile image signs in and sees the existing default avatar.
- The profile-image display does not trigger a network request to a null or invalid URL.
- A regression test covers the missing-image case.
- The existing login and profile tests still pass.

This is an example of what to investigate, not a claim about the attached deck’s codebase.

### Focused implementation prompt

~~~text
Implement the approved missing-profile-image fix.

Keep authentication behavior unchanged. Only change the profile display path and the smallest relevant test file(s). Reuse the existing default-avatar behavior; do not add a package.

Add a regression test for an absent or null profile_image value. Also keep the existing valid-image case covered.

Run the focused test and the relevant existing test command. Report the changed paths, actual test output, and any behavior you could not verify.
~~~

### Review before accepting

Check whether the patch:

- handles both null and absent fields if both are possible;
- preserves the valid image path;
- uses the project’s existing default-avatar component;
- avoids changing authentication or authorization logic unnecessarily;
- does not silently swallow unrelated network errors;
- includes a test that exercises the missing-image trigger;
- passes the test and relevant checks.

## 11. Reusable prompt and review templates

### Bug report template

~~~text
Title:
[short, observable failure]

Environment:
[branch/commit, operating system, runtime, browser/device if relevant]

Steps to reproduce:
1.
2.
3.

Expected:
[what should happen]

Actual:
[what happens]

Frequency:
[always / sometimes / once]

Evidence:
[sanitized error, trace, screenshot description, test output]

Constraints:
[areas that must not change, compatibility requirements]

Ask:
First diagnose and propose a minimal test and fix. Do not edit until the cause and scope are clear.
~~~

### Scope-review prompt

~~~text
Review this proposed diff without changing files.

Task:
[approved objective and acceptance criteria]

Check:
- changed paths against the authorized scope;
- behavior changes and affected callers;
- new or changed dependencies and APIs;
- removed tests, weakened assertions, or bypassed validation;
- security, data, permission, and external side effects;
- missing tests for failure and boundary cases.

For each finding, cite the file and relevant code, explain the impact, and label it as blocker, important, or optional. If you cannot establish a claim from the repository or official documentation, say so.
~~~

### Regression-test prompt

~~~text
Based on this reproduced bug, propose a regression test before changing production code.

The test must:
- set up the exact trigger;
- fail against the current behavior for the right reason;
- assert the expected behavior, not just that the code did not crash;
- preserve a nearby valid case;
- use the repository's existing test framework and conventions.

Show the test and explain what it proves. Do not modify production code yet.
~~~

## 12. Common failure patterns and corrections

| Pattern | Why it fails | Better move |
|---|---|---|
| “Fix everything wrong with this project” | No boundary, priority, or acceptance test | Name one issue and the behavior that will prove it is fixed |
| Prompting from a crash screenshot alone | The trigger and stack are missing | Reproduce and add steps, state, and sanitized logs |
| Repeatedly asking for another patch | Each guess changes the evidence and code | Pause, compare hypotheses, return to the original trigger |
| Accepting an unexplained new dependency | Package risk and maintenance cost are hidden | Verify registry, version, security, license, and necessity |
| Treating a large diff as automatically wrong | Legitimate migrations can touch many files | Check whether each change is needed and connected |
| Treating a small diff as automatically safe | One line can bypass security or corrupt data | Review consequences and test the behavior |
| Trusting “tests passed” without output | The command may not have run or may have tested the wrong path | Inspect exact commands, exit results, and test coverage |
| Discarding all changes after one bad patch | User edits may be mixed with the agent’s work | Inspect Git status and recover only the isolated patch |
| Rewriting the spec for an ordinary implementation bug | The contract may already be clear | Fix the implementation and add a regression test |
| Letting agent instructions edit their own rules | Persistent instructions can steer future sessions | Review changes to AGENTS.md and other instruction files explicitly |
| Giving an agent broad access for a narrow fix | A prompt boundary does not technically restrict its tools | Use available sandboxing, permissions, and least privilege |

## 13. Slide-by-slide lecture notes

### Slide 1 — Managing the Machine: Reviewing and Debugging AI Code

**Deck content:** The title frames the session as managing generated code through review and debugging.

**Lecture interpretation:** The key skill is not merely prompting. It is turning a request into a testable task and deciding whether the proposed implementation fits the real repository.

**Visual reading:** A pencil overlays a document, reinforcing that generated code is a draft to be examined.

### Slide 2 — Meet your new engineering intern

**Deck content:** The expectation is a “Senior Architect”; the reality is a fast system that writes 1,000 lines a minute, says yes, and may invent facts to finish faster. The human’s job is to manage it, review drafts, and contain chaos.

**Lecture interpretation:** The slide warns against equating fluent output or code volume with senior engineering judgment. Human ownership includes requirements, review, tests, security, and maintenance.

**Verification note:** “1,000 lines a minute” is an illustrative claim, not a productivity measurement. Models do not literally choose to please or invent with human intent. Treat speed and correctness as separate qualities.

### Slide 3 — You are no longer a creator; you are an auditor

**Deck content:** Traditional engineering writes line by line, trusts its own logic, builds slowly, and tests near the end. The AI-native auditor generates in blocks, trusts nothing, tests each step, and needs system logic and boundary setting.

**Lecture interpretation:** The useful shift is from manual typing as the main bottleneck to specifying, steering, and verifying work. The title is intentionally provocative. Developers still need to create, understand, and maintain code; they are not reduced to passive auditors.

**Verification note:** “Trusts nothing” is a reminder to verify, not a recommendation to reject every suggestion. Confidence should follow evidence and risk.

### Slide 4 — The 3-Step Audit Rule

**Deck content:** Check file scope, verify facts and APIs, and enforce simplicity. If a patch fails any check, send it back rather than silently fixing it.

**Lecture interpretation:** These are three fast gates for detecting out-of-scope edits, nonexistent tools, or unnecessary complexity. Add behavioral testing and security review before accepting a patch.

**Verification note:** A developer may appropriately make a small manual correction after understanding it. The important condition is that every retained change is reviewed, explained, and tested.

### Slide 5 — Check file scope before reading code

**Deck content:** A target login file is shown inside concentric system areas such as UI styling, payment gateway, and database configuration. If a login-button task changes core database rules, stop and reject the patch.

**Lecture interpretation:** Compare the agent’s actual touched paths with the task boundary early. Unrelated changes should trigger a pause and explanation.

**Verification note:** “Do not try to read it” is too absolute. Inspect the file list and a concise diff summary so you understand the scope; do not merge unexpected changes without an approved reason. A feature may legitimately require several files.

### Slide 6 — Treat new libraries like suspicious bibliography references

**Deck content:** The slide shows plausible-looking package names, including a deliberately suspicious fake, and says to check any unrequested library, integration, or tool online.

**Lecture interpretation:** A dependency name is a factual claim. Verify the exact package, source, version, maintenance, and security before installing it.

**Verification note:** A missing public documentation page is a warning, not conclusive proof of hallucination. It may be an internal API or a version mismatch. Check authoritative project sources and package registries.

### Slide 7 — Reject hidden complexity

**Deck content:** A straight human core loop from State A to State B is contrasted with tangled AI logic. The slide asks for the thinnest working path and says code that cannot be explained plainly is too complex.

**Lecture interpretation:** Implement the required user behavior and no speculative machinery. Explain the control flow and each branch in ordinary language.

**Verification note:** Complexity can be necessary for security, correctness, resilience, or real requirements. “Thinnest” means no unsupported complexity, not “remove every safeguard.”

### Slide 8 — Spot a panic patch

**Deck content:** The good patch touches one or two files, deletes more code than it adds, explains the previous failure, and uses the existing architecture. The panic patch changes five or more files, adds mysterious libraries, adds large if/else blocks, or rewrites a full function.

**Lecture interpretation:** Look for breadth that does not match the task, unexplained dependencies, and large rewrites without a clear causal reason.

**Verification note:** These are warning examples, not objective patch-quality tests. File counts and lines added/deleted do not determine quality. Review the changed behavior and why each edit is needed.

### Slide 9 — Do not blindly prompt through a bug

**Deck content:** A loop shows a crash, a human pasting an error without reading it, an AI guessing, and the human copying the panic patch, causing a worse crash.

**Lecture interpretation:** The failure is the unexamined loop: symptom, guess, unverified change, new symptom. Break it by establishing a reproducible trigger and evidence first.

**Verification note:** Error text is often useful. Read it, remove secrets, preserve the relevant stack information, and share it with context when appropriate.

### Slide 10 — Repro-first debugging

**Deck content:** Stop; recreate the issue manually; identify the exact trigger; then prompt with what you did, expected, and observed. Example trigger: a user without a profile picture logs in and crashes.

**Lecture interpretation:** Reproducibility turns an ambiguous complaint into a testable condition. It also helps separate an authentication bug from a later rendering bug.

**Verification note:** Some failures are intermittent or environment-specific. Record their frequency and environment rather than claiming they cannot be debugged.

### Slide 11 — Revert discipline

**Deck content:** Three AI panic patches lead away from a fresh stable state. The slide says not to fix a bad AI fix; return to the last working state and start over.

**Lecture interpretation:** Repeatedly layering patches can make causes and effects hard to see. Preserve a known-good checkpoint and isolate experiments.

**Verification note:** The slide uses “revert” generically. Git’s revert, restore, and reset commands differ. Never discard all working-tree changes without first checking whether they include your own work.

### Slide 12 — Sometimes the bug is in the instructions

**Deck content:** If the AI repeatedly fails the audit, hallucinates APIs, or tangles logic, reject the patch and reopen the one-page spec. The diagnostic questions ask whether the feature contradicts the data model, skips a user-journey step, or is necessary for the “aha moment.”

**Lecture interpretation:** The specification is a useful diagnostic artifact. Persistent errors may mean the request is unclear, internally inconsistent, or outside the system’s defined boundaries.

**Verification note:** Not every bad patch is a bad spec. Check whether the issue is implementation, test design, a version mismatch, environment, or actual requirement ambiguity before rewriting the spec.

### Slide 13 — The Solo Engineer’s Shield

**Deck content:** AI supplies speed and code blocks; the developer supplies steering through the spec and repro-first debugging, plus brakes through the audit and recovery discipline. The closing line says the developer need not be smarter than AI, but more disciplined.

**Lecture interpretation:** Good results come from combining generation with constraints, tests, and human responsibility. Discipline makes the system’s work reviewable.

**Verification note:** “Infinite velocity” and “tireless, but careless” are metaphors. Engineering time still includes review, integration, test, security, and maintenance work.

## 14. Practice exercises and answer key

### Exercise 1 — Review the file-count rule

An agent fixes a shared request type and updates a backend handler, frontend caller, fixture, and tests. It changes six files. Is this automatically a panic patch? What evidence do you need?

**Answer:** No. File count is a review prompt. Check that each file participates in the same contract change, that the behavior and compatibility are clear, and that tests cover both sides of the interface. Ask for an explanation if any file seems unrelated.

### Exercise 2 — Repair an unsafe debugging prompt

A user sends only: “It crashes. Fix it.” Write four pieces of information to collect before implementation.

**Answer:** Reproduction steps, expected behavior, actual behavior, and a sanitized error trace or relevant logs. Also record environment/version and frequency when relevant. First ask for diagnosis before code changes.

### Exercise 3 — Handle a new dependency

The agent adds a package named “super-fast-magic-db” for a small null-check fix. What should you do?

**Answer:** Pause the patch. Verify the exact package and publisher on the official registry, check maintenance, security, license, and version compatibility, then ask why the package is needed for a simple null check. If it is unnecessary or unverified, ask for a solution using existing project tools.

### Exercise 4 — Choose a recovery action

Your branch contains your own uncommitted edits plus an agent’s broken change. Should you run a hard reset to return to the last commit?

**Answer:** No. First inspect Git status and diffs, protect your edits, and isolate the agent’s paths. Restore only the changes you intend to discard. A hard reset may destroy unrelated uncommitted work.

### Exercise 5 — Decide whether to rewrite the spec

The agent implemented a clearly stated default-avatar requirement but used the wrong component. It fails a test. Is this a spec problem?

**Answer:** Probably not. The requirement is clear; the implementation needs correction. Add or preserve a regression test and ask for a focused fix. Rewrite the spec only if the expected default behavior or compatibility rule was actually ambiguous.

### Exercise 6 — Review a patch that deletes more than it adds

A patch removes 40 lines of validation to stop a test from failing. What is the key concern?

**Answer:** The patch may suppress the symptom by removing a required check. Determine what the validation protects, why the test failed, whether the test is correct, and whether the intended behavior is still enforced. A shorter diff can be less safe.

### Exercise 7 — Write a bounded Codex task

Write a one-sentence objective, an explicit boundary, and a testable acceptance criterion for a bug in the project you are working on.

**Sample answer:** “Fix the empty avatar field causing the dashboard to crash after login. Change only the profile display component and its focused test unless another path is demonstrably required. A user with no avatar must reach the dashboard and see the existing default avatar; a user with a valid avatar must still see that image.”

## 15. Final working checklist

### Before asking the agent to change code

- [ ] I can state the requested behavior in one or two sentences.
- [ ] I know the relevant spec and acceptance criteria.
- [ ] I inspected the current branch and working tree.
- [ ] I recorded the task boundary and protected unrelated work.
- [ ] I reproduced the bug or clearly stated what evidence is missing.
- [ ] I redacted credentials, personal data, and private tokens from shared logs.
- [ ] I know the project’s real test and build commands.

### Before accepting a patch

- [ ] Every changed path is understood and relevant.
- [ ] The diff does not silently weaken tests, permissions, validation, or security.
- [ ] Any new package or API was verified from authoritative sources.
- [ ] The implementation follows the required behavior and existing contracts.
- [ ] I can explain the change and its failure behavior.
- [ ] The regression test exercises the original trigger.
- [ ] I ran the relevant tests and checked their actual output.
- [ ] I know how to return to a safe state without deleting unrelated work.

## 16. Reference library

These links support the practices in this lecture. Tool documentation changes over time; follow each project’s current official docs and the versions used in your repository. Checked on 2026-10-05.

### Coding with Codex

1. [How OpenAI uses Codex](https://openai.com/business/guides-and-resources/how-openai-uses-codex/) — Examples for code understanding, debugging, test coverage, task scoping, prompts, and persistent repository context.
2. [Code generation — OpenAI API](https://developers.openai.com/api/docs/guides/code-generation) — Current overview of code generation and Codex.
3. [Codex learning resources — OpenAI Developers](https://developers.openai.com/learn/codex) — Guides and materials for Codex workflows and the IDE extension.

### Reviewing changes and managing dependencies

4. [Reviewing proposed changes in a pull request — GitHub Docs](https://docs.github.com/en/pull-requests/how-tos/review-pull-requests/reviewing-proposed-changes-in-a-pull-request) — Inspect diffs, review files, and check dependency changes.
5. [Secure Coding with AI — OWASP Cheat Sheet Series](https://cheatsheetseries.owasp.org/cheatsheets/Secure_Coding_with_AI_Cheat_Sheet.html) — Risks from hallucinated packages, untrusted agent context, secrets, permissions, and generated code review.
6. [Vulnerable Dependency Management — OWASP Cheat Sheet Series](https://cheatsheetseries.owasp.org/cheatsheets/Vulnerable_Dependency_Management_Cheat_Sheet.html) — How to handle third-party dependencies and vulnerability findings.
7. [Software Supply Chain Security — OWASP Cheat Sheet Series](https://cheatsheetseries.owasp.org/cheatsheets/Software_Supply_Chain_Security_Cheat_Sheet.html) — Dependency and development-chain risks.

### Software quality and AI risk

8. [Secure Software Development Framework (SSDF), NIST SP 800-218](https://csrc.nist.gov/pubs/sp/800/218/final) — Secure software-development practices that can be integrated into the development lifecycle.
9. [SSDF Profile for Generative AI and Dual-Use Foundation Models, NIST SP 800-218A](https://csrc.nist.gov/pubs/sp/800/218/a/final) — AI-specific additions to secure development practices.
10. [NIST AI Risk Management Framework: Generative AI Profile](https://www.nist.gov/publications/artificial-intelligence-risk-management-framework-generative-artificial-intelligence) — Generative AI risks, including confabulation, and risk-management practices.

### Git recovery and tests

11. [git status](https://git-scm.com/docs/git-status) — Understand the current working tree and staged changes.
12. [git diff](https://git-scm.com/docs/git-diff) — Inspect changes between versions, the index, and the working tree.
13. [git revert](https://git-scm.com/docs/git-revert) — Record a new commit that reverses an earlier commit.
14. [git restore](https://git-scm.com/docs/git-restore) — Restore selected paths; understand which local changes can be overwritten.
15. [git reset](https://git-scm.com/docs/git-reset) — Read carefully before moving branch/index state; some modes discard work.
16. [pytest documentation](https://docs.pytest.org/en/stable/) — Official documentation for writing and running Python tests, if the project uses pytest.

## 17. Closing takeaway

The AI can draft a patch quickly. The developer makes it safe to keep by asking a bounded question, reproducing the failure, checking the diff, verifying external claims, testing the intended behavior, and preserving a known-good recovery point.

> **Class takeaway:** Let the model generate. Let evidence decide. Keep a human responsible for every change that enters the codebase.
