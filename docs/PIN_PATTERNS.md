# Pin patterns — what a live pin holds, and what has ever freed one (2026-09-11)

Measured by `tools/pin_sites.py` (per-site census, `ledger/pins_site.jsonl`; subset erasure,
`ledger/pins_subsets.jsonl`) and a replay of every landed pin removal since the swap-over (the
pre-fix text recovered from git). The question it answers is the owner's: *are the thousands of
pins really a few dozen patterns, and do pins that sit together hold each other up?*

The numbers below are as measured on 2026-09-11. `tools/pin_patterns.py --history >
docs/PIN_PATTERNS_DATA.md` regenerates every table from the ledgers (only records at a row's
current text count, so re-run `pin_sites.py` on changed rows first); this file is the reading.

## 1. The measurement

Every live site of every pinned row outside the day's sweep set (9,249 sites) was erased **on its
own** from the current text and scored with the aligned-regions view, so each record carries the
retail word positions that move, next to what the site is: macro, pinned variable, its declared
type, how it is defined (load / constant / KSEG0 literal / call / parameter / arithmetic / copy),
and where it sits.

* **No live pin is dead on its own** (0 of 8,972 records at the current text). T2 has done its
  job; every remaining pin holds something — alone, or with others.
* Damage when erased alone (8,821 non-marker sites): 1–2 words 1,681 · 3–5 2,040 · 6–12 2,296 ·
  13+ 2,804. A fifth of the live sites are one or two words from falling.
* Marker pins (`ASM_TAILSLOT_PIN*`, `ASM_PAGEBASE_PIN`, `ASM_JALDELAY_PIN`) are assembler-keyed
  scaffolding, not C shapes; they are counted separately (151) and left out below.

## 2. How many patterns?

It depends on what "pattern" means, and the answer is different at each level:

| granularity | clusters | cover 50 % | cover 80 % | cover 90 % |
|---|---:|---:|---:|---:|
| residue class (what kind of damage) | 15 | 3 | 7 | 10 |
| **macro family × residue class** (the mechanism) | 103 | 8 | **24** | **37** |
| residue signature (the exact instruction change) | 2,860 | 36 | 1,096 | 1,978 |
| macro family × signature | 3,345 | 94 | 1,581 | 2,463 |

Within 5 words of falling (3,721 sites) the head is sharper: 5 signatures cover half the sites,
14 family×class clusters cover 80 %.

**Reading.** The owner's "20–30 patterns" is right at the level of *mechanism*: two dozen
family×class clusters cover four fifths of the sites. It is not right at the level of *fix*: the
exact instruction change has a long tail, and the same mechanism needs a different C shape
depending on conditions the site carries (what the pinned value was computed from, whether a copy
of it is read in a branch arm, which build compiled it). A pattern is therefore a triple — the
mechanism, the APPEARS condition, and the RESOLVES shape — and only the first of the three is
few.

## 3. The head, by mechanism (sites within 12 words, single erasure)

| signature | sites | mechanism | what frees it |
|---|---:|---|---|
| `rename` / `rename*` | 1,896 | same instructions, registers differ: cse collapsed two same-value pseudos, or pure colouring | a value-preserving mode change (`narrow`), un-expanding a compiler idiom (t16, `%`) — see 3a |
| `move:move move:sw`, `move:move`, `move:addiu`, `move:lw`, … | ~750 | one instruction moved by the scheduler | a `do {} while (0)` fence at the right statement (40 % of all historical removals) |
| `+addiu -ori move:lui` and kin | ~240 | a KSEG0 literal (`0x800D0000 - 0x34C` folds to `lui;ori`) where retail relocates a symbol (`lui;addiu`) | the symbol, plus a second non-folding set (the `litsym` family; 0 generator closes so far) |
| `operand*` | ~100 | same instructions, an immediate differs | read per row |

### 3a. Inside the rename cluster

At instruction level (sites within 12 words): a destination renamed 1,691 sites, a source 953, a
store/branch reading another register 947, both 712 — and two directional kinds that name a
mechanism:

* **FOLD — retail computes in place, gcc reads the copy's source** (243 sites). `negu` 27 is the
  `abs()` idiom (t16). `addiu` 206 instructions / 124 sites is **address materialisation, not
  loops** (123 of 124 outside any loop; 113 are `ASM_REG` on a pointer loaded from a global or an
  address): retail builds `lui $a2; addiu $a2,$a2,%lo` in one register, gcc splits the high part
  into another (`lui $v0; addiu $a2,$v0,%lo`), and the pin forces the single register. `sll` 44 is
  the sign-extension copy (`x = (s16)x` after `y = x`), the `narrow` family.
* **SPLIT — gcc computes in place, retail reads another register** (185 sites): `addiu` 75,
  `addu` 33, `sra` 21, `andi` 21.

## 4. Linkage

Every subset of two or more pins of every 2..5-pin row (5,018 subsets over 575 rows, every one
scored). For a pair, compare the joint cost with the two single costs:

| relation | pairs | share | reading |
|---|---:|---:|---|
| additive (joint ≈ sum) | 1,284 | 53 % | independent: each pin holds its own instructions |
| overlap (joint < sum) | 961 | 40 % | the two pins hold the SAME instructions — remove them as a unit |
| synergy (joint > sum) | 131 | 5 % | removing both breaks something neither breaks alone |
| cancel (joint < either single) | 29 | 1 % | the pair falls more easily together than apart: invisible to a one-at-a-time search |

Distance matters, but less than it looks:

| line gap between the pins | pairs | overlap | synergy |
|---|---:|---:|---:|
| ≤ 3 lines | 600 | 52 % | 10 % |
| 4–15 lines | 741 | 43 % | 4 % |
| 16+ lines | 1,064 | 32 % | 3 % |

So the owner's intuition holds both ways: pins that sit together usually hold one thing, and a
third of the pins that sit far apart are still intertwined — typically a register pin at the
declaration and a keep at the use. **12 proper subsets were exact** (5 × two of four pins, 5 × two
of five, 2 × three of five) — partial removals that T2 (singles, source order), the strip (all at
once) and t15's partial path (all but one, budget permitting) had never tried. The largest per row
landed as `pin_subsets` (10 rows). No full set was exact: the strip census is still right that
no 2..5-pin row falls to erasure alone.

The consequence for the search: a row's pins should be grouped by overlap before any shape is
tried, and a shape tried against a group, not a pin. `ledger/pins_subsets.jsonl` is that grouping
for the 575 rows it covers; rows with six or more pins have single-site data only.

## 5. What has ever freed a pin

Replay of 301 landings (428 removed sites) from t15, the depin lanes, the cell fixes and t9:

| fix | removed sites |
|---|---:|
| t15 `fence` (`do { stmt; } while (0)`) | 172 |
| t15 `narrow` (value-preserving mode change) | 42 |
| t15 `fence-return` | 25 |
| wrong compiler cell (`t13_cellfix`, pure erasure) | 23 |
| depin lanes (hand rewrites of every kind) | ~70 |
| t15 `efence`, `fence2`, `fence+fence-return` | 31 |
| t15 `depinject`, `deadstore`, `dup_after_if`, partial strip | ~40 |

**Over half of every pin removed before this session (≈55 %, 237 of 428) was replaced by a fence
or a fence variant** — compiler steering spelled in portable C, not a recovered source shape.
With this session's t16/t17/subset landings in the replay the share falls to 47 % (244 of 515):
the first sizeable batch of removals that were not fences. Only 44 of the 428 were pure erasure. The
removed sites were REG 194, KEEP 145, barrier 52, USE 22, KEEP_NV 13.

## 6. Compiler idioms — the family that pays

A multi-instruction sequence that gcc's MIPS backend emits as ONE insn (or with its own fresh
pseudo) is invisible to cse. m2c decompiles it into several statements, cse then folds the copy
those statements spell out, and a pin appears to put the copy back. Writing the sequence back as
the C operator restores the compiler's own copy, and the pin has nothing left to hold.

| idiom | APPEARS | RESOLVES | POPULATION | RESULT |
|---|---|---|---|---|
| `x % (1 << n)` (t19) | bias `if (t < 0)` (`b = x + K`, `b += K`, `b = (x + K) >> n`), then `x - ((b >> n) << n)` / `x - (q << n)` | expand_divmod's `copy_to_mode_reg` | 42 idioms in 28 pinned rows (arm reads a copy in 13) | 2 rows by the reg-rename lane (09-09); **t19: 2 rows, 2 pins** (one copy arm, one source arm freed by the dead pass); 16 byte-neutral rewrites |
| `abs(x)` (t16) | `if (t < 0) { d = -d; }`, guard on d or on what d was copied from | MIPS `abssi2` = `bgez; move; subu` as one insn | 142 pinned rows eligible | **36 rows, 75 pins off, 3 rows pin-free** — half of them freed OTHER pins once the idiom was gone |
| `x / (1 << n)` (t17) | `if (t < 0) d += 2^n-1; … d >> n` | expand_divmod's branch form | 108 pinned rows eligible | 2 rows, 2 pins; in 64 rows the `/` spelling is byte-identical and frees nothing — a negative, with a reason |

**The precondition that separates them.** An idiom's hand spelling needs a pin only when a
branch arm *reads the copy* (`d = -d`): that read is what cse folds into the source. The bias
spelling of a division reads the source (`d = t + K`), so there is nothing to fold, and m2c's text
already reproduces retail — with the copy (`main/func_8001AA50`) or in place
(`town/func_80097A54`). Check this before building the next idiom plugin: count the sites whose
arm reads the copy, not the sites where the pattern appears.

**t19 refines it: necessary-looking, not sufficient.** Of the 13 `%` rows whose arm reads a copy,
one gained (`dungeon/func_81934928`, the lane's own spelling, jointly with its pins); one
source-arm row gained too (`town/func_808B2D90`, where the rewrite left an `ASM_REG` nothing to
hold). The rule explains abs against division; it does not predict a row.

## 7. Next leads, ranked

1. **Search by pin GROUP, not by pin.** 40 % of pin pairs hold the same instructions. Extend
   `pin_sites.py --subsets` to pairs on the 6–10-pin rows (370 rows, ~9,000 scorer runs, about an
   hour at ten workers), group each row's pins by overlap, and hand a group — not a site — to t15,
   the idiom plugins and the lanes. The 12 exact subsets are the free part of that; the grouping
   is the useful part.
2. **The `%` idiom** (`r = x - (q << n)` after the bias; 33 remainder sites in pinned rows): the
   lane-proven mechanism, now one matcher and one spelling on top of `idiom_search`. Check first
   that the hand spelling reads the copy (section 6), then build it.
3. **FOLD-`addiu`, address materialisation** (124 sites / 99 rows, 113 of them `ASM_REG`): retail
   builds a symbol address in ONE register, gcc splits the `%hi` into another. The lanes went 0/4
   on this class by reshaping C; it is a compiler question first — which cells split an address
   (`la` as one insn vs HIGH/LO_SUM) and what makes the split pseudo die early. Measure it with the
   instrumented cc1 in `toolchain/compiler-src/patches/` before any lane is briefed.
4. **FOLD-`sll`, the sign-extension copy** (43 sites / 37 rows): `narrow`'s family, not caught by
   it. Find the missing precondition (where the copy sits relative to the cast) on three rows by
   hand, then widen `narrow`.
5. **Readability, not pins:** t17's 64 byte-neutral `/` rewrites and t16's are clean source
   (`d = abs(d)`, `x / 4096`) that carry no pin gain. They belong to an L2/L4 readability pass, not
   to this campaign; the journals name the rows.
6. The scheduler-move head (~750 sites) is what the fence family already covers; the literal-page
   family (~240) waits on the second non-folding set. Neither is new.

## 8. Two classes measured before any lane is briefed (2026-09-11, afternoon)

### 8a. Address materialisation (FOLD-`addiu` with a `%lo`: 121 sites within 12 words)

**Mechanism, from the genuine SN source** (`config/mips/mips.md` `movsi`, `mips.c:3678`): with GAS
and optimisation on, every non-GP symbol address is split at expand time — `tem = HIGH (sym)`
into a FRESH pseudo, then `dest = LO_SUM (tem, sym)`. Retail's one-register form
(`lui $a1; addiu $a1,$a1,%lo`) means `tem` and `dest` got the same hard register.

**Measured with the instrumented cc1** (the preserved `cc1-oracle-all-blocks` build of the genuine
SN source, kept with the compiler sources outside this tree; output byte-identical to the shipped
cc1 on both texts), on
`dungeon/func_8098D5A8` (`register u8 *anim_table ASM_REG("$5")`):

| text | `dest` | `tem`'s local-alloc quantity | code |
|---|---|---|---|
| pinned | hard reg 5 | `sugg=5 phys=5` | `lui $a1; addiu $a1,$a1,%lo` (retail) |
| pin erased | `reg/v 91`, "used 6 times across 22 insns" — one variable for TWO arms | no suggestion, `phys=2` | `lui $v0; addiu $a1,$v0,%lo` |
| one variable per arm, or the symbol inlined and the variable dropped | block-local pseudo | tied | `lui $v1; addiu $v1,$v1,%lo` — one register again |

So the tie needs a destination local-alloc can see: a hard register, or a pseudo that lives in one
basic block. m2c's habit of reusing ONE pointer variable across arms makes it a cross-block
pseudo, and the split is what the pin was holding. **82 of the 121 sites pin a pointer that is
assigned from an address two or more times** — the population for that half of the fix.

It is only half. With the tie restored, local-alloc's priority order picks the register, and on
this row the address quantity and its neighbour (`facing_angle`) swap `$v1`/`$a1`: residue 16,
where the pinned-then-erased text sat at 4; four statement orders gave 16–32. A lane brief for
this class must name both halves — block-local first, then the register choice among that
block's quantities — and inlining the symbol while the variable stays is inert (cse folds the uses
back into it: byte-identical, measured).

**Closed (2026-09-11, a native lane with the oracle; `work/native_lane/func_8098D5A8/REPORT.md`).**
The second handle is not a register preference at all: **m2c's `goto` was its rendering of jump2's
post-reload cross-jumping between two SEPARATE calls.** Written as each arm making its own call,
with the temporaries forward-substituted into the call's arguments (expression form), the arm is one
basic block; the address quantity then ranks last by local-alloc's `QTY_CMP_PRI` (4545 against the
direction chain 22500, `%hi` 10000, facing 5000), `find_free_reg` scans v0, v1, a0, a1 in order,
v0/v1 are taken and a0 is live because sched1 hoisted the `a0 = s4` argument copy into the address's
life - so it gets `$a1` by exclusion, not suggestion (the oracle prints `sugg= copy=` empty). Four
conditions, each broken by one measured variant (one variable per value, facing kept global, the
chain kept global, the goto tail kept: 16–51 words). The same rewrite closes the row's six siblings
(same function in six other overlays): 7 pins, landed as `t21_crossjump`. Only the goto-undoing and
substitution are mechanical; whether the register then lands right is a post-sched1 priority margin,
so every candidate must be scored. Reach: 90 pinned pointers sit behind a goto whose label starts
with a call (the cross-jump rendering) — the population for a statement-level generator.

### 8b. The sign-extension copy (FOLD-`sll`: 102 sites / 76 rows within 12 words)

71 are sign extensions (`sll …,0x10` / `0x18`), 31 are index scaling (`sll …,2/3/5`) — a different
mechanism the old count mixed in. The sign-extension shape: `y = x; KEEP(x); … (s16)x` — retail
extends in the COPY's register (`sll $a1,$a1,16`), gcc reads the source (`sll $a1,$s3,16`).
`narrow` never sees it: it retypes only a plain local declaration with no initializer. Hand tests on
two one-word rows (`dungeon/func_800B5DFC`, `town/func_800ABBF8`): reading the copy at the use,
reversing the copy direction, an `s16` temp — all inert (1 → 1) or worse (→ 5). The variable map
is the wrong axis here too.

The oracle trace of `dungeon/func_800B5DFC` (2.7.2-cdk, output identical to the shipped cc1) says
why: the unpinned `sll` reads `reg/v:SI 18 s2` — `slot_or_angle`, which ANOTHER pin of the row
(`ASM_REG("$18")`, 61 words alone) fixes in a hard register, while `packet_or_angle` is fixed in
`$16` by a third (`ASM_REG("$16")`, 63 words). `slot_or_angle = packet_or_angle` makes the two
hard-register variables one cse class, and the `(s16)` use is rewritten to the other one; the
one-word `ASM_KEEP_NV` only stands between them. The site's cost of 1 is an artefact of the row's
register pins: the fix belongs to that group, not to `narrow`. Count how many of the 71 sites
have a hard-register variable on BOTH sides of the copy before widening `narrow` at all.

## 9. The fence study — what a `do { } while (0)` stands for (2026-09-11)

The owner stopped t18 at ~4,200 of 6,767 rows to ask whether the fences hide a real 1997 C shape,
including one specific theory: a compiled-out debug hook (`#define HOOK() do { } while (DEBUG)`,
0 in the release build, 1 to spin until a debugger attaches). An Opus lane took 22 rows / 24
fence sites (16 landed that day by t18, 6 older empty fences from t15), 184 scorer runs, and
per-pass `-da` dumps of fenced vs unfenced text. Every claimed exact was re-verified here.

**How a fence acts** (gcc 2.7.2 source + the dumps; no fence changes the basic-block count):
a loop note is a full barrier to the scheduler (14 sites: 13 sched1, 1 sched2); cse ends its
block at the loop-end note and will not follow a jump past it (8); flow weights the references
inside a loop, which changes allocation priority (2 — `town/func_8046C048`).

**The debug-hook theory: the bytes allow it, the positions do not.** One EMPTY `do {} while (0);`
next to the statement reproduces retail at 22 of 24 sites, and `while (0) { }` / `for (;0;) { }`
are byte-identical to it in all 18 checks. But it works on one specific side of one specific
statement (before only 9, after only 4, either 3), never at the natural home of a hook — function
entry: 0 of 20 — and the two allocation-weight fences cannot be an empty loop at all.

| verdict | rows | what it means |
|---|---:|---|
| H3 — a natural shape, no fence at all | 8 | drop a copy and use its source (`town/func_80878714`, `town/func_800A29F0`); the store / `\|=` / `&=` written inside both if-arms instead of a join temp (`town/func_800C5228`, `town/func_800A7FDC`); `return` inside a loop → `break` + return after it (`town/func_800ABDC8`); a pointer walk → an array-indexed `for` (`dungeon/func_8009A874`/`924`, the pointers were loop's output); the post-increment folded into its use, `sum += (entry++)->field18` (`main/func_8001AA50`) |
| H2 — a shared statement macro | 2 | `dungeon/func_80091258` and `func_80087054` carry the same control-flag store unit (`D_80083460.unk_02 \|= 0x80`) and set-action stores; wrapping the flag store as a unit also frees `ASM_KEEP(saved_target)` — inline that is a pin for a fence (net 0), so it only pays as a real named macro in a shared header |
| H4 — a barrier and nothing else | 12 | ~55 %: 11 byte-compatible with an empty fence on one side, 1 row of allocation-weight fences |

**Landed as `t20_fencefree`: the 8 H3 rows** — 8 fences gone, nothing added, two rows now carry
neither pins nor fences (`dungeon/func_8009A874`, `func_8009A924`). A macro-shaped wrap that
matched elsewhere proves nothing: its closing brace always sat where an empty fence already
matched. And because census excludes `#define` bodies, naming the H4 fences as macros would hide
the debt without paying it — they stay counted.

**Follow-up on the five H4 near misses** (best fence-free spelling within 1–5 words; ~25 runs
each, gcc's own `.s` used as a free pre-filter): **one closed — `town/func_800B6514`**, m2c's goto
loop written as the real `do { ... } while (slot < 5);` with the loop increment ONCE at the end
instead of in each arm (a sixth shape: at the join sched1 can no longer hoist the increment above
the call, and the delay-slot filler re-creates retail's per-arm copy). Landed as `t20_fencefree`
(9 rows). The other four are stuck on a named heuristic, not on budget: `dungeon/func_808CB16C` —
sched's single-set priority boost and hazard test inside a two-insn region between two volatile
keeps; `main/func_80013128` — sched2's "greater potential hazard" ordering around an unaligned
block move; `town/func_80330560` — a load-delay stall only a block boundary reproduces;
`town/func_80810F98` — cse following a one-use label that sits right after a noreturn call. Three
of them sit between OTHER pins of the row (the keeps that bound 808CB16C's region, 80330560's
register pin and asm alias, 80810F98's `ASM_REG("$4")` and noreturn attribute): their fences may
only fall together with those pins — a group question, not a fence question.

**Rules it leaves:** try the six natural shapes BEFORE any fence (they are the next generators);
when a fence does land, try an empty fence on each side — if neither matches, the fence works
through allocation weighting and cannot be a macro at all. `census.py` now counts `while (0) { }`
and `for (;0;)` too (none in the tree yet; a lane that learned the equivalence could otherwise
trade a counted fence for an invisible one). Share of the ~400 fences in the tree, from a sample
of small functions: natural shapes perhaps a third, evidenced macros ~10 %, about half H4.

## 10. The natural shapes as generators — t20 over every fenced row (2026-09-11, late)

Section 9's shapes, one generator each (`tools/xform/natural.py`: `dropcopy`, `armstore`,
`ret2break`, `ptr2index`, `postinc`, `gotoloop`, plus agy's base-page `basesym`), searched per fence
by `tools/xform/t20_fencefree.py`: take the fence off (if the text is still exact, the fence was
dead); otherwise the shapes over the WHOLE function, nearest the fence first — the shape lives next
to the fence, not in it (the if/else before a fenced call, the copy a fenced statement reads) — two
greedy rounds, then with one pin near the fence erased too; last, the shapes on the text itself
where a shape deletes a pin by itself (a copy's `register … ASM_REG` declaration, a keep on a page
base). A candidate lands only when pins do not grow and pins + fences strictly fall.

**Acceptance before any sweep** (the nine rows section 9 closed by hand, from their fenced
pre-images, byte-exact through the scorer): all nine close again with no fence and no new pin — and
the smallest closing step is often less than the hand edit. `dungeon/func_8009A874` needs only
`ptr2index` (the lane also rewrote its goto/return structure); `town/func_800B6514` only the goto-form
join hoist (the lane wrote the whole do/while); `main/func_8001AA50` only the post-increment (no temp
fold). `dungeon/func_8009A924` needs a second step, m2c's counted do/while as the `for` it came from —
`dowhile2for` now takes a counter started in its declaration and turns a `goto next` before the
increment into `continue`. agy's two base-page rows reproduce too: `town/func_8077DC0C` 6 → 5 pins;
`town/func_8050E100`'s two fences are dead alone, then `basesym` twice: 2 → 0 pins, without the arm
collapse the lane needed.

**Over every fenced row** (503 rows, 692 fences in scored code, 16 min at 12 workers): 122 rows
landed — **151 fences and 21 pins off, nothing added: net −172**; 38 rows now carry neither. By what
the fence wrapped (against HEAD):

| fence body | fences | off |
|---|---:|---:|
| local assignment | 316 | 67 |
| store | 115 | 21 |
| several statements | 88 | 28 |
| copy `x = y` | 55 | 12 |
| empty | 37 | 11 |
| `return` | 33 | 6 |
| call statement | 30 | 6 |
| `x = <page literal>` | 15 | 0 |

**Most of it was dead fences: 123 of the 151 came off alone** — exact with the fence simply taken
off. 109 of those 123 sit in rows where no t15/t18 sweep ever landed a fence: the agent lanes wrote
them, and nothing re-tested a fence the way t2 re-tests every pin after every landing. The shapes
took the other 28 fences and the 21 pins: `dropcopy` 11 at a fence + 10 in the pin pass, `dup_after_if`
7 (t15's statement in both arms — it trades a fence for a duplicated statement), `narrow` 6,
`armstore` 4, `basesym` 4, one pin erased with its fence.

**The same shapes on the pinned rows that carry no fence** (585 rows where some shape's candidate
deletes a pin, plus the 10 fenced rows the first pass had searched with a `_declare` bug — it looked
for the new symbol in its own output and so never declared one): 83 rows, **121 pins off, nothing
added** — `dropcopy` 67, `basesym` 29, `ptr2index` 3. The base-page shape agy found twice is a family
once the generator writes the symbol at the sum (`p = (u8 *)0x80020000; ASM_KEEP(p); p += 0x61C0;`
→ `p = (u8 *)&D_800261C0;`): 29 rows, 33 steps in all. Then t2 over all 205 touched rows: 39 rows,
44 more pins dead once the fence or the copy beside them was gone.

**First phase** (205 rows, against HEAD): **186 pins + 151 fences off, nothing added — net −337**;
47 rows now carry neither pins nor fences; every landing byte-exact through the scorer and re-gated.
With the second phase below (t18 resumed, agy 4–6, the widened `basesym`: 71 rows, net −117), the
session comes to 268 rows, 307 pins off, 151 fences off and 4 added — **net −454**.

**t18 with the shapes first.** t18 resumed where the owner stopped it, its menu now leading with
the natural shapes and ending with the fences: 50 rows, 88 pins off, **4 fences added** (net −84).
Its first pass had landed 232 fence steps against ~20 real shapes; this pass 4 fences against 57
shape steps (`narrow` 34, `dropcopy` 8, `dup_after_if` 4, `basesym` 3, `gotoloop` 2, `armstore` 1)
and 5 group erasures. A fence was what t18 reached for when nothing else was on its menu.

**agy batches 4–6** (24 rows, fences forbidden): 6 landed — a callee prototype trimmed to the
argument it really takes, a load folded into its consumer, a hand-expanded `/4` written back as `/`,
the division bias as explicit branch arms, block temps folded into the store, and the base-page
shape on an integer local (`offset_addr = 0x80530000; … offset_addr += 0x6D6;` →
`(s32)&D_805306D6`). The last widened `basesym` (uncast literal, integer local, byte arithmetic):
from that row's pre-agy text all four of its page sites close, two more than the lane took.
Across the pack: 11 of 48 rows. The widened `basesym` over the 128 pinned rows it now reaches:
8 rows, 9 pins off, nothing added. agy pack 2's one gated row (`dungeon/func_8132A730`) spelled the
same page through an integer cast (`resource_addr = (s32)0x80170000; … += 0x1D90;`); `basesym` takes
that too now — from the row's pre-agy text it closes the lane's site and a second one — and over the
161 pinned rows it then reached: 9 rows, 9 pins and 2 fences off, nothing added. Three agy wins,
three widenings, 46 rows in all: the base-page shape is the family this campaign's lanes kept
finding.

**Research from other decomps (2026-09-12, `work/research/sotn_findings.md`).** A pass over
sotn-decomp, ygofm-decomp (cc1psx 2.8.1 + maspsx, the closest toolchain) and the permuter forks,
with BFM's harvest not repeated. The levers new to this tree: one name per pointer-chain step
instead of a reused cursor (ygofm, 34 -> 7 on one row); a named local, not a cast, to stop combine
substituting a sign-extend away; an lvalue cast (`*(s8 *)&x`) where a value cast is dropped; store
groups ordered by phase to dodge dead-store elimination; declaration placement as a register-class
lever; `find_cross_jump` compares only the block physically above a label, so arm order decides a
merge; and sotn's `FAKE` convention — shipped, matched code that uses a plain named local, an extra
copy, a dead block or an empty `if` where this tree spends an `ASM_*` macro. The first lever is now
`natural.splitcursor` (straight-line chains, `v = E0; v = f(v); …` → `v`, `v2`, `v3`, the
variable's pin dropped): 31 rows carry a candidate, 16 a pin-deleting one, **3 landed** (3 pins).
`FAKE`-style replacements are deliberately NOT mechanised yet: census cannot see a plain copy, so a
bulk trade would hide debt; if adopted they must carry a `FAKE` note that census counts.

**The scratchpad class, reasoned out** (a native lane, 2026-09-12, `work/native_lane/scratchpad/REPORT.md`;
42 rows pin a variable set from `0x1F80xxxx`). combine.c:3787 rewrites an addition as an OR when the
operands share no set bits, and it knows a variable set once from `0x1F800000` is exactly that
constant — so every scratch field address copied into an argument register or an `ASM_REG` local
becomes `ori` where retail has `addu`; `ASM_KEEP_NV(scratch)` hides the constant. Retail's `addu`
comes from **a real loop**: in a loop containing a call, loop.c substitutes a single-use invariant
temporary into its one use before combine, leaving nothing to merge — and gcc calls m2c's goto loop
"phony" and does none of it. `dungeon/func_800942BC` matched with no pin as `do { … if (!c) break;
… } while (1);` (`gotoloop` (d) and `realloop` now generate that, the latter with the loop's pins
erased). Two corollaries worth keeping: only VOLATILE asm with operands (`ASM_KEEP`, `ASM_SET`)
blocks a combine merge — `ASM_KEEP_NV`, `ASM_SCHED_BARRIER()` and volatile memory do not; and
flow.c adds the loop depth to every reference count, so making a loop real re-ranks local-alloc
for every other pin inside it (why it lands cleanly only where no other pin sits in the loop).

**What it says.** Section 9's "natural shapes perhaps a third" does not carry to the corpus with
these generators: at fences they took 28 of 692 (4 %); dead fences were 18 %; 78 % of the fences
remain. `ret2break`, `postinc` and `gotoloop` closed nothing outside their own test rows, and
`ptr2index` only 3 pins — the study's rows WERE those shapes' population. The shapes that carry are
the two that are also pin shapes: `dropcopy` (73 rows, 88 steps — mostly the copy a `register …
ASM_REG` or keep was pinning) and `basesym` (29 rows). The standing rule it leaves: **run t20 after every lane or
campaign landing**, as t2 is run for pins — a fence is re-testable debt, and nothing else tests it.
Readability pass on top: `armstore` now tries `D |= K` before `D = D | K` (three landed rows
respelled, byte-identical).
