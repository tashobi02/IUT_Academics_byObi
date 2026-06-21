# Lecture 4: Understanding MAC for Managing Shared Wireless Channels

> **Course:** CSE 4615 — Wireless Networks (IUT)
> **Scope:** Answers to **every** numbered item — all **Exercises (§4.1–4.6, E1–E26)** *and* all **Sample Questions (§5.1–5.3, S1–S23)** — in full depth, plus a conceptual deep-dive, exam pointers, common mistakes, tricks, and a formula/reference sheet. Verified against the slides ("no fate sharing," RTS/CTS virtual carrier sense, thresholded correlation, "collisions are spatially located at the receiver").

---

## 1. Lecture Overview

This lecture answers: **how do many devices share one wireless channel without chaos?** That is the job of the **Medium Access Control (MAC)** sublayer.

The narrative builds in three movements:

1. **Why wired collision detection (CSMA/CD) fails in wireless.** In wired Ethernet, every node shares the *same* electrical state on the wire — **"fate sharing"** — so a transmitter can **listen while transmitting** and detect a collision. In wireless this breaks for three reasons: a radio **can't hear a faint remote signal under its own ~10⁶× stronger transmission** ("no fate sharing"), **fading** makes "silence" unreliable, and the **hidden terminal problem** hides collisions from the sender.

2. **The 802.11 answer: CSMA/CA.** Instead of *detecting* collisions, **avoid** them: sense the medium, wait an **IFS + random backoff**, transmit, and use a **link-layer ACK** as proof of success (no ACK ⇒ assume collision/loss). Add **RTS/CTS control frames** to create **virtual carrier sense (NAV)** that defeats hidden terminals.

3. **Two philosophies of access.** **Contention-based** (CSMA/CA — sense and compete) vs **provisioned/scheduled** (**TDMA/FDMA/CDMA** — pre-assign time/frequency/code). Plus the spatial idea: **far-apart links can reuse space concurrently (spatial reuse); nearby links must take turns.**

The unifying insight, stated explicitly on the slides: **collisions are spatially located at the receiver, not the transmitter.** This single fact explains why sender-side carrier sensing is insufficient and why **receiver-anchored control (CTS/NAV)** is the fix.

---

## 2. Suggestion Questions and Answers

> **Part A — Exercises (E1–E26).**  **Part B — Sample Questions (S1–S23).**

### — Part A: EXERCISES —

#### 4.1 Shared Medium and Carrier Sense

### E1 — Why two conversations are independent in wired but interfere in wireless (with diagram).
**Answer:**
**Wired:** each link is a **separate, contained electrical path** (point-to-point cable / switched port). Signals stay **inside the wire**, so conversation A↔B and C↔D **don't mix**. *(Diagram: two isolated lines, A—B and C—D, no overlap.)*
**Wireless:** all nodes radiate into the **same open air** (a **broadcast, shared medium**). Signals **spread and overlap in space**, so two simultaneous transmissions in range **add together and corrupt** each other. *(Diagram: A→B and C→B radiating circles overlapping at B.)*
**Core difference:** wired = **guided & isolated**; wireless = **broadcast & shared** — sharing is the root of all MAC problems.

### E2 — Define "carrier sense" and "multiple access"; why sensing can fail.
**Answer:**
- **Carrier Sense (CS):** before transmitting, a station **listens** to check whether the channel is **busy or idle** (detects an ongoing carrier).
- **Multiple Access (MA):** **many stations share one channel**, each contending for access.
**Why CS can fail in wireless:** a station may **not hear** an ongoing transmission because the other transmitter is **out of range (hidden terminal)** or its signal is **faded below the sense threshold** — so CS reports "idle" when the channel is actually busy **at the receiver**. Sensing happens at the *transmitter*, but collisions occur at the *receiver*.

### E3 — The two problems preventing 802.11 collision detection (+ physical cause each).
**Answer:**
1. **Signal-strength asymmetry / "no fate sharing":** a radio's **own transmitted signal is ~10⁶ times stronger** than a far-off incoming signal, so it **physically cannot hear** a remote collision while transmitting. *Physical cause:* limited receiver dynamic range / self-interference (effectively half-duplex on one channel).
2. **Hidden terminal problem:** two senders out of each other's range collide **at the receiver**, invisibly to the senders. *Physical cause:* finite radio range + the broadcast geometry (collision is a **receiver-side** event). *(Fading compounds both — received strength fluctuates.)*

### E4 — Compare CSMA/CD vs CSMA/CA (procedure, hardware, efficiency, deployment).
**Answer:**

| Aspect | CSMA/CD | CSMA/CA |
|---|---|---|
| Core idea | **Detect** collisions while transmitting | **Avoid** collisions before transmitting |
| Procedure | Sense → transmit **& listen** → on collision, jam + backoff | Sense → IFS + **random backoff** → transmit → **ACK** |
| Hardware | Must **transmit & receive simultaneously** | Half-duplex OK; needs ACK timing |
| Collision handling | Abort early (efficient on wire) | Can't abort; full packet may be lost |
| Efficiency | High on shared wire | Lower (backoff + ACK + RTS/CTS overhead) |
| Deployment | **Wired Ethernet** | **Wireless 802.11 Wi-Fi** |

#### 4.2 Collision Detection and Fate Sharing

### E5 — "Fate sharing of the link" in wired; why it makes CD feasible at the transmitter.
**Answer:** **Fate sharing** means **all nodes on the wire experience the same channel state** — if two signals collide, **everyone (including each transmitter) sees the corrupted/elevated voltage**. Because the transmitter's own signal and any colliding signal are **comparable in strength on the shared wire**, the transmitter can **listen while transmitting** and **directly detect** the collision (abnormal signal). Shared fate = shared evidence ⇒ **collision detection works at the sender**.

### E6 — Signal-strength-vs-space diagram for wired (A,B,C): where collision occurs; how A detects it.
**Answer:** *(Plot signal strength along the wire A—B—C.)* If A and C transmit together, their signals **superpose along the entire wire**, producing an **abnormally high/garbled level everywhere**, including **at A**. Because A reads the **same combined level** as everyone (fate sharing), A **detects** the mismatch between what it sent and what's on the wire ⇒ **collision detected at A**. The collision is observable **at the transmitter**.

### E7 — Repeat for wireless; why states at A and B differ and CD fails.
**Answer:** *(Plot strength vs space for A and C transmitting to B.)* Near **A**, A's **own signal dominates** (huge); C's distant signal is **tiny** → A "sees" only itself and senses **no collision**. At **B (the receiver)**, A's and C's signals arrive at **comparable strength and collide**. So the **signal state at A ≠ state at B**: A reads "clean," B reads "collision." Because the **transmitter and receiver no longer share the same fate**, A **cannot detect** the collision ⇒ **CD fails**; the collision is only visible **at B**.

### E8 — Why wireless radios aren't full-duplex (MAC view); the hardware constraint.
**Answer:** A radio transmitting on a frequency floods its **own receiver** with its outgoing signal, which is **orders of magnitude (~10⁶×) stronger** than any incoming signal. The receiver's **limited dynamic range** can't pick out a faint remote signal under this **self-interference**, so the radio **can't meaningfully receive while transmitting on the same channel** — effectively **half-duplex**. *Hardware constraint:* simultaneous same-channel transmit-and-receive requires impractical **self-interference cancellation**, so practical 802.11 radios don't do it ⇒ no listen-while-transmit ⇒ no CD.

#### 4.3 Link-Layer ACK and CSMA/CA

### E9 — How link-layer ACKs substitute for CD; what absence of ACK means.
**Answer:** Since the sender **can't detect** a collision directly, the **receiver sends a short ACK** after correctly receiving a frame (after a **SIFS**). The ACK is **positive proof of success**. **Absence of an ACK** (within the timeout) is interpreted by the sender as **failure** — a **collision or loss** — triggering **retransmission** (with **doubled contention window**, exponential backoff). So the ACK turns the **receiver into the collision reporter**, replacing the impossible sender-side detection.

### E10 — Timing diagram for a successful CSMA/CA exchange (DIFS, Data, Random Backoff, SIFS, ACK).
**Answer:** *(Timeline, left→right):*
1. **Channel idle for DIFS** (sender waits a full DIFS of idle medium).
2. **Random Backoff** — sender counts down a random number of idle slots (freezing if the medium goes busy); reaching 0 →
3. **Data transmission** (the frame).
4. **SIFS** — short gap (SIFS < DIFS gives ACK priority).
5. **ACK** from the receiver.
*Order:* `DIFS → (Backoff) → DATA → SIFS → ACK`. The **SIFS < DIFS** ordering guarantees the ACK seizes the medium before any new contention starts.

### E11 — Advantage of small RTS/CTS control frames when data packets are large.
**Answer:** If a **collision is going to happen**, it's far cheaper for it to hit a **tiny RTS** than a **large DATA** frame. RTS/CTS lets stations **reserve the channel** with **short frames first**; only after a successful RTS→CTS handshake is the **big DATA** sent — now collision-protected. So the **collision cost is bounded to the small frame**, dramatically improving efficiency for **large packets** (and where hidden terminals exist). For **small packets**, the RTS/CTS overhead isn't worth it.

### E12 — Define "virtual carrier sense"; how RTS/CTS implements it.
**Answer:** **Virtual carrier sense** is a **logical "busy" indication** maintained **without physically hearing** the data transmission. It's implemented via the **NAV (Network Allocation Vector)**: **RTS and CTS frames carry a duration field** announcing how long the upcoming exchange will last. Every station that hears RTS *or* CTS **sets its NAV** and **defers** for that duration — even if it **cannot hear the actual DATA**. This **virtual** (NAV-based) sense complements **physical** carrier sense and is what protects **hidden terminals** (they hear the CTS even if they can't hear the sender).

#### 4.4 Hidden Terminal and Exposed Terminal Problems

### E13 — Hidden terminal scenario (A,B,C): why C transmits during A→B; result at B.
**Answer:** *(Topology A — B — C; A and C both in range of B but **not of each other**.)* A transmits to B. **C carrier-senses and hears nothing** (A is out of C's range), concludes **"idle,"** and also transmits to B. The two signals **collide at B**, **corrupting A's frame**. Neither A nor C is aware. **Result:** undetected collision **at the receiver B**; A's transmission fails (no ACK) → retransmit. The senders are "hidden" from each other.

### E14 — How RTS/CTS solves hidden terminal; which frame makes the hidden node defer.
**Answer:** Sequence: **A→ RTS → B; B→ CTS → (heard by A *and* C); A→ DATA → B; B→ ACK → A.** Because **B's CTS reaches C** (C is in B's range), **C learns the channel is reserved** and **sets its NAV to defer** for the announced duration — even though **C never heard A's RTS or DATA**. **The CTS frame is what makes the hidden node (C) defer.** Anchoring the reservation **at the receiver (B)** is precisely why it works (collisions are located at B).

### E15 — Exposed terminal scenario (A,B,C,D): why C unnecessarily defers from C→D.
**Answer:** *(Topology A — B — C — D; B↔C in range.)* B is transmitting to A. **C hears B's transmission** and, under plain CSMA, senses **"busy"** and **defers** — even though C wants to send to **D**, which is **out of B's range**. C→D would **not** have collided with B→A (different receivers, spatially separated). So **C wastes a transmission opportunity**: a **false-busy**. **Consequence:** reduced throughput / lost spatial reuse.

### E16 — How RTS/CTS lets exposed terminal C decide it's safe; which frame C hears/doesn't.
**Answer:** With RTS/CTS, C **hears B's RTS** (B is in range) but **does NOT hear a CTS from A** (A is out of C's range). **Hearing RTS-only, without the matching CTS, tells C that C is an exposed terminal** — its intended receiver (D) is away from the protected receiver (A). C concludes it is **safe to transmit to D concurrently**. **C hears: RTS (from B). C does not hear: CTS (from A).** Conclusion: **transmit** (spatial reuse). *(In practice 802.11 still often defers, but the mechanism in principle distinguishes exposed nodes.)*

### E17 — Key insight on spatial location of collisions; why it motivates receiver-based control.
**Answer:** **Collisions are spatially located at the *receiver*, not the transmitter.** Two transmissions only "collide" where they **overlap at a receiver** trying to decode one of them. Since the **sender can't observe its own receiver's environment**, sender-side carrier sense is fundamentally insufficient. The fix must be **anchored at the receiver**: the receiver issues a **CTS** that **silences nodes near it** (those that could corrupt its reception). This is the rationale for **receiver-based collision control (RTS/CTS/NAV)**.

#### 4.5 Provisioned MAC Protocols

### E18 — TDMA round structure; 6-station net, only 1,3,4 active — draw allocation & wasted slots.
**Answer:** A **TDMA round** divides time into a **fixed sequence of slots**, **one per station**, repeating each frame. *(Six slots:)*

| Slot | 1 | 2 | 3 | 4 | 5 | 6 |
|---|---|---|---|---|---|---|
| Owner | S1 | S2 | S3 | S4 | S5 | S6 |
| Status | **used** | **WASTED** | **used** | **used** | **WASTED** | **WASTED** |

Only S1, S3, S4 have data → **slots 2, 5, 6 sit idle** but **still reserved** (no one else may use them). **Inefficiency:** **fixed allocation wastes the unused slots** even when other stations are backlogged.

### E19 — "Out-of-band" mechanism in TDMA: what, why, overhead.
**Answer:** **Out-of-band signaling** is a **separate control channel** (apart from the data slots) used to **assign slots, synchronize clocks, and coordinate** which station owns which slot. It's **necessary** because TDMA isn't automatic — stations must **agree on the schedule and stay time-aligned**. **Overhead:** consumes **extra spectrum/resources** for signaling, adds **coordination delay and complexity**, and requires **tight synchronization** — costs that contention protocols avoid.

### E20 — FDMA; frequency-vs-time diagram for 6 stations, 3 active — wasted bands & guard bands.
**Answer:** FDMA gives each station its **own frequency band** for **all time**. *(Six horizontal bands stacked in frequency; only 3 carry signal.)*

| Band | f1 | f2 | f3 | f4 | f5 | f6 |
|---|---|---|---|---|---|---|
| Status | used | **idle** | used | **idle** | used | **idle** |
| Between bands | ↔ **guard band** ↔ (every adjacent pair) |

**Wasted:** the **3 idle bands** are reserved but unused; additionally, **guard bands** between every pair are **permanently unusable spectrum** (prevent adjacent-channel interference). **Inefficiency:** idle bands **can't be reused**, and guard bands cost spectrum.

### E21 — Compare TDMA vs FDMA (resource divided, guaranteed access, idle waste, coordination, fading).
**Answer:**

| Attribute | TDMA | FDMA |
|---|---|---|
| Resource divided | **Time** slots | **Frequency** bands |
| Guaranteed access | Yes (own slot) | Yes (own band) |
| Idle-resource waste | Unused **slots** wasted | Unused **bands** wasted |
| Coordination overhead | **High** (time sync, slot scheduling) | Lower (set frequencies, but guard bands) |
| Robustness to fading | A whole slot can hit a **deep fade** | A band can sit in a **frequency-selective fade** |
| Extra cost | Guard **times** + sync | Guard **bands** (wasted spectrum) |

### E22 — TDMA vs contention for real-time voice, 20 users — recommend & why.
**Answer:** **Recommend TDMA (provisioned).** Real-time voice needs **bounded, predictable delay and guaranteed bandwidth**; with a **fixed, modest user count (20)** and **steady periodic traffic**, TDMA's **dedicated slots** deliver **collision-free, low-jitter** delivery. Contention (CSMA/CA) suffers **variable delay and collisions under load**, hurting voice QoS. **Trade-off accepted:** some slot waste during silence + sync overhead, in exchange for **QoS guarantees**. *(If traffic were bursty/sparse, contention would win.)*

#### 4.6 Spatial Reuse and Carrier-Sense Thresholds

### E23 — Explain spatial reuse; when concurrent vs take turns.
**Answer:** **Spatial reuse** = letting **spatially separated links use the same channel simultaneously** because their signals **don't reach each other's receivers**. **Transmit concurrently when:** the two links are **far enough apart** that neither transmitter interferes at the other's **receiver** (e.g., the exposed-terminal pair). **Take turns when:** the links are **close** so their signals **overlap at a common/nearby receiver** (e.g., the hidden-terminal pair). The deciding factor is **interference at the receiver**, not at the transmitter.

### E24 — Two topologies: CS enables correct concurrency vs CS forces unnecessary deferral.
**Answer:**
- **(a) CS works correctly (far-apart pairs):** A↔B and far-away X↔Y. Each transmitter senses **only its own neighborhood**; they **don't hear each other**, so they **transmit concurrently — correctly** (no receiver overlap). CS gives the right answer.
- **(b) CS over-defers (exposed terminal):** A—B—C—D linear. B→A active; C wants C→D. C **hears B** and **defers**, although C→D wouldn't collide (D is away from A). Here CS forces **unnecessary deferral** (false-busy). **Difference:** CS keys on **transmitter-side audibility**, which is right for far-apart pairs but **wrong for exposed terminals**, where the collision criterion is **receiver-side**.

### E25 — "Thresholded correlation value" in carrier sense; how it decides occupancy.
**Answer:** A receiver **correlates** the incoming waveform against the **known signal structure (e.g., preamble/PN sequence)**, producing a **correlation value** measuring how strongly a valid signal is present. This value is compared to a **threshold (e.g., the CCA energy/correlation level)**: **above threshold → medium "busy"**; **below → "idle."** Correlation (vs raw energy) lets the radio **distinguish a real 802.11 signal from noise**, giving a robust **busy/idle** decision for carrier sense.

### E26 — Advantages of one wide shared channel (e.g., 100 MHz) vs narrow dedicated channels.
**Answer:** A **single wideband shared channel** offers:
1. **Robustness to multipath/frequency-selective fading** — a fade hits only part of the wide band; the rest survives (vs a narrow channel that can be **entirely faded out**).
2. **Dynamic/statistical sharing** — any station can grab the **whole bandwidth when free** (bursty traffic gets high peak rates), instead of being capped at a small fixed band.
3. **Spatial reuse** — far-apart links reuse the same wide channel concurrently.
4. **No guard-band waste / rigid pre-allocation**. *Cost:* needs **contention/coordination** to arbitrate the shared resource.

### — Part B: SAMPLE QUESTIONS —

#### 5.1 Short Questions

### S1 — Define CSMA; expand the acronym.
**Answer:** **Carrier Sense Multiple Access** — stations **sense** the channel (Carrier Sense) before transmitting on a **shared** medium used by **many** stations (Multiple Access), transmitting only if it senses idle.

### S2 — Why 802.11 uses collision avoidance, not detection.
**Answer:** Wireless radios **can't listen while transmitting** (own signal ~10⁶× stronger → no fate sharing), and **hidden terminals + fading** hide collisions from the sender. So detection is infeasible; 802.11 **avoids** collisions (backoff) and confirms success via **ACK**.

### S3 — "Fate sharing of the link" — what & which network.
**Answer:** All nodes experience the **same channel state**, so a collision is **visible to everyone including the transmitter**. Applies to **wired networks (CSMA/CD Ethernet)**; it does **not** hold in wireless.

### S4 — Name the four CSMA/CA control/data frames.
**Answer:** **RTS → CTS → DATA → ACK.**

### S5 — What does absence of an ACK signal?
**Answer:** The sender infers the frame was **lost or collided** → it **retransmits** (with exponential backoff).

### S6 — Hidden terminal problem in one sentence.
**Answer:** Two transmitters out of each other's range transmit to a common receiver and **collide at that receiver**, undetected by either sender.

### S7 — Exposed terminal problem in one sentence.
**Answer:** A station **needlessly defers** because it hears a nearby sender, even though its own transmission (to a different, far receiver) **wouldn't have collided**.

### S8 — In RTS/CTS, which frame makes a hidden terminal defer? Why.
**Answer:** The **CTS** (from the receiver). The hidden node hears the receiver's CTS and **sets its NAV to defer**, because it lies near the receiver (where the collision would occur) even though it can't hear the sender.

### S9 — Why can an exposed terminal safely transmit even after hearing an RTS?
**Answer:** Hearing **RTS but no CTS** means its receiver is **out of range of the protected receiver**, so concurrent transmission **won't collide** — it's safe to use **spatial reuse**.

### S10 — TDMA: one advantage, one disadvantage.
**Answer:** **+** Guaranteed, **collision-free** access (good for real-time). **−** **Wastes idle slots** and needs **tight time sync/coordination**.

### S11 — FDMA: one advantage, one disadvantage.
**Answer:** **+** Each user gets a **dedicated band**, simultaneous & collision-free. **−** **Idle bands wasted** and **guard bands** consume spectrum; can't grab unused bands.

### S12 — Key insight on where collisions are located.
**Answer:** **At the receiver, not the transmitter** — which is why receiver-anchored control (CTS/NAV) is needed.

### S13 — Define spatial reuse; one example.
**Answer:** Spatially separated links using the **same channel at the same time** without interfering. *Example:* the **exposed-terminal** pair (B→A and C→D) transmitting concurrently because their receivers are far apart.

### S14 — What is virtual carrier sense and how is it provided?
**Answer:** A **logical busy indication via the NAV**, set from the **duration field in RTS/CTS** frames; stations defer for that duration **without hearing the actual data** — provided by the **RTS/CTS** exchange.

#### 5.2 Descriptive Questions

### S15 — Why CSMA/CD can't be applied in wireless (hidden terminal, fading, hardware).
**Answer:** Three barriers:
1. **Hardware (no fate sharing):** a radio's **own transmission swamps its receiver (~10⁶×)**, so it **can't listen while transmitting** → can't detect a remote collision. Wireless is effectively **half-duplex**.
2. **Hidden terminal:** the collision happens **at the receiver**, possibly caused by a sender the first transmitter **can't hear** → invisible to the sender.
3. **Fading:** received strength **fluctuates**; "I hear nothing" doesn't guarantee the channel is clear **at the receiver**, so sensing is unreliable.
Because the transmitter and receiver **don't share fate**, detection at the sender is impossible → 802.11 uses **CSMA/CA + ACK + RTS/CTS** instead.

### S16 — Complete RTS/CTS mechanism (diagram); hidden fix, exposed partial fix, trade-offs.
**Answer:**
**Sequence (diagram in words):** `A —RTS→ B` (A reserves) → `B —CTS→ A` (and heard by neighbors of B) → `A —DATA→ B` → `B —ACK→ A`. RTS and CTS carry a **duration** that sets neighbors' **NAV**.
- **Solves hidden terminal:** the **CTS reaches nodes near B** (including the hidden node), making them **defer** for the data duration → no collision at B.
- **Partially addresses exposed terminal:** a node hearing **RTS-only (no CTS)** can in principle infer it's **exposed** and transmit concurrently — but standard 802.11 often still defers, so the fix is **incomplete**.
- **Trade-offs:** **overhead** of two extra frames + SIFS gaps (bad for small packets); benefits dominate for **large packets / hidden-terminal-prone** networks → hence the **RTS threshold** (use RTS/CTS only above a packet-size threshold).

### S17 — Hidden vs exposed terminal (diagrams): cause, consequence, RTS/CTS solution.
**Answer:**

| | Hidden Terminal | Exposed Terminal |
|---|---|---|
| Topology | A—B—C (A,C → B; A,C can't hear each other) | A—B—C—D (B→A; C→D) |
| Cause | Senders **can't hear each other** → both send to B | Sender **hears a neighbor** and defers though receivers differ |
| Sensing error | **False idle** | **False busy** |
| Consequence | **Collision at receiver B** (lost data) | **Wasted opportunity** (lost throughput) |
| RTS/CTS fix | **CTS** makes hidden node defer → **solved** | **RTS-only (no CTS)** signals safe to send → **partially solved** |

### S18 — Spatial reuse: far-apart concurrent vs nearby take-turns; how CS enforces it & when it fails.
**Answer:** **Spatial reuse** maximizes capacity by reusing the channel across space. **Far-apart links transmit concurrently** because neither reaches the other's **receiver** (no collision). **Nearby links take turns** because their signals **overlap at a shared/close receiver**. **Carrier sensing enforces this** by making a station defer when it **hears** an ongoing transmitter nearby (so close links serialize). **It fails** in two ways: **hidden terminals** (CS says idle but a collision occurs at the receiver — under-deferral) and **exposed terminals** (CS says busy but concurrency was safe — over-deferral). CS keys on **transmitter audibility**, while the real criterion is **interference at the receiver**.

### S19 — Role of link-layer ACKs in 802.11; necessity & limitation re hidden terminal.
**Answer:** **Role:** the receiver returns an **ACK (after SIFS)** to confirm correct receipt; **no ACK ⇒ sender assumes loss ⇒ retransmit**. **Necessity:** since the sender **can't detect collisions**, the ACK is the **only reliable success signal**, providing link-layer reliability and an implicit collision indicator. **Limitation:** ACKs are **reactive** — they confirm *after* a (possibly collided) transmission, so they **don't prevent** hidden-terminal collisions; they only let the sender **recover** by retransmitting (wasting the failed transmission). **Prevention** still needs **RTS/CTS**.

#### 5.3 Analysis and Design Questions

### S20 — Warehouse: forklifts on opposite sides of metal shelving, common AP — MAC problem & fix.
**Answer:** **Problem = hidden terminal.** The **metal shelving blocks** the forklifts from hearing each other, but both reach the **central AP**; their simultaneous uplinks **collide at the AP**, undetected by either forklift → repeated losses/retransmissions. **Fix with RTS/CTS:** a forklift sends **RTS** to the AP; the **AP's CTS is heard by both forklifts** (both are in AP range), so the **other forklift sets its NAV and defers** for the data duration → **no collision at the AP**. The receiver-anchored CTS overcomes the blocked sender-to-sender path.

### S21 — Linear A–B–C–D (each hears only neighbours); B→A and C→D simultaneously.
**Answer:**
- **(a) Collision?** **No.** B→A's receiver is **A**; C→D's receiver is **D**. A and D are **far apart** and each receiver hears only its intended sender → **no overlap at either receiver**. This is the **exposed-terminal** geometry; concurrency is **safe**.
- **(b) Will plain CSMA prevent C?** **Yes (wrongly).** C **hears B's transmission** (B is C's neighbor) and senses **busy**, so plain CSMA makes C **defer unnecessarily** — lost throughput.
- **(c) RTS/CTS handling:** C hears B's **RTS** but **no CTS from A** (A is out of C's range). Hearing **RTS-without-CTS** indicates C is an **exposed terminal**, so in principle C **may transmit to D concurrently**, restoring spatial reuse. *(Caveat: many real 802.11 implementations still defer; the mechanism nonetheless distinguishes the case.)*

### S22 — RTS/CTS for all packets vs only large packets — when is the overhead justified?
**Answer:** RTS/CTS adds **fixed overhead** (RTS+CTS+two SIFS) per transmission.
- **For small packets:** the handshake can **cost as much as the data** → **net loss**; better to send directly.
- **For large packets:** the handshake is **small relative to the data**, and it **caps collision cost to the tiny RTS** → **net win**.
**Overhead is justified when:** packets are **large**, **and/or hidden terminals are present**, **and/or the network is congested** (high collision probability). 802.11 captures this with an **RTS threshold**: use RTS/CTS **only above a configured packet size**. *Rule:* **big packets / hidden terminals / high load → RTS/CTS on; small packets / clean topology → off.**

### S23 — Dense IoT, short infrequent packets: provisioned (TDMA/FDMA) vs contention (CSMA/CA)?
**Answer:** **Recommend contention-based CSMA/CA.** Reasoning by the four criteria:
- **Channel utilization:** traffic is **sparse/bursty**; provisioned slots/bands would sit **mostly idle (wasted)**, whereas CSMA/CA uses the channel **on demand** → higher utilization.
- **Coordination overhead:** TDMA/FDMA need **scheduling + tight synchronization** across **many** nodes (out-of-band signaling) — heavy for a **dense** network; CSMA/CA is **distributed**, needing none.
- **Latency:** for **infrequent** packets, CSMA/CA usually grabs an idle channel **immediately**; TDMA forces a node to **wait for its slot** even when nothing else is sending.
- **Energy:** CSMA/CA lets nodes **sleep and wake to send**, avoiding the **always-on synchronization** TDMA demands → better battery life.
**Caveat:** if the network became **dense *and* heavily, periodically loaded**, contention collisions would rise and a **scheduled/hybrid** approach would become attractive. For **sparse, short, infrequent** IoT traffic, **CSMA/CA wins**.

---

## 3. Conceptual Deep Dive

**The whole lecture hangs on one sentence:** *collisions are spatially located at the receiver, not the transmitter.* Internalize this and every other idea falls out.

**Why CD works on wire but not air — the fate-sharing story.** On a wire, every node reads the **same** signal level (**fate sharing**), so a transmitter listening to the wire **sees the collision**. In air, a transmitter is **deafened by its own signal** (~10⁶× stronger) and its receiver-side environment differs from a distant receiver's — **no fate sharing** — so the sender is blind to the collision. The collision lives **at the receiver**, somewhere the sender can't observe.

**CSMA/CA = avoid + confirm.** Can't detect? Then (1) **avoid** collisions by sensing + **random backoff** (so two waiting stations rarely fire together), and (2) **confirm** success with an **ACK** (the receiver reports for you). Backoff spreads contenders in time; ACK closes the loop.

**RTS/CTS = move control to the receiver.** Since the danger zone is around the **receiver**, let the **receiver speak**: its **CTS silences its own neighbors** (the would-be colliders), including **hidden** nodes the sender can't reach. The **duration field → NAV** is **virtual carrier sense**: stations defer because they were *told* the channel is reserved, not because they *hear* the data. This is the elegant core of 802.11.

**Hidden vs exposed — two opposite sensing errors.** Hidden = **false idle** (CS misses a real collision → under-defer → lost data). Exposed = **false busy** (CS sees a harmless transmitter → over-defer → lost throughput). RTS/CTS **fully** fixes hidden (CTS) and **partially** fixes exposed (RTS-without-CTS).

**Two access philosophies.** **Contention** (CSMA/CA): no schedule, sense-and-compete — great for **bursty/sparse/many** nodes, but collisions under load. **Provisioned** (TDMA/FDMA/CDMA): pre-assigned time/frequency/code — **guaranteed, collision-free** for **steady/real-time** traffic, but **wastes idle resources** and needs **coordination/sync**. **CDMA** is special: **everyone shares time *and* frequency**, separated by **codes**, gaining fading robustness.

**Spatial reuse ties it together.** The art is concurrency where safe (far links) and turns where necessary (near links). Carrier sense approximates this but misjudges the hidden/exposed edge cases — which is exactly why receiver-based RTS/CTS exists.

**Where students get confused.** Saying the collision is "between the transmitters" (it's **at the receiver**); thinking RTS/CTS *fully* solves the exposed problem (only **partial**); mixing up hidden (false-idle) with exposed (false-busy); forgetting **SIFS < DIFS** is what gives ACK/CTS priority; assuming TDMA is always better (only for steady/real-time traffic).

---

## 4. Important Exam Pointers
- **The flagship line:** *"Collisions are spatially located at the receiver, not the transmitter."* Quote it — it justifies RTS/CTS.
- **Four frames in order: RTS → CTS → DATA → ACK.** Know who hears each and who defers (CTS silences hidden nodes).
- **CSMA/CD vs CSMA/CA table** is near-guaranteed — include hardware (listen-while-transmit) and "fate sharing."
- **Hidden vs exposed:** false-**idle** (collision/lost data) vs false-**busy** (wasted throughput); CTS fixes hidden, RTS-only flags exposed.
- **TDMA/FDMA/CDMA comparison** — resource divided, guarantee, waste, coordination, fading robustness.
- **Design questions:** real-time/steady → **provisioned (TDMA)**; bursty/sparse/dense IoT → **contention (CSMA/CA)**. Always justify with utilization, latency, overhead, energy.
- **RTS threshold logic:** RTS/CTS pays off for **large packets / hidden terminals / high load** only.
- **Draw the A–B–C(–D) topologies** and the **DIFS→backoff→DATA→SIFS→ACK** timeline.

## 5. Commonly Forgotten Points
- **The collision is at the RECEIVER.** The #1 conceptual marking point.
- **"No fate sharing" + ~10⁶× self-signal** is the precise reason CD fails (not just "radios are simple").
- **CTS (not RTS) makes the hidden node defer;** **RTS-without-CTS** flags the exposed node.
- **RTS/CTS only PARTIALLY solves the exposed terminal;** it **fully** solves hidden.
- **Virtual carrier sense = NAV**, set by the **duration field**, not by hearing data.
- **SIFS < DIFS** gives ACK/CTS priority over new contention (ties to Lecture 5).
- **TDMA wastes idle *slots*; FDMA wastes idle *bands* + *guard bands*.**
- **CDMA shares the same time AND frequency** (code-separated) — unlike TDMA/FDMA.
- **ACKs are reactive** (recover), not preventive — they don't stop hidden-terminal collisions.

## 6. Tips and Tricks
- **Frame order mnemonic "R-C-D-A":** **R**eady? **C**lear! **D**ata… **A**ck. (RTS, CTS, DATA, ACK.)
- **Hidden vs Exposed:** **Hidden = "I didn't hear, so I crashed"** (false idle); **Exposed = "I heard, so I hid"** (false busy).
- **Who defers?** *"CTS covers the receiver's crowd"* (silences hidden nodes near the receiver).
- **Fate sharing test:** *can the sender hear the collision? Wire = yes (CD); Air = no (CA).*
- **Provisioned vs contention:** *steady & scheduled → slots; bursty & spontaneous → sense.*
- **TDMA vs FDMA waste:** *TDMA wastes Time, FDMA wastes Frequency (+ guard bands).*
- **RTS/CTS worth it?** *Only when the data is big or the terminal is hidden.*

## 7. Formula Cheat Sheet / Key Reference

*(Lecture 4 is mechanism-based; memorize relationships, sequences, and the comparison matrix.)*

### Core sequences & rules
| Item | Detail |
|---|---|
| CSMA/CA success timeline | `DIFS → (random backoff) → DATA → SIFS → ACK` |
| Four-frame exchange | `RTS → CTS → DATA → ACK` |
| Virtual carrier sense | **NAV** set from **duration field** in RTS/CTS |
| ACK rule | **No ACK within timeout ⇒ assume collision ⇒ retransmit** |
| Carrier-sense decision | **correlation value > threshold ⇒ busy**, else idle |
| Key insight | **Collision location = receiver** |

### Hidden vs Exposed
| | Hidden | Exposed |
|---|---|---|
| Sensing error | false **idle** | false **busy** |
| Result | collision at receiver (lost data) | wasted opportunity (lost throughput) |
| Trigger frame for fix | **CTS** → defer | **RTS-only** → safe to send |
| RTS/CTS outcome | **fully solved** | **partially solved** |

### Provisioned MAC matrix
| | TDMA | FDMA | CDMA |
|---|---|---|---|
| Divides by | time slots | frequency bands | codes (shared time+freq) |
| Guaranteed access | yes | yes | yes (soft) |
| Idle waste | unused slots | unused bands + guard bands | minimal |
| Coordination | high (time sync) | medium (guard bands) | power control / codes |
| Fading robustness | low (slot in fade) | low (band in fade) | **high** (spread spectrum) |

### Design heuristics
| Situation | Choose |
|---|---|
| Real-time, steady, fixed users (voice) | **TDMA/provisioned** |
| Bursty, sparse, dense, infrequent (IoT) | **CSMA/CA/contention** |
| Large packets / hidden terminals / high load | **RTS/CTS on** |
| Small packets / clean topology | **RTS/CTS off** |

> **One-line summary:** Wireless can't detect collisions (no fate sharing), so it **avoids** them (sense + random backoff), **confirms** with **ACK**, and **protects the receiver** with **RTS/CTS/NAV** — because *the collision is always at the receiver.*
