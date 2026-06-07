# LaTeX Mathematical Expressions — Mastery Guide
**Reference syllabus:** `math-expression.tex` | **Target:** TRW Lab PDF reconstruction  
**Required packages:** `amsmath`, `amssymb`, `hyperref`

---

## Quick Selector — Which Environment to Use?

| Situation | Environment | Numbered? |
|---|---|---|
| Math within a sentence | `$...$` or `\(...\)` | No |
| Standalone, no number needed | `\[...\]` | No |
| Single important equation | `equation` | Yes |
| Single equation, no number | `equation*` | No |
| Multiple aligned equations | `align` | Yes (each line) |
| Multiple aligned, no numbers | `align*` | No |
| Stacked centered equations | `gather` / `gather*` | Both options |
| One long equation, two lines | `multline` | Yes |
| Multi-step, one number | `equation` + `split` | One total |

---

## PART 1 — Categories, Syntax & Explanations

---

### Category 1 — Inline Math Mode

**What it is:** Math embedded within flowing text. Size adjusts to fit the line height.

**Three syntaxes — all produce identical output:**

```latex
\(x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}\)   % RECOMMENDED — robust
$E = mc^2$                                     % common shorthand — acceptable
\begin{math} Area = \pi R^2 \end{math}        % verbose — avoid this
```

**When to use:** Writing "The quadratic formula \(x = ...\) was derived by..." — any expression that belongs in the flow of a sentence.

**Common mistakes:**
- Using `$$...$$` for inline (that is display mode — creates a new centered line)
- Forgetting to close: `$x = 5` with no closing `$` — errors cascade
- Writing `sin x` instead of `\sin x` (plain text becomes italic, looks wrong)
- Writing multi-word variables: use `\text{MSE}` not `MSE` (italic M·S·E looks like a product)

**Examples (easy → advanced):**
```latex
Let $f(x) = x^2$ be defined on $\mathbb{R}$.
The area of a circle is $A = \pi r^2$.
For all $n \geq 1$, the sum $\sum_{i=1}^{n} i = \frac{n(n+1)}{2}$.
The condition $\|\mathbf{x} - \mathbf{x}^*\| < \varepsilon$ defines convergence.
```

---

### Category 2 — Display Math Mode (Unnumbered)

**What it is:** Math on its own centered line, larger than inline, no equation number.

**Three syntaxes:**

```latex
\[ \int_0^\infty e^{-x^2}\,dx = \frac{\sqrt{\pi}}{2} \]    % RECOMMENDED

$$ f(x) = \sum_{n=0}^{\infty} \frac{x^n}{n!} $$             % TeX syntax — avoid

\begin{displaymath}
  \lim_{x \to 0} \frac{\sin x}{x} = 1
\end{displaymath}                                             % verbose — avoid
```

**Always prefer `\[...\]`.**  
`$$...$$` is TeX syntax, not LaTeX2e. It has subtle spacing bugs. `\begin{displaymath}` is exactly equivalent to `\[...\]` but harder to read.

**Common mistakes:**
- Putting `\\` at the end of a single `\[...\]` — use `align` for multiple lines
- Forgetting `\,` before `dx` in integrals (`\int f(x)\,dx` — the comma is a thin space)

---

### Category 3 — Equation Environments (Numbered)

**What it is:** A numbered display equation. Numbers are assigned and updated automatically.

```latex
% Numbered — reference with \label
\begin{equation}
  \label{eqn:pythagoras}
  a^2 + b^2 = c^2
\end{equation}

% Unnumbered — same visual as \[...\] but more explicit
\begin{equation*}
  a^2 + b^2 = c^2
\end{equation*}
```

**Label and Reference system:**

```latex
\begin{equation}
  \label{eqn:euler}        % label MUST be inside the environment
  e^{i\pi} + 1 = 0
\end{equation}

% Referencing — needs two compilations to resolve
As shown in Equation~\ref{eqn:euler}...         % → "Equation 1"
As shown in \autoref{eqn:euler}...              % → "eq. 1" (with hyperref)
```

**Label naming convention:** Use `eqn:name` prefix to distinguish from `fig:`, `tab:`, `sec:`.

**Common mistakes:**
- Putting `\label` outside the environment — numbering breaks
- Using `\\` inside `equation` to break a line — compile error; use `split` or `multline`
- Forgetting `~` before `\ref` — prevents a line break between "Equation" and "1"

---

### Category 4 — Superscripts & Subscripts

**Superscript:** `^` | **Subscript:** `_`

```latex
% Single character — braces optional but recommended
x^2        x_i

% Multiple characters — braces REQUIRED
x^{10}     x_{ij}     x^{2n+1}     a_{i,j}^{(k)}

% Combined super + subscript
x_i^2      x_{ij}^{2k}

% Nested
e^{x^2}          % e to the (x squared)
x_{i_{jk}}       % nested subscript

% In summation/integral limits
\sum_{i=1}^{n}   \int_0^\infty   \prod_{k=0}^{N-1}
```

**Common mistakes:**
- `x^10` → only `1` superscripted; fix: `x^{10}`
- `x_ij` → only `i` subscripted; fix: `x_{ij}`
- `e^-x` → `-` becomes a dash superscript; fix: `e^{-x}`

---

### Category 5 — Fractions

**Syntax:** `\frac{numerator}{denominator}`

```latex
\frac{a}{b}                             % simple fraction
\frac{-b \pm \sqrt{b^2 - 4ac}}{2a}      % quadratic formula
\frac{d}{dx}                            % derivative operator
\frac{d^m}{dx^m}                        % m-th derivative
\frac{\partial f}{\partial x}           % partial derivative
```

**Display style inline — force with `\dfrac`:**
```latex
% Compressed in inline mode (bad for complex fractions):
$\frac{n+1}{2}$

% Force display size inline (amsmath):
$\dfrac{n(n+1)}{2}$
```

**Nested fractions:**
```latex
\frac{\frac{a}{b}}{\frac{c}{d}}                  % fraction within fraction
\frac{1}{1 + \frac{1}{1 + \frac{1}{x}}}          % continued fraction
\frac{\frac{ac}{d^2}}{\sin\!\left(\frac{2\theta}{\pi}\right)}
```

**Common mistakes:**
- `\frac ab` → only `a` is numerator, `b` is denominator; fix: `\frac{a}{b}` always
- Using `/` in display math: `x/2` — use `\frac{x}{2}` instead

---

### Category 6 — Roots & Radicals

```latex
\sqrt{x}              % square root
\sqrt{x^2 + y^2}      % expression under root
\sqrt[3]{8}           % cube root — third argument is index
\sqrt[n]{x}           % nth root
\sqrt[\alpha]{f(x)}   % custom-index root
```

**Common mistakes:**
- Writing `\sqrt 2` instead of `\sqrt{2}` — works for single char but `\sqrt{2+x}` needed for expressions
- `\sqrt[2]{x}` shows the index "2" explicitly; usually just write `\sqrt{x}` for square roots

---

### Category 7 — Summations

```latex
% Inline: limits appear to the right
$\sum_{i=1}^{n} x_i$

% Display: limits appear above/below
\[ \sum_{i=0}^{\infty} \frac{x^i}{i!} \]

% Common academic forms
\sum_{n=0}^{\infty} \frac{x^n}{n!}           % exponential series
\sum_{i=1}^{N} (y_i - \hat{y}_i)^2          % residual sum of squares
\sum_{j=1}^{m} \sum_{i=1}^{n} a_{ij} x_j   % double summation

% Product
\prod_{k=1}^{n} k = n!                       % factorial as product
```

**Common mistake:** Using `\Sigma` (Greek letter Σ, no limits) instead of `\sum` (operator with limits).

---

### Category 8 — Integrals

```latex
\int f(x)\,dx                           % indefinite — note \, before dx
\int_a^b f(x)\,dx                        % definite
\int_0^\infty e^{-x^2}\,dx              % improper
\int_{-\infty}^{\infty} e^{-x^2}\,dx = \sqrt{\pi}   % Gaussian

% Multiple integrals (amsmath)
\iint_D f(x,y)\,dA                      % double
\iiint_V f\,dV                          % triple
\oint_C \vec{F} \cdot d\vec{r}          % line integral (closed path)

% With complex integrand
\int_0^x (x - t)^{m - \alpha - 1} f(t)\,dt     % Riemann-Liouville style
```

**The `\,` before `dx`:** Always include it — thin space is required for professional typesetting. `\int f(x)dx` looks cramped; `\int f(x)\,dx` is correct.

**Common mistakes:**
- Missing `\,`: `\int f(x)dx` — cramped
- `\int\int` vs `\iint` — `\iint` has correct spacing for a double integral symbol

---

### Category 9 — Limits

```latex
\lim_{x \to 0} \frac{\sin x}{x} = 1
\lim_{n \to \infty} \left(1 + \frac{1}{n}\right)^n = e
\lim_{h \to 0} \frac{f(x+h) - f(x)}{h}         % derivative definition
\lim_{\substack{x \to 0 \\ y \to 0}} f(x,y)    % two-variable limit
\limsup_{n \to \infty} a_n \quad \liminf_{n \to \infty} a_n
```

**Note:** In display mode, the subscript appears below `\lim`. In inline mode it appears to the right. Force display style inline with `\displaystyle\lim_{...}`.

---

### Category 10 — Trigonometric & Standard Functions

LaTeX has named function commands that render in **upright Roman** (not italic):

```latex
\sin x    \cos x    \tan x
\sin^2 x  \cos\theta  \tan^{-1} x      % = arctan
\arcsin x  \arccos x  \arctan x
\sinh x    \cosh x    \tanh x          % hyperbolic
\ln x      \log x     \log_{10} x
\exp(x)    \max_{x \in S}  \min_{i}
\gcd(a,b)  \det(A)    \dim V
```

**Why this matters:** Writing `sin x` without `\backslash` renders as *sin x* (italic) — looks like a product s·i·n·x. The command `\sin x` renders as sin x (upright) — correct.

**Common mistakes:**
- `sin x` → wrong style
- `\sin(x)^2` → reads as sin applied to `(x)^2`; write `\sin^2(x)` or `\sin^2 x`

---

### Category 11 — Mathematical Operators & Symbols

```latex
% Arithmetic
\times   \div   \cdot   \pm   \mp

% Dots
\cdots   % centered:  a · · · z
\ldots   % lower:     a ... z
\vdots   % vertical (matrices)
\ddots   % diagonal (matrices)

% Arrows
\to   \rightarrow   \leftarrow   \Rightarrow   \Leftrightarrow
\mapsto   \longrightarrow   \iff   \implies

% Sets
\in   \notin   \subset   \subseteq   \cup   \cap   \emptyset

% Logic
\forall   \exists   \neg   \land   \lor
```

---

### Category 12 — Relation & Comparison Symbols

```latex
\neq     % ≠  not equal
\leq     % ≤  less than or equal
\geq     % ≥  greater than or equal
\approx  % ≈  approximately
\equiv   % ≡  equivalent / defined as
\propto  % ∝  proportional to
\ll      % ≪  much less than
\gg      % ≫  much greater than
\sim     % ~  similar to / distributed as
\cong    % ≅  congruent
\simeq   % ≃  approximately equal
```

---

### Category 13 — Scalable Brackets & Delimiters

**The problem:** Fixed delimiters look wrong around tall expressions.  
**The solution:** `\left` and `\right` auto-scale to the height of their contents.

```latex
% Always pair \left with \right
\left( ... \right)                  % parentheses  ( )
\left[ ... \right]                  % square brackets  [ ]
\left\{ ... \right\}                % curly braces  { }  — backslash required
\left| ... \right|                  % single bars  | |
\left\| ... \right\|                % double bars  ‖ ‖  (norm)
\left\langle ... \right\rangle      % angle brackets  ⟨ ⟩
\left\lceil ... \right\rceil        % ceiling  ⌈ ⌉
\left\lfloor ... \right\rfloor      % floor  ⌊ ⌋

% Evaluated-at bar — use \right. for invisible right delimiter
\left. \frac{dy}{dx} \right|_{x=0}
```

**Reference file example explained:**
```latex
\left( \frac{\frac{ac}{d^2}}{\sin{\frac{2\theta}{\pi}}} \right)
```
The `\left(` sees the outer fraction, which contains an inner fraction — it scales to contain both.

**Common mistakes:**
- `\left(` without matching `\right)` — LaTeX error
- `\{ ... \}` without backslashes — curly braces are invisible in math; use `\left\{...\right\}`

---

### Category 14 — Greek Letters — Full Reference

**Lowercase:**

| Command | Symbol | Command | Symbol | Command | Symbol |
|---|---|---|---|---|---|
| `\alpha` | α | `\beta` | β | `\gamma` | γ |
| `\delta` | δ | `\varepsilon` | ε | `\epsilon` | ε |
| `\zeta` | ζ | `\eta` | η | `\theta` | θ |
| `\iota` | ι | `\kappa` | κ | `\lambda` | λ |
| `\mu` | μ | `\nu` | ν | `\xi` | ξ |
| `\pi` | π | `\rho` | ρ | `\sigma` | σ |
| `\tau` | τ | `\phi` | φ | `\varphi` | φ |
| `\chi` | χ | `\psi` | ψ | `\omega` | ω |

**Uppercase (only those different from Roman letters):**

| `\Gamma` Γ | `\Delta` Δ | `\Theta` Θ | `\Lambda` Λ |
|---|---|---|---|
| `\Pi` Π | `\Sigma` Σ | `\Phi` Φ | `\Psi` Ψ |
| `\Omega` Ω | `\Xi` Ξ | `\Upsilon` Υ | |

**Common mistake:** Writing `\Alpha` (doesn't exist — uppercase alpha = A in Roman, no special command).

---

### Category 15 — Mathematical Fonts

Three distinct font families for math, each with a specific meaning:

```latex
% \mathbb{} — Blackboard Bold — requires amssymb
% Use for: number sets, probability spaces
\mathbb{R}   % ℝ  real numbers
\mathbb{Z}   % ℤ  integers
\mathbb{N}   % ℕ  natural numbers
\mathbb{C}   % ℂ  complex numbers
\mathbb{Q}   % ℚ  rational numbers

% \mathcal{} — Calligraphic (UPPERCASE ONLY — built into LaTeX)
% Use for: sets, algebras, transforms, ML loss functions
\mathcal{A}  % 𝒜  set or algebra
\mathcal{L}  % ℒ  loss function / Laplacian / Lagrangian
\mathcal{N}  % 𝒩  normal distribution
\mathcal{O}  % 𝒪  big-O complexity
\mathcal{F}  % ℱ  Fourier transform

% \mathfrak{} — Fraktur — requires amssymb
% Use for: Lie algebras, ideals, advanced algebra
\mathfrak{H}   % 𝔥  Hilbert space
\mathfrak{g}   % 𝔤  Lie algebra
\mathfrak{sl}  % 𝔰𝔩 special linear algebra
```

**Common mistakes:**
- `\mathbb{r}` → lowercase blackboard bold doesn't exist visually; use `\mathbb{R}`
- Using `\mathcal` for lowercase — only uppercase calligraphic is defined

---

### Category 16 — Vectors

```latex
% Standard arrow notation (LaTeX built-in)
\vec{v}                       % v with arrow
\vec{AB}                      % vector AB
\hat{n}                       % unit vector with hat

% Bold notation (preferred in engineering / ML)
\mathbf{v}                    % bold roman v
\boldsymbol{\omega}           % bold Greek (for Greek vectors)

% Dot product
\vec{u} \cdot \vec{v} = |\vec{u}||\vec{v}|\cos\theta

% Norm
\|\mathbf{x}\|_2 = \sqrt{\sum_{i=1}^n x_i^2}

% Gradient
\nabla f                      % gradient of scalar f
\nabla \cdot \vec{F}          % divergence
\nabla \times \vec{F}         % curl

% Transpose
\mathbf{X}^T\mathbf{X}        % X-transpose times X (ML)
```

**Important note:** The reference file uses `\Vec{v}` (capital V) — this is NOT standard LaTeX.  
Always use `\vec{v}` (lowercase v). The capital `\Vec` may cause undefined command errors.

**Two style conventions:** `\vec{v}` (arrow accent) vs `\mathbf{v}` (bold). Match whichever style the PDF you are reconstructing uses.

---

### Category 17 — Align & Align* Environments

**`align`** — multiple equations numbered individually  
**`align*`** — multiple equations, no numbers

The `&` is the alignment anchor (placed before the `=` sign). `\\` ends each line.

```latex
% align (each line gets a number)
\begin{align}
    x + y  &= 5   \\
    2x - y &= 10  \\
    x      &= 2
\end{align}

% align* (no numbers)
\begin{align*}
    (a+b)^2 &= a^2 + 2ab + b^2 \\
             &= a^2 + b^2 + 2ab
\end{align*}
```

**Key rules:**
- `&` can appear multiple times per line — each `&` aligns with the corresponding `&` on other lines
- No `\\` on the last line
- `\notag` after `\\` suppresses number for that line only

```latex
% Selective numbering
\begin{align}
    f(x) &= (x+1)(x-1)  \notag \\   % no number
         &= x^2 - 1                  % numbered
\end{align}
```

---

### Category 18 — Gather & Gather*

**`gather`** — equations stacked centrally, each numbered  
**`gather*`** — same, no numbers

No `&` alignment character — equations are just stacked:

```latex
\begin{gather*}
    a + b = c \\
    x^2 + y^2 = r^2
\end{gather*}
```

**When to use over align:** When the equations have no natural equal-sign alignment and you just want them centered and stacked.

---

### Category 19 — Multline

A **single equation** too long for one line, split across two or more lines:
- First line: left-aligned
- Last line: right-aligned
- Middle lines: centered

```latex
\begin{multline}
    p(x) = x^8 + x^7 + x^6 + x^5 \\
           + x^4 + x^3 + x^2 + x + 1
\end{multline}
```

**When to use:** One very long expression. For multi-step derivations, use `align` instead.

---

### Category 20 — Split (Inside Equation)

A multi-line derivation that counts as a **single numbered equation**. Must be nested inside `equation`:

```latex
\begin{equation}
    \begin{split}
        f(x) &= x^2 + 2x + 1 \\
             &= (x+1)^2
    \end{split}
\end{equation}
```

**`split` vs `align`:**

| | `align` | `split` inside `equation` |
|---|---|---|
| Line count | Multiple | Multiple |
| Equation numbers | One per line | One total |
| Use when | Separate equations | One derivation, one number |

---

### Category 21 — Matrices — All Six Variants

All require `amsmath`. Columns: `&` | Rows: `\\`

```latex
% 1. matrix — no delimiters (bare)
\begin{matrix} a & b \\ c & d \end{matrix}

% 2. pmatrix — round parentheses ( )
\begin{pmatrix} a & b \\ c & d \end{pmatrix}

% 3. bmatrix — square brackets [ ]
\begin{bmatrix} a & b \\ c & d \end{bmatrix}

% 4. Bmatrix — curly braces { }
\begin{Bmatrix} a & b \\ c & d \end{Bmatrix}

% 5. vmatrix — single vertical bars | | (determinant notation)
\begin{vmatrix} a & b \\ c & d \end{vmatrix}

% 6. Vmatrix — double vertical bars ‖ ‖ (matrix norm)
\begin{Vmatrix} a & b \\ c & d \end{Vmatrix}
```

**General n×m matrix with dots:**
```latex
\begin{pmatrix}
  a_{11} & a_{12} & \cdots & a_{1n} \\
  a_{21} & a_{22} & \cdots & a_{2n} \\
  \vdots & \vdots & \ddots & \vdots \\
  a_{m1} & a_{m2} & \cdots & a_{mn}
\end{pmatrix}
```

**Common mistakes:**
- `&` at the end of a row instead of only between columns
- Missing `\\` between rows
- `\\` after the LAST row — causes extra blank line
- Forgetting to wrap in `\[...\]` or an equation environment

---

### Category 22 — Text in Math & Spacing

```latex
% \text{} — Roman text inside math (requires amsmath)
f(x) = x^2  \quad \text{for all } x > 0
D^\alpha_a f(x), \quad \text{where } m = \lceil \alpha \rceil

% Spacing commands (from narrow to wide)
\,      % thin space  (3/18 em)  ← use before dx in integrals
\:      % medium space (4/18 em)
\;      % thick space (5/18 em)
\quad   % 1 em
\qquad  % 2 em
\!      % negative thin space (removes space)

% Correct integral spacing
\int f(x)\,dx          % good
\int f(x) \, dx        % also good
\int f(x)dx            % bad — cramped

% \text vs \mathrm
\text{MSE}     % upright text in math — for words/abbreviations
\mathrm{e}     % upright math letter — for Euler's number e
```

---

## PART 2 — Expanded Academic Examples

---

### Integrals — by domain

**Pure Mathematics:**
```latex
% Gaussian integral
\int_{-\infty}^{\infty} e^{-x^2}\,dx = \sqrt{\pi}

% Gamma function definition
\Gamma(n) = \int_0^\infty t^{n-1} e^{-t}\,dt

% Beta function
B(x,y) = \int_0^1 t^{x-1}(1-t)^{y-1}\,dt = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}
```

**Physics:**
```latex
% Maxwell's equation — Gauss's law
\oint_S \vec{E} \cdot d\vec{A} = \frac{Q_{\text{enc}}}{\varepsilon_0}

% Work done by a force
W = \int_a^b \vec{F} \cdot d\vec{r}
```

**Engineering:**
```latex
% Laplace transform
\mathcal{L}\{f(t)\} = F(s) = \int_0^\infty f(t)e^{-st}\,dt

% Fourier transform
\hat{f}(\omega) = \int_{-\infty}^{\infty} f(t)e^{-i\omega t}\,dt
```

---

### Matrices — by domain

**Linear Algebra:**
```latex
% Identity matrix
I_n = \begin{pmatrix} 1 & 0 & \cdots & 0 \\ 0 & 1 & \cdots & 0 \\ \vdots & & \ddots & \vdots \\ 0 & 0 & \cdots & 1 \end{pmatrix}

% Determinant of 2x2
\begin{vmatrix} a & b \\ c & d \end{vmatrix} = ad - bc

% 3x3 determinant
\det(A) = \begin{vmatrix} a & b & c \\ d & e & f \\ g & h & i \end{vmatrix}
```

**Machine Learning:**
```latex
% Design matrix (ML)
X = \begin{bmatrix} x_1^T \\ x_2^T \\ \vdots \\ x_N^T \end{bmatrix}
\in \mathbb{R}^{N \times d}

% Covariance matrix
\Sigma = \frac{1}{N}\sum_{i=1}^N (\mathbf{x}_i - \boldsymbol{\mu})(\mathbf{x}_i - \boldsymbol{\mu})^T
```

---

### Align Environments — by domain

**Algebra step-by-step derivation:**
```latex
\begin{align*}
    (x+y)^3 &= (x+y)(x+y)^2 \\
             &= (x+y)(x^2 + 2xy + y^2) \\
             &= x^3 + 2x^2y + xy^2 + x^2y + 2xy^2 + y^3 \\
             &= x^3 + 3x^2y + 3xy^2 + y^3
\end{align*}
```

**Physics — energy derivation:**
```latex
\begin{align}
    E_k &= \frac{1}{2}mv^2                     \\
    E_p &= mgh                                  \\
    E   &= E_k + E_p = \frac{1}{2}mv^2 + mgh
\end{align}
```

**ML — gradient derivation:**
```latex
\begin{align}
    \frac{\partial \mathcal{L}}{\partial \theta}
      &= \frac{\partial}{\partial\theta}\left[\frac{1}{N}\sum_{i=1}^N(y_i - \theta^Tx_i)^2\right] \\
      &= \frac{-2}{N}\sum_{i=1}^N(y_i - \theta^Tx_i)x_i \\
      &= \frac{-2}{N}X^T(y - X\theta)
\end{align}
```

---

### Fractions — by domain

**Physics:**
```latex
\frac{1}{2}mv^2    \quad    \frac{F}{m} = a    \quad    \frac{dQ}{dt} = -kA\frac{dT}{dx}
```

**Signal Processing:**
```latex
H(z) = \frac{\sum_{k=0}^{M} b_k z^{-k}}{1 + \sum_{k=1}^{N} a_k z^{-k}}
```

**ML — Softmax:**
```latex
\sigma(\mathbf{z})_j = \frac{e^{z_j}}{\sum_{k=1}^{K} e^{z_k}}
```

---

## PART 3 — Mastery Exercises

*Recreate each expression in LaTeX. Solutions are in the separate solution manual.*

---

### Block A — Inline Math (Easy)

**A1.** Write inline: "The slope formula is m = (y₂ - y₁)/(x₂ - x₁)"

**A2.** Write inline: "For n ≥ 1, the factorial n! = n·(n-1)·...·2·1"

**A3.** Write inline: "Einstein's mass-energy relation E = mc²"

**A4.** Write inline: "The standard deviation is σ = √(1/N · Σ(xᵢ - μ)²)"

---

### Block B — Display Math & Equation (Easy)

**B1.** Display (unnumbered): The definition of e as a limit

**B2.** Display (numbered, label `eqn:gaussian`): The Gaussian integral equals √π

**B3.** Numbered equation: The definition of derivative as a limit

**B4.** Unnumbered equation: The binomial theorem (a+b)^n = Σ C(n,k) a^(n-k) b^k

---

### Block C — Fractions & Roots (Easy–Medium)

**C1.** `\frac` with simple numerator and denominator: (3x² + 2x) / (x³ - 1)

**C2.** A nested fraction: a/b divided by c/d

**C3.** The cube root of 27

**C4.** The nth root of x^(2n)

**C5.** The continued fraction: 1 / (2 + 1/(3 + 1/4))

---

### Block D — Integrals (Medium)

**D1.** Indefinite integral of x² dx

**D2.** Definite integral from 0 to 1 of x·e^x dx

**D3.** Improper integral from 0 to ∞ of e^(-x) dx = 1

**D4.** The Fourier transform definition (using ω)

**D5.** Double integral over region D of f(x,y) dA

---

### Block E — Matrices (Medium)

**E1.** A 2×2 pmatrix with entries 1, 2, 3, 4

**E2.** A 2×2 vmatrix (determinant) with entries a, b, c, d — set equal to ad - bc

**E3.** A 3×3 bmatrix with entries 1 through 9

**E4.** A general m×n pmatrix using aᵢⱼ notation with \cdots, \vdots, \ddots

**E5.** The identity matrix I₃ (3×3)

---

### Block F — Alignment Environments (Medium–Hard)

**F1.** Use `align*` to show the expansion of (a - b)²

**F2.** Use `align` (numbered) to write a 3-equation linear system

**F3.** Use `split` inside `equation` for a two-step factoring: x³ - x = x(x-1)(x+1)

**F4.** Use `multline` for a long polynomial p(x) = x⁶ + 5x⁵ + 4x⁴ + 3x³ + 2x² + x + 1

**F5.** Use `gather*` to write three related identities: sin²θ + cos²θ = 1, tan²θ + 1 = sec²θ, and 1 + cot²θ = csc²θ

---

### Block G — Advanced Mixed (Hard)

**G1.** Write the normal distribution PDF with \mathcal{N}:
f(x | μ, σ²) = (1/√(2πσ²)) · exp(-(x-μ)²/(2σ²))

**G2.** Write the gradient descent update rule with partial derivatives and vector notation

**G3.** Write the Riemann-Liouville integral with \Gamma function, \lceil \rceil ceiling, and text annotations (matching the uploaded PDF style)

**G4.** Write a block matrix equation:
[A  B] [x]   [f]
[C  D] [y] = [g]

**G5.** Write the Cauchy-Schwarz inequality with norms and inner product notation:
|⟨u, v⟩| ≤ ‖u‖ · ‖v‖

**G6.** Write the eigendecomposition A = P Λ P⁻¹ where Λ is a diagonal matrix with λ₁...λₙ

**G7.** Write a full numbered `align` derivation of completing the square for x² + bx + c

---

### Block H — Debugging Exercises

*Each snippet has at least one error. Find and fix every mistake.*

**H1.**
```latex
$\frac{x+1{x-1}$
```

**H2.**
```latex
\begin{equation}
  a^2 + b^2 = c^2 \\
  d^2 + e^2 = f^2
\end{equation}
```

**H3.**
```latex
\[\sum^n_{i=0} x_i = \frac{n+1}{2}\]
```

**H4.**
```latex
\begin{align}
  x + y = 5
  2x - y = 10
\end{align}
```

**H5.**
```latex
\begin{pmatrix}
  1 & 2 & 3 &
  4 & 5 & 6 \\
  7 & 8 & 9
\end{pmatrix}
```

**H6.**
```latex
$\left( \frac{a}{b} \right]$
```

---

## PART 6 — Exam Preparation

---

### Viva Questions

1. What is the difference between `equation` and `equation*`?
2. Why must `\label` be placed inside the equation environment?
3. What does the `&` character do inside an `align` environment?
4. What is the visual difference between `\vec{v}` and `\mathbf{v}`, and when is each preferred?
5. Why does `x^10` not give x to the power 10? What is the fix?
6. What is the difference between `split`, `align`, and `multline`? Give a use case for each.
7. Name all six matrix variants and their delimiters.
8. Why should you use `\[...\]` instead of `$$...$$` for display math?
9. What is the purpose of `\,` in `\int f(x)\,dx`?
10. What is the difference between `\mathbb{R}`, `\mathcal{L}`, and `\mathfrak{g}`?
11. Why does `\sin x` look different from `sin x`?
12. What does `\left. \frac{dy}{dx} \right|_{x=0}` produce, and what is `\right.`?
13. When would you use `gather*` instead of `align*`?
14. What is `\notag` used for inside an `align` environment?
15. How do you produce the ceiling function ⌈α⌉ in LaTeX?

---

### Common Mistakes — Quick Reference

| Mistake | Wrong | Correct |
|---|---|---|
| Multi-char superscript | `x^10` | `x^{10}` |
| Multi-char subscript | `x_ij` | `x_{ij}` |
| Negative exponent | `e^-x` | `e^{-x}` |
| Trig without backslash | `sin x` | `\sin x` |
| Curly braces in math | `{a, b}` | `\{a, b\}` |
| Greek uppercase | `\Alpha` | `A` (Roman letter) |
| Wrong display math | `$$...$$` | `\[...\]` |
| Missing `\,dx` | `\int f(x)dx` | `\int f(x)\,dx` |
| `\\` in equation | (error) | Use `split` or `align` |
| `&` at end of row | `a & b &` | `a & b` (no trailing `&`) |
| `\\` after last matrix row | (extra space) | Remove last `\\` |
| Lowercase `\mathbb` | `\mathbb{r}` | `\mathbb{R}` |
| Vector with capital V | `\Vec{v}` | `\vec{v}` |
| Missing braces in fraction | `\frac a b` | `\frac{a}{b}` |
| Mismatched delimiters | `\left( ... \right]` | matching pairs only |

---

### Fix the Syntax — Quick Drills

For each, identify the error and write the corrected version:

```latex
% 1.
$x = \frac{-b ± \sqrt{b^2 - 4ac}}{2a}$

% 2.
\[\sum_i=1^n x_i^2\]

% 3.
\begin{align*}
  f(x) = x^2 + 1
  g(x) = 2x - 3
\end{align*}

% 4.
\left\{ \frac{a}{b} \right\)

% 5.
\begin{equation}
  \label{eq1}
  f(x) = sin^2(x) + cos^2(x) = 1
\end{equation}

% 6.
\begin{bmatrix}
  1 & 2 \\
  3 & 4
\bmatrix}

% 7.
$A \in \mathbb{R}^n x n$

% 8.
\[\lim x \to \infty \frac{1}{x} = 0\]
```

---

*End of main guide. See `mock_assignments.html` for Part 4 and `solution_manual.md` for Part 5.*
