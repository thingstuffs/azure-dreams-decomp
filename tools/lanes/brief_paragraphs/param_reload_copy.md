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
SCOPE (r107_sonnet_prc census follow-up): only a STACK-HOME parameter (its uses start with `lw $r,N($sp)` reloads). If
the parameter lives in a saved register (`move $21,$6` at entry) the shared temp is a real pseudo MERGE of the parameter
and another role, not a copy - splitting it recolours (8182C800: split = dist 80, pin unchanged). Where the copy is real
but the pin holds something else, the rule is still a readability landing at equal pins (80095160: body_addr dropped,
exact, pin unchanged at erase distance 75).
