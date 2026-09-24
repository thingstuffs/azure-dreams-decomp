# F240 retail reconstruction

Leaf, no frame or saved registers. Twelve words.

- 0: LUI a0 holds queue base high.
- 1: LBU v1 reads owned D_800814D0 via GP.
- 2: ADDIU a0 completes D_80083968 base and fills the head-load delay.
- 3-4: v1 = (head + 31) & 31.
- 5-7: v0 = ((index << 1) + index) << 3, the 24-byte queue stride.
- 8: v0 += a0, queue base remains live until here.
- 9: LBU v0 reads entry byte zero.
- 10-11: JR ra; NOP.

Access owners: D0 local small data, queue external absolute base. No stores or other family-exclusive fingerprints in this leaf. The common CDK recipe is a cohort hypothesis, not an exclusive attribution. Initial candidate emits base late and an extra load-delay NOP, with head v0 and stride v1. First hypothesis: explicit queue-base local before the index local can expose the retail base live range. No pins or asm.
