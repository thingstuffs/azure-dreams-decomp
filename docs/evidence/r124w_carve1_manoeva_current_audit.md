# Manoeva factory: current-target allocator hold

The ordinary baseline is remeasured on 648eafb94 using current headers and
2.7.2-cdk -O2 -G0. All 540 emitted bytes are linked and retained: aligned LCS
has eight substitutions and zero indels. The complete retail section at
DUNGEON +E570B4 is unchanged. Frame 56 and saved s0-s7/fp/ra agree; Gate 0
register roles fail because tile Y and position are interchanged.

Fresh candidate.c.lreg reports p90 position: four references, live length 80;
p84 tile Y: two references, live length 23; p82 tile X: two references, live
length 26. candidate.c.greg assigns them s5, s6, s7 respectively. Retail needs
s6, s5, s7. This reproduces the prior allocation-input attribution on current
headers. The fresh pure lineage_fingerprint scan of all 135 instructions again
has no family attribution. No compiler wall or source impossibility is claimed.

Queued item I2-REG-PRIORITY routes to rtl_probe/I2: trace these lifetimes through
sched1 and update_equiv_regs. Find a natural C lifetime or a documented producer
flag that reverses their priority while preserving the operation graph, then
route to az-c-rebuild. The existing handoff includes the complete site map and
feature table. The prior live-length intervention is counterfactual diagnostic
output and must never be staged. Only ordinary uninjected output may proceed
to independent complete-section checks at all five observed placements.

The portable current receipt is run4-manoeva-reaudit.json in the lane proof
package. Ignored fresh dumps live under work/wall_E570B4_run4/rtl in the private
target; only their hashes and source-level conclusions are delivered. No row,
C home, placement or runtime-coverage improvement is added by this audit.
