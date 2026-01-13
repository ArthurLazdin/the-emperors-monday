# The Emperor’s Monday 👑📅

> **"If you don't know how many legs a cow has, your program will return a wrong result even if your math is perfect."**

This repository contains the source code and documentation for the article **"The Emperor’s Monday: Why History is the Ultimate Stress-Test for Your Code."** It explores the transition from simple coding to software engineering through the lens of Zeller’s Congruence and a famous historical paradox.

---

## 📖 The Story

In this project, we attempt to calculate the day of the week for historical dates using a "perfect" mathematical formula. 

The turning point occurs when we test the coronation of Charlemagne (December 25, 800 AD):
* **The Program (Gregorian Math):** Confidently claims it was a **Monday**.
* **The History Books:** Record it as a **Sunday**.

This discrepancy is not a bug in the code, but a failure of the **mathematical model**. We explore why the 1582 Gregorian reform matters to a modern C programmer and how "Design by Contract" can protect our software from such silent failures.



---

## 🚀 Project Structure

The code is organized into five progressive steps, demonstrating the evolution of an engineering solution:

* `step1_basic.c`: Raw implementation of Zeller's formula.
* `step2_refactor.c`: Moving from a script to a testable, reusable function.
* `step3_oracle.c`: Automated validation against the C standard library (`time.h`).
* `step4_history.c`: Implementing the Julian/Gregorian calendar switch (The "Charlemagne" fix).
* `step5_contract.c`: Final version using `assert()` and explicit functional contracts.

---

## 🛠️ Building the Project

The project includes a `Makefile` for automated building.

```bash
# Clone the repository
git clone [тут я вставлю ссылку на репозиторий](https://github.com/your-username/the-emperors-monday.git)
cd the-emperors-monday

# Compile all steps
make

# Run the final version to see the correct Sunday result for 800 AD
./step5_contract