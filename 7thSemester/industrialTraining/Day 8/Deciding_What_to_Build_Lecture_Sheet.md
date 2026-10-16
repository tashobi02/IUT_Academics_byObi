# Lecture Sheet: Deciding What to Build

**Topic:** Moving from a problem hypothesis to a buyer, price, competitor map, and ranked feature list  
**Source deck:** `2nd Class.pdf`  
**Deck title:** *Class 2: Deciding What to Build*  
**Deck length:** 28 pages  
**Prepared:** 2026-09-24  
**Audience:** IUT undergraduate students, early builders, and Bangladesh-based founders  
**Central idea:** When AI makes polished prototypes cheap, appearance and feature volume are weak advantages by themselves. Choose a specific buyer and price, study the alternatives they already use, find the outcome they will pay for, and rank features by evidence of money, time, or risk saved.

> **How to read this sheet:** **Deck content** records what the page teaches. **Lecture interpretation** explains how to use the idea and where it can fail. **Verification note** distinguishes a useful heuristic from a claim that needs evidence. The web links and public pricing references were checked on 2026-09-24 and can change.

## 1. Learning objectives

By the end of this class, you should be able to:

1. Explain why cheaper prototyping makes differentiation, customer access, and reliable delivery more important.
2. Apply the ChatGPT test to decide whether a proposed feature is simply a prompt result or part of a product buyers may value.
3. Describe five product advantages that a chat window alone may not provide: customer data, a recurring workflow, integration, reliability, and owned distribution.
4. Define an ideal customer profile (ICP), distinguish the user from the buyer and approver, and connect each to a price point.
5. Compare possible price levels without treating the deck's example prices as validated demand.
6. Conduct a competitor teardown using positioning, pricing, target buyer, onboarding, reviews, ads, screenshots, and source links.
7. Separate direct competitors from substitutes, manual work, and the status quo.
8. Turn competitor feature lists into a frequency matrix and distinguish table stakes from a possible product opening.
9. Use landing page prototypes to test the promise before building the product.
10. Rank features by evidence that they save money, save time, or reduce risk.
11. Use AI models as bounded reviewers, preserve the differences between their roles, and make the final decision from verified evidence.
12. Produce the three deliverables due before Class 3: one evidence-backed ICP, a competitor teardown, and a ranked feature list with problem-sheet evidence.

## 2. Prerequisites and working rules

- Bring the context document and problem sheet from Class 1.
- Have access to an AI assistant, a spreadsheet or document table, and web browsing.
- Bring five competitors discovered during Class 1. The deck's live restaurant example names Rosuii, ChillyPOS, Nexchar, TMBill, and Loyverse.
- Use screenshots only for research and internal comparison. Do not copy protected logos, text, imagery, source code, or a competitor's exact branded design into your product.
- Use current public pricing pages. If a vendor has no public price, record “quote required” instead of guessing.
- Record currency, billing period, unit, branch count, fees, and the date for every price. “৳1,500/month” is incomplete if it is unclear whether the fee is per branch, per restaurant, or per user.
- A competitor's page is evidence of what the vendor claims, not proof that customers use the feature, trust the product, or get the claimed result.
- A feature appearing on many competitor pages is not proof that customers need it. A feature appearing on few pages is not automatically an opportunity.
- A quote is evidence that someone said something. It does not, by itself, prove frequency, market size, willingness to pay, or a solution requirement.
- Keep each claim labelled as a verified fact, estimate, assumption, recommendation, or unknown.

## 3. One-page lecture summary

### The decision workflow

```text
Problem evidence
    -> Choose a buyer and a price hypothesis
    -> Map products, manual work, and the status quo
    -> Compare promise, pricing, buyer, onboarding, reviews, ads
    -> Identify category expectations and possible gaps
    -> Test the promise with real buyers
    -> Rank features by money, time, or risk saved
    -> Build the smallest version that delivers the chosen outcome
```

### The five questions before building

| Question | Evidence to bring |
|---|---|
| Who will buy this? | A defined buyer and a row from the problem sheet |
| At what price and unit? | A price hypothesis with currency, period, and billing unit |
| What do they use today? | Named competitors, manual workarounds, and the status quo |
| Why might they switch? | A repeated pain, failed workaround, or important unmet job |
| What should be built first? | A short feature list ranked by evidence of value |

### The ChatGPT test

Ask whether a person can already get the promised result with one ordinary prompt and a little manual work. If yes, the prompt by itself is unlikely to be a defensible product. A product may still be valuable when it adds:

1. Customer-specific data the model does not already have.
2. A recurring workflow that runs at the right time without a fresh prompt.
3. Integration into the tools and permissions the customer already uses.
4. Reliable, checked output with clear recovery when the system fails.
5. A way to reach and retain buyers that the model provider does not give you.

These are hypotheses to investigate, not a universal list of necessary product features. A simple service, template, or manual workflow may still be the best first offer.

### The three artifacts

| Artifact | Minimum content |
|---|---|
| One ICP | One buyer, one price point, the job, current alternative, evidence, and buying route |
| Competitor teardown | Five competitors, all eight teardown steps, screenshots, a feature matrix, and a source on every claim |
| Ranked feature list | Feature, problem-sheet row, money/time/risk outcome, evidence strength, and priority |

## 4. Core concepts and frameworks

### 4.1 Prototype cost fell; product value did not become automatic

The deck's opening argument is that AI builders can produce polished interfaces quickly. That lowers the cost of creating a demo and also lowers the cost for competitors to imitate visible screens. It does not remove the harder work:

- finding the correct user and buyer;
- understanding local practices and exceptions;
- earning access to data and systems;
- reaching customers repeatedly;
- operating reliably during real work;
- supporting customers and handling failures;
- proving the result is worth its cost.

The statement “building got cheap” refers mainly to producing an initial interface or prototype. It should not be read as “a secure, accurate, supported, production-ready business is cheap to build.”

### 4.2 The ChatGPT test: feature versus product

The deck contrasts summarising meeting notes, which a person can ask a general chat assistant to do, with chasing every unpaid invoice and messaging clients, which may require access, a workflow, records, timing, and careful execution.

Use the test this way:

1. Describe the customer outcome without naming AI.
2. Try to get that outcome with a general assistant and a realistic prompt.
3. List everything the customer would still have to do manually.
4. Identify where data, repeated execution, integrations, checking, permissions, or support are needed.
5. Ask whether those additions create enough value to justify a separate product and price.

**Important correction:** “If one prompt gets the result, they won't pay” is a provocation, not a law. People pay for time saved, confidence, convenience, compliance, workflow fit, support, or a result they cannot reliably produce alone. A simple prompt can also become a paid service or packaged workflow. Test payment rather than infer it from the prompt test.

### 4.3 Five capabilities beyond a chat window

| Capability | What it adds | Questions to validate |
|---|---|---|
| Customer-specific data | Context the general model has not seen | Can the customer lawfully provide it? Is it accurate and current? |
| Recurring workflow | Work happens at a trigger or schedule | Does it run at the right time? What should happen when an exception occurs? |
| Integration into existing tools | Less copying and pasting; work lands where it is used | Which system is authoritative? What permissions are needed? |
| Reliability | Similar quality, checks, logs, and recovery each time | What error rate is acceptable? Who reviews uncertain cases? |
| Owned distribution | A path to reach buyers directly | Can you reach buyers without relying entirely on a model provider or marketplace? |

Integrations or private data do not automatically form a “moat.” Competitors can build integrations, and data can be incomplete, sensitive, or difficult to maintain. Advantage depends on customer trust, execution, learning, and the cost of switching as well as technical access.

### 4.4 Buyer, user, approver, and ICP

An **ideal customer profile (ICP)** is a focused description of the type of organization or person most likely to receive meaningful value and buy the product. It should be specific enough to guide research and distribution.

| Role | Meaning | Restaurant billing example |
|---|---|---|
| User | Person doing the workflow | Cashier or accounts clerk closing the shift |
| Buyer | Person or organization paying | Restaurant owner or finance manager |
| Champion | Person who wants the change and helps evaluate it | Manager who repeatedly reconciles discrepancies |
| Approver | Person who authorizes the purchase or data access | Owner, head office, or finance lead |

These roles may be the same person in a small business. Do not assume that because a cashier has pain, the owner will pay, or that the owner can approve sharing transaction data.

### 4.5 Price is a hypothesis about buyer and value

The deck asks students to generate three potential buyer profiles at low, medium, and high price points. Its slide uses `$10`, `$100`, and `$1,000` as an example for an individual, a small-team lead, and a company. Those are prompts to examine different buying situations, not recommended price points.

For every price hypothesis, specify:

- currency: BDT, USD, or another currency;
- period: per month, year, transaction, or project;
- unit: per user, branch, company, or usage volume;
- buyer and approver;
- current alternative and current cost;
- value delivered and evidence for it;
- procurement steps and sales channel;
- extra charges such as onboarding, hardware, tax, payment fees, or support.

The price should shape the ICP and research plan. It should not decide the segment by itself. Three prices do not guarantee three distinct buyers; validate each with interviews, observed behavior, a trial, and a credible payment or commitment.

### 4.6 Competitors include more than software vendors

For a buyer, competition is any alternative that currently gets the job done or helps them tolerate the pain.

| Alternative type | Example for restaurant cash reconciliation |
|---|---|
| Direct competitor | A POS or accounting product that records sales and supports closing reports |
| Adjacent product | A bookkeeping or payment reconciliation tool that handles part of the workflow |
| Manual workaround | Cash book, spreadsheet, calculator, notebook, or staff double-check |
| Outsourced workaround | Accountant, bookkeeper, or supervisor doing the closing task |
| Status quo | Accepting a mismatch, postponing reconciliation, or absorbing a loss |

The customer's current process is often the most important competitor. A software list that excludes notebooks, phone calls, spreadsheets, or “do nothing” misses the real choice.

### 4.7 Eight teardown steps

The deck's teardown sequence is:

| Step | Action | Output |
|---:|---|---|
| 1 | Read the context brief and ICP | A bounded target market and task |
| 2 | Find ten competitors | Candidate list including direct, adjacent, and manual alternatives |
| 3 | Record positioning, pricing, and buyer | A comparable row for each candidate |
| 4 | Screenshot the homepage and pricing page | Dated source evidence |
| 5 | Pull 20 reviews per product where available | Review corpus with source and date |
| 6 | Build a feature matrix: common versus missing | Counts plus notes about definitions and scope |
| 7 | Put a source link on every claim | Auditable teardown |
| 8 | Save it and compare it with the last run | Change log for prices, features, and messaging |

The Class 2 homework specifies a teardown of five competitors. Use the eight-step method for those five; treat the slide's ten-competitor step as the broader research pipeline when time and market coverage allow. If a competitor has fewer than 20 reviews or no public reviews, record the actual number or “none found in sources checked.” Never invent review rows.

### 4.8 Read the feature count carefully

The deck offers a useful first interpretation:

| Count among competitors | Deck interpretation | How to use it responsibly |
|---|---|---|
| Present in 8 of 10 | Likely table stakes; match the category expectation | Confirm the same buyer needs it and compare quality, not just presence |
| Present in 1 or 2 | Possible opening or differentiation | Interview buyers and test the job; scarcity can mean low demand |
| Present in none | Check whether anyone wants it | Investigate before building; it may be a new need, a poor idea, or a feature hidden under another name |

These thresholds are a teaching heuristic, not a validated statistical cutoff. Normalize feature definitions before counting. “Offline support,” for example, can mean anything from reading cached data to processing transactions with conflict-safe sync.

Feature frequency does not measure use, quality, or importance. The restaurant teardown notes that inventory appears across all five products, but the buyer may never open it. Check what the target role actually uses during the task.

### 4.9 Positioning and the promise

**Positioning** is the place a product occupies in a buyer's mind relative to their alternatives. The deck maps a homepage headline to one promise. A useful promise names:

1. the target buyer;
2. the important job or pain;
3. the outcome;
4. the reason to believe it can happen.

Example structure:

> For **[specific buyer]** who needs to **[job]**, **[product/service]** helps **[measurable outcome]** by **[credible mechanism or proof]**.

Avoid unproved superlatives such as “best,” “smartest,” or “AI-powered.” A promise is a hypothesis until the intended buyer understands it and acts on it.

### 4.10 A competitor gap is a positioning hypothesis

The deck's follow-up question compares five competitors' pages and asks what each assumes the user knows. Its example says they are written for a buyer at a desk rather than a restaurant owner at 11 pm. This may suggest a specific angle: help an owner understand and close the day when they are tired and away from a desk.

Treat the gap as a hypothesis with at least three checks:

- Do owners actually use the product at that time and place?
- Is the problem the wording of the pitch, the interface, the workflow, or the underlying records?
- Would the owner pay for a change, and what outcome would count as success?

The gap in a vendor's marketing page is not automatically a product gap. Some competitors may solve the issue through onboarding, customer support, a mobile app, or an offline process that is not obvious from a homepage.

### 4.11 Test the promise before building the product

The deck recommends making three landing page versions, showing them to five real buyers, and keeping one. Its warning is to test the promise, not the colours.

Use each version to express a different value proposition or buyer segment. Ask people to explain:

- who they think the product is for;
- what it helps the person do;
- what they think happens after clicking;
- what sounds implausible or unclear;
- what they would use instead.

Five conversations are useful for qualitative learning, not for a statistically reliable conversion-rate claim. Avoid implying that a service already exists when it does not. Use a clear concept-test or waitlist description and do not collect unnecessary personal data.

### 4.12 Trust is observable, but not just visual polish

When asked which competitor looks trustworthy, identify specific signals rather than saying “the design looks better.” Possible signals include:

- a clear price and billing unit;
- credible customer proof with verifiable context;
- understandable setup and support steps;
- realistic claims and transparent limitations;
- local language, payment, tax, or workflow fit;
- security, privacy, data-export, and cancellation explanations;
- a product experience that works on the devices customers use.

Treat each as a hypothesis. Logos and testimonials are selected by the vendor; they are not independent proof of performance. A polished interface can create confidence before the product earns it.

### 4.13 What people pay for: money, time, or risk

The deck groups reasons to pay into saving money, saving time, and removing risk. Each candidate feature should link to evidence in the problem sheet.

| Value type | Possible measurement | Example evidence |
|---|---|---|
| Saves money | Reduced loss, rework, fees, labour cost, or missed sales | A dated record or quote naming a recurring cost |
| Saves time | Minutes per task × frequency × people involved | Observed task timing and repeated workflow evidence |
| Removes risk | Lower chance or impact of an error, delay, fraud, or compliance issue | Incident records, near misses, or a decision-maker's stated exposure |

Illustrative calculations:

\[
\text{monthly time value} = \text{hours saved per month} \times \text{appropriate hourly cost}
\]

\[
\text{expected risk cost} = \text{probability of loss} \times \text{impact of loss}
\]

These calculations are estimates. Mark their assumptions and avoid converting “time saved” directly into a price unless the buyer agrees that the time is valuable and can be redeployed.

### 4.14 Use models as reviewers; keep a human decision-maker

The deck's five-pass story has Claude draft a teardown, Claude notice broken English, GPT redesign the questions, Claude find gaps in GPT's plan, and the human decide. The learning is that models can contribute different checks; no one model should own the decision.

For a repeatable review, give each pass a defined role:

1. Extract claims and sources from competitor pages.
2. Check the extraction for omissions and ambiguous terms.
3. Compare features and positioning across vendors.
4. Identify unsupported claims, gaps, and counterexamples.
5. Have a human verify decision-critical items and choose the next test.

Model agreement is not evidence of truth. Different model brands may use overlapping data or search indexes, and the same model may repeat its earlier mistake. The strongest cross-check often comes from a source page, a customer, an observed workflow, or a paid test.

### 4.15 Current competitor snapshot from the live example

The deck's Class 2 live teardown uses a small Dhaka restaurant billing idea priced at an illustrative **৳1,500 per month**, for owner-run businesses with one to three outlets. It reports five names: Rosuii (the deck table appears to spell it “Rosii”), ChillyPOS, Nexchar, TMBill, and Loyverse.

Current public pages checked on 2026-09-24 show:

| Product named in the deck | What its public page currently shows | What remains to validate |
|---|---|---|
| Rosuii | Official page lists a free plan and BDT plans including ৳500, ৳1,200, and ৳2,500 per month. | Whether it handles the exact end-of-day cash-versus-bills workflow; what users actually use; support and hardware costs |
| ChillyPOS | Public page lists a basic per-branch plan at ৳1,000/month plus installation and training fees; it also lists a premium plan. | Exact plan terms, what the displayed struck-through amount means, actual onboarding cost, and the relevant reconciliation workflow |
| Nexchar | Public pricing lists Free, $5, $10, and $20 monthly tiers; its Bangladesh page advertises retail/POS use and a local office contact. | Currency/BDT checkout, restaurant workflow fit, payment and support details for a specific Dhaka customer |
| TMBill | Public pages describe a broad restaurant operating system and invite demo or sales contact; no price was visible on the inspected main page. | Current Bangladesh price, local support and integrations, implementation and hardware costs |
| Loyverse | Core POS features are listed as free, with optional paid USD add-ons such as longer sales history, employee management, and advanced inventory. | Bangladesh payment and tax fit, total needed add-on cost, and fit with the exact local cash-closing job |

**What this changes:** the live example should not be interpreted as an empty category. The named products and current public pages establish visible alternatives; some are free or priced close to the illustrative ৳1,500. That does **not** prove one of them solves the quoted cash mismatch, nor that every one is a direct competitor. It means the first build decision must compare the exact workflow, price unit, onboarding cost, and customer behavior before claiming an opening.

**Evidence-quality warning:** vendor websites are first-party evidence about advertised features and pricing. They are not independent evidence of customer satisfaction or actual results. Product pages, prices, add-ons, and local availability may change.

## 5. Reusable templates and prompts

### 5.1 Buyer and price hypothesis

```markdown
# Buyer hypothesis - version/date

- Buyer organization/person:
- Daily user:
- Champion:
- Approver:
- Job to be done:
- Current product or workaround:
- Problem-sheet row IDs:
- Proposed price:
- Currency and period:
- Billing unit (user/branch/company/usage):
- Buying route and time to decision:
- What must be true for this buyer to pay:
- What I still need to verify:
```

### 5.2 Prompt to develop three buyers

```text
Using my context document and problem sheet, describe three possible
buyer profiles at [price A], [price B], and [price C] per [period and unit].
Use [currency]. For each, state:
- who uses, buys, champions, and approves;
- the job and current alternative;
- where the buyer can realistically be reached;
- how the buyer discovers, evaluates, and approves a purchase;
- the exact problem-sheet row IDs supporting each claim;
- what is an assumption or unknown.

Do not invent a quote. If the sheet does not support a statement, say
"not established by current evidence" and suggest the cheapest check.
Do not decide that a higher price automatically means a larger company.
```

### 5.3 Competitor teardown table

| Competitor | Type | Promise | Buyer/user | Price and unit | Onboarding to first value | Common features | Reviews/complaints | Ads | Source/date | Unknowns |
|---|---|---|---|---|---|---|---|---|---|---|
|  | Direct/adjacent/manual/status quo |  |  |  |  |  |  |  |  |  |

### 5.4 Teardown prompt for AI

```text
Read my context brief and target ICP. Research the five named competitors
below using current public sources. For each one, inspect positioning,
pricing, target user/buyer, onboarding, reviews, and ads where available.

Competitors: [names and official websites]
Research date: [date]
Geography and customer segment: [scope]

For every claim, include the direct source URL and exact supporting
sentence or visible data. Record date, price currency, period, and billing
unit. Separate first-party marketing claims from independent user evidence.
Do not fill missing prices or reviews from inference. Mark them unknown.
Create a feature matrix and explain how each feature was defined.
Include manual work and the status quo as alternatives. Respect each
website's access terms; do not bypass login or scraping controls.
```

### 5.5 Feature ranking sheet

| Feature | Buyer job | Problem row/quote | Money saved | Time saved | Risk reduced | Frequency | Confidence | Build/test first? |
|---|---|---|---:|---:|---:|---|---|---|
|  |  |  |  |  |  |  |  |  |

If there is no problem row, mark the feature **assumption / nice-to-have** until new evidence supports it. Some enabling, safety, or compliance features may not appear in customer quotes; document their separate rationale rather than pretending a quote exists.

### 5.6 Three landing page concept test

```text
Create three concept-page drafts for this buyer and problem.
Keep the visual style simple and comparable. Change the promise or
positioning angle between versions, not just the colours.

For each version, show:
- target buyer;
- headline and one-sentence promise;
- proof or evidence we actually have;
- one clear next action;
- claims that still need verification.

Do not claim the product exists, has customers, or produces results unless
my evidence says so. Make the page appropriate for a concept test.
```

### 5.7 Model review protocol

| Pass | Reviewer task | Output to preserve |
|---|---|---|
| 1 | Extract facts and claims from source pages | Claim table with URLs and dates |
| 2 | Check evidence and detect missing fields | Corrections and unknowns |
| 3 | Compare positioning and features | Matrix with definitions |
| 4 | Challenge the proposed opportunity | Counterexamples and cheapest tests |
| 5 | Human decision | Decision, evidence, and next action |

For reproducibility, save the model/provider, model version when shown, prompt, source set, and research date. Keep private customer information out of third-party model workflows unless you have permission and an appropriate data arrangement.

## 6. Detailed page-by-page lecture notes

### Page 1 - Class 2: Deciding what to build

**Deck content:** The class subtitle says one idea should move from a guess to a buyer, a price, and a list of competitors.

**Lecture interpretation:** Class 1 gathered context and problem evidence. Class 2 narrows the decision. The work is not to generate a longer feature list; it is to choose whose problem to serve, what value to promise, and which alternatives already compete for the buyer's money or attention.

**Checkpoint:** Write one candidate buyer, the problem-sheet row that supports them, and the current alternative. If any field is missing, that is a research task.

### Page 2 - Open one competitor pricing page

**Deck content:** Students are asked to open one pricing page and note what surprised them.

**Lecture interpretation:** Pricing pages expose more than the number. Look for billing units, feature gates, free plans, onboarding fees, trial limits, support levels, and words the vendor uses to define its buyer. Compare the page with what the buyer says they do today.

**Exercise:** Capture a dated screenshot. Record the price, currency, period, unit, tax or setup fees, and the source URL. Write one question the page cannot answer.

**Verification note:** A pricing page shows the vendor's published offer. It does not establish the final negotiated price or whether the product is used in your target segment.

### Page 3 - Section 1: What sells now

**Deck content:** A section divider introduces the product and market changes that affect what can sell.

**Lecture interpretation:** The next pages challenge interface-only differentiation. Product selection must consider how quickly competitors can produce a similar prototype and what part of the customer workflow remains difficult to copy or deliver.

### Page 4 - Building got cheap; so did every competitor's

**Deck content:** The slide contrasts a past when building was hard and competitors were few with current AI builders such as Lovable, Bolt, and v0 that can produce polished UI quickly. Its rule is that a thin MVP may be acceptable, but a bad-looking one is less acceptable now.

**Lecture interpretation:** This is a strategic shift: a demo is easier to make, so the customer can compare more polished alternatives. Use visual quality to remove avoidable friction, then differentiate through customer fit, workflow, integration, reliability, distribution, and results.

**Verification note:** The deck's “an afternoon” and “in hours” timing is illustrative and task-dependent. A generated interface is not a validated product, production system, or tested customer outcome. Tool features, pricing, and speed change.

**Study prompt:** Name one feature of your idea that is visible in a screenshot and one advantage that would require access, repeat use, or trust.

### Page 5 - The ChatGPT test

**Deck content:** A meeting-notes summary is presented as something available in a free chat; chasing unpaid invoices and messaging a client is framed as a result worth paying for. The headline says that if one prompt gets the result, the user will not pay.

**Lecture interpretation:** Ask what remains after the model generates text. The invoice task may require current invoice records, overdue rules, customer history, message approvals, a send channel, and a dependable follow-up process. The value could lie in doing the complete job safely, not merely writing a message.

**Verification note:** The binary “free prompt versus paid product” is a teaching shortcut. Buyers may pay for a simple prompt packaged with expertise, convenience, confidentiality, or support. Validate willingness to pay with behavior.

### Page 6 - Five things a chat cannot do

**Deck content:** The slide lists customer-owned data, an unattended recurring workflow, a workflow inside the tools customers use through APIs rather than copy-and-paste, reliability, and owned distribution.

**Lecture interpretation:** This is a productization checklist. For each candidate advantage, identify the exact customer action or outcome it changes. “Has API integration” is not a benefit by itself; it matters if it reduces errors or steps in a workflow the buyer values.

**Verification note:** General assistants continue to add connectors, scheduled work, and reliability features. Re-run the ChatGPT test over time. Data access and integration are not automatically defensible and must be permissioned.

### Page 7 - Clone one competitor

**Deck content:** Students are told to use one of their five competitors' homepage and pricing page to write a rebuild specification containing screens, features, and pricing tiers.

**Lecture interpretation:** Use the exercise as a teardown, not as a plan to copy the competitor's brand or protected work. Extract the buyer journey, information architecture, feature promises, plan boundaries, and onboarding assumptions. Then write an original product specification for the job.

**Safe and useful output:**

- list screens and what decision each screen supports;
- list behaviors and inputs/outputs;
- record public price and its unit;
- identify evidence shown on the site;
- note what is not explained;
- propose one difference grounded in your problem sheet.

**Verification note:** Public visibility does not grant permission to republish text, imagery, logos, or source code. Keep screenshots private for analysis and create original wording and design.

### Page 8 - Agency Handy and the next model update

**Deck content:** The sequence moves from a proposal and invoice maker, to AI-generated proposals becoming free in ChatGPT, to an MCP layer letting Claude or ChatGPT work with Agency Handy data, and then to building an assistant into the product. The key line is that the feature got cheap but the data behind it did not.

**Lecture interpretation:** The case distinguishes a generic content-generation feature from a contextual workflow attached to customer records. An integration can preserve product value by helping a model act on the customer's real information inside an existing workflow.

**Verification note:** “The data did not get cheap” is a case-specific claim, not a universal fact. Data quality, permissions, portability, and alternative integrations affect its value. MCP access must be deliberately scoped and protected; it does not automatically make a product secure or unique.

**Reflection:** What could the next model update make pointless in your product? What customer-specific data or workflow would remain useful afterward?

### Page 9 - Feedboss: paid versus liked

**Deck content:** The slide says the team built a smart growth assistant that tuned posts for reach, while customers paid for simple posts in their own voice with good visuals. It says the customer's voice is their data and a chat window does not have it. The clever AI was for the builders; simple AI was for the customer.

**Lecture interpretation:** Product sophistication and buyer value are different measures. A technically clever feature can be less valuable than a reliable, ordinary task that helps the customer publish consistently. A customer's voice may be captured through examples, preferences, and revision history, but only with clear control over the content and data.

**Verification note:** The slide reports the presenter's experience. Treat it as a useful case, not proof that every customer prefers simplicity or that every model lacks style context.

**Exercise:** For each idea feature, label it “buyer asked for,” “user behavior shows it,” “builder likes it,” or “unknown.”

### Page 10 - Run the ChatGPT test on your own idea

**Deck content:** Students are asked whether their idea survives the test.

**Lecture interpretation:** For each feature, simulate the result with a general assistant. Then record the manual work, missing data, error risk, and repeatability limitations. A surviving product idea should have a meaningful paid outcome after the generic model response is accounted for.

**Prompt:** “Show me how a customer could get this result with a general AI chat and manual steps. Then list exactly what my product would still need to do better, with evidence from my problem sheet.”

### Page 11 - Section 2: Research you can finally do

**Deck content:** A section divider introduces AI-supported competitor research.

**Lecture interpretation:** AI can make repetitive page review, extraction, and comparison faster. The research remains only as good as its source coverage, definitions, and verification.

### Page 12 - Ask for three buyers, not one

**Deck content:** The deck says asking AI for one ICP can produce a confident single profile; instead, ask for three at `$10`, `$100`, and `$1,000` per month. It sketches an individual, a small-team lead, and a company, with different discovery and approval routes. The rule is: pick the price, then find who pays it.

**Lecture interpretation:** The useful insight is that price, buyer role, procurement, and acquisition channel interact. The slide values are sample scenarios, not market facts or a pricing recommendation. In Bangladesh, test locally meaningful BDT values as well as any international target, and specify whether pricing is per branch, person, or business.

**Verification note:** Buyers do not sort neatly into one price point. Individuals may have large budgets; small firms can require formal approval; companies may reject a low-cost tool if security or procurement does not fit.

### Page 13 - Prompt for three buyer profiles

**Deck content:** Students are asked to use the context doc and problem sheet to describe buyers at three monthly prices, including who they are, their current tools, where they gather, and how they decide. Every claim should be backed by a problem-sheet row.

**Lecture interpretation:** The prompt requires traceability and forces the model to use the user's evidence. Improve it by asking the model to label unsupported items as unknown and cite row IDs rather than fabricate quotes.

**Verification note:** A problem-sheet row may support the problem but not the buyer's channel or procurement path. Label these as assumptions until separately verified.

### Page 14 - Six competitor dimensions

**Deck content:** The slide maps six inputs to insights: homepage headline to positioning; pricing screenshot to side-by-side tiers; case studies and logos to target buyer; recorded signup to onboarding and first value; G2, Capterra, and app stores to complaint clusters; Meta and Google ad libraries to current messaging.

**Lecture interpretation:** These are complementary evidence sources. Review each for selection bias:

| Source | What it can suggest | Limitation |
|---|---|---|
| Homepage | Intended promise | Marketing language may overstate performance |
| Pricing page | Published plan boundaries | Negotiated discounts and hidden costs may differ |
| Case studies/logos | Claimed customer segment | Vendor-selected examples; verify independently |
| Onboarding walkthrough | Steps to first value | A demo or your own signup may not match every customer |
| Reviews | Reported praise and complaints | Extreme, self-selected, and platform-specific |
| Ad libraries | Messages a vendor is currently testing or serving | An ad running does not prove it is profitable or effective |

**Verification note:** “The message that works” is a hypothesis from ads, not an observed conversion rate. Google and Meta transparency tools reveal ads in defined scopes; they do not reveal full spend or ROI.

### Page 15 - The teardown in eight steps

**Deck content:** The process reads the brief and ICP, finds ten competitors, records positioning/pricing/buyer, screenshots homepage and pricing, pulls 20 reviews each, builds a common-versus-missing feature matrix, puts a source link on every claim, and saves/comparers the run in a project rather than a chat.

**Lecture interpretation:** The durable value is a dated, reproducible record. Saving a report in a project or versioned file makes comparisons possible and reduces context drift. Keep the raw source and extracted claim distinct.

**Verification note:** “20 reviews each” is a desired sample, not a license to invent data or pretend the sample is representative. If public reviews are sparse, report that absence and use interviews or site visits.

**Practical standard:** For the five assigned competitors, complete the eight steps with current evidence. If time allows, expand discovery to ten to reduce the chance of missing a major substitute.

### Page 16 - Live teardown: five restaurant billing competitors

**Deck content:** The live task is a billing tool for small Dhaka restaurants at an illustrative ৳1,500/month, for owner-run businesses with one to three outlets, based on the quote “Every night the cash doesn't match the bills.” The slide lists Rosuii, ChillyPOS, Nexchar, TMBill, and Loyverse and shows search terms or discovery paths. It says the research showed what it searched and what it could not find: no local tool had real reviews online. A warning says today's screenshot is more reliable than old prices.

**Lecture interpretation:** This is a strong demonstration of search transparency and a useful warning about stale pricing. It is also a snapshot, not a complete competitor census. Current official public pages checked on 2026-09-24 already list Rosuii plans around the example price and ChillyPOS at a lower per-branch monthly price before setup/training fees. Nexchar and Loyverse publish free or low-cost plans; TMBill directs visitors toward a demo. Therefore, “no local tool has real reviews online” must remain a claim about the pages and search path checked at that time, not an established market fact.

**Do not jump from category competition to problem validation:** POS competitors establish visible alternatives, not that they solve the exact discrepancy between expected bills and counted cash. Interview owners and staff, observe a close, and trace how cash, bKash/Nagad, refunds, discounts, delivery platforms, staff meals, and petty cash enter today's records.

**Verification note:** Company pricing pages are first-party sources. Confirm plan unit, fees, taxes, current terms, and fit by requesting a demo or asking a target buyer. The current competitor list and prices are a dated snapshot, not an endorsement.

### Page 17 - Hand the screenshots to the model

**Deck content:** Students ask what repeats across five competitor pages and what each assumes the user knows. The example answer says all five are written for a buyer at a desk and none for the owner at 11 pm. The rule says the gap in their pitch is your pitch.

**Lecture interpretation:** The prompt generates a positioning hypothesis: perhaps the product should support a tired owner closing the day away from a desk. Check the reality before adopting it. The actual gap may be reconciliation accuracy, training, connectivity, trust, price, or support rather than the page's wording.

**Follow-up questions:**

- What exact evidence on each page supports the model's comparison?
- Which target role and task are absent from the pages?
- Does an app, demo, or customer support process already address the supposed gap?
- Can five owners confirm that the problem matters at closing time?

### Page 18 - Section 3: What the category expects

**Deck content:** A divider introduces category expectations and the fact that buyers compare a new product with the last tool they used.

**Lecture interpretation:** Category knowledge helps meet basic expectations. A product is judged against the buyer's habits and alternatives, not only against its own feature list.

### Page 19 - Feature lists in, a count out

**Deck content:** The slide asks AI to count competitor features. It interprets presence in 8 of 10 as table stakes, 1 or 2 as a possible opening, and none as a reason to check whether anyone wants the feature. In the restaurant example, inventory appears in all five competitors, but the buyer may never open it.

**Lecture interpretation:** Counting is useful for spotting category conventions and potential differentiation. Before counting, define the feature and verify that each page actually supports the same capability. A vendor may use “inventory” to mean basic item counts while another offers recipe-level depletion.

**Verification note:** The numeric thresholds are heuristics. The most important question is buyer behavior. Ask what the target user opens, uses, trusts, and pays for during the specific workflow.

### Page 20 - AI designs the average

**Deck content:** A generic prompt to design a SaaS landing page is shown producing a familiar purple gradient and generic hero. A better input combines the ICP, three competitor screens, and what to stand apart from. The rule is to fit in on layout and stand out on the promise.

**Lecture interpretation:** Standard layout conventions can make a page easy to understand; distinctive positioning should come from the customer and offer. Give an AI builder reference pages, visual constraints, buyer context, and an original promise. Do not copy a competitor's protected brand assets or exact copy.

**Checkpoint:** Can a buyer understand who the product is for and what changes in five seconds? If not, revise the promise before adding polish.

### Page 21 - Three landing pages before one line of product

**Deck content:** The workflow is to use v0 or Claude for design, make three versions in an hour, show five real buyers, and keep one. The warning is to test the promise, not the colours.

**Lecture interpretation:** The fast artifacts are disposable research tools. Vary the value proposition or buyer, hold the visual complexity roughly constant, and ask for a concrete reaction. “Which colour do you like?” rarely tests willingness to pay.

**Verification note:** Five buyer conversations can surface confusion and objections. They do not establish statistically reliable preference or demand. Do not say a landing page test proves the market.

### Page 22 - Which competitor looks most trustworthy?

**Deck content:** The page asks which competitor appears trustworthy and what creates that impression.

**Lecture interpretation:** Convert the impression into observable factors: clear pricing, coherent workflows, relevant local proof, transparent limitations, support routes, security and data information, and a usable interface. Then ask target buyers which of these changes their willingness to try or pay.

**Exercise:** Pick one site and mark three evidence-based trust signals and two unanswered questions. Separate “looks trustworthy” from “has earned trust through delivery.”

### Page 23 - Section 4: Making the call

**Deck content:** A divider moves from research into feature and product decisions.

**Lecture interpretation:** The decision should now be constrained by buyer evidence, competitor findings, and a stated outcome. It is the stage for ranking and pruning, not adding every interesting capability discovered in research.

### Page 24 - The feature people pay for

**Deck content:** The slide presents three reasons people pay: saves money, saves time, removes risk. It asks students to back every feature with a quote from the problem sheet and warns that AI may invent supporting quotes; each quote must be checked against the sheet.

**Lecture interpretation:** Treat a feature as a proposed mechanism for a user outcome. For each, ask who gets the benefit, how often, how much, and what evidence establishes it. Trace quotes to row IDs and verify exact wording.

**Important refinement:** A quote supports that a person said something; it may not prove a measured saving or broad demand. Use observation, records, and a pilot to estimate actual impact.

### Page 25 - Righted asked AI the wrong questions

**Deck content:** Two generic prompts about agency client portals are contrasted with contextual questions from a freelancer becoming an agency and a small agency struggling with invoicing. The rule is: do not template for AI; give it context and let it write.

**Lecture interpretation:** Search using the user's vocabulary and real situation, not only category keywords. Generic terms can return vendor marketing pages; the problem phrasing may surface alternative workflows, discussions, and workarounds.

**Verification note:** Natural phrasing improves query relevance in some cases but does not guarantee comprehensive results. Use synonyms, category terms, buyer language, and direct source checks. Structured templates remain valuable for comparing the results after discovery.

### Page 26 - Neither model got it right alone

**Deck content:** The five-pass sequence shows Claude drafting, Claude catching broken English, GPT redesigning the questions, Claude finding gaps in GPT's plan, and the human deciding. OpenRouter is offered as one key to compare multiple models. The warning is that agreement is not proof and disagreement is where learning happens.

**Lecture interpretation:** Assign different bounded jobs to the reviewers and preserve a human owner for the decision. For example, extraction, completeness check, alternative generation, and evidence challenge. OpenRouter can simplify model access, but it introduces its own pricing, routing, privacy, provider, and availability considerations.

**Verification note:** This is a narrated process example, not a controlled comparison showing one model is generally better. A second model can repeat the first model's error. Check disagreement against primary sources or customers.

### Page 27 - Rank your features

**Deck content:** Students rank features by money, time, or risk saved, cite a problem-sheet row for each, mark a feature as nice-to-have when it has no quote, then run the ChatGPT test on every feature.

**Lecture interpretation:** The rule protects against building features the founder finds exciting but customers have not asked for. Use row IDs and evidence strength. If a feature is necessary for privacy, reliability, or safe operation but has no customer quote, mark it as an enabling requirement with a separate technical or ethical rationale.

**Decision record:** Include the feature, intended buyer, mechanism, evidence, estimate, uncertainty, smallest test, and stop condition.

### Page 28 - Before next class

**Deck content:** Three deliverables are required: one ICP with a buyer, one price point, and evidence attached; a teardown of five competitors covering the eight steps; and a ranked feature list with every feature backed by a quote. The next class is building.

**Lecture interpretation:** These artifacts translate research into a build brief. Each deliverable should be concise enough to guide a prototype and traceable enough to revise when new information appears.

| Deliverable | Ready when |
|---|---|
| One ICP | One buyer and price unit are named; the problem and current alternative have traceable evidence |
| Teardown | Five products or alternatives have dated sources, pricing, screenshots, available reviews, and a comparable feature matrix |
| Ranked feature list | Each feature has a problem row or a clearly labelled enabling rationale; nice-to-haves are separated |

**Verification note:** “Every feature backed by a quote” should not lead to fabricated quotes. Where a feature lacks a quote, label it an assumption or justified requirement and plan a validation step.

## 7. Guided practical: the Dhaka restaurant billing example

### Problem hypothesis

The deck's example is a small billing tool for owner-run Dhaka restaurants with one to three outlets, at an illustrative ৳1,500 per month. The evidence phrase is: “Every night the cash doesn't match the bills.”

Keep the statement as a hypothesis. It could describe several different problems:

- POS sales totals differ from cash drawer count;
- bKash/Nagad settlements are delayed or recorded incorrectly;
- refunds, discounts, voids, or delivery-platform adjustments are missed;
- cash is used for petty purchases or staff meals without records;
- duplicate or incomplete bills are created;
- the owner cannot see who changed or voided an order;
- the closing procedure is inconsistent across staff or shifts.

### Step 1 - Define the buyer roles

Interview the owner, cashier, and person who closes the books if those are different people. Ask who counts, who enters, who reconciles, who can approve a tool, and who would have to change their routine.

### Step 2 - Observe a real closing workflow

With permission, record the steps rather than just the final mismatch:

```text
Orders and bills -> payment method -> refunds/discounts/voids
-> drawer and digital settlement checks -> expenses and adjustments
-> closing report -> exception investigation -> owner decision
```

For each step, note the source record, actor, time, handoff, and likely error. Do not photograph customer records or payment details without explicit permission.

### Step 3 - Map competitors and substitutes

Start with the five deck examples: Rosuii, ChillyPOS, Nexchar, TMBill, and Loyverse. Add the actual tools and manual alternatives used by the interviewee. Do not count a vendor as a direct competitor only because it says “POS”; compare the specific closing task.

### Step 4 - Test the price unit

Compare the illustrative ৳1,500/month with current alternatives. Determine whether the buyer thinks in monthly fee per outlet, setup fee, device purchase, or staff labour. Ask what they already pay and what the mismatch currently costs.

### Step 5 - Test the promise

Draft three distinct promises, for example:

1. Close the cash drawer faster.
2. Find which payment or bill created a daily mismatch.
3. See sales, cash, mobile payments, and adjustments in one clear closing report.

Show the concepts to real owners and staff. Ask them to explain what they understand and what evidence they would require. Do not imply a working product exists if it does not.

### Step 6 - Rank the first features

Potential features might include an end-of-day reconciliation checklist, payment-method summary, exception flag, audit log, offline mode, or an integration. Do not treat this list as a build specification. Each feature needs a specific observed workflow and a value hypothesis.

### Step 7 - Define a manual test

Before coding, offer to reconcile a limited sample manually using anonymized or permissioned records. Measure time, error discovery, missing information, and whether the owner uses the result. Agree what data can be handled and deleted.

### Step 8 - Set a stop rule

Example stop rules:

- stop if the mismatch cannot be diagnosed from records the buyer is willing and able to provide;
- stop if current POS tools already resolve it with a setting or report;
- stop if owners report little cost or urgency and will not try a manual service;
- change direction if staff experience the problem but the buyer will not fund a solution;
- continue only if repeated observations show an important, reachable workflow and a credible path to payment.

## 8. Exercises and assessment

### Exercise A - ChatGPT test

Choose one feature from your idea. Try to achieve its promised result with a general chat assistant and a realistic prompt. Record:

1. What the model did well.
2. What information it lacked.
3. What the user still had to do.
4. What can go wrong if the result is inaccurate.
5. What a paid product would add and which evidence supports that addition.

### Exercise B - Competitor teardown

Complete the eight steps for five competitors or alternatives. Your report must include:

- homepage and pricing page screenshots with collection date;
- buyer, user, and price unit;
- first-use steps or “not tested”;
- up to 20 reviews each when available, with URL and date;
- common/missing feature matrix with definitions;
- source links for every claim;
- at least one manual workaround or status quo;
- the top three unknowns that need customer research.

### Exercise C - Three promises, five buyers

Make three concept-page variants for one buyer and one problem. Show the same simple layout with a different promise. Ask five people who match the target segment what they think the page offers, what is confusing, and what they do today. Report qualitative feedback; do not call five people a statistically representative sample.

### Exercise D - Rank the features

Create a feature list. For every item, cite a problem-sheet row or mark it as an assumption/enabling requirement. Estimate money, time, and risk effects separately. Select one feature for the smallest manual or prototype test.

### Short-answer questions with concise answers

1. **Why is a polished UI a weaker differentiator now?**  
   AI builders lower the cost of producing similar interfaces, so the interface alone is easier to imitate. It still matters for usability and credibility.

2. **What does the ChatGPT test reveal?**  
   Whether a general assistant can already produce the result, and what product work remains beyond generating text.

3. **Name the five capabilities the deck says can go beyond chat.**  
   Customer data, recurring workflow, integration, reliability, and owned distribution.

4. **Why ask for three buyers at three prices?**  
   To reveal how price relates to buyer, approval, and acquisition assumptions. The resulting profiles still require validation.

5. **What can a feature-frequency count tell you?**  
   It can suggest category expectations and candidate gaps. It cannot prove importance, quality, or demand.

6. **Why is a missing competitor feature not automatically an opportunity?**  
   Customers may not want it, may solve the task another way, or the feature may be hidden under a different label.

7. **What is the difference between the user and the buyer?**  
   The user performs the workflow; the buyer pays or controls the purchase. They may be different people.

8. **What does a competitor ad prove?**  
   It proves that an ad is visible in the library's scope and time window, not that the ad is profitable or works.

9. **Why save teardown reports in a project or versioned file?**  
   To preserve context and compare changes to product pages, prices, features, and claims over time.

10. **When should a feature with no quote be called a nice-to-have?**  
    When no current customer evidence supports it and no separate technical, safety, or compliance rationale requires it.

### Homework rubric: 20 points

| Criterion | Points |
|---|---:|
| ICP identifies the buyer, user, problem, current alternative, and evidence | 4 |
| Price includes currency, period, unit, and a reasoned hypothesis | 3 |
| Teardown covers five alternatives and uses current, traceable sources | 4 |
| Feature matrix uses consistent definitions and includes limitations | 3 |
| Ranked features connect to quotes/observations and money, time, or risk | 4 |
| Assumptions, unknowns, and next checks are explicit | 2 |
| **Total** | **20** |

## 9. Exam review

### Essential definitions

- **Productization:** Turning a task or capability into a repeatable offer that a buyer can access, trust, and pay for.
- **ICP:** A focused description of the type of customer most likely to get value and buy.
- **Positioning:** How the product is framed relative to a buyer's alternatives.
- **Table stakes:** Capabilities buyers expect in a category before they consider a product seriously.
- **Competitor teardown:** A structured, sourced comparison of alternatives across promise, buyer, pricing, onboarding, reviews, ads, and features.
- **Feature matrix:** A comparison of clearly defined capabilities across products or alternatives.
- **Value hypothesis:** A claim about the money, time, or risk a feature may save, awaiting validation.
- **Status quo:** The current behavior or workaround, including tolerating the problem.

### Possible long-answer question

> You are an IUT student investigating a ৳1,500/month restaurant reconciliation tool. Explain how you would choose an ICP, compare five alternatives, test a product promise, and rank the first features before writing production code.

**Expected answer structure:**

1. Identify buyer, user, approver, and one repeated problem using the context doc and problem sheet.
2. Define price currency, billing period, and unit; label price as a hypothesis.
3. Compare direct POS products, adjacent tools, manual work, and the status quo.
4. Capture current prices and feature claims from first-party pages; separate these from independent reviews and customer evidence.
5. Test a clear promise with target buyers and disclose that it is a concept test.
6. Rank features by verified money, time, or risk evidence; mark unsupported items as assumptions.
7. Propose a manual test, safety/privacy boundaries, and a stop rule.

## 10. Necessary links and sites

The deck asks for live competitor research and model-supported comparison. These are the direct links to use. The section lists official product pages where possible and marks review/advertising sites as source discovery tools. Recheck terms and prices before using data in a build or business decision.

### Competitors shown in the live teardown

- [Rosuii restaurant POS](https://rosuii.com/) - Bangladesh-focused restaurant operations product.
- [Rosuii pricing](https://rosuii.com/pricing) - public BDT plan page; compare limits, billing period, and extra costs.
- [ChillyPOS](https://chillypos.com/) - Bangladesh restaurant POS product and public pricing information.
- [Nexchar POS in Bangladesh](https://www.nexchar.com/pos-bd) - local market/product page.
- [Nexchar pricing](https://www.nexchar.com/pricing) - current published tiers; inspect currency and limits.
- [TMBill](https://www.tmbill.com/) - restaurant operations/POS product; the inspected main page directs prospects to request a demo.
- [TMBill products](https://www.tmbill.com/products) - product families and workflow coverage.
- [Loyverse restaurant POS](https://loyverse.com/restaurants-pos) - global restaurant product page.
- [Loyverse pricing](https://loyverse.com/pricing) - free core and optional paid add-ons.

### AI tools for research, critique, and prototypes

- [ChatGPT](https://chatgpt.com/) - use with the context document, problem sheet, and source links.
- [OpenAI image inputs guidance](https://help.openai.com/en/articles/8400551-image-inputs-for-chatgpt-faq) - current limitations for interpreting screenshots and visual pages.
- [ChatGPT Projects](https://help.openai.com/en/articles/10169521-projects-in-chatgpt) - keep related chats, research files, and project instructions together.
- [Claude](https://claude.ai/) - model review and screenshot/page analysis.
- [Gemini](https://gemini.google.com/) - a separate model option for controlled review.
- [Perplexity](https://www.perplexity.ai/) - search-oriented research interface; still open and check the cited sources.
- [Lovable documentation](https://docs.lovable.dev/introduction/welcome) - AI web application builder reference.
- [Bolt documentation](https://support.bolt.new/get-started/intro-bolt) - AI builder reference.
- [v0 documentation](https://v0.app/docs) - Vercel's generative UI and app-building reference.
- [OpenRouter model documentation](https://openrouter.ai/docs/guides/overview/models) - available model/provider list for comparison.
- [OpenRouter pricing](https://openrouter.ai/pricing) - current platform fees and plan comparison; model usage pricing may be separate.

### Reviews, product discovery, and public ads

- [G2 Restaurant POS category](https://www.g2.com/categories/restaurant-pos) - global category and review discovery. Its coverage is not a census of Bangladesh restaurants.
- [Capterra Point of Sale category](https://www.capterra.com/point-of-sale-software/) - global software discovery and reviews.
- [Apple App Store](https://www.apple.com/app-store/) - public app discovery and user review surfaces.
- [Google Play Store](https://play.google.com/store) - public app discovery and user review surfaces.
- [Meta Ad Library](https://www.facebook.com/ads/library) - search ads visible across Meta platforms.
- [Google Ads Transparency Center](https://adstransparency.google.com/) - search ads by advertiser or website and filter by region/date where available.
- [Google's Ads Transparency Center guidance](https://support.google.com/My-Ad-Center-Help/answer/12155361?hl=en) - official explanation of advertiser and ad search.
- [Google Trends](https://trends.google.com/trends/) - relative public search interest, not direct sales or total market size.

### APIs and official access routes

- [Google Places API overview](https://developers.google.com/maps/documentation/places/web-service/overview) - official place-data access route; check current terms, fields, and billing.
- [LinkedIn Developer Solutions](https://developer.linkedin.com/) - official API/product access route; access is product- and permission-dependent.
- [Reddit API documentation](https://www.reddit.com/dev/api/) - official API documentation for permitted community data access.
- [Meta Ad Library tools](https://transparency.meta.com/researchtools/ad-library-tools/) - Meta's official information about its Ad Library.

### How to use these sites

1. Begin with the customer's problem words, not only your product category name.
2. Open each vendor's own homepage, pricing, product, help, privacy, and onboarding pages.
3. Record date, geography, currency, billing unit, plan limits, and any setup or hardware fees.
4. Use G2, Capterra, app stores, and forums to find review evidence, but record review count, date, language, and likely selection bias.
5. Use ad libraries as evidence that an ad is visible in a defined period, not evidence that it converts profitably.
6. Use screenshots to compare structure and user assumptions. Create original product copy and design.
7. Read the exact source behind every important AI-generated claim.
8. Carry findings into interviews and workflow observation before deciding what to build.

## 11. Final takeaways and Class 3 checklist

### Five takeaways

1. **A prototype is easier to imitate than a trusted workflow.** Polish helps, but it does not prove value.
2. **The buyer and price change the research question.** State currency, unit, time period, decision-maker, and current alternative.
3. **Competitors include workarounds and inaction.** The buyer's spreadsheet, notebook, accountant, or tolerated error may be the strongest alternative.
4. **Feature counts generate questions, not decisions.** Check usage, quality, and importance with customers.
5. **Every priority needs evidence or a labelled rationale.** Quotes, observations, and payment behavior should shape the build list.

### Before Class 3: Building it

- [ ] One ICP names one buyer, user, job, and price point.
- [ ] Each claim in the ICP links to a problem-sheet row or is marked as unknown.
- [ ] Price includes currency, billing interval, unit, limits, and extra fees where known.
- [ ] Teardown covers five competitors or alternatives with all eight steps.
- [ ] Current pricing has an access date and source link.
- [ ] Manual work and the status quo appear in the comparison.
- [ ] Feature definitions are consistent in the matrix.
- [ ] Reviews and competitor claims are separated from direct customer evidence.
- [ ] Three positioning concepts have been shown to target buyers.
- [ ] Each feature is ranked by money, time, or risk saved and backed by evidence or labelled assumption.
- [ ] One small manual test, one stop rule, and the next decision are written down.

### Source fidelity and caveats

- This note preserves the 28-page sequence and expands each page into definitions, decisions, risks, prompts, and exercises.
- The deck's stories about Agency Handy, Feedboss, and Righted are presented as instructor case examples rather than independently audited business claims.
- Slide rules such as the ChatGPT test, 8-of-10 feature threshold, and “the gap in their pitch is your pitch” are heuristics. Their conclusions must be checked with target buyers and observed behavior.
- The competitor pricing table is a public-page snapshot taken on 2026-09-24. Vendor pages may change, and prices may depend on negotiation, country, setup, payment, and hardware.
- Vendor marketing pages support statements about what the vendor advertises. They do not establish independent product quality, adoption, reliability, or customer outcomes.
