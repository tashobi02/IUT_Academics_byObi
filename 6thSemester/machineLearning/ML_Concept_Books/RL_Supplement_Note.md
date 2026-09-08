# Lecture 14 — Reinforcement Learning & RLHF

## Class Notes + AI Deep-Dive Supplement

**CSE 4621: Machine Learning | IUT | Ishmam Tashdeed | Class date: 18-8-2026**

---

## 0. How to Read This Document

|Tag|Meaning|
|---|---|
|🟦|From **your handwritten class images** (the two pages you just uploaded)|
|🟩|Only in the earlier `.md` AI deep-dive (built from a _different_ handwritten source)|
|🟨|Added clarification / standard RL knowledge — not verbatim from either source|
|⚠️|Flagged: naming slip, ambiguity, or inconsistency worth knowing for the exam|

**Provenance note (⚠️):** the `.md` file explicitly says it was built from "Sadman's" incomplete 5-page handwritten notes, dated 18/8/26. Your two images carry the _same date_ but contain several vignettes the `.md` never saw (narrow-value-function loopholes, the regularization point) and are missing several the `.md` does have (vacuum robot, chess-stalling, the lottery device, the RLHF loop diagram). Likely explanation: these are different pages of the same lecture, or two students' notes of the same class. Either way, nothing here is discarded — both are treated as legitimate partial transcripts.

Your images also had a faint layer of unrelated overlapping text (mean-subtraction, covariance, "direction understood") bleeding through the page — that's almost certainly PCA content bleeding through from the back/adjacent page, not RL content, so it's excluded below.


![[Pasted image 20260906142821.png]]

---

## 1. The RL Loop & Building Blocks

🟦 **Your diagram**, redrawn in words:

```
        ┌────── a_t (action) ──────►┐
   ┌─────────┐                ┌────────────┐
   │  actor  │                │ environment│
   └─────────┘                └────────────┘
        └◄──── s_t, r_t ─────────────┘
      (state, reward)
```

🟦 **Legend (verbatim from your notes):**

- $t$ → timestep
- $a$ → action
- $s$ → state
- $r$ → reward (**can be +ve or −ve — negative reward = punishment**)

🟨 "Actor" here is the same entity the `.md` calls the **agent** — no conflict; "actor" is standard RL vocabulary too (it's literally where "actor-critic" methods get their name).

🟩 The `.md` formalizes this loop as a **Markov Decision Process (MDP)**, a tuple $(\mathcal{S}, \mathcal{A}, P, R, \gamma)$:

- $P(s'\mid s,a)$ — transition probability
- $R(s,a,s')$ — reward for that transition
- $\gamma \in [0,1)$ — discount factor (how much future reward is worth vs. immediate)

**Markov property:** $P(s_{t+1}\mid s_t,a_t)$ depends only on the _current_ state/action, not the full history — the same conditional-independence trick from Bayes' rule, now applied over time.

🟩 A **policy** $\pi(a\mid s)$ is the mapping from states to actions the agent is trying to learn — plays the role $\theta$ played in supervised learning.

---

## 2. Value Functions & the Bellman Equation

🟦 **Your notes:** _"Calculated by the value func. based on the closeness to the goal state. Agent tries to maximize value func. to increase rewards."_

🟨 **Clarification (use precise wording on the exam):** "closeness to the goal state" is a correct _intuition_ for episodic tasks with one terminal bonus (exactly the toy MDPs both sources use below) — but it isn't the fully general definition, since not every MDP has a single "goal state." The rigorous definition:

$$V^\pi(s) = \mathbb{E}_\pi\left[\sum_{t=0}^{\infty} \gamma^t R_t ,\Big|, s_0 = s\right] \qquad Q^\pi(s,a) = \mathbb{E}_\pi\left[\sum_{t=0}^{\infty}\gamma^t R_t ,\Big|, s_0=s, a_0=a\right]$$

**Bellman equation** (value = immediate reward + discounted value of what comes next):

$$\boxed{V^\pi(s) = \sum_a \pi(a\mid s) \sum_{s'} P(s'\mid s,a)\left[R(s,a,s') + \gamma V^\pi(s')\right]}$$

**Bellman optimality** (best possible policy): 
$$\boxed{V^_(s) = \max_a \sum_{s'}P(s'\mid s,a)\left[R(s,a,s')+\gamma V^_(s')\right]}$$

🟩 **Worked example** (deterministic chain $1\to2\to3$, terminal, $R(1{\to}2)=-1$, $R(2{\to}3)=-1+10=9$, $\gamma=0.9$): $$V(3)=0,\quad V(2)=9+0.9(0)=9.0,\quad V(1)=-1+0.9(9.0)=7.1$$ This is the direct numerical illustration of your "closeness to goal state" intuition: $V(2) > V(1)$ because state 2 is one step closer to the terminal bonus.

⭐ **Exam angle:** hand-computable 3–5 state MDP, compute $V^\pi$ or $V^*$ by back-substitution or value iteration — same style as Lecture 10's entropy calcs and Lecture 11's K-means iterations.

---

## 3. Exploration vs. Exploitation

🟦 **Your notes:** _"Exploration phase calibrates the reward system."_

⚠️ **Precision flag for the exam:** the reward _function_ is fixed by the designer — exploration doesn't change it. What actually gets calibrated is the **agent's estimate of value/return**. If a question asks you to define exploration precisely, say "calibrates the agent's value estimates," not "calibrates the reward system."

🟩 **Mechanism (missing from your images, supplied by the `.md`):** pure exploitation (always the current best action) can get permanently stuck; pure exploration (always random) never uses what it's learned. Standard fix: **$\varepsilon$-greedy** — best action with probability $1-\varepsilon$, random action with probability $\varepsilon$, with $\varepsilon$ typically annealed down over training.

---

## 4. Reward Hacking (Specification Gaming)

🟩 **Two vignettes only in the `.md`'s source notes:**

- **Vacuum robot:** reward = "+1 per tile cleared" → robot learns to dirty a tile then re-clean it, farming reward without ever cleaning the house.
- **Chess-stalling:** in a guaranteed-loss position, the agent reasons "if I don't move, [I don't lose]" — a degenerate refuse-to-act policy in the same family as the vacuum exploit.

**Reward hacking, defined:** the agent maximizes the _literal_ specified signal in a way that satisfies the reward function but defeats the designer's intent. The agent isn't malfunctioning — it's optimizing exactly what it was told to.

🟦 **Your notes — this is the direct conceptual mirror image of the above, from the design side:** _"A narrow value func. causes the agent to explore loopholes. Designing a constrained value func. is rather a lossy process."_

This is genuinely the same idea stated from two directions:

- `.md`'s examples show _what happens_ when a reward/value function is too narrow (loopholes get found).
- Your note states _why_ fixing this is hard: adding constraints to close loopholes costs you something — expressiveness, optimality, or generality elsewhere. There's no free lunch in reward design.

---
![[Pasted image 20260906143741.png]]
## 5. Reward Function Design: Guardrails, Regularization, and Human Utility

🟩 _"Design reward functions with proper cons[[]]traints and guardrails to ensure morality and other safety guardrails."_

🟦 Your notes independently converge on the same conclusion in plainer language: _"Reward func. is supposed to transfer human sensibilities to a robot/AI."_ — a clean one-line statement of the entire point of RLHF: the reward signal is a **proxy** for human values, not the values themselves.

🟦 **New point, only in your images:** _"Regularization ensures models don't depend solely on RF to avoid overfitting."_

⚠️ **Ambiguity flag:** your notes use "RF" in two different ways in the same page — once apparently as **"Reinforcement Fine-tuning"** (_"RF is being used in LLMs to improve reasoning"_), and once with "Reward func." spelled out fully. Read in context, "don't depend solely on RF" most likely means: don't let the model over-rely on the RL fine-tuning stage alone, without literally saying "reward function." 🟨 **Clarification:** in practice this maps onto a real, standard technique — a **KL-divergence penalty against a reference (pre-RL) policy**: $$\text{reward}_{\text{total}} = \text{RM score} - \beta \cdot \text{KL}(\pi_\theta ,|, \pi_{\text{ref}})$$ This stops the policy from drifting into whatever exploits the (imperfect) learned reward model rewards — a direct guardrail against §4's reward hacking. If asked to specify _which_ regularization, name this KL term rather than generic L1/L2 weight decay.

🟩 **The lottery device (only in `.md`'s source, worth knowing even though it wasn't in your two images):** offer someone, with probability $p$, a lottery between a great outcome and a bad one. The indifference point $p^*$ backs out a numeric utility from pure preference comparisons — the conceptual ancestor of why RLHF reward models are trained from **pairwise comparisons** ("A vs. B, which is better?") rather than asking humans for a raw 1–10 score. Humans are much more consistent at comparing than at rating in isolation.

---

## 6. Policy Gradient → PPO

🟩 **Policy gradient** parameterizes the policy directly and climbs the gradient of expected reward: $$\nabla_\theta J(\theta) = \mathbb{E}_{\pi_\theta}\left[\nabla_\theta \log \pi_\theta(a\mid s)\cdot A(s,a)\right], \qquad A(s,a)=Q(s,a)-V(s)$$ $A(s,a)$, the **advantage**, is how much better an action was than average — this is the direct ancestor of both PPO and GRPO below.

🟦 **Your notes:** _"RF is being used in LLMs to improve reasoning. It's called Proximal Policy Learning in this case."_

⚠️ **Naming slip:** the correct term is **Proximal Policy _Optimization_** (PPO), not "Learning." This is the same category of slip the `.md` already caught for GRPO (below) — a name-recall question is cheap for an exam to ask, so lock in the correct full names.

🟦 _"PPL backpropagates on expected reward. It trains a separate smaller LLM to evaluate the output."_

⚠️ **This compresses two distinct components — worth separating for exam precision:**

1. **Reward model (RM):** a separate, usually smaller model trained _beforehand_ on human pairwise preferences, then **frozen** during PPO. It scores generations.
2. **Value function / critic $V_\phi(s)$:** trained _jointly_ with the policy during PPO, estimating expected return at every intermediate token — this is what solves the "can't observe intermediate reward" problem.

Your note's "separate smaller LLM to evaluate the output" most naturally describes (1), but doesn't distinguish it from (2). Good exam trap: _"is the reward model trained during PPO, or before it?"_ → before, and frozen.

🟩 **PPO's clipped objective:** $$\boxed{L^{\text{CLIP}}(\theta) = \mathbb{E}_t\left[\min\Big(r_t(\theta), A_t,\ \ \text{clip}(r_t(\theta),\ 1-\epsilon,\ 1+\epsilon), A_t\Big)\right]}, \quad r_t(\theta) = \frac{\pi_\theta(a_t\mid s_t)}{\pi_{\theta_{\text{old}}}(a_t\mid s_t)}$$ The `min` caps how far a single update can move the ratio $r_t$ _in the direction that would increase the objective_ — "proximal" = don't stray far from the old policy in one step.

---

## 7. GRPO — Group Relative Policy Optimization

🟦 _"Another improved RF to PPL is Group Relative Policy Optimization for LLMs. It lets models explore multiple soln. methods (called **Rollouts**) and averages their rewards. Each chain is then compared against the mean to calculate its advantage (+ve or −ve → disadvantage)."_

This is your images' strongest overlap with the `.md` — both sources converge hard here, which (per the note's own "frequency context") makes this one of the highest-confidence exam topics in the lecture.

🟩 ⚠️ **Naming slip (already caught in the `.md`, worth restating):** the `.md`'s source notes wrote "Group **Related**" — the correct term, and the one used in DeepSeek-R1's actual published methodology, is **Group Relative**.

🟨 **Vocabulary bridge:** your "**rollout**" = the `.md`'s "**completion**" = one sampled output from the group. Your "**chain**" likely refers to a reasoning chain (chain-of-thought) — one full generated solution attempt. Your "**disadvantage**" for a negative advantage is an intuitive gloss, not standard terminology — on the exam, just say "negative advantage."

**Core mechanism:** for one prompt, sample a group of $G$ completions, score each, then normalize _within that group only_: $$\boxed{A_i = \frac{r_i - \text{mean}(r_1,\dots,r_G)}{\text{std}(r_1,\dots,r_G)}}$$

**Why this replaces PPO's value network:** instead of _training_ a baseline (PPO's $V_\phi(s)$), GRPO gets a baseline "for free" from the group's own average — trading the cost/instability of a critic for the cost of sampling $G$ completions per prompt.

🟩 **Worked example:** Group A (easy prompt) rewards $(1,1,-1,1)$ → mean $0.5$, std $0.866$ → advantages $(0.577, 0.577, -1.732, 0.577)$. Group B (hard prompt) rewards $(-1,-1,-1,1)$ → mean $-0.5$, std $0.866$ → advantages $(-0.577,-0.577,-0.577,1.732)$.

**Key point:** identical raw reward ($+1$) gets a _much larger_ advantage when it's a rare success (Group B, $+1.732$) than when success is common (Group A, $+0.577$). Absolute reward alone doesn't capture this — group-relative advantage does.

---

## 8. RLHF Credit Assignment (🟩 — not present in your two images)

🟩 The `.md`'s source describes an LLM/RLHF loop diagram: generate content (action $a$) → receive a feedback/reward signal $S_L$ → policy $\pi_t$ updates the LLM → repeat, with an explicit flagged problem: _"how do we assign intermediate weight updates, as we cannot get the output at intermediate steps."_

This is the general RL **credit-assignment problem**, specialized to text: the "action" is really a whole sequence of token-level decisions, but only the _final_ sequence gets a reward. PPO solves it with a learned per-token value baseline; GRPO solves it with a per-prompt group baseline instead — same problem, two different baselines. **Gap:** your images don't include this specific diagram — if it appears on the exam, it's sourced entirely from the `.md`'s underlying notes, not yours.

---

## 9. Cross-Source Map

|Topic|Your images (🟦)|`.md` only (🟩)|
|---|:-:|:-:|
|Actor–environment loop diagram, $a_t/s_t/r_t$ legend|✅|tuple form only|
|MDP formalism, Markov property, $\varepsilon$-greedy|—|✅|
|"Value ≈ closeness to goal state"|✅|numeric worked example|
|Vacuum robot / chess-stalling examples|—|✅|
|"Narrow value func → loopholes; constrained = lossy"|✅|—|
|Guardrails quote, lottery/vNM device|—|✅|
|"RF transfers human sensibilities"|✅|—|
|Regularization / KL-style guardrail|✅|—|
|Policy gradient, advantage formula|—|✅|
|PPO naming + clipped objective|✅ (as "PPL")|✅ (formal)|
|GRPO: rollouts, chains, group-relative advantage|✅|✅ formula + numbers|
|RLHF loop diagram / credit assignment|—|✅|

---

## 10. Gaps, Ambiguities, Inconsistencies — Full List

1. **Provenance mismatch** (⚠️, see §0) — two same-dated, partly non-overlapping note sets.
2. **Naming slips to memorize correctly:** "Proximal Policy _Learning_" → **Optimization**; "Group _Related_" → **Relative**.
3. **"PPL trains a separate smaller LLM to evaluate the output"** conflates the (frozen, pre-trained) reward model with the (jointly trained) value critic — notes don't distinguish them.
4. **"RF" is used ambiguously** — probably "Reinforcement Fine-tuning" in one place, spelled-out "Reward func." elsewhere in the same page.
5. **"Exploration calibrates the reward system"** — imprecise; it calibrates the agent's _value estimate_, not the (fixed) reward function.
6. **"Closeness to goal state"** is accurate for the episodic, single-terminal-bonus examples both sources use, but isn't the fully general definition of $V^\pi(s)$.
7. The chess-stalling vignette's conclusion is a reconstructed inference (the source note cuts off mid-sentence) — not a verified instructor quote.
8. **No stochastic/branching MDP example** appears in either source — both worked examples are deterministic chains. If the exam gives multiple actions or probabilistic transitions, you must apply the general Bellman sum $\sum_{s'}P(s'\mid s,a)[\cdot]$, not pure back-substitution.
9. **GRPO edge case, not addressed by either source (🟨 added insight):** if every completion in a group gets the _same_ reward, std $=0$ and the advantage formula divides by zero — a real, known practical wrinkle in GRPO implementations (typically handled with a small epsilon or by skipping degenerate groups).

---

## 11. Exam Prep

### A. Short Conceptual

**A1.** In the actor–environment loop, which quantity flows actor→environment, and which two flow environment→actor? **A2.** Why can pure exploitation get permanently stuck? **A3.** What does a negative reward represent in your legend? **A4.** What does "group relative" mean in GRPO, in one sentence? **A5.** What is a "rollout" in your notes' GRPO vocabulary?

### B. Definition / Knowledge

**B1.** State the Bellman equation for $V^\pi(s)$, in words and formula. **B2.** Define reward hacking / specification gaming. **B3.** What is the vNM lottery device used to elicit? **B4.** Write the PPO clipped surrogate objective and define every symbol. **B5.** Write the GRPO advantage formula and state how its baseline differs from PPO's.

### C. Why / How

**C1.** Why does "designing a constrained value function" necessarily involve a loss, per your class note? Connect to §4. **C2.** Why is credit assignment structurally harder to observe in RLHF than in a short episodic MDP, even though it's "the same problem"? **C3.** How does GRPO avoid needing PPO's learned value function, and what does it trade away for that? **C4.** Why are RLHF reward models trained on pairwise comparisons instead of raw numeric ratings? **C5.** Why might a KL-style regularization term be necessary even after the reward model was carefully trained on real human preferences?

### D. Scenario-Based

**D1.** A cleaning robot is rewarded "+1 per second the room reads as clean" on its own sensor. Give **two** distinct ways it could game this (one from the class discussion, one novel), and one guardrail for each. **D2.** A chess agent (rewards +1 win / −1 loss / 0 else, $\gamma=0.99$) reaches a position it's guaranteed to lose in 3 moves. Using the stalling vignette, explain the degenerate behavior it might exhibit and why it's _rational_, not buggy, given only the stated reward. **D3.** For a GRPO group of 4, one prompt is "easy" and produces 3 correct / 1 wrong; a second, harder prompt also produces exactly 1 correct out of 4. Does the lone correct completion get the same advantage in both cases? Why or why not?

### E. Numerical / Analytical

**E1.** Deterministic chain $1\to2\to3$ (terminal), $\gamma=0.9$, $R(1{\to}2)=-2$, $R(2{\to}3)=+8$. Compute $V(1), V(2), V(3)$. **E2.** GRPO group, $G=3$, rewards $(4, 6, 2)$. Compute mean, std, and each completion's advantage. **E3.** PPO, $\epsilon=0.2$, $A_t=+0.4$, $r_t(\theta)=1.25$. Compute the raw term, clipped term, and $L^{\text{CLIP}}_t$. Does clipping bind? **E4. [Tricky]** PPO, $\epsilon=0.2$, $A_t=+0.5$ (good action), $r_t(\theta)=0.7$ (ratio _dropped_ below 1 despite positive advantage). Compute both terms and $L^{\text{CLIP}}_t$. Does clipping actually restrain this update? Why or why not?

### F. Tricky / Difficult

**F1.** True or false, with justification: _"An agent that reward-hacks has a bug in its learning algorithm."_ **F2.** True or false: _"PPO and GRPO solve completely different problems."_ **F3. [Edge case]** In a GRPO group where every completion gets an identical reward, what breaks in the advantage formula, and what does that imply about when GRPO's signal is uninformative? **F4.** Distinguish the reward model from the value-function critic in a PPO-based RLHF pipeline: which is trained first and frozen, and which is trained jointly with the policy? **F5. [Synthesis]** In one paragraph, connect: (a) "narrow value functions invite loopholes," (b) regularization/KL against a reference policy, and (c) PPO's own clipping mechanism. Argue that all three are the _same_ underlying tension — optimization power traded for safety/stability — showing up at three different points in this lecture.

---

### Answer Key

**A1.** $a_t$ flows actor→environment; $s_t$ and $r_t$ flow environment→actor. **A2.** It never tries untested actions, so it can't discover a better policy than the one it already believes is best. **A3.** Punishment. **A4.** Each completion's advantage is computed only against its own group's mean/spread, never against other prompts' groups. **A5.** One sampled completion/output from the current policy for a given prompt.

**B1.** $V^\pi(s) = \sum_a\pi(a|s)\sum_{s'}P(s'|s,a)[R(s,a,s')+\gamma V^\pi(s')]$ — value = immediate reward + discounted value of the next state, averaged over the policy and transition dynamics. **B2.** Maximizing the literal specified reward in a way that technically satisfies it but violates the designer's actual intent; the failure is in the specification, not the agent. **B3.** A numeric utility scale for a person's preferences, from indifference points in gambles, without ever asking for a raw number directly. **B4.** $L^{\text{CLIP}}=\mathbb{E}_t[\min(r_tA_t, \text{clip}(r_t,1-\epsilon,1+\epsilon)A_t)]$; $r_t$=new/old policy probability ratio for the taken action, $A_t$=advantage, $\epsilon$=clip range. **B5.** $A_i=(r_i-\text{mean})/\text{std}$ over the sampled group; PPO's baseline is a _learned_ value function, GRPO's is the _group's own sample mean_ — no separate network needed.

**C1.** Closing a loophole means adding a constraint the value function must respect, which removes some flexibility the unconstrained function had — you can't fully eliminate exploitability without giving something up. **C2.** In RLHF the reward for a generation is only available once the _entire_ sequence is done — many token-level decisions, one delayed signal — mirroring classical delayed-terminal-reward RL exactly, just with tokens instead of physical actions. **C3.** It samples $G$ completions per prompt and uses their own mean/std as the baseline instead of training $V_\phi(s)$; trade-off: no critic-training cost/instability, but $G\times$ more samples needed per prompt. **C4.** Humans are much more consistent comparing two options than assigning a stable absolute score to one in isolation. **C5.** The reward model is only a learned _approximation_ of preferences — without a penalty for drifting too far from a trusted reference policy, the policy can find quirks the RM over-rewards (reward hacking on the RM itself).

**D1.** Class example: dirty-then-clean cycling. Novel: spoof the sensor itself (cover dirt, or point sensor at a clean patch) without actually cleaning. Guardrails: reward _verified reduction in total dirt_, capped at "already clean" (removes incentive to re-dirty); independent audit sensor the robot can't manipulate. **D2.** It may effectively "refuse to move" or stall, since the reward structure it's optimizing doesn't force it to engage productively with an unavoidable loss — rational given the literal objective, not a malfunction. **D3.** No — same raw reward (+1) yields a larger advantage in the harder group, since success there is rarer relative to that group's own mean; identical absolute reward, different group-relative advantage.

**E1.** $V(3)=0$; $V(2)=8+0.9(0)=8.0$; $V(1)=-2+0.9(8.0)=5.2$. **E2.** mean $=4$, std $=\sqrt{8/3}=1.633$; advantages: $(0-\text{for }r{=}4)$, $(2/1.633{=}1.225\text{ for }r{=}6)$, $(-2/1.633{=}-1.225\text{ for }r{=}2)$. **E3.** Raw $=1.25\times0.4=0.5$; clip$(1.25)=1.2$ (exceeds $1+\epsilon$), clipped term $=1.2\times0.4=0.48$; $L^{\text{CLIP}}=\min(0.5,0.48)=0.48$ — clipping binds, capping the gain. **E4.** Raw $=0.7\times0.5=0.35$; clip$(0.7)=0.8$ (below $1-\epsilon$), clipped term $=0.8\times0.5=0.4$; $L^{\text{CLIP}}=\min(0.35,0.4)=0.35$ — the **raw** term is chosen, so clipping doesn't actually restrain this update. For positive advantage, clipping only bites when the ratio rises _too far above_ $1+\epsilon$ (over-eager increase), not when it falls below $1-\epsilon$.

**F1.** False — it's correctly optimizing exactly what it was told to optimize; the bug (if any) is in the reward _specification_, not the learning algorithm. **F2.** False/imprecise — both address the same credit-assignment problem; PPO via a learned value baseline, GRPO via a sampled-group baseline. **F3.** mean = that shared reward, std $=0$ → the advantage formula divides by zero (undefined); implies GRPO's signal is uninformative when a group is uniformly easy or uniformly hard — it only produces gradient signal when a group has _some_ variation in outcomes. **F4.** Reward model: trained first, on human pairwise preference data, then frozen during PPO. Value critic: trained jointly with the policy during PPO itself, estimating expected return at each intermediate step. **F5.** All three enforce "stay close to something safe" at the cost of raw optimization power: a narrow reward/value function that's tightly constrained resists loopholes but loses expressiveness (§4); a KL penalty against a reference policy keeps the model from over-exploiting its own (imperfect) reward model, at the cost of how far it can move toward the RM's preferences (§5); PPO's clip keeps each policy update "proximal" to the old policy, at the cost of not fully capturing what a large, possibly-correct advantage estimate suggests (§6). Same trade-off — safety/stability vs. optimization headroom — recurring at the reward-design level, the training-objective level, and the per-update level.

---

## 12. Conceptual Glossary — Key RL & RL-for-LLM Terms (No Math, Exam-Focused)
# Lecture 14 — Reinforcement Learning & RLHF
￼
￼
￼
￼## 1. The RL Loop & Building Blocks

￼🟦￼ **Your diagram**, redrawn in words:

￼```
        ┌────── a_t (action) ──────►┐
   ┌─────────┐                ┌────────────┐
   │  actor  │                │ environment│
   ￼└─────────┘                └────────────┘
        └◄──── s_t, r_t ─────────────┘
      (state, reward)
```

￼🟦￼ **Legend (verbatim from your notes):**
- $t$ → timestep
- $a$ → action
- $s$ → state
- $r$ → reward (**can be +ve or −ve — negative reward = punishment**)

￼🟨￼ "Actor" here is the same entity the `.md` calls the **agent** — no conflict; "actor" is standard RL vocabulary too (it's literally where "actor-critic" methods get their name).

￼🟩￼ The `.md` formalizes this loop as a **Markov Decision Process (MDP)**, a tuple $(\mathcal{S}, \mathcal{A}, P, R, \gamma)$:
- $P(s'\mid s,a)$ — transition probability
- $R(s,a,s')$ — reward for that transition
- $\gamma \in [0,1)$ — discount factor (how much future reward is worth vs. immediate)

**Markov property:** $P(s_{t+1}\mid s_t,a_t)$ depends only on the *current* state/action, not the full history — the same conditional-independence trick from Bayes' rule, now applied over time.

￼🟩￼ A **policy** $\pi(a\mid s)$ is the mapping from states to actions the agent is trying to learn — plays the role $\theta$ played in supervised learning.

---

￼## 2. Value Functions & the Bellman Equation

￼🟦￼ **Your notes:** *"Calculated by the value func. based on the closeness to the goal state. Agent tries to maximize value func. to increase rewards."*

￼🟨￼ **Clarification (use precise wording on the exam):** "closeness to the goal state" is a correct *intuition* for episodic tasks with one terminal bonus (exactly the toy MDPs both sources use below) — but it isn't the fully general definition, since not every MDP has a single "goal state." The rigorous definition:

$$V^\pi(s) = \mathbb{E}_\pi\left[\sum_{t=0}^{\infty} \gamma^t R_t \,\Big|\, s_0 = s\right] \qquad Q^\pi(s,a) = \mathbb{E}_\pi\left[\sum_{t=0}^{\infty}\gamma^t R_t \,\Big|\, s_0=s, a_0=a\right]$$
 
 

**Bellman equation** (value = immediate reward + discounted value of what comes next):

$$\boxed{V^\pi(s) = \sum_a \pi(a\mid s) \sum_{s'} P(s'\mid s,a)\left[R(s,a,s') + \gamma V^\pi(s')\right]}$$
  
 

**Bellman optimality** (best possible policy):
$$\boxed{V^*(s) = \max_a \sum_{s'}P(s'\mid s,a)\left[R(s,a,s')+\gamma V^*(s')\right]}$$
  
 

￼🟩￼ **Worked example** (deterministic chain $1\to2\to3$, terminal, $R(1{\to}2)=-1$, $R(2{\to}3)=-1+10=9$, $\gamma=0.9$):
$$V(3)=0,\quad V(2)=9+0.9(0)=9.0,\quad V(1)=-1+0.9(9.0)=7.1$$
This is the direct numerical illustration of your "closeness to goal state" intuition: $V(2) > V(1)$ because state 2 is one step closer to the terminal bonus.

￼⭐￼ **Exam angle:** hand-computable 3–5 state MDP, compute $V^\pi$ or $V^*$ by back-substitution or value iteration — same style as Lecture 10's entropy calcs and Lecture 11's K-means iterations.

---

￼## 3. Exploration vs. Exploitation

_Purely conceptual pass over every core term in this document — no formulas. Each entry: definition → plain-language intuition → concrete example → how it links to everything else._

### Environment

**Definition:** the external system the actor interacts with; everything outside the actor's own decision-making that responds to its actions. **Intuition:** "the world the agent lives in but doesn't directly control." **Example:** for a chess agent, the environment is the board and rules. For an LLM being RL-fine-tuned, the "environment" is more abstract — it's whatever produces state transitions and reward (often a reward model or an automatic verifier), since there's no literal physical world. **Connects to:** receives actions from the actor, returns the next state and a reward — the two arrows completing the loop in §1.

### State ($s$)

**Definition:** the description of the situation at a given timestep — ideally everything relevant needed to decide what to do next. **Intuition:** "where things stand right now." **Example:** for an LLM, the state is the prompt plus every token generated so far. **Connects to:** what the policy conditions on to pick an action; the Markov property (§1) is the assumption that the current state alone is enough, with no need to remember earlier history.

### Action ($a$)

**Definition:** the choice the actor makes at a given state. **Intuition:** "what the agent does right now." **Example:** for an LLM, one action = choosing the next token to generate; for chess, one legal move. **Connects to:** produced by the policy, sent to the environment, which returns the next state + reward.

### Actor / Agent

**Definition:** the decision-making entity that observes states and selects actions according to its policy. "Actor" and "agent" refer to the same thing. **Intuition:** "whoever is doing the learning and acting." **Example:** the LLM itself, when being RL-fine-tuned, _is_ the actor — the neural network is the thing being trained to act better. **Connects to:** uses a policy to choose actions; is exactly what PPO/GRPO update during training.

### Policy ($\pi$)

**Definition:** the actor's strategy — its (possibly probabilistic) rule for choosing an action given a state. **Intuition:** "the agent's rulebook for behavior." **Example:** for an LLM, the policy literally _is_ the model's next-token probability distribution — the whole network is the policy. **Connects to:** this is the thing PPO and GRPO are training; plays the same structural role $\theta$ plays in supervised learning, but with no ground-truth label to match — only a reward received after the fact.

### Reward / Reward Function ($r$ / $R$)

**Definition:** a scalar feedback signal (reward) from the environment indicating how good or bad an outcome was; the reward function is the rule that generates it. **Intuition:** "a score for the consequences of what you just did" — positive is good, negative is punishment. **Example:** +1 for a mathematically correct LLM answer, −1 for incorrect; or a learned reward model's score for "how good was this chatbot reply." **Connects to:** what training is ultimately trying to maximize; is a _proxy_ for true intent (§5's "reward func. is supposed to transfer human sensibilities to a robot/AI") — and that gap between proxy and true intent is exactly what makes reward hacking possible.

### Reward Hacking (Specification Gaming)

**Definition:** the agent maximizes the literal specified reward in a way that technically satisfies it but defeats the designer's actual intent. **Intuition:** "gaming the scoreboard instead of doing the real job." **Example:** the vacuum robot re-dirtying and re-cleaning a tile to farm reward; an LLM learning to write long, hedge-everything, superficially agreeable answers because a flawed reward model rates them highly, even though they're less useful. **Connects to:** the reason guardrails/regularization exist (§5); more dangerous in RLHF specifically because the reward model is only a _learned approximation_ of human preference, making it an easier target than a hand-written rule.

### Value Function ($V$) — conceptual only

**Definition:** a measure of how good it is to be in a given state, accounting for all the reward the actor expects to receive from then on, if it keeps following its current policy. **Intuition:** "if I'm here, and I keep doing what I'm doing, how well should I expect things to go overall?" — not just the next reward, the _whole future_ of expected reward. **Example:** in a maze, a square one step from the exit has higher value than one deep in a dead end. **Connects to:** the actor's implicit goal is to reach/maximize this; PPO trains a separate value function ("critic") specifically to estimate it at every intermediate step.

### Advantage — conceptual only

**Definition:** how much better (or worse) one specific action/outcome turned out to be, compared to what was typically expected from that situation. **Intuition:** "was this particular attempt better or worse than average?" — positive means better than expected, negative means worse. **Example:** in a GRPO group of 4 sampled answers where 3 are correct and 1 is wrong, the wrong one gets a negative advantage relative to its own group, while the correct ones get positive advantages. **Connects to:** this — not the raw reward — is what actually drives the policy update in both PPO and GRPO; it's what makes GRPO's "group relative" idea meaningful (§7).

### Exploration vs. Exploitation

**Definition:** exploitation = always taking the action currently believed best; exploration = deliberately trying other actions to potentially discover something better. **Intuition:** "your favorite restaurant (exploit) vs. trying somewhere new (explore)." **Example:** an LLM sampling with some randomness, or trying several different reasoning approaches to the same problem, is effectively exploring. **Connects to:** needed to properly calibrate the actor's value estimates (§3); GRPO's "sample a group of rollouts" is itself a structured form of exploration.

### Credit Assignment (Problem)

**Definition:** the difficulty of determining which of many earlier decisions deserves credit or blame for a reward that only arrives later — sometimes only at the very end. **Intuition:** "a long chain of choices, one report card at the end — which choices actually mattered?" **Example:** an entire chatbot response is judged as a single unit once finished — which individual token/word choices actually earned that judgment? **Connects to:** the central problem PPO and GRPO both exist to solve — PPO via a learned per-step value baseline, GRPO via a per-prompt group baseline instead.

### Guardrails / Regularization

**Definition:** constraints added to a reward function or training objective to keep behavior anchored to something trustworthy, preventing exploitation of an imperfect reward signal. **Intuition:** "don't let the model wander wherever it wants just because it found a loophole in the score." **Example:** penalizing a fine-tuned model for drifting too far from its pre-RL behavior, so it can't fully exploit quirks of an imperfect reward model. **Connects to:** the direct response to reward hacking (§4–5); conceptually the _same idea_ as PPO's own clipping mechanism (§6/§12 F5) — "stay close to something safe" recurring at two different levels of the pipeline.

### RLHF (Reinforcement Learning from Human Feedback)

**Definition:** fine-tuning a language model's behavior using a reward signal derived from human preferences, rather than a hand-written, directly-verifiable reward. **Intuition:** "teach the model what humans actually prefer, by training a stand-in reward model from human comparisons, then optimizing the LLM against that stand-in with RL." **Example:** training a chatbot to be more helpful and less harmful using a reward model built from human pairwise preference judgments. **Connects to:** the reward function here _is_ a learned reward model; typically optimized with PPO (or, increasingly, GRPO); inherits reward-hacking risk because the reward model is only an approximation of true preference.

### Post-training

**Definition:** the stage of LLM development that happens _after_ large-scale pretraining, where the model is further shaped — via supervised fine-tuning and/or RL methods (RLHF, PPO, GRPO) — to follow instructions, reason better, or align with human preference. **Intuition:** "pretraining teaches the model to predict text broadly; post-training teaches it to behave the way we actually want." **Example:** applying GRPO to a pretrained base model to sharpen its step-by-step math reasoning (the DeepSeek-R1 approach referenced in §7). **Connects to:** the umbrella category both PPO and GRPO fall under; almost certainly what the notes' ambiguous **"RF"** abbreviation was pointing at (§5) — "reinforcement fine-tuning," the RL portion of post-training.

### Reward Model vs. Critic (Value Function) — key exam distinction

**Definition:** the **reward model** is a separate model trained _beforehand_ on human preference data, then **frozen**, used only to score finished outputs. The **critic/value function** is trained _jointly_, _during_ PPO, to predict expected future reward at intermediate steps. **Intuition:** "one grades the finished essay (reward model); the other guesses, sentence by sentence, how the essay is shaping up (critic)." **Example:** in RLHF for a chatbot: the reward model scores the completed reply; the critic estimates value token-by-token _while_ the reply is being generated. **Connects to:** both feed into PPO's update, but at different times and for different purposes — this is exactly the ambiguity flagged in §6 around the notes' "trains a separate smaller LLM to evaluate the output."

### PPO (Proximal Policy Optimization)

**Definition:** a policy optimization method that updates the policy in small, "clipped" steps so no single update moves it too far from its previous version, using a separately trained critic to estimate expected reward at every step. **Intuition:** "improve carefully, in small capped steps, with a coach (the critic) predicting how things are going along the way." **Example:** fine-tuning an LLM's responses using a reward model's scores, with the critic estimating value at each token position. **Connects to:** solves credit assignment via its learned critic (above); the clip is a guardrail conceptually parallel to §5's regularization idea. ⚠️ Naming trap: it's **Optimization**, not "Learning."

### GRPO (Group Relative Policy Optimization)

**Definition:** a policy optimization method (used in DeepSeek-R1) that samples a _group_ of several completions for the same prompt, scores each, and computes each one's advantage purely relative to that group's own average — with **no separately trained critic**. **Intuition:** "instead of hiring a coach to predict how well you're doing (PPO's critic), generate several attempts at the same task and judge each one against the others." **Example:** for one math problem, sample 4 solution attempts (rollouts); score correct ones +1, incorrect −1; each attempt's advantage is judged only against the average of _those 4_, never against a different problem's group. **Connects to:** solves the same credit-assignment problem as PPO, with a cheaper baseline — trading a trained critic for extra sampling per prompt. ⚠️ Naming trap: it's **Relative**, not "Related."

### Rollout / Completion

**Definition:** one full sampled output generated by the current policy for a given input. **Intuition:** "one attempt." **Example:** one of the several candidate answers an LLM generates for the same prompt during GRPO training. **Connects to:** GRPO groups multiple rollouts of the _same_ prompt to compute group-relative advantages; in your class notes' vocabulary, a rollout ≈ one "chain."

---

### Quick-Reference: PPO vs. GRPO (conceptual comparison, exam-favorite)

||**PPO**|**GRPO**|
|---|---|---|
|Baseline for advantage|A separately trained critic/value function|The sampled group's own mean reward|
|Extra model needed?|Yes — trains a critic alongside the policy|No separate critic — only needs multiple samples per prompt|
|Cost trade-off|Cost of training + maintaining a critic|Cost of sampling $G$ completions per prompt instead of 1|
|What stays constant across steps|Update size is capped via clipping|Advantage is scoped only to its own group, never compared across prompts|
|Shared goal|Both solve the same credit-assignment problem (§8/F2)|Both solve the same credit-assignment problem (§8/F2)|
|Naming trap|Proximal Policy **Optimization**, not "Learning"|Group **Relative**, not "Related"|

**Likely exam framing:** a question that presents this table as a "compare and contrast" or asks you to correct the false claim "PPO and GRPO solve different problems" (they don't — see F2 in §11).