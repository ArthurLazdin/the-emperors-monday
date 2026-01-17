# Working Title: The Emperor’s Monday

Subtitle: Why History is the Ultimate Stress-Test for Your Code

## Introduction

I once wrote a program that calculated the day of the week for any given date.  
It was based on a well-known mathematical formula.  
It was compact, elegant, and easy to test.  
And it was wrong.

Not because of a bug.  
Not because of an off-by-one error.

It was wrong because I assumed that mathematics alone was enough.

At first, everything looked perfect.  
The algorithm passed all my tests.  
It matched the results of the standard C library.  
Thousands of dates — no failures.

The problem appeared when I tried a date from the year 800.

This article is not about calendars.  
And not really about algorithms either.  
It is about the moment when programming stops being mathematics and starts becoming engineering.  
About assumptions.  
About responsibility.  
And about the uncomfortable gap between “the code works” and “the code works in the real world”.

## Section 1. The Comfort of Pure Mathematics

The algorithm I used was not obscure or experimental.  
It was a well-known mathematical formula for calculating the day of the week.

No loops.  
No conditionals.  
Just arithmetic.

This kind of code is deeply comforting.  
You can look at it and feel that it must be correct.  
The formula has existed for decades.  
It appears in books, articles, and university courses.

If something goes wrong, surely the mistake must be in your implementation — not in the idea itself.

From a programmer’s point of view, it was almost perfect.  
One function.  
Deterministic input.  
Deterministic output.

We are drawn to these abstractions because math offers a sense of timeless, universal truth — a logical sanctuary where rules do not change regardless of who is observing them.

It was easy to believe that correctness was a binary property:  
either the algorithm works, or it doesn’t.

At this stage, I was still thinking like a mathematician.

*Code reference: The initial, raw implementation of the formula is available in `step1_basic.c`.*

## Section 2. When Testing Feels Like Proof

Turning the formula into a function felt like an obvious next step.  
Once the code was no longer embedded directly in `main`, it became something I could reason about.  
Something I could test.

The inputs were simple: a day, a month, a year.  
The output was a single number.  
No side effects.  
No hidden state.

From the outside, it looked like the perfect candidate for unit testing.

I started with the obvious cases.  
Ordinary dates.  
Recent years.  
Dates I could easily verify using a calendar or a search engine.

All of them passed.

That success was reassuring.  
Every green test felt like evidence.  
Each checkmark felt like a small proof that the algorithm was correct.

At this point, I wasn’t testing the algorithm anymore.  
I was testing my expectations.

And the expectations were modest.  
If the code works for common dates, if it handles leap years, if it survives the turn of the century — what else could possibly go wrong?

*Code reference: See how the code evolved into a testable function in `step2_refactor.c`.*

## Section 3. In Search of an Oracle

When your own tests are no longer convincing, the natural instinct is to look for an authority.  
In software testing, this authority is often called an oracle: a source that is assumed to produce correct results against which everything else can be compared.

I didn’t have to invent one.

The C standard library already had what I needed — at least within the same modern assumptions my code was implicitly making.  
The `time.h` module can calculate the day of the week for a given date.  
It has been used in countless programs, tested across platforms, and refined for decades.

Compared to my small function, it felt industrial.

If my code disagreed with `time.h`, the conclusion seemed obvious: my code was wrong.

So I turned the standard library into my oracle.

Instead of checking a handful of hand-picked dates, I let the computer do what it does best.  
I generated thousands of test cases and compared the results automatically.  
Every month. Every year. Again and again.

The results matched.

Not for ten dates.  
Not for a hundred.  
For all of them.

At that moment, the problem felt solved.  
The algorithm was correct.  
The tests were thorough.  
The oracle agreed.

There was nothing left to doubt.

*Code reference: The automated comparison between my code and the standard `time.h` library can be found in `step3_oracle.c`.*

## Section 4. The Emperor’s Monday

The first failing test was not a technical error; it was a collision between silicon logic and the dust of the ninth century.

I showed my “perfect” program to my friend Mark, a medieval historian.  
He didn’t look at the source code; he looked through it, as if searching for the people who had actually lived the dates I was processing.

“What does your math say about December 25, 800 AD?” he asked.  
The coronation of Charlemagne.  
The day the Holy Roman Empire was born under the arches of Old St. Peter’s Basilica.

I typed the date.

The algorithm returned “Monday.”

Mark smiled — the weary smile of a scholar who knows that reality is rarely as tidy as a function.

“In every chronicle, from the *Annales regni Francorum* to the papal records,” he said, “it was a Sunday. Your program just moved the foundation of an empire by a day.”

I went back to the code.

This time, I corrected the model.  
I replaced the proleptic Gregorian assumptions with the Julian calendar that was actually in use in the year 800.  
The math was careful.  
The rules were historically appropriate.

The answer changed — but not to Sunday.

The corrected algorithm said: Friday.

At first, this felt like a contradiction.  
But it wasn’t a disagreement between code and history.  
It was a disagreement between two different meanings of what a “day” even is.

My program was calculating a computational weekday: a formal, arithmetic mapping between dates and days of the week.  
The historical sources were describing liturgical time, where days begin in the evening, and events like Christmas are understood within a religious cycle rather than a civil clock.

The coronation took place during the Christmas liturgy — on what contemporaries understood as Sunday — even if, by a strictly computational model, the date still belonged to Friday.

The code was doing exactly what it was designed to do.  
The math was correct.

But once again, the model had a boundary.

Mathematics did not fail.  
Engineering had simply discovered another assumption.

*Code reference: You can see how the logic branches to accommodate both Julian and Gregorian eras in `step4_history.c`.*

## Section 5. Responsibility Has a Boundary

The failure with Charlemagne’s coronation revealed a fundamental truth: my code didn’t have a bug; it had a boundary problem.

In mathematics, a formula is often treated as universally applicable.  
In engineering, every solution has a domain of validity.

My algorithm was a specialized tool for the Gregorian calendar, but I had treated it like a universal oracle.

This is where the concept of a software contract becomes vital.

A function should not be a black box that tries to handle the entire universe.  
It should be a specialist that operates within a strictly defined territory.

If the code is used outside that territory — say, for a date in the year 800 — the contract is breached.  
The responsibility for the error doesn’t lie with the math, but with the missing boundary.

*Code reference: The final implementation of this contractual boundary can be found in `step5_contract.c`.*

## Section 6. Enforcing the Boundary: Refusal as a Feature

To test this new perspective, I brought the “historically aware” version of my code back to Mark.  
I was confident I had fixed the model.

As Mark began to type, his finger slipped.  
He entered “October 32nd.”

The program didn’t flinch.  
It calculated a value and calmly announced that October 32nd was a Tuesday.

This was the final lesson.

A robust function must do more than calculate; it must refuse.

If a function accepts “October 32nd” or “Year 800” when it isn’t designed for them, it is lying to the caller.

This is where mechanisms like `assert`, explicit validation, or defensive APIs move from being debugging tools to architectural instruments.

By making assumptions executable, I turned an implicit boundary into an explicit one.

An assertion says: “Beyond this point, I can no longer guarantee the truth.”  
It forces the program to fail loudly and immediately, instead of allowing a confident hallucination to propagate through the system.

## Conclusion. What This Date Taught Me

The date itself was not special.

It did not reveal a hidden bug.  
It did not expose a clever edge case.

It simply existed outside the assumptions I had made.

The algorithm worked.  
The tests passed.  
The standard library agreed.

And yet the result was wrong — not because the code failed, but because the model did.

This is the difference between writing code and practicing engineering.

Code answers questions.  
Engineering decides which questions are worth answering — and under which conditions the answers still make sense.

Once those conditions are explicit, failure stops being mysterious.  
It becomes informative.
