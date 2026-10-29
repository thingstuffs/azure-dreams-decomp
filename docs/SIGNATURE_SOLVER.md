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
| `sig_txn.py` | One owning-header transaction: prototypes into H (append block or in-place respelling), every other declaration removed, `#include "H"` added where needed (or a canonical local respelling when the TU cannot include H), definition narrowing for `W`, floor markers; proof with `tools/build/affected.py prove` over the edited files (production recipes whose closure contains an edited file, placement copies, image relinks); greedy back-off by the names whose edits reach a non-PASS recipe. |

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
   and the rest); inside a batch take 5-10 headers whose names do not overlap.  Never run two batches that
   share an owning header or a consumer folder another lane holds.
2. Solve the batch once (one census for all its headers; read-only for tracked files):
   `python3 tools/typing/sig_solver.py solve --header H1 H2 ... --out runs/<batch> --abi-cache runs/abi.json.gz --workers 8`
   Output per header: `runs/<batch>/<slug>/decisions.json`, `floors.jsonl`, `solve.log`.
3. For each header of the batch, in order, on a clean committed tree:
   `python3 tools/typing/sig_txn.py --decisions runs/<batch>/<slug>/decisions.json --out runs/<batch>/<slug>/txn --natcheck <port>/tools/natcheck.py --max-rounds 10`
   - exit 0 and `result: PASS` in txn.log: commit src/ include/ ledger/ (`git add -A src include ledger`),
     then `python3 tools/typing/sig_solver.py floors --decisions .../decisions.json --txn .../txn/txn.json`
     and commit `ledger/prototype_floors.jsonl`;
   - then `nice -n 10 make -j8` before the next header (the proof's baseline is build/obj at HEAD);
   - natcheck exit 3 (a stale port `source-owners` pin) is accepted; exit 1 is not (the writer backs off).
4. After the batch: full `make -j8`, natcheck, `git diff <batch base>` as the batch patch (work/ excluded).
5. Re-run a batch later only for names the transaction backed off (`backoffs` in txn.json with why
   `proof`/`natcheck`); recorded floors are skipped automatically.

Timing seen: item.h (25 names, 851 sites) solve ~7 min, transaction 3 proof rounds ~20 min, make ~45 min;
small feature headers solve < 1 min, transaction ~2 min.

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
