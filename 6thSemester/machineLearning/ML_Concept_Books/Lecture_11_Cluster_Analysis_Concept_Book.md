# Cluster Analysis — Concept Book
**CSE 4621: Machine Learning | Lecture 11 | Ishmam Tashdeed, CSE, IUT**
*A study companion built from the 31-slide lecture deck, expanded for depth*

---

### How to read this book

Three tags run through every section:

- 🎓 **Lecture** — what the slide deck actually says (paraphrased in full sentences — the slides themselves are bullet-point telegraphic)
- 💡 **Explained** — reasoning, derivations, and connective tissue Claude adds to fill the gaps the slides leave open
- 🌐 **External** — a concept the slides gesture at but don't define, brought in from a textbook, paper, or documentation, with a source noted

The lecture has 31 slides for an entire topic in unsupervised learning, so a lot of it is compressed into single lines ("Repeat until no change of centroids") that hide real mathematical content. This book keeps the lecture's exact sequence and topic order, and unpacks each step.

One editorial note up front, because precision matters for this project: **Slide 15 labels the K-Medoids centroid update as "the median of the cluster."** This is the lecture's own wording, not a transcription artifact — but it's a simplification worth flagging early, because "median" and "medoid" are different objects (see §2.I and §3.2). Everywhere below, 🎓 tags report what the slide says even where 💡/🌐 tags go on to correct or sharpen it.

---

## 1. Big Picture

**🎓 Lecture.** Slide 3 frames the whole topic with one sentence: unsupervised learning means finding undetected patterns in a dataset that has no pre-existing labels, with minimum human supervision. Cluster analysis and PCA are given as the two named tools under that umbrella. The motivating example is a recommendation engine — grouping content or users by their activity so that "similar" items can be suggested to each other (slide 3's diagram shows this split into content-based filtering vs. collaborative filtering, both of which lean on some notion of grouping similar things).

Slide 5 gives the formal-ish definition: cluster analysis is *the study of finding similarities between data points according to the characteristics found in the data, and grouping similar data objects into clusters*. A cluster itself is defined relationally: a collection of objects that are similar to each other within the group and dissimilar to objects in other groups.

**💡 What problem this solves.** Most of the data you'll ever touch doesn't come with labels. Nobody tags every customer transaction with "this customer is a bargain-hunter" or every gene-expression profile with "this is cancerous tissue type 3." Clustering is the tool for the question *"does this unlabeled data already have structure in it, and can I find that structure automatically?"* It turns a pile of feature vectors into a small number of interpretable groups — which is either the end goal (segment my customers) or a stepping stone toward another task (compress this data, flag the weird points, pre-sort before a supervised model).

**💡 Where it sits inside unsupervised learning.** The lecture only names two techniques (slide 3): Cluster Analysis and PCA. It's worth being explicit about *why* those two are the flagship examples, because they solve different problems that are easy to conflate:

| | Cluster Analysis | PCA |
|---|---|---|
| Answers | "Which group does each point belong to?" | "What are the directions of maximum variance in the data?" |
| Output | Discrete group labels per point | Continuous new coordinates (components) |
| Reduces | Number of *groups* | Number of *dimensions* |
| Typical use | Segmentation, compression by grouping, anomaly detection | Dimensionality reduction, visualization, noise removal, decorrelation |

They're not competitors — clustering is frequently run *after* PCA (PCA to strip noisy/redundant dimensions, then cluster the compressed representation), which is exactly what slide 9 calls out under "Summarization → Before regression/classification or PCA."

**🎓 Lecture — applications (slides 6–8).** Three concrete cases are shown:
1. **Document/topic clustering** — an article gets grouped with other articles under "Technology," "Sports," or "Entertainment" style buckets, and separately, Pinterest's visual search clusters images by visual similarity to surface "visually similar results."
2. **Recommendation** — Amazon's "Top picks for you" panel, i.e., grouping a user with others who buy/rate similarly (collaborative filtering rests on this).
3. **Search-result clustering and geospatial clustering** — the Vivísimo search engine (a real early-2000s enterprise search product) clustering the results of a "forensic psychiatry" query into sub-topics like "University," "Forensic Psychology," "Expert Witness"; and a city map partitioned into 6 "block clusters" and 4 "street clusters" for urban analysis.

**🌐 External — more application families worth knowing for exam breadth** (not on the slides, but standard extensions of the same three ideas): customer/market segmentation in marketing analytics, image segmentation (grouping pixels by color/texture), gene-expression clustering in bioinformatics (grouping genes with correlated expression patterns), and anomaly/fraud detection (points that don't fit any cluster well). These aren't inventions — they're the textbook-standard elaborations of exactly the "pre-processing tool" uses the lecture lists on slide 9 (summarization, compression, localization, outlier detection).

**Connects to:** this section is the "why," and the very next lecture topic (§2.B–§2.F) is the "how do we even define a good cluster," which is the necessary vocabulary before any algorithm (§2.G onward) makes sense.


---

## 2. Topic-by-Topic Explanation

*Followed in the lecture's exact order. Slides 6–8 (Applications), 30 (Resources), and 31 (Thank you) are folded into §1 and skipped here as non-conceptual.*

### A. Unsupervised Learning (Slide 3)

**Simple Explanation.** You're given data with no "correct answer" attached to any row, and you want an algorithm to notice groupings or structure on its own.

**Formal Definition.** 🎓 Unsupervised learning: finding undetected patterns in a dataset that has no pre-existing labels, using minimal human supervision.

**Intuition.** Supervised learning is like a student checking answers against an answer key after every practice problem. Unsupervised learning is like being handed a box of mixed puzzle pieces with no picture on the box — you sort by edge shape, color, and texture because those regularities are visible in the pieces themselves, not because someone told you which pile is "correct."

**Mathematical Explanation.** 💡 Formally: you have data $D = \{x_1, x_2, \dots, x_n\}$, $x_i \in \mathbb{R}^d$, with **no** accompanying label vector $y$. Contrast with supervised learning's $D = \{(x_i, y_i)\}$. The learning objective in clustering is not "minimize prediction error against $y$" (there is no $y$) but "minimize/maximize some internally-defined notion of grouping quality" — this is precisely why §2.E (Quality of a Cluster) has to invent its own scoring criteria instead of borrowing accuracy/precision-style metrics from supervised learning.

**Example.** Netflix has no ground-truth label saying "user 4471 is a sci-fi binge-watcher." But if enough users who watch the same shows also rate them similarly, that pattern is discoverable directly from the ratings matrix — no human tagged anyone.

**Common Mistakes.** Students often assume "no labels" means "no information" — it doesn't. Structure in the raw feature values *is* the information; the lack of labels only means there's no external ground truth to check the discovered structure against.

**ML Relevance.** Almost every real dataset starts unlabeled; labels are expensive (human annotation) or nonexistent (transaction logs, sensor streams). Unsupervised methods are frequently the *first* thing run on new data, before anyone commits to the cost of labeling.

---

### B. What is Cluster Analysis (Slides 4–5)

**Simple Explanation.** A cluster is a bunch of data points that look like each other and look different from points outside the bunch. Cluster analysis is the process of finding those bunches.

**Formal Definition.** 🎓 Cluster: *a collection of data objects that are similar (or related) to one another within the same group, and dissimilar (or unrelated) to the objects in other groups.* Cluster Analysis: *the study of finding similarities between data points according to the characteristics found in the data, and grouping similar data objects into clusters.*

**Intuition.** Slide 4's "alien invasion" bit (three alien pictures: one eating chili peppers, a blank "average" face, one lifting weights) is a joke framing device for an implicit question: if you had to sort aliens into species by traits alone — spice tolerance, muscle mass, whatever you can measure — with no field guide, could you? That's clustering: partitioning by *measured similarity*, not by a pre-existing taxonomy.

**Mathematical Explanation.** 💡 Given $D = \{x_1,\dots,x_n\}$ and a target cluster count $k$, clustering produces an assignment function $c: \{1,\dots,n\} \to \{1,\dots,k\}$ such that a chosen similarity/dissimilarity function $d(x_i, x_j)$ is small on average for pairs with $c(i)=c(j)$ (intra-cluster) and large on average for pairs with $c(i)\neq c(j)$ (inter-cluster). Slide 5 also draws the line between clustering as a **stand-alone analysis tool** (the clusters themselves are the deliverable) versus a **pre-processing step** for another downstream algorithm (the deliverable is what happens *after* clustering) — this distinction resurfaces concretely on slide 9.

**Example.** Given 2D points scattered on a plane, three visually separated "blobs" (as literally shown in slide 2's own example scatterplot, colored red/green/blue) are three clusters — no labels were given; the grouping is read directly off the point positions.

**Common Mistakes.** "No predefined classes" (slide 5) doesn't mean "no assumptions." Every clustering method smuggles in assumptions about what a cluster *should* look like (e.g., K-Means assumes roughly round, similarly-sized blobs — see §2.J). Students sometimes treat clustering as assumption-free just because it's unsupervised.

**ML Relevance.** This is the base vocabulary — "cluster," "similarity," "dissimilarity" — that every algorithm in the rest of the lecture is built out of.

---

### C. Applications of Clustering (Slides 6–8)

Covered in depth in §1. In one line per slide, matching lecture order: **(6)** topic-clustering of documents + Pinterest visual similarity search; **(7)** Amazon's recommendation panel; **(8)** Vivísimo search-result clustering + city block/street geospatial clustering.

**ML Relevance callback:** notice the pattern across all five examples — *none of them required a human to define categories in advance.* The categories (Technology/Sports/Entertainment, "visually similar," "6 block clusters") all emerged from the data's own structure. That's the throughline connecting every application back to the §2.A definition.

---

### D. Clustering as a Pre-Processing Tool (Slide 9)

**Simple Explanation.** Sometimes you don't want the clusters themselves — you want to *use* clustering to make some other task cheaper or better.

**Formal Definition.** 🎓 Four named uses: **Summarization** (cluster before running regression/classification/PCA, so the downstream model sees fewer, denser summary points instead of raw noisy ones); **Compression** (vector quantization — replace each point with its cluster's representative "codeword"); **Localization** (restrict an expensive search to a few small clusters instead of the whole dataset); **Outlier Detection** (outliers are typically far from every established cluster, so "distance to nearest cluster" becomes an anomaly score).

**Intuition.** The right-hand figure on slide 9 is the classic **vector quantization** picture: input vectors (✗ marks) get grouped into hexagonal **Voronoi regions**, and each region is represented by a single red dot ("codeword"). Instead of storing/searching every ✗, you store/search the much smaller set of codewords.

**Mathematical Explanation.** 💡 Vector quantization formalizes compression as: replace $x_i \in \mathbb{R}^d$ with the index of its nearest codeword $\mu_j$, i.e., store $\arg\min_j \|x_i - \mu_j\|$ instead of the full $d$-dimensional vector. If there are far fewer codewords than data points, this is lossy compression — and it's *exactly* the same nearest-centroid assignment rule K-Means uses (§2.G), just applied for a compression goal instead of a "find natural groups" goal. This is the clearest bridge in the whole lecture between "clustering as an end in itself" and "clustering as a subroutine."

![[Pasted image 20260829113230.png]]

**Example.** JPEG-style color quantization: an image with millions of RGB colors gets clustered into (say) 256 representative colors; every pixel is then stored as a small index into that 256-color table rather than a full 24-bit color — this is literally vector quantization, and it's usually implemented by running K-Means on the pixel colors.

**Common Mistakes.** Students conflate "clustering as pre-processing" with "clustering is always exploratory." Slide 9's four bullets are all about clustering in service of a *different* downstream objective — the cluster boundaries themselves are a means, not the end product.

**ML Relevance.** This is a frequently tested distinction (stand-alone tool vs. pre-processing step) because it tests whether a student actually read past the algorithm mechanics into *why* you'd reach for clustering at all.

---

### E. Quality of a Cluster (Slide 10)

**Simple Explanation.** A "good" clustering isn't just *any* partition of the data — it should make tight, distinct groups.

**Formal Definition.** 🎓 A good clustering algorithm produces clusters with **high intra-class similarity** (cohesive within clusters) and **low inter-class similarity** (distinctive between clusters). The quality of a clustering method depends on the *similarity measure* used and its ability to discover some or all of the hidden patterns. Similarity is expressed via a distance function $d(i,j)$, and weights should be attached to different variables depending on the application and data semantics.

**Intuition.** Picture pulling all same-cluster points close together (cohesion) while pushing different-cluster points apart (separation). A clustering that satisfies neither — loose, overlapping blobs — isn't wrong in a "buggy code" sense, it's just *low quality*: it hasn't found much real structure.

**Mathematical Explanation.** 💡 Slide 10 stays qualitative, so here's the standard formalization it's pointing at. Intra-class similarity is usually operationalized as **within-cluster sum of squares (WCSS)**, and this is exactly the quantity the elbow method plots later (§2.K):

```
WCSS = Σ_{i=1}^{k}  Σ_{x ∈ Cᵢ}  d(x, μᵢ)²
```

Low WCSS = high cohesion. Inter-class separation doesn't have one canonical formula on these slides, but the standard companion metric (🌐 external — this exact instrument doesn't appear in the deck, but it directly operationalizes slide 10's "low inter-class similarity" criterion and is the natural continuation once you've defined WCSS) is the **silhouette coefficient** (Rousseeuw, 1987):

```
a(i) = mean distance from point i to every other point in i's own cluster      (cohesion)
b(i) = mean distance from point i to every point in the *nearest other* cluster (separation)
s(i) = (b(i) − a(i)) / max(a(i), b(i))                                          range: [−1, 1]
```

$s(i)$ close to $+1$ means $i$ is well inside its own cluster and far from the next-nearest one — exactly slide 10's two criteria captured in a single number per point (average $s(i)$ over all points to score a whole clustering).

**Example.** Two candidate 2-cluster splits of the same 10 points: split A has all points tightly hugging their own centroid with the two centroids far apart (low WCSS, high silhouette); split B slices the same 10 points down an arbitrary line through a single dense blob (higher WCSS, near-zero or negative silhouette, since points near the arbitrary boundary are about equally close to both centroids). Split A is the "good" clustering by both of slide 10's criteria even though both splits use $k=2$.

**Common Mistakes.** "Similarity measure" (slide 10) is doing more work than it looks like — the *same* raw data can produce wildly different "good" clusterings depending on whether you use Euclidean distance, Manhattan distance, or a weighted distance, because slide 10 explicitly says weights should reflect the application. Choosing a metric is a modeling decision, not a formality.

**ML Relevance.** This is the rubric every algorithm in this lecture is implicitly optimizing against — K-Means (§2.G) literally minimizes WCSS, so understanding "quality" here is a prerequisite for understanding *why* K-Means's update rule (recompute centroid as the mean) is the right update rule at all (see §8).

![[Pasted image 20260829114207.png]]

---

### F. Considerations for Cluster Analysis (Slide 11)

**Simple Explanation.** Before you cluster anything, four design questions have to be answered, and each has two contrasting options.

**Formal Definition.** 🎓 Slide 11 lists exactly four considerations, each a binary contrast:

| Consideration | Option 1 | Option 2 | Lecture's example |
|---|---|---|---|
| **Partitioning Criteria** | Single-level partitioning | Hierarchical (multi-level) partitioning | Politics vs. Sports → (Football, Cricket, Volleyball, …) |
| **Separation of Clusters** | Exclusive (1 object → 1 cluster) | Non-exclusive (1 object → possibly many clusters) | A customer belongs to only one region (excl.) vs. a document may belong to more than one topic class (non-excl.) |
| **Similarity Measure** | Distance-based | Connectivity-based | Euclidean/road-network/vector distance vs. density or contiguity |
| **Clustering Space** | Full space | Subspace | Often full space when low-dimensional; subspaces in high-dimensional clustering |

**Intuition.** These are the four knobs that quietly determine *which algorithm you should even consider*. "Single-level vs. hierarchical" asks whether you want one flat partition or a nested tree of partitions (a topic → subtopic tree, e.g. Sports → Football/Cricket/Volleyball). "Exclusive vs. non-exclusive" asks whether cluster membership is a hard partition or can overlap. "Distance- vs. connectivity-based" foreshadows the K-Means-vs-density-based-methods split explored in §2.J. "Full space vs. subspace" is the high-dimensional caveat — in high dimensions, most feature axes may be irrelevant noise, so clustering only in a relevant subspace can outperform clustering in the full feature space.

**Mathematical Explanation.** 💡 None of the algorithms taught later in this lecture (K-Means, K-Medoids, KNN) are hierarchical, non-exclusive, connectivity-based, or subspace methods — every one of them is **single-level, exclusive, distance-based, full-space**. That's not a coincidence; it's exactly why this slide exists at this point in the sequence: it's setting up the assumptions the rest of the lecture will silently make, so their limitations (§2.J's non-convex-cluster failure) are traceable back to a specific box on this table.

**Example.** A news aggregator that must place every article into exactly one section (Politics *or* Sports, never both) is doing exclusive, single-level, distance-based clustering. A tagging system that lets one article appear under both "Politics" and "Economy" is non-exclusive.

**Common Mistakes.** Treating this slide as trivia to memorize rather than as a lens: when you later see K-Means fail on crescent-shaped clusters (§2.J), the diagnosis is literally "K-Means is a distance-based, full-space method — it has no connectivity-based option," which is a direct callback to this table.

**ML Relevance.** This table is the conceptual map for the entire clustering literature (hierarchical clustering, fuzzy/non-exclusive clustering, density-based methods, subspace clustering) — none of which are covered as *algorithms* in this lecture, but all of which live inside this table's four rows.


### G. K-Means Clustering (Slides 12–14)

![[Pasted image 20260829154421.png]]

**Simple Explanation.** Pick $k$ starting points. Assign every data point to whichever starting point it's closest to. Recompute each group's average position. Repeat until nothing changes.

**Formal Definition.** 🎓 Slide 12, verbatim structure:
- **Input:** $k$ (number of clusters), $D$ (dataset of $n$ objects)
- **Output:** a set of $k$ clusters
- **Method:**
  1. Randomly choose $k$ objects from $D$ as initial centroids.
  2. Repeat until no change of centroids:
     - Assign each object to the cluster it is most similar to.
     - Update the cluster centroids as the **mean** of the cluster.

**Intuition.** This is a two-step dance repeated to a fixed point: *assign* (draw boundaries around the current centroids) then *update* (move each centroid to the middle of the crowd it just attracted). Slide 13's figure is the assignment step frozen mid-algorithm: three yellow markers (square, triangle, circle) are the current centroids, and the colored/shaded regions are the **Voronoi partition** induced by those three centroids — every point in the pink region is closer to the square than to the triangle or circle, etc. The caption literally reads "iteration 0: assign points to clusters," confirming this is a snapshot of step 2's first sub-step, before any centroid has moved.

**Mathematical Explanation.** 💡 The lecture never writes down an explicit objective function on these three slides, but slide 16 (§2.I) reveals it implicitly via the notation $E(c_1, c_2, \dots, c_k)$. Making that explicit: K-Means minimizes the **within-cluster sum of squared distances**

```
J(c₁,...,c_k, μ₁,...,μ_k) = Σᵢ₌₁ⁿ  ||xᵢ − μ_{c(i)}||²
```

where $c(i) \in \{1,\dots,k\}$ is the cluster assignment of point $i$ and $\mu_j$ is centroid $j$. The two-step loop is coordinate descent on this objective:
- **Assignment step** fixes the $\mu_j$'s and minimizes $J$ over $c(i)$: the optimal assignment for a fixed set of centroids is "nearest centroid," which is exactly slide 12's "assign each object to the cluster it is most similar to."
- **Update step** fixes the $c(i)$'s and minimizes $J$ over $\mu_j$: for squared Euclidean distance, the minimizer of $\sum_{x \in C_j} \|x - \mu_j\|^2$ over $\mu_j$ is *exactly* the arithmetic mean of $C_j$ (take the derivative, set to zero — see §8 for the full derivation). That is precisely why the update in slide 12 says "mean," and it's the mathematical reason K-Means is called K-*Means* rather than something else.

Because each of the two steps can only decrease or hold $J$ constant (never increase it), and there are finitely many possible partitions of $n$ points into $k$ groups, the algorithm is **guaranteed to converge** — "repeat until no change of centroids" (slide 12) will always terminate, though not necessarily at the global minimum (§2.I).

**Example.** Slide 12's own scatterplot shows three visually obvious 2D blobs; running the loop from any reasonable random initialization inside those blobs converges in a handful of iterations to centroids sitting near each blob's visual center. Slide 14 shows the same idea in 3D with the RGB-colored points — note that in that slide, the colors overlap noticeably at the blob boundaries, a visual admission that the "iteration 0" hard boundary of slide 13 doesn't perfectly match the human-perceived group boundaries once the data has real overlap/noise.

**Common Mistakes.** (1) Thinking "randomly choose $k$ objects" (slide 12) always gives a good result — it doesn't; see §2.I. (2) Confusing the *centroid* (an abstract mean point, may not correspond to any real data point) with a *medoid* (§2.H) or with an actual observed data point. (3) Assuming K-Means finds "the" clusters — it finds *a* locally-optimal partition for the $k$ you chose, using the distance metric you chose; change either input and you can get a different, equally "valid by the algorithm's own logic" answer.

**ML Relevance.** K-Means is the default first clustering algorithm taught/used almost everywhere because it's simple, fast ($O(nkd)$ per iteration — see §3.1), and works well when its core assumption (roughly spherical, similarly-sized, similarly-dense clusters) roughly holds.

**Connects to:** the *median* update in K-Medoids (§2.H) is a direct one-word variation on this slide's *mean* update; the failure mode explored in §2.J (non-convex clusters) is a direct consequence of the squared-Euclidean-distance assumption baked into this objective.

---

### H. K-Medoids Clustering (Slide 15)

![[Pasted image 20260829163536.png]]

**Simple Explanation.** Same loop as K-Means, but the "center" of a cluster is required to be one of the actual data points, not a computed average.

**Formal Definition.** 🎓 Slide 15 — same **Input/Output** as slide 12, and the **same three-step Method**, with exactly one word changed: *"Update the cluster centroids as the **median** of the cluster."*

**⚠️ Flagging the lecture's phrasing precisely, since this project cares about exact source wording.** The slide literally says "median," and that word is reported faithfully above under the 🎓 tag. But "median" and "medoid" are not the same object, and the standard K-Medoids algorithm (Partitioning Around Medoids, PAM — Kaufman & Rousseeuw, 1987/1990) updates using the **medoid**, not the coordinate-wise median:

> "A medoid is defined as a representative item in a dataset or its subset (or cluster), which is centrally located and has the least sum of dissimilarities with other items in the group... A medoid is not equivalent to other statistical descriptors of median, centroid, or mean, but is the closest to median by virtue of an item in the dataset serving as a representative, as opposed to a computed entity."

**Intuition.** A **centroid** (K-Means) is a computed point — it can land anywhere in space, including nowhere any real data point exists (e.g., the mean of (0,0) and (2,2) is (1,1), which might not be an observed data point at all). A **medoid** (proper K-Medoids/PAM) must *be* one of your actual data points — specifically, whichever data point in the cluster has the smallest total distance to every other point in that cluster. A coordinate-wise **median** (what the slide's wording literally says) is yet a third thing: sort each feature independently and take the middle value per dimension — this can *also* produce a point that was never actually observed in the data (a "phantom" combination of independently-median coordinates), unlike a true medoid.

**Mathematical Explanation.** 💡 The medoid of cluster $C_j$ is
```
medoid(Cⱼ) = argmin_{x ∈ Cⱼ}  Σ_{x' ∈ Cⱼ} d(x, x')
```
— an exhaustive search over the (finite) points already in the cluster, not a closed-form average. This is *why* K-Medoids is more expensive per update than K-Means: computing the mean of $m$ points is $O(m)$; finding the medoid by this definition is $O(m^2)$ pairwise-distance evaluations (naively) per cluster, per iteration.

**Example.** Cluster = {(1,1), (2,2), (3,3), (100,100)}. The **mean** (K-Means centroid) is (26.5, 26.5) — dragged far from three of the four points by the outlier. The **medoid** (true K-Medoids) is whichever of the four *actual points* minimizes total distance to the other three — that will be (2,2) or (3,3), still sitting right in the middle of the tight trio, barely moved by the outlier. This single example is the standard textbook justification for why K-Medoids is described as more **robust to outliers** than K-Means (§6).

**Common Mistakes.** Assuming K-Medoids and K-Means always produce the same clustering because the algorithm skeleton looks identical — they can diverge substantially whenever outliers or non-Euclidean dissimilarities are involved, precisely because the update rule differs (an actual data point vs. a computed average).

**ML Relevance.** K-Medoids generalizes to **any dissimilarity measure** (it only ever needs pairwise distances, never coordinate arithmetic), so it works for data types where "mean" isn't even defined — e.g., strings compared by edit distance, categorical data, or graphs. K-Means, by contrast, needs a vector space where averaging makes sense.

**Connects to:** directly follows K-Means by design (slide 15 reuses slide 12's template intentionally, to make the one-word contrast obvious); its "one bad point can't drag the center" property is the natural answer to a "why would you ever use K-Medoids over K-Means" exam question (§9).

---

### I. Local Optima (Slide 16)

**Simple Explanation.** Because K-Means starts from a random guess, it can get stuck in a "pretty good but not the best" answer, and different random starts can lead to different final answers.

**Formal Definition.** 🎓 "As the centroids are randomly initialized, they can get stuck in a local optima. One naive solution is to repeat the clustering algorithm multiple times and pick the one with the lowest cost $E(c_1, c_2, \dots, c_k)$."

**Intuition.** The right-side figure is a well-known illustration (nine points, three intended clusters of three points each) run from two different random initializations: the top panel, labeled **GLOBAL OPTIMUM**, cleanly separates all three visually-obvious triples; the bottom two panels, labeled **LOCAL OPTIMA**, show the same nine points partitioned *differently* — in one, two of the true triples get merged into a lopsided split while the third is torn between two centroids. All three panels are *stable* under the algorithm (no further reassignment would change anything), but only the top one is actually the best split by the cost function.

**Mathematical Explanation.** 💡 $E(c_1,\dots,c_k)$ in slide 16 is the same objective $J$ defined in §2.G — the "cost" being compared across repeated runs is literally WCSS. Because K-Means's assignment step is a hard nearest-centroid rule, the overall optimization landscape of $J$ over all possible $(c(\cdot), \mu_1,\dots,\mu_k)$ combinations is **non-convex** with many basins of attraction; coordinate descent (§2.G's alternating loop) only guarantees convergence to *some* stationary point of $J$, not the global minimum. The "naive solution" the slide names — restart from several random initializations, keep the run with lowest final $J$ — is exactly the strategy implemented as the `n_init` parameter in `sklearn.cluster.KMeans` (§7).

**Example.** Run K-Means with $k=3$ on the nine-point toy dataset from slide 16 twenty times with different random seeds; tally the final $J$ for each run. Most runs land on $J_{\text{global}}$ (the top panel's split); a minority land on a strictly higher $J$ (one of the two local-optima splits) — picking the run with the smallest recorded $J$ recovers the global optimum with high probability, without ever proving optimality analytically.

**Common Mistakes.** Assuming "K-Means converged" means "K-Means found the best answer" — convergence only guarantees a **local** optimum, and the algorithm gives you no automatic warning when it's landed on a bad one; you have to actively check via repeated runs or a smarter initialization scheme.

**ML Relevance.** This single slide is the reason `k-means++` initialization exists (🌐 external — not named in the lecture, but it's the standard practical fix, spreading initial centroids apart deliberately instead of picking them uniformly at random, which sharply reduces the chance of landing in a bad basin) and the reason production K-Means implementations always run multiple restarts by default.

---

### J. Non-convex Clusters (Slide 17)

![[Pasted image 20260904145335.png]]

**Simple Explanation.** K-Means literally cannot represent clusters that aren't roughly round/blob-shaped, no matter how many times you restart it.

**Formal Definition.** 🎓 "$k$-means cannot represent density-based clusters." Two side-by-side figures: **"Convex Shaped"** — two round blobs, cleanly separated by a single straight decision line, each point connected by a thin ray back to its centroid (a "spider diagram" making the Voronoi assignment visible); **"Non-Convex Shaped"** — a small round blob sitting next to a crescent/banana-shaped cluster that partially wraps around it, where K-Means visibly misassigns: the shaded regions cut straight through the crescent instead of following its curve.

**Intuition.** K-Means's assignment rule is "nearest centroid" — geometrically, the boundary between any two clusters is *always* a straight line (in 2D) or hyperplane (in higher dimensions), because that's what "equidistant from two points" always looks like under Euclidean distance. A crescent shape wraps *around* another cluster; no single straight line can separate "inside the crescent's curve" from "the blob it's wrapping around" the way the crescent's own true shape does. This is a hard geometric limitation, not a tuning problem — no amount of restarting (§2.I) fixes it, because every possible K-Means solution is, by construction, made of straight-line boundaries.

**Mathematical Explanation.** 💡 Formally: the region assigned to centroid $\mu_j$ under K-Means is $\{x : \|x-\mu_j\| \le \|x-\mu_l\| \; \forall l\}$ — this is by definition a **convex polytope** (an intersection of half-spaces, one per rival centroid). A union of convex regions can only ever approximate a non-convex true cluster shape, and does so poorly when the shape curves sharply (like a crescent) relative to the number of centroids allowed. This is precisely why the slide title says "non-convex" — it's naming the geometric property (every K-Means region is provably convex) that causes the failure, not just describing the picture.

**Example.** Two concentric rings of points (one ring nested just inside a larger ring) is a classic non-convex case: K-Means with $k=2$ will typically cut the rings in half by angle (left-half vs. right-half) rather than by ring (inner vs. outer), because "half by angle" is what minimizes squared distance to two centroids, even though "by ring" is the intuitively correct grouping.

**Common Mistakes.** Concluding "K-Means is broken" — it isn't; it's doing exactly what its objective function asks it to do (minimize WCSS with straight-line boundaries). The mismatch is between the *algorithm's assumption* (convex, compact clusters) and the *data's true shape* (non-convex). The fix is switching algorithms (density-based methods like DBSCAN, or spectral clustering — 🌐 external, not covered in this lecture), not tuning K-Means harder.

**ML Relevance.** This is the single most commonly tested "limitation" question for K-Means, because it's the cleanest example of a broader ML theme: an algorithm's implicit assumptions (here: convex clusters) determine where it will silently fail, and recognizing that failure mode is more valuable than memorizing the algorithm's steps.

**Connects to:** directly follows §2.I (both slides 16 and 17 are "why K-Means can go wrong" content) and directly precedes §2.K, where the lecture pivots from "is the clustering good" questions to "how many clusters should there even be" questions.

---

### K. Choosing the Number of Clusters (Slides 18–25)

**Simple Explanation.** $k$ is an input you have to supply to K-Means/K-Medoids — the algorithm never tells you what $k$ should be. This whole block is about how to pick it.

**Formal Definition.** 🎓 The block opens (slides 18–22) with the *same* 17-point 2D scatterplot shown five times, circling a different number of groups each time — no circles at all (18), 2 groups (19), 3 groups (20), 4 groups (21), 5 groups (22) — under the repeated question "How to choose the value of $k$?" It then states explicitly (slides 23–24): "The value of $k$ depends on the downstream task," illustrated by labeling the *same* groupings as t-shirt sizes: a 3-way split labeled Small/Medium/Large (23), and a 4-way split labeled S/M/XL/XXL (24). Finally (slide 25): "Use the elbow method," backed by a line chart of **Within-Cluster Sum of Squares (WCSS)** against $k = 1$ through $9$, with an explicit "Elbow Point" marked at $k=4$.

**Intuition.** Slides 18–22 make a visual argument entirely non-verbally: with the *same* fixed set of points, $k=2$, $3$, $4$, and $5$ are all *plausible* groupings by eye — there's no single objectively correct number of clusters baked into the data itself, which is why the lecture needs a principled way to choose. Slides 23–24 supply the resolution: business/downstream needs pick $k$ directly (a clothing retailer picks 3 or 5 sizes depending on how much manufacturing complexity they can afford, not because one number is mathematically "more correct"). Slide 25's elbow method supplies a *data-driven* fallback for when there's no such external constraint: keep increasing $k$; WCSS always goes down (more clusters can only fit the data at least as well), but the *rate* of improvement drops sharply after the "true" number of groups is reached — the chart bends like an elbow at that point, and $k$ = the joint is the recommended choice.

**Mathematical Explanation.** 💡 The elbow method plots $J(k)$ (the WCSS objective from §2.G, minimized by running K-Means to convergence at each candidate $k$) against $k$ itself. Two boundary facts drive the shape: $J(1) = $ total variance of the whole dataset around its single global mean (worst case); $J(n) = 0$ (every point is its own cluster, zero within-cluster distance, but a useless clustering). The curve is monotonically non-increasing in between. The "elbow" is the point where the *second derivative* (rate of decrease of the rate of decrease) is largest in magnitude — informally, where adding one more cluster stops buying you much reduction in WCSS. On slide 25's chart, WCSS drops from roughly 310 ($k=1$) to about 105 ($k=2$) to about 40 ($k=3$) to about 18 ($k=4$), then flattens to single digits by $k=9$ — the sharpest bend visually sits at $k=4$, matching the marked elbow point.

**Example.** Slides 23–24 walk the *identical* 17-point dataset through two different "correct" answers depending purely on what question you're asking: "group by general size tier" → 3 clusters (S/M/L); "group by finer size tier" → 4 clusters (S/M/XL/XXL). Neither is more mathematically correct than the other — they answer different downstream questions about the *same* underlying data.

**Common Mistakes.** (1) Treating the elbow method as producing one unambiguous answer — real WCSS curves are often smoother than slide 25's textbook-clean example, and the "elbow" can be genuinely ambiguous between two adjacent values of $k$. (2) Forgetting that "more clusters always reduces WCSS" is mathematically guaranteed and therefore *cannot* be used by itself to pick $k$ — you specifically need the point of *diminishing returns*, not the point of lowest WCSS (which is trivially $k=n$). (3) Ignoring slides 23–24's message entirely and assuming there's always a single "objectively right" $k$ waiting to be found — often there isn't, and business context should override a purely statistical elbow.

**ML Relevance.** Choosing $k$ is one of the most practically important — and most commonly tested — parts of applying any partitioning clustering algorithm, precisely because K-Means/K-Medoids have no built-in mechanism to discover it themselves (unlike, say, hierarchical clustering, where you can cut a dendrogram at any level after the fact — 🌐 external aside, not covered in this lecture).

**Connects to:** this block is the practical answer to a question implicitly raised back in §2.G/§2.H (both algorithms *require* $k$ as an input) — everything from slide 12 onward has been silently assuming $k$ was already known, and this block finally supplies methods for choosing it.

---

### L. Supervised Clustering / K-Nearest Neighbors (Slides 26–29)

**Simple Explanation.** Given a brand-new point, look at its $k$ closest already-labeled neighbors, and assign it whatever label the majority of those neighbors have.

**Formal Definition.** 🎓 "In some cases, clustering analysis can be used in supervised settings. One such example is K-Nearest Neighbors (KNNs)." Slide 26's worked figure: a new (unlabeled) point has 5 circled nearest neighbors — 3 from "Category A," 2 from "Category B" — and a side box states the tally directly: *Category A: 3 neighbours, Category B: 2 neighbours*. Slide 27 shows the general 3-panel procedure (locate target point → draw distance lines to every candidate → circle the $k$ nearest within a radius) using two classes (green/red). Slides 28–29 show a 3-class version end-to-end: slide 28 is the raw unlabeled scatter of the training data (red/yellow/green classes), slide 29 is the finished result — every point in the plane colored by which class KNN would assign it, producing three jagged, irregular regions, explicitly labeled "KNN clustering result."

**⚠️ Naming note, worth flagging precisely.** The lecture's own section header calls this "Supervised Clustering," and slide 29's chart is captioned "KNN clustering result." Under the standard ML taxonomy, KNN used this way is **classification**, not clustering — it requires labeled training data ("Category A"/"Category B"/Classes 0/1/2 are pre-existing labels, not discovered groups) and produces a decision rule for new points, which is the definition of supervised learning laid out back in §2.A. The lecture's own header actually names this tension directly ("Supervised Clustering" is a deliberately paradoxical label), so this isn't correcting an error so much as making explicit what the lecture is pointing at: KNN reuses the *mechanism* of clustering (distance to nearby points) inside a fundamentally supervised task.

**Intuition.** Slide 26 is literally a democracy: the new orange point doesn't get a vote of its own — it looks at the 5 nearest points that *do* have votes (existing labels) and goes with the majority. Slide 29's jagged, non-straight-line boundary is the single biggest visual contrast with every clustering figure earlier in the lecture: K-Means/K-Medoids can only ever draw straight boundaries (§2.J), but KNN's boundary bends and curves however the local neighbor-density demands, because there's no centroid being computed at all — every prediction is a fresh local vote.

**Mathematical Explanation.** 💡 For a query point $x_q$: compute $d(x_q, x_i)$ for every labeled training point $x_i$; let $N_k(x_q)$ be the $k$ closest ones; predict
```
ŷ(x_q) = argmax_c  Σ_{x_i ∈ N_k(x_q)}  𝟙[yᵢ = c]
```
i.e., majority vote among the $k$ nearest labels. Slide 26's tally (3 vs. 2, out of 5 circled neighbors) confirms $k=5$ was used for that particular illustration, and the prediction would be "Category A" (3 > 2).

**Example.** Slide 27's middle panel shows dashed lines from the blue target point to every candidate — this is the brute-force distance computation every KNN prediction requires. The right panel circles the $k$ closest ones with an explicit radius — for that panel, a rough count of circled points inside the dashed circle would decide green vs. red by majority, exactly mirroring slide 26's tally.

**Common Mistakes.** (1) Believing KNN "learns" a model the way K-Means/K-Medoids/most classifiers do — it doesn't; KNN has **no training phase** at all (it's called a "lazy learner" — 🌐 external term, standard in the ML literature though not on these slides), it simply stores the training data and does all its work at prediction time. (2) Confusing $k$-Nearest-*Neighbors* with $k$-Means/$k$-Medoids' $k$ — both use the letter $k$, but in KNN it's "how many neighbors to vote," in K-Means/K-Medoids it's "how many clusters to form"; they are unrelated hyperparameters that happen to share a name. (3) Missing that KNN needs labels at all — unlike every other method in this lecture, it cannot run on unlabeled data.

**ML Relevance.** KNN is included here specifically to draw a contrast, not because it's a clustering algorithm in the technical sense — it's the lecture's way of showing what happens to "assign by nearest reference point" once you *do* have labels available: the assignment rule stays conceptually similar (nearest wins), but the boundary geometry (jagged, arbitrary shape) and the presence of ground-truth to check against are both fundamentally different from K-Means.

**Connects to:** closes the loop back to §2.A's supervised/unsupervised distinction, and its irregular decision boundary (slide 29) is the most direct visual counterpoint to §2.J's "K-Means can only draw straight lines" limitation — the two slides essentially answer each other.


---

## 3. Important Algorithms

*Deep-dive treatment of every algorithm the lecture names. K-Means and K-Medoids are unsupervised (the lecture's core topic); KNN is included because the lecture explicitly frames it as clustering's supervised cousin.*

### 3.1 K-Means Clustering

**Core idea.** Represent each cluster by the mean of its members; alternate between assigning points to their nearest mean and recomputing means, until stable.

**Step-by-step procedure.**
1. Choose $k$.
2. Initialize $k$ centroids $\mu_1,\dots,\mu_k$ (lecture: uniformly at random from the existing data points).
3. **Assignment step:** for every point $x_i$, set $c(i) = \arg\min_j \|x_i - \mu_j\|^2$.
4. **Update step:** for every cluster $j$, set $\mu_j = \frac{1}{|C_j|}\sum_{x \in C_j} x$.
5. If no point changed its assignment (or $\mu_j$'s stopped moving, or a max-iteration cap is hit), stop; otherwise go to step 3.

**Intuition.** Coordinate descent on a "who's closest to whom" game — centroids chase the crowd, then the crowd re-sorts itself around the new centroid positions, and the process settles once nobody wants to switch teams.

**Mathematical formulation.** Objective (WCSS / inertia):
```
J = Σᵢ₌₁ⁿ  ‖xᵢ − μ_{c(i)}‖²
```
Assignment step exactly minimizes $J$ over $c(\cdot)$ given fixed $\mu$'s; update step exactly minimizes $J$ over $\mu$'s given fixed $c(\cdot)$ (proof in §8.1). Both steps are exact minimizations of $J$ restricted to one block of variables, which is why $J$ never increases across iterations.

**Example.** Points: (1,1), (1,2), (5,5), (5,6); $k=2$; initial centroids (1,1) and (5,5) (already lucky). Assignment: (1,1)→C1, (1,2)→C1, (5,5)→C2, (5,6)→C2. Update: $\mu_1 = (1, 1.5)$, $\mu_2 = (5, 5.5)$. Re-assign: nothing changes (each point is still closest to its own new centroid). Converged in one update.

**Strengths.** Fast and simple; scales well to large $n$; easy to explain to non-technical stakeholders; guaranteed to converge (to *a* local optimum, §2.I).

**Weaknesses.** Requires $k$ chosen in advance (§2.K); sensitive to initialization (§2.I); only finds convex, roughly-equal-size, roughly-equal-density clusters (§2.J); sensitive to outliers (a single far-away point can drag a mean noticeably — contrast §3.2); requires a vector space where "mean" is defined (doesn't directly handle categorical data, strings, graphs).

**Hyperparameters.** $k$ (number of clusters — the central design choice, §2.K); number of random restarts / `n_init` (mitigates §2.I); initialization scheme (plain random vs. `k-means++`, 🌐 external, not named in lecture but standard practice); distance metric (lecture uses Euclidean implicitly; other metrics are possible but break the "mean minimizes squared distance" guarantee — see §8.1); convergence tolerance / max iterations.

**Computational considerations.** Each iteration costs $O(nkd)$ ($n$ points, $k$ centroids, $d$ dimensions — every point compares against every centroid). Number of iterations to convergence is typically small in practice (tens), though worst-case bounds are much larger. This makes K-Means one of the cheapest clustering algorithms to run at scale, which is a major reason it's the default choice.

**When to use it.** Large datasets, roughly spherical/blob-shaped groups expected, need for speed and interpretability over robustness, exploratory first pass before trying something fancier.

---

### 3.2 K-Medoids Clustering

**Core idea.** Same alternating loop as K-Means, but represent each cluster by one of its actual member points (the medoid) rather than a computed average, so the representative is never dragged off by an outlier.

**Step-by-step procedure** (as the lecture presents it, slide 15):
1. Choose $k$.
2. Randomly choose $k$ data points as initial "centroids" (medoids).
3. **Assignment step:** assign each point to its nearest medoid.
4. **Update step:** recompute each cluster's representative (🎓 the slide says "median"; the standard, textbook-correct algorithm computes the **medoid** — see the flag in §2.H).
5. Repeat until no change.

**Intuition.** Think of it as "find the most centrally-located *actual member*," like picking the person standing closest to everyone else in a group photo, rather than computing a hypothetical average position that no one is actually standing at.

**Mathematical formulation.** The proper PAM objective is total dissimilarity, not squared error:
```
TD = Σⱼ₌₁ᵏ  Σ_{x ∈ Cⱼ}  d(x, medoid(Cⱼ)),   where  medoid(Cⱼ) = argmin_{m ∈ Cⱼ} Σ_{x ∈ Cⱼ} d(x, m)
```
Because the medoid must be an existing data point found by exhaustive comparison within the cluster, this update has no closed-form shortcut the way the mean does.

**Example.** See §2.H's worked comparison: cluster {(1,1),(2,2),(3,3),(100,100)} — K-Means centroid = (26.5, 26.5) (nowhere near the real cluster); K-Medoids medoid = an actual point, (2,2) or (3,3) (still central to the tight trio).

**Strengths.** Robust to outliers (the representative can't be an arbitrarily-bad average — it's always a real, "typical" point); works with **any** dissimilarity measure, not just Euclidean/squared-error (so it generalizes to categorical data, strings via edit distance, or precomputed distance matrices); the representative point is always directly interpretable ("this real customer/document/gene is the archetype of this cluster").

**Weaknesses.** Much more expensive per iteration than K-Means (medoid search is combinatorial, roughly $O(m^2)$ per cluster of size $m$ for a naive full evaluation, versus $O(m)$ for a mean); still requires $k$ chosen in advance; still assumes exclusive, distance-based partitioning per §2.F's table, so it inherits the same non-convex-cluster limitation as K-Means (§2.J) — swapping mean for medoid fixes the outlier problem, not the cluster-shape problem.

**Hyperparameters.** $k$; choice of dissimilarity measure $d(\cdot,\cdot)$ (this is where K-Medoids' flexibility over K-Means actually pays off — you can plug in any valid distance); initialization scheme; number of restarts (same local-optima risk as K-Means, §2.I, since it's the same style of coordinate-descent loop).

**Computational considerations.** The classic PAM algorithm doesn't scale well to large $n$ because of the medoid search cost; large-data variants exist (🌐 external — CLARA, CLARANS, FastPAM are standard scalability fixes from Kaufman & Rousseeuw and later authors, not covered in this lecture) precisely to address this bottleneck.

**When to use it.** Data with significant outliers you don't want dragging your cluster centers; data where "mean" doesn't make sense (categorical/mixed-type data, or data you only have pairwise distances for, not raw coordinates); smaller datasets where the extra computational cost is affordable.

---

### 3.3 K-Nearest Neighbors (as presented — "Supervised Clustering")

![[Pasted image 20260904224809.png]]

**Core idea.** To label a new point, look at its $k$ nearest already-labeled points and take a majority vote.

**Step-by-step procedure.**
1. Choose $k$ (number of neighbors to consult).
2. Store the full labeled training set (no separate "training" computation happens beyond this).
3. For a new query point $x_q$: compute distance from $x_q$ to every stored training point.
4. Select the $k$ closest training points.
5. Predict the majority class among those $k$ neighbors' labels (ties broken by some rule, e.g. smallest total distance or smaller $k$).

**Intuition.** "You are the average of the company you keep" — literally: a new point's predicted label is whatever label is most common among its closest neighbors in feature space.

**Mathematical formulation.**
$$
ŷ(x_q) = argmax_c  Σ_{xᵢ ∈ N_k(x_q)} 𝟙[yᵢ = c]
$$
where $N_k(x_q)$ is the set of the $k$ training points minimizing $d(x_q, x_i)$.

**Example.** Slide 26: 5 nearest neighbors, 3 labeled "Category A," 2 labeled "Category B" → predict "Category A." Slide 29 extends this to 3 classes across the whole feature plane, producing a full decision-boundary map instead of a single prediction.

**Strengths.** No training phase (data is the model); naturally handles multi-class problems; decision boundary can be arbitrarily complex/non-linear (slide 29's jagged regions), which is precisely what fixes the §2.J "K-Means can only draw straight lines" limitation — *if* you have labels to work with.

**Weaknesses.** Every prediction requires scanning the (potentially huge) stored training set — slow at prediction time, the opposite trade-off from most models (which are slow to train, fast to predict); performance degrades in high dimensions (🌐 external — the "curse of dimensionality": in high-dimensional spaces, distances between points tend to become less discriminative, so "nearest" neighbors stop being meaningfully close — not covered on these particular slides, but directly relevant to any distance-based method including K-Means/K-Medoids too); sensitive to irrelevant/unscaled features, since every feature contributes equally to the distance unless explicitly weighted or normalized.

**Hyperparameters.** $k$ (small $k$ → sensitive to noise/overfits to local quirks; large $k$ → oversmoothed, biased toward the majority class overall); distance metric; optional distance-weighting of votes (closer neighbors count more — 🌐 external refinement, not shown on these slides).

**Computational considerations.** Naive prediction cost is $O(nd)$ per query (compare against every training point); spatial index structures (🌐 external — k-d trees, ball trees) can speed this up in low-to-moderate dimensions, but lose their advantage in very high dimensions for the same curse-of-dimensionality reason noted above.

**When to use it.** You have labeled data, decision boundaries are expected to be irregular/non-linear, dataset is small-to-moderate (prediction-time cost is manageable), and interpretability of "this prediction is based on these specific similar past examples" is valuable.


---

## 4. Worked Examples

### 4.1 The examples already in the slides

**A. K-Means template scatterplot (slides 12–14).** The lecture shows the algorithm's *behavior* on realistic 2D blob data (the "step 0" R plots and the 3D colored-point plot) but never walks arithmetic by hand — it's there to build visual trust that the method converges sensibly, not to be hand-computed. The Voronoi-region figure (slide 13) is worth re-reading once more here: three yellow markers (■ ▲ ●) are candidate centroids, and the shaded regions are exactly the set "all points closer to this centroid than to either other one" — this is the geometric object every worked K-Means example below is built from.

**B. The elbow-method dataset (slides 18–25) — verified numerically.** Reading the 17 points off slide 18's scatterplot (approximate — visually estimated, standard caveat for any coordinate read off a plotted figure) gives:

```
(1,4) (1,5) (2,6) (3,5) (4,9) (4,10) (5,6) (5,9) (6,6) (6,7) (6,8)
(7,1) (8,2) (8,3) (9,1) (9,2) (9,3)
```

Running real K-Means (from-scratch NumPy implementation, best of many random restarts) on these exact points and computing WCSS at each $k$ gives:

| $k$ | WCSS |
|---|---|
| 1 | 248.00 |
| 2 | 81.88 |
| 3 | 31.80 |
| 4 | 16.92 |
| 5 | 13.58 |
| 6 | 11.17 |
| 7 | 8.67 |

This reproduces slide 25's elbow shape almost exactly — a steep drop through $k=1\to4$, then a visibly flattening tail — and the sharpest bend is indeed at $k=4$ (WCSS improvement drops from $-14.9$ going $3\to4$ to only $-3.3$ going $4\to5$), matching the lecture's marked elbow point.

The lecture's own hand-drawn circles (slides 19–22, $k=2$ through $5$) turn out to match the *true* K-Means-optimal partition of this exact dataset almost exactly — direct confirmation that the visual groupings in the deck aren't just illustrative doodles, they're (very close to) what the real algorithm converges to.

**Bonus finding, straight from this dataset, that concretely demonstrates §2.I (Local Optima):** for $k=5$, only about **11% of 200 random restarts** (22/200) found the true global-optimum partition (WCSS ≈ 13.58, matching the lecture's own grouping); the rest landed on strictly worse local optima, some dramatically worse (WCSS as high as 77 — nearly 6× worse than optimal — from unlucky initial centroid placement). This is real, computed evidence for exactly the claim slide 16 makes in words: *"as the centroids are randomly initialized, they can get stuck in a local optima"* — and it's why the "naive solution" of repeating the algorithm and keeping the best run (also slide 16) is not just a throwaway suggestion but a genuinely necessary step even on small, clean, textbook-style data.

**C. K-Nearest Neighbors tally (slide 26).** Given directly: 5 circled neighbors, 3 in Category A, 2 in Category B → new point predicted as Category A by majority vote. This is the entire computation the slide performs — no distances are shown numerically, just the final tally.

### 4.2 Original worked examples (increasing difficulty)

**Beginner — one full K-Means iteration by hand.**
Points: $A=(2,2)$, $B=(2,4)$, $C=(8,2)$, $D=(8,4)$. Let $k=2$, initial centroids $\mu_1=(2,2)$ (=$A$), $\mu_2=(8,2)$ (=$C$).
*Assignment:* $d(A,\mu_1)=0 < d(A,\mu_2)=6 \Rightarrow A\to C_1$. $d(B,\mu_1)=2 < d(B,\mu_2)=6.32 \Rightarrow B\to C_1$. $d(C,\mu_1)=6 > d(C,\mu_2)=0 \Rightarrow C\to C_2$. $d(D,\mu_1)=6.32 > d(D,\mu_2)=2 \Rightarrow D\to C_2$.
*Update:* $\mu_1 = \text{mean}(A,B) = (2,3)$; $\mu_2=\text{mean}(C,D)=(8,3)$.
*Re-check assignment with new centroids:* every point is still closer to its own new centroid (verify: $d(A,\mu_1)=1$ vs $d(A,\mu_2)=6.08$, etc.) → **converged after one update.** Final WCSS $= (0^2+1^2)+(0^2+1^2)+(0^2+1^2)+(0^2+1^2) = 4$.

**Intermediate — K-Medoids vs. K-Means under an outlier.**
Cluster candidates: $(1,1), (2,1), (1,2), (50,50)$.
*K-Means centroid* $=\left(\frac{1+2+1+50}{4}, \frac{1+1+2+50}{4}\right) = (13.5, 13.5)$ — a point roughly 17 units from every one of the three "real" cluster members and nowhere near any actual data.
*K-Medoids medoid* — compute total distance from each candidate point to the other three (Manhattan distance for simplicity): $(1,1)$: $1+1+98=100$. $(2,1)$: $1+2+97=100$. $(1,2)$: $1+2+97=100$. $(50,50)$: $98+97+97=292$. Minimum total distance is tied among $(1,1)$, $(2,1)$, $(1,2)$ (all $=100$) — any of the three tight points is selected as medoid, e.g. $(1,1)$, which sits right where the real mass of data is, completely unmoved by the outlier. This is the mechanical reason behind the "K-Medoids is more robust to outliers" claim in §6.

**Advanced — local optima, quantified (uses §4.1.B's dataset).** Already walked through above: 200 restarts of real K-Means at $k=5$ on the lecture's own 17-point dataset produce WCSS values ranging from 13.58 (global optimum, found ~11% of the time) up to 77.05 (a 5.7× worse local optimum). An "advanced" exercise: explain *why* $k=5$ shows more local-optima risk than $k=2$ on the same data (answer: more centroids means more distinct ways to partition 17 points into stable-but-suboptimal groups — the number of local optima generally grows with $k$, because there are more degrees of freedom in the assignment).

**Tricky / conceptual — feature scaling silently changes the answer.**
Four "customers," measured by (age in years, income in dollars): $A=(25, 40000)$, $B=(27,42000)$, $C=(55,41000)$, $D=(58,39000)$. Suppose two candidate centroids are $\mu_1=(25,40000)=A$ and $\mu_2=(58,39000)=D$.
*Using raw (unscaled) Euclidean distance,* customer $C=(55,41000)$: $d(C,\mu_1)=\sqrt{30^2+1000^2}\approx 1000.4$, $d(C,\mu_2)=\sqrt{3^2+2000^2}\approx 2000.0$ → **assigned to $\mu_1$'s cluster** (income difference completely swamps the 30-year age gap, since income is measured in thousands and age in tens).
*Using standardized (z-scored) features,* the same point $C$ comes out with $d(C,\mu_1)\approx2.155$, $d(C,\mu_2)\approx1.800$ → **assigned to $\mu_2$'s cluster instead** — the assignment *flips* purely because of rescaling, with no change to the underlying data. This is a direct, numeric demonstration of slide 10's warning that *"weights should be associated with different variables based on applications and data semantics"* — if you don't consciously choose a scale, the feature with the largest raw numeric range silently dominates every distance computation.


---

## 5. Visual & Geometric Intuition

**Distance intuition.** Every algorithm in this lecture reduces to one operation: "how far apart are these two points?" Euclidean distance ($\sqrt{\sum (x_i-y_i)^2}$) measures straight-line ("as the crow flies") distance and is what every slide in this deck uses implicitly. Manhattan distance ($\sum |x_i - y_i|$) measures grid-path distance (like walking city blocks) and is less sensitive to any single large coordinate difference — it's a common alternative when you want to reduce the influence of extreme values in one feature without fully standardizing.

**2D geometric interpretation — Voronoi regions.** Every K-Means solution partitions the plane into convex polygonal regions, one per centroid — this is called a **Voronoi diagram**, and it's exactly what slide 13's colored regions are. Two centroids always produce a boundary that is a single straight line, perpendicular to the segment joining them, passing through its midpoint. Three or more centroids produce straight-line boundaries that meet at shared vertices. This single geometric fact is *the* reason K-Means can't represent non-convex clusters (§2.J) — no configuration of straight lines can trace a crescent.

**Decision-boundary intuition — K-Means/K-Medoids vs. KNN.** K-Means/K-Medoids commit to a *fixed* set of $k$ boundaries once training finishes — the boundary is determined entirely by the final centroid/medoid positions (straight lines, per above). KNN has no fixed boundary at all — its "boundary" is only ever computed on demand, per query point, from the local arrangement of nearby labeled points, and it can bend arbitrarily (slide 29's jagged 3-class regions). This is the single biggest visual and conceptual difference between the two halves of this lecture.

**Simple matplotlib visualization of the elbow-method dataset and its Voronoi partition:**
```python
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Voronoi, voronoi_plot_2d
from sklearn.cluster import KMeans

pts = np.array([
    (1,4),(1,5),(2,6),(3,5),
    (4,9),(4,10),(5,6),(5,9),(6,6),(6,7),(6,8),
    (7,1),(8,2),(8,3),(9,1),(9,2),(9,3)
], dtype=float)

km = KMeans(n_clusters=4, n_init=10, random_state=0).fit(pts)   # n_init: multiple restarts, guards against §2.I local optima

fig, ax = plt.subplots(figsize=(6,6))
ax.scatter(pts[:,0], pts[:,1], c=km.labels_, cmap='tab10', s=80, edgecolor='k')
ax.scatter(km.cluster_centers_[:,0], km.cluster_centers_[:,1],
           marker='X', s=200, c='black', label='centroids')
vor = Voronoi(km.cluster_centers_)                              # draws the straight-line region boundaries
voronoi_plot_2d(vor, ax=ax, show_vertices=False, line_colors='gray', line_alpha=0.6)
ax.set_xlim(-1, 11); ax.set_ylim(-1, 12)
ax.legend(); ax.set_title("K-Means, k=4 — Voronoi partition")
plt.show()
```
*Key lines:* `KMeans(n_clusters=4, n_init=10, ...)` — `n_init=10` runs the algorithm 10 times from different random starts and keeps the lowest-WCSS result, directly implementing slide 16's "naive solution" to local optima. `Voronoi(km.cluster_centers_)` builds the actual geometric partition object from the final centroids; plotting it makes the straight-line boundary claim from §2.J visible rather than asserted.

**Reproducing the elbow chart (slide 25) with real numbers:**
```python
wcss = []
for k in range(1, 8):
    km = KMeans(n_clusters=k, n_init=10, random_state=0).fit(pts)
    wcss.append(km.inertia_)          # scikit-learn's name for WCSS / J

plt.plot(range(1,8), wcss, marker='x')
plt.axvline(4, color='red', linestyle='--', label='elbow (k=4)')
plt.xlabel("Number of Clusters (k)"); plt.ylabel("WCSS"); plt.legend()
```
*Key line:* `km.inertia_` is scikit-learn's built-in attribute holding exactly the $J$ / WCSS value derived in §2.G and §3.1 — no manual sum-of-squares loop needed once you trust the library.

**Illustrating the non-convex failure (§2.J) with synthetic data:**
```python
from sklearn.datasets import make_moons

X, _ = make_moons(n_samples=300, noise=0.06, random_state=0)   # the crescent/"moons" shape
km2 = KMeans(n_clusters=2, n_init=10, random_state=0).fit(X)

plt.scatter(X[:,0], X[:,1], c=km2.labels_, cmap='coolwarm', s=15)
plt.title("K-Means on non-convex data — straight-line boundary\ncuts both crescents in half, doesn't separate them")
```
*Key line:* `make_moons` generates exactly the kind of crescent-shaped, non-convex clusters slide 17 shows — running K-Means on it visibly fails to recover the two moons, reproducing the lecture's own point with a runnable, controllable example instead of a static picture.


---

## 6. Algorithm Comparison

| Dimension | K-Means | K-Medoids (PAM) | K-Nearest Neighbors |
|---|---|---|---|
| **Learning type** | Unsupervised | Unsupervised | Supervised (needs labels — §2.L's naming caveat) |
| **Cluster representative** | Computed mean (centroid) | Actual data point (medoid) | N/A — no representative, votes per query |
| **Distance/dissimilarity** | Typically Euclidean (mean-minimizing requires squared error, §8.1) | Any valid dissimilarity measure | Any distance measure |
| **Cluster shape assumption** | Convex, roughly spherical (§2.J) | Convex, roughly spherical (same geometric limit as K-Means — swapping mean for medoid fixes outliers, not shape) | No shape assumption — boundary is whatever the local neighbor density implies (slide 29) |
| **Sensitivity to initialization** | High — real risk of local optima (§2.I, quantified in §4.1.B) | High — same coordinate-descent structure, same risk | None — no iterative fitting, no initialization |
| **Sensitivity to outliers** | High — a single far point drags the mean (§4.2 intermediate example) | Low — the medoid can't be dragged past an actual central point | Moderate — a mislabeled/outlier neighbor can flip a close vote, especially for small $k$ |
| **Requires $k$ chosen in advance** | Yes (number of clusters, §2.K) | Yes (number of clusters) | Yes, but a *different* $k$ (number of neighbors to consult, §3.3 — same letter, unrelated meaning) |
| **Training cost** | $O(nkd)$ per iteration | $O(n \cdot m)$-ish per iteration (medoid search is the bottleneck, §3.2) | None — "lazy learner," no training phase |
| **Prediction cost** | $O(kd)$ (compare new point to $k$ stored centroids) | $O(kd)$ (compare to $k$ stored medoids) | $O(nd)$ per query (compare to *every* stored training point) — the opposite trade-off from the other two |
| **Interpretability of "center"** | Moderate — a computed average, may not be a realistic instance | High — always a real, "typical" example | N/A |
| **Works on non-Euclidean/categorical data** | No (needs a vector space where "mean" is defined) | Yes (only needs pairwise distances) | Yes (only needs a distance function) |
| **Decision boundary shape** | Straight-line (convex Voronoi regions, §5) | Straight-line (same as K-Means) | Arbitrary/jagged (§2.L, slide 29) |
| **Typical use case** | Large-scale exploratory clustering, compression/vector quantization (§2.D) | Outlier-heavy data, non-Euclidean dissimilarities, need for interpretable "archetype" points | Any labeled classification/regression task where local similarity is a good predictor |

**Reading the table for exam purposes:** the two rows that most often anchor "compare X and Y" questions are *sensitivity to outliers* (mean vs. medoid — the direct payoff of §4.2's worked example) and *decision boundary shape* (straight lines vs. jagged — the direct payoff of §2.J vs. §2.L). If you can explain *why* each of those two rows is true from the underlying math (not just recite the table), you can defend almost any comparison question the professor could construct from this lecture.


---

## 7. Python Implementation

**7.1 K-Means from scratch (NumPy only) — makes the §2.G loop concrete.**
```python
import numpy as np

def kmeans(X, k, n_iter=100, n_init=10, seed=None):
    rng = np.random.default_rng(seed)
    best_centroids, best_labels, best_wcss = None, None, np.inf

    for _ in range(n_init):                                   # multiple restarts — mitigates §2.I local optima
        idx = rng.choice(len(X), size=k, replace=False)
        centroids = X[idx].copy()

        for _ in range(n_iter):
            dists = ((X[:, None, :] - centroids[None, :, :]) ** 2).sum(axis=2)   # assignment step
            labels = dists.argmin(axis=1)
            new_centroids = np.array([
                X[labels == j].mean(axis=0) if np.any(labels == j) else centroids[j]
                for j in range(k)
            ])                                                  # update step: mean of each cluster
            if np.allclose(new_centroids, centroids):
                break
            centroids = new_centroids

        wcss = sum(((X[labels == j] - centroids[j]) ** 2).sum() for j in range(k))
        if wcss < best_wcss:                                    # keep the lowest-cost run across restarts
            best_centroids, best_labels, best_wcss = centroids, labels, wcss

    return best_labels, best_centroids, best_wcss
```
*Important lines:* the `dists = ((X[:, None, :] - centroids[None, :, :]) ** 2).sum(axis=2)` line is a vectorized way to compute squared Euclidean distance from every point to every centroid at once (broadcasting an $(n,1,d)$ array against a $(1,k,d)$ array gives an $(n,k,d)$ array of differences, squared and summed over the last axis to get an $(n,k)$ distance matrix) — this *is* the assignment step from §2.G in one line. The `X[labels == j].mean(axis=0)` line *is* the update step — literally the arithmetic mean derivation from §8.1 written as code. The outer `for _ in range(n_init)` loop is the direct implementation of slide 16's "naive solution" to local optima.

**7.2 scikit-learn — the production-grade version of the same algorithm.**
```python
from sklearn.cluster import KMeans

km = KMeans(n_clusters=4, n_init=10, init='k-means++', random_state=0)
labels = km.fit_predict(X)
print(km.cluster_centers_, km.inertia_)      # inertia_ is scikit-learn's name for WCSS / J (§2.G, §5)
```
*Important lines:* `init='k-means++'` (🌐 external — not named in the lecture, but it's scikit-learn's default) spreads the initial centroids apart deliberately instead of picking them uniformly at random, which is a smarter, non-naive answer to the exact local-optima problem slide 16 raises. `n_init=10` is the direct library equivalent of the restart loop in §7.1.

**7.3 K-Medoids — scikit-learn's core package doesn't ship K-Medoids directly; `scikit-learn-extra` does.**
```python
from sklearn_extra.cluster import KMedoids

kmed = KMedoids(n_clusters=4, metric='manhattan', random_state=0)   # any dissimilarity metric is valid (§3.2)
labels = kmed.fit_predict(X)
print(kmed.cluster_centers_)     # every returned "center" is guaranteed to be an actual row of X
```
*Important line:* `metric='manhattan'` (or any other valid metric) is exactly the flexibility called out as K-Medoids' key strength in §3.2 — swap this one argument and the algorithm now clusters by a completely different notion of "close," something K-Means's mean-based update cannot do at all.

**7.4 K-Nearest Neighbors classification.**
```python
from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier(n_neighbors=5)      # this k = "how many neighbors to vote" (§3.3), NOT cluster count
knn.fit(X_train, y_train)                      # "fitting" just stores the data — no real training happens
pred = knn.predict(X_new)
```
*Important line:* `knn.fit(...)` is misleadingly named for this algorithm — as §3.3 explains, KNN has no training phase; `.fit()` here just stores `X_train, y_train` for later lookup. All the real computation happens inside `.predict()`, at query time — the opposite of every other model in this lecture.

**7.5 Elbow method, end-to-end (reproduces slide 25 with real numbers, as computed in §4.1.B).**
```python
import matplotlib.pyplot as plt

wcss = [KMeans(n_clusters=k, n_init=10, random_state=0).fit(X).inertia_ for k in range(1, 8)]
plt.plot(range(1, 8), wcss, marker='x')
plt.xlabel("k"); plt.ylabel("WCSS")
```
*Important line:* the list comprehension re-fits K-Means from scratch for every candidate $k$ — the elbow method is not a separate algorithm, it's just "run K-Means repeatedly at different $k$ and look at how $J$ changes," which is worth remembering conceptually as well as in code.


---

## 8. Deep Understanding / "Why?"

### 8.1 Why does the *mean* minimize within-cluster squared distance? (The full derivation slide 12 skips.)

For a fixed cluster $C$ with points $x_1,\dots,x_m \in \mathbb{R}^d$, we want the point $\mu$ that minimizes
```
f(μ) = Σᵢ₌₁ᵐ ‖xᵢ − μ‖²
```
Take the gradient with respect to $\mu$ and set it to zero:
```
∇f(μ) = Σᵢ₌₁ᵐ  2(μ − xᵢ) = 0
⇒  m·μ = Σᵢ₌₁ᵐ xᵢ
⇒  μ = (1/m) Σᵢ₌₁ᵐ xᵢ
```
That's the arithmetic mean — exactly, with no approximation. Because $f$ is a sum of convex quadratics, this stationary point is the *global* minimum of $f$ for this fixed cluster. This is the entire mathematical justification for slide 12's "update the cluster centroids as the mean" — it isn't a heuristic choice, it's the exact minimizer of the objective given the current assignment. Note this derivation is specific to **squared Euclidean distance**; if you used absolute (Manhattan) distance instead, the minimizer would be the coordinate-wise **median**, not the mean — which is a genuinely interesting side note given slide 15's wording (§2.H): the word "median" on that slide would actually be the mathematically correct update *if* K-Medoids used Manhattan distance and allowed the representative to be any point in space (not restricted to actual data points) — but standard K-Medoids restricts the representative to actual data points regardless of the distance metric used, which is the real distinction from K-Means.

### 8.2 What assumptions does K-Means make, and why do those assumptions matter?

Three assumptions, all implied by the objective function in §2.G/§8.1, none stated explicitly on the slides:
1. **Clusters are convex** (§2.J) — because Voronoi regions from squared-Euclidean nearest-centroid assignment are always convex polytopes.
2. **Clusters are roughly similar size and density** — because a large, low-density cluster and a small, high-density cluster sitting near each other will have their shared boundary pulled toward the *smaller* cluster (the centroid-distance boundary doesn't know about density, only distance), often splitting the sparse cluster incorrectly or absorbing part of it into the dense one.
3. **The features are on comparable, meaningfully-weighted scales** — because unweighted Euclidean distance treats every feature axis equally, and slide 10 explicitly names weighting as an application-dependent decision (confirmed numerically in §4.2's tricky example).

### 8.3 What happens when those assumptions fail?

- **Non-convex clusters** → K-Means gives a confidently wrong answer with straight-line cuts through curved structure (§2.J) — no warning is raised; the algorithm still "converges," it just converges to a bad partition of good data.
- **Very different cluster sizes/densities** → boundaries get pulled away from the sparser/larger cluster's true edge, effectively "stealing" some of its points.
- **Unscaled features** → whichever feature has the largest raw numeric range dominates every distance calculation, and clustering effectively happens almost entirely along that one axis (§4.2's age/income example, where income in dollars swamps age in years).
- **General fix pattern (🌐 external, not on these slides):** standardize/normalize features before clustering; switch to density-based methods (DBSCAN) for non-convex shapes; switch to Gaussian Mixture Models for elliptical, differently-sized clusters with soft/probabilistic assignment.

### 8.4 What changes if the data distribution changes?

If the true generating distribution shifts from "well-separated spherical blobs" toward "overlapping, elongated, or differently-shaped groups," three things degrade together: (1) WCSS becomes a less meaningful quality signal, because even the best possible K-Means partition of badly-shaped data will have high within-cluster spread; (2) the elbow in the elbow-method chart (§2.K) becomes less sharp/more ambiguous, because there's no longer a $k$ at which adding more clusters stops helping much; (3) the local-optima risk (§2.I) generally increases, because more irregular data creates more distinct "locally sensible but globally wrong" ways to partition it — directly consistent with the §4.1.B finding that $k=5$ (more degrees of freedom) had a much lower global-optimum hit rate than smaller $k$.

### 8.5 Why might two clustering methods produce different results on the same data?

Four independent sources of disagreement, each traceable to a specific part of this lecture: **(a) different objective functions** — K-Means minimizes squared Euclidean distance to a *mean*; K-Medoids minimizes total dissimilarity to a *medoid* — these are literally different optimization targets, so their optima need not coincide (§4.2's outlier example is the sharpest illustration). **(b) different distance metrics** — even running the *same* algorithm with Euclidean vs. Manhattan distance can produce different partitions, because "closest" means something different under each metric. **(c) initialization randomness** — the same algorithm, same data, same $k$, different random seed can land in different local optima (§2.I, §4.1.B). **(d) different $k$** — trivially, but worth stating: comparing a $k=3$ result to a $k=5$ result on the same data isn't "disagreement," it's two different questions (§2.K's t-shirt-size framing) being answered correctly.


---

## 9. Common Exam & Viva Questions

**Exam-pattern calibration note.** The midterm reverse-engineering work on this course established a fairly consistent authorship signature for Ishmam Tashdeed's exams: (1) numeric questions are frequently built directly from a worked example that already appears in the slide deck, sometimes reusing the exact figures rather than inventing fresh ones; (2) some word-problems have external sources behind them; (3) "why does X happen" and "compare X and Y" questions test the underlying mechanism, not just recall of a definition; (4) at least one question routinely reaches into a slide well past the introductory material rather than staying on the headline early slides. Applying that same signature here, the highest-probability sources for a Lecture 11 question are the elbow-method dataset (§4.1.B — its exact WCSS numbers are ready-made for a numeric question), the mean-vs-medoid outlier behavior (§4.2), and the non-convex-cluster failure (§2.J) — each pairs a concrete lecture visual with a mechanism you have to explain, not just name. **To be explicit about confidence:** this is a prediction of likely question *style and content* based on an established pattern, not a confirmed exam question the way the midterm dossier's findings were — none of this has been checked against an actual Lecture 11 exam.

**Definitions**

1. *Define a cluster, in the sense used in this lecture.* — A collection of data objects that are similar to one another within the group and dissimilar to objects in other groups (§2.B).
2. *What is a medoid, and how does it differ from a centroid?* — A medoid is an actual data point in the cluster that minimizes total dissimilarity to every other point in that cluster; a centroid is a *computed* mean that may not correspond to any real observed point (§2.H, §3.2).
3. *Define WCSS (inertia) and state its role in the elbow method.* — $\text{WCSS} = \sum_j \sum_{x \in C_j} \|x-\mu_j\|^2$; the elbow method plots WCSS against $k$ and picks the $k$ where the rate of decrease sharply flattens (§2.K).

**Conceptual**

4. *Why is clustering called "unsupervised"?* — There's no label vector $y$ to check assignments against; quality has to be defined internally (intra/inter-cluster similarity), not by comparison to ground truth (§2.A, §2.E).
5. *Distinguish clustering as a stand-alone tool vs. a pre-processing step, with one example each.* — Stand-alone: customer segmentation, where the clusters *are* the deliverable. Pre-processing: vector quantization/compression, where clustering feeds into a different downstream goal (§2.D).
6. *Why can K-Means never represent a non-convex cluster, regardless of restarts?* — Its assignment rule (nearest centroid under squared Euclidean distance) always produces convex Voronoi regions; restarting changes *which* convex partition you land on, never whether the boundaries are straight lines (§2.J, §5).

**Why / How**

7. *Derive why the cluster mean minimizes within-cluster sum of squared distances.* — Full derivation in §8.1: set $\nabla_\mu \sum_i \|x_i-\mu\|^2 = 0$, solve for $\mu$, get $\mu = \frac{1}{m}\sum x_i$.
8. *Why does K-Means sometimes converge to a local, not global, optimum — and what's the lecture's proposed fix?* — Coordinate descent on a non-convex objective landscape only guarantees a stationary point, not the global minimum; the fix is repeating the algorithm from several random initializations and keeping the lowest-cost run (§2.I, quantified with real numbers in §4.1.B).
9. *Why is K-Medoids more robust to outliers than K-Means?* — Its representative must be an actual data point selected by minimizing total dissimilarity, so one extreme value can't drag it the way it drags an averaged centroid (§2.H, §4.2).

**Mathematical**

10. *Points (1,1),(2,1),(1,2),(50,50) form one cluster. Find the K-Means centroid and the K-Medoids medoid (Manhattan distance). What does the comparison show?* — Centroid = (13.5, 13.5) (dragged toward the outlier, sits near none of the real points); medoid = one of (1,1)/(2,1)/(1,2) (tied at total distance 100, vs. 292 for the outlier) — shows the medoid stays anchored to the real mass of data (§4.2).
11. *WCSS values 248, 82, 32, 17, 14 for k=1..5 — identify and justify the elbow.* — Differences are −166, −50, −15, −3; the drop shrinks sharply after $k=4$ (−15 → −3), so $k=4$ is the elbow (§2.K, §4.1.B).
12. *5 nearest neighbors are labeled {A,A,B,A,B} — what does KNN predict? What if k is reduced to 3 using the same ordered list?* — At k=5: 3 A's vs. 2 B's → predict A. At k=3 (first three in the list, A,A,B): 2 A's vs. 1 B → still predict A here, but note in general shrinking $k$ can flip the answer if the closer neighbors happen to disagree with the majority of the full set (§3.3).

**Scenario-based**

13. *You cluster customers by (age, income in dollars) without scaling — what goes wrong, and how do you fix it?* — Income's much larger numeric range dominates the distance calculation, so clustering happens almost entirely along the income axis regardless of age; fix by standardizing both features before computing distances (§4.2's tricky worked example, §8.2/8.3).
14. *One customer's income is 100× the rest — K-Means or K-Medoids?* — K-Medoids: its medoid can't be pulled toward a single extreme value the way a mean can (§2.H, §3.2, §4.2).
15. *You segment the same data into 3 tiers (S/M/L) vs. 4 tiers (S/M/XL/XXL) — is one "more correct"?* — No; $k$ depends on the downstream task, not on one objectively correct number hidden in the data (§2.K, slides 23–24's t-shirt framing).

**Comparison**

16. *Compare K-Means and K-Medoids on update rule, outlier sensitivity, cost, and applicable metrics.* — See the full table in §6; the two rows worth leading with are outlier sensitivity (mean vs. medoid) and metric flexibility (Euclidean-only vs. any dissimilarity).
17. *Compare the decision-boundary shape of K-Means vs. KNN and explain the geometric reason.* — K-Means/K-Medoids always draw straight-line (convex Voronoi) boundaries because they compare distance to a small fixed set of representatives; KNN draws arbitrarily jagged boundaries because each prediction is a fresh local vote among nearby labeled points with no fixed representative at all (§2.J, §2.L, §5).
18. *K-Means's $k$ and KNN's $k$ — same kind of parameter?* — No: in K-Means/K-Medoids, $k$ = number of clusters/groups to form; in KNN, $k$ = number of neighbors consulted per prediction. They share a letter, not a meaning (§3.3's explicit warning).

**Tricky**

19. *"K-Means failed to separate two clearly-visible crescents — it must have a bug." Evaluate.* — Not a bug: K-Means is doing exactly what its objective (minimize squared distance to straight-line-bounded regions) asks; the mismatch is between the algorithm's convexity assumption and the data's true non-convex shape (§2.J, §8.3).
20. *Is KNN, as presented in this lecture, actually clustering? Justify using the lecture's own definitions.* — By §2.A's definition (no pre-existing labels), no — KNN requires labeled training data and produces a classification rule, which is supervised learning; the lecture itself names this tension by calling the section "Supervised Clustering" (§2.L).
21. *Two runs of K-Means, same data, same k, different final WCSS — is K-Means non-deterministic "in principle"?* — The algorithm itself is deterministic *given* a fixed initialization; the apparent non-determinism comes entirely from random centroid initialization (§2.I) — fix the seed and the result is reproducible.


---

## 10. Final Mastery Section

### One-Page Concept Summary

Cluster analysis groups unlabeled data by similarity: high cohesion within a group, low similarity across groups (§2.B, §2.E). K-Means represents each group by its mean and alternates nearest-centroid assignment with mean-recomputation, minimizing WCSS (§2.G) — this converges reliably but only to a *local* optimum (§2.I) and only ever draws straight-line (convex) boundaries, so it fails on crescent/non-convex shapes (§2.J). K-Medoids is the same loop with the representative constrained to be an actual data point (a medoid) chosen by minimizing total dissimilarity, which makes it robust to outliers and usable with any distance metric, at higher computational cost (§2.H, §3.2). Neither algorithm can tell you $k$ — that's chosen either by the downstream task's needs or via the elbow method, which plots WCSS against $k$ and looks for the point of diminishing returns (§2.K). KNN reuses "distance to nearby points" for a fundamentally different, *supervised* job — classifying a new point by majority vote among its $k$ nearest labeled neighbors — and produces arbitrarily jagged decision boundaries because it has no fixed representative at all (§2.L, §3.3).

### Formula Sheet

```
Euclidean distance:      d(x,y) = √( Σ (xᵢ − yᵢ)² )
Manhattan distance:      d(x,y) = Σ |xᵢ − yᵢ|
K-Means objective (WCSS / J / inertia):
                          J = Σⱼ Σ_{x∈Cⱼ} ‖x − μⱼ‖²      minimized by  μⱼ = mean(Cⱼ)
K-Medoids objective:      TD = Σⱼ Σ_{x∈Cⱼ} d(x, medoid(Cⱼ))
                          medoid(Cⱼ) = argmin_{m∈Cⱼ} Σ_{x∈Cⱼ} d(x,m)
Silhouette (per point, 🌐 external):
                          s(i) = (b(i) − a(i)) / max(a(i), b(i))     range [−1, 1]
KNN prediction:           ŷ(x_q) = argmax_c Σ_{xᵢ∈N_k(x_q)} 𝟙[yᵢ = c]
```

### Terminology Cheat Sheet

- **Cluster** — group of mutually-similar, externally-dissimilar objects.
- **Centroid** — computed mean representative of a cluster (K-Means); may not be a real data point.
- **Medoid** — actual data point minimizing total dissimilarity to its cluster (K-Medoids).
- **WCSS / Inertia / $J$** — within-cluster sum of squared distances; the quantity K-Means minimizes.
- **Voronoi region** — the convex set of points closer to one centroid than to any other; always bounded by straight lines/hyperplanes.
- **Local optimum** — a stable K-Means result that isn't the lowest-possible-WCSS partition.
- **Elbow method** — plotting WCSS vs. $k$ and picking the point of diminishing returns.
- **Vector quantization** — using cluster codewords to compress data (§2.D).
- **Lazy learner** — a model with no training phase (KNN); all computation happens at prediction time.
- **Convex cluster shape** — a shape a straight-line/hyperplane boundary can fully enclose; K-Means's implicit assumption.

### Algorithm Selection Guide

| If your situation is... | Reach for... |
|---|---|
| Large dataset, roughly blob-shaped groups expected, need speed | **K-Means** |
| Outliers present, or data isn't naturally a vector space (categorical, string, precomputed distances) | **K-Medoids** |
| You have labels and want a flexible, non-linear decision boundary | **KNN** |
| Clusters are crescent/ring-shaped or highly irregular | Neither — consider density-based methods (🌐 external, not covered here) |
| You don't know $k$ and have no business constraint | Elbow method on WCSS (§2.K) |
| You do know a business/task constraint on group count | Let the task pick $k$ directly (slides 23–24's t-shirt-size logic) |

### Common Mistakes (consolidated)

- Treating "no labels" as "no assumptions" (§2.B).
- Believing K-Means convergence implies global optimality (§2.I).
- Assuming K-Medoids' "median" wording (slide 15) means coordinate-wise median rather than an actual-data-point medoid (§2.H).
- Forgetting that more clusters *always* lowers WCSS, so the elbow method needs diminishing-returns reasoning, not "lowest WCSS wins" (§2.K).
- Confusing K-Means/K-Medoids' $k$ (cluster count) with KNN's $k$ (neighbor count) (§3.3).
- Running distance-based clustering on unscaled features and not noticing one feature is silently dominating (§4.2, §8.2).
- Calling KNN "clustering" without noting it's actually supervised classification wearing a clustering-flavored name (§2.L).

### High-Yield Exam Points

1. The mean-minimizes-squared-error derivation (§8.1) — shows up whenever a question asks "why mean, not something else."
2. The mean-vs-medoid outlier example (§4.2) — the single cleanest "compare K-Means and K-Medoids" payload.
3. Non-convex clusters as a *geometric*, not a *bug*, limitation (§2.J, §8.3) — a recurring "evaluate this claim" trap.
4. Elbow method reasoning by rate-of-change, not by raw minimum (§2.K).
5. KNN's naming tension ("supervised clustering") as a definitional trap (§2.L).

### Conceptual Practice Questions

- Why does adding more clusters always reduce WCSS, and why does that fact make "just minimize WCSS" a bad rule for choosing $k$?
- If you standardized every feature before running K-Means, would the non-convex-cluster limitation (§2.J) go away? Why or why not?
- Could you run K-Medoids on a dataset where you only have a pairwise distance matrix and no actual coordinates? Could you run K-Means the same way? Explain the difference.

### Hard Challenge Questions

- Prove that K-Means's objective $J$ never increases across a full assignment-then-update iteration (hint: each sub-step is an exact minimization over one block of variables while the other is held fixed — see §8.1 for the update-step half of this argument).
- Design a small synthetic 2D dataset (give explicit coordinates) where K-Means with $k=2$ and two different random initializations provably converge to two different final partitions with different WCSS. Justify why both are stationary points.
- The lecture's own elbow-method dataset (§4.1.B) showed only ~11% of random restarts finding the true optimum at $k=5$. Without increasing `n_init`, propose one change to the initialization *scheme* (not just "try more times") that would likely raise that success rate, and explain the mechanism.
