Random Number Generation {#RNG}
===

Onyx's default Random Number Generator (`Onyx/Core/RNG.h`) internally uses a seeded uniform distribution, Granting an equal probability of each result. 
Multiple instances of `RNG` may exist at a time, each with unique seeds. Setting the Seed to 0 will set it to the current system time, effectively randomising it. 

<div class="section_buttons">
 
| Previous          |                              Next |
|:------------------|----------------------------------:|
| [Maths](Maths.md) | [Timing](Timing.md) |
 
</div>
