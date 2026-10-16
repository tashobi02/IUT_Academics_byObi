# Lecture Sheet: Building It

**Topic:** Turning a validated product idea into a build plan, an AI-ready specification, a controlled working process, a sustainable cost model, and a first distribution channel  
**Source deck:** `3rd Class.pdf`  
**Deck title:** *Class 3: Building It*  
**Deck subtitle:** *A spec, a build route, and numbers that work*  
**Deck length:** 27 pages  
**Prepared:** 2026-09-25  
**Audience:** IUT undergraduate students, early builders, and Bangladesh-based founders  
**Central idea:** AI can help a small team produce software faster, but speed does not remove product decisions, testing, cost control, support, or customer acquisition. Write those decisions down, build the smallest useful version, measure the real workload, and keep a person responsible for the final choices.

> **How to read this sheet:** **Deck content** records what the page teaches. **Lecture interpretation** explains how to apply the idea and where it can fail. **Verification note** separates a useful rule from a claim that needs evidence. Prices and product pages linked below were checked on 2026-09-25; they can change.

## 1. Learning objectives

By the end of this class, you should be able to:

1. Explain what AI-assisted building can accelerate and what remains the builder’s responsibility.
2. Choose a suitable build route by balancing speed, control, cost, and the quality needed for the product’s first real users.
3. Write a concise product specification that states the user, job, paid outcome, boundaries, fixed decisions, and success criteria.
4. Explain why unspecified product details become assumptions in generated software.
5. Design a first-use experience that helps a new user reach a useful, trustworthy result quickly.
6. Specify an AI feature using accepted outputs, cost per use, failure behavior, and examples that can become an evaluation set.
7. Use a second model as a reviewer without mistaking model agreement for proof.
8. Maintain a specification, decision ledger, and locked-rule list so work can continue across sessions without silently reviving old decisions.
9. Delegate a bounded work loop to an agent while keeping approval, external actions, and product decisions under human control.
10. Estimate model cost from actual input tokens, output tokens, calls per user, tools, and heavy-user behavior.
11. Compare subscription, usage-based, and lifetime pricing while accounting for continuing service costs.
12. Choose a first customer acquisition channel and design a measurable experiment for finding the first ten users.
13. Identify which statements in the slides are examples, assumptions, or reported outcomes rather than independently established facts.
14. Prepare the three deliverables for the next class: a one-page spec, a per-user cost estimate with a heavy-user case, and a channel hypothesis.

## 2. Prerequisites and working rules

### Bring these inputs

- The problem evidence, interview notes, and buyer hypothesis developed in Classes 1 and 2.
- One product idea narrow enough to specify in one page.
- A spreadsheet or table for the feature, cost, and channel work.
- A current model/API pricing page for whichever provider you expect to use.
- A way to run and inspect the product: a test account, sample data, and a basic test checklist.

### Working rules

- Keep one named person accountable for the final product decisions. AI can propose, draft, code, and check; it cannot own the consequences.
- Record whether each item is a **fact**, **estimate**, **assumption**, **decision**, or **unknown**. Do not let a polished AI answer turn an assumption into a fact.
- Write exclusions explicitly. “Not in the first version” is a real product decision.
- Do not put private customer information, API keys, or production credentials in prompts, logs, or public repositories.
- Test on synthetic or consented data first. Restrict data access to what the task needs.
- Use test cases that check both that intended behavior works and that prohibited behavior stays absent.
- For every price, record currency, billing unit, billing period, included usage, fees, date checked, and source URL.
- Estimate the heavy user separately. Averages can hide a small group of users whose usage makes a free or flat-price plan unprofitable.
- Treat provider prices as the API model component of cost, not the full cost of operating a product.
- Build a prototype to learn. Before accepting real users or payments, review security, permissions, data retention, reliability, support, and rollback.
- Use a different model for a second opinion when helpful, but verify important claims against source material, executable tests, or real users.

## 3. One-page lecture summary

### The build workflow

~~~text
Problem evidence
    -> Choose a buyer and the first valuable outcome
    -> Write what the product does and does not do
    -> Specify the AI output, cost, failure behavior, and tests
    -> Pick the simplest build route that can meet the quality bar
    -> Build a narrow, testable version
    -> Measure quality, real usage, and real costs
    -> Make the first-use experience useful and trustworthy
    -> Choose one first-user channel and run a small experiment
    -> Review results, update the decision ledger, and decide what to build next
~~~

### The six parts of a useful first specification

| Part | The question it answers | Example |
|---|---|---|
| What it does | What task can a user complete? | Find candidate stores that meet a stated product profile |
| Who it is for | Which user and buyer have this problem? | A small UK DTC brand sourcing relevant leads |
| The paid feature | What result is valuable enough to charge for? | A qualified, source-backed list that saves research time |
| Out of scope | What must the first version not attempt? | No automated sending, no paid lead database, no social-platform automation |
| Locked rules | What decisions must not drift? | A lead without source provenance is excluded; unknown is never automatically treated as pass |
| How we know it works | What observable test indicates success? | Every exported lead has a working source and passes a defined review rubric |

### Three documents to keep the work aligned

| Document | Contents | It prevents |
|---|---|---|
| **SPEC.md** | Current user, problem, scope, workflows, acceptance criteria | Rebuilding a generic version of the product |
| **DECISIONS.md** | Dated decisions, reason, evidence, owner, status, and what would reopen them | A later session quietly reversing a settled decision |
| **LOCKED_RULES.md** | Invariants and prohibitions that every implementation must preserve | A removed feature, unsafe action, or non-negotiable constraint returning |

These documents work best when they have one current source of truth, a clear owner, and a revision history. They support collaboration; they do not remove the need to discuss uncertain or consequential decisions with people.

### Cost formula

For a text-only API estimate:

**Model cost per user per month**  
= calls per user × [(average input tokens per call × input price per token) + (average output tokens per call × output price per token)]

If provider prices are given per million tokens:

**Cost**  
= (monthly input tokens ÷ 1,000,000 × input price per million)  
+ (monthly output tokens ÷ 1,000,000 × output price per million)  
+ paid tools and other metered services

Then estimate the rest of the service: hosting, database, storage, email, payment fees, monitoring, retries, abuse, refunds, support, and development/operations time.

### Model choice loop

~~~mermaid
flowchart TD
    A["Define an accepted-output test set"] --> B["Run the cheapest suitable model"]
    B --> C{"Meets quality, safety, and latency limits?"}
    C -->|"Yes"| D["Measure real usage and cost"]
    C -->|"No"| E["Try a stronger model or add a check"]
    E --> A
~~~

### The Class 3 hand-in

1. A one-page specification with out-of-scope items and locked rules.
2. A per-user cost line using current prices, token assumptions, and a separate heavy-user estimate.
3. One channel hypothesis: where the first ten users could come from and how to test that assumption.

## 4. Core concepts and frameworks

### 4.1 AI speeds up tasks; it does not supply product judgment

The slide maps a former fifteen-person team to AI-assisted research, product management, design, coding, quality assurance, and writing. This is a way to show that AI can perform or accelerate pieces of work that once required several roles. It is not evidence that one person plus an AI has the expertise, coordination, accountability, or output quality of a fifteen-person team.

The builder still needs to:

- choose the right customer and product scope;
- inspect data quality, privacy, and permissions;
- set acceptance criteria and test the result;
- decide what to ship;
- manage failures, security, support, refunds, and updates;
- understand whether customers actually receive value.

A useful mental model is **AI as a fast contributor inside a human-owned process**, not AI as a complete company.

### 4.2 Build route: move one rung at a time

A build route is the mix of tools and engineering effort used to create the product. The slide highlights four factors:

| Factor | What to ask |
|---|---|
| Speed | How soon can I test the core workflow with a real user? |
| Control | Can I inspect and change the data model, integrations, permissions, and behavior? |
| Cost | What do tools, API calls, development time, and operations cost? |
| Quality bar | What reliability, accessibility, security, and polish does the real workflow require? |

A practical ladder:

1. **Clickable prototype or no-code builder:** useful for testing screens, wording, and workflow assumptions.
2. **AI-assisted code:** useful when the product needs real data, logic, and integrations but a builder can still inspect and test generated code.
3. **Custom engineering:** useful when security, scale, special integrations, performance, or control requirements exceed the earlier route.

The slide’s rule, “climb one rung at a time,” means that the team should learn what its product needs before paying for complexity. It does not mean a real product can remain on a tool that cannot meet its requirements. A rough prototype may be enough for an interview; software handling customer data or payments needs a higher quality bar.

**Important distinction:** the cost of using an AI coding assistant is not the same as the cost of running the resulting product. Builder credits or a coding subscription are development expenses. Production API calls and infrastructure are recurring service expenses.

### 4.3 A specification turns silent assumptions into visible decisions

A **product specification (spec)** describes the user, outcome, scope, behavior, constraints, and tests well enough that someone else can build and evaluate the product without guessing key decisions.

AI code generation will often fill gaps with plausible defaults. The deck gives examples: email/password authentication, every database field stored as a string without validation, and an unlimited free tier. The exact defaults vary by tool and prompt. The general risk is that an unstated choice can become code before the builder notices it.

A good spec does not describe every implementation detail. It makes high-impact choices explicit:

- user roles, permissions, and account recovery;
- data fields, formats, validation, retention, and deletion;
- the primary workflow and exception paths;
- what happens when the model is uncertain or unavailable;
- billing and usage limits;
- required integrations and their permissions;
- success criteria and tests;
- what is deliberately out of scope.

The slide recommends “one page, not twenty” as a discipline for the first version. Keep the current product contract concise, then link to detailed data schemas, evaluation cases, or operational procedures when needed.

### 4.4 The first run is part of the product

An empty screen and a blinking cursor provide no evidence that the product works. A strong first-use experience helps a new user reach one meaningful result before asking them to configure everything.

For an AI product, a useful first run can include:

- a clearly labelled sample workflow or sample data;
- one result grounded in visible inputs;
- citations or source records when the feature relies on external information;
- an editable result and an explanation of what the system did;
- a clear route to upload the user’s own data safely.

Do not preload real customer data without permission. Use a synthetic example or user-approved sample. “Give the user a useful first result” is a design hypothesis to test. Some products must first collect data, verify identity, or configure permissions; make those steps transparent instead of pretending every product can produce an instant answer.

### 4.5 An AI feature spec needs examples and a failure plan

A conventional feature description often says what the feature does. An AI feature also needs to define:

1. **Good output:** an example of a useful answer and the criteria it meets.
2. **Cost per use:** an estimate from input/output tokens, model, tools, and retries.
3. **When it is wrong:** what the user sees and what action is blocked or allowed.
4. **Accepted examples:** real or synthetic input/output pairs that demonstrate the required behavior.

Accepted examples can become an **evaluation set**: a fixed group of test cases run against each prompt, model, or code change. Include normal examples, edge cases, ambiguous inputs, unsupported requests, and failures. Score more than style: correctness, source quality, completeness, safety, latency, and cost may all matter.

A small, representative test set is more useful than one perfect demo. Keep test inputs separate from the prompt being optimized where practical, so a prompt is not merely tailored to memorize the examples.

### 4.6 A second model is a reviewer, not a proof system

The slide’s loop is: one model writes, a second model checks, and a person decides. A second model can find unclear requirements, overlooked cases, or weak assumptions. It can also repeat the same error, misunderstand the spec, or express unjustified confidence.

Use model review to generate questions and candidate defects:

- ask it to quote the exact spec line that is unclear;
- require it to separate direct evidence from inference;
- ask it to list assumptions and missing tests;
- verify findings against source documents and actual product behavior;
- run automated and manual tests before accepting code.

Two models agreeing is not the same as two independent measurements. The human reviewer must still decide whether the result satisfies the product and its users.

### 4.7 Context, decision ledgers, and invariants

A model can only use project information available in its active context or through tools and files it actually reads. A new session may not contain earlier decisions. A long session may be summarized, may lose detail, or may include obsolete instructions. Exact behavior depends on the application.

A **decision ledger** records why a decision was made, when, by whom, and what evidence could change it. A **locked rule** is a constraint that must remain true across implementation changes. Examples:

- SEND_ENABLED=false;
- every exported lead must have a source;
- unknown qualification status is not a pass;
- never auto-send a message;
- deleted features must remain absent unless a named person approves restoring them.

Tests can encode some invariants. Documentation should make them easy to find. Version control should show when they changed. If several files disagree, resolve the conflict and identify one authoritative version before asking an agent to make changes.

### 4.8 An agent should complete a bounded loop

An **agent** is a system that can read context, use tools, take one or more steps, inspect results, and continue toward a goal. The class rule is “delegate the loop, not the call”: provide a bounded task and context, let the agent execute and check it, then review its work.

A safe delegation defines:

- allowed files, tools, and data;
- expected output and tests;
- actions that require approval;
- where output is saved;
- what it should do when evidence is missing;
- a human review step before external or irreversible action.

For example, an agent can scan a set of ideas, compare each against earlier records, and save a report. A person can pick or reject them. An agent that drafts a message should not automatically send it unless the product explicitly supports that action and appropriate consent, permissions, review, and controls are in place.

### 4.9 Model routing is a quality-and-cost decision

Different models can have different reasoning quality, latency, context limits, reliability, and price. The deck’s “frontier / mid-tier / budget / local” categories are a useful starting framework, not a permanent ranking of current model brands.

Test the actual workload:

1. Write a rubric and create representative examples.
2. Run each candidate model with the same inputs.
3. Score quality and failure rates, not just fluency.
4. Measure latency and token usage.
5. Compare total cost for the expected workload.
6. Start with the least expensive model that reliably meets the required quality.
7. Route difficult or uncertain cases to a stronger model or a human review path.

A model is “cheap” only relative to the whole workload. A less expensive model that needs extra retries or creates costly errors may cost more in practice.

### 4.10 Estimate the heavy user and the full service cost

The user who makes ten times as many calls may cost about ten times as much **if** call size, model, tool usage, and error/retry rates are similar. If their prompts are longer or they use image, audio, search, or agents, their cost may grow by more than ten times.

Track at least:

- calls per user per month;
- input and output tokens per call;
- model and pricing tier;
- cached tokens where applicable;
- tool, search, storage, or runtime fees;
- retries, timeouts, and failed runs;
- p50 and high-percentile usage;
- cost by account and by feature.

The API invoice is only one part of cost of service. Add infrastructure, database, storage, email, payment processing, monitoring, support, refunds, abuse prevention, and time spent maintaining the product.

### 4.11 Price from the cost floor, then test value and willingness to pay

A **cost floor** is the minimum revenue needed to cover the relevant service and business costs. It is not automatically the right market price. A product may be worth more than its delivery cost, or customers may not pay even when its cost is low.

Estimate price from both directions:

- **Cost side:** API use, infrastructure, support, payment fees, refunds, and fixed expenses.
- **Buyer side:** the value of the problem solved, the buyer’s alternatives, urgency, budget, and willingness to pay.

The three pricing models in the deck have different risk profiles:

| Pricing model | Benefit | Risk to check |
|---|---|---|
| Subscription | Recurring, predictable revenue | Heavy usage or support can exceed the flat fee |
| Usage-based | Revenue rises with consumption | An unpredictable bill can scare users away |
| Lifetime deal | Cash arrives upfront and can speed an initial launch | Service and model costs can continue for years after the sale |

If a lifetime deal is considered, define usage limits and calculate a realistic service lifetime. “Cash now, cost forever” is the deck’s warning: a one-time payment does not make ongoing model calls, support, or infrastructure disappear.

### 4.12 Distribution changes what you build

A **distribution channel** is a repeatable way to reach potential users or buyers. The five slide categories are search and AI answers, communities, outreach, marketplaces, and content.

The channel affects the product:

- search users need clear landing pages, indexable material, and a self-serve path;
- communities require useful participation and trust before promotion;
- outreach requires a defined target, relevant reason to contact, and a safe, respectful process;
- marketplaces impose listing, pricing, promotion, and customer-support rules;
- content requires original useful material and a way to convert attention into a product trial or conversation.

Do not select a channel because it is fashionable. Pick the one where the first ten plausible users can be reached, make a small experiment, and record responses. Search visibility and generative answers are not guaranteed by publishing AI-written pages; Google says its search systems reward helpful, original content and treats ranking manipulation through scaled automation as spam. See the official guidance in Section 10.

## 5. Reusable templates and prompts

### 5.1 One-page product specification

~~~text
PRODUCT:
VERSION / DATE:
OWNER:

1. USER AND BUYER
Primary user:
Buyer / approver:
Job they are trying to complete:
Evidence from interviews or observation:

2. WHAT IT DOES
In one sentence:
Primary workflow:
What the user receives:
What data or permissions it needs:

3. THE PAID OUTCOME
Why this matters:
What the buyer gets:
Current alternative:
Price hypothesis and unit:

4. OUT OF SCOPE
The first version will not:
Explicitly blocked actions:

5. LOCKED RULES
Rules that must remain true:
Rules requiring human approval:
Unknown information must be handled by:

6. HOW WE KNOW IT WORKS
Acceptance criteria:
Test cases:
Quality threshold:
Cost / latency limit:
Failure and recovery behavior:

7. FIRST RUN
What the user sees first:
Sample or demo data:
First useful result:
How the user edits, checks, or rejects it:

8. OPERATIONS
Who reviews errors:
How to stop or roll back:
Support route:
Usage limits:
~~~

### 5.2 AI feature and evaluation-set template

Use one row for each test case.

| Field | What to record |
|---|---|
| Case ID | Stable identifier |
| Input | Synthetic or consented input |
| Expected behavior | What a correct system should do |
| Must include | Required facts, fields, or sources |
| Must not do | Prohibited action or unsupported claim |
| Acceptance rubric | Correctness, completeness, grounding, safety |
| Expected failure handling | Ask, defer, decline, or send for review |
| Model and prompt version | Reproducibility |
| Cost and latency | Measured usage, not a guess |
| Result | Pass/fail plus reviewer note |

### 5.3 Decision ledger template

| Date | Decision | Reason and evidence | Owner | Status | What would reopen it? |
|---|---|---|---|---|---|
| YYYY-MM-DD | Example: no auto-send in v1 | Customer trust and insufficient test coverage | Product owner | Locked | A reviewed consent and safety design |

Keep the ledger short enough that a new session or collaborator can scan it. Link supporting evidence rather than copying entire research notes into the ledger.

### 5.4 Locked-rules template

~~~text
LOCKED PRODUCT RULES

- No automatic external messages in version 1.
- A record without a verifiable source is not exported as a qualified lead.
- Unknown is never treated as a qualification pass.
- No production credentials in prompts or repository files.
- Any exception requires approval from: [role/name].
- Update this file and the decision ledger when a rule changes.
~~~

Translate critical rules into code checks when possible. Documentation is a reminder; tests can catch regressions, but neither replaces review of the workflow.

### 5.5 Session-start prompt

~~~text
Read SPEC.md, DECISIONS.md, and LOCKED_RULES.md before changing anything.
Tell me which version/date of each file you read.
Summarize the task and the relevant acceptance criteria in 3-5 bullets.
List any conflict between the task and the locked rules.
If a required fact is unknown, ask or mark it unknown. Do not invent a pass.
Do not send messages, publish, spend money, or change production data.
Make only the requested local changes, run the listed tests, and report
the files changed, test results, remaining uncertainty, and estimated cost.
~~~

### 5.6 Ambiguity-review prompt

~~~text
Review this specification as a developer who has never spoken with me.
For every place you would have to guess:
1. quote the exact line;
2. state the assumption you would make;
3. explain the product risk if it is wrong;
4. propose a question or acceptance criterion that would remove the ambiguity.

Separate missing decisions from implementation suggestions. Do not silently
choose a default. Treat LOCKED_RULES.md as binding. Do not claim a test passes
unless you ran it and can show the result.
~~~

### 5.7 Cost worksheet

| Input | Example assumption | How to replace it with evidence |
|---|---:|---|
| Calls per light user per month | 20 | Measure a test cohort |
| Calls per heavy user per month | 200 | Use observed high-percentile usage or a stress case |
| Input tokens per call | 2,000 | Log actual prompt and retrieved context sizes |
| Output tokens per call | 500 | Measure generated output |
| Model input price per 1M tokens | Current provider rate | Provider pricing page, checked on a date |
| Model output price per 1M tokens | Current provider rate | Provider pricing page, checked on a date |
| Tool/search/runtime charges | $0 in text-only example | Inspect provider rate card and tool use |
| Other service cost per user | To be measured | Hosting, DB, storage, email, support, refunds |
| Monthly signups / active users | Separate counts | Do not treat signups as active users |

Formula:

~~~text
Input cost = monthly input tokens / 1,000,000 * input price per 1M
Output cost = monthly output tokens / 1,000,000 * output price per 1M
Model cost = input cost + output cost + paid tools
Service cost = model cost + infrastructure + other variable costs + support
~~~

### 5.8 Channel experiment template

~~~text
CHANNEL:
WHY THIS BUYER IS THERE:
FIRST TEN PEOPLE OR ORGANIZATIONS:
FIRST ACTION:
VALUE PROVIDED BEFORE ASKING FOR A SALE:
MESSAGE OR LANDING-PAGE PROMISE:
MEASURE:
- qualified conversations:
- trials or demos:
- activation:
- paid conversion:
- time spent and cash spent:
STOP / CHANGE RULE:
WHAT I LEARNED:
~~~

### 5.9 Bounded-agent task template

~~~text
GOAL:
INPUT FILES / DATA:
ALLOWED TOOLS AND FILES:
DO NOT:
OUTPUT LOCATION:
ACCEPTANCE TESTS:
ASK FOR APPROVAL BEFORE:
IF DATA IS MISSING:
FINAL REPORT MUST INCLUDE:
~~~

## 6. Detailed page-by-page lecture notes

### Page 1 — Class 3: Building It

**Deck content.** The class title is “Building It,” with the subtitle “A spec, a build route, and numbers that work.”

**Lecture interpretation.** “Building” here means more than generating code. The deck connects product definition, AI-assisted implementation, continuity across sessions, operating cost, and customer acquisition. The build is not successful merely because a demo runs; the team needs an outcome that a buyer values and a system it can operate.

**Verification note.** The subtitle is a useful class promise, not proof that any particular stack, price, or business model will work. Each must be tested against the product’s users and real usage.

### Page 2 — Section 1: How you’ll build it

**Deck content.** A section divider introduces the build-route discussion.

**Lecture interpretation.** Start by deciding how to learn quickly without committing to more technology than the product needs. The following pages compare speed, control, cost, and quality.

**Verification note.** Do not infer that a specific tool is required. The tool names on the slides are examples, and their features or pricing can change.

### Page 3 — What a team used to cost

**Deck content.** The slide maps six roles to AI-assisted tasks: researcher, PM, designer, developer, QA, and writer. It concludes: “One person and AI now. The work didn’t disappear, the headcount did.”

**Lecture interpretation.** This is a map of tasks that AI can help with:

- **Researcher:** gather and cluster reviews or complaints.
- **Product manager:** draft the spec and record decisions.
- **Designer:** generate and compare layouts.
- **Developer:** write and review code.
- **QA:** run tests and look for regressions.
- **Writer:** draft product copy, documentation, and messages.

A solo builder can use these capabilities to move faster, but the person still has to verify research, resolve competing goals, judge interface quality, assess security, run meaningful tests, and take responsibility for writing that users see. AI-assisted work can reduce the need for some tasks or shorten them; it does not establish that one person has the capacity of fifteen experienced specialists.

**Verification note.** The slide gives no study, workload, quality level, or team comparison behind the “fifteen people” claim. Read it as a framing device. In a real plan, estimate the actual human hours, review burden, and skills required.

### Page 4 — Picking your rung

**Deck content.** Four factors decide the build route: speed, control, cost, and how good the product has to be. Lovable is given as a fast landing-page builder; Claude Code is shown as a way to build a backend. The rule is to climb one rung at a time.

**Lecture interpretation.** Prototype first when the question is “Will a buyer understand or want this?” Move to a code route when the product needs real data or workflows that the prototype cannot support. Use deeper engineering when security, reliability, integration, or scale requires it. Match the route to the next learning objective.

Separate four budgets:

1. prototype and coding tools;
2. human implementation and review time;
3. production model/API use;
4. hosting and ongoing operations.

A tool that accelerates development does not necessarily reduce production cost. A backend generated in a day is not automatically safe to expose to customers.

**Verification note.** Product names are examples from the slide. Check current documentation and terms. A landing-page mockup and a service that stores customer data have different quality and security needs.

### Page 5 — How I build

**Deck content.** The process is “AI writes it → a second model checks it → I decide.” The speaker says they are not a developer and uses the spec to stay in charge.

**Lecture interpretation.** This is a practical role separation: drafting can be delegated; review can be assisted; ownership stays with the builder. When accepting generated code, ask the AI to explain the change, inspect the diff, run tests, and verify the product workflow yourself. A reviewer model can help identify overlooked requirements, but it cannot certify security or correctness by agreement alone.

A beginner can preserve control by working in small changes:

1. state one task and the relevant spec section;
2. ask for a proposed change before a broad rewrite;
3. inspect changed files;
4. run the tests and a manual check;
5. update the decision ledger if a product decision changed.

**Verification note.** Models can share failure patterns. A different model is useful for another perspective, not an independent guarantee. Compare claims with tests and observed behavior.

### Page 6 — Section 2: The spec

**Deck content.** A divider introduces the specification section.

**Lecture interpretation.** The spec is the control document for the product: it lets a builder or coding agent implement the intended behavior while exposing missing decisions early.

**Verification note.** A spec is useful only when it is current and accessible to the person or agent doing the work. Keep a date/version and resolve conflicting copies.

### Page 7 — If you don’t decide, AI decides

**Deck content.** The slide says an unspecified authentication choice may become email/password with no SSO or magic link; an unspecified data model may use strings with no validation; unspecified pricing may become an unlimited free tier. Its rule: every gap is a decision you did not know you made.

**Lecture interpretation.** Generated systems require defaults. Those defaults may be convenient for a demo but inappropriate for real users. Review the high-impact areas before implementation: authentication and recovery, data types and validation, access control, deletion, pricing limits, and failure behavior.

For every unresolved point, either:

- make and record a decision;
- explicitly mark it unknown and prevent a risky default; or
- defer it by keeping the feature out of scope.

**Verification note.** These examples are plausible failure modes, not guaranteed outputs from every AI builder. Inspect the generated schema and configuration instead of assuming the model chose a particular implementation.

### Page 8 — One page, not twenty

**Deck content.** The spec should contain six items: what it does, who it is for, the paid feature, out of scope, locked rules, and how the team knows it works. The slide says “out of scope” is the part people skip.

**Lecture interpretation.** The six items form a compact product contract. “Out of scope” protects time and prevents a builder from adding plausible but unneeded features. “How you know it works” should describe observable behavior, not a vague aspiration such as “it is accurate” or “it feels fast.”

Turn each important requirement into acceptance criteria. For example: “Every exported lead shows a source URL and the date checked” can be tested. “The lead list is high quality” needs a rubric and examples before it can be tested consistently.

**Verification note.** One page is a useful first summary. A regulated, data-intensive, or technically complex product may also need separate detailed specifications. Keep the one-page overview as the index, not as a reason to omit necessary engineering detail.

### Page 9 — The first output is the product

**Deck content.** The slide contrasts an empty screen with a first useful result already loaded. In one case the user sees “Start typing” without sample data or guidance and closes the tab; in the other, the user sees a result, source information, and an editable output. It says the first run decides everything for an AI product.

**Lecture interpretation.** The first session is a high-value test of whether the product’s promise is understandable and whether the user can reach value. A sample run can demonstrate what inputs are needed, what the AI produces, and how a person can correct it. Show provenance when the output depends on sources.

Give users control: let them inspect, edit, reject, or retry. Mark demo data clearly. Do not imply that synthetic or preloaded examples are real customer records.

**Verification note.** “The first run decides everything” is emphatic product advice, not a measured universal law. Some workflows require onboarding, permissions, or data import before producing value. Test completion, time-to-first-value, and return use with actual target users.

### Page 10 — A spec for an AI feature

**Deck content.** Four items a normal spec can miss are a good output, cost per use, what happens when it is wrong, and examples the team would accept. The slide says accepted examples become the test set.

**Lecture interpretation.** Treat AI output as a product behavior that needs a definition, a budget, and an evaluation plan. For each feature, save representative input/output examples and define what makes them acceptable. Add edge cases and examples where the correct behavior is to ask for more information, refuse, or send the case for human review.

When testing versions, keep the task inputs consistent. Track model, prompt, settings, token counts, latency, and results so a change can be compared fairly.

**Verification note.** A small test set can reveal regressions but may not reflect the whole population. Do not tune only to the examples you already have; add new cases from real, consented use.

### Page 11 — Try this prompt

**Deck content.** The prompt asks a developer who has never spoken to the author to list every point where they would need to guess, state the assumption, and quote the relevant line. The “watch for” says to use a different model from the one that wrote the spec.

**Lecture interpretation.** This is an ambiguity audit. Ask a reviewer to make hidden assumptions visible before implementation. Requiring a quote ties the criticism to the actual document and makes it easier to fix. A second model can reveal gaps that the original writer did not notice.

After the review, classify each issue as:

- a missing product decision;
- a missing acceptance test;
- a technical choice that can be deferred;
- a low-risk detail with an approved default.

**Verification note.** The different-model instruction is a useful diversity heuristic, not a guarantee of independence. The reviewer can invent ambiguity or miss an important one. The product owner resolves the issue and updates the source document.

### Page 12 — Factory: the lead pipeline spec

**Deck content.** The slide shows a one-page spec for a lead pipeline. It includes SEND_ENABLED=false, “UNKNOWN is never PASS,” and “spend nothing until proven.” Out of scope: no paid lead databases, no auto-sending, no LinkedIn or Instagram automation, and no custom UI because the spreadsheet is the interface. The rule says every lead keeps its source; EmailProvenance is required and a lead without a source is excluded.

The estimated funnel is:

| Stage | Count shown | Approximate retention from previous stage |
|---|---:|---:|
| Domains | 50,000 | Starting estimate |
| Age 2y+ | 35,000 | 70% |
| DTC + category | 10,500 | 30% |
| £40+ | 4,200 | 40% |
| No blockers | 3,150 | 75% |
| Variant depth | 1,575 | 50% |
| Unit volume | 630 | 40% |
| LLM judgment | 315 | 50% |
| Leads | ~160 | About 51% |

**Lecture interpretation.** The strongest part of this example is that it specifies both positive criteria and things the system must not do. Provenance makes a result auditable: a reviewer can see where a lead came from and decide whether the evidence still supports it. “Unknown is never pass” prevents the pipeline from turning missing evidence into a qualified lead. “Spend nothing until proven” sets a budget gate.

The counts make a funnel model visible. The retention percentages approximately reproduce the slide’s counts, but they are estimates. To make the pipeline testable, define each filter precisely: what counts as a domain being two years old, which categories qualify, what “£40+” means, how a blocker is identified, what counts as variant depth or unit volume, and what the LLM judgment may decide.

**Verification note.** Do not report ~160 as observed leads or as a market-size fact. Validate the initial list, record exclusions at each stage, measure false positives and false negatives, and compare the estimate with actual reviewed results. A language model should not silently convert uncertain signals into a pass. Keep the prohibited auto-sending rule unless a separate review establishes that an external action is appropriate and controlled.

### Page 13 — Section 3: Keeping AI on track

**Deck content.** A section divider introduces the continuity and project-management section.

**Lecture interpretation.** A product built over multiple sessions needs a reliable way to carry forward requirements and decisions. The following pages use project documents, locked rules, and review loops to maintain continuity.

**Verification note.** Do not rely on undocumented memory. Check which files, instructions, or project context the active AI tool actually reads.

### Page 14 — Why it drifts

**Deck content.** The slide says a model starts each session empty, long chats lose the middle, and summaries can soften decisions. Its rule: a fresh chat plus documents is better than a long thread.

**Lecture interpretation.** The core issue is available context. An AI tool may receive conversation history, a summary, explicit project files, or stored instructions, depending on the product and setup. If a requirement is not included or discoverable, the model may not apply it. A long thread can also contain stale or contradictory decisions.

A robust workflow opens a fresh task with the current spec and decision records, names the active versions, states the task, and asks the agent to report conflicts before editing. Keep decisions in maintained files instead of depending on a past chat.

**Verification note.** “It starts every session empty” is a simplification; some products support project memory or repository instructions. The transferable rule is to verify what context is loaded and make critical constraints explicit.

### Page 15 — Your management layer

**Deck content.** Three documents replace repeated meetings in the slide’s framing: the spec, the dated decision ledger, and the locked rules. Without them, the AI makes an average product, undoes a prior decision, or restores deleted features. It says to provide all three at the start of each session.

**Lecture interpretation.** The documents have distinct jobs:

- **Spec:** what is being built and what is excluded.
- **Ledger:** what was decided, why, and by whom.
- **Locked rules:** non-negotiable product and safety invariants.

Make each concise, version-controlled, and consistent. At the start of work, provide or point to the current documents and confirm that the AI has read them. If files conflict, stop and resolve the conflict; do not let the model choose which history to believe.

**Verification note.** Documents reduce avoidable repetition; they do not replace human discussion when a decision is uncertain, costly, or affects stakeholders. “Paste all three” is one workflow; repository-aware tools may read them directly. In either case, verify that they were actually loaded.

### Page 16 — Righted: the button that came back

**Deck content.** The slide reports that a removed feature was later rebuilt from an old spec even though the code tests passed. The “watch for” states that tests check code while locked rules check decisions.

**Lecture interpretation.** A program can pass tests while violating current product intent if the tests encode old behavior or do not cover the requirement. When removing a feature, update the spec, ledger, locked rules, UI, APIs, and acceptance tests. Add a regression test where possible.

For the lead pipeline, for example, a test can assert that no sending function is called, that a record without provenance is rejected, and that an unknown qualification is not exported as a pass.

**Verification note.** The slide provides no repository or test report, so treat it as a course anecdote. The general engineering lesson is sound: test product invariants in addition to code mechanics, and keep tests aligned with the current spec.

### Page 17 — Agents that work like you

**Deck content.** The slide says “delegate the loop, not the call.” The agent reads documents, completes a task, and checks against the spec; the person approves or rejects the work and updates the ledger. The example is a weekly ideas scan: read context, generate five ideas, compare them with previous weeks, save the output, then let the person pick or ignore.

**Lecture interpretation.** This is a bounded, reviewable agent task. The agent is given inputs and rules, produces a saved artifact, and checks its own output. Human review stays at the product decision point. This is safer and easier to inspect than giving an agent a vague open-ended goal.

Specify the workflow’s allowed tools, output location, completion conditions, and approval gates. If an action affects people or external systems—sending messages, purchasing data, publishing, or changing production—make the approval requirement explicit.

**Verification note.** Self-checks can catch omissions but are not independent validation. “Reads the docs” should be verified by asking the agent to identify the relevant rule or version. The slide’s scenario is an example, not evidence of agent reliability in every task.

### Page 18 — Section 4: The numbers

**Deck content.** A divider starts the model-cost and pricing section.

**Lecture interpretation.** Estimate costs from observed work rather than model-name intuition. Cost is one part of whether a product can be sustained.

**Verification note.** Treat any table of model names or prices as a dated snapshot. Providers may change model availability, tokenization, prices, and billing details.

### Page 19 — Righted: 78% of the cost, 11% of the calls

**Deck content.** The slide reports that the team used a frontier model for everything; routine formatting, classification, and tagging accounted for many calls; after moving some work down a tier, the bill dropped by two-thirds with no visible change. The rule: model choice is a pricing decision, not only a technical one.

**Lecture interpretation.** A small fraction of expensive calls can dominate a bill. Classify tasks by difficulty, then test whether a cheaper model meets the quality threshold for each task. Routine, structured tasks are good candidates for lower-cost models; a user-facing core task or a high-consequence result may need a stronger model or human review.

Before routing, freeze a set of representative test cases and compare models on correctness, format compliance, error handling, latency, and cost. Monitor after release because input distribution can change.

**Verification note.** The 78%, 11%, and two-thirds figures are a reported case in the slide, with no time window, token counts, model names, workload mix, benchmark, or definition of “no visible change.” Treat them as a motivating example, not a guaranteed saving. The current Righted site presents an AI-visibility product; it does not independently verify the deck’s earlier cost story.

### Page 20 — Four tiers, four prices

**Deck content.** The slide groups models into frontier, mid-tier, budget, and local options, gives illustrative tasks for each, and says to start at the bottom and move up only when output fails. The listed examples and price ranges are per million input tokens.

**Lecture interpretation.** The tier idea is useful; the brand names and price ranges are not durable. Compare current models on the task you need, including output-token prices. A model page can quote input and output separately, and long context, caching, region, multimodal features, and tools can change the bill. Local inference avoids a per-token provider bill but requires hardware, power, maintenance, and engineering.

**Dated pricing example checked 2026-09-25:** OpenAI’s current API pricing page lists standard short-context rates in USD per million tokens for these models:

| Example model | Input / 1M tokens | Output / 1M tokens | Notes |
|---|---:|---:|---|
| GPT-6 Luna | $0.05 | $0.25 | Standard short-context list price |
| GPT-6 Sol | $1.00 | $5.00 | Standard short-context list price |
| GPT-6 Astra | $5.00 | $25.00 | Standard short-context list price |

These names and rates are a dated example from the [OpenAI API pricing page](https://developers.openai.com/api/docs/pricing), not a permanent model recommendation. Check the current provider price immediately before budgeting or shipping. The same page distinguishes short and long context, cached input, and cache writes.

**Verification note.** The slide’s input-only price bands are not enough to estimate output-heavy products. Do not map a model name to a tier without current capability and price information.

### Page 21 — What one user costs you

**Deck content.** The slide estimates 20 calls per month for a light user and 200 for a heavy user. It gives cost-per-call bands, says ten times the calls means ten times the cost, and calculates 1,000 signups × 20 calls × $0.005 = $100 per month before payment.

**Lecture interpretation.** The equation is correct under its assumptions: 1,000 × 20 × $0.005 = $100. But the $0.005 per call must be measured or justified; calls can have very different input/output sizes and tools. Ten times the number of calls is ten times the model cost only if the other usage assumptions stay approximately constant.

**Worked example using the dated OpenAI rates on Page 20:** Assume 20 calls per active user per month, 2,000 input tokens and 500 output tokens per call. That gives 40,000 input tokens and 10,000 output tokens per user each month.

| Model | Input cost | Output cost | Model-only total per user/month | At 200 similarly sized calls |
|---|---:|---:|---:|---:|
| GPT-6 Luna | $0.002 | $0.0025 | $0.0045 | $0.045 |
| GPT-6 Sol | $0.04 | $0.05 | $0.09 | $0.90 |
| GPT-6 Astra | $0.20 | $0.25 | $0.45 | $4.50 |

At 1,000 users with the same 20-call workload, the model-only totals would be $4.50, $90, and $450 respectively. These calculations exclude paid tools and every non-model cost. Actual usage and current rates should replace these assumptions.

**Verification note.** This is a worked example, not a product forecast. API prices are per token, not inherently per call. The slide’s $100 example is also valid for its assumed $0.005 cost/call, but that assumed call price differs from this example’s token size and chosen rates. Measure actual tokens, retries, tool calls, and heavy-user usage before setting a free tier.

### Page 22 — Which model, which job

**Deck content.** The slide asks three questions: Is this the core task users pay for? Can the output be slightly worse without users noticing? Is the task simple, repetitive, or rarely seen? It maps answers to frontier, mid-tier, or budget/local models.

**Lecture interpretation.** Convert the questions into an evaluation process:

1. Define what “good enough” means for this feature.
2. Test the low-cost candidate on normal and difficult cases.
3. Check whether errors are visible, reversible, or harmful.
4. Move to a stronger model or add a deterministic check when needed.
5. Keep the chosen model only if it meets the quality and latency bar at an acceptable cost.

Do not route solely by whether the feature is “core.” A core feature with a strict format and safe validation may run on a lower-cost model; a rare feature may still deserve a stronger model if a wrong answer has serious consequences.

**Verification note.** The tier map is a heuristic. Model quality is task-dependent and changes with prompts, context, and tool setup. Validate with the same test set and monitor production performance.

### Page 23 — Practical: cost your idea

**Deck content.** The prompt asks an assistant to estimate cost per user per month from the spec, calls per user, tokens per call, and current model prices, show the heavy user separately, and ask for missing information instead of assuming. The “watch for” warns that an AI may guess prices from training data.

**Lecture interpretation.** This is an estimation prompt, not a substitute for pricing research. Give the model a dated rate card, actual usage logs, and the assumptions you want tested. Ask it to show formulas and totals so the result can be checked. If usage data is unavailable, label it as an assumption and calculate low, expected, and high scenarios.

Make sure the estimate separates:
- input tokens;
- output tokens;
- cached tokens;
- model/tool usage;
- light, typical, and heavy users;
- variable operating cost and fixed monthly cost.

**Verification note.** Do not rely on a model’s memory for live prices. Use the provider’s official rate card, save the date and unit, then compare estimates against the first actual invoices and usage logs.

### Page 24 — Three ways to charge

**Deck content.** The slide compares subscription, usage-based billing, and a lifetime deal. It warns that subscriptions can be exposed to heavy users, usage billing may feel scary, and lifetime deals bring cash now with costs that continue.

**Lecture interpretation.** Match the billing model to how buyers understand and receive value:

- **Subscription:** easy to budget when usage is fairly predictable; set fair-use boundaries if costs vary widely.
- **Usage:** aligns revenue with consumption; show estimates, alerts, caps, or prepaid credits so users are not surprised.
- **Lifetime deal:** may help with initial cash or marketplace discovery; model support and infrastructure over the expected lifetime, and be clear about limits and future maintenance.

Consider a hybrid only if it is understandable: a base plan plus a defined included allowance and transparent overage, for example. Simplicity is valuable, but not if it hides an unprofitable usage pattern.

**Verification note.** The slide’s labels capture common trade-offs, not universal outcomes. Test buyer preferences and calculate expected costs before announcing a plan.

### Page 25 — The real constraint: can two people run it?

**Deck content.** Support, refunds, outages, and abuse land on the founders; every feature adds something that can break. The rule: “If you can’t run it, don’t ship it.”

**Lecture interpretation.** Product scope creates an operational promise. Before launch, define who monitors failures, who handles support, how users report problems, how data is restored, how to disable a broken feature, and how abuse or unexpectedly high use is controlled. Add a small runbook and usage alerts.

A small team can ship a limited beta with clear boundaries. It should not promise 24/7 availability, instant support, or unrestricted usage unless it can provide them.

**Verification note.** “Don’t ship it” is a useful quality gate, but it need not block learning. Use a prototype, demo, or carefully bounded pilot that matches the support capacity. Be clear with users about its status and limits.

### Page 26 — Pick the channel before you build

**Deck content.** Five possible channels are shown:

| Channel | Slide description and examples |
|---|---|
| Search and AI answers | People search for the problem and may find the product; examples named: AgentiSEO and Righted |
| Communities | Find places where likely users talk; examples: Reddit, Facebook groups, Indie Hackers |
| Outreach | Find prospective users individually and contact them; the slide calls this “the lead machine” |
| Marketplaces | Use another company’s audience and rules; example: Feedboss on AppSumo |
| Content | Write material that people search for; examples: Feedboss LinkedIn engine |

The slide says the channel changes the product, price, and spec, and that the next class goes deeper into each channel.

**Lecture interpretation.** Pick a plausible route to the first ten users, not a vague aspiration like “we will use social media.” For each candidate, state who you can reach, what you will do, what value you provide, the time/cash budget, and the signal that would justify continuing.

| Channel | A useful first experiment | Measure |
|---|---|---|
| Search / AI answers | Publish one original page that answers a specific buyer question and clearly explains the product | Qualified visits, signups, and activated users—not impressions alone |
| Community | Answer a real question or share a useful artifact in a relevant group, following its rules | Helpful conversations and permission-based follow-up |
| Outreach | Personally contact a small, well-researched set with a relevant question or offer | Replies, interviews, qualified interest, and opt-outs |
| Marketplace | Review audience fit, fees, listing rules, refunds, and support terms before applying | Qualified buyers, refund rate, support load, net revenue |
| Content | Publish a useful example, analysis, or walkthrough based on real expertise | Saves, qualified discussions, trials, and paid conversion |

AI can help draft, but it cannot manufacture first-hand experience or guarantee reach. Google’s official search guidance says content is evaluated for helpfulness and originality; using automation primarily to manipulate rankings is against spam policies. Do not build a plan around bulk AI pages ranking automatically.

The current public product examples should be treated as leads for further research, not proof that the channel caused success. Search results show a current [Righted](https://www.righted.io/) site for AI visibility and a current [FeedBoss AppSumo listing](https://appsumo.com/products/feedboss/); neither by itself verifies the class’s earlier internal case claims.

**Verification note.** The slide gives no acquisition metrics for the examples. Before investing in a channel, check current platform rules, economics, buyer activity, and whether the product fits how people discover and purchase there.

### Page 27 — Before next class: three things

**Deck content.** Bring three outputs: a one-page spec with out-of-scope items and locked rules; a cost line with the heavy user shown separately; and a channel guess for where the first ten users will come from. The next topic is selling and scaling with one or two people.

**Lecture interpretation.** Make the deliverables evidence-backed:

1. The spec should show the buyer, paid outcome, scope, locked rules, first-run flow, and measurable acceptance criteria.
2. The cost line should show current prices, input/output tokens, actual or labelled assumed calls, paid tools, non-model costs, and heavy-user risk.
3. The channel hypothesis should name a reachable first-ten-user group, a specific experiment, a time/cash budget, and a success or stop rule.

**Verification note.** A channel guess is not a validated acquisition plan. Keep the next step small enough to learn whether the intended users can be reached and whether the message earns a response.

## 7. Guided practical: spec, cost, and channel for a lead pipeline

This exercise turns the example on Page 12 into a product plan. Its purpose is to demonstrate the method; the funnel numbers below are the slide’s estimates, not market facts.

### Step 1 — State the outcome

**Draft job:** “Help a small DTC brand find a reviewable list of candidate businesses that match its stated profile, with evidence attached to every row.”

This description avoids promising that a model can find “perfect leads.” Define what counts as a relevant candidate with the buyer.

### Step 2 — Name user, buyer, and scope

- **User:** the person who researches potential partner or sales accounts.
- **Buyer:** the owner or team lead who pays for time saved or qualified opportunities.
- **First interface:** a spreadsheet, as the slide proposes.
- **First version includes:** source-backed candidate records, defined filters, and a review column.
- **First version excludes:** paid lead databases, auto-sending, LinkedIn/Instagram automation, and a custom UI.

Do not assume that source data may be collected or processed merely because a page is publicly visible. Check the source and tool terms, minimize stored data, and avoid collecting personal contact information unless the product has a documented reason and appropriate process.

### Step 3 — Define “unknown is never pass”

For every criterion, store one of **pass**, **fail**, or **unknown**, plus the supporting evidence:

| Criterion | Evidence required | If evidence is missing |
|---|---|---|
| Domain age is at least two years | Chosen domain-age source and date | Unknown; exclude from qualified export |
| DTC + target category | Page or catalog evidence and category rule | Unknown; send to manual review |
| Price threshold is met | Product and price page, with currency | Unknown; do not infer from a different item |
| No blocker found | Written blocker list and pages checked | Unknown; manual review |
| Variant depth / unit volume | Defined indicators and page evidence | Unknown; do not let the LLM fill the gap |
| Final relevance judgment | Rubric score plus cited evidence | Low-confidence cases go to a person |

### Step 4 — Recalculate and then measure the funnel

The slide’s rough percentages produce about 160 final leads from 50,000 starting domains. To test the estimate, label a sample at each stage and record actual retained counts. Compare the model’s classifications with human-reviewed decisions. Track false positives (bad records incorrectly included) and false negatives (good records excluded).

### Step 5 — Specify the AI judgment

The model may summarize evidence or classify a record against a stated rubric. It must not invent source data, contact a lead, or turn missing evidence into a pass. Store the source URL, checked date, model/prompt version, and confidence or review state. Make the final spreadsheet row easy for a human to inspect.

### Step 6 — Estimate cost

Use the worksheet in Section 5. Record the actual average and high-percentile number of records processed per user, tokens per record, retries, and paid tools. A batch with long websites may cost very differently from a short classification call. Price the heavy user separately and set a cap while actual usage is unknown.

### Step 7 — Choose an initial channel

A plausible experiment could be five short conversations with DTC operators who currently research partners or prospects manually. Show one source-backed sample row and ask them to assess accuracy, usefulness, and workflow fit. Do not start by building a large lead database or sending bulk outreach. Use the evidence to decide whether to refine the ICP, filters, spreadsheet workflow, price, or channel.

### Step 8 — Decide what to learn

After the test, record:

- which fields buyers inspect first;
- which inclusion errors are unacceptable;
- how often they would use the pipeline;
- whether they would pay, and at what unit;
- whether they trust the provenance;
- where the first users were reachable;
- what the observed cost per reviewed record was.

Put decisions in the ledger and unresolved questions in the spec. Do not treat a handful of conversations as proof of broad demand.

## 8. Exercises and assessment

### Exercise 1 — Pick a build route

Choose one feature from your product idea. Rate prototype, AI-assisted code, and custom engineering from 1–5 on speed, control, cost, and required quality. Explain which route best answers your next customer question and what limitation would force you to move up a rung.

**Deliverable:** a short decision table plus one reason to revisit the decision.

### Exercise 2 — Find the assumptions in a vague spec

Start with: “Build an AI assistant that helps small businesses get more customers.” Ask a reviewer model to identify every decision it would have to guess. Classify each as product scope, data, access, output quality, pricing, or failure behavior. Rewrite the spec so the first version has one user, one workflow, one measurable outcome, and explicit exclusions.

**Assessment:** a strong answer quotes the ambiguous text and replaces it with a decision or acceptance criterion.

### Exercise 3 — Create an AI evaluation set

Write five synthetic examples for one AI feature:

1. a routine success;
2. an unusual but valid case;
3. missing information;
4. conflicting evidence;
5. a case that must be declined or escalated.

For each, define expected behavior, prohibited behavior, pass criteria, and how the result will be reviewed.

### Exercise 4 — Encode an invariant

Choose one locked rule, such as “a record without a source is never exported.” Write:
- the rule in plain language;
- the implementation point where it should be enforced;
- a passing test;
- a failing test;
- what the person sees when the record is excluded.

### Exercise 5 — Calculate user cost

Using the Page 21 workload (20 calls, 2,000 input tokens and 500 output tokens per call), reproduce the model-only totals for one current provider rate. Then calculate:
- a 200-call heavy user;
- 1,000 users at the expected workload;
- the effect of doubling average input size;
- the effect of one retry per call.

State what is excluded from the total.

### Exercise 6 — Compare model routes

Select three models from official rate cards. Run the same fixed evaluation examples on each. Record correctness, failure behavior, output format, latency, input/output tokens, and cost. Select the cheapest model that meets your threshold, or specify why a stronger model or a human check is needed.

### Exercise 7 — Choose a pricing model

For a product with variable AI usage, compare monthly subscription, usage billing, and a lifetime deal. Include a typical and heavy user, free-tier limit, refund/support exposure, and the value the buyer receives. Explain how the customer will estimate or control usage charges.

### Exercise 8 — Test a first channel

Name a group of ten likely users that you can reach without buying a large audience. Design a one-week experiment with:
- a specific action;
- useful value offered;
- time and cash budget;
- a response or activation metric;
- a stop/change threshold;
- one thing you will learn even if nobody buys.

**Scoring rubric (10 points):**

| Criterion | Points |
|---|---:|
| User, buyer, and job are specific | 2 |
| Scope and locked rules are explicit | 2 |
| AI feature includes output, failure, and tests | 2 |
| Cost assumptions and heavy-user case are visible | 2 |
| Channel experiment has a measurable learning goal | 2 |

## 9. Exam review

### Key questions with concise answers

**1. Why does the deck require a spec if an AI can generate the product?**  
Because the model needs product decisions and constraints. If the spec omits them, the tool may fill the gap with assumptions that are plausible but wrong for the buyer.

**2. What six items does the slide say belong in a concise spec?**  
What the product does, who it is for, the paid feature, what is out of scope, locked rules, and how success is known.

**3. What four AI-specific items can a normal feature spec miss?**  
A good output, cost per use, behavior when the system is wrong, and accepted examples that can become tests.

**4. Why save a decision ledger if the spec already exists?**  
The spec describes current behavior and scope. The ledger records decisions, rationale, dates, owners, and evidence so later changes do not silently undo earlier choices.

**5. What is a locked rule?**  
A product invariant or prohibition that must remain true across work, such as “unknown is never treated as pass.”

**6. Why can code tests pass while a product decision is violated?**  
The tests may verify that code runs without checking whether current requirements still hold. Add acceptance and regression tests for important product invariants.

**7. What does “delegate the loop, not the call” mean?**  
Give an agent context, a bounded goal, tools, and acceptance checks; let it perform and inspect the work; keep human approval for decisions and external actions.

**8. Why is a second model not proof that generated code or a spec is correct?**  
Models may share errors, misread the source, or agree without evidence. Check against documents, tests, and observed behavior.

**9. How do you calculate token-based model cost?**  
Calculate input tokens and output tokens separately, multiply each by its per-token rate, and add any tools or other metered services.

**10. Why model a heavy user separately?**  
Averages can hide a high-usage customer whose calls, token sizes, tools, or retries make the service much more expensive.

**11. Is local inference free?**  
It may avoid a per-call API charge, but hardware, electricity, deployment, maintenance, and engineering still cost money.

**12. Does the cheapest model always minimize product cost?**  
No. More errors, retries, review work, or customer harm can outweigh a lower token price. Compare total cost at a defined quality threshold.

**13. Why is an AI-written content engine not a guaranteed search channel?**  
Search performance depends on usefulness, originality, and user value. AI use does not guarantee ranking; using automation primarily to manipulate rankings can violate search spam policies.

**14. What are the three deliverables before next class?**  
A one-page spec with exclusions and locked rules; a per-user cost line with a separate heavy-user estimate; and a channel hypothesis for the first ten users.

### Fast recall

- **Spec:** intended product contract.
- **Decision ledger:** why and when a choice was made.
- **Locked rule:** invariant that must not drift.
- **Evaluation set:** fixed representative examples with a scoring rule.
- **Heavy user:** high-usage case for cost and support planning.
- **Channel hypothesis:** a testable route to a specific group of buyers.
- **Human gate:** the point where a person approves a consequential choice or external action.

## 10. Necessary links and sites

### Build tools and project instructions

- [Lovable](https://lovable.dev/) — AI-assisted app building.
- [Lovable documentation](https://docs.lovable.dev/introduction/welcome) — official introduction and product workflow.
- [Claude Code documentation](https://code.claude.com/docs/en/overview) — terminal-based AI coding tool.
- [Claude Code memory and project instructions](https://code.claude.com/docs/en/memory) — how CLAUDE.md instructions are loaded and managed.
- [OpenAI Codex](https://developers.openai.com/codex/) — coding-agent product and documentation.
- [Codex AGENTS.md instructions](https://developers.openai.com/codex/guides/agents-md) — project-level instructions for Codex.
- [Ollama FAQ](https://docs.ollama.com/faq) and [model library](https://ollama.com/library) — local model setup and available models.

### Current model prices and evaluation

- [OpenAI API pricing](https://developers.openai.com/api/docs/pricing) — model, token, cache, and tool rates.
- [OpenAI API models](https://developers.openai.com/api/docs/models) — current model names and capabilities.
- [OpenAI evals guide](https://developers.openai.com/api/docs/guides/evals) — designing repeatable evaluations.
- [Anthropic API pricing](https://platform.claude.com/docs/en/about-claude/pricing) — model, cache, and tool rates.
- [Anthropic model overview](https://platform.claude.com/docs/en/models/overview) — current Claude models and capabilities.
- [Gemini API pricing](https://ai.google.dev/gemini-api/docs/pricing) — official token and tool pricing.
- [Gemini API models](https://ai.google.dev/gemini-api/docs/models) — current model list.
- [DeepSeek model pricing](https://api-docs.deepseek.com/quick_start/pricing) — current model, cache, and token rates.

### Search, content, and first-user channels

- [Google Search guidance on AI-generated content](https://developers.google.com/search/blog/2023/02/google-search-and-ai-content) — quality and spam guidance.
- [Creating helpful, reliable, people-first content](https://developers.google.com/search/docs/fundamentals/creating-helpful-content) — official content guidance.
- [Google Search Console](https://search.google.com/search-console/about) — monitor a site’s search performance.
- [Reddit](https://www.reddit.com/) — communities; read each community’s rules before promoting.
- [Facebook Groups](https://www.facebook.com/groups/) — find relevant user communities.
- [Indie Hackers](https://www.indiehackers.com/) — founder and builder community.
- [LinkedIn](https://www.linkedin.com/) — professional network and content channel.
- [AppSumo](https://appsumo.com/) — software marketplace; review seller terms, fees, refunds, and support requirements.

### Examples named in the slides

- [Righted](https://www.righted.io/) — current public product page; do not treat it as independent proof of the deck’s earlier cost anecdote.
- [FeedBoss on AppSumo](https://appsumo.com/products/feedboss/) — current listing for the channel example. Listing content and deal terms can change.
- The slide names **AgentiSEO** as an example, but the deck does not provide a URL. Verify the intended product before using it as a research source rather than guessing which similarly named service is meant.

## 11. Final takeaways and Class 3 checklist

### Keep these principles

1. AI-assisted coding can shorten work, but the builder remains responsible for product choices, testing, data handling, and operations.
2. Pick a build route based on the next thing you need to learn and the real quality bar.
3. Put the user, paid outcome, exclusions, invariants, and acceptance criteria in a current spec.
4. Give AI features accepted examples, an evaluation rubric, a cost budget, and a failure path.
5. Keep a dated decision ledger and locked rules; verify which documents the active tool actually reads.
6. Delegate bounded work loops and keep human approval for decisions and consequential external actions.
7. Choose models using measured output quality, latency, and complete usage cost—not model labels alone.
8. Measure calls, input/output tokens, tools, retries, and high-percentile users before setting a free tier or price.
9. Include hosting, support, abuse, refunds, and maintenance in the operating-cost picture.
10. Choose one channel experiment that can reach specific first users and teach you something measurable.

### Before the next class

- [ ] **The spec:** one page with what the product does, who it serves, the paid feature, out-of-scope items, locked rules, and success tests.
- [ ] **A cost line:** current source URL and date, tokens and calls per user, model/tool costs, other service costs, and a separate heavy-user estimate.
- [ ] **A channel guess:** where the first ten users may come from, the first action, the value offered, the metric, and the stop/change rule.

The next class is framed as **selling and scaling with one or two people**.
