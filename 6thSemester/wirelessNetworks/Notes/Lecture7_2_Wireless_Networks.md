# CSE 4615 — Lecture 7.2 (MAC Efficiency Boost: Collision-Free Access via Off-the-Shelf Tech): Complete Answer Key

**Course:** CSE 4615/4616 Wireless Networks, IUT
**Scope:** Every exercise in Section 4 and every sample question in Section 5 of the uploaded study guide — covering the **Perfect Coordination (PC) protocol**, **Deterministic Backoff (CSMA/ECA)**, and **Beacon-Assisted Deterministic Backoff**.

## How to read this document

Facts are grounded directly in the Lecture 7.2 slide deck — including the actual STA1–STA4 slot-by-slot countdown table (I traced it frame by frame from the slide images, not just the text captions, to get every collision and success slot exactly right). Supplementary reasoning is marked 💡.

**One real content gap worth flagging clearly:** Exercises **11 and 12** (Section 4.2) reference *"the worked example in Section 4 (stations A, B, C; CWmin = 8; Bd = 3)"* with a claimed *"collision at slot 8."* I checked the full Lecture 7.2 slide deck page by page — **this example does not actually exist anywhere in it.** The deck's only Deterministic Backoff walk-through is the STA1–STA4 / CWmin=16 example (which Exercises 9–10 correctly reference). This looks like a reference to content that didn't make it into the version of the guide you uploaded — possibly a leftover from an earlier draft. Rather than guess at numbers I can't verify, I've built my **own clearly-labeled, self-consistent reconstruction** using the constraints Exercise 12 itself implies (station A starts at 3, station C starts at 0), so you can still practice the method — but I could not reproduce the specific "slot 8" collision claim, and you should flag this with your instructor if it appears on a graded assessment.

Exercises **14** and **18**, and Sample Question **18**, are "design your own" problems. I've worked clean illustrative instances for each, clearly labeled — swap in your own numbers and repeat the same steps.

---

## Quick Reference

| Quantity | Value / Formula |
|---|---|
| PC sub-phases, in order | Learning-to-Win → Rectifying-the-Count → Learning-the-Losers |
| Who participates | Pending only → Winners only → Winners + Pending |
| Deterministic backoff formula | Bd = ⌈CWmin/2⌉ − 1 (evaluated at k=0, right after a success) |
| Bd for CWmin=16 | **7** |
| Bd for CWmin=8 / 32 / 64 / 128 | 3 / 15 / 31 / 63 |
| Steady-state period per station | Bd + 1 slots |
| STA1–STA4 slide example (CWmin=16) | Collision: STA3 & STA4 at slot 1. First successes: STA4@4, STA1@6, STA2@11, STA3@16. Steady-state residues (mod 8): STA3=0, STA2=3, STA4=4, STA1=6 |
| Beacon-Assisted example | V(d)=16 → converges to stable order 2,3,4,5,1 → window shrinks to V(d)=8 |

---

# Part A — Exercises (Study Guide Section 4)

## 4.1 Perfect Coordination (PC) Protocol

**1. Cycle 1, Learning-to-Win: null → {1} → {1,2} → {1,3}.**
(a) **Station 1** is confirmed as cycle 1's winner, at the **slot where "{1}" appears alone** (the second slot in the sequence — the first was null).
(b) Slots {1,2} and {1,3} involve **more than one station active simultaneously**. From the network's observation of *who's active*, a slot with multiple stations transmitting together can't cleanly isolate a single winner the way the "{1}-alone" slot did — at most it tells the network that stations 2 and 3 are each still actively participating in some structured way alongside the already-confirmed winner, feeding into how they're handled going forward.
(c) The network must carry stations **2 and 3 forward as pending** into the next cycle's Learning-to-Win sub-phase, since only station 1 has been confirmed so far.

**2. Rectifying-the-Count: single slot, only station 1 transmits.**
(a) This slot **confirms/locks in station 1's status as a definitively established winner**, removing any residual ambiguity from the earlier multi-station test slots — a clean, unambiguous single-station observation that every station in the network can trust, and (in later cycles, with multiple prior winners) it's also how the network confirms the *exact order/rank* among already-declared winners.
(b) It's safe for only the winner(s)-so-far to participate because their status **isn't in question anymore** — this slot isn't for discovering anything new about who's pending; it's a pure confirmation/bookkeeping step, and including still-pending stations would just introduce noise into what should be a clean verification.

**3. Learning-the-Losers: stations 1, 2, 3 all transmit together.**
(a) By observing which stations are active **together with the already-known winner (station 1)**, the network gets a joint reference point it can cross-check against the earlier individual test slots to isolate exactly **which stations remain in the loser pool** — i.e., that 2 and 3, as a set, are the ones still pending.
(b) This can't be inferred from cycle 1's Learning-to-Win slots alone because those slots only tested the winner **paired one at a time** with each other station (winner+2, then winner+3) — they never directly establish 2 and 3 as a **joint, simultaneous** losing set. The combined "everyone together" slot is what nails that down.

**4. Cycle 2 (only stations 2, 3 pending): null → {3} → {3,2}.**
(a) **Station 3** wins cycle 2 (confirmed at the slot where "{3}" appears alone).
(b) Cycle 2 needs only 3 slots vs. cycle 1's 4 because with **one fewer pending station**, fewer pairing test-slots are needed to isolate the winner — each additional pending station generally costs one more test-slot. As the pending set shrinks cycle over cycle, each subsequent Learning-to-Win sub-phase shrinks correspondingly, directly cutting total learning overhead as the network converges.

**5. Final winner order 1, 3, 2 — Transmission Phase for 6 packets.**
(a) Sequence: **1, 3, 2, 1, 3, 2** (the fixed order repeated twice).
(b) **Zero idle slots and zero collisions** because every station already knows the complete, agreed order from the preceding learning cycles — no one needs to sense the channel, wait, or guess when to go; each transmits in its predetermined turn back-to-back. This contrasts with every learning cycle, where genuine ambiguity about who's pending/winning necessitated the deliberate null/multi-station test slots.

**6. N=5, avg 4 slots/cycle, slot=9 µs, 5 full cycles needed.**
(a) Learning-phase overhead = 5 × 4 × 9 = **180 µs.**
(b) η = (50×250)/(180 + 50×250) = 12500/12680 ≈ **98.58%.**

**7. Why Learning-the-Losers needs both winners *and* pending stations together.**
💡 The network needs a **common reference point** to correctly interpret the combined activity pattern. Including the already-known winner(s) gives the network a known "anchor" against which to interpret the rest of the observed activity — distinguishing "the expected winner, plus these other signals = the losers" from an otherwise ambiguous raw pattern. Pending stations transmitting alone (without that anchor) wouldn't give the network the same reliable frame of reference, especially across later cycles where multiple confirmed winners need to be jointly referenced at once.

## 4.2 Deterministic Backoff (CSMA/ECA)

**8. Bd = ⌈CWmin/2⌉ − 1, tabulated.**

| CWmin | 8 | 16 | 32 | 64 | 128 |
|---|---|---|---|---|---|
| **Bd** | 3 | 7 | 15 | 31 | 63 |

**9. Slide's 4-station example: B1=6, B2=11, B3=1, B4=1, CWmin=16 (Bd=7).**
Tracing the actual slide diagram slot by slot:
(a) **STA3 and STA4 collide at slot 1** — both had drawn backoff = 1, so both hit 0 simultaneously on the very first countdown tick.
(c) After redrawing (STA3→14, STA4→2, per the slide), **STA4 is the first to succeed**, at **slot 4** (its redrawn value of 2, counted down over 2 more slots from slot 2).

**10. After all four stations have each won once.**
(a) Once every station has succeeded at least once, all four are running the **identical fixed Bd=7 cycle** (period = Bd+1 = 8 slots) — but each began that cycle at a **different offset**, set by when it individually first succeeded (STA4@4, STA1@6, STA2@11, STA3@16). Since Bd is the same constant for everyone, each station's subsequent transmissions recur exactly every 8 slots from its own starting point. Because their first-success times were naturally staggered, their steady-state slots-mod-8 land on **four distinct residues** — STA4=4, STA1=6, STA2=3 (11 mod 8), STA3=0 (16 mod 8) — producing a clean, collision-free, perfectly periodic pattern with zero further coordination needed.
(b) **Period of one complete round through all 4 stations = Bd+1 = 8 slots.** Within any 8-slot window, all four stations get exactly one transmission opportunity each, at their fixed offsets (in order: STA3 at residue 0, STA2 at 3, STA4 at 4, STA1 at 6).

**11–12. ⚠️ Flagged gap: no "stations A, B, C, CWmin=8" example exists in the source material.**
As noted above, I could not locate this example anywhere in the Lecture 7.2 deck. Here is my own self-consistent reconstruction, using the values Exercise 12 implies (A=3, C=0 originally, and B=5 per Exercise 12's phrasing "instead of 5"), with CWmin=8 (Bd=3):

*My reconstruction, clearly labeled as such (not verified against a slide):*

| t | A | B | C |
|---|---|---|---|
| 0 (initial) | 3 | 5 | 0 |
| 1 | 2 | 4 | **transmits (1st success)** |
| 2 | 1 | 3 | 3 (reload) |
| 3 | **transmits (1st success)** | 2 | 2 |
| 4 | 3 (reload) | 1 | 1 |
| 5 | 2 | **transmits (1st success)** | **transmits (2nd success, period=5−1=4 ✓)** |

Using this reconstruction: (a) **A, B, and C each achieve a first success within the first 5 slots** (not "within 8" as Exercise 11 asks to verify — my version converges even faster than that bound, which is at least consistent with the exercise's claim, just not a tight match). (b) In my reconstruction, **B and C's counters coincide at 0 at slot 5**, not slot 8 as the original exercise states — I cannot reproduce "slot 8" from the given constraints (A=3, C=0, B=5, CWmin=8), and flag this discrepancy rather than force an answer that doesn't check out. If your actual course slide shows a different table, please use that instead — the *method* shown here (decrement-and-check each tick, reload to Bd on success, redraw uniformly on collision) is the transferable part.

**Exercise 12** (B's original draw was 4 instead of 5, all else A=3, C=0 unchanged): redoing the table with B0=4:

| t | A | B | C |
|---|---|---|---|
| 0 | 3 | 4 | 0 |
| 1 | 2 | 3 | transmits (1st success) |
| 2 | 1 | 2 | 3 (reload) |
| 3 | transmits (1st success) | 1 | 2 |
| 4 | 3 (reload) | transmits (1st success) | 1 |
| 5 | 2 | 3 (reload) | transmits (2nd success) |

(a) **No collision occurs anywhere in this modified run** — with B0=4 instead of 5, B's first success shifts to slot 4, and it never coincides with anyone else's zero.
(b) Once all three have succeeded (by slot 4), residues mod 4 (Bd+1=4): A: 3 mod4=3, C: 1 mod4=1, B: 4mod4=0. All distinct — **yes, the eventual pattern is still collision-free with period Bd+1=4 slots per station**, just with a different steady-state ordering (B, C, A by ascending residue) than whatever the original (unreproducible) example would have shown.

**13. Six stations, CWmin=32 (Bd=15).**
(a) **Bd = 15.**
(b) One complete round-robin cycle = Bd+1 = **16 slots** (6 stations fit comfortably within a 16-slot cycle, each at a distinct offset).
(c) η = (6×250)/(6×250 + 6×16×9) = 1500/(1500+864) = 1500/2364 ≈ **63.45%.**
💡 Note this formula (as given) treats each station's *entire* Bd+1-slot period as dedicated overhead per station, rather than accounting for the fact that all 6 stations' periods actually overlap in real time (they share the same 16-slot window). It's a simplified, conservative accounting method as specified by the exercise, not literal wall-clock efficiency — treat it as the exercise's own defined metric rather than a direct restatement of Ex. 10's "zero collisions once converged" result.

**14. Design your own: three stations, CWmin=16 (Bd=7), collision guaranteed on the very first countdown.**
💡 My illustrative instance — call the stations **P, Q, R** with initial backoffs **P=1, Q=1, R=8** (mirroring the slide's own STA3/STA4 pattern for a guaranteed slot-1 collision):

| t | P | Q | R |
|---|---|---|---|
| 0 | 1 | 1 | 8 |
| 1 | collision | collision | 7 |
| 2 | 5 (redraw) | 12 (redraw) | 6 |
| ... | (counting down) | (counting down) | (counting down) |
| 7 | transmits (P's 1st success) | 7 | 1 |
| 8 | 7 (reload) | 6 | transmits (R's 1st success) |
| 14 | 1 | transmits (Q's 1st success) | 2 |
| 15 | transmits (P's 2nd success, period=8 ✓) | 7 (reload) | 1 |
| 16 | 7 (reload) | 6 | transmits (R's 2nd success, period=8 ✓) |

All three (P, Q, R) have succeeded at least once by slot 14. Steady-state residues mod 8: P=7, R=0, Q=6 (14 mod 8). **Final steady-state round-robin order: R (residue 0) → Q (residue 6) → P (residue 7), repeating every 8 slots.**

**15. Why larger CWmin → longer steady-state period; risk of too-small CWmin.**
Bd = ⌈CWmin/2⌉−1 grows roughly linearly with CWmin, so the steady-state period (Bd+1) between a station's own successive transmissions grows correspondingly — **more idle slots elapse between two successes of the same station** when CWmin is large. A designer might prefer a **smaller** CWmin once the network has already converged, since it shortens this gap and gives each station more frequent turns (higher steady-state per-station throughput). 💡 The risk of setting CWmin too small **before** convergence: a smaller CWmin confines the *initial* random backoff draws to a much narrower range, substantially raising the probability that two or more stations draw the same value and collide — trading faster eventual steady-state throughput for a much bumpier, more collision-prone path to get there.

## 4.3 Beacon-Assisted Deterministic Backoff

**16. V(d)=16; window 1: station 3 collides with 1 in slot 1; stations 2, 4, 5 win later random slots.**
(a) **Two stations (1 and 3) have not yet won** by the end of window 1.
(b) Already-won stations can safely use fixed slots without re-contending because the **periodic beacon re-synchronizes every station to the same window boundary each interval** — giving everyone a shared, common time reference. A winner can simply reserve "my known slot, every window from now on" without needing to re-verify or re-contend, and the beacon's regular re-sync is exactly what makes this safe and unambiguous for the rest of the network.

**17. Window 3: all five stations deterministic, no random slots remain.**
(a) This implies **far fewer wasted/idle slots** than window 1 — every station now transmits in its own fixed, non-contending slot, with no need to reserve a large random-contention region (which, by design, holds some inherently unproductive capacity to accommodate collision-avoidance among not-yet-won stations).
(b) "Less channel wastage" than plain Deterministic Backoff: the periodic beacon lets the set of already-won (deterministic) stations grow and consolidate quickly within a **bounded, re-synchronized** window — rather than plain Deterministic Backoff's fully organic, unsynchronized convergence, which has no external checkpoint at which the random-vs-deterministic split (or the window size itself) can be explicitly re-tuned to how many stations remain unresolved.

**18. Slot 49 (window 4): new beacon; schedule reorganizes to 2,3,4,5 (det.), then 1 (det., last).**
(a) 💡 The beacon can cause a re-ordering, rather than simply repeating window 3's exact sequence, because the AP/beacon mechanism has the authority to reorganize deterministic slot assignments at each re-sync point — e.g., station 1 (having won *last*, at the very end of window 1's collision resolution) may simply be placed at the end of the newly consolidated order once every station is finally accounted for.
(b) The beacon provides **central coordination authority** that a fully decentralized protocol (plain Deterministic Backoff) doesn't have: because an AP is actively broadcasting an authoritative periodic signal, it can impose or adjust a global, agreed-upon slot order at each interval — something no single station in a purely peer-to-peer scheme could do, since plain Deterministic Backoff's order emerges only organically, with no external authority able to reorganize it.

**19. Slots 129–144: stable order 2,3,4,5,1 repeating; window shrinks V(d)=16→8.**
(a) Once the network is **fully converged** (all 5 stations deterministic, no random contenders left at all), there's no longer any need to reserve the larger pool of random-contention slots that used to accommodate not-yet-won stations — since all 5 already have known, fixed slots, a much smaller window (8 slots, still ≥5) suffices without losing anyone's guaranteed access.
(b) Time saved per window = (16−8)×9 = **72 µs.** Percentage reduction = (16−8)/16 = **50%.**

**20. N=8 stations, converged, V(d)=8 slots + 8 × 250 µs data.**
Total time = 8×9 + 8×250 = 72 + 2000 = **2072 µs.** η = 2000/2072 ≈ **96.53%.**
Versus plain 802.11 DCF (8 stations, 100 µs avg backoff/packet): 8×(100+250) = **2800 µs**, η = 2000/2800 ≈ 71.43%.
Beacon-Assisted Deterministic Backoff finishes in **2072 µs vs. 2800 µs** — about **26% less total time.**

**21. Beacon-Assisted vs. pure PC — central coordination.**
**PC is fully distributed** (no AP needed — the learning phase itself is entirely peer-to-peer). **Beacon-Assisted Deterministic Backoff requires an AP** to broadcast the periodic beacon, so it is *not* fully distributed. 💡 Does that make it strictly worse? **No — it's a genuine trade, not a downgrade.** Giving up "fully distributed" status (a real architectural cost, introducing dependency on the AP) is exchanged for concrete gains: "less channel wastage" (achievable *specifically because* the beacon gives a reliable re-sync point) and "easier re-synchronization" (stations can cleanly re-enter the collision-free state at the next beacon, rather than needing an organic, unsynchronized convergence). In infrastructure-mode WLANs — which already have an AP broadcasting beacons for association, timing, etc. (per Lecture 6.1) — "requiring an AP" often isn't really an *extra* cost at all, making the trade favor Beacon-Assisted's efficiency gains with little real downside in that common setting.

## 4.4 Comparative Analysis

**22. Comparison table.**

| Protocol | Special PHY/OFDM? | Extra antenna? | Tight time sync? | Central coordinator/AP? | Handles dynamic membership well? |
|---|---|---|---|---|---|
| Frequency-Domain Backoff (7.1) | Yes | Yes (listen antenna) | Not explicitly required | No (fully distributed) | Not deeply covered in 7.1; contention re-runs per schedule, so new arrivals join the next round |
| PC protocol | No | No | **Yes** | No (fully distributed) | **Poor** — any join/leave forces a full re-learning phase |
| Deterministic Backoff | No | No | No | No (fully distributed) | Trivial handling of arrival/departure (per its strengths), though high churn can still disrupt steady state |
| Beacon-Assisted Deterministic Backoff | No | No | No (beacon sync, not "tight" sync) | **Yes** (needs AP) | Same churn sensitivity as plain Deterministic Backoff, but easier re-sync via the beacon |
| Plain 802.11 DCF | No | No | No | No | Naturally handles it well — pure per-packet contention, no converged state to disrupt |

**23. What each fully-distributed protocol substitutes for a central coordinator.**
- **Frequency-Domain Backoff**: substitutes an **extra antenna** (simultaneous transmit+listen) — every station coordinates itself by directly observing everyone else's choice in real time.
- **PC protocol**: substitutes a **complex, dedicated learning phase** (structured rounds of silence/action signaling) — the network collectively *discovers* the order through repeated observation and elimination, in place of a coordinator assigning it.
- **Deterministic Backoff**: substitutes **reliance on randomness alone**, plus a shared, universally-known constant (Bd) — ordinary random backoff naturally produces staggered first-success times, and from then on the same fixed Bd, applied independently by every station, keeps them from colliding again, with no learning phase or extra hardware required.

**24. Ranking least → most disruption from a single new station joining an already-converged network.**
1. **Frequency-Domain Backoff (least disruption)** — contention re-runs fresh for every new TDMA schedule anyway; a new station simply joins the next round like anyone else, since there's no persistent state to disrupt in the first place.
2. **Deterministic Backoff** — per its own strengths list, "handling the new node arrival and departure is trivial": the new station just runs ordinary random backoff once, then adopts the shared Bd and slots into the existing pattern (assuming its offset doesn't happen to collide, a low-probability, self-resolving event).
3. **Beacon-Assisted Deterministic Backoff** — shares that same "trivial" handling in principle, but cleanly integrating the newcomer still depends on the AP's beacon cycle to reopen a random contention block for it, and the window may need to grow back, undoing some prior V(d) shrinkage (per its stated weakness).
4. **PC protocol (most disruption)** — per its explicit weakness, *any* arrival or departure forces the **entire** dedicated, multi-cycle learning phase to be repeated from scratch, since PC depends on knowing the exact, fixed set of contenders up front.

**25. Recommend a protocol: no extra antenna, highly dynamic clients, an AP already broadcasting beacons.**
**Recommendation: Beacon-Assisted Deterministic Backoff.**
Justification, at least three facts from Section 1:
1. It "doesn't require Special PHY (OFDM) Layer" and "doesn't require Additional Antenna at each Node" — directly satisfying the no-extra-antenna constraint, ruling out Frequency-Domain Backoff.
2. It inherits Deterministic Backoff's "trivial" handling of node arrival/departure, and additionally offers "easier re-synchronization thanks to the periodic beacon" — a meaningfully better fit for a highly dynamic population than PC, whose weakness explicitly states it's "not efficient for Highly Dynamic Networks."
3. Its one real structural weakness — needing "support of central coordinator/AP for beacon transmission" — costs **nothing extra** here, since the deployment already has an AP broadcasting beacons for other purposes; its efficiency benefit ("Less Channel wastage" vs. plain Deterministic Backoff) comes essentially for free.

---

# Part B — Sample Questions (Study Guide Section 5)

## 5.1 Short Questions

**1.** **Learning-to-Win → Rectifying-the-Count → Learning-the-Losers.**

**2.** Only the **winner(s)-so-far (all winners)** participate in Rectifying-the-Count.

**3.** **Bd = ⌈CWmin/2⌉ − 1**, evaluated with **k=0**. k=0 is used because the retry counter is reset to 0 the instant a transmission succeeds — Bd is meant to be the fixed, permanent value reused after *every future* success, computed from that clean "just succeeded" state, not from whatever retry count happened to precede it.

**4.** CWmin=32 → Bd = ⌈32/2⌉−1 = **15.**

**5.** A **fresh collision** (two or more counters reaching 0 in the same slot) triggers a station to draw a new random backoff instead of reusing Bd.

**6.** The periodic beacon achieves **synchronized re-entry into the collision-free state with far fewer wasted idle slots**, regardless of the number of stations or traffic load — something plain Deterministic Backoff has no mechanism for.

**7.** Once stable, **V(d) shrinks** (e.g., 16 → 8), because fewer (eventually zero) random contention slots are needed once every station is already deterministic.

**8.** Shared weakness of all three: **not highly efficient in highly dynamic networks** — newly arrived nodes can disrupt the converged steady state and cause instability again (PC pays this as a *full re-learn*; the other two as *steady-state disruption*).

**9.** **Beacon-Assisted Deterministic Backoff** requires a central coordinator (AP), to transmit the beacon.

**10.** **Hysteresis** and **Fair Share** — extensions used to support a large number of contenders while keeping the collision-free schedule stable.

## 5.2 Descriptive Questions

**11. PC protocol, phase by phase (N=3, K=4 example) — why each sub-phase is necessary.**
Starting from all 3 stations pending, **Learning-to-Win** runs a structured sequence of test slots (null → {1} → {1,2} → {1,3}) that isolates a single confirmed winner (station 1, at the slot where it transmits alone) while leaving stations 2 and 3's status still ambiguous. **Rectifying-the-Count** then has *only* the confirmed winner transmit alone in a single clean slot — locking in that winner's status/rank beyond any doubt, something the noisier multi-station slots of Learning-to-Win couldn't fully guarantee. **Learning-the-Losers** has winner and pending stations transmit *together*, giving the network a reliable anchor (the known winner) against which to correctly attribute the rest of the activity and definitively identify stations 2 and 3 as the loser set to be recycled into cycle 2. If **Learning-to-Win** were skipped, no winner would ever be identified in the first place. If **Rectifying-the-Count** were skipped, the winner's status would remain only provisionally established from noisy multi-station observations, risking ambiguity especially once multiple winners accumulate across cycles. If **Learning-the-Losers** were skipped, the network would have no reliable way to confirm exactly which stations remain pending for the next cycle. This repeats — cycle 2 with only stations 2, 3 pending (null → {3} → {3,2}), confirming station 3 — until, after cycle 3, the full order 1, 3, 2 is known, and the Transmission Phase runs collision-free and idle-free forever after.

**12. Deterministic Backoff end to end, using the worked STA1–STA4 example.**
Every station begins with an ordinary **random** backoff draw (STA1=6, STA2=11, STA3=1, STA4=1) and counts down normally. Whenever two counters hit 0 in the same slot (STA3 and STA4, both drawing 1, collide at slot 1), the colliding pair draws fresh random values and re-contends — everyone else's count is undisturbed. The moment a station's counter hits 0 **without** colliding, that's a **success**, and from that point on the station stops drawing random numbers: it reloads to the single fixed constant **Bd = ⌈CWmin/2⌉−1** (evaluated with the retry counter k reset to 0, since it just succeeded) after every subsequent transmission. STA4 succeeds first (slot 4), then STA1 (slot 6), then STA2 (slot 11), then STA3 (slot 16) — each switching to the Bd=7 cycle upon its own first success. Once **all four** have succeeded at least once, every station is running the identical 8-slot (Bd+1) period, but at different offsets set by when each first won — and since those offsets happen to land on four distinct residues mod 8, the network locks into a permanent, collision-free round-robin. The network can still experience occasional collisions **even after this point**, though — because Bd is a single *shared* constant, nothing in the base algorithm actually *guarantees* that two stations' first-success times will land on different residues; it's a probabilistic, not guaranteed, outcome (see Q17 in Section 5.3 for the full argument).

**13. Beacon-Assisted Deterministic Backoff: blending random and deterministic access.**
Within a single window of V(d) slots, stations that have **already won** transmit in fixed, deterministic slots, while stations that **haven't yet won** contend randomly for whatever slots remain. In the lecture's example (V(d)=16), window 1 starts with almost everyone random: station 3 collides with station 1 in slot 1, while stations 2, 4, 5 each win their own random slot later in the same window. By window 2, the newly-won stations (1, 2) shift to fixed deterministic slots, while the still-unresolved stations (3, 4, 5 — some newly deterministic, some still contending) fill the remaining random slots. By window 3, **every** station has won at least once, so the window is entirely deterministic — no random slots remain at all. The periodic **beacon** is what makes this evolution clean: it re-synchronizes every station (won or not) to the same window boundary each interval, so the deterministic/random mix can be re-evaluated and consolidated at every beacon without ambiguity. Once the network reaches a fully stable state (order 2, 3, 4, 5, 1 repeating with zero random contenders left), the window itself can **shrink** (16 → 8) — since the whole reason V(d) needed to be large was to leave room for random contention among not-yet-won stations; once nobody is contending randomly anymore, that reserved capacity is simply unnecessary and can be reclaimed.

**14. Compare all three protocols: signalling overhead and graceful handling of churn.**
**(a) Signalling/learning overhead before steady state:** PC pays the **heaviest, most structured** cost — a dedicated multi-cycle, multi-sub-phase learning process that must fully complete (N cycles for N stations) before any collision-free transmission can begin at all. Deterministic Backoff pays **essentially none** — there's no separate learning phase whatsoever; the collision-free schedule emerges as an organic *byproduct* of ordinary random backoff, with convergence simply happening as stations naturally accumulate first successes. Beacon-Assisted Deterministic Backoff sits in between: it still relies on the same organic convergence as plain Deterministic Backoff, but structures it into discrete, beacon-bounded windows, trading a small amount of AP-dependency for a cleaner, faster, less wasteful convergence path.
**(b) Handling a station leaving or joining after convergence:** **PC handles this worst** — any single membership change invalidates the fixed, known station count the whole learning phase depended on, forcing a **complete re-run** of the entire learning process. **Deterministic Backoff handles it best** among these three — a new station just runs ordinary random backoff once and organically slots into the existing pattern; a departing station's slot simply goes unused (no active harm to anyone else's schedule). **Beacon-Assisted Deterministic Backoff** handles it almost as gracefully as plain Deterministic Backoff, but the AP/beacon cycle needs to briefly reopen a random-contention block for the newcomer (and the window may need to grow back), which is a small extra step plain Deterministic Backoff doesn't require.

## 5.3 Analysis and Design Questions

**15. Four stations, CWmin=16 (Bd=7): B1=2, B2=9, B3=4, B4=4.**
(a) Hand-simulated countdown (A=STA1, B=STA2, C=STA3, D=STA4):

| t | A | B | C | D |
|---|---|---|---|---|
| 0 | 2 | 9 | 4 | 4 |
| 1 | 1 | 8 | 3 | 3 |
| 2 | **succeeds (1st)** | 7 | 2 | 2 |
| 3 | 7 (reload) | 6 | 1 | 1 |
| 4 | 6 | 5 | **collision** | **collision** |
| 5 | 5 | 4 | 6 (redraw) | 10 (redraw) |
| 9 | 1 | **succeeds (1st)** | 2 | 6 |
| 10 | **succeeds (2nd, period 8 ✓)** | 7 (reload) | 1 | 5 |
| 11 | 7 (reload) | 6 | **succeeds (1st)** | 4 |
| 15 | 3 | 2 | 4 | **succeeds (1st)** |
| 17 | 1 | **succeeds (2nd, period 8 ✓)** | 2 | 6 |
| 18 | **succeeds (3rd, period 8 ✓)** | 7 (reload) | 1 | 5 |

*(Redraw values for the C/D collision at t=4 — C→6, D→10 — are illustrative choices within the extended [0,31] range specified by the exercise, chosen so the eventual steady state is collision-free; using different redraws would shift the specific residues but not the method.)*

By t=18, all four stations have each succeeded at least once: A@2, B@9, C@11, D@15.
(b) Steady-state residues mod 8: A=2, B=1 (9 mod 8), C=3 (11 mod 8), D=7 (15 mod 8) — all distinct. **Final steady-state round-robin order: B → A → C → D, repeating every 8 slots (period = Bd+1 = 8).**

**16. Campus WLAN, N=40 devices, ~5 join/leave per minute: PC vs. Beacon-Assisted.**
(a) Using the reasoning from Ex.6 (Section 4.1): a full PC learning phase for N=40 costs roughly 40 cycles × 4 slots/cycle × 9 µs ≈ **1.44 ms per complete re-learn.** 💡 In isolation that's small, but PC's weakness is that it must repeat this **entire** re-learn on *every single* membership change — with a change roughly every 12 seconds on average (5/minute), the network would be triggering a full re-learn dozens of times per hour, and each fresh re-learn discards whatever collision-free Transmission Phase was just established. The cost isn't really about the raw microseconds; it's that PC would likely spend a **chronic, disruptive fraction of its capacity re-learning rather than transmitting**, making it a poor fit here.
(b) Beacon-Assisted Deterministic Backoff copes far better: a join or leave is absorbed at the granularity of **individual beacon intervals**, not full network-wide resets — a new station simply contends in the next beacon's reopened random-slot block (with the window briefly growing back if needed), while every *other* already-deterministic station is completely unaffected and keeps transmitting in its known slot. This **localizes** the cost of churn to just the changed station(s), making it far more scalable to this environment's described 5-changes-per-minute load.

**17. Why "never a second collision" is fundamentally impossible under plain Deterministic Backoff; a fix.**
Because **every** station, once converged, reuses the exact same shared constant Bd after each of its own successes — but *which* residue (mod Bd+1) a given station lands on in steady state is set entirely by the essentially random timing of when it happened to achieve its **first** success. Nothing in the base algorithm enforces that different stations' first-success times land on distinct residues; it's a matter of chance (as nearly happened in Exercise 15's simulation above, before choosing different redraw values deliberately avoided it). If two stations *do* happen to share a residue, they will **collide every single cycle, forever**, with no built-in mechanism to detect or correct this beyond eventually observing the collision and falling back to random re-backoff — at which point there's still no guarantee the new residue avoids everyone else's. So collision-freedom under plain Deterministic Backoff is fundamentally **probabilistic, not guaranteed**, precisely because Bd is shared rather than individualized.
**Proposed modification:** assign each station a **distinct** deterministic backoff value rather than one shared Bd — e.g., have the network (or an AP) explicitly assign each station a unique offset within the shared (Bd+1)-slot period once it first succeeds, similar in spirit to how Beacon-Assisted Deterministic Backoff assigns fixed slots.
**New coordination cost this introduces (one sentence):** it requires some mechanism — either explicit peer-to-peer negotiation or a lightweight central authority (an AP, much like Beacon-Assisted) — to assign and communicate unique per-station offsets and avoid two stations being independently given the same one, reintroducing exactly the kind of coordination overhead plain Deterministic Backoff was originally designed to avoid.

**18. Design a scenario: three stations collide simultaneously on their very first countdown.**
💡 My illustrative instance — CWmin=16 (Bd=7), three stations **X, Y, Z**, all drawing the **same** initial backoff = 1 (directly generalizing the slide's own 2-way STA3/STA4 collision to a 3-way tie):

| t | X | Y | Z |
|---|---|---|---|
| 0 | 1 | 1 | 1 |
| 1 | **3-way collision** | **3-way collision** | **3-way collision** |
| 2 | 3 (redraw) | 10 (redraw) | 22 (redraw) |
| 5 | **succeeds (1st)** | 7 | 19 |
| 12 | 7 (reload) | **succeeds (1st)** | 12 |
| 24 | ... | ... | **succeeds (1st)** |

*(Redraws X→3, Y→10, Z→22 are illustrative, chosen from the extended post-collision range so the three converge to distinct residues.)* All three succeed at least once by t=24 (X@5, Y@12, Z@24). Residues mod 8: X=5, Y=4 (12 mod 8), Z=0 (24 mod 8) — all distinct. **Final steady-state order: Z → Y → X, repeating every 8 slots.**
