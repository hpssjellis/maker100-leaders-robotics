# Bring Maker100 Leaders Robotics to Your High School
## A $2,000 PAC Pilot Proposal

## The Idea

Give a small group of motivated high school students the chance to explore **robotics, electronics, programming, AI, physics, and engineering** through a hands-on, project-based course — without asking the school to create a new standalone class.

**Maker100 Leaders Robotics** is a meta-course that gets embedded inside an *existing* computer lab, robotics, electronics, programming, or web-design course.

**The 7 students are not a new class.** They're selected from a class that already exists, with a teacher who already teaches it. For example: a Grade 10 Web Design class has 25 students. Seven (±1) motivated students are chosen to run Maker100 projects during an agreed portion of class time, while the teacher continues teaching Web Design to everyone else. The seven stay enrolled in the normal course — Maker100 becomes an additional, student-directed pathway inside it, not a separate section the teacher has to run on top of their existing load.

This same model works inside computer science, robotics, electronics, engineering, or any general computer lab / STEM course.

**Curriculum:** [maker100-leaders-robotics](https://github.com/hpssjellis/maker100-leaders-robotics/tree/main)
**Underlying course materials:** [maker100-curriculum](https://github.com/hpssjellis/maker100-curriculum)
**2026 Price List:** [price-list-2026.html](https://hpssjellis.github.io/maker100-leaders-robotics/price-list-2026.html) *(set student count to 7 for this pilot)*

## The Pitch to Your PAC

Fund a **7-student pilot** — roughly **$2,000 USD** — inside a course that already runs. If it succeeds, the school has real, local evidence for whether to build a full course around it. If it doesn't, the school has learned that for $2,000, not after committing to a much larger program.

**This is a pilot, not a commitment to create a new course.**

## Why It's a Meta-Course

Maker100 draws on concepts from Math, Physics, Chemistry, Biology, Communication Skills, and Peer Teaching all at once — which is why it fits inside almost any technical elective rather than competing with it.

## Why No Robotics Specialist Is Required

- **Students do the problem-solving.** The host teacher doesn't need deep robotics expertise — their job is safety, structure, and guidance, not knowing every answer.
- **Hardware changes fast**, on purpose — it keeps generating new problems to solve instead of going stale.
- **The Analog Firewall**: students hand-write summaries and draw circuit diagrams before touching code or hardware, forcing real understanding instead of copy-paste assembly.
- **Teach Three**: whoever makes a discovery is responsible for passing it on to three other students — knowledge moves student-to-student, not just teacher-to-student.
- **LLMs (ChatGPT or private local models)** are used as problem-solving aids, the way they're used in real engineering — but the ~50 physical assignments still have to actually work before students move to final projects.

## Why the Curriculum Stays Relevant

Hardware will keep getting cheaper, faster, and lower-power — expected, and it doesn't require rewriting the course. The core concepts, and most supporting sensors and actuators, don't change dramatically. Interconnected/bundled hardware sets are deliberately avoided, since they tend to hide the very connections between components that make the learning happen.

## The PAC Ask

1. Approve pilot funding (~$2,000 USD for 7 students, per the 2026 price list)
2. Identify one existing course and teacher willing to host the pilot
3. Confirm IT support for installing required software (Arduino IDE, Python, Node.js, USB/serial access)
4. Treat this as a **test**, not a commitment — the goal is real evidence, not a promise

## An Important Note on Funding Beyond the Pilot

The PAC is well positioned to fund this **pilot** — a small, one-time cost to prove the concept. It is *not* the right long-term funder for a full standalone course. If the pilot succeeds and the school decides to run Maker100 as a full course, that decision — and its ongoing funding — should shift to the administration/district budget.

**The PAC's role is to buy the evidence, not to become the permanent funding source.** Framing it this way up front protects the PAC from being expected to fund a recurring course indefinitely, and gives the PAC a clear, natural point to hand the idea off to admin with a strong case in hand.

## Cons & Potential Hurdles (Things to Anticipate)

**Classroom management & noise.** The Maker100 students, working heads-down on breadboards, sensors, and code, tend to be quiet and focused by nature of the task. The more realistic classroom-management risk is the *other* students in the room — a subset visibly doing something different and hands-on can be a distraction for the rest of the class, and that's a conversation to have with the host teacher up front, not something to gloss over.

**IT department friction.** School IT departments can be cautious about local device permissions. In practice, installing the Arduino IDE is a routine, low-risk install. If it does hit friction, **PlatformIO with VS Code** is a solid fallback that installs cleanly on Windows and avoids some of the friction points of the standalone Arduino IDE.

**Assessment complexity.** The host teacher is already grading a different subject and shouldn't be expected to build a parallel assessment system from scratch. The pilot handles this by putting the tracking burden on the students themselves: a **shared chart of all ~50 assignments**, checked off as each is physically completed and verified. This keeps assessment lightweight for the teacher while still producing a clear, auditable record of progress.

**Selection bias.** Choosing only seven (±1) students always raises a fairness question. For this pilot, selection is based on **combined math/science grades** — a straightforward, defensible metric rather than teacher subjective judgment. Because this is a small proof-of-concept, not the final program, it's deliberately scoped to students who can work independently with minimal support. When the program expands to a full class, the pilot cohort's role shifts to **teaching the incoming students** — Teach Three at full-class scale — which is how the model extends access rather than staying limited to an initial small group.

---

# Appendix: Common Questions

**Does the teacher have to teach seven students separately?**
No. The seven remain part of the existing class. The teacher supports the rest of the class as normal while the seven work through Maker100 during an agreed slice of class time.

**What if the teacher doesn't know robotics?**
They don't need to be a specialist — just interested in STEM, comfortable with classroom management, and willing to let students troubleshoot independently rather than handing them answers.

**Won't students just get ChatGPT to do everything?**
Physical hardware, handwritten planning, and peer teaching make pure copy-paste ineffective — the code still has to make real hardware work. The goal is teaching students to use AI while still verifying what it produces.

**Will we need expensive bundled robotics kits?**
No — Maker100 discourages heavily integrated kits because they hide the relationships between components (sensor → data → program → decision → actuator), and those relationships are a big part of the learning.

**What if the technology changes?**
Expected and fine. The curriculum emphasizes concepts and connections, not one fixed generation of hardware.

**Who pays if this becomes a full course?**
The PAC funds the pilot. If the school decides to run Maker100 as a full course afterward, that funding should come from the school/district, not the PAC.

## Suggested Pilot Steps

1. **Identify a host course** (CS, web design, robotics, electronics, engineering, or similar) and a willing teacher.
2. **Select ~7 students** (±1) using combined math/science grades — motivation and independence matter more than being the strongest coder.
3. **Agree on logistics** — how much class time, how progress is tracked (the 50-assignment chart), how normal course requirements are still met.
4. **Prep the tech** — purchase hardware, install software (Arduino IDE, with PlatformIO/VS Code as a fallback), confirm USB/serial permissions.
5. **Run the pilot** — Build → Test → Fail → Understand → Fix → Explain.
6. **Measure results** — completed projects, student independence, teacher workload, interest in continuing.
7. **Decide** — expand, adjust, or stop, based on your own school's evidence. If expanding to a full course, hand off funding responsibility to the administration, and have pilot students help teach the incoming class.

---

**We are asking the PAC to approve approximately $2,000 USD to run a seven-student Maker100 Leaders Robotics pilot within an existing course.**

The hardware can change. The learning can continue.
