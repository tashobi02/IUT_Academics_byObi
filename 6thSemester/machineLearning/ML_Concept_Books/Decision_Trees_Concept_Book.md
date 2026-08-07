# 🧠 Decision Trees
### CSE 4621 · Islamic University of Technology · Companion to Lecture 10

> **What this book is.** A self-contained companion to **Lecture 10: Decision Trees** (15 slides, lecturer Ishmam Tashdeed). Unlike Lecture 9's slides, this deck's text layer is not cipher-encoded — it extracts cleanly — but it is still terse: definitions and formulas are stated without derivation, and the deck's own outline promises two topics (**Gini Impurity**, **Regression Trees**) that never actually appear in the slide content. This book supplies everything the slides assume you'll pick up elsewhere: derivations, a fully hand-verified worked example (the classic "Play Golf" dataset), and self-contained treatment of both missing topics.

---

## How to use this book

Same rhythm as your other concept books:

1. **📐 Formal Definition**
2. **🗣️ Layman's Explanation**
3. **🎯 Why This Concept Exists**
4. **🧠 Intuition**
5. **🧮 Mathematical Explanation**
6. **🧪 Worked Numerical Example**
7. **🌍 Practical Example**
8. **⚠️ Common Misconceptions**
9. **🎓 Exam Tips**

Callouts:

> [!info] **Why this matters**

> [!tip] **Memory trick**

> [!warning] **Exam trap**

> [!danger] **Slide gap / discrepancy** — content promised by the outline but missing, or a slide detail that needs a careful second look.

> [!example] **Worked example**

---

## 📚 Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Learning Objectives](#2-learning-objectives)
3. [Core Concepts](#3-core-concepts)
   - [3.1 What Is a Decision Tree](#31-what-is-a-decision-tree)
   - [3.2 How a Decision Tree Makes a Prediction](#32-how-a-decision-tree-makes-a-prediction)
   - [3.3 The Test Function & Decision Regions](#33-the-test-function--decision-regions)
   - [3.4 Univariate Trees](#34-univariate-trees)
   - [3.5 Impurity Measures — The General Framework](#35-impurity-measures--the-general-framework)
   - [3.6 Entropy as an Impurity Measure](#36-entropy-as-an-impurity-measure)
   - [3.7 Gini Impurity — the syllabus gap, filled in](#37-gini-impurity--the-syllabus-gap-filled-in)
   - [3.8 Split and Sub-Tree Generation](#38-split-and-sub-tree-generation)
   - [3.9 Information Gain](#39-information-gain)
   - [3.10 Regression Trees — the other syllabus gap, filled in](#310-regression-trees--the-other-syllabus-gap-filled-in)
   - [3.11 Stopping Criteria, Pruning & Overfitting](#311-stopping-criteria-pruning--overfitting)
4. [Mathematical Foundations Deep Dive](#4-mathematical-foundations-deep-dive)
5. [Architecture & Diagram Explanations](#5-architecture--diagram-explanations)
6. [Worked Examples](#6-worked-examples)
7. [Concept Connections — The Big Picture](#7-concept-connections--the-big-picture)
8. [Exam Preparation](#8-exam-preparation)
9. [Practice Questions with Full Solutions](#9-practice-questions-with-full-solutions)
10. [References](#10-references)

---

# 1. Executive Summary

Decision trees answer a deceptively simple question: **can you build an accurate predictor purely out of a sequence of yes/no questions?** The lecture builds this idea up in four stages:

1. **Structure.** A decision tree is a hierarchical, **non-parametric** data structure — internal nodes ask a question (a *test function*), branches are the possible answers, and leaves hold the final prediction. Nothing here is a weight vector or a fixed functional form (contrast with linear/logistic regression) — the tree's shape and the questions it asks are themselves learned from data.
2. **The question of *which* question to ask.** At any node, many candidate questions ("is Outlook = Sunny?", "is Humidity > 75%?") could be asked. The lecture needs a way to score how *good* a candidate split is — this is the **impurity measure**: a function that is $0$ when a split perfectly separates the classes and maximal when it doesn't separate them at all.
3. **A specific impurity measure: entropy.** Borrowed directly from information theory, entropy scores how "mixed" a set of labels is. The tree-building algorithm (ID3-style) computes entropy before and after each candidate split, and the *reduction* in entropy — the **information gain** — is what decides which question gets asked at each node.
4. **Recursion.** The winning split is applied, the data is partitioned into child nodes, and the entire procedure — compute impurity, try every candidate split, pick the best, recurse — repeats on each child until nodes are pure (or some stopping rule fires).

The lecture demonstrates this concretely with the classic **"Play Golf"** weather dataset (14 days, 4 categorical features, a Yes/No label) — computing the entropy of every candidate first split (Outlook, Temperature, Humidity, Windy) and showing that **Outlook** wins by information gain, which is exactly the split ID3 would choose.

Two topics are named in the lecture's own outline — **Gini Impurity** and **Regression Trees** — but never actually appear in the 15 slides. Both are supplied in full here (Sections 3.7 and 3.10), since they are natural, high-probability exam topics for this lecture whether or not the slides delivered them.

> [!info] **Why this matters**
> The one-sentence version of this whole lecture: *"Score every possible question by how much it reduces label-impurity, greedily ask the best one, and repeat on each resulting subset until you're done."* Nearly every exam question on this topic is testing some piece of that sentence.

---

# 2. Learning Objectives

By the end of this chapter you should be able to:

1. Define a decision tree precisely (hierarchical, divide-and-conquer, non-parametric, composed of internal decision nodes and terminal leaves) and explain what "non-parametric" means in this context, contrasting it with linear/logistic regression.
2. Explain how a trained tree makes a prediction on a new input, tracing the path from root to leaf via the test function $f_m(x)$ at each internal node.
3. State and use the general impurity-measure framework $\phi(p, 1-p)$, and explain why it must be $0$ at $p\in\{0,1\}$ and maximal at $p=0.5$.
4. Write the entropy formula (binary and $K$-class) from memory, compute it by hand for a given class split, and explain its information-theoretic meaning (expected number of bits).
5. Compute Gini impurity by hand and explain how it compares to entropy (shape, computational cost, typical use in CART vs. ID3/C4.5).
6. Compute the information gain of a candidate split by hand, from a raw dataset, for a categorical feature with multiple values (as in the worked "Play Golf" example).
7. Explain the greedy, recursive nature of standard decision-tree induction, and why this greediness is a deliberate trade-off (a globally optimal tree is computationally intractable to find exactly).
8. State the regression-tree analogue of information gain (variance/SSE reduction) and explain why classification's entropy/Gini doesn't directly apply to a continuous target.
9. Explain why decision trees are prone to overfitting, and connect this to the course's general bias-variance/regularization framework (Lecture 4).
10. Place decision trees within the broader course narrative: non-parametric vs. parametric methods, and as the direct foundation for ensemble methods (bagging, random forests, boosting) that extend this lecture's material.

---

# 3. Core Concepts

## 3.1 What Is a Decision Tree

**Slide reference:** Lecture 10, p. 3.

### 📐 Formal Definition
A **decision tree** is a hierarchical data structure implementing the **divide-and-conquer** approach to prediction. It is a **non-parametric method**, usable for both **classification** and **regression**, composed of **internal decision nodes** and **terminal leaves** — equivalently, a combination of multiple nested `if`-`else` statements.

### 🗣️ Layman's Explanation
A decision tree is a flowchart. Start at the top, answer a question about your input, follow the branch matching your answer, hit another question, and so on, until you land on a box with no more questions — that box is the prediction.

### 🎯 Why This Concept Exists
Linear and logistic regression (Lectures 3 and 5) commit to a **fixed functional form** up front ($\theta^\top x$, or $\sigma(\theta^\top x)$) — the *shape* of the decision boundary is decided before training even starts (a hyperplane), and training only fits the coefficients within that fixed shape. A decision tree makes no such commitment: the **structure itself** — how many splits, on which features, in what order — is learned from data. This is what "non-parametric" means here: not "no parameters at all," but **the number and form of the parameters is not fixed in advance** — it grows and adapts to the data (contrast with a fixed-length parameter vector $\theta$).

### 🧠 Intuition — reading the diagram (Slide 3)
The slide's example: classify an animal using the questions *"Has feathers?"* → *"Can fly?"* / *"Has finns?"*:

```
                    Has feathers?
                   /              \
                True              False
                 /                    \
            Can fly?              Has finns?
           /        \             /         \
        True       False       True         False
         |            |          |             |
       Hawk        Penguin    Dolphin         Bear
```

Every internal node is a yes/no question about the input; every leaf is a final class label. Note that this is literally *"a combination of multiple if-else statements"* — you could write this exact tree as nested Python `if`/`elif`/`else` blocks with no loss of information.

### 🌍 Practical Example
Decision trees are widely used exactly where their *interpretability* matters — credit approval, medical triage, regulatory/compliance settings — because, unlike a neural network's weights, a decision tree's decision path for any single prediction can be read off and explained in plain language ("declined because income < \$X and existing debt > \$Y").

### ⚠️ Common Misconceptions
- **"Non-parametric means the model has no parameters."** It has plenty of "parameters" in an informal sense (which feature to split on and at what threshold, at every node) — what makes it non-parametric is that the **number** of these decisions is not fixed ahead of time; it is determined by the data and the tree's growth process, unlike, say, a logistic regression model, which always has exactly $d+1$ parameters no matter how much data you feed it.
- **"A decision tree can only do classification."** The slide explicitly states it can be used for **both classification and regression** (Section 3.10 covers the regression case).

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Decision tree = **divide** (split the data) **and conquer** (recurse on each piece) — the exact same algorithmic pattern as merge sort or quicksort, just applied to a labeling problem instead of an ordering problem.

---

## 3.2 How a Decision Tree Makes a Prediction

**Slide reference:** Lecture 10, p. 4.

### 📐 Formal Definition
Given an input $x$, at each node the tree applies a **test function** and follows the branch matching the outcome, repeating recursively until a **leaf node** is reached; the leaf's stored label (or value) is returned as the prediction. Each decision node $m$ implements a test function $f_m(x)$ with **discrete outcomes** labeling its outgoing branches.

### 🗣️ Layman's Explanation
Feed your input into the root question. Whatever the answer, follow that branch to the next question. Keep going until there are no more questions — that's your answer.

### 🎯 Why This Concept Exists
This is simply the formal statement of "how do you actually use a trained tree" — the previous section defined the *structure*; this section defines the *inference procedure* that walks that structure.

### 🧠 Intuition — reading the diagram (Slide 4)
The slide pairs a 2D scatter plot (features $x_1, x_2$; classes $C_1, C_2$) with its equivalent decision tree:

```
         x1 > w10?
        /          \
      Yes            No
      /                \
 x2 > w20?             C1
  /      \
Yes      No
 |        |
 C2      C1
```

The scatter plot shows the **axis-aligned decision boundary** this tree carves out: a vertical line at $x_1=w_{10}$ splits the plane into "$x_1 \le w_{10}$" (immediately labeled $C_1$, no further questions needed) and "$x_1 > w_{10}$" (which needs a **second** question, a horizontal line at $x_2=w_{20}$, to fully separate $C_1$ from $C_2$). This is the clearest possible illustration of two ideas at once: (1) a tree's decision regions are unions of **axis-aligned rectangles** — a direct geometric consequence of univariate splits (Section 3.4); (2) different branches of the same tree can have **different depths** — the "No" branch from the root needed zero further questions, the "Yes" branch needed one more.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> Do not describe tree inference as "the input is compared against every leaf." Only **one path** from root to leaf is ever traversed for any given input — at each internal node, exactly one of the possible branches is taken, so a tree with $L$ leaves requires only $O(\text{depth})$ test evaluations per prediction, not $O(L)$.

---

## 3.3 The Test Function & Decision Regions

**Slide reference:** Lecture 10, p. 5.

### 📐 Formal Definition
Each test function $f_m(x)$ defines a **discriminant** in the $d$-dimensional feature space, dividing it into smaller subsets. Different tree families use different test-function models (e.g., axis-aligned thresholds vs. linear combinations of features), producing different shapes of decision boundary. Hierarchical decisions can locate a region efficiently: **$\log(B)$ decisions in the best, balanced case**, where $B$ is the number of regions (leaves).

### 🗣️ Layman's Explanation
Every question you ask cuts the space of possible inputs into pieces. A well-designed sequence of questions — like a well-designed game of "20 Questions" — can narrow down to one specific region very quickly, *if* each question is chosen to split the remaining possibilities roughly in half.

### 🎯 Why This Concept Exists
This is the theoretical justification for why trees can be efficient: it directly imports the complexity argument behind **binary search**. If a tree is perfectly balanced, each internal node halves the number of remaining candidate regions, so reaching any one of $B$ leaf regions takes only $\log_2(B)$ decisions — logarithmic, not linear, in the number of regions.

### 🧮 Mathematical Explanation
This is the same complexity argument used for balanced binary search trees and binary search over a sorted array: with $B$ leaves and a perfectly balanced binary tree, the depth is $\lceil \log_2 B \rceil$. The qualifier **"in the best balanced case"** is doing real work here — an unbalanced tree (e.g., one that always splits off a single example at a time, like an unbalanced BST built from already-sorted input) degrades toward $O(B)$ depth in the worst case. This is precisely why tree-building algorithms care about choosing splits that meaningfully divide the data (Section 3.8), rather than splits that peel off one point at a time.

### 🌍 Practical Example
This complexity argument is why decision trees scale well to large datasets at **prediction** time (each prediction is cheap, $O(\text{depth})$) even though **building** the tree (choosing all the splits) is the computationally expensive part, done once, up front.

### ⚠️ Common Misconceptions
- **"Every test function only compares one feature to a threshold."** That specific restriction is what defines a **univariate** tree (Section 3.4) — the general definition here only requires $f_m(x)$ to be *some* discriminant function of $x$; a **multivariate** (or "oblique") tree's test function can combine several features at once (e.g., $w^\top x > c$ for a learned weight vector $w$, producing diagonal rather than axis-aligned splits).

### 🎓 Exam Tips
> [!tip] **Memory trick**
> $\log(B)$ decisions for $B$ regions is exactly the "20 Questions" guarantee: with well-chosen yes/no questions, you can distinguish among $2^{20}\approx10^6$ possibilities in only 20 questions.

---

## 3.4 Univariate Trees

**Slide reference:** Lecture 10, p. 6.

### 📐 Formal Definition
In a **univariate tree**, each internal node's test function uses **only one** of the input features (attributes) — e.g., "is Humidity $>75\%$?" — never a combination of several features at once.

### 🗣️ Layman's Explanation
Every question the tree asks is about exactly one column of your data table — never "is (feature A plus twice feature B) greater than some number," only ever "is feature A [above/below/equal to] some value?"

### 🎯 Why This Concept Exists
Univariate splits are the default in the most widely taught tree algorithms (ID3, C4.5, CART) because they are cheap to search over (for each feature, only a handful of candidate thresholds need to be tried) and because the resulting tree is maximally interpretable — a single condition per node reads naturally as an English sentence.

### 🧠 Intuition — reading the diagram (Slide 6)
The slide gives a 10-day toy weather dataset (Day, Weather, Temperature, Humidity, Wind, Play?) and shows **two equivalent trees** built from it, differing only in how the same underlying splits are described:

**Tree A (categorical thresholds):**
```
                        Weather
              /            |            \
          Sunny          Cloudy         Rainy
            |               |              |
        Humidity           Yes           Wind
        /      \                        /     \
      High    Normal                 Strong   Weak
       |         |                      |        |
       No       Yes                    No       Yes
```
**Tree B (numeric thresholds — same tree, different attribute encoding):**
```
                        Weather
              /            |            \
          Sunny          Cloudy         Rainy
            |               |              |
        Humidity           Yes            Wind
       /        \                        /      \
    >75%       <=75%                   >20      <=20
      |           |                      |         |
      No          Yes                    No        Yes
```
These two diagrams make one subtle but important point: **the same logical split can be described either as a categorical comparison ("High" vs. "Normal") or as a numeric threshold comparison ($>75\%$ vs. $\le75\%$)** — the underlying partitioning of the data is identical either way; only the *representation* of the humidity feature differs (categorical bucket vs. raw percentage). Root: split on **Weather** (three-way branch: Sunny / Cloudy / Rainy); the Cloudy branch is already pure (always "Yes," no further split needed), while Sunny and Rainy each need one more question (Humidity, Wind respectively) to reach a pure leaf.

### 🧪 Worked Numerical Example
See [Worked Example 4](#worked-example-4--building-the-univariate-tree-from-scratch) for the full entropy/gain computation that justifies *why* Weather is chosen as the root split for this exact dataset.

### ⚠️ Common Misconceptions
- **"Univariate splits can only handle categorical features."** Both branches of the slide's own diagram show the *same* tree, one using categorical buckets, one using a numeric threshold — univariate splits work identically well for continuous features (pick a threshold $c$ and test $x_i > c$) and categorical ones (pick a value or subset of values).

### 🎓 Exam Tips
> [!warning] **Exam trap**
> A tempting distractor: "univariate trees produce diagonal decision boundaries." **False** — univariate splits are always **axis-aligned** in feature space (each split is perpendicular to exactly one feature axis, as in Slide 4's rectangle-shaped regions); only **multivariate/oblique** trees (splits on a linear combination of features) can produce diagonal boundaries.

---

## 3.5 Impurity Measures — The General Framework

**Slide reference:** Lecture 10, p. 7.

### 📐 Formal Definition
In a classification tree, the **goodness of a split** is quantified by an **impurity measure**. The function $\phi(p, 1-p)$ is an impurity measure, where $p$ is the proportion of examples belonging to one class (in the binary case). A split is **pure** if every example in each resulting branch belongs to the same class; a split is **maximally impure** if it contains a 50/50 mixture.

### 🗣️ Layman's Explanation
After you ask a question and the data splits into groups, how "mixed up" is each group? If everyone in a group has the same label, that group is perfectly sorted (pure, impurity $=0$). If a group is a coin-flip mix of both labels, that's as mixed up as it gets (maximally impure).

### 🎯 Why This Concept Exists
The whole tree-building algorithm is "try lots of candidate questions, keep the one that helps most" — but "helps most" needs a **number** to compare across candidates, and that number is impurity (or, equivalently, its reduction — information gain, Section 3.9). Without a quantitative impurity measure, there would be no principled way to prefer one candidate split over another.

### 🧠 Intuition
Slide 7's own one-line summary captures the required shape exactly: *"Impurity rises as the classes become more balanced, then falls again."* Any valid impurity function $\phi(p,1-p)$ must satisfy:
1. $\phi(0,1) = \phi(1,0) = 0$ (pure nodes have zero impurity, regardless of *which* class is the pure one),
2. $\phi(p,1-p)$ is **maximized** at $p=0.5$ (maximally mixed),
3. $\phi$ is symmetric: $\phi(p,1-p)=\phi(1-p,p)$ (swapping which class is "positive" doesn't change how mixed the group is).

Both entropy (Section 3.6) and Gini impurity (Section 3.7) satisfy all three properties — they are two different specific functions built to this same general template.

### 🌍 Practical Example
This "rises then falls, symmetric, zero at the extremes" shape is exactly the shape of a variance-like statistic — and in fact, both entropy and Gini impurity can be understood as different ways of measuring the "spread"/uncertainty of a categorical (Bernoulli/categorical) distribution, in the same spirit that variance measures the spread of a continuous distribution.

### ⚠️ Common Misconceptions
- **"Any function that's 0 at the extremes counts as a valid impurity measure."** It must also be maximized at $p=0.5$ and symmetric — a function like $\phi(p)=p(1-p)^2$ is zero at $p\in\{0,1\}$ but is **not** symmetric and does **not** peak at $p=0.5$, so it would not be an acceptable impurity measure under this framework (in fact, this specific example is not even valid, since $\phi(p, 1-p)$ must depend on $p$ and $1-p$ symmetrically by definition).

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Impurity is a "how mixed is the fruit basket" measure: an all-apples basket (pure) or an all-oranges basket (pure) scores 0; a half-apples-half-oranges basket scores the maximum.


---

## 3.6 Entropy as an Impurity Measure

**Slide reference:** Lecture 10, p. 8.

### 📐 Formal Definition
The lecture's chosen impurity measure is **entropy**, borrowed from information theory:
$$\phi(p, 1-p) = -p\log(p) - (1-p)\log(1-p)$$
Generalized to $K$ classes at tree node $m$:
$$I_m = -\sum_{i=1}^{K} p_m^i \log(p_m^i)$$
where:

| Symbol | Meaning |
|---|---|
| $m$ | the current tree node |
| $K$ | number of classes |
| $p_m^i$ | proportion of the samples in node $m$ that belong to class $i$ |
| $I_m$ | entropy of node $m$ |

(Logarithms are conventionally base 2, giving entropy in **bits** — see Section 4.2.)

### 🗣️ Layman's Explanation
Entropy answers: *"If I had to describe which class a random example from this node belongs to, how many yes/no questions would I expect to need, on average?"* A pure node needs zero questions (you already know the answer). A perfectly 50/50 node needs exactly one question on average.

### 🎯 Why This Concept Exists
Entropy is not an arbitrary choice — it is *the* quantity information theory derives as the unique (up to a multiplicative constant) measure of "average surprise"/uncertainty in a distribution, making it a theoretically well-motivated choice for "how mixed is this set of labels," not merely a convenient one.

### 🧠 Intuition — reading the graph (Slide 8)
The slide's plot of $\phi(p,1-p) = -p\log_2 p - (1-p)\log_2(1-p)$ against $p\in[0,1]$ is a symmetric curve, $0$ at both $p=0$ and $p=1$, peaking at exactly $1$ when $p=0.5$ — a direct visual confirmation of Section 3.5's three required properties. See Section 4.2 for the calculus proof that the peak sits at exactly $p=0.5$ with value exactly $1$.

### 🧪 Worked Numerical Example
For the "Play Golf" dataset's root node (9 Yes, 5 No, out of 14): $p_{\text{Yes}}=9/14\approx0.643$, $p_{\text{No}}=5/14\approx0.357$.
$$I = -(0.643)\log_2(0.643) - (0.357)\log_2(0.357) \approx 0.4098 + 0.5306 \approx 0.940$$
matching the slide's own value $E(\text{PlayGolf})=E(5,9)=0.94$ exactly (verified independently in Section 6). Contrast with a pure node (say, 4 Yes, 0 No): $p_{\text{Yes}}=1$, $p_{\text{No}}=0$, and $I = -(1)\log_2(1) - (0)\log_2(0) = -(1)(0) - 0 = 0$ (using the standard convention $0\log_2 0 \triangleq 0$, justified by the limit $\lim_{p\to0^+}p\log_2p=0$).

### 🌍 Practical Example
Entropy-based information gain (Section 3.9) is the splitting criterion used by the classic **ID3** and **C4.5** decision-tree algorithms (Quinlan).

### ⚠️ Common Misconceptions
- **"Entropy is always between 0 and 1."** For a **binary** class variable, entropy (base-2 log) is bounded in $[0,1]$. For $K>2$ classes, the maximum possible entropy is $\log_2(K)$ (attained at a uniform distribution over all $K$ classes) — e.g., with 4 equally likely classes, max entropy is $\log_2(4)=2$ bits, not 1.
- **Forgetting the convention $0\log_2 0 = 0$.** A literal calculator computation of $0 \times \log_2(0)$ is undefined ($\log_2(0)=-\infty$), but the *limit* of $p\log_2 p$ as $p\to0^+$ is $0$ — this convention must be applied whenever a class is entirely absent from a node (as in the "Overcast" branch of the worked example, Section 6).

### 🎓 Exam Tips
> [!warning] **Exam trap**
> A common error is writing the entropy formula with a **natural log** ($\ln$) instead of $\log_2$, then reporting a numeric answer that doesn't match the expected "bits" convention used throughout this lecture and the standard ID3 literature — always confirm which base is expected (this lecture and the worked example use $\log_2$ throughout).

---

## 3.7 Gini Impurity — the syllabus gap, filled in

**Slide reference:** Lecture 10, p. 2 lists *"Gini Impurity"* as an outline bullet — but **no slide anywhere in the 15-slide deck defines or discusses it.**

> [!danger] **Slide gap**
> The outline promises Gini Impurity; the deck never delivers it. This is exactly the kind of gap most likely to appear on an exam precisely *because* it was in the stated outline. Full self-contained treatment below.

### 📐 Formal Definition
For $K$ classes at node $m$, the **Gini impurity** is:
$$G_m = \sum_{i=1}^{K} p_m^i\big(1-p_m^i\big) = 1 - \sum_{i=1}^{K}\big(p_m^i\big)^2$$
For the binary case ($K=2$, proportions $p$ and $1-p$): $G = p(1-p)+(1-p)p = 2p(1-p)$.

### 🗣️ Layman's Explanation
Gini impurity asks: *"If I picked two random examples from this node (with replacement) and guessed each one's label according to the node's own class proportions, how often would I be wrong?"* — it is literally the probability of a mislabeling under this random-guessing scheme.

### 🎯 Why This Concept Exists
It is an alternative to entropy that avoids computing logarithms — cheaper to evaluate at scale — while satisfying the exact same three required properties from Section 3.5 (zero at purity, symmetric, maximized at $p=0.5$).

### 🧮 Mathematical Explanation
The two equivalent forms above are derived as follows: $\sum_i p_m^i(1-p_m^i) = \sum_i p_m^i - \sum_i (p_m^i)^2 = 1 - \sum_i(p_m^i)^2$, using $\sum_i p_m^i = 1$ (proportions sum to 1). For the binary case, at $p=0.5$: $G = 2(0.5)(0.5) = 0.5$ — note this is Gini's **maximum value for $K=2$**, numerically different from entropy's maximum of $1$ bit at the same point — the two measures agree on *where* the peak is (at $p=0.5$) but not on the peak's *height*, since they are different functions built to the same general template (Section 3.5).

### 🧪 Worked Numerical Example
For the "Play Golf" root node ($p_{\text{Yes}}=9/14$, $p_{\text{No}}=5/14$):
$$G = 2\times\frac{9}{14}\times\frac{5}{14} = 2\times\frac{45}{196} = \frac{90}{196} \approx 0.459$$
Compare to this same node's entropy, $0.940$ (Section 3.6) — both measures agree this node is highly impure (close to their respective maxima), even though the two numbers are on different scales and should never be directly compared to each other across different measures.

### 🌍 Practical Example
Gini impurity is the default splitting criterion in **CART** (Classification and Regression Trees, Breiman et al.) and is scikit-learn's default `criterion` for `DecisionTreeClassifier` — largely for the computational reason above (no logarithms needed).

### ⚠️ Common Misconceptions
- **"Gini and entropy always pick the same split as 'best.'"** They usually agree, but not always — because their curves have different shapes (entropy is "more peaked" near $p=0.5$ on a relative basis for extreme splits), the two criteria can occasionally rank two competing candidate splits in a different order, particularly when comparing splits that produce very different node sizes.
- **"Gini impurity's maximum value is 1, same as entropy."** For $K=2$ classes, Gini's maximum is $0.5$, not $1$ — do not assume the two measures share a numeric scale.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Gini = "probability of a random mislabeling." Entropy = "expected number of yes/no questions." Same job (measure impurity), different metaphor, different formula, different numeric scale.

---

## 3.8 Split and Sub-Tree Generation

**Slide reference:** Lecture 10, p. 9.

### 📐 Formal Definition
If a node is not pure: evaluate every candidate attribute and split position; compute the impurity of the resulting child nodes for each candidate split; choose the split with the **minimum post-split impurity** (equivalently, the **largest impurity decrease**). This is a **greedy algorithm** — it locally chooses the most immediately optimal split at each node, with no lookahead to whether a different, locally-worse split might enable better splits further down the tree.

The **total impurity after a split** into $n$ child branches:
$$I'_m = \sum_{j=1}^{n} \frac{N_{mj}}{N_m}\, I_{mj}, \qquad I_{mj} = -\sum_{i=1}^{K} p_{mj}^i \log(p_{mj}^i)$$
where $N_{mj}$ is the number of samples in child branch $j$, $N_m$ is the total number of samples at parent node $m$, and $p_{mj}^i$ is the proportion of class $i$ **within child branch $j$**.

> [!danger] **A notational subtlety worth flagging precisely**
> The compact version of this formula as typically abbreviated (and as it appears in a compressed form on the slide) writes the inner proportion simply as $p_m^i$ — but this must be read as shorthand for $p_{mj}^i$, the **class proportion within child branch $j$**, not the parent node $m$'s own overall class proportion. If you use the *parent's* proportions instead of each *child's own* proportions when computing $I'_m$, you get a meaningless number (indeed, you'd get the parent's own entropy $I_m$ regardless of the split, since $\sum_j N_{mj}/N_m=1$) — always recompute class proportions **fresh, within each child branch**, using only the examples that actually landed in that branch. The worked example in Section 6 makes this explicit at every step.

### 🗣️ Layman's Explanation
If your current group of examples isn't already sorted by label, try every reasonable yes/no question you could ask about it. For each candidate question, see how impure the two (or more) resulting sub-groups would be, weighted by how many examples land in each sub-group. Pick whichever question leaves you with the least total impurity. Do this again, separately, inside every sub-group that still isn't pure.

### 🎯 Why This Concept Exists
This is the actual **algorithm** — Sections 3.5–3.7 defined *what* impurity means; this section defines *how a tree is actually built* using that definition: a recursive, greedy search over candidate splits.

### 🧮 Mathematical Explanation — why weight by $N_{mj}/N_m$
A candidate split producing one large, moderately impure child and one tiny, perfectly pure child should not automatically be preferred over a split producing two medium-sized, moderately impure children — what matters is the impurity **averaged over where the data actually ends up**. Weighting each child's impurity by its share of the parent's examples ($N_{mj}/N_m$) is precisely the operation that produces this proper (sample-size-weighted) average, and is what makes $I'_m$ directly comparable, apples-to-apples, across candidate splits that partition the data into differently-sized groups.

### ⚠️ Common Misconceptions
- **"Greedy" means "wrong" or "a shortcut that should be avoided."** Greedy splitting is a deliberate, standard design choice, not a compromise made only due to laziness: finding the single globally optimal decision tree (over all possible sequences of splits) is an NP-hard combinatorial search problem; the greedy, one-split-at-a-time approach is what makes tree-building computationally tractable in practice, at the cost of only a *local* (not global) optimality guarantee.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> If asked to compute $I'_m$ for a specific candidate split, the single most common calculation error is plugging in the **parent node's** class proportions instead of recomputing proportions **separately for each child branch** — see the danger callout above, and double-check this specific step in your own working.

---

## 3.9 Information Gain

**Slide reference:** Lecture 10, p. 9.

### 📐 Formal Definition
$$\text{Gain}(S, T) = \text{Entropy}(S) - \text{Entropy}(S, T)$$
where $S$ is the current (parent) node's set of examples, $T$ is a candidate split (attribute/threshold), $\text{Entropy}(S)$ is the parent node's own entropy (Section 3.6), and $\text{Entropy}(S,T)$ is the **weighted post-split entropy** $I'_m$ from Section 3.8, computed using split $T$.

### 🗣️ Layman's Explanation
Information gain is simply: *"how much less mixed-up are things after I ask this question, compared to before?"* The bigger the drop in impurity, the more useful the question.

### 🎯 Why This Concept Exists
This is the actual **scoring function** used to compare candidate splits (Section 3.8's "choose the split with... the largest impurity decrease," made numerically precise): among all candidate attributes and thresholds, greedily pick whichever one **maximizes** $\text{Gain}(S,T)$.

### 🧮 Mathematical Explanation
Since $\text{Entropy}(S)$ is a fixed number (it doesn't depend on which candidate split $T$ you're evaluating), maximizing $\text{Gain}(S,T)$ over candidate splits $T$ is **exactly equivalent** to minimizing $\text{Entropy}(S,T) = I'_m$ over the same candidates — Sections 3.8 and 3.9 are two equivalent framings ("minimize post-split impurity" vs. "maximize impurity reduction") of the very same selection rule.

### 🧪 Worked Numerical Example
See [Worked Example 1](#worked-example-1--play-golf-choosing-the-root-split) for the complete, from-scratch information-gain computation for all four candidate attributes (Outlook, Temperature, Humidity, Windy) in the "Play Golf" dataset.

### 🌍 Practical Example
Because raw information gain is systematically **biased toward attributes with many distinct values** (an attribute like a unique row ID would trivially achieve maximum gain, perfectly separating every example into its own singleton, pure branch, while being useless for generalization), the C4.5 algorithm (Quinlan's successor to ID3) instead uses **Gain Ratio** — information gain divided by the "split information" (the entropy of the split itself, treating branch membership as the random variable) — specifically to correct for this bias. This refinement is beyond the current lecture's scope but is a natural, high-value follow-up fact (see Section 8.4).

### ⚠️ Common Misconceptions
- **"A higher-gain split is always better for the final model's generalization."** Information gain measures how well a split fits the **training data immediately in front of you** — an attribute like a unique ID column can achieve enormous information gain (each branch becomes a single, perfectly pure example) while being completely useless for predicting on new data. Gain must be interpreted alongside a generalization safeguard (Section 3.11), not maximized blindly.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Gain = "before" minus "after." If you ever get a **negative** gain, you've made an arithmetic error somewhere — entropy can only decrease or stay the same after a split, in expectation (this is a mathematical property of entropy called *concavity*), so a well-computed information gain is never negative.


---

## 3.10 Regression Trees — the other syllabus gap, filled in

**Slide reference:** Lecture 10, p. 2 lists *"Regression Trees"* as the outline's final bullet — but, like Gini Impurity, **no slide anywhere in the deck covers it**; slide 15 is "Thank you."

> [!danger] **Slide gap**
> A second outline promise with zero delivered content. Since regression trees are the natural, expected capstone of this lecture (the deck's own opening slide states a decision tree "can be used for both classification and regression"), treat this as a high-probability gap-fill exam topic.

### 📐 Formal Definition
A **regression tree** has exactly the same hierarchical, recursive-splitting structure as a classification tree, with two changes: (1) the label $y$ is now **continuous**, not categorical; (2) each leaf stores a **predicted numeric value** — conventionally, the **mean** of the training $y$-values that landed in that leaf — rather than a class label. The splitting criterion is no longer entropy/Gini (which require discrete classes) but the **reduction in variance / sum of squared errors (SSE)**.

For a node $m$ with examples $\{y_1,\dots,y_N\}$, define the node's impurity as its variance (equivalently, mean squared error against its own mean):
$$\text{Var}_m = \frac{1}{N}\sum_{k=1}^{N}(y_k - \bar y_m)^2, \qquad \bar y_m = \frac{1}{N}\sum_{k=1}^{N} y_k$$
A candidate split into children $m_1, m_2$ (analogous to Section 3.8's $I'_m$) is scored by the sample-size-weighted post-split variance:
$$\text{Var}'_m = \frac{N_{m_1}}{N_m}\text{Var}_{m_1} + \frac{N_{m_2}}{N_m}\text{Var}_{m_2}$$
and the tree greedily picks the split that **minimizes** $\text{Var}'_m$ (equivalently, maximizes the variance reduction $\text{Var}_m - \text{Var}'_m$ — the direct regression analogue of information gain).

### 🗣️ Layman's Explanation
Classification asks "which split makes each group as label-homogeneous as possible?" Regression asks the exact same question, just replacing "label-homogeneous" with "numerically tight-clustered around one average value." A leaf's prediction is simply "the average $y$ of everyone who ended up here."

### 🎯 Why This Concept Exists
Entropy and Gini are built specifically around a *categorical* probability distribution ($p_m^i$, the proportion belonging to class $i$) — they have no meaning for a continuous target (there is no "class" for a house price or a temperature reading). Variance/SSE is the natural continuous-target substitute: it is likewise $0$ when a group is perfectly "pure" (every $y$ value identical), and it grows as the group's $y$ values become more spread out — exactly the same qualitative shape required in Section 3.5, just measured on a continuous rather than categorical scale.

### 🧮 Mathematical Explanation
The connection to your earlier coursework is direct: minimizing within-leaf variance is *exactly* minimizing the **Mean Squared Error** loss (Lecture 3, Linear Regression) that a leaf's constant prediction $\bar y_m$ would incur on its own training examples — a regression tree's leaf value $\bar y_m$ is literally the value that minimizes $\sum_k (y_k - c)^2$ over choices of constant $c$ (achieved at $c=\bar y_m$, the sample mean — a standard calculus result: differentiate w.r.t. $c$, set to 0). So a regression tree can be understood as fitting a great many tiny "regression models" — each one just a constant — one per leaf, with the *splits* doing the work of deciding which examples share which constant.

### 🧪 Worked Numerical Example
Suppose a node contains 4 examples with house prices (in some unit) $y = \{100, 120, 300, 320\}$. $\bar y = 210$. $\text{Var} = \frac{1}{4}\big[(100-210)^2+(120-210)^2+(300-210)^2+(320-210)^2\big] = \frac{1}{4}[12100+8100+8100+12100] = \frac{40400}{4}=10100$. Now split by a feature that separates $\{100,120\}$ from $\{300,320\}$: child 1 has $\bar y=110$, $\text{Var}_1 = \frac{1}{2}[(100-110)^2+(120-110)^2] = \frac{1}{2}[100+100]=100$; child 2 has $\bar y=310$, $\text{Var}_2=100$ by symmetry. Weighted post-split variance: $\text{Var}' = \frac{2}{4}(100)+\frac{2}{4}(100) = 100$. Variance reduction: $10100-100=10000$ — a massive reduction, correctly reflecting that this split perfectly separates the "cheap" and "expensive" groups.

### 🌍 Practical Example
Regression trees are the base learner inside **Gradient Boosted Regression Trees** (XGBoost, LightGBM) and **Random Forest Regressors** — arguably the single most common real-world use of the tree structure taught in this lecture is as one weak learner inside a larger ensemble, rather than as a single standalone model.

### ⚠️ Common Misconceptions
- **"A regression tree can output any real number, so it's just as flexible as linear regression."** A regression tree's predictions are a **step function** — piecewise-constant, one constant value per leaf/region. Within any single leaf, the prediction is identical for every input that lands there, regardless of how that input varies within the region — this is qualitatively different from linear regression's smoothly-varying prediction surface.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> "Regression trees use entropy, just computed on the continuous target." **False** — entropy is fundamentally undefined for a continuous variable without first discretizing it into bins (which would be a lossy, ad hoc workaround). The natural, standard regression-tree criterion is variance/SSE reduction, not entropy.

---

## 3.11 Stopping Criteria, Pruning & Overfitting

**Slide reference:** Not covered in this deck (pages 1–15 end at the worked example with no stopping-criteria or pruning discussion) — included here because it is the natural, immediately-following concern once recursive splitting has been defined, and it connects directly to material you've already covered.

### 📐 Formal Definition
Naive recursive splitting (Section 3.8), run without limit, continues until every leaf is **perfectly pure** — which, for real-world data with noise or overlapping classes, typically means growing the tree until individual leaves contain only one or a handful of training examples. **Stopping criteria** (e.g., maximum depth, minimum samples per leaf, minimum information gain to justify a split) or **pruning** (growing a full tree, then removing branches that don't improve validation performance) are used to halt this process before it overfits.

### 🗣️ Layman's Explanation
If you keep asking more and more specific questions, you can eventually build a tree that gets every single training example exactly right — including its noise and one-off quirks. That tree has memorized your training set rather than learned the underlying pattern, and will perform poorly on new data.

### 🎯 Why This Concept Exists
This is a direct instance of the **bias-variance trade-off** and overfitting framework from Lecture 4 (Regularization): an unconstrained decision tree is a very **high-variance** model — small changes in the training data can produce a very differently-shaped tree — and stopping criteria/pruning are the tree-specific analogue of the regularization techniques (e.g., $L_2$ penalty) you studied there.

### 🌍 Practical Example
Common stopping rules in practice: `max_depth`, `min_samples_split`, `min_samples_leaf` (all available as hyperparameters in scikit-learn's `DecisionTreeClassifier`/`Regressor`) — each one directly trades training-set fit (lower bias) against generalization (lower variance), exactly the trade-off curve from your Lecture 4 material.

### ⚠️ Common Misconceptions
- **"A fully-grown (unpruned) tree is the 'correct' or 'best' tree, and pruning is only a practical compromise."** A fully-grown tree, in the presence of any label noise, is close to guaranteed to **overfit** — pruning/stopping is not a reluctant compromise but a *necessary* part of getting a decision tree to generalize at all.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Decision trees are the textbook example of "low bias, high variance" — the exact opposite failure mode from the underfitting side of your bias-variance spectrum. This is a natural comparison point if an exam question asks you to place different models (linear regression, decision trees, k-NN, etc.) along the bias-variance spectrum.


---

# 4. Mathematical Foundations Deep Dive

## 4.1 Notation Recap

| Symbol | Meaning |
|---|---|
| $m$ | a tree node |
| $K$ | number of classes |
| $N_m$ | number of training examples reaching node $m$ |
| $p_m^i$ | proportion of node $m$'s examples belonging to class $i$ |
| $I_m$ | entropy (impurity) of node $m$ |
| $G_m$ | Gini impurity of node $m$ |
| $T$ | a candidate split (an attribute, and for continuous attributes, a threshold) |

## 4.2 Entropy — Where the Formula Comes From, and Why It Peaks at $p=0.5$

**Information-theoretic origin.** Shannon entropy measures the expected number of bits needed to communicate the outcome of a random variable, given optimal (Huffman-style) coding. For a binary variable with $P(\text{class 1})=p$, the information content ("surprise") of observing class 1 is $-\log_2(p)$ bits (rarer events are more surprising, hence carry more information) — the *expected* surprise, averaged over both possible outcomes, is:
$$\mathbb{E}[\text{surprise}] = p\cdot\big(-\log_2 p\big) + (1-p)\cdot\big(-\log_2(1-p)\big) = -p\log_2 p - (1-p)\log_2(1-p)$$
which is exactly the entropy formula in Section 3.6 — it is not an arbitrary "mixedness" formula, but literally the average number of bits an optimal code would need per symbol, given the class distribution.

**Proof that the peak is at $p=0.5$ with value $1$.** Let $H(p) = -p\log_2 p - (1-p)\log_2(1-p)$. Differentiate with respect to $p$ (using $\frac{d}{dp}[p\log_2 p] = \log_2 p + \frac{1}{\ln 2}$):
$$H'(p) = -\left(\log_2 p + \frac{1}{\ln 2}\right) + \left(\log_2(1-p) + \frac{1}{\ln 2}\right) = \log_2(1-p) - \log_2 p = \log_2\!\left(\frac{1-p}{p}\right)$$
Setting $H'(p)=0$: $\frac{1-p}{p}=1 \implies p = 0.5$. The second derivative $H''(p) = -\frac{1}{p\ln2} - \frac{1}{(1-p)\ln2} < 0$ everywhere on $(0,1)$, confirming this critical point is a **maximum** (entropy is concave). At $p=0.5$: $H(0.5) = -0.5\log_2(0.5) - 0.5\log_2(0.5) = -0.5(-1)-0.5(-1) = 1$ — confirming the graph on Slide 8 peaks at exactly $y=1$.

## 4.3 Entropy for $K>2$ Classes — the Maximum Value

By the same style of argument (maximize $I_m = -\sum_i p_m^i\log_2 p_m^i$ subject to $\sum_i p_m^i=1$, via a Lagrange multiplier), the maximum is attained at the **uniform** distribution $p_m^i = 1/K$ for all $i$, giving:
$$I_m^{\max} = -\sum_{i=1}^{K}\frac{1}{K}\log_2\!\left(\frac{1}{K}\right) = -K\cdot\frac{1}{K}\log_2\!\left(\frac{1}{K}\right) = \log_2(K)$$
For $K=2$: $\log_2(2)=1$, matching Section 4.2. For $K=4$ (equally likely): max entropy is $\log_2(4)=2$ bits.

## 4.4 Gini Impurity Is a First-Order Approximation of Entropy

This is a clean, rigorous derivation connecting Sections 3.6 and 3.7, using entropy measured in **nats** (natural log) rather than bits, purely to make the Taylor expansion clean. Recall $\ln(p) = \ln(1-(1-p))$; using the Taylor expansion of $\ln(1-\varepsilon)$ around $\varepsilon=0$ (i.e., $p$ near 1): $\ln(1-\varepsilon) = -\varepsilon - \frac{\varepsilon^2}{2} - \dots \approx -\varepsilon$ to first order, with $\varepsilon = 1-p$:
$$\ln(p) \approx -(1-p) \qquad\Longrightarrow\qquad -p\ln(p) \approx p(1-p)$$
By the symmetric argument (expanding around $1-p$ near 1, i.e., $p$ near 0): $-(1-p)\ln(1-p)\approx (1-p)p$. Adding these two approximations:
$$H_{\text{nats}}(p) = -p\ln p - (1-p)\ln(1-p) \;\approx\; p(1-p) + (1-p)p = 2p(1-p) = G(p)$$
**Gini impurity is the first-order Taylor approximation of Shannon entropy** (in nats) around the point of maximum purity. This is exactly why the two measures behave so similarly in practice (same zeros, same location of maximum) despite having different exact formulas and different peak heights when compared in mismatched units (bits vs. nats vs. the unscaled Gini value).

## 4.5 Balanced Tree Depth — Formal Statement

For a binary tree with $B$ leaves, arranged as a **complete, balanced** binary tree, the depth $d$ satisfies $2^d = B$, so $d = \log_2(B)$. This is the exact statement behind Slide 5's "$\log(B)$ decisions in the best balanced case" — and the qualifier matters: an *unbalanced* tree with $B$ leaves can have depth as large as $B-1$ (e.g., a tree that peels off exactly one example per split, a "linked-list-shaped" tree) — the same asymptotic gap between $O(\log B)$ and $O(B)$ that separates a balanced binary search tree from a degenerate (linked-list-like) one.

## 4.6 Information Gain Is a Weighted-Average Identity

A clean way to see why Section 3.8's weighting scheme ($N_{mj}/N_m$) is exactly correct, not merely a reasonable heuristic: consider computing entropy over the **pooled** set of all $N_m$ examples at the parent, but now imagining you first reveal *which child branch* each example landed in, then reveal its class. By the chain rule for entropy (a standard information-theory identity, $H(\text{class}) = H(\text{branch}) + H(\text{class}\mid\text{branch})$ when "branch" is a deterministic function of the split attribute), the **expected** entropy of the class *given* the branch is exactly:
$$H(\text{class}\mid\text{branch}) = \sum_{j=1}^{n} \Pr(\text{branch}=j)\cdot H(\text{class}\mid\text{branch}=j) = \sum_{j=1}^n \frac{N_{mj}}{N_m} I_{mj}$$
— precisely $I'_m$ from Section 3.8, with $\Pr(\text{branch}=j)$ estimated by its empirical frequency $N_{mj}/N_m$. Information gain $\text{Entropy}(S)-\text{Entropy}(S,T)$ is therefore exactly the **mutual information** between the class label and the split attribute, $I(\text{class}\,;\,\text{branch}) = H(\text{class}) - H(\text{class}\mid\text{branch})$ — a standard, named information-theory quantity, not an ad hoc invention specific to decision trees.

## 4.7 Regression Trees — the Variance Decomposition

For a candidate split creating children $m_1,\dots,m_n$, the **law of total variance** gives an exact decomposition of the parent's variance:
$$\underbrace{\text{Var}_m}_{\text{total}} = \underbrace{\sum_{j}\frac{N_{mj}}{N_m}\text{Var}_{mj}}_{\text{within-group (}=\text{Var}'_m\text{, Section 3.10)}} + \underbrace{\sum_j \frac{N_{mj}}{N_m}(\bar y_{mj} - \bar y_m)^2}_{\text{between-group}}$$
This means the **variance reduction** achieved by a split — $\text{Var}_m - \text{Var}'_m$ — is **exactly equal** to the weighted variance of the children's means around the parent's mean (the "between-group" term). In other words: *a split is good, for regression, exactly to the extent that it separates the data into groups with very different average $y$-values* — a precise, provable statement, not just an intuition, and the direct regression-tree analogue of Section 4.6's mutual-information identity for classification.

## 4.8 Computational Cost of Finding the Best Split

For one categorical attribute with $v$ distinct values, evaluating all possible splits into subsets costs at most $O(2^v)$ in general, but standard tree algorithms typically restrict to splitting on each individual attribute value (as in the multi-way "Play Golf" Outlook example) or, for ordered/continuous attributes, sort the $N_m$ examples by that attribute ($O(N_m\log N_m)$) and scan the $N_m-1$ midpoints between consecutive sorted values as candidate thresholds ($O(N_m)$ evaluations, each $O(K)$ to update running class counts) — an overall $O(N_m\log N_m)$ cost per attribute, per node. Across $d$ attributes and (in the balanced case) $O(\log N)$ levels of the tree, this gives standard decision-tree induction algorithms a practical total complexity on the order of $O(d\, N\log^2 N)$ — efficient enough for tree induction to remain a fast, practical algorithm even on large tabular datasets.


---

# 5. Architecture & Diagram Explanations

## 5.1 The Animal Classification Tree (Lecture 10, p. 3)
**What it shows:** a 4-level tree — root question "Has feathers?" splits True/False; the True branch asks "Can fly?" (→ Hawk / Penguin); the False branch asks "Has finns?" (→ Dolphin / Bear).
**Information flow:** strictly top-to-bottom — each internal node's question is only ever reached after its parent's condition has already been satisfied, so "Can fly?" is only ever asked of animals already known to have feathers. This is the cleanest possible illustration of Section 3.1's "combination of multiple if-else statements": it is equivalent to `if has_feathers: (if can_fly: Hawk else: Penguin) else: (if has_finns: Dolphin else: Bear)`.

## 5.2 The Axis-Aligned Decision Boundary (Lecture 10, p. 4)
**What it shows:** two side-by-side panels. Left: a 2D scatter plot of two classes ($C_1$: circles, $C_2$: squares) with a vertical line at $x_1=w_{10}$ and a horizontal line at $x_2=w_{20}$, drawn only in the right-hand portion of the plot. Right: the equivalent tree, root "$x_1>w_{10}$?" → No: leaf $C_1$; Yes: "$x_2>w_{20}$?" → Yes: $C_2$, No: $C_1$.
**Information flow:** the tree (right) is read top-to-bottom exactly as in Diagram 5.1; the scatter plot (left) should be read as the **geometric consequence** of that same tree — every region of the plane is labeled by whichever leaf you'd reach by checking, in order, "which side of $w_{10}$ is this point on?" then (only if needed) "which side of $w_{20}$?" This is the diagram to reproduce if asked to explain why univariate trees produce **axis-aligned, rectangular** decision regions (Section 3.4): each split is a single straight cut, always perpendicular to one axis, never diagonal.

## 5.3 The Univariate Tree Example (Lecture 10, p. 6)
**What it shows:** a 10-row toy table (Day, Weather, Temperature, Humidity, Wind, Play?) alongside two versions of the same tree — root "Weather" (three-way split: Sunny / Cloudy / Rainy); Sunny branch continues to "Humidity" (High→No, Normal→Yes); Cloudy branch terminates immediately at "Yes"; Rainy branch continues to "Wind" (Strong→No, Weak→Yes). The second tree diagram is identical in shape but relabels the Humidity/Wind branches with numeric thresholds ($>75\%$/$\le75\%$ and $>20$/$\le20$) instead of categorical labels.
**Information flow:** top-to-bottom, three-way at the root, then (for two of the three branches) a further two-way split. The side-by-side duplication of the same tree with two different attribute encodings is the diagram's core teaching point (Section 3.4): **the partition of the data is identical either way** — only the surface-level description of the Humidity/Wind features changes (bucketed category vs. raw numeric threshold).

## 5.4 The Entropy Curve (Lecture 10, p. 8)
**What it shows:** a plot of $\phi(p,1-p) = -p\log_2p - (1-p)\log_2(1-p)$ against $p\in[0,1]$: a smooth, symmetric, upward-bulging (concave) curve, equal to $0$ at both endpoints $p=0$ and $p=1$, reaching a peak of exactly $1$ at $p=0.5$.
**Information flow:** N/A (a static function plot, not a process diagram) — its purpose is to make Section 3.5's three abstract required properties (zero at purity, symmetric, maximal at $p=0.5$) visually undeniable for the *specific* choice of entropy, and to provide the exact peak height ($1$, in bits) proven algebraically in Section 4.2.

## 5.5 The "Play Golf" Frequency Table and Root Entropy (Lecture 10, p. 10)
**What it shows:** the full 14-row raw dataset table (Outlook, Temperature, Humidity, Windy, Play Golf), plus a small "Frequency Table" summarizing Play Golf(14): 9 Yes, 5 No, plus a boxed calculation deriving $E(\text{PlayGolf})=E(5,9)=0.94$.
**Information flow:** the frequency table is a **marginal summary** of the full raw table (counting only the final Play Golf column, ignoring all four features) — it is the input to the **root node's** entropy calculation, $I_m$ for $m=$"the entire dataset," before any split has been considered. This is the necessary "before" quantity that every subsequent candidate split's information gain (Section 3.9) will be measured against.

## 5.6 The Outlook Split Computation (Lecture 10, p. 12)
**What it shows:** a small frequency table cross-tabulating Outlook (Sunny/Overcast/Rainy) against Play Golf (Yes/No) — Sunny: 3 Yes, 2 No (5 total); Overcast: 4 Yes, 0 No (4 total); Rainy: 2 Yes, 3 No (5 total) — alongside three boxed sub-calculations, $E(\text{Sunny})=E(3,2)=0.971$, $E(\text{Overcast})=E(4,0)=0$, $E(\text{Rainy})=E(2,3)=0.971$, combined into the weighted total $E(\text{PlayGolf},\text{Outlook}) = \frac{5}{14}(0.971)+\frac{4}{14}(0)+\frac{5}{14}(0.971) = 0.693$.
**Information flow:** each of the three per-branch entropy boxes is computed **independently**, using only the rows belonging to that one Outlook value (exactly Section 3.8's warning about using $p_{mj}^i$, not $p_m^i$) — then the three results are combined via the sample-size-weighted sum into the single number $E(\text{PlayGolf},\text{Outlook})$, which is directly compared against the root entropy ($0.94$, Diagram 5.5) to yield $\text{Gain}(\text{Outlook})=0.94-0.693=0.247$.

> [!warning] **A slide-arithmetic detail worth flagging precisely**
> The slide's own displayed intermediate working for $E(\text{Sunny})=E(3,2)$ writes $-(0.60\log_2 0.60) - (0.40\log_2 0.40) = -(0.60\times0.737) - (0.40\times0.529)$. The final answer, $0.971$, is **correct** (independently re-verified in Section 6). But taken literally, "$0.529$" is *not* $\log_2(0.40)$ — that value is $-1.322$. What "$0.529$" actually represents is the **entire second term's value**, $0.40\times|\log_2(0.40)| = 0.40\times1.322=0.529$ — i.e., the slide's displayed intermediate compresses two steps (look up $\log_2(0.40)$, then multiply by $0.40$) into one number, in a way that can look, at a glance, like $0.529$ is being claimed as $\log_2(0.40)$ itself. It is not — if you compute $\log_2(0.40)$ independently while checking your own work, you should get $-1.322$, not $-0.529$; only after multiplying by $0.40$ does $0.529$ appear.

## 5.7 The Remaining Three Splits & Final Gain Comparison (Lecture 10, pp. 13–14)
**What it shows:** analogous boxed calculations for Temperature ($E=0.911$), Humidity ($E=0.788$), and Windy ($E=0.892$), each following the identical template as Diagram 5.6 (per-branch entropy, then sample-size-weighted combination) — followed by a summary comparing all four gains: $\text{Gain}(\text{Outlook})=0.247$, $\text{Gain}(\text{Temperature})=0.029$, $\text{Gain}(\text{Humidity})=0.152$, $\text{Gain}(\text{Windy})=0.048$.
**Information flow:** these four gain values are **siblings**, not a sequence — they are four independent evaluations of "what if I split the root on this attribute instead," all computed against the same root entropy ($0.94$) baseline, existing purely to be **compared against each other**. The largest value, $\text{Gain}(\text{Outlook})=0.247$, wins — Outlook is the attribute ID3 would greedily select as the root split for this dataset, exactly mirroring the structure of Diagram 5.3's worked example (a different toy dataset, same procedure), where "Weather" (that example's version of Outlook) was likewise the winning root split.


---

# 6. Worked Examples

All numeric results below were independently re-derived with Python from the raw 14-row (and, for Worked Example 4, 10-row) datasets before being written up — every value matches the slide's own reported figures to 3 decimal places.

## Worked Example 1 — Play Golf: Choosing the Root Split

**Dataset** (14 days; Outlook, Temperature, Humidity, Windy → Play Golf):

| Outlook | Temp | Humidity | Windy | Play |
|---|---|---|---|---|
| Rainy | Hot | High | FALSE | No |
| Rainy | Hot | High | TRUE | No |
| Overcast | Hot | High | FALSE | Yes |
| Sunny | Mild | High | FALSE | Yes |
| Sunny | Cool | Normal | FALSE | Yes |
| Sunny | Cool | Normal | TRUE | No |
| Overcast | Cool | Normal | TRUE | Yes |
| Rainy | Mild | High | FALSE | No |
| Rainy | Cool | Normal | FALSE | Yes |
| Sunny | Mild | Normal | FALSE | Yes |
| Rainy | Mild | Normal | TRUE | Yes |
| Overcast | Mild | High | TRUE | Yes |
| Overcast | Hot | Normal | FALSE | Yes |
| Sunny | Mild | High | TRUE | No |

**Step 1 — root entropy.** 9 Yes, 5 No, out of 14.
$$E(\text{PlayGolf}) = E(5,9) = -\frac{9}{14}\log_2\frac{9}{14} - \frac{5}{14}\log_2\frac{5}{14} = -(0.643)(-0.6371) - (0.357)(-1.4863) = 0.4098+0.5306 = 0.940$$

**Step 2 — Outlook split.** Sunny: 3 Yes, 2 No (5 total). Overcast: 4 Yes, 0 No (4 total). Rainy: 2 Yes, 3 No (5 total).
$$E(\text{Sunny})=E(3,2) = -0.6\log_2(0.6) - 0.4\log_2(0.4) = 0.4422+0.5288 = 0.971$$
$$E(\text{Overcast})=E(4,0) = -1\log_2(1) - 0\log_2(0) = 0 - 0 = 0 \quad\text{(pure — every Overcast day is "Yes")}$$
$$E(\text{Rainy})=E(2,3) = -0.4\log_2(0.4)-0.6\log_2(0.6) = 0.5288+0.4422 = 0.971 \quad\text{(same \{0.4,0.6\} split as Sunny, just swapped)}$$
$$E(\text{PlayGolf},\text{Outlook}) = \frac{5}{14}(0.971)+\frac{4}{14}(0)+\frac{5}{14}(0.971) = 0.3571(0.971)\times2 = 0.6935$$
$$\text{Gain}(\text{Outlook}) = 0.940 - 0.6935 = 0.2467 \approx 0.247$$

**Step 3 — the other three splits** (same method; independently verified):

| Attribute | Branch entropies | Weighted $E(S,T)$ | Gain |
|---|---|---|---|
| Temperature | Hot $E(2,2){=}1.000$; Mild $E(4,2){=}0.918$; Cool $E(3,1){=}0.811$ | $0.911$ | $0.940-0.911=\mathbf{0.029}$ |
| Humidity | High $E(3,4){=}0.985$; Normal $E(6,1){=}0.592$ | $0.789$ | $0.940-0.789=\mathbf{0.152}$ |
| Windy | False $E(6,2){=}0.811$; True $E(3,3){=}1.000$ | $0.892$ | $0.940-0.892=\mathbf{0.048}$ |

**Step 4 — pick the winner.** $\text{Gain}(\text{Outlook})=0.247$ is the largest of the four — **Outlook is chosen as the root split.** The Overcast branch is already pure ($E=0$) and becomes an immediate "Yes" leaf; the Sunny and Rainy branches ($E=0.971$ each, still highly impure) require the algorithm to **recurse** — repeating this entire procedure using only the Sunny (or only the Rainy) subset of rows, now choosing among the *remaining* attributes (Temperature, Humidity, Windy).

**Reading the result.** This exactly reproduces the classic Quinlan ID3 "Play Tennis"/"Play Golf" textbook example, and demonstrates the full split-selection procedure end-to-end on a real (if small) dataset — every number here is independently checkable by hand using nothing but the entropy formula (Section 3.6) and a calculator.

---

## Worked Example 2 — Gini Impurity for the Same Root Node

**Setup.** Same root node as Worked Example 1: 9 Yes, 5 No out of 14; $p=9/14\approx0.643$.

**Computation.**
$$G = 2p(1-p) = 2\times\frac{9}{14}\times\frac{5}{14} = 2\times\frac{45}{196} = \frac{90}{196} \approx 0.459$$

**Reading the result.** Compare to this node's entropy, $0.940$ (in bits). Both numbers indicate a highly impure node (both are close to their own respective maxima — entropy's max is $1$, Gini's max for $K=2$ is $0.5$) — but the two numbers are **not on the same scale** and should never be subtracted from or compared directly against each other; each is only meaningfully compared against *other values of the same measure* (e.g., Gini-before vs. Gini-after a split), never cross-measure.

---

## Worked Example 3 — Verifying the $0\log_2 0 = 0$ Convention

**Setup.** The Overcast branch from Worked Example 1: 4 Yes, 0 No.

**Computation.** $p_{\text{Yes}}=4/4=1$, $p_{\text{No}}=0/4=0$.
$$E(\text{Overcast}) = -(1)\log_2(1) - (0)\log_2(0) = -(1)(0) - (\text{undefined}\times0)$$
The first term is unambiguous: $\log_2(1)=0$, so $-(1)(0)=0$. The second term, $0\times\log_2(0)$, is a $0\times(-\infty)$ indeterminate form as written — but taking the limit $\lim_{p\to0^+} p\log_2(p)$ (via L'Hôpital's rule, rewriting as $\lim_{p\to0^+}\frac{\log_2 p}{1/p}$) gives exactly $0$. By convention, this term is simply defined as $0$.

**Reading the result.** $E(\text{Overcast})=0$ — correctly indicating perfect purity, exactly as expected for a branch where *every single example* shares the same label. This convention must be applied every time a candidate split produces an empty class within some branch (a very common occurrence in real datasets), and forgetting it (e.g., leaving the term as "undefined" and refusing to compute an entropy) is a common source of stalled calculations under exam time pressure.

---

## Worked Example 4 — Building the Univariate Tree from Scratch

This example independently re-derives Slide 6's toy 10-row tree (Section 3.4, Diagram 5.3), showing *why* Weather is chosen as the root, and why the Sunny/Rainy branches each need exactly one more split while Cloudy needs none.

**Dataset** (10 days; Weather, Temperature, Humidity, Wind → Play):

| Weather | Temp | Humidity | Wind | Play |
|---|---|---|---|---|
| Sunny | Hot | High | Weak | No |
| Cloudy | Hot | High | Weak | Yes |
| Sunny | Mild | Normal | Strong | Yes |
| Cloudy | Mild | High | Strong | Yes |
| Rainy | Mild | High | Strong | No |
| Rainy | Cool | Normal | Strong | No |
| Rainy | Mild | High | Weak | Yes |
| Sunny | Hot | High | Strong | No |
| Cloudy | Hot | Normal | Weak | Yes |
| Rainy | Mild | High | Strong | No |

**Step 1 — root entropy.** 5 Yes, 5 No, out of 10 — a perfect 50/50 split: $E(\text{Play}) = -0.5\log_2(0.5)-0.5\log_2(0.5) = 1.000$ (maximum possible entropy for a binary label, as proven in Section 4.2 — this dataset starts out *maximally* impure).

**Step 2 — compare all four candidate root splits** (independently computed):

| Attribute | Branches (n, Yes/No, entropy) | Weighted $E$ | Gain |
|---|---|---|---|
| **Weather** | Sunny (3: 1Y/2N, $E{=}0.918$); Cloudy (3: 3Y/0N, $E{=}0$); Rainy (4: 1Y/3N, $E{=}0.811$) | $0.600$ | $1.000-0.600=\mathbf{0.400}$ |
| Temperature | Hot (4: 2Y/2N, $E{=}1.0$); Mild (5: 3Y/2N, $E{=}0.971$); Cool (1: 0Y/1N, $E{=}0$) | $0.886$ | $1.000-0.886=0.114$ |
| Humidity | High (7: 3Y/4N, $E{=}0.985$); Normal (3: 2Y/1N, $E{=}0.918$) | $0.965$ | $1.000-0.965=0.035$ |
| Wind | Weak (4: 3Y/1N, $E{=}0.811$); Strong (6: 2Y/4N, $E{=}0.918$) | $0.876$ | $1.000-0.876=0.124$ |

**Weather wins decisively** (gain $0.400$, more than triple the next-best candidate, Wind at $0.124$) — matching the diagram in Section 3.4/5.3, where Weather is indeed the root.

**Step 3 — recurse on the Sunny branch** (3 rows: 1 Yes, 2 No — rows with Weather=Sunny). Only Humidity distinguishes these three rows in this toy dataset (High → the two "No" rows; Normal → the one "Yes" row) — splitting on Humidity here yields **two perfectly pure children** (High: 0Y/2N, $E{=}0$; Normal: 1Y/0N, $E{=}0$), for a weighted post-split entropy of exactly $0$ — a full information gain of $0.918$ (this branch's own starting entropy). No further recursion is needed on this branch.

**Step 4 — recurse on the Rainy branch** (4 rows: 1 Yes, 3 No). Splitting on Wind separates these perfectly: Strong → the three "No" rows ($E{=}0$), Weak → the one "Yes" row ($E{=}0$) — again a fully pure split, terminating recursion on this branch.

**Step 5 — the Cloudy branch** (3 rows, all Yes) was already pure after the root split ($E{=}0$) — it requires no further splitting at all, exactly as drawn in Slide 6's diagram.

**Reading the result.** This fully reconstructs, from raw data and the entropy/gain formulas alone, the *exact* tree shape shown on the slide — confirming that Slide 6's diagram is not an arbitrary illustration but the actual, correct output of the ID3 procedure applied to this specific 10-row dataset.

---

## Worked Example 5 — Regression Tree Variance Reduction (Law of Total Variance Check)

**Setup.** Reusing Section 3.10's numeric example: node with $y=\{100,120,300,320\}$, $\bar y_m=210$, $\text{Var}_m=10100$; split into $\{100,120\}$ ($\bar y=110$) and $\{300,320\}$ ($\bar y=310$), each with within-group variance $100$.

**Verifying the Section 4.7 decomposition.** Within-group term: $\text{Var}'_m = \frac{2}{4}(100)+\frac{2}{4}(100)=100$. Between-group term: $\frac{2}{4}(110-210)^2 + \frac{2}{4}(310-210)^2 = 0.5(10000)+0.5(10000) = 10000$. Sum: $100+10000=10100$ — **exactly** matching $\text{Var}_m$, confirming the law-of-total-variance identity numerically. Variance reduction ($10100-100=10000$) exactly equals the between-group term ($10000$), as Section 4.7 proves in general.


---

# 7. Concept Connections — The Big Picture

## 7.1 Where Decision Trees Sit in the Course

| Earlier concept | Connection to this lecture |
|---|---|
| **Parametric models (L3, L5 — Linear/Logistic Regression)** | Both commit to a fixed functional form ($\theta^\top x$) before training; a decision tree is the course's first genuinely **non-parametric** method — structure is learned, not just coefficients within a fixed structure. |
| **MLE / probability (L2)** | Entropy is a probability-based quantity ($-\sum p_i\log p_i$); the whole impurity-measure framework (Section 3.5) is a direct descendant of treating each node's label distribution as a categorical probability distribution. |
| **Bias-variance / Regularization (L4)** | An unconstrained decision tree is the course's canonical **high-variance, low-bias** model — Section 3.11 connects stopping criteria/pruning directly to the regularization framework you already built. |
| **Evaluation Metrics (L7)** | Choosing between competing splits (or between a shallow vs. deep tree) still requires held-out validation performance, not just training-set information gain — the overfitting risk named in Section 3.9's "unique ID column" misconception is exactly why. |
| **Universal Approximation Theorem (L6.2)** | A sufficiently deep, unconstrained tree can, in principle, perfectly fit *any* finite training set (a form of universal approximation on the training data) — precisely because it is non-parametric; but (echoing UAT's own silence on trainability/generalization) perfectly fitting the training set is not the same as generalizing, which is exactly Section 3.11's point. |

## 7.2 What Comes Next (On the Horizon)

A single decision tree, however carefully pruned, remains a high-variance model. The next natural step in most ML curricula — and very likely upcoming in this course — is **ensembling** many trees together to cancel out this variance:

- **Bagging / Random Forests**: train many trees on bootstrap-resampled data (and, for random forests, a random subset of features at each split), then average their predictions — directly targeting the "high variance" weakness named in Section 3.11.
- **Boosting (AdaBoost, Gradient Boosting, XGBoost)**: train trees **sequentially**, each new tree focused on correcting the previous ensemble's errors — turning many high-bias "weak learner" trees (often just a few levels deep, sometimes literally "decision stumps" — a single split) into a low-bias, low-variance ensemble.

Every concept in this chapter — entropy/Gini as the splitting criterion, information gain as the greedy selection rule, variance reduction for regression — is reused **unchanged** as the base learner inside both of these ensemble families; this lecture is the necessary prerequisite for understanding either.

## 7.3 One Thread Worth Isolating: "Impurity Reduction" Is a General-Purpose Idea

Sections 3.9, 4.6, and 4.7 collectively make one point from three angles: **information gain (classification) and variance reduction (regression) are the same idea**, applied to two different kinds of impurity measure:

$$\text{Gain} = \text{Impurity}(\text{parent}) - \text{Impurity}(\text{weighted children})$$

For classification, "impurity" is entropy or Gini (a function of class *proportions*); for regression, "impurity" is variance (a function of the *spread* of a continuous target). Both are special cases of a more general idea from statistics: **decompose total variability into a within-group part and a between-group part, and prefer splits that push as much of the variability as possible into the between-group term** (Section 4.7's law-of-total-variance identity makes this exact for regression; Section 4.6's mutual-information identity makes the classification analogue exact). This is an excellent unifying answer if an exam asks you to compare classification-tree and regression-tree splitting criteria.


---

# 8. Exam Preparation

## 8.1 High-Yield Facts

- A decision tree is hierarchical, non-parametric, divide-and-conquer; composed of internal decision nodes and terminal leaves.
- Each decision node $m$ implements test function $f_m(x)$ with discrete outcomes labeling branches; prediction = one root-to-leaf traversal.
- Balanced-tree depth: $\log_2(B)$ for $B$ leaves (best case); degrades toward $O(B)$ if unbalanced.
- Univariate tree: each node's test uses exactly one feature → axis-aligned decision regions.
- Impurity measure $\phi(p,1-p)$: must be $0$ at $p\in\{0,1\}$, symmetric, maximal at $p=0.5$.
- Entropy: $\phi(p,1-p)=-p\log_2p-(1-p)\log_2(1-p)$; $K$-class: $I_m=-\sum_i p_m^i\log_2p_m^i$; max value $\log_2K$ (binary max $=1$, at $p=0.5$).
- Gini impurity: $G=1-\sum_i(p_m^i)^2$; binary form $G=2p(1-p)$; max $=0.5$ (binary) at $p=0.5$. Gini is the first-order Taylor approximation of entropy (nats) near purity.
- $0\log_2 0 \triangleq 0$ (by the limit $p\to0^+$), needed whenever a branch is missing a class entirely.
- Total post-split impurity: $I'_m=\sum_j\frac{N_{mj}}{N_m}I_{mj}$ — **must** use each child's own class proportions $p_{mj}^i$, not the parent's $p_m^i$.
- Information Gain: $\text{Gain}(S,T)=\text{Entropy}(S)-\text{Entropy}(S,T)$; maximizing gain ⇔ minimizing post-split impurity (same selection rule, two framings).
- Tree induction (ID3-style) is **greedy** and **recursive**: locally optimal split at each node, no lookahead; globally optimal tree search is NP-hard.
- "Play Golf" canonical numbers: root $E=0.94$ (9 Yes/5 No); Gain(Outlook)$=0.247$ (wins); Gain(Temperature)$=0.029$; Gain(Humidity)$=0.152$; Gain(Windy)$=0.048$.
- Regression trees: leaf prediction = mean of training $y$ in that leaf; splitting criterion = variance/SSE reduction, not entropy/Gini.
- Law of total variance: $\text{Var}_{\text{parent}} = \text{Var}_{\text{within}} + \text{Var}_{\text{between}}$; variance reduction from a split = the between-group term, exactly.
- Decision trees are the course's canonical **high-variance, low-bias** model; unconstrained growth overfits; stopping criteria/pruning are the tree-specific regularization analogue.

## 8.2 Common Student Mistakes

1. **Using the parent node's class proportions when computing a child's entropy** instead of recomputing proportions freshly within each branch (Section 3.8's flagged subtlety).
2. **Forgetting the $0\log_2 0=0$ convention** and getting stuck on a "pure" branch's entropy calculation.
3. **Confusing entropy's numeric scale with Gini's** — assuming both max out at the same value (entropy: 1 bit; Gini: 0.5, for binary classes).
4. **Believing higher information gain always means a better model** — ignoring the "unique ID column" overfitting trap (Section 3.9).
5. **Treating "univariate" as a restriction to categorical features** — univariate splits work identically for continuous features via a threshold.
6. **Assuming regression trees use entropy on a discretized target** — the natural, standard criterion is variance/SSE reduction, not entropy.
7. **Describing tree induction as exhaustive/globally optimal** — it is a greedy, locally-optimal search; the global optimum is NP-hard to find exactly.
8. **Log-base confusion**: computing entropy with $\ln$ instead of $\log_2$ and reporting a bits-scaled answer with a nats-scaled number.

## 8.3 Professor Trap Questions

> [!warning] Same "true fact about a slightly different concept" pattern as always — read the precise qualifier.

1. *"A decision tree with more leaves always has lower training error."* — **True**, but a trap if the question is really asking about *generalization* (test error) — more leaves (deeper tree) almost always reduces training error monotonically while eventually *increasing* test error past some point (overfitting, Section 3.11).
2. *"Gini impurity and entropy always select the same split as best."* — **Trap**: they usually agree but are not guaranteed to, since they weight extreme vs. moderate impurities slightly differently (Section 3.7).
3. *"A univariate decision tree can approximate any decision boundary, given enough depth."* — **Trap**: it can approximate boundaries **arbitrarily well** with enough axis-aligned rectangular steps (in the limit), but it can never produce an exactly diagonal boundary with any finite depth — a genuinely diagonal boundary requires a multivariate/oblique split.
4. *"Information gain is unbiased with respect to the number of values an attribute has."* — **Trap**: it is **biased toward high-cardinality attributes** (Section 3.9); this is exactly why C4.5 introduced Gain Ratio.
5. *"A regression tree's prediction can be any real number."* — **Trap**: only within the *range* of leaf-mean values seen during training, and only as a piecewise-**constant** step function — it cannot smoothly extrapolate or interpolate the way linear regression can.
6. *"Higher entropy always means a worse split was chosen."* — **Trap**: entropy is a property of a **node**, not of "a split" being good or bad in isolation — a split is scored by its *information gain* (reduction relative to the parent), not by the child nodes' absolute entropy values alone (a split producing two moderately impure but large, useful children can have a higher gain than a split producing one tiny pure node and one still-mostly-impure large node).

## 8.4 Frequently Confused Concepts

| Concept A | Concept B | The distinction |
|---|---|---|
| Entropy | Gini Impurity | Entropy: information-theoretic (bits), formula uses $\log$, binary max $=1$. Gini: probability-of-mislabeling interpretation, no logarithms, binary max $=0.5$. Gini ≈ first-order Taylor approx. of entropy (nats) near purity. |
| Information Gain | Gain Ratio | Gain: $\text{Entropy}(S)-\text{Entropy}(S,T)$, biased toward high-cardinality attributes. Gain Ratio (C4.5): Gain divided by the split's own "split information," correcting that bias. |
| Univariate tree | Multivariate (oblique) tree | Univariate: one feature per split, axis-aligned regions. Multivariate: linear combination of features per split ($w^\top x>c$), diagonal regions. |
| Classification tree | Regression tree | Classification: entropy/Gini splitting criterion, leaf = majority class. Regression: variance/SSE splitting criterion, leaf = mean of training $y$. |
| Greedy tree induction | Globally optimal tree search | Greedy: locally-best split at each node, no lookahead, computationally tractable ($O(dN\log^2N)$-ish). Global search: NP-hard, practically infeasible for any nontrivial dataset. |
| Pruning | Stopping criteria (pre-pruning) | Pruning ("post-pruning"): grow a full tree first, then remove branches that don't help validation performance. Stopping criteria ("pre-pruning"): halt growth early via rules like `max_depth`/`min_samples_leaf`, before the tree is fully grown. |


---

# 9. Practice Questions with Full Solutions

## A. Conceptual Questions

**Q1.** Explain what "non-parametric" means for a decision tree, and contrast it with logistic regression.

> **Solution.** "Non-parametric" does not mean "no parameters" — a fitted tree has plenty of implicit parameters (which feature to split on, what threshold, at every node). It means the **number and structure** of these decisions is not fixed in advance and is instead determined by the training data itself — a tree trained on more/different data can end up with an entirely different shape (different depth, different splits). Logistic regression, by contrast, is parametric: it always has exactly $d+1$ parameters ($\theta_0,\dots,\theta_d$) regardless of how much training data you have, and commits to a fixed functional form (a linear decision boundary through a sigmoid) before training begins.

**Q2.** State the three properties any valid impurity measure $\phi(p,1-p)$ must satisfy, and explain, for each, why it is necessary.

> **Solution.** (1) $\phi(0,1)=\phi(1,0)=0$ — a node where every example shares one label is perfectly sorted; any nonzero value here would incorrectly penalize a split that has already succeeded completely. (2) Maximal at $p=0.5$ — a 50/50 mixture is the least-informative possible label distribution (a coin flip), so this is where "confusion" should peak. (3) Symmetric, $\phi(p,1-p)=\phi(1-p,p)$ — which class happens to be labeled "positive" is an arbitrary naming choice, and impurity should not depend on it.

**Q3.** Why is standard decision-tree induction described as "greedy," and what is the practical consequence of this design choice?

> **Solution.** At each node, the algorithm picks whichever single candidate split locally maximizes information gain (or minimizes post-split impurity) *right now*, with no consideration of how that choice affects what splits become available (or necessary) further down the tree. The practical consequence is a trade-off: greedy search is computationally tractable (polynomial-time, roughly $O(dN\log^2N)$), whereas finding the single globally optimal tree over all possible sequences of splits is NP-hard — greediness sacrifices a global-optimality guarantee for practical feasibility.

## B. Short-Answer Questions

**Q4.** Write the binary entropy formula and state its maximum value and where it occurs.

> **Solution.** $\phi(p,1-p) = -p\log_2p - (1-p)\log_2(1-p)$. Maximum value is $1$ (bit), occurring at $p=0.5$.

**Q5.** State the formula for Gini impurity for $K$ classes, and its binary special case.

> **Solution.** $G = 1-\sum_{i=1}^K (p^i)^2$; binary case: $G=2p(1-p)$.

## C. Mathematical Derivations

**Q6.** Prove that binary entropy $\phi(p,1-p)$ is maximized at $p=0.5$.

> **Solution.** See the full derivation in Section 4.2: differentiate $H(p)=-p\log_2p-(1-p)\log_2(1-p)$ to get $H'(p)=\log_2\!\left(\frac{1-p}{p}\right)$; setting this to $0$ gives $\frac{1-p}{p}=1\Rightarrow p=0.5$; the negative second derivative confirms it's a maximum, with value $H(0.5)=1$.

**Q7.** Derive the relationship between Gini impurity and Shannon entropy (measured in nats) near a node's point of maximum purity.

> **Solution.** Using the Taylor expansion $\ln(p) = \ln(1-(1-p)) \approx -(1-p)$ for $p$ near $1$: $-p\ln(p)\approx p(1-p)$, and symmetrically $-(1-p)\ln(1-p)\approx (1-p)p$. Summing: $H_{\text{nats}}(p) \approx p(1-p)+(1-p)p = 2p(1-p) = G(p)$ — Gini impurity is the first-order Taylor approximation of (nats-based) Shannon entropy near purity. See Section 4.4 for the full derivation.

**Q8.** Prove that the variance reduction achieved by a regression-tree split equals the weighted variance of the children's means around the parent's mean.

> **Solution.** By the law of total variance: $\text{Var}_{\text{parent}} = \underbrace{\sum_j\frac{N_{mj}}{N_m}\text{Var}_{mj}}_{\text{within-group}} + \underbrace{\sum_j\frac{N_{mj}}{N_m}(\bar y_{mj}-\bar y_m)^2}_{\text{between-group}}$. Since variance reduction is defined as $\text{Var}_{\text{parent}} - \text{Var}'_{\text{parent}}$ (parent variance minus the weighted within-group/post-split variance), and the within-group term is exactly $\text{Var}'_{\text{parent}}$, rearranging the identity gives $\text{Var}_{\text{parent}} - \text{Var}'_{\text{parent}} = \text{between-group term}$, proving the claim exactly (see Section 4.7, and the numeric check in Worked Example 5).

## D. Numerical Problems

**Q9.** A node has 4 examples of class A and 2 of class B. Compute its entropy and its Gini impurity.

> **Solution.** $p_A=4/6=0.667$, $p_B=2/6=0.333$. Entropy: $-0.667\log_2(0.667) - 0.333\log_2(0.333) = 0.3900+0.5283=0.918$. Gini: $2(0.667)(0.333)=0.444$.

**Q10.** The node from Q9 is split into two children: Child 1 has 3 examples, all class A. Child 2 has 3 examples, 1 class A and 2 class B. Compute the information gain of this split.

> **Solution.** Child 1 is pure: $E_1=0$. Child 2: $p_A=1/3=0.333$, $p_B=2/3=0.667$; $E_2 = -0.333\log_2(0.333)-0.667\log_2(0.667) = 0.5283+0.3900=0.918$. Weighted post-split entropy: $\frac{3}{6}(0)+\frac{3}{6}(0.918) = 0.459$. Gain $= 0.918-0.459=0.459$.

**Q11.** For the same split as Q10, compute the information gain using **Gini impurity** instead of entropy.

> **Solution.** Parent Gini (from Q9): $0.444$. Child 1 (pure): $G_1=0$. Child 2 ($p_A=1/3$): $G_2 = 2(1/3)(2/3)=4/9=0.444$. Weighted post-split Gini: $\frac{3}{6}(0)+\frac{3}{6}(0.444)=0.222$. Gini gain $=0.444-0.222=0.222$. (Note this is a different *number* from Q10's entropy-based gain, $0.459$ — as always, the two measures are not on the same scale, though in this case they happen to agree on the qualitative conclusion that the split is a strong improvement.)

## E. Architecture Explanation

**Q12.** Describe, step by step, how a trained decision tree would classify a new example, using the animal-classification tree from Section 3.1 (Has feathers? → Can fly?/Has finns? → Hawk/Penguin/Dolphin/Bear) as a concrete case, for a new example described as "no feathers, has finns."

> **Solution.** Start at the root: evaluate "Has feathers?" — the new example has no feathers, so answer False, follow the False branch. Arrive at "Has finns?" — the example has finns, so answer True, follow the True branch. Arrive at the leaf labeled "Dolphin" — no further questions remain, so the tree predicts **Dolphin**. Only two test-function evaluations were needed (not four, and not a comparison against all four leaves) — exactly one question was asked per level of depth actually traversed, per Section 3.2's exam trap.

## F. Comparison Questions

**Q13.** Compare entropy and Gini impurity as splitting criteria, along at least three axes.

> **Solution.**
>
> | Axis | Entropy | Gini Impurity |
> |---|---|---|
> | Formula | $-\sum_i p^i\log_2 p^i$ (requires logarithms) | $1-\sum_i(p^i)^2$ (no logarithms; cheaper to compute) |
> | Binary maximum value | $1$ (at $p=0.5$) | $0.5$ (at $p=0.5$) |
> | Interpretation | Expected number of bits to communicate the class label | Probability of mislabeling under random guessing from the node's own class proportions |
> | Typical algorithm | ID3, C4.5 | CART (and scikit-learn's default) |
> | Relationship | — | First-order Taylor approximation of entropy (nats) near purity |

**Q14.** Compare classification trees and regression trees along splitting criterion, leaf prediction, and the shape of the resulting prediction function.

> **Solution.** **Splitting criterion:** classification trees use entropy or Gini impurity (functions of categorical class proportions); regression trees use variance/sum-of-squared-error reduction (a function of a continuous target's spread). **Leaf prediction:** classification trees predict the majority class among training examples reaching that leaf; regression trees predict the mean of the training $y$-values reaching that leaf. **Shape of prediction function:** both produce a **piecewise-constant, step-function-like** prediction surface over the input space — classification trees assign one of $K$ discrete labels to each rectangular region; regression trees assign one specific real number to each rectangular region — neither can smoothly interpolate within a single leaf's region.

## G. Higher-Order Reasoning

**Q15.** A colleague builds a decision tree and includes a "Customer ID" column as a candidate splitting attribute. The tree achieves 100% training accuracy using almost entirely Customer-ID-based splits. Explain what went wrong and connect your answer to a specific concept from this chapter.

> **Solution.** Information gain (Section 3.9) is systematically **biased toward high-cardinality attributes** — a Customer ID column, with as many distinct values as there are training rows, can always achieve the maximum possible information gain: splitting on it puts each single example into its own perfectly pure, singleton branch (entropy $=0$ for every branch, since each contains exactly one example). This trivially "explains" the training data perfectly while learning **nothing generalizable** — Customer ID has no relationship to the true label-generating process, and this same tree, applied to any new customer (a new, unseen ID value), has no learned rule to apply at all. This is the exact overfitting failure mode flagged in Section 3.9's misconception box, and it is precisely why C4.5 introduced Gain Ratio (normalizing gain by the split's own information content) and why practical tree-building pipelines exclude obvious identifier columns before training, in addition to applying the stopping-criteria/pruning safeguards of Section 3.11.

**Q16.** A regression tree and a linear regression model are both fit to the same dataset, where the true relationship between $x$ and $y$ is $y = 3x + 5$ (an exact straight line, no noise). Which model will fit better, and why, connecting your answer to the "shape of the prediction function" idea from Q14?

> **Solution.** Linear regression will fit this data **essentially perfectly** (it directly represents $y=3x+5$ with two parameters), while a regression tree — restricted to a piecewise-**constant** prediction within each leaf region — can only ever *approximate* a smoothly sloped line by a staircase of small constant steps, never representing it exactly with a finite tree. Given enough depth (enough splits, i.e., enough steps in the staircase), a regression tree's approximation error can be made arbitrarily small, but it will never reach *exactly* zero error the way linear regression's two-parameter fit can for a perfectly linear relationship — this is a direct consequence of the "piecewise-constant, step-function" structural limitation named in Q14, and a good illustration of why model choice should be informed by the expected shape of the true underlying relationship (smooth and linear → parametric linear model likely wins; genuinely non-linear, interaction-heavy, or discontinuous → tree-based models often win).


---

# 10. References

## 10.1 Slide-derived content

Lecture 10 does not include a "Textbook Chapters" or "References" slide (unlike Lecture 9), so no citations are given directly on the slides. All content in Sections 3.1–3.6, 3.8–3.9, and 5 derives directly from the lecture's own 15 slides (decoded/extracted text and diagrams, cross-verified via independent recomputation of every numeric example in Section 6).

## 10.2 Probable primary textbook source

1. **Alpaydın, E.**, *Introduction to Machine Learning*, MIT Press — **Chapter 9, "Decision Trees."** The Slide 4 diagram (2D scatter plot with axis-aligned regions labeled $w_{10}, w_{20}$, alongside its equivalent tree) is a very widely reproduced illustration closely matching this textbook's standard figure for univariate decision trees; the lecture's terminology ("univariate tree," "test function $f_m(x)$," discriminant-based framing) closely follows this book's treatment. Supports Sections 3.1–3.4.

## 10.3 Additional authoritative sources used for gaps and derivations

2. **Quinlan, J. R.**, "Induction of Decision Trees," *Machine Learning*, 1(1), 1986 — the original **ID3** algorithm paper; entropy-based information gain as the splitting criterion (Sections 3.6, 3.9) traces to this paper. The "Play Golf" / "Play Tennis" worked dataset (Section 6, Worked Example 1) is the classic textbook example associated with this algorithm (as popularized in later textbooks, e.g. Mitchell's *Machine Learning*, 1997).
3. **Quinlan, J. R.**, *C4.5: Programs for Machine Learning*, Morgan Kaufmann, 1993 — introduces **Gain Ratio** as a bias-correction for information gain's preference for high-cardinality attributes (Section 3.9, Section 8.4).
4. **Breiman, L., Friedman, J., Olshen, R. & Stone, C.**, *Classification and Regression Trees*, Wadsworth, 1984 — the original **CART** book; source of **Gini impurity** (Section 3.7, the gap-filled topic) and of the standard regression-tree formulation via variance/SSE reduction (Section 3.10, the second gap-filled topic).
5. **Shannon, C. E.**, "A Mathematical Theory of Communication," *Bell System Technical Journal*, 1948 — the origin of entropy as a measure of information/uncertainty (Section 4.2).
6. **Mitchell, T.**, *Machine Learning*, McGraw-Hill, 1997 — standard textbook presentation of the ID3 "Play Tennis" dataset and worked entropy/information-gain calculations, closely matching the structure of Section 6's Worked Example 1.

## 10.4 Which sections benefited from which references

| Section(s) | Primary reference(s) |
|---|---|
| 3.1–3.4 (Tree structure, test functions, univariate trees) | Lecture 10 slides; Alpaydın Ch. 9 |
| 3.5–3.6, 3.9 (Impurity framework, entropy, information gain) | Lecture 10 slides; Shannon 1948; Quinlan 1986 |
| 3.7 (Gini impurity — gap-fill) | Breiman et al. 1984 (CART) |
| 3.8 (Split/sub-tree generation) | Lecture 10 slides; standard ID3/C4.5 literature |
| 3.10 (Regression trees — gap-fill) | Breiman et al. 1984 (CART) |
| 3.11 (Stopping criteria, overfitting) | General ML pedagogy; direct extension of this course's own Lecture 4 |
| Section 4 (Math deep dive) | Shannon 1948; standard calculus/statistics (law of total variance) |
| Section 5 (Diagrams) | Direct analysis of the lecture's own 15 slides (this book's own primary contribution) |
| Section 6 (Worked examples) | Constructed and numerically verified for this book (Python-checked against the lecture's own raw 14-row and 10-row datasets); Quinlan 1986 / Mitchell 1997 for the classic dataset structure |

---

*End of chapter. Cross-reference: this document is designed to sit alongside `ML_Concept_Book.md` and `LM_Transformers_Concept_Book.md` as the Lecture 10 companion — notation, callout conventions, and per-concept structure match both so all three can be studied as one continuous course.*
