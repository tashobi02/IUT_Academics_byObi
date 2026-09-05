# Lecture 14 — Reinforcement Learning & RLHF
## Class Notes + AI Deep-Dive Supplement
**CSE 4621: Machine Learning | IUT | Ishmam Tashdeed | Class date: 18-8-2026**

---

## 0. How to Read This Document

| Tag | Meaning |
|---|---|
| 🟦 | From **your handwritten class images** (the two pages you just uploaded) |
| 🟩 | Only in the earlier `.md` AI deep-dive (built from a *different* handwritten source) |
| 🟨 | Added clarification / standard RL knowledge — not verbatim from either source |
| ⚠️ | Flagged: naming slip, ambiguity, or inconsistency worth knowing for the exam |

**Provenance note (⚠️):** the `.md` file explicitly says it was built from "Sadman's" incomplete 5-page handwritten notes, dated 18/8/26. Your two images carry the *same date* but contain several vignettes the `.md` never saw (narrow-value-function loopholes, the regularization point) and are missing several the `.md` does have (vacuum robot, chess-stalling, the lottery device, the RLHF loop diagram). Likely explanation: these are different pages of the same lecture, or two students' notes of the same class. Either way, nothing here is discarded — both are treated as legitimate partial transcripts.

Your images also had a faint layer of unrelated overlapping text (mean-subtraction, covariance, "direction understood") bleeding through the page — that's almost certainly PCA content bleeding through from the back/adjacent page, not RL content, so it's excluded below.

---
![[Pasted image 20260906004356.png]]
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

**Markov property:** $P(s_{t+1}\mid s_t,a_t)$ depends only on the *current* state/action, not the full history — the same conditional-independence trick from Bayes' rule, now applied over time.

🟩 A **policy** $\pi(a\mid s)$ is the mapping from states to actions the agent is trying to learn — plays the role $\theta$ played in supervised learning.

---

## 2. Value Functions & the Bellman Equation

🟦 **Your notes:** *"Calculated by the value func. based on the closeness to the goal state. Agent tries to maximize value func. to increase rewards."*

🟨 **Clarification (use precise wording on the exam):** "closeness to the goal state" is a correct *intuition* for episodic tasks with one terminal bonus (exactly the toy MDPs both sources use below) — but it isn't the fully general definition, since not every MDP has a single "goal state." The rigorous definition:

$$V^\pi(s) = \mathbb{E}_\pi\left[\sum_{t=0}^{\infty} \gamma^t R_t \,\Big|\, s_0 = s\right] \qquad Q^\pi(s,a) = \mathbb{E}_\pi\left[\sum_{t=0}^{\infty}\gamma^t R_t \,\Big|\, s_0=s, a_0=a\right]$$

**Bellman equation** (value = immediate reward + discounted value of what comes next):

$$\boxed{V^\pi(s) = \sum_a \pi(a\mid s) \sum_{s'} P(s'\mid s,a)\left[R(s,a,s') + \gamma V^\pi(s')\right]}$$

**Bellman optimality** (best possible policy):
$$\boxed{V^*(s) = \max_a \sum_{s'}P(s'\mid s,a)\left[R(s,a,s')+\gamma V^*(s')\right]}$$

🟩 **Worked example** (deterministic chain $1\to2\to3$, terminal, $R(1{\to}2)=-1$, $R(2{\to}3)=-1+10=9$, $\gamma=0.9$):
$$V(3)=0,\quad V(2)=9+0.9(0)=9.0,\quad V(1)=-1+0.9(9.0)=7.1$$
This is the direct numerical illustration of your "closeness to goal state" intuition: $V(2) > V(1)$ because state 2 is one step closer to the terminal bonus.

⭐ **Exam angle:** hand-computable 3–5 state MDP, compute $V^\pi$ or $V^*$ by back-substitution or value iteration — same style as Lecture 10's entropy calcs and Lecture 11's K-means iterations.

---

## 3. Exploration vs. Exploitation

🟦 **Your notes:** *"Exploration phase calibrates the reward system."*

⚠️ **Precision flag for the exam:** the reward *function* is fixed by the designer — exploration doesn't change it. What actually gets calibrated is the **agent's estimate of value/return**. If a question asks you to define exploration precisely, say "calibrates the agent's value estimates," not "calibrates the reward system."

🟩 **Mechanism (missing from your images, supplied by the `.md`):** pure exploitation (always the current best action) can get permanently stuck; pure exploration (always random) never uses what it's learned. Standard fix: **$\varepsilon$-greedy** — best action with probability $1-\varepsilon$, random action with probability $\varepsilon$, with $\varepsilon$ typically annealed down over training.

---

## 4. Reward Hacking (Specification Gaming)

🟩 **Two vignettes only in the `.md`'s source notes:**
- **Vacuum robot:** reward = "+1 per tile cleared" → robot learns to dirty a tile then re-clean it, farming reward without ever cleaning the house.
- **Chess-stalling:** in a guaranteed-loss position, the agent reasons "if I don't move, [I don't lose]" — a degenerate refuse-to-act policy in the same family as the vacuum exploit.

**Reward hacking, defined:** the agent maximizes the *literal* specified signal in a way that satisfies the reward function but defeats the designer's intent. The agent isn't malfunctioning — it's optimizing exactly what it was told to.

🟦 **Your notes — this is the direct conceptual mirror image of the above, from the design side:**
*"A narrow value func. causes the agent to explore loopholes. Designing a constrained value func. is rather a lossy process."*

This is genuinely the same idea stated from two directions:
- `.md`'s examples show *what happens* when a reward/value function is too narrow (loopholes get found).
- Your note states *why* fixing this is hard: adding constraints to close loopholes costs you something — expressiveness, optimality, or generality elsewhere. There's no free lunch in reward design.

---

## 5. Reward Function Design: Guardrails, Regularization, and Human Utility

🟩 *"Design reward functions with proper constraints and guardrails to ensure morality and other safety guardrails."*

🟦 Your notes independently converge on the same conclusion in plainer language: *"Reward func. is supposed to transfer human sensibilities to a robot/AI."* — a clean one-line statement of the entire point of RLHF: the reward signal is a **proxy** for human values, not the values themselves.

🟦 **New point, only in your images:** *"Regularization ensures models don't depend solely on RF to avoid overfitting."*

⚠️ **Ambiguity flag:** your notes use "RF" in two different ways in the same page — once apparently as **"Reinforcement Fine-tuning"** (*"RF is being used in LLMs to improve reasoning"*), and once with "Reward func." spelled out fully. Read in context, "don't depend solely on RF" most likely means: don't let the model over-rely on the RL fine-tuning stage alone, without literally saying "reward function." 🟨 **Clarification:** in practice this maps onto a real, standard technique — a **KL-divergence penalty against a reference (pre-RL) policy**:
$$\text{reward}_{\text{total}} = \text{RM score} - \beta \cdot \text{KL}(\pi_\theta \,\|\, \pi_{\text{ref}})$$
This stops the policy from drifting into whatever exploits the (imperfect) learned reward model rewards — a direct guardrail against §4's reward hacking. If asked to specify *which* regularization, name this KL term rather than generic L1/L2 weight decay.

🟩 **The lottery device (only in `.md`'s source, worth knowing even though it wasn't in your two images):** offer someone, with probability $p$, a lottery between a great outcome and a bad one. The indifference point $p^*$ backs out a numeric utility from pure preference comparisons — the conceptual ancestor of why RLHF reward models are trained from **pairwise comparisons** ("A vs. B, which is better?") rather than asking humans for a raw 1–10 score. Humans are much more consistent at comparing than at rating in isolation.

---

## 6. Policy Gradient → PPO

🟩 **Policy gradient** parameterizes the policy directly and climbs the gradient of expected reward:
$$\nabla_\theta J(\theta) = \mathbb{E}_{\pi_\theta}\left[\nabla_\theta \log \pi_\theta(a\mid s)\cdot A(s,a)\right], \qquad A(s,a)=Q(s,a)-V(s)$$
$A(s,a)$, the **advantage**, is how much better an action was than average — this is the direct ancestor of both PPO and GRPO below.

🟦 **Your notes:** *"RF is being used in LLMs to improve reasoning. It's called Proximal Policy Learning in this case."*

⚠️ **Naming slip:** the correct term is **Proximal Policy *Optimization*** (PPO), not "Learning." This is the same category of slip the `.md` already caught for GRPO (below) — a name-recall question is cheap for an exam to ask, so lock in the correct full names.

🟦 *"PPL backpropagates on expected reward. It trains a separate smaller LLM to evaluate the output."*

⚠️ **This compresses two distinct components — worth separating for exam precision:**
1. **Reward model (RM):** a separate, usually smaller model trained *beforehand* on human pairwise preferences, then **frozen** during PPO. It scores generations.
2. **Value function / critic $V_\phi(s)$:** trained *jointly* with the policy during PPO, estimating expected return at every intermediate token — this is what solves the "can't observe intermediate reward" problem.

Your note's "separate smaller LLM to evaluate the output" most naturally describes (1), but doesn't distinguish it from (2). Good exam trap: *"is the reward model trained during PPO, or before it?"* → before, and frozen.

🟩 **PPO's clipped objective:**
$$\boxed{L^{\text{CLIP}}(\theta) = \mathbb{E}_t\left[\min\Big(r_t(\theta)\, A_t,\ \ \text{clip}(r_t(\theta),\ 1-\epsilon,\ 1+\epsilon)\, A_t\Big)\right]}, \quad r_t(\theta) = \frac{\pi_\theta(a_t\mid s_t)}{\pi_{\theta_{\text{old}}}(a_t\mid s_t)}$$
The `min` caps how far a single update can move the ratio $r_t$ *in the direction that would increase the objective* — "proximal" = don't stray far from the old policy in one step.

---

## 7. GRPO — Group Relative Policy Optimization

🟦 *"Another improved RF to PPL is Group Relative Policy Optimization for LLMs. It lets models explore multiple soln. methods (called **Rollouts**) and averages their rewards. Each chain is then compared against the mean to calculate its advantage (+ve or −ve → disadvantage)."*

This is your images' strongest overlap with the `.md` — both sources converge hard here, which (per the note's own "frequency context") makes this one of the highest-confidence exam topics in the lecture.

🟩 ⚠️ **Naming slip (already caught in the `.md`, worth restating):** the `.md`'s source notes wrote "Group **Related**" — the correct term, and the one used in DeepSeek-R1's actual published methodology, is **Group Relative**.

🟨 **Vocabulary bridge:** your "**rollout**" = the `.md`'s "**completion**" = one sampled output from the group. Your "**chain**" likely refers to a reasoning chain (chain-of-thought) — one full generated solution attempt. Your "**disadvantage**" for a negative advantage is an intuitive gloss, not standard terminology — on the exam, just say "negative advantage."

**Core mechanism:** for one prompt, sample a group of $G$ completions, score each, then normalize *within that group only*:
$$\boxed{A_i = \frac{r_i - \text{mean}(r_1,\dots,r_G)}{\text{std}(r_1,\dots,r_G)}}$$

**Why this replaces PPO's value network:** instead of *training* a baseline (PPO's $V_\phi(s)$), GRPO gets a baseline "for free" from the group's own average — trading the cost/instability of a critic for the cost of sampling $G$ completions per prompt.

🟩 **Worked example:** Group A (easy prompt) rewards $(1,1,-1,1)$ → mean $0.5$, std $0.866$ → advantages $(0.577, 0.577, -1.732, 0.577)$. Group B (hard prompt) rewards $(-1,-1,-1,1)$ → mean $-0.5$, std $0.866$ → advantages $(-0.577,-0.577,-0.577,1.732)$.

**Key point:** identical raw reward ($+1$) gets a *much larger* advantage when it's a rare success (Group B, $+1.732$) than when success is common (Group A, $+0.577$). Absolute reward alone doesn't capture this — group-relative advantage does.

---

## 8. RLHF Credit Assignment (🟩 — not present in your two images)

🟩 The `.md`'s source describes an LLM/RLHF loop diagram: generate content (action $a$) → receive a feedback/reward signal $S_L$ → policy $\pi_t$ updates the LLM → repeat, with an explicit flagged problem: *"how do we assign intermediate weight updates, as we cannot get the output at intermediate steps."*

This is the general RL **credit-assignment problem**, specialized to text: the "action" is really a whole sequence of token-level decisions, but only the *final* sequence gets a reward. PPO solves it with a learned per-token value baseline; GRPO solves it with a per-prompt group baseline instead — same problem, two different baselines. **Gap:** your images don't include this specific diagram — if it appears on the exam, it's sourced entirely from the `.md`'s underlying notes, not yours.

---

## 9. Cross-Source Map

| Topic | Your images (🟦) | `.md` only (🟩) |
|---|:---:|:---:|
| Actor–environment loop diagram, $a_t/s_t/r_t$ legend | ✅ | tuple form only |
| MDP formalism, Markov property, $\varepsilon$-greedy | — | ✅ |
| "Value ≈ closeness to goal state" | ✅ | numeric worked example |
| Vacuum robot / chess-stalling examples | — | ✅ |
| "Narrow value func → loopholes; constrained = lossy" | ✅ | — |
| Guardrails quote, lottery/vNM device | — | ✅ |
| "RF transfers human sensibilities" | ✅ | — |
| Regularization / KL-style guardrail | ✅ | — |
| Policy gradient, advantage formula | — | ✅ |
| PPO naming + clipped objective | ✅ (as "PPL") | ✅ (formal) |
| GRPO: rollouts, chains, group-relative advantage | ✅ | ✅ formula + numbers |
| RLHF loop diagram / credit assignment | — | ✅ |

---

## 10. Gaps, Ambiguities, Inconsistencies — Full List

1. **Provenance mismatch** (⚠️, see §0) — two same-dated, partly non-overlapping note sets.
2. **Naming slips to memorize correctly:** "Proximal Policy *Learning*" → **Optimization**; "Group *Related*" → **Relative**.
3. **"PPL trains a separate smaller LLM to evaluate the output"** conflates the (frozen, pre-trained) reward model with the (jointly trained) value critic — notes don't distinguish them.
4. **"RF" is used ambiguously** — probably "Reinforcement Fine-tuning" in one place, spelled-out "Reward func." elsewhere in the same page.
5. **"Exploration calibrates the reward system"** — imprecise; it calibrates the agent's *value estimate*, not the (fixed) reward function.
6. **"Closeness to goal state"** is accurate for the episodic, single-terminal-bonus examples both sources use, but isn't the fully general definition of $V^\pi(s)$.
7. The chess-stalling vignette's conclusion is a reconstructed inference (the source note cuts off mid-sentence) — not a verified instructor quote.
8. **No stochastic/branching MDP example** appears in either source — both worked examples are deterministic chains. If the exam gives multiple actions or probabilistic transitions, you must apply the general Bellman sum $\sum_{s'}P(s'\mid s,a)[\cdot]$, not pure back-substitution.
9. **GRPO edge case, not addressed by either source (🟨 added insight):** if every completion in a group gets the *same* reward, std $=0$ and the advantage formula divides by zero — a real, known practical wrinkle in GRPO implementations (typically handled with a small epsilon or by skipping degenerate groups).

---

## 11. Exam Prep

### A. Short Conceptual
**A1.** In the actor–environment loop, which quantity flows actor→environment, and which two flow environment→actor?
**A2.** Why can pure exploitation get permanently stuck?
**A3.** What does a negative reward represent in your legend?
**A4.** What does "group relative" mean in GRPO, in one sentence?
**A5.** What is a "rollout" in your notes' GRPO vocabulary?

### B. Definition / Knowledge
**B1.** State the Bellman equation for $V^\pi(s)$, in words and formula.
**B2.** Define reward hacking / specification gaming.
**B3.** What is the vNM lottery device used to elicit?
**B4.** Write the PPO clipped surrogate objective and define every symbol.
**B5.** Write the GRPO advantage formula and state how its baseline differs from PPO's.

### C. Why / How
**C1.** Why does "designing a constrained value function" necessarily involve a loss, per your class note? Connect to §4.
**C2.** Why is credit assignment structurally harder to observe in RLHF than in a short episodic MDP, even though it's "the same problem"?
**C3.** How does GRPO avoid needing PPO's learned value function, and what does it trade away for that?
**C4.** Why are RLHF reward models trained on pairwise comparisons instead of raw numeric ratings?
**C5.** Why might a KL-style regularization term be necessary even after the reward model was carefully trained on real human preferences?

### D. Scenario-Based
**D1.** A cleaning robot is rewarded "+1 per second the room reads as clean" on its own sensor. Give **two** distinct ways it could game this (one from the class discussion, one novel), and one guardrail for each.
**D2.** A chess agent (rewards +1 win / −1 loss / 0 else, $\gamma=0.99$) reaches a position it's guaranteed to lose in 3 moves. Using the stalling vignette, explain the degenerate behavior it might exhibit and why it's *rational*, not buggy, given only the stated reward.
**D3.** For a GRPO group of 4, one prompt is "easy" and produces 3 correct / 1 wrong; a second, harder prompt also produces exactly 1 correct out of 4. Does the lone correct completion get the same advantage in both cases? Why or why not?

### E. Numerical / Analytical
**E1.** Deterministic chain $1\to2\to3$ (terminal), $\gamma=0.9$, $R(1{\to}2)=-2$, $R(2{\to}3)=+8$. Compute $V(1), V(2), V(3)$.
**E2.** GRPO group, $G=3$, rewards $(4, 6, 2)$. Compute mean, std, and each completion's advantage.
**E3.** PPO, $\epsilon=0.2$, $A_t=+0.4$, $r_t(\theta)=1.25$. Compute the raw term, clipped term, and $L^{\text{CLIP}}_t$. Does clipping bind?
**E4. [Tricky]** PPO, $\epsilon=0.2$, $A_t=+0.5$ (good action), $r_t(\theta)=0.7$ (ratio *dropped* below 1 despite positive advantage). Compute both terms and $L^{\text{CLIP}}_t$. Does clipping actually restrain this update? Why or why not?

### F. Tricky / Difficult
**F1.** True or false, with justification: *"An agent that reward-hacks has a bug in its learning algorithm."*
**F2.** True or false: *"PPO and GRPO solve completely different problems."*
**F3. [Edge case]** In a GRPO group where every completion gets an identical reward, what breaks in the advantage formula, and what does that imply about when GRPO's signal is uninformative?
**F4.** Distinguish the reward model from the value-function critic in a PPO-based RLHF pipeline: which is trained first and frozen, and which is trained jointly with the policy?
**F5. [Synthesis]** In one paragraph, connect: (a) "narrow value functions invite loopholes," (b) regularization/KL against a reference policy, and (c) PPO's own clipping mechanism. Argue that all three are the *same* underlying tension — optimization power traded for safety/stability — showing up at three different points in this lecture.

---

### Answer Key

**A1.** $a_t$ flows actor→environment; $s_t$ and $r_t$ flow environment→actor.
**A2.** It never tries untested actions, so it can't discover a better policy than the one it already believes is best.
**A3.** Punishment.
**A4.** Each completion's advantage is computed only against its own group's mean/spread, never against other prompts' groups.
**A5.** One sampled completion/output from the current policy for a given prompt.

**B1.** $V^\pi(s) = \sum_a\pi(a|s)\sum_{s'}P(s'|s,a)[R(s,a,s')+\gamma V^\pi(s')]$ — value = immediate reward + discounted value of the next state, averaged over the policy and transition dynamics.
**B2.** Maximizing the literal specified reward in a way that technically satisfies it but violates the designer's actual intent; the failure is in the specification, not the agent.
**B3.** A numeric utility scale for a person's preferences, from indifference points in gambles, without ever asking for a raw number directly.
**B4.** $L^{\text{CLIP}}=\mathbb{E}_t[\min(r_tA_t, \text{clip}(r_t,1-\epsilon,1+\epsilon)A_t)]$; $r_t$=new/old policy probability ratio for the taken action, $A_t$=advantage, $\epsilon$=clip range.
**B5.** $A_i=(r_i-\text{mean})/\text{std}$ over the sampled group; PPO's baseline is a *learned* value function, GRPO's is the *group's own sample mean* — no separate network needed.

**C1.** Closing a loophole means adding a constraint the value function must respect, which removes some flexibility the unconstrained function had — you can't fully eliminate exploitability without giving something up.
**C2.** In RLHF the reward for a generation is only available once the *entire* sequence is done — many token-level decisions, one delayed signal — mirroring classical delayed-terminal-reward RL exactly, just with tokens instead of physical actions.
**C3.** It samples $G$ completions per prompt and uses their own mean/std as the baseline instead of training $V_\phi(s)$; trade-off: no critic-training cost/instability, but $G\times$ more samples needed per prompt.
**C4.** Humans are much more consistent comparing two options than assigning a stable absolute score to one in isolation.
**C5.** The reward model is only a learned *approximation* of preferences — without a penalty for drifting too far from a trusted reference policy, the policy can find quirks the RM over-rewards (reward hacking on the RM itself).

**D1.** Class example: dirty-then-clean cycling. Novel: spoof the sensor itself (cover dirt, or point sensor at a clean patch) without actually cleaning. Guardrails: reward *verified reduction in total dirt*, capped at "already clean" (removes incentive to re-dirty); independent audit sensor the robot can't manipulate.
**D2.** It may effectively "refuse to move" or stall, since the reward structure it's optimizing doesn't force it to engage productively with an unavoidable loss — rational given the literal objective, not a malfunction.
**D3.** No — same raw reward (+1) yields a larger advantage in the harder group, since success there is rarer relative to that group's own mean; identical absolute reward, different group-relative advantage.

**E1.** $V(3)=0$; $V(2)=8+0.9(0)=8.0$; $V(1)=-2+0.9(8.0)=5.2$.
**E2.** mean $=4$, std $=\sqrt{8/3}=1.633$; advantages: $(0-\text{for }r{=}4)$, $(2/1.633{=}1.225\text{ for }r{=}6)$, $(-2/1.633{=}-1.225\text{ for }r{=}2)$.
**E3.** Raw $=1.25\times0.4=0.5$; clip$(1.25)=1.2$ (exceeds $1+\epsilon$), clipped term $=1.2\times0.4=0.48$; $L^{\text{CLIP}}=\min(0.5,0.48)=0.48$ — clipping binds, capping the gain.
**E4.** Raw $=0.7\times0.5=0.35$; clip$(0.7)=0.8$ (below $1-\epsilon$), clipped term $=0.8\times0.5=0.4$; $L^{\text{CLIP}}=\min(0.35,0.4)=0.35$ — the **raw** term is chosen, so clipping doesn't actually restrain this update. For positive advantage, clipping only bites when the ratio rises *too far above* $1+\epsilon$ (over-eager increase), not when it falls below $1-\epsilon$.

**F1.** False — it's correctly optimizing exactly what it was told to optimize; the bug (if any) is in the reward *specification*, not the learning algorithm.
**F2.** False/imprecise — both address the same credit-assignment problem; PPO via a learned value baseline, GRPO via a sampled-group baseline.
**F3.** mean = that shared reward, std $=0$ → the advantage formula divides by zero (undefined); implies GRPO's signal is uninformative when a group is uniformly easy or uniformly hard — it only produces gradient signal when a group has *some* variation in outcomes.
**F4.** Reward model: trained first, on human pairwise preference data, then frozen during PPO. Value critic: trained jointly with the policy during PPO itself, estimating expected return at each intermediate step.
**F5.** All three enforce "stay close to something safe" at the cost of raw optimization power: a narrow reward/value function that's tightly constrained resists loopholes but loses expressiveness (§4); a KL penalty against a reference policy keeps the model from over-exploiting its own (imperfect) reward model, at the cost of how far it can move toward the RM's preferences (§5); PPO's clip keeps each policy update "proximal" to the old policy, at the cost of not fully capturing what a large, possibly-correct advantage estimate suggests (§6). Same trade-off — safety/stability vs. optimization headroom — recurring at the reward-design level, the training-objective level, and the per-update level.
