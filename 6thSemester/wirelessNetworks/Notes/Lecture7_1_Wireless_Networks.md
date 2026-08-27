# CSE 4615 — Lecture 7.1 (MAC Efficiency Boost: Frequency-Domain Backoff / Back2F): Complete Answer Key

**Course:** CSE 4615/4616 Wireless Networks, IUT
**Scope:** Every exercise in Section 4 and every sample question in Section 5 of the uploaded study guide.

## How to read this document

Facts and worked numbers are grounded directly in the Lecture 7.1 slide deck. Where I've added reasoning or framing the slides don't spell out explicitly, it's marked 💡. Two things worth flagging up front:

- **Q5(c)**: the raw payload formula (L×8/R) gives **222.22 µs** for a 1500-byte frame at 54 Mbps, while the "Topics Covered" section of your guide separately quotes the lecture's own rounded figure of **"~250 µs."** Both are correct — 222.22 µs is the exact math the exercise asks for; ~250 µs is the lecture's informal rounding (likely folding in PLCP preamble/header overhead the pure payload formula doesn't capture). I use 222.22 µs wherever the exercise explicitly asks you to compute it, and note the ~250 µs figure separately where the guide's own text uses it.
- Several exercises (**26** in Section 4.4, and **26** in Section 5.3, which reuses the same number) are "design your own" problems with no fixed numeric answer. I've worked a clean illustrative instance for each so you can see the method, clearly labeled as my own construction — swap in your own numbers and redo the same steps.

---

## Quick Reference

| Quantity | Value |
|---|---|
| 1500-byte frame @ 54 Mbps (raw payload) | 222.22 µs |
| Average temporal (802.11) backoff | ≈ 100 µs |
| OFDM subcarriers | 48, indexed 0–47 |
| One frequency-backoff round | 1 OFDM symbol = 4 µs |
| Winner rule | lowest-indexed active subcarrier |
| Rank formula | rank = 1 + (# active subcarriers with strictly smaller index) |
| 802.11a slot | 9 µs |

---

# Part A — Exercises (Study Guide Section 4)

## 4.1 802.11 Temporal Backoff Review (with Numericals)

**1. S1 (B1=15), S2 (B2=25), simultaneous DIFS finish.**
(a) **S1 transmits first** (15 < 25).
(b) While S1 counts its 15 slots down to 0, S2 is counting down the same real time, so it also drops by 15: **S2's remaining backoff = 25 − 15 = 10.**
(c) After S1's Data+ACK and a fresh DIFS, S1 draws a new B1 = 18, while S2 resumes from its frozen 10. **S2 wins the second round** (10 < 18), transmitting **after 10 slots.**

**2. S1's remaining backoff when S2 transmits.**
(a) While S2 counts its remaining 10 down to 0, S1's fresh draw of 18 also drops by 10 in that same real time: **S1's remaining = 18 − 10 = 8.**
(b) This matches the slide's own **B1 = 8** — confirmed by direct counting.

**3. Idle time wasted, both rounds, plus DIFS.**
Round 1 idle = 15 slots × 9 µs = **135 µs.** Round 2 idle = 10 slots × 9 µs = **90 µs.** Two DIFS periods = 2 × 34 = **68 µs.**
**Total contention overhead = 135 + 90 + 68 = 293 µs.**

**4. Three stations draw 4, 4, 11.**
(a) After 4 slots, the two stations that drew **4** both hit 0 simultaneously → **collision**; the third station (11) has counted down to **11 − 4 = 7.**
(b) The two colliding stations draw fresh random backoffs and re-contend; the third station simply **continues counting down from its remaining value (7)** — it wasn't involved in the collision, so its progress isn't reset.
(c) This is exactly the failure mode that motivates a "everyone can see all chosen values" mechanism: in plain time-domain backoff, colliding stations only discover the collision indirectly (missing ACK, after wasting a full data-frame time), and non-colliding stations never learn *what* values anyone drew — they only sense "busy." A scheme where every station directly observes every chosen backoff value (as Back2F allows) removes this blindness entirely.

**5. 1500-byte frame @ 54 Mbps.**
(a) Tdata = (1500×8)/(54×10⁶) = 12000/54,000,000 ≈ **222.22 µs.**
(b) η = Tdata/(Tdata+100) = 222.22/322.22 ≈ **68.97%** (i.e., ≈31.03% overhead from backoff alone).
(c) The lecture's "~35% overhead at 54 Mbps" figure is **larger** than the 31.03% backoff-only overhead computed here, because the lecture's total includes **DIFS, SIFS, ACK, and header overhead in addition to** the backoff — so 31% is a subset (backoff alone) of the full ~35% total overhead, not a contradiction.

**6. Repeat for a 200-byte frame.**
Tdata = (200×8)/(54×10⁶) ≈ **29.63 µs.**
η = 29.63/(29.63+100) ≈ **22.86%.**
Efficiency collapses as the frame shrinks (from ~69% down to ~23%), because the 100 µs backoff overhead is essentially **fixed per packet** regardless of packet size — it doesn't shrink along with the data. 💡 This is exactly why VoIP-style traffic (many small packets) suffers disproportionately under 802.11's per-packet contention: the fixed overhead dominates far more when there's less actual data to amortize it over.

## 4.2 From Time Domain to Frequency Domain (Conceptual)

**7. "Backoff is not fundamentally a time-domain operation."**
Backoff's real purpose is **randomized ordering** — giving contending stations a way to resolve who goes first without prior coordination, spreading collision probability thin. Time-domain counting (idle slots) is just **one implementation** of that randomization. Since the actual goal is randomized ordering, not "waiting" per se, that goal can be realized in **any domain that supports comparably random, orderable choices** — including frequency (which subcarrier you pick).

**8. The MAC opportunity Back2F extracts.**
OFDM's 48 narrowband subcarriers exist for a **purely PHY reason** (robustness to frequency-selective fading) — nothing to do with MAC contention. Back2F's opportunity is to **repurpose this existing PHY resource**: treat the 48 subcarriers as integers and let a station's random backoff draw map directly onto "which subcarrier do I signal on," turning an unrelated PHY feature into a fast MAC-layer contention-resolution tool.

**9. Number of subcarriers; Back2F's reinterpretation.**
**48 subcarriers.** Back2F reinterprets them as **integers 0–47**, so a station's random backoff choice becomes "which subcarrier do I transmit on" instead of "how many time slots do I wait."

**10. Why time-domain backoff wastes idle time and frequency-domain doesn't.**
Time-domain backoff's "waiting" **is literally implemented as not transmitting** for that many slots — the channel sits genuinely idle and unusable for that whole duration. Frequency-domain backoff avoids this because the entire randomized-ordering exchange happens within **a single OFDM symbol (4 µs)**: every station signals its choice and listens for everyone else's simultaneously, resolving the whole contention almost instantly instead of spreading it across many serial time slots.

## 4.3 Back2F Main Idea and Rank Determination (with Numericals)

**11. Two simultaneous roles; why two antennas.**
A station must **transmit** its own chosen subcarrier (signaling its backoff value) and **listen** for every other station's chosen subcarrier, at the same time, within the same OFDM symbol. A single antenna operating in normal half-duplex mode can't send and receive simultaneously, so this requires (at least conceptually) **two separate antennas** — one dedicated to transmitting, one dedicated to listening.

**12. S1 picks 6, S2 picks 18.**
**S1 wins** (6 < 18). Both stations know this without any coordinator because each one's **listen antenna directly observes the full active set {6, 18}** in that single symbol — S1 sees itself is the lowest and knows it won; S2 sees the same set and knows 18 isn't the lowest, so it knows it lost. No announcement or central arbiter is needed.

**13. Four stations pick {31, 4, 22, 4} (A, B, C, D).**
(a) **No station wins outright** — the lowest subcarrier (4) is held by **two** stations (B and D), so there's a tie right at the top.
(b) **B and D are tied at subcarrier 4.** This can't be resolved within the same round because their combined RF energy on subcarrier 4 looks the same to every listener whether it's one station or two transmitting there — it's a genuine collision, just realized in frequency rather than time.
(c) A **second round of contention** must occur between B and D: each redraws a fresh random subcarrier, and the lower of their two new picks wins the tie. (C at 22 and A at 31 already have unambiguous relative order and simply slot in after whichever of B/D wins.)

**14. Why "lowest wins" rather than highest or some other rule.**
The specific direction (lowest vs. highest) **doesn't matter conceptually** — what matters is that it's a single, fixed, universally-known convention that every station applies identically. As long as everyone uses the *same* rule, each station can independently compute the same rank from the same observed active set, with no need for negotiation. "Lowest wins" and "highest wins" are symmetric choices; either would work equally well.

**15. S1=6, S2=18, simultaneous transmit+listen.**
(a) S1's listen antenna observes the **full active set {6, 18}**.
(b) S2's listen antenna observes the **same set {6, 18}**.
(c) **S1 wins** (lowest = 6). Crucially, **S2 also directly knows it lost** — and knows exactly what beat it (subcarrier 6 was active). Contrast with time-domain backoff: a losing station there only observes "channel busy" via CCA — it learns nothing about who won, what value they had, or its own precise rank; it just knows it isn't its turn and must defer blind.

**16. Five APs at {3, 7, 12, 29, 44}.**
(a) Rank of the AP at 12: rank = 1 + |{3,7}| = **Rank 3.**
(b) AP at 44: rank = 1 + |{3,7,12,29}| = 1+4 = **Rank 5** — it transmits **last** (5th) in the TDMA order.
(c) If a 6th AP joins at subcarrier 0: since 0 is now lower than everyone, **every existing AP's rank increases by exactly 1** (rank1→2, 2→3, 3→4, 4→5, 5→6), and the new AP at 0 becomes **Rank 1.**

**17. AP transmits on 12, hears {2, 8, 12, 27, 40}.**
Rank = 1 + |{2,8}| = 1+2 = **Rank 3** — confirmed, matching the slide's stated "Rank in TDMA: 3."
**General rule:** rank = 1 + (number of active subcarriers with a strictly smaller index than your own).

**18. One round = 4 µs.**
(a) Single round, 3-station schedule: contention time = **4 µs.**
(b) Two rounds (with collision resolution): **8 µs.**
(c) Versus three separate 802.11 contentions at ≈100 µs each = **300 µs.** Even the 2-round Back2F case (8 µs) is roughly **37.5× faster** than three separate 802.11 contentions.

**19. Tdata = 250 µs/packet, 3 packets.**
(a) 802.11 per-packet: 3×(100+250) = **1050 µs.**
(b) Back2F, one 4 µs round for the whole schedule: 4 + 3×250 = **754 µs.**
Time saved ≈ (1050−754)/1050 ≈ **28.2%**, equivalently throughput rises by about **39%** (1050/754 ≈ 1.39×). This is below the lecture's "up to 50%" headline figure — reasonable, since with only k=3 packets the fixed 4 µs startup cost hasn't fully amortized yet (see Q20, where the advantage keeps growing with k).

**20. General efficiency formulas, k=1,3,10, Tdata=250 µs.**
η₈₀₂.₁₁(k) = Tdata/(Tdata+100) — **independent of k**, since 802.11 re-pays the 100 µs overhead every single packet. = 250/350 ≈ **71.43%**, constant for all k.
ηB2F(k) = (k·Tdata)/(4 + k·Tdata):
- k=1: 250/254 ≈ **98.43%**
- k=3: 750/754 ≈ **99.47%**
- k=10: 2500/2504 ≈ **99.84%**
As **k → ∞**: η₈₀₂.₁₁ stays flat forever at ≈71.4% (every packet pays the same fixed tax), while **ηB2F → 100%** (the one-time 4 µs cost gets amortized into insignificance over an ever-larger schedule).

## 4.4 Frequency-Domain Collisions and the Second Round (with Numericals)

**21. Red and green both choose subcarrier 1; three others choose 3, 4, 5.**
(a) Neither red nor green can detect the collision **by itself** during round 1, because from each one's own listen-antenna perspective, subcarrier 1 simply reads as "active" — the two stations' RF energy combines on that one subcarrier, and there's no way to tell from signal presence alone whether it's one transmitter there or two.
(b) The **second round** resolves it: only the tied pair (red, green) re-contend, each independently drawing a fresh subcarrier from a reduced set; whichever lands lower wins the tie.
(c) If they collide **again** in round 2, a further round would be needed, repeating the same tie-break — in principle this can continue for multiple rounds, though the chance of a repeat collision shrinks each time.

**22. Collision probabilities, uniform redraw over 48 subcarriers.**
(a) P(collide again in round 2) = **1/48 ≈ 2.08%.**
(b) P(collide in **both** rounds, independent draws) = (1/48)×(1/48) = **1/2304 ≈ 0.043%.**
(c) The key qualitative difference: a **time-domain** collision is only discovered after wasting a **full failed data transmission** (hundreds of µs, waiting for a missing ACK). A **frequency-domain** collision is discovered within **one OFDM symbol (4 µs)** — before any real data is even sent. So even though frequency-domain collisions aren't necessarily rarer (see below), each one costs vastly less to detect and recover from.

*P(no collision) among N stations over K=48 subcarriers:*
For **N=5**: P = ∏ᵢ₌₀⁴ (48−i)/48 = 1 × 0.9792 × 0.9583 × 0.9375 × 0.9167 ≈ **0.806** → ≈19.4% chance of at least one collision.
For **N=10**: continuing the product through i=9 gives P(all distinct) ≈ **0.366** → **≈63.5% chance of at least one collision.**
💡 This is worth pausing on: it's actually **higher** than the "10 time-domain contenders exceed 40% collision probability" figure from Lecture 6.1 — with only 48 "slots" to spread 10 contenders across, frequency-domain collisions aren't inherently rarer in raw probability (this is a birthday-paradox effect). The reason Back2F still wins overall isn't lower collision probability — it's that **each individual collision is vastly cheaper to detect and resolve** (4 µs vs. a full wasted data frame).

**23. Why "only winners in round 2" often makes TDMA ineffective; the proposed fix.**
If round 2 admits only the bare-minimum tied stations, you spend a whole extra 4 µs round to resolve just one small ambiguous pair, while every other already-unique winner sits outside the process entirely — a poor overhead-to-benefit trade that barely extends the usable ranked schedule. The lecture's fix ("Optimize for TDMA") is to admit **a few more stations than strictly necessary** — the tied pair *plus* the next couple of already-unique low-subcarrier winners — into round 2, so that one extra round resolves a **longer, more useful prefix** of the final TDMA order in a single pass, while the remaining higher-subcarrier winners (already unambiguous relative to everyone) simply get appended afterward without needing to re-contend.

**24. Purple→Rank1, red→Rank2, green→Rank3 (round-2 markers 0, 2, 4).**
From the slide diagram: the tied pair (red, green, originally both at subcarrier 1) **plus** the single round-1 winner at subcarrier 3 (purple) all advance to round 2. Each of these three independently re-picks a **new** subcarrier from the reduced set {0, 2, 4}: purple picks 0, red picks 2, green picks 4. Applying the **same lowest-wins rule** within round 2 to just these three re-picks gives: purple (0) → **Rank 1**, red (2) → **Rank 2**, green (4) → **Rank 3**. Their final rank depends entirely on their round-2 pick — their original round-1 subcarrier value no longer matters once round 2 has fully disambiguated them.

**25. Minimum stations needed for a meaningful round 2.**
The strict minimum is **2** — you need at least a tied/ambiguous pair to have anything worth resolving; a "round 2" with only 1 station is already unambiguous and pointless to re-run. 💡 In the lecture's specific example, the tie itself only strictly requires the 2 originally-colliding stations (red, green); admitting the 3rd station (purple) is a deliberate design choice to extend the usefully-resolved prefix, not a strict requirement of the tie-break itself.

## 4.5 Scheduled TDMA Transmission and Channel Utilization

**26. "Only a Few Stations in Second Round" — why "TDMA will not be effective."**
If round 2's participation is restricted to the bare-minimum tied stations, the resulting schedule barely improves on what round 1 alone almost already gave you — you pay a full extra round (4 µs) to resolve just one small tie, a poor exchange rate that doesn't meaningfully extend the ranked TDMA order. Hence the lecture's conclusion that minimal-participation round 2 makes TDMA "not effective": the round's cost isn't justified by how little new ranking information it produces.

**27. Round-1 holders at subcarriers 1, 3, 4; round-2 picks {2, 0, 4} respectively.**
Matching each original station to its round-2 pick (station-from-1 → 2, station-from-3 → 0, station-from-4 → 4), the final TDMA order is by **ascending round-2 pick**:
**Rank 1** = station originally at subcarrier 3 (round-2 pick 0)
**Rank 2** = station originally at subcarrier 1 (round-2 pick 2)
**Rank 3** = station originally at subcarrier 4 (round-2 pick 4)

**28. Six stations, protocol always advances the lowest-indexed 3 to round 2.**
(a) The other **3 stations** (highest subcarriers) simply **don't participate in round 2** — they keep their original round-1 relative order among themselves (already unambiguous) and get appended after the round-2-resolved group, becoming Rank 4, Rank 5, Rank 6.
(b) 💡 They should be placed directly after the round-2 group, ordered among themselves by their original round-1 subcarrier index — no re-contention needed since they were never ambiguous relative to each other.

**29. Trade-off in how many stations advance per round.**
**Too small** (e.g., always exactly 1): the schedule is built one station at a time across many separate rounds — barely more efficient than resolving everyone sequentially, and each round's fixed 4 µs cost buys very little new information.
**Too large** (all N contenders every round): wastes overhead by forcing already-unambiguous stations to needlessly re-contend, inflating total rounds/time relative to what's actually being resolved.
The right balance (as in "Optimize for TDMA") admits just the genuinely ambiguous stations plus a modest number of extra nearby winners, so each round resolves a meaningful chunk of the final order without wasting effort on stations that don't need it.

**30. Two timelines side by side, channel time saved.**
**(a) 802.11**: [DIFS + backoff (red/wasted slot)] → Data/ACK, repeated three separate times, each preceded by its own contention.
**(b) Back2F**: one short [Frequency Backoff] burst (4 µs) → Data/ACK → Data/ACK → Data/ACK, back-to-back with **no** contention in between.
Channel time is saved exactly in the "missing" red contention slots that would otherwise appear before packets 2 and 3 in the 802.11 timeline — Back2F pays the contention cost **once** for the whole train instead of three separate times.

**31. Rank-2's exchange fails mid-schedule due to fading.**
Since each station's slot position is fixed by its already-known rank (not by real-time sensing), Rank 3's turn structurally follows Rank 2's turn regardless of whether Rank 2's exchange succeeded — **so long as the failure doesn't consume more time than Rank 2's allotted slot was expected to take.** If a failed exchange causes Rank 2 to keep retrying beyond its planned window, that *would* delay Rank 3. 💡 Reasonable behavior: Rank 2 should **not** endlessly retry within the fixed schedule — its failed slot should simply be treated as skipped for this round, with retransmission deferred to its *next* regular turn (or a brief separate recovery mechanism outside the fixed schedule), so Rank 3's guaranteed slot isn't eaten into.

**32. Six stations, 4 µs/round, 2 rounds, 250 µs Data/ACK each.**
Total time = 2×4 + 6×250 = 8 + 1500 = **1508 µs.**
Per-packet effective overhead ≈ 8/6 ≈ **1.33 µs/packet.**
η = 1500/1508 ≈ **99.47%.**
Versus 802.11 (100+250 per packet × 6 = **2100 µs**, η = 1500/2100 ≈ 71.43%): Back2F finishes in **1508 µs vs. 2100 µs** — about 28% less total time.

## 4.6 Advantages, Limitations, and Design Trade-offs

**33. Five advantages, one-sentence justification each.**
- **Fully Distributed** → works without any central controller or coordination messages between devices.
- **Low Overhead** → doesn't need frequent control messages or feedback beyond the brief listen-antenna observation.
- **Highly Efficient** → very few collisions and minimal wasted time; ranks resolve almost instantly and stations transmit back-to-back with no gaps.
- **No Idle Time Before Transmission** → unlike 802.11's real idle-time backoff, Back2F's "wait" costs only a single 4 µs OFDM symbol.
- **Quick to Stabilize** → reaches a working, ranked state within one or two short rounds.

**34. Three limitations, underlying technical cause.**
(a) **Needs Extra Antenna** — transmitting your own subcarrier and simultaneously listening for everyone else's requires two separate RF chains; a single antenna can't send and receive at once on typical half-duplex hardware.
(b) **Sensitive to Channel Fluctuation** — the whole scheme depends on correctly detecting which discrete subcarriers are active, and fading/interference can suppress or distort a subcarrier, causing a listener to miss it entirely (undercounting active subcarriers, corrupting its rank calculation).
(c) **Unfairness to Legacy 802.11** — legacy devices don't participate in subcarrier signaling at all; in a mixed deployment, Back2F stations resolve contention almost instantly and then transmit long TDMA trains, while legacy devices — still doing slow temporal backoff — can get squeezed out.

**35. Deep fade wipes out subcarriers 0–5; another station signals on subcarrier 2.**
The affected listener simply **fails to detect** subcarrier 2 as active at all — it undercounts the true active set. This could lead it to compute its **own rank as better than it actually is** (fewer stations appear to rank ahead of it than truly do), potentially even believing it's the outright winner when it isn't. The resulting MAC-level failure: the listener may **transmit in a TDMA slot it doesn't actually own**, colliding with the rightful (subcarrier-2) station's transmission — exactly the risk the "Sensitive to Channel Fluctuation" limitation warns about.

**36. Back2F's TDMA vs. 802.11 PCF — coordination model.**
Both produce contention-free periods, but the coordination model is fundamentally different. **PCF** relies on a single, centrally-designated **Point Coordinator** that actively polls each station in turn — the schedule is imposed top-down by that one entity, and stations play no role in constructing it themselves. **Back2F** has no coordinator at all: every station independently participates in the subcarrier-signaling round and computes its **own** rank locally from the shared observed set — the order emerges bottom-up from all stations' simultaneous, mutually-visible choices, with no single entity deciding or announcing it. That's precisely why Back2F is "fully distributed" while PCF, dependent on its Point Coordinator, is not.

**37. Why legacy stations may starve; a coexistence mechanism.**
Step by step: (1) A Back2F group exchanges subcarrier symbols (a few µs) to establish ranks. (2) They then transmit a **long**, continuous TDMA train, occupying the channel for an extended stretch. (3) A legacy station doing ordinary CCA just senses "busy" throughout — it looks like one long, uninterrupted transmission. (4) The legacy station must defer its whole backoff for the entire train's duration, and since Back2F's own contention overhead is near-zero, Back2F stations can re-enter a new round almost immediately after finishing one — leaving few or no genuine gaps long enough for the legacy station to complete its DIFS+backoff. (5) Over time, if Back2F stations dominate this way, the legacy station's throughput can be squeezed toward zero. 💡 One coexistence mechanism: **cap the maximum TDMA train length** (a TXOP-limit-style bound, similar in spirit to 802.11e), forcing Back2F stations to periodically yield the channel and give legacy stations a genuine, fair contention window.

---

# Part B — Sample Questions (Study Guide Section 5)

## 5.1 Short Questions

**1.** Approximate MAC overhead at 54 Mbps: **~35%**; dominant cause: **temporal (random) backoff** — the idle channel time burned during the countdown before every packet.

**2.** 1500-byte frame @ 54 Mbps ≈ **222.22 µs** (exact math) / the lecture's own rounded figure is **~250 µs**. Average temporal backoff ≈ **100 µs.**

**3.** **48** OFDM subcarriers; Back2F indexes them as **integers 0–47.**

**4.** Original PHY motivation for OFDM in 802.11a/g/n: **robustness to fast, frequency-selective fading** (splitting a wideband channel into many narrowband subcarriers so each one sees comparatively flat, easier-to-equalize fading).

**5.** Main idea of Back2F, in one sentence: each station signals its randomly-chosen backoff value by transmitting on the correspondingly-indexed OFDM subcarrier while simultaneously listening with a second antenna to observe every other station's choice, so every station learns its rank within a single OFDM symbol instead of a serial time-domain countdown.

**6.** One frequency-domain backoff round = **4 µs**, corresponding physically to **one OFDM symbol.**

**7.** The **second (listen) antenna**, used simultaneously with the transmit antenna.

**8.** Active subcarriers {5, 11, 23}: winner = lowest = **subcarrier 5.** Rank of the station on subcarrier 23 = 1+|{5,11}| = **Rank 3.**

**9.** Back2F resolves two stations on the same subcarrier via a **second round of contention**: the tied stations redraw new subcarrier values and recontend.

**10.** "A few more stations" beyond the strict winners are admitted into round 2 so the resulting TDMA schedule can be **extended to cover more stations in one pass**, rather than round 2 resolving just a trivial 1–2 station tie.

**11.** Each station transmits over the **entire channel bandwidth** — subcarriers are used only for signaling/ranking during contention, not for the actual data.

**12.** 802.11 contends **once per packet**; Back2F contends **once per TDMA schedule** (potentially covering many packets after just one contention round).

**13.** Throughput improvement claimed: **up to 50%.**

**14.** Three limitations: **needs an extra (listen) antenna; sensitive to channel fluctuation/fading on subcarriers; may cause unfairness to legacy 802.11 devices in mixed deployments.**

## 5.2 Descriptive Questions

**15. Full 802.11 contention cycle, S1(15)/S2(25), two rounds — quantitative "high channel wastage."**
Both stations finish DIFS together; S1 (15) counts down faster and transmits first, while S2's counter freezes at 10 (25−15) the instant S1 starts. After S1's Data+ACK and a fresh DIFS, S1 draws a new B1=18 while S2 resumes counting down from its frozen 10 — S2 reaches 0 first this round and transmits, leaving S1's fresh countdown frozen at 8 (18−10, matching the slide exactly). The channel sits **idle** during every one of these countdown segments: 15 slots in round 1, 10 more slots in round 2 (S2's final descent), totaling 25 slots × 9 µs = 225 µs of pure idle waiting, plus 2×34 µs = 68 µs of DIFS, for **293 µs of contention overhead** across just two packets. The lecture calls this "high channel wastage" because none of that 293 µs carries any data — for a 1500-byte frame taking only ≈222 µs to actually transmit, spending nearly as much time again just deciding *who* transmits is a substantial tax, quantified at roughly 35% total overhead once DIFS, SIFS, ACK, and headers are folded in.

**16. Complete Back2F procedure, illustrated with backoffs 6 and 18.**
Each station independently draws a random integer from {0,...,47} — S1 draws 6, S2 draws 18. Both **simultaneously transmit** a brief signal on their chosen subcarrier while **simultaneously listening** (via a second antenna) for every active subcarrier, all within a single OFDM symbol (4 µs). Each station's listen antenna observes the full active set {6, 18}. Applying the shared "lowest wins" rule, both S1 and S2 independently compute the same conclusion: S1 (subcarrier 6) is the winner, S2 (subcarrier 18) is not — and, crucially, S2 also learns this fact directly (unlike a time-domain loser, who only senses "busy"). The network then transitions into **TDMA transmission**: since every station's rank is now known to everyone, stations transmit back-to-back, in rank order, using the **full channel bandwidth** (not the narrow signaling subcarrier) — contention has been resolved once for the whole resulting transmission opportunity, not once per packet.

**17. Efficiency derivation and comparison, growth with k.**
η₈₀₂.₁₁(k) = Tdata/(Tdata+100 µs) — a **constant** regardless of k, since every packet re-pays the fixed 100 µs contention cost. With Tdata=250 µs, this sits at a fixed ≈71.4% no matter how many packets are sent. ηBack2F(k) = (k·Tdata)/(4 µs + k·Tdata) — this **grows toward 100%** as k increases, since the one-time 4 µs cost gets divided over an ever-larger schedule (98.4% at k=1, 99.5% at k=3, 99.8% at k=10). This directly mirrors the lecture's two-timeline diagrams: 802.11's "contention per packet" repeats a red contention slot before every single Data/ACK burst, so its overhead never amortizes; Back2F's "contention per TDMA schedule" pays that cost exactly once, so the advantage compounds the longer the schedule runs.

**18. All five advantages and three limitations, with mitigation and cost for each limitation.**
*Advantages* (see Ex. 33 for full one-line justifications): Fully Distributed, Low Overhead, Highly Efficient, No Idle Time Before Transmission, Quick to Stabilize.
*Limitations, with mitigation and cost:*
- **Needs Extra Antenna** → mitigation: leverage radios that already carry multiple antennas for MIMO, repurposing one as the listen antenna. Cost: doesn't help single-antenna legacy hardware, limiting deployability.
- **Sensitive to Channel Fluctuation** → mitigation: use conservative energy-detection thresholds with margin, or redundant signaling across adjacent subcarriers. Cost: added complexity and effectively fewer usable distinct subcarrier values (some sacrificed to redundancy).
- **Unfairness to Legacy Wi-Fi** → mitigation: cap TDMA train length (TXOP-style bound) so Back2F periodically yields the channel. Cost: gives back some of Back2F's own efficiency gain in exchange for legacy fairness.

## 5.3 Analysis and Design Questions

**19. Four APs: 9, 21, 9, 36.**
(a) Round-1 collision: the two APs at **subcarrier 9** tie.
(b) They redraw to **14** and **3**; APs at **21** and **36** also join round 2 (with their existing values). Comparison set = {3, 14, 21, 36}. Final order: **Rank 1** = AP that redrew to 3, **Rank 2** = AP that redrew to 14, **Rank 3** = AP originally at 21, **Rank 4** = AP originally at 36.
(c) Contention time = 2×4 = **8 µs.** Total service time = 8 + 4×250 = **1008 µs.**
(d) 802.11 (100 µs/packet, no collisions): 4×(100+250) = **1400 µs.** Improvement = (1400−1008)/1400 ≈ **28%.**

**20. N=20 stations, K=48 subcarriers.**
(a) P(all distinct) = ∏ᵢ₌₀¹⁹(48−i)/48 ≈ **0.97%** → **≈99% chance of at least one collision.** (Continuing the same running product from Ex.22's N=10 result of ≈36.6%, multiplied through the remaining 10 terms.)
(b) Frequency-domain collisions stay far cheaper even here because they're detected within one OFDM symbol (µs-scale) via a quick extra round, rather than only being discovered after a full wasted data-frame transmission (hundreds of µs) as in time domain — the raw probability of collision isn't necessarily lower, but the **cost per collision** is dramatically lower.
(c) 💡 The number of contention rounds should scale gently (not linearly) with N — each additional round only needs to resolve the residual *tied* subset, which shrinks rapidly round-over-round, so a small constant number of extra rounds (2–3) typically resolves the large majority even at high N. Each extra round costs a fixed 4 µs, which stays cheap in absolute terms even when several rounds are needed.

**21. Coherence time 2 ms, Tdata=250 µs, 2 rounds × 4 µs = 8 µs.**
(a) Max k: 8 + 250k ≤ 2000 → k ≤ 7.968 → **k=7.**
(b) η at k=7 = (7×250)/(8+7×250) = 1750/1758 ≈ **99.54%.**
(c) If coherence time drops to 0.5 ms (500 µs): k ≤ (500−8)/250 ≈ 1.97 → **k=1.** 💡 This directly worsens the "Sensitive to Channel Fluctuation" limitation: a shorter coherence window forces much smaller schedules, pushing Back2F back toward "contend almost every packet" territory and eroding exactly the amortization advantage that makes it worthwhile over 802.11.

**22. Alternate transmit/listen (symbol 1 transmit, symbol 2 listen).**
(a) **No, not reliably.** If every station follows the identical "transmit-then-listen" pattern, nobody is ever listening during anyone else's transmit symbol — during symbol 1 (when everyone transmits) a given station is also transmitting, not listening; during symbol 2 (when it listens) everyone else has *already stopped* transmitting. No one hears anyone.
(b) The new failure: every station observes **no active subcarriers at all** in symbol 2 (or only noise) — the entire ranking mechanism fails silently, since there's genuinely nothing to hear.
(c) A randomized fix: each round, every station randomly chooses to be either "transmit-first, listen-second" or "listen-first, transmit-second" — roughly half the population transmits while the other half listens in each symbol, so most stations get heard by at least the opposite group at least once. Estimated added overhead: at least **doubling** the base cost from 1 OFDM symbol (4 µs, true simultaneous case) to **≈2 symbols (8 µs)**, possibly more if extra rounds are needed to guarantee complete mutual visibility.

**23. 802.11 DCF vs. Back2F — comparison table.**

| Dimension | 802.11 DCF | Back2F |
|---|---|---|
| Contention overhead/packet | ~100 µs, paid every packet | ~4 µs amortized over the schedule (→0 for large k) |
| Collision detection latency | Only after a full failed transmission (~250 µs+, via missing ACK) | Within 1 OFDM symbol (~4 µs), before data is sent |
| Hardware requirements | Standard single antenna | Requires a second (listen) antenna |
| Robustness to fading | Robust regardless of specific frequency conditions | Vulnerable — fading on a subcarrier can hide a station's signal |
| Fairness to legacy devices | Is the legacy baseline | Can starve legacy stations via long, continuous TDMA trains |
| Behavior at high density | Collision probability and overhead both climb sharply | Handles moderate density well via multi-round tie-breaking, though very high N still needs extra rounds |

💡 Prefer plain DCF when: hardware can't support a second simultaneous-listen antenna; the deployment is mixed with many legacy-only devices where fairness matters more than peak efficiency; the channel is highly unstable (short coherence time), making subcarrier signaling unreliable; or traffic is naturally light, where DCF's overhead is already small in absolute terms and Back2F's added hardware/complexity isn't justified.

**24. Six stations: A=14, B=2, C=39, D=2, E=27, F=9.**
(a) Lowest subcarrier is **2**, but it's **tied between B and D** — no clean outright winner.
(b) **B and D tie** at subcarrier 2; neither can yet be placed in the final order.
(c) The three lowest **distinct** subcarrier values are {2, 9, 14} — corresponding to **4 actual stations** (B, D at 2; F at 9; A at 14), since the value 2 is shared by two stations. All four (B, D, F, A) advance to round 2. Proposed round-2 set: **{0, 2, 4, 6}** (4 distinct values for 4 stations) — e.g., B picks 0, D picks 2, F picks 4, A picks 6, breaking the B/D tie and settling F and A's relative order in the same pass.

**25. Ten stations, 250 µs packets each.**
(a) Legacy DCF: 10×(100+250) = **3500 µs.**
(b) Back2F, single round (ties resolved): 4 + 10×250 = **2504 µs.**
Improvement = (3500−2504)/3500 ≈ **28.5%.**

**26. Design-your-own instance: N stations from digits X, Y.**
💡 This exercise is a personal template — plug in your own X and Y. Here's a fully worked illustration using **X=5, Y=3**:
N = 4+(5 mod 4) = 4+1 = **5 stations.**
subcarrierᵢ = (5·i+3) mod 48:
i=1: 8, i=2: 13, i=3: 18, i=4: 23, i=5: 28 → **{8, 13, 18, 23, 28}**, all distinct.
(b) Round-1 winner: lowest = **8** (station i=1).
(c) No ties exist as assigned. To create one deliberately: change station i=2's pick from 13 to **8** (matching i=1) — now i=1 and i=2 tie at subcarrier 8, and a second round (each redrawing fresh) would resolve it exactly as in the earlier collision-resolution exercises.
(d) Total channel time (single-round Back2F): 4 + 5×250 = **1254 µs.** Legacy DCF: 5×(100+250) = **1750 µs.** Savings = 496 µs ≈ **28.3%.**
💡 Notice this keeps landing near **28–28.6%** across nearly every worked exercise in this guide (19, 25, 26 here) — that's not a coincidence: as k grows, % improvement → 100/(100+250) = 100/350 ≈ **28.57%**, since Back2F's fixed round overhead (4–8 µs) becomes negligible next to the per-packet 100 µs it eliminates. This is the scheme's asymptotic "headline" gain at moderate-to-large k, distinct from the "up to 50%" figure which likely reflects different overhead assumptions or larger k in the original paper.
