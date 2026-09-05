# 🧠 Language Modeling & The Mathematics Behind Transformers
### CSE 4621 · Islamic University of Technology · Companion to Lecture 9 & the "Maths Behind Transformers" Deck

> **What this book is.** A self-contained companion to two source decks — **Lecture 9: Language Modeling** (19 slides, lecturer Ishmam Tashdeed) and **Maths Behind Transformers** (14 slides, "ML Men Group," same lecturer) — expanded with derivations, worked numerical examples, and connections to the rest of CSE 4621. Both original decks are visual and terse: they show a diagram or a formula and trust you to already understand it. This book does the opposite — it never shows you a diagram without explaining every arrow, and never writes a formula without deriving where it comes from. If you read only this document, you should be able to walk into an exam on Language Modeling / Transformers and outperform someone who only memorized the slides.

---

## How to use this book

This book follows the same per-concept rhythm as your main `ML_Concept_Book.md`, extended with a few extra lenses the source material specifically needs (this material is notation- and diagram-heavy, and the slides skip almost all derivations):

1. **📐 Formal Definition** — the precise statement.
2. **🗣️ Layman's Explanation** — the same idea in plain words.
3. **🎯 Why This Concept Exists** — the problem it was invented to solve.
4. **🧠 Intuition** — the mental picture to hold onto under exam pressure.
5. **🧮 Mathematical Explanation** — every variable named, every step shown.
6. **🧪 Worked Numerical Example** — hand-computable arithmetic, verified to the 4th decimal.
7. **🌍 Practical Example** — where this shows up outside the slide.
8. **⚠️ Common Misconceptions**
9. **🎓 Exam Tips**

Recurring callouts (same convention as the main book):

> [!info] **Why this matters**

> [!tip] **Memory trick**

> [!warning] **Exam trap**

> [!danger] **Course/slide discrepancy** — flagged wherever the slide's citation or labelling drifts from the standard convention.

> [!example] **Worked example**

---

## 📚 Table of Contents

1. [Executive Summary](#1-executive-summary)
2. [Learning Objectives](#2-learning-objectives)
3. [Core Concepts](#3-core-concepts)
   - [3.1 Language as Data](#31-language-as-data)
   - [3.2 The Language Modeling Task](#32-the-language-modeling-task)
   - [3.3 Representing Words — One-Hot Encoding and Its Failures](#33-representing-words--one-hot-encoding-and-its-failures)
   - [3.4 Representing Words — Dense Embeddings and Word2Vec](#34-representing-words--dense-embeddings-and-word2vec)
   - [3.5 Distributional Semantics & Self-Supervised Learning](#35-distributional-semantics--self-supervised-learning)
   - [3.6 Recurrent Neural Networks (RNNs)](#36-recurrent-neural-networks-rnns)
   - [3.7 Backpropagation Through Time (BPTT)](#37-backpropagation-through-time-bptt)
   - [3.8 Vanishing and Exploding Gradients](#38-vanishing-and-exploding-gradients)
   - [3.9 Long Short-Term Memory (LSTM)](#39-long-short-term-memory-lstm)
   - [3.10 GRUs — the syllabus gap, filled in](#310-grus--the-syllabus-gap-filled-in)
   - [3.11 The Sequence-to-Sequence Bottleneck Problem](#311-the-sequence-to-sequence-bottleneck-problem)
   - [3.12 The Attention Mechanism](#312-the-attention-mechanism)
   - [3.13 Self-Attention & Scaled Dot-Product Attention](#313-self-attention--scaled-dot-product-attention)
   - [3.14 Multi-Head Attention](#314-multi-head-attention)
   - [3.15 Positional Encoding](#315-positional-encoding)
   - [3.16 The Transformer Architecture](#316-the-transformer-architecture)
   - [3.17 Transformers Beyond NLP — the other syllabus gap](#317-transformers-beyond-nlp--the-other-syllabus-gap)
4. [Mathematical Foundations Deep Dive](#4-mathematical-foundations-deep-dive)
5. [Architecture & Diagram Explanations](#5-architecture--diagram-explanations)
6. [Worked Examples](#6-worked-examples)
7. [Concept Connections — The Big Picture](#7-concept-connections--the-big-picture)
8. [Exam Preparation](#8-exam-preparation)
9. [Practice Questions with Full Solutions](#9-practice-questions-with-full-solutions)
10. [References](#10-references)

---

# 1. Executive Summary

Lecture 9 and the Maths Behind Transformers deck together tell **one continuous story**: *how do you get a computer to handle a sequence of words, when the two obvious ideas — treat it like a fixed-size vector, or slide a fixed window over it — both fail?*

The story has five acts:

1. **The representation problem.** Text isn't fixed-size like an image, and words in isolation (one-hot vectors) carry no meaning. Act 1 replaces one-hot vectors with **learned, dense word embeddings** (Word2Vec), using the idea that *a word is defined by the company it keeps* (distributional semantics).
2. **The sequence problem.** Once words are vectors, how do you process a variable-length sequence of them? Act 2 introduces the **Recurrent Neural Network (RNN)**: one set of weights, reused at every time step, carrying a **hidden state** forward as a compressed memory of everything seen so far.
3. **The memory problem.** Plain RNNs forget. Backpropagating through many time steps multiplies the same Jacobian over and over, and that product either **vanishes** (forgetting) or **explodes** (diverges). Act 3 fixes this with the **LSTM**, which replaces repeated multiplication with an **additive, gated cell state** — a "conveyor belt" that lets gradients flow unchanged across time.
4. **The bottleneck problem.** Even LSTMs, when used in an encoder-decoder (sequence-to-sequence) setup, must squeeze an *entire* input sentence into **one fixed-size vector**. Long sentences lose information — translation quality degrades sharply as sentences get longer. Act 4 introduces **attention**: instead of one summary vector, let the decoder look back at *every* encoder state and decide, per output word, which input words matter most.
5. **The parallelism problem.** Attention fixed accuracy, but RNNs are still sequential — you cannot compute $h_t$ before $h_{t-1}$, so training cannot be parallelized across time. Act 5 is the **Transformer** (*Attention Is All You Need*, Vaswani et al., 2017): throw away recurrence entirely and build a model out of **self-attention** alone, restoring position information with a hand-crafted **positional encoding**, and stabilizing training with **multi-head attention**, residual connections, and layer normalization.

Every later architecture you will hear about — BERT, GPT, T5, and ultimately today's LLMs — is a variation on Act 5. This is why the course places this lecture at the very end: it is the payoff for everything before it (linear algebra for the matrix projections, probability for the language-modeling objective, neural networks for the encoder/decoder blocks, regularization and evaluation metrics for training them well).

> [!info] **Why this matters**
> If you remember nothing else from this chapter, remember the five-act structure above. Almost every exam question is really asking "why did Act $n$ fail, motivating Act $n+1$?"

---

# 2. Learning Objectives

By the end of this chapter you should be able to:

1. Explain why fixed-size representations (used for images) fail for text, and state the language modeling objective $P(w_t \mid w_1, \dots, w_{t-1})$ using the chain rule of probability.
2. Explain the three failures of one-hot encoding (dimensionality, no similarity, no generalization) and how dense embeddings fix each one.
3. Derive and explain the Skip-gram and CBOW training objectives, and articulate the distributional hypothesis ("a word is known by the company it keeps") as the mechanism that makes self-supervised embedding learning work.
4. Write the RNN recurrence $h_t = f(W_{hh}h_{t-1} + W_{xh}x_t + b_h)$ from memory, explain weight sharing across time, and read one-to-one / one-to-many / many-to-one / many-to-many RNN diagrams.
5. Explain Backpropagation Through Time (BPTT) and derive, at least qualitatively, why repeated multiplication by the same Jacobian causes vanishing/exploding gradients.
6. Write all six LSTM equations (forget, input, candidate, cell-state update, output, hidden state) from memory and explain *why* the additive cell-state update solves vanishing gradients where plain RNNs cannot.
7. Explain the sequence-to-sequence bottleneck problem quantitatively (why BLEU score falls as sentence length grows) and state attention as its fix.
8. Compute self-attention **by hand** on a toy example: build $Q$, $K$, $V$ from an embedding matrix and per-head weight matrices, compute scaled dot-product scores, apply softmax, and form the weighted output.
9. Explain why attention scores are divided by $\sqrt{d_k}$ (the variance argument) and why multiple heads are used instead of one large head.
10. Derive the sinusoidal positional encoding formula, compute it numerically for small $d_{model}$, and explain why sinusoids (rather than learned or integer positions) were chosen.
11. Draw and label the full encoder-decoder Transformer architecture diagram from *Attention Is All You Need*, including masked self-attention, encoder-decoder cross-attention, residual connections, and Add & Norm blocks.
12. Place every concept above on a single timeline: N-gram models → neural language models → word embeddings → RNN → LSTM → seq2seq + attention → self-attention → Transformer → modern LLMs.

---

# 3. Core Concepts

## 3.1 Language as Data

**Slide reference:** Lecture 9, pp. 3–4.

### 📐 Formal Definition
Text is a **variable-length sequence of discrete tokens** drawn from a finite vocabulary, where the joint meaning of the sequence is not decomposable into independent, position-wise meanings of its parts — i.e., the semantics of token $w_i$ depends on its context $w_{<i}$ and $w_{>i}$.

### 🗣️ Layman's Explanation
An image is always the same shape — a $224\times224\times3$ grid is a $224\times224\times3$ grid whether it's a cat or a car. A sentence has no such fixed shape: "I love ML" is 3 words, "I really, really love machine learning" is 6. You cannot just reshape a sentence into a fixed-length vector the way you reshape an image into a tensor.

### 🎯 Why This Concept Exists
This slide exists purely to motivate *why the rest of the lecture is necessary*. Every technique that follows (embeddings, RNNs, attention, Transformers) is a direct engineering response to one of the three specific failures named on this slide:

| Failure named on the slide | Concept that fixes it |
|---|---|
| Images have fixed $H\times W\times C$ shape; sentences have variable length | RNNs (Sec 3.6) process one token at a time, so the *architecture* doesn't care how long the sequence is |
| "The meaning of a word depends on context" (*"I never said Messi cheated"*) | Attention / self-attention (Sec 3.12–3.13) build **context-dependent** representations |
| Convolutional sliding windows have a fixed receptive field and can't capture arbitrarily long-range dependencies | Self-attention connects **every** token to **every** other token in a single step, regardless of distance |

### 🧠 Intuition
The famous slide example is the sentence *"I never said Messi cheated."* Depending on which word you stress, the sentence has (at least) five different meanings ("I never said it — someone else did"; "I never said it — I only implied it"; "I never said Messi specifically cheated — someone else did"; etc.). A model that reads word-by-word without letting later or earlier words modulate each token's representation cannot capture this — it needs some mechanism for tokens to influence each other's meaning. That mechanism is exactly what Sections 3.6–3.16 build, piece by piece.

### ⚠️ Common Misconceptions
- **"We could just pad every sentence to the same length and treat it like an image."** Padding solves the *shape* problem but not the *context-dependence* problem — a CNN or MLP applied to padded one-hot vectors still can't let word meanings interact across arbitrary distances.
- **"A big enough convolutional receptive field would fix long-range dependencies."** In principle stacking enough conv layers *can* grow the receptive field, but the required depth grows with sequence length, and gradients must still flow through many layers — the same underlying difficulty resurfaces (this is precisely why later architectures like WaveNet needed dilated convolutions, and even those lose to attention on very long contexts).

### 🎓 Exam Tips
> [!warning] **Exam trap**
> If asked "why can't we use a standard feedforward network / CNN for language modeling," do not just say "sentences are different lengths." That is necessary but incomplete — you must also mention the **context-dependence of word meaning** and the **long-range dependency** limitation of fixed receptive fields. Professor Tashdeed's slide names *three* separate failures; a complete answer names all three.

---

## 3.2 The Language Modeling Task

**Slide reference:** Lecture 9, p. 4.

### 📐 Formal Definition
Given a sequence of tokens $w_1, w_2, \dots, w_{t-1}$, a **language model** defines a probability distribution over the next token:
$$P(w_t \mid w_1, w_2, \dots, w_{t-1})$$
The probability of an entire sentence $S = (w_1, \dots, w_T)$ is obtained via the **chain rule of probability**:
$$P(S) = P(w_1)\cdot P(w_2\mid w_1)\cdot P(w_3 \mid w_1, w_2) \cdots P(w_T \mid w_1,\dots,w_{T-1}) = \prod_{t=1}^{T} P(w_t \mid w_{<t})$$

### 🗣️ Layman's Explanation
A language model is an extremely well-read autocomplete. Given everything typed so far, it assigns a probability to every possible next word. "The cat sat on the ___" → *mat* gets a high probability, *quantum* gets a probability near zero.

### 🎯 Why This Concept Exists
Framing "understanding language" as "predicting the next word" is a deliberate trick: next-word prediction is a **self-supervised** task — the label (the actual next word) is *free*, hiding in any raw text corpus with no human annotation required. This single reframing is what unlocked training on the entire internet, and it is the direct ancestor of how every modern LLM (GPT-family, etc.) is pretrained.

### 🧠 Intuition
Slide 4 gives three examples that quietly teach three different *kinds* of knowledge a language model must encode:
- *"The cat sat on the ___" → mat* (high probability), *quantum* (near zero) — **syntactic/semantic plausibility**.
- *"The capital of Bangladesh is ___" → Dhaka* — **factual/world knowledge**, memorized from training text.
- *"2 + 2 = ___" → 4* — **simple symbolic/arithmetic reasoning**, learned purely as a text pattern, not as an execution of arithmetic.

The diagram on slide 4 (sentence $S=$ "Where are we going") labels "Where are we" as **context** (green) and "going" as the **word being predicted** (magenta), and gives:
$$P(S) = P(\text{Where}) \times P(\text{are}\mid\text{Where}) \times P(\text{we}\mid\text{Where, are}) \times P(\text{going}\mid\text{Where, are, we})$$
This is a direct instance of the chain rule above with $T=4$.

### 🧮 Mathematical Explanation
The chain rule decomposition is *exact* (not an approximation) — it follows directly from the definition of conditional probability, applied repeatedly:
$$P(w_1, w_2) = P(w_1)P(w_2\mid w_1)$$
$$P(w_1,w_2,w_3) = P(w_1,w_2)\cdot P(w_3\mid w_1,w_2) = P(w_1)P(w_2\mid w_1)P(w_3\mid w_1,w_2)$$
and so on by induction. What *is* an approximation is how a specific model chooses to estimate each conditional factor — an **n-gram model** truncates the context to the last $n-1$ words (a Markov assumption), while an **RNN/Transformer language model** conditions on the *entire* preceding context (in principle, unboundedly long for RNNs; up to the context-window length for Transformers).

### 🧪 Worked Numerical Example
See [Worked Example 1](#worked-example-1--chain-rule-probability-of-a-sentence) in Section 6 for a fully numeric version of this decomposition.

### 🌍 Practical Example
Every time your phone's keyboard suggests the next word, or ChatGPT/Claude generates text one token at a time, it is sampling from $P(w_t \mid w_{<t})$ — repeatedly, feeding each sampled word back in as context for the next prediction (**autoregressive generation**).

### ⚠️ Common Misconceptions
- **"The model computes $P(S)$ directly."** It does not — it only ever computes *one conditional distribution at a time* ($P(w_t\mid w_{<t})$); $P(S)$ is a downstream product used mainly for evaluation (e.g., computing perplexity) or for scoring complete candidate sentences, not something the model outputs directly during generation.
- **Confusing "predicts the next word" with "understands arithmetic."** The $2+2=4$ example is often misread as evidence of reasoning; it is evidence of an extremely well-fit *text pattern* — this distinction becomes exam-relevant when discussing LLM limitations.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Chain rule = "peel the sentence like an onion, left to right": $P(S) = P(w_1)\times P(w_2 \mid \text{everything before it}) \times \dots$


---

## 3.3 Representing Words — One-Hot Encoding and Its Failures

**Slide reference:** Lecture 9, p. 5.

### 📐 Formal Definition
Given a vocabulary of size $V$, word $w_i$ is represented as a **one-hot vector** $e_i \in \{0,1\}^V$: all zeros, except a single $1$ at index $i$.

### 🗣️ Layman's Explanation
Give every word in the dictionary its own numbered slot. To represent word #3, write down $V$ zeros and change the 3rd one to a 1.

### 🎯 Why This Concept Exists
It is the *simplest possible* way to turn a categorical symbol (a word) into a vector a model can consume — and its simplicity is exactly why it is taught first, immediately before showing why it must be replaced.

### 🧮 Mathematical Explanation & Worked Numerical Example
The slide's own toy vocabulary $\{$the, cat, sat, on, mat$\}$ ($V=5$) gives the one-hot matrix:

| word | dim 1 | dim 2 | dim 3 | dim 4 | dim 5 |
|---|---|---|---|---|---|
| the | **1** | 0 | 0 | 0 | 0 |
| cat | 0 | **1** | 0 | 0 | 0 |
| sat | 0 | 0 | **1** | 0 | 0 |
| on  | 0 | 0 | 0 | **1** | 0 |
| mat | 0 | 0 | 0 | 0 | **1** |

Three concrete failures fall out of this matrix:

1. **Dimensionality → large weights.** With a realistic vocabulary ($V\sim10^5$–$10^6$), every input/output layer touching a word needs a $V$-wide row or column of weights. This is expensive in both memory and the amount of data needed to train each rarely-seen weight.
2. **No similarity.** For any two distinct one-hot vectors $e_i, e_j$ ($i\neq j$): $\;e_i \cdot e_j = 0$, and since $\lVert e_i\rVert = \lVert e_j\rVert = 1$, cosine similarity is
$$\cos(e_i, e_j) = \frac{e_i\cdot e_j}{\lVert e_i\rVert \lVert e_j\rVert} = \frac{0}{1} = 0$$
"cat" and "dog" are exactly as dissimilar as "cat" and "refrigerator." The slide's own table shows *the·cat = 0*, *the·sat = 0*, …, *on·mat = 0* — **every pair, without exception**, because one-hot vectors are mutually orthogonal by construction. In the slide's own 5-word toy example, each row is $80\%$ zeros (only 1 non-zero entry out of 5); for a realistic vocabulary of hundreds of thousands of words, this becomes **extreme sparsity**: still only 1 non-zero entry per row, now out of hundreds of thousands.
3. **No generalization → all words are treated as independent.** If a model learns something useful about "cat" (e.g., from "the cat sat on the mat"), that knowledge does not transfer at all to "kitten" or "dog" — there is no shared structure between their vectors for the model to exploit.

### 🌍 Practical Example
One-hot encoding is still perfectly fine for **small, unordered categorical variables with no inherent similarity structure** (e.g., a "color" feature with 4 possible values in a tabular ML dataset) — the failures above are specifically about *language*, where vocabulary size is huge and words genuinely do have graded similarity.

### ⚠️ Common Misconceptions
- **"One-hot vectors are bad because they're big."** Size is only one of three named problems — an exam answer that mentions only dimensionality is incomplete.
- **Thinking one-hot vectors have *some* similarity structure by their layout (e.g., adjacent indices are "more similar").** They do not — the assignment of words to indices is arbitrary (e.g., alphabetical, or by first appearance), so index adjacency carries no semantic meaning.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> A favorite distractor: "one-hot encoding fails because it can't represent out-of-vocabulary words." This is *true* but is **not one of the three failures the slide names** (dimensionality, no similarity, no generalization). If the question explicitly says "per the lecture," answer with the three named failures, not OOV handling.

---

## 3.4 Representing Words — Dense Embeddings and Word2Vec

**Slide reference:** Lecture 9, pp. 6–7.

### 📐 Formal Definition
Replace each word with a **dense, low-dimensional, continuous vector** $v_i \in \mathbb{R}^d$ (typically $d \in [50, 1000]$, versus $V$ for one-hot), learned from data such that geometric relationships between vectors (distance, direction) encode semantic relationships between words.

### 🗣️ Layman's Explanation
Instead of giving every word its own isolated numbered slot, place every word at a *coordinate* in some abstract space, chosen so that words with similar meanings end up near each other.

### 🎯 Why This Concept Exists
It directly repairs all three one-hot failures at once: $d \ll V$ (dimensionality), nearby vectors have high cosine similarity (similarity), and because the vector *space* has continuous structure, a model can interpolate/generalize between words that are geometrically close even if it never saw one of them very often.

### 🧠 Intuition
Slide 6's toy 2D plot places `kitten` (1.6, 1.9) near `cat` (1.2, 1.6) and `dog` (0.6, 1.0) — all clustered together and far from `physics` (−1.8, −1.2) and `algebra` (−0.8, −1.7). Distances are now **non-zero and meaningful**: $d(\text{cat}, \text{kitten})$ is small, $d(\text{cat}, \text{algebra})$ is large. This is "what we want to learn" — but the slide poses the obvious question: **"But how?"**

### 🧮 Mathematical Explanation — Word2Vec
The slide's answer: initialize every word to a **random** vector (e.g., $v_{\text{cat}} = [0.13, -0.44, 0.91,\dots]$), then force the model to get good at a **fake supervised task** built out of raw, unlabeled text, so that gradient descent is forced to organize the vectors usefully as a side effect. Word2Vec (Mikolov et al., 2013) proposes two such fake tasks:

| Architecture | Task | Given | Predict |
|---|---|---|---|
| **Skip-gram** | given the center word, predict surrounding words | center word $w_t$ | context words $w_{t-c},\dots,w_{t-1},w_{t+1},\dots,w_{t+c}$ |
| **CBOW** (Continuous Bag of Words) | given the surrounding words, predict the center word | context words | center word $w_t$ |

Formally, Skip-gram maximizes, over a corpus of $T$ words with window size $c$:
$$\mathcal{L} = \sum_{t=1}^{T}\sum_{\substack{-c\le j \le c \\ j\neq 0}} \log P(w_{t+j} \mid w_t), \qquad P(w_O\mid w_I) = \frac{\exp(v'_{w_O}{}^{\top} v_{w_I})}{\sum_{w=1}^{V}\exp(v'_w{}^{\top}v_{w_I})}$$
where $v_w$ is $w$'s "input" (center-word) embedding and $v'_w$ is its "output" (context-word) embedding — the softmax over the *entire* vocabulary $V$ is exactly why in practice Word2Vec uses **negative sampling** or a **hierarchical softmax** to make this tractable (a detail beyond the slide's scope but standard exam-adjacent knowledge).

Once training converges, the **input embedding matrix** rows are taken as the final word vectors — the fake task is discarded; only the learned representations are kept.

### 🧪 Worked Numerical Example
The famous analogy check: $v_{\text{king}} - v_{\text{man}} + v_{\text{woman}} \approx v_{\text{queen}}$ — slide 7's 3D "Royalty / Gender / Age" toy plot shows the vector from `man→king` and `woman→queen` are nearly parallel and equal in length, i.e., *"add the same 'became royal' direction to both."* See also [Worked Example 6](#worked-example-6--word-analogy-by-vector-arithmetic) for arithmetic with concrete toy numbers.

### 🌍 Practical Example
Pretrained Word2Vec / GloVe vectors were, for years (2013–2018), the standard first layer of nearly every NLP model — sentiment classifiers, named-entity recognizers, and machine translation systems all started by looking up pretrained embeddings before doing anything else.

### ⚠️ Common Misconceptions
- **"Skip-gram and CBOW are different models with different embeddings."** They're two *training objectives* for the same underlying idea (predict word-in-context from raw text); the slide presents them as symmetric mirror-image tasks, not competing architectures.
- **"The model is trying to actually get good at predicting context words."** It is not — the prediction task is a scaffold. *Nobody cares about Skip-gram's test accuracy.* The only useful byproduct is the embedding matrix built to make that prediction possible.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> **C**BOW = **C**ontext → center (many inputs, one output). Skip-gram = one input **skip**s out to many context outputs.

> [!warning] **Exam trap**
> "Word2Vec embeddings are contextual — the vector for 'apple' changes depending on the sentence." **False**, and this is one of the most important traps in this whole chapter: Word2Vec (and GloVe) produce **one fixed, static vector per word type**, regardless of context. "Apple" the fruit and "Apple" the company get the *same* vector. This exact limitation is the entire motivation for the Maths-Behind-Transformers deck's "apple" example (Section 3.12) and for attention/self-attention more broadly — see the danger callout in Section 3.12.

---

## 3.5 Distributional Semantics & Self-Supervised Learning

**Slide reference:** Lecture 9, p. 8.

### 📐 Formal Definition
The **distributional hypothesis**: words that occur in similar linguistic contexts tend to have similar meanings. Quoted directly on the slide: *"You shall know a word by the company it keeps"* — J. R. Firth, 1957.

### 🗣️ Layman's Explanation
You can guess what an unfamiliar word means just from the words around it. If you repeatedly see *"I drank a glass of ___"* filled in with *milk, juice, water*, and one day see it filled with an unfamiliar word, you'd guess that word is also a drinkable liquid — without anyone ever defining it for you.

### 🎯 Why This Concept Exists
This is the **theoretical justification** for why the Word2Vec trick (Section 3.4) works at all — it explains *why* gradient descent on a next/context-word prediction task ends up organizing embeddings by meaning, rather than producing an arbitrary or meaningless arrangement.

### 🧠 Intuition
During training, whenever two words $w_i, w_j$ **co-occur** frequently (e.g., "cat" and "milk" both appear near "drinks"), gradient descent — trying to make the correct context word likelier — repeatedly nudges their embeddings **toward each other**. Over millions of sentences, words that share contexts converge to nearby points in embedding space purely as an emergent consequence of the optimization, with no explicit "similarity" objective ever written down.

### 🧮 Mathematical Explanation
This is why the slide names the training style **self-supervised learning**: *"Creating labeled data from completely unlabeled data."* The "label" for Skip-gram — the correct context word — is not human-annotated; it is mechanically extracted from the position of words in raw text. This matters far beyond Word2Vec: it is the exact same principle behind pretraining every modern language model — next-token prediction (Section 3.2) is self-supervised in precisely this sense.

### 🌍 Practical Example
Self-supervised pretraining (masked-language-modeling for BERT, next-token prediction for GPT) followed by task-specific fine-tuning is the dominant paradigm in all of modern NLP — Firth's 1957 one-liner is, in a very real sense, the theoretical seed of the entire field.

### ⚠️ Common Misconceptions
- **"Self-supervised = unsupervised."** They are related but distinct: unsupervised learning (e.g., clustering) has no labels at all; self-supervised learning *manufactures* labels from the structure of the unlabeled data itself, then trains with completely ordinary supervised machinery (cross-entropy loss, gradient descent).

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Firth's quote *is* the exam-ready one-liner for "what is distributional semantics" — memorize it verbatim, it is exactly the kind of quotable definition that appears in short-answer questions.


---

## 3.6 Recurrent Neural Networks (RNNs)

**Slide reference:** Lecture 9, pp. 9–10.

### 📐 Formal Definition
A Recurrent Neural Network maintains a **hidden state** $h_t \in \mathbb{R}^n$ updated at every time step by the *same* set of weights:
$$h_t = f(W_{hh}\cdot h_{t-1} + W_{xh}\cdot x_t + b_h), \qquad \hat{y}_t = g(W_{hy}\cdot h_t + b_y)$$
where:

| Symbol | Meaning |
|---|---|
| $h_t$ | hidden state at time $t$ (captures memory of everything seen so far) |
| $x_t$ | input at time $t$ (e.g., the embedding of the current word) |
| $\hat{y}_t$ | output/prediction at time $t$ |
| $W_{hh}$ | hidden-to-hidden ("recurrent") weight matrix |
| $W_{xh}$ | input-to-hidden weight matrix |
| $W_{hy}$ | hidden-to-output weight matrix |
| $b_h, b_y$ | hidden and output bias vectors |
| $f, g$ | activation functions (typically $f=\tanh$, $g=\text{softmax}$) |

Critically: **one set of weights** $\{W_{hh}, W_{xh}, W_{hy}, b_h, b_y\}$ is shared across **all** $T$ time steps.

### 🗣️ Layman's Explanation
Read a sentence one word at a time. After each word, update a running mental summary ("so far, this sentence seems to be about..."). Use the *same* update rule every time, regardless of which word or which position in the sentence you're at.

### 🎯 Why This Concept Exists
It is the natural fix for the "language as data" problem (Section 3.1): since the *same* small set of weights is reapplied at every step, the model handles sequences of **any length** without needing an architecture that changes size. Slide 9 draws an explicit analogy: *"Similar to CNN models sharing filter weights across the image, but for RNNs, it is in the temporal dimension."* Both CNNs and RNNs exploit **weight sharing** — CNNs share a filter across spatial locations, RNNs share the recurrence across time steps. This is the single most useful analogy for connecting Lecture 8 (CNNs) to Lecture 9.

### 🧠 Intuition — reading the diagrams
**Single time step (Slide 9, left panel):** three inputs converge on $h_t$ — the previous hidden state $h_{t-1}$ (via $W_{hh}$), the current input $x_t$ (via $W_{xh}$) — and $h_t$ produces the output $\hat{y}_t$ (via $W_{hy}$).

**Unrolled across time (Slide 10):** the *same node* is drawn repeatedly, once per time step, showing $h_0 \to h_1 \to h_2 \to \dots \to h_T$, with $x_1=$"The", $x_2=$"cat", $x_3=$"sat", etc. feeding in at each step, and every arrow labeled $W_{hh}$, $W_{xh}$, or $W_{hy}$ using the *exact same matrix* at every step (the slide explicitly boxes this: "Shared across all time steps").

**The five RNN "shapes" (Slide 9, bottom-right):**

| Shape | Example use case |
|---|---|
| one-to-one | plain feedforward classification (not really recurrent) |
| one-to-many | image captioning (one image → sequence of words) |
| many-to-one | sentiment classification (sequence of words → one label) |
| many-to-many (aligned) | video frame labeling, POS tagging (input/output sequences same length, produced together) |
| many-to-many (encoder-decoder) | machine translation (read entire input, then generate output sequence) |

> [!warning] **Exam trap**
> Language modeling itself is a **many-to-many (aligned)** task at training time — every input word produces a prediction for the *next* word at every step — but is used **autoregressively** at generation time (feed each output back in as the next input). Don't confuse "the shape of training" with "the procedure used at inference."

### 🧮 Mathematical Explanation
Two separate matrices are needed ($W_{xh}$ and $W_{hh}$) because they act on vectors of potentially different dimensions and play different roles: $W_{xh}$ maps the current input's embedding dimension into the hidden dimension; $W_{hh}$ maps the hidden dimension into itself (it must be a **square** matrix, $n \times n$, for the recurrence to be well-typed — the hidden state must have the same dimensionality before and after each update, since it feeds into itself at the next step).

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Three matrices, one letter-pattern: $W_{\text{FROM-TO}}$. $W_{xh}$: input→hidden. $W_{hh}$: hidden→hidden. $W_{hy}$: hidden→output.

---

## 3.7 Backpropagation Through Time (BPTT)

**Slide reference:** Lecture 9, p. 11 (diagram only — no equations on the slide; this section supplies them, since the slide explicitly shows the mechanism but never writes it down).

### 📐 Formal Definition
**BPTT** is ordinary backpropagation applied to the RNN's **unrolled computational graph**: treat the $T$-step recurrence as a $T$-layer feedforward network (with tied/shared weights across "layers"), compute the loss at every step, and propagate gradients backward through the entire unrolled chain, accumulating gradients for the shared weights at every step they were used.

### 🗣️ Layman's Explanation
Since the same weights are reused at every time step, "learning" from a mistake made while processing word 10 must also flow all the way back to influence how word 1 was processed — because word 1 used the *very same* weights. Slide 11 shows this directly: forward pass (top) produces a loss $L_t$ at every step; backward pass (bottom) shows the *error flowing backward through the hidden states*, all the way to $h_0$.

### 🎯 Why This Concept Exists
Without BPTT, you could only train the *last* time step's contribution to the loss — but the recurrent weights were used at every step, so ignoring earlier steps' gradients would systematically underestimate (or corrupt) the true gradient with respect to the shared weights.

### 🧮 Mathematical Explanation
For a total loss $L = \sum_{t=1}^{T} L_t$, the gradient with respect to the shared recurrent weight $W_{hh}$ must sum contributions from **every** time step, because $W_{hh}$ was reused at every step:
$$\frac{\partial L}{\partial W_{hh}} = \sum_{t=1}^{T} \frac{\partial L_t}{\partial W_{hh}}$$
Each term $\frac{\partial L_t}{\partial W_{hh}}$ itself requires the chain rule back through **every earlier hidden state** $h_t, h_{t-1}, \dots, h_1$, because $h_t$ depends on $h_{t-1}$ which depends on $h_{t-2}$, and so on:
$$\frac{\partial L_t}{\partial W_{hh}} = \sum_{k=1}^{t} \frac{\partial L_t}{\partial h_t}\left(\prod_{i=k+1}^{t}\frac{\partial h_i}{\partial h_{i-1}}\right)\frac{\partial h_k}{\partial W_{hh}}$$
The product $\prod_{i=k+1}^{t}\frac{\partial h_i}{\partial h_{i-1}}$ — a chain of Jacobians, one per time step between $k$ and $t$ — is precisely where Section 3.8's vanishing/exploding gradient problem originates, and is exactly what slide 11's caption means by *"BPTT 'unrolls' the RNN over time, then applies regular backpropagation on this unrolled chain."*

### 🌍 Practical Example
In practice, BPTT is almost always **truncated** (TBPTT): gradients are only propagated back a fixed number of steps (say, 20–100), both to bound compute/memory and because — as Section 3.8 shows — gradients beyond ~20 steps are numerically negligible anyway for plain RNNs.

### ⚠️ Common Misconceptions
- **"BPTT is a different algorithm from backpropagation."** It is not a different *algorithm* — it's the same chain-rule backpropagation, applied to a computational graph that happens to be the RNN unrolled across time, with the added bookkeeping that gradients for the *same* shared weight must be **summed** across all the time steps that used it.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> If asked to state $\dfrac{\partial L}{\partial W_{hh}}$, a common error is to forget the outer sum over $t$ — students often derive the gradient for a *single* time step's loss and stop, forgetting that $W_{hh}$ contributed to *every* $L_t$, not just the last one.

---

## 3.8 Vanishing and Exploding Gradients

**Slide reference:** Lecture 9, p. 12.

### 📐 Formal Definition
**Vanishing gradients**: gradients shrink exponentially as they are backpropagated across many time steps, so early time steps receive an effectively-zero learning signal. **Exploding gradients**: gradients grow exponentially across time steps, producing numerical overflow (`NaN`) and divergent training.

### 🗣️ Layman's Explanation
Per the slide: *"Gradients shrink exponentially → Early layers learn nothing → RNN forgets after 10~20 steps."* And the mirror-image failure: *"Gradients grow exponentially → NaN parameters → Training diverges."* Either way, **plain RNNs cannot feasibly remember information from more than roughly 20 steps in the past** — this exact number is stated on the slide and is a high-yield fact.

### 🎯 Why This Concept Exists
This is the direct, mathematically inevitable consequence of the repeated-Jacobian product derived in Section 3.7 — it exists as a slide because it is the **specific failure that LSTMs (Section 3.9) were invented to fix**.

### 🧮 Mathematical Explanation
Consider the scalar simplification of the Jacobian chain from Section 3.7: $\dfrac{\partial h_i}{\partial h_{i-1}} = W_{hh}^{\top}\,\text{diag}\big(f'(z_i)\big)$, where $z_i = W_{hh}h_{i-1}+W_{xh}x_i+b_h$. The product over $t-k$ steps has norm bounded (roughly) by:
$$\left\lVert\prod_{i=k+1}^{t}\frac{\partial h_i}{\partial h_{i-1}}\right\rVert \;\lesssim\; \big(\lVert W_{hh}\rVert \cdot \max_z\,|f'(z)|\big)^{\,t-k}$$
This is a number raised to the power $(t-k)$ — i.e., **exponential in the number of steps being backpropagated through**:

- If $\lVert W_{hh}\rVert \cdot \max|f'(z)| < 1$: the product **shrinks exponentially** toward 0 → **vanishing gradients**.
- If $\lVert W_{hh}\rVert \cdot \max|f'(z)| > 1$: the product **grows exponentially** → **exploding gradients**.

Two facts make vanishing the "default" failure mode for $\tanh$/sigmoid RNNs specifically:
1. $\max_z |\tanh'(z)| = 1$ (attained only at $z=0$; it decays elsewhere), and $\max_z|\sigma'(z)| = 0.25$ (recall this exact number from the course's Logistic Regression chapter — the same sigmoid-derivative bound reappears here).
2. Weight matrices are typically initialized with $\lVert W_{hh}\rVert$ close to 1, so the product is very sensitive to whether $\max|f'(z)|$ pushes it just above or just below 1 — and because $|f'(z)|\le 1$ always for these activations, the *typical* regime leans toward shrinkage, especially since $z=0$ (where $\tanh'=1$ exactly) is a measure-zero condition that real activations rarely sit exactly at.

> [!danger] **Course-consistent flag, not a new discrepancy**
> Note the reappearance of the sigmoid-derivative maximum $0.25$ from your Logistic Regression chapter (`ML_Concept_Book.md`) — this is the *same* fact showing up in a new context: it is precisely why sigmoid-gated architectures (including LSTM gates, Section 3.9) are still vulnerable to *saturation* even though the LSTM's cell-state pathway itself avoids the multiplicative vanishing problem.

### 🧪 Worked Numerical Example
Reusing the exact value from your memory bank: $0.25^{20} \approx 9.1\times10^{-13}$. If $\max|f'(z)|=0.25$ (a saturated sigmoid gate) and $\lVert W_{hh}\rVert \approx 1$, then after just 20 steps the gradient has shrunk by a factor of $\sim9\times10^{-13}$ — for any practical purpose, **zero**. This is the arithmetic justification for the slide's "~20 steps" claim.

### 🌍 Practical Example
This is precisely why early neural machine translation systems (pre-attention, pre-Transformer) struggled badly on long sentences — the encoder RNN's hidden state at the end of a 40-word sentence had, for all practical purposes, forgotten the first 10–15 words.

### ⚠️ Common Misconceptions
- **"Exploding gradients are the more common/dangerous problem."** In practice, exploding gradients have a cheap, effective fix (**gradient clipping** — rescale the gradient if its norm exceeds a threshold). Vanishing gradients have no equally simple fix within the plain-RNN architecture — this asymmetry is exactly why an entirely new architecture (LSTM) was needed, rather than just a training trick.
- **"Vanishing gradients mean the loss stops decreasing."** More precisely, it means **specific parameters** (those needed to route information across long time gaps) stop receiving a useful gradient signal — the *overall* loss can still decrease, driven by short-range dependencies, while long-range dependencies remain unlearned.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> "RNNs can't handle long sequences because of limited memory (hardware)." **No** — the limitation here is a **gradient/optimization** problem (the learning signal vanishes), not a hardware/capacity problem. The hidden state $h_t$ has plenty of numerical capacity to store information; it's that gradient descent has no way to *train* the weights to actually use that capacity for long-range information.


---

## 3.9 Long Short-Term Memory (LSTM)

**Slide reference:** Lecture 9, pp. 13–14.

### 📐 Formal Definition
An LSTM cell maintains **two** state vectors — the hidden state $h_t$ (as in a plain RNN) **and** a **cell state** $c_t$ — updated via three multiplicative **gates** (forget, input, output) and one candidate-value computation:

$$
\begin{aligned}
f_t &= \sigma\big(W_f\cdot[h_{t-1},x_t] + b_f\big) &&\text{(1. Forget gate)}\\
i_t &= \sigma\big(W_i\cdot[h_{t-1},x_t] + b_i\big) &&\text{(2. Input gate)}\\
\tilde{c}_t &= \tanh\big(W_c\cdot[h_{t-1},x_t] + b_c\big) &&\text{(3. Candidate cell)}\\
c_t &= f_t \odot c_{t-1} + i_t \odot \tilde{c}_t &&\text{(4. Cell state update)}\\
o_t &= \sigma\big(W_o\cdot[h_{t-1},x_t] + b_o\big) &&\text{(5. Output gate)}\\
h_t &= o_t \odot \tanh(c_t) &&\text{(6. Hidden state)}
\end{aligned}
$$

where $[h_{t-1}, x_t]$ denotes **concatenation**, $\odot$ is **element-wise multiplication**, and $\sigma$/$\tanh$ are applied element-wise.

### 🗣️ Layman's Explanation
Give the RNN a second memory channel — the cell state $c_t$ — that acts like a **conveyor belt**: information can ride along it largely unchanged unless a gate explicitly decides to remove it (forget gate) or add something new (input gate). The hidden state $h_t$ becomes a filtered "read-out" of that conveyor belt (output gate), rather than *being* the memory itself.

### 🎯 Why This Concept Exists
It is the direct architectural fix for Section 3.8's vanishing gradient problem. The key design choice is equation (4): $c_t = f_t\odot c_{t-1} + i_t\odot\tilde{c}_t$ is **additive**, not a matrix multiplication passed through a saturating nonlinearity at every step. Differentiating it:
$$\frac{\partial c_t}{\partial c_{t-1}} = f_t$$
If the forget gate $f_t \approx 1$ (the network has learned "keep remembering this"), gradients flow backward through the cell state **almost unchanged**, across arbitrarily many time steps — no repeated multiplication by a weight matrix and an activation derivative that can each independently shrink the signal. This additive pathway is often called the **Constant Error Carousel (CEC)**.

### 🧠 Intuition — reading the diagram (Slide 13–14)
Four colored boxes sit side-by-side, each taking $[h_{t-1}, x_t]$ as input: **Forget Gate** ($\sigma$), **Input Gate** ($\sigma$), **Candidate Cell** ($\tanh$), **Output Gate** ($\sigma$). Reading left to right along the top "conveyor belt": $c_{t-1}$ enters, gets multiplied ($\times$) by the forget gate's output (deciding what to erase), then has the input-gate-scaled candidate added ($+$) to it, producing $c_t$. Separately, $c_t$ is squashed by $\tanh$ and multiplied by the output gate to produce $h_t$.

| Gate | Question it answers | Activation | Range |
|---|---|---|---|
| Forget ($f_t$) | What should we erase from the old cell state? | sigmoid | $(0,1)$ — 0 = fully forget, 1 = fully keep |
| Input ($i_t$) | How much of the new candidate should we write in? | sigmoid | $(0,1)$ |
| Candidate ($\tilde{c}_t$) | What new information *could* be written? | tanh | $(-1,1)$ |
| Output ($o_t$) | How much of the cell state should we expose as $h_t$? | sigmoid | $(0,1)$ |

> [!info] **Why sigmoid for gates but tanh for candidates?**
> Gates need outputs in $(0,1)$ to act as a "how much" fraction/mask (sigmoid). The candidate value is genuinely new *content*, not a gating fraction, so it uses $\tanh$ (matching the hidden-state activation range and being zero-centered, which tends to help optimization).

### 🌍 Practical Example
LSTMs were the dominant architecture for machine translation, speech recognition, and text generation from roughly 2014–2017, until Transformers (Section 3.16) overtook them — but LSTMs remain useful today for streaming/low-latency sequential tasks where full self-attention's $O(T^2)$ cost is undesirable.

### ⚠️ Common Misconceptions
- **"LSTMs completely solve vanishing gradients."** They substantially *mitigate* it (the additive path can preserve gradients much further than a plain RNN), but do not eliminate it entirely — the gates themselves use sigmoids, which still saturate, and very long sequences (hundreds+ of steps) still degrade.
- **Mixing up $c_t$ and $h_t$.** $c_t$ is the long-term "conveyor belt" memory; $h_t$ is the short-term, filtered output actually exposed to the next layer/output prediction. They are computed from each other but are *not* the same object.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> "**F**orget, **I**nput, **C**andidate, **O**utput" — spells **F-I-C-O**, in the exact top-to-bottom order the internal-calculations box lists them.

> [!warning] **Exam trap**
> A common trap swaps the forget-gate and input-gate roles in the cell-update equation. It is $c_t = f_t\odot c_{t-1} + i_t\odot\tilde{c}_t$ — forget gate multiplies the **old** state, input gate multiplies the **new candidate**. Writing $i_t \odot c_{t-1}$ or $f_t \odot \tilde{c}_t$ is a sign-swap error that changes the entire semantics of the gates.

---

## 3.10 GRUs — the syllabus gap, filled in

**Slide reference:** Lecture 9, p. 2 lists *"LSTMs and GRUs"* as an outline bullet — but **no GRU slide, equations, or diagram appear anywhere in the 19-slide deck.** This is a genuine content gap between the stated learning objectives and the delivered material.

> [!danger] **Slide/syllabus gap**
> The outline promises GRUs; the deck never delivers them. If GRUs appear on your exam, it will be testing whether you sought this out independently (or attended a session not fully captured in these slides) — the following is a compact, self-contained supplement so you are not caught out.

### 📐 Formal Definition
The **Gated Recurrent Unit** (Cho et al., 2014) simplifies the LSTM to **two** gates and **one** state vector (no separate cell state):
$$
\begin{aligned}
z_t &= \sigma(W_z\cdot[h_{t-1},x_t]) &&\text{(update gate)}\\
r_t &= \sigma(W_r\cdot[h_{t-1},x_t]) &&\text{(reset gate)}\\
\tilde{h}_t &= \tanh\big(W\cdot[r_t\odot h_{t-1}, x_t]\big) &&\text{(candidate hidden state)}\\
h_t &= (1-z_t)\odot h_{t-1} + z_t \odot \tilde{h}_t &&\text{(hidden state update)}
\end{aligned}
$$

### 🗣️ Layman's Explanation
A GRU merges the LSTM's forget-and-input gates into a **single update gate** $z_t$ that directly interpolates between "keep the old hidden state" and "write the new candidate" — and merges the cell-state/hidden-state distinction into one vector. The **reset gate** $r_t$ additionally controls how much of the past hidden state is even allowed to influence the *new* candidate computation.

### 🎯 Why This Concept Exists
Fewer parameters and gates than an LSTM (roughly 25% fewer weights for the same hidden size), making GRUs faster to train and sometimes competitive with LSTMs despite the simpler design — a useful practical trade-off when compute or data is limited.

### ⚠️ Common Misconceptions & Exam Tips
> [!warning] **Frequently confused (see Section 8.4 table)**
> Do not confuse the GRU's **update gate** $z_t$ with the LSTM's **input gate** $i_t$ — they play *analogous but not identical* roles: the GRU's $(1-z_t)$ vs. $z_t$ split ties the "keep old" and "write new" decisions together (they must sum to 1), whereas an LSTM's forget gate $f_t$ and input gate $i_t$ are computed **independently** and need not sum to anything in particular.

---

## 3.11 The Sequence-to-Sequence Bottleneck Problem

**Slide reference:** Lecture 9, p. 15.

### 📐 Formal Definition
In an **encoder-decoder (sequence-to-sequence)** architecture, an encoder RNN/LSTM reads the entire input sequence and compresses it into a **single, fixed-size context vector** $c$ (e.g., the encoder's final hidden state); the decoder then generates the output sequence conditioned **only** on this one vector $c$ (plus its own previously generated outputs).

### 🗣️ Layman's Explanation
Read an entire paragraph, then close the book, and try to write a translation of it using only a single sentence-length "gist" you memorized — no matter how long or detailed the original paragraph was, you're only allowed to remember one summary of fixed size.

### 🎯 Why This Concept Exists
This slide exists to make the *failure* vivid, quantitatively, so that attention's fix (Section 3.12) feels necessary rather than merely "an improvement." Slide 15's diagram shows the German translation example — an encoder reading `How are you ? [EOS]` and compressing it into a **512-number context vector**, which alone drives the decoder producing `Wie geht es Ihnen`.

### 🧮 Mathematical Explanation
The core issue is information-theoretic: a fixed-size vector $c\in\mathbb{R}^{512}$ has a **fixed capacity**, but the amount of information in the input sequence **grows** with sentence length. Something must be dropped as sentences get longer, and empirically, the first thing to go is fine-grained information about the *early* parts of a long input — exactly the vanishing-gradient failure mode from Section 3.8, now viewed at the whole-sentence level rather than the per-parameter level.

### 🧪 Worked Numerical Example
Slide 15's own bar chart (BLEU translation quality score vs. sentence length) is a direct empirical demonstration:

| Sentence length | BLEU score |
|---|---|
| 10 words | 92% |
| 20 words | 85% |
| 30 words | 74% |
| 40 words | 58% |
| 50 words | 40% |
| 60 words | 22% |

Translation quality falls almost monotonically and sharply as sentences get longer — a **70-percentage-point drop** from 10 words to 60 words — direct empirical evidence that the fixed-size context vector is losing information, exactly as the slide's caption states: *"Quality degrades dramatically for long sentences — the context vector loses information."*

> [!info] **Why this matters**
> BLEU (BiLingual Evaluation Understudy) — an $n$-gram precision-based machine translation metric — connects this slide directly back to Lecture 7 (Evaluation Metrics). If your exam asks you to justify *why* attention was needed using a quantitative metric, this table is the canonical answer.

### 🌍 Practical Example
This exact problem (and this exact BLEU-vs-length curve) is precisely what motivated Bahdanau et al.'s 2014 paper *"Neural Machine Translation by Jointly Learning to Align and Translate"* — the paper that introduced attention specifically to fix seq2seq translation quality on long sentences.

### ⚠️ Common Misconceptions
- **"The bottleneck is a hardware/memory limitation — just use a bigger context vector."** Making $c$ bigger delays the problem but doesn't solve it structurally: no *fixed* size, however large, can losslessly represent an *unboundedly* long input — the fix has to be architectural (let the decoder access **all** encoder states, not just one summary), not just "allocate more numbers."

### 🎓 Exam Tips
> [!tip] **Memory trick**
> "Bottleneck" = **one** vector, **all** the information has to squeeze through it. The fix (attention) is precisely: stop forcing everything through one vector.


---

## 3.12 The Attention Mechanism

**Slide reference:** Lecture 9, p. 16; Maths Behind Transformers, pp. 3–8.

### 📐 Formal Definition
**Attention** computes, for a given query representation, a **weighted sum** over a set of value vectors, where the weights ("attention scores") measure how relevant each value is to the query — allowing a model to build a new, **context-dependent** representation of a token by selectively pulling in information from every other token, rather than being limited to one fixed-size summary or one fixed local window.

### 🗣️ Layman's Explanation
Instead of squeezing an entire sentence into one summary vector (Section 3.11) or reading only a fixed nearby window (Section 3.1), let every output word "look back" at *every* input word and decide, on the fly, how much attention to pay to each one.

### 🎯 Why This Concept Exists
It is the direct fix for the seq2seq bottleneck (Section 3.11): the decoder is no longer limited to one context vector — at every output step, it computes a *fresh*, custom-weighted combination of *all* encoder hidden states.

### 🧠 Intuition — reading Slide 16's four-panel diagram
Using the sentence *"The cat sat on the mat"* with the query word **"sat"**:

1. **Input sequence → embeddings.** Every word is converted to a vector.
2. **For a target word, use it as the Query.** "sat" becomes the **query**; all six words (including "sat" itself) serve as **keys**.
3. **Compute attention scores.** Compare the query against every key to get relevance scores: `The`=0.05, `cat`=0.10, **`sat`=0.60**, `on`=0.05, `the`=0.15, `mat`=0.05 (these sum to 1 — they are a probability distribution produced by softmax, Section 4.4).
4. **Compute the output.** Take the weighted sum of all word embeddings (as **values**) using these scores, producing a *new representation of "sat"* that has folded in information from the words it attends to most (`sat` itself and `cat`, per the scores above).

The slide's own summary: *"Attention computes how relevant every other word is to the current word, then builds a representation by focusing more on the important ones and less on the others."*

### 🧠 Intuition — the "apple" example (Maths Behind Transformers, pp. 3–8)
This is the deck's central illustration of *why static embeddings (Word2Vec) are insufficient* and attention is necessary:

- Pages 3–6 show that early (non-contextual) embeddings place each *word* at one fixed point — the word "apple" sits at one location, ambiguously between the cluster of fruits (banana, strawberry, cherry, orange) and the cluster of tech brands (Android, Microsoft, phone, laptop) — because "apple" the fruit and "Apple" the company are forced to share **one single vector**.
- Page 7 shows two sentences: *"please buy an **apple** and an `orange`"* vs. *"**apple** unveiled the new `phone`"*. Attention lets the word "apple" **move** in embedding space depending on which other word it attends to — toward the fruit cluster when it attends to "orange," toward the tech cluster when it attends to "phone."
- Page 8 shows attention scores as literal arrows between words in the sentence *"please buy an apple and an orange"* — "apple" attends most strongly to "orange," pulling its representation toward the fruit meaning.

> [!danger] **Course-consistent flag: this directly resolves Section 3.4's exam trap**
> Recall from Section 3.4: Word2Vec embeddings are **static** — one vector per word type, forever. Attention is the mechanism that finally produces **contextual** embeddings — the *same* word gets a *different* final representation depending on its sentence. This single fact (static vs. contextual embeddings) is one of the highest-yield conceptual distinctions in this entire chapter.

### 🧮 Mathematical Explanation
Formally (previewing Section 3.13, spelled out fully in Section 4): given a query vector $q$ and a set of key vectors $\{k_1,\dots,k_n\}$ and value vectors $\{v_1,\dots,v_n\}$,
$$\text{score}_i = \text{similarity}(q, k_i), \qquad \alpha_i = \frac{\exp(\text{score}_i)}{\sum_j \exp(\text{score}_j)}, \qquad \text{output} = \sum_i \alpha_i v_i$$
Slide 16's numeric example *is* exactly this formula with $q=$query("sat"), the six words as keys, and $\alpha = [0.05,0.10,0.60,0.05,0.15,0.05]$ already computed — see [Worked Example 3](#worked-example-3--slide-attention-weighted-sum-for-sat) for the explicit arithmetic.

### 🌍 Practical Example
Attention was first introduced (Bahdanau et al., 2014) as an **add-on** to RNN encoder-decoders for machine translation — the RNNs were kept, and attention was added purely to fix the bottleneck. It took three more years for someone to ask "do we even need the RNN anymore?" — the answer (Section 3.16) was no.

### ⚠️ Common Misconceptions
- **"Attention scores need to sum to 1 because that's a rule of attention."** More precisely: they sum to 1 because they are produced by a **softmax**, which is a *choice* (a convenient one, ensuring a well-behaved weighted average) — not an intrinsic law of "attention" as a concept. Some attention variants (e.g., sparse or hard attention) do not use a softmax at all.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> "Attention replaces the encoder-decoder architecture." In its *original* (Bahdanau) form, attention was added **on top of** an existing RNN encoder-decoder — it did not replace recurrence. Only the Transformer (Section 3.16) removed recurrence entirely. Conflating "attention" with "Transformer" is one of the most common conceptual errors students make — they are related but distinct ideas, introduced three years apart.

---

## 3.13 Self-Attention & Scaled Dot-Product Attention

**Slide reference:** Maths Behind Transformers, pp. 9–13 (Keys, Queries & Values).

### 📐 Formal Definition
**Self-attention** is attention (Section 3.12) where the queries, keys, *and* values all come from the **same** sequence — every token attends to every other token (including itself) within one sequence, rather than one sequence (decoder) attending to a different sequence (encoder).

For a set of input vectors packed as rows of a matrix $X \in \mathbb{R}^{n\times d_{model}}$, self-attention first learns three separate linear projections:
$$Q = XW^Q,\qquad K = XW^K, \qquad V = XW^V$$
with $W^Q, W^K \in \mathbb{R}^{d_{model}\times d_k}$ and $W^V \in \mathbb{R}^{d_{model}\times d_v}$, then computes:
$$\text{Attention}(Q,K,V) = \text{softmax}\!\left(\frac{QK^{\top}}{\sqrt{d_k}}\right)V$$

### 🗣️ Layman's Explanation
Every word produces **three different versions of itself**: a *Query* ("what am I looking for?"), a *Key* ("what do I have to offer, for matching purposes?"), and a *Value* ("what do I actually contribute, once someone decides to attend to me?"). Every word's Query is compared against every word's Key to decide how much attention to pay; then that attention is used to blend everyone's Values.

### 🎯 Why This Concept Exists
Section 3.12 explained attention loosely as "compare a query against keys, weight the values." Q/K/V formalizes this with three **separate, learnable** projection matrices instead of reusing the raw embeddings for all three roles — because "being good at finding relevant matches" (Q/K) and "being good at contributing useful content once found relevant" (V) are genuinely *different jobs*, and forcing one vector to do both would be a needless constraint.

### 🧠 Intuition — reading Maths-Behind-Transformers pp. 11–13
- **Page 11** shows the canonical diagram from *Attention Is All You Need*: $Q, K$ feed into a `MatMul`, then `Scale`, then optional `Mask`, then `Softmax`, then a second `MatMul` with $V$.
- **Page 12** visualizes similarity as literally comparing an "orange" query's row-vector against a "phone" key's row-vector via projections through $K$ and $Q$ weight matrices — the diagram makes explicit that the raw token vectors are first passed through learned matrices *before* the similarity is computed; you are never comparing raw embeddings directly.
- **Page 13** is the deck's most important intuition: it draws **two different subspaces** — one plane is *"Best embedding for finding similarities"* (the Q/K space), the other is *"Best embedding for finding the next word"* (the V space, captioned *"...we move the words here"*). This is the clearest possible visual statement of *why Q/K and V are different learned projections*: the geometry that's best for **measuring relevance** is not necessarily the geometry that's best for **actually representing content to be blended**.

> [!info] **Why this matters — the deepest intuition in the whole chapter**
> Q/K optimizes a *retrieval* problem (which other tokens are relevant?); V optimizes a *representation* problem (given relevance is decided, what content should flow through?). Keeping them as separate learned matrices lets the model solve these two different problems independently, rather than being forced to find one shared space that's simultaneously good at both.

### 🧮 Mathematical Explanation — why divide by $\sqrt{d_k}$
This is one of the single highest-yield derivations in the whole deck (and the paper devotes an entire footnote to it). Assume the components of $q$ and $k$ are independent random variables with mean 0 and variance 1. Their dot product is:
$$q\cdot k = \sum_{i=1}^{d_k} q_i k_i$$
Each term $q_ik_i$ has mean $0$ and variance $1$ (product of two independent, mean-0, variance-1 variables has variance 1). Summing $d_k$ **independent** such terms:
$$\text{Var}(q\cdot k) = \sum_{i=1}^{d_k}\text{Var}(q_ik_i) = d_k$$
So the raw dot product's variance **scales linearly with $d_k$** — for large $d_k$ (e.g., 64), dot products can become very large in magnitude *purely from dimensionality*, not from genuine relevance. Feeding large-magnitude scores into softmax pushes it into a **saturated regime** — one score dominates, the rest are driven near zero, and (crucially) the **gradient of softmax in this saturated regime is tiny** (see Section 4.4). Dividing by $\sqrt{d_k}$ rescales the variance back down to exactly $1$:
$$\text{Var}\!\left(\frac{q\cdot k}{\sqrt{d_k}}\right) = \frac{d_k}{d_k} = 1$$
restoring softmax to a well-behaved, non-saturated operating region regardless of how large $d_k$ is.

### 🧪 Worked Numerical Example
See [Worked Example 4](#worked-example-4--full-hand-computed-self-attention) for a complete, hand-verified 3-token, 2-dimensional self-attention computation (Q, K, V matrices, raw scores, scaled scores, softmax, weighted output).

### 🌍 Practical Example
Self-attention (not cross-attention) is what powers GPT-style decoder-only language models entirely — every layer is self-attention over the tokens generated so far; there is no separate "encoder" sequence at all.

### ⚠️ Common Misconceptions
- **"Self-attention has no learnable parameters — it's just a similarity computation."** The similarity computation (softmax of scaled dot products) has no parameters, but the $W^Q, W^K, W^V$ projection matrices that produce $Q,K,V$ from the input **are** learned — self-attention layers are full of trainable weights.
- **"Query, Key, and Value are three different tokens."** They are three different **linear projections of the same token embeddings** — for self-attention specifically, every token simultaneously plays all three roles (as a query when it's the one attending, as a key/value when others attend to it).

### 🎓 Exam Tips
> [!warning] **Exam trap**
> A guaranteed-to-appear question: "why scale by $\sqrt{d_k}$ specifically, and not $d_k$ or some other function?" The answer must invoke the **variance argument** above — $\sqrt{d_k}$ is exactly the factor that restores unit variance, no more, no less. An answer that just says "to make the numbers smaller" without the variance derivation will lose marks.

---

## 3.14 Multi-Head Attention

**Slide reference:** Maths Behind Transformers, pp. 9–11.

### 📐 Formal Definition
Instead of computing one attention function with $d_{model}$-dimensional queries/keys/values, **multi-head attention** runs $h$ independent attention computations ("heads") in parallel, each in a lower-dimensional subspace, then concatenates and linearly re-combines the results:
$$\text{MultiHead}(Q,K,V) = \text{Concat}(\text{head}_1,\dots,\text{head}_h)\,W^O, \qquad \text{head}_i = \text{Attention}(QW_i^Q,\, KW_i^K,\, VW_i^V)$$
with $W_i^Q, W_i^K \in \mathbb{R}^{d_{model}\times d_k}$, $W_i^V\in\mathbb{R}^{d_{model}\times d_v}$ per head, and $W^O \in \mathbb{R}^{hd_v \times d_{model}}$. In the original Transformer: $h=8$, $d_{model}=512$, $d_k=d_v=d_{model}/h=64$.

### 🗣️ Layman's Explanation
One attention head might learn to track subject-verb agreement, another might track coreference ("it" refers back to "the cat"), another might track adjacent-word syntax. Rather than forcing one attention computation to discover all these relationship types at once inside one shared subspace, give it $h$ separate, smaller subspaces to specialize in.

### 🎯 Why This Concept Exists
Maths-Behind-Transformers p. 9 states the motivation explicitly: *"Problem: Building many embeddings is a lot of work! Solution: We'll build embeddings by modifying existing embeddings"* — i.e., rather than training $h$ entirely separate embedding tables from scratch, project the *same* embeddings into $h$ different learned subspaces (cheap: just $h$ small matrix multiplications) and let attention run independently in each.

### 🧠 Intuition — reading the diagrams
- **Page 9 ("Good / Bad / So-so"):** shows that a *single* linear projection of the embedding space can separate "apple/orange" (fruit) from "phone" (tech) with varying quality depending on which 1D subspace you pick — "Good" cleanly separates them along one line, "Bad" collapses them together, "So-so" partially separates them. This motivates: *don't rely on just one projection — use several, and let the model learn which axes are useful.*
- **Page 10 (parallelogram diagrams, "Okay / Bad / Good," with scores 1 / 0.1 / 4):** different learned 2D subspaces (parallelograms) separate the same four tokens (phone, apple, apple, orange) with dramatically different quality — reinforcing that the *choice* of projection matters enormously, and a model benefits from having several different projections available simultaneously rather than being forced to commit to just one.
- **Page 11 (the canonical multi-head diagram):** $V, K, Q$ each pass through **their own** `Linear` projection (this is literally $W_i^V, W_i^K, W_i^Q$ for head $i$), then into `Scaled Dot-Product Attention` (Section 3.13) — this whole block is repeated $h$ times ("$\times h$" in the diagram) — then all $h$ outputs are `Concat`-enated and passed through one final `Linear` layer ($W^O$).

### 🧮 Mathematical Explanation
The parameter cost of $h$ heads with $d_k=d_v=d_{model}/h$ is (by design) almost identical to one head with the full $d_{model}$ dimensionality — the paper explicitly notes: *"Due to the reduced dimension of each head, the total computational cost is similar to that of single-head attention with full dimensionality."* Multi-head attention is not "more expensive attention" — it is the **same** total compute, sliced into parallel narrower subspaces instead of one wide one.

### 🧪 Worked Numerical Example
See [Worked Example 5](#worked-example-5--multi-head-attention-toy-example) for a fully hand-verified 2-head toy computation, extending Worked Example 4.

### 🌍 Practical Example
Visualizations of trained Transformer attention heads (e.g., in BERT) consistently show specialization: some heads attend almost entirely to the previous token, some to the sentence's syntactic head word, some to matching delimiters/quotation marks — direct empirical confirmation of the "different heads, different relationship types" intuition.

### ⚠️ Common Misconceptions
- **"More heads is strictly better."** $h$ and $d_k=d_{model}/h$ trade off against each other — too many heads makes each head's subspace too small to represent anything useful; the original paper's ablation (Table 3) shows both too few (1 head) and too many heads hurt performance relative to the chosen $h=8$.
- **"Each head sees a different part of the sentence."** Each head sees the **entire** sequence (nothing is spatially/positionally restricted) — heads differ in **projection subspace** ($W_i^Q, W_i^K, W_i^V$), not in *which tokens* they're allowed to look at.

### 🎓 Exam Tips
> [!tip] **Memory trick**
> Multi-head attention cost ≈ single-head attention cost, because $h \times d_k = h \times (d_{model}/h) = d_{model}$ — the total dimensionality processed is conserved, just split into parallel narrower "lanes."


---

## 3.15 Positional Encoding

**Slide reference:** Lecture 9, p. 2 (outline bullet only); Maths Behind Transformers, p. 2 (shown in the architecture diagram, not derived).

> [!danger] **Slide gap**
> Positional encoding is *drawn* (as a small sinusoid-plus-circle icon feeding into the architecture diagram) but **never derived or explained** in either deck. Given how consistently this appears on exams (it is one of the most distinctive, memorable formulas in the whole Transformer architecture), the full derivation is supplied here.

### 📐 Formal Definition
Since self-attention (Section 3.13) treats its input as an **unordered set** of vectors — attention is computed identically regardless of token order — a fixed, deterministic **positional encoding** vector $PE(pos)\in\mathbb{R}^{d_{model}}$ is added to each token's embedding before the first layer, injecting information about token position:
$$PE_{(pos,\,2i)} = \sin\!\left(\frac{pos}{10000^{2i/d_{model}}}\right), \qquad PE_{(pos,\,2i+1)} = \cos\!\left(\frac{pos}{10000^{2i/d_{model}}}\right)$$
where $pos$ is the token's position in the sequence ($0,1,2,\dots$) and $i$ indexes pairs of dimensions ($0,1,\dots,d_{model}/2 - 1$).

### 🗣️ Layman's Explanation
Self-attention, by itself, is **permutation-equivariant**: shuffle the input tokens, and the *set* of outputs is exactly the same shuffle of what you'd have gotten unshuffled — attention has no innate notion of "first," "second," "next to." So before doing anything else, stamp each token's embedding with a unique, position-dependent pattern of sine and cosine waves, so the model can tell tokens apart by position even though the attention mechanism itself is blind to order.

### 🎯 Why This Concept Exists
Without positional encoding, "the cat chased the dog" and "the dog chased the cat" would look **identical** to a self-attention layer (as a bag of the same 6 tokens) — clearly unacceptable for language, where word order carries meaning (subject vs. object). Positional encoding is the (surprisingly small, cheap) patch that restores order-sensitivity without giving up self-attention's core advantage (full parallelism, no recurrence).

### 🧠 Intuition
Why **sinusoids**, specifically, rather than just using the raw integer position (0, 1, 2, …) or a learned position embedding?

1. **Bounded, well-scaled values.** Raw integer positions grow unboundedly and would dominate the embedding's scale for long sequences; $\sin/\cos$ are always in $[-1,1]$.
2. **Each dimension oscillates at a different frequency.** As $i$ increases, the divisor $10000^{2i/d_{model}}$ grows, so the wavelength grows — dimension 0 oscillates very fast (period $2\pi$), later dimensions oscillate very slowly (period up to $\sim 2\pi\cdot 10000$). This is exactly like binary encoding of an integer, but continuous — together, the full vector of frequencies uniquely encodes every position, the same way a clock's second/minute/hour hands together uniquely encode a specific moment in a 12-hour cycle.
3. **Relative positions become a *linear* function.** For any fixed offset $k$, $PE(pos+k)$ can be written as a **linear transformation** of $PE(pos)$ (via the trigonometric angle-addition identities $\sin(a+b)=\sin a\cos b + \cos a \sin b$, similarly for cosine) — this means the model can, in principle, easily learn to attend by *relative* position ("look 3 tokens back") using simple linear operations on the positional encodings, not just absolute position.
4. **Extrapolation.** Because sinusoids are defined for *any* real-valued position, a model can (at least in principle) generalize to sequence lengths longer than anything seen during training — a fixed-size learned position-embedding table, by contrast, simply has no vector for position 5000 if it only ever saw sequences up to length 512.

### 🧮 Mathematical Explanation
For $d_{model}=4$, the two frequency "channels" are indexed by $i=0$ and $i=1$:
$$i=0:\ \text{divisor} = 10000^{0/4} = 10000^0 = 1 \qquad\Rightarrow\qquad PE(pos,0)=\sin(pos),\ \ PE(pos,1)=\cos(pos)$$
$$i=1:\ \text{divisor} = 10000^{2/4} = 10000^{0.5} = 100 \qquad\Rightarrow\qquad PE(pos,2)=\sin(pos/100),\ \ PE(pos,3)=\cos(pos/100)$$
Dimension pair $(0,1)$ cycles very fast (period $2\pi\approx6.28$ positions); dimension pair $(2,3)$ cycles 100× slower.

### 🧪 Worked Numerical Example
See [Worked Example 7](#worked-example-7--positional-encoding-values) for the fully computed $4\times4$ table of $PE(pos)$ for $pos=0,1,2,3$.

### 🌍 Practical Example
Later architectures (e.g., T5, and most modern LLMs via RoPE — Rotary Positional Embeddings) replace this exact sinusoidal scheme with alternatives that encode **relative** position even more directly, but the *problem being solved* — giving an inherently order-blind self-attention mechanism a sense of sequence — is identical to what this section describes.

### ⚠️ Common Misconceptions
- **"Positional encoding is learned."** In the *original* Transformer paper, it is a **fixed, non-learned** function (the sinusoidal formula above) — the paper does note learned positional embeddings were also tried and performed nearly identically, but the sinusoidal version was preferred for its extrapolation property.
- **"Positional information is only added once, at the input."** Correct for the original Transformer — the positional encoding is added once, to the input embeddings, before the first encoder/decoder layer (not re-added at every layer) — but it persists through the network via the residual connections (Section 3.16).

### 🎓 Exam Tips
> [!warning] **Exam trap**
> "Why not just concatenate the position as an extra feature, like $[x_1,\dots,x_d, pos]$?" A single extra scalar dimension can't cheaply encode "attend to something 3 positions back" via a linear operation the way the full sinusoidal vector can (per the angle-addition argument above) — and it wastes none of the existing $d_{model}$ dimensions to do so, since it's *added* elementwise rather than appended.

---

## 3.16 The Transformer Architecture

**Slide reference:** Maths Behind Transformers, p. 2 (the full architecture diagram from *Attention Is All You Need*, Figure 1).

### 📐 Formal Definition
The **Transformer** is a sequence-to-sequence model built **entirely** from attention, feedforward layers, residual connections, and layer normalization — with **no recurrence and no convolution**. It consists of a stack of $N$ identical **encoder** layers and a stack of $N$ identical **decoder** layers ($N=6$ in the original paper).

**Each encoder layer:**
$$\text{Encoder Layer}(x) = \text{LayerNorm}\big(x + \text{FFN}(\,\text{LayerNorm}(x+\text{MultiHeadSelfAttn}(x))\,)\big)$$
(informally — each of the two sub-layers, self-attention and feedforward, is wrapped in a residual connection followed by layer normalization: "Add & Norm.")

**Each decoder layer** has **three** sub-layers instead of two:
1. **Masked multi-head self-attention** over the decoder's own (partially generated) output sequence — "masked" so position $t$ cannot attend to positions $>t$ (it must not see the future word it's trying to predict).
2. **Multi-head cross-attention**: queries come from the decoder, but **keys and values come from the encoder's output** — this is how the decoder looks back at the input sequence.
3. A **feedforward network**, identical in form to the encoder's.

Each sub-layer, in both stacks, is wrapped in the same **residual + layer norm ("Add & Norm")** pattern.

### 🗣️ Layman's Explanation
Read Section 5.7's diagram walkthrough for the full left-to-right, bottom-to-top tour of the architecture; conceptually: the encoder builds a rich, contextual representation of the *entire* input sentence (every token attending to every other input token); the decoder generates the output one token at a time, at each step (a) attending to everything it has generated *so far* (masked self-attention) and (b) attending to the *entire* encoded input (cross-attention) to decide what to generate next.

### 🎯 Why This Concept Exists
It is the endpoint of the whole lecture's arc: RNNs (Section 3.6) process sequentially — you cannot compute $h_5$ before $h_4$, so training cannot be parallelized across the time dimension, only across independent training examples. Attention (Sections 3.12–3.14) fixed the *bottleneck/quality* problem while attention was still bolted onto an RNN. The Transformer's insight is that **attention alone**, with no recurrence at all, is sufficient to build a working sequence model — and because there's no sequential dependency between token computations *within* a layer, the entire sequence can be processed **in parallel** on a GPU, layer by layer — a massive practical speedup that is arguably as important to the Transformer's success as any accuracy gain.

### 🧠 Intuition — the encoder/decoder input arrows
The bottom of the diagram shows two separate input streams: **Inputs** (source sentence) feed the encoder (left stack); **Outputs (shifted right)** feed the decoder (right stack). *"Shifted right"* means: to predict output token $t$, the decoder is fed tokens $1,\dots,t-1$ (a special start token is prepended) — this is exactly the autoregressive, chain-rule structure from Section 3.2, now implemented via masking rather than an explicit recurrence.

### 🧮 Mathematical Explanation — masking
Masked self-attention modifies the scaled dot-product formula (Section 3.13) by adding a mask matrix $M$ **before** the softmax:
$$\text{MaskedAttention}(Q,K,V) = \text{softmax}\!\left(\frac{QK^\top}{\sqrt{d_k}} + M\right)V, \qquad M_{ij} = \begin{cases}0 & j\le i \\ -\infty & j>i\end{cases}$$
Adding $-\infty$ (in practice, a large negative number) to any "future" position $j>i$ forces $\exp(-\infty)=0$ after softmax — that position receives **exactly zero** attention weight, with no gradient leaking through it either. This is the mechanism referenced on Maths-Behind-Transformers p. 11's diagram as the optional "Mask" block between "Scale" and "Softmax."

### 🌍 Practical Example
- **Encoder-only** Transformers (e.g., BERT) drop the decoder entirely and are used for representation learning / classification tasks — they use **bidirectional** (unmasked) self-attention, since there's no autoregressive generation to protect.
- **Decoder-only** Transformers (e.g., the GPT family) drop the encoder entirely — pure masked self-attention over one sequence, which is exactly the setup for autoregressive language modeling (Section 3.2).
- **Encoder-decoder** Transformers (e.g., the original translation model, T5) keep both stacks, as described above — natural for tasks with genuinely two different sequences (source/target language, question/answer).

### ⚠️ Common Misconceptions
- **"The decoder's self-attention and its cross-attention (into the encoder) are the same operation."** They share the *same formula* (scaled dot-product multi-head attention) but differ in **where $Q$, $K$, $V$ come from**: masked self-attention has $Q,K,V$ all from the decoder; cross-attention has $Q$ from the decoder but $K,V$ from the encoder's final output.
- **"Layer normalization and batch normalization are the same thing, just different names in different papers."** They normalize over **different axes** — batch norm normalizes each feature across the batch dimension; layer norm normalizes across the feature dimension for each individual example — this distinction matters especially for variable-length sequences, where batch statistics are awkward to define consistently across positions, which is exactly why Transformers use layer norm.

### 🎓 Exam Tips
> [!warning] **Exam trap**
> If asked to name **all three** places attention appears in the full Transformer, a common incomplete answer only mentions self-attention. The complete list is: (1) **encoder self-attention** (bidirectional, unmasked), (2) **decoder masked self-attention** (causal), (3) **encoder-decoder cross-attention** (decoder queries, encoder keys/values). All three appear explicitly, separately, in the architecture diagram.

---

## 3.17 Transformers Beyond NLP — the other syllabus gap

![[Pasted image 20260905224721.png]]

**Slide reference:** Lecture 9, p. 2 lists *"Transformers in other fields"* as an outline bullet, with **no corresponding slide content** anywhere in either deck.

> [!danger] **Slide gap**
> Like GRUs (Section 3.10), this is promised in the outline but never delivered in the slides. A short, exam-safe supplement:

- **Vision Transformer (ViT)** — Dosovitskiy et al., 2020: split an image into fixed-size patches (e.g., $16\times16$ pixels), flatten and linearly embed each patch (directly analogous to how a word is embedded — a patch is "a visual word"), add positional encodings, and feed the resulting sequence into a standard Transformer encoder.
- **Protein structure prediction** — AlphaFold2 uses attention-based mechanisms (Evoformer) over both sequence and pairwise-residue representations.
- **Audio/speech** — Transformer encoders operating over spectrogram frames or learned audio tokens (e.g., Whisper).
- **Multimodal models** — interleave image-patch tokens and text tokens in a single Transformer sequence (e.g., vision-language models).

The unifying thread: **any data that can be chunked into a sequence of tokens** — patches, protein residues, audio frames, code tokens — can be fed through the exact same self-attention + positional-encoding + feedforward recipe developed for words. This generality (not any NLP-specific trick) is a large part of why the Transformer became the dominant architecture across nearly all of deep learning by the early 2020s.

> [!tip] **Exam tip**
> If an exam question asks "why do Transformers generalize to non-language domains," the correct high-level answer is: self-attention makes **no language-specific assumption** — it only assumes the input is *some* sequence of vectors. Contrast this with CNNs (Lecture 8), which bake in an assumption specific to spatial/grid-structured data (translation invariance via convolution).


---

# 4. Mathematical Foundations Deep Dive

This section consolidates and extends the derivations touched on in Section 3 into one unified mathematical reference — every equation used anywhere in this chapter is derived here from first principles, with every intermediate step shown.

## 4.1 Notation Recap

| Symbol | Meaning |
|---|---|
| $V$ | vocabulary size |
| $d_{model}$ | embedding / model dimension (512 in the base Transformer) |
| $n$ (or $T$) | sequence length |
| $h$ | number of attention heads (8 in the base Transformer) |
| $d_k, d_v$ | per-head key/value dimension ($=d_{model}/h = 64$ in the base Transformer) |
| $\odot$ | element-wise (Hadamard) product |
| $[a,b]$ | vector concatenation |
| $\sigma(z) = \frac{1}{1+e^{-z}}$ | sigmoid function |

## 4.2 RNN Forward and Backward Pass, in Full

**Forward pass**, per time step $t=1,\dots,T$:
$$z_t = W_{hh}h_{t-1} + W_{xh}x_t + b_h, \qquad h_t = \tanh(z_t), \qquad \hat{y}_t = \text{softmax}(W_{hy}h_t+b_y)$$
with per-step loss (cross-entropy against the true next word $y_t$): $L_t = -\log \hat{y}_{t,y_t}$, and total loss $L=\sum_{t=1}^T L_t$.

**Backward pass.** Define $\delta_t \triangleq \dfrac{\partial L}{\partial h_t}$. Because $h_t$ affects *both* the immediate output $\hat y_t$ *and* the next hidden state $h_{t+1}$ (which affects all future losses), $\delta_t$ has two contributions:
$$\delta_t = \underbrace{W_{hy}^\top(\hat{y}_t - \mathbf{1}_{y_t})}_{\text{direct effect on }L_t} + \underbrace{\left(\frac{\partial h_{t+1}}{\partial h_t}\right)^{\!\top}\delta_{t+1}}_{\text{indirect effect, via future steps}}$$
where $\frac{\partial h_{t+1}}{\partial h_t} = \text{diag}(1-\tanh^2(z_{t+1}))\,W_{hh}$ (using $\tanh'(z) = 1-\tanh^2(z)$). This recursion is computed **backward**, from $t=T$ down to $t=1$ ($\delta_T$ has only the direct term, since there is no $t=T{+}1$). The gradient with respect to the shared weight $W_{hh}$ accumulates a contribution from **every** time step:
$$\frac{\partial L}{\partial W_{hh}} = \sum_{t=1}^{T} \delta_t \odot \big(1-\tanh^2(z_t)\big)\, h_{t-1}^\top$$
This is the fully-expanded version of the schematic formula given in Section 3.7, and it is this recursive $\delta_t$ computation, unrolled, that produces the repeated-Jacobian product responsible for vanishing/exploding gradients (Section 3.8).

## 4.3 The Softmax Function

**Definition.** For a logit vector $z \in \mathbb{R}^K$:
$$\text{softmax}(z)_i = \frac{e^{z_i}}{\sum_{j=1}^{K}e^{z_j}}$$

**Properties exploited throughout this chapter:**
1. **Output is a valid probability distribution** — all entries in $(0,1)$, summing to 1 — required both for language-model next-word prediction (Section 3.2) and for attention weights (Section 3.12).
2. **Translation invariance:** $\text{softmax}(z+c) = \text{softmax}(z)$ for any constant $c$ — this is why, numerically, implementations subtract $\max_j z_j$ before exponentiating (as used silently in the worked examples below) purely for numerical stability, without changing the mathematical result.
3. **Saturation under large-magnitude inputs.** If one $z_i$ is much larger than the rest, $\text{softmax}(z)_i \to 1$ and all others $\to 0$. The **Jacobian** of softmax is $\frac{\partial \text{softmax}(z)_i}{\partial z_j} = \text{softmax}(z)_i(\delta_{ij}-\text{softmax}(z)_j)$, which $\to 0$ for *all* $i,j$ as the distribution saturates toward a one-hot output — i.e., **gradients vanish exactly when softmax is most "confident."** This is the precise mechanism behind the $\sqrt{d_k}$-scaling argument in Section 3.13: large dot products → saturated softmax → vanishing gradients through the attention weights.

## 4.4 Cross-Entropy Loss and Perplexity for Language Modeling

Given the model's predicted distribution $\hat{y}_t = P(\cdot \mid w_{<t})$ and the true next word $w_t$, the per-token loss is the negative log-likelihood:
$$L_t = -\log P(w_t\mid w_{<t})$$
matching the general Binary/Categorical Cross-Entropy framework already established in your Logistic Regression and Neural Networks chapters — language modeling's loss is simply categorical cross-entropy with $K=V$ (vocabulary-size-many classes) instead of $K=2$.

**Perplexity**, the standard language-model evaluation metric, is defined as the exponentiated average per-token loss:
$$\text{Perplexity} = \exp\!\left(\frac{1}{T}\sum_{t=1}^{T} L_t\right) = \exp\!\left(-\frac{1}{T}\sum_{t=1}^T \log P(w_t\mid w_{<t})\right)$$
Intuitively, perplexity is the *effective number of equally-likely choices* the model is choosing among at each step — a perplexity of 1 means perfect, certain prediction; a perplexity of $V$ means the model is no better than uniform random guessing over the vocabulary. This connects Section 3.2's language modeling objective directly to Lecture 7's evaluation-metrics framework.

## 4.5 Scaled Dot-Product Attention — Complexity

For a sequence of length $n$ and dimension $d$: computing $QK^\top$ costs $O(n^2 d)$ (an $n\times d$ matrix times a $d\times n$ matrix), and the subsequent softmax-weighted sum with $V$ costs another $O(n^2 d)$. Total: $O(n^2 d)$ — **quadratic in sequence length**. This is the well-known practical cost of self-attention, and is exactly why long-context Transformers require specialized approximations (sparse attention, linear attention, sliding-window attention) as $n$ grows into the tens of thousands.

Contrast with an RNN's per-layer cost: $O(nd^2)$ — **linear** in sequence length, but crucially, RNN computation cannot be parallelized across $n$ (each step must wait for the previous one), while attention's $n^2$ term is embarrassingly parallel across a GPU. This is the precise trade-off named in Section 3.16: attention trades better parallelism and constant path-length between any two tokens (better long-range gradient flow — the "maximum path length" between any two positions is $O(1)$ for self-attention vs. $O(n)$ for an RNN) for worse asymptotic compute scaling.

## 4.6 Layer Normalization

$$\text{LayerNorm}(x) = \gamma\odot\frac{x-\mu}{\sqrt{\sigma^2+\epsilon}} + \beta, \qquad \mu = \frac{1}{d}\sum_{i=1}^d x_i,\ \ \sigma^2=\frac{1}{d}\sum_{i=1}^{d}(x_i-\mu)^2$$
where $\gamma,\beta \in \mathbb{R}^d$ are learned scale/shift parameters, and the mean $\mu$ and variance $\sigma^2$ are computed **across the feature dimension**, independently for every single token, in every single training example — unlike batch normalization, which computes statistics across the batch dimension. This per-token independence is exactly what makes layer norm suit variable-length sequences: it never needs to define statistics jointly over a padded batch.

## 4.7 Why Residual Connections Help — the same story as the LSTM's cell state

Each Transformer sub-layer is wrapped as $x + \text{Sublayer}(x)$ rather than just $\text{Sublayer}(x)$. Differentiating:
$$\frac{\partial}{\partial x}\big[x+\text{Sublayer}(x)\big] = I + \frac{\partial\,\text{Sublayer}(x)}{\partial x}$$
The identity term $I$ guarantees the gradient has a path of magnitude **exactly 1** back through every layer, regardless of what the sublayer's own Jacobian looks like — this is architecturally the *same fix* as the LSTM's additive cell-state update (Section 3.9): both replace a purely multiplicative chain (which can vanish or explode) with an **additive shortcut** that guarantees at least one unimpeded gradient path across many stacked layers. With $N=6$ stacked encoder layers (or far deeper modern LLMs, 32–100+ layers), this is not optional — deep networks without residual connections are empirically very difficult to train past a moderate depth.

## 4.8 Positional Encoding — the Relative-Position Linearity Proof

Claim: for any fixed offset $k$, $PE(pos+k)$ is a linear function of $PE(pos)$. For one frequency pair (dropping the $i$ subscript for brevity, writing $\omega = 1/10000^{2i/d_{model}}$):
$$PE(pos+k) = \begin{pmatrix}\sin(\omega(pos+k))\\ \cos(\omega(pos+k))\end{pmatrix} = \begin{pmatrix}\sin(\omega\, pos)\cos(\omega k) + \cos(\omega\, pos)\sin(\omega k)\\ \cos(\omega\, pos)\cos(\omega k) - \sin(\omega\, pos)\sin(\omega k)\end{pmatrix}$$
using the angle-sum identities $\sin(a+b)=\sin a\cos b+\cos a\sin b$ and $\cos(a+b)=\cos a\cos b - \sin a \sin b$. This can be written as a matrix-vector product:
$$PE(pos+k) = \underbrace{\begin{pmatrix}\cos(\omega k) & \sin(\omega k)\\ -\sin(\omega k) & \cos(\omega k)\end{pmatrix}}_{\text{a rotation matrix, depending only on }k,\text{ not on }pos} \cdot PE(pos)$$
i.e., shifting position by a fixed offset $k$ corresponds to applying a **fixed rotation matrix** (depending only on $k$) to the positional encoding — the same linear map works regardless of the starting position $pos$. This is the rigorous version of Section 3.15's claim #3 ("relative positions become a linear function") and is precisely why a Transformer *can*, in principle, learn to attend by relative offset using only linear operations on the positional encodings.

## 4.9 Parameter Count of One Encoder Layer (worked reference)

For the base Transformer ($d_{model}=512$, $h=8$, $d_{ff}=2048$):
- **Multi-head self-attention:** $W^Q, W^K, W^V$ each $512\times512$ (summed across all heads) $= 3\times512^2 = 786{,}432$, plus $W^O$: $512\times512=262{,}144$. Subtotal: $1{,}048{,}576$.
- **Feedforward network** ($d_{model}\to d_{ff}\to d_{model}$): $(512\times2048) + (2048\times512) = 2{,}097{,}152$, plus biases (negligible).
- **Two LayerNorm blocks:** $2\times(512+512)=2048$ (negligible next to the above).

**Total per encoder layer $\approx 3.15$ million parameters**; with $N=6$ layers, the encoder alone is $\approx 19$ million parameters — before counting embeddings, the decoder stack, or the final output projection. This kind of order-of-magnitude estimate (which component dominates parameter count) is a favorite higher-order exam question — the feedforward sub-layer, not attention itself, holds the majority of parameters in each layer.


---

# 5. Architecture & Diagram Explanations

Every diagram-bearing slide from both decks, explained component-by-component. Concepts are cross-referenced back to Section 3 rather than re-explained.

## 5.1 Language Modeling Chain Rule (Lecture 9, p. 4)
**What it shows:** the sentence $S=$"Where are we going" split into context (green, "Where are we") and predicted word (magenta, "going"), with the chain-rule product $P(S)=P(\text{Where})\times P(\text{are}\mid\text{Where})\times P(\text{we}\mid\text{Where, are})\times P(\text{going}\mid\text{Where, are, we})$ written beneath.
**Information flow:** left to right — each factor conditions on *strictly more* context than the last, matching Section 3.2's chain rule exactly.

## 5.2 One-Hot Encoding Grid (Lecture 9, p. 5)
**What it shows:** a $5\times5$ grid (5 vocabulary words × 5 dimensions), one bolded "1" per row, plus a side panel of pairwise dot products, all reading $0$.
**Information flow:** none (this is a static representation, not a computation graph) — its purpose is purely to make Section 3.3's "no similarity" failure numerically undeniable.

## 5.3 Learned Embedding Scatter Plot (Lecture 9, p. 6)
**What it shows:** a 2D scatter plot with `kitten`, `cat`, `dog` clustered in the upper-right, and `physics`, `algebra` clustered in the lower-left, captioned "This is what we want to learn."
**Information flow:** N/A (illustrative target state, not a process diagram) — see Section 3.4.

## 5.4 Word2Vec Analogy Cube (Lecture 9, p. 7)
**What it shows:** a 3D plot with axes Gender / Age / Royalty; `man→king` and `woman→queen` drawn as parallel arrows of similar length.
**Information flow:** the diagram encodes an *algebraic* relationship geometrically — parallel, equal-length arrows mean "the same vector added to different starting points," i.e., $v_{\text{king}}-v_{\text{man}} \approx v_{\text{queen}}-v_{\text{woman}}$. See Worked Example 6.

## 5.5 RNN Single Time Step (Lecture 9, p. 9, left panel)
**What it shows:** three inputs — $h_{t-1}$ (green circle, labeled "recurrent," via $W_{hh}$), $x_t$ (blue circle, "input," via $W_{xh}$) — both arrows pointing into the central $h_t$ node (green), which then has one arrow out to $\hat{y}_t$ (yellow circle, via $W_{hy}$).
**Information flow:** two arrows **in** to $h_t$ (previous memory + current input, combined additively inside $f$), one arrow **out** (to the current prediction). This is the atomic unit that gets repeated in Diagram 5.6.

## 5.6 RNN Unrolled Across Time (Lecture 9, p. 10)
**What it shows:** the same node from 5.5, drawn $T$ times side-by-side (once per word: "The," "cat," "sat," "on," "the," …, "mat"), with $h_0\to h_1\to h_2\to\dots\to h_T$ connected left-to-right, every arrow explicitly labeled with which weight matrix it is, and a caption confirming every $W_{hh}$/$W_{xh}$/$W_{hy}$ arrow is the **same** matrix reused at every step.
**Information flow:** strictly left-to-right through the hidden-state chain — this is the diagram to reproduce if an exam asks you to "draw an RNN unrolled across time."

## 5.7 Vanishing/Exploding Gradients — Forward & Backward Pass (Lecture 9, p. 11)
**What it shows:** two rows. Top row ("Forward Pass"): identical to Diagram 5.6, but now every $h_t$ also produces a loss $L_t$ (red boxes) by comparing $\hat{y}_t$ against the true next word. Bottom row ("Backward Pass"): the *same* diagram, but arrows point **right to left**, labeled "error," showing the error at each $L_t$ flowing backward through every earlier hidden state, all the way to $h_0$.
**Information flow:** forward pass flows left→right (computing predictions); backward pass flows right→left (computing gradients) — the juxtaposition of both rows is precisely BPTT (Section 3.7), and the diagram is the visual justification for why the gradient at $h_1$ has to pass through *every* intervening hidden state — the literal chain of arrows *is* the chain of Jacobians in Section 4.2's $\delta_t$ recursion.

## 5.8 LSTM Cell, Single Time Step (Lecture 9, pp. 13–14)
**What it shows:** a green-bordered box representing one LSTM cell. Left-to-right inside: four small labeled boxes (Forget Gate $\sigma$, Input Gate $\sigma$, Candidate Cell $\tanh$, Output Gate $\sigma$), each fed by $h_{t-1}$ and $x_t$ from below. Along the top: $c_{t-1}$ enters from the left, passes through a $\times$ node (multiplied by the forget gate's output), then a $+$ node (adding the input-gate-scaled candidate), producing $c_t$ exiting to the right. A branch from $c_t$ passes through $\tanh$, then a $\times$ node (multiplied by the output gate), producing $h_t$.
**Information flow:** the **top row** (the $c_{t-1}\to\times\to+\to c_t$ path) is the "conveyor belt" (Section 3.9) — it has only two operations (one multiply, one add) between $c_{t-1}$ and $c_t$, which is exactly why gradients can flow through it with far less attenuation than the plain-RNN hidden state, which is repeatedly passed through a full matrix multiply and a $\tanh$ nonlinearity at every step. Page 14 additionally overlays the six numbered equations from Section 3.9 directly onto the same diagram, gate by gate.

## 5.9 Seq2Seq Bottleneck (Lecture 9, p. 15)
**What it shows:** a row of blue encoder-input boxes (`How`, `are`, `you`, `?`, `[EOS]`) feeding into a single red box labeled "Context Vector $c$ — 512 numbers," which alone feeds a row of green decoder-output boxes (`Wie`, `geht`, `es`, `Ihnen`). Below: the BLEU-vs-sentence-length bar chart from Section 3.11.
**Information flow:** many-to-one (encoder → single vector), then one-to-many (single vector → decoder outputs) — the diagram's entire point is that the "many-to-one" step is a hard bottleneck: all input information *must* pass through that single 512-number box.

## 5.10 Attention Mechanism, Four-Panel Worked Example (Lecture 9, p. 16)
**What it shows:** four sequential panels for the sentence "The cat sat on the mat" with query word "sat": (1) input embeddings; (2) "sat" highlighted as the Query, all six words listed as candidate Keys; (3) a $1\times6$ heat-map row of attention scores (0.05, 0.10, **0.60**, 0.05, 0.15, 0.05), colored light-to-dark green by magnitude; (4) arrows of varying thickness/darkness from each of the six words into a new output vector for "sat," proportional to each word's score.
**Information flow:** left to right through the four numbered stages — this is the single most important diagram to be able to redraw from memory, since it is the diagram-form of the full attention formula (Section 3.12) with every intermediate quantity made concrete and numeric.

## 5.11 "Apple" Embedding Ambiguity (Maths Behind Transformers, pp. 3–8)
**What it shows:** a progression across six slides — (p.3) generic embedding scatter plots for words/images; (p.4) a real-data word-embedding heatmap plus the "king−man+woman≈queen" bar-chart; (p.5–6) a 2D scatter plot where fruit emoji and tech-brand icons are plotted, with "apple" (both the red fruit icon and the black Apple-logo icon) sitting at nearly the **same point**, roughly between the two clusters; (p.7) two example sentences with curved arrows showing "apple" attending to "orange" (pulling toward fruit) vs. "phone" (pulling toward tech); (p.8) the same idea generalized to a full sentence, "please buy an apple and an orange," with dotted attention-arrows of different lengths/directions from every word to every other word, and "apple"'s arrow to "orange" highlighted as the dominant one (thick dashed orange line).
**Information flow:** this whole sequence is a *narrative* diagram, not a single computational one — it walks from "static embeddings can't disambiguate 'apple'" (the problem) to "attention lets 'apple' move toward whichever cluster the context word pulls it toward" (the fix), i.e., it is a fully worked visual proof of Section 3.12's contextual-embedding argument.

## 5.12 Multi-Head Attention Motivation (Maths Behind Transformers, pp. 9–10)
**What it shows:** (p.9) three small 2D scatter plots labeled "Good," "Bad," "So-so," each showing the same four icons (phone, two apples, orange) with a single dashed line ("axis") drawn through them at different angles, illustrating that a *single* 1D projection separates the tech/fruit clusters with varying success depending on its angle; (p.10) the same four icons re-plotted inside **parallelograms** (representing 2D projected subspaces) labeled "Okay" (score 1), "Bad" (score 0.1), "Good" (score 4), where the shape/skew of the parallelogram represents a different learned linear projection of the embedding space.
**Information flow:** N/A (comparison diagram) — its purpose is purely to visually argue "different projections separate the same data with very different quality, so use several (multi-head) rather than betting on just one," motivating Section 3.14.

## 5.13 Scaled Dot-Product & Multi-Head Attention (Maths Behind Transformers, p. 11)
**What it shows:** the canonical two-panel diagram from *Attention Is All You Need*, Figure 2. **Left panel** ("Scaled Dot-Product Attention"): $Q,K$ arrows enter a `MatMul` box, whose output passes through `Scale`, then optional `Mask`, then `Softmax`, then a second `MatMul` combines this with $V$. **Right panel** ("Multi-Head Attention"): $V,K,Q$ each pass through their own `Linear` box, then into a `Scaled Dot-Product Attention` block (drawn stacked, "$\times h$" to indicate $h$ parallel copies), whose $h$ outputs are `Concat`-enated, then passed through one final `Linear` box.
**Information flow:** bottom-to-top in both panels — raw $Q,K,V$ enter at the bottom, the final attention output exits at the top. The two formulas beneath the diagrams (Section 3.13's $\text{Attention}(Q,K,V)$ formula, and Section 3.14's $\text{MultiHead}(Q,K,V)$ formula) are the algebraic transcription of exactly what these boxes compute.

## 5.14 Keys/Queries Similarity Geometry (Maths Behind Transformers, pp. 12–13)
**What it shows:** (p.12) an "orange" token and a "phone" token, each first passed through small colored grids labeled "Keys" (green grid) and "Queries" (magenta grid) respectively — representing the $W^K$ and $W^Q$ projection matrices — with a "Similarity(orange, phone) = " equation assembling the pieces; (p.13, left) a labeled angle between two vectors in a parallelogram-shaped subspace, captioned "Using these similarities... Best embedding for finding similarities"; (p.13, right) a *different* parallelogram-shaped subspace with the caption "...we move the words here / Best embedding for finding the next word."
**Information flow:** p.12 shows the **similarity computation** direction (raw tokens → $K$/$Q$ projections → dot product); p.13's two side-by-side panels are not sequential steps but **parallel, contrasting** spaces — the key visual argument (Section 3.13) that the Query/Key subspace (optimized for *measuring* relevance) and the Value subspace (optimized for *representing content to blend*) are two **different** learned geometries, not one shared space doing double duty.

## 5.15 The Full Transformer Architecture (Maths Behind Transformers, p. 2)
**What it shows:** the complete encoder (left stack) / decoder (right stack) diagram from *Attention Is All You Need*, Figure 1 (see Section 3.16 for the full equation-level explanation). Bottom-to-top: `Inputs`/`Outputs (shifted right)` → `Input/Output Embedding` → `+ Positional Encoding` → ($N\times$) `Multi-Head Attention` (masked, for the decoder) → `Add & Norm` → (decoder only) `Multi-Head Attention` (cross-attention into the encoder stack, shown via the arrows crossing from the encoder's top into the decoder's second attention block) → `Add & Norm` → `Feed Forward` → `Add & Norm` → (after $N$ repetitions) `Linear` → `Softmax` → `Output Probabilities`.
**Information flow:** bottom-to-top through each stack, with one **explicit cross-stack arrow**: the encoder's final output (top of the left stack) feeds directly into the second attention block of *every* decoder layer, as the source of $K$ and $V$ for cross-attention — this single arrow is the entire mechanism by which the decoder "sees" the input sentence at all, and is the most commonly mis-drawn part of this diagram on exams (students often forget to draw it, or draw it only into the first decoder layer instead of all $N$).


---

# 6. Worked Examples

All numeric results below were independently verified with Python (NumPy) before being written up — every value is exact to the precision shown.

## Worked Example 1 — Chain-Rule Probability of a Sentence

**Setup.** Take the slide's own sentence $S=$ "Where are we going" and assign small illustrative conditional probabilities (these specific numbers are constructed for this example, not given on the slide, but the *decomposition* is exactly the slide's):

| Factor | Illustrative value |
|---|---|
| $P(\text{Where})$ | 0.02 |
| $P(\text{are}\mid\text{Where})$ | 0.30 |
| $P(\text{we}\mid\text{Where, are})$ | 0.40 |
| $P(\text{going}\mid\text{Where, are, we})$ | 0.25 |

**Computation.**
$$P(S) = 0.02 \times 0.30 \times 0.40 \times 0.25 = 0.0006$$
Step by step: $0.02\times0.30 = 0.006$; $\; 0.006\times0.40=0.0024$; $\; 0.0024\times0.25=0.0006$.

**Reading the result.** A probability of $0.0006$ looks tiny, but this is normal and expected — the chain rule multiplies many numbers each less than 1, so *any* specific full sentence, out of the astronomically many possible sentences, will have a small absolute probability. What matters for language modeling is not this absolute number but the **relative** ranking: a good model assigns *this* sentence a much higher probability than a garbled alternative like "Where us we goings," and it is this relative-ranking behavior that both training (maximize likelihood of real sentences) and evaluation (perplexity, Section 4.4) actually depend on.

---

## Worked Example 2 — One-Hot Cosine Similarity

**Setup.** Vocabulary $\{$the, cat, sat$\}$, $V=3$. One-hot vectors: $e_{\text{the}}=(1,0,0)$, $e_{\text{cat}}=(0,1,0)$, $e_{\text{sat}}=(0,0,1)$.

**Computation.**
$$e_{\text{cat}}\cdot e_{\text{sat}} = (0)(0)+(1)(0)+(0)(1) = 0, \qquad \lVert e_{\text{cat}}\rVert = \lVert e_{\text{sat}}\rVert = \sqrt{0^2+1^2+0^2}=1$$
$$\cos(e_{\text{cat}}, e_{\text{sat}}) = \frac{0}{1\times1} = 0$$

**Reading the result.** This holds for **any** two distinct one-hot vectors in **any** vocabulary size $V$ — the computation above generalizes immediately, which is exactly why Section 3.3 states the failure as an absolute, not an approximate, fact: one-hot vectors are **always exactly orthogonal**, never "somewhat similar."

---

## Worked Example 3 — Slide Attention Weighted Sum for "sat"

**Setup.** From Lecture 9, p. 16: query word "sat," attention scores over the six words of "The cat sat on the mat": $\alpha = [0.05,\ 0.10,\ 0.60,\ 0.05,\ 0.15,\ 0.05]$ (these sum to 1.00, confirmed). The slide does not give the actual embedding vectors, so — purely to make the weighted-sum mechanics concrete and hand-checkable — assign simple illustrative 2D value vectors:

| Word | Value vector $v_i$ |
|---|---|
| The | $(1, 0)$ |
| cat | $(0, 1)$ |
| sat | $(1, 1)$ |
| on | $(-1, 0)$ |
| the | $(0.5, 0.5)$ |
| mat | $(0, -1)$ |

**Computation.** $\text{output} = \sum_i \alpha_i v_i$:
$$
\begin{aligned}
\text{output} &= 0.05(1,0) + 0.10(0,1) + 0.60(1,1) + 0.05(-1,0) + 0.15(0.5,0.5) + 0.05(0,-1)\\
&= (0.05,0) + (0,0.10) + (0.60,0.60) + (-0.05,0) + (0.075,0.075) + (0,-0.05)\\
&= \big(0.05+0-0.05+0.075+0,\ \ 0+0.10+0.60+0+0.075-0.05\big)\\
&= (0.675,\ 0.725)
\end{aligned}
$$

**Reading the result.** The new representation of "sat" is $(0.675, 0.725)$ — visibly pulled most strongly toward "sat"'s own value vector $(1,1)$ (weight 0.60) and secondarily toward "the" (weight 0.15) and "cat" (weight 0.10), with negligible pull from "The," "on," and "mat" (weight 0.05 each). This is the numeric essence of Section 3.12's claim: the output is a genuinely new vector, assembled by *selectively* blending the other tokens' content in proportion to relevance.

---

## Worked Example 4 — Full Hand-Computed Self-Attention

This is the single most exam-relevant worked example in this chapter — a **complete**, from-scratch self-attention computation with real (if small) $Q$, $K$, $V$ matrices.

**Setup.** Three tokens — "I," "love," "ML" — with 2-dimensional input embeddings, packed as rows of $X$:
$$X = \begin{pmatrix}1 & 0\\ 0 & 1 \\ 1 & 1\end{pmatrix} \begin{matrix}\leftarrow \text{I}\\ \leftarrow\text{love}\\ \leftarrow\text{ML}\end{matrix}$$
Let $W^Q = W^K = I$ (the $2\times2$ identity, for arithmetic simplicity — so $Q=K=X$), and $W^V = \begin{pmatrix}0&1\\1&0\end{pmatrix}$ (swaps the two coordinates).

**Step 1 — compute $Q$, $K$, $V$.**
$$Q = K = X = \begin{pmatrix}1&0\\0&1\\1&1\end{pmatrix}, \qquad V = XW^V = \begin{pmatrix}0&1\\1&0\\1&1\end{pmatrix}$$
(row 1: $(1,0)\to(0,1)$; row 2: $(0,1)\to(1,0)$; row 3: $(1,1)\to(1,1)$, unchanged since it's symmetric.)

**Step 2 — raw scores $QK^\top$** (every pairwise dot product):
$$QK^\top = \begin{pmatrix}1&0&1\\0&1&1\\1&1&2\end{pmatrix}$$
(e.g., row 1, col 3: $q_{\text{I}}\cdot k_{\text{ML}} = (1,0)\cdot(1,1) = 1$; row 3, col 3: $q_{\text{ML}}\cdot k_{\text{ML}}=(1,1)\cdot(1,1)=2$.)

**Step 3 — scale by $\sqrt{d_k}=\sqrt{2}\approx1.4142$:**
$$\frac{QK^\top}{\sqrt{2}} = \begin{pmatrix}0.7071 & 0 & 0.7071\\ 0 & 0.7071 & 0.7071\\ 0.7071 & 0.7071 & 1.4142\end{pmatrix}$$

**Step 4 — softmax, row-wise.** Row 1, $[0.7071,\ 0,\ 0.7071]$: $e^{0.7071}=2.0281$, $e^0=1$; sum $=2.0281+1+2.0281=5.0562$ → weights $= [2.0281/5.0562,\ 1/5.0562,\ 2.0281/5.0562] \approx [0.4011,\ 0.1978,\ 0.4011]$.
Row 2 is the same pattern permuted: $[0.1978,\ 0.4011,\ 0.4011]$.
Row 3, $[0.7071,\ 0.7071,\ 1.4142]$: → weights $\approx [0.2483,\ 0.2483,\ 0.5035]$.
$$\text{Attention weights} = \begin{pmatrix}0.4011 & 0.1978 & 0.4011\\ 0.1978 & 0.4011 & 0.4011\\ 0.2483 & 0.2483 & 0.5035\end{pmatrix}$$

**Step 5 — weighted sum with $V$** (this row of weights times $V$, for each token):
$$
\begin{aligned}
\text{out}_{\text{I}} &= 0.4011(0,1)+0.1978(1,0)+0.4011(1,1) = (0.5989,\ 0.8022)\\
\text{out}_{\text{love}} &= 0.1978(0,1)+0.4011(1,0)+0.4011(1,1) = (0.8022,\ 0.5989)\\
\text{out}_{\text{ML}} &= 0.2483(0,1)+0.2483(1,0)+0.5035(1,1) = (0.7517,\ 0.7517)
\end{aligned}
$$

**Reading the result.** Notice "I" and "love" get *mirror-image* outputs $(0.5989,0.8022)$ vs. $(0.8022,0.5989)$ — a direct consequence of $X$ and $W^V$'s symmetric construction (swapping which token is "I" vs. "love" swaps the coordinates) — while "ML," being equally similar to both other tokens (its raw scores to "I" and "love" are both exactly 1), gets a perfectly symmetric output $(0.7517,0.7517)$. This symmetry is a useful **sanity check** you can build into your own exam answers: if your constructed example has an obvious symmetry, your computed output should respect it — if it doesn't, you've made an arithmetic error.

---

## Worked Example 5 — Multi-Head Attention Toy Example

**Setup.** Extend Example 4 to $d_{model}=4$, split into $h=2$ heads of $d_k=2$ each. Full embeddings:
$$X = \begin{pmatrix}1&0&1&1\\0&1&1&-1\\1&1&2&0\end{pmatrix}\begin{matrix}\leftarrow\text{I}\\\leftarrow\text{love}\\\leftarrow\text{ML}\end{matrix}$$
**Head A** uses columns 1–2 (identical to Example 4's setup: $X_A=\begin{pmatrix}1&0\\0&1\\1&1\end{pmatrix}$, $W^Q_A=W^K_A=I$, $W^V_A=\begin{pmatrix}0&1\\1&0\end{pmatrix}$) — so Head A's output is **exactly** Example 4's result:
$$\text{Head A output} = \begin{pmatrix}0.5989 & 0.8022\\ 0.8022 & 0.5989\\ 0.7517 & 0.7517\end{pmatrix}$$

**Head B** uses columns 3–4: $X_B = \begin{pmatrix}1&1\\1&-1\\2&0\end{pmatrix}$, with $W^Q_B=W^K_B=W^V_B=I$ (identity, for simplicity — so $Q_B=K_B=V_B=X_B$).

Raw scores $Q_BK_B^\top$:
$$\begin{pmatrix}2&0&2\\0&2&2\\2&2&4\end{pmatrix}\quad\text{(e.g., }(1,1)\cdot(1,1)=2\text{; }(1,1)\cdot(1,-1)=0\text{; }(2,0)\cdot(2,0)=4\text{)}$$
Scaled by $\sqrt2$: $\begin{pmatrix}1.4142&0&1.4142\\0&1.4142&1.4142\\1.4142&1.4142&2.8284\end{pmatrix}$.

Softmax, row-wise (verified numerically):
$$\text{Head B weights} = \begin{pmatrix}0.4458&0.1084&0.4458\\0.1084&0.4458&0.4458\\0.1636&0.1636&0.6728\end{pmatrix}$$
Weighted sum with $V_B=X_B$:
$$\text{Head B output} = \begin{pmatrix}1.4458 & 0.3374\\ 1.4458 & -0.3374\\ 1.6728 & 0.0000\end{pmatrix}$$

**Concatenate the two heads** (3 tokens × 4 dims):
$$\text{Concat} = \begin{pmatrix}0.5989&0.8022&1.4458&0.3374\\0.8022&0.5989&1.4458&-0.3374\\0.7517&0.7517&1.6728&0.0000\end{pmatrix}$$
**Final linear projection $W^O$.** Using $W^O=I_4$ (identity, so the final output equals the concatenation exactly — in a real trained model, $W^O$ would learn to mix information *across* heads, not just pass it through):
$$\text{MultiHead output} = \text{Concat}$$

**Reading the result.** This is the complete mechanical pipeline of Section 3.14: two independent attention computations (different subspaces, different — here, deliberately different — weighting patterns: compare Head A's weights to Head B's weights, e.g., for "I": Head A gives $[0.4011,0.1978,0.4011]$ vs. Head B's $[0.4458,0.1084,0.4458]$, a *different* relevance pattern from a *different* projection), concatenated into one wider vector, then linearly re-mixed by $W^O$ into the layer's final output.

---

## Worked Example 6 — Word Analogy by Vector Arithmetic

**Setup.** Toy 2D embeddings constructed to satisfy the analogy $v_{\text{king}}-v_{\text{man}}+v_{\text{woman}}\approx v_{\text{queen}}$:

| Word | Vector |
|---|---|
| man | $(3.0,\ 1.0)$ |
| woman | $(3.0,\ 4.0)$ |
| king | $(5.5,\ 1.5)$ |
| queen | $(5.5,\ 4.5)$ |

**Computation.**
$$v_{\text{king}} - v_{\text{man}} + v_{\text{woman}} = (5.5,1.5) - (3.0,1.0) + (3.0,4.0) = (2.5,0.5) + (3.0,4.0) = (5.5,\ 4.5)$$
This equals $v_{\text{queen}} = (5.5, 4.5)$ **exactly**, by construction.

**Reading the result.** The vector $(2.5, 0.5) = v_{\text{king}}-v_{\text{man}}$ represents "the direction of becoming royal" — and adding that *same* direction to `woman` lands exactly on `queen`. In real, trained Word2Vec embeddings, this relationship holds only **approximately** (the analogy is a well-documented emergent property, not an exact algebraic guarantee) — but the exercise of constructing toy vectors that satisfy it exactly is a good way to internalize *what the analogy claim actually means geometrically*: parallel, equal-length displacement vectors between analogous pairs.

---

## Worked Example 7 — Positional Encoding Values

**Setup.** $d_{model}=4$, so there are two frequency channels: $i=0$ (divisor $10000^{0/4}=1$) and $i=1$ (divisor $10000^{2/4}=100$). Formula:
$$PE(pos,0)=\sin(pos),\quad PE(pos,1)=\cos(pos),\quad PE(pos,2)=\sin(pos/100),\quad PE(pos,3)=\cos(pos/100)$$

**Computation**, for $pos=0,1,2,3$ (verified numerically to 4 decimal places):

| $pos$ | $PE_{,0}=\sin(pos)$ | $PE_{,1}=\cos(pos)$ | $PE_{,2}=\sin(pos/100)$ | $PE_{,3}=\cos(pos/100)$ |
|---|---|---|---|---|
| 0 | 0.0000 | 1.0000 | 0.0000 | 1.0000 |
| 1 | 0.8415 | 0.5403 | 0.0100 | 1.0000 |
| 2 | 0.9093 | −0.4161 | 0.0200 | 0.9998 |
| 3 | 0.1411 | −0.9900 | 0.0300 | 0.9996 |

**Reading the result.** Columns 0–1 (fast frequency, period $2\pi\approx6.28$) change dramatically from row to row — $\sin(pos)$ swings from $0$ to $0.84$ to $0.91$ to $0.14$ across just 4 positions. Columns 2–3 (slow frequency, period $200\pi\approx628$) barely move — $\sin(pos/100)$ crawls from $0$ to $0.03$. This is the numeric confirmation of Section 3.15's claim: different dimensions encode position at genuinely different "clock speeds," and it is the *combination* across all $d_{model}$ dimensions, fast and slow together, that makes every position's full encoding vector unique.


---

# 7. Concept Connections — The Big Picture

## 7.1 The Full Timeline

```
N-gram models              "predict next word from last (n-1) words only"
       │                    (Markov assumption; no learned representation at all)
       ▼
Neural Language Models      predict next word using a neural net over word history
       │                    (still needs a way to represent words as input → embeddings)
       ▼
Word Embeddings              one-hot  →  dense, learned vectors (Word2Vec: Skip-gram / CBOW)
(Sec 3.3–3.5)                 STATIC: one vector per word type, no matter the sentence
       │
       ▼
Recurrent Neural Networks     give the network a hidden state → sequences of any length
(Sec 3.6)                     STILL sequential: must compute h_1 before h_2 before h_3...
       │
       ▼
Vanishing/Exploding            plain RNNs forget after ~20 steps (Sec 3.7–3.8)
Gradients
       │
       ▼
LSTM (Sec 3.9) / GRU (3.10)    additive "conveyor belt" cell state fixes long-range memory
       │                        (still sequential — doesn't fix the parallelism problem)
       ▼
Seq2Seq Bottleneck (3.11)       encoder-decoder squeezes whole input into ONE vector
       │                        BLEU score collapses on long sentences
       ▼
Attention (3.12)                 let decoder look back at EVERY encoder state, weighted by relevance
       │                          (bolted onto an RNN encoder-decoder — Bahdanau et al., 2014)
       ▼
Self-Attention (3.13)             every token attends to every OTHER token in the SAME sequence
       │                           → produces CONTEXTUAL embeddings (fixes Word2Vec's static-vector problem)
       ▼
Multi-Head Attention (3.14)        run several attention "lanes" in parallel subspaces
       │
       ▼
Positional Encoding (3.15)         patch in order-information (self-attention is order-blind)
       │
       ▼
The Transformer (3.16)             attention + FFN + residuals + layernorm, NO recurrence at all
       │                            → fully parallelizable training, O(1) path length between any 2 tokens
       ▼
Modern LLMs (GPT, BERT, T5, ...)    decoder-only / encoder-only / encoder-decoder Transformers,
                                     pretrained via self-supervised next-token or masked-token prediction
                                     (Sec 3.2, Sec 3.5) at massive scale
```

## 7.2 Why the Course Places This Lecture Last

Every earlier lecture is a *prerequisite tool* this chapter cashes in:

| Earlier lecture | What it supplies here |
|---|---|
| **L2 (Probability & Statistics)** | The chain rule underlying the entire language-modeling objective (Sec 3.2); MLE as the justification for cross-entropy loss (Sec 4.4) |
| **L3–L4 (Linear/Logistic Regression, Regularization)** | Gradient descent as the training mechanism throughout; the sigmoid derivative bound (max $0.25$) reappears verbatim in the vanishing-gradient derivation (Sec 3.8) |
| **L6 (Neural Networks, UAT)** | RNNs, LSTMs, and Transformer feedforward blocks are all just neural networks with extra structure; UAT's promise ("networks *can* represent almost anything") is exactly what motivates trusting a big enough Transformer to represent complex language phenomena, while UAT's *silence on trainability* is exactly why vanishing gradients (a trainability problem, not a representational-capacity problem) needed a separate fix |
| **L7 (Evaluation Metrics)** | BLEU (seq2seq bottleneck evidence, Sec 3.11) and perplexity (Sec 4.4) are both evaluation metrics in exactly Lecture 7's sense — a language model or translation system is only as good as what these metrics can certify |
| **L8 (CNNs)** | Weight sharing (CNN: same filter across space; RNN: same weights across time, Sec 3.6) is a direct, examinable analogy; the failure of "fixed receptive field" convolutions to capture long-range dependencies (Sec 3.1) is precisely the gap self-attention closes |

## 7.3 One Thread Worth Isolating: "How Do We Fix a Bottleneck?"

Three *different* techniques in this chapter are all, structurally, "stop forcing information through one narrow channel":

1. **LSTM's cell state** replaces the RNN hidden state's *single*, repeatedly-overwritten channel with an additive conveyor belt that preserves information across time.
2. **Attention** replaces the seq2seq encoder's *single* fixed-size context vector with a per-step, re-weighted combination of *all* encoder states.
3. **Residual connections** (Sec 4.7) replace a deep stack's *single*, purely-multiplicative gradient path with an additive identity shortcut at every layer.

All three are instances of the same underlying principle: **when a multiplicative/single-summary pathway causes information or gradients to degrade, add a parallel additive pathway that lets them bypass the degradation.** This is an excellent higher-order exam answer if asked to find a unifying theme across LSTM, attention, and residual connections.


---

# 8. Exam Preparation

## 8.1 High-Yield Facts

- Chain rule: $P(S) = \prod_{t=1}^T P(w_t\mid w_{<t})$.
- One-hot's three named failures: dimensionality, no similarity (cosine sim $=0$ always), no generalization.
- Skip-gram: center → context. CBOW: context → center.
- Firth (1957): *"You shall know a word by the company it keeps."*
- RNN recurrence: $h_t = f(W_{hh}h_{t-1}+W_{xh}x_t+b_h)$; **one shared weight set across all $T$ steps.**
- Plain RNNs forget after **~20 steps** (vanishing gradients); $0.25^{20}\approx9.1\times10^{-13}$.
- $\max|\tanh'(z)|=1$; $\max|\sigma'(z)|=0.25$.
- LSTM's 6 equations, in order: forget $f_t$, input $i_t$, candidate $\tilde c_t$, cell update $c_t=f_t\odot c_{t-1}+i_t\odot\tilde c_t$, output $o_t$, hidden $h_t=o_t\odot\tanh(c_t)$.
- Seq2seq bottleneck: BLEU falls from 92% (10 words) to 22% (60 words) as sentence length grows — direct empirical proof.
- Attention: $\text{output}=\sum_i \alpha_i v_i$, $\alpha=\text{softmax}(\text{scores})$.
- Self-attention: $\text{Attention}(Q,K,V)=\text{softmax}\!\left(\frac{QK^\top}{\sqrt{d_k}}\right)V$.
- Scaling by $\sqrt{d_k}$: because $\text{Var}(q\cdot k)=d_k$ when components are i.i.d. mean-0 variance-1 — dividing by $\sqrt{d_k}$ restores unit variance and prevents softmax saturation.
- Multi-head attention: $\text{MultiHead}(Q,K,V)=\text{Concat}(\text{head}_1,\dots,\text{head}_h)W^O$; base Transformer uses $h=8$, $d_k=d_v=64$, $d_{model}=512$.
- Positional encoding: $PE_{(pos,2i)}=\sin(pos/10000^{2i/d_{model}})$, $PE_{(pos,2i+1)}=\cos(pos/10000^{2i/d_{model}})$ — fixed, not learned, in the original paper.
- Transformer base hyperparameters (Vaswani et al., 2017): $N=6$ layers, $d_{model}=512$, $h=8$, $d_{ff}=2048$, dropout $0.1$, label smoothing $0.1$, Adam ($\beta_1=0.9,\beta_2=0.98,\epsilon=10^{-9}$), warmup steps $=4000$.
- Three places attention appears in the full architecture: encoder self-attention, decoder masked self-attention, encoder-decoder cross-attention.
- Self-attention cost: $O(n^2d)$ (quadratic in sequence length, but fully parallel); RNN cost: $O(nd^2)$ (linear, but sequential).

## 8.2 Common Student Mistakes

1. **Dropping the $\sqrt{d_k}$ scaling** when writing the attention formula from memory, or forgetting *why* it's there (the variance argument, not just "to make numbers smaller").
2. **Swapping the forget-gate/input-gate roles** in the LSTM cell-update equation.
3. **Conflating "attention" with "Transformer."** Attention (Bahdanau, 2014) predates and does not require the Transformer; the Transformer (2017) is what removed recurrence entirely.
4. **Forgetting BPTT's outer sum over time steps** when writing $\partial L/\partial W_{hh}$ — treating it as if only the last time step contributed.
5. **Believing Word2Vec produces contextual embeddings.** It produces exactly **one static vector per word type** — this is the single most consequential misconception in the whole chapter, since it is the direct motivation for everything from Section 3.12 onward.
6. **Thinking more attention heads is strictly better**, ignoring the $d_k=d_{model}/h$ trade-off.
7. **Believing positional encoding is re-added at every layer.** It's added once, at the input, and persists via residual connections.
8. **Confusing encoder self-attention (bidirectional) with decoder self-attention (masked/causal).**
9. **Forgetting the cross-attention arrow feeds *every* decoder layer**, not just the first one, from the encoder's final output.

## 8.3 Professor Trap Questions

> [!warning] These are the kind of "true fact about a slightly different concept" traps this course is known for (per your established course-pattern notes). Read the precise qualifier before selecting an answer.

1. *"One-hot encoding fails primarily because it cannot represent out-of-vocabulary words."* — **Trap**: true statement, but **not one of the three failures the slide names** (dimensionality, no similarity, no generalization).
2. *"LSTMs completely eliminate the vanishing gradient problem."* — **Trap**: they substantially mitigate it via the additive cell state, but the gate sigmoids still saturate; "completely eliminate" overstates it.
3. *"Self-attention has no learnable parameters."* — **Trap**: the similarity/softmax computation itself has none, but $W^Q, W^K, W^V$ (and $W^O$ for multi-head) are learned.
4. *"Multi-head attention is more computationally expensive than single-head attention with the same total dimensionality."* — **Trap**: by construction ($h\times d_k = d_{model}$), the total compute is comparable — the paper explicitly notes this.
5. *"Attention was introduced by the 'Attention Is All You Need' paper."* — **Trap**: attention itself is Bahdanau et al., 2014; Vaswani et al., 2017 introduced the **Transformer** (attention *without* recurrence) — different contributions, three years apart.
6. *"Positional encodings are learned parameters in the original Transformer."* — **Trap**: they are a fixed sinusoidal function; the paper notes learned embeddings were tried too and performed similarly, but the fixed version is what's in the canonical architecture (and was preferred for its extrapolation property).
7. *"Since GRUs and LSTMs are both gated RNNs, their gates play identical roles."* — **Trap**: GRU's single update gate $z_t$ ties "keep old" and "write new" together (they sum to 1 via $(1-z_t)$ and $z_t$); LSTM's forget and input gates are computed independently and need not be complementary.

## 8.4 Frequently Confused Concepts

| Concept A | Concept B | The distinction |
|---|---|---|
| Skip-gram | CBOW | Skip-gram: center word → predict context. CBOW: context words → predict center. |
| Self-attention | Cross-attention | Self-attention: $Q,K,V$ all from the *same* sequence. Cross-attention: $Q$ from one sequence (decoder), $K,V$ from another (encoder). |
| Encoder self-attention | Decoder self-attention | Encoder: bidirectional/unmasked (every token sees every other). Decoder: masked/causal (token $t$ only sees tokens $\le t$). |
| LSTM | GRU | LSTM: 3 gates + separate cell state $c_t$ and hidden state $h_t$. GRU: 2 gates, single state, update gate ties "keep"/"write" together. |
| Bahdanau (additive) attention | Luong / dot-product attention | Additive: score $= v^\top\tanh(W_1h+W_2s)$, a small feedforward net. Dot-product (used by Transformers): score $=q\cdot k$ (or scaled), just a dot product — cheaper, and what scales to modern architectures. |
| Static embeddings (Word2Vec) | Contextual embeddings (Transformer output) | Static: one fixed vector per word type, forever. Contextual: a *different* vector for the same word depending on its sentence, produced by (self-)attention. |
| Batch normalization | Layer normalization | Batch norm: normalizes across the **batch** dimension per feature. Layer norm (used in Transformers): normalizes across the **feature** dimension per example/token — better suited to variable-length sequences. |
| Vanishing gradients | Exploding gradients | Vanishing: repeated multiplication by factors $<1$ → gradient $\to0$; hard to fix architecturally (motivated LSTM). Exploding: repeated multiplication by factors $>1$ → gradient $\to\infty$/NaN; easy fix exists (gradient clipping). |


---

# 9. Practice Questions with Full Solutions

## A. Conceptual Questions

**Q1.** Explain why images can be represented as fixed-size tensors but sentences cannot. Name all three specific failure points the lecture identifies for naive language representations.

> **Solution.** Images have a fixed $H\times W\times C$ shape by construction (a photo is always some agreed pixel grid), so a fixed-size input tensor is a natural fit. Sentences have no such fixed shape — they vary in length token by token — so flattening a sentence into one fixed-size vector either truncates/pads awkwardly or is simply undefined for token counts beyond what was fixed at design time. The lecture names three specific failure points: (1) images have a fixed shape while sentences have variable length, so you can't flatten a sentence the way you flatten an image; (2) word meaning depends on context ("I never said Messi cheated" has multiple readings depending on stress/context), which a context-blind representation cannot capture; (3) convolutional sliding windows have a fixed receptive field and cannot capture arbitrarily long-range dependencies between words far apart in a sentence.

**Q2.** State the distributional hypothesis and explain how it justifies why Word2Vec's self-supervised training produces *meaningful* embeddings rather than an arbitrary arrangement of vectors.

> **Solution.** The distributional hypothesis (Firth, 1957): "You shall know a word by the company it keeps" — words appearing in similar contexts tend to have similar meanings. Word2Vec trains embeddings on a manufactured prediction task (Skip-gram: center word → context words; CBOW: context → center) using nothing but raw, unlabeled text. Because gradient descent is pushed to make correct context predictions, whenever two words $w_i, w_j$ co-occur frequently with the same neighboring words, their embeddings are repeatedly nudged toward each other during training (both need to produce similar output-context predictions). Over a large corpus, words that are distributionally similar (appear in similar contexts) converge to nearby points in embedding space — not because "similarity" was ever explicitly written into the loss function, but as an emergent consequence of the prediction task combined with the distributional hypothesis being empirically true of real language.

**Q3.** Why is self-attention described as "permutation-equivariant," and what problem does this create that positional encoding is designed to solve?

> **Solution.** Self-attention computes, for each token, a weighted sum over all other tokens' values, where the weights come from query-key dot products — none of these operations reference a token's *position* in the sequence, only its *content* (embedding). If you permute (shuffle) the order of input tokens, the attention computation produces the exact same set of outputs, correspondingly permuted — the mechanism itself has no notion of "first," "second," "adjacent." This creates a problem because word order carries meaning in language ("the cat chased the dog" vs. "the dog chased the cat" would look identical to a positionally-blind self-attention layer, since both contain the same multiset of tokens). Positional encoding solves this by adding a fixed, position-dependent vector to each token's embedding before the first attention layer, so that position information is available to the model as part of each token's content, even though the attention mechanism itself remains order-agnostic.

## B. Short-Answer Questions

**Q4.** State the LSTM cell-state update equation and explain in one sentence why it is additive rather than multiplicative.

> **Solution.** $c_t = f_t\odot c_{t-1} + i_t \odot \tilde{c}_t$. It is additive so that, when the forget gate $f_t\approx1$, gradients can flow backward through the cell state across many time steps with a multiplier close to 1 (rather than being repeatedly passed through a weight matrix and a saturating nonlinearity, as in a plain RNN's hidden state), which is what prevents the vanishing-gradient problem from recurring inside the LSTM.

**Q5.** Name the three sub-layers of a single Transformer decoder layer, in the order they appear.

> **Solution.** (1) Masked multi-head self-attention (over the decoder's own generated sequence, causally masked); (2) multi-head cross-attention (decoder queries against encoder keys/values); (3) a position-wise feedforward network. Each is wrapped in a residual connection followed by layer normalization ("Add & Norm").

## C. Mathematical Derivations

**Q6.** Starting from the Jacobian $\dfrac{\partial h_i}{\partial h_{i-1}}$, derive why backpropagating an RNN's gradient across many time steps causes vanishing or exploding gradients.

> **Solution.** For $h_i = \tanh(W_{hh}h_{i-1}+W_{xh}x_i+b_h) = \tanh(z_i)$, the Jacobian is $\dfrac{\partial h_i}{\partial h_{i-1}} = \text{diag}(1-\tanh^2(z_i))\,W_{hh}$ (chain rule through the elementwise $\tanh$ and the linear map $W_{hh}$). To propagate a gradient from time $t$ back to time $k$, these Jacobians are **multiplied together** across every intermediate step:
> $$\frac{\partial h_t}{\partial h_k} = \prod_{i=k+1}^{t}\frac{\partial h_i}{\partial h_{i-1}}$$
> Bounding the norm of each factor by $\lVert W_{hh}\rVert\cdot\max_z|1-\tanh^2(z)| = \lVert W_{hh}\rVert \cdot \max|\tanh'(z)|$, the product's norm is bounded by this quantity raised to the power $(t-k)$ — the number of steps being backpropagated through. If this per-step factor is $<1$, the bound shrinks **exponentially** with $(t-k)$ (vanishing); if $>1$, it grows **exponentially** (exploding). Since $\max|\tanh'(z)|=1$ (attained only exactly at $z=0$) and typical weight initialization keeps $\lVert W_{hh}\rVert$ near 1, the product is highly sensitive to small perturbations either way, and in practice tends toward the vanishing regime for anything beyond a modest number of steps.

**Q7.** Derive why dividing attention scores by $\sqrt{d_k}$ keeps $\text{Var}(q\cdot k)$ equal to 1, assuming the components of $q$ and $k$ are i.i.d. with mean 0 and variance 1.

> **Solution.** $q\cdot k = \sum_{i=1}^{d_k} q_ik_i$. Each term $q_ik_i$ is a product of two independent, mean-0, variance-1 random variables, so $E[q_ik_i] = E[q_i]E[k_i] = 0$ and $\text{Var}(q_ik_i) = E[(q_ik_i)^2] - 0 = E[q_i^2]E[k_i^2] = 1\times1=1$. Since the $d_k$ terms are independent, variances add: $\text{Var}(q\cdot k) = \sum_{i=1}^{d_k}\text{Var}(q_ik_i) = d_k$. Dividing by $\sqrt{d_k}$: $\text{Var}\!\left(\frac{q\cdot k}{\sqrt{d_k}}\right) = \frac{1}{d_k}\text{Var}(q\cdot k) = \frac{d_k}{d_k}=1$ (using $\text{Var}(cX)=c^2\text{Var}(X)$ with $c=1/\sqrt{d_k}$). This restores unit variance regardless of $d_k$, preventing the raw dot product's magnitude from growing with dimensionality and saturating the softmax.

**Q8.** Prove that, for a fixed offset $k$, $PE(pos+k)$ can be written as a linear transformation of $PE(pos)$.

> **Solution.** See the full derivation in Section 4.8. Using the angle-sum identities for a single frequency $\omega$: $PE(pos+k) = \begin{pmatrix}\cos(\omega k)&\sin(\omega k)\\-\sin(\omega k)&\cos(\omega k)\end{pmatrix}PE(pos)$ — a rotation matrix depending only on the offset $k$, not on $pos$ itself, proving the claim.

## D. Numerical Problems

**Q9.** For a 4-word vocabulary $\{$dog, run, fast, tree$\}$, write the one-hot vectors for "run" and "tree" and compute their cosine similarity.

> **Solution.** $e_{\text{run}}=(0,1,0,0)$, $e_{\text{tree}}=(0,0,0,1)$. Dot product $= 0$. Both have norm 1. Cosine similarity $= 0/(1\times1) = 0$ — as with any two distinct one-hot vectors, regardless of vocabulary size or which two words are chosen.

**Q10.** Two tokens, "sun" and "moon," have embeddings $x_{\text{sun}}=(2,0)$, $x_{\text{moon}}=(0,2)$. Let $W^Q=W^K=I$ (identity) and $W^V=\begin{pmatrix}1&0\\0&-1\end{pmatrix}$. Compute the full self-attention output for both tokens.

> **Solution.** $Q=K=X=\begin{pmatrix}2&0\\0&2\end{pmatrix}$, $V=XW^V=\begin{pmatrix}2&0\\0&-2\end{pmatrix}$.
> Raw scores $QK^\top = \begin{pmatrix}4&0\\0&4\end{pmatrix}$ (since $(2,0)\cdot(2,0)=4$, $(2,0)\cdot(0,2)=0$, $(0,2)\cdot(0,2)=4$).
> Scaled by $\sqrt{2}$: $\begin{pmatrix}2.8284&0\\0&2.8284\end{pmatrix}$.
> Softmax, row-wise: row 1 $[2.8284, 0]$ → $e^{2.8284}=16.919$, $e^0=1$, sum$=17.919$ → weights $[0.9442, 0.0558]$; row 2 is the mirror image: $[0.0558, 0.9442]$.
> Weighted sum with $V$: $\text{out}_{\text{sun}} = 0.9442(2,0)+0.0558(0,-2) = (1.8884,\ -0.1116)$; $\text{out}_{\text{moon}} = 0.0558(2,0)+0.9442(0,-2) = (0.1116,\ -1.8884)$.
> Each token's output is dominated by its *own* value vector (since each is maximally similar to itself — score 4 vs. 0 for the other token), with a small ($\sim5.6\%$) contribution bleeding in from the other token.

**Q11.** A 3-token sequence receives per-token predicted probabilities (of the true next token) $0.5, 0.25, 0.2$. Compute the perplexity of this sequence.

> **Solution.** Per-token negative log-likelihoods: $-\ln(0.5)=0.6931$, $-\ln(0.25)=1.3863$, $-\ln(0.2)=1.6094$. Average: $(0.6931+1.3863+1.6094)/3 = 1.2296$. Perplexity $=e^{1.2296} \approx 3.42$. Interpretation: the model's average uncertainty at each step is "as if" it were choosing uniformly among about 3.4 equally-likely next tokens.

## E. Architecture Explanation

**Q12.** Describe, in words, a fully-labeled unrolled RNN diagram for the 4-word sentence "The cat sat down," including every weight matrix.

> **Solution.** Draw an initial hidden state $h_0$ (often zero-initialized). For $t=1,\dots,4$, draw a hidden-state node $h_t$; feed in $x_t$ (the embedding of "The","cat","sat","down" respectively) via an arrow labeled $W_{xh}$; feed in $h_{t-1}$ via an arrow labeled $W_{hh}$; produce an output prediction $\hat y_t$ via an arrow out of $h_t$ labeled $W_{hy}$. Connect $h_0\to h_1\to h_2\to h_3\to h_4$ left to right. Every $W_{xh}$ arrow across all 4 steps is the *same* matrix; likewise for every $W_{hh}$ and every $W_{hy}$ arrow — this weight-sharing, not the diagram's visual repetition, is the defining property of an RNN (contrast with a 4-layer feedforward network, where each layer would have its own independent weights).

**Q13.** Using the encoder-decoder Transformer diagram, trace exactly which components a decoder input token passes through, from its output embedding to the final output probability.

> **Solution.** Output embedding → add positional encoding → masked multi-head self-attention (over previously-generated decoder tokens only) → Add & Norm → multi-head cross-attention (queries from the decoder, keys/values from the **encoder's final output**, which itself required the full $N$-layer encoder stack to be run once, in advance, on the entire input sequence) → Add & Norm → position-wise feedforward network → Add & Norm → (this whole 3-sublayer block repeats for $N$ decoder layers, each one's cross-attention drawing from the *same* encoder output) → final linear projection (mapping $d_{model}\to V$, vocabulary size) → softmax → output probability distribution over the vocabulary for the next token.

## F. Comparison Questions

**Q14.** Compare additive (Bahdanau) attention and scaled dot-product (Transformer) attention along at least three axes.

> **Solution.**
>
> | Axis | Additive (Bahdanau) attention | Scaled dot-product attention |
> |---|---|---|
> | Score function | $v^\top\tanh(W_1h + W_2s)$ — a small feedforward network with learned $v, W_1, W_2$ | $\dfrac{q\cdot k}{\sqrt{d_k}}$ — a plain (scaled) dot product, no extra learned score-network |
> | Computational cost | More expensive per pair (a full small-MLP forward pass per query-key pair) | Cheaper (just a dot product); implementable as efficient matrix multiplication, which is why it scales to modern hardware |
> | Original context | Introduced as an add-on to an RNN encoder-decoder, specifically to fix the seq2seq bottleneck | Introduced as the *sole* mechanism of the Transformer, with recurrence removed entirely |
> | Historical position | 2014 (Bahdanau et al.) | 2017 (Vaswani et al., building on and simplifying the attention idea) |

**Q15.** Compare RNNs and Transformers along parallelizability, path length between distant tokens, and computational complexity.

> **Solution.** **Parallelizability:** RNNs must compute $h_1,h_2,\dots$ strictly in sequence — $h_t$ cannot be computed before $h_{t-1}$ exists — so training cannot be parallelized across the time dimension. Transformers compute self-attention for all tokens simultaneously (given the full sequence), so a training step is fully parallel across the sequence dimension. **Path length between distant tokens:** in an RNN, information from token 1 must pass through $t-1$ recurrent steps to influence token $t$'s representation — an $O(n)$ path length, which is exactly why vanishing gradients degrade long-range dependencies. In a Transformer, self-attention connects every pair of tokens directly in a single layer — an $O(1)$ path length, regardless of distance. **Computational complexity:** an RNN layer costs $O(nd^2)$ (linear in sequence length $n$, quadratic in hidden dimension $d$); a self-attention layer costs $O(n^2d)$ (quadratic in sequence length, linear in dimension) — Transformers trade worse asymptotic scaling in sequence length for full parallelism and short gradient paths, a trade-off that favors Transformers whenever hardware parallelism is cheap relative to sequential depth (the typical modern GPU-training regime).

## G. Higher-Order Reasoning

**Q16.** A colleague argues: "Since Transformers have no recurrence, they cannot model sequences at all — they just process an unordered set." Critique this claim using specific architectural components as evidence.

> **Solution.** The claim is partially right and importantly wrong. It is right that self-attention *by itself* is permutation-equivariant (Section 3.15) — without any additional mechanism, a Transformer layer genuinely would treat its input as an unordered set, exactly as the colleague suggests. It is wrong to conclude Transformers "cannot model sequences at all," because the *full* architecture is not self-attention alone: (1) **positional encoding** is added to every token's embedding specifically to break permutation-equivariance by injecting position-dependent information (Section 3.15); (2) in the **decoder**, self-attention is additionally **causally masked** (Section 3.16), so token $t$ can only attend to tokens $\le t$ — this masking is itself an explicit, hard-coded sequential/ordering constraint, structurally similar in spirit (though not in mechanism) to an RNN's forward-only information flow. Taken together, positional encoding plus causal masking give the full Transformer architecture genuine order-sensitivity — the colleague's claim would be correct only for a *stripped-down*, position-encoding-free, unmasked (bidirectional, encoder-only) self-attention layer in isolation, which is not what "a Transformer" refers to in practice.

**Q17.** Suppose you increase the number of attention heads $h$ from 8 to 64 while keeping $d_{model}=512$ fixed. Predict what happens to model quality and explain the mechanism.

> **Solution.** With $d_{model}=512$ fixed and $h=64$, each head's dimension becomes $d_k=d_v=512/64=8$ (down from $512/8=64$ at $h=8$). Model quality would likely **degrade**, for a mechanistic reason directly derivable from Section 3.13–3.14: each head's $Q$/$K$/$V$ projections now operate in an 8-dimensional subspace, which is a very low-dimensional space in which to represent a useful notion of "relevance" between tokens — the projection has much less room to encode a rich matching function, and empirically (per the original paper's own ablation study, Table 3) both too few and too many heads underperform the chosen middle ground ($h=8$, $d_k=64$), because very small per-head dimensions cause each head to have insufficient representational capacity for its Q/K similarity computation, even though the *total* compute cost stays roughly constant (per Section 3.14's parameter-conservation argument, $h\times d_k = d_{model}$ regardless of $h$). This question tests whether a student understands that multi-head attention's total-compute-conservation property does **not** mean head count is a free parameter — the per-head dimension $d_k$ is doing real representational work, and shrinking it too far has a real cost.


---

# 10. References

## 10.1 Cited directly on the source slides

These appear on Lecture 9 p. 17 ("Textbook Chapters") and Maths Behind Transformers p. 14 ("References"), reproduced here with the sections of this book they support:

1. **Goodfellow, Bengio & Courville**, *Deep Learning*, MIT Press, 2016 — cited on the slide as "Chapter 9." Supports Sections 3.6–3.9 (RNNs, BPTT, LSTMs).
   > [!danger] **Course/slide discrepancy**
   > Verified against the publisher's own table of contents: **Chapter 9** of *Deep Learning* is **Convolutional Networks**; **Sequence Modeling: Recurrent and Recursive Nets** — the chapter actually covering this lecture's RNN/LSTM content — is **Chapter 10**. This is very likely a slide typo (off-by-one chapter reference), in the same family as the previously-documented "High Bias, High Variance" labelling issue in your main concept book. If an assessment item quotes the slide's citation directly, answer per the slide; otherwise, cite Chapter 10 as the standard reference.
2. **Alpaydın, E.**, *Introduction to Machine Learning*, MIT Press — cited on the slide as "Chapter 12." Chapter numbering for this book varies meaningfully by edition (the widely-used 2nd/3rd edition's Chapter 12 is "Local Models," on RBF/mixture-of-experts-style methods, unrelated to sequence modeling); the 4th edition added a new deep-learning chapter and new RNN/word2vec material inside the Multilayer Perceptrons chapter, which plausibly shifted numbering such that "Chapter 12" in the edition your course uses corresponds to this lecture's content. Treat this citation as edition-dependent rather than a firm error.
3. **Mikolov et al.**, *Embeddings in Machine Learning Explained* (referenced resource #1, Maths Behind Transformers p. 14). Supports Section 3.4.
4. **Jay Alammar**, *The Illustrated Word2vec* (referenced resource #2). Supports Sections 3.4–3.5.
5. *Large Language Models* [Playlist] (referenced resource #3) — general background for Section 3.17.
6. **Jay Alammar** (attributed style), *Illustrated Guide to Transformers Neural Network: A Step-by-Step Explanation* (referenced resource #4). Supports Sections 3.13–3.16 and Section 5.
7. *The Neuroscience of "Attention"* (referenced resource #5) — cited as background motivation for the attention mechanism's name/metaphor (Section 3.12).
8. **University of Waterloo**, *CS480/680 Lecture 19: Attention and Transformer Networks* (referenced resource #6). Supports Sections 3.13–3.16.
9. Lecture 9's own "Recommended Resources" (p. 18): *Meme search using pretrained word2vec*; *Recurrent Neural Networks (RNNs)* [external resource, title only on slide].

## 10.2 Additional authoritative sources used to fill gaps and derivations in this book

10. **Vaswani, A. et al.**, *Attention Is All You Need*, NeurIPS 2017 (arXiv:1706.03762). The primary source for Sections 3.13–3.16, Section 4.5–4.9, and Section 5.13–5.15 — every architecture diagram, hyperparameter ($N=6$, $d_{model}=512$, $h=8$, $d_k=d_v=64$, $d_{ff}=2048$, dropout $0.1$, label smoothing $0.1$, warmup steps $4000$, Adam $\beta_1=0.9,\beta_2=0.98,\epsilon=10^{-9}$), and formula in this section of the book traces back to this paper.
11. **Bahdanau, D., Cho, K. & Bengio, Y.**, *Neural Machine Translation by Jointly Learning to Align and Translate*, ICLR 2015 (arXiv:1409.0473). Supports Section 3.12 (original attention mechanism) and Section 8.4 (additive attention comparison).
12. **Mikolov, T. et al.**, *Efficient Estimation of Word Representations in Vector Space*, ICLR 2013 (arXiv:1301.3781) and *Distributed Representations of Words and Phrases and their Compositionality*, NeurIPS 2013. The original Word2Vec papers; support Section 3.4's Skip-gram/CBOW formalization.
13. **Hochreiter, S. & Schmidhuber, J.**, *Long Short-Term Memory*, Neural Computation, 1997. The original LSTM paper; supports Section 3.9.
14. **Cho, K. et al.**, *Learning Phrase Representations using RNN Encoder-Decoder for Statistical Machine Translation*, EMNLP 2014 (arXiv:1406.1078). Introduces the GRU; supports Section 3.10's gap-fill.
15. **Pascanu, R., Mikolov, T. & Bengio, Y.**, *On the Difficulty of Training Recurrent Neural Networks*, ICML 2013 (arXiv:1211.5063). Formal treatment of vanishing/exploding gradients; supports Sections 3.8 and 4.2.
16. **Firth, J. R.**, "A Synopsis of Linguistic Theory 1930–1955," in *Studies in Linguistic Analysis*, 1957 — the original source of the quote in Section 3.5.
17. **Dosovitskiy, A. et al.**, *An Image is Worth 16x16 Words: Transformers for Image Recognition at Scale*, ICLR 2021 (arXiv:2010.11929). Supports Section 3.17 (Vision Transformer).

## 10.3 Which sections benefited from which references

| Section(s) | Primary reference(s) |
|---|---|
| 3.1–3.2 (Language as data, LM task) | Lecture 9 slides; general NLP background |
| 3.3–3.5 (One-hot, Word2Vec, distributional semantics) | Lecture 9 slides; Mikolov et al. 2013 (×2); Firth 1957; *The Illustrated Word2vec* |
| 3.6–3.10 (RNN, BPTT, vanishing gradients, LSTM, GRU) | Lecture 9 slides; Goodfellow et al. Ch. 10; Hochreiter & Schmidhuber 1997; Cho et al. 2014; Pascanu et al. 2013 |
| 3.11–3.12 (Bottleneck, attention) | Lecture 9 slides; Bahdanau et al. 2015; Maths Behind Transformers slides |
| 3.13–3.16 (Self-attention, multi-head, positional encoding, Transformer) | Maths Behind Transformers slides; Vaswani et al. 2017; *CS480/680 Lecture 19*; *Illustrated Guide to Transformers* |
| 3.17 (Beyond NLP) | Dosovitskiy et al. 2021; general background |
| Section 4 (Math deep dive) | Vaswani et al. 2017; Pascanu et al. 2013; standard backpropagation/softmax theory |
| Section 5 (Diagrams) | Direct visual analysis of both source decks (this book's own primary contribution) |
| Section 6 (Worked examples) | Constructed and numerically verified for this book (NumPy-checked); slide 16's attention-weight values are the one directly slide-sourced numeric input |

---

*End of chapter. Cross-reference: this document is designed to sit alongside `ML_Concept_Book.md` as the Lecture 9 / Transformers companion — the notation, callout conventions, and per-concept structure match that book so the two can be studied as one continuous course.*
