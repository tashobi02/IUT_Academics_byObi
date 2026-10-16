# Lecture Sheet: Selling and Scaling with One or Two People

**Topic:** Finding buyers, earning attention, converting signups, and learning from customers with a very small team  
**Source deck:** 4th Class.pdf  
**Deck title:** *Class 4: Selling and Scaling with One or Two People*  
**Deck subtitle:** *Find buyers, reach them, keep them. The team is you.*  
**Deck length:** 27 pages  
**Prepared:** 2026-09-26  
**Audience:** IUT undergraduate students, early builders, and Bangladesh-based founders  
**Central idea:** AI can help a small team research, draft, route, summarize, and repeat marketing and customer-work tasks. The founder still chooses the customer, makes promises, approves public or irreversible actions, handles sensitive cases, and checks whether the work produced real customer value.

> **How to read this sheet:** **Deck content** records the slide’s message. **Lecture interpretation** explains how to use it. **Verification note** distinguishes a useful method from a benchmark, anecdote, vendor claim, or rule that needs checking. The link directory at the end was checked on 2026-09-26; product features, pricing, platform policies, and legal rules can change.

## 1. Learning objectives

By the end of this class, you should be able to:

1. Compare search, content, outreach, communities, and marketplaces as customer-acquisition channels.
2. Explain why the channel choice can change product scope, pricing, support, and the first-use experience.
3. Define an ideal customer profile (ICP) as a practical filter and score leads using evidence rather than model confidence.
4. Sketch a lead-research workflow with source URLs, deduplication, verification, review, and a human approval step.
5. Describe an SEO and content workflow while preserving original insight, product evidence, and a recognizable voice.
6. Test how public AI assistants describe a product without treating a small prompt sample as a measure of all customer awareness.
7. Separate email authentication and delivery from legal permission to contact a person.
8. Identify the cold-email volume, warm-up, and sequence instructions in the deck as unverified heuristics rather than universal safe limits.
9. Design community participation around listening and useful contributions instead of automated promotion.
10. Compare marketplaces by audience access, fees, refund exposure, support commitments, and whether the platform supplies discovery.
11. Define an activation event and calculate funnel rates with clear denominators and time windows.
12. Design a support workflow that uses AI to classify and draft while reserving money, anger, and policy decisions for a person.
13. Turn repeated support themes into product questions and investigate them before turning them into roadmap commitments.
14. Ask an AI analytics tool for a specific drop-off analysis and verify its data, SQL, cohort, and interpretation.
15. Produce a four-week launch plan and a support plan that name the channel, owner, measures, review gates, and next decision.

## 2. Prerequisites and working rules

### Bring these inputs

- The product specification and customer hypothesis from earlier classes.
- A narrow ICP: who has the problem, what evidence identifies them, and who can pay.
- One target outcome for the next four weeks, such as five qualified conversations or ten activated users.
- A spreadsheet or simple analytics table with consistent event names and date ranges.
- A current, locally relevant review of privacy, direct-marketing, consumer-protection, and platform rules before collecting leads or sending promotions.

### Working rules

- Mark each number as **observed**, **estimated**, **assumed**, or **reported by the deck**. Do not turn a slide anecdote into a forecast.
- Preserve the source URL and collection date for each researched lead. A guessed score without evidence is not qualification.
- Verify that collecting and using contact data is permitted for the source, the platform, and the recipient’s jurisdiction. A deliverable address is not permission to market to it.
- Give every automated process a defined input, output, failure path, owner, and stop condition.
- Keep a person responsible for public posts, external messages, refunds, prices, legal commitments, and new support policies.
- Use the least personal data required. Mask or remove names, emails, tokens, payment data, and private user content before sending tickets or session recordings to an AI system.
- Define funnel events before analyzing conversion. Use a named cohort, a fixed time window, and consistent denominators.
- Review quality, not just volume. More scraped leads, generated pages, launch-day visits, or support replies do not automatically mean more customers.
- For email, treat authentication and deliverability as infrastructure. They do not establish lawful basis, consent where required, relevance, or recipient expectation.
- For every third-party tool, check current pricing, data handling, retention, permissions, platform compatibility, and cancellation terms before connecting it to real user data.

## 3. One-page lecture summary

### The selling-and-learning loop

~~~text
Choose a buyer and the outcome they value
    -> Select a channel that fits their behavior and the product economics
    -> Prepare a truthful offer and a measurable first-use path
    -> Use AI for bounded research, drafting, sorting, and summarizing
    -> Review work before it reaches a customer or changes a policy
    -> Measure qualified interest, activation, payment, retention, and support
    -> Investigate the largest meaningful drop or repeated customer problem
    -> Improve the product, message, or channel
    -> Repeat with a clearer hypothesis
~~~

### The five channels in the deck

| Channel | What it can do well | What the founder still decides | Typical first test |
|---|---|---|---|
| Search | Capture demand from people already looking for a solution | Which problem and search intent merit a useful page | Publish one evidence-backed page; track relevant visits and qualified actions |
| Content | Teach, demonstrate expertise, and create repeatable distribution | Point of view, examples, accuracy, and voice | Publish a small number of useful pieces in the channel the ICP uses |
| Outreach | Start a relevant conversation with a named potential buyer | Whether contact is appropriate, what to say, and when to stop | Contact a small, permitted, well-researched group and measure useful replies |
| Communities | Learn language, needs, objections, and norms | Whether and how the founder participates | Listen, answer a real question, and disclose affiliation when relevant |
| Marketplaces | Borrow platform infrastructure and, sometimes, audience | Offer terms, economics, support commitment, and launch readiness | Compare the deal terms and expected workload with direct acquisition |

### After a signup: measure a real path to value

| Stage | Define it as | Example event |
|---|---|---|
| Visitor | A person reaches the product page in the chosen time window | `landing_page_view` |
| Signup | A unique person completes account creation | `account_created` |
| Activation | A new user completes the behavior that indicates meaningful first value | `first_qualified_report_created` |
| Paid | A user or account starts a paid plan | `subscription_started` |
| Retained | The cohort returns and completes a meaningful behavior in a later window | `report_created_week_4` |

**Example with hypothetical counts:** 1,000 page visitors, 100 signups, 40 activated users, and 8 paid users.

- Signup rate = 100 ÷ 1,000 = **10%**.
- Activation rate = 40 ÷ 100 = **40% of signups**.
- Paid conversion = 8 ÷ 40 = **20% of activated users**, or 8 ÷ 100 = **8% of signups**.

Always state the denominator. “Paid conversion is 20%” is incomplete unless the audience knows whether the denominator is signups, activated users, or something else.

### The operating rule

**AI handles repeatable work; a person owns judgment and consequential actions.** In this class that means AI may research, classify, draft, cluster, or explain. A person chooses who to contact, approves messages and posts, decides refunds and policy, interprets weak data, and determines what ships.

## 4. Core concepts and frameworks

### 4.1 Channel fit is a product decision

A channel is the route through which the intended customer discovers and evaluates the product. It affects the product itself because customers arrive with different expectations.

| If the channel is… | The product and offer may need… | A key risk |
|---|---|---|
| Direct outreach | A narrow buyer, a clear business outcome, a short proof path, and a relevant demo or trial | Spending time on contacts who are not appropriate or interested |
| Search | Pages that answer specific questions, trustworthy facts, and a product that can fulfill the promise | Writing large quantities of thin pages in hope of rankings |
| Content | A repeatable point of view, examples, and a way to turn attention into a useful next step | Publishing generic material that sounds interchangeable |
| Community | Respect for local rules and a genuine contribution before promotion | Treating a community as an ad list and losing trust or access |
| Marketplace | A polished listing, clear terms, realistic support capacity, and deal economics | Trading future service obligations for an impressive launch-day number |

The deck’s useful principle is to choose a first channel before finalizing every product detail. The channel helps reveal what buyers need to see, what objections they will raise, and how much onboarding or support will be necessary. This should guide prioritization, not excuse building channel-specific features before confirming demand.

**Practical channel-fit questions**

1. Where does this buyer already look for a solution?
2. Does the buyer need to trust a person, compare products, see a demo, or read technical proof?
3. Can one or two people serve the customers that this channel might bring?
4. What is the expected time from first contact to useful feedback or revenue?
5. What would count as evidence that this channel deserves more effort?

### 4.2 Lead generation: relevance and provenance before volume

An **ideal customer profile (ICP)** is a set of observable conditions that helps a team identify likely-fit customers. It should be a filter the team can apply, not only a polished paragraph.

For example, “small manufacturing companies” is too broad. A more useful filter could specify:

- geography or service area;
- company size or operating model;
- the role that experiences the problem;
- a public signal that the problem may exist;
- a reason the product is relevant now;
- clear exclusion criteria.

A good lead row includes the company or person, evidence for each criterion, a source URL, a collection date, a confidence/status label, and a reason for human review. Avoid collecting fields “just in case.” Personal data should be limited to what is necessary for an authorized purpose.

**Lead quality statuses**

| Status | Meaning | Appropriate use |
|---|---|---|
| Research candidate | A public signal suggests a possible fit; not yet checked | Continue research only |
| Verified company | The organization and source appear current | May still need role, need, and contact-permission review |
| Qualified lead | Evidence supports the ICP and a relevant reason for contact | A person decides whether contact is appropriate |
| Disqualified | Evidence shows mismatch, stale data, or an objection | Suppress from the active list |
| Unknown | Evidence is missing or conflicting | Do not silently treat as a match |

The deck’s example has 50,000 scraped candidates and 163 verified leads. If the 163 are a subset of those 50,000, the simple verified-address yield is about **0.33%**. This calculation does not prove that the addresses are relevant, lawful to contact, or likely to buy. The lesson is to inspect quality and provenance rather than celebrate a large scrape.

**Lead scoring is a triage aid.** A 1–10 score should map to visible criteria and be checked against human-reviewed examples. It is not a probability of conversion unless the team has tested and calibrated it against real outcomes.

### 4.3 Research automation needs quality controls

A lead workflow might run weekly:

~~~text
Authorized source
    -> Extract a minimal set of public fields
    -> Enrich only fields relevant to the ICP
    -> Normalize, deduplicate, and check freshness
    -> Attach source URL and collection date
    -> Score against explicit rules
    -> Place uncertain or high-impact records in a review queue
    -> Human decides whether to use the record
~~~

Tools such as Apify, n8n, or Make can connect steps. They do not remove the need to check source terms, API limits, data accuracy, failures, stale records, access controls, and privacy obligations. A workflow that runs every Friday can repeatedly reproduce the same mistake if nobody checks its outputs.

A useful pipeline dashboard reports:

- rows discovered, deduplicated, and rejected;
- reason counts for rejection;
- percentage with current source URLs;
- human override rate for AI scores;
- source freshness;
- failures and retry counts;
- whether any record is on a suppression or “do not contact” list.

### 4.4 SEO and content: automation is a production aid, not a ranking guarantee

The deck’s proposed content workflow is: find topics, group search intent, create a brief, draft with a voice reference, review, publish, and repurpose. That can reduce repetitive work. The content still needs to answer a real question with accurate, useful information.

A strong workflow adds these checks:

1. **Choose a real question:** Use customer calls, support tickets, search queries, community discussions, or product usage to find a need.
2. **Check intent:** Is the person learning, comparing alternatives, looking to buy, or troubleshooting?
3. **Gather evidence:** Use first-party product facts, tested examples, expert review, customer permission, or original research.
4. **Draft from a brief:** Give the model the audience, desired outcome, source material, voice examples, claims to avoid, and format.
5. **Verify every claim:** Check quotations, product limits, statistics, prices, and citations against primary sources.
6. **Edit for usefulness:** Remove repetition and generic filler; add a real explanation, example, or point of view.
7. **Publish and measure:** Track relevant impressions, visits, qualified actions, and whether the page continues to help.
8. **Update or remove:** Correct stale information and pages that no longer serve users.

A top-ranking-page review can reveal common questions and missing coverage. It is a research input, not permission to copy another page’s wording, structure, or data. Search systems do not guarantee that a page will be indexed or rank simply because it is technically correct. Google’s official guidance emphasizes helpful, reliable, people-first content and says that using AI does not itself guarantee ranking benefits. See [Google Search Essentials](https://developers.google.com/search/docs/essentials) and [Creating helpful, reliable, people-first content](https://developers.google.com/search/docs/fundamentals/creating-helpful-content).

### 4.5 AI visibility checks are a small, changing sample

The deck suggests asking ChatGPT, Claude, and Gemini what a product is and whom it serves. This is a useful **positioning test**: it can reveal confusing language, incorrect descriptions, or differences among model responses.

It is not a complete visibility metric. Results can vary with the exact wording, model version, search access, account settings, geography, sources available, and time. A model that fails to mention a product does not prove that no customer knows it. A model that recommends it does not prove that customers trust it or will buy.

To make a manual check more informative:

- use a fixed set of realistic buyer questions;
- record model, date, query, and full answer;
- repeat the same prompts later;
- separate correct facts, omissions, and unsupported claims;
- test against real customer language and interviews;
- use public sources that are accurate and helpful rather than writing solely to influence a model;
- do not treat a vendor’s visibility score as independently validated unless its method and sample are transparent.

The deck names Righted. Its current product page describes a scan and ongoing monitoring across assistants, but any output remains the vendor’s measurement of a changing sample. The page itself says changes do not guarantee immediate changes in model answers. The deck also names “AgentiSEO”; I could not unambiguously identify a current official product site from that name in this review, so its slide claim is not independently verified.

### 4.6 Cold outreach: permission, relevance, and reputation are separate checks

The deck recommends verifying addresses, researching a person, writing a short message, sequencing follow-ups, and tracking results. Personalization and a clear, brief message can make a legitimate message more relevant. None of those steps establishes permission to send.

Before a marketing email:

1. Identify the recipient’s jurisdiction and whether the address belongs to an individual or a corporate role.
2. Check current laws and provider/platform terms that apply to the sender, recipient, data source, and message type.
3. Document the source, collection date, purpose, and lawful basis or consent status where required.
4. Ensure the sender identity is accurate and clear.
5. Provide a practical way to object or unsubscribe where required or appropriate; maintain a suppression list.
6. Stop after an objection, opt-out, hard bounce, or clear disinterest.
7. Review complaints, replies, qualified interest, and conversion. Do not optimize only for opens.

For example, UK rules distinguish corporate subscribers from individuals, and use of an identifiable business contact’s personal data may still bring UK GDPR duties. US CAN-SPAM and the EU ePrivacy framework have their own scope and conditions. Bangladesh has its own current legal materials. These examples do not determine the law for every recipient or campaign. Review the official sources in the link directory and obtain jurisdiction-specific advice where needed.

Email authentication protects domain identity and supports delivery. Gmail guidance for senders covers SPF, DKIM, and DMARC; bulk-sender requirements also address spam rates and one-click unsubscribe for relevant promotional traffic. **Authentication does not make an unsolicited message lawful or wanted.** There is no universal “50 cold emails per day is safe” threshold in the cited provider guidance.

Open rates are also a weak success measure. Apple Mail Privacy Protection can prevent senders from seeing whether a recipient opened an email. Prefer qualified replies, meetings held, trials started, purchases, opt-outs, complaints, and unsubscribes. The deck’s “under 80 words,” “no images or links,” and day 1/3/7 sequence are testable writing heuristics, not compliance or inbox-placement guarantees.

### 4.7 Domain setup: protect identity and reputation, avoid folklore

The deck recommends a separate lookalike domain, SPF/DKIM/DMARC, “fake threads” for warm-up, and a fixed ramp to 50 messages a day. Treat these as vendor-style practice from the slide, not a universal standard.

A practical, defensible setup focuses on:

- using a domain clearly associated with the actual organization and sender;
- publishing and testing the authentication records required by the sending provider;
- monitoring provider reputation and delivery errors;
- sending only relevant, permitted mail to appropriately selected recipients;
- honoring objections and removing invalid addresses;
- keeping a record of which system sends what;
- avoiding misleading domain names or fabricated engagement.

The deck’s “two to three weeks of fake threads” advice is not established by the cited Google sender guidance. Simulated conversations do not prove recipient interest or compliance. Do not present them as required. Use official provider documentation and the email service’s current acceptable-use rules.

### 4.8 Communities: listen first, contribute in the local format

A community is a relationship and learning environment before it is an acquisition channel. Read the rules, learn what members consider useful, answer an actual question, and disclose your product affiliation when it is relevant. A useful contribution can still include a product mention if the rules allow it and the mention directly helps the person asking.

An operating rhythm can be:

- monitor a narrow list of topics or communities;
- collect only relevant public posts;
- summarize recurring questions with links back to the source;
- draft possible responses for a person to inspect;
- post from an accountable human identity;
- record what people ask, not only what they click;
- stop monitoring a space if its rules or member expectations prohibit it.

Automated posting, unsolicited direct messages, or repeated link drops can violate community rules and damage trust. Tools can help notice public mentions; they should not impersonate authentic participation.

### 4.9 Marketplaces: model the whole offer, not only day-one revenue

The deck compares AppSumo, Product Hunt, Gumroad, and Lemon Squeezy. These do different jobs. Some may offer a marketplace or launch surface; payment infrastructure by itself may not bring customers. Check current deal terms rather than inferring capabilities from a name.

Before a deal or launch, estimate:

- one-time revenue after platform share, tax, payment costs, refunds, and support;
- expected usage and infrastructure costs per customer;
- the cost of serving customers for the promised period;
- redemption behavior, refund window, and customer-support load;
- what counts as a lifetime commitment and what exceptions apply;
- whether the price trains buyers to expect a discount;
- how the team will reach customers after launch traffic declines.

A lifetime deal can create a long-term service commitment while producing one-time revenue. Support and hosting must be sustainable under heavy usage, not merely average usage. Product Hunt can produce attention and feedback, but do not assume a launch position or traffic spike will become durable sales.

The deck reports that FeedBoss generated “$150K+,” had four partners, and experienced about 20% refunds. This is a slide anecdote, not an audited result. The current AppSumo listing is useful for reviewing the live product page and terms; it does not independently verify the slide’s historic sales or refund figures. AppSumo’s own refund documentation says terms depend on the deal and its stated timeframe, which can change.

### 4.10 Signup, activation, and first value

**Onboarding** helps a new user understand how to get value. A behavior-triggered message responds to a user action or an unmet need, such as “created an account but did not import a file.” It is often more useful than a generic sequence, but triggers need a clear purpose, appropriate consent/preferences, and a way to stop irrelevant messages.

**Activation** is a defined behavior that indicates the user has experienced the product’s main value. It is not simply signing in. Good activation definitions are:

- observable in product data;
- connected to the user’s intended outcome;
- achievable early enough to improve onboarding;
- measured over a fixed window;
- checked against later retention or success.

Do not assume that the single action associated with retention in one product will apply to another. Use cohorts and validate the relationship over time.

**First value** should be real. Sample data can make an empty interface easier to understand, but it must be clearly labeled as sample data and separated from the user’s real account. Synthetic examples should not look like actual customer records or imply that the product has completed work it has not done.

### 4.11 Support is both service and product evidence

The slide’s support flow—ticket, AI classification, AI draft, human review, send—is a useful human-controlled pattern.

AI can help with:

- routing by topic or urgency;
- retrieving an approved help article;
- drafting a response from a known policy;
- summarizing a long thread;
- suggesting an issue link;
- identifying common themes.

A person should decide refunds, billing adjustments, pricing promises, angry or vulnerable customers, account-security incidents, legal questions, exceptions, and anything that changes policy. Before sending a draft, verify the customer’s details, the facts, the policy version, and that the answer actually addresses the question. Do not paste unnecessary personal or financial data into a general-purpose model.

Repeated tickets can indicate unclear copy, a broken workflow, a bug, an expectation mismatch, or a missing feature. “Ten similar tickets” is a signal to investigate, not proof that the product should build a particular feature. Review representative examples, customer segments, impact, and available alternatives before writing a spec.

### 4.12 Product analytics: find the largest meaningful loss

A funnel analysis needs:

- event definitions and instrumentation checks;
- a time period;
- a cohort definition;
- unique users or accounts as the unit;
- consistent stage order;
- counts and rates;
- a baseline for comparison;
- a qualitative check of what users experienced.

A simple funnel is:

| Stage | Count | Conversion from prior stage |
|---|---:|---:|
| Visitors | 1,000 | — |
| Signups | 100 | 100 ÷ 1,000 = 10% |
| Activated | 40 | 40 ÷ 100 = 40% |
| Paid | 8 | 8 ÷ 40 = 20% |

The largest numerical drop is not always the best problem to solve. A tiny cohort, tracking error, seasonality, or a channel with low intent can distort the picture. Segment by acquisition source, device, customer type, or product version when the sample is large enough. Review recordings only with appropriate privacy controls, masking, access, retention, and consent or other required basis.

An AI-generated query is a hypothesis about the data. Check that it uses valid event names, deduplicates users appropriately, applies the right dates and cohort, handles missing values, and computes the intended denominator. Inspect the SQL and result before acting. Ask for the evidence behind a conclusion and for alternative explanations.

### 4.13 Turn analysis into an experiment

A useful experiment states:

- **Observation:** What did users do or fail to do?
- **Evidence:** Which cohort, timeframe, event, support examples, or interviews show it?
- **Hypothesis:** What change might improve the outcome, and why?
- **Test:** What is the smallest safe comparison or usability check?
- **Measure:** Which primary metric and guardrail will be tracked?
- **Decision rule:** What result would lead to ship, revise, or stop?
- **Owner and date:** Who reviews the result, and when?

For example, if a funnel suggests users abandon during setup, do not immediately rewrite all onboarding. Observe a few permitted sessions, ask affected users what confused them, test one change, and compare completion for a defined cohort. This turns “AI says there is a drop” into a product learning loop.

## 5. Reusable templates and prompts

### 5.1 Channel choice

~~~text
Product and outcome:
Target buyer:
Evidence that this buyer has the problem:
Where the buyer currently looks for solutions:
Candidate channel:
Why this channel fits the buyer:
What product, proof, or support must change for this channel:
Four-week test:
Primary measure:
Guardrail (quality, complaints, cost, or support load):
What result would make us continue, change, or stop:
Person responsible:
~~~

### 5.2 ICP and lead-review record

~~~text
Company/person:
Source URL:
Date checked:
Public evidence:
ICP criteria met:
ICP criteria not met or unknown:
Reason this product may be relevant:
Data fields collected and why each is needed:
Source/platform terms checked:
Recipient jurisdiction and contact category:
Contact permission/legal review status:
Suppression/objection check:
AI score and evidence for each point:
Human decision: review / qualify / reject / suppress
~~~

### 5.3 Content brief with a voice file

~~~text
Audience and their situation:
Question or task they need to solve:
Search/community intent:
What the product actually does:
First-party evidence and source links:
Claims we must not make:
Voice examples (with permission):
Required explanation or example:
What competing pages commonly cover:
What original value will this page add:
Draft format and length range:
Human reviewer:
Fact-check checklist:
Publication and update date:
Success measure:
~~~

**Useful drafting prompt**

~~~text
Create a first draft from the brief and source material below.
Do not invent metrics, customer results, product functions, quotations, or citations.
Mark any unsupported statement as [VERIFY].
Use the supplied voice examples for tone, but do not copy their sentences.
Answer the reader's question directly, explain the reasoning, and include the real example provided.
Brief:
[Paste brief]
Source material:
[Paste approved sources]
~~~

### 5.4 Outreach review checklist

Use this before drafting or sending any campaign. It is a decision checklist, not permission to send.

~~~text
Who is the intended recipient and in which jurisdiction?
Is the address a corporate role address or an identifiable individual's address?
Where did the data come from, when was it collected, and may it be used this way?
What law and provider/platform rules apply to this sender, recipient, and message?
Is there consent or another documented basis where required?
Is the message accurate, relevant, and transparent about who sent it?
Is there a clear way to object or unsubscribe where required or appropriate?
Does the suppression list include prior objections, unsubscribes, and hard bounces?
What is the stop rule for non-response or negative response?
Which measure matters: qualified replies, meetings held, conversion, complaints, opt-outs?
Who reviews the list and message before sending?
~~~

### 5.5 Marketplace economics

| Item | Estimate | Evidence/status |
|---|---:|---|
| Gross sales |  | Assumption or observed |
| Platform/payment share and fees |  | Current terms |
| Taxes and currency conversion |  | Jurisdiction-specific |
| Refunds and chargebacks |  | Scenario, not a universal rate |
| Support cost per customer |  | Expected hours and loaded cost |
| Hosting/API cost per customer |  | Average and heavy-user case |
| Expected active period |  | Lifetime commitment definition |
| Net contribution |  | Gross minus all relevant costs |
| Post-launch acquisition plan |  | Named channel and owner |

### 5.6 Activation and onboarding

~~~text
Target user:
Desired first outcome:
Activation event name:
What the user must do:
What does not count as activation:
Time window:
Cohort entry event:
Segment(s) to compare:
Sample size and data-quality check:
Behavior that predicts later retention (if tested):
Current obstacle supported by evidence:
Onboarding change to test:
Primary metric:
Guardrail:
Human reviewer and review date:
~~~

### 5.7 Support triage and escalation

~~~text
Ticket ID (pseudonymous if possible):
AI category:
Urgency:
Relevant approved policy/help article:
Draft response:
Facts that require checking:
Sensitive data present? redact before model use.
Escalation reason: money / anger / security / policy / legal / unclear / other
Human reviewer:
Final action:
Does this indicate a repeated product problem?
Related issue or ticket cluster:
~~~

**Routing rules to start from**

| Ticket type | AI may help with | Human gate |
|---|---|---|
| Known how-to question | Find the approved article and draft a response | Check that the article matches the customer’s version and case |
| Reproducible bug | Summarize steps and attach the right issue | Confirm the bug, priority, and customer communication |
| Refund or billing | Gather relevant account context and draft options | A person decides any money movement or exception |
| Angry or distressed user | Summarize the concern and find policy | A person reviews tone and handles the response |
| Security or privacy | Route immediately and preserve relevant evidence | Authorized owner investigates; do not expose secrets to a model |
| Feature request | Classify and count similar requests | Product owner validates need and decides roadmap |

### 5.8 Funnel-analysis prompt

~~~text
Analyze this funnel for [product] over [start date] to [end date].
Use [new accounts / unique users] as the unit.
Cohort: users who completed [entry event] during this period.
Stages and exact event names:
1. [event]
2. [event]
3. [event]
4. [event]
Show counts, conversion from the prior stage, and conversion from the original cohort.
State the denominator and time window for every rate.
Check for duplicate events, missing data, test accounts, and event-name mismatches.
Show the SQL or query used and explain each filter.
Identify the largest supported drop, then give three testable explanations.
Separate observed facts from hypotheses.
Do not recommend a change until you identify what evidence would distinguish the explanations.
~~~

### 5.9 Four-week launch plan

| Week | Build and prepare | Publish or contact | Measure and decide |
|---|---|---|---|
| 1: focus | Lock ICP, offer, exclusions, support capacity, and one channel | Prepare a landing page or channel profile with truthful claims | Record baseline and define the primary success measure |
| 2: proof | Test the first-use path; instrument visitor, signup, and activation events | Share useful proof or request feedback from appropriate early users | Check data quality and note objections/questions |
| 3: launch | Fix the most important onboarding or reliability issue | Run the bounded channel test; publish or launch only where platform rules fit | Review qualified interest, activation, replies, support, and cost |
| 4: learn | Fix one evidenced product or message problem | Follow up with users who expect follow-up; continue useful content/community work | Compare against the hypothesis; continue, revise, or stop |

If outreach is a candidate channel, complete jurisdiction, data-source, provider-policy, authentication, and suppression checks before any send. The deck’s “Week 0 warm-up / Week 4 volume” timetable is not a legal or provider guarantee.

## 6. Detailed page-by-page lecture notes

### Page 1 — Class 4: Selling and scaling with one or two people

**Deck content:** The title frames the class around finding buyers, reaching them, and keeping them, with the founder as the small team.

**Lecture interpretation:** The class moves from deciding what to build to learning whether the product can reach and serve real customers. “One or two people” describes a resource constraint, not a reason to automate every interaction. The core design challenge is to automate repeatable work while preserving care, accuracy, and accountability where a person’s decision matters.

**Verification note:** The title is a course framing, not evidence that a single person can sustain every marketing, support, compliance, and operations task at arbitrary scale. Workload and customer expectations must be measured.

### Page 2 — Five channels and the division of labor

**Deck content:** Search, content, outreach, communities, and marketplaces are paired with AI tasks and founder judgment. AI can research, draft, monitor, or prepare listings; the founder chooses priorities, owns voice and examples, reviews messages, posts personally, and handles deal terms or refund calls. The slide’s rule is “AI does the volume. You do the judgment and anything irreversible.”

**Lecture interpretation:** This is a useful responsibility map. AI can prepare options and summarize evidence; the person decides what to publish, who to contact, what to promise, and how to handle a consequence. “Anything irreversible” is broader than money: a public claim, a privacy disclosure, a customer-data export, or a platform post can be difficult to undo.

**Verification note:** A human-review step does not by itself make a workflow accurate or lawful. Define what the reviewer checks and make sure they can reject or stop the action.

### Page 3 — Channel choice changes the product

**Deck content:** Outreach may require a free trial, short sales cycle, and ROI in the pitch. A marketplace may require a polished page, lifetime-deal math, and support capacity. The deck advises choosing the channel before finalizing the spec.

**Lecture interpretation:** Distribution affects requirements. A buyer contacted directly may need a concise demo and a credible business case; a marketplace customer may decide from screenshots, public reviews, terms, and a self-serve onboarding flow. Use channel needs to identify product risks and evidence gaps.

**Verification note:** The slide gives examples, not fixed rules. A marketplace deal does not always require a lifetime plan; an outreach customer does not always need a trial. Validate the conditions with the intended buyers and current platform terms.

### Page 4 — Find buyers with an ICP and verified evidence

**Deck content:** Define the ICP as a filter, run a scheduled scrape, enrich each lead with relevant public signals, verify, deduplicate, and score. The sample pipeline shows 50,000 records resulting in 163 verified leads, with company emails, a score, and a source URL. The slide says 50 verified names can beat 5,000 scraped records.

**Lecture interpretation:** The useful point is the movement from a broad candidate pool to a small, reviewable set. A source URL makes the record auditable. Add collection dates and explicit match criteria so a reviewer can explain why a record was kept.

**Verification note:** The displayed conversion is about 0.33% if 163 is a subset of 50,000. “Verified” may mean only that an address exists or passed a service check; it does not establish fit, consent, lawful basis, or likely purchase. The “50 vs 5,000” line is a heuristic, not a measured universal result.

### Page 5 — Build a lead pipeline, then review it

**Deck content:** A weekly cron job triggers a scraper; an AI step extracts ICP fields as JSON; an email API verifies addresses and deduplicates; an AI score ranks leads; a Sheet or CRM receives records; the founder reviews them. The slide names Apify/custom code, n8n, and Make and estimates one evening for setup.

**Lecture interpretation:** This is a clear data pipeline with a human decision at the end. JSON provides a structured output, but generated fields still need validation against a schema and their source. Add error handling, retry limits, access controls, stale-data flags, API-cost limits, and a way to pause the job.

**Verification note:** “One evening” is an anecdotal estimate. Integration quality, source permissions, data protection, API quotas, and ongoing maintenance determine the actual work. A verification API checks an address property; it does not decide whether the person should receive marketing.

### Page 6 — SEO/content workflow

**Deck content:** A keyword sheet feeds topic clustering, briefs based on top search results, AI drafts using a voice file and real product examples, scoring, technical site audits, human editing, and deployment. The deck says “AgentiSEO does all four” and compares the process with a former five-person team.

**Lecture interpretation:** The workflow can remove repetitive steps: grouping queries, making a draft outline, listing technical issues, and creating a review queue. The human contribution is selecting a useful topic, adding product knowledge, checking originality and factual claims, and deciding what deserves publication.

**Verification note:** Search tools and automated audits can be wrong or incomplete; keyword metrics are estimates. The slide’s team-replacement and output-volume claim is not independently established. Google’s guidance emphasizes helpful, reliable, people-first content and states that technical eligibility does not guarantee crawling, indexing, or ranking. Do not use scaled pages primarily to manipulate rankings.

### Page 7 — AgentiSEO as a product example

**Deck content:** The slide presents “5 people → 1 AI tool,” says targets and volume stayed the same, and describes the tool as something first built for the speaker and later productized.

**Lecture interpretation:** This is a founder story about converting an internal workflow into a product. The transferable question is whether other customers have the same recurring job and would pay for a tool that performs it reliably.

**Verification note:** The slide does not give an independent benchmark, customer sample, cost comparison, or quality measure for the “five people” claim. “Same volume” does not establish equivalent accuracy, support, originality, or business outcome. The current official identity behind the exact “AgentiSEO” name was ambiguous in this review; treat the product example as unverified until the presenter supplies a source.

### Page 8 — How LLMs may form product recommendations

**Deck content:** The slide says LLMs read public pages, structured data, reviews, and Reddit; may miss login-gated, thin, or crawler-blocked pages; and recommends stating information in a parseable format. It names Righted as a tool that audits ChatGPT, Claude, and Gemini.

**Lecture interpretation:** Public, accurate product information can make a product easier for people and systems to understand. Maintain consistent descriptions of what the product does, its audience, evidence, pricing, and limitations. Structured data can help systems interpret page content when it follows the relevant documentation.

**Verification note:** Different systems use different retrieval and training methods. A structured-data markup does not guarantee that a product will be recommended. The slide’s explanation is simplified, and the provider’s audit is a commercial measurement. See Google’s [structured-data guidelines](https://developers.google.com/search/docs/appearance/structured-data/sd-policies); follow the specific assistant’s current documentation as well.

### Page 9 — Test how assistants describe the product

**Deck content:** Ask ChatGPT, Claude, and Gemini “what is [product] and who is it for,” then compare disagreements, errors, and omissions. The slide says, “If the model doesn’t know you, neither does anyone who asks it.”

**Lecture interpretation:** The prompt is a quick test of message clarity. If an assistant repeatedly mistakes the category or audience, inspect the public product description and compare it with what actual customers understand. Keep a dated record so you can tell whether wording changes affected answers.

**Verification note:** The final sentence is rhetorical, not a valid inference. Many potential buyers do not ask assistants, and assistant answers can be incomplete or variable. A small sample is one diagnostic signal, not a proxy for awareness, demand, or sales.

### Page 10 — AI content engine

**Deck content:** Discover topics from autocomplete, “People Also Ask,” and Reddit; cluster intent; draft from a brief and voice examples; distribute to LinkedIn, a CMS, or a newsletter platform; repurpose one article into posts, carousels, video scripts, and threads. FeedBoss is cited as an example.

**Lecture interpretation:** Repurposing can save effort when each format remains useful in its own context. A long explanation may become a short post, but it should be adapted for the new audience rather than copied mechanically. Keep the original evidence and link it to derivative pieces.

**Verification note:** Scheduling and APIs must comply with current platform rules and user permissions. “One article becomes many formats” is a production strategy, not proof that each derivative deserves publication. FeedBoss’s current listing can show its present offer; it cannot establish that its outputs will fit every product’s voice or platform requirements.

### Page 11 — AI content without voice is noise

**Deck content:** The slide contrasts generic AI copy with a voice file made from 50 past posts, screenshots, and real numbers. Its rule: feed AI the founder’s writing first; otherwise the generated output is worth what it costs.

**Lecture interpretation:** Voice references give the model examples of wording, rhythm, and point of view. Add a claims policy: which numbers are approved, what customer details are private, which product capabilities are current, and which phrases feel unlike the brand. Prefer a smaller set of representative examples over a large, unreviewed archive.

**Verification note:** “50 posts” is not a required sample size. Remove personal or confidential details and confirm you have the rights to use the examples. A model can imitate surface style without knowing whether a claim is true or whether the content is useful.

### Page 12 — Cold outreach that does not get flagged

**Deck content:** Verify addresses, research the website/bio/recent posts, write under 80 words with one ask and no images or links, use a day 1/3/7 sequence, and track opens, replies, and meetings. The slide warns that more than 50 cold emails per day from a new domain means spam.

**Lecture interpretation:** Research and relevance may improve the value of an appropriate business message. A small test is easier to inspect than a large sequence. Set stop rules, disclose identity, honor objections, and measure useful replies and customer outcomes.

**Verification note:** The fixed volume warning is not a universal provider rule, and the short-message and sequence advice are heuristics. Email rules vary by recipient type and jurisdiction; address verification does not provide consent. Open tracking is unreliable for some recipients: Apple Mail Privacy Protection prevents senders from seeing whether a message was opened. See the official Gmail, FTC, ICO, and EU sources in Section 10 before planning email activity.

### Page 13 — Domain setup and warm-up

**Deck content:** The slide proposes a separate lookalike domain, SPF/DKIM/DMARC, two to three weeks of “fake threads,” then a ramp from five a day upward to 50, with AI watching bounce rates.

**Lecture interpretation:** Authentication, monitoring, and gradual operational rollout can be part of responsible system setup. Use a sender identity people can recognize. Monitor authentication, bounces, complaints, opt-outs, and delivery errors; pause if signals worsen.

**Verification note:** The lookalike domain, simulated conversations, and fixed daily ramp are not established by the cited Google guidelines as required methods or safe limits. A lookalike can confuse recipients. Authentication helps receivers verify a domain; it does not establish permission to contact people. Follow the provider’s current documentation and applicable law. Do not count simulated messages as real engagement.

### Page 14 — Channel-choice prompt

**Deck content:** The slide asks: “Pick one channel for your product. Why that one?”

**Lecture interpretation:** The useful output is a written hypothesis, not a favorite channel. Name the buyer, where they look for help, what proof they need, the smallest test, and what result would change your mind.

**Verification note:** Do not choose a channel just because a tool makes it easy to automate. Match the channel to the buyer’s behavior, product economics, and the team’s ability to serve resulting demand.

### Page 15 — Break

**Deck content:** A short break slide separates the acquisition-channel section from communities and marketplaces.

**Lecture interpretation:** Use the pause to record one channel hypothesis and one unresolved question. The next section asks how to earn attention inside spaces and platforms that have their own norms.

**Verification note:** No standalone factual claim is made on this page.

### Page 16 — Communities are not an automated channel

**Deck content:** The slide names Reddit, Facebook groups, Indie Hackers, Discord, and Slack. The “wrong way” is to join and post a link; the “right way” is to answer questions for two weeks before speaking up. The rule is “Be useful first, sell second.”

**Lecture interpretation:** Community participation starts with understanding the group’s rules and what members actually need. A period of listening helps the founder learn the vocabulary and recurring problems. If a product mention is relevant and permitted, make the relationship clear.

**Verification note:** “Two weeks” is a suggested practice, not a universal rule. Some communities prohibit promotion entirely; others have a designated launch thread. Follow each community’s current rules rather than assuming a waiting period creates permission.

### Page 17 — AI helps listen, not post

**Deck content:** AI creates a daily monitoring digest and drafts replies, but the founder posts manually. The slide names Mention, Brand24, F5Bot, and n8n with RSS.

**Lecture interpretation:** A digest can reduce the effort of checking many sources. Include the source post, date, and a short reason it may matter so the person can inspect context before replying. Keep the draft visibly labeled as a draft.

**Verification note:** Monitoring public posts is still subject to platform terms, privacy expectations, data-retention choices, and rate limits. Manual posting helps preserve accountability, but does not guarantee that a reply is appropriate. Confirm the current permissions and features of each tool.

### Page 18 — Marketplaces: another audience, another set of rules

**Deck content:** AppSumo is described as cash up front with about 20% refunds and long support; Product Hunt as a one-day traffic event with brand/backlinks rather than guaranteed sales; Gumroad and Lemon as payment platforms where the seller brings traffic. The slide reports FeedBoss launched on AppSumo with $150,000+, four partners, and about 20% refunds.

**Lecture interpretation:** Compare each platform’s audience, discovery, pricing, payment role, refund terms, customer relationship, and workload. Make a realistic support and infrastructure plan before offering a discounted or lifetime plan.

**Verification note:** The refund percentage and FeedBoss sales/partner figures are reported slide claims, not independently verified results. Refund rights and windows can depend on the exact deal terms and current policy. Payment processing, marketplace discovery, and marketing are distinct platform functions; inspect each current product page and seller agreement.

### Page 19 — Launch sequence

**Deck content:** Four weeks before: waitlist, landing page, Product Hunt “coming soon,” and community posts. Two weeks before: screenshots, build process, and early feedback. Launch day: marketplace, Product Hunt, and owned channels together. One week after: respond to reviews, fix the loudest complaint, and report the fix. One month after: move to content, search, and outreach because launch traffic has faded.

**Lecture interpretation:** The sequence keeps preparation, launch, and post-launch learning connected. The most valuable post-launch activity may be correcting the first confusing or broken step that many users encounter. Build an ongoing acquisition loop before assuming a one-day event will sustain growth.

**Verification note:** This calendar is a template. Product Hunt’s own guidance says makers can launch their own product and emphasizes genuine engagement; follow its current rules rather than assuming a particular day or rank guarantees results. Use community posts only where permitted.

### Page 20 — What happens after signup

**Deck content:** Behavior-triggered onboarding email, activation analysis to find the action separating stayers from leavers, and a first output that works with realistic sample data. The slide names Customer.io, Loops, PostHog, Mixpanel, Claude API, and n8n. It connects the work to Class 3’s “first five minutes.”

**Lecture interpretation:** The first-use experience should help a real person reach the product’s core outcome quickly. Define the activation event, check where new users stall, and use small tests to improve the path. Sample data is useful when clearly labeled and safe to remove.

**Verification note:** “Stayers vs leavers” is a hypothesis that needs cohort and time-window analysis. Do not let AI infer activation from vague activity. Behavior-triggered emails must respect current consent, unsubscribe, and provider requirements.

### Page 21 — Support that scales with review

**Deck content:** Ticket comes in, AI classifies it, AI drafts a reply, a human reviews, and then it is sent. Refunds/billing/pricing, anger, and precedent-setting cases are never auto-sent.

**Lecture interpretation:** Human review is a sensible gate for actions with financial or policy consequences. Add a known-answer source, customer-context check, escalation path, and audit trail. Make sure the AI cannot silently issue a refund, change a plan, or promise a feature.

**Verification note:** The “never auto-sent” rule is the deck’s operating recommendation. It is especially useful for small teams that have not validated draft quality. Even low-risk answers need a monitoring process and a way to correct misinformation.

### Page 22 — Repeated tickets reveal product questions

**Deck content:** The slide says repeated questions are likely UX issues, recommends turning the top three clusters into spec changes, and shows AI routing: repeated question to a Linear issue, bug pattern to an existing issue, feature cluster to a roadmap, and weekly spikes to Slack. The founder still decides what ships.

**Lecture interpretation:** Ticket clustering can make a hidden pattern visible. Preserve representative, redacted examples and counts. Then ask whether the cluster is caused by unclear language, a defect, a product gap, a specific customer segment, or a policy mismatch.

**Verification note:** “Ten times” and “top three” are convenient thresholds, not proof. One severe incident can matter more than ten low-impact questions. AI clustering may combine different problems or split one problem into several labels; review examples before creating or reprioritizing issues.

### Page 23 — Read product data with AI assistance

**Deck content:** The slide contrasts manually watching 40 replays, waiting for SQL, and unread reports with AI summaries of stuck users, plain-English query generation, and a Monday summary of changes plus one number. It advises asking where the drop is if AI says everything looks fine. Tools include PostHog, Hotjar, FullStory, Amplitude, and Metabase.

**Lecture interpretation:** AI can shorten the path from a question to a first analysis. Ask it to show the exact event, cohort, dates, exclusions, query, and evidence. Request negative evidence and plausible alternatives instead of accepting a reassuring summary.

**Verification note:** A summary can miss small cohorts, exceptions, and data-quality problems. Session recordings may capture sensitive content; use masking, access controls, retention limits, and appropriate notice/consent. Check generated SQL and calculations before acting. See the analytics vendor’s current privacy documentation.

### Page 24 — Find the bottleneck

**Deck content:** A prompt supplies visitor, signup, activated, and paid counts and asks for the largest drop plus three specific tests. The slide warns that generic answers are not useful and says to ask again for product-specific advice.

**Lecture interpretation:** Add exact event names, cohort, date range, acquisition source, and definitions. Ask for rates and counts, not only a conclusion. A useful test is one that distinguishes competing explanations and has a measurable outcome.

**Verification note:** AI cannot infer your product context from four numbers alone. A large percentage drop may come from a tiny sample or a tracking defect. Do not run a test until you confirm the data and can explain what result would support or reject the hypothesis.

### Page 25 — Choose what to automate this week

**Deck content:** The slide asks for the channel to test this week and the first task to automate.

**Lecture interpretation:** Pick a task that is frequent, bounded, and easy to review—such as summarizing a public-topic feed or labeling support categories. Keep external messages and policy decisions behind a human approval step.

**Verification note:** Automating an unproven process can make waste or mistakes happen faster. First document the current manual task, its quality bar, the expected time saved, and how errors will be detected.

### Page 26 — Build a four-week launch plan

**Deck content:** Use the product spec, ICP, and selected channel to plan what to build, write, post, and whom to message each week. Include domain setup if outreach is a channel.

**Lecture interpretation:** Make the calendar concrete: owner, deliverable, date, audience, measure, and decision point. A four-week plan should include readiness and customer follow-up, not only launch-day promotion. If a message channel is under consideration, insert compliance and provider review before sending.

**Verification note:** The timeline is a planning scaffold, not evidence that every channel can be prepared safely in four weeks. The deck’s domain warm-up sequence is not a substitute for current provider guidance or local legal review.

### Page 27 — Homework and next class

**Deck content:** Students prepare a channel choice and reason, a specific four-week plan, and a support plan dividing AI work from human work. The next class is AI in Operations.

**Lecture interpretation:** The hand-in should show the reasoning behind the channel, the evidence to gather, the risks, and the person responsible for each review gate. The support plan should specify what the AI may draft or route and which cases require a human decision.

**Verification note:** A plan is a hypothesis. Label assumptions, select a measurable test, and update the plan when user evidence contradicts it.

## 7. Guided practical: launch a small B2B research tool

**Scenario:** A hypothetical product helps small software consultancies prepare a source-backed list of organizations that may need a specific service. It does not send email automatically. This is a classroom example, not a recommendation to scrape or contact any particular person.

### Step 1: Choose one buyer

Write a narrow ICP, such as a firm type, size range, geography, and public signal that suggests a possible need. Add exclusions. Ask two or three people who match the profile whether the signal is meaningful; do not assume it is because a model says so.

### Step 2: Define the product outcome

A first version might return a short list of organizations with a source URL, the reason each appears to fit, the date checked, and a clear uncertainty label. A record without evidence is not shown as a qualified result.

### Step 3: Choose one channel test

Compare two candidates:

| Candidate | Why it might fit | Four-week test |
|---|---|---|
| Direct conversations | Buyer may need trust and can explain current workflow | Hold five appropriate, permission-aware discovery conversations |
| Search content | Buyer may already search for the problem | Publish one useful comparison or workflow page and measure qualified actions |

Select one based on buyer behavior and team capacity. Do not launch both simply because the slide lists multiple channels.

### Step 4: Instrument the first-use funnel

Define visitor, signup, report-created, report-reviewed, and paid events. Test the instrumentation with a test account. Use a clear cohort and date range.

### Step 5: Add a support loop

Classify questions as data quality, usability, product gap, billing, or privacy. The AI may draft a response from approved documentation; a person reviews the answer. Redact personal data before analysis.

### Step 6: Review the result

At the end of four weeks, record:

- number of appropriate conversations or qualified visits;
- signup and activation counts and rates;
- the first point where users stall;
- repeated questions and example tickets;
- delivery, support, and model costs;
- assumptions that were confirmed, rejected, or remain unknown;
- one product or channel decision for the next cycle.

## 8. Exercises and assessment

### Exercise A — Channel fit

Choose a real or hypothetical product. Select one first channel. Write a one-paragraph reason that includes buyer behavior, required proof, expected support, and a four-week test. Name a result that would make you stop or change direction.

### Exercise B — Lead-list audit

Review ten sample lead records. For each one, mark source URL, date, evidence, ICP match, uncertainty, jurisdiction, data source, and human disposition. Identify any record that should be suppressed or removed. Explain why verification is different from permission.

### Exercise C — Outreach claim audit

Assess the slide’s “50 per day,” “fake threads,” “under 80 words,” and “day 1/3/7” instructions. Classify each as:

- provider requirement;
- legal requirement in a named jurisdiction;
- vendor/course heuristic;
- unverified outcome claim.

Then replace the slide’s blanket guidance with a decision checklist that checks recipient, jurisdiction, source, provider terms, suppression, and success metrics.

### Exercise D — Funnel analysis

Given 1,000 visitors, 100 signups, 40 activated users, and 8 paid users:

1. Calculate each stage conversion using the prior stage.
2. Calculate paid conversion from signup.
3. State which denominator you would use for each question.
4. List two tracking errors and two non-tracking explanations for the largest drop.
5. Propose a small test and a guardrail.

### Exercise E — Ticket triage

Classify five anonymized tickets. Decide which the AI can summarize or draft, which require human approval, and which should become a product investigation. Remove personal details from the examples before sending them to an external AI tool.

### Exercise F — Launch plan review

Exchange four-week plans with a partner. Check whether each week has an owner, output, audience, metric, support capacity, and stop/change decision. Flag any line that assumes launch traffic or a fixed email volume will produce a predictable result.

### Assessment rubric

| Criterion | Strong submission |
|---|---|
| Channel reasoning | Connects a specific buyer behavior to one measurable channel test |
| Evidence quality | Distinguishes observed facts, assumptions, and slide/vendor claims |
| Data quality | Defines events, cohort, time window, and denominators |
| Responsible automation | Uses a human gate for consequential external or policy decisions |
| Customer learning | Connects tickets and analytics to testable product hypotheses |
| Practicality | Assigns owners, workload, timeline, and a decision rule |

## 9. Exam review

**What is the difference between a lead and a qualified lead?**  
A lead is a candidate record. A qualified lead has evidence that it meets explicit fit criteria and has been reviewed for relevance and appropriate use. Address validity alone is not qualification.

**Why can channel choice change the product spec?**  
Each channel creates different expectations for proof, onboarding, pricing, support, and time to value. These needs can affect what the first version must include.

**What is the human’s role in the five-channel map?**  
The human sets the goal and criteria, reviews output, approves external actions, decides terms, handles sensitive cases, and interprets outcomes.

**Does SPF/DKIM/DMARC prove that a recipient agreed to marketing?**  
No. These mechanisms authenticate a sending domain and support mail handling. They do not establish consent or lawful contact.

**Is 50 emails per day a universal safe threshold?**  
No universal threshold is established by the slide or Gmail’s published sender guidance. Sending limits and deliverability depend on provider rules, authentication, reputation, complaints, message type, recipient behavior, and applicable law.

**Why are open rates weak evidence?**  
Some privacy features can prevent senders from seeing whether mail was opened. Replies, qualified meetings, activation, conversion, opt-outs, and complaints usually give more actionable evidence.

**What does AI visibility testing reveal?**  
It can reveal how a small set of model responses describe a product at a particular time. It cannot prove general buyer awareness, demand, or future recommendations.

**What is an activation event?**  
A defined, observable behavior that indicates the user has experienced the product’s main value. It should be connected to the product outcome and measured for a named cohort and time window.

**Why are repeated support tickets useful?**  
They can reveal friction, bugs, unclear expectations, or missing information. A cluster is a signal to investigate, not automatic proof that a feature should be built.

**What should be checked in AI-generated funnel analysis?**  
Event names, deduplication, cohort, dates, exclusions, denominators, SQL, missing data, sample size, and alternative explanations.

**What is the class’s core operating rule?**  
Let AI prepare and organize repeatable work; keep accountable humans responsible for judgment, public claims, money, policy, and customer consequences.

## 10. Necessary links and sites

Links below are grouped by the job they support. Official guidance comes first where available. Vendor links are product references, not endorsements; check live pricing, policy, features, and data handling before use.

### A. Email delivery, direct marketing, and privacy

- [Gmail email sender guidelines](https://support.google.com/mail/answer/81126?hl=en) — authentication, sender requirements, and delivery guidance.
- [Gmail sender-guidelines FAQ](https://support.google.com/mail/answer/14229414?hl=en) — spam-rate and unsubscribe details for relevant messages.
- [Google Postmaster Tools](https://postmaster.google.com/) — sender reputation and delivery diagnostics for Gmail.
- [FTC: CAN-SPAM Act compliance guide](https://www.ftc.gov/business-guidance/resources/can-spam-act-compliance-guide-business) — official US business guidance.
- [UK ICO: business-to-business marketing](https://ico.org.uk/for-organisations/direct-marketing-and-privacy-and-electronic-communications/business-to-business-marketing/) — UK distinction between corporate and individual subscribers and use of personal data in business contexts.
- [UK ICO: electronic mail marketing](https://ico.org.uk/for-organisations/direct-marketing-and-privacy-and-electronic-communications/guide-to-pecr/electronic-and-telephone-marketing/electronic-mail-marketing/) — UK consent, existing-customer exception, identity, and opt-out guidance.
- [EU ePrivacy Directive 2002/58/EC](https://eur-lex.europa.eu/eli/dir/2002/58/oj/eng) — primary EU legal text; check national implementation and later amendments.
- [Bangladesh National Cyber Security Agency: laws and regulations](https://dsa.portal.gov.bd/pages/static-pages/6922e12a933eb65569e2a9f5) — official index listing Bangladesh’s Personal Data Protection Ordinance 2025 and related legal materials. Read the current text and status; this sheet does not interpret it.
- [Bangladesh Laws portal](https://bdlaws.minlaw.gov.bd/) — official legislation portal.
- [Apple: Mail Privacy Protection](https://support.apple.com/guide/iphone/use-mail-privacy-protection-iphf084865c7/ios) — explains that the feature can prevent senders from seeing whether a message was opened.

**Use these sources by recipient jurisdiction and message type.** A law applying in one country does not determine the rules for recipients elsewhere. Review current rules before collecting, enriching, storing, or contacting people.

### B. Search and structured data

- [Google Search Essentials](https://developers.google.com/search/docs/essentials) — technical eligibility, spam policies, and core best practices.
- [Google: creating helpful, reliable, people-first content](https://developers.google.com/search/docs/fundamentals/creating-helpful-content) — content self-assessment.
- [Google structured-data policies](https://developers.google.com/search/docs/appearance/structured-data/sd-policies) — requirements and limits for structured data.
- [Google Search Console](https://search.google.com/search-console/about) — monitor search performance and indexing information.
- [Ahrefs](https://ahrefs.com/) — SEO research and site-audit product.
- [Semrush](https://www.semrush.com/) — SEO and marketing research product.
- [Surfer](https://surferseo.com/) — content research and optimization product.

### C. Workflow and research automation

- [Apify documentation](https://docs.apify.com/) — actors, APIs, integrations, and platform documentation.
- [n8n documentation](https://docs.n8n.io/) — workflow automation documentation.
- [Make](https://www.make.com/) — visual workflow automation product.

Check source terms, API limits, authorization, privacy, retention, and error handling before using these tools on real data.

### D. Outreach and content tools named in the deck

- [Instantly](https://instantly.ai/)
- [Smartlead](https://www.smartlead.ai/)
- [Lemlist](https://www.lemlist.com/)
- [Canva](https://www.canva.com/)
- [Beehiiv](https://www.beehiiv.com/)
- [Kit (formerly ConvertKit)](https://kit.com/)
- [LinkedIn](https://www.linkedin.com/)

These tools do not determine whether a campaign or post is appropriate. Check current platform terms, local rules, authentication, data processing, and account permissions.

### E. Communities and listening

- [Reddit](https://www.reddit.com/)
- [Indie Hackers](https://www.indiehackers.com/)
- [Discord](https://discord.com/)
- [Slack](https://slack.com/)
- [Brand24](https://brand24.com/)
- [F5Bot](https://f5bot.com/)

Every group or forum has its own current rules. A monitoring tool should help a person inspect context, not post or message members automatically.

### F. Marketplaces and launch platforms

- [Product Hunt launch guide](https://www.producthunt.com/launch) — platform’s current preparation and launch guidance.
- [Product Hunt: before launch](https://www.producthunt.com/launch/before-launch)
- [AppSumo marketplace](https://appsumo.com/)
- [AppSumo refund policy](https://help.appsumo.com/article/31-refund-policy) — current policy points to the timeframe and terms on each deal page.
- [AppSumo partner/seller information](https://sell.appsumo.com/)
- [FeedBoss on AppSumo](https://appsumo.com/products/feedboss/) — current product listing; not independent evidence for the historic figures on the slide.
- [Gumroad](https://gumroad.com/)
- [Lemon Squeezy](https://www.lemonsqueezy.com/)

Read the individual offer, seller agreement, refund terms, fees, payment terms, and customer-support obligations before modeling marketplace economics.

### G. Onboarding, support, product analytics, and issue tracking

- [Customer.io](https://customer.io/)
- [Loops](https://loops.so/)
- [PostHog session replay documentation](https://posthog.com/docs/session-replay) — capture configuration, masking, privacy, and retention.
- [PostHog](https://posthog.com/)
- [Mixpanel](https://mixpanel.com/)
- [Hotjar](https://www.hotjar.com/)
- [Fullstory](https://www.fullstory.com/)
- [Amplitude](https://amplitude.com/)
- [Metabase](https://www.metabase.com/)
- [Linear](https://linear.app/)

Before recording sessions or analyzing support data, review notice/consent requirements, masking, access, retention, vendor terms, and whether sensitive content can be excluded.

### H. Model assistants for manual description checks

- [ChatGPT](https://chatgpt.com/)
- [Claude](https://claude.ai/)
- [Google Gemini](https://gemini.google.com/)
- [Righted](https://www.righted.io/) — vendor product named in the deck; treat its visibility results as a tool’s sample and method, not a universal measure.
- **AgentiSEO:** the deck supplies this name without a URL; I could not unambiguously verify the official product site in this review.

## 11. Final takeaways and next-class checklist

### Five takeaways

1. A channel is a hypothesis about how a specific buyer discovers and evaluates the product.
2. Lead volume and email validity do not establish relevance, permission, or revenue potential.
3. AI can accelerate drafts and analysis, but search rankings, recommendations, inbox placement, and launch sales are not guaranteed.
4. After signup, measure activation and retention with named events, cohorts, time windows, and denominators.
5. Support patterns and analytics suggest what to investigate; a person decides what to promise, refund, change, or ship.

### Class 4 hand-in

1. **Channel choice:** one selected channel, buyer-fit reason, evidence, and a four-week success measure.
2. **Four-week launch plan:** weekly work, owner, audience, output, metric, review date, and stop/change rule.
3. **Support plan:** what AI may classify, summarize, or draft; what a human must approve; privacy and escalation rules.

### Before the next class: AI in Operations

- Bring one repetitive operational task with a clear input and output.
- Estimate current time, error rate, cost, and who is affected.
- Identify the data and permissions the task requires.
- Define what the AI may do, what it may only recommend, and what requires approval.
- Propose a small test with a human fallback and a measurable quality threshold.

