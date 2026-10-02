# func_80095160: rubber-duck pass on the remaining four pins

2026-10-02. Continues the r88 four-pin source, at the unchanged
`2.7.2-cdk-G0` recipe. **One more pin removed: 4 -> 3.**

The body is `func_8009A8C0`, 736 retail bytes. Lane:
`work/native_lane/r89_sol_80095160`. `DUCK.md` records the hypotheses before
source experiments; `scratch/*_diagnostic.txt` contains the pass decisions.
The full retail site map remains in the r88 lane's `REPORT.md`.

## What does the `$3` pin support?

`coord_or_height` is a shared scratch variable: actor coordinates, bounds
checks, shifted X, and finally the sampled height. The pin also forces the
otherwise anonymous *final comparison temporaries* to stay out of `$v0`.

Erasing the pin alone gives byte total **20**. The visible changes include
the first call's shifted return moving to `$a0`, the final signed comparison
using `$v0`, an extra result copy, and a changed delay-slot fill. These are
not four independent source defects.

`alloc_need.py` identifies local quantity **214+215**, block 19, occupying
`$v0` over indices 8..12 inside the global result's 4..14 lifetime. Local
allocation runs first. The global result therefore cannot take `$v0` and
goes to `$a0`. The local quantity takes the lowest available register; no
priority adjustment or small lifetime shift of that quantity explains
retail. This matches the known **local value that should belong to a shared
global allocno** residue in `tools/lanes/brief_paragraphs/shared_global.md`.

The C to inspect is the final expression, not the declaration:

```c
coord_or_height = actor_or_height.height << 0x10;
if ((coord_or_height >> 0x10) < 0x201) {
    result = 1;
}
```

The first targeted candidate removes the pin and writes the conversion and
test back into that scratch variable:

```c
coord_or_height = actor_or_height.height << 0x10;
coord_or_height >>= 0x10;
coord_or_height = coord_or_height < 0x201;
if (coord_or_height) {
    result = 1;
}
```

**Exact on the first attempt.** Both new assignments have actual consumers;
there is no dummy use, initializer, barrier, or new pin. The scratch's final
role is now the boolean decision as well as its signed input. Its existing
earlier roles keep it global; the independent local quantity disappears.

In the `.greg` comparison, scratch pseudo 97 changes from 14 references /
36 live instructions (priority 11666) to 18 / 38 (18947), still allocated
to `$v1`. Result pseudo 96 remains 5 / 9 (11111), but changes from `$a0`
back to `$v0` because the local conflict is gone. Thus this is primarily a
local/global allocation repair, not merely a priority flip. The register
names printed by the tools are shifted by the local union declaration;
these variable identities were checked against the RTL and source.

## What does the `$20` center pin support?

It preserves the copy from `offset_work` to `center_y`. Without it, CSE
folds the copy and extends the reused scratch through a call. The saved
register assignment changes and the body pointer stops spilling. Lone
erasure from the new three-pin source gives byte total **66**.

The relevant source is:

```c
offset_work += 0x20;
center_y = offset_work;
/* first call */
coord_work = *pb + center_y;
```

Known classes: copy canonicalization, disjoint source roles, saved-register
priority, and resulting reload changes. A fresh `center_y = offset_work +
0x20` plus the `$3` fix removes the scratch-copy problem: the residue becomes
**12 substitutions, 0 indels**, a three-register rotation among center,
direction, and height. It is `cand/two_center_fresh.c`, not landed.

The measured center is 2 refs / 18 live, priority 1111. Direction is 4 / 49,
1632; height is 4 / 67, 1194. Center must outrank both without taking an
earlier spatial register. The tool's lower bounds are 3 refs at the current
length, or length <=12 at two refs. Reusing a real later monster/status/test
or height-argument role raises its priority too far or introduces surviving
copies. Copy/add spellings reintroduce coalescing. Narrow centers add
extensions and can turn the add into `ori`. These failed experiments do not
justify a dummy reference; no suitable additional real use was recovered.

**r90 correction:** center-Y's priority is only half the constraint. Raising
it alone takes the X center's s0. The exact allocation replay requires X
center before Y center, both ahead of direction; see
`docs/evidence/r90_80095160_coupled_centers.md`. The reference-count and
lifetime bounds above are necessary, not a sufficient standalone fix.

## What does the `$5` tile pin support?

Two early X-coordinate argument shifts. With the pin erased, the values and
registers remain right but three instructions move: byte total **4**
(2 substitutions, 2 indels). `checks.py` separates the sites:

1. The first call's `srl a1,v1,6` is **REORDERABLE**: combine folds it into
   the late argument setup, and sched2's LUID tie puts it after the Y shifts.
   Inspect the first shifted-X producer, the Y shift, and call argument
   setup together.
2. At the later placement call, X becomes a single-set pseudo and gets
   sched1's birthing boost; reused Y does not. Their order is
   **NOT-REORDERABLE by statement order alone**. This is the known
   `early_arg.md` / `pin_removal_possibilities.md` single-set boost residue.

Swapping X/Y carriers fixes part of the order but changes preferences and
leaves argument copies. Reassigning the original X source preserves the
early calculation but lengthens the scratch into a saved register. Fresh
`u16` placement coordinates reduce the score to **3** (1 substitution,
2 indels), but leave an extra `andi` at the call and the first-call ordering
tie (`cand/tile_narrow_u16.c`). The signed version leaves sign extensions.

The actual definitions were checked: `func_80094DE0.c` declares A540's X/Y
as s16; `func_80095AFC.c` declares B25C's coordinates as s16 and returns a
pointer. Matching the first callee's narrow coordinate prototype here adds
instructions (byte total 12), so it is not a pin-removal landing.

## What does the failure barrier support?

It preserves a distinct failure-return block and thereby the delay slot
following the placement-result branch. Lone erasure from the new source
gives byte total **15**. The 38-line listing distance includes label
renumbering; it is not a 38-word byte discrepancy.

`dbr.py --retail` names the decision: EQ is predicted not taken;
`fill_eager_delay_slots` tries the owned fall-through first and steals
`li v0,-1` from its jump's slot. Retail instead has the target thread's
`sll v1,s2,16`. This is the known EQ/fall-through residue in `dslot.md`.

Inspect `move_failed`, `check_height`, and their incoming edges. Direct
bounds returns, an explicit failure edge, shared-result returns, and three
final if/else spellings all canonicalize to the same unwanted layout.
Neither a fake one-trip loop nor another barrier was introduced. The open
question is source control flow that retains the needed thread ownership
through jump optimization; this pass did not establish a compiler wall.

## Validation and scope

- Four-pin control and three-pin candidate: exact at the established recipe.
- All seven nonempty erasure subsets of the remaining three pins miss.
- Old and new `NON_MATCHING` variants compile; assembly differs. No unscored
  conditional arms were edited.
- 32 measured source variants in `REPORT_TABLE.md`, including the repeated
  exact candidate. The next pass must start from the landed three-pin text.
- Independent `apply_candidates.py` verification: `applied match 0`;
  `t2_pins`: noop.
- Full 393,216-byte dungeon-engine window MATCH; 2,174 other windows current.
- SLUS SHA-1 MATCH (860 TUs, unchanged pinned recipe). Full logs are in
  the lane's `landing.log`.

The lineage fingerprint remains inconclusive for this row; it was rerun
after stalled families. No compiler/flag sweep was used. The surviving
pins are open C-shape questions with named pass decisions, not impossibility
claims.
