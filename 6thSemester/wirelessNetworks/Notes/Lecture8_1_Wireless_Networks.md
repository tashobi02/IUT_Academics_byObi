# CSE 4615 — Lecture 8.1 (Understanding Vehicular Communication): Complete Answer Key

**Course:** CSE 4615/4616 Wireless Networks, IUT
**Scope:** Every exercise in Section 4 and every sample question in Section 5 of the uploaded study guide — VANET fundamentals, safety applications, IEEE 802.11p PHY/MAC, EDCA/HCF QoS, WAVE/DSRC channel management, and vehicular propagation models.

## How to read this document

Facts are grounded directly in the Lecture 8.1 slide deck (based on Sommer & Dressler's *Vehicular Networking*, plus supplementary NHTSA/VSCC and IEEE 1609 material). Supplementary reasoning is marked 💡. Two small things worth flagging before you start:

- **Exercise 17** (and the "how to study" guidance behind it) describes subcarrier spacing as "bandwidth ÷ number of subcarriers," using **52**. Divided that way, 20 MHz/52 ≈ 384.6 kHz — which does **not** match the target value of 312.5 kHz the exercise itself asks you to confirm. The technically correct divisor is the OFDM **FFT size (64)**, not the count of *used* subcarriers (52 data+pilot, out of 64 total FFT bins). 20 MHz/64 = 312.5 kHz exactly, matching the target. I've used 64 throughout and flagged this clearly in Ex.17 rather than silently "fixing" the lecture's phrasing.
- **Exercise 6** asks you to "list the **five** components of a Smart Vehicle," then names **six** (radar, positioning, computing, display, communication, event recorder). I answer using all six named items and note the count mismatch.
- **Sample Q8** ("five characteristics of VANET") has a similar minor wrinkle: the slide's summary header list and its own prose explanation don't list quite the same five items (the prose swaps in "Wireless Communication" where the header list has "Predictable Mobility"). I've gone with the header list, since that's what the study guide's own "Topics Covered" section names, and flagged the discrepancy there.

---

## Quick Reference

| Quantity | 802.11a | 802.11p |
|---|---|---|
| Channel bandwidth | 20 MHz | 10 MHz |
| Subcarriers (FFT size) | 64 (52 used) | 64 (52 used) |
| Subcarrier spacing | 312.5 kHz | 156.25 kHz |
| Useful symbol time | 3.2 µs | 6.4 µs |
| Guard interval | 0.8 µs | 1.6 µs |
| **Total symbol time** | **4 µs** | **8 µs** |
| Bit rates | 6–54 Mbit/s | 3–27 Mbit/s |

| EDCA parameter | AC0 (BK) | AC1 (BE) | AC2 (VI) | AC3 (VO) |
|---|---|---|---|---|
| AIFSN | 9 | 6 | 3 | 2 |
| AIFS (SIFS=32µs, Slot=13µs) | 149 µs | 110 µs | 71 µs | 58 µs |
| CWmin (from CWmin=15) | 15 | 15 | 7 | 3 |
| Measured tw | 264 µs | 152 µs | 72 µs | 56 µs |

| DSRC | Value |
|---|---|
| U.S. band | 7 × 10 MHz = 70 MHz total |
| EU (ETSI) band | 5 × 10 MHz = 50 MHz total |
| Sync interval | 100 ms (50 ms CCH + 50 ms SCH) |
| Control Channel | IEEE Ch. 178, 5.900 GHz |

---

# Part A — Exercises (Study Guide Section 4)

## 4.1 VANET Fundamentals and Architecture

**1. Define VANET; place it in the taxonomy.**
**VANET (Vehicular Ad-Hoc Network)** is an application of **MANET (Mobile Ad-Hoc Network)** that uses moving vehicles themselves as the network's nodes, forming a mobile ad-hoc network on the road. Within the broader Wireless Ad-Hoc Network (WANET) taxonomy, VANET sits alongside other MANET applications like Wireless Mesh Networks and Wireless Sensor Networks — all are specializations of the general ad-hoc networking concept, distinguished by their node type and mobility pattern (VANET: vehicles, highly mobile but road-constrained; WSN: typically static or low-mobility sensors; WMN: semi-fixed mesh routers).

**2. Three major VANET components and their responsibility.**
- **OBU (On-Board Unit)** → **communication relay**: installed in the vehicle, provides wireless communication with other vehicles and infrastructure, integrates display/driver interaction.
- **RSU (Roadside Unit)** → **roadside connectivity**: deployed at intersections/hotspots, provides information and Internet access to vehicles within its radio coverage.
- **TA (Trusted Authority)** → **security/authentication**: installs secure parameters in the OBU, responsible for user authentication and security.

**3. OBU exchanging status 500m ahead vs. obtaining Internet near an intersection.**
(a) Exchanging status with a car 500 m ahead in the same lane is a **V2V exchange**, handled by the two vehicles' **OBUs** communicating directly, ad-hoc (within the stated ~300m–1km V2V range).
(b) Obtaining Internet access near an intersection is handled by the **RSU**, since RSUs are specifically "deployed at intersections and hotspots" to provide Internet access to vehicles within their coverage.

**4. Message flow from local control to a V2V accident-prevention application.**
In order: **Local Control** (steering, brakes, throttle — the vehicle's own physical control loops) → **In-Car Network** (connects local control systems together within the vehicle) → **Driver Control** (the layer where driver inputs/awareness interface with the vehicle) → out through the **V2V network** (ad-hoc communication between vehicles) → to **accident-prevention applications** (which, per the lecture's conceptual data-flow diagram, may act by informing the driver or, in more advanced cases, by direct intervention/actuation that can pass by driver control).

**5. Gap-closing time calculation.**
Initial gap = 800 m; needs to close to 300 m, so the gap must shrink by **800 − 300 = 500 m**.
Relative closing speed = 20 km/h = 20×1000/3600 ≈ **5.556 m/s.**
Time = 500 / 5.556 ≈ **90 seconds.**

**6. Five (⚠️ actually six) Smart Vehicle components, matched to function.**
- **Radar** (front/reversing) → **safety**: environmental sensing, e.g. collision/blind-spot detection (feeds LCA, CCW-type functions).
- **GPS/Positioning** → **safety and convenience**: vehicle positioning and driving assistance/navigation.
- **Computing System** → **safety and convenience** (supporting function): processes all collected information for every other function.
- **Display** → **convenience**: driver interface for information and interaction.
- **Communication System** → **safety and convenience**: enables V2V and V2I exchange underlying nearly every VANET application.
- **Event Recorder** → **safety** (post-hoc): records events like an aircraft "black box," supporting post-crash investigation.

## 4.2 V2X Communication Patterns and Taxonomy of Use Cases (with Numericals)

**7. Three V2X communication patterns, with an example each.**
- **"...to vehicle" (V2V)**: direct vehicle-to-vehicle exchange — e.g., **EEBL**, where a hard-braking vehicle broadcasts a warning directly to nearby vehicles.
- **"...to infrastructure" (V2I)**: vehicle-to-roadside — e.g., an **RSU** at an intersection providing traffic/road condition information or Internet access.
- **"...to home" (V2H)**: 💡 the lecture labels this pattern in its V2X illustration but doesn't detail a specific example — a reasonable inferred instance would be a vehicle relaying trip/status data to a home hub (e.g., pre-conditioning a garage door or charging schedule as the vehicle approaches), though this isn't elaborated on in the slides themselves.

**8. Classify by the Taxonomy-of-Use-Cases diagram.**
(a) **Adaptive Cruise Control** → **Safety / Situation-Awareness.**
(b) **Congestion Information** → **Non-Safety / Traffic-Information** (Congestion, Accident Information).
(c) **Traffic Light Violation warning** → **Safety / Warning-Message.**
(d) **In-vehicle entertainment** → **Non-Safety / Comfort** (Entertainment).

**9. Why a safety message can tolerate lower per-transmission reliability yet the overall function stays highly reliable.**
Safety messages like BSMs are **periodic and frequently repeated** (e.g., 10 Hz — every 100 ms). If any single transmission is lost, the *next* one, arriving just moments later with fresh (or nearly identical) status information, gives the receiving vehicle another chance to learn the same critical fact. So the safety **function's** overall reliability emerges from this **high repetition rate** — the system doesn't need any one packet to be perfectly reliable, because the cost of occasionally missing one packet is quickly compensated for by the next, arriving well within the application's latency tolerance.

**10. Hazard-warning re-broadcast count over a 2-minute window.**
2 minutes = 120 s. Re-sent every 10 s → **120/10 = 12 messages** (broadcasts at t=0, 10, 20, ..., 110 s, spanning the full 120 s window). 💡 If you count inclusive of both the window's start and end boundary, this could read as 13 — but 12 is the standard count for "how many times within a 120 s span, resent every 10 s."

## 4.3 Safety Applications: EEBL, PCN, LCA, CCW (with Numericals)

**11. How EEBL overcomes conventional brake-light visibility limits.**
Conventional brake lights only work if the following driver can **directly see** them — a problem when a large truck, fog, or heavy rain blocks the view. EEBL instead **broadcasts** a Basic Safety Message wirelessly the instant hard braking occurs, reaching every nearby vehicle within range **regardless of line of sight.** Two additional pieces of information an EEBL BSM can carry beyond "braking is happening": **deceleration rate** and **duration of braking.**

**12. Car B (no LOS to the truck) still gets a timely EEBL warning — step by step.**
1. The truck brakes hard and broadcasts an EEBL BSM to all vehicles within range.
2. Car A, directly behind the truck, receives this BSM (and/or sees the physical brake lights) and begins braking in response.
3. Car A, now itself braking hard, **also** broadcasts its own EEBL BSM.
4. Car B — even with no direct line of sight (or direct wireless range) to the *truck* — is within range of **Car A's** broadcast, and receives Car A's EEBL warning.
5. Car B gets a timely alert **relayed** through Car A's own hard-braking event, even though it never had any visibility (physical or wireless) to the original triggering vehicle.

**13. PCN trigger and the two vehicle-state variables used.**
PCN detects a collision/incident based on: **vehicle speed** and **deceleration rate** — an abnormal, sudden combination of these two (e.g., a sharp, unplanned speed drop) signals a likely collision event, triggering the notification.

**14. LCA closing-time calculation.**
Distance = 40 m; relative closing speed = 20 km/h = 20×1000/3600 ≈ **5.556 m/s.**
Time = 40/5.556 ≈ **7.2 seconds** before the adjacent-lane vehicle reaches the driver's position.

**15. Traditional (sensor-only) vs. wireless-based CCW.**
Traditional CCW relies on **direct physical sensors** (radar, lidar, camera) monitoring the vehicle's immediate front, rear, left, and right — it can only detect what's within its own sensors' physical line of sight/range. Wireless-based CCW instead builds awareness by **receiving wireless status messages** from nearby vehicles (which also transmit their own status) — since this doesn't depend on physical sensing at all, it can build awareness of vehicles **no physical sensor could ever detect**, such as a vehicle two cars ahead (blocked from any of your own sensors by the car directly in front of you, but still broadcasting its own wireless status which propagates independently of physical line-of-sight sensing).

**16. Why MVEDR storage is useful even though CCW's purpose is prevention.**
Even though CCW's primary goal is to **prevent** collisions, the data it continuously calculates and stores (relative safety distances, vehicle states leading up to any incident) becomes a valuable **forensic record** if an accident does occur despite prevention efforts — supporting post-accident investigation and reconstruction, much like an aircraft's black box helps investigators understand what happened even though the aircraft's systems were designed to prevent the incident in the first place.

## 4.4 IEEE 802.11p PHY/MAC and Differences from 802.11a (with Numericals)

**17. Subcarrier spacing for 802.11a and 802.11p.**
⚠️ As flagged above: spacing = bandwidth ÷ **FFT size (64)**, not ÷52 (the count of *used* subcarriers) — using 52 gives ≈384.6 kHz, which doesn't match the target.
**802.11a**: 20 MHz / 64 = **312.5 kHz** ✓
**802.11p**: 10 MHz / 64 = **156.25 kHz** ✓ (halved bandwidth, same FFT size → halved spacing)

**18. OFDM symbol duration.**
Symbol duration = 1/spacing gives the **useful (FFT) portion** only: 802.11a → 1/312.5kHz = **3.2 µs**; 802.11p → 1/156.25kHz = **6.4 µs**. Adding the standard guard interval (0.8 µs for 802.11a, 1.6 µs for 802.11p — itself doubled along with everything else) gives the **total** symbol duration quoted in the slides:
**802.11a: 3.2 + 0.8 = 4 µs** ✓ **802.11p: 6.4 + 1.6 = 8 µs** ✓

**19. Why doubling guard time/FFT period/preamble improves multipath robustness.**
A longer guard interval (cyclic prefix) can "absorb" a longer span of delayed multipath echoes without those echoes bleeding into (interfering with) the *next* symbol — so doubling these durations directly raises the maximum multipath delay spread the receiver can tolerate before inter-symbol interference sets in, which matters because vehicular environments (high speeds, reflective surroundings like other vehicles and roadside structures) typically produce more severe and longer multipath spreads than a typical stationary indoor/office 802.11a deployment.

**20. 802.11p bit-rate set (half of 802.11a's).**
802.11a: {6, 9, 12, 18, 24, 36, 48, 54} Mbit/s → halved:
**802.11p: {3, 4.5, 6, 9, 12, 18, 24, 27} Mbit/s** ✓ confirmed.

**21. 300-byte BSM transmission time at 3 Mbit/s vs. 27 Mbit/s.**
At 3 Mbit/s: T = (300×8)/(3×10⁶) = 2400/3,000,000 = **800 µs.**
At 27 Mbit/s: T = 2400/27,000,000 ≈ **88.89 µs.**
The lowest rate takes **exactly 9× longer** than the highest rate (matching the 27/3 = 9 ratio between the two data rates directly).

**22. At least four reasons plain 802.11{a,b,g,n} is unsuited for Car-to-X.**
- Cannot be in **infrastructure mode and ad hoc mode at the same time.**
- **Switching time** (between modes/networks) is too slow for vehicular contact windows.
- **Association time** is too slow — vehicles pass each other or an RSU too quickly for a full beacon→auth→association handshake.
- **No integral within-network security.**
- **No integral QoS** (no built-in prioritization for safety-critical traffic).
- **Shared, congested ISM spectrum**, prone to interference from unrelated devices.
- **Multipath effects reduce range and speed** in the standard 802.11a/b/g/n configuration.

**23. Classic BSS join vs. WAVE mode; why WAVE avoids join overhead.**
The **classic BSS** model is **SSID-based**: a node belongs to exactly one BSS, packets carry a BSSID, and foreign-BSS packets are ignored. Joining requires an explicit multi-step handshake: the AP sends a **beacon**, then an **authentication dialogue**, then an **association dialogue** — only after all three does the node officially belong to the BSS. **WAVE mode** instead defaults to a **wildcard BSSID**: a provider broadcasts an on-demand beacon containing everything a user needs to configure its lower layers and start using the service immediately — **no formal join process** at all. BSS membership is merely **implied** once a beacon has been received and used, and the BSS even continues to exist after the original provider leaves. WAVE avoids the classic join overhead because vehicular contact windows (fast-moving vehicles, brief encounters with an RSU) are often far too short to tolerate a full beacon→authentication→association handshake's latency — direct, immediate use of an advertised service is essential given how fleeting these contact opportunities are.

## 4.5 EDCA/HCF QoS in IEEE 802.11p (with Numericals)

**24. Four Access Categories, increasing priority; which serves safety-critical messages.**
**AC0 (AC_BK) → AC1 (AC_BE) → AC2 (AC_VI) → AC3 (AC_VO)**, lowest to highest priority.
**AC_VO (AC3)** is used for safety-critical messages such as BSMs — it gets the shortest AIFS and smallest contention window.

**25. AIFS[AC] for AIFSN {9, 6, 3, 2}, SIFS=32µs, SlotTime=13µs.**
AIFS[AC] = SIFS + AIFSN[AC] × SlotTime:

| AC | AIFSN | AIFS |
|---|---|---|
| AC0 | 9 | 32 + 9×13 = **149 µs** |
| AC1 | 6 | 32 + 6×13 = **110 µs** |
| AC2 | 3 | 32 + 3×13 = **71 µs** |
| AC3 | 2 | 32 + 2×13 = **58 µs** |

**26. CWmin for AC_VI and AC_VO, CWmin=15.**
CW_AC_VI_min = ⌈(15+1)/2⌉ − 1 = ⌈16/2⌉ − 1 = 8 − 1 = **7** ✓
CW_AC_VO_min = ⌈(15+1)/4⌉ − 1 = ⌈16/4⌉ − 1 = 4 − 1 = **3** ✓

**27. What a "virtual collision" is, and why it can occur with only one radio.**
A virtual collision happens when **two or more of a single station's own internal AC queues** both reach a backoff counter of 0 **at the same instant** — both queues are simultaneously "ready to transmit." Even though the station has only **one physical radio** (so only one frame can actually go out over the air at a time), this is a genuine internal scheduling conflict that must be resolved *within* the station: the **higher-priority AC is granted the actual transmission**, while the lower-priority AC's queue is treated exactly as if it had suffered a **real** external collision — its CW doubles and it re-enters backoff. It's called "virtual" because no real RF collision occurred on the shared medium; the conflict is purely internal, but it's resolved using the same collision-response logic as a real one.

**28. Why AC0 has the largest tw, and how this connects to the delay-vs-node-density plot.**
AC0 has by far the largest measured tw (264 µs) because it stacks **two** disadvantages: the **largest AIFSN (9)**, giving the longest AIFS (149 µs) before it can even begin its backoff countdown, **and** the **largest CWmin/CWmax (15/1023)**, giving it the widest possible/average random backoff range on top of that. Both factors compound into the longest average total wait. As node density grows (50 → 300 nodes in the End-to-End-Delay plot), **all** ACs face rising contention, but AC0 — already starting from the worst baseline and having the *least* aggressive priority parameters to protect it — has the least "headroom" to absorb the extra contention, so its delay **degrades fastest**, while higher-priority ACs (especially AC3/AC_VO, specifically tuned with a short AIFS and tiny CW) stay comparatively insulated as the network gets busier.

**29. AC_VO backoff at 0, channel becomes busy — step by step.**
1. AC_VO's backoff counter reaches **0**, meaning it's ready to transmit.
2. If the channel is (or becomes) **busy** right at that moment — whether from another station's transmission or an internally higher-priority queue winning a virtual collision — AC_VO **cannot** transmit immediately, even with its counter at 0; it must defer.
3. AC_VO waits for the channel to become **idle** again.
4. Once idle, it must wait a **fresh AIFS[AC_VO]** period (not just resume instantly) — this is a mandatory sensing interval before any access attempt, whether the counter is mid-countdown or already at 0.
5. If the channel stays idle through that entire AIFS wait, AC_VO — since its counter is still 0 — can transmit **immediately** at the end of the AIFS period. It does **not** redraw a random backoff, since this was a deferral due to a busy channel, not a failed/collided transmission.

## 4.6 WAVE/DSRC Channel Management and Protocol Stack (with Numericals)

**30. The five 1609.x components and what each governs.**
- **1609.1** → **resource management.**
- **1609.2** → **security services.**
- **1609.3** → **networking services**, including the WAVE Short Message Protocol (WSMP) — broadcasting of BSMs, and defining channel number/power per message.
- **1609.4** → **multi-channel operation** (channel switching/coordination between CCH and SCHs).
- **1609.11** → **application layer** — specifically, "electronic payment" services.

**31. Total U.S. DSRC spectrum vs. ETSI Europe.**
U.S.: 7 channels × 10 MHz = **70 MHz total.**
Europe (ETSI): 5 channels × 10 MHz = **50 MHz total.**
The U.S. allocates **20 MHz more (40% more spectrum)** than the European allocation.

**32. Sync intervals per second; CCH listening time per second.**
1 second = 1000 ms; 1000/100 = **10 full synchronization intervals per second.**
Each interval spends 50 ms on CCH → 10 × 50 = **500 ms per second** (i.e., exactly half the time) that a single-radio device spends listening on the Control Channel.

**33. WSA mechanism, step by step (Node A / Node B).**
1. **Node A** (provider) broadcasts a **WSA on the Control Channel (CCH)**, identifying which service(s)/BSS(s) are available, on which **Service Channel(s)**, plus the channel parameters needed to decode that SCH traffic.
2. **Node B** (user), which — like every single-radio WAVE device — periodically monitors the CCH, receives this WSA and learns the relevant SCH channel number and decode parameters.
3. Node B **switches (tunes)** to the announced Service Channel at the appropriate time.
4. Node A (or the relevant provider) transmits the actual **Data** (e.g., the Traffic Information Service content) on that SCH.
5. Node B, now correctly tuned and configured, **receives and decodes** the data — matching the lecture's Node A/Node B diagram: WSA (on CCH) → Data (on SCH) → Data (on SCH).

**34. Why safety messages stay on a dedicated, always-monitored channel rather than being spread across SCHs.**
Every single-radio WAVE device is **required** to periodically listen to the CCH regardless of which particular services it's individually interested in (per the fixed 1609.4 channel-switching schedule) — so placing BSMs there **guarantees** that every nearby vehicle, no matter what it's otherwise doing, will still reliably receive safety broadcasts. If BSMs were instead scattered across various SCHs (which vehicles only tune into selectively, based on individual WSA-driven service interest), there'd be no guarantee that all nearby vehicles are listening on the **same** channel at the **same** time to catch a given safety message — directly undermining the universal, time-critical reach safety applications require.

**35. The full WAVE protocol stack, in words.**
From the bottom up: **WAVE PHY** (IEEE 802.11p) → **WAVE MAC / LLC** (802.11p's CSMA/CA, with **1609.4** coordinating multi-channel operation/switching between CCH and SCH) → then two parallel columns running alongside the data path: **Security (1609.2)** and **Management** on one side, and the data path itself splitting into two options at the same layer: **WSMP** (1609.3, for lightweight WAVE Short Messages — BSMs, WSAs, WSMs) *or* the conventional **IPv6 → TCP/UDP → Internet Applications** path (for general-purpose IP-based services). Both WSMP and the standard Internet stack sit at the **same layer**, directly above LLC — giving WAVE nodes a choice: use the lightweight, low-latency custom WSMP for safety/service-advertisement traffic, or the standard Internet stack for general applications, both riding on the same underlying 802.11p PHY/MAC foundation.

## 4.7 Cellular vs. 802.11p, Challenges, and Propagation Models

**36. UMTS/LTE and 802.11p — two pros and two cons each.**
**UMTS/LTE pros**: easy provision of centralized services; pre-deployed infrastructure (already exists widely).
**UMTS/LTE cons**: high short-range latencies (potentially too high for safety-critical use); high dependence on the network operator.
**802.11p/ad hoc pros**: smallest possible latency; network load highly localized.
**802.11p/ad hoc cons**: needs a gateway (e.g., an RSU) for provision of centralized services; no pre-deployed hardware, and hardware is still expensive.

**37. Why VANET security is harder than typical MANET security.**
Under the lecture's **Security** challenge category: VANET has **"no (or no reliable) uplink to central infrastructure"** — unlike a MANET, which might occasionally reach a central authority for key distribution or revocation, VANET nodes often can't reliably reach a Trusted Authority in real time, undermining standard centralized security operations (certificate checks, revocation-list updates) exactly when they're most needed. VANET also has a **"heterogeneous user base"** — securing interactions among a huge, largely unrelated population of private vehicle owners raises trust-establishment and privacy trade-offs (balancing driver accountability against driver privacy) that a smaller, more controlled MANET deployment (e.g., a coordinated group of devices) typically doesn't face to the same degree.

**38. LOS vs. N-LOS: fading model and delay spread.**
**LOS** (direct visual line-of-sight between transmit and receive antennas) → modeled with the **Ricean** distribution.
**N-LOS** (no direct line of sight) → modeled with the **Rayleigh** distribution.
**N-LOS (Rayleigh) typically has the larger delay spread** — several times greater than LOS, per the lecture.

**39. Vehicle 1 (40 km/h) and Vehicle 2 (0 km/h, blocked by a truck around a bend), 200 m apart.**
This should be modeled as **N-LOS**, using the **Rayleigh** fading distribution — the scenario explicitly describes Vehicle 2 as "out of direct line of sight" with "a truck blocking the path," which is precisely the defining condition for a Non-Line-of-Sight link per the lecture.

**40. Why a hybrid (cellular + 802.11p) system is the practical conclusion.**
Cellular and 802.11p have **complementary** strengths and weaknesses: cellular offers reliable, pre-deployed, wide-area centralized delivery but can suffer from latency too high for the most time-critical safety alerts and heavy reliance on operator/core-network infrastructure; 802.11p offers the lowest possible latency and fully localized, operator-independent operation ideal for time-critical V2V safety messages, but lacks pre-deployed infrastructure everywhere and needs gateways (RSUs) for centralized services. Choosing one exclusively means inheriting **all** of that technology's weaknesses; deploying **both**, and dynamically choosing which to use depending on the specific application's latency/reliability needs and whichever infrastructure happens to be available in a given area, gives the best overall coverage and performance across the full range of VANET use cases.

---

# Part B — Sample Questions (Study Guide Section 5)

## 5.1 Short Questions

**1.** **Vehicular Ad-Hoc Network** — an application of **MANET (Mobile Ad-Hoc Network).**

**2.** **OBU, RSU, TA.**

**3.** **≈300 m – 1 km.**

**4.** Primary goal: **road safety.** Secondary/additional services: **value-added infotainment** (email/messaging, audio/video sharing, other infotainment services).

**5.** **On-Board Unit** — installed in vehicles to provide wireless communication, exchanging information with other vehicles and infrastructure; the key communication unit in Intelligent Transportation Systems.

**6.** **Roadside Unit** — typically deployed **at intersections and hotspots**, providing information and Internet access to vehicles within its radio coverage.

**7.** **Trusted Authority** — installs secure parameters in the OBU; responsible for **user authentication and security.**

**8.** ⚠️ Per the slide's own summary header list (matching the study guide's Topics Covered section): **High Mobility, Rapid Changing Network Topology, Predictable Mobility, No Power Constraint, Strict Time Management.** (Note: the same slide's prose explanation elsewhere swaps in "Wireless Communication" for "Predictable Mobility" — a minor internal inconsistency in the source material; I've gone with the header list.)

**9.** **Emergency Electronic Brake Light** — it solves the **limited visibility** problem of conventional brake lights, which only work when directly, visually visible (blocked by large trucks, fog, heavy rain); EEBL broadcasts wirelessly to all nearby vehicles regardless of line of sight.

**10.** Traditional CCW uses **direct physical sensors** (radar, lidar, camera) to detect vehicles within immediate sensor range/line of sight. Wireless-based CCW uses **wireless message exchange** instead, letting it build awareness of vehicles no physical sensor could ever detect (e.g., two cars ahead).

**11.** **52** OFDM subcarriers (same count as 802.11a); its channel bandwidth is **halved** — 10 MHz vs. 20 MHz for 802.11a.

**12.** **AC0 (AC_BK) → AC1 (AC_BE) → AC2 (AC_VI) → AC3 (AC_VO)**, lowest to highest priority.

**13.** A **WAVE Service Advertisement** — a broadcast that announces and describes services/data available on Service Channels; it's broadcast on the **Control Channel (CCH).**

**14.** **100 ms**, split into alternating **50 ms on CCH and 50 ms on SCH** (with short guard intervals at each slot boundary).

**15.** **LOS → Ricean distribution.** **N-LOS → Rayleigh distribution.**

## 5.2 Descriptive Questions

**16. Complete VANET architecture and message flow to a TA for authentication.**
The architecture rests on three components. **OBUs**, installed in vehicles, provide the wireless communication capability that lets a vehicle exchange information both with other vehicles (V2V) and with roadside infrastructure (V2I) — they integrate the display and driver interaction, serving as the vehicle's key ITS communication unit. **RSUs**, deployed at intersections and traffic hotspots, provide roadside connectivity: any OBU within an RSU's radio coverage gets access to information and, through the RSU's backhaul, the wider Internet. The **TA (Trusted Authority)** sits above this physical communication layer as the security anchor: it installs the secure parameters an OBU needs and is responsible for authenticating users. A typical message flow: a vehicle's OBU generates or forwards a message → if within V2V range, it can reach nearby vehicles' OBUs directly; if it needs to reach further, or needs an authenticated/secured exchange, it's relayed through a nearby RSU → the RSU, connected onward (via wired or wireless wide-area backhaul) to the broader network, can forward the message's authentication-relevant parameters up to the TA → the TA verifies the message/user against the secure parameters it originally issued, completing the authentication loop before the message (or the sender's continued participation) is trusted by the wider network.

**17. Safety vs. Non-Safety use cases — message frequency, packet size, latency, reliability.**
**Non-Safety** applications (e.g., in-vehicle entertainment, congestion information, route planning) are characterized by **many messages, high data rate, low latency demands, and low reliability demands** — a dropped or delayed infotainment packet is a minor inconvenience, not a hazard, so the system can afford to be relaxed about both timing and delivery guarantees while pushing large volumes of data. **Safety** applications (e.g., EEBL, Collision Warning, Traffic Light Violation) are the opposite profile: **few messages, small packet size, high latency demands, and high reliability demands** — a safety message must be small (to transmit and be processed almost instantly) and must reliably arrive within a tight deadline (often ~100 ms or less per the NHTSA table), because a late or lost safety warning can directly translate into a missed collision-avoidance opportunity. Despite the "high reliability demand" framing, note (per Exercise 9) that safety applications achieve their overall reliability through frequent repetition rather than requiring each individual transmission to be flawless.

**18. Four safety mechanisms — EEBL, PCN, LCA, CCW.**
**EEBL (Emergency Electronic Brake Light)** is triggered by a vehicle braking hard; it broadcasts a Basic Safety Message (including deceleration rate and braking duration) to nearby vehicles, extending the warning beyond direct line of sight — overcoming the visibility limits of conventional brake lights (blocked by trucks, fog, rain). **PCN (Post-Collision Notification)** is triggered by detecting a collision/incident, based on abnormal vehicle speed and deceleration-rate readings; it reports the post-crash event, helping identify and respond to incidents that have already occurred. **LCA (Lane Change Assist)** uses radar to continuously monitor blind spots and traffic behind the vehicle, measuring the closing speed of adjacent-lane vehicles to determine whether a lane change is currently safe, providing audible/visual warnings when it isn't — improving on a driver's own limited blind-spot visibility. **CCW (Cooperative Collision Warning)** exchanges static and dynamic vehicle information wirelessly with neighboring vehicles (rather than relying solely on physical sensors), calculating relative safety distances and storing data in the MVEDR — its wireless basis lets it build collision awareness of vehicles that traditional sensor-only systems (radar/lidar/camera, limited to direct physical detection range) simply cannot see, such as a vehicle two cars ahead.

**19. 802.11p vs. 802.11a — PHY and MAC differences, and why the PHY changes help.**
At the **PHY layer**: bandwidth is halved (10 MHz vs. 20 MHz), which — with the FFT size unchanged — halves the subcarrier spacing (156.25 kHz vs. 312.5 kHz), which in turn **doubles** the OFDM symbol duration (8 µs vs. 4 µs total, including guard interval), and correspondingly doubles the guard interval, FFT period, and preamble duration; bit rates are halved as a direct consequence (3–27 Mbit/s vs. 6–54 Mbit/s). Each of these PHY changes serves the **same underlying goal**: a longer symbol/guard time gives the receiver more tolerance for multipath delay spread and Doppler shift from high relative speeds — reflections and frequency shifts that would corrupt a shorter, faster 802.11a-style symbol have more "room" to settle within 802.11p's longer symbol window without causing inter-symbol interference. At the **MAC layer**: 802.11p adds a **random MAC address** (privacy), **EDCA-based QoS** (prioritizing safety-critical traffic over the same shared medium), **multi-frequency/multi-radio capability** (supporting the CCH/SCH channel-switching scheme), and a **new ad hoc mode** (the wildcard-BSSID WAVE mode, avoiding formal join overhead) — none of these are PHY changes, but together they adapt the classic 802.11a MAC for the specific demands of brief, high-speed, safety-critical vehicular contact.

**20. Full WAVE/DSRC protocol stack, and WSMP vs. conventional TCP/UDP/IPv6.**
Building on the **IEEE 802.11p** PHY/MAC foundation, the WAVE/1609.x family layers on top: **1609.4** governs multi-channel coordination directly above the MAC (deciding when the radio is on CCH vs. SCH); **1609.2** provides security services as a parallel column alongside the data path; **1609.3** provides networking services, including the **WSMP (WAVE Short Message Protocol)** — a lightweight alternative data path sitting at the same layer as a conventional **IPv6 → TCP/UDP** stack; and **1609.11** sits at the application layer, defining specific services like electronic payment. The key contrast: **WSMP** is a minimal, low-overhead protocol purpose-built for short, latency-sensitive WAVE messages (BSMs, WSAs, WSMs) — it skips the full IP addressing/routing/congestion-control machinery entirely. The **conventional path** (IPv6 → TCP/UDP → general Internet applications) instead gives WAVE nodes access to the full standard Internet application ecosystem, at the cost of the additional overhead that stack carries. Both paths run over the exact same underlying 802.11p PHY/MAC and 1609.4 channel coordination — the choice between them is made per-application, based on whether low-latency WAVE-native messaging or general IP connectivity is needed.

**21. DSRC channel management: CCH, SCH, sync interval, and WSA's role.**
The U.S. DSRC band reserves 7×10 MHz channels in the 5.850–5.925 GHz range: one dedicated **Control Channel (CCH, Ch. 178)**, four general-purpose **Service Channels (SCH)**, and two special-purpose channels (Critical Safety of Life at Ch. 172, Hi-Power Public Safety at Ch. 184). Time is divided into a fixed **100 ms synchronization interval**, itself split into alternating **50 ms on CCH** and **50 ms on SCH**, synchronized across devices via GPS receiver clocks, with a short **guard interval** at the start of each slot (during which the medium is treated as busy, forcing backoff) to absorb any residual timing drift between devices. Every single-radio WAVE device must periodically return to the CCH during its allotted window — this is where BSMs and, critically, **WAVE Service Advertisements (WSAs)** are broadcast. The WSA is the **only** mechanism by which a node learns what's being transmitted on a given SCH and how to decode it — without receiving a WSA on the CCH first, a vehicle has no way to know a given SCH's traffic even exists, let alone tune to and correctly decode it, which is exactly why safety-critical BSM traffic is kept on the universally-monitored CCH rather than scattered across the selectively-tuned SCHs.

## 5.3 Analysis and Design Questions

**22. City-wide EEBL and Curve Speed Warning deployment — design differences and AC assignment.**
Per the NHTSA table: **EEBL** ("Emergency Brake Lights") is **V2V, event-driven, P2M, 10Hz, 100ms latency, 300m range**; **Curve Speed Warning** is **I2V, periodic, P2M, 1Hz, 1s latency, 200m range.** The key design difference: EEBL is purely **vehicle-generated and V2V** — it requires **zero new infrastructure**, working anywhere cars are present, triggered only when hard braking actually occurs, with a very tight 100 ms latency budget. Curve Speed Warning, being **I2V**, is tied to a **fixed roadway feature** (the curve itself) rather than a dynamic vehicle event — it requires an **RSU physically installed at every relevant curve** city-wide, broadcasting periodically with a more relaxed 1 s latency budget. This makes Curve Speed Warning a much larger infrastructure-planning and capital-cost exercise than EEBL, which needs no roadside deployment at all. **AC assignment**: EEBL → **AC_VO (AC3)**, matching its event-driven, tight-100ms-latency, safety-critical profile (the same tier as BSM). Curve Speed Warning → **AC_VI (AC2)** is a reasonable fit — still safety-related and deserving priority over ordinary data, but its more relaxed 1 s latency and periodic (non-emergency) nature don't require the very top AC_VO tier reserved for the most urgent alerts.

**23. Cellular vs. 802.11p for a 50 km highway safety-warning system, no existing RSU.**
**Cellular** likely already has coverage along most highway corridors (existing cell towers), so it needs **no new infrastructure investment** specifically for this system — but its short-range latency may be too high for the tightest safety-message deadlines, and it depends heavily on the network operator and adds load to the core network even for purely local, nearby-vehicle communication. **802.11p** offers the lowest possible latency (ideal for the safety-warning use case) and fully localized V2V operation independent of any backend — but since the highway has **no existing RSU infrastructure**, and 802.11p needs RSUs specifically for any centralized/backend function, standing up full 802.11p coverage across 50 km would require a real new capital investment. 💡 Given safety warnings are fundamentally **V2V-local** (nearby vehicles alerting each other), and cellular coverage likely already exists: a **hybrid approach** is preferable — use 802.11p directly between nearby vehicles for the actual low-latency safety-critical warning propagation (which doesn't strictly need RSU coverage to function V2V-to-V2V), while leaning on the already-existing cellular network for wide-area coordination and backend services, deploying RSUs incrementally over time only at the highest-value locations (e.g., known accident black-spots) rather than the entire 50 km stretch up front.

**24. Vehicle transitioning city (RSU) → rural highway (no RSU) → tunnel (signal loss): patterns and propagation model per phase.**
**Phase 1 (city, RSU-covered)**: both **V2V and V2I** are available (RSU coverage exists). Propagation is a **mix**: dense urban surroundings (buildings, other vehicles) make many links **N-LOS (Rayleigh)**, though direct nearby-vehicle links can still be **LOS (Ricean)** depending on the specific pair and obstruction.
**Phase 2 (rural highway, no RSU)**: only **V2V** is available (no RSU means no V2I). On an open highway with fewer obstacles, same-lane vehicle links are much more likely to be **LOS (Ricean)** — consistent with the lecture's freeway characterization (1D mobility, bimodal connectivity: stable same-lane vs. unstable opposite-lane).
**Phase 3 (tunnel, complete signal loss, LOS blocked)**: by definition, **neither V2V nor V2I** is meaningfully available during actual complete signal loss. To whatever extent any residual multipath-reflected signal exists in the enclosed tunnel environment among very nearby vehicles, it would be modeled as **N-LOS (Rayleigh)**, with likely severe delay spread given the highly reflective, enclosed surroundings — but practically, this phase represents a real connectivity gap the vehicle's application layer needs to handle gracefully (e.g., falling back on locally cached data until signal returns).

**25. AC priority scheme for BSM, EEBL, infotainment audio, background SW update.**
**(a) 10 Hz BSM → AC_VO (AC3)**: explicitly the lecture's own stated example of AC_VO's intended use — safety-critical, shortest AIFS, smallest CW, ensuring consistently fast, low-jitter access for the periodic status broadcast.
**(b) Event-driven EEBL → AC_VO (AC3)**: equally safety-critical and even more latency-sensitive (100 ms deadline, event-triggered) — deserves the same top-tier treatment as BSM; EDCA differentiates by AC rather than by specific message type within an AC, so both legitimately share AC_VO.
**(c) Infotainment audio stream → AC_VI (AC2)**: matches the lecture's description of AC_VI as "non-critical but time-sensitive infotainment" — audio needs low jitter to sound acceptable, but carries no life-safety consequence.
**(d) Background software-update download → AC_BK (AC0)**: matches the lecture's explicit description of AC_BK as "low-priority background updates" — a large bulk transfer with no real-time deadline, appropriately given the lowest priority (largest AIFSN and CW), so it only uses the channel when nothing more urgent needs it.

**26. Channel choice for a pedestrian-crossing warning application (safety-critical, low data rate).**
💡 Given the U.S. DSRC channel plan — **Ch. 172 reserved for "Critical Safety of Life"**, **Ch. 178 as the Control Channel**, **Ch. 184 for Hi-Power/Dedicated Public Safety**, and shared SCHs in between — a pedestrian-crossing warning (inherently safety-critical, low data rate, needing guaranteed low-latency delivery) is the kind of traffic **Channel 172** was specifically designed for: it's the dedicated "safety-of-life" allocation, separate from both the general-purpose Control Channel (mainly reserved for management traffic and WSAs across *all* applications) and the shared SCHs (intended for general, non-safety data services that vehicles only tune into selectively). A reasonable design: broadcast the actual warning on **Ch. 172**, while still using a **WSA on the Control Channel (Ch. 178)** to make newly-arriving vehicles aware that this service exists and that they should also monitor Ch. 172 — combining the CCH's universal-reach guarantee with Ch. 172's dedicated, low-latency safety delivery.

**27. Why VANET is not "MANET on wheels" — at least three specific differences and their protocol-design consequences.**
1. **Topology dynamics / mobility model**: VANET nodes move at consistently high speed but with **predictable** mobility (constrained to road topology, known speed limits, lane structure), unlike MANET's more arbitrary, unconstrained mobility. **Consequence**: VANET routing/connectivity protocols can (and should) exploit this predictability — e.g., anticipating link breaks before they happen, using road-topology-aware geo-routing — rather than relying on the more purely reactive approaches typical MANET protocols use for genuinely unpredictable movement.
2. **Communication patterns**: VANET traffic is dominated by frequent, small, **broadcast/periodic** status messages (BSM/CAM — unidirectional, no response expected), rather than the more bidirectional, session-oriented, often-unicast traffic typical of MANET. **Consequence**: VANET MAC design (EDCA prioritization, a dedicated always-monitored CCH for safety broadcasts) is built around efficiently supporting massive periodic one-to-many broadcast traffic, rather than optimizing point-to-point unicast throughput/reliability the way many MANET protocols do.
3. **Infrastructure availability**: VANET commonly has at least *partial* infrastructure available (RSUs, a Trusted Authority, cellular backhaul) and is explicitly designed to operate across a spectrum from pure ad hoc to fully infrastructure-assisted, whereas classic MANET is defined by the assumption of essentially **no** fixed infrastructure. **Consequence**: VANET protocol and security design can lean on infrastructure-provided services (TA-based authentication, RSU-relayed wide-area information) in ways pure MANET protocols, built to assume zero infrastructure, generally cannot.
4. 💡 *(Bonus, a fourth difference)* **Power constraints**: VANET nodes draw on an effectively unlimited vehicle battery/alternator supply, unlike typical (often battery-limited) MANET nodes. **Consequence**: VANET protocols don't need the aggressive power-conservation/duty-cycling optimizations central to much MANET protocol design, freeing them to prioritize timeliness and throughput instead.
