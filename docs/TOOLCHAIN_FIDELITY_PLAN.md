# Toolchain fidelity plan (owner-approved direction, 2026-09-24)

Status: **STEPS 1-2 RUNNING (2026-09-24 ~03:30Z; Opus agents, briefs docs/evidence/fidelity_step{1,2}_brief.md).** Was: planned - starts when the round-77 lanes still running at 2026-09-24 ~03:00Z (r77_opus_p5, p6, b1, b2, m8)
have finished and landed. No new pin lanes until step 2 reports.**

Goal (owner): byte accuracy AND cleanliness for every row. Principle: a row's recipe is the toolchain the original
was built with (compiler cell + flags + assembler version), and its C is what that toolchain needs to reproduce
retail. Pins or page constants that imitate a different toolchain are not clean, even when byte-exact.

Trigger: the round-77 Fable sceptic disproved the split-address "toolchain gap"
(`docs/evidence/r77_splitaddr_verdict.md`, lane `work/native_lane/r77_fable_splitaddr`): retail's split
`lui %hi / ... / addiu %lo` pairs come from the `2.7.2-cdk` cell, rows registered at non-splitting cells carry
page-constant pins imitating it, and maspsx has passes that imitate it in the assembler stage.

## Steps (in order)

### 1. Genuine-ASPSX differential over the whole tree (CPU, measurement only)
For every landed TU: the cc1 output of its registered recipe, assembled by maspsx (as the pipeline does) AND by
genuine ASPSX 2.56 / 2.67 / 2.77 (sibling repo `toolchain/psyq/psyq4.x/ASPSX.EXE` under `toolchain/bin/wibo`,
`-q -o OUT.OBJ IN.S`, CRLF, `.include`/`#APP` stripped; 2.56 cannot parse %hi/%lo). Relocation-resolved word
comparison (start from `work/native_lane/r77_fable_splitaddr/cands/pipe.py`, `aspsx_run.py`).
Output: per TU, which assembler version(s) reproduce retail, and every maspsx-vs-genuine difference attributed to the
maspsx pass that made it. Answers decisions 1-3 below with data instead of one row.

### 2. Split-fingerprint census in every container (CPU, measurement only)
Retail words showing cc1-level address splitting (HIGH and LO_SUM separated by other insns, LO_SUM into a register
other than its HIGH, a `lui` half in a delay slot, one `lui` shared by several accesses) cannot come from 2.6.3/2.7.2
non-split cells (their mips.c has no split_addresses path) nor from genuine ASPSX (never splits `la`). Scan slus AND
the overlays (the sceptic scanned slus only: 185/317 pin-free cdk rows show it, 6/364 pin-free 2.7.2 rows, all
maspsx-made). Add the fingerprint as an evidence column of `ledger/module_recipe_census.jsonl`.

### 3. Decisions (owner signs; recommendations as agreed 2026-09-24)
1. **maspsx cdk-imitating passes** (`_sink_call_separated_la`, `_split_funcaddr_la`, plus whatever step 1 finds):
   keep for now (removing them breaks exact rows); list dependents per pass; re-recipe the dependents (step 4);
   delete a pass once it fires on zero landed rows (byte-neutral, as the casesi patch was).
2. **ASPSX version per TU**: record the assembler version in each TU's recipe, as the compiler cell is, set to the
   version step 1 shows reproduces it (cdk output implies >= 2.67, the PsyQ 4.1 pairing). One global
   `--aspsx-version=2.56` cannot be right for a binary that mixes cells.
3. **Small-extern `$gp` model**: fix maspsx to genuine ASPSX behaviour (every `.extern` absolute; only TU-defined small
   `.comm`/`.sbss` `$gp`-relative); gate on the TUs step 1 shows affected; rows that shift go to step 4.
4. **Recipe route for the page-constant class** (~50 rows / ~125 sites at non-splitting cells; 150 rows / 332 sites
   on `0x8XXX0000` locals overall): charter amendment needed - a coherence repair toward the recipe the RETAIL BYTES
   prove (step 2's fingerprint), not only toward the module census recipe.

### 4. Re-recipe with natural C
After the step-3 decisions: CPU sweep `t86_symaddr`-style natural symbol spellings, cellscored at the evidenced recipe,
over the class; exact rows land as coherence trades (ledger/recipe_trades.jsonl); the rest go to Opus port-style
lanes (cheap: ~150k tokens a lane in round 77). Fix the wrong ADDR_ALIAS comment in `src/slus/w_8003D92C.c` when
that row lands.

### 5. Retire maspsx passes
Delete each imitation pass once step 4 leaves it firing on zero landed rows; re-gate the tree.

## Owner sign-off needed
- Charter amendment for decision 4 (coherence toward the retail-proven recipe).
- Any change to what "exact" means: the ASPSX version in the recipe (decision 2), the maspsx `$gp` fix (decision 3),
  deleting a maspsx pass (step 5).
Steps 1 and 2 are measurements and need no sign-off.

## Log
- 2026-09-24: plan recorded (round 77, after the sceptic's verdict). Pins at the time: 3,316 in 817 rows.
- 2026-09-24 ~03:30Z: round-77 lanes all landed (3,512 -> 3,207, incl. the NON_MATCHING arm-retirement ruling). Steps 1 and 2 launched in parallel as Opus agents; outputs tools/fidelity/, work/fidelity/, docs/evidence/fidelity_step{1,2}_*.md.
