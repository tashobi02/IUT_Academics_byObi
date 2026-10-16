# Lecture Sheet: AI in Operations

**Topic:** Finding repeatable work that AI can assist or automate, then designing safe, measurable workflows  
**Source deck:** Last Class.pdf  
**Deck title:** *Class 5: AI in Operations*  
**Deck subtitle:** *The business around the product — how six industries actually use AI*  
**Deck length:** 29 slides  
**Prepared:** 2026-09-28  
**Audience:** IUT undergraduate students, early builders, and Bangladesh-based founders  
**Central idea:** Automate repeated, well-described work where outputs can be checked; keep people responsible for judgment, exceptions, and consequential decisions.

> **How to use this sheet:** Each page note has **Deck content**, **Lecture interpretation**, and **Verification note**. The slide claims are recorded faithfully, while company statistics and market opinions are identified as reported or unverified. The link directory was checked on 2026-09-28. Product features and legal requirements change; check the current source and jurisdiction before using a tool or deploying a workflow.

## 1. Learning objectives

By the end of this class, you should be able to:

1. Identify work that is frequent, rules-based, structured, and reviewable.
2. Distinguish full automation from AI assistance with a human approval gate.
3. Measure task volume and time before choosing an automation project.
4. Separate labor savings, risk reduction, revenue effects, implementation costs, and residual error risk.
5. Interview a process owner to learn how work actually happens, including exceptions and handoffs.
6. Convert a repeated process into a written process document and testable automation specification.
7. Explain the stages of a basic workflow: trigger, input processing, AI step, validation, action, and logging.
8. Choose between a no-code workflow tool, a more configurable workflow platform, and a custom script based on the task and its operating needs.
9. Compare operations use cases across manufacturing, retail, finance, legal services, healthcare, and logistics.
10. Recognize why integration, distribution, proprietary data, pricing, and trust can matter as much as model capability.
11. Set up a small pilot with baseline measures, a reviewer, exception handling, and a stop condition.
12. Explain why model confidence alone is not proof of correctness or safety.

## 2. Prerequisites and working rules

### Useful inputs

- A named team or personal workflow, not a broad label such as “operations.”
- A process owner who performs or checks the task.
- Recent examples of inputs, outputs, corrections, and exceptions, with personal or confidential data removed where appropriate.
- A baseline: number of cases, active minutes per case, turnaround time, error rate, and rework.
- A clear statement of who may approve, reject, or override an AI-produced result.

### Rules for evaluating an idea

- Count the work before automating it. “It feels repetitive” is a starting hypothesis, not a measurement.
- Treat “more than 10 times a week” as the deck’s screening heuristic, not a universal threshold. A task with fewer cases may merit automation if delays or errors are costly; frequent work may not be worth automating if the work is already cheap and reliable.
- Separate task steps. One process may contain deterministic steps, judgment calls, and relationship work; different steps deserve different treatment.
- Keep an exception path. A workflow should be able to say “I cannot determine this” and route the case for review.
- Test the whole workflow, including permissions, retries, duplicate submissions, logging, handoffs, and failure notifications.
- Treat confidence as a routing signal only after it has been tested against representative examples. A model’s own confidence score is not a calibrated probability by default.
- Give a human reviewer enough evidence to make a decision: source document, extracted fields, rules triggered, and reason for escalation.
- Measure quality and consequences, not just speed. Track false acceptance, missed exceptions, rework, wait time, user impact, and cost to maintain.
- Avoid placing personal, financial, health, legal, or confidential data into a third-party tool until the organization has reviewed its terms, access controls, retention, security, and applicable law.
- Before a real deployment, assign an owner, define rollback or shutdown, document the current process, and train staff on the new one.

## 3. One-page lecture summary

### The operations loop

~~~text
Observe repeated work
    -> document actual steps and exceptions
    -> measure volume, time, errors, delay, and cost
    -> classify each step: rules, judgment, relationship, or high-consequence
    -> choose a narrow task with a checkable output
    -> build a workflow with validation, human review, and logs
    -> pilot against a baseline
    -> keep, revise, or stop based on measured outcomes
~~~

### First-pass fit table

| Work characteristic | Likely approach | Example |
|---|---|---|
| Repeated, structured, deterministic, low-impact if wrong | Automate the rule-based step; log results and sample quality | Match invoice totals to a purchase order and flag mismatches |
| Repeated but requires interpretation | AI prepares a draft or ranked queue; a qualified person approves | Summarize contract clauses against a lawyer’s playbook |
| Input is messy or inconsistent | Standardize the intake first; assist the operator while improving the process | Convert supplier emails and attachments into a common case form |
| Novel, relationship-heavy, or high consequence | Keep decision ownership with an expert; use AI only for bounded support if suitable | A clinician reviews and signs a drafted note; an analyst decides a suspicious-fraud case |
| Infrequent and low cost | Usually keep it manual until evidence justifies a change | A one-off quarterly request that takes a few minutes |

### The six-step workflow shown in the deck

| Stage | Purpose | Design question |
|---|---|---|
| Trigger | Starts a run: schedule, webhook, form, email, or another event | What event creates exactly one work item? |
| Input processing | Parses, cleans, and extracts the relevant fields | What formats and missing values must be handled? |
| AI step | Classifies, extracts, summarizes, or drafts into a defined schema | What is the model allowed to decide or produce? |
| Validation | Checks schema, deterministic rules, and escalation conditions | What must be true before the result can move forward? |
| Action | Creates a draft, ticket, sheet row, notification, or approved API change | Is this reversible, and who authorizes it? |
| Log | Records input reference, output, version, costs, status, and errors | Can an operator reconstruct what happened? |

### Use a value model with separate terms

The deck says to rank by “hours saved × cost of an error.” That phrase is a useful reminder to consider both time and risk, but it is not a dimensionally clear scoring formula. Keep separate estimates first:

- **Monthly task hours:** minutes per case × cases per week × 4.33 ÷ 60.
- **Labor capacity released:** task hours actually removed from staff workload. Released time is not automatically cash savings; it may instead improve service or allow more work.
- **Expected loss:** probability of an error × impact if that error occurs, using a defined time period.
- **Net monthly value, approximately:** realizable labor or capacity value + measurable avoided loss + attributable revenue effect − build, software, maintenance, review, training, and residual error costs.

Use legal, safety, privacy, and customer-harm limits as constraints, not merely as points in a ranking score. A high business return does not make an unacceptable failure mode acceptable.

## 4. Core concepts and frameworks

### 4.1 Automate a step, not a vague process name

“Accounts payable” is a department. “Read a supplier invoice, extract invoice number/date/amount/PO number, match the invoice lines to the purchase order and receipt, and queue mismatches for review” is a candidate workflow.

For each step, identify:

1. The trigger and work owner.
2. The input and its format.
3. The action performed.
4. The expected output.
5. The rule or judgment used.
6. The exceptions and how they are handled.
7. The consequences of a late or wrong result.
8. The person who checks or signs off.

If a process owner cannot describe the steps, edge cases, and completion condition, the first project is process discovery and standardization.

### 4.2 Classify steps by decision type

| Type | Meaning | Useful system behavior |
|---|---|---|
| Deterministic rule | The same explicit rule should produce the same answer | Use code, a rules engine, or workflow conditions; test boundary cases |
| Extraction | Convert a document, image, or message into fields | Return structured fields plus source locations; validate required values |
| Classification | Assign a case to a defined category or queue | Provide labels and evidence; measure false positives and false negatives |
| Generation | Produce a draft, summary, or explanation | Constrain format and sources; require review before publication or action |
| Prediction or ranking | Estimate likelihood, priority, or expected outcome | Measure calibration, drift, subgroup behavior, and the cost of errors |
| Relationship or consequential judgment | Resolve ambiguity, negotiate, diagnose, approve, or determine rights | Preserve qualified human ownership; any AI role needs domain review and safeguards |

The “AI step” may combine a conventional model, a language model, and ordinary software. Use AI where flexibility is useful; use explicit rules for exact requirements such as dates, totals, required fields, access, and approval.

### 4.3 Score value and risk separately

Make an initial 1–5 estimate for frequency, minutes per case, cost of delay, error impact, input consistency, reversibility, and reviewability. These scores help structure discovery; they do not prove value.

| Measure | Example of a useful baseline |
|---|---|
| Volume | Number of complete work items per week or month |
| Active effort | Median minutes of staff work per item; include rework |
| Cycle time | Median and 90th percentile from receipt to completion |
| Quality | Error and rework rates, with error categories |
| Risk | Error likelihood and impact by failure type |
| Adoption | Share of eligible cases actually processed through the workflow |
| Run cost | Software, model/API, support, review, and maintenance cost |

Rank candidates by plausible net benefit, feasibility, and risk. Do not allow a single aggregate score to conceal a severe failure mode.

### 4.4 Human review must be designed, not merely mentioned

A useful approval screen lets the reviewer compare the AI output to source evidence, see why a case was flagged, correct fields, reject the result, and record a reason. Avoid a perfunctory “approve” button that hides the source or encourages rubber-stamping.

For each review gate, define:

- Who is qualified and authorized to review?
- What source evidence must be visible?
- What error patterns require escalation?
- What is the expected response time?
- What happens if nobody reviews the item?
- Can the reviewer undo the action?
- How will disagreements and corrections improve the process?

### 4.5 Build for uncertainty and operational failure

Handle missing fields, unreadable files, unsupported formats, timeouts, partial API failures, duplicate emails, stale documents, unexpected values, and conflicting records. A safe default is to pause and route uncertain work to a person. Do not silently convert an error into a plausible-looking answer.

Use idempotency or duplicate checks so a retried run does not create repeated payments, tickets, or customer replies. Keep credentials out of prompts and logs. Limit access to the minimum permissions the workflow needs.

### 4.6 Why an incumbent or integration can win

The industry examples suggest several non-model advantages:

- the workflow is already embedded in a system the buyer uses;
- the vendor already has permissioned access to relevant data;
- the vendor has a trusted route to the buyer and an existing contract;
- the price or packaging fits how a team buys;
- the product handles review, audit, security, and support;
- the workflow is narrow enough to produce a measurable outcome.

These are product and distribution hypotheses. They do not establish that any listed product is more accurate, compliant, or economical for a particular organization.

## 5. Six-industry map from the deck

| Industry | Examples of repeated work in the slides | Buyer or measure proposed by the deck | Main operational question |
|---|---|---|---|
| Manufacturing | Invoice matching, goods-in checks, visual inspection, machine warnings, shift reports, supplier follow-up | Plant manager and finance director; plant-level budget | Can the workflow tolerate downtime, false alarms, and imperfect sensor or document data? |
| Retail | Listings, photo tags, SKU/store/week demand forecasts, order-status replies, review summaries, price monitoring | E-commerce or service lead; time-to-list and customer contact rate | Does the generated or summarized information stay accurate and current? |
| Finance | Identity documents, fraud ranking, claims intake, loan covenants, AML alert triage, customer questions | COO or compliance; risk budget | Who may approve an account, transaction, claim, or regulatory action? |
| Legal | Contract review, due diligence, research drafts, version comparison, billing narratives, conflict intake | In-house legal or law firm; cost or capacity | Are sources, jurisdiction, privilege, confidentiality, and lawyer review handled correctly? |
| Healthcare | Notes, patient-message drafts, coding, prior-authorization letters, appointment triage, discharge summaries | Hospital operations and clinical leadership | Does the tool fit the clinical record and local clinical, privacy, and device rules? |
| Logistics | Customs papers, expiry alerts, delay detection, delivery proof, load matching, structured field reports | Operations director; penalties and demurrage | Are current documents, customs requirements, and operational consequences verified? |

The buyer descriptions and “who wins” statements are the deck’s market hypotheses. Confirm the actual budget owner, procurement route, regulatory role, data access, and measurable outcome with each prospective customer.

## 6. Reusable templates

### 6.1 Two-week task inventory

For every recurring task in one team, log individual steps rather than department-level labels.

| Field | Record |
|---|---|
| Task and step | |
| Owner and other handoffs | |
| Trigger and frequency | |
| Input type and format | |
| Minutes of active work per case | |
| Output and completion condition | |
| Exceptions and rework | |
| Late-result consequence | |
| Error types and impact | |
| Existing review or approval | |
| Structured, judgment-based, or relationship-based? | |
| Candidate automation boundary | |

At the end, calculate monthly hours with the formula above. Verify samples with the people doing the work; avoid relying only on estimates from a manager or founder.

### 6.2 Process discovery interview

Ask the operator to walk through a recent real case:

1. “Walk me through the last time this went wrong.”
2. “Who touches this between the request and completion?”
3. “What happens if it is late?”
4. “What do you check before you sign or send it?”
5. “Show me the file or a safe example of the input.”
6. “Which step do people dread or redo most?”
7. “What exceptions make you stop and ask someone?”
8. “What does a correct, complete result look like?”

Listen for actual behavior, workarounds, handoffs, and exceptions. Do not assume the official process document describes reality.

### 6.3 Process-document interview prompt

~~~text
I’m going to describe a process I do repeatedly. Interview me step by step.
For each step, ask:
- What is the input?
- What do I do with it?
- What is the output?
- What could go wrong?

Ask follow-up questions when a step or exception is unclear. Do not invent missing rules.
At the end, write a process document with the trigger, roles, steps, inputs,
outputs, decision rules, exceptions, approval points, completion condition,
and open questions. Mark anything that I have not confirmed.
~~~

### 6.4 Process document template

~~~text
Name and owner:
Purpose:
Start trigger:
Inputs and accepted formats:
Required fields:
Steps in order:
Decision rules:
Human judgment points:
Exceptions and escalation:
Output:
Who reviews or approves:
Definition of done:
Expected volume and turnaround:
Error consequences:
Data or access restrictions:
Unconfirmed rules:
~~~

### 6.5 Automation specification

~~~text
Problem and owner:
Target users:
Baseline and target:
In scope:
Out of scope:
Trigger:
Input schema and source:
Processing steps:
AI task and permitted output:
Deterministic validation:
Confidence / abstention behavior:
Human review point:
Action after approval:
Failure and retry behavior:
Duplicate handling:
Logs and audit trail:
Data retention and permissions:
Quality measures:
Cost assumptions:
Pilot duration and sample:
Stop / rollback conditions:
Ongoing owner:
~~~

### 6.6 Vendor or build decision

Compare tools using:

- Does the tool connect to the existing source of truth?
- Can it enforce roles, review gates, audit history, and error queues?
- Can data be kept in the approved region and retention period?
- Can the team test with representative examples before activating actions?
- Is there a clear way to retry, roll back, export, and shut down?
- What will implementation, run, review, and maintenance cost?
- Does the workflow rely on a feature that could be removed or repackaged?
- Is a vendor claim independently evaluated, or only vendor-reported?

Choose the simplest tool that meets the operational requirements. A visual no-code builder can be quick for straightforward connections; a configurable workflow platform can offer more control; a script can fit a small, well-understood integration. Any choice still needs authentication, monitoring, error handling, documentation, and a maintainer.

## 7. Detailed slide-by-slide notes

### Slide 1 — Class 5: AI in Operations

**Deck content:** Introduces AI in operations as the business around the product and promises examples from six industries.

**Lecture interpretation:** Operations is the work that makes a product or service run: processing requests, documents, transactions, inventory, customer issues, and internal handoffs. The course question is how to make this work faster or more reliable while preserving accountable ownership.

**Verification note:** The subtitle frames the lesson; it is not evidence that every named example is current, independently evaluated, or suitable for a new buyer.

### Slide 2 — What is the most repetitive task you have automated?

**Deck content:** A large opening question invites students to name a repetitive task.

**Lecture interpretation:** Start from a real workflow rather than choosing a model first. A useful answer names the task, frequency, input, output, and what happens when it fails. A student who has not automated anything can describe a manual task and identify where an automation boundary might fit.

**Verification note:** Personal examples should not include confidential customer, employer, health, or financial information.

### Slide 3 — Where AI fits and where it does not

**Deck content:** The slide uses three stacked categories: **fits** high-volume work with clear rules, structured inputs/outputs, and a human check; **doesn’t fit** novel decisions, relationships, or catastrophic one-time errors; **grey zone** repeated judgment calls where AI drafts and a person approves. Its rule is “Automate the volume. Keep the judgement.”

**Lecture interpretation:** Treat the categories as a workflow-level guide, not a claim that an entire occupation is automatable. A single process can contain an easy extraction step, a difficult judgment call, and an important customer conversation. Automate only the bounded part. “Human checks first” should mean a designed and informed review gate, not a nominal sign-off.

**Verification note:** This is a practical heuristic, not a formal AI risk framework. NIST’s AI Risk Management Framework is a useful companion for identifying and managing risks across context, measurement, and operation.

### Slide 4 — How to find the scope

**Deck content:** A four-column sequence says: **List** recurring tasks in one team for two weeks, recording steps rather than process names; **Measure** minutes × times per week to estimate monthly hours; **Classify** rules, judgment, or relationship; **Rank** by “hours saved × cost of an error.” A footer says teams guess their biggest time sink and should measure first.

**Lecture interpretation:** The numbered cards form a discovery funnel: observe, quantify, classify, then prioritize. Multiply minutes per case by frequency, then convert to hours. Include waiting and rework separately from active labor. Estimate both potential capacity and error exposure, but keep them as separate measures before deciding. Error costs may be rare, uncertain, or asymmetric, so a single multiplication can hide the wrong thing.

**Verification note:** “Two weeks” is a useful short observation period, not a statistically guaranteed sample. The ranking expression is underspecified; use the separate value model in Section 3 and let safety or legal constraints rule out an otherwise attractive task.

### Slide 5 — Should you automate this?

**Deck content:** A four-question decision table asks whether the work happens more than ten times weekly, has structured or structurable input, catches a wrong output before it reaches someone, and costs less to automate than to do manually. “No” paths recommend manual work, AI assistance, human approval, or waiting.

**Lecture interpretation:** This is a first-pass filter. It correctly asks about volume, input quality, review, and economics. Add at least three checks: whether the failure is reversible, who owns the workflow, and what data or rules apply. A single severe error may disqualify a task even if the expected savings look high.

**Verification note:** Ten runs weekly is a classroom threshold, not a universal standard. Compare the total cost of implementation, model/tool use, human review, exception handling, maintenance, training, and residual errors.

### Slide 6 — Problem to solution

**Deck content:** A two-column table maps “too slow” to extract → validate → flag → approve; “costs too much” to a scheduled batch pipeline; “mistakes” to a rules engine plus confidence threshold; “can’t scale” to a process document plus agent and log; and “customers wait too long” to classify → route → draft reply.

**Lecture interpretation:** These are workflow shapes, not guaranteed fixes. Extraction and validation can reduce handling time; batching can reduce repetitive setup; classification can route cases; a draft can shorten response time. Before choosing a shape, define the actual bottleneck and metric. For example, lower handle time is not a win if errors, repeat contacts, or customer abandonment rise.

**Verification note:** Confidence thresholds need empirical testing and an abstention path. For deterministic requirements, enforce explicit rules rather than asking a model to “be confident.” Keep outward-facing replies as drafts until quality and escalation behavior are established.

### Slide 7 — How to find the real problem

**Deck content:** Five interview prompts ask about the last failure, handoffs, the consequence of lateness, what is checked before signing, and the actual file. The closing visual directs the student to listen for the step everyone dreads rather than the first step they describe.

**Lecture interpretation:** The prompts move from concrete incident to handoffs, value, control, and input quality. Ask the process owner to reconstruct a recent real case, including workarounds. The most painful step may be downstream rework or waiting, not the first visible task. The file reveals whether inputs are consistent and whether source evidence can be retained.

**Verification note:** “No consequence means no budget” is too absolute as a market rule. A task may have prevention, service, compliance, or strategic value that is not immediately visible. Verify who funds the work and what outcome they will pay for.

### Slide 8 — What buyers actually pay for

**Deck content:** Three side-by-side value propositions are shown: **cost per transaction** (priced against headcount; examples include AP, support, claims intake); **risk and compliance** (priced against fines, failed audits, or stopped shipments; examples include KYC, certificates, audit trails); and **revenue speed** (time-to-list, quote, or close; examples include catalogues, proposals, lead qualification). A market callout says chatbots/content are crowded and regulated documents are open.

**Lecture interpretation:** The useful point is to connect a product to a buyer’s measurable outcome. The three groups need different evidence: unit cost and capacity; control effectiveness and avoided loss; or causal contribution to revenue speed. “Risk reduction” must be carefully measured and should not be promised as prevention of a fine or audit failure without evidence.

**Verification note:** “Highest willingness to pay,” “hardest to attribute,” and “open market” are market hypotheses, not universal facts. Validate through buyer interviews, procurement records, alternatives, and paid pilots. Compliance software still requires legal and domain expertise.

### Slide 9 — Manufacturing: what gets automated

**Deck content:** Six numbered tiles list invoice-to-purchase-order matching, photographed goods-in checks for damage or shortfalls, camera-based inspection of every item, sensor-based failure warnings, shift-data production reports, and supplier follow-up for late deliveries. The buyer callout names plant managers and finance directors and says the budget sits with the plant rather than IT.

**Lecture interpretation:** The six examples cover document extraction, visual inspection, prediction, reporting, and outbound drafting. They require different evidence and fallbacks. An invoice mismatch can be checked against source records; an image inspection needs labeled defect examples and a process to handle false alarms; failure prediction needs alert lead time and missed-failure rates, not just model accuracy.

**Verification note:** Buyer and budget roles vary by company size and procurement structure. A high-volume camera workflow needs a measured false-reject and missed-defect rate; a predictive-maintenance model needs a comparison with existing maintenance practice.

### Slide 10 — Manufacturing: who owns it

**Deck content:** Three visual columns name SAP invoice checking, Siemens machine failure sensors, and Amazon warehouse quality checks. Each “why it wins” card emphasizes an existing system, per-machine pricing, or having built a solution for internal use before selling it. A footer says two of the three won on distribution and pricing rather than the model.

**Lecture interpretation:** The lesson is that ownership of workflow, installed base, packaging, and sales route can determine adoption. A tool inside an ERP or plant system may avoid manual data transfer; per-machine pricing can align a purchase with deployment units; an internal system can be shaped around a real operating environment.

**Verification note:** SAP documents AP automation that captures invoice data, matches invoices to purchase orders and receipts, and routes approvals. Siemens markets predictive-maintenance products. The slide does not identify the Amazon system, so do not treat it as a specific currently supported Amazon product. AWS Panorama, if someone assumes that is the example, reached end of support on 2026-05-31; do not recommend it as an available service. The “distribution and pricing” comparison is the lecturer’s interpretation.

### Slide 11 — Retail: what gets automated

**Deck content:** Six tiles list product listings from specifications, photo tagging, demand forecasting by SKU/store/week, order-status replies, review summaries, and competitor price monitoring. The buyer callout names the e-commerce head and service lead; measures include time-to-list and contact rate.

**Lecture interpretation:** The examples span generation, image classification, forecasting, support, summarization, and monitoring. Measure accuracy and downstream outcomes: listing corrections, inventory error, duplicate or stale price alerts, escalation rate, and whether a summary preserves minority or negative review themes. “Per SKU/store/week” correctly signals that forecasts need operationally useful granularity.

**Verification note:** A generated listing can invent benefits or details. Shopify tells merchants to review generated product descriptions for accuracy before publishing. Review summaries are compressions; retain access to original reviews.

### Slide 12 — Retail: who owns this space

**Deck content:** Three columns associate Shopify with product descriptions inside seller admin, Amazon with review summaries, and Klarna with an AI assistant handling about two-thirds of support chats. The slide credits Shopify’s bundled distribution, Amazon’s access to its review data, and Klarna’s faster response time. It warns against selling a feature separately if a platform includes it for free.

**Lecture interpretation:** A standalone product can be displaced when a platform bundles similar functionality or owns the customer’s data and workflow. Compare the buyer’s total cost and switching friction; find a differentiated task the platform does not solve. For customer support, evaluate resolution, repeat contact, customer satisfaction, and escalation quality—not response speed alone.

**Verification note:** Shopify’s help page confirms automatic description generation and explicitly leaves accuracy review to the merchant. Amazon describes AI review highlights. Klarna’s “two-thirds” figure was a company-reported first-month claim in 2024; its filings later reported 69% for the 12 months ending June 30, 2025, and 80% for 2025. These figures describe different reporting periods and remain company-reported; they do not independently establish quality or causal savings, and they are not universal benchmarks.

### Slide 13 — Finance: what gets automated

**Deck content:** Six tiles show document checks for passports and proofs, millisecond fraud scoring, claims intake from photos/forms/calls, loan covenant and ratio extraction, AML-alert ranking, and customer balance or statement questions. The buyer callout names COO and compliance leadership, and frames budget as risk rather than efficiency.

**Lecture interpretation:** Finance use cases range from low-risk support drafts to identity checks, fraud decisions, lending, and AML. Treat each according to its effect on access to money, service, or account status. Keep source links and review histories for extracted terms; route uncertain, contested, or high-value cases to authorized staff.

**Verification note:** The deck’s buyer/budget wording is a sales hypothesis. Applicable financial-services, privacy, anti-money-laundering, consumer-protection, and model-governance requirements depend on jurisdiction and use. A generic confidence score does not satisfy those requirements.

### Slide 14 — Finance: who owns this space

**Deck content:** The three company examples are Mastercard fraud scoring, JPMorgan’s COIN system for loan agreements, and Lemonade’s rapid claims. Their advantages are described as decades of transaction data, building core work in-house, and building an insurer around automation. The closing rule is “Utilities get bought. Differentiators get built.”

**Lecture interpretation:** Decide whether the task is a commodity capability available from a trusted vendor or a source of strategic differentiation that justifies internal investment. Internal builds bring control but also ongoing model, security, operations, and evaluation costs. Vendor selection still requires diligence on data, error handling, and contractual remedies.

**Verification note:** JPMorgan’s 2016 annual report described COIN as machine learning, not a current generative-AI benchmark. It reported extraction of 150 attributes from 12,000 annual commercial credit agreements in seconds and compared this with “as many as 360,000 hours per year” of manual review. Attribute the number to the 2016 company report; do not present it as an independently audited saving. Lemonade’s current claims page says some claims are instantly approved and others go to humans; its fastest recorded claim and instant-handling percentages are company-reported.

### Slide 15 — Legal: what gets automated

**Deck content:** Six examples cover contract review, issue-by-issue due diligence, sourced research-memo drafts, version comparison, billing narratives from activity logs, and conflict checks. The buyer callout says in-house teams buy faster than firms and recommends selling cost internally and capacity externally.

**Lecture interpretation:** Legal workflows need traceable source material, jurisdiction, matter context, privilege controls, and lawyer review. Good bounded tasks include finding clauses, comparing versions, summarizing a defined document set, or drafting from approved source materials. A polished draft is not a verified legal conclusion.

**Verification note:** Procurement speed and willingness to pay differ across firms and corporate legal departments. Keep the buyer claim as a hypothesis. Avoid uploading privileged or confidential matter data until contractual, security, access, and retention terms are approved.

### Slide 16 — Legal: who owns this space

**Deck content:** Harvey is associated with research and drafting informed by a firm’s prior work; Westlaw with an assistant inside an existing legal-research product; DocuSign with extracting dates, renewals, and obligations from agreements. The slide attributes advantages to security/trust, distribution, and already holding signed contracts, then says to sell to in-house teams because billable-hour economics work against selling to firms.

**Lecture interpretation:** The visual compares specialized legal AI, a research incumbent, and a system already holding agreements. Integration and trusted content can reduce friction. Whether a firm benefits from automation depends on its pricing model, practice area, client expectations, and how recovered time is redeployed.

**Verification note:** Harvey and Thomson Reuters currently describe contract-review and legal-research features; DocuSign markets AI for agreement analysis. Product capabilities evolve and are vendor descriptions. “Billable-hour model works against you” is a broad commercial claim, not a rule for every law firm.

### Slide 17 — Healthcare: what gets automated

**Deck content:** Six examples are consultation notes, patient-message drafts in the medical record, coding suggestions, prior-authorization letters, appointment urgency ranking, and discharge summaries for clinician signature. The buyer callout names hospital operations and clinical leaders, notes long pilots and compliance review, and describes the systems as sticky.

**Lecture interpretation:** The slide usefully places note and message drafts inside an existing clinical record and names a clinician sign-off. Any workflow that influences triage, coding, coverage, or care requires domain-specific validation and oversight. Evaluate omissions, distortions, unsupported details, clinician edit burden, and patient outcomes as relevant.

**Verification note:** “Long pilots,” “sticky,” and the buyer role are market generalizations. In the United States, HIPAA Security Rule safeguards apply to covered entities and business associates handling electronic protected health information; FDA software policies depend on intended use and function. These are U.S. references only and do not substitute for local review.

### Slide 18 — Healthcare: who owns this space

**Deck content:** Microsoft is linked to note drafting from a consultation, Epic to patient replies and letters inside the medical record, and Ada Health to symptom questions and urgency ranking. The slide claims the winners plug into or own the clinical workflow and says Ada “never diagnoses, so it clears regulation.”

**Lecture interpretation:** Embedding in the clinician’s record can reduce copying and context switching, but it also makes integration, permissions, reliability, and vendor governance central. Patient-facing symptom guidance needs careful limits, escalation advice, and clear intended use.

**Verification note:** Microsoft documents Dragon Copilot for clinical documentation, and Epic describes AI charting that drafts visit notes and suggests orders. Ada’s own statement says it is not a substitute for professional advice and does not provide clinical decision support, but that does not establish a blanket regulatory exemption. Product classification depends on intended use, product functionality, claims, and jurisdiction; the slide’s “clears regulation” phrasing is too broad.

### Slide 19 — Logistics: what gets automated

**Deck content:** Six tiles cover customs documents before port arrival, certificate/license expiry alerts, plan-versus-actual delay detection with drafted escalation, proof-of-delivery filing, instant load matching/pricing, and converting voice notes into structured job records. The buyer is an operations director; the value is framed as avoided penalties and demurrage rather than hours saved.

**Lecture interpretation:** The examples connect document quality and event visibility to operational consequences. A useful pilot measures missed expiry alerts, customs rework, detention/demurrage, delivery evidence completeness, load utilization, and time to resolve exceptions. Keep an operator in control of actions that could change a shipment, filing, or customer commitment.

**Verification note:** Cost-of-delay claims must be calculated for the route, contract, port, and customer. Customs documentation rules vary by destination and commodity; an AI-generated classification or description needs qualified verification.

### Slide 20 — Logistics: who owns this space

**Deck content:** Maersk is associated with reading customs documents and flagging expiry; DHL with predicting delays and rerouting before a customer calls; Uber Freight with automated load matching and instant prices. The slide says one stopped container can cover a year of Maersk fees and that all three sell a number rather than a capability.

**Lecture interpretation:** The pitch should connect the workflow to an operating result buyers care about. For customs, estimate avoided dwell, rework, or penalty exposure; for routing, measure predicted delay accuracy and whether an action improved delivery; for matching, compare utilization, booking time, and service quality.

**Verification note:** Maersk’s 2026 product material describes document and product-data extraction with confidence scores and traceable sources. Uber Freight documents instant quotes and load-matching features. DHL’s trend material describes predictive and adaptive logistics at an industry level; it does not by itself verify every detail of this specific slide example. The stopped-container payback statement is not independently established here.

### Slide 21 — Which process in your work has the most manual steps?

**Deck content:** A large reflective question asks students to identify their most manual process and whether parts can be automated.

**Lecture interpretation:** Answer by naming one process and one candidate step. A useful first pass states the trigger, weekly frequency, input, manual minutes, recurring error, output, and reviewer. Do not choose the most visible or technically exciting task unless its measured value supports the choice.

**Verification note:** Avoid sharing workplace data or customer records in a classroom tool. Use synthetic or properly anonymized examples.

### Slide 22 — What is running elsewhere at scale

**Deck content:** Six cards list Harvey for legal research/contracts; JPMorgan COIN reviewing loan agreements in seconds and a reported 360,000 hours per year; Klarna at about two-thirds of customer-service chats; ambient scribes turning doctor dictation into notes; Unilever screening CVs in an initial hiring round; and Duolingo generating exercises, explanations, and stories with a smaller content team. The summary says none replaced experts, but each replaced volume work around experts.

**Lecture interpretation:** Use the examples to generate questions about the boundary of automation: which work is assisted, which decisions remain human-owned, and how the system handles difficult cases. Distinguish deployment scale from independently established quality or net job effects. The same workflow can alter job tasks without proving that no jobs were displaced.

**Verification note:** COIN’s hours figure is a historical JPMorgan-reported comparison from its 2016 annual report. Klarna’s proportion is company-reported and period-specific. Duolingo’s 2025 shareholder letter says nearly 150 new courses were introduced using AI-generated content; it does not establish the slide’s “smaller content team” causal claim. Historical reporting described algorithmic screening at Unilever in 2017, but this does not establish a current company-wide practice: a current Unilever UK early-career role page says AI is not used as a screening tool for that process. Hiring tools need careful fairness, accessibility, and employment-law review.

### Slide 23 — The pattern across all of them

**Deck content:** Three numbered statements say the organizations structured input first, kept a human at the end, and started narrow before expanding. A footer says AI cannot follow steps that cannot be described.

**Lecture interpretation:** These are sound implementation principles: standardize, assign review, and prove a bounded workflow before scaling. A written process is necessary for implementation and evaluation; it is not sufficient to make every step appropriate for AI. Stable processes still need error monitoring because inputs, software, rules, and staff behavior can change.

**Verification note:** The slide’s universal phrasing (“every single one,” “nobody launched a department”) is rhetorical. The lecture sheet treats the three items as recommended patterns, not verified facts about all named deployments.

### Slide 24 — How these actually get built

**Deck content:** A two-row pipeline connects **trigger** (schedule/webhook/form/email) → **input processing** (parse, clean, extract) → **AI step** (structured prompt and JSON) → **validation** (schema, rules, confidence) → **action** (email/sheet/ticket/API) → **log** (input, output, cost, pass/fail). Tool examples are n8n, Make, Zapier, and custom scripts. The slide recommends the simplest tool that works.

**Lecture interpretation:** This is the implementation backbone of the class. Add authentication, least privilege, duplicate protection, retries, exception queue, monitoring, human approval, versioning, and an owner. A valid JSON object may still contain false information; schema validation checks shape, while factual validation checks content against source evidence or explicit rules.

**Verification note:** The named tools change features, plan limits, and data terms over time. Select based on current documentation and the organization’s controls, not the slide’s brief list.

### Slide 25 — Build your process document

**Deck content:** The slide provides an interview prompt: describe a repeated process, have the AI interview step by step about inputs, actions, outputs, and failure possibilities, then produce a process document. Its bold instruction is “Interview, don’t ask,” and it calls the process document the automation specification.

**Lecture interpretation:** The useful technique is interactive elicitation: ask one question at a time, probe vague phrases such as “check it,” and get concrete examples. Then verify the AI’s write-up with the process owner. The source of truth is the confirmed process, not the model-generated document.

**Verification note:** Use the reusable prompt in Section 6.3. The prompt should explicitly prohibit invention and mark unresolved rules as open questions.

### Slide 26 — Write your first automation specification

**Deck content:** Students are asked to pick a repetitive task from an idea or daily life, create the process document, then choose n8n, Make, Zapier, or a script.

**Lecture interpretation:** Decide the workflow requirements before choosing a tool. If the process contains regulated data, complex permissions, external side effects, or strict uptime needs, include those requirements in the selection. Test with a small, representative set and keep actions in draft mode until the approval path is reliable.

**Verification note:** The slide’s tool list is illustrative. Product pricing, integrations, hosting options, and policies may have changed; check the vendor’s official current documentation.

### Slide 27 — What is the first automation you will build?

**Deck content:** A closing reflection asks each student to name the first automation they will build after the course.

**Lecture interpretation:** Make the answer specific enough to start: “For the next two weeks, log incoming supplier invoices; then test extracting invoice number, date, amount, and PO number into a review queue.” Include the owner, data source, expected benefit, and test.

**Verification note:** Avoid an unsupervised live deployment as the first experiment. Prefer read-only, draft-only, or synthetic-data testing until the workflow’s failure behavior is known.

### Slide 28 — The course arc

**Deck content:** A five-part row maps Class 1 to finding the problem, Class 2 to deciding what to build, Class 3 to building it, Class 4 to selling it, and Class 5 to running it. The line underneath says one idea across five classes gives students what they need to start.

**Lecture interpretation:** Operations is the bridge between a product promise and repeated delivery. The operating workflow feeds back into product decisions: recurring exceptions may reveal a product gap; support volume may change unit economics; quality problems can invalidate a sales claim.

**Verification note:** The course sequence is a teaching structure, not a guarantee that five classes are sufficient to launch or operate a safe commercial product.

### Slide 29 — What you leave with

**Deck content:** Five outcomes are shown: an updated context document; a one-page specification with locked rules and a cost line; a launch plan with channel, sequence, and support; an automation specification or process document; and a way of working that starts with context, checks everything, and keeps decisions with the student. It closes with “Now go build something.”

**Lecture interpretation:** These are concrete artifacts. The operations handoff should include a process owner, the approved scope, baseline measures, a spec, test cases, review rules, support instructions, and a shutdown plan. Maintain one versioned record so the automation can be audited and updated.

**Verification note:** “Locked rules” should not mean immutable rules. Policies, inputs, vendors, and laws change; assign an owner to review and revise them.

## 8. Guided practical: invoice matching pilot

This is a hypothetical classroom example, not a recommendation to automate payments immediately.

### Starting process

A small manufacturer receives supplier invoices by email. An accounts-payable clerk opens each PDF, finds the supplier, invoice number, date, amount, and purchase-order reference, compares those values to the purchase order and goods-receipt record, then approves or asks a person to resolve a mismatch.

### Proposed boundary

1. Trigger on a new invoice email.
2. Store the original attachment and record a unique message/invoice identifier.
3. Extract the five fields and keep source references for each extracted value.
4. Match supplier and purchase-order identifiers against approved internal records.
5. Apply deterministic checks for required fields, duplicate invoice number, currency, arithmetic, and allowed tolerance.
6. Put complete, exact matches into a review queue with original document and source records visible.
7. Route missing, low-quality, mismatched, or duplicate cases to an exception queue.
8. Require an authorized person to approve any payment-related action.
9. Log extraction output, validation results, corrections, reviewer decision, and failure.

### Measure the pilot

Before testing, gather a baseline sample and define:

- eligible invoices and number processed;
- field-level extraction accuracy;
- percentage matched correctly without correction;
- missed duplicates and false mismatch flags;
- reviewer minutes per invoice;
- total cycle time, including exceptions;
- cost per processed invoice, including review and maintenance;
- any payment, privacy, or security incident.

Use a historical or shadow-mode test first. Compare the workflow to the manual process, inspect errors by type, and review enough samples to find rare but severe failures. Do not allow automatic payment release in the initial pilot.

## 9. Exercises and assessment

### Exercise A — Map one task

Choose a repeated personal or team task. Create a task inventory, interview one person who does it, and draw the current steps. Submit the input types, handoffs, exception cases, completion condition, and baseline.

### Exercise B — Choose an automation boundary

Label each step as deterministic, extraction, classification, generation, prediction, relationship work, or consequential judgment. Mark which steps should stay manual, be AI-assisted, or be candidates for automation. Explain your reasoning and the failure path.

### Exercise C — Draft the specification

Complete the template in Section 6.5. Write three ordinary test cases, three difficult or ambiguous cases, and one case where the system must abstain. Specify expected output, source evidence, reviewer action, and log entry for each.

### Exercise D — Evaluate a business claim

Select one named company example. Record the exact claim, source, date, whether the source is a vendor/company or independent party, what the source does not establish, and what evidence a buyer would still need.

### Assessment rubric

| Criterion | Strong submission |
|---|---|
| Process understanding | Describes actual steps, owners, handoffs, exceptions, and completion |
| Measurement | Includes a baseline with units, time window, and denominator |
| Scope | Automates only a bounded task and explains excluded decisions |
| Safety and quality | Defines review, abstention, exception handling, retries, and rollback |
| Evidence | Distinguishes measured evidence from assumptions and vendor claims |
| Economics | Includes build, run, oversight, maintenance, error, and adoption costs |
| Implementation | Specifies access, logging, testing, and operational ownership |

## 10. Exam review

### Questions

1. What work characteristics make a task a strong candidate for automation?
2. Why should a student log steps rather than write only a process name?
3. What does the slide’s “more than ten times a week” threshold miss?
4. How is monthly task time calculated from minutes per case and weekly volume?
5. Why is “hours saved × cost of an error” not a complete value formula?
6. What belongs in the workflow between an AI output and an external action?
7. Why can valid JSON still be wrong?
8. What are the three patterns shown across the industry examples?
9. Give one reason a platform or incumbent may win beyond model quality.
10. Why does a symptom checker’s intended-use statement not establish blanket regulatory exemption?

### Short answer key

1. Repeated, reasonably structured, bounded, checkable, and low enough in impact—or protected by adequate review.
2. Process names hide actual work, handoffs, exceptions, and decision points.
3. It ignores cost, consequence, risk, task complexity, and whether the task is suitable or permitted.
4. Minutes per case × cases per week × 4.33 ÷ 60.
5. The units and relationship are unclear; it mixes labor capacity and error loss and omits build/run/oversight costs and residual risk.
6. Validation, abstention/exception handling, human approval where required, permission checks, duplicate protection, and logging.
7. Schema correctness checks structure, not factual correctness against the original source.
8. Structured inputs, a human review point, and a narrow start before expansion.
9. Existing workflow integration, data, buyer trust, distribution, price packaging, or support.
10. Legal classification depends on intended use, functionality, claims, and jurisdiction; a disclaimer alone is not decisive.

## 11. Necessary links and sites

The references below prioritize primary and official sources. Company pages confirm what a vendor says its product does; they do not independently prove accuracy, savings, or suitability.

### Risk management and workflow design

- [NIST AI Risk Management Framework](https://www.nist.gov/itl/ai-risk-management-framework) — voluntary cross-sector risk-management resource.
- [NIST Generative AI Profile (AI 600-1)](https://www.nist.gov/publications/artificial-intelligence-risk-management-framework-generative-artificial-intelligence) — risks and practices specific to generative AI.
- [n8n documentation](https://docs.n8n.io/) — workflow concepts, setup, and operational details.
- [Zapier workflow quick start](https://help.zapier.com/hc/en-us/articles/22234847450893-Zap-workflows-quick-start-guide) — current workflow basics.
- [Make Help Center](https://help.make.com/) — current platform documentation.

### Industry examples cited in the deck

- **Manufacturing and invoices:** [SAP AP automation overview](https://www.sap.com/resources/what-is-ap-automation); [Siemens predictive maintenance example](https://www.siemens.com/en-us/industries/consumer-packaged-goods/food-beverage/predictive-maintenance-in-production/); [AWS Panorama end-of-support notice](https://docs.aws.amazon.com/panorama/latest/dev/panorama-end-of-support.html).
- **Retail:** [Shopify product description generation and accuracy responsibility](https://help.shopify.com/en/manual/products/details/product-descriptions/shopify-magic); [Amazon AI review highlights](https://www.aboutamazon.com/news/retail/amazon-ai-generated-review-highlights); [Klarna’s first-month AI assistant claim](https://www.klarna.com/international/press/klarna-ai-assistant-handles-two-thirds-of-customer-service-chats-in-its-first-month/); [Klarna 2025 annual report filed with the SEC](https://www.sec.gov/Archives/edgar/data/2003292/000162828026038366/annualreport2025.htm).
- **Finance:** [Mastercard AI fraud protection](https://www.mastercard.com/gateway/payment-solutions/secure-payments/fraud-protection/ai-payment-fraud-solution.html); [JPMorgan Chase 2016 annual report](https://www.jpmorganchase.com/content/dam/jpmc/jpmorgan-chase-and-co/investor-relations/documents/2016-annualreport.pdf); [Lemonade claims process](https://www.lemonade.com/claims).
- **Legal:** [Harvey Contract Intelligence](https://www.harvey.ai/platform/contract-intelligence); [Thomson Reuters CoCounsel features](https://legal.thomsonreuters.com/en/products/cocounsel-legal/features); [DocuSign Agreement AI](https://www.docusign.com/en-gb/products/platform/ai).
- **Healthcare:** [Microsoft Dragon Copilot documentation](https://learn.microsoft.com/en-us/industry/healthcare/dragon-copilot/); [Epic AI Charting](https://www.epic.com/epic/post/epic-ai-charting-rolls-out-alongside-an-expanding-set-of-built-in-ai-capabilities/); [Ada intended-use and safety statement](https://ada.com/help/what-degree-of-liability-does-ada-accept/).
- **Logistics:** [Maersk AI-powered Trade and Tariff Studio](https://www.maersk.com/insights/digitalisation/2026/08/18/ai-powered-customs-management); [DHL Logistics Trend Radar 8.0](https://group.dhl.com/en/media-relations/press-releases/2026/ai-takes-action-while-people-remain-at-the-center-of-logistics-finds-dhl-logistics-trend-radar.html); [Uber Freight pricing](https://help.uber.com/freight/carrier/article/how-does-uber-freight-pricing-work?nodeId=58be903d-552e-41f8-8864-5d20ff4f6e39) and [load matching](https://www.uberfreight.com/en-US/blog/better-load-matching-with-ai).
- **Other examples:** [Duolingo Q1 2025 shareholder letter](https://duolingo.gcs-web.com/static-files/01420520-3377-4985-887b-55ed3c1e4fc5); [Unilever UK early-career hiring process](https://careers.unilever.com/en/uk-and-ireland-early-careers-industrial-placement-legal) (the page says AI is not used as a screening tool for that specific process).

### Healthcare, employment, and local data protection

- [HHS HIPAA Security Rule](https://www.hhs.gov/hipaa/for-professionals/security/index.html) — U.S. safeguards for electronic protected health information.
- [HHS HIPAA Privacy Rule](https://www.hhs.gov/hipaa/for-professionals/privacy/index.html) — U.S. privacy requirements for protected health information.
- [U.S. FDA Clinical Decision Support guidance](https://www.fda.gov/regulatory-information/search-fda-guidance-documents/clinical-decision-support-software) — U.S. software guidance; assess intended use and function.
- [U.S. EEOC employment tests and selection procedures](https://www.eeoc.gov/laws/guidance/employment-tests-and-selection-procedures) — employment selection considerations in the U.S.
- [Bangladesh Personal Data Protection Act, 2026](https://bdlaws.minlaw.gov.bd/act-print-1692.html), [National Cyber Security Agency laws and rules index](https://ncsa.gov.bd/pages/static-pages/6922e12a933eb65569e2a9f5), and [Bangladesh Laws database](https://bdlaws.minlaw.gov.bd/) — check the current official text and amendments; do not rely on an older ordinance page if it has been superseded.
- [EU Artificial Intelligence Act](https://eur-lex.europa.eu/eli/reg/2024/1689/oj/eng) — relevant only where the Act applies; check current implementation and obligations for the specific use.

### How to use these links

1. Start with the official law or framework for the jurisdiction where the system and affected people operate.
2. Open the product documentation to confirm current capability, supported integrations, and limits.
3. Search for an independent evaluation before treating a vendor metric as proven performance.
4. Ask the process owner and domain expert to validate the workflow and its failure cases.
5. Recheck this directory before deployment; dates, product features, laws, and platform packaging may change.

## 12. Final takeaways

- Measure the task before building.
- Describe steps, inputs, outputs, exceptions, and owners.
- Automate bounded volume work; keep accountable people responsible for judgment and consequential decisions.
- Validate against source evidence, allow the system to abstain, and route exceptions.
- Measure end-to-end quality, cost, time, adoption, and residual risk.
- Start with a narrow pilot and expand only when the evidence supports it.
- Treat company examples as case studies to investigate, not as guaranteed results to copy.

**Class deliverable:** one verified process document, one automation specification, a baseline and pilot plan, named review gates, and a tool choice that fits the real operating requirements.
