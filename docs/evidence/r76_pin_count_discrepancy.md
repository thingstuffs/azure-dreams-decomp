# r76: pin count discrepancy, STATUS "Pin sites now" vs ledger/levels.jsonl (2026-09-23)

## Symptom

At STATUS 2026-09-23T08:38:15Z, "Pin sites now" said **3,701 sites in 902 rows**. `ledger/levels.jsonl` (`tools/levels.py`)
summed `pins_left` to **3,756 in 916 rows** (3,752 / 915 without ovmovie), and STATUS's L4-residue line said
"pins 916 rows (878,384 B)". The ledger was not stale: re-running the old `levels.py` logic on the tree gave the same
3,756 / 916.

## Which side is right

The charter (goal paragraph, rule 5) defines the counter as `tools/pin_census.sites_of` over every row except parked
`ovmovie`. `status.py` uses exactly that. `levels.py` did not: it counted raw `\bASM_[A-Z0-9_]+\(` tokens
(`census.PIN_RE`) in comment-stripped text. That token count also read text that is not a pin site. **levels.py was
wrong.** The counter was not changed.

## Gap decomposition: 55 sites / 14 rows

| class | sites | rows | what it is | a real pin? |
|---|---:|---:|---|---|
| A: NON_MATCHING / `#if 0` arm text | 26 | 17 | `#define ASM_KEEP(v) ((void)0)` stubs and nameless `#define ({ ... ASM_REG(...) ...` fragments in port arms | no: only the port build compiles it, and there every ASM_* is a no-op (`pin_census.arm_labels`) |
| B: macro definition in the compiled arm | 22 | 17 | local wrapper definitions (`#define ASM_KEEP(v) __asm__(...)`, `#define ASM_CLOBBER_A0() ASM_CLOBBER("$4")`, `#define READ_ZERO(var) ASM_UNDEF(var)`) | no: a definition emits nothing. Its call sites are pins, and `sites_of` counts them (every wrapper here has an `ASM_` name, or no call sites at all) |
| C: `ASM_REG` on a non-`register` local | 3 | 1 | `dungeon/func_81329D94`: `void *object, *state ASM_REG("$19"), *position ASM_REG("$17"), *sprite ASM_REG("$16");` | no: gcc 2.x `rest_of_decl_compilation` ignores an asm-spec on an auto variable. **Checked:** with the three removed, `tools/verify.py` still reports `exact: true` |
| parked ovmovie | 4 | 1 | counted by levels.jsonl, excluded by the counter | parked (charter) |

The row counts overlap: 27 rows differ, and 13 of them have 0 counter sites but >0 in levels (915 − 902 = 13).
Per line, the two counts agreed everywhere except on the lines listed below. There was no statement-level pin that
one count saw and the other did not.

## Per-row table (counter = `sites_of`; levels = old `pins_left`)

| row | counter (sites_of) | levels (old) | diff | reason (sites) |
|---|---:|---:|---:|---|
| town/func_800AB548 | 0 | 2 | +2 | A port-arm 1, B macro-def 1 |
| town/func_800B79CC | 0 | 1 | +1 | A port-arm 1 |
| town/func_800B9B58 | 1 | 3 | +2 | A port-arm 1, B macro-def 1 |
| town/func_80874E18 | 1 | 3 | +2 | A port-arm 2 |
| town/func_80874F4C | 1 | 2 | +1 | A port-arm 1 |
| town/func_8088124C | 0 | 2 | +2 | A port-arm 2 |
| town/func_8096B058 | 0 | 1 | +1 | A port-arm 1 |
| town/func_8096B16C | 0 | 1 | +1 | A port-arm 1 |
| dungeon/func_800B6A54 | 0 | 2 | +2 | A port-arm 1, B macro-def 1 |
| dungeon/func_800C97F4 | 0 | 3 | +3 | A port-arm 1, B macro-def 2 |
| dungeon/func_80E657E4 | 0 | 2 | +2 | B macro-def 2 |
| dungeon/func_81329D94 | 0 | 3 | +3 | C nonreg-ASM_REG 3 |
| dungeon/func_81811EC0 | 0 | 1 | +1 | B macro-def 1 |
| dungeon/func_81811F04 | 1 | 2 | +1 | B macro-def 1 |
| dungeon/func_81811FA8 | 1 | 2 | +1 | B macro-def 1 |
| dungeon/func_818B6AFC | 11 | 14 | +3 | A port-arm 3 |
| dungeon/func_818BDEBC | 12 | 14 | +2 | A port-arm 2 |
| dungeon/func_818C3B90 | 11 | 13 | +2 | A port-arm 2 |
| dungeon/func_81988C1C | 3 | 4 | +1 | B macro-def 1 |
| slus/w_8003D468 | 0 | 1 | +1 | B macro-def 1 |
| slus/w_800434E4 | 0 | 1 | +1 | B macro-def 1 |
| slus/w_80048C3C | 2 | 3 | +1 | B macro-def 1 |
| slus/w_80051228 | 4 | 6 | +2 | A port-arm 1, B macro-def 1 |
| slus/w_80053858 | 3 | 7 | +4 | A port-arm 2, B macro-def 2 |
| slus/w_80053CFC | 1 | 5 | +4 | A port-arm 2, B macro-def 2 |
| slus/w_80055E84 | 0 | 4 | +4 | A port-arm 2, B macro-def 2 |
| slus/w_80059814 | 9 | 10 | +1 | B macro-def 1 |

Class A includes six rows whose port arm has a nameless `#define ({ ... })` (town/func_80874E18, func_80874F4C,
func_8088124C; dungeon/func_818B6AFC, func_818BDEBC, func_818C3B90). This is the known 548963e9 residue that
`pin_census.landing_refusal`'s `port_ref` works around. The -DNON_MATCHING build of those rows does not compile. That
is port-build damage, not a pin.

## Fix (tools only; counter untouched)

- `tools/levels.py`: `pins = len(pin_census.sites_of(text))` replaces the `PIN_RE` token count. It feeds `pins_left`,
  the L1 gate, the strict L4 `pins == 0` check, and `l4_residue`/`l5_residue`. A site-for-pin trade is a real `ASM_*`
  statement, so it still counts at L4 (ruling 2026-09-22 evening, decision 3).
- `tools/status.py`: the L4-residue line now skips parked containers, matching "Pin sites now".
- Test: `tools/tests/test_levels.py::test_pins_left_is_the_charter_counter`.
- Effect (levels.py re-run through its normal invocation): `pins_left` 3,756/916 -> 3,705/903 (**3,701 / 902 without
  ovmovie, equal to the counter**). 27 rows changed `pins_left`. 13 rows lost `pins` from `l4_residue`. **No row changed
  level**: all are L3, still `not_in_module`. STATUS re-run through `status.py`: L4 residue before "pins 916 rows
  (878,384 B), tail_jump 9, not_in_module 6,767"; after "pins 902 rows (873,312 B), tail_jump 8, not_in_module 6,745"
  (parked excluded). "Pin sites now" is unchanged at 3,701 / 902.

## Landing gates

- `tools/lanes/land_lanes.sh` keeps a candidate only if `len(sites_of(cand)) < len(sites_of(cur))`, that is, the
  counter strictly drops. It also refuses the candidate if any raw `ASM_X(` token kind grows (`/* */` stripped). The
  token check is stricter than both counts: a lane cannot add a wrapper definition or a port-arm stub. Now that
  levels.py counts with `sites_of`, a lane landing can no longer raise `pins_left`. One small gap remains in the token
  guard: it does not strip `//` comments, so a candidate that turns a `// ASM_KEEP(x)` comment into code keeps the
  same token count. The `sites_of` decrease still catches that case.
- `tools/lanes/land_coherence.sh` (recipe coherence, clause 4b) has no grow guard, by design. It records
  `pins_before`/`pins_after` from `sites_of` in `ledger/recipe_trades.jsonl`.
- `tools/apply_candidates.py` has no pin check of its own. It relies on its callers.

## For the owner (no change made): pins behind a non-`ASM_` wrapper are counted once per definition

Neither count sees how many times a pin is expanded. `sites_of` counts an `ASM_*` statement inside a
`#define WRAPPER(...)` body once. Each `WRAPPER(x);` call is not an `ASM_` token, so the calls are not counted.
In the current tree this involves 2 rows and 5 extra expanded sites:

- dungeon/func_807B0B3C: `FINISH_GLOBAL_TABLE` has 1 `ASM_KEEP_DEP_NV` and 4 calls (+3).
- dungeon/func_818B7F38: `LOAD_TABLE_X_BASE` and `LOAD_TABLE_Y_BASE` each have 1 `ASM_KEEP` and 2 calls (+1 each).

A wrapper with a single call (`LOAD_SPLIT_GLOBAL`) is counted correctly. `pin_census.hidden_asm` already reports 9
calls of local *asm* wrappers ("Hidden scaffolding, not in the pin count"), but not of `ASM_*` wrappers.

Proposed wording, if the owner wants the count to follow expansions: *"A pin inside a function-like macro counts
once per call of that macro in compiled code, not once per definition (`pin_census.sites_of` expands local
wrappers whose body carries an ASM_* statement)."* The counter would move from 3,701 to 3,706. Otherwise, leave it:
5 sites in 2 rows, which a lane removes together with the wrapper anyway.

Free cleanup (a src edit, not made here): the three non-`register` `ASM_REG` annotations in dungeon/func_81329D94
are byte-neutral dead text. Neither count sees them any more.
