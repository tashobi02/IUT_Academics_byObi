# Applied AI in the Wild

## Lecture sheet: a blueprint for industrial automation and product building

**Source:** `Applied_AI_Blueprint.pdf`  
**Coverage:** 15 raster-image slides  
**Audience:** IUT undergraduate students, especially students preparing to build and ship software in industry  
**Prepared:** 2026-09-15

> Central idea: useful industrial AI is not mainly about asking a chatbot clever questions. It is about connecting messy information to a reliable workflow: ingest the information, extract structure, apply explicit rules, take a useful action, and keep a human responsible for important decisions.

## 1. Learning objectives

By the end of the lecture, a student should be able to:

- Explain the difference between a foundation model, an AI application, and an agentic workflow.
- Translate a messy business task into the five-step automation loop.
- Select a promising first automation using the repetition-logic-friction heuristic.
- Design a structured output schema with evidence, confidence, and an exception path.
- Explain why context, source documents, fresh task boundaries, style examples, and adversarial review improve AI results.
- Describe a practical architecture for invoice matching, contract review, content generation, and message-to-database workflows.
- Evaluate an automation using accuracy, false-negative rate, human review rate, latency, cost, auditability, and safety.
- Distinguish a useful prototype from a production system.

## 2. One-page lecture summary

### The problem

Many businesses still operate through a mixture of email, WhatsApp, spreadsheets, PDFs, voice notes, handwritten forms, legacy exports, and manual reports. The data is available, but it is scattered and difficult to read consistently.

The human cost is predictable:

- Repeated report construction.
- Several people checking routine records.
- Orders and requests hidden in message history.
- Expired licenses, contracts, or certificates discovered too late.
- Experts spending their time reading and copying information instead of making decisions.

### The proposed shift

AI is presented as a very well-read intern. It can read large amounts of material quickly, but it does not automatically understand a particular company's policies, data quality, authority, or risk tolerance. The surrounding system must provide context, rules, permissions, verification, and human accountability.

### The universal automation loop

1. **Information arrives.** Read data where it already exists: email, WhatsApp, sensor streams, PDFs, spreadsheets, audio, or legacy systems.
2. **AI reads it.** Extract entities, fields, intent, relationships, and evidence from the raw material.
3. **Rules decide.** Apply business logic, thresholds, validation, policy checks, and routing rules.
4. **Something happens.** File, update, notify, respond, create a task, quarantine an item, or produce a dashboard.
5. **A person approves.** Humans review exceptions and sign off on consequential actions.

This can be summarized as:

`messy inputs -> extraction -> deterministic rules -> action -> human review and audit`

### The first-use-case heuristic

Start with a task where all three conditions are present:

- **Repetition:** the same task happens frequently.
- **Logic:** there is a reasonably clear correct or incorrect outcome.
- **Friction:** people dislike the task or make mistakes when tired.

The best first project is usually a boring, high-volume, measurable task with a low-to-moderate risk profile and a clear exception path.

## 3. Slide-by-slide lecture notes

## Slide 1 - Applied AI in the Wild

### What the slide shows

The opening slide presents an AI engine between unstructured inputs and structured operational outputs.

**Input sources shown:**

- WhatsApp messages.
- Sensor data input.
- Unstructured logs.
- Client feedback, including audio.
- PDF documents.
- Legacy system exports.
- Manual reports.

**Output examples shown:**

1. **Intelligent process output:** a JSON-like result with `status: success`, a processed efficiency score of about `98.5`, `anomaly_detected: false`, no predicted downtime, optimization actions such as `adjust_pressure` and `reroute_workflow`, a timestamp, source `AI_ENGINE_V2`, and version `1.2.0`.
2. **Structured data schema:** product ID `P10-90210`, issue `defect_detected`, location `assembly_line_2`, action `quarantine`, confidence score `0.99`, and processing time of `45 ms`.
3. **High-fidelity dashboard:** system efficiency of `98.5%`, real-time anomaly detection, optimization gains for energy savings, time reduction, and output increase, plus live alerts for predictive maintenance, quality control, and supply chain status.

The slide credits **Minhaz-Us-Salakeen Fahme, CEO, Battery Low Interactive and FeedBoss**.

### Lecture interpretation

The important transformation is not “text becomes a number.” It is:

`human and machine observations -> machine-readable representation -> business decision -> visible operational result`

Structured output is valuable because other software can validate and use it. A dashboard alone is not automation; it becomes automation when the result can trigger a controlled next step.

### Engineering translation

A production result should normally contain more than the slide's simplified JSON:

```json
{
  "status": "success",
  "source_id": "message-or-document-id",
  "extracted": {
    "product_id": "P10-90210",
    "issue": "defect_detected",
    "location": "assembly_line_2"
  },
  "decision": {
    "action": "quarantine",
    "needs_human_review": true
  },
  "confidence": 0.99,
  "evidence": [
    {"source": "inspection-report.pdf", "page": 3}
  ],
  "created_at": "2026-09-15T00:00:00Z"
}
```

The additional fields make the result auditable and safer to operate.

## Slide 2 - The manual grind versus the AI alternative

### What the slide says

The slide introduces **Kamal Bhai**, a business owner with 40 staff and 18 years in business who still works past 6 PM. The manual examples are:

- Rebuilding the 900th manual report by hand.
- Three people checking one invoice and finding nothing wrong.
- An order buried in 340 unread WhatsApp messages.
- A factory license discovered 11 days after expiration.

The proposed automated Tuesday is:

- A report writes itself overnight from scattered data.
- Only mismatched invoices reach a human desk.
- WhatsApp orders populate the master sheet automatically.
- A license flags itself 60 days before expiration.

The closing message is: **the factory's way of working did not change; the reader changed.**

### Lecture interpretation

The opportunity is often not a new product or a complete enterprise transformation. It is a reading, classifying, checking, or routing bottleneck.

The right question is not “Where can I add AI?” It is:

> Which recurring information-handling step consumes skilled human attention without requiring much human judgment?

### Worked example: license monitoring

Suppose each license record contains a name, expiry date, owner, and issuing authority.

1. Read records from a spreadsheet or document repository.
2. Normalize dates and identify the responsible owner.
3. Compute `days_until_expiry`.
4. If the value is below 60 days, create an alert and task.
5. Keep a person responsible for confirming renewal.

This is a good first automation because the rule is explicit, repetition is high, and the benefit is measurable.

## Slide 3 - The speaker's bridge from theory to shipping

### What the slide says

The speaker presents a progression:

- **The Foundation:** IUT alumnus, CSE 2016, CGPA 3.64, First Class, learned the theory.
- **The Builder:** Founder and CEO of Battery Low Interactive, a pioneering XR studio with 300+ global projects and shipped software.
- **The Global Perspective:** US State Department Professional Fellow, author of *How to Make a Game*, and President of IGDA Bangladesh.
- **The AI Era:** CEO of FeedBoss AI, shipped a complex AI SaaS product in three months, and is learning to automate.

The message to students is that four years of learning how to build should lead to the ability to automate and ship real industrial products.

### Lecture interpretation

This is a professional-development slide, but it also introduces the lecture's standard of evidence: theory matters, yet a system is not real until it works in an operational context.

The slide visually repeats “Professional” in the phrase about the US State Department fellowship. The intended reading is **US State Department Professional Fellow**; this is a slide typo, not a separate qualification.

### Discussion prompt

Ask students to name one concept they learned in a course and one real workflow where that concept could reduce manual effort. Examples include databases and spreadsheet reconciliation, networking and message ingestion, software engineering and approval workflows, or statistics and anomaly detection.

## Slide 4 - Models and agents

### What the slide says

AI is described as the world's best-read intern:

- It has read a great deal of written material.
- It knows nothing about a specific business unless context is supplied.
- It does not become bored or tired.

The slide contrasts:

- **Model:** answers when asked, like a consultant waiting for the next question.
- **Agent:** has a job and does it, like a junior employee who receives a task and rules once and runs the process repeatedly.

The slide's thesis is that industry is shifting from models that answer to agents that do.

### Formal distinction

- A **model** is a learned function that maps inputs to outputs. In an LLM application, it may generate text, classify content, extract fields, call tools, or produce structured data.
- An **agentic workflow** is a system around one or more models that includes goals, state, tools, control flow, permissions, memory, retries, and stopping conditions.
- An **agent** is not merely a model with a human-sounding prompt. The agentic behavior comes from the orchestration and the allowed actions.

### Important qualification

The intern analogy is useful but not literal. Models do not automatically know a company's truth, and agents do not deserve unrestricted access simply because they can operate autonomously. A safe agent needs narrow permissions, explicit tools, validation, limits, monitoring, and human approval for high-impact operations.

## Slide 5 - The AI model matrix

### Matrix presented in the deck

| System | Role presented | Suggested use |
|---|---|---|
| ChatGPT / OpenAI | Generalist baseline | Marketing, content generation, and everyday use; safest first choice in the deck |
| Claude / Anthropic | Deep thinker | Long-document analysis, writing in a particular human voice, and heavy coding workflows |
| Gemini / Google | Ecosystem native | Workflows for clients already using Google Workspace; large document folders and audio briefings |
| Perplexity | Verified researcher | Real-time research with citations when source visibility matters |
| DeepSeek | High-volume engine | Cost-efficient simple, repetitive extraction at large scale |

### How to teach the matrix correctly

Treat it as a time-sensitive starting hypothesis, not a permanent ranking. Model names, prices, context windows, latency, policies, and tool support change. A serious comparison should benchmark the actual task using:

- Field-level extraction accuracy.
- Reasoning or classification accuracy.
- Citation correctness and source coverage.
- Latency and throughput.
- Cost per document or task.
- Reliability and rate limits.
- Privacy, data retention, and residency requirements.
- Integration with the customer's existing systems.
- Ease of evaluation and observability.

The practical rule from the slide is still useful: pick one API, build with it for a month, measure it on representative examples, and only then judge its technical limits.

### A useful evaluation table

| Criterion | Question |
|---|---|
| Accuracy | Does the system produce the right answer on the real data distribution? |
| Robustness | What happens when the document is incomplete, noisy, or adversarial? |
| Cost | What is the cost per item at the expected volume? |
| Latency | Can the user wait for the result? |
| Safety | What happens when the system is uncertain or wrong? |
| Maintainability | Can a developer update rules, schemas, prompts, and connectors? |

## Slide 6 - The universal pipeline of enterprise automation

### Five steps in the deck

1. **Information arrives:** data enters wherever it already lives, such as email or WhatsApp. The user should not have to re-enter it.
2. **AI reads it:** the system ingests the material as-is. The slide says “absolutely no cleanup required.”
3. **Your rules decide:** a developer writes the business logic once, and the engine applies it consistently.
4. **Something happens:** the system flags, files, replies, or alerts.
5. **A person approves:** a human reviews an exception or signs the consequential output.

The slide emphasizes that AI does the reading while a human does the signing.

### Engineering interpretation

The pipeline is better written as:

`ingest -> parse and extract -> validate -> apply rules -> act -> review -> record evidence`

The slide's “no cleanup” wording is a persuasive simplification. A pilot can avoid a large ERP migration, but it still needs adapters, validation, duplicate handling, access control, schema decisions, provenance, and error handling. Data cleanup has not disappeared; much of it has moved into the ingestion and validation layer.

### Human-in-the-loop design

Human review should be triggered by conditions such as:

- Low confidence.
- Missing required fields.
- Conflicting source documents.
- A rule violation.
- A high-value transaction.
- An irreversible action.
- A new pattern not covered by tests.

## Slide 7 - Why AI fails in practice

### Failure modes and 30-second fixes

| Failure mode | Typical result | Quick engineering fix |
|---|---|---|
| Zero context | Generic, robotic advice | Name the exact supplier, order number, data, and desired outcome |
| Business blindness | Confident but wrong pricing or policy answer | Attach real source documents such as price lists, policies, and recent quotes |
| Endless chat history | Irrelevant old context leaks into a new task | Start a fresh task boundary; design the API call as stateless unless memory is deliberate |
| Generic blog tone | Messages such as “Dear Valued Customer...” | Supply a profile and examples of the actual historical writing voice |
| AI as a yes-man | Terrible ideas receive polished approval | Ask for a counterargument and five concrete failure reasons |

### The deeper engineering lessons

- **Prompting:** state the task, constraints, format, audience, and failure behavior.
- **Grounding:** give the system access to authoritative source material and require evidence.
- **Task boundaries:** do not let unrelated old context silently influence a new decision.
- **Style transfer:** use representative examples, not a vague instruction such as “sound human.”
- **Adversarial review:** explicitly ask the system to find contradictions, missing assumptions, and failure cases.
- **Evaluation:** compare versions against a fixed test set instead of judging quality by one impressive demo.

### Example of an evidence-aware instruction

> Extract the invoice number, supplier, total, currency, and purchase-order number. Return JSON matching the schema. For every extracted field, include the source page or message ID. If a field is absent or conflicting, return `null` and set `needs_human_review` to `true`. Do not infer a missing value.

## Slide 8 - Mid-scale automation: accounts check themselves

### What the slide shows

The slide shows a spreadsheet with 400 line items entering an **AI Verification Engine**. The engine automatically matches the items against master purchase orders in seconds. Only two mismatches are routed to a human. The work that used to consume one person's Thursday becomes a short exception review.

### Reference architecture

1. Read invoice or expense rows from the source sheet.
2. Normalize supplier names, dates, currency, units, and identifiers.
3. Match each row to the relevant purchase order.
4. Compare quantity, price, tax, total, and approval status.
5. Produce a match score and evidence for the decision.
6. Route only uncertain or mismatched rows to a person.
7. Write the result and reviewer decision to an audit log.

### Metrics to measure

- Mismatch precision: how many flagged rows are genuinely wrong?
- Mismatch recall: how many real mismatches were caught?
- False-negative rate: how many bad invoices passed automatically?
- Human review rate: what fraction needed manual attention?
- Processing time and cost per invoice.
- Amount of money or risk protected.

The headline “only two mismatches” is useful as an illustration, not a guarantee. In finance, false negatives are often more serious than a high review rate.

## Slide 9 - Mid-scale automation: 60 pages in, 1 page out

### What the slide shows

The slide presents a contract stack and says **61 pages read in 74 seconds**, even though the title says “60 pages in, 1 page out.” The system extracts variables and flags non-standard deviations.

The example output says:

- Parties and key dates were extracted and verified.
- **Clause 14.2:** auto-renews for three years, while the company standard is 60 days.
- **Clause 9.1:** late-delivery penalty is uncapped; no ceiling clause was found.

The slide explicitly says that no legal advice is given and no judgment is replaced. The machine does the reading so the human can do the thinking.

### Safe contract-analysis workflow

- Extract clauses, dates, parties, obligations, thresholds, and exceptions.
- Attach page, paragraph, or line evidence to every claim.
- Compare extracted variables against a versioned company playbook.
- Display deviations with confidence and the exact source location.
- Require a qualified human to interpret and approve the result.

### Why evidence matters

“The contract renews for three years” is not enough. A reviewer needs to see where the statement came from, whether an amendment supersedes it, and whether the extraction is reliable. The system should never turn a missing clause into a confident assertion.

## Slide 10 - Enterprise-scale examples

### Examples presented in the deck

**Law:** A&O Shearman and Harvey are presented as equipping 4,000 lawyers, reducing contract-reading time by 30%. The message is that lawyers were not necessarily removed; routine reading was reduced.

**Banking:** JPMorgan's COIN system is presented as reading 12,000 agreements in seconds and saving 360,000 human hours. Routine extraction is automated and people see exceptions.

**Healthcare:** ambient scribes are presented as listening to consultations, drafting clinical notes, and saving 16 minutes per doctor per shift. The doctor reviews and signs.

### General lesson

Large organizations often begin by automating one high-volume, boring, well-bounded task. They do not need to transform every department at once.

### Evidence and qualification

- The JPMorgan figures have an official source: the 2016 JPMorgan Chase annual report letter describes COIN extracting 150 attributes from 12,000 annual commercial credit agreements in seconds, compared with as many as 360,000 hours of manual review per year.
- The official A&O Shearman and Harvey pages support the 30% contract-review time reduction, but the current public customer material does not cleanly verify the deck's “4,000 lawyers” figure. Treat that number as a slide claim until the speaker supplies a primary source.
- Contemporary ambient-scribe reporting describes about 16 fewer documentation minutes per eight hours of scheduled patient care in one multi-site study. That is more precise than treating “16 minutes per shift” as a universal result.
- Healthcare documentation is safety-critical. A clinician must review, correct, and sign the note; the system must protect patient data and preserve an audit trail.

## Slide 11 - The “no cleanup” paradigm shift

### What the slide shows

The slide shows messy sources: Google Sheets, WhatsApp voice notes, tags, handwritten slip numbers, and random documents. It claims:

- An ERP is not required to start.
- Data does not need to be pristine or normalized before a pilot.
- Messy data can remain where it is.
- Modern AI can read the mess.
- The AI engine reads the sources as-is.
- Clean output can be structured JSON, a dashboard, or a normalized database-like table.

### Correct interpretation

“No cleanup” should mean **no big-bang migration before learning whether the use case works**. It should not mean “no data engineering.” A real system still needs:

- A data contract and output schema.
- Validation and type checking.
- Duplicate and conflict handling.
- Access permissions.
- Source provenance and retention rules.
- Confidence thresholds and exception routing.
- Observability, replay, and audit logging.

This is a useful product strategy: start with adapters around the existing workflow, learn from real exceptions, and only later decide whether a system-of-record migration is justified.

## Slide 12 - The FeedBoss architecture

### Layers and callouts shown

The deck presents FeedBoss as a complex AI workspace with the following layers:

- **Ingestion Layer:** reads user history, voice notes, and PDFs autonomously.
- **Spatial Layer:** a small raster caption is garbled and cannot be transcribed confidently. The visual appears to describe an intermediate workspace or state layer; the exact wording should be checked against the original source.
- **Carousel Layer:** a small caption is also garbled; the intended meaning appears to be designing LinkedIn carousel visuals.
- **Output Layer:** generates formatted carousels, videos, and multi-platform posts.
- **Persona Engine:** matches an author's voice DNA with a claimed 96% accuracy.
- **Feedback Loop:** learns from human edits in real time and is claimed never to make the same mistake twice.

The bottom message is that this is not just one API call, but a system of 24 tools engineered into one workspace to replace parts of a content team.

### Architecture interpretation

The useful abstraction is:

1. Knowledge and history ingestion.
2. A persistent workspace or state layer.
3. Persona and style representation.
4. Generation and design tools.
5. Output adapters and publishing channels.
6. Feedback, evaluation, and observability.

### Production qualifications

- “96% voice match” needs a defined benchmark: agreement with whom, on what test set, and measured how?
- “Never makes the same mistake twice” is not a safe engineering promise. Feedback should be versioned, tested, and reversible.
- Human approval should remain in the publishing path, especially for public or brand-sensitive content.
- The system should distinguish user-provided facts from generated suggestions.
- A multi-tool agent needs least-privilege permissions, rate limits, idempotency, retries, and clear failure states.

## Slide 13 - From viral post to shipped product in 30 days

### What the slide says

The slide gives a signal-to-product story:

- **Signal:** a post asking, “What if we gifted AI credits for weddings and breakups instead of blenders?” reached 252,000 views and 75,000 engaged people in seven hours.
- **Build:** wrap a Claude API in a giftable consumer experience with secure Stripe checkout, unique redemption codes, and automated email delivery.
- **Product:** Boon shipped in four weeks.

Use cases include a graduation edge, a breakup thought-partner, and a wedding assistant. The closing idea is that modern AI lets a founder move from a half-formed thought to a live, monetized product in weeks.

### The repeatable product loop

`signal -> narrow prototype -> payment and access control -> fulfillment -> live product -> measure and iterate`

The hard parts are not only the model call. They include product scope, authentication, payments, redemption, data handling, abuse prevention, support, monitoring, and unit economics.

### Critical distinction

Viral attention is a signal, not proof of a sustainable business. A founder must separately test:

- Will users pay?
- Do they complete the experience?
- Do they return or recommend it?
- What is the cost of each AI interaction?
- What happens when the model produces unsafe, insensitive, or incorrect output?
- Are the payment, privacy, and platform terms satisfied?

## Slide 14 - The automation heuristic

### The three-way test

Automate a task when all three are true:

- **Repetition:** it occurs again and again.
- **Logic:** a clear right or wrong answer exists, or the decision can be expressed through rules.
- **Friction:** humans dislike it or make errors when tired.

The center of the Venn diagram is **AUTOMATE THIS**.

The slide advises students not to start with the most important task in the business. Start with the most boring one.

### Why the heuristic works

Repetition creates return on investment. Logic makes evaluation possible. Friction creates adoption and a clear reason to improve the process.

### Extra filters for a first project

Prefer tasks with:

- High volume.
- Stable inputs.
- Explicit rules.
- Low-to-moderate consequence of an error.
- A measurable baseline.
- A human exception path.
- A bounded integration surface.

Avoid beginning with fully autonomous decisions involving safety, employment, credit, medical treatment, legal rights, or irreversible financial actions.

## Slide 15 - Find one task this week

### The assignment shown

- Enter your industrial training.
- Look for the “Kamal Bhai” problems.
- Find the manual grind.
- Apply the five-step loop.
- Build the solution.

The QR code includes the text **Minhaz-Us-Salakeen Fahme**, the message **“Let's build the next generation of tech from IUT,”** and **“Scan to WhatsApp me.”** The QR target itself was not machine-readable from the provided raster using the available local decoding tools. Use the public contact links in the resource section rather than guessing a WhatsApp URL.

### Suggested student deliverable

Submit a one-page automation proposal containing:

1. The current manual task and who performs it.
2. The number of occurrences per day or week.
3. Three common input examples.
4. The expected structured output schema.
5. The deterministic business rules.
6. The action the system may take.
7. The cases that require human approval.
8. A baseline and target metric.
9. A failure mode and mitigation.
10. A small demo using synthetic or authorized data.

## 4. A practical implementation blueprint

### Step 1 - Observe before automating

Shadow the person doing the task. Record the inputs, sequence of decisions, exceptions, handoffs, and final outputs. Do not assume the written procedure matches reality.

### Step 2 - Collect a representative test set

Start with 20-50 real or safely anonymized examples, including difficult cases. Separate development examples from a small holdout set used only for evaluation.

### Step 3 - Define the schema and evidence contract

Specify required fields, types, allowed values, null behavior, confidence, source locations, and human-review conditions. A schema is an interface between the AI output and the rest of the software.

### Step 4 - Separate probabilistic extraction from deterministic decisions

Let AI handle fuzzy reading, transcription, classification, and extraction. Use ordinary code for arithmetic, thresholds, joins, permissions, dates, and irreversible actions.

### Step 5 - Add the exception path first

Every automatic decision needs a clear way to say:

`I do not know -> show evidence -> ask a person -> record the correction`

### Step 6 - Evaluate before expanding scope

Track accuracy, false negatives, false positives, review percentage, processing time, cost, and user effort. Expand only after the baseline improves on the holdout set.

### Step 7 - Operate it like software

Add authentication, authorization, secrets management, logs, retries, idempotency, rate limits, alerting, versioned prompts and rules, rollback, and data-retention controls.

## 5. Worked mini-projects

### A. WhatsApp order to master sheet

| Component | Design |
|---|---|
| Input | Customer text or voice message |
| Extraction | Product, quantity, delivery date, customer ID, and special instructions |
| Validation | Product exists, quantity is positive, required fields are present |
| Rule | High-value or ambiguous orders require review |
| Action | Create a draft row and notify the sales owner |
| Human check | Confirm price, availability, and final submission |
| Metrics | Field accuracy, order-entry time, missed orders, review rate |

### B. Invoice and purchase-order matcher

| Component | Design |
|---|---|
| Input | PDF invoice, spreadsheet line items, purchase-order records |
| Extraction | Supplier, invoice ID, line items, quantity, unit price, tax, total |
| Normalization | Supplier aliases, currency, units, dates, identifiers |
| Rule | Compare quantities, prices, totals, and approval status |
| Action | Auto-route matches; flag exceptions |
| Human check | Resolve mismatches and approve payment |
| Metrics | Mismatch recall, false-negative rate, review rate, hours saved |

### C. Contract deviation report

| Component | Design |
|---|---|
| Input | Contract and company playbook |
| Extraction | Parties, dates, renewal, liability, penalties, termination, governing law |
| Rule | Compare each field with approved standards |
| Action | Produce a one-page exception report with evidence |
| Human check | Lawyer or authorized reviewer decides what to negotiate |
| Metrics | Extraction accuracy, citation accuracy, review time, missed deviations |

### D. License-expiry monitor

| Component | Design |
|---|---|
| Input | Spreadsheet, scanned certificate, or PDF register |
| Extraction | License number, owner, category, expiry date |
| Rule | Alert at 60, 30, and 7 days; escalate overdue items |
| Action | Create tasks and send a notification |
| Human check | Confirm renewal status and close the alert |
| Metrics | Expired items caught, false alerts, time to renewal, overdue count |

## 6. Exam-oriented quick reference

### Definitions

| Term | Exam-ready definition |
|---|---|
| Foundation model | A broadly trained model that can be adapted to many downstream tasks through prompting, fine-tuning, tools, or retrieval |
| LLM application | Software that uses a language model as one component inside a larger product or workflow |
| Agentic workflow | A controlled system that combines a model with goals, state, tools, control flow, permissions, and stopping conditions |
| Grounding | Supplying or retrieving relevant source material so an output can be tied to evidence |
| Structured output | A machine-readable result conforming to a defined schema, such as JSON with required fields and types |
| Rules engine | Deterministic code or policy logic that applies explicit conditions and actions |
| Human-in-the-loop | A design in which a person reviews, approves, corrects, or can override system output |
| Exception path | The route for uncertain, invalid, conflicting, or high-risk cases |
| Evaluation set | Representative examples with expected answers used to measure system quality |
| Audit trail | A record of input, output, evidence, rules, model version, reviewer decision, and timestamps |

### Short-answer questions

1. Why is a model not the same thing as an agent?
2. Explain each step of the five-step enterprise automation loop.
3. Why is “no cleanup required” an overstatement?
4. Give one example where deterministic code should be used instead of an LLM.
5. How can a system reduce human review without increasing dangerous false negatives?
6. What evidence should a contract-extraction system return?
7. Why are fresh task boundaries useful in an API-based workflow?
8. What makes a task a good first automation candidate?
9. Propose two metrics for the invoice-matching system and explain what each catches.
10. Why are viral views insufficient evidence that a product has product-market fit?

### Design question

> Design an AI system that reads incoming purchase requests and creates draft purchase orders. Identify the input channels, extraction schema, validation rules, action, human approval conditions, logs, and evaluation metrics.

A high-quality answer separates probabilistic reading from deterministic validation and does not allow the model to submit an irreversible order without authorization.

## 7. Necessary links and sites

Links were checked on 2026-09-15. Model capabilities, pricing, URLs, platform policies, and product features can change; use the official documentation as the current authority.

**Source labels:** the model, integration, workflow, and governance sections are official documentation or standards resources; the enterprise case-study section prioritizes original company or indexed-study records; product and social links are included for follow-through, not as independent evidence of performance; the STAT link is secondary reporting.

### A. Model and API documentation

These are the primary starting points for the model matrix and for building the examples in the deck.

- [OpenAI API documentation](https://developers.openai.com/api/docs) - models, Responses API, tools, structured outputs, agents, evaluation, safety, and pricing entry points.
- [OpenAI API quickstart](https://developers.openai.com/api/docs/quickstart) - first API call and basic setup.
- [OpenAI structured outputs](https://developers.openai.com/api/docs/guides/structured-outputs) - schema-constrained output.
- [OpenAI function calling](https://developers.openai.com/api/docs/guides/function-calling) - connecting a model to application tools.
- [OpenAI Agents API overview](https://developers.openai.com/api/docs/guides/agents-api/overview) - agentic orchestration concepts.
- [OpenAI evaluation guide](https://developers.openai.com/api/docs/guides/evaluation-getting-started) - building task-specific evaluations.
- [OpenAI safety best practices](https://developers.openai.com/api/docs/guides/safety-best-practices) - production safety guidance.
- [OpenAI Cookbook](https://cookbook.openai.com/) - practical examples and patterns.
- [Claude Platform documentation](https://platform.claude.com/docs/en/intro) - Anthropic API, tools, citations, files, structured outputs, and managed agents.
- [Gemini API getting started](https://ai.google.dev/gemini-api/docs/get-started) - Google Gemini API, multimodal input, structured output, tools, and function calling.
- [Google AI Studio](https://aistudio.google.com/) - interactive Gemini experimentation and API-key setup.
- [Perplexity API documentation](https://docs.perplexity.ai/docs/getting-started/overview) - search, citations, router, agents, and privacy/security documentation.
- [DeepSeek API documentation](https://api-docs.deepseek.com/) - API reference and OpenAI-compatible request patterns.
- [DeepSeek platform](https://platform.deepseek.com/) - account, keys, and usage.

### B. Input channels and enterprise data

- [WhatsApp Business Developer Hub](https://whatsappbusiness.com/developers/developer-hub/) - official developer documentation, webhooks, test numbers, sandbox, policies, and pricing.
- [Meta WhatsApp Business Messaging overview](https://developers.facebook.com/documentation/business-messaging/whatsapp/overview) - official platform overview.
- [WhatsApp message API reference](https://developers.facebook.com/documentation/business-messaging/whatsapp/reference/whatsapp-business-phone-number/message-api) - message operations and parameters.
- [Google Sheets API concepts](https://developers.google.com/workspace/sheets/api/guides/concepts) - reading and modifying spreadsheet data programmatically.
- [Google Cloud Document AI overview](https://docs.cloud.google.com/document-ai/docs/overview) - OCR, layout, key-value extraction, invoices, receipts, contracts, and custom extractors.
- [Azure AI Document Intelligence overview](https://learn.microsoft.com/en-us/azure/ai-services/document-intelligence/overview) - read, layout, prebuilt invoice and contract models, and custom extraction.
- [Amazon Textract overview](https://docs.aws.amazon.com/textract/latest/dg/what-is.html) - OCR and document text/structure extraction.

### C. Workflow and product engineering

- [n8n documentation](https://docs.n8n.io/) - visual workflow automation, integrations, data transformations, and AI workflow patterns.
- [LangGraph overview](https://docs.langchain.com/oss/python/langgraph/overview) - long-running, stateful agent workflows, persistence, human-in-the-loop, and evaluation/tracing concepts.
- [Stripe Checkout documentation](https://docs.stripe.com/payments/checkout) - hosted or embedded checkout sessions for a product like Boon.
- [JSON Schema](https://json-schema.org/) - standard for describing and validating structured JSON data.
- [Pydantic documentation](https://docs.pydantic.dev/latest/) - Python data validation and schema modeling.
- [FastAPI documentation](https://fastapi.tiangolo.com/) - lightweight API layer for prototypes and production services.
- [GitHub](https://github.com/) - source control, issues, pull requests, and reproducible engineering workflows.

### D. Governance and security

- [NIST AI Risk Management Framework](https://www.nist.gov/itl/ai-risk-management-framework) - voluntary framework for managing AI risks and improving trustworthiness.
- [OWASP GenAI Security Project](https://genai.owasp.org/) - current community guidance for LLM and generative-AI application security, including agentic systems.
- [OWASP GenAI Security Project on GitHub](https://github.com/GenAI-Security-Project/GenAI-LLM-Top10) - source materials and project history.

Use these resources to think about prompt injection, sensitive-data exposure, excessive agency, insecure tool use, supply-chain risks, data poisoning, and unsafe output handling.

### E. Speaker, product, and case-study links

These links are useful for following the speaker's work and for checking the examples referenced by the deck.

- [Minhaz Fahme official site](https://www.minhazfahme.com/) - biography, talks, contact information, and links to work.
- [Battery Low Games](https://batterylowgames.com/) - public company site and services.
- [Battery Low Interactive team page](https://xr.batterylowinteractive.com/index.php/our-team/) - public team/company context.
- [FeedBoss official site](https://www.feedboss.ai/) - current product surface, content workflows, analytics, approvals, and platform features.
- [Boon official site](https://useaboon.com/) - giftable AI-credit product and the signal-to-shipped-product story described on the slide.
- [Boon application](https://app.useaboon.com/) - product entry point linked from the official site.
- [Minhaz Fahme on LinkedIn](https://bd.linkedin.com/in/minhaz-fahme) - professional profile.
- [Minhaz Fahme on X](https://x.com/MinhazFahme) - public social profile.
- [Battery Low YouTube channel](https://www.youtube.com/channel/UCUxGLH3GqebKAW4hLCehkzw) - public video channel.

### F. Primary sources for the enterprise examples

- [JPMorgan Chase 2016 CEO letter](https://reports.jpmorganchase.com/investor-relations/2016/ar-ceo-letter-matt-zames.htm) - primary source for COIN, the 12,000 agreements, 150 attributes, and up to 360,000 manual-review hours per year.
- [JPMorgan Chase 2016 annual report PDF](https://www.jpmorganchase.com/content/dam/jpmc/jpmorgan-chase-and-co/investor-relations/documents/2016-annualreport.pdf) - the annual-report source document.
- [A&O Shearman and Harvey launch partnership](https://www.aoshearman.com/en/news/ao-announces-exclusive-launch-partnership-with-harvey) - official A&O announcement and historical scale context.
- [A&O Shearman and Harvey agentic AI announcement](https://www.aoshearman.com/en/news/ao-shearman-and-harvey-to-roll-out-agentic-ai-agents-targeting-complex-legal-workflows) - official announcement about agentic legal workflows.
- [Harvey and A&O Shearman customer story](https://www.harvey.ai/customers/a-and-o-shearman) - source for the public 30% contract-review time-reduction claim and current customer description.
- [PubMed search for the ambient-scribe study](https://pubmed.ncbi.nlm.nih.gov/?term=Changes+in+Clinician+Time+Expenditure+and+Visit+Quantity+With+Adoption+of+Artificial+Intelligence-Powered+Scribes) - use the indexed paper record for the exact study and metric.
- [STAT report on ambient-scribe time savings](https://www.statnews.com/2026/04/01/ai-ambient-scribes-modest-time-savings-clinical-documentation/) - secondary reporting; useful context, but the paper remains the authority.

## 8. Verification and transcription notes

- The supplied PDF is image-only: it has 15 embedded JPEG page images and no useful text layer. The slide text was transcribed with OCR and visual review.
- Several small captions are stylized or garbled, especially on Slides 8, 11, and 12. Where wording could not be recovered confidently, this sheet labels the text as garbled and records only the intended architectural interpretation.
- Slide 1 uses JSON-like examples for teaching. They are illustrative rather than a complete production schema.
- Slide 3 contains a duplicated “Professional” word in the fellowship line.
- Slide 8 has unusual capitalization in its title; it is normalized here to “The accounts check themselves.”
- Slide 9 says “60 pages” in the title but the visual says “61 pages read in 74 seconds.” Both details are retained.
- Slides 5, 10, and 12 contain vendor or product claims that should be benchmarked or checked against primary sources before being used as factual guarantees.
- The Slide 15 QR destination could not be decoded reliably from the available raster. Do not infer a WhatsApp destination from the visible name alone.

## 9. Final takeaway

The lecture's practical message is simple:

> Find one repeated, rule-rich, frustrating task. Connect the existing inputs to structured extraction, explicit rules, a controlled action, and human review. Measure the result. Then expand.

The engineering challenge is not to make AI sound intelligent. It is to make the whole workflow dependable when the data is messy, the answer is uncertain, and the consequences are real.
