# Lecture 2: Overview of Wireless Access Networks

> **Course:** CSE 4615 — Wireless Networks (IUT)
> **Scope:** Answers to **every** numbered item in the suggestion PDF — all **Exercises (§4.1–4.7, E1–E32)** *and* all **Sample Questions (§5.1–5.3, S1–S32)** — with full depth, plus a conceptual deep-dive, exam pointers, common mistakes, tricks, and a reference/formula sheet. Data values (WLAN rates, WMN challenges, Bluetooth states) are taken from the actual lecture slides.

---

## 1. Lecture Overview

This lecture maps **how end systems connect to the Internet** and then **classifies every kind of wireless access network.**

It starts at the **network edge** (your device → the **first/edge router**), reviews the **protocol stack** (transport: multiplexing/reliability/congestion control; network: routing/forwarding/QoS), and the split into **network edge, core, and physical media**. It then covers **wired access** (DSL, cable, Ethernet) before classifying **wireless access** using two questions:

1. **Single-hop or multi-hop?** — does traffic reach the wired network in **one wireless hop**, or **relay** through other wireless nodes?
2. **Infrastructure-based or infrastructure-less?** — is there a **base station/AP backbone**, or is it **peer-to-peer/ad hoc**?

These create a **four-quadrant taxonomy** populated by: **Cellular, WLAN, WiMAX** (single-hop, infrastructure); **Bluetooth** (single-hop, ad hoc); **Wireless Mesh** (multi-hop, infrastructure); and **Ad-hoc/WSN/VANET/DTN** (multi-hop, infrastructure-less). The payoff: **place any real system in the right quadrant and justify it**, and know each technology's frequency, range, rate, and role.

---

## 2. Suggestion Questions and Answers

> **Part A — Exercises (E1–E32).**  **Part B — Sample Questions (S1–S32).**
> Some sample questions revisit exercise topics in greater depth; each is answered on its own, with shared reference tables in §7.

### — Part A: EXERCISES —

#### 4.1 Access Networks and Wired Technologies

### E1 — Labeled DSL access network diagram (premises, line, splitter, DSLAM, ISP).
**Answer:** *Components in order (describe as a left-to-right diagram):*
**Subscriber premises** (home PC + **DSL modem**) → **telephone line (copper twisted pair)** → at the home a **splitter** separates voice (low band) from data → the line runs to the **central office**, where a **DSLAM (DSL Access Multiplexer)** aggregates many subscriber lines and forwards **data to the ISP** (and voice to the PSTN).
**Key idea:** voice and data **coexist on the same copper** in **different frequency bands**; the splitter keeps them apart; the DSLAM is the aggregation/uplink point.

### E2 — How FDM separates video channels and data in cable networks.
**Answer:** Cable uses **Frequency Division Multiplexing** on the coaxial cable: the broadband spectrum is **divided into many frequency channels**, each carrying a different **TV channel**, with **separate bands reserved for upstream/downstream data**. Because frequencies don't overlap, video and data **travel simultaneously** without interfering. Note: unlike DSL, the cable medium is **shared among neighbors** (contention for the data band).

### E3 — Compare DSL and cable (technology, shared medium, data rates).
**Answer:**

| Attribute | DSL | Cable |
|---|---|---|
| Medium | Telephone **twisted pair** | **Coaxial** TV cable |
| Sharing | **Dedicated** per subscriber | **Shared** among neighbors (HFC) |
| Multiplexing | Frequency bands (voice/up/down) | **FDM** (many channels) + shared data band |
| Rate behavior | Stable, **distance-sensitive** (drops with line length) | Higher peak, but **drops as neighbors load** the shared band |
| Typical rates | a few–tens of Mbps | tens–hundreds of Mbps (shared) |

### E4 — Role of the edge router; why "first router on the path"?
**Answer:** The **edge router** is the **boundary device where the access network meets the ISP/core**. It is the **first router a packet from an end system reaches** on its way into the Internet (and the last on the way back). It performs the initial **routing/forwarding** into the core. The name reflects its position: the very first **Layer-3 routing** hop on the path from host to destination.

#### 4.2 Wireless Network Components and Modes

### E5 — Four components of a wireless network + real example each.
**Answer:**
1. **Wireless host** — end device sending/receiving (laptop, phone, sensor).
2. **Wireless link** — the radio channel connecting host to base station/other host (Wi-Fi/cellular air interface).
3. **Base station** — fixed infrastructure relaying to the wired net (cell tower, Wi-Fi **AP**).
4. **Network infrastructure** — the wired backbone/core behind the base station (ISP/Internet, switches/routers).

### E6 — Compare infrastructure vs ad hoc mode (+2 examples each).
**Answer:**
- **Infrastructure mode:** all traffic goes **through a base station/AP**; managed, fixed topology. *Examples:* home/campus Wi-Fi (AP), cellular network (tower).
- **Ad hoc mode:** **no infrastructure**, nodes communicate **peer-to-peer**; dynamic, self-organizing. *Examples:* Bluetooth piconet, MANET (e.g., disaster/military mesh of laptops).

### E7 — Fill the four-quadrant table (≥2 examples per cell).
**Answer:**

| | Infrastructure-based | Infrastructure-less |
|---|---|---|
| **Single-hop** | Cellular (3G/4G/5G), **WLAN (802.11)**, WiMAX (802.16) | Bluetooth piconet, single-hop ad hoc |
| **Multi-hop** | **Wireless Mesh Networks (WMN)** | MANET, **WSN**, VANET, DTN |

### E8 — 802.11g campus APs: which quadrant? Justify.
**Answer:** **Single-hop, infrastructure-based.** Each device reaches an **AP (base station) in one wireless hop**, and the APs connect to the wired campus backbone — so there is an **infrastructure** and **one wireless hop** to it. (It is not multi-hop because devices don't relay through each other; not ad hoc because an AP backbone exists.)

#### 4.3 Single-Hop Infrastructure-Based Systems

### E9 — Draw & label the 3G cellular data architecture.
**Answer:** *(describe the chain):* **Mobile host → Base Station (Node B)** over the air → **Radio Access Network (RAN)** managing radio resources/soft handoff → **MTSO (Mobile Telephone Switching Office)** doing switching, mobility management, and **handoff** → connection to **PSTN / Internet core**. Capacity comes from **cell-based frequency reuse**; the MTSO coordinates which base station serves a moving user.

### E10 — Cell reuse; why shrinking cells increases capacity; trade-offs.
**Answer:** **Cell reuse** = the same frequencies/timeslots/codes are **reused at spatially separated cells** (far enough apart to limit interference). **Shrinking cells** packs **more cells per area**, so each frequency is reused more often → **more total capacity** and more users served. **Trade-offs:** more cells → **more base stations (cost)**, **more frequent handoffs**, and **greater co-channel interference risk** if cells are too close.

### E11 — Tabulate 802.11 standards (band + max rate).
**Answer:** *(from the lecture slides)*

| Standard | Band | Max data rate |
|---|---|---|
| 802.11b | 2.4–2.485 GHz | up to **11 Mbps** |
| 802.11a | 5.1–5.8 GHz | up to **54 Mbps** |
| 802.11g | 2.4–2.485 GHz | up to **54 Mbps** |
| 802.11n (Wi-Fi 4) | 2.4 & 5 GHz | up to **600 Mbps** |
| 802.11ac (Wi-Fi 5) | 5 GHz | up to **6.9 Gbps** |
| 802.11ax (Wi-Fi 6/6E) | 2.4/5/6 GHz | up to **9.6 Gbps** |
| 802.11be (Wi-Fi 7) | 2.4/5/6 GHz | targeting **>30 Gbps** |

### E12 — How WiMAX serves as a DSL/cable alternative for last-mile.
**Answer:** **WiMAX (IEEE 802.16)** delivers **long-range wireless broadband** from a base station to subscribers, covering the **"last mile"** **without laying cable/telephone lines**. It supports **triple-play (voice/data/video)** and reaches areas where DSL/cable are uneconomical — ideal for **rural/underserved** regions.

### E13 — DSLAM (DSL) vs base station controller (cellular).
**Answer:** Both **aggregate many access links into the core**, but: the **DSLAM** aggregates **wired DSL subscriber lines** at the central office and forwards data to the ISP (no mobility). The **base station / its controller** aggregates **wireless cellular links**, additionally managing **radio resources, power control, and handoff** for **mobile** users. *DSLAM = wired aggregation; base-station controller = wireless aggregation + mobility management.*

#### 4.4 Bluetooth and Single-Hop Ad Hoc

### E14 — Bluetooth piconet: 1 master, 4 slaves (2 Parked, 1 Standby).
**Answer:** *(describe diagram):* a central **Master** connected to **slaves**; the master controls the hopping/clock. Mark two slaves **Parked** (still **synchronized** to the master but **not actively communicating**), one **Standby** (**idle, not connected** to any piconet), and the remaining slave **Active**. **Up to 7 slaves can be active** simultaneously; only the **master initiates/controls** communication.

### E15 — Compare Bluetooth vs Wi-Fi (range, rate, topology, use).
**Answer:**

| Attribute | Bluetooth (802.15.1) | Wi-Fi (802.11) |
|---|---|---|
| Range | **~10 m** (short) | **~100 m** |
| Data rate | low–moderate (Mbps) | high (tens of Mbps–Gbps) |
| Topology | **piconet** (master/slave, ad hoc) | infrastructure (AP) / ad hoc |
| Power | very low | higher |
| Typical use | **peripherals/PAN** (headset, mouse) | LAN/Internet access |

#### 4.5 Wireless Mesh Networks

### E16 — Roles of mesh routers vs mesh clients.
**Answer:** **Mesh routers (MRs):** **fixed backbone** nodes that **route/relay** traffic multi-hop and often act as **Internet gateways**; abundant power. **Mesh clients (MCs):** **end-user devices** (laptops, phones, sensors) that **send/receive their own traffic** and may connect to MRs or each other; limited routing role, often mobile.

### E17 — Self-healing and self-configuration with examples.
**Answer:**
- **Self-healing:** if a node/link **fails**, the network **automatically reroutes** traffic via alternative paths → high reliability. *Example:* a mesh router goes down; neighbors detect the break and forward through a different router.
- **Self-configuration:** a **new node joins** and **starts routing without manual setup**, discovering neighbors dynamically. *Example:* adding a mesh router to extend coverage — it auto-integrates into routing.

### E18 — The eight WMN challenges (one problem + one mitigation each).
**Answer:** *(the lecture lists exactly eight):*
1. **Interference/shared medium** — co-channel/hidden/exposed terminals → *mitigate:* multi-radio/multi-channel, directional antennas, smart channel assignment.
2. **Scalability** — routing overhead/contention grow with nodes → *hierarchical routing, gateways*.
3. **Dynamic topology & routing complexity** — frequent route breaks → *adaptive routing, fast convergence*.
4. **Limited bandwidth/throughput** — each extra hop reduces bandwidth → *fewer hops, capacity-aware placement, multi-channel*.
5. **Security threats** — eavesdropping/spoofing/DoS/routing attacks → *encryption, authentication, secure routing*.
6. **Quality of Service (QoS)** — hard latency/jitter guarantees → *traffic prioritization, admission control*.
7. **Synchronization & coordination** — distributed scheduling/clock sync → *time-sync protocols, coordinated MAC*.
8. **Heterogeneity of devices** — differing capabilities/protocols → *standard interfaces, gateways/translation*.

### E19 — Two real WMN applications and why mesh suits them.
**Answer:** *(from slides):*
- **Maritime mesh network** — ships/buoys relay over water where no fixed infrastructure exists; **multi-hop** extends coverage across the sea surface.
- **Smart & connected city** (or **community broadband backbone**) — many static/mobile devices; mesh provides **flexible, self-healing, gateway-connected** coverage without cabling every node.
*(Others: military battlefield, drone/UAV mesh, large-scale agriculture with mobile machinery.)*

#### 4.6 Ad-Hoc, Sensor, Vehicular, Delay-Tolerant

### E20 — Contrast Ad-Hoc vs Mesh (≥5 attributes).
**Answer:**

| Attribute | Wireless Mesh (WMN) | Ad-Hoc (MANET) |
|---|---|---|
| Backbone | **Semi-infrastructure** (fixed mesh routers) | **Purely infrastructure-less** |
| Mobility | Routers static, clients may move | All nodes typically mobile |
| Topology | Relatively stable | Frequently changing |
| Internet gateways | Yes | Usually none |
| Energy | Routers often **powered** | **Battery-operated** |
| Reliability | Higher | Lower (frequent route breaks) |

### E21 — Three characteristics shared by WSN, VANET, DTN.
**Answer:** All three are **(1) infrastructure-less / self-organizing**, **(2) multi-hop with dynamic topology** (due to node failure/sleep, mobility, or intermittent links), and **(3) decentralized** (no central controller). They also typically face **resource constraints** and unreliable links.

### E22 — Why energy is WSN's primary constraint; sleep modes' help & problems.
**Answer:** Sensor nodes are **tiny, numerous, battery-powered, and often unreachable**, so **battery life dictates network lifetime** — sensing, processing, and especially **radio** all drain energy. **Sleep modes** turn radios off to **save energy** (extending lifetime). **Problems introduced:** a sleeping node **can't receive/forward** → **added latency**, possible **missed events**, harder **synchronization/coordination**, and routing complexity (must wake the right nodes). *Trade-off:* **lifetime vs delay/throughput.**

### E23 — V2V and V2I with one ITS example each.
**Answer:** **V2V (vehicle-to-vehicle):** direct car-to-car messaging. *ITS example:* **collision/brake warning** in a platoon. **V2I (vehicle-to-infrastructure):** car ↔ **roadside unit (RSU)**. *ITS example:* **traffic-signal/AIM coordination** or speed advisories at an intersection.

### E24 — Autonomous Intersection Management (AIM) + benefits.
**Answer:** In **AIM**, vehicles broadcast position/speed/intent (V2V) and coordinate with an **intersection manager (V2I/RSU)** that **schedules conflict-free crossing slots**, so cars **cross without stopping**. **Benefits over signals:** **higher throughput**, **less idling/emissions**, **lower delay**, and potentially **fewer collisions** — at the cost of strict reliability/security needs.

### E25 — Store-and-forward in DTNs.
**Answer:** A node **stores** a message (**bundle**) in persistent memory when **no next hop is available**, **carries** it, and **forwards** it when a **contact/link opportunity** appears. This **store-carry-forward** tolerates **long delays and intermittent connectivity** instead of needing a continuous end-to-end path.

### E26 — Compare DTN vs traditional Internet (delay, connectivity, reliability).
**Answer:**

| Aspect | Traditional Internet | DTN |
|---|---|---|
| Delay | Low, bounded | **Very large**, variable |
| Connectivity | **Continuous** end-to-end path | **Intermittent**, opportunistic |
| Reliability | TCP/ARQ end-to-end ACKs | **Hop-by-hop custody** (no classic end-to-end ARQ) |
| Path assumption | Always exists | **May never** exist simultaneously |

*Why TCP fails in DTN:* it assumes a continuous path and quick ACKs → **times out** under huge delay/disconnection.

#### 4.7 Comparison and Analysis

### E27 — Comparison table: Cellular, WLAN, WiMAX, Bluetooth, WMN.
**Answer:**

| Tech | Frequency | Range | Data rate | Infrastructure | Primary use |
|---|---|---|---|---|---|
| Cellular | licensed (sub-6/mmWave) | km | high | Yes | Wide-area mobile |
| WLAN (802.11) | 2.4/5/6 GHz ISM | ~100 m | high (Mbps–Gbps) | Yes | LAN/campus |
| WiMAX (802.16) | licensed/unlicensed µwave | km | high | Yes | Last-mile broadband |
| Bluetooth (802.15.1) | 2.4 GHz ISM | ~10 m | low–med | No | Peripherals/PAN |
| WMN | varies (often ISM) | wide (multi-hop) | medium | Semi (routers) | City/community coverage |

### E28 — Compare WSN, VANET, DTN (+ primary application domain).
**Answer:**

| Feature | WSN | VANET | DTN |
|---|---|---|---|
| Infrastructure | infra-less (sink) | infra-less (RSUs optional) | infra-less |
| Topology | dynamic (failure/sleep) | **highly dynamic** (mobility) | **intermittent** |
| Self-organizing | Yes | Yes | Yes |
| Primary constraint | **energy** | **mobility/safety** | **delay/disconnection** |
| Routing | data-centric to sink | geo/position-based | store-carry-forward |
| **Primary application domain** | environmental/industrial sensing | intelligent transport (ITS) | space/rural/disaster, wildlife |

### E29 — Four C2X challenge categories.
**Answer:**
1. **Channel conditions** — fast-varying, fading vehicular channel.
2. **Networking** — highly dynamic topology, scalability, short link lifetimes.
3. **Mobility** — rapid handoffs, brief contact windows, high speeds.
4. **Security** — authentication, integrity, privacy for safety-critical messages (a spoofed message can be dangerous).

### — Part B: SAMPLE QUESTIONS —

#### 5.1 Short Questions

### S1 — Define an access network; role in Internet architecture.
**Answer:** The network that **connects an end system to its first/edge router** (the "last mile"), bridging the user device to the Internet core. Examples: DSL/cable, campus Ethernet/Wi-Fi, cellular.

### S2 — What is an edge router?
**Answer:** The **first router on the path** from an end system into the core — the boundary where the access network meets the ISP. Packets enter/leave the Internet through it.

### S3 — Four access-network types by technology.
**Answer:** **Ethernet, Wi-Fi (WLAN), WiMAX, Cellular** (and **Low-PAN / IEEE 802.15** for sensors). Wired: **DSL, Cable**.

### S4 — Upstream vs downstream in DSL.
**Answer:** **Downstream** = ISP→user (download), the **higher** rate; **upstream** = user→ISP (upload), **lower**. DSL is **asymmetric (ADSL)** because users download more than they upload; voice/up/down occupy **separate frequency bands** on the same copper.

### S5 — Define base station; two examples.
**Answer:** Fixed infrastructure relaying between wireless hosts and the wired network, managing the radio link. **Examples:** **cellular tower** and **Wi-Fi access point (AP)**.

### S6 — What is a piconet in Bluetooth?
**Answer:** A small Bluetooth network: **one master + up to 7 active slaves** (plus parked/standby), all using **FHSS synchronized to the master's clock**.

### S7 — Two differences: infrastructure vs ad hoc.
**Answer:** (1) Infrastructure routes through a **base station/AP**; ad hoc is **peer-to-peer, no backbone**. (2) Infrastructure has a **fixed/managed** topology; ad hoc is **dynamic/self-organizing**.

### S8 — What is handoff in cellular networks?
**Answer:** Transferring an **active call/session from one cell to another** as a user moves, **without dropping** the connection; managed by the **MTSO**.

### S9 — Define co-channel interference.
**Answer:** Interference between cells that **reuse the same frequency channel**; it limits how closely frequencies can be reused (a cost of frequency reuse for capacity).

### S10 — WiMAX stands for / which IEEE standard?
**Answer:** **Worldwide Interoperability for Microwave Access**, the **IEEE 802.16** family; last-mile broadband wireless.

### S11 — Primary constraint in WSN design?
**Answer:** **Energy (battery)** — drives sleep cycles, data aggregation, low-power radios, and routing.

### S12 — Define store-and-forward (DTN).
**Answer:** Store a **bundle** when no next hop exists, **carry** it, and **forward** at the next contact — tolerating long delay/intermittent links.

### S13 — What is V2V? Safety example.
**Answer:** Direct **vehicle-to-vehicle** communication. *Safety example:* **collision/brake warning** so following cars react before seeing brake lights.

### S14 — Two differences: mesh router vs mesh client.
**Answer:** (1) Routers form the **fixed backbone and route/relay**; clients mainly send/receive **their own** traffic. (2) Routers have **more power + gateway role**; clients are simpler/often mobile.

### S15 — Two challenges of C2X communication.
**Answer:** Any two of: **channel conditions, networking (dynamic topology), mobility (fast handoffs), security/privacy.**

#### 5.2 Descriptive Questions

### S16 — Path of a packet: home DSL → web server (elements + layers).
**Answer:**
1. **Home PC** generates packet (app → transport → network → link → physical).
2. → **DSL modem** modulates data onto the line's data band.
3. → **Splitter** separates voice/data frequencies on the copper pair.
4. → **DSLAM** at the central office aggregates many lines, forwards data to the **ISP**.
5. → **Edge/first router** injects it into the **Internet core**, which **routes/forwards** (network layer) hop-by-hop.
6. → Destination **edge router** → **web server**.
*Layers:* application/transport end-to-end; network for routing/forwarding; link/physical per hop.

### S17 — Four-quadrant classification (≥2 examples each).
**Answer:** Two axes — **hops** (single/multi) and **infrastructure** (based/less):
- **Single + Infra:** Cellular, WLAN, WiMAX (host → base station in one hop → wired core).
- **Single + Ad hoc:** Bluetooth (one-hop peer-to-peer, no backbone).
- **Multi + Infra:** Wireless Mesh (relays through routers to a gateway).
- **Multi + Ad hoc:** MANET, WSN, VANET, DTN (nodes relay for each other, no backbone).

### S18 — 3G cellular architecture; roles of base station, RAN, MTSO.
**Answer:** Mobile ↔ **Base Station (Node B)** over the air. **RAN** manages radio resources and **soft handoff** across base stations. **MTSO** is the **core switch/control**: call setup, **mobility management, handoff**, and connection to **PSTN/Internet**. Capacity = **cell frequency reuse**; MTSO coordinates the serving cell for a moving user.

### S19 — How a WMN operates (router/client roles, multi-hop, self-healing/config).
**Answer:** **Mesh routers** form a **fixed multi-hop backbone**; **mesh clients** attach. Traffic relays **router-to-router** to a **gateway** to the Internet. **Self-configuration:** new routers auto-join and route. **Self-healing:** on failure, traffic **reroutes** automatically. This yields wide coverage without cabling.

### S20 — WMN challenges + 3 mitigations.
**Answer:** Pick any three of the eight (E18): e.g., **Interference** → multi-channel/directional antennas; **Scalability** → hierarchical routing/gateways; **Security** → encryption + secure routing. (Also QoS → prioritization; throughput → fewer hops; heterogeneity → standard interfaces.)

### S21 — Compare WMN vs Ad-Hoc (≥6 attributes); best for smart city.
**Answer:** Use the table in E20 plus: **WMN** has a **semi-fixed backbone, gateways, powered routers, stable topology, self-healing, higher reliability**; **MANET** is **fully peer/mobile, battery-limited, dynamic**. **Smart-city verdict → WMN**: stable backbone + gateways + self-healing scale better for sustained city-wide coverage.

### S22 — DTN store-and-forward; why Internet protocols fail.
**Answer:** DTN uses a **bundle layer** above transport with **store-carry-forward** and **hop-by-hop custody**. Conventional protocols (TCP/ARQ) assume a **continuous path + quick ACKs**, so they **time out** under **large delay/disconnection**; routing assumes persistent links. DTN instead exploits **intermittent contacts** and tolerates huge latency.

### S23 — VANETs: V2V, V2I, ≥3 ITS applications.
**Answer:** **V2V** = direct car-to-car safety messaging; **V2I** = car ↔ **RSU**. *ITS apps:* **AIM** (signal-free intersections), **platooning** (tight convoys, fuel/safety), **eco-driving / traffic optimization**, **cooperative perception / collision warning**.

### S24 — WSNs in precision agriculture & military; structured vs unstructured.
**Answer:** **Precision agriculture:** nodes **placed deliberately (structured)** in a grid for soil/moisture monitoring. **Military surveillance:** nodes **scattered randomly (unstructured)**, e.g., air-dropped in hostile terrain. The **application domain dictates structure** — controlled fields → planned/structured; inaccessible/hostile → random/unstructured, needing more self-organization and redundancy.

#### 5.3 Analysis and Design Questions

### S25 — Rural broadband: WiMAX vs WMN?
**Answer:** With **no cable/telephone** infrastructure: **WiMAX** gives long-range **single-hop last-mile** broadband from a tower (good if a tower + backhaul exist). **WMN** spreads coverage via **multi-hop relays** without towers (good for scattered homes, but throughput falls over hops). **Recommend:** long-range point-to-multipoint with backhaul → **WiMAX**; incremental, infrastructure-light coverage of dispersed homes → **WMN**. Justify by **range, throughput, cost, backhaul**.

### S26 — Hospital vital-sign monitoring: WSN, WMN, or WLAN?
**Answer:** Needs **reliable, low-latency, continuous** delivery indoors. **WLAN** = high rate/low latency but higher power; **WSN** = energy-efficient for many tiny sensors but lower rate/higher latency. **Recommend a WSN/WLAN hybrid:** energy-efficient **bedside sensors** feeding **Wi-Fi APs** — balancing **energy** (sensors) with **latency/reliability** (Wi-Fi) and ward-scale **range**. Pure WSN if power dominates; Wi-Fi if latency/reliability dominate.

### S27 — Disaster relief, infrastructure destroyed.
**Answer:** Deploy a **MANET (ad-hoc)** — or a **DTN** for sparse connectivity. Responders' devices **self-organize peer-to-peer**, relaying multi-hop without a backbone; where links are intermittent, **store-and-forward** carries messages until contact. **Justification:** infrastructure-less, rapid, self-healing — fits the missing-infrastructure scenario.

### S28 — AIM: how V2V/V2I removes signals.
**Answer:** Vehicles **broadcast position/speed/intent** (V2V) and coordinate with an **intersection manager (V2I/RSU)** that assigns **conflict-free crossing slots**, so cars cross in interleaved trajectories **without stopping** → **fixed signals become unnecessary**. Benefits: higher throughput, lower delay, less idling — needs strong reliability/security.

### S29 — ZebraNet-style wildlife tracking (DTN): challenges + design.
**Answer:**
- **Intermittent contacts** (animals rarely meet) → **store-and-forward** + ample buffering.
- **Energy scarcity** (solar/battery collars) → aggressive **duty-cycling/sleep**, low-power radios.
- **No fixed sinks** → **opportunistic/epidemic forwarding** to base stations when in range.
- **Unpredictable mobility** → delay-tolerant routing, redundancy to raise delivery probability.

### S30 — Bluetooth vs Wi-Fi vs WiMAX for three scenarios.
**Answer:**
- **(a) Peripherals to a laptop → Bluetooth** (short range, low power, simple piconet).
- **(b) Campus-wide Internet → Wi-Fi** (medium range, high rate, AP infrastructure for density).
- **(c) Rural village broadband → WiMAX** (long-range last-mile where wired infrastructure is absent).
Justify by **frequency, range, data rate**.

### S31 — V2V truck platooning: benefits + challenges.
**Answer:** **Benefits:** lead-truck braking is **broadcast instantly** → followers react in **ms (reduced brake lag)** → tight spacing → **drafting cuts fuel**; coordinated braking **improves safety**. **Challenges:** **communication** (reliable low-latency in fast channels), **security** (a spoofed "brake" is catastrophic → authentication/integrity), **mobility/scalability** as platoons form/dissolve.

### S32 — Single-hop infrastructure vs multi-hop ad-hoc for 10,000 IoT sensors over 50 km².
**Answer:** **Single-hop infrastructure** (cellular/LPWAN towers) = **managed/reliable** but **tower+backhaul cost** grows with coverage. **Multi-hop ad-hoc/mesh** = **no towers, self-organizing, cheap to scatter**, but suffers **per-hop throughput loss, routing overhead, relay energy drain**. **Verdict:** for **dense, low-rate, sparse-traffic** agricultural sensing over a large area, **multi-hop infrastructure-less** typically wins on **cost & coverage**, accepting lower per-node throughput and routing/energy overhead.

---

## 3. Conceptual Deep Dive

**Two axes organize the entire lecture.** *How many wireless hops?* and *Is there a backbone?* Internalize the **four-quadrant table** and you can place and justify any system. Most exam questions are secretly "which quadrant, and why?"

**The edge-to-core mental model.** The Internet is a highway (core); the **access network** is your driveway + on-ramp to the **first/edge router**. Wired access (DSL, cable, Ethernet) and wireless access are just **different on-ramps**.

**Wired access in one line each.**
- **DSL** = data + voice share **one phone line** in **different frequency bands**; **splitter** separates them; **DSLAM** aggregates at the central office; **dedicated** per subscriber.
- **Cable** = data shares the **TV coax** via **FDM**; but the medium is **shared among neighbors** (contention).

**Infrastructure vs ad hoc.** Infrastructure = "everything goes through the boss (AP/base station)." Ad hoc = "everyone talks directly, no boss." This single distinction explains topology stability, gateways, and management.

**The wireless families, connected.**
- **Single-hop + infra:** the "big three" with a backbone — **Cellular, Wi-Fi, WiMAX** (differ in range/rate/use).
- **Single-hop + ad hoc:** **Bluetooth** (piconet, FHSS 1600 hops/s).
- **Multi-hop + infra:** **Mesh** (router backbone + gateways, self-healing/config).
- **Multi-hop + ad hoc:** the **WSN/VANET/DTN/MANET** family — all infra-less and self-organizing, differing in **constraint**: WSN = **energy**, VANET = **mobility/safety**, DTN = **delay/disconnection**.

**Where students get confused.** WiMAX (802.16) vs Wi-Fi (802.11); cable being **shared** while DSL is **dedicated**; mesh routers being **static** while clients move; assuming all multi-hop ad-hoc nets are identical (they differ by constraint).

---

## 4. Important Exam Pointers
- **The four-quadrant table is the spine** — draw it, fill ≥2 examples per cell, and answer "which quadrant?" questions (e.g., 802.11g campus → **single-hop, infrastructure**).
- **High-value tables to reproduce:** WLAN standards (band+rate, with the **6.9/9.6/>30 Gbps** figures), cross-tech comparison, **WMN vs Ad-hoc**, **WSN/VANET/DTN**, the **eight WMN challenges**.
- **DSL packet-path** (modem → splitter → DSLAM → edge router → core → server) is a classic descriptive answer.
- **Define acronyms exactly:** MTSO, DSLAM, RSU, BSS, FHSS, V2V/V2I, RAN, WiMAX=802.16.
- **Justify design choices** with **range, data rate, infrastructure need, energy, latency** — never a bare "use X."
- **Cellular trio:** cell reuse → capacity; handoff → mobility; co-channel interference → the limiting cost.

## 5. Commonly Forgotten Points
- **Bluetooth = up to 7 *active* slaves** (others parked/standby); **FHSS = 1600 hops/s**.
- **Parked = synchronized-but-inactive; Standby = idle/not connected.** (Don't swap.)
- **DSL is *asymmetric* (down > up)** with **separate frequency bands** on the **same copper**.
- **Cable is *shared* among neighbors; DSL is *dedicated*** — a common comparison trap.
- **Mesh routers can be static while clients move** — mesh ≠ "all mobile."
- **WiMAX = 802.16; Wi-Fi = 802.11; WSN/Low-PAN = 802.15.4.** Don't swap.
- **DTN has no continuous end-to-end path and no classic end-to-end ARQ** — that's why TCP fails.
- **Handoff is coordinated by the MTSO.**
- **WSN structure depends on the application** (agriculture=structured, military=unstructured).

## 6. Tips and Tricks
- **Quadrant mnemonic:** Single+Infra = **Cellular/Wi-Fi/WiMAX**; Single+Ad hoc = **Bluetooth**; Multi+Infra = **Mesh**; Multi+Ad hoc = **A-W-V-D** (Ad-hoc, WSN, VANET, DTN).
- **Constraint tags:** **W**SN→**Watts (energy)**, **V**ANET→**Velocity (mobility)**, **D**TN→**Delay/Disconnection**.
- **DSL chain:** *"Modem, Splitter, DSLAM, then the Door (edge router)."*
- **WLAN bands:** **b/g/n** at **2.4 GHz**, **a/ac** at **5 GHz**, **n/ax/be** span both; rates climb b→a/g→n→ac→ax→be.
- **Mesh = self-Healing + self-Configuring** (two guaranteed-marks words).
- **WiMAX number:** 802.1**6** for the "**6**th sense" of long-range broadband; Wi-Fi = 802.1**1**.

## 7. Formula Cheat Sheet / Key Reference Tables

*(Lecture 2 is conceptual — reproduce these facts.)*

### 802.11 WLAN standards (slide values)
| Standard | Band | Max rate |
|---|---|---|
| 802.11b | 2.4 GHz | 11 Mbps |
| 802.11a | 5 GHz | 54 Mbps |
| 802.11g | 2.4 GHz | 54 Mbps |
| 802.11n | 2.4 & 5 GHz | 600 Mbps |
| 802.11ac | 5 GHz | 6.9 Gbps |
| 802.11ax | 2.4/5/6 GHz | 9.6 Gbps |
| 802.11be | 2.4/5/6 GHz | >30 Gbps |

### Four-quadrant taxonomy
| | Infrastructure-based | Infrastructure-less |
|---|---|---|
| **Single-hop** | Cellular, WLAN, WiMAX | Bluetooth |
| **Multi-hop** | Wireless Mesh (WMN) | Ad-hoc, WSN, VANET, DTN |

### The eight WMN challenges
1. Interference/shared medium • 2. Scalability • 3. Dynamic topology/routing complexity • 4. Limited bandwidth/throughput (per-hop) • 5. Security threats • 6. QoS • 7. Synchronization/coordination • 8. Device heterogeneity.

### Key constants & acronyms
- **Bluetooth FHSS = 1600 hops/s**; piconet = **1 master + ≤7 active slaves**; states **Active/Parked/Standby**.
- **WiMAX = IEEE 802.16**; **Wi-Fi = IEEE 802.11**; **WSN/Low-PAN = IEEE 802.15.4**.
- **MTSO** = handoff/switching; **DSLAM** = DSL aggregation; **RSU** = roadside unit; **RAN** = radio access network.
