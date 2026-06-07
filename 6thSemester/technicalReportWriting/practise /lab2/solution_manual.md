# Solution Manual
**LaTeX Mathematical Expressions — Exercises & Mock PDF Reconstructions**

---

## Part 3 Solutions — Exercise Blocks A through H

---

### Block A — Inline Math

**A1.**
```latex
The slope formula is $m = \dfrac{y_2 - y_1}{x_2 - x_1}$.
```

**A2.**
```latex
For $n \geq 1$, the factorial $n! = n \cdot (n-1) \cdot\ldots\cdot 2 \cdot 1$.
```

**A3.**
```latex
Einstein's mass-energy relation $E = mc^2$.
```

**A4.**
```latex
The standard deviation is $\sigma = \sqrt{\dfrac{1}{N}\sum_{i=1}^{N}(x_i - \mu)^2}$.
```

---

### Block B — Display Math & Equation

**B1.**
```latex
\[
  e = \lim_{n \to \infty} \left(1 + \frac{1}{n}\right)^n
\]
```

**B2.**
```latex
\begin{equation}
  \label{eqn:gaussian}
  \int_{-\infty}^{\infty} e^{-x^2}\,dx = \sqrt{\pi}
\end{equation}
```

**B3.**
```latex
\begin{equation}
  f'(x) = \lim_{h \to 0} \frac{f(x+h) - f(x)}{h}
\end{equation}
```

**B4.**
```latex
\begin{equation*}
  (a+b)^n = \sum_{k=0}^{n} \binom{n}{k} a^{n-k} b^k
\end{equation*}
```
> `\binom{n}{k}` produces the binomial coefficient C(n,k). Requires `amsmath`.

---

### Block C — Fractions & Roots

**C1.**
```latex
\frac{3x^2 + 2x}{x^3 - 1}
```

**C2.**
```latex
\frac{\dfrac{a}{b}}{\dfrac{c}{d}} = \frac{a}{b} \cdot \frac{d}{c} = \frac{ad}{bc}
```

**C3.**
```latex
\sqrt[3]{27} = 3
```

**C4.**
```latex
\sqrt[n]{x^{2n}} = x^2
```

**C5.**
```latex
\cfrac{1}{2 + \cfrac{1}{3 + \cfrac{1}{4}}}
```
> `\cfrac` (continued fraction fraction) from `amsmath` gives better spacing for nested fractions.

---

### Block D — Integrals

**D1.**
```latex
\int x^2\,dx = \frac{x^3}{3} + C
```

**D2.**
```latex
\int_0^1 x e^x\,dx = \left[xe^x - e^x\right]_0^1 = 1
```

**D3.**
```latex
\int_0^{\infty} e^{-x}\,dx = 1
```

**D4.**
```latex
\hat{f}(\omega) = \int_{-\infty}^{\infty} f(t)\,e^{-i\omega t}\,dt
```

**D5.**
```latex
\iint_D f(x,y)\,dA
```

---

### Block E — Matrices

**E1.**
```latex
\[
  \begin{pmatrix} 1 & 2 \\ 3 & 4 \end{pmatrix}
\]
```

**E2.**
```latex
\[
  \begin{vmatrix} a & b \\ c & d \end{vmatrix} = ad - bc
\]
```

**E3.**
```latex
\[
  \begin{bmatrix}
    1 & 2 & 3 \\
    4 & 5 & 6 \\
    7 & 8 & 9
  \end{bmatrix}
\]
```

**E4.**
```latex
\[
  \begin{pmatrix}
    a_{11} & a_{12} & \cdots & a_{1n} \\
    a_{21} & a_{22} & \cdots & a_{2n} \\
    \vdots & \vdots & \ddots & \vdots \\
    a_{m1} & a_{m2} & \cdots & a_{mn}
  \end{pmatrix}
\]
```

**E5.**
```latex
\[
  I_3 = \begin{pmatrix}
    1 & 0 & 0 \\
    0 & 1 & 0 \\
    0 & 0 & 1
  \end{pmatrix}
\]
```

---

### Block F — Alignment Environments

**F1.**
```latex
\begin{align*}
    (a - b)^2 &= (a-b)(a-b) \\
              &= a^2 - ab - ab + b^2 \\
              &= a^2 - 2ab + b^2
\end{align*}
```

**F2.**
```latex
\begin{align}
    x + 2y + 3z  &= 6  \\
    2x - y  + z  &= 1  \\
    3x + y  - 2z &= 5
\end{align}
```

**F3.**
```latex
\begin{equation}
    \begin{split}
        x^3 - x &= x(x^2 - 1) \\
                 &= x(x-1)(x+1)
    \end{split}
\end{equation}
```

**F4.**
```latex
\begin{multline}
    p(x) = x^6 + 5x^5 + 4x^4 \\
         + 3x^3 + 2x^2 + x + 1
\end{multline}
```

**F5.**
```latex
\begin{gather*}
    \sin^2\theta + \cos^2\theta = 1 \\
    \tan^2\theta + 1 = \sec^2\theta \\
    1 + \cot^2\theta = \csc^2\theta
\end{gather*}
```

---

### Block G — Advanced Mixed

**G1.**
```latex
\begin{equation}
  f(x\mid\mu,\sigma^2) =
    \frac{1}{\sqrt{2\pi\sigma^2}}
    \exp\!\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)
\end{equation}
```

**G2.**
```latex
\begin{equation}
  \theta^{(t+1)} = \theta^{(t)} - \alpha\,\nabla_\theta\,\mathcal{L}(\theta^{(t)})
\end{equation}
```

**G3.**
```latex
\begin{equation}
  D^\alpha_a f(x) =
    \frac{1}{\Gamma(m-\alpha)}
    \frac{d^m}{dx^m}
    \int_0^x (x-t)^{m-\alpha-1} f(t)\,dt,
    \quad \text{where } m = \lceil\alpha\rceil
\end{equation}
```
> This directly recreates the Katugampola derivative from the uploaded PDF.
> Key elements: `\Gamma`, `\frac{d^m}{dx^m}`, `\int_0^x`, `m-\alpha-1`, `\lceil\alpha\rceil`, `\text{where }`.

**G4.**
```latex
\[
  \begin{bmatrix} A & B \\ C & D \end{bmatrix}
  \begin{pmatrix} \mathbf{x} \\ \mathbf{y} \end{pmatrix}
  =
  \begin{pmatrix} \mathbf{f} \\ \mathbf{g} \end{pmatrix}
\]
```

**G5.**
```latex
\begin{equation}
  \left|\langle \mathbf{u},\, \mathbf{v}\rangle\right|
  \leq
  \|\mathbf{u}\| \cdot \|\mathbf{v}\|
\end{equation}
```

**G6.**
```latex
\[
  A = P \Lambda P^{-1},
  \qquad
  \Lambda = \begin{pmatrix}
    \lambda_1 & 0         & \cdots & 0         \\
    0         & \lambda_2 & \cdots & 0         \\
    \vdots    & \vdots    & \ddots & \vdots    \\
    0         & 0         & \cdots & \lambda_n
  \end{pmatrix}
\]
```

**G7.**
```latex
\begin{align}
    x^2 + bx + c
      &= x^2 + bx + \frac{b^2}{4} - \frac{b^2}{4} + c    \notag \\
      &= \left(x + \frac{b}{2}\right)^2 - \frac{b^2}{4} + c \notag \\
      &= \left(x + \frac{b}{2}\right)^2 + \left(c - \frac{b^2}{4}\right)
\end{align}
```

---

### Block H — Debugging Solutions

**H1.** Missing closing brace for `\frac` numerator:
```latex
% Wrong:  $\frac{x+1{x-1}$
% Fixed:
$\frac{x+1}{x-1}$
```

**H2.** `\\` inside `equation` is not allowed — use `align` or `split`:
```latex
% Wrong: \begin{equation} ... \\ ... \end{equation}
% Fixed:
\begin{align}
  a^2 + b^2 &= c^2 \\
  d^2 + e^2 &= f^2
\end{align}
```

**H3.** Subscript braces and `^` order wrong:
```latex
% Wrong:  \[\sum^n_{i=0} x_i = \frac{n+1}{2}\]
% This technically works but the subscript/superscript order looks inconsistent.
% More importantly, the sum formula is wrong. Fixed (correct formula):
\[ \sum_{i=0}^{n} i = \frac{n(n+1)}{2} \]
```

**H4.** Missing `&` alignment anchor and `\\` line separators:
```latex
% Wrong:
\begin{align}
  x + y = 5
  2x - y = 10
\end{align}

% Fixed:
\begin{align}
  x + y  &= 5   \\
  2x - y &= 10
\end{align}
```

**H5.** Trailing `&` after last column, and missing row separator:
```latex
% Wrong: 1 & 2 & 3 &  (trailing &)  and no \\ after first row
% Fixed:
\[
\begin{pmatrix}
  1 & 2 & 3 \\
  4 & 5 & 6 \\
  7 & 8 & 9
\end{pmatrix}
\]
```

**H6.** Mismatched delimiters — `\left(` must pair with `\right)`, not `\right]`:
```latex
% Wrong:  \left( \frac{a}{b} \right]
% Fixed:
\left( \frac{a}{b} \right)
```

---

## Part 4 Solutions — Mock PDF LaTeX Sources

---

### Assignment 1 — Fundamental Theorems of Calculus

```latex
\documentclass[12pt, a4paper]{article}
\usepackage{amsmath, amssymb}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}

\title{Fundamental Theorems of Calculus}
\author{Practice Assignment}
\date{}

\begin{document}
\maketitle

\section{The Derivative}

The derivative of $f(x)$ with respect to $x$ is defined as the following limit:

\begin{equation}
  f'(x) = \lim_{h \to 0} \frac{f(x+h) - f(x)}{h}
\end{equation}

For any $n \in \mathbb{R}$, the power rule states:

\begin{equation}
  \frac{d}{dx}\left(x^n\right) = nx^{n-1}
\end{equation}

\section{Integration}

The power rule for indefinite integration is given in Equation 3:

\begin{equation}
  \int x^n\,dx = \frac{x^{n+1}}{n+1} + C, \qquad n \neq -1
\end{equation}

The famous Gaussian integral evaluates to:

\begin{equation}
  \int_{-\infty}^{\infty} e^{-x^2}\,dx = \sqrt{\pi}
\end{equation}

\section{Rotation Matrix}

A rotation in $\mathbb{R}^2$ by angle $\theta$ is represented by the matrix:
\[
  R(\theta) = \begin{pmatrix}
    \cos\theta & -\sin\theta \\
    \sin\theta &  \cos\theta
  \end{pmatrix}
\]

Its determinant satisfies:

\begin{equation}
  \begin{vmatrix}
    \cos\theta & -\sin\theta \\
    \sin\theta &  \cos\theta
  \end{vmatrix}
  = \cos^2\theta + \sin^2\theta = 1
\end{equation}

\section{Basic Trigonometric Identity}

The following identities follow from the Pythagorean theorem:

\begin{gather*}
  \sin^2\theta + \cos^2\theta = 1 \\[6pt]
  \tan^2\theta + 1 = \sec^2\theta \\[6pt]
  1 + \cot^2\theta = \csc^2\theta
\end{gather*}

\end{document}
```

---

### Assignment 2 — Linear Systems and Vector Spaces

```latex
\documentclass[12pt, a4paper]{article}
\usepackage{amsmath, amssymb}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}

\title{Linear Systems and Vector Spaces}
\author{Practice Assignment}
\date{}

\begin{document}
\maketitle

\section{System of Linear Equations}

Consider the following system of three equations in three unknowns:

\begin{align}
  2x + 3y - z  &= 7   \\
  x  - y  + 2z &= -3  \\
  3x + y  + z  &= 10
\end{align}

This is written compactly in matrix form $A\mathbf{x} = \mathbf{b}$ as:
\[
  \begin{bmatrix} 2 & 3 & -1 \\ 1 & -1 & 2 \\ 3 & 1 & 1 \end{bmatrix}
  \begin{pmatrix} x \\ y \\ z \end{pmatrix}
  =
  \begin{pmatrix} 7 \\ -3 \\ 10 \end{pmatrix}
\]

\section{Vector Operations}

\subsection{Dot Product}

The dot product of $\vec{u}$ and $\vec{v}$ in $\mathbb{R}^n$ is:

\begin{equation}
  \vec{u} \cdot \vec{v} = \sum_{i=1}^{n} u_i v_i = |\vec{u}||\vec{v}|\cos\theta
\end{equation}

\subsection{The $L^2$ Norm}

The Euclidean norm of a vector $\mathbf{v} \in \mathbb{R}^n$:

\begin{equation}
  \|\mathbf{v}\|_2 = \sqrt{\sum_{i=1}^{n} v_i^2}
\end{equation}

\section{Eigenvalue Problem}

For a matrix $A \in \mathbb{R}^{n \times n}$, the eigenvalue equation is:

\begin{equation}
  A\mathbf{x} = \lambda\mathbf{x}, \qquad \lambda \in \mathbb{C}
\end{equation}

The eigenvalues are roots of the characteristic polynomial:

\begin{equation}
  \det(A - \lambda I) = 0
\end{equation}

\section{Taylor Series Expansion}

The Taylor expansion of a smooth function $f(x)$ around the point $x = a$:

\begin{equation}
  f(x) = \sum_{n=0}^{\infty} \frac{f^{(n)}(a)}{n!}\,(x - a)^n
\end{equation}

For $a = 0$ and $f(x) = e^x$, this reduces to:
\[
  e^x = \sum_{n=0}^{\infty} \frac{x^n}{n!}
      = 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + \cdots
\]

\end{document}
```

---

### Assignment 3 — Gradient Descent and Optimization

```latex
\documentclass[12pt, a4paper]{article}
\usepackage{amsmath, amssymb}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}

\title{Gradient Descent and Optimization}
\author{Practice Assignment}
\date{}

\begin{document}
\maketitle

\section{Loss Function}

Given a training set $\{(x_i, y_i)\}_{i=1}^{N}$ with predictions
$\hat{y}_i = \theta^T x_i$, the mean squared error loss is:

\begin{equation}
  \mathcal{L}(\theta)
    = \frac{1}{N}\sum_{i=1}^{N}\left(y_i - \hat{y}_i\right)^2
\end{equation}

where $\theta \in \mathbb{R}^d$ is the parameter vector.

\section{Gradient Computation}

The gradient of $\mathcal{L}$ with respect to $\theta$ is derived step by step:

\begin{align}
  \frac{\partial\mathcal{L}}{\partial\theta}
    &= \frac{\partial}{\partial\theta}
       \left[\frac{1}{N}\sum_{i=1}^{N}
         \left(y_i - \theta^T x_i\right)^2\right] \\[6pt]
    &= \frac{-2}{N}\sum_{i=1}^{N}
       \left(y_i - \theta^T x_i\right)x_i \\[6pt]
    &= \frac{-2}{N}X^T(y - X\theta)
\end{align}

\section{Normal Equation}

Setting the gradient to zero and solving for $\hat{\theta}$:

\begin{equation}
  \hat{\theta} = \left(X^TX\right)^{-1}X^Ty
\end{equation}

where $X \in \mathbb{R}^{N \times d}$ and $y \in \mathbb{R}^N$.

\section{Gradient Descent Update Rule}

Starting from an initial $\theta^{(0)}$, the update at iteration $t$ is:

\begin{equation}
  \theta^{(t+1)} = \theta^{(t)}
    - \alpha \cdot \nabla_\theta\,\mathcal{L}\!\left(\theta^{(t)}\right)
\end{equation}

Substituting the gradient from Section 2:

\begin{equation}
  \begin{split}
    \theta^{(t+1)}
      &= \theta^{(t)} - \alpha \cdot \frac{-2}{N}
         X^T\!\left(y - X\theta^{(t)}\right) \\[4pt]
      &= \theta^{(t)} + \frac{2\alpha}{N}\,
         X^T\!\left(y - X\theta^{(t)}\right)
  \end{split}
\end{equation}

\section{Convergence Criterion}

Gradient descent converges when:

\begin{equation}
  \left\|\nabla_\theta\,\mathcal{L}\!\left(\theta^{(t)}\right)\right\|_2
  \leq \varepsilon
\end{equation}

for some pre-specified $\varepsilon > 0$.
The softmax function for multiclass output:

\begin{equation}
  \sigma(\mathbf{z})_j
    = \frac{e^{z_j}}{\displaystyle\sum_{k=1}^{K} e^{z_k}},
    \qquad j = 1, 2, \ldots, K
\end{equation}

\end{document}
```

---

## Key Syntax Rules — Pattern Reference

| Pattern | Command | Notes |
|---|---|---|
| Multi-char exponent | `x^{2n+1}` | Braces always for > 1 char |
| Multi-char subscript | `a_{ij}` | Same rule |
| Fraction | `\frac{top}{bottom}` | Never omit braces |
| Large fraction inline | `\dfrac{a}{b}` | Forces display size |
| Auto-scaling brackets | `\left( ... \right)` | Always paired |
| Evaluated at bar | `\left. f \right|_{x=0}` | `\right.` = invisible |
| Integral spacing | `\int f(x)\,dx` | `\,` before dx |
| Text in math | `\text{where } x > 0` | Roman font, requires amsmath |
| Number sets | `\mathbb{R}`, `\mathbb{Z}` | Uppercase only |
| Suppress number | `\notag` after `\\` | Inside align |
| One-number derivation | `split` inside `equation` | Not standalone |
| Selective stacking | `gather*` | No alignment anchor |

---

*End of solution manual.*
