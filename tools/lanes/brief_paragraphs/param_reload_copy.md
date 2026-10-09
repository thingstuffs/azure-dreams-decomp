## Stack-home parameter copies (round 106: r106_opus_pins2 - dungeon/func_818FA12C 1 -> 0 pins, volatile 1 -> 0)
APPEARS: m2c spells retail's RELOAD of a spilled parameter (its home is a stack slot, e.g. `lw $9,128($sp)` at the start
of each run of uses) as a shared integer copy: `tmp = (s32)param; ((T *)tmp)->f = ...`, usually with a `volatile` on the
parameter and/or a KEEP/REG pin nearby. The single global copy pseudo is what those pins fight: it takes the wrong
register (an equal-priority sched1 tie), floats above stores in sched1, and carries the pointer across a join so the
other arm's reload disappears.
RESOLVES: write `param->f` directly at EVERY site (type the parameter, drop the copy), then drop the volatile and the
pin. With no copy pseudo, reload puts the stack-slot `lw` at each first use, once per arm, after the stores. Keep the
temp only for roles that are genuinely not the parameter (818FA12C: two product roles stayed). Control: try direct
access with the pin still present - if that is exact, the pin held nothing once the copy was gone.
