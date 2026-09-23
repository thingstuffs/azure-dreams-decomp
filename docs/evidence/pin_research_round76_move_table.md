# Round 76 harvest: MOVE TABLE from the r76 model lanes (2026-09-23)

Source: every `base/out` pair with fewer pin sites in `out/` across the lanes under `work/native_lane/` named
`r76_{opus,sonnet,sol6,astra,agy,luna6}_*` and `r76o_{opus,sonnet}_*` that had `last_message.txt` when the harvest
looked (~11:00Z), plus the `REPORT.md` rule sentences of the lanes with no win.  **23 rows, 43 pin sites removed**
(`pin_census.sites_of(base) - sites_of(out)` on the lane's own `base/<id>.c` and `out/<id>.c`).  The r76o_* lanes are
the A/B overlap arms: their moves are READ here (as exemplars), their rows are never staged or landed by this harvest
(see "Holds" below).

| lanes read | model | rows | pins |
|---|---|---|---|
| r76_opus_b12_1 / b12_2 / b37_1 / b37_2, r76o_opus_b12 / b37 | claude-opus-5-5 | 15 | 34 |
| r76_astra_b37_1 | astra | 3 | 4 |
| r76_agy_b12_1 / b12_2 / b37_1 / b37_2 | gemini (agy) | 3 | 3 |
| r76_sol6_b12_1 / b12_2 | gpt-6-sol | 2 | 2 |
| r76_sonnet_b12_1 / b12_2 / b37_1 / b37_2, r76o_sonnet_b12 / b37 | claude-sonnet | 0 | 0 |

NOT read (no `last_message.txt` yet, codex pools running): r76_astra_b12_1 (out: town/func_80956E6C 1 -> 0),
r76_luna6_b12_1 / b12_2 (out: town/func_800ADA80 1 -> 0) / b37_1, r76_sol6_b37_1 (town/func_80810F98 3 -> 1) / b37_2
(dungeon/func_80BBB094 7 -> 3), r76o_agy_b12, r76o_astra_b12 / b37, r76o_sol6_b12.  The six sonnet lanes finished
0 / 17 rows (every row a measured negative with a named pass; their rules are in the bounded-negative list).

"Owner today" = a gen_drive run of the owning generator on the lane's PRE-landing text (`--base-from <lane> --only
<id>`), lanes `work/native_lane/r76_h_<gen>_check_*` (a/b/c: the generator as it stood; x/y: after this harvest's
build).  compose2 checks: `r76_h_compose_check_{a,b,c}`.

| # | move | pins | rows | models (rows) | owner today (measured) | verdict |
|---|---|---|---|---|---|---|
| 1 | **parameters used directly** instead of `T x = x_in;` copies (the copy's REG_EQUIV doubling / the keep's second set), the surviving copy taking the parameter's other reads, the leftover pins erased | 15 | 5 | opus 5 | t69_prologue: 809815A8 d2, 80BECDA4 d4, 809F3C00 d140, 80AC7A30 d190; refuses 813236DC / 80F88C94 "no redundant parameter copy" | 809815A8 needed two more steps -> **t69 EXTENDED (T69_UNPIN_REST)**; the other rows each carry a second move (#6, #12, `s16` parameter + volatile slot) |
| 2 | **an in-place update chain written as ONE set** (`v = E; v >>= k;` -> `v = (E) >> k`), an accumulator's prefix moved to a fresh local so the pinned register is set once | 4 | 2 | opus 2 | none (t100/t107/t115 fold FIELDS; t94 splits the other way) | **BUILT t118_setonce** 2/2 |
| 3 | surplus call argument dropped to the callee's arity + the address argument passed directly (no `v = (s32)&x` carrier) | 2 | 1 | opus 1 | t113 d4 (drop only); compose2 t113 -> t115/t117 A-empty | **t115 EXTENDED (T115_ADDRCARRIER)**, composed into **t113 (T113_ADDRCARRIER)** 1/1 |
| 4 | `p = q + C; KEEP(p)` -> `p = q; p = p + C;` AND the arm's opening copy hoisted above the `if` | 1 | 1 | opus 1 | t111 d20 (all five spellings); compose2 t111 -> t105 miss | **t111 EXTENDED (T111_HOIST)** 1/1 |
| 5 | a call's result routed through the kept copy (`KEEP(v); x = f(v); v = w;` -> `v = f(v); x = v; v = w;`) | 1 | 1 | opus 1 (astra solved it too, r76o_astra_b12, unread) | t115 d3, t117 d86 | **t115 EXTENDED (T115_CALLCOPY)** 1/1 - five clone siblings exact in the sweep |
| 6 | the goto'd shared `call; return` / `x++; store; return` tail written inline at the goto (jump2 cross-jumps it back) | 1 (+ 2 rows compound) | 1 (+2) | opus 3 | t102_gotojoin 809F3C00 d138, 81989320 d10, 80F88C94 d4; compose2 t69 -> t102 A-empty | compound (each row pairs it with #1 or #8) - NOT BUILT |
| 7 | **dead zero initializer at a declaration** (`void *effect = 0;`, owner ruling 2026-09-23) replacing the keep, the copy sunk one statement | 1 | 1 | opus 1 | none | **BUILT t119_deadinit** 1/1 (both directions: add `= 0` / remove one) |
| 8 | a multi-purpose `register ... result ASM_REG("$2")` split into per-use temporaries + loop invariants written inside the loop | 4 | 1 | opus 1 | t85 refused ("16 vs 13 allocnos"); with T85_WIDE: an order site, best lever d142 | compound one-off - NOT BUILT (priority 2 below) |
| 9 | `volatile` access dropped together with the register pin it propped up (and the volatile stack slot made plain) | 1 (+ in 813236DC) | 1 (+1) | astra 1, opus 1 | none | **BUILT t120_unvolatile** 1/1 (8009C5EC); 813236DC miss (needs the `s16` parameter too) |
| 10 | a narrow cast at the kept use written as the in-place shift pair (`KEEP(v); f((s16)v)` -> `v <<= 16; v >>= 16; f(v)`) | 1 | 1 | agy 1 | t94_castsplit d2 | **t94 EXTENDED (T94_CASTUSE)** 1/1 |
| 11 | a loop exit as `break` (blocks dbra reversal) + the loop variables reused for later values | 2 | 1 | opus 1 | - | one-off - NOT BUILT |
| 12 | a hand-written 16-byte block-copy loop -> one aggregate copy (block_move_loop regenerates it) | 1 | 1 | opus 1 | - | census 3 pinned rows with a `*(CopyN *)d = *(CopyN *)s` loop - NOT BUILT (the aggregate type must be invented per row) |
| 13 | `ASM_REG("$2")` return variable: the temp arm returns a literal, one more early return goes through the shared label | 1 | 1 | opus 1 | - | one-off - NOT BUILT |
| 14 | a statement moved between `n = i + 1;` and `i = n;` (the copy no longer adjacent to its producer) | 1 | 1 | opus 1 | - | census 0 other pinned rows - NOT BUILT |
| 15 | lifetimes: a fresh numerator local (sol 8008C504), two `base` lifetimes merged into one outer local (sol 80285E80), a helper + merged pointer lifetimes (astra 8092192C), one counter indexing both tables (astra 8028484C, 2) | 5 | 4 | sol 2, astra 2 | t87_lifetimemerge 8008C504 miss (near 26), 80285E80 miss (near 3) | one-offs of the t87/t89 family - NOT BUILT |
| 16 | if/goto dispatch ladder with `dispatch_zero = 0` + keep -> `switch` (agy 800A78F8); page constant -> the field symbol (agy 80093598) | 2 | 2 | agy 2 | t73 / t86 not re-run | one-offs - NOT BUILT |

Per model: claude-opus-5-5 34 pins / 15 rows (moves 1-9 and 11-14), astra 4 / 3, agy 3 / 3, sol 2 / 2,
sonnet 0 / 0 (17 rows served, 6 lanes).  The set-exactly-once family (#1, #2, #3, #5, #7, #9, #10) is 25 of the 43 pins.  dungeon/func_809CAE20 (#7) was staged
in r76_opus_b12_2/out after the owner's dead-initializer ruling, mid-harvest; it is counted here.

## Rows and splits

| row | lane | pins | move # |
|---|---|---|---|
| dungeon/func_80DFB054 | r76_opus_b12_1 | 1 | #4 |
| dungeon/func_8009A61C | r76_opus_b12_1 | 2 | #3 |
| dungeon/func_809F3C00 | r76_opus_b12_2 | 1 | #1 with #6 (goto'd `call; return` tail inline) |
| dungeon/func_80AC7A30 | r76_opus_b12_2 | 2 | #1 1, #12 1 |
| dungeon/func_81989320 | r76_opus_b12_2 | 2 | #6 1, #14 1 |
| dungeon/func_809CAE20 | r76_opus_b12_2 | 1 | #7 (dead_init) |
| dungeon/func_80BECDA4 | r76_opus_b37_2 | 6 | #1 (+ `x = f & K; f = x` on the `$2` local, a goto retargeted) |
| dungeon/func_80CE7A1C | r76_opus_b37_2 | 3 | #2 |
| dungeon/func_80E38914 | r76o_opus_b12 | 1 | #13 |
| dungeon/func_80E9D000 | r76o_opus_b12 | 2 | #11 |
| dungeon/func_809DB054 | r76o_opus_b12 | 1 | #5 |
| town/func_8032FD1C | r76o_opus_b37 | 1 | #2 (accumulator split) |
| dungeon/func_809815A8 | r76o_opus_b37 | 3 | #1 |
| dungeon/func_813236DC | r76o_opus_b37 | 4 | #1 (`s16` parameter) with #9 (volatile slot plain), one-trip blocks gone |
| dungeon/func_80F88C94 | r76o_opus_b37 | 4 | #8 with #6 |
| dungeon/func_8092192C | r76_astra_b37_1 | 1 | #15 |
| dungeon/func_8009C5EC | r76_astra_b37_1 | 1 | #9 |
| dungeon/func_8028484C | r76_astra_b37_1 | 2 | #15 |
| dungeon/func_800A78F8 | r76_agy_b12_1 | 1 | #16 (switch) |
| dungeon/func_800B5DFC | r76_agy_b37_1 | 1 | #10 |
| dungeon/func_80093598 | r76_agy_b37_1 | 1 | #16 (page symbol) |
| dungeon/func_8008C504 | r76_sol6_b12_1 | 1 | #15 |
| dungeon/func_80285E80 | r76_sol6_b12_1 | 1 | #15 |

## The set-exactly-once mechanism (read this first)

An `ASM_KEEP(v)` is `__asm__ __volatile__("" : "=r"(v) : "0"(v))`: a SECOND set of v.  gcc 2.x gives two boosts only to
a pseudo with `REG_N_SETS == 1`: sched.c `birthing_insn_p` (the producer raised to LAUNCH_PRIORITY, so the backward
scheduler emits it last in its block) and local-alloc.c `update_equiv_regs` (a REG_EQUIV/REG_EQUAL-noted single set
records an equivalence and DOUBLES `REG_LIVE_LENGTH`, which halves global.c's allocno priority
`floor_log2(refs) * refs / live_length`).  A keep switches both off; the lanes' resolving moves make the C set the
variable the number of times the keep faked, in plain C:

- **fewer sets** (the boosts come back): use the parameter directly (its entry copy is REG_EQUIV to the stack slot -
  `alloc_sim.doubled()` shows parameters 80-82 of dungeon/func_807AE960 doubled), fold `v = E; v op= F`, set an
  accumulator once, drop an argument register the callee never reads (so `$6` is single-set), drop a `volatile`;
- **more sets** (the boosts go away where retail did not have them): route a call result through the kept copy, spell a
  cast as the in-place shift pair, add a dead `= 0` at the declaration (owner ruling 2026-09-23).

`tools/alloc_sim.py` did not need a doubling MODEL: the lreg dump's `used N times across K insns` is read after
`update_equiv_regs`, so `simulate()` already sees doubled lengths (opus, open row dungeon/func_807AE960: "Flow live 22 becomes 16
after sched, and 32 in lreg").  What it lacked was WHICH allocnos are doubled; it now reads it: `set_counts(lreg)` (REG_N_SETS as the
insn stream shows it, REG_EQUIV per pseudo), `doubled(rd)`, `priority_undoubled(rd, p)` (the what-if for adding a second
set).  gcc 2.7.2's `dump_flow_info` prints no `set N times`, so the count is read off the RTL.

## The lanes' rules, per built / extended move

**#1 (t69 T69_UNPIN_REST).**  opus, `func_80BECDA4`: "APPEARS: a `T *p = p_arg;` local copy of a parameter together
with an `ASM_REG`/`ASM_KEEP_NV` on it at function entry, where the erased residue is prologue-copy order plus a
callee-saved rotation. RESOLVES: rename the parameter to the local's name, delete the copy, and let REG_EQUIV live
doubling set the priority."  opus, `func_809815A8`: "use the parameter itself (its doubled sched1 live length lowers
its rank), keep genuinely separate pointer variables as plain copies."  opus, `func_80AC7A30`: "`local = param_in;`
copies plus `ASM_KEEP(local)` whose erase residue is only the prologue order ... RESOLVES: use the parameters directly".
Measured: t69's nearest candidate on 809815A8 (entity+motion dropped) was d2 - the lane also erased the third copy's
`ASM_REG` (`entity_state`) and read `sprite` for `sprite_in`.  The opening offers the three nearest dropped-copy texts
again with each surviving copy's parameter reads renamed to it (never a parameter the merge itself created) and the
remaining pins erased jointly and singly.
**#2 (t118).**  opus, `func_80CE7A1C`: "APPEARS: an `ASM_KEEP(v)` whose lone erasure is a same-opcode reorder
(MOVED/BOTH), and v is a pointer set once in C. RESOLVES: erase it. If a reorder remains, look for an in-place compound
assignment (`v <<= k; v >>= m;`, `v -= c`) in the reordered block and fold it into one expression, so each pseudo in the
block is set once."  opus, `func_8032FD1C`: "the three-times-set `dst_index` (18 refs / 17 live, rank 0) avoided $a0
because src_cursor prefers $a0 ... single-set it is 6 refs / 5 live and takes $a0".
**#3 (T115_ADDRCARRIER / T113_ADDRCARRIER).**  opus, `func_8009A61C`: "APPEARS: argument-register `ASM_REG` pins
(`$4`..`$7`) on a call whose erase is a 2-4 line reorder of the argument moves, in a function where an earlier call
passes an argument the callee does not take (a register that is set twice). RESOLVES: drop the surplus argument (so the
argument register is single-set and gets the birthing boost) and pass the address argument directly."
**#4 (T111_HOIST).**  opus, `func_80DFB054`: "APPEARS: a `p = q + C; ASM_KEEP(p)` whose erase census shows `C'($q)`
addresses replacing `($p)` addresses (cse association of pointer+const). RESOLVES: `p = q; p = p + C;` ... If a statement
between the KEEP and the next call loses its position, hoist it into the previous block."
**#5 (T115_CALLCOPY).**  opus, `func_809DB054`: "APPEARS: `ASM_KEEP(v)` right before a call that takes v, where v is a
copy of another variable and is re-set to that variable right after the call. RESOLVES: assign the call's result to v,
then copy it to the result variable, so the re-set is no longer redundant for cse."
**#7 (t119).**  opus, `func_809CAE20`: "`x = call(); y = x; ASM_KEEP(x); mem = x; if (y ...)` ... RESOLVES: store before
the copy and give `y` a life beyond the cse block" - byte-exact only with `void *effect = 0;`, which the owner's
2026-09-23 ruling admits (a dead zero initializer at a DECLARATION; dead assignments between statements stay banned).
**#9 (t120).**  astra, `func_8009C5EC`: "APPEARS: a pinned wide local receives a volatile byte load, and erasing the
binding introduces a redundant extension/mask. RESOLVES: remove the recovered volatile access together with the
register binding, allowing `combine` to form a zero-extending memory load".
**#10 (T94_CASTUSE).**  agy, `func_800B5DFC` (no REPORT; the diff): `ASM_KEEP_NV(packet_or_angle); f((s16)packet_or_angle)`
-> `packet_or_angle <<= 16; packet_or_angle >>= 16; f(packet_or_angle)`.

## Generators: exemplar checks and sweeps

| generator | built / extended | exemplar check | sweep lane | eligible | exact | pins | staged (after holds) |
|---|---|---|---|---|---|---|---|
| t118_setonce | built | 2/2 (80CE7A1C 3/3 `scaled_y fold + greedy3`, 8032FD1C 1/1 `split`) | r76_h_t118_setonce | 247 | 11 | 14 | 9 rows / 10 pins |
| t119_deadinit | built | 1/1 (809CAE20 `add:effect:sink`) | r76_h_t119_deadinit | 455 | 5 | 5 | 4 / 4 |
| t69_prologue | T69_UNPIN_REST | 1/2 (809815A8 3/3; 80BECDA4 d4) | r76_h_t69_prologue | 285 | 9 | 29 | 8 / 26 |
| t115_carrierfold | T115_CALLCOPY | 1/1 (809DB054) | r76_h_t115_carrierfold (the 6 callcopy rows) | 6 | 6 | 6 | 5 / 5 |
| t115_carrierfold | T115_ADDRCARRIER | (via t113) | r76_h_t115_carrierfold2 (the address-carrier rows) | 108 | 1 | 1 | 1 / 1 |
| t113_sibarity | T113_ADDRCARRIER | 1/1 (8009A61C 2/2) | r76_h_t113_sibarity (address-carrier rows) | 43 | 1 | 1 | 1 / 1 |
| t111_selfadd | T111_HOIST | 1/1 (80DFB054 1/1) | - (no pinned row has a hoistable arm today: the exemplar landed) | 0 | - | - | - |
| t120_unvolatile | built | 1/1 (8009C5EC); 813236DC miss | r76_h_t120_unvolatile | 163 | 3 | 3 | 3 / 3 |
| t94_castsplit | T94_CASTUSE | 1/1 (800B5DFC 1/1) | r76_h_t94_castsplit (castuse rows) | 4 | 0 | 0 | - |
| t85_allocorder | T85_WIDE | 80F88C94: now an order site, best d142 | r76_h_t85_allocorder | 238 | 0 | 0 | - |
| t121_barrierstrip | built (probe) | - | r76_h_t121_barrierstrip / r76_h_barrier_compose | 241 / 184 | 0 / 2 | 0 / 2 | - / 2 rows, 2 pins |

Exact rows.  t118: dungeon/func_80E0F7C0, 80EF7000, 80F89A94, 810332A4 (10 -> 9), 81087818, 81820DB4 (2 -> 0), 81875828
(joint fold), 8187C45C, 818CFB74 (31 -> 30).  t119: town/func_800C0220 (`s32 motion_base = 0;`), dungeon/func_800A3A00
(`s32 one = 0;`), 81331C88 (`void *init_fn = 0;`, a KEEP_DEP_NV), 81988C1C (`u32 addr_mask = 0;`) - every one the ADD
direction; the REMOVE direction found nothing.  t69: the seven-row clone family dungeon/func_809755A8, 8097B5A8, 809875A8,
8098D5A8, 809935A8, 809995A8 (and the held exemplar 809815A8), 3 pins each at `entity+motion+unpin-1` - the exemplar's
own move, found without the `usecopy` step; dungeon/func_7FFEE0B8 5 -> 0 (`mode+list+unpin-all`), 80AEF904 6 -> 3.  t115
callcopy: the 809DB054 clone family - dungeon/func_80091258, 809CF054, 809E1054, 809ED054, 80A9B07C (1 -> 0 each).  t113:
dungeon/func_800C78A4.  t115 (address-carrier sweep): dungeon/func_80F89A94 2 -> 1 - by t115's own `fix` plan
on the text t118 had just landed (the address carrier itself found nothing).  t120: town/func_800C0220, dungeon/func_800A76D4, 80E0F7C0 (each a further pin on a row t118 /
t119 had just landed).

Landing (land_finished2.sh, isolated; state when this was written): `lane_r76_h_t118_setonce` 9 applied (10 pins),
`lane_r76_h_t119_deadinit` 4 applied (4 pins, four `dead_init` trade records), in the fin1125 transaction (gate
pending).  Staged for the next cycle: t69 8 rows / 26 pins, t115 callcopy 5 / 5, t113 1 / 1, barrier compose 2 / 2,
t120 1 live of 3 (two of its rows moved on under later landings; t120 is in the landing cascade now).  Census
"Pin sites now": 3,644 in 891 rows at the harvest's start (5581bdfe); 3,590 in 880 rows live in src/ at the end
(all landings in the window, this harvest's 14 among them; STATUS.md is rewritten by the lander's snapshot).

Catch-up after fin1125 (its cascade predates t118-t120 in cascade_extra.txt; the stale t120 / t115 / t118 candidates
sit on rows that later landings changed): `gen_drive.py --catchup` lanes `r76_h_t120_unvolatile_catchup` (3 changed
rows), `r76_h_t118_setonce_catchup` (7), `r76_h_t115_carrierfold_catchup` (633: its module changed after its first
sweep) - **0 exact**; the stale candidates' pins are not on the current text.

## Priority 2: the "stale" t85 verdicts

The lanes named dungeon/func_8008F228 and dungeon/func_80F88C94 as t85 refusals computed on older text.  Re-measured on
the current text (`r76_h_t85_allocorder_check_x`): **8008F228** is no longer eligible at all - its current text has no
callee-saved `ASM_REG` pin ("no callee-saved ASM_REG pin"), so the old verdict is moot, not wrong.  **80F88C94** refuses
identically on its current text ("erased allocno count 16 vs 13") - the verdict was not stale, the PRECONDITION was too
strict: `is_order_site` bounded the new allocnos by the callee-saved register pins only, while erasing the `$2` pin and
two `ASM_USE`s (second sets) adds allocnos of its own.  **T85_WIDE** (default on) bounds the count by the erased sites and
compares the SETS of callee-saved registers in use (an extra allocno may share a register).  On 80F88C94 t85 now runs its
levers: best d142 (lever d, `particle_offset_x` s32->s16) - the lane's solution was ten role splits + a tail duplication
+ loop invariants, not one lever.  Tree-wide (`r76_h_t85_allocorder`, 238 eligible): 107 rows pass the order-site test
(78 of 350 under the strict test at r61), **0 exact**; nearest 81254460 d6, 81332EC0 d10, 80BAF094 d11, 800BFCCC d12,
8046FF64 d12.  Refusal table: 27 "not a permutation", 26 "untrusted dump reading", 8 "no allocno changes register",
~60 "contested allocnos cross no call" (the preference family), 9 count bounds.

## Owner ruling 2026-09-23 (dead zero initializer) - tooling

- `tools/dead_init.py`: `trades(cur, new)` finds declarations gaining a `= 0` / `NULL` initializer; `record()` builds the
  `{"kind": "dead_init", ...}` trade record (same shape as the hand-written 809CAE20 one).
- `tools/apply_candidates.py` appends that record to `ledger/recipe_trades.jsonl` for every APPLIED landing whose
  candidate adds such an initializer (deduped against an existing record for the same id and init), so land_lanes.sh /
  land_gap.sh / land_finished2.sh record the trade without knowing about the lever.  The four t119 landings wrote theirs
  (11:25Z).
- `tools/status.py`: a "Dead-initializer trades" line next to the site-for-pin line (informational; the pin count is
  unchanged).

## Holds (the A/B overlap arms)

Every row that is in any `r76o_*` lane's `base/` is removed from the staged lanes before they are named `r76_h_*`
(sweeps run as `x76_h_*`, which land_finished2.sh's glob does not match; `held.jsonl` in each lane lists what moved to
`held/`): t118 town/func_8032FD1C, t69 dungeon/func_809815A8, t115 dungeon/func_809DB054.  Deduped against a model
lane's out/ with <= pins: t118 dungeon/func_80CE7A1C (r76_opus_b37_2 holds it at 2), t119 dungeon/func_809CAE20
(r76_opus_b12_2 at 0).

## Bounded negatives

- **Tail duplication (#6)** stays unbuilt as a family: t102 reaches d4-d138 on the three rows, and compose2 t69 -> t102
  on 809F3C00 is A-empty (t69 alone is d140 there); every exemplar pairs it with a second move.
- **80BECDA4** (opus, 6 of 7): t69 + T69_UNPIN_REST d4 - the lane also staged `x = owner->unk_98 & 0xFF7F; owner->unk_98 =
  x;` on the existing `$2` local and retargeted a goto; not composed.
- **t85 with T85_WIDE**: 107 order sites, 0 exact (above).
- **t94 T94_CASTUSE sweep**: 4 eligible rows (813236DC held), 0 exact.
- **t120 on 813236DC**: the volatile slot alone is d>0; the lane's win needs the `s16` parameter first.
- **Sonnet lanes**: 0 of 17 rows; their named mechanisms (the call-argument coalescing of 800BA09C / 81087818, reload_cse
  forgetting constants only at a CODE_LABEL (800AC3B0), the sched LUID tie-breaks) carry no generator rule.
- Not built for population: #12 block-copy loop (3 rows), #14 (0 rows), #11 / #13 / #16 one-offs.

## Barrier-strip composition probe (coordinator request)

`t121_barrierstrip` (built for the probe): every one-trip `do { } while (0)` block rewritten as a plain `{ }` block and
every `ASM_SCHED_BARRIER` erased, all of a function's barriers at once and each alone.  Standalone
(`r76_h_t121_barrierstrip`): 241 eligible rows, **0 exact** - 17 rows have a listing-exact strip, 15 of them remove no
pin site (a do-while strip only: scaffolding, not a pin), and the 2 that do were not byte-exact.  Composition
(`compose2.py --A t121_barrierstrip --B t2_pins,t118,t119,t69,t115,t117,t120,t94,t85,t87 --k 2`, lane
`r76_h_barrier_compose`) over the 184 rows whose nearest stripped text is within listing distance 12 (+ 800A6A78):
**2 wins, 1,198 s** - town/func_80098520 8 -> 7 (the do-while around the `y_step_or_side` block stripped, then its
`ASM_KEEP_NV` erased; t2_pins, t118 and t119 each reach it) and dungeon/func_8008A31C 6 -> 5 (the do-while around a
volatile byte load stripped, then t120 drops the `volatile` and the `init_anim ASM_REG("$4")`).  The named example
dungeon/func_800A6A78 stays a miss: stripped texts d4 / d8, best B near 9 (t115 / t119) - the lane's own finding
(the order half still needs a memory dependence the fences supplied) holds.  t121 is NOT added to the cascade (0
standalone); the composition is the lever, at ~6.5 s a row.
