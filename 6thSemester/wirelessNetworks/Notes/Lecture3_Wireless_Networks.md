# Lecture 3: Enhancing Insight into Wireless Transmission Fundamentals

> **Course:** CSE 4615 — Wireless Networks (IUT)
> **Scope:** Answers to **every** numbered item — all **Exercises (§4.1–4.7, E1–E26)** *and* all **Sample Questions (§5.1–5.4, S1–S30)** — with full depth and every numerical worked, plus a conceptual deep-dive, exam pointers, common mistakes, tricks, and a complete formula sheet. Verified against the lecture slides (transmitter-chain 300→600→900 MHz example; bandwidth 100–1000 Hz / 90% energy 300–700 Hz example).

---

## 1. Lecture Overview

This is the **physical-layer** lecture: how bits become **electromagnetic signals** and travel through the air. Four big ideas:

1. **Antennas & the transmitter chain** — how a low-frequency source is amplified, **up-converted (mixed)**, filtered, and radiated. Antenna types: **omnidirectional vs directional** (and multi-element arrays).
2. **Two views of a signal** — **time domain** (analog/digital, periodic/aperiodic, and the five sine parameters: amplitude, frequency, period, phase, wavelength) and **frequency domain** (spectrum, fundamental frequency, **absolute vs effective bandwidth**, bandwidth ↔ data rate).
3. **Modulation** — placing data on a carrier: **analog (AM/FM/PM)** and **digital (ASK/FSK/PSK, QAM/QPSK)**; plus channel-combating tools (error coding, **AMC**, equalization). Each scheme changes **one carrier parameter**.
4. **Multiplexing & multiple access** — sharing the medium across **space/time/frequency/code** (FDM/TDM/CDM ↔ SDMA/TDMA/FDMA/CDMA), and **cognitive radio** for opportunistic spectrum reuse.

Two relationships anchor the numerics: **λ = c/f** (wavelength ↔ frequency, antenna size) and **bandwidth ≈ capacity** (more bandwidth ⇒ higher rate, at a cost). **Modulation ≠ multiplexing** is the conceptual line you must never blur.

---

## 2. Suggestion Questions and Answers

> **Part A — Exercises (E1–E26).**  **Part B — Sample Questions (S1–S30).**

### — Part A: EXERCISES —

#### 4.1 Antennas and the Transmitter Chain

### E1 — Draw & label the transmitter chain; function of each stage.
**Answer:** Chain: **Source → Amplifier → Oscillator → Mixer → Filter → Amplifier → Antenna.**
- **Source:** generates the baseband/low-frequency signal.
- **Amplifier (1st):** strengthens the initial signal.
- **Oscillator:** creates a stable **carrier wave** at the needed frequency.
- **Mixer:** **combines** signal + oscillator → produces **sum & difference** frequencies (up-conversion to the carrier).
- **Filter:** **selects the correct frequency**, rejecting unwanted mixer products/images.
- **Amplifier (2nd / power amp):** strengthens before transmission.
- **Antenna:** radiates the EM wave.
*Slide example:* 300 MHz source + **600 MHz oscillator** → **900 MHz** output; filter keeps 900 MHz.

### E2 — Source 200 MHz, transmit at 1.8 GHz: oscillator frequency & mixer role.
**Answer:** Required **oscillator = 1800 − 200 = 1600 MHz**. The **mixer** multiplies source (200 MHz) and oscillator (1600 MHz), producing the **sum (1.8 GHz)** and **difference (1.4 GHz)**. We want the **1.8 GHz sum**, so a **filter** afterward **passes 1.8 GHz** and **rejects** the 1.4 GHz difference and images.

### E3 — Multi-element antenna array + one advantage.
**Answer:** A **multi-element (array) antenna** uses several radiating elements whose signals combine. **Advantage:** it can **shape/steer the beam (beamforming)** and provide **diversity/gain** — focusing energy in a chosen direction → **better SINR/range** and interference rejection vs a single antenna.

### E4 — Omnidirectional vs directional antennas + an application each.
**Answer:**
- **Omnidirectional:** radiates **equally in all horizontal directions**. *Application:* Wi-Fi AP / broadcast where clients are all around.
- **Directional:** concentrates energy in a **specific direction** (higher gain/range). *Application:* point-to-point backhaul, satellite dish, long-range links.

#### 4.2 Time-Domain Signal Concepts

### E5 — Define & give SI units: peak amplitude, frequency, period, phase, wavelength.
**Answer:**
- **Peak amplitude (A):** max signal strength — **volts (V)**.
- **Frequency (f):** cycles per second — **hertz (Hz)**.
- **Period (T):** time for one cycle — **seconds (s)**; T = 1/f.
- **Phase (φ):** position in the cycle / time offset — **radians or degrees**.
- **Wavelength (λ):** distance of one cycle — **metres (m)**; λ = c/f.

### E6 — Periodic vs aperiodic signal + a wireless example each.
**Answer:** **Periodic:** repeats every period, **s(t + T) = s(t)** — e.g., a **carrier sine wave**. **Aperiodic:** no repetition — e.g., a **data/voice waveform** (random information). In wireless, the **carrier** is periodic; the **modulated information signal** is aperiodic.

### E7 — Signal f = 500 Hz: period and wavelength in air.
**Answer:** **T = 1/f = 1/500 = 2 ms.** **λ = c/f = 3×10⁸ / 500 = 600,000 m = 600 km.** (Very long wavelength → impractically large antenna — why such low frequencies aren't used for compact wireless.)

#### 4.3 Frequency-Domain Concepts and Bandwidth

### E8 — Signal 200–2000 Hz; 85% energy in 500–1200 Hz.
**Answer:** **Absolute bandwidth = 2000 − 200 = 1800 Hz.** **Effective bandwidth = 1200 − 500 = 700 Hz.** (Effective uses the **energy-band edges**, not a fraction of absolute.)

### E9 — Trade-off "more bandwidth ⇒ higher rate, but at a cost"; two wireless costs.
**Answer:** More bandwidth raises capacity (Shannon: capacity grows with bandwidth). **Two wireless-specific costs:** (1) **spectrum scarcity/licensing cost** — bandwidth is regulated and expensive; (2) **more noise/interference captured** (and higher power/complexity needed), since a wider band integrates more noise and is harder to keep clean.

### E10 — Compare 4G LTE (~20 MHz) vs 5G mmWave (≥400 MHz).
**Answer:** **5G mmWave** has **~20× the bandwidth**, so far **higher data-rate potential**. **Practical challenges of mmWave:** severe **path loss**, **easy blockage** (walls, body, rain), **short range**, needing **dense small cells + beamforming**. **LTE's 20 MHz** gives lower peak rate but **better range/penetration** and simpler deployment.

#### 4.4 Frequency Spectrum and Regulation

### E11 — Wavelength at 2.4 GHz (Wi-Fi) and 28 GHz (5G mmWave).
**Answer:** **λ = c/f.** At **2.4 GHz:** 3×10⁸/2.4×10⁹ = **0.125 m (12.5 cm)**. At **28 GHz:** 3×10⁸/28×10⁹ = **≈0.0107 m (1.07 cm)**. (Higher frequency → much shorter wavelength → tiny antennas, but worse propagation.)

### E12 — What are ISM bands? Three technologies + frequency range.
**Answer:** **ISM (Industrial, Scientific, Medical)** bands are **unlicensed** spectrum for free use under power rules. **Examples:** **Wi-Fi (2.4 GHz & 5 GHz), Bluetooth (2.4 GHz), Zigbee/IoT (2.4 GHz, sub-GHz 868/915 MHz)**. Common ISM bands: **2.400–2.4835 GHz** and **5 GHz**.

### E13 — Why VHF/UHF for mobile radio but SHF for satellite links?
**Answer:** **VHF/UHF (30 MHz–3 GHz)** propagate well over terrain — they **diffract around obstacles, penetrate buildings, and travel far**, ideal for **mobile** users on the move. **SHF (3–30 GHz)** offers **huge bandwidth** and supports **highly directional dish antennas** with **line-of-sight** to satellites (atmospheric/space path is clear), making it ideal for **high-capacity satellite/point-to-point** links where mobility/penetration isn't the priority.

#### 4.5 Modulation

### E14 — Sketch ASK/FSK/PSK for bits 1 0 1; which carrier parameter changes.
**Answer:**
- **ASK:** carrier **amplitude** changes (e.g., 1 = high/on, 0 = low/off). *Parameter: amplitude.*
- **FSK:** carrier **frequency** changes (1 = f₁, 0 = f₂). *Parameter: frequency.*
- **PSK:** carrier **phase** changes (1 = 0°, 0 = 180°). *Parameter: phase.*
*(Sketch: same carrier, with amplitude/frequency/phase switching at each bit boundary for 1-0-1.)*

### E15 — Compare ASK/FSK/PSK (bandwidth, interference, complexity).
**Answer:**

| Scheme | Bandwidth need | Robustness to interference | Complexity |
|---|---|---|---|
| **ASK** | low | **poor** (amplitude noise-prone) | **simple** |
| **FSK** | **high** (two+ frequencies) | **good** (amplitude-independent) | moderate |
| **PSK** | moderate | **best** (info in phase) | higher (coherent detection) |

### E16 — Analog vs digital modulation + two examples each.
**Answer:** **Analog modulation** varies the carrier continuously with an **analog message**: **AM** (AM radio), **FM** (FM radio), **PM**. **Digital modulation** maps **digital bits** to carrier states: **ASK, FSK, PSK** (and **QAM/QPSK**) — used in **Wi-Fi, LTE/5G, Bluetooth**. *Two examples:* analog → **AM/FM broadcast**; digital → **Wi-Fi (QAM), Bluetooth (FSK)**.

### E17 — Draw & label the full modulation/demodulation chain.
**Answer:** *Transmitter:* **digital data → modulator (maps bits to carrier states) → up-conversion/amplifier → antenna.** *Channel:* adds noise/fading. *Receiver:* **antenna → filter/amplifier → down-conversion → demodulator (recovers bits from carrier states) → digital data**, often with **equalization + error decoding** to clean channel effects. The demodulator reverses exactly what the modulator did.

### E18 — What is AMC? Scenario for switching higher→lower order.
**Answer:** **Adaptive Modulation and Coding (AMC)** dynamically **chooses modulation order + coding rate based on channel quality (SNR/SINR)**. **Scenario:** a mobile user **moves away from the AP**, SNR drops; the system **switches from 64-QAM (high order, high rate) down to QPSK/BPSK (low order, robust)** with stronger coding to **keep BER acceptable** — trading rate for reliability.

#### 4.6 Multiplexing and Multiple Access

### E19 — Four multiplexing dimensions; access scheme + a system each.
**Answer:**

| Dimension | Access scheme | Example system |
|---|---|---|
| **Space** | SDMA | cellular frequency reuse / MIMO beams |
| **Time** | TDMA | GSM |
| **Frequency** | FDMA | 1G/analog cellular, FM channels |
| **Code** | CDMA | 3G (W-CDMA/CDMA2000) |

### E20 — Compare FDM vs TDM (assignment, sync, analog suitability, guards).
**Answer:**

| Attribute | FDM | TDM |
|---|---|---|
| Channel assignment | **frequency band** per user (all simultaneous) | **time slot** per user (one at a time) |
| Synchronization | **loose** (no tight timing) | **strict** slot timing |
| Analog suitability | **good** for analog | naturally **digital** |
| Guard requirement | **guard bands** (frequency) | **guard times** (timing) |

### E21 — Complete FDM/TDM/CDM comparison (≥5 attributes).
**Answer:**

| Attribute | FDM | TDM | CDM |
|---|---|---|---|
| Divides by | frequency | time | **code** (shared time+freq) |
| Simultaneity | all channels at once | one at a time | all at once (codes) |
| Synchronization | loose | strict timing | code/power control |
| Guard needed | guard **bands** | guard **times** | none (codes) |
| Analog support | yes | digital | digital |
| Interference resistance | low (narrowband) | moderate | **high** (spread spectrum) |
| Per-user rate | fixed band | full band in slot | **lower** per user |

### E22 — Why cost per kbps falls as facility data rate rises.
**Answer:** A **high-capacity link** has large **fixed costs** (equipment, deployment) spread over **many more bits/second**, so the **cost per kbps drops** (economies of scale). Since each device needs only a **modest data rate**, **multiplexing many users onto one fast facility** is far cheaper than giving each a dedicated low-rate link.

#### 4.7 Cognitive Radio

### E23 — Define cognitive radio; what problem it solves.
**Answer:** **Cognitive radio** is a smart radio that **senses the spectrum and dynamically uses idle frequencies ("white spaces")** without harming licensed users. **Problem solved:** **spectrum scarcity/underutilization** — much licensed spectrum sits idle in time/space, and CR lets **secondary users** opportunistically exploit it.

### E24 — Primary (PU) vs secondary (SU) users.
**Answer:** **Primary users (PU):** licensed owners with **priority** access to a band. **Secondary users (SU):** **unlicensed opportunists** that may use the band **only when the PU is idle**, and **must vacate immediately** when the PU returns.

### E25 — Two real spectrum white-space examples CR can exploit.
**Answer:** (1) **TV white spaces** — unused VHF/UHF TV channels in a given area; (2) **idle cellular/licensed bands** at certain times/locations (e.g., a rural licensed band rarely used). CR senses these vacancies and uses them for **IoT/broadband**.

### E26 — How cognitive radio relates to time/frequency/space multiplexing.
**Answer:** CR is **opportunistic multiplexing across all three dimensions**: it reuses a band in **frequency** (a vacant channel), in **time** (when the PU is idle), and in **space** (where the PU's signal is absent). Effectively it adds a **dynamic, sensing-driven layer** on top of fixed multiplexing.

### — Part B: SAMPLE QUESTIONS —

#### 5.1 Short Questions

### S1 — Define an antenna; function in Tx and Rx.
**Answer:** A transducer between **guided signals and free-space EM waves.** **Tx:** converts electrical signal → radiated EM wave. **Rx:** captures the EM wave → electrical signal.

### S2 — Peak amplitude; SI unit.
**Answer:** Maximum signal strength of the waveform (∝ energy/power); SI unit **volts (V)**.

### S3 — Period vs frequency relationship.
**Answer:** Reciprocal: **T = 1/f** (f = 1/T). Period in s, frequency in Hz.

### S4 — Define wavelength; formula vs frequency.
**Answer:** Physical length of one cycle; **λ = c/f** (c ≈ 3×10⁸ m/s). Higher f → shorter λ → smaller antenna.

### S5 — Fundamental frequency.
**Answer:** The **lowest frequency component** of a periodic signal; all others are **harmonics** (integer multiples). Equals **1/T**.

### S6 — Absolute vs effective bandwidth.
**Answer:** **Absolute** = full spectral width (max − min frequency present). **Effective** = band holding **most (e.g., 85–90%) of the energy**. Effective ≤ absolute.

### S7 — Four modulation types in the lecture.
**Answer:** **AM, FM, PM** (analog) and the **digital shift-keying** family **ASK/FSK/PSK** (+ QAM/QPSK). Carrier parameters changed: amplitude, frequency, phase (+ amplitude/phase for QAM).

### S8 — What is ASK? One disadvantage.
**Answer:** **Amplitude Shift Keying** — data via **carrier amplitude** changes. **Disadvantage:** very **noise/fading-sensitive** (noise corrupts amplitude directly).

### S9 — What is PSK? One advantage over ASK.
**Answer:** **Phase Shift Keying** — data via **carrier phase**. **Advantage:** **more robust to amplitude noise/fading** → lower BER at the same SNR.

### S10 — Modulation vs multiplexing (one sentence each).
**Answer:** **Modulation** transforms one data signal onto a carrier for transmission. **Multiplexing** shares one medium among **multiple signals** (space/time/frequency/code).

### S11 — ISM band; one technology.
**Answer:** **Unlicensed Industrial/Scientific/Medical** spectrum usable without a license (e.g., 2.4 GHz). **Example:** Wi-Fi (also Bluetooth, Zigbee).

### S12 — Define cognitive radio (two sentences).
**Answer:** A radio that **senses spectrum and dynamically uses idle channels** without disturbing licensed users. It lets **secondary users** transmit when **primary users** are inactive, then vacates when the PU returns.

### S13 — Two FDM advantages and two TDM advantages.
**Answer:** **FDM:** no tight time sync; works for **analog**; continuous transmission. **TDM:** one carrier at a time (simpler RF); **high throughput / flexible**; digital-friendly.

### S14 — Purpose of a guard space in FDM.
**Answer:** Unused spectrum **between channels** to **prevent adjacent-channel interference** from spectral leakage/imperfect filters; costs some bandwidth.

### S15 — Two reasons for widespread multiplexing.
**Answer:** (1) **Cost per kbps falls** as facility rate rises (economies of scale). (2) **Per-device data needs are modest**, so many users share one high-capacity link efficiently.

#### 5.2 Descriptive Questions

### S16 — Complete transmitter chain (role of each component).
**Answer:** **Source → Amplifier → Oscillator → Mixer → Filter → Amplifier → Antenna.** Source makes the baseband signal; amplifier strengthens it; **oscillator** makes the carrier; **mixer** up-converts (sum/difference); **filter** selects the wanted frequency; power amplifier boosts; antenna radiates. *(300 MHz + 600 MHz osc → 900 MHz.)*

### S17 — Frequency-domain view: spectrum, fundamental freq, absolute & effective BW (with example).
**Answer:** Any signal = sum of sinusoids; the **spectrum** is its set of frequency components; **fundamental** = lowest (with **harmonics** above). **Absolute BW** = full width; **effective BW** = energy band. *Example (slide):* **100–1000 Hz → absolute = 900 Hz**; **90% energy 300–700 Hz → effective = 400 Hz.**

### S18 — EM spectrum in telecom (bands + ranges + a technology each).
**Answer:**

| Band | Range | Technology |
|---|---|---|
| VLF/LF | 3–300 kHz | navigation, longwave |
| MF | 300 kHz–3 MHz | **AM radio** |
| HF | 3–30 MHz | shortwave |
| VHF | 30–300 MHz | **FM radio, TV** |
| UHF | 300 MHz–3 GHz | **cellular, Wi-Fi 2.4 GHz, Bluetooth** |
| SHF | 3–30 GHz | **satellite, radar, 5 GHz Wi-Fi** |
| EHF | 30–300 GHz | **5G mmWave (28 GHz)** |

*Rule:* lower bands → longer range/penetration; higher bands → more bandwidth, shorter range.

### S19 — Compare analog (AM/FM/PM) vs digital (ASK/FSK/PSK): parameter varied + use case.
**Answer:**

| Scheme | Type | Parameter varied | Use case |
|---|---|---|---|
| AM | analog | amplitude | AM broadcast |
| FM | analog | frequency | FM radio |
| PM | analog | phase | legacy/analog data |
| ASK | digital | amplitude | simple/optical |
| FSK | digital | frequency | Bluetooth, robust low-rate |
| PSK | digital | phase | Wi-Fi/cellular |
| QAM/QPSK | digital | amplitude + phase | high-rate Wi-Fi/LTE |

### S20 — Four multiplexing dimensions (diagrams) + access scheme + system each.
**Answer:** **Space → SDMA** (cellular reuse/MIMO); **Time → TDMA** (GSM); **Frequency → FDMA** (analog cellular/FM); **Code → CDMA** (3G). *(Diagram-in-words: SDMA = separate locations; TDMA = time slots stacked; FDMA = frequency bands stacked; CDMA = overlapping signals separated by codes.)*

### S21 — Compare FDM vs TDM in detail (principle, pros/cons, guards, traffic).
**Answer:** **FDM** assigns each user a **frequency band**, all transmitting simultaneously; needs **guard bands**; loose sync; good for **continuous/analog** traffic; wastes idle bands. **TDM** assigns **time slots**, one user at a time on the full band; needs **strict timing + guard times**; digital-friendly; good for **bursty digital** traffic; wastes idle slots. *Trade-off:* FDM = continuous-but-rigid spectrum; TDM = flexible-but-sync-heavy timing.

### S22 — Bandwidth ↔ data rate; asset and constraint.
**Answer:** **More bandwidth ⇒ higher capacity/data rate** → bandwidth is an **asset**. But it is **scarce, regulated, expensive**, and wider bands **collect more noise/interference** and need more power/complexity → a **constraint**. Hence designers maximize **spectral efficiency** (modulation/coding/multiplexing).

#### 5.3 Numerical Problems

### S23 — Signal 400–2400 MHz; 90% energy 800–1800 MHz.
**Answer:**
- **Absolute BW = 2400 − 400 = 2000 MHz.**
- **Effective BW = 1800 − 800 = 1000 MHz.**
- **λ at 400 MHz = 3×10⁸/400×10⁶ = 0.75 m.**
- **λ at 2400 MHz = 3×10⁸/2.4×10⁹ = 0.125 m.**

### S24 — Produce 1.9 GHz from a 400 MHz source.
**Answer:** **Oscillator = 1900 − 400 = 1500 MHz.** **Mixer** multiplies → **sum 1.9 GHz** and **difference 1.1 GHz**. **Filter** is needed to **pass 1.9 GHz** and **reject the 1.1 GHz difference / images**.

### S25 — LTE FDM, 200 kHz channels in 20 MHz.
**Answer:**
- **Ignoring guards:** 20 MHz / 200 kHz = **100 channels.**
- **With 100 kHz guards:** N·200 + (N−1)·100 ≤ 20000 ⇒ 300N ≤ 20100 ⇒ **N ≈ 66–67 channels.**
- **Why guard bands:** real filters aren't ideal → guards **prevent adjacent-channel interference** from spectral leakage.

### S26 — TDMA, 8 slots/frame, frame = 4.6 ms.
**Answer:**
- **Slot duration = 4.6 ms / 8 = 0.575 ms.**
- **Users per frequency channel = 8** (one per slot).
- **Sync challenge:** all stations must align to **slot boundaries**; clock drift/propagation delay need **guard times** + tight timing (overhead).

### S27 — Cognitive radio: PU idle on 5 MHz at 850 MHz; SU for IoT.
**Answer:**
- **Multiplexing type:** opportunistic **frequency (and time) multiplexing** — using a vacant band while idle.
- **If PU returns:** SU **must vacate immediately** and find another white space (PU has priority).
- **λ at 850 MHz = 3×10⁸/850×10⁶ ≈ 0.353 m (35.3 cm).**

#### 5.4 Higher-Level and Design Questions

### S28 — Choose FDMA/TDMA/CDMA for dense urban, 500 users/cell.
**Answer:** **Recommend CDMA.** All users share the **same wideband frequency** via **unique codes** → **universal frequency reuse, soft capacity** (graceful degradation as users grow), **soft handoff**, and **robustness to multipath**. **Trade-offs:** needs **tight power control** (near-far problem) and more processing. (FDMA wastes spectrum on guard bands; TDMA's rigid slots + strict sync scale less gracefully to 500 simultaneous users.)

### S29 — Wi-Fi 2.4 GHz vs 5G mmWave 28 GHz (wavelength, propagation, bandwidth, deployment).
**Answer:**

| | 2.4 GHz Wi-Fi | 28 GHz mmWave |
|---|---|---|
| **λ = c/f** | 12.5 cm | ≈1.07 cm |
| **Propagation** | penetrates/diffracts, longer range | high loss, easily blocked, short range, near-LOS |
| **Bandwidth** | limited/crowded | **very large** (high rate) |
| **Deployment** | indoor/wide coverage | **dense small cells**, LOS urban hotspots |

### S30 — Cognitive radio for TV white space reuse: requirements + role of sensing.
**Answer:** For an SU to avoid harming PUs it must: **reliably detect PU presence** (sensitive **spectrum sensing**), **vacate quickly** when the PU appears, **limit transmit power**, and possibly consult a **geolocation database**. **Spectrum sensing** is the enabler — it continuously checks whether the TV channel is **vacant**, allowing safe opportunistic use and immediate evacuation, ensuring **non-interference** with licensed broadcasts.

---

## 3. Conceptual Deep Dive

**The transmitter chain is a frequency journey.** *Make it (source) → make it strong (amp) → pick a carrier (oscillator) → shift it up (mixer) → clean it (filter) → shout it (power amp → antenna).* The **mixer is a frequency adder/subtracter**: multiplying two sinusoids yields **sum & difference**; the **filter keeps the wanted one**. So **oscillator = target − source** (sum mixing).

**Two views, one signal.** Time domain shows *amplitude over time* (the five sine parameters). Frequency domain shows *which frequencies are present* (spectrum, fundamental, harmonics, bandwidth). The **frequency-domain view defines bandwidth**, which links directly to **data rate**.

**Absolute vs effective bandwidth.** Absolute = "everything present" (max − min). Effective = "where the energy actually is" (the 85–90% band). They give **different numbers** in every problem — compute both.

**Modulation vs multiplexing — never blur this.** **Modulation** transforms *one* signal onto a carrier (changes **one carrier knob**: A=AM/ASK, F=FM/FSK, P=PM/PSK; QAM = A+P). **Multiplexing** *shares the medium* among *many* signals across **Space/Time/Frequency/Code → SDMA/TDMA/FDMA/CDMA**.

**Cognitive radio = polite spectrum borrowing.** Sense → use white space → leave when the owner (PU) returns. It's a sensing-driven, opportunistic overlay on fixed multiplexing across time/frequency/space.

**Where students get confused.** Computing effective bandwidth as a *percentage of absolute* (wrong — use the energy-band edges); adding instead of subtracting for the oscillator; thinking FSK is bandwidth-cheap (it's the widest); forgetting the **filter** after the mixer; and blurring **modulation with multiplexing**.

---

## 4. Important Exam Pointers
- **λ = c/f is guaranteed.** Memorize 2.4 GHz→12.5 cm, 850 MHz→~35 cm, 28 GHz→~1.07 cm. Keep units consistent.
- **Absolute vs effective BW:** absolute = full span; effective = **energy-band edges** — compute **both**.
- **"Which carrier parameter changes?"** ASK→amplitude, FSK→frequency, PSK→phase, QAM→amplitude+phase.
- **FDM vs TDM** and **FDM/TDM/CDM** tables are high-frequency items — include sync/guard/analog rows.
- **Mixer math:** oscillator = output − source; explain the **filter's job** (reject difference/image).
- **Define modulation vs multiplexing crisply** — a favourite one-mark trap.
- **Dimension↔access mapping must be exact** (Space↔SDMA, Time↔TDMA, Frequency↔FDMA, Code↔CDMA).

## 5. Commonly Forgotten Points
- **Effective BW uses energy-band edges**, not a % of absolute. (700−500 = 200, not 0.85×span.)
- **Oscillator = output − source** (sum mixing); don't forget the **filter**.
- **FSK needs MORE bandwidth** than ASK/PSK (multiple frequencies).
- **PSK > ASK** in robustness (phase, not noise-prone amplitude).
- **CDMA = same time AND frequency**, separated only by **code**.
- **Guard *band* (FDM/frequency) vs guard *time* (TDM/timing).**
- **Higher frequency → shorter λ → smaller antenna but worse range/penetration.**
- **In CR, the SU yields to the PU instantly.**

## 6. Tips and Tricks
- **λ shortcut:** `λ(cm) ≈ 30/f(GHz)` → 2.4 GHz=12.5 cm, 28 GHz≈1.07 cm, 0.85 GHz≈35 cm.
- **Modulation "A-F-P":** ASK/AM=Amplitude, FSK/FM=Frequency, PSK/PM=Phase; QAM = A+P.
- **Mixer rule:** *Oscillator = Target − Source*; filter discards the difference.
- **Bandwidth:** *Absolute is Always wider; Effective is the Energy band.*
- **Dimensions↔access "S-T-F-C":** Space→SDMA, Time→TDMA, Frequency→FDMA, Code→CDMA.
- **FDM vs TDM:** *FDM splits the dial (guard bands); TDM splits the clock (guard times).*

## 7. Formula Cheat Sheet

### Signal & wave
| Formula | Variables | Use |
|---|---|---|
| `T = 1/f` | T(s), f(Hz) | period ↔ frequency |
| `λ = c/f` | λ(m), c=3×10⁸, f(Hz) | wavelength, antenna size |
| `λ(cm) ≈ 30/f(GHz)` | quick λ | mental GHz wavelengths |
| `s(t+T) = s(t)` | — | periodicity condition |

### Bandwidth
| Formula | Use |
|---|---|
| `Absolute BW = f_high − f_low` | total spectral width |
| `Effective BW = f_hi(energy) − f_lo(energy)` | energy band width |
| `Capacity ∝ Bandwidth` (qualitative) | bandwidth–rate trade-off |

### Transmitter / mixing
| Relationship | Use |
|---|---|
| `f_out = f_source ± f_oscillator` | mixer sum/difference |
| `f_oscillator = f_out − f_source` | required local oscillator (sum) |

### Multiplexing ↔ access
| Dimension | Access | Divides by |
|---|---|---|
| Space | SDMA | location/beam |
| Time | TDMA | time slot |
| Frequency | FDMA | frequency band |
| Code | CDMA | spreading code |

### TDMA timing (numerical)
| Formula | Use |
|---|---|
| `slot = frame duration / number of slots` | per-slot time |
| `users per channel = number of slots` | TDMA capacity per band |

> **Constants:** c ≈ 3×10⁸ m/s. **λ landmarks:** 2.4 GHz→12.5 cm, 850 MHz→~35 cm, 28 GHz→~1.07 cm.
