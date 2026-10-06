# sched_whatif (harvested from r95_opus_T, 2026-10-06)

An instrumented copy of the genuine cdk cc1 (toolchain/gcc-src/2.7.2-cdk + sched_r95_whatif.patch) that logs every sched1/sched2
ready-list decision and can force one decision the other way. With every switch off it is byte-identical to the shipped cc1.
Build (in a lane, never in toolchain/): copy toolchain/gcc-src/2.7.2-cdk to <lane>/tmp/gcc, `patch -p1 < sched_r95_whatif.patch`,
`make cc1 CC='gcc -m32'`, use tmp/gcc/cc1 as cc1_whatif. A built copy: work/native_lane/r95_opus_T/tmp/cc1_whatif.
Env switches: R95_FLIP (force one tied decision), R95_BOOSTCTL (force a birthing boost on/off for one insn), global rule switches
(LUIDREV, NOHAZ, STOREHAZ0, BOOSTANY, NOBOOST, FRESHSETS, ...) - see whatif.py.
- flip.py <row>: every single tied-decision flip and boost toggle on the erased text, then stacks the best -> the exact sched moves that
  turn the erased text into retail (tmp/flip/<row>.erased.json). Use it to SPECIFY what a source change must achieve.
- hazcensus.py: undoes every sched2 potential-hazard pick one at a time (retail follows the hazard rule: 135 proven vs 14 against).
Result (TIE_CENSUS.md in the lane): no global tie rule differs between retail and our cc1 - every global flip breaks 13-60 of 62
pin-free rows. The tie rows are per-row source problems (insn order before scheduling, per-variable set counts, dependences).
Note: whatif.py/flip.py set LANE = the script's grandparent (they ran from <lane>/tools/); copy them into a lane's tools/ to use.
