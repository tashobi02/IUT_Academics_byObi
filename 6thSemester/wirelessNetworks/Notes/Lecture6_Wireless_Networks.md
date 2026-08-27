# CSE 4615 — Lecture 6.1 (IEEE 802.11 WLANs): Complete Answer Key

**Course:** CSE 4615/4616 Wireless Networks, IUT
**Scope:** Every exercise in Section 4 and every sample question in Section 5 of the uploaded study guide, answered in full.

## How to read this document

All definitions, numbers, and mechanisms below come straight from the Lecture 6.1 slide deck (*IEEE 802.11 WLANs*, Chapter 5, IEEE 802 Wireless Systems). Where I've added reasoning, worked steps, or framing the slides don't spell out explicitly (e.g. *why* a design choice was made, or an approximate figure like EIFS), it's marked with 💡 so you can tell lecture fact from supplementary scaffolding.

**Two small flags before you start**, because mismatched references are exactly the kind of thing that trips people up in a viva:
- **Q15** says "using the 802.11a values from Question 14" — but Q14 is the *hypothetical* variant (aSlotTime = 20 µs, SIFS = 10 µs), not 802.11a. I've answered Q15 using the actual 802.11a values derived in **Q13**, since the question explicitly asks for "802.11a values."
- **Q27** says "using your answer to Question 25," and **Q28** says "in Question 26" — both are off by one. Q25 is the hidden-station explanation (no number to reuse); Q26 is the DATA transmission-time calculation. I've treated Q27's reference as Q26, and Q28's reference as Q27, since that's the only reading that makes the arithmetic work.

---

## Quick Reference: Key 802.11a Numbers & Formulas

| Quantity | Value / Formula |
|---|---|
| aSlotTime | 9 µs |
| SIFS | 16 µs |
| PIFS | SIFS + aSlotTime = 25 µs |
| DIFS | SIFS + 2×aSlotTime = 34 µs |
| EIFS | 💡 longer than DIFS by design (≈ SIFS + DIFS + ACK-at-basic-rate); lecture doesn't derive an exact number |
| CWmin / CWmax | 16 / 1024 |
| Contention Window | CW(n) = min(2^(n−1)·CWmin − 1, CWmax) |
| Backoff duration | r × aSlotTime, where r = Rand(0, CW) |
| CCA threshold | −82 dBm |
| Max MSDU length | 2346 bytes |
| SRC limit / LRC limit | 7 / 4 |
| Non-overlapping channels | 802.11b/g: 3 (ch. 1, 6, 11) · 802.11a: 8 |
| EDCA AIFS | AIFS[AC] = SIFS + AIFSN[AC]×aSlotTime (AIFSN ≥ 2) |
| EDCA CW per stage | CWi[AC] = min(2^i·(CWmin[AC]+1) − 1, CWmax[AC]) |

---

# Part A — Exercises (Study Guide Section 4)

## 4.1 Architecture, Services, and Frame Formats

**1. Define BSS, IBSS, and ESS.**
A **BSS** (Basic Service Set) is the fundamental building block of an 802.11 network: a group of stations under the control of a single Coordination Function. An **IBSS** (Independent BSS) is the simplest form — a minimum of two stations with no station holding priority and coordination distributed among all of them (no AP). An **ESS** (Extended Service Set) is built by connecting one or more BSSs together over the **Distribution System (DS)**, so an ESS is effectively "many BSSs stitched into one logical LAN" via their APs and the DS.

**2. DCF vs. PCF — which is mandatory, which optional?**
**DCF** (Distributed Coordination Function) is mandatory and used by every station in a BSS; it's the CSMA/CA-based contention access described throughout the lecture. **PCF** (Point Coordination Function) is an optional extension layered on top of DCF that adds priority, polling-based access for QoS, controlled by a Point Coordinator (typically the AP).

**3. Two categories of 802.11 services; which is unavailable in an IBSS?**
The two categories are **Station Services (SS)** — e.g. MSDU delivery, (de)authentication, privacy — and **Distribution System Services (DSS)** — e.g. (re)association, (dis)association, integration. **DSS is unavailable in an IBSS**, because DSS is delivered *through* the Distribution System, and an IBSS has no AP and therefore no DS to provide it.

**4. Integration function: entity and frame path.**
The entity responsible is the **DSS "integration" service**, delivered via the **portal** — the logical point where the DS connects to a non-802.11 LAN. The frame's path: source station → its AP (via the wireless medium) → **DS** (carries the MSDU between APs/segments) → **portal** (translates/bridges into the non-802.11 LAN's addressing and frame format) → destination device on the wired LAN. In the reverse direction the same path runs backward.

**5. The three MPDU types and their frame-body length.**
The three MPDU types are **management, data, and control frames**. Data and management frames have a **variable-length** frame body; control frames (RTS, CTS, ACK) are short and effectively fixed/minimal since they carry little more than addressing and duration information.

**6. 802.11b/a/g/n/ac comparison; dual-band standard.**

| Standard | Band | Max rate |
|---|---|---|
| 802.11b | 2.4–2.5 GHz | 11 Mbps |
| 802.11a | 5–6 GHz | 54 Mbps |
| 802.11g | 2.4–2.5 GHz | 54 Mbps |
| 802.11n | 2.4 GHz **and** 5 GHz | 600 Mbps |
| 802.11ac | 5–6 GHz | 3.4 Gbps |

**802.11n** is the one that can operate in both 2.4 GHz and 5 GHz simultaneously (dual-band, using MIMO, frame aggregation, and channel bonding to reach its higher rates).

---

## 4.2 Physical Layer and Listen-Before-Talk (with Numericals)

**7. The three original PHYs.**
- **FHSS** (Frequency Hopping Spread Spectrum): the carrier rapidly switches among many frequency channels using a pseudorandom sequence known to both transmitter and receiver.
- **DSSS** (Direct Sequence Spread Spectrum): all stations operate at the same center frequency, and different spreading codes let different sets of communicating stations reduce mutual interference.
- **IR** (Infrared): not commercially successful, though the lecture notes it could suit future in-house residential use.

**8. How HR/DSSS beats plain DSSS using CCK.**
HR/DSSS uses **Complementary Code Keying (CCK)**, which draws from a **richer code set** than the Walsh codes used in plain DSSS. A richer code set lets each symbol encode more bits per chip sequence, so at the same chip/spreading rate, HR/DSSS packs more information per symbol — that's the mechanism behind its higher data rate in the same band.

**9. CCA threshold check: −78 dBm vs. −85 dBm (threshold −82 dBm).**
CCA compares measured power against −82 dBm; **the channel is busy if measured power exceeds this threshold.**
- **−78 dBm**: this is *stronger* than −82 dBm (less negative = more power) → **channel is busy.**
- **−85 dBm**: this is *weaker* than −82 dBm → **channel is idle.**

**10. CCA vs. NAV; a scenario where NAV succeeds but CCA fails.**
**CCA** is physical carrier sensing — a station literally measures RF power on the channel against a threshold. **NAV** is virtual carrier sensing — a countdown timer set from information carried in overheard frames (e.g. the Duration field of RTS/CTS), which decrements regardless of the medium's actual physical state and blocks transmission as long as it's running. 💡 The classic scenario where CCA fails but NAV succeeds is the **hidden-terminal case**: a station may be too far from the actual transmitter to physically detect its signal (CCA reads idle), but if it can hear the **CTS** reply (from a station closer to it), it reads the Duration field, sets its NAV, and stays silent — protecting the exchange even though physical sensing alone would have let it transmit and collide.

**11. NAV countdown remaining.**
Duration signaled = 312 µs; elapsed = 90 µs.
**Remaining NAV = 312 − 90 = 222 µs.** The station may not attempt to sense the channel again until this 222 µs elapses.

---

## 4.3 Interframe Spaces and Timing (with Numericals)

**12. The four IFS, increasing order, and highest priority.**
In increasing duration: **SIFS < PIFS < DIFS < EIFS**. Since a *shorter* IFS means a station can access the medium sooner (and therefore "cuts in line" ahead of others), **SIFS gives the highest priority** — it's reserved for the most urgent, time-critical responses (ACK, CTS, fragment bursts, PCF polling responses).

**13. Compute PIFS and DIFS for 802.11a.**
Given aSlotTime = 9 µs, SIFS = 16 µs:
- **PIFS = SIFS + aSlotTime = 16 + 9 = 25 µs** ✓
- **DIFS = SIFS + 2×aSlotTime = 16 + 18 = 34 µs** ✓

**14. Hypothetical variant: aSlotTime = 20 µs, SIFS = 10 µs.**
- **PIFS = 10 + 20 = 30 µs**
- **DIFS = 10 + 2×20 = 50 µs**

**15. PCF vs. DCF head start (802.11a values).**
As flagged above, I'm using the real 802.11a numbers from Q13 (PIFS = 25 µs, DIFS = 34 µs), since the question asks for "802.11a values."
**Difference = DIFS − PIFS = 34 − 25 = 9 µs.**
💡 That gap is *exactly one aSlotTime* — which isn't a coincidence: DIFS is defined as PIFS + one extra aSlotTime, so the PCF station's head start over the DCF station is always precisely one slot time, by construction of the formulas.

**16. When EIFS is used instead of DIFS, and why it's the correct design choice.**
EIFS is used instead of DIFS when a station has just received a frame **it could not decode correctly** (e.g., failed FCS check) — the lecture ties this to situations where stations are hidden from each other and therefore start frame exchanges at different, uncoordinated times. 💡 The reasoning: if a station can't decode a frame, it has no idea what that frame was for or how long the resulting exchange (e.g., a pending ACK it can't see) will take. Using a *longer* wait (EIFS) before contending again is a conservative safety margin — it reduces the chance that this station starts transmitting right into the middle of an ACK or continuation it doesn't know about. As soon as *any* subsequent frame is received correctly, the station drops back to ordinary DIFS, since it's now back in sync with the medium.

---

## 4.4 Backoff, Contention Window, and Collision Avoidance (with Numericals)

**17. The CW formula, symbol by symbol.**
**CW = min(2^(n−1)·CWmin − 1, CWmax)**
- **CW**: the current contention window size (in slots), from which the random backoff count is drawn.
- **CWmin, CWmax**: the standard's fixed minimum and maximum window bounds (16 and 1024 for 802.11a).
- **n**: the **attempt number** — how many times this station has tried (and possibly failed) to deliver this MSDU, starting at n = 1 for the first attempt. Each additional failure increases n, doubling the window (Binary Exponential Backoff) up to the CWmax ceiling.

**18. CW for attempts n = 1 to 5 (CWmin = 16, CWmax = 1024).**

| n | 2^(n−1)×16 − 1 | CW |
|---|---|---|
| 1 | 16 − 1 | **15** |
| 2 | 32 − 1 | **31** |
| 3 | 64 − 1 | **63** |
| 4 | 128 − 1 | **127** |
| 5 | 256 − 1 | **255** |

n = 1 gives CW = 15, matching the "15 slots" shown in the lecture's RTS/CTS timing figure. ✓

**19. Smallest n at which CW saturates at CWmax = 1024.**
Continuing the pattern:

| n | 2^(n−1)×16 − 1 | CW |
|---|---|---|
| 6 | 512 − 1 | 511 |
| 7 | 1024 − 1 | 1023 |
| 8 | 2048 − 1 | min(2047, 1024) = **1024** |

**CW first saturates at CWmax on the 8th attempt (n = 8).** Note that n = 7 gets tantalizingly close (1023) but doesn't actually hit the cap — only n = 8 does.

**20. Backoff duration, 3rd attempt, max possible r.**
At n = 3, CW = 63 (from Q18), so the maximum possible draw is **r = 63**.
**Backoff duration = r × aSlotTime = 63 × 9 = 567 µs.**

**21. Why rB = 25 is impossible on attempt 1; A vs. B with rA = 4, rB = 9.**
On the 1st attempt, CW = 15, so r = Rand(0, CW) can only take values **0 through 15**. rB = 25 is simply outside that range — it's not a legal draw on the first attempt (it *would* become legal starting at the 2nd attempt, where CW = 31).

With rA = 4, rB = 9, and aSlotTime = 9 µs, counting from the DIFS boundary:
- Station A would transmit at **4 × 9 = 36 µs** after DIFS ends.
- Station B would transmit at **9 × 9 = 81 µs** after DIFS ends.
**Station A transmits first**, since 36 µs < 81 µs.

**22. B's remaining backoff after freezing.**
Both A and B count down simultaneously from the DIFS boundary. B had counted 4 slot times (the same 4 slots A also counted down, since they were counting in the same real time) before the channel went busy (A started transmitting exactly when A's own count reached 0).
**B's remaining count = original rB − slots elapsed = 9 − 4 = 5.**
B does **not** redraw a fresh random value — it resumes counting down from 5 once the channel is sensed idle for DIFS again. This is deliberate: if B were forced to redraw, a station that happened to draw a large backoff (and thus "lost" the race) would face the same odds all over again next time, with no memory of how long it had already waited. Preserving the frozen count instead means stations that deferred longest get to the front of the queue soonest once the channel frees up — this is what gives DCF backoff its fairness property.

**23. CW and average backoff for the 3rd attempt (n = 3).**
From Q18, **CW3 = 63**.
Average r = CW/2 = 63/2 = 31.5.
**Average backoff duration = 31.5 × 9 = 283.5 µs.**

---

## 4.5 RTS/CTS, Hidden Stations, and Medium Access Overhead (with Numericals)

**24. Full RTS/CTS exchange, gap by gap.**
Sequence: **DIFS → random backoff → RTS → SIFS → CTS → SIFS → DATA → SIFS → ACK.**
- **DIFS**: the initial wait once the channel is sensed idle, before a station may even start its backoff — this is the "everyone's baseline" wait, used to obtain the medium in the first place.
- **The gaps between RTS↔CTS, CTS↔DATA, and DATA↔ACK all use SIFS**, the shortest interframe space.
This difference matters because it's what makes RTS/CTS/DATA/ACK function as one **atomic, protected sequence**: any other station that finished sensing the channel idle for a full DIFS could, in principle, jump in — but because SIFS is *shorter* than DIFS, the stations already mid-exchange (waiting only SIFS between their own frames) always get to continue before a new contender's DIFS timer even expires. Priority by IFS length is precisely what prevents the sequence from being interrupted partway through.

**25. Hidden-station scenario: Station 6 hears CTS but not RTS.**
Step by step:
1. Station 2 sends an **RTS** to Station 1. Station 6 is too far from Station 2 (or otherwise physically shielded) to receive this RTS — it stays physically unaware a request was made.
2. Station 1 replies with a **CTS**. Station 6 *is* within range of Station 1, so it receives this CTS.
3. The CTS carries a **Duration field** describing how long the rest of the exchange (DATA + ACK) will occupy the channel.
4. Station 6 reads that Duration field and sets its **NAV** accordingly — even though it never saw the RTS that started this exchange.
5. For the duration of the NAV, Station 6 refrains from transmitting, **regardless of what CCA tells it** about the physical channel state.
Because NAV is *virtual* carrier sensing driven by frame content rather than raw RF energy detection, Station 6 stays silent purely from the information in the CTS — this is exactly why RTS/CTS solves the hidden-terminal problem even for stations that only overhear one half of the handshake.

**26. DATA transmission time, 1000-byte frame at 54 Mbps.**
T = L × 8 / R = (1000 × 8) / (54 × 10⁶) = 8000 / 54,000,000 ≈ **0.00014815 s = 148.15 µs.**

**27. Total channel-occupancy time for a full RTS/CTS exchange.**
(Using the answer from Q26 for DATA time, per the flagged reference correction.)
Sum = DIFS + avg. backoff + RTS + SIFS + CTS + SIFS + DATA + SIFS + ACK.

Using 802.11a values (DIFS = 34, SIFS = 16) and 1st-attempt average backoff = (CW/2)×aSlotTime = (15/2)×9 = 67.5 µs:

| Component | Duration (µs) |
|---|---|
| DIFS | 34.00 |
| Avg. backoff | 67.50 |
| RTS | 20.00 |
| SIFS | 16.00 |
| CTS | 14.00 |
| SIFS | 16.00 |
| DATA | 148.15 |
| SIFS | 16.00 |
| ACK | 14.00 |
| **Total** | **345.65 µs** |

**28. Non-RTS/CTS version, and overhead percentages.**
(Using Q27's total as the reference point, per the flagged correction.)

Non-RTS/CTS sum = DIFS + avg. backoff + DATA + SIFS + ACK:

| Component | Duration (µs) |
|---|---|
| DIFS | 34.00 |
| Avg. backoff | 67.50 |
| DATA | 148.15 |
| SIFS | 16.00 |
| ACK | 14.00 |
| **Total** | **279.65 µs** |

**Overhead as a percentage of total exchange time** (overhead = everything except DATA):
- **RTS/CTS-enabled**: overhead = 345.65 − 148.15 = 197.5 µs → **197.5 / 345.65 ≈ 57.1%**
- **RTS/CTS-disabled**: overhead = 279.65 − 148.15 = 131.5 µs → **131.5 / 279.65 ≈ 47.0%**

So RTS/CTS costs noticeably more overhead as a fraction of total airtime (~57% vs. ~47% here) — this quantifies exactly *why* RTS/CTS is often disabled when hidden terminals aren't a serious problem: the protection it buys comes at a real, measurable throughput cost.

**29. Why collision probability falls as CWmin rises, and why CWmax caps the benefit.**
💡 With k active stations each independently drawing a backoff slot uniformly from a window of size CW+1, the chance that two stations pick the *same* slot shrinks as the window widens — more available slots means any given pair of stations is less likely to collide by coincidence. This is exactly why **Binary Exponential Backoff (BEB)** doubles CW after every failed attempt: as contention/collisions increase, the protocol automatically spreads stations across a wider window, cutting the odds of a repeat collision.

The catch is **CWmax = 1024**: once CW has doubled up to this ceiling, further failed attempts don't grow the window any more. If the number of contending stations is large enough that even a window of 1024 slots still produces frequent coincidental collisions, BEB has no further lever to pull — collision probability plateaus rather than continuing to fall, and the station is stuck retrying at that fixed collision rate (subject only to the SRC/LRC retry limits) until contention eases. CWmax exists as a deliberate trade-off: an unbounded window would keep reducing collisions asymptotically, but at the cost of unbounded worst-case delay, which is unacceptable for real traffic.

---

## 4.6 Recovery, Post-Backoff, and Fragmentation (with Numericals)

**30. SRC vs. LRC.**
The **Short Retry Counter (SRC)** is incremented when a failed exchange involved a frame **smaller than the fragmentation threshold, or an RTS**. The **Long Retry Counter (LRC)** is incremented for failed exchanges involving larger frames. **Default limits: SRC = 7, LRC = 4.** Both counters reset to zero whenever the MSDU is eventually delivered successfully.

**31. 7th consecutive failure on a short frame (SRC = 7 limit).**
Since the default SRC limit is exactly 7, the **7th failure hits the discard threshold — the frame is dropped** and not retransmitted further; it's simply given up on at the MAC layer.

**32. Post-backoff, in one paragraph.**
Post-backoff means that after **every** successful transmission, a station must perform another random backoff — even if it currently has nothing else queued to send. 💡 The point is to guarantee a uniform rule: *any* frame that is ever transmitted, including the very next one that shows up moments later, will always have gone through a proper backoff, with no special case for "the queue happened to be empty." The direct payoff is for **lightly loaded systems**: since the post-backoff has usually already finished counting down by the time a new MSDU arrives, that new MSDU can be sent almost immediately (as soon as the channel has been idle for DIFS) instead of having to wait through an entire fresh backoff from scratch — reducing delivery delay precisely when the channel is otherwise idle and available.

**33. 3000-byte MSDU exceeding the 2346-byte limit.**
This MSDU must undergo **fragmentation**: it's partitioned into multiple smaller MPDUs, each within the size limit, before transmission. At the receiver, the reverse process — **defragmentation** — reassembles the fragments back into the original 3000-byte MSDU.

**34. Fragments needed for 2346 bytes at ≤1000 bytes/fragment.**
Number of fragments = ⌈2346 / 1000⌉ = ⌈2.346⌉ = **3 fragments** (e.g., 1000 + 1000 + 346 bytes).
- **Benefit of a smaller threshold on a high-error channel**: if a bit error corrupts one fragment, only that (smaller) fragment needs retransmitting, not the whole MSDU — this both wastes less airtime on retransmission and, since shorter frames are statistically less likely to contain an error in the first place, raises the odds of each individual fragment succeeding.
- **Drawback**: more fragments means more per-fragment overhead — each fragment carries its own MAC header, needs its own interframe spacing, and (depending on the ACK policy) may need its own acknowledgment, so a very aggressive fragmentation threshold trades retransmission efficiency for a heavier overhead tax on every successful transmission too.

---

## 4.7 Synchronization, Beacons, and Scanning (with Numericals)

**35. TSF and TBTT in an infrastructure BSS.**
The **Timing Synchronization Function (TSF)** keeps all stations in a BSS aligned to a common clock. The **Target Beacon Transmission Time (TBTT)** is the scheduled instant the next beacon is due; beacons carry the TSF timer value so that every station receiving them can update its local clock to match — this is how the whole BSS stays synchronized despite each station running its own independent hardware clock.

**36. Beacon timing when the channel is busy at TBTT.**
Rule: if the channel is busy at TBTT, the beacon is transmitted **PIFS after the current transmission ends**. TBTT = 0, channel busy until it becomes idle at t = 40 µs, PIFS = 25 µs.
**Beacon transmitted at t = 40 + 25 = 65 µs.**

**37. Beacon generation: IBSS vs. infrastructure BSS.**
In an **infrastructure BSS**, only the AP generates beacons — it's a single, centralized source of truth. In an **IBSS**, there's no AP, so beacon generation is **distributed**: all stations participate, using a mechanism similar to the backoff procedure to contend for the right to send the next beacon. A station that hears another station's beacon first simply stops trying to send its own for that interval. Because any station's beacon (delivering that station's TSF timer value) can win the contention and get accepted — and a station only updates its own timer if the received value is *earlier* than its current one — the whole IBSS ends up converging on whichever station happens to have the **fastest-running clock**, since that station's timer value is always "earliest" relative to everyone else's slower clocks.

**38. Passive vs. active scanning: message order and trade-offs.**
- **Passive scanning**: (1) AP(s) send beacon frames periodically, (2) the station picks an AP and sends an Association Request, (3) the AP replies with an Association Response. The station itself sends no messages until it's ready to associate — it just listens.
- **Active scanning**: (1) the station broadcasts a Probe Request, (2) AP(s) reply with Probe Response frames, (3) the station sends an Association Request to its chosen AP, (4) the AP replies with an Association Response.
**Passive scanning involves fewer distinct message types** (it skips the probe request/response round-trip). **Active scanning lets a station discover an AP faster on a lightly loaded channel**, since it doesn't have to sit and wait for the AP's next scheduled beacon — it can force an immediate response by probing.

**39. Max total scanning time across 5 channels.**
MaxChannelTime = 20 ms/channel × 5 channels = **100 ms maximum total.**
💡 One factor that could shorten this in practice: the actual scanning duration "may vary, depending on the number of channels to be scanned, the Beacon Interval, and the load of the system" — for example, with active scanning, a station that receives (and gets its Probe Response acknowledged) well before MaxChannelTime elapses doesn't need to keep waiting out the rest of the window on that channel; it can move on early.

---

## 4.8 PCF and 802.11e QoS (EDCA/HCCA) (with Numericals)

**40. Legacy PCF superframe structure.**
The superframe is split into a **Contention-Free Period (CFP)**, during which **PCF** governs access (the Point Coordinator polls stations directly, no contention), followed by a **Contention Period (CP)**, during which ordinary **DCF** governs access (standard CSMA/CA contention).

**41. Station 4, hidden from the PC, doesn't set its NAV — is it correctly part of this BSS?**
**No.** Because Station 4 cannot hear the PC's beacon/CFP announcements, it never sets its NAV for the CFP and has no way of knowing the channel is reserved for polled access. It could therefore transmit during the CFP and collide with a station the PC has just polled — directly undermining the whole point of PCF's protected, contention-free access. As the lecture states, a station in this position "should not be part of the BSS coordinated by the PC," since PCF's guarantees only hold for stations that can actually hear (and obey) the coordinator.

**42. The four EDCA Access Categories, lowest to highest priority.**
**AC_BK (background) < AC_BE (best effort) < AC_VI (video) < AC_VO (voice).**

**43. AIFS[AC] for practice AIFSN = {7, 3, 2, 2}.**
AIFS[AC] = SIFS + AIFSN[AC] × aSlotTime, with SIFS = 16 µs, aSlotTime = 9 µs.

| AC | AIFSN | AIFS = 16 + AIFSN×9 |
|---|---|---|
| AC_BK | 7 | 16 + 63 = **79 µs** |
| AC_BE | 3 | 16 + 27 = **43 µs** |
| AC_VI | 2 | 16 + 18 = **34 µs** |
| AC_VO | 2 | 16 + 18 = **34 µs** |

**AC_VI and AC_VO tie for the shortest AIFS** (34 µs) in this practice set. That matches their intended priority in the broad sense (both are latency-sensitive, real-time traffic classes that should contend fastest) — 💡 though note the standard enforces **AIFSN ≥ 2** for every AC, so 34 µs is the theoretical floor here, exactly equal to legacy DIFS. In a real deployment, AC_VO is still differentiated from AC_VI mainly through a *smaller* CWmin/CWmax rather than a smaller AIFSN, since AIFSN alone can't push VO ahead of VI once both are already at the AIFSN floor.

**44. CWi[AC_VO] for i = 0, 1, 2, with CWmin[AC_VO] = 3.**
CWi[AC] = min(2^i × (CWmin[AC]+1) − 1, CWmax[AC]) — no CWmax[AC_VO] given, so no capping applies here.

| i | 2^i × 4 − 1 | CWi |
|---|---|---|
| 0 | 1×4 − 1 | **3** |
| 1 | 2×4 − 1 | **7** |
| 2 | 4×4 − 1 | **15** |

**45. Virtual collision in EDCA.**
A **virtual collision** happens when two (or more) of a *single station's own* independent Access Category backoff entities count down to zero at the same instant — e.g. its AC_VO and AC_BE queues both become ready to transmit simultaneously. Rather than actually sending two frames at once (which would be wasteful and pointless, since only one radio exists), the station resolves this internally: the **higher-priority AC wins and transmits**, while the lower-priority AC's entity behaves exactly as if a real collision had occurred on the medium — it increases its own CW and backs off again, just as it would after losing a genuine over-the-air collision to another station.

**46. EDCA-TXOP vs. HCCA-TXOP.**
An **EDCA-TXOP** is won through ordinary contention-based EDCA access and is bounded by **TXOPlimit[AC]**. An **HCCA-TXOP** (polled TXOP) is granted directly by the Hybrid Coordinator via polling, without contention, and is instead protected by **NAV** (other stations defer because they've heard the poll/duration information, not because they lost a contention race).

**47. HCCA-TXOP with three MSDUs.**
1. The HC polls the station (QoS CF-Poll), granting it a TXOP.
2. The station sends **MSDU 1** immediately.
3. After **SIFS**, it sends **MSDU 2**.
4. After another **SIFS**, it sends **MSDU 3**.
Each transmission is separated only by SIFS, so the whole burst stays tightly packed within the granted TXOP. If sending the third MSDU would push the total exchange **past TXOPlimit**, the station must **not** send it in this TXOP — it has to stop, and that MSDU waits to be delivered in the next TXOP it's granted (whether by a future poll, or by winning contention later, depending on context).

---

## 4.9 Block Acknowledgment, DLP, and Radio Spectrum (with Numericals)

**48. Block Acknowledgment throughput benefit.**
Instead of requiring a separate ACK after every single MSDU (each ACK adding its own SIFS + ACK-frame overhead), **Block Acknowledgment** lets a backoff entity deliver a whole run of MSDUs consecutively within one TXOP and get them all acknowledged **together, in one combined ACK**. This collapses many individual ACK round-trips into one, cutting the cumulative SIFS/ACK overhead per MSDU and directly raising throughput efficiency.

**49. Purpose of DLP; why AP-relaying wastes capacity.**
In legacy 802.11 infrastructure mode, **every** frame between two stations — even two stations both associated with the same AP — must be relayed *through* the AP: station A → AP → station B. That means the same data effectively crosses the wireless medium **twice** for every single delivery, consuming twice the airtime it strictly needs to. The **Direct Link Protocol (DLP)** sets up a **Direct Link (DiL)** so 802.11e stations can talk to each other directly, skipping the AP relay hop entirely and using the channel far more efficiently for station-to-station traffic.

**50. Two differences: 802.11 Unicast vs. Broadcast.**
Any two of the following:
- Unicast uses **RTS/CTS** (optional handshake); broadcast uses **no RTS/CTS** at all.
- Unicast uses **ACK/retransmission**; broadcast has **no ACK/retransmission** (there's no single recipient to acknowledge).
- Unicast uses **exponential backoff**; broadcast uses **no exponential backoff**.
- Unicast uses **auto-rate adaptation**; broadcast transmits at a **single (low) rate**, chosen conservatively so all recipients can decode it.

**51. Max APs in a linear arrangement, 3 non-overlapping channels, adjacent APs must differ.**
💡 Since the constraint given is only that *adjacent* APs must not share a channel (not that every AP in the whole deployment needs a globally unique channel), you can simply **cycle the 3 channels in a repeating pattern**: 1 → 6 → 11 → 1 → 6 → 11 → … Every AP differs from its immediate neighbors, and non-adjacent APs are far enough apart (in a linear chain) that reusing the same channel doesn't cause direct interference. Under this reading, there's **no fixed upper limit** — you can deploy an arbitrarily long line of APs this way, because the reuse factor of 3 (the classic 1/6/11 pattern) is exactly what makes 2.4 GHz WLAN deployments scale in practice. (If the question instead intended "no two APs anywhere may share a channel," the answer would simply be **3 APs**, one per non-overlapping channel — but that's a much stricter and less realistic constraint than "adjacent APs must differ.")

**52. 6 closely spaced APs: 802.11b/g alone vs. 802.11a alone.**
- **802.11b/g alone**: **not possible.** Only 3 non-overlapping channels exist (1, 6, 11), but 6 APs need 6 unique assignments to guarantee zero co-channel interference among all of them. At least some pairs would be forced to reuse a channel, risking interference.
- **802.11a alone**: **possible.** With 8 non-overlapping channels available and only 6 APs to place, each AP can be given its own unique non-overlapping channel with 2 channels to spare.

---

# Part B — Sample Questions (Study Guide Section 5)

## 5.1 Short Questions

**1.** 802.11 covers **OSI Layers 1 and 2**; the DLC layer is split into **LLC** and **MAC** sublayers.

**2.** **BSS**: a group of stations controlled by a Coordination Function. **IBSS**: the simplest 802.11 network — minimum 2 stations, no priority, distributed coordination, no AP. **ESS**: one or more BSSs connected via the Distribution System.

**3.** **DCF** is the mandatory, CSMA/CA-based contention access used by all stations. **PCF** is an optional extension for QoS, providing priority polling-based access via a Point Coordinator.

**4.** **Station Services (SS)** and **Distribution System Services (DSS)**. **DSS is unavailable in an IBSS** (no AP, so no DS to deliver it).

**5.** **FHSS, DSSS, and IR** (infrared).

**6.** **−82 dBm.**

**7.** **CCA** is physical carrier sensing (measuring actual RF power against a threshold). **NAV** is virtual carrier sensing (a timer set from frame content that counts down regardless of physical channel state).

**8.** **SIFS, PIFS, DIFS, EIFS** (increasing order).

**9.** For 802.11a: **aSlotTime = 9 µs, SIFS = 16 µs, PIFS = 25 µs, DIFS = 34 µs.**

**10.** **CW = min(2^(n−1)·CWmin − 1, CWmax)**, with **CWmin = 16, CWmax = 1024** for 802.11a.

**11.** RTS/CTS solves the **hidden-terminal problem** by reserving the channel via short control frames so even stations that can't hear each other directly still defer via NAV. It's often disabled because of the **overhead** it adds (extra RTS/SIFS/CTS/SIFS delay before every data frame).

**12.** Maximum MSDU length is **2346 bytes**. A station fragments an MSDU when it exceeds this (or a smaller configured threshold) to reduce the cost/probability impact of transmission errors on long frames.

**13.** **Passive scanning**: the station only listens for beacons. **Active scanning**: the station transmits Probe Requests and waits for Probe Responses, forcing a faster reply from APs.

**14.** **AC_BK < AC_BE < AC_VI < AC_VO** (lowest to highest priority).

**15.** **802.11b/g: 3 non-overlapping channels** (2.4 GHz). **802.11a: 8 non-overlapping channels** (5 GHz).

## 5.2 Descriptive Questions

**16. The complete 802.11 architecture, and how DCF/PCF relate to it.**
The basic building block is the **BSS** — a group of stations coordinated together. In its simplest, infrastructure-less form, a BSS is an **IBSS**: just stations talking peer-to-peer with no AP, coordinating access among themselves. In infrastructure mode, a BSS instead includes an **AP**, which has access to the wired network. When multiple infrastructure BSSs are connected together over a **DS (Distribution System)**, the result is an **ESS** — effectively one logical extended LAN built from several physical BSS "cells." Where the ESS needs to reach a non-802.11 wired LAN, that bridging happens through a **portal**. Layered on top of this physical/topological architecture are the two **Coordination Functions** that actually decide *who* gets to transmit *when*: **DCF**, the mandatory CSMA/CA-based contention scheme used by every station regardless of BSS type, and **PCF**, an optional add-on usable only in infrastructure BSSs (since it needs a Point Coordinator, typically housed in the AP) that grants priority, polling-based access for QoS-sensitive traffic. So the architecture defines *where* stations sit relative to each other and the wired world, while DCF/PCF define *how* they share the radio medium within that topology.

**17. Full DCF frame exchange with RTS/CTS, every IFS named.**
A station with an MSDU to send first waits for the channel to be sensed idle for a full **DIFS**. It then draws a random backoff count from the current Contention Window and counts down, freezing whenever the channel goes busy and resuming (without redrawing) once it's idle for DIFS again. When the countdown reaches zero, the station transmits an **RTS**. After a **SIFS**, the intended receiver replies with a **CTS** (assuming the RTS was received correctly), which sets the NAV of every station that hears it — including hidden ones. After another **SIFS**, the original station sends its **DATA** frame. After a final **SIFS**, the receiver returns an **ACK**, confirming successful delivery and letting both stations reset their retry counters. Every gap between RTS→CTS→DATA→ACK uses the short **SIFS**, which is what keeps the whole sequence atomic and un-interruptible by any newly-arriving contender (whose minimum wait is the longer DIFS). Only the very first wait, before backoff even starts, uses DIFS — everything from RTS onward runs on SIFS.

**18. The CW/backoff mechanism in detail.**
Before transmitting, a station must sense the channel idle for DIFS, then draw a random backoff count **r = Rand(0, CW)** and count down one slot (aSlotTime) at a time. The size of CW itself starts at **CWmin (15 slots effectively, since CW = 15 on attempt 1)** and follows **Binary Exponential Backoff**: after every failed transmission attempt, CW roughly doubles, following CW(n) = min(2^(n−1)·CWmin − 1, CWmax), up to a ceiling of CWmax = 1024. This growth spreads stations across an increasingly wide range of possible backoff slots as contention/collisions increase, reducing the odds that two stations pick the exact same slot again. Crucially, the countdown is not "all or nothing": as long as the channel stays idle, the timer keeps decrementing; the instant the channel becomes busy (someone else transmitted), the timer **freezes** rather than resetting; and once the channel returns to idle for a fresh DIFS, the timer **resumes counting down from wherever it froze**, rather than drawing a brand-new random value. This preserves fairness — a station that has already waited a long time (and was close to zero when it got interrupted) gets to the front of the line faster than a station starting a fresh, potentially-large random draw would.

**19. Hidden-station problem and NAV via CTS.**
The hidden-station problem occurs when two stations can each reach a common third station (e.g. an AP) but cannot detect each other's transmissions directly — so ordinary physical carrier sensing (CCA) fails to prevent them from colliding at that shared receiver. RTS/CTS solves this using **NAV**, virtual carrier sensing driven by frame content rather than raw signal detection. Even a station that never received the original RTS — because it's simply out of range of the sender — can still be close enough to the *receiver* to hear the **CTS** reply. That CTS carries a Duration field describing exactly how long the ensuing DATA + ACK exchange will occupy the channel. The hidden station reads that field and sets its NAV accordingly, deferring for the full duration regardless of what its own physical channel sensing says. Because NAV is set from *information in the frame* rather than requiring the station to have heard the *original* transmission, this mechanism protects the exchange even when only one half of the RTS/CTS handshake was actually audible to the hidden station.

**20. Legacy PCF superframe vs. 802.11e HCF superframe.**
The **legacy PCF superframe** has a strict two-phase structure: a **Contention-Free Period (CFP)**, during which a single **Point Coordinator** polls stations one at a time (CF-Poll/CF-Ack), and a following **Contention Period (CP)**, during which ordinary **DCF** contention takes over completely — the PC has no role during CP. The **802.11e HCF superframe** keeps the same beacon-initiated two-phase shape, but changes what happens in each phase: during the CFP, backoff entities still only transmit when explicitly polled (same as PCF), but during the **CP**, the **Hybrid Coordinator can still poll stations** (issuing QoS CF-Polls, e.g. after sensing the medium idle for PIFS, no backoff needed) *in addition to* the normal EDCA contention-based access happening among the four Access Categories. In other words, legacy PCF's coordinator authority is confined strictly to the CFP, while 802.11e's HC retains scheduling power throughout the *entire* superframe — CFP and CP alike — giving it much finer-grained control over QoS delivery than PCF ever had.

**21. EDCA in full.**
EDCA gives every 802.11e station **four independent backoff entities**, one per **Access Category**: AC_VO (voice), AC_VI (video), AC_BE (best effort), AC_BK (background), each contending for the medium on behalf of its traffic class. Each AC has its own **AIFS[AC] = SIFS + AIFSN[AC]×aSlotTime** (with AIFSN ≥ 2 required by the standard) — a smaller AIFSN means that AC starts counting down sooner after the channel goes idle, giving it earlier, higher-priority access. Each AC also has its own contention window, **CWi[AC] = min[2^i·(CWmin[AC]+1) − 1, CWmax[AC]]**, where smaller CWmin/CWmax values mean smaller expected backoff and thus faster access — but at the cost of higher collision risk if many stations share that AC. When two of a *single station's own* ACs happen to reach zero backoff simultaneously, that's a **virtual collision**: rather than transmitting both, the station lets the higher-priority AC go and makes the lower-priority AC behave as though it had lost a real over-the-air collision (increment its CW, back off again). Once an AC wins access, it's granted a **TXOP**, bounded by **TXOPlimit[AC]** — within that TXOP the AC may send one or more MSDUs back-to-back (separated only by SIFS), a technique that lets a single successful contention win deliver a burst of traffic rather than just one frame.

## 5.3 Analysis and Design Questions

**22. AC assignment for VoIP vs. bulk file transfer.**
Assign **VoIP to AC_VO** and bulk file transfer to **AC_BE** (or AC_BK if you want file transfer to yield completely to everything else). Justification: VoIP is latency- and jitter-sensitive but produces small, steady packets, so it needs the **smallest AIFSN** (fastest medium access after idle) and the **smallest CWmin/CWmax** (short, low-variance backoff, so packets aren't stuck waiting behind a long random draw — jitter matters as much as raw delay for voice quality). Bulk file transfer, by contrast, has no real-time deadline and can tolerate being deprioritized; giving it a **larger AIFSN and larger CWmin/CWmax** means it contends less aggressively and yields the channel to voice/video traffic whenever both are active, without materially hurting the file transfer's eventual completion time (throughput matters more than any individual packet's delay for a bulk transfer). 💡 This mirrors the real intent behind the four ACs: differentiate purely by how *sensitive* each traffic type is to delay/jitter versus how much it just needs eventual, high aggregate throughput.

**23. RTS/CTS-enabled vs. disabled in a dense lecture hall with many hidden terminals.**
In a lecture hall with many students' devices spread across a large room, hidden-terminal pairs (devices that can each reach the AP but not each other) are common — meaning collisions from hidden terminals would otherwise be frequent and costly, since a full-length DATA frame colliding wastes far more airtime than a short RTS colliding would. Given the overhead analysis from Q27/Q28 above (RTS/CTS added roughly 10 percentage points of extra overhead in that worked example, ~57% vs ~47%), the throughput trade-off is: RTS/CTS costs a fixed, small overhead on *every* transmission, but *saves* a much larger cost (full DATA-frame collisions and their retransmissions) whenever a hidden-terminal collision would otherwise have occurred. **In a densely populated hall with many hidden pairs, RTS/CTS-enabled is the more appropriate configuration** — the fixed per-frame tax is worth paying because the alternative (frequent full-frame collisions in a crowded, hidden-terminal-heavy room) would cost far more in wasted airtime and retransmissions than the RTS/CTS overhead itself. In a sparser or single-cell deployment where hidden terminals are rare, the calculus flips and disabling RTS/CTS is usually better.

**24. Three APs along a corridor: 802.11b/g vs. 802.11a.**
With **802.11b/g** (3 non-overlapping channels: 1, 6, 11), three APs along a corridor can each be assigned a distinct non-overlapping channel (1, 6, 11) with **no channels left to spare** — this works, but only just, and leaves zero margin if a fourth AP is later added or if adjacent-building APs also need to avoid these same three channels. With **802.11a** (8 non-overlapping channels), the three APs can be assigned distinct channels with **5 channels to spare**, giving comfortable headroom for future expansion or coordination with neighboring deployments. If the b/g deployment *couldn't* assign unique channels (e.g., a fourth close AP were added), the consequence would be **co-channel interference**: two APs sharing a channel would have their coverage areas overlap on that frequency, and stations near the boundary would experience the classic CSMA/CA symptoms — increased collisions, more binary-exponential-backoff growth, and reduced effective throughput for clients on both APs, exactly the "significant inefficiencies" the lecture describes under heavy contention.

**25. Priority scheme for VoIP, video conferencing, web browsing, and background backup.**
- **AC_VO — VoIP packet stream.** Smallest AIFSN and smallest CWmin/CWmax: voice packets are small, frequent, and need consistently low delay/jitter above all else; any queuing delay directly degrades perceived call quality.
- **AC_VI — video conferencing.** Second-smallest AIFSN/CW: video also needs low latency, but tolerates more jitter than voice and typically has larger, burstier frames, so it sits just below AC_VO in priority.
- **AC_BE — web browsing.** Moderate AIFSN/CW: interactive but not truly real-time — a user notices if a page takes noticeably longer, but small additional delays (tens of ms) are imperceptible, so best-effort priority is adequate.
- **AC_BK — background file backup.** Largest AIFSN/CWmin/CWmax: this traffic has no interactivity requirement at all and should yield the channel to everything else, contending only when the medium would otherwise sit idle.
This ordering follows directly from the AIFSN/CWmin/CWmax trade-off discussed earlier: **shorter AIFSN and smaller CW = faster, lower-variance access but higher collision risk if many stations share that AC**, so the traffic classes that most need low, predictable delay (VO, then VI) are given that faster access, while classes that are throughput-oriented rather than latency-oriented (BE, then BK) are deliberately made to wait longer and contend less aggressively.

**26. Throughput under 10-node congestion; BEB behavior and one mitigation.**
As contention increases, each failed attempt doubles this station's CW (Binary Exponential Backoff) — which *helps* up to a point by spreading stations across a wider range of backoff slots and cutting the immediate collision probability. But the lecture notes that with 10 active nodes, the probability of at least two picking the same slot already exceeds 40% even before accounting for CWmax's ceiling — and once CW saturates at 1024, no further widening is available to relieve that pressure. The practical effect on this station's throughput: as its own retry count climbs, its effective backoff duration keeps growing (worse latency per attempt) while the underlying collision probability stops improving once CWmax is hit, and it faces a real risk of exhausting its SRC/LRC retry limit and having the frame **discarded outright** — a hard throughput/reliability failure, not just a slowdown. 💡 One reasonable mitigation: **enable RTS/CTS.** Even though it adds per-frame overhead (as quantified in Q27/28), that overhead is paid by a *short* RTS frame — so when a collision does happen under heavy contention, it's a cheap RTS collision rather than an expensive full DATA-frame collision, which is a much better trade at high contention levels than at low ones. (802.11e's EDCA with per-AC differentiation would be another valid mitigation, letting this station's more latency-sensitive traffic classes get priority access even as overall contention rises — though that's a bigger architectural change than simply toggling RTS/CTS.)

**27. Why PCF and HCF are successive QoS attempts on top of DCF, and three specific PCF limitations HCF/EDCA fixes.**
Both PCF and 802.11e's HCF are explicitly built as *optional layers on top of* the same mandatory DCF foundation — neither replaces DCF; both add a coordinator-driven access mode alongside it, because DCF alone provides no way to prioritize time-bounded or latency-sensitive traffic over ordinary best-effort traffic. Three specific limitations of PCF that HCF/EDCA address:

1. **No traffic differentiation within the coordinator's own polling.** PCF's Point Coordinator polls stations essentially uniformly — there's no built-in concept of "this station's traffic is more urgent than that one's" during the CFP itself. HCF/EDCA's **four Access Categories** fix this directly, giving every station's own traffic classes distinct AIFSN/CW parameters so prioritization happens at a much finer granularity than "polled vs. not polled."
2. **Unpredictable CFP timing and duration.** The lecture notes the CFP can be **delayed** if the channel is busy at TBTT, and that the duration of a polled station's data frame is **not under the PC's control** — meaning worst-case latency for other stations waiting to be polled isn't well bounded. HCF addresses this with **TXOPlimit**-bounded transmission opportunities (both EDCA-TXOP and HCCA-TXOP), giving the coordinator (and the standard itself) an explicit ceiling on how long any single station can occupy the medium once granted access.
3. **No low-latency path outside of being polled.** Under legacy PCF, a station with urgent traffic during the CFP has no choice but to wait to be individually polled — there's no contention-based fast path available. HCF's **EDCA** gives every station a genuine contention-based route to fast access (especially via AC_VO's short AIFSN/CW) that doesn't depend on the coordinator getting around to polling it, which is a meaningful robustness and responsiveness improvement, particularly during the CP where PCF offered the coordinator no role at all.
