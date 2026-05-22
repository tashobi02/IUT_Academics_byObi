# CSE 4631 — DSP Quiz: 70 Questions with Full Solutions

**Course:** Introduction to Signals & Systems  
**Instructor:** Syem Aziz  
**Sources:** Chapter 1 (Signals & Systems), Chapter 2-Part 1 (Sinusoidal Signals), Chapter 2-Part 2 (A/D & D/A Conversion)

---

## HOW TO USE THIS DOCUMENT

Each question is followed immediately by its solution in a collapsible block. Work through each question on your own first, then reveal the answer. Questions are graded **Easy (E)**, **Medium (M)**, **Hard (H)**, or **Bonus (B)**.

---

# SECTION 1 — Basic / Definitional Questions

---

### Q1 (E) — Definition of a Signal
Define a signal in DSP terms. What are its two key mathematical properties?

**Solution:**

A **signal** is any physical quantity that carries information and varies as a function of one or more independent variables (such as time, space, or frequency).

Mathematically, a signal is a **function**: `s = f(variable)`

The two key mathematical properties are:
1. **It carries information** from a source to a destination.
2. **It can be measured, recorded, reproduced, and processed** — i.e., it has a well-defined mathematical value at each point in its domain.

---

### Q2 (E) — Scalar vs Multichannel Signal
What is the difference between a **scalar signal** and a **multichannel (vector) signal**? Give one real-world example of each.

**Solution:**

| Type | Description | Example |
|---|---|---|
| **Scalar signal** | A single-component signal; one value per time instant | Temperature T(t), speech s(t), ECG v(t) |
| **Multichannel (vector) signal** | Multiple components from different sensors, grouped into a vector | Earthquake acceleration with 3 sensors; 12-lead ECG |

A multichannel signal is written in vector form:

$$\mathbf{s}(t) = \begin{bmatrix} s_1(t) \\ s_2(t) \\ s_3(t) \end{bmatrix}$$

Each component represents one measurement channel.

---

### Q3 (E) — Notation: x(t) vs x[n]
What does the notation `x(t)` vs `x[n]` indicate? Why does the choice of bracket matter?

**Solution:**

- `x(t)` — **round brackets**: denotes a **continuous-time (CT)** signal. The variable `t ∈ ℝ` is a real number (defined at every instant).
- `x[n]` or `x(n)` — **square brackets**: denotes a **discrete-time (DT)** signal. The variable `n ∈ ℤ` is an integer (defined only at integer sample indices).

The bracket is not cosmetic — it immediately tells you the domain of the signal. Using x(t) for a sequence, or x[n] for a continuous function, is mathematically incorrect because the domain types differ fundamentally.

---

### Q4 (E) — Digital Signal Definition
What is a **digital signal**? What two conditions must hold simultaneously for a signal to be called digital?

**Solution:**

A **digital signal** is a signal that is simultaneously:
1. **Discrete in time** — it exists only at integer sample indices `n ∈ ℤ`
2. **Discrete in value (amplitude)** — its amplitude is restricted to a finite set of levels `{L₁, L₂, ..., L_{2^B}}` produced by a B-bit ADC

Only digital signals can be stored and processed by computers. A signal that is discrete in time but has continuous amplitude (e.g., ideal DSP computation) is a **sampled signal**, not a digital signal.

$$x_q[n] \in \{L_1, \ldots, L_{2^B}\}, \quad n \in \mathbb{Z}$$

---

### Q5 (E) — CT Sinusoid General Form
What is the general form of a **continuous-time (CT) sinusoidal signal**? Name and give the units for every parameter.

**Solution:**

$$x(t) = A\cos(\Omega t + \theta)$$

| Symbol | Name | Unit |
|---|---|---|
| A | Amplitude | Same as signal unit (e.g., volts); A > 0 always |
| Ω | Angular frequency | rad/s |
| t | Continuous time | seconds (s) |
| θ | Phase angle | radians (rad) |
| F | Cyclic frequency | Hertz (Hz) |
| T₀ | Fundamental period | seconds (s) |

**Key relations:**
$$\Omega = 2\pi F, \qquad F = \frac{1}{T_0}, \qquad T_0 = \frac{2\pi}{\Omega}$$

---

### Q6 (E) — DT Sinusoid General Form
What is the general form of a **discrete-time (DT) sinusoidal signal** x(n)? What are the allowed ranges of the normalized frequency f and discrete angular frequency ω?

**Solution:**

$$x(n) = A\cos(\omega n + \phi) = A\cos(2\pi f n + \phi)$$

| Symbol | Name | Range |
|---|---|---|
| n | Sample index (integer) | n ∈ ℤ = {..., −2, −1, 0, 1, 2, ...} |
| A | Amplitude | A > 0, real |
| ω | Discrete angular frequency | ω ∈ [−π, π] (rad/sample) |
| f | Normalized frequency | f ∈ [−½, ½] (cycles/sample) |
| φ | Phase angle | radians |
| N | Period (if periodic) | smallest positive integer s.t. x(n+N) = x(n) |

Key relation: `ω = 2πf`

---

### Q7 (E) — Role of ADC and DAC
What is the role of the **A/D converter** and **D/A converter** in a DSP system?

**Solution:**

The complete DSP signal chain is:

`Analog in → A/D → DSP Core → D/A → Analog out`

- **A/D Converter (ADC):** Converts the analog (continuous-time, continuous-valued) input signal into a digital (discrete-time, discrete-valued) binary sequence that the processor can handle. It performs **sampling** (time discretization) and **quantization** (amplitude discretization).

- **D/A Converter (DAC):** Converts the processed digital output back into an analog signal so it can drive physical devices (speakers, displays, actuators). It reconstructs a continuous-time signal by interpolation from discrete samples.

Without the ADC, the digital processor cannot receive real-world input. Without the DAC, the digital output cannot be perceived or used in the physical world.

---

### Q8 (E) — Four Signal Processing Operations
Name the four main signal processing operations listed in the slides. Give a real-world application of each.

**Solution:**

| Operation | Description | Real-world Example |
|---|---|---|
| **Filtering** | Remove unwanted frequency components | Removing wind noise from a phone call |
| **Amplification** | Increase signal strength | Audio amplifier in a speaker system |
| **Compression** | Reduce data size | MP3 audio, JPEG image |
| **Modulation** | Encode a signal for transmission | 4G/5G mobile data transmission |

---

### Q9 (E) — Period of CT Sinusoid
What is the **fundamental period** T₀ of a CT sinusoid with angular frequency Ω? Write the formula.

**Solution:**

For any CT sinusoid `x(t) = A cos(Ωt + θ)`, the fundamental period is:

$$T_0 = \frac{2\pi}{\Omega} = \frac{1}{F}$$

**Proof:** The signal satisfies x(t + T₀) = x(t) for all t because:
$$\cos(\Omega(t + T_0) + \theta) = \cos(\Omega t + \underbrace{\Omega \cdot \frac{2\pi}{\Omega}}_{2\pi} + \theta) = \cos(\Omega t + \theta) ✓$$

A CT sinusoid is **always periodic** — no exceptions.

---

### Q10 (E) — Frequency Normalization
What is the relationship between the physical frequency F (in Hz), the sampling rate Fₛ (in Hz), and the normalized frequency f?

**Solution:**

$$f = \frac{F}{F_s}$$

where:
- F = physical (analog) frequency in Hz
- Fₛ = sampling rate in Hz (samples per second)
- f = normalized frequency in **cycles per sample** (dimensionless)

**Derived relation for ω:**
$$\omega = 2\pi f = 2\pi \frac{F}{F_s} = \frac{\Omega}{F_s}$$

**Intuition:** f tells you how many complete oscillation cycles happen per sample. If f = 1/4, the signal completes exactly one cycle every 4 samples.

---

# SECTION 2 — Conceptual Questions

---

### Q11 (M) — The 2×2 Signal Classification Table
Explain clearly: a signal can be *discrete-time* without being *discrete-valued*. Give a concrete example of each combination in the 2×2 signal classification table.

**Solution:**

The two independent axes of classification are **time** (CT vs DT) and **value** (continuous vs discrete). This gives four combinations:

| | **Continuous Value** | **Discrete Value** |
|---|---|---|
| **Continuous Time** | **Analog signal** — x(t) ∈ ℝ, t ∈ ℝ. *Example: microphone voltage* | **Quantized analog** — x(t) ∈ {Lᵢ}, t ∈ ℝ. *Example: thermostat output {18,19,20,21,22}°C* |
| **Discrete Time** | **Sampled signal** — x[n] ∈ ℝ, n ∈ ℤ. *Example: ideal DSP computation* | **Digital signal** — x[n] ∈ {Lᵢ}, n ∈ ℤ. *Example: MP3, JPEG, computer data* |

**Key insight:** "Discrete-time" only constrains *when* the signal is defined (at integer indices). It says nothing about the *amplitude*, which can still be any real number. "Discrete-valued" (quantized) constrains the amplitude to a finite set, independent of time.

---

### Q12 (M) — CT vs DT Periodicity
A CT sinusoid is **always periodic**. Is the same true for a DT sinusoid? Explain the key condition.

**Solution:**

**No** — a DT sinusoid is **not always periodic**.

- **CT sinusoid** `x(t) = A cos(Ωt + θ)`: Always periodic with T₀ = 2π/Ω because t is real and the period T₀ always exists as a real number.

- **DT sinusoid** `x(n) = A cos(ωn + φ)`: Periodic **only if** the normalized frequency f = ω/(2π) is a **rational number** (i.e., f = k/N for some integers k, N).

**Why?** For periodicity x(n + N) = x(n), we need ωN = 2πm for some integer m. This gives:
$$N = \frac{2\pi m}{\omega}$$
N must be a **positive integer**. This happens if and only if ω/2π = f ∈ ℚ (rational).

If f is irrational (e.g., f = 1/π), no integer N can satisfy the periodicity condition → the signal never repeats.

---

### Q13 (M) — Why is ω Bounded for DT?
Why is the normalized frequency f of a DT signal bounded to the range (−½, ½], while the CT angular frequency Ω is unbounded (from −∞ to +∞)?

**Solution:**

The key is **2π-periodicity of DT sinusoids**:

$$\cos((\omega + 2\pi)n) = \cos(\omega n + 2\pi n) = \cos(\omega n) \quad \forall n \in \mathbb{Z}$$

Since n is always an integer, adding 2π to ω gives exactly the same signal. This means all frequencies ω and ω + 2π are **indistinguishable** from samples alone. The entire real line collapses into one period of length 2π.

We conventionally choose the **principal range** ω ∈ (−π, π], which corresponds to f ∈ (−½, ½].

In CT, t is continuous, so e^{j(Ω+2π)t} ≠ e^{jΩt} — there is no such periodicity in the frequency axis. Every distinct Ω produces a genuinely different CT signal.

---

### Q14 (M) — Meaning of f = ½ and f = 0
What is the physical meaning of f = ½ in a DT sinusoid? What does f = 0 represent?

**Solution:**

- **f = 0:** DC signal. `x(n) = A cos(0) = A` — a constant sequence that never oscillates. Zero oscillations per sample.

- **f = ½ (or ω = π):** The **Nyquist frequency** — the highest representable frequency in DT. The signal `x(n) = A cos(πn)` alternates between +A and −A every sample: ..., +A, −A, +A, −A, ... This is the fastest possible oscillation in discrete time — one complete sign flip every sample.

- **f = ¼ (ω = π/2):** Completes one full cycle every 4 samples: A, 0, −A, 0, A, ...

Frequencies above f = ½ are identical to frequencies below it (aliasing), which is why the range is bounded.

---

### Q15 (M) — Phase Shift Direction
In the sinusoid x(t) = A cos(Ωt + θ), if θ > 0, does the waveform shift **left** or **right** on the time axis? Justify your answer.

**Solution:**

When θ > 0, the waveform shifts **left** (earlier in time) — the signal **leads**.

**Justification:** The peak of cos(Ωt + θ) occurs when Ωt + θ = 0, i.e., at:
$$t_{\text{peak}} = -\frac{\theta}{\Omega}$$

If θ > 0, then t_peak < 0 — the peak occurs **before** t = 0, meaning the waveform has been shifted to the left.

**Memory aid:**
- θ > 0 → phase **leads** → shifts **left**
- θ < 0 → phase **lags** → shifts **right**
- θ = π/2 → cos → sin (since cos(x + π/2) = −sin(x))

---

### Q16 (M) — Random Signal Analysis
Two random signals may look completely different from one another yet share the same statistical properties. Why is this important in DSP? How are random signals typically analyzed?

**Solution:**

Random signals (e.g., noise, speech, seismic) cannot be described by an exact mathematical formula — their future values are unpredictable. However, many different **realizations** of a random process can share the same underlying **statistical distribution** (same mean, variance, frequency content).

**Why this matters:** DSP systems must be designed to work for the entire *class* of signals sharing those statistics, not just one specific waveform. For example, a noise-cancellation algorithm cannot know the exact noise waveform in advance, but can exploit statistical properties.

**Analysis tool:** Probability and statistics — specifically:
- Mean (expected value)
- Variance / power spectral density
- Autocorrelation function (ACF)

The slides note: "Different signals may look different but share similar statistical properties" — this is the foundation of statistical signal processing.

---

### Q17 (M) — 16-bit Audio
In a mobile phone call DSP chain, voice is sampled at 8 kHz at 16-bit resolution. What does "16-bit" tell you about the signal's value representation? How many distinct amplitude levels does it produce?

**Solution:**

"16-bit" refers to the **bit depth** B = 16, meaning the quantizer maps each sample to one of:

$$2^{16} = 65{,}536 \text{ amplitude levels}$$

These 65,536 levels span the signal's dynamic range [x_min, x_max]. The quantization step size is:
$$\Delta = \frac{x_{\max} - x_{\min}}{2^{16}}$$

**In context:** Each sample is encoded as a 16-bit binary word. The bit rate of this uncompressed signal is:
$$8000 \text{ samples/s} \times 16 \text{ bits/sample} = 128{,}000 \text{ bits/s} = 128 \text{ kbps}$$

This is then compressed by AMR codec before transmission.

---

### Q18 (M) — Why Quantization Is Needed for Computers
Why must a discrete-time signal x[n] be stored as a **digital signal** for a computer to process it? What process converts a DT signal to a digital signal?

**Solution:**

A computer's memory has **finite precision** — it can only store a finite number of distinct values using a fixed number of bits (typically 8, 16, 24, 32, or 64 bits per number). A pure DT signal x[n] ∈ ℝ has **infinite possible amplitude values**, which cannot be stored exactly.

**The conversion process is quantization:**
$$x_q[n] = Q[x[n]]$$

Each continuous-amplitude sample x[n] is mapped (rounded) to the nearest value in a finite set of levels. This introduces a small but unavoidable **quantization error**:
$$e[n] = x[n] - x_q[n]$$

**Summary:** Discrete-time alone → cannot store. Discrete-time + quantized amplitude (digital) → can be stored, processed, transmitted by any digital computer.

---

### Q19 (M) — Color Video as Multichannel + Multidimensional
Explain why a color video signal is simultaneously **multichannel** and **multidimensional**. Write the mathematical representation.

**Solution:**

- **Multidimensional:** Each video frame is a 2D image I(x, y), so brightness depends on spatial coordinates x and y. Adding time makes it 3D: I(x, y, t). → Multidimensional because it depends on **multiple independent variables**.

- **Multichannel:** Color requires three separate channels (Red, Green, Blue) at each spatial and temporal location. → Multichannel because there are **multiple signal components** at each point.

**Mathematical representation:**
$$\mathbf{I}(x, y, t) = \begin{bmatrix} I_R(x, y, t) \\ I_G(x, y, t) \\ I_B(x, y, t) \end{bmatrix}$$

This is both: a **vector** (3 channels → multichannel) and a **function of 3 variables** (x, y, t → multidimensional).

---

### Q20 (M) — Positive Amplitude Convention
The slides say "A > 0 always; the sign is absorbed into θ." What does this mean? How can you represent A cos(Ωt + π) as a positive-amplitude sinusoid?

**Solution:**

The convention A > 0 means the amplitude is always taken as the **positive peak value**. A negative sign in front (like −A cos(Ωt)) is not a separate case — it is equivalent to adding π to the phase:

$$-A\cos(\Omega t) = A\cos(\Omega t + \pi)$$

This follows from the identity: cos(x + π) = −cos(x).

**Your question:** A cos(Ωt + π)
$$A\cos(\Omega t + \pi) = -A\cos(\Omega t)$$

To write with positive amplitude and absorbed phase, this is already in the standard form — amplitude = A (positive), phase θ = π. It represents a cosine flipped upside down.

**General rule:** Any sinusoid of the form −A cos(Ωt + θ) can be rewritten as A cos(Ωt + θ + π), keeping A positive.

---

# SECTION 3 — Mathematical / Derivation Questions

---

### Q21 (M) — CT Frequency Calculations
Given Ω = 2π × 50 rad/s, compute: (a) T₀, (b) F in Hz, (c) Ω in rad/s.

**Solution:**

Given: Ω = 2π × 50 rad/s (mains electricity in Bangladesh)

**(a) Period T₀:**
$$T_0 = \frac{2\pi}{\Omega} = \frac{2\pi}{2\pi \times 50} = \frac{1}{50} = 0.02 \text{ s} = 20 \text{ ms}$$

**(b) Frequency F:**
$$F = \frac{1}{T_0} = \frac{1}{0.02} = 50 \text{ Hz}$$

**(c) Angular frequency Ω:**
$$\Omega = 2\pi F = 2\pi \times 50 \approx 314.16 \text{ rad/s}$$

(This was given, confirming consistency.)

---

### Q22 (M) — DT Frequency Calculations
A DT sinusoid has physical frequency F = 1000 Hz and sampling rate Fₛ = 8000 Hz. (a) Compute f. (b) Compute ω. (c) Write x(n).

**Solution:**

**(a) Normalized frequency f:**
$$f = \frac{F}{F_s} = \frac{1000}{8000} = \frac{1}{8} = 0.125 \text{ cycles/sample}$$

**(b) Discrete angular frequency ω:**
$$\omega = 2\pi f = 2\pi \times \frac{1}{8} = \frac{\pi}{4} \text{ rad/sample}$$

**(c) Signal equation:**
$$x(n) = A\cos\!\left(\frac{\pi}{4}\,n + \phi\right)$$

**Check range:** f = 0.125 ∈ (−0.5, 0.5] ✓ — no aliasing.

---

### Q23 (M) — Quantization Formula
A B-bit ADC quantizes a signal over the range [x_min, x_max]. Write the formula for (a) step size Δ, (b) quantized value x_q[n]. How many levels for 16-bit?

**Solution:**

**(a) Quantization step size:**
$$\Delta = \frac{x_{\max} - x_{\min}}{2^B}$$

**(b) Quantized value:**
$$x_q[n] = \Delta \cdot \left\lfloor \frac{x[n]}{\Delta} + \frac{1}{2} \right\rfloor$$

(Round to nearest quantization level.)

**(c) Number of levels for 16-bit:**
$$2^{16} = 65{,}536 \text{ levels}$$

**Interpretation:** Each level represents a voltage step of Δ. The quantization error satisfies |e[n]| ≤ Δ/2 (bounded by half a step).

---

### Q24 (M) — Periodicity Check for DT Sinusoids
Determine whether the following DT sinusoids are periodic, and if so, find the period N:
(a) x(n) = cos(πn/6), (b) x(n) = cos(n), (c) x(n) = cos(0.3πn)

**Solution:**

Use the test: **periodic iff f = ω/(2π) ∈ ℚ**. If periodic, N = 2πm/ω for smallest integer m giving integer N.

**(a) x(n) = cos(πn/6), so ω = π/6:**
$$f = \frac{\omega}{2\pi} = \frac{\pi/6}{2\pi} = \frac{1}{12} \in \mathbb{Q} \quad \checkmark$$
$$N = \frac{2\pi \times 1}{\pi/6} = 12 \text{ samples}$$

**(b) x(n) = cos(n), so ω = 1 rad/sample:**
$$f = \frac{1}{2\pi} \notin \mathbb{Q} \quad \text{(irrational)}$$
→ **NOT periodic** — the signal never exactly repeats.

**(c) x(n) = cos(0.3πn), so ω = 0.3π:**
$$f = \frac{0.3\pi}{2\pi} = \frac{0.3}{2} = \frac{3}{20} \in \mathbb{Q} \quad \checkmark$$
$$N = \frac{2\pi \times 1}{0.3\pi} = \frac{2}{0.3} = \frac{20}{3} \notin \mathbb{Z}$$
Try m = 3: N = 2π × 3 / (0.3π) = 20 ✓
→ **Periodic with N = 20 samples**

---

### Q25 (M) — Converting Sample Index to Time
At sampling rate Fₛ = 8000 Hz, at what sample index n does t = 20 ms occur?

**Solution:**

The relationship between sample index and time is:
$$t = \frac{n}{F_s} \implies n = t \cdot F_s$$

Substituting:
$$n = 0.020 \text{ s} \times 8000 \text{ samples/s} = 160$$

So sample n = 160 corresponds to t = 20 ms.

**Verification:** t = 160/8000 = 0.020 s = 20 ms ✓

---

### Q26 (M) — Phase Identity
Express x(t) = cos(Ωt + π/2) as a sine function. Show the identity.

**Solution:**

Using the trigonometric identity:
$$\cos\!\left(\alpha + \frac{\pi}{2}\right) = -\sin(\alpha)$$

Therefore:
$$x(t) = \cos\!\left(\Omega t + \frac{\pi}{2}\right) = -\sin(\Omega t)$$

**Verification:** cos(Ωt + π/2) = cos(Ωt)cos(π/2) − sin(Ωt)sin(π/2) = 0 − sin(Ωt) = −sin(Ωt) ✓

This confirms the slides' statement: θ = π/2 converts cos → (negative) sin.

---

### Q27 (M) — Deriving the Power of a CT Sinusoid
The power of A cos(Ωt + θ) is A²/2. Derive this result.

**Solution:**

Power is defined as the time average of the squared signal:
$$P = \lim_{T \to \infty} \frac{1}{T} \int_0^T x^2(t)\, dt = \frac{1}{T_0}\int_0^{T_0} A^2\cos^2(\Omega t + \theta)\, dt$$

Using the identity: cos²(u) = (1 + cos(2u))/2:
$$P = \frac{A^2}{T_0}\int_0^{T_0} \frac{1 + \cos(2\Omega t + 2\theta)}{2}\, dt$$

$$P = \frac{A^2}{2T_0}\left[\int_0^{T_0} 1\, dt + \underbrace{\int_0^{T_0}\cos(2\Omega t + 2\theta)\, dt}_{=\,0 \text{ (full period of cosine)}}\right]$$

$$\boxed{P = \frac{A^2}{2}}$$

The cosine integral over a full period is zero, leaving only the constant term.

---

### Q28 (M) — Finding Period from ω
A DT sinusoid has ω = π/4 rad/sample. Find the smallest period N. Show all steps.

**Solution:**

**Step 1:** Check rationality.
$$f = \frac{\omega}{2\pi} = \frac{\pi/4}{2\pi} = \frac{1}{8} \in \mathbb{Q} \quad \checkmark$$
Signal is periodic.

**Step 2:** Apply the formula N = 2πm/ω, find smallest integer N.
$$N = \frac{2\pi m}{\pi/4} = 8m$$

For m = 1: N = 8 ✓ (integer)

**Answer:** The fundamental period is **N = 8 samples**.

**Verification:** x(n + 8) = cos(π/4 · (n + 8)) = cos(πn/4 + 2π) = cos(πn/4) = x(n) ✓

---

# SECTION 4 — Tricky / Exam-Style Questions

---

### Q29 (H) — Does Sampling Rate Affect Frequency?
A student claims: "If I sample a 5 kHz sinusoid at Fₛ = 8 kHz, then at Fₛ = 16 kHz, I get two DT signals with different frequencies." Is the student correct?

**Solution:**

The student is **partially correct but misleading**.

The **normalized frequency** f = F/Fₛ does differ:
- At Fₛ = 8000 Hz: f = 5000/8000 = 5/8 **> ½ → aliasing!**
- At Fₛ = 16000 Hz: f = 5000/16000 = 5/16 ∈ (0, ½) → no aliasing ✓

At Fₛ = 8000 Hz, the 5 kHz signal **aliases** — it appears as |5000 − 8000| = 3000 Hz.
At Fₛ = 16000 Hz, the 5 kHz signal is **correctly represented** with ω = 2π × 5/16 = 5π/8.

So yes, the two DT signals are different — but the reason is deeper: at 8 kHz sampling, the Nyquist criterion is violated (requires Fₛ ≥ 10 kHz for a 5 kHz signal), and the represented frequency is wrong. The student's framing misses the aliasing issue entirely.

---

### Q30 (H) — True or False: Signal Classification
True or False (justify each):
(a) Every DT signal is also a digital signal.
(b) A digital signal is always discrete in both time and value.
(c) A CT signal can be discrete-valued.
(d) A DT sinusoid with irrational ω is always aperiodic.

**Solution:**

**(a) FALSE.** A DT signal has a discrete time index (n ∈ ℤ) but its amplitude x[n] ∈ ℝ can be any real number. It is not digital unless the amplitude is also quantized to a finite set.

**(b) TRUE.** By definition, a digital signal must be discrete in time (n ∈ ℤ) AND discrete in value (x[n] ∈ finite set). This is the definition — both conditions are required.

**(c) TRUE.** A continuous-time signal can take only a finite set of values. Example: a thermostat that reads temperature continuously in time but only outputs values from {18, 19, 20, 21, 22}°C. This is a quantized-analog signal — bottom-right cell of the 2×2 table.

**(d) TRUE.** A DT sinusoid x(n) = cos(ωn) is periodic iff f = ω/(2π) ∈ ℚ. If ω is irrational (e.g., ω = √2 rad), then f = √2/(2π) is also irrational (irrational/irrational can be either, but ω itself irrational → ω/2π irrational since 2π is transcendental). The signal never repeats.

---

### Q31 (H) — 2π-Periodicity of DT Sinusoids
x(n) = cos(ωn) and y(n) = cos((ω + 2π)n). Are they the same signal? What property does this demonstrate?

**Solution:**

**Yes, they are identical.**

$$y(n) = \cos((\omega + 2\pi)n) = \cos(\omega n + 2\pi n)$$

Since n ∈ ℤ (always an integer), 2πn is always an exact multiple of 2π:
$$\cos(\omega n + 2\pi n) = \cos(\omega n) = x(n) \quad \forall n \in \mathbb{Z}$$

This demonstrates **2π-periodicity in frequency** for DT sinusoids:

> In discrete time, sinusoids with frequencies ω and ω + 2π are **indistinguishable** from their samples alone.

**Consequence:** The frequency axis of DT signals "wraps around" every 2π. The highest unique frequency is ω = π (f = ½). All frequencies outside [−π, π] are aliases of frequencies inside this range. This is why the slides state: "DT: ω and ω + 2π give the same signal."

---

### Q32 (H) — Thermostat Classification
A thermostat reads temperature continuously but outputs only values {18, 19, 20, 21, 22}°C. What type of signal is this? Classify it precisely.

**Solution:**

This signal is:
- **Continuous-time**: the thermostat reads temperature at all times t ∈ ℝ (it monitors continuously)
- **Discrete-valued**: the output is restricted to 5 fixed levels — {18, 19, 20, 21, 22}°C

Using the 2×2 classification table: this is a **quantized analog signal** (top-right cell: continuous time, discrete value).

It is **NOT** a digital signal (which requires discrete time too) and **NOT** an analog signal (which requires continuous value too).

This is exactly the example used in the slides to illustrate that continuous-time and discrete-valued can coexist independently.

---

### Q33 (H) — Physical Meaning of Sample Index n
The sample index n is described as "dimensionless on its own." What gives n units of time, and what formula converts n to real time t?

**Solution:**

By itself, n is simply an integer counter: n ∈ {0, 1, 2, 3, ...}. It has **no units**.

To convert n to physical time t, you need the **sampling period** Tₛ = 1/Fₛ:

$$t = n \cdot T_s = \frac{n}{F_s}$$

where Fₛ is the sampling frequency in Hz (samples per second).

**Example from the slides:** If Fₛ = 8000 Hz, then:
- n = 160 → t = 160/8000 = 0.020 s = 20 ms

This is also why the n-axis in stem plots is labelled "sample index" and not "time (s)" — it only becomes time once the sampling rate is specified.

---

### Q34 (H) — Analog Speed Advantage
Why do the slides show that analog systems have **higher raw speed** than digital systems? What is the fundamental trade-off?

**Solution:**

Analog systems process signals **physically in continuous time** — electrical circuits respond instantaneously to input changes, limited only by component physics (RC time constants, transistor bandwidth). There is no need to sample, digitize, or wait for a processor clock cycle.

Digital systems require:
1. **A fast ADC clock** to sample at Fₛ
2. **Processing time** for the DSP algorithm
3. **DAC reconstruction** time

These introduce **latency** and impose a **speed ceiling** at the Nyquist rate.

**The fundamental trade-off:**

| Property | Analog | Digital |
|---|---|---|
| Speed | Very fast (circuit-limited) | Requires fast ADC clock |
| Flexibility | Fixed hardware design | Reprogrammable in software |
| Noise immunity | Low (noise accumulates) | High (error detection/correction) |
| Precision | Limited by component tolerances | Set exactly by bit depth |
| Storage | Degrades over time | Lossless (hard drives, cloud) |

Modern systems combine both: analog front-end for speed, digital back-end for programmability and precision.

---

### Q35 (H) — Period Verification
A student writes: "x(n) = cos(9πn/7) has period N = 7." Check whether this is correct.

**Solution:**

The student is **wrong**.

**Step 1:** Identify ω = 9π/7.

**Step 2:** Compute f:
$$f = \frac{\omega}{2\pi} = \frac{9\pi/7}{2\pi} = \frac{9}{14} \in \mathbb{Q} \quad \checkmark$$

**Step 3:** Find N using N = 2πm/ω:
$$N = \frac{2\pi m}{9\pi/7} = \frac{14m}{9}$$

For this to be an integer, m must be a multiple of 9. Smallest: m = 9 → N = 14.

**Check m = 1:** N = 14/9 ✗ (not integer)
**Check m = 9:** N = 14 ✓

**Correct answer: N = 14 samples**, not 7.

The student's error was likely confusing the denominator of ω with the period, without applying the full 2πm/ω formula and checking for integer N.

---

### Q36 (H) — Why ω + 2π Differs in CT but Not DT
Explain intuitively: why does adding 2π to ω in a DT sinusoid produce the **exact same signal**, but adding 2π to Ω in a CT sinusoid produces a **different (higher-frequency) signal**?

**Solution:**

The difference is entirely in the **nature of the independent variable** (integer vs real).

**DT case:** The signal is evaluated only at integers n ∈ ℤ.
$$\cos((\omega + 2\pi)n) = \cos(\omega n + 2\pi n)$$
Since n is always an integer, 2πn is always a multiple of 2π → cosine is unchanged. **Adding 2π to ω leaves the signal values exactly the same** at every sample point.

**CT case:** The signal is evaluated at all real t ∈ ℝ.
$$\cos((\Omega + 2\pi)t) = \cos(\Omega t + 2\pi t)$$
Since t is a continuous real number, 2πt is generally **not** a multiple of 2π. For example, at t = 0.3: 2π × 0.3 = 0.6π ≠ 0, 2π, 4π... So the two signals differ at almost every point.

**Intuition:** In CT, every real t is a potential evaluation point, so adding 2π to frequency actually rotates the phase by a different amount at each t. In DT, the integers "align" perfectly with 2π, so the extra winding cancels out completely.

---

# SECTION 5 — Sampling & the Nyquist–Shannon Theorem

---

### Q41 (E) — Nyquist–Shannon Theorem
State the Nyquist–Shannon Sampling Theorem precisely. What is the Nyquist rate? What is the physical consequence of violating it?

**Solution:**

**Theorem (Nyquist–Shannon, 1949):**
> A band-limited signal with highest frequency fₘₐₓ can be **perfectly reconstructed** from its samples **if and only if**:
> $$f_s \geq 2f_{\max}$$

The **Nyquist rate** is fₙ = 2fₘₐₓ — the minimum sampling frequency required.

In angular frequency terms: Ωₛ ≥ 2Ωₘₐₓ.

**Consequence of violation (fₛ < 2fₘₐₓ):**
High-frequency components "fold back" and appear as spurious lower-frequency components in the sampled signal — this is called **aliasing**. The original signal **cannot be recovered** from aliased samples, no matter how sophisticated the reconstruction algorithm. The damage is irreversible.

---

### Q42 (M) — Sampling Definition
Define the sampling interval T and its relationship to fₛ. Write the equation defining how samples x(n) are obtained from xₐ(t).

**Solution:**

**Sampling** converts a CT signal xₐ(t) into a DT signal x(n) by measuring its value at **equally spaced instants**:

$$x_a(nT) = x(n), \quad n \in \mathbb{Z}$$

where **T = sampling interval** (seconds) = time between consecutive samples.

**Relationship:** 
$$f_s = \frac{1}{T} \quad \text{(sampling frequency in Hz)}$$

Each sample x(n) is the amplitude of the analog signal at time t = nT.

**Key property:** Sampling is **reversible** (no information loss) provided fₛ ≥ 2fₘₐₓ. The original continuous signal can be perfectly recovered by ideal interpolation (sinc reconstruction) from its samples.

---

### Q43 (M) — Reversibility of Sampling vs Quantization
The slides state that sampling is **reversible** but quantization is **always irreversible**. Explain why.

**Solution:**

**Sampling is reversible** (under Nyquist condition) because:
- Each sample value x(n) = xₐ(nT) is the **exact** analog value — no information is discarded.
- The Nyquist-Shannon theorem guarantees that from samples taken at fₛ ≥ 2fₘₐₓ, you can perfectly reconstruct the original analog signal using sinc interpolation.
- The mapping xₐ(t) → x(n) is **injective** (one-to-one) for band-limited signals.

**Quantization is irreversible** because:
- Each sample x(n) ∈ ℝ (infinite precision) is mapped to the **nearest finite level** xq(n) — information is permanently thrown away.
- Many different real values map to the same quantization level (the mapping is many-to-one, not invertible).
- There is no way to recover the original x(n) from xq(n) because the quantization error e(n) = x(n) − xq(n) is not stored.

**Summary:** Sampling discards nothing (under Nyquist). Quantization discards the fractional part of each amplitude value — permanently.

---

### Q44 (M) — Why CD Uses 44.1 kHz
Why does a CD use a sampling rate of 44.1 kHz? Trace the reasoning from the Nyquist criterion.

**Solution:**

**Step 1:** Human hearing range is approximately **20 Hz to 20 kHz**.

**Step 2:** To capture all audible frequencies, the Nyquist criterion requires:
$$f_s \geq 2 \times f_{\max} = 2 \times 20{,}000 = 40{,}000 \text{ Hz}$$

**Step 3:** The practical minimum is 40 kHz, but engineers add a **safety margin** to accommodate the roll-off of real anti-aliasing filters (which cannot cut off infinitely sharply at 20 kHz).

**Step 4:** 44.1 kHz > 40 kHz ✓ — satisfies Nyquist with margin.

(44.1 kHz was also historically tied to compatibility with video equipment — 3 samples per video line × 245 lines × 60 fields/s = 44,100 Hz.)

---

### Q45 (M) — Anti-Aliasing Filter
What is an **anti-aliasing filter** and where in the A/D pipeline must it be placed? What would happen if it were applied after sampling?

**Solution:**

An **anti-aliasing filter** is a **low-pass filter** (LPF) that removes all frequency components above fₛ/2 (the Nyquist frequency) from the analog signal **before** it is sampled.

**Correct placement:** Before the sampler — in the analog domain:
$$x_a(t) \xrightarrow{\text{LPF}} x_{\text{filtered}}(t) \xrightarrow{\text{Sample}} x(n)$$

**Why before:** Once sampling occurs and aliasing has happened, the alias frequencies are indistinguishable from genuine low-frequency components. Filtering after sampling cannot remove them — you cannot tell which low-frequency components are real and which are aliases.

**If applied after sampling:** The filter would operate on the DT signal, which already contains aliased components. It would only remove frequencies above fₛ/2 in the DT domain, but since aliases have already "folded" into the baseband, they cannot be separated. The damage cannot be undone.

---

# SECTION 6 — Aliasing: Conceptual & Computational

---

### Q46 (M) — Definition of Aliasing
Define **aliasing** precisely. What is the physical reason it occurs?

**Solution:**

**Aliasing** is the phenomenon where, when a signal is sampled below the Nyquist rate (fₛ < 2fₘₐₓ), high-frequency components of the signal **masquerade as lower-frequency components** in the sampled signal — they produce the same set of sample values as a lower-frequency sinusoid would.

**Physical reason:** When fₛ is too low, the sampling interval T = 1/fₛ is too large. A high-frequency sinusoid (many oscillations per second) is sampled so infrequently that the samples match those of a lower-frequency sinusoid that oscillates less between samples. The two signals are **indistinguishable** from their samples alone.

**Formula:** A signal at frequency F sampled at Fₛ appears at:
$$f_{\text{alias}} = |F - k \cdot F_s|, \quad k \in \mathbb{Z}$$
Choose k so that fₐₗᵢₐₛ ∈ [0, Fₛ/2].

---

### Q47 (M) — Alias Frequency Formula
Write the formula for fₐₗᵢₐₛ. What constraint must it satisfy?

**Solution:**

$$f_{\text{alias}} = |F - k \cdot F_s|, \quad k \in \mathbb{Z}$$

Choose the integer k such that:
$$f_{\text{alias}} \in \left[0,\; \frac{F_s}{2}\right]$$

This places fₐₗᵢₐₛ within the **principal frequency range** (Nyquist band) of the sampled signal.

**Intuition:** Aliasing is equivalent to the 2π-wrapping of DT frequencies. In discrete time, any frequency ω outside [−π, π] is identical to its reduction modulo 2π back into [−π, π].

**Example:** F = 900 Hz, Fₛ = 1000 Hz, k = 1:
$$f_{\text{alias}} = |900 - 1 \times 1000| = 100 \text{ Hz}$$

---

### Q48 (H) — Full Aliasing Worked Example
xₐ(t) = 3 cos(100πt) is sampled at Fₛ = 75 Hz. Answer (a)–(e).

**Solution:**

**(a) Physical frequency F:**
Compare 100πt with 2πFt:
$$2\pi F = 100\pi \implies F = 50 \text{ Hz}$$

**(b) Is Nyquist satisfied?**
$$2F = 100 \text{ Hz} > F_s = 75 \text{ Hz} \quad \times$$
**No** — Nyquist is violated. Aliasing will occur.

**(c) DT signal by substitution t = n/Fₛ:**
$$x[n] = 3\cos\!\left(100\pi \cdot \frac{n}{75}\right) = 3\cos\!\left(\frac{4\pi}{3}\,n\right)$$

**(d) Reduce to principal range [−π, π):**
$$\omega = \frac{4\pi}{3} > \pi \quad \Rightarrow \quad \frac{4\pi}{3} - 2\pi = -\frac{2\pi}{3}$$
Using cos(−u) = cos(u):
$$x[n] = 3\cos\!\left(\frac{2\pi}{3}\,n\right)$$

**(e) Alias frequency in Hz:**
$$F_{\text{alias}} = \frac{\omega}{2\pi} \cdot F_s = \frac{2\pi/3}{2\pi} \times 75 = \frac{1}{3} \times 75 = 25 \text{ Hz}$$

**Conclusion:** The 50 Hz signal appears as a 25 Hz signal after sampling at 75 Hz.

---

### Q49 (M) — Sampling at 200 Hz (No Aliasing)
xₐ(t) = 3 cos(100πt) sampled at Fₛ = 200 Hz. (a) Write x[n]. (b) Does aliasing occur?

**Solution:**

**(a) DT signal:**
$$x[n] = 3\cos\!\left(100\pi \cdot \frac{n}{200}\right) = 3\cos\!\left(\frac{\pi}{2}\,n\right)$$

Check range: ω = π/2 ∈ (−π, π] ✓ — already in principal range.

**(b) Aliasing check:**
$$F_s = 200 \text{ Hz} > 2F = 100 \text{ Hz} \quad \checkmark$$
**No aliasing** — Nyquist is satisfied.

The discrete frequency is:
$$f = \frac{F}{F_s} = \frac{50}{200} = \frac{1}{4} \in \left(-\frac{1}{2}, \frac{1}{2}\right] \quad \checkmark$$

---

### Q50 (M) — Alias Frequency Calculation
A 900 Hz sinusoid is sampled at fₛ = 1000 Hz. What alias frequency does it appear as?

**Solution:**

$$f_{\text{alias}} = |F - k \cdot F_s|, \quad k \in \mathbb{Z}$$

Try k = 1:
$$f_{\text{alias}} = |900 - 1 \times 1000| = |-100| = 100 \text{ Hz}$$

Check: 100 Hz ∈ [0, Fₛ/2] = [0, 500] ✓

**Answer:** The 900 Hz signal appears as a **100 Hz signal** when sampled at 1000 Hz.

**Intuition:** 900 Hz is only 100 Hz below the sampling rate. When sampled at 1000 Hz, the signal "wraps" around and appears 100 Hz above DC (from the other side of the spectrum).

---

# SECTION 7 — The A/D Conversion Pipeline

---

### Q51 (E) — The Three-Stage ADC Pipeline
Draw and label the three-stage A/D conversion pipeline. What is the signal type at the output of each stage?

**Solution:**

```
Analog Signal   →  [Sampler]  →  [Quantizer]  →  [Coder]  →  Digital Signal
   xₐ(t)                                                         0 1 0 1 1...
```

| Stage | Output type | Description |
|---|---|---|
| **Sampler** | Discrete-time, continuous-valued | Takes snapshots at intervals T; x[n] = xₐ(nT) ∈ ℝ |
| **Quantizer** | Discrete-time, discrete-valued | Maps each x[n] to nearest of 2^B levels; xq[n] ∈ {L₁,...,L_{2^B}} |
| **Coder** | Binary sequence | Encodes each level as a b-bit binary word; output = bitstream 01011... |

**ADC = Quantizer + Coder** (slides' labelling). The full pipeline including Sampler converts analog → digital.

**Key insight:** Although modelled as 3 steps, in practice a single IC chip performs all three operations simultaneously.

---

### Q52 (E) — Why One Device for ADC
Why does the slides' key insight say all three ADC operations are performed by a **single device**?

**Solution:**

The modular decomposition (Sampler → Quantizer → Coder) is a **conceptual model** for understanding and analysis. In hardware, these operations are:

1. **Simultaneous** — the chip samples and quantizes in one triggered clock cycle
2. **Inseparable** — it is physically impossible to store a "sampled but unquantized" real value in digital hardware; the very act of storing a number in a register quantizes it to the register's bit depth
3. **Ordered** — sampling must always precede quantization (you cannot quantize an analog signal without first choosing when to measure it)

A real ADC chip takes an analog input voltage and outputs a binary word (e.g., "1001 1011") in microseconds, with no intermediate "discrete-time continuous-valued" signal existing outside the chip's internals.

---

### Q53 (E) — Quantization Definition
What is **quantization**? Write the definition of xq(n). What is the quantization error e(n)?

**Solution:**

**Quantization** maps each sample x(n) (which can be any real value) to the **nearest value** from a finite set of levels {L₁, L₂, ..., L_{2^b}}:

$$x_q(n) = Q[x(n)]$$

where Q[·] is the rounding/truncation operator.

**Quantization error:**
$$e(n) = x(n) - x_q(n)$$

**Properties of quantization error:**
- Bounded: |e(n)| ≤ Δ/2 where Δ is the step size
- Irreversible: once quantized, e(n) cannot be recovered
- Treated as noise in analysis (called "quantization noise")
- More bits → smaller Δ → smaller |e(n)|

---

### Q54 (E) — Bit Depth Table
How many quantization levels does a b-bit ADC produce? Complete the table.

**Solution:**

Number of levels = 2^b

| Bit depth | Number of levels | Application |
|---|---|---|
| 8-bit | 2⁸ = **256** | Telephone audio |
| 16-bit | 2¹⁶ = **65,536** | CD audio |
| 24-bit | 2²⁴ = **16,777,216 ≈ 16.7M** | Studio recording |

**Rule of thumb:** Each additional bit **doubles** the number of levels and reduces quantization noise by approximately 6 dB (SNR ≈ 6.02B + 1.76 dB).

---

### Q55 (M) — Coding: Binary Representation
What is the role of the **Coder**? Given a quantized level of 5 in a 3-bit system, what is its binary representation?

**Solution:**

**Role of Coder:** The coder assigns a unique **b-bit binary codeword** to each of the 2^b quantization levels. It converts the integer level index into a binary bit stream that can be stored, transmitted, and processed by digital hardware.

**Binary representation of level 5 in 3-bit system:**

With 3 bits: levels 0 to 7, each encoded as:

| Level | Binary |
|---|---|
| 0 | 000 |
| 1 | 001 |
| 2 | 010 |
| 3 | 011 |
| 4 | 100 |
| **5** | **101** |
| 6 | 110 |
| 7 | 111 |

Level 5 → **101**

- **MSB** (Most Significant Bit) = **1** (leftmost)
- **LSB** (Least Significant Bit) = **1** (rightmost)

Verify: 1×2² + 0×2¹ + 1×2⁰ = 4 + 0 + 1 = 5 ✓

---

# SECTION 8 — D/A Conversion

---

### Q56 (E) — Why D/A Conversion Is Necessary
Why is D/A conversion necessary? Why can digital output not simply be "used" without it?

**Solution:**

Digital signals are **sequences of binary numbers** — abstract mathematical objects. The physical world operates in continuous time and continuous amplitude. To drive physical devices (speakers, motors, displays), you need an actual continuous-time voltage or current.

Specifically:
- A **speaker** requires a continuously varying air pressure wave — it cannot respond to a series of integers
- A **human ear** perceives sound as a continuous pressure wave, not discrete samples
- **Actuators and amplifiers** need a smooth analog input signal

The D/A converter "connects the dots" — it takes the discrete samples and reconstructs a continuous-time approximation of the original analog signal using interpolation.

Without D/A: you get numbers. With D/A: you get sound, images, control signals.

---

### Q57 (M) — D/A Interpolation Methods
Name the three D/A interpolation methods from the slides. Describe each in one sentence. Which produces a "staircase"?

**Solution:**

| Method | Description |
|---|---|
| **Zero-Order Hold (ZOH)** | Holds each sample value constant until the next sample — produces a **staircase** waveform |
| **Linear interpolation** | Connects successive sample values with straight lines — produces a piecewise-linear waveform |
| **Quadratic interpolation** | Fits a parabola through 3 successive samples — produces a smoother curved approximation |

**ZOH produces the staircase** because it simply latches the current sample value and holds it for the full sampling interval T before jumping to the next value. This creates square-step transitions between samples.

Higher-order interpolation methods produce smoother outputs but require more computation. An ideal DAC would use **sinc interpolation** (ideal low-pass filtering), which perfectly reconstructs the original signal if sampling was done above Nyquist.

---

### Q58 (M) — ZOH Distortion and Remedy
What distortion does ZOH introduce, and what would be added after ZOH for smoother reconstruction?

**Solution:**

**Distortion introduced by ZOH:**
- **Staircase artifact** — high-frequency step transitions at each sample boundary
- These steps contain spectral energy at multiples of fₛ — frequency components that were NOT in the original signal
- ZOH acts like a filter with frequency response |H(f)| = T·|sinc(fT)|, which **attenuates higher frequencies** and introduces a slight **amplitude droop** near fₛ/2

**Remedy:** A **reconstruction low-pass filter** (also called a **smoothing filter** or **post-filter**) is applied after the ZOH DAC:
- Removes the high-frequency staircase harmonics
- Smooths the output into a continuously varying waveform
- Ideally a perfect low-pass filter at fₛ/2

In practice, this filter also compensates for the sinc frequency droop of the ZOH to flatten the passband response.

---

# SECTION 9 — Worked Problem-Solving Questions

---

### Q59 (M) — A-note Sampling Full Worked Example
xₐ(t) = 2cos(2π × 440 · t) sampled at Fₛ = 8000 Hz. Full solution.

**Solution:**

**(a) Write x(n) by substituting t = n/Fₛ:**
$$x(n) = 2\cos\!\left(2\pi \times 440 \times \frac{n}{8000}\right)$$

**(b) Simplify ω:**
$$\omega = \frac{2\pi \times 440}{8000} = \frac{2\pi \times 11}{200} = \frac{11\pi}{100} \text{ rad/sample}$$

So: x(n) = 2cos(11πn/100)

**(c) Is it periodic? Check rationality of f:**
$$f = \frac{440}{8000} = \frac{11}{200} \in \mathbb{Q} \quad \checkmark$$
Signal **is periodic**.

**(d) Find fundamental period N:**
$$N = \frac{2\pi m}{\omega} = \frac{2\pi m}{11\pi/100} = \frac{200m}{11}$$

Find smallest m such that N is a positive integer:
- m = 1: N = 200/11 ≈ 18.18 ✗
- m = 2: N = 400/11 ≈ 36.36 ✗
- ...
- **m = 11: N = 200/11 × 11 = 200 ✓**

**Answer:** x(n) = 2cos(11πn/100), periodic with **N = 200 samples per cycle**.

Physical check: At 8000 Hz, one period of 440 Hz takes 8000/440 = 200/11 samples. After 11 full musical periods (11 × 1/440 = 11/440 s), exactly 200 samples have been taken → period = 200 samples.

---

### Q60 (H) — Period of x(n) = 3cos(3πn/7 + π/3)
Determine whether x(n) = 3cos(3πn/7 + π/3) is periodic. If so, find N. Show all steps.

**Solution:**

**Step 1: Identify ω:**
$$\omega = \frac{3\pi}{7}$$

(Phase π/3 does not affect periodicity — it only shifts the signal.)

**Step 2: Compute f:**
$$f = \frac{\omega}{2\pi} = \frac{3\pi/7}{2\pi} = \frac{3}{14}$$

Is f = 3/14 ∈ ℚ? **YES** (it is k/N with k = 3, N = 14) ✓ → Signal is **periodic**.

**Step 3: Find fundamental period N:**
$$N = \frac{2\pi m}{\omega} = \frac{2\pi m}{3\pi/7} = \frac{14m}{3}$$

Find smallest positive integer m such that N ∈ ℤ:
- m = 1: N = 14/3 ✗
- m = 2: N = 28/3 ✗
- **m = 3: N = 14 ✓**

**Answer:** x(n) is **periodic with fundamental period N = 14 samples**.

**Verification:** x(n + 14) = 3cos(3π(n+14)/7 + π/3) = 3cos(3πn/7 + 6π + π/3) = 3cos(3πn/7 + π/3) ✓

---

### Q61 (M) — Voice Digitization Specifications
Voice signal: fₘₐₓ = 4 kHz, 8-bit, Nyquist rate. Find (a) minimum sampling rate, (b) quantization levels, (c) bit rate.

**Solution:**

**(a) Minimum sampling rate (Nyquist):**
$$f_s^{\min} = 2 \times f_{\max} = 2 \times 4000 = \textbf{8000 Hz} \text{ (8 kHz)}$$

This matches the telephone standard (G.711).

**(b) Number of quantization levels:**
$$2^b = 2^8 = \textbf{256 levels}$$

**(c) Bit rate:**
$$R = f_s \times b = 8000 \frac{\text{samples}}{\text{s}} \times 8 \frac{\text{bits}}{\text{sample}} = \textbf{64{,}000 bits/s} = \textbf{64 kbps}$$

This is the standard PCM (Pulse Code Modulation) bit rate for a telephone-quality voice channel. The AMR codec compresses this further to 4.75–12.2 kbps for mobile transmission.

---

# SECTION 10 — Tricky Exam-Style Questions (Continued)

---

### Q62 (H) — Bit Depth vs Sampling Rate
"I should always increase bit depth first before increasing sampling rate." Critically evaluate this.

**Solution:**

This statement is **context-dependent** — neither always correct nor always wrong.

**When increasing bit depth matters more:**
- When the signal's **amplitude precision** is the bottleneck (e.g., low SNR due to quantization noise)
- When the signal bandwidth is already captured correctly (fₛ ≥ 2fₘₐₓ satisfied)
- Example: Medical ECG recordings where fₛ = 1000 Hz suffices but 24-bit depth is needed to resolve tiny cardiac events

**When increasing sampling rate matters more:**
- When **aliasing** is occurring (fₛ < 2fₘₐₓ) — no amount of extra bits fixes aliased data
- When high-frequency signal content is being missed
- Example: High-fidelity audio capturing beyond 20 kHz for audiophile applications

**Key principle:** Aliasing errors (from insufficient fₛ) are **irreversible and catastrophic** — they mix signal components together permanently. Quantization errors (from insufficient bits) are **bounded and gradual** — you get a slightly noisy signal, but the frequency content is preserved.

**Rule of thumb:** Fix aliasing first (ensure Nyquist), then increase bit depth for better amplitude resolution.

---

### Q63 (H) — True or False: ADC Properties
Justify each:
(a) Aliasing is irreversible once it has occurred.
(b) Sampling at exactly fₛ = 2fₘₐₓ always guarantees perfect reconstruction.
(c) Quantization error is always positive.
(d) Increasing sampling rate reduces quantization error.
(e) The coder loses information compared to the quantizer output.

**Solution:**

**(a) TRUE.** Once a high-frequency component aliases to a lower frequency, its samples are identical to those of the genuine lower-frequency signal. There is no mathematical way to distinguish them — the information is permanently destroyed.

**(b) FALSE.** Sampling at exactly the Nyquist rate (fₛ = 2fₘₐₓ) is the *theoretical* minimum, but in practice it fails for signals with energy at exactly fₘₐₓ (e.g., a cosine at fₘₐₓ could be sampled always at its zero crossings, giving a zero output). Perfect reconstruction requires a strict inequality fₛ > 2fₘₐₓ or use of ideal interpolation filters, which are physically unrealizable.

**(c) FALSE.** Quantization error e(n) = x(n) − xq(n) can be **positive or negative** depending on whether the sample is rounded up or down. It is bounded by |e(n)| ≤ Δ/2 and is approximately uniformly distributed on [−Δ/2, +Δ/2] for complex signals.

**(d) FALSE.** Sampling rate controls **time resolution** (and aliasing). It has **no direct effect** on quantization error, which is determined solely by bit depth B and step size Δ = (xₘₐₓ − xₘᵢₙ)/2^B. To reduce quantization error, increase B — not fₛ.

**(e) FALSE.** The coder is a **lossless** mapping: it assigns a unique binary codeword to each of the 2^b quantization levels. Given the binary output, you can exactly recover the quantization level. The information loss occurs in the **quantizer** step, not the coder.

---

### Q64 (H) — Information Loss from Aliasing
If you only have the aliased samples, can you tell whether the original was 50 Hz or 25 Hz?

**Solution:**

**No, you cannot tell.** This is the fundamental nature of aliasing.

At Fₛ = 75 Hz, both a 50 Hz sinusoid and a 25 Hz sinusoid produce **identical sample sequences**:
$$3\cos(2\pi \times 50 \times \frac{n}{75}) = 3\cos\!\left(\frac{2\pi}{3}n\right) = 3\cos(2\pi \times 25 \times \frac{n}{75})$$

The samples are mathematically equivalent — no algorithm, however sophisticated, can determine which frequency produced them.

**Implication:** Aliasing is a **many-to-one mapping** — infinitely many different analog frequencies (F, F ± Fₛ, F ± 2Fₛ, ...) all produce exactly the same sample sequence. The original frequency information is destroyed.

This is why the anti-aliasing filter must be applied **before** sampling — once the samples are taken, the damage is permanent and irreversible.

---

### Q65 (H) — Why Sampling Must Precede Quantization
Why can the ADC order (Sampler → Quantizer → Coder) never be reversed? What would "quantize first" mean?

**Solution:**

**Sampling must precede quantization** because:

1. **Quantization requires a specific value to round.** To quantize, you must first have a definite sample amplitude to map to a level. An analog signal xₐ(t) exists at every real t simultaneously — there is no single "value" to quantize until you pick a specific time t = nT (i.e., sample first).

2. **"Quantizing first" is physically undefined.** You would need to simultaneously quantize the amplitude of a continuous-time signal at every instant, which would require infinite operations per second (uncountably many time instants). This is physically impossible.

3. **Logically:** Quantization maps ℝ → finite set. This requires a finite number of values as input. Sampling provides this (one value per time instant). The reverse order has no mathematical meaning.

In short: you cannot round a number you haven't yet measured.

---

### Q66 (H) — The Only Inherently Lossy Step
In the full DSP chain xₐ(t) → ADC → DSP Core → DAC → output, which single step is inherently lossy?

**Solution:**

The **Quantizer** (within the ADC) is the only inherently and irreversibly lossy step.

**Why each step is reversible or lossless:**

| Step | Reversible? | Reason |
|---|---|---|
| **Sampler** | ✓ Yes (under Nyquist) | Perfect reconstruction possible via sinc interpolation |
| **Quantizer** | ✗ **NO** | Many-to-one mapping; e(n) is discarded and irrecoverable |
| **Coder** | ✓ Yes | Bijective (one-to-one): given the binary code, level is recovered exactly |
| **DSP Core** | ✓ (usually) | Algorithms are typically designed to be reversible (e.g., FIR filtering is invertible in principle) |
| **DAC** | ✓ (approximately) | Reconstruction filters and interpolation aim to reverse the sampling |

**Conclusion:** No algorithm, no matter how sophisticated, can recover the quantization error e(n) = x(n) − xq(n) because it was never stored. All other steps can, in principle, be perfectly inverted.

---

# SECTION 11 — Advanced / Bonus Questions

---

### Q37 (B) — Doubling Sampling Rate: What Changes?
If you double Fₛ while keeping B fixed, what changes and what stays the same?

**Solution:**

| Quantity | Effect of doubling Fₛ |
|---|---|
| **Time resolution** | Doubles — samples are now T/2 seconds apart instead of T |
| **Frequency range** | Doubles — can now represent up to Fₛ (new) / 2 without aliasing |
| **Normalized frequency f** of a given tone F | Halves: f_new = F/(2Fₛ) = f_old/2 |
| **Amplitude resolution (Δ)** | **Unchanged** — Δ = (xₘₐₓ − xₘᵢₙ)/2^B depends only on B and signal range |
| **Quantization error bound** | **Unchanged** — still |e[n]| ≤ Δ/2 |
| **Bit rate** | Doubles — 2Fₛ samples/s × B bits/sample = 2 × original |
| **Data storage per second** | Doubles |

**Key insight:** Sampling rate and bit depth are **orthogonal** design parameters. Fₛ controls time/frequency resolution; B controls amplitude resolution. Doubling Fₛ has zero effect on quantization noise.

---

### Q38 (B) — f = 3/8 and f = 5/8 Same Period
Show that f = 3/8 and f = 5/8 have the same discrete period, and explain why using 2π-periodicity.

**Solution:**

**(a) Period for f = 3/8:**
$$\omega_1 = 2\pi \times \frac{3}{8} = \frac{3\pi}{4}, \quad N_1 = \frac{2\pi m}{\omega_1} = \frac{2\pi m}{3\pi/4} = \frac{8m}{3}$$
Smallest integer: m = 3 → **N₁ = 8**

**(b) Period for f = 5/8:**
$$\omega_2 = 2\pi \times \frac{5}{8} = \frac{5\pi}{4}, \quad N_2 = \frac{2\pi m}{\omega_2} = \frac{2\pi m}{5\pi/4} = \frac{8m}{5}$$
Smallest integer: m = 5 → **N₂ = 8**

Both have **N = 8 samples**.

**(c) Why? Using 2π-periodicity:**
$$\cos\!\left(\frac{5\pi}{4}\,n\right) = \cos\!\left(\frac{5\pi}{4}\,n - 2\pi n\right) = \cos\!\left(\left(\frac{5\pi}{4} - 2\pi\right)n\right) = \cos\!\left(-\frac{3\pi}{4}\,n\right) = \cos\!\left(\frac{3\pi}{4}\,n\right)$$

f = 5/8 and f = 3/8 are **aliases** of each other in discrete time. They produce the same signal because 5/8 = 1 − 3/8, and frequencies that sum to 1 (or equivalently, whose ω values sum to 2π) are mirror images in discrete frequency.

---

### Q39 (B) — Infinite Energy but Finite Power
The energy of a CT sinusoid is infinite, but its power is A²/2. Why is this not contradictory?

**Solution:**

This is resolved by distinguishing **energy signals** from **power signals**:

**Energy** of a signal is defined as:
$$E = \int_{-\infty}^{\infty} |x(t)|^2\, dt$$

For a sinusoid: the integral over an infinite interval diverges → E = ∞

**Power** is the **time-averaged** energy rate:
$$P = \lim_{T \to \infty} \frac{1}{T} \int_{-T/2}^{T/2} |x(t)|^2\, dt = \frac{A^2}{2}$$

This is finite because the "infinite energy" grows at a **constant rate** (the signal keeps oscillating with the same amplitude forever). The average rate per unit time is well-defined and finite.

**Signal classification:**
- **Energy signal:** E < ∞, P = 0. Example: a pulse of finite duration.
- **Power signal:** E = ∞, 0 < P < ∞. Example: a sinusoid, a DC signal. All periodic signals are power signals.

A sinusoid is an ideal mathematical model that extends to ±∞ in time — in practice, real signals are always of finite duration and thus have finite energy.

---

### Q40 (B) — Integrator System Applied to a Sinusoid
y(t) = ∫_{−∞}^{t} x(τ)dτ. (a) Is output well-defined for x(t) = A cos(Ωt)? (b) Compute y(t) explicitly.

**Solution:**

**(a) Is the output well-defined?**

Formally:
$$y(t) = \int_{-\infty}^{t} A\cos(\Omega\tau)\, d\tau$$

This integral **diverges** if evaluated from −∞, because the cosine integrates to a sine, and adding up infinitely many oscillations without a decaying envelope does not converge.

However, as a **system** starting from some finite initial time t₀ (with initial conditions), it is well-defined:
$$y(t) = \int_{t_0}^{t} A\cos(\Omega\tau)\, d\tau + y(t_0)$$

In practice, the integrator system y(t) = H{x(t)} = ∫₋∞ᵗ x(τ)dτ is only well-defined for signals that are zero for t < some finite t₀, or for signals with a convergent integral.

**(b) Compute y(t) explicitly (from 0 to t, y(0) = 0):**
$$y(t) = \int_0^t A\cos(\Omega\tau + \theta)\, d\tau = \frac{A}{\Omega}\left[\sin(\Omega\tau + \theta)\right]_0^t$$

$$\boxed{y(t) = \frac{A}{\Omega}\left[\sin(\Omega t + \theta) - \sin(\theta)\right]}$$

The output is also a sinusoid (the integral of cosine is sine), with:
- **Same frequency Ω** (systems preserve frequency for sinusoidal inputs)
- **Amplitude scaled by 1/Ω** (integration attenuates higher frequencies)
- **Phase shifted by π/2** (sine lags cosine by 90°)
- **Plus a DC offset** −A sin(θ)/Ω from the initial condition

---

### Q67 (B) — Multi-Component Aliasing
Signal with 200 Hz and 800 Hz components, sampled at Fₛ = 1000 Hz. Full aliasing analysis.

**Solution:**

Nyquist limit = Fₛ/2 = 500 Hz.

**(a) Which components alias?**

- **200 Hz:** F = 200 < 500 Hz ✓ → No aliasing
- **800 Hz:** F = 800 > 500 Hz ✗ → Aliases!

Alias of 800 Hz: fₐₗᵢₐₛ = |800 − 1×1000| = 200 Hz

**(b) DT signals:**

For 200 Hz component (amplitude a):
$$x_1(n) = a\cos\!\left(2\pi \times \frac{200}{1000}\,n\right) = a\cos(0.4\pi\,n)$$

For 800 Hz component (amplitude a), aliased to 200 Hz:
$$x_2(n) = a\cos\!\left(2\pi \times \frac{800}{1000}\,n\right) = a\cos(1.6\pi\,n) = a\cos(1.6\pi n - 2\pi n) = a\cos(-0.4\pi n) = a\cos(0.4\pi n)$$

**(c) Is the original signal recoverable?**

**No.** Both the genuine 200 Hz component and the aliased 800 Hz component produce **identical DT signals** `a cos(0.4πn)`. In the sampled data, they are completely superimposed — their contributions cannot be separated. The original signal cannot be recovered because you cannot tell how much of the 0.4π component came from 200 Hz versus aliased 800 Hz.

This illustrates a critical point: aliasing does not just distort individual components — it causes **destructive interference** between real and aliased frequencies.

---

### Q68 (B) — Autocorrelation Function
ACF = (A²/2)cos(Ωτ). What does this tell you about the "memory" of a sinusoid?

**Solution:**

The **Autocorrelation Function (ACF)** of a signal measures how similar the signal is to a time-shifted version of itself:
$$R_{xx}(\tau) = \lim_{T\to\infty}\frac{1}{T}\int_0^T x(t)\,x(t+\tau)\,dt = \frac{A^2}{2}\cos(\Omega\tau)$$

**What this tells us:**

1. **Perfect memory:** The ACF never decays to zero — it is a cosine that oscillates indefinitely. This means a sinusoid is "infinitely correlated with itself" at any lag τ that is a multiple of its period. It has **perfect predictability** — knowing the past values completely determines future values.

2. **Periodic structure:** ACF = (A²/2)cos(Ωτ) has the same period as x(t). The signal "remembers" its own periodic structure at every lag.

3. **Only lag matters, not absolute time:** ACF depends only on τ (the lag), not on the absolute time t. This is the definition of a **wide-sense stationary (WSS)** signal — its statistics are time-invariant. Contrast with random signals, whose ACF typically decays.

4. **Power from ACF:** At τ = 0: R_xx(0) = A²/2 = **signal power** ✓ — consistent with our earlier derivation.

---

### Q69 (B) — Reversible vs Irreversible in Mobile Call Chain
In the 6-step mobile phone DSP chain, identify irreversible vs reversible steps.

**Solution:**

The 6-step chain:
1. Voice (analog) enters microphone
2. A/D: sampled at 8 kHz, 16-bit
3. Compressed using AMR codec
4. Transmitted as packets over 4G/5G
5. Decompressed at receiver
6. D/A: converted back to sound

| Step | Reversible? | Reason |
|---|---|---|
| **1. Microphone capture** | ✓ (approximately) | Transducer — captures analog waveform faithfully |
| **2a. Sampling (in ADC)** | ✓ Under Nyquist | 8 kHz > 2 × 4 kHz (voice bandwidth) → recoverable |
| **2b. Quantization (in ADC)** | ✗ **IRREVERSIBLE** | 16-bit rounding — quantization error e(n) is discarded |
| **3. AMR compression** | ✗ **IRREVERSIBLE** (lossy) | AMR is a lossy codec; perceptually unimportant components are discarded |
| **4. Packet transmission** | ✓ (with error correction) | Forward error correction recovers bit errors; lossless if no packet loss |
| **5. Decompression** | ✓ (given AMR data) | Decoder reverses compression steps exactly from the AMR bitstream |
| **6. DAC** | ✓ (approximately) | ZOH + low-pass filter reconstructs smooth analog waveform |

**Summary:** Two inherently irreversible steps — **quantization** (fundamental, always) and **AMR compression** (chosen/deliberate for bandwidth efficiency).

---

### Q70 (B) — Sampling a DT Sinusoid Again
x(n) = cos(ω₀n) is "sampled" at M samples per period. Express M in terms of ω₀ and show the aperiodicity condition. Find minimum integer M for ω₀ = 2π/5.

**Solution:**

**Expressing M in terms of ω₀:**

The period of x(n) = cos(ω₀n) (if it exists) is N₀ = 2π/ω₀ (assuming m = 1 case).

The number of samples per period would be:
$$M = N_0 = \frac{2\pi}{\omega_0}$$

**Condition for M to be a positive integer:**

$$M = \frac{2\pi}{\omega_0} \in \mathbb{Z}^+ \iff \omega_0 = \frac{2\pi}{M}$$

More generally (for m > 1): x(n) is periodic with period N = 2πm/ω₀. N is an integer iff ω₀/(2π) = m/N ∈ ℚ.

If ω₀/(2π) is irrational → N is never an integer → **x(n) is aperiodic**.

**For ω₀ = 2π/5:**
$$M = \frac{2\pi}{\omega_0} = \frac{2\pi}{2\pi/5} = 5$$

The minimum integer M = **5 samples per period**.

**Verification:** x(n) = cos(2πn/5)
- f = 1/5 ∈ ℚ ✓
- N = 5: x(n+5) = cos(2π(n+5)/5) = cos(2πn/5 + 2π) = cos(2πn/5) ✓

---

# QUICK REFERENCE: KEY FORMULAE

| Formula | Description |
|---|---|
| x(t) = A cos(Ωt + θ) | CT sinusoid general form |
| x(n) = A cos(ωn + φ) | DT sinusoid general form |
| Ω = 2πF, T₀ = 2π/Ω | CT frequency–period relations |
| ω = 2πf = 2πF/Fₛ = Ω/Fₛ | DT angular frequency |
| f = F/Fₛ ∈ (−½, ½] | Normalized frequency range |
| Periodic DT iff f ∈ ℚ | DT periodicity condition |
| N = 2πm/ω (smallest integer) | DT period formula |
| P = A²/2 | Power of CT sinusoid |
| fₛ ≥ 2fₘₐₓ | Nyquist–Shannon theorem |
| fₐₗᵢₐₛ = \|F − kFₛ\| | Alias frequency formula |
| e(n) = x(n) − xq(n) | Quantization error |
| Levels = 2^b | Quantization levels from b bits |
| Bit rate = fₛ × b | Data rate of digital signal |
| t = n/Fₛ = n·Tₛ | Sample index to time conversion |
| ACF = (A²/2)cos(Ωτ) | Autocorrelation of CT sinusoid |

---

*End of Document — 70 Questions with Full Solutions*
*CSE 4631 · Syem Aziz · Prepared from Chapter 1, Chapter 2-Part 1, Chapter 2-Part 2*
