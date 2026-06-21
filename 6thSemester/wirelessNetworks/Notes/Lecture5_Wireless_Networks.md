# Lecture 5: IEEE 802.11 WLANs

> **Course:** CSE 4615 — Wireless Networks (IUT)
> **Scope:** Answers to **every** numbered item — all **Exercises (§4.1–4.7, E1–E33)** *and* all **Sample Questions (§5.1–5.3, S1–S27)** — in full depth with every numerical worked, plus a conceptual deep-dive, exam pointers, common mistakes, tricks, and a complete formula sheet. **802.11a values used throughout (from the slides): aSlotTime = 9 µs, SIFS = 16 µs, PIFS = 25 µs, DIFS = 34 µs, EIFS ≈ 200 µs, CCA threshold = −82 dBm, CWmin = 16, CWmax = 1024.**

---

## 1. Lecture Overview

Lecture 5 turns the MAC principles of Lecture 4 into the **concrete IEEE 802.11 (Wi-Fi) standard**. It covers four layers:

1. **Architecture & standards.** The building blocks — **station, BSS, IBSS, AP, Distribution System (DS), portal, ESS** — and the two coordination functions: **DCF** (mandatory, contention-based, no priority) and **PCF** (optional, polling-based, QoS/priority).
2. **Carrier sensing — physical + virtual.** **CCA (Clear Channel Assessment)** measures channel energy against the **−82 dBm** threshold; **NAV (Network Allocation Vector)** is *virtual* carrier sense set by the **duration field** of RTS/CTS. A station transmits only if **both** say "idle."
3. **Timing — the four interframe spaces.** **SIFS < PIFS < DIFS < EIFS**, with **PIFS = SIFS + aSlotTime** and **DIFS = SIFS + 2·aSlotTime**. Shorter IFS ⇒ higher priority — this is how ACKs/CTS jump the queue.
4. **DCF mechanics.** **CSMA/CA + ACK (ARQ)**, **Binary Exponential Backoff (BEB)** with the contention window, the three **MSDU delivery scenarios**, **RTS/CTS** and the hidden-station fix via NAV, and finally **DCF overhead (~35% at 54 Mbps)** and its **three inefficiencies**.

The throughline: 802.11 is **Lecture 4's CSMA/CA made precise** — exact timers, an exact backoff rule, and an exact reservation handshake, all engineered around the fact that **collisions happen at the receiver** and the medium must be shared **fairly** and **reliably** over an unreliable channel.

---

## 2. Suggestion Questions and Answers

> **Part A — Exercises (E1–E33).**  **Part B — Sample Questions (S1–S27).**

### — Part A: EXERCISES —

#### 4.1 Architecture and Standards

### E1 — 802.11 architecture: define BSS, IBSS, DS, portal; how BSSs form an ESS.
**Answer:** *(Diagram in words: two APs, each with stations, both connected by a Distribution System; one isolated peer group.)*
- **BSS (Basic Service Set):** the basic 802.11 cell — a set of stations controlled by **one AP** (infrastructure mode).
- **IBSS (Independent BSS):** an **ad-hoc** BSS with **no AP** — stations talk peer-to-peer.
- **DS (Distribution System):** the **backbone** (often wired) interconnecting multiple APs/BSSs so frames move between them.
- **Portal:** the **bridge** between the 802.11 network and a **non-802.11 (e.g., wired Ethernet) LAN**.
- **ESS (Extended Service Set):** **multiple BSSs joined by a DS**, appearing as **one logical network (same SSID)**, enabling **roaming/handoff** between APs.

### E2 — Compare DCF and PCF (traffic, priority, coordination, mandatory/optional).
**Answer:**

| Attribute | DCF | PCF |
|---|---|---|
| Traffic type | best-effort / asynchronous | time-bounded / real-time (QoS) |
| Priority | **none** (equal contention) | **prioritized** (polled) |
| Coordination | **distributed** (CSMA/CA + backoff) | **centralized** (AP polls stations) |
| Mandatory? | **Mandatory** | **Optional** |
| Built on | contention | contention-free polling (on top of DCF) |

### E3 — Minimum stations to form an IBSS? Justify.
**Answer:** **Two (2).** An IBSS is a peer-to-peer ad-hoc set with **no AP**; communication requires at least **one sender and one receiver**, so **two stations** are the minimum to have a functioning IBSS. One station alone has no peer to communicate with.

### E4 — Why CSMA/CD (wired Ethernet) can't be used in 802.11.
**Answer:** Because wireless has **no fate sharing** and **half-duplex radios**: a station's **own transmission (~10⁶× stronger)** deafens its receiver, so it **can't listen while transmitting** to detect a collision. Add the **hidden terminal problem** (collision occurs at the receiver, invisible to the sender) and **fading** (silence isn't reliable), and **collision detection is infeasible**. 802.11 therefore **avoids** collisions (CSMA/CA) and confirms via **ACK**. *(See Lecture 4 for the full treatment.)*

#### 4.2 Clear Channel Assessment and Virtual Carrier Sensing

### E5 — Define CCA; busy threshold; two CCA variants.
**Answer:** **CCA (Clear Channel Assessment)** is the **physical carrier sense**: the PHY measures the channel and declares **busy/idle**. The channel is declared **busy when received power exceeds ≈ −82 dBm**. **Two variants:** (1) **Energy-detection CCA** — declare busy if total received **energy** exceeds the threshold; (2) **Carrier-sense/correlation CCA** — declare busy if a **valid 802.11 signal (preamble correlation)** is detected (more selective than raw energy).

### E6 — Define NAV; difference from CCA; when a station refrains from transmitting.
**Answer:** **NAV (Network Allocation Vector)** is a **countdown timer = virtual carrier sense**: a station sets it from the **duration field** of a heard RTS/CTS (or other) frame and treats the medium as **busy** until it expires. **Difference:** CCA is **physical** (actually senses energy on air); NAV is **virtual** (logical reservation, set even when the data itself isn't heard). **A station refrains from transmitting whenever EITHER** the **NAV is non-zero** (virtual busy) **OR CCA reports busy** — it transmits only when **both indicate idle**.

### E7 — Why SIFS is too short for CCA; SIFS's hardware function.
**Answer:** **SIFS (16 µs)** is **shorter than the time CCA needs** to reliably assess the channel, so it is **not** a sensing gap — nothing should re-contend within a SIFS. Its **hardware function** is **transceiver turnaround**: the brief time a radio needs to **switch from receive to transmit mode** (and let the medium settle) before sending an **ACK/CTS**. By making this gap **shorter than any contention IFS**, SIFS guarantees the **follow-up frame (ACK/CTS) seizes the medium first**, before any new station can begin a fresh transmission.

### E8 — Scenario where CCA says idle but NAV blocks transmission.
**Answer:** A station **X** is a **neighbor of the receiver but hidden from the sender**. Sender **A** sends an **RTS** to receiver **B**; **B replies with CTS** (carrying a duration). X **hears the CTS** and **sets its NAV** for that duration. During A's **DATA** transmission, X **physically hears nothing** (A is out of X's range) → **CCA reports idle** — but X's **NAV is still counting down**, so X **defers anyway**. This is exactly how **virtual carrier sense protects the hidden station**: NAV overrides a "clear" CCA.

#### 4.3 Timing and Interframe Spaces

### E9 — Four interframe spaces in increasing order; purpose of each.
**Answer:** **SIFS < PIFS < DIFS < EIFS.**
- **SIFS (16 µs):** shortest; for **immediate, highest-priority** responses (ACK, CTS) — transceiver turnaround.
- **PIFS (25 µs):** for the **PCF (point coordinator/AP)** to gain **priority access** for contention-free service.
- **DIFS (34 µs):** the normal wait before a **DCF station** may start a **new transmission** (after sensing idle).
- **EIFS (≈200 µs):** longest; used **after receiving an erroneous/garbled frame** to give an in-progress exchange time to complete (extra protection).

### E10 — Using 802.11a (aSlotTime = 9 µs, SIFS = 16 µs), calculate PIFS and DIFS.
**Answer:**
- **PIFS = SIFS + aSlotTime = 16 + 9 = 25 µs.**
- **DIFS = SIFS + 2 × aSlotTime = 16 + 2×9 = 16 + 18 = 34 µs.**

### E11 — Priority mechanism in IFS durations; why shorter IFS = higher priority.
**Answer:** All stations defer for an **idle IFS** before acting; a station with a **shorter required IFS finishes waiting first** and **seizes the medium** before longer-IFS stations even begin. Thus **IFS length encodes priority**: **SIFS (ACK/CTS) < PIFS (PCF) < DIFS (new DCF frame) < EIFS (after error)**. Because an ACK only waits **SIFS (16 µs)** while a fresh frame waits **DIFS (34 µs)**, the **ACK always wins**, keeping exchanges atomic.

### E12 — When EIFS is used instead of DIFS; trigger and why longer.
**Answer:** **EIFS** replaces DIFS when a station **receives a frame it cannot decode correctly** (bad CRC/garbled) — it **doesn't know the NAV/duration** of the ongoing exchange. To **avoid colliding with an exchange it failed to parse**, the station waits the **longer EIFS (≈200 µs)**, which is long enough to let the unheard ACK/response complete. Once it hears a correct frame, it reverts to normal **DIFS** timing. The **longer deferral provides protection** in the face of decoding uncertainty.

### E13 — Timing diagram: busy channel, deferred access, contention window (SIFS/PIFS/DIFS + RTS).
**Answer:** *(Slide-style timeline, left→right):*
```
[ Busy medium ]──DIFS(34µs)──[ Contention Window: backoff slots (9µs each) ]──> RTS
                  ^SIFS(16µs) and PIFS(25µs) measured from end of busy
```
- While the medium is **busy**, all stations defer.
- After the medium goes idle, a DCF station waits **DIFS (34 µs)**; **SIFS (16 µs)** and **PIFS (25 µs)** are shorter reference points from the same instant (used by ACK/CTS and PCF respectively).
- Then the station counts down its **contention-window backoff** in **9 µs slots**; on reaching 0 it sends its frame (e.g., **RTS**).
*(Label: SIFS=16, PIFS=25, DIFS=34 µs; each backoff slot = aSlotTime = 9 µs.)*

#### 4.4 Frame Exchange Scenarios and ARQ

### E14 — The three MSDU delivery scenarios (what happens at station 1 & 2, and why).
**Answer:** (Station 1 = sender, Station 2 = receiver.)
1. **First unsuccessful (DATA lost):** S1 sends **DATA**; it's **corrupted/lost** → S2 receives nothing → **sends no ACK**. S1's **ACK timeout** expires → S1 infers failure, **doubles CW (BEB)**, and **retransmits**.
2. **Second unsuccessful (ACK lost):** S1 retransmits **DATA**; **S2 receives it correctly** and sends **ACK**, but the **ACK is lost** (interference). S1 again sees **no ACK** → infers failure → **retransmits again**. (S2 will get a **duplicate** — flagged by the retry bit/sequence number and discarded.)
3. **Successful:** S1 sends **DATA**; **S2 receives it** and, after **SIFS**, returns **ACK**; **S1 receives the ACK** → success → **CW resets to CWmin**, sequence advances.

### E15 — Second-unsuccessful: DATA received but ACK lost — what S1 infers/does.
**Answer:** S1 **cannot distinguish** a lost ACK from a lost DATA — it only knows **no ACK arrived**. So S1 **infers the transmission failed** and **retransmits the DATA** (with the **retry bit set** and CW doubled per BEB). S2, having already received the original, gets a **duplicate**, which it **detects via the sequence number/retry bit and discards**, while still **re-sending the ACK**. This duplicate handling is why 802.11 needs **sequence numbers**.

### E16 — Why 802.11 uses link-layer ARQ; what channel characteristic makes it necessary.
**Answer:** **ARQ (Automatic Repeat reQuest)** = ACK + retransmission at the **link layer**. It's necessary because the **wireless channel is unreliable**: **high, time-varying BER from fading, interference, noise, and collisions** means frames are **frequently lost/corrupted**. Recovering locally (per hop) with fast link-layer ACK/retransmit is **far quicker** than waiting for end-to-end (e.g., TCP) recovery, keeping throughput and latency acceptable over a lossy medium.

### E17 — Why ACK waits SIFS but a new transmitter waits DIFS; what if ACK used DIFS.
**Answer:** The **ACK waits only SIFS (16 µs)** so it can be sent **before any new station** (which must wait the longer **DIFS, 34 µs**) can grab the channel — guaranteeing the **DATA→ACK exchange stays atomic and prioritized**. **If the ACK used DIFS instead of SIFS**, then after the DATA a **new contending station (also waiting DIFS) could seize the medium at the same time**, **colliding with — or pre-empting — the ACK**. The receiver might **never get to send the ACK**, the sender would assume failure, and the network would suffer **needless retransmissions and collisions**.

#### 4.5 Collision Avoidance and Binary Exponential Backoff

### E18 — The complete backoff procedure (trigger, value selection, behavior when busy).
**Answer:**
- **Trigger:** a station with a frame to send finds the medium **busy**, or has **just completed/failed** a transmission, or must defer after DIFS → it enters **backoff**.
- **Value selection:** pick a **random integer in [0, CW]** (the current contention window); multiply by **aSlotTime (9 µs)** to get the backoff time.
- **Countdown:** while the medium stays **idle** (after a DIFS), **decrement the counter once per idle slot**. If the medium becomes **busy** mid-countdown, the station **freezes** the counter, waits until the medium is idle again **for a DIFS**, then **resumes from where it stopped** (not a new value). When the counter hits **0**, it **transmits**.

### E19 — CWmin = 16, CWmax = 1024: contention window after the 1st–5th failed attempts.
**Answer:** Using **CW after attempt n = min(2ⁿ⁻¹·CWmin − 1, CWmax)** (the window is `[0, CW]`):

| Failed attempt (n) | 2ⁿ⁻¹·16 − 1 | CW value |
|---|---|---|
| 1st | 2⁰·16 − 1 | **15** |
| 2nd | 2¹·16 − 1 | **31** |
| 3rd | 2²·16 − 1 | **63** |
| 4th | 2³·16 − 1 | **127** |
| 5th | 2⁴·16 − 1 | **255** |

*(Window keeps doubling: 511, 1023, then capped at CWmax = 1024.)* **Note on 16 vs 15:** **CWmin = 16** is the *parameter* (16 possible slot choices, `Rand(0…15)`); the *first CW value* is **15 = CWmin − 1** (the highest slot index). Both are correct — just different views.

### E20 — Why a deferred station resumes (not restarts) its countdown; the fairness property.
**Answer:** A station that **froze** during a busy period **resumes its remaining count** rather than drawing a new value because the slots it already counted down represent **time it has already "paid"** waiting. **Fairness property:** stations that have **waited longer have smaller remaining counters**, so they get to transmit **sooner** — this provides **temporal fairness / avoids starvation** and prevents a station from being repeatedly unlucky by re-randomizing each time. It approximates **FIFO/round-robin fairness** among contenders.

### E21 — AP1 (backoff 15) vs AP2 (backoff 25): trace countdown; who transmits first; the other's action.
**Answer:** After DIFS, both decrement once per idle slot **in lockstep**:
- After **15 idle slots**, **AP1 reaches 0 → AP1 transmits first.**
- At that moment, **AP2 has counted 15 slots too → its counter = 25 − 15 = 10 remaining.**
- AP2 senses the medium **busy** (AP1 transmitting) and **freezes at 10**, waiting. It will **resume from 10** once the medium is idle for a DIFS again.
**Result:** **AP1 transmits first; AP2 freezes with 10 slots remaining.**

### E22 — Continue: AP1 draws new backoff 18; AP2 resumes remaining 10 — who transmits next?
**Answer:** After AP1's Data+ACK completes and the medium is idle for DIFS, both count down again:
- **AP2 resumes at 10; AP1 starts fresh at 18.**
- After **10 idle slots**, **AP2 reaches 0 → AP2 transmits next.**
- At that point **AP1 has counted 10 → its counter = 18 − 10 = 8 remaining**, and AP1 **freezes at 8** while AP2 transmits.
**Result:** **AP2 transmits next** (its smaller remaining count wins) — demonstrating the **resume-not-restart fairness**.

### E23 — Why BEB grows CW on each failure; what if CW stayed at CWmin.
**Answer:** **BEB doubles CW after each failure** to **spread contenders over more slots** as collisions reveal **higher load** — lowering the probability that two stations pick the **same slot** again, which **stabilizes the network** under congestion. **If CW stayed at CWmin** regardless of collisions, then under load **many stations would keep contending in a tiny window**, **colliding repeatedly**; retransmissions would pile up, throughput would **collapse**, and latency would spike (a congestion-collapse / instability scenario). Growing CW is the **adaptive congestion control** of DCF.

#### 4.6 RTS/CTS and Hidden Station Problem

### E24 — How RTS/CTS "reserves" the channel; what the duration field carries.
**Answer:** The sender first transmits a small **RTS**; the receiver replies with a small **CTS**. Both frames carry a **duration field** announcing **how long the rest of the exchange (CTS + DATA + ACK + SIFS gaps) will take**. Every station hearing **RTS or CTS sets its NAV to that duration** and defers — effectively **reserving the channel** for the sender before the big DATA goes out. So the **duration field = the reservation length** that drives everyone's NAV.

### E25 — How NAV is set in neighbors of the transmitter (heard RTS) vs hidden stations near the receiver (heard CTS only).
**Answer:**
- **Neighbors of the transmitter** hear the **RTS** → they **set NAV** from the RTS duration and defer (they're near the sender).
- **Stations hidden from the transmitter but near the receiver** can't hear the RTS, but they **hear the receiver's CTS** → they **set NAV** from the CTS duration and defer.
Together, **RTS covers the sender's neighborhood** and **CTS covers the receiver's neighborhood** — and since **collisions happen at the receiver**, the **CTS-driven NAV is what protects against the hidden station**.

### E26 — Six-station example: station 6 hidden from station 2 but hears station 1's CTS — why it stays silent.
**Answer:** Station 2 wants to send to station 1. **Station 2 sends RTS → station 1; station 1 replies CTS.** **Station 6 cannot hear station 2's RTS** (hidden from station 2), so by physical CCA it might think the channel is free. **But station 6 is in range of station 1 and hears station 1's CTS**, which carries the **duration** of the upcoming DATA+ACK. Station 6 **sets its NAV** for that duration and **defers** — even though **it never received the RTS**. Thus the **CTS-based virtual carrier sense** silences the hidden station 6, **preventing a collision at station 1** during station 2's DATA.

### E27 — Why SIFS < DIFS in RTS/CTS; what if CTS used DIFS after an RTS.
**Answer:** The receiver returns **CTS after only SIFS (16 µs)** so the **CTS is sent before any other station** (which must wait **DIFS, 34 µs**) can act — keeping the RTS→CTS handshake **atomic and prioritized**. **If CTS waited DIFS instead of SIFS**, then **other contending stations (also waiting DIFS) could transmit at the same moment**, **colliding with the CTS** or grabbing the channel first. The reservation would **break**, hidden stations wouldn't receive the CTS reliably, and the **hidden-terminal protection would fail**.

### E28 — One advantage and one disadvantage of RTS/CTS; when overhead is justified.
**Answer:**
- **Advantage:** **Solves the hidden-terminal problem** (via receiver CTS/NAV) and **caps collision cost** to the small RTS instead of a large DATA frame.
- **Disadvantage:** **Per-packet overhead** (extra RTS + CTS + two SIFS gaps), which **reduces efficiency**, especially for small packets.
- **Justified when:** packets are **large**, **hidden terminals are likely**, or the network is **congested/high-load** — captured by an **RTS threshold** (enable RTS/CTS only above a packet-size). For **small packets / clean topologies**, leave it off.

#### 4.7 Medium Access Overhead and DCF Inefficiencies

### E29 — All overhead sources in a full DCF transmission with RTS/CTS (timelines).
**Answer:** *(Transmitter/receiver timeline overhead components):*
1. **DIFS** wait (34 µs) before contending.
2. **Random backoff** (idle slots, 9 µs each) — average ~CW/2 slots.
3. **RTS** frame + **SIFS**.
4. **CTS** frame + **SIFS**.
5. **PHY preamble/header** on **every** frame (RTS, CTS, DATA, ACK).
6. **MAC header + FCS** on the DATA frame.
7. **SIFS** before the **ACK**.
8. **ACK** frame.
*(Timeline:* `DIFS → backoff → RTS → SIFS → CTS → SIFS → DATA → SIFS → ACK`*, with preambles/headers on each frame.)* Only the **DATA payload** is "useful"; everything else is overhead.

### E30 — Why ~35% overhead at 54 Mbps; which components dominate at high rates.
**Answer:** At **54 Mbps** the **payload is sent very fast**, but the **fixed-time overheads don't shrink** — they're paid in **microseconds regardless of data rate**. The dominating components are the **constant-time, rate-independent** ones: **DIFS/SIFS gaps, backoff slots, and especially the PHY preambles/headers** (often sent at a **low basic rate**), plus RTS/CTS/ACK frames. Because the **DATA shrinks in time while the overhead stays fixed**, overhead becomes a **larger fraction (~35%)** as the data rate rises. *(Overhead is dominated by fixed timing + preamble, not the payload.)*

### E31 — The three significant DCF inefficiencies.
**Answer:**
1. **Idle channel time during countdown:** while stations **count down backoff slots**, the channel sits **idle/unused** — wasted capacity even when traffic is waiting.
2. **Collision probability under high node density:** with **many stations** contending in a finite CW, the chance **two pick the same slot** rises, causing **collisions and retransmissions**.
3. **Exponential backoff under congestion:** repeated collisions **double CW**, making stations wait **ever longer**, which **increases latency** and can **under-utilize** the channel during heavy load (long idle backoffs).

### E32 — At 10 nodes, P(≥2 same backoff slot) > 40%: consequences for throughput and latency.
**Answer:** When **>40%** of rounds have **two+ stations choosing the same slot**, those stations **transmit simultaneously → collide**. **Consequences:**
- **Throughput drops:** a large fraction of transmission attempts are **wasted on collisions**; the channel carries **retransmissions instead of new data**.
- **Latency rises:** each collision triggers **BEB (CW doubling) + retransmission**, so packets wait through **multiple backoff rounds**; **jitter** worsens.
The network spends increasing time **resolving contention** rather than delivering payload — the classic **DCF-under-density** degradation.

### E33 — Backoff waste (idle slots) vs collision waste (retransmissions): which is worse at low vs high density?
**Answer:**
- **Low node density:** **collisions are rare** (few contenders), so the dominant waste is **idle backoff slots** — the channel sits idle while a lone station counts down. **Backoff (idle) waste is worse at low density.**
- **High node density:** **many stations contend**, so **collisions dominate** — repeated simultaneous transmissions and retransmissions consume the channel. **Collision waste dominates at high density.**
*(This is why an ideal CW is small at low load, large at high load — and why fixed CWmin hurts under congestion.)*

### — Part B: SAMPLE QUESTIONS —

#### 5.1 Short Questions

### S1 — What does BSS stand for / what is it?
**Answer:** **Basic Service Set** — the fundamental 802.11 building block: a group of stations coordinated by **one AP** (infrastructure BSS) sharing the same channel.

### S2 — Role of the Coordination Function (CF).
**Answer:** The CF **decides which station may transmit and when**, coordinating access to the shared medium — via **DCF** (distributed contention) or **PCF** (centralized polling).

### S3 — DCF vs PCF in one sentence each.
**Answer:** **DCF** = mandatory, **distributed, contention-based** access (CSMA/CA + backoff, no priority). **PCF** = optional, **centralized, polling-based** access giving **contention-free, prioritized** service for time-bounded traffic.

### S4 — Minimum stations in an IBSS.
**Answer:** **Two.**

### S5 — Frequency band and max data rate of 802.11n.
**Answer:** **2.4 GHz and 5 GHz**; **up to 600 Mbps.**

### S6 — What is CCA and its power threshold in 802.11?
**Answer:** **Clear Channel Assessment** = physical carrier sensing; the channel is declared **busy above ≈ −82 dBm**.

### S7 — Define NAV; physical or virtual?
**Answer:** **Network Allocation Vector** — a countdown reservation timer; it is **virtual carrier sensing** (logical, set by frame duration fields), complementing physical CCA.

### S8 — Four IFS types, shortest to longest.
**Answer:** **SIFS < PIFS < DIFS < EIFS** (16 < 25 < 34 < ≈200 µs in 802.11a).

### S9 — Formula for DIFS in terms of SIFS and aSlotTime.
**Answer:** **DIFS = SIFS + 2 × aSlotTime.**

### S10 — 802.11a values of aSlotTime, SIFS, PIFS, DIFS.
**Answer:** **aSlotTime = 9 µs, SIFS = 16 µs, PIFS = 25 µs, DIFS = 34 µs.**

### S11 — When is EIFS used instead of DIFS?
**Answer:** After a station **receives a frame it can't decode correctly** (bad CRC) — it waits the longer **EIFS** to protect the ongoing exchange it failed to parse.

### S12 — BEB formula for CW after the n-th failed attempt.
**Answer:** **CW(n) = min(2ⁿ⁻¹ · CWmin − 1, CWmax)** (window `[0, CW]`); equivalently CW doubles each failure up to CWmax.

### S13 — CWmin and CWmax in 802.11a.
**Answer:** **CWmin = 16, CWmax = 1024.**

### S14 — Why resume (not restart) the backoff countdown after the channel is idle again.
**Answer:** To **credit the slots already waited**, giving **longer-waiting stations priority** → **fairness / no starvation** (vs re-randomizing, which would discard waiting time).

### S15 — What does the RTS/CTS duration field carry; how others use it.
**Answer:** It carries the **time remaining for the whole exchange** (CTS+DATA+ACK+SIFS). Other stations **set their NAV** to that value and **defer** until it expires (virtual carrier sense).

#### 5.2 Descriptive Questions

### S16 — Complete DCF sender state machine.
**Answer:**
1. **Frame ready → sense channel (CCA + NAV).**
2. **If idle for DIFS** → (if backoff pending or after a prior tx) **run backoff countdown** (decrement per idle slot; **freeze if busy**, resume after next DIFS).
3. **Backoff = 0 →** *(optional)* send **RTS**, wait **SIFS**, receive **CTS** (if RTS/CTS enabled).
4. **Send DATA**, then **wait SIFS** for **ACK**.
5. **ACK received → SUCCESS:** reset **CW = CWmin**, advance sequence number, done.
6. **No ACK (timeout) → FAILURE:** **double CW (BEB)**, set retry bit, pick new backoff, **go to step 2** (retransmit) until success or retry limit (then drop).
*(If medium busy at step 1, defer and enter backoff.)*

### S17 — Three MSDU delivery scenarios with timing diagrams.
**Answer:**
- **(1) First unsuccessful — DATA lost:** `DIFS→DATA→(no ACK, timeout)`. S2 gets nothing → no ACK; S1 infers loss → BEB + retransmit. **Frame lost: DATA.**
- **(2) Second unsuccessful — ACK lost:** `DATA→(S2 OK)→ACK lost`. S1 sees no ACK → retransmits (retry bit); S2 detects **duplicate** (sequence number) and discards but re-ACKs. **Frame lost: ACK.**
- **(3) Successful:** `DIFS→DATA→SIFS→ACK→(received)`. S1 gets ACK → success, **CW resets to CWmin**. **Frame lost: none.**
*Common thread:* S1 only knows **ACK present/absent**, so lost-DATA and lost-ACK look identical to it → both trigger retransmit; duplicates are filtered by sequence numbers.

### S18 — Four interframe spaces in detail (purpose, value/formula, scenario).
**Answer:**

| IFS | 802.11a value/formula | Purpose | Applied when |
|---|---|---|---|
| **SIFS** | 16 µs | Highest priority; transceiver turnaround | Before **ACK, CTS**, consecutive frames |
| **PIFS** | SIFS + aSlotTime = 25 µs | PCF/AP priority access | Start of **contention-free (PCF)** period |
| **DIFS** | SIFS + 2·aSlotTime = 34 µs | Normal DCF access wait | Before a **new DCF** frame after idle |
| **EIFS** | ≈200 µs | Protection after a decode error | After receiving a **corrupted** frame |

### S19 — Binary Exponential Backoff in detail.
**Answer:** The **contention window CW** defines the range `[0, CW]` from which a station picks a **random backoff** (× aSlotTime). **Purpose:** randomize transmit times so contenders rarely collide. **Growth:** start at **CWmin = 16**; **each failed attempt doubles CW** (15→31→63→127→255…) up to **CWmax = 1024**; **success resets to CWmin**. **Countdown:** decrement once per **idle slot**; **freeze when busy**, **resume** after the next DIFS. **Why resume, not restart:** to credit waiting time → **fairness / starvation avoidance**. The doubling is DCF's **adaptive response to congestion**.

### S20 — RTS/CTS mechanism in 802.11 (spacing, NAV in neighbor/hidden, SIFS priority).
**Answer:** Exchange: `RTS —SIFS→ CTS —SIFS→ DATA —SIFS→ ACK`, all **separated by SIFS** so the sequence stays **atomic and high-priority** (no DIFS-waiting station can break in). **NAV setting:** stations hearing the **RTS** (transmitter's neighbors) set NAV; stations hearing **only the CTS** (hidden from the sender but near the receiver) **also set NAV** → both neighborhoods defer. **SIFS** ensures **CTS and ACK** are sent before any new contention, which is what makes the **reservation reliable** and protects the **hidden station** (collision point is the receiver, covered by CTS).

### S21 — DCF medium-access overhead + three inefficiencies under load.
**Answer:** **Overhead components:** DIFS wait, backoff idle slots, RTS+CTS (if enabled), **PHY preamble/header on every frame**, MAC header+FCS, SIFS gaps, and the ACK — only the **payload** is useful (≈35% overhead at 54 Mbps, dominated by **fixed-time** preamble/IFS). **Three inefficiencies under high load:** (1) **idle countdown** wastes the channel; (2) **collisions rise with node density** (same-slot picks) → retransmissions; (3) **exponential backoff under congestion** lengthens waits → higher latency and possible under-utilization. Together they cap DCF's throughput as users grow.

#### 5.3 Analysis and Design Questions

### S22 — 802.11a: A backoff = 7, B backoff = 12, both count down after DIFS.
**Answer:**
- **(a) Who transmits first?** **Station A** (smaller backoff, 7 < 12) reaches 0 first.
- **(b) B's remaining backoff when A begins:** both decremented **7 slots**, so **B = 12 − 7 = 5 slots remaining** (B freezes at 5).
- **(c) Additional slots B waits after A's transmission ends:** B **resumes its remaining 5 slots** (after the channel is idle for a DIFS), so **5 more backoff slots** (= 5 × 9 µs = 45 µs of countdown) before B can transmit.

### S23 — CWmin = 16; four consecutive failures.
**Answer:**
- **(a) CW after each failure:** 1st → **15**, 2nd → **31**, 3rd → **63**, 4th → **127** (i.e., 2ⁿ⁻¹·16 − 1).
- **(b) If the 5th attempt succeeds, CW on the 6th attempt:** **success resets CW to CWmin**, so the 6th attempt uses **CW = 15 (CWmin = 16)**. **Justification:** a successful transmission always **resets the contention window to CWmin** — BEB only grows CW on *failures*, never carries the inflated window past a success.

### S24 — Hidden terminal, RTS/CTS disabled; A and B both transmit after DIFS.
**Answer:**
- **(a) At the AP:** A's and B's frames **collide at the AP** → the AP receives a **corrupted frame** (decode fails).
- **(b) How the AP signals failure:** it **sends no ACK** — the **absence of an ACK** is the failure signal to both A and B.
- **(c) What each node does + how BEB helps:** each node's **ACK timeout** expires → it **doubles its CW (BEB)** and picks a **new random backoff from the larger window**. The bigger window makes it **less likely** A and B pick the **same slot** again → **lower future collision probability** and eventual successful, staggered transmissions.

### S25 — Same hidden scenario but RTS/CTS enabled; A wins backoff and sends RTS.
**Answer:**
- **(a) Frame trace + NAV setters:**
  1. **A → RTS → AP:** stations hearing the RTS (**A's neighbors**) set **NAV**.
  2. **AP → CTS → (heard by A and B):** **B hears the CTS** (B is near the AP/receiver) and **sets its NAV** for the exchange duration.
  3. **A → DATA → AP** (B is silent, NAV active).
  4. **AP → ACK → A** (after SIFS).
- **(b) Why B can't collide during A's DATA:** B **set its NAV from the CTS**, so B treats the medium as **busy for the whole DATA+ACK duration** and **defers** — even though B can't hear A's DATA. The **CTS-driven NAV** removes the hidden-terminal collision at the AP.

### S26 — Dense office: 20 active 802.11g stations on one AP — why DCF performs poorly; BEB's role; one improvement.
**Answer:** **Why poor:** with **20 contenders** in a finite contention window, the **probability two pick the same slot is high** → **frequent collisions**; the channel fills with **retransmissions, idle backoff, and IFS/preamble overhead** rather than payload → **throughput collapses, latency/jitter spike**. **BEB's role:** each collision **doubles CW**, so stations **wait longer and longer**, reducing collisions but **increasing delay** and leaving the channel **idle during long backoffs** — it stabilizes but doesn't restore efficiency. **One protocol-level improvement:** adopt **802.11e EDCA/QoS with tuned/adaptive CW** (or a **scheduled/polled access like PCF/HCCA**, or **frame aggregation A-MPDU/A-MSDU**) to **amortize overhead and reduce contention** — any approach that **schedules or aggregates** to cut per-packet contention.

### S27 — RTS/CTS enabled vs disabled: comparison table + when each is better.
**Answer:**

| Criterion | RTS/CTS **enabled** | RTS/CTS **disabled** |
|---|---|---|
| Hidden-terminal protection | **Yes** (CTS/NAV) | **No** |
| Overhead per packet | **Higher** (RTS+CTS+2 SIFS) | **Lower** |
| Effective throughput (small packets) | **Lower** (overhead dominates) | **Higher** |
| Effective throughput (large packets) | **Higher** (collision cost capped to RTS) | Lower if collisions occur |
| NAV-based protection | **Yes** (virtual carrier sense) | No (physical CCA only) |

**When each wins:** **enable** RTS/CTS for **large packets, hidden-terminal-prone or congested** networks; **disable** for **small packets in clean, low-contention** topologies. 802.11 captures this with an **RTS threshold** (use RTS/CTS only above a packet-size).

---

## 3. Conceptual Deep Dive

**802.11 = Lecture 4 with exact numbers.** Every abstract idea from the MAC lecture gets a concrete value here: "wait before transmitting" becomes **DIFS = 34 µs**; "random backoff" becomes **BEB over [0, CW] in 9 µs slots**; "virtual carrier sense" becomes the **NAV set by RTS/CTS duration fields**; "confirm success" becomes the **SIFS-then-ACK** exchange.

**The architecture hierarchy.** *Station → BSS (one AP) → ESS (many BSSs joined by a DS, one SSID, roaming).* **IBSS** is the AP-less ad-hoc cousin (min **2** stations). The **portal** bridges to wired LANs. This hierarchy is what enables **seamless roaming**.

**Two carrier senses, one rule.** A station transmits only when **physical (CCA, −82 dBm) AND virtual (NAV) both say idle**. The genius is **NAV**: it lets a **hidden station defer based on a CTS it heard**, even though its **CCA hears nothing** — solving the hidden terminal at the **receiver**, exactly where the collision would occur.

**IFS = a priority ladder.** Because every station must see the medium idle for its IFS before acting, **shorter IFS = higher priority**. So **SIFS (ACK/CTS) beats PIFS (PCF) beats DIFS (new data) beats EIFS (after error)**. This single mechanism keeps **DATA→ACK and RTS→CTS atomic**: the response (SIFS) always pre-empts any new contender (DIFS). Memorize **PIFS = SIFS + slot**, **DIFS = SIFS + 2·slot**.

**BEB = distributed congestion control.** CW starts small (**16**), **doubles on every failure** (to spread out contenders as load is revealed), and **resets to CWmin on success**. **Resume-not-restart** countdown gives **fairness** (waiting time is credited). Without doubling, dense networks would **collapse** into endless collisions.

**The three inefficiencies are the punchline.** DCF wastes capacity on **idle backoff**, **collisions at density**, and **long exponential backoff under congestion** — together producing **~35% overhead at 54 Mbps** (dominated by **fixed-time** preamble/IFS, not payload). This motivates everything after 802.11a: **QoS (802.11e), aggregation (n/ac), and scheduled access**.

**The 16-vs-15 subtlety (resolved).** **CWmin = 16** is the *parameter* — there are **16 possible backoff slots**, `Rand(0…15)`. The *first CW value* equals **15 = CWmin − 1** (the largest slot index). So "16" (slot count / CWmin) and "15" (first CW value) are **both correct**, viewed differently — not a slide error. On an exam: **CWmin = 16; first CW = 15.**

**Where students get confused.** Reporting the wrong IFS order or forgetting **PIFS** entirely; thinking a lost ACK is distinguishable from lost DATA (it isn't — both → retransmit, duplicates filtered by sequence number); forgetting **success resets CW to CWmin**; saying CCA protects hidden stations (it's **NAV/CTS**); mixing the **16 vs 15** values.

---

## 4. Important Exam Pointers
- **Memorize the 802.11a numbers cold:** aSlotTime **9**, SIFS **16**, PIFS **25**, DIFS **34**, EIFS **≈200 µs**, CCA **−82 dBm**, CWmin **16**, CWmax **1024**.
- **PIFS = SIFS + aSlotTime; DIFS = SIFS + 2·aSlotTime** — derive them, don't just recall.
- **BEB computations are near-certain:** CW = 15, 31, 63, 127, 255… (2ⁿ⁻¹·16 − 1), reset to CWmin on success.
- **Backoff traces:** lower backoff wins; loser **freezes and resumes the remainder** (e.g., 12 with winner 7 → 5 left). Practice E21/E22/S22.
- **IFS priority:** shorter IFS = higher priority; **SIFS keeps ACK/CTS atomic** — a favorite "what if ACK used DIFS?" question.
- **NAV/CTS solves hidden stations** (E8, E26, S25) — anchor it at the **receiver**.
- **Three MSDU scenarios** + the **lost-ACK → duplicate** subtlety (sequence numbers).
- **DCF overhead (~35%) and the three inefficiencies** — explain *why* fixed-time overhead dominates at high rates.
- **DCF (mandatory/contention) vs PCF (optional/polling/QoS).**

## 5. Commonly Forgotten Points
- **Don't omit PIFS** in the IFS list; order is **SIFS < PIFS < DIFS < EIFS**.
- **CCA threshold = −82 dBm** (a specific number the instructor uses).
- **Success resets CW to CWmin** — BEB only grows on *failures*.
- **Resume, not restart** the backoff counter (fairness).
- **Hidden station is silenced by NAV from the CTS**, not by CCA.
- **Lost DATA and lost ACK are indistinguishable to the sender** → both retransmit; **duplicates filtered by sequence number**.
- **EIFS follows a *decode error*** (unknown duration), not a normal idle.
- **IBSS minimum = 2 stations; ESS = multiple BSSs + DS.**
- **The "16 vs 15":** CWmin = 16 (slots), first CW value = 15.
- **DCF overhead is dominated by fixed-time preamble/IFS**, which is why it grows as a % at high data rates.

## 6. Tips and Tricks
- **IFS ladder mnemonic "S-P-D-E":** **S**IFS(16) → **P**IFS(25) → **D**IFS(34) → **E**IFS(200); shorter = higher priority.
- **Derive the timers:** PIFS = 16+9 = **25**; DIFS = 16+18 = **34**. (aSlotTime = 9.)
- **BEB doubling:** 15→31→63→127→255→511→1023→cap **1024**. (Each = previous×2 + 1.)
- **Backoff race rule:** *lowest backoff transmits; the loser keeps (its value − winner's) and resumes.*
- **Success = reset:** any successful frame snaps CW back to **CWmin (16)**.
- **Who sets NAV?** *RTS covers the sender's side; CTS covers the receiver's side (hidden node).*
- **SIFS priority test:** *"If ACK/CTS waited DIFS, a new station would collide with it."*
- **16 vs 15:** *"Sixteen slots, top index fifteen."*

## 7. Formula Cheat Sheet

### 802.11a constants (memorize)
| Symbol | Value | Meaning |
|---|---|---|
| aSlotTime | **9 µs** | one backoff slot |
| SIFS | **16 µs** | shortest IFS (ACK/CTS turnaround) |
| PIFS | **25 µs** | PCF priority IFS |
| DIFS | **34 µs** | DCF normal-access IFS |
| EIFS | **≈200 µs** | IFS after a decode error |
| CCA threshold | **−82 dBm** | busy/idle power level |
| CWmin / CWmax | **16 / 1024** | contention-window bounds |

### Timing formulas
| Formula | Use |
|---|---|
| `PIFS = SIFS + aSlotTime` | = 25 µs |
| `DIFS = SIFS + 2·aSlotTime` | = 34 µs |
| `backoff time = Rand(0…CW) × aSlotTime` | random deferral |
| `IFS order: SIFS < PIFS < DIFS < EIFS` | priority (shorter = higher) |

### Backoff (BEB)
| Formula | Use |
|---|---|
| `CW(n) = min(2ⁿ⁻¹·CWmin − 1, CWmax)` | window after n-th failure (15,31,63,127,255…) |
| `CW ← CWmin on success` | reset rule |
| `remaining = own_backoff − winner_backoff` | freeze/resume after losing |
| `slots → time: ×9 µs` | convert slots to µs |

### Frame exchange & reliability
| Item | Detail |
|---|---|
| Successful exchange | `DIFS → backoff → [RTS → SIFS → CTS → SIFS →] DATA → SIFS → ACK` |
| ACK rule | **No ACK ⇒ collision/loss ⇒ retransmit (BEB)** |
| NAV | set from **duration field** of RTS/CTS = virtual carrier sense |
| Transmit condition | **CCA idle AND NAV = 0** |
| DCF overhead | **≈35% at 54 Mbps** (dominated by fixed-time preamble/IFS) |

### Architecture quick reference
| Term | Meaning |
|---|---|
| BSS / IBSS | AP-based cell / ad-hoc (no AP, **min 2** stations) |
| DS / portal | backbone joining BSSs / bridge to non-802.11 LAN |
| ESS | multiple BSSs + DS = one logical network (roaming) |
| DCF / PCF | mandatory contention / optional polling (QoS) |

> **One-line summary:** 802.11 DCF = **CSMA/CA with exact timers** — sense (**CCA + NAV**), wait (**DIFS**), **BEB backoff**, optionally **reserve (RTS/CTS → NAV)**, send **DATA**, confirm with **SIFS-priority ACK** — engineered around *collisions-at-the-receiver*, at the cost of **~35% overhead** and three density-driven inefficiencies.
