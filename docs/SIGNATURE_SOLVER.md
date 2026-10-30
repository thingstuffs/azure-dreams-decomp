# Signature-consensus solver

One canonical prototype per function, written into its owning feature header and decided by object
bytes, so that local externs, empty `f()` declarations and the casts they force can be removed in one
proven transaction per header.  Owner rulings of 2026-10-29 apply:

* **(a) Width rule.**  Prefer the narrow type.  When call sites need different return widths, publish an
  ABI-wide `s32`/`u32` prototype and keep the narrowing in the definition body (`return (s16)index;`).
* **(b) Floors.**  When no single legal prototype exists the site keeps its local declaration, marked
  `/* Unprototyped: <reason> */`, and the name is recorded once in `ledger/prototype_floors.jsonl`.  `tools/proto/prototypes.py` holds every recorded
  floor (`prototype_floor:<class>`) and the solver skips recorded names unless `--retry-floors`.

## Tools (tools/typing/)

| Tool | Role |
|---|---|
| `abi_facts.py` | Capstone pass over every built object: callee arity (a0-a3 and stack arguments read before write, GTE `mtc2`/`ctc2`/`lwc2` included), return kind and width (v0 reaching definitions at `jr ra`), call sites (`R_MIPS_26`) with argument narrowness, registers set in the call's block, outgoing stack stores and v0 use (none / returned / test / store8-32 / ext_s8-u16 / raw). Names via `config/names.tsv`; per-unit linker assignments via `link_bindings`. Importable; `scan()` caches by object mtime (~45 s for 10.8k objects at 8 workers). Shared ground with the code map's `retail_fn` table. |
| `sig_census.py` | Declaration census on the header planner (`tools/headers/plan.py`): definitions, every file-scope declaration with a canonical signature key, users (bodies and initialisers), header references, owning header. |
| `sig_probe.py` | Neutral-set prober. Each variant is the TU with every `#include` wrapped in `#define NAME __sigprobe_NAME` / `#undef NAME` (header declarations renamed away), the TU's own declarations removed and the candidate inserted before the first item that mentions the name.  Compiled at the production recipe through the root's `mkbuild.compile_uncached` from a sibling file `.sigprobe_<pid>_<file>.c`, compared with `abi_facts.object_difference` (sections, relocations, global symbols; STT_FILE ignored). The control (today's spelling) must equal the production object. Native (genuine ASPSX) module recipes are probed through the maspsx pipeline at the same compiler args (identical gcc output is identical under either assembler). At most 8 workers, nice 10. |
| `sig_consensus.py` | Pure decision: `D` (the definition's prototype) when neutral at every site, else `W` (width rule), else a refusal with partitions and a floor class (`phantom_arguments`, `varying_arity`, `param_width`, `return_width`, `unprobeable`, `name_hold`). |
| `sig_solver.py` | Driver: `solve --header H --out DIR` (census, ABI facts, probes, consensus -> `decisions.json`, `floors.jsonl`); `floors --decisions ... --txn ...` (ledger upsert). |
| `sig_txn.py` | One owning-header transaction: prototypes into H (append block or in-place respelling), every other declaration removed, `#include "H"` added where needed (or a canonical local respelling when the TU cannot include H), definition narrowing for `W`, floor markers, visibility repairs; proof with `tools/build/affected.py prove` over the edited files (production recipes whose closure contains an edited file, placement copies, image relinks); greedy back-off by the names whose edits reach a non-PASS recipe.  `Transaction.plan_edits` returns the edit plan in baseline offsets and `render()` merges the plans of several headers. |
| `sig_batch.py` | Batch mode (the default run-book step): every header of one `solve` run planned over the same baseline and rendered together, ONE build-graph proof over the union of edited files, ONE natcheck; failures resolved by attribution plus bisection instead of per-header re-proofs (see below). |

## Running a batch (default)

```sh
python3 tools/typing/sig_solver.py solve --header H1 H2 ... --out runs/<batch> --abi-cache runs/abi.json.gz --workers 8
python3 tools/typing/sig_batch.py --batch runs/<batch> --out runs/<batch>/txn --scope <lane prefixes...> \
    --natcheck <port>/tools/natcheck.py --record-floors --workers 8
git add -A src include ledger && git commit ...
nice -n 10 make -j8          # once per batch: the image proof of the SLUS partitions and the lane's final check
```

`sig_batch.py` plans every header's transaction (`Transaction.plan_edits`) over the committed baseline and
renders them together (`render()`): spans of every header applied in one pass, a consumer TU that several
headers edit gets all their includes and removals, an owner header that another header's names are removed
from also gets its own appended block.  Batch-level checks before any compile:

* names held by one header are re-planned out before the others' include checks (the include-conflict
  check treats every batch name as unified, so a held name must not count);
* a TU that keeps a floor declaration of one header's name never gains a header whose closure reaches
  that owner;
* overlapping spans from two headers in one file hold the later header's names (`batch_overlap`);
* `--scope PREFIX...`: an edit to a header outside the prefixes, other than the batch's own owner headers,
  holds the names that make it (`out_of_scope_header`; what the town lane reverted by hand).

Proof and back-off (`Runner.settle`):

1. One `affected.prove` (in process, one build graph) over the union of edited `.c`/`.h` files.
2. On a failure, the compiler's own words first: `conflicting types for` / `previous declaration of` /
   `too many|few arguments to function` naming a batch name back that name off without bisection; the
   identifiers on the reported error lines (`<file>:<line>:`) that are batch names are the attributed
   culprits; otherwise the names whose edits reach the failing recipe (its own source, else its edited
   dependencies narrowed to the names the TU mentions).  SLUS recipes are mapped through the
   `build_slus/` views to the tree file.
3. A conflict located in a type header that an owner header newly includes (the self-contained includes)
   refuses that include at the owner header; one brought by a TU's new owner include stops that TU
   including the owner (it keeps a respelled declaration); a failing recipe that compiles a repaired path
   withdraws that visibility repair.  These change the plan, not the name set, and re-prove.
4. Bisection: the unattributed names are proved first (usually PASS), then the attributed ones by halves
   (by owning header first, then by name).  A single attributed name, or a single name failing on top of a
   proven set, is backed off (`why: proof`).  Failing sets are memoised, so no set is proved twice.
5. Every accepted state is one whole-set PASS of exactly the files written (half-proofs are attribution
   only); the files on disk at exit are that state.  Recipes whose edited inputs are byte-identical to an
   earlier byte-identical compile in the same run are reused (`affected.prove(reuse=, reuse_key=)`: key =
   recipe id + every edited file reaching it, newly included headers followed, plus the layout ledger for
   placement copies), so re-proofs after a back-off cost seconds.
6. Natcheck once on the final state; unit failures back off the names they mention and the survivors are
   re-proved (bounded).  `--max-proofs` (40) caps the proof count; on exhaustion the largest proven set is
   kept and the rest is backed off as `proof_budget`.

Outputs: `<out>/batch.json` (per-header yields, every proof with its failing recipes, back-offs by reason,
repairs, timings, debt deltas), `<out>/batch.patch`, `<out>/batch.log`, and per header
`<out>/<slug>/txn/txn.json` + `txn.patch` in the sig_txn receipt form, so `sig_solver.py floors --txn` and the
reviewer checks below are unchanged (`--record-floors` runs `floors` for every header after a PASS).
The acceptance rules are the per-header ones: byte-identical over the build graph, the debt ratchet per
file (no class may rise in a `.c`; headers may gain prototypes; no `S_<addr>` published in a feature
header), no call-site casts beyond the width rule, floors recorded.

## Visibility repairs

Tried inside the transaction (default on; `--no-repair` turns them off); the proof decides each one, and a
refused repair falls back to the old hold:

* `include_common_h` (was `cannot_include_owner:...:tu_without_common_h`): a TU that spells its own base
  typedefs (`typedef unsigned char u8;` ...) instead of including `common.h` gets `#include "common.h"` in
  place of the first of them, the local typedefs that `common.h` defines identically are removed (a local
  typedef of a common.h name with another type keeps the hold), and then the owner include.  gcc 2.7
  rejects a repeated typedef, so the removal is required, not cosmetic.
* `include_type_header` (was `respell_type_not_visible:X`): when a TU cannot include the owner and its kept
  declaration at X is respelled to a prototype naming a typedef X cannot see, X includes that type's single
  defining header (a shared/records type header when X is a header).
* `drop_unneeded_owner_include` (part of `floor_site_sees_owner_header`): a floor TU that includes the owner
  directly, reaches it through nothing else, and uses no name, type, tag, enum constant or macro the owner
  brings besides its floored names, stops including it.  The hold reason now says `direct` or `transitive`;
  direct ones are usually genuine conflicts (pointer-kind or arity floors in TUs that need the owner) and stay.
* Struct tags are not typedef uses: `struct X` in a prototype or an owner header no longer requires X's
  typedef header (this held names as `respell_type_not_visible` and made owner headers gain needless type
  includes that conflicted with consumers).

Not repaired here (type moves, listed for a typing task): `generated_layout_in_prototype` (an `S_<addr>`
parameter needs a named type in its owning header first) and the includes they block (e.g. 27 `slus.h`
names wait on `init_object_header_b(struct S_8004EFF4 *)` because `src/slus/code.c` cannot include `slus.h`
until that declaration agrees).

## Running one header

```sh
python3 tools/typing/sig_solver.py solve --header include/dungeon/item.h --out <dir> --workers 8
python3 tools/typing/sig_txn.py --decisions <dir>/decisions.json --out <dir>/txn --affected <affected.py>
python3 tools/typing/refresh_layout_inline.py --root . --base HEAD
python3 tools/typing/sig_solver.py floors --decisions <dir>/decisions.json --txn <dir>/txn/txn.json
```

`sig_txn.py` refuses to start with uncommitted src/ or include/ changes (the proof reads the baseline text
with `git show HEAD:path`), and the root's `build/obj` must be current for HEAD (run `make` between
transactions).  Then natcheck and a full `make`.

## Probe semantics and limits

* Parameters always take the definition's types (a prototype that disagrees with the definition does not
  compile).  A caller whose bytes need its own narrow parameter spelling (`andi` on an `s16` argument
  for a `u16` declaration) blocks every candidate: `param_width`.  A call-site cast would unblock it; that
  is not done (no new casts beyond the width rule).
* A caller that extends the result itself under a narrow declaration (`sll/sra` after `jal`) blocks `W`:
  `return_width`.
* Partial transactions (ruling (b) per site): when every blocker is a non-definition TU that will not see
  the owning header, the name is unified everywhere else and the blockers keep their declaration with a
  floor marker; `--no-partial` turns this off.
* Block-scope declarations are not modelled (none in the tree when written).  Multi-declarator or
  conditional declaration sites hold the name.

## Transaction details learned in the pilots

* Merged (LL7) TUs: `ledger/layout_inline.jsonl` is refreshed (`refresh_layout_inline.py --base HEAD`) before
  the proof, because placement copies are projected from the member extents.
* An `#include` of the owning header is only added where every declaration the header brings agrees with the
  TU's whole include closure; otherwise the TU keeps the declaration it sees today (its own, or the header
  one) respelled to the canonical prototype.  A compile error naming another declaration stops that TU from
  including H; one naming a name being unified drops that name.
* Pointer/integer disagreements between a site and the definition (bytes agree) are floors, never unified:
  the definition needs a type change first.
* Floor TUs never gain `#include H`; a floor may keep a header declaration only when every TU that sees
  that header is itself a floor site and never sees H.
* Debt ratchet before the proof: no debt class may rise in a .c file; headers may gain prototypes.
  Generated `S_<addr>` layout names are never published in a feature header.
* Natcheck runs after a PASS byte proof; unit failures back off the names they mention.  A port source pin
  (`source-owners`) going stale is expected when a pinned game source changes (exit 3) and is the port's
  refresh, not a failure of the transaction.

## Run-book: full-tree run in header batches

One lane root at the current master, built once (`nice -n 10 make -j8`).  At most 8 workers, nice 10.

1. Plan the batches (one census, ~80 s):
   `python3 tools/typing/sig_solver.py headers --prefix include/dungeon/ > batches_dungeon.tsv`
   (columns: header, conflicting names, declaration sites, slug).  Batch by subsystem prefix
   (`include/dungeon/`, `include/town/`, `include/engine/`, `include/frontend/`, then `include/` for slus.h
   and the rest); a batch can be the whole prefix (one solve, one transaction, one make); split it only
   when its proof scope gets very large.  Never run two batches that share an owning header or a consumer
   folder another lane holds, and pass that lane boundary to sig_batch as `--scope`.
2. Solve the batch once (one census for all its headers; read-only for tracked files):
   `python3 tools/typing/sig_solver.py solve --header H1 H2 ... --out runs/<batch> --abi-cache runs/abi.json.gz --workers 8`
   Output per header: `runs/<batch>/<slug>/decisions.json`, `floors.jsonl`, `solve.log`.
3. Apply the whole batch at once on a clean committed tree (build/obj current for HEAD):
   `python3 tools/typing/sig_batch.py --batch runs/<batch> --out runs/<batch>/txn --scope <the lane's header prefixes> --natcheck <port>/tools/natcheck.py --record-floors`
   - exit 0 and `result: PASS` in batch.log: commit src/ include/ ledger/ (`git add -A src include ledger`;
     the floors ledger is already updated);
   - natcheck exit 3 (a stale port `source-owners` pin) is accepted; unit failures back the names off.
   Batches can be big (a whole subsystem prefix: 20-40 headers): the proof cost grows with the union of
   affected recipes, not with the header count, and back-offs re-prove from reused compiles.
4. After the batch: one full `nice -n 10 make -j8`, `git diff <batch base>` as the batch patch (work/ excluded).
   Tidy-ups the make or a reviewer finds go in a follow-up commit, not a re-run.
5. Re-run later only for names backed off with why `proof`/`natcheck`/`proof_budget` (`backoffs` in
   batch.json); recorded floors are skipped automatically.  Holds (`cannot_include_owner`, ...) are re-tried
   by a later solve once the blocker changes.

Per-header fallback (one header, or to reproduce one header's result): step 3 per header with
`python3 tools/typing/sig_txn.py --decisions runs/<batch>/<slug>/decisions.json --out runs/<batch>/<slug>/txn --natcheck <port>/tools/natcheck.py --max-rounds 10`,
commit, `sig_solver.py floors ...`, commit the ledger, and `make -j8` before the next header (its proof's
baseline is build/obj at HEAD).

Timing seen (per-header flow): item.h (25 names, 851 sites) solve ~7 min, transaction 3 proof rounds
~20 min, make ~45 min; small feature headers solve < 1 min, transaction ~2 min; town lane (39 headers):
~42 s census + 0.5-2 min proof per header plus an ~8-10 min make between headers, ~5 h of builds.
Batch flow, slus pilot (include/slus.h + include/main.h, 48 candidates, 480 recipes incl. 176 SLUS):
one census 90 s, 3 proofs 169 s (the second and third reuse 438 and 478 of ~479 compiles), natcheck 9 s,
4 min 45 s end to end, then one make.

## What a reviewer (Luna/Sonnet) checks

Per header, read `txn/txn.json`, `txn/txn.patch` and `decisions.json`:
- **Floors** (`floor_sites`, refused names in `decisions.json`): does each blocking site's reason match
  its spelling?  `phantom_arguments`: the site declares/passes more arguments than the definition reads
  (callee `abi.arity`); `param_width`: a narrow parameter spelling the caller's bytes need;
  `return_width`: the caller extends the result itself; `pointer_kind`: pointer vs integer view (needs a
  definition retype, a separate task).  A floor whose spelling equals the canonical prototype is a tool
  bug - report it.
- **casts_would_unify**: list names where `sufficient` is true and `sites` is small (1-3): candidates for
  the owner's cast-trade decision.  Do not add casts.
- **Respellings** (`respelled`): canonical duplicates left in non-owner headers or TUs that cannot include
  the owner; acceptable, list them for a later extern wave.
- **Prototype text in the owner header**: no `S_<addr>` names (the writer refuses them), parameter names
  kept from the definition, forward `struct` tags only where needed.
- **Never**: a cast added at a call site, a changed definition body other than the width-rule narrowing,
  an `#include` of one interface header inside another.
