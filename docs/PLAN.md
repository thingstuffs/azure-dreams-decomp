# azure-dreams-decomp (local checkout `azure-clean`): readable, byte-exact C for the whole game

Written 2026-09-07 after re-grounding in the upstream tree and an earlier clean-C attempt
(one function at a time through a heavy admission gate; 0.15 % of the game in 37 hours), which
this plan supersedes.

Goal (owner): human-readable, better-structured C for all of Azure Dreams that still rebuilds
the retail containers byte-exact. No deadline; efficiency matters.

---

## 1. Where things stand (measured 2026-09-07 02:45 UTC)

### 1.1 Upstream (byte-matching tree, master @ `7b62e858`)

| | |
|---|---|
| matched rows | ~7,000 across SLUS (884 TUs), MAIN 426, TOWN 2,701, DUNGEON 2,742 (+685 engine mirror), OVMOVIE 22 |
| honest exactness, name-blind assembler (09-05 rescore) | 5,862 / 5,882 overlay rows exact; 7 flip on maspsx name tables |
| bridge remediation (live upstream) | 90 bridged rows / 45 KB left of 191; 101 closed since 09-06 |
| per-row scorer | `tools/aligned_score.py` (overlays) / `tools/match.py` (SLUS), ~0.8 s per row |
| rename layer | `config/names.tsv` + `tools/apply_names.py` + `ccproc.py` emits `func_<addr> = <name>` alias; byte-exact by construction; only 20 names used so far |
| fidelity plan (08-31) | sweep engine `tools/fidelity_sweep.py` was **never built**; only `passthru_repair.py` (20 % of its class) exists |

What the matched corpus looks like, file by file (6,766 files):

| defect | files | notes |
|---|---:|---|
| m2c boilerplate block (61 lines of macros per file) | ~2,000 | pure text, no codegen |
| `M2C_FIELD(p, T*, off)` raw offset access | ~2,500 | needs a struct, even a partial one |
| m2c local names (`temp_v0_2`, `arg0`, `sp10`) | ~5,160 (76 %) | biggest readability hit; zero codegen risk to rename |
| `ASM_*` pin / barrier macros | ~2,100 files, 25,700 sites | dungeon: 1,374 files / 20,652 sites; 617 dungeon files carry >10 pins |
| `goto` control flow | ~1,550 | m2c shape; some is load-bearing for match |
| computed-goto jump tables (`goto *D_...[]`) | ~185 TUs | the hard tail |
| local address-named structs (`S_8xxx`, `Func8xxxState`) | ~600 | good raw material for headers |

Pin mix: `ASM_REG` 12,600 sites, `ASM_KEEP` 6,900, `ASM_KEEP_NV` 2,460, `ASM_SCHED_BARRIER` 1,330,
`ASM_TAILSLOT_PIN` ~570, the rest under 300 each.

### 1.2 Probes run today (read-only, upstream scorer, live maspsx, random stock-exact rows)

| transform | sample | result |
|---|---|---|
| T1 strip boilerplate, keep macros in a prelude | 36 rows | **35 exact**, 1 build failure (my prelude dropped `M2C_TRAP_IF`; moot with a real header) |
| T3 greedy single-site pin erasure | 30 pinned rows, 146 sites | **49 sites erased (34 %) byte-exact**; 23 `register … ASM_REG` + 26 statement pins; only 1 of 30 rows ends fully pin-free |

So: boilerplate and a third of the pins go for free by machine. Two thirds of pins are
load-bearing under the stock compiler; those functions need a real rewrite (agent tier) or keep
a documented pin.

### 1.3 The earlier attempt

An earlier clean-C campaign re-derived one function at a time through a gate with no include
root, a behaviour oracle, a role-play review and a release kit per batch: 146 rows / 4,248 B
(0.15 %) in 37 hours, with 1,699 rows parked by its own policies (unknown struct layout, pins,
unresolved calls) while 2,666 plain-C rows were never touched. Its principles were right
(isolation, stock compilers only, no name-keyed assembler tricks, an honest bytes metric);
its unit of work was wrong. What carries over: the 62 hand-cleaned bodies as refinement
candidates, its maspsx policy note, and the lesson that receipts are not progress.

---

## 2. The reframing

Clean C is a **transformation of the verified corpus**, not a re-derivation of it. Every row
upstream is already byte-exact. The product is produced by *layers of transforms that preserve
the bytes*, run corpus-wide by machines, with agents only on the residue that machines refuse.
Progress is measured in bytes at each cleanliness level, never in receipts.

Consequences:

1. **The unit of work is a transform, not a function.** One transform is written once, applied
   to thousands of rows, and every row is verified. A row that fails is *refused* and journalled,
   never guessed at.
2. **Verification is object equality, then retail equality.** For a transform that must not
   change codegen, "compiled object identical to the pinned upstream object" (`.text` bytes +
   relocations) is sufficient and costs one compile (~0.4 s). Retail-slice comparison through
   `aligned_score.py` / the window gates is the milestone check, not the per-edit check.
3. **The tree is derived and replayable.** `azure-clean` = upstream at a pinned commit → machine
   transforms → hand refinements stored per row. Refreshing the snapshot is a command (bump the
   pin, replay, re-verify, diff verdicts), which permanently removes the "snapshot is out of
   date" problem that killed the previous campaign's relevance in two days.
4. **Names are an alias layer.** `func_XXXXXXXX` / `D_XXXXXXXX` stay as permanent aliases
   (upstream's `ccproc.py` already does this); semantic names are a table, cheap to change,
   verified by byte equality.
5. **Feed back upstream at hold points.** Transforms that hold corpus-wide are exactly what
   upstream's fidelity ratchet wants; they get landed there in window-batched commits when the
   bridge wave is at a hold point, so the two trees converge over time instead of diverging.

---

## 3. Product shape (target)

```
azure-clean/
  PIN                       upstream commit the tree is derived from
  include/                  one header per subsystem: partial structs with explicit unk_XX,
                            prototypes, globals; m2c_compat.h holds the few residual macros
  src/slus/<module>.c       functions grouped by module, retail order inside a module
  src/main/…  src/town/…  src/dungeon/…  src/ovmovie/…
  refine/<container>/<func>.c   hand-refined bodies that supersede the generated ones
  names.tsv                 semantic names with evidence; aliases keep func_ addresses
  tools/                    census, verify, xform/*, sweep, refresh, status  (small)
  ledger/                   per-row: source sha, verdict, level, tool hashes (jsonl, append-only)
  docs/PLAN.md STATUS.md
```

Cleanliness levels per row (the metric; `STATUS.md` reports bytes at ≥ each level):

| level | meaning |
|---|---|
| L0 | verified byte-exact at the pin through stock cells and name-blind assembler |
| L1 | no boilerplate, no dead pins, no `LABEL_AS_CALL` / zero-arg pass-through (fidelity classes) and no pseudo-call to a label inside the row (checked from the text, not only the baseline audit) — the mechanical sweeps have been tried on every site (`t8_passthru`, `t10_epilogue`, the mid-row lanes) |
| L2 | no `M2C_FIELD`: typed access through a (possibly partial, `unk_`-padded) struct |
| L3 | locals named, one-line summary comment, control flow simplified where match allows; **every remaining pin, marker and tail-call spelling was attempted for removal** by the lane that refined the row (journalled counts before/after) |
| L4 | in a module with a shared header; struct declared once; globals typed |
| L5 | **strict, nothing left**: no `ASM_*` pin or marker, no noreturn tail-call spelling, no fidelity site of any audit class (blocking or byte-derived), no computed-goto table, no inline asm, no `NON_MATCHING` guard. A row that cannot get there stays at L4 with each residue documented with the measured reason (`ledger/levels.jsonl` `l5_residue` names it) |

A row can sit at L3 with pins. Honest scaffolding with a comment is readable; silent
scaffolding is not.

**Scaffolding debt is one class (measured 2026-09-08, `docs/FIDELITY.md`, `work/exp_psyq/`):**
the gcc-facing pins, the maspsx markers (`ASM_TAILSLOT_PIN`, `ASM_PAGEBASE_PIN`,
`ASM_JALDELAY_PIN`) and the noreturn tail-call spelling (`extern void tail(void)
__attribute__((noreturn)); tail();`, which maspsx turns into retail's `j`) all compensate for a
source shape we have not found: the shipped SN compiler reproduces the decompals rebuild byte
for byte, and the shipped ASPSX fills no delay slot and converts no `jal`. So the rule for all
three is the same — find the shape, prove it through the window gate, delete the scaffolding —
and the attempts are scheduled at three points: the L1 sweeps (mechanical rules with a measured
yield), every L3 lane (the refining agent must try, and its journal records pins/markers/sites
before and after), and a dedicated L5 shape-search pass on what is left. The end state also
retires maspsx's tail-`jal`→`j` and frame-elision passes, which have no producer in the shipped
toolchain.

---

## 4. Layers and sequencing

Cost estimates use the measured 0.4–0.8 s/row compile and 6 niced workers (24 cores, load ~4,
Codex lanes running).

### Layer 0 — census and baseline (machine, ~2 h wall)

- `tools/census.py`: for every row at the pin, record container, config, size, offset, pins
  by kind, `M2C_FIELD` count, boilerplate, gotos, computed-goto, m2c-named locals, local structs,
  call targets, data targets, audit classes from `decomp_audit.py`. This is the denominator and
  the cleanliness score.
- `tools/verify.py`: compile a row at its stock cell (upstream `toolchain/`, read-only; fresh
  name-blind maspsx copy via upstream's `neutralise.py`) and compare the object to the cached
  pinned object; retail-slice mode via `aligned_score.py` / `match.py` for milestones.
- Rows whose config is a bridge cell or a `platform-asm` row are **excluded** until they close
  upstream (90 rows today, falling).
- Output: `STATUS.md` with bytes per level. Everything starts at L0.

### Layer 1 — mechanical transforms, corpus-wide (machine, a few hours per pass)

Each transform is a plugin in `tools/xform/` with a precondition, a rewrite, and a refusal list;
`tools/sweep.py` applies one transform to every eligible row, verifies, journals, refuses on
mismatch. Never a hand edit.

- **T1 boilerplate → `#include "common.h"`** (+ `m2c_compat.h`). Probed 35/36; expect ~100 %.
- **T2 dead-pin erasure**, greedy per site then pairwise on the survivors. Probed 34 % of sites.
- **T3 fidelity classes**: `LABEL_AS_CALL` → `goto`/`return` (upstream proved 71 % of the class
  rewrites byte-exact), `PASSTHRU_NO_ARGS` → filled args. This *is* the unbuilt upstream sweep
  engine; build it once here, land it there.
- **T4 `M2C_FIELD` → local typed struct**: derive a per-function `S_<addr>` struct from the
  function's own access census (offset, width, signedness), `unk_XX` padding, exactly the
  upstream STYLE convention. GCC 2.x has no strict aliasing, so this should hold widely; every
  row verified, refusals journalled.
- **T5 normalise types and spelling** (`s32`/`u8` stay, as upstream STYLE says; consistent
  formatting; extern prototypes deduplicated).

Expected: most of the corpus reaches L1, a large share reaches L2, by machine alone.

### Layer 2 — locals, comments, control flow (cheap agents in a verified loop)

Bounded task per row: rename locals meaningfully, add a one-line summary, simplify control
flow only where it stays exact. The verify command is in the loop; a candidate that is not
object-identical is refused automatically. Zero codegen risk from renames, so the cheap tier
fits. This is where the **Astra evaluation** happens (§5).

### Layer 3 — structs, headers, modules (census by machine, judgement by Fable + sol)

- Access census across *all* users of a base pointer (globals `D_xxx`, arguments traced through
  callers) → candidate layouts; merge the ~600 local `S_` structs where they agree.
- Headers per subsystem; modules from the assertion catalogue where it exists (`main.c`,
  `lshop.c`, `player.c`, … for TOWN/MAIN) and from call-graph clusters and address ranges
  elsewhere. A module `.c` is generated from its rows in retail order; the per-row ledger keeps
  the row identity.
- Every user re-verified after each header change; the header hash goes into the ledger.

### Layer 4 — the hard residue (Fable, sol@max)

Heavily pinned and computed-goto functions (617 dungeon files with >10 pins, ~185 jump-table
TUs). Real rewrite work: `switch` instead of `goto *table[]`, struct types instead of register
games. Some will keep pins; they get a documented reason. Hand results go under `refine/` and
survive snapshot refreshes.

Sequence: L0 → L1 (this week, machine) → Astra/luna/sol evaluation on L2 (30-row bake-off) →
L2 at scale with the winner → L3 headers/modules alongside → L4 continuously on the residue.
Upstream hand-back of L1 at the first bridge-wave hold point.

---

## 5. Agent policy and the Astra evaluation

- Machines do every corpus-wide edit and every verification. Agents never verify by hand.
- Cheap tier (luna, gemini) only on tasks with zero codegen risk (Layer 2 renames/comments).
- sol@high/xhigh for T4 refusals and struct census judgement; Fable for headers/modules
  design and the Layer 4 residue.
- **Astra bake-off (Layer 2):** 30 random L1 rows, three arms (gpt-6-astra high, gpt-5.6-sol
  high, gpt-5.6-luna xhigh), identical prompt: "make this readable; byte-exact is checked by
  `tools/verify.py`; output the file". Measure exact rate on first attempt, readability delta
  (blind rubric), wall time and tokens. Pick per-row routing from the numbers. If Astra wins on
  tokens-per-accepted-row it runs Layer 2 at scale; if not, it does not.

---

## 6. What is reused, what is scrapped

Reused from upstream (read-only): toolchain, `aligned_score.py`, `match.py`, `cc.sh` recipes,
`decomp_audit.py`, `neutralise.py`, `names.tsv`/`ccproc.py` alias mechanism, `STYLE.md`,
`NAMING.md`, assertion catalogue, local `S_` structs.

Reused from the earlier attempt (imported, re-verified, credited): the 62 hand-cleaned bodies as
`refine/` candidates, its three headers as header seeds, its maspsx policy note as policy.

Scrapped: the per-function gate, behaviour oracles, kits, role-play reviews, receipts per
physical id, the immutable snapshot copy. The earlier tree stays as an archive.

---

## 7. Risks and guards

| risk | guard |
|---|---|
| upstream tree is mid-campaign (dirty, lanes landing) | derive from a *commit*, compile in scratch, never write upstream; land upstream only at hold points through their gate |
| a transform holds at object level but the window differs | milestone retail check via the real scorer/gates before any hand-back |
| name-blind maspsx copy stale vs live dials (bit the probe today) | regenerate the copy from live maspsx at every pin bump; ledger records its hash |
| struct guesses that "match" but are wrong | partial structs with `unk_` only; a field gets a name only with evidence; ledger keeps the census |
| agent output drift (rewrites that change meaning while matching) | Layer 2 tasks are rename/comment/control-flow only; object equality is the gate; diffs sampled by Fable |
| IO discipline on the shared disk | no recursive searches over `work/`; census reads only the six source roots; journals are small jsonl |

---

## 8. Decisions taken

1. A new derived tree (this repository); the earlier attempt frozen as an archive.
2. Transform-and-verify replaces re-derive-and-admit. Object equality is the per-edit gate.
3. The snapshot is a pin plus a replay, refreshed on command.
4. Upstream hand-back of machine layers at bridge-wave hold points, window-batched.
5. Agents are evaluated as Layer-2 workers in a bake-off, never as campaign owners.

---

## 9. Pin classes and their cleaner alternatives (census 2026-09-07, 218 rows / 2,280 sites)

Measured by erasing each pin alone from the original text and scoring against retail
(`docs/PIN_CENSUS.md`, `tools/pin_census.py`). 44 % of pin sites are dead on their own; only
4 % of pinned rows are pin-free after single-site erasure, so most pinned functions keep at
least one load-bearing pin. What the load-bearing ones protect, and the mechanical alternative
each class gets, in order of share:

| breakage when erased | share | the pin protects | mechanical alternative (plugin) | status |
|---|---:|---|---|---|
| reorder-only | 19 % | instruction order (scheduler) | source statement reorder search around the site, bounded k≤3; keep only if exact | to build (T5a) |
| broad | 15 % | the whole shape | none: document the pin (`/* MATCH: ... */`) and route to agent tier | documented |
| reg-rename | 12 % | register colouring | local-declaration order permutation, bounded; merge two temps into one | to build (T5b) |
| code-motion | 7 % | a statement's position across a call/branch | re-place the statement; a data dependency through a local | T5a |
| length-drift | 7 % | a copy the compiler would drop or add | reuse the variable instead of a temp (agent tier) | agent |
| addressing | 6 % | %hi/%lo vs gp / base+offset form | extern declaration shape flip (scalar ↔ array), deterministic | to build (T5c) |
| block-order | 5 % | basic-block layout | if/else arm swap, goto polarity | agent |
| const-remat | 5 % | a constant kept in a register | named local holding the constant, used at both sites | T5d |
| delay-slot / slot-rotation | 9 % | what fills a delay slot | TAILSLOT/PAGEBASE family: assembler-shaped, never dead in the sample; keep documented | documented |
| hold-set | 4 % | callee-saved set / frame | scope a temp to shrink its live range; else documented | agent |
| li-expansion | 2 % | lui/addiu split of an immediate | write the constant in the split form | T5d |

Reading the table: roughly 40 % of the surviving pins (reorder-only, reg-rename, addressing,
const-remat, li-expansion, code-motion) have a bounded mechanical alternative worth building
as verified search plugins; the rest are honest matching scaffolding and get a one-line
documented reason rather than hand work. Context matters: `ASM_KEEP` immediately before a
`return` is dead 70 % of the time; `ASM_TAILSLOT_PIN` before a call is never dead.
