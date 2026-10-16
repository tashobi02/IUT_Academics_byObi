# Lecture Sheet: From Idea to Buildable Spec

**Topic:** Turning an AI product idea into a narrow, testable, buildable four-week project  
**Source deck:** *Class 11_ From Idea to Buildable Spec.pdf*  
**Deck title:** *From Idea to Buildable Spec*  
**Deck subtitle:** *Engineering the One-Page Solo AI Product*  
**Deck length:** 20 slides  
**Prepared:** 2026-09-28  
**Audience:** Solo builders, undergraduate students, and early product teams  
**Central idea:** Choose one specific user and one valuable job, define the smallest reliable AI-assisted path from problem to outcome, decide how success will be measured, and write down what the first release will not do.

> **How to use this sheet:** It follows the deck slide by slide and adds interpretation, worked examples, implementation checks, exercises, and references. The slide PDF is image-based, so the page notes were reconstructed from OCR and visual review. Deck claims are identified separately from guidance added here. Numerical claims in the slides that lack a cited study are treated as workshop rhetoric or hypotheses, not established facts. Reference links were checked on 2026-09-28.

## 1. Learning objectives

By the end of this lecture, you should be able to:

1. Explain why moving from ideation to implementation requires narrower decisions and explicit trade-offs.
2. Distinguish a demo, prototype, MVP, and production system by what each is meant to prove or serve.
3. Describe a target user in terms of context, trigger, repeated task, current workaround, and stakes.
4. Express a job as a transition from a user’s current state to a useful outcome.
5. Define the user’s first meaningful value event and measure the time and steps needed to reach it.
6. Turn a broad quality ambition into a testable acceptance criterion with a defined dataset, denominator, error threshold, and latency condition.
7. Sketch the minimum data model needed for the core job, including ownership, retention, and evidence links.
8. Create a Will-Not-Build ledger that protects the core workflow while preserving basic security, privacy, and reliability.
9. Defend or revise scope when a plausible feature request arrives.
10. Draft a one-page executable spec and identify the supporting technical documents it depends on.

## 2. The lecture in one page

### From idea to build sequence

~~~text
Choose a user in a real situation
    -> identify the repeated job and current workaround
    -> define State A and the desired State B
    -> choose the smallest AI-assisted path between them
    -> name the first meaningful value event
    -> define testable quality, time, and safety conditions
    -> model only the data the path requires
    -> list exclusions and the reason for each
    -> build, evaluate, observe real use, and revise
~~~

### The four quadrants of the spec

| Quadrant | Question | Minimum answer |
|---|---|---|
| Target persona | Who specifically has the problem? | Role, situation, trigger, frequency, existing workaround, and why the problem matters |
| Job-to-be-done | What progress does the user need? | State A, the core task, and a useful State B |
| Time-to-Aha | How soon does the user reach meaningful value? | The first value event, start and end events, and a measured time/step target |
| Quantifiable success | How will we know the core works? | Dataset, unit of measurement, threshold, error handling, and test procedure |

### Three failure modes highlighted by the deck

| Failure mode | What it causes | Design response |
|---|---|---|
| No specific target user | Requirements and edge cases have no boundary | Pick one reachable user group and interview people in that group |
| No concrete data model | Inputs, outputs, persistence, and ownership stay vague | Sketch the core entities, relationships, identifiers, evidence, and retention |
| Scope creep | Work expands beyond the time and capacity available | Keep a visible Will-Not-Build ledger and require trade-offs for additions |

### Three guardrails

- A one-page spec is a compact decision sheet, not every engineering document the product needs.
- “Binary” acceptance tests make individual outcomes checkable; they do not make overall product quality perfectly binary.
- Fixed time and team size do not make privacy, security, correctness, or accessibility optional. Cut optional features before cutting essential safeguards.

## 3. Before drafting: the stage and its evidence

### Discovery does not end; the work changes

The opening slide says the ideation phase is over and contrasts expansive possibility with ruthless constraint. Treat this as a change in the main work, not a ban on further learning. Before implementation, the team should have enough evidence to make a focused bet. During the build, new evidence may still invalidate the persona, workflow, data assumptions, or value proposition.

A practical readiness check:

- Can you name the user and reach several people like them?
- Have you seen recent examples of the task or workaround?
- Can you describe the result the user wants without naming your AI feature?
- Is there a reason to believe the user will adopt, pay for, or otherwise make room for the product?
- Can one person build a thin version and test it within the timebox?
- Can an incorrect result be detected, corrected, or safely contained?

If the only evidence is “AI could do this,” the product idea is not yet validated.

### A practical build-stage taxonomy

The deck presents four build types. This table is a teaching model, not a universal industry standard.

| Build type | Main question | Data and audience | Quality expectation |
|---|---|---|---|
| Demo | Can we communicate the idea? | Often synthetic or staged data; investors or internal stakeholders | Clearly labeled as a demonstration; should not imply production readiness |
| Prototype | Can the core interaction or technical approach work? | Test, sample, or appropriately permissioned data; selected testers | Useful for learning; rough edges are acceptable if contained and understood |
| MVP | Can a real user get real value from the smallest product? | Real use and real operating conditions, with appropriate permission and controls | Narrow in scope, but dependable on the core task |
| Production product | Can the service operate reliably for its intended market? | Persistent user data and ongoing use | Maintained, monitored, supportable, secure, and designed for failure recovery |

**Important distinction:** An MVP is not a license to ship a knowingly unsafe or unusable system. “Minimum” describes the scope of the product; “viable” still requires a real, useful outcome and an acceptable risk level.

The slide’s “AI tolerance” column is ambiguous. It could mean how much AI error the user or product can tolerate, or how much AI autonomy is allowed. Specify both separately:

- **Error tolerance:** Which errors are acceptable, which need review, and which must block release?
- **Autonomy boundary:** May the AI draft, recommend, edit, publish, or take an external action?

## 4. Core concepts and tools

### 4.1 Write the persona as a situation, not a demographic

The slide contrasts “Marketers who need to write better content” with “B2B SaaS marketers writing daily 300-word LinkedIn hooks based on technical whitepapers.”

The second is more useful because it suggests a task, input, frequency, and context. It is still a hypothesis to verify. A highly specific sentence can sound convincing while describing a group too small or hard to reach. Add evidence about the user’s actual workflow and ability to adopt the product.

A useful persona card:

| Field | Prompt |
|---|---|
| Role and context | What work does this person own, and where does it happen? |
| Trigger | What event makes them start this task? |
| Frequency | How often do they face it, and how much work does it create? |
| Current workaround | What tools, people, templates, or manual steps do they use now? |
| Pain and consequence | What is slow, expensive, risky, frustrating, or frequently delayed? |
| Desired progress | What would they be able to do after the task is complete? |
| Adoption path | Can they try or buy the product? Who else must approve it? |
| Evidence | Which interviews, observed tasks, or records support these statements? |

The deck says a target user is “a highly specific person with a highly specific, repeatable problem that AI can solve.” A useful correction is to begin with a problem that matters to a reachable user, then test whether AI is a suitable part of the solution. Do not force AI into a task that ordinary software, a template, or a better process can solve more safely.

### 4.2 Define the job as progress from State A to State B

The deck’s example:

- **State A — friction:** The user has a raw 50-page PDF and a blank text editor.
- **Core task:** Extract the three core arguments and format them as a thread.
- **State B — resolution:** The user has a formatted, ready-to-publish five-part thread.

This format works because it names the starting condition, the work to be done, and the outcome. Make the result concrete enough that a tester can judge it. For example, “a five-part draft with three source-supported arguments and page references” is easier to inspect than “better content.”

The job is the user’s progress, not the model call. A user may be able to complete the job without AI; AI earns a place if it improves the outcome, time, cost, access, or experience without creating unacceptable risks.

### 4.3 Define “Aha” as an observable event

The deck asks builders to map seconds and clicks from login to the core AI value and gives a 15-second/two-click illustration. That is a useful prompt to remove unnecessary setup. The statement “every additional click halves your active users” is not supported in the deck and should not be used as a general conversion law.

Write down:

1. **Start event:** When does the clock begin? For example, when a user opens the tool, uploads a file, or submits a task.
2. **Value event:** What observable event counts as first value? For example, the user sees a source-linked draft they can edit.
3. **Eligibility:** Which sessions count? Exclude internal staff, bots, duplicate tests, or sessions without a valid input if appropriate.
4. **Measures:** Track median and a tail measure such as the 90th percentile, along with failure and abandonment rates.
5. **Quality guard:** Fast output does not count as value if it is irrelevant, unsupported, or unsafe.

A useful product metric could be: “For eligible first-time users who upload a supported PDF, time from upload completion to first editable, source-linked draft; report median and p90, plus the share who abandon before preview.” The target should come from observation and product needs, not a slogan.

### 4.4 Make success testable without pretending all quality is binary

The slide rejects “high-quality summaries” and gives a more concrete target: extract 100% of financial figures, map them to correct JSON keys, avoid hallucinations, and finish in under four seconds.

The direction is useful: replace vague adjectives with observable tests. The sample target is not yet a complete specification. It needs:

- a definition of a financial figure and its unit;
- a labeled dataset with a known set of expected values;
- a rule for tables, footnotes, ranges, currencies, negatives, and repeated figures;
- a precise meaning of “correct JSON keys” and an allowed schema;
- a definition of hallucination and the consequences of an error;
- a runtime environment and a percentile or pass rate, not just one best-case run;
- an abstention or review path for unreadable or ambiguous values.

“100%” may be appropriate for a narrowly constrained field or a release-blocking critical case, but it is not automatically a credible general goal for messy documents. Avoid implying that one test corpus proves zero risk in every future input.

A better acceptance-test template:

> On **[named, permission-cleared test set]**, for **[defined input class]**, the system must achieve **[metric] ≥ [threshold]**, with **[critical-error condition]**, and **[latency target]** measured at **[specified percentile and conditions]**. Inputs outside the supported class must **[abstain, explain, or route to review]**.

Useful extraction measures include:

- **Field exact-match rate:** correct required fields divided by all required fields tested.
- **Precision:** correct extracted items divided by all extracted items.
- **Recall:** correctly extracted items divided by all items expected.
- **Critical-field success:** share of cases where every designated critical field is correct.
- **Schema-valid rate:** outputs accepted by a schema validator divided by outputs tested.
- **Latency:** median and p90/p95 under a stated file size, provider/model, and test condition.

For generated language, combine measurable checks—required sections, valid evidence references, source support—with human review of usefulness, clarity, and tone. A strict JSON schema can constrain output shape, but it does not establish that the content is true. See the [Structured Outputs guide](https://developers.openai.com/api/docs/guides/structured-outputs) and use a representative [evaluation dataset](https://developers.openai.com/api/docs/guides/evals).

### 4.5 Make the data model small, explicit, and connected to the job

The slide identifies an absent data model as a source of infinite system boundaries. A small initial model for the PDF-to-thread example might include:

| Entity | Minimum useful fields | Why it exists |
|---|---|---|
| User or workspace | user_id, workspace_id if needed, access role | Establishes who owns a document and its result |
| Source document | document_id, owner_id, storage reference, type, size, created_at, retention_status | Tracks the input and its permitted lifecycle |
| Extraction job | job_id, document_id, status, model/prompt version, error code, timestamps | Makes processing state and failures observable |
| Claim or argument | claim_id, job_id, text, source_page, evidence excerpt or location, review status | Connects generated claims back to source evidence |
| Draft segment | segment_id, job_id, order, text, linked_claim_ids, edit status | Stores the five thread parts and their support |
| Feedback or evaluation | evaluation_id, job_id, reviewer outcome, error category, notes, timestamp | Supports learning and quality checks |

This is a conceptual starting point, not a requirement to build six database tables on day one. Combine or omit entities if the initial workflow does not need them. Do not omit ownership, access control, deletion, or evidence lineage merely to make the schema look small.

Before persisting a field, ask: Is it required for the user outcome, reliability, support, safety, or an explicitly planned evaluation? If not, defer it. The data model should also state whether original PDFs are retained, for how long, who can retrieve them, and whether content is included in logs.

### 4.6 Scope is a product decision; safeguards remain

The deck lists custom dashboards, themes, export modules, and multi-tenant roles as features that can kill a small project. These may be reasonable exclusions for a narrow first release. The critical path is the shortest reliable route to the user’s core value, including the technical and safety steps needed to provide that value.

Examples of non-user-facing work that may still be essential:

- access control for private documents;
- basic error handling and retry limits;
- deletion and retention behavior;
- output validation and source references;
- logging that avoids storing sensitive content unnecessarily;
- a way to report or correct a bad result;
- a human confirmation before external publication or irreversible action.

The deck suggests using a “single-user hardcoded login” for an MVP. That should only be an isolated local-development shortcut with synthetic data. Never ship a publicly accessible hard-coded login, and never use it to protect real user data. Use a supported authentication mechanism and check authorization on each resource. OWASP’s [Authentication](https://cheatsheetseries.owasp.org/cheatsheets/Authentication_Cheat_Sheet.html) and [Session Management](https://cheatsheetseries.owasp.org/cheatsheets/Session_Management_Cheat_Sheet.html) guidance are useful starting points.

If users upload documents, file parsing and model input introduce additional concerns: restrict file types and size, validate files, isolate processing, avoid executing embedded content, protect stored files, and consider prompt injection in document text. Consult the [OWASP File Upload Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/File_Upload_Cheat_Sheet.html) and [LLM Prompt Injection Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/LLM_Prompt_Injection_Prevention_Cheat_Sheet.html).

### 4.7 Keep a Will-Not-Build ledger

A non-goal is a deliberate boundary for the current release, not a promise never to build a feature. Good entries record why the feature is deferred, what the user will do instead, and what evidence would justify revisiting it.

| Deferred feature | Why it is out of scope | First-release substitute | Revisit when |
|---|---|---|---|
| Multi-tenant roles and admin dashboard | One verified user workflow is the current learning goal | Private single-user workspace with real access controls | Several teams validate a shared-workspace need |
| Custom settings | No evidence that users need personalization yet | One opinionated default workflow | Interviews show different recurring workflows |
| Theme toggle | No effect on core job validation | One accessible visual theme | User evidence or accessibility review requires changes |
| PDF/Excel export | Export adds format, layout, and compatibility work | Copyable text plus source links | Target users repeatedly need a specific destination format |
| Auto-publishing to LinkedIn | A factual mistake could be published externally | Human reviews and copies the draft | Source support and user approval behavior are tested; publishing permissions are designed |
| Long-term document library | Retention and search add privacy and product scope | Delete input after the job, or use a clearly stated short retention period | Users demonstrate a recurring retrieval need and controls are ready |

A useful feature request review asks:

- Which target user and job does it support?
- Does it improve the first meaningful value event or a validated requirement?
- What is the smallest version of the request?
- What is the effort, dependency, risk, and test cost?
- Which committed item would be removed to make room?
- Is the request a release blocker, a future hypothesis, or merely attractive?

### 4.8 Treat time, capacity, scope, and quality as different constraints

The deck uses an Iron Triangle: one person and four weeks are fixed, so scope must change. This is a useful model for the exercise. In real projects, cost and schedule may also change. For a four-week solo project, scope is often the easiest adjustable variable, but quality and safety must remain above a defined floor.

A sample four-week path:

| Week | Goal | Evidence or artifact |
|---|---|---|
| 1 — Narrow and specify | Confirm the persona and workflow; define the spec, model, acceptance tests, and non-goals | One-page spec, interview notes, supported-input list, test-set plan |
| 2 — Build the vertical slice | Complete one thin path from input to user-visible outcome | Upload or input, core AI step, output view, one happy-path test |
| 3 — Evaluate and harden | Test representative and difficult cases; add errors, review, and access controls | Evaluation results, failure handling, security/privacy checklist, revised scope |
| 4 — Pilot and decide | Let a small, intended user group try the narrow product; observe task success and failure | Pilot notes, baseline comparison, issue list, ship/revise/stop decision |

This schedule is an example, not a promise. Model latency, external APIs, document formats, and account approvals can change the work. If the core workflow is not usable by the end of week two, cut optional scope and re-evaluate the plan.

### 4.9 Use the spec as a front door, with linked support

The one-page constraint is a forcing function for clarity, not a universal rule that every technical detail must fit on one page. Keep the decision sheet compact and link to supporting artifacts where needed:

- data model and data lifecycle;
- API or integration contract;
- prompt and model configuration;
- test corpus and evaluation procedure;
- threat model and access-control notes;
- operational runbook, monitoring, and rollback plan.

## 5. Fillable one-page executable spec

Copy this section and replace the prompts before implementation.

### Product and timebox

- **Working name:**
- **Owner:**
- **Target release or experiment date:**
- **Timebox and team capacity:**
- **One-sentence product promise:**

### Quadrant 1 — Target persona

- **Specific user and context:**
- **Trigger and frequency:**
- **Current workaround:**
- **Cost or consequence of the problem:**
- **Evidence we have:**
- **Assumptions still untested:**

### Quadrant 2 — Job and core loop

- **State A:**
- **User’s job in their own terms:**
- **Smallest product action:**
- **State B:**
- **Human review or action required:**
- **Supported inputs and explicit input limits:**

### Quadrant 3 — Time-to-Aha

- **Start event:**
- **First meaningful value event:**
- **Target median time:**
- **Tail target (p90 or p95):**
- **Clicks or steps before value:**
- **Failure and abandonment events to log:**

### Quadrant 4 — Success and safety

- **Test set and permission/source:**
- **Task-success definition:**
- **Quality metric and target:**
- **Critical error and release-blocking condition:**
- **Latency target and conditions:**
- **Out-of-scope input behavior:**
- **Privacy, access, retention, and deletion rule:**
- **Human approval point:**

### Will-Not-Build ledger

| Feature | Why it is deferred | First-release substitute | Revisit trigger |
|---|---|---|---|
| 1. |  |  |  |
| 2. |  |  |  |
| 3. |  |  |  |
| 4. |  |  |  |
| 5. |  |  |  |

### Definition of ready to test

- The core path works end to end on a supported input.
- The expected result and the known failure behavior are documented.
- The evaluation data is permissioned and representative of the intended input.
- Private data cannot be accessed by another user or exposed through logs.
- The user can review, correct, or reject important AI-generated claims.
- The excluded features and substitutions are visible to the team.
- A person owns pilot feedback and the decision to ship, revise, or stop.

## 6. Worked example: PDF to source-grounded LinkedIn thread

This worked example expands the deck’s marketer scenario. Its targets are illustrative starting hypotheses, not benchmark results or universal standards.

### Persona and evidence to collect

**Candidate persona:** A B2B SaaS marketer who regularly turns long technical whitepapers into short LinkedIn drafts, has limited access to subject-matter experts, and must preserve the source’s meaning.

Before building, interview or observe several marketers. Ask them to show a recent task, how they selected the main claims, where they verified facts, who approved the result, and how much time corrections took. Ask about their current tools and whether they would use a separate product. Do not rely only on hypothetical willingness to use AI.

### State A, core action, and State B

- **State A:** The marketer has a technical PDF, a blank document, and a deadline.
- **Core action:** The tool extracts candidate arguments with page references, then drafts a five-part thread linked back to those arguments.
- **State B:** The marketer has an editable, source-linked draft and can verify the claims before publication.
- **Aha event:** The first preview appears with at least one claim that the user can trace to the source.
- **Human boundary:** The tool drafts only. The marketer approves the factual content and chooses whether to publish.

This version slightly strengthens the deck’s “ready-to-publish” phrasing: a draft should not be considered ready for external publication until a person has reviewed it.

### Initial boundaries

**In scope**

- One user uploads one supported PDF.
- The tool extracts text and proposes three core arguments.
- Each argument includes a page reference and a short supporting excerpt.
- The tool creates five editable thread segments from those arguments.
- Unsupported or ambiguous claims are marked for review.
- The user can copy the draft and delete the source document and result.

**Out of scope**

- Automatic posting or scheduling.
- Multiple social networks or export formats.
- Team workspaces, custom roles, and dashboards.
- Persistent searchable document history.
- Market research, fact checking against the open web, image generation, or brand-voice training.
- Guaranteed performance, engagement, or audience growth.

### Initial success measures

| Measure | Operational definition | Example pilot target | Important limit |
|---|---|---|---|
| Source support | Human reviewers judge each factual claim in the thread against the supplied PDF; count supported claims ÷ all factual claims | At least 95% on the defined held-out corpus | Must define claim segmentation and reviewer procedure; a corpus result is not a universal guarantee |
| Evidence reference validity | Page references point to the page containing the supporting evidence | Every citation in the release test set resolves to the correct page | Does not prove the claim is complete or interpreted correctly |
| Key-argument coverage | Expected key arguments present in the source that appear in the extraction | At least 85% on the labeled test set | Define what counts as a key argument and how omissions are judged |
| Critical failure | A fabricated financial figure, named entity, or direct quote appears without source support | Zero such failures in the release test set; unsupported cases must be flagged | Zero observed failures does not mean zero future risk |
| Structured output | Required JSON fields and five ordered thread segments pass schema validation | 100% schema-valid output on supported test cases, or safe retry/failure | Schema validity checks shape, not truth |
| Time-to-Aha | Time from completed upload to first editable, source-linked preview | Median under 60 seconds on the stated test setup; track p90 too | Tune after measuring realistic PDF sizes and provider latency |
| User task success | Target users can review a draft and identify whether it is usable for editing | At least 4 of 5 pilot participants finish the defined task without help | A small pilot is directional, not statistical proof |
| Data handling | Source document and output follow the declared retention/deletion path | Deletion test passes; access isolation test passes | Security and privacy tests need a broader plan before public launch |

The numeric values above are candidate gates to discuss and test. A team should revise them after inspecting the task, the cost of mistakes, the available test corpus, and the user’s review burden.

### A minimal evaluation set

Build a small, permission-cleared set of example PDFs before tuning prompts. Include ordinary cases and difficult cases, such as:

- clean text PDF with clear headings;
- long paper with repeated claims and summaries;
- tables, footnotes, and charts;
- scanned or low-quality document that should be rejected or OCR-processed;
- contradictory sections or outdated figures;
- document with irrelevant instructions embedded in the text;
- input that lacks three defensible arguments;
- short document or unsupported file type.

For each file, record the expected arguments, evidence pages, critical facts, known ambiguity, and expected product behavior. Keep some examples out of prompt iteration so the final test is not simply the examples used to tune the system. Have a human reviewer define the reference answers and resolve disagreement.

### Lightweight processing design

1. Validate file type, size, and readability.
2. Extract text and preserve page boundaries.
3. Ask the model for candidate arguments, quotes/excerpts, and page references in a constrained schema.
4. Validate the schema and confirm page references are within range.
5. Generate the five-part draft from only the selected, source-linked arguments.
6. Check that draft factual claims map back to source evidence; flag claims without support.
7. Show the draft and evidence side by side.
8. Let the user edit, copy, reject, or delete.
9. Record minimal operational events and evaluation outcomes without retaining sensitive source text unnecessarily.

Structured output can reduce formatting and missing-key errors. It does not replace evidence checks or human review. Uploaded content can also contain misleading instructions; treat document text as untrusted data and limit the model’s privileges and actions.

## 7. Slide-by-slide lecture notes

### Slide 1 — From Idea to Buildable Spec

**Deck content:** “Engineering the One-Page Solo AI Product.”

**Lecture interpretation:** The class moves from selecting an opportunity to defining a build contract. “Buildable” means a small team can identify the user, input, output, boundaries, tests, and release decision without inventing the product while coding.

**Verification note:** “One page” is the deck’s format constraint. A one-page brief should point to, not replace, detailed design or safety documents.

### Slide 2 — The mindset shift

**Deck content:** Block 2 covers discovering problems, validating demand, and finding the single paid feature. Block 3 covers writing the spec, defining the data model, and shipping in four weeks.

**Lecture interpretation:** Discovery creates evidence and options. Execution chooses a focused hypothesis and makes it concrete. “Single paid feature” is a useful business prompt, but not every project has direct payment as its first validation signal; adoption, repeated use, cost reduction, or stakeholder approval may be more suitable.

**Verification note:** The deck’s four-week schedule is an exercise constraint. A real timeline depends on complexity, integrations, data access, approval, and release requirements.

### Slide 3 — The Solo AI Developer’s Paradox

**Deck content:** AI supposedly gives one engineer the output capacity of a ten-person development team; without constraints, this may mean building the wrong thing faster.

**Lecture interpretation:** AI tools can increase the amount of code or prototypes a developer can produce, but they do not remove requirements work, review, integration, testing, debugging, or responsibility. More output is valuable only when the target and acceptance conditions are clear.

**Verification note:** The ten-person multiplier is not evidenced in the slide. Treat it as rhetoric. “Wrong thing faster” is a useful risk metaphor, not a measured law.

### Slide 4 — The taxonomy of builds

**Deck content:** A demo communicates an illusion of magic using fake data and throwaway code; a prototype tests the core mechanic; an MVP seeks the first real value exchange; production aims to support a scalable business. The table also compares target audience and “AI tolerance.”

**Lecture interpretation:** Name the build’s purpose before choosing the architecture. A prototype can use simulated data if it is clearly labeled and appropriate for the question being tested. An MVP should provide real value in a narrow task. Production adds ongoing operations, support, monitoring, access controls, and maintenance.

**Verification note:** The taxonomy is a teaching aid, not a formal standard. “AI tolerance” needs definition: acceptable model error and permitted autonomy are separate design choices.

### Slide 5 — The Failure Trinity of Solo Engineering

**Deck content:** No specific target user leads to impossible edge cases; scope creep dilutes the product; no concrete data model leaves system boundaries infinite.

**Lecture interpretation:** These risks reinforce each other. A vague persona makes it difficult to decide which inputs matter. Unbounded inputs make the data and processing model larger. New features then add workflows before the core path is understood.

**Verification note:** Scope can also be blocked by dependencies, unclear ownership, privacy requirements, or release risk. The triangle is a memorable summary, not an exhaustive root-cause list.

### Slide 6 — Constraint breeds clarity

**Deck content:** The one-page executable spec is presented as a physical constraint enforcing a technical constraint: if the product cannot fit on one page, one person cannot build it in four weeks.

**Lecture interpretation:** Compression exposes competing goals and forces decisions. Use the page to state the bet, boundaries, and acceptance conditions. Put detailed schemas, integrations, and controls in linked supporting material.

**Verification note:** The claim is intentionally absolute for the exercise; it is not a universal software-engineering rule. A complex product may need more than one page even when well-scoped.

### Slide 7 — Anatomy of the executable spec

**Deck content:** Four quadrants: target persona, job-to-be-done, time-to-Aha, and quantifiable success.

**Lecture interpretation:** The quadrants form a compact chain: identify whose problem matters, define the progress they need, make first value reachable, and decide how to test whether the product delivered it.

**Verification note:** Add a data boundary, human-review rule, and non-goals if the page has room; otherwise link them clearly.

### Slide 8 — The ruthless persona

**Deck content:** “Marketers who need to write better content” is too broad; the deck narrows it to B2B SaaS marketers writing daily LinkedIn hooks from technical whitepapers.

**Lecture interpretation:** Specificity helps make the workflow and examples testable. Verify that the group exists, has this repeated need, can be reached, and has a reason to adopt the solution.

**Verification note:** “The problem AI can solve” should be tested after the problem is validated. Do not define the user around the solution you already want to build.

### Slide 9 — Job-to-be-done

**Deck content:** The user begins with a 50-page PDF and blank editor, asks for three core arguments formatted as a thread, and ends with a five-part draft.

**Lecture interpretation:** The input, transformation, and outcome are visible. Add the evidence trail and human review so “ready-to-publish” does not imply unverified factual accuracy.

**Verification note:** The deck’s Gemini Notebook label is a source/tool label in the slide image, not a requirement to use that product.

### Slide 10 — Time-to-Aha compression

**Deck content:** The slide suggests mapping seconds and clicks from login to AI value, claims each extra click halves active users, and marks a 15-second/two-click path.

**Lecture interpretation:** Reduce unnecessary onboarding and instrument a real value event. Measure time and abandonment for the intended users, then compare paths or cohorts if there is enough data.

**Verification note:** The “halves active users” claim is uncited and should not be treated as a conversion formula. The plotted 15-second/two-click point is a design target, not a universal benchmark.

### Slide 11 — Quantifiable success metrics

**Deck content:** The deck contrasts “high-quality summaries” with a test that requires all financial figures, correct JSON fields, no hallucination, and under four seconds.

**Lecture interpretation:** The improved statement is more inspectable, but it still needs a defined corpus, exact scoring rules, supported file sizes, and behavior for ambiguity. Separate structural correctness, factual correctness, latency, and user usefulness.

**Verification note:** Four seconds and 100% accuracy are not evidenced by a test result in the deck. Do not advertise them as achieved performance. Schema-constrained output helps formatting but cannot guarantee factual correctness.

### Slide 12 — Strategy is what you choose not to do

**Deck content:** A solo four-week sprint requires aggressively outlawing features before coding.

**Lecture interpretation:** Write the exclusions early. When new requests arrive, compare them to the user, Aha event, outcome metric, cost, and safety needs. If one enters scope, identify what leaves.

**Verification note:** “Hostile environment” is rhetorical. A timebox is useful for the exercise, but projects should use realistic estimates and respond to new evidence.

### Slide 13 — The iceberg of scope

**Deck content:** The diagram labels roughly 10% “built” above water and 90% “explicitly outlawed” below water.

**Lecture interpretation:** Many attractive ideas do not belong in a first release. Naming those ideas helps resist accidental commitment and makes trade-offs visible to collaborators.

**Verification note:** The 10%/90% split is a metaphor, not a measured ratio of software work.

### Slide 14 — Seductive features that kill

**Deck content:** A feature not on the critical path to Aha should be cut. Examples include multi-tenant roles, custom settings, theme toggles, and PDF/Excel exports. The slide suggests hard-coded single-user login.

**Lecture interpretation:** Defer optional complexity and offer a simple substitute: one default workflow, one theme, copyable text. Preserve minimum controls that protect real users and data.

**Verification note:** Hard-coded authentication is only for isolated local testing with synthetic data. It is not an acceptable public release control. Real document upload also requires access control, file validation, safe processing, and a retention decision.

### Slide 15 — The Iron Triangle of Solo AI

**Deck content:** Time is fixed at four weeks, developer capacity at one person, and scope is the variable to cut.

**Lecture interpretation:** Under this constraint set, protect the single user journey and remove optional work. Keep explicit floors for core task quality, access control, privacy, testability, and recovery from failure.

**Verification note:** The classic project trade-off model is simplified on the slide. Quality and safety cannot be assumed to remain acceptable simply because the team fixed time and scope.

### Slide 16 — The protected core

**Deck content:** The one-page spec sits inside the “Will-Not-Build” ledger; non-goals form armor around the core AI loop.

**Lecture interpretation:** The ledger protects attention, communicates why features are deferred, and makes future scope changes explicit. It should be revisited when evidence changes, not treated as permanent doctrine.

**Verification note:** A non-goal must not hide an essential requirement. Authentication, deletion, evidence display, and error handling may be necessary parts of a safe core.

### Slide 17 — The Forge: Drafting and Defense

**Deck content:** The class has 90 minutes to produce the primary engineering artifact and prepare to defend it.

**Lecture interpretation:** The time limit creates a decision exercise. Participants should leave with a testable spec and be able to explain why the omitted features do not block the learning goal.

**Verification note:** The slide title is visually read as “The Forge: Drafting & Defense.”

### Slide 18 — Step-by-step construction

**Deck content:** Draft the core loop; cut scope in half and remove an assumption; cut it in half again; document the non-goals.

**Lecture interpretation:** Start with the user’s State A and State B. Identify assumptions that drive most of the effort, then test, constrain, or defer them. “Cut in half” is a prompt to challenge scope, not a mathematical requirement.

**Verification note:** Do not remove an assumption by silently ignoring a user need. Use an interview, prototype, file test, or explicit limitation to learn whether it is essential.

### Slide 19 — The defense protocol

**Deck content:** The engineer uses the locked spec and non-goals to reject “just one more feature” and protect the four-week timeline.

**Lecture interpretation:** A defensible answer may be “no,” “later,” or “yes, if we remove X.” Ask who benefits, what evidence supports it, what it costs, and what changes if it is included. Defend the outcome and constraints, not personal ownership of a frozen document.

**Verification note:** “If your spec allows scope creep, you fail” is a workshop rule. In practice, change control should allow evidence-based changes with an explicit trade-off.

### Slide 20 — Workshop artifacts

**Deck content:** Produce a one-page spec containing persona, JTBD, time-to-Aha, and metrics, plus a Will-Not-Build ledger with at least five major exclusions.

**Lecture interpretation:** The two artifacts show both intent and restraint. For AI products, also state supported inputs, evidence behavior, human approval, test data, and privacy/security boundaries.

**Verification note:** Five exclusions are a useful exercise minimum, not a quality score. A small but important set of justified non-goals is better than a long list that hides an unbounded core.

## 8. 90-minute workshop plan

| Time | Activity | Output |
|---|---|---|
| 0–8 min | Pick a real user and recent task; reject broad market labels | Persona candidate and evidence gaps |
| 8–20 min | Write State A, job, and State B | A clear user transition |
| 20–30 min | Identify the first meaningful value event and remove setup | Aha event and candidate time measure |
| 30–45 min | Define the input/output boundary and sketch the data entities | Minimum data model and supported-input list |
| 45–58 min | Write test cases, quality thresholds, critical errors, and latency conditions | Initial acceptance tests |
| 58–68 min | Draft at least five Will-Not-Build entries and substitutes | Scope ledger |
| 68–80 min | Peer defense: challenge the persona, metric, security boundary, and one exclusion | Revised spec |
| 80–90 min | Read the spec aloud and decide what must be learned before coding | Ready-to-build checklist and unresolved assumptions |

### Peer defense prompts

- Can a real person be identified and reached from the persona statement?
- Does the job describe progress, or merely name an AI feature?
- Is the Aha event observable in a product session?
- Can a reviewer reproduce the success score from the test set?
- What happens when the model is uncertain, the file is unreadable, or the source contradicts itself?
- Does any excluded feature contain an essential security or data-protection control?
- What evidence would cause the team to revisit one non-goal?

## 9. Practice and review

### Exercise 1 — Narrow the persona

Rewrite “people who need help with documents” into a persona with a role, context, trigger, frequency, and current workaround. List two pieces of evidence you would seek before building.

**Sample answer:** “A procurement coordinator at a 50–200 person company who receives 20–40 supplier quotes each week, copies prices and delivery dates into a comparison sheet, and asks a manager to review unusual terms.” Evidence could include observing a recent comparison task and inspecting permission-cleared sample quotes and correction history.

### Exercise 2 — Write the transition

For the sample persona, write State A, the smallest useful product action, and State B. Do not name the model or API.

**Sample answer:** State A: the coordinator has several supplier quotes and a blank comparison sheet. Action: extract quoted price, currency, delivery estimate, and stated conditions with source references, then flag missing or conflicting values. State B: the coordinator has a reviewable comparison and can decide which supplier to discuss.

### Exercise 3 — Repair a weak metric

Weak statement: “The AI makes accurate LinkedIn posts instantly.”

Improve it by defining input class, evidence support, a test dataset, a measurable time condition, and a behavior for unsupported claims.

**Sample answer:** “On the permission-cleared held-out set of supported PDFs, at least 95% of factual claims in the generated draft must be judged supported by two reviewers using the written rubric; every page citation must resolve to a page containing evidence. Report median and p90 time from upload completion to preview. If a claim cannot be tied to evidence, mark it for user review rather than presenting it as verified.” The 95% target is illustrative and should be risk-tested.

### Exercise 4 — Defend a feature request

A customer asks for automatic social publishing in week two. Respond using the persona, Aha event, metric, risk, effort, and trade-off.

**Sample answer:** “Publishing is outside this release because our current test is whether marketers can produce a useful, source-supported draft. Automatic posting adds account permissions, error handling, and a higher-impact failure mode. We’ll let users edit and copy the draft. We’ll revisit publishing after evidence shows repeated demand and the evidence-review path works. If it must enter now, we need to remove an agreed feature and add time for permission and failure testing.”

### Exercise 5 — Identify an unsafe shortcut

A teammate proposes one shared hard-coded password so five pilot users can upload client PDFs. What is wrong, and what should change?

**Sample answer:** A shared hard-coded credential does not provide individual access control or accountability and can expose every uploaded file if it leaks. Use an established authentication mechanism, check each user’s authorization on every file, keep pilot access restricted, use permissioned test data, and define retention and deletion. If safe access is not ready, keep the pilot local or use synthetic/non-sensitive documents.

### Short knowledge check

1. What four questions does the executable spec answer?
2. Why is “high-quality output” not an adequate acceptance test?
3. What is the difference between valid JSON and a correct answer?
4. Why is a Will-Not-Build entry stronger when it includes a substitute and revisit trigger?
5. Which product qualities should remain release floors when time and team size are fixed?
6. Is “every extra click halves activation” a universal product law?
7. Why should a generated claim link to source evidence in a document-to-thread tool?
8. What should the product do when a source document is unsupported or ambiguous?

**Answer key**

1. Who has the problem; what progress they need; how soon they reach meaningful value; and how success is tested.
2. It has no operational definition, so different people cannot score it consistently.
3. Valid JSON means the output matches a structure. Correctness means the content is factually and semantically right for the task.
4. The substitute keeps the user’s core task possible, while the trigger ties future work to evidence instead of habit.
5. The necessary quality and safety floors: correct core behavior, protected data, adequate access control, observable failures, and a way to review or recover.
6. No. The deck gives it without a source; measure the product’s own onboarding and activation behavior.
7. The user needs to verify that the draft preserves the source and did not invent claims.
8. It should explain the limitation, abstain where needed, or route the case for review rather than silently returning a confident-looking result.

## 10. Reference library: useful sites and links

These are selected sources for applying the lecture. Use the primary source pages first; product documentation and law can change. Legal links are starting points for checking the current text, not legal advice.

### Product discovery and metrics

1. [Jobs to Be Done Theory — Christensen Institute](https://www.christenseninstitute.org/theory/jobs-to-be-done/) — A framework for understanding the progress people seek in their circumstances.
2. [What Is an MVP? — Lean Startup Co.](https://leanstartup.co/resources/articles/what-is-an-mvp/) — Explains MVP as a way to learn with a minimal product effort.
3. [Measuring the User Experience at Scale — Google Research](https://research.google/pubs/measuring-the-user-experience-on-a-large-scale-user-centered-metrics-for-web-applications/) — Original HEART framework paper and a process for mapping goals to user-centered measures.

### AI evaluation and output design

4. [Working with evals — OpenAI API](https://developers.openai.com/api/docs/guides/evals) — Build repeatable evaluations for model outputs.
5. [Evaluation best practices — OpenAI API](https://developers.openai.com/api/docs/guides/evaluation-best-practices) — Design an evaluation that matches the application and task.
6. [Structured model outputs — OpenAI API](https://developers.openai.com/api/docs/guides/structured-outputs) — Constrain output to a schema; use alongside semantic and evidence checks.
7. [NIST AI Risk Management Framework: Generative AI Profile](https://www.nist.gov/publications/artificial-intelligence-risk-management-framework-generative-artificial-intelligence) — Risk-management guidance across the generative AI lifecycle.
8. [NIST AI RMF Playbook](https://airc.nist.gov/airmf-resources/playbook/) — Suggested actions and documentation aligned to the AI RMF.

### Security, uploads, and privacy

9. [OWASP Top 10 for Large Language Model Applications](https://owasp.org/www-project-top-10-for-large-language-model-applications/) — Common LLM application risks and mitigations.
10. [OWASP LLM Prompt Injection Prevention Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/LLM_Prompt_Injection_Prevention_Cheat_Sheet.html) — Practical controls for treating user and document input as untrusted.
11. [OWASP File Upload Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/File_Upload_Cheat_Sheet.html) — File validation and safer upload handling.
12. [OWASP Authentication Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Authentication_Cheat_Sheet.html) and [Session Management Cheat Sheet](https://cheatsheetseries.owasp.org/cheatsheets/Session_Management_Cheat_Sheet.html) — Authentication and session-control guidance.
13. [Bangladesh Personal Data Protection Act, 2026 — official legislation portal](https://bdlaws.minlaw.gov.bd/act-print-1692.html) — Consult the current official text and applicable rules if operating in Bangladesh.
14. [Bangladesh Cyber Security Act, 2026 — official legislation portal](https://bdlaws.minlaw.gov.bd/act-print-1710.html) — Consult the current official text and qualified local guidance for applicable requirements.

## 11. Closing checklist

Before writing the first production-minded implementation, confirm:

- The persona is specific, reachable, and supported by real evidence.
- State A and State B describe a useful user outcome.
- The first value event is observable and can be timed.
- Success tests define inputs, labels, scoring, thresholds, and critical errors.
- The model’s output is grounded in evidence where the task requires it.
- Uncertain or unsupported cases have a safe behavior.
- The data model has clear ownership, access, retention, and deletion rules.
- The first release has no automatic external action unless it is necessary and safely controlled.
- The Will-Not-Build ledger has at least five real trade-offs, each with a substitute and revisit trigger.
- Security and privacy requirements have not been removed to meet the timebox.
- A small pilot will measure task success, quality, time, and failure—not just usage.
- The team knows what evidence would lead it to ship, revise, or stop.

> **Class takeaway:** Ideation creates options. A buildable spec turns one evidence-backed option into a bounded path, defines how it can fail, and makes clear what the first release deliberately leaves out.

