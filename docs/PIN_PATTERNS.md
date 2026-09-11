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
| `x % (1 << n)` | `q = x; q >>= n; if (x < 0) q = (x + m) >> n; r = x - (q << n)` | expand_divmod's `copy_to_mode_reg` | 35 pinned rows (2026-09-09) | 2 rows by the reg-rename lane; no sweep yet |
| `abs(x)` (t16) | `if (t < 0) { d = -d; }`, guard on d or on what d was copied from | MIPS `abssi2` = `bgez; move; subu` as one insn | 142 pinned rows eligible | **36 rows, 75 pins off, 3 rows pin-free** — half of them freed OTHER pins once the idiom was gone |
| `x / (1 << n)` (t17) | `if (t < 0) d += 2^n-1; … d >> n` | expand_divmod's branch form | 108 pinned rows eligible | 2 rows, 2 pins; in 64 rows the `/` spelling is byte-identical and frees nothing — a negative, with a reason |

**The precondition that separates them.** An idiom's hand spelling needs a pin only when a
branch arm *reads the copy* (`d = -d`): that read is what cse folds into the source. The bias
spelling of a division reads the source (`d = t + K`), so there is nothing to fold, and m2c's text
already reproduces retail — with the copy (`main/func_8001AA50`) or in place
(`town/func_80097A54`). Check this before building the next idiom plugin: count the sites whose
arm reads the copy, not the sites where the pattern appears.

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
