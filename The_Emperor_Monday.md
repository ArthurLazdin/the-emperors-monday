Working Title: The Emperor’s Monday
Subtitle: Why History is the Ultimate Stress-Test for Your Code
Introduction
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
Section 1. The Comfort of Pure Mathematics
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
In other words, it was easy to believe that correctness was a binary property:
either the algorithm works, or it doesn’t.
At this stage, I was still thinking like a mathematician.

Code Reference: The initial, raw implementation of the formula is available in step1_basic.c.
Section 2. When Testing Feels Like Proof
Turning the formula into a function felt like an obvious next step.
Once the code was no longer embedded directly in main, it became something I could reason about.
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

Code Reference: See how the code evolved into a testable function in step2_refactor.c.
Section 3. In Search of an Oracle
When your own tests are no longer convincing, the natural instinct is to look for an authority.
In software testing, this authority is often called an oracle: a source that is assumed to produce correct results against which everything else can be compared.
I didn’t have to invent one.
The C standard library already had what I needed.
The time.h module can calculate the day of the week for a given date.
It has been used in countless programs, tested across platforms, and refined for decades.
Compared to my small function, it felt industrial.
If my code disagreed with time.h, the conclusion seemed obvious: my code was wrong.
So I turned the standard library into my oracle.
Instead of checking a handful of hand-picked dates, I let the computer do what it does best.
I generated thousands of test cases and compared the results automatically.
Every month. Every year. Again and again.
The results matched.
Not for ten dates. Not for a hundred. For all of them.
At that moment, the problem felt solved.
The algorithm was correct. The tests were thorough. The oracle agreed.
There was nothing left to doubt.

Code Reference: The automated comparison between my code and the standard time.h library can be found in step3_oracle.c.
Section 4. The Emperor’s Monday
The first failing test was not a technical error.
It was a confrontation with history.
I showed my "perfect" program to my friend Mark, a medieval historian.
He didn't look at the code. He just looked at me and asked:
"What does your math say about December 25, 800 AD?"
The coronation of Charlemagne. The birth of the Holy Roman Empire.
I typed the date into my program.
The algorithm blinked: Monday.
Mark smiled, but it wasn't the smile of someone impressed by technology.
"In every chronicle, from the Annales regni Francorum to the papal records," he said, "it was a Sunday. Your program just moved the foundation of the Holy Roman Empire by one day."
I felt a sudden, cold realization.
The code was doing exactly what it was designed to do.
The math was correct, but the model was blind.
My algorithm assumed a Gregorian calendar.
The world of 800 AD did not.
The Gregorian reform of 1582 was not just a historical footnote; it was a fundamental change in how dates map to days of the week.
By applying modern rules to an ancient era, I wasn't being precise. I was being anachronistic.
Mathematics did not fail. Engineering did.

Code Reference: You can see how the logic branches to accommodate both Julian and Gregorian eras in step4_history.c.
Section 5. Responsibility Has a Boundary
Once the model had failed, a new question appeared.
Not a mathematical one. And not a historical one.
Who was responsible for the incorrect result?
At first, the answer felt obvious.
The algorithm should have handled the date correctly.
After all, the input was valid. Day, month, year.
But valid according to which rules?
My function never promised to handle multiple calendar systems.
It never claimed historical accuracy across reforms.
Those assumptions existed only in my head.
This is where the idea of responsibility becomes unavoidable.
In engineering, responsibility is not universal. It has boundaries.
A function does not exist in isolation.
It exists within a contract — explicit or implicit — between the code and its caller.
If the caller respects the assumptions, the function guarantees a correct result.
If the assumptions are violated, the guarantees quietly disappear.
Undefined Behavior is not a bug.
It is a consequence of a broken contract.
Section 6. Assert as a Bridge
A contract is only useful if it can be enforced.
Mark proved this to me by accident.
I brought him the "historically corrected" version of my code.
I was proud. I was confident.
Mark took the keyboard to try another date, but his finger slipped.
He typed "32nd of October."
The program didn't crash. It didn't show an error.
It calmly calculated a value and announced that October 32nd was a Tuesday.
Mark laughed. "Your code is still hallucinating. October doesn't have 32 days."
That was the moment I realized that a function is not a shield; it is a specialist.
My function shouldn't know how to handle garbage. It should refuse to even touch it.
This is where assert becomes a bridge.
An assertion is not meant to protect the user. It is meant to protect the developer from their own assumptions.
By using assert, I made the contract executable.
If the caller violates the rules — by passing a 32nd day or a 13th month — the program fails immediately.
It fails loudly. It fails exactly where the problem is.
The contract remains. The ambiguity does not.

Code Reference: The final implementation of this "contractual armor" using assert can be found in step5_contract.c.
Conclusion. What This Date Taught Me
The date itself was not special.
It did not reveal a hidden bug. It did not expose a clever edge case.
It simply existed outside the assumptions I had made.
The algorithm worked. The tests passed. The standard library agreed.
And yet the result was wrong — not because the code failed, but because the model did.
This is the difference between writing code and practicing engineering.
Code answers questions.
Engineering decides which questions are worth answering — and under which conditions the answers still make sense.
Once those conditions are explicit, failure stops being mysterious.
It becomes informative.