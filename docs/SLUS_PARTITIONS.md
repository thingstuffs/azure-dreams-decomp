# SLUS function partitions: foundation and private build proof

Status: **planner/renderer and plural compilation available; production activation pending**.
The existing whole-row module model remains active. There is no production
`config/slus_partitions.json`. Production configure, full-image candidate gating,
genuine comparison and placement certification still use the existing model;
the new plural compilation API is available independently.
Do not activate a partition solely from the private build proof below.

## Purpose and identity

The [E0 list-cursor pilot](evidence/gp_e0_partition.md) needs one function from
`slus/code`, one from `slus/code2`, and the whole `slus/w_80041134` row. The new
`tools/build/slus_partitions.py` records each collector's immutable raw hash,
original recipe, complete canonical definition set, and disjoint subsets sent
to named modules. It retains both original row IDs and canonical editable C
files. Generated source views hold each collector remainder and its moved
function bodies. A remainder retains declarations for the moved functions.

The actual frozen and current definitions are 156 for `code` and 24 for `code2`;
these sets equal their emitted ELF function sets. The registry's 221/32 `defs`
counts also include prototypes and must not be used as physical function counts.
The [example plan](evidence/slus_partitions/example_plan.json) preserves all 180
collector functions. The E0 destination has its ordinary one-function member
41134 plus two explicit incoming function parts. No function is falsely assigned
to 41134's original logical identity, and its frozen whole-member check is kept.

## Contracts

- `load_plan` validates identities, canonical functions, unique ownership and a
  nonempty remainder. Retiring a fully distributed collector requires a separate
  explicit migration; it is not silently allowed here.
- `validate_context` checks the frozen raw hash and exact definition set, original
  recipe, known destinations, and conflicts with whole module membership or
  aggregator sources. A graph edge alone is not a historical TU assertion.
- `render_parent` accepts ordinary top-level C definitions, respecting comments,
  strings and braces. Conditional definitions, directives inside selected bodies,
  macro-defined functions and nested C includes fail closed when coverage cannot
  be established. This is a conservative source-view tool, not a general C parser.
- `expected_units` and `check_emitted` require exact physical function sets and
  reject missing or duplicate ownership. Build consumers must run the emitted
  check; source extraction by itself is not the emitted-code proof.
- `connected_context`, `row_units` and `fingerprint` describe every connected
  parent/owner and the separate physical recipes/function scopes. Fingerprints
  require all declared source/header inputs and include the alias map and tool
  code. Build consumers must supply the complete connected closure.
- `output_paths`, `render_files` and `project_edges` retain original logical
  source/object identities while using explicit generated compiler inputs.
  Projection rejects bypassed/missing remainders and recipe or object drift.
  The original logical recipe is provenance; it does **not** claim every moved
  function still uses that recipe. Per-owner recipes must remain in proofs.

The renderer writes only beneath the build directory, refuses escaping output
symlinks, and preserves unchanged output mtimes. Its CLI is:

```sh
python3 tools/slus_partitions.py render --plan config/slus_partitions.json \
  --output-dir build/partition_sources --names config/names.tsv
```

That command is shown relative to an exported build root. The optional plan
loader accepts an absent plan; the explicitly requested render command does not.

## Measured private build

The [normal-Ninja receipt](evidence/slus_partitions/build_receipt.json) and
[configure candidate diff](evidence/slus_partitions/configure.diff) prove the
build mechanics in isolation. A multi-output render edge takes the original C
files as inputs, and its `restat = 1` rule avoids rebuilding unchanged views.
The generated remainder files compile at the original collector recipes, while
the E0 module uses 2.8.1. No hand patch to the final Ninja file is needed.

The private build retains all 19 active modules, adds the E0 owner, and has
873 physical inputs projecting to the exact existing 884-row ledger. All **181
functions** in the two remainders plus destination occur exactly once. All **44
E0 words** match fresh stock, actual linked and genuine ASPSX 2.79 objects with
zero masks; this does not claim genuine equality for all collector functions.
The whole 524288-byte image matches retail SHA-256
`ae19d8d4bdd2db9a933b1e44d70dd61be670781e441d7cb37da85250a7aed31f`.
Primary review confirms actual four-byte `.sdata` ownership and non-absolute
linkage at `800814E0`, with the old absolute assignment removed, while canonical
collector files remain unchanged.

Normal source edits test both paths. Changing 41110 in canonical `code.c`
rebuilds only its destination object; changing an unmoved function rebuilds only
`code.o`. Both images fail retail equality. Restoring each source rebuilds only
the corresponding object and returns the exact retail image. `code2.o` remains
untouched in both cases. Thirteen [unit tests](../tools/tests/test_slus_partitions.py)
cover the schema, frozen provenance, missing/duplicate functions, unsupported
source forms, transitive owner closure, per-owner recipes, fingerprint freshness,
projection and filesystem output boundaries. See the
[primary review](evidence/slus_partitions/primary_review.json).

Reproduce with `python3 work/native_lane/slus_partition_build/probe.py` for the
isolated normal build and `python3 -m unittest discover -s tools/tests -p
test_slus_partitions.py -v` for the library. The private configure candidate is
saved for review; the production configure file is unchanged.

## Plural candidate compilation

`slus_module_context.compilation_sources` now returns each physical source view,
its own compiler recipe, the original row's function subset, and the complete
expected function set of that object. A collector edit renders all connected
source views privately; a whole member keeps incoming collector functions in its
actual owner context. Canonical sources and original row IDs are preserved.
Connected fingerprints include all participating parents, aggregators, whole
members, declared headers, aliases, recipes, and both rendering/adapter tools.
Existing unpartitioned module fingerprints retain their previous contract.

`verify.compile_slus_units` compiles each stream and requires exact ELF function
coverage, with no missing, additional or duplicated ownership. It refuses stale
inputs and partial compile failures. This is an input/coverage API, not a linked
retail or genuine-ASPSX verdict. `verify_slus` and other singular consumers refuse
partition-connected live inputs until their complete plural gates are integrated.
Historical frozen-raw compilation remains independent.

The [compile receipt](evidence/slus_partitions/plural_receipt.json) checks all
three E0 logical inputs through this API. Both remainder objects (155 and 23
functions) and the three-function destination have identical allocated sections,
relocations and symbols to the already retail-linked private build objects.
The [negative receipt](evidence/slus_partitions/plural_negative_receipt.json)
changes a moved body and a remainder body: only the expected object changes.
A macro-generated extra function, invisible to the conservative source scanner,
is rejected by the compiled coverage check. This illustrates why source parsing
alone is not a coverage proof. Likewise, edge projection must still be followed
by exact whole-ledger equality. Malformed paths and ambiguous or invalid alias
targets fail closed.

Six context tests cover multiple destinations, incoming sibling parents, distinct
recipes, host-compiled candidate behavior, fingerprints, legacy refusals and raw
exceptions. Five compiler-boundary tests check per-owner recipes, complete emission,
header selection, source/fingerprint drift and failure without partial success.
All 85 SLUS tests pass; `row_db.py check` passes. The existing runtime-directory
pilot has been recertified against
the changed verifier: full production image MATCH and genuine ASPSX 2.79 exact
with zero masks. See [review hashes](evidence/slus_partitions/plural_review.json).
Reproduce the actual MIPS routing/coverage probe with
`python3 work/native_lane/slus_plural_context/negative_probe.py`.

## Remaining integration, in order

1. **Implemented:** plural physical contexts, connected fingerprints and candidate
   compilation with exact emitted-function coverage. Legacy singular entry points
   refuse partition-connected live rows; frozen raw remains standalone.
2. Wire optional build generation and logical projection, then teach `SlusView`
   to substitute a canonical candidate, render all affected views, run one full
   image gate, and restore every input/object. Require emitted-set coverage.
3. Aggregate genuine-ASPSX records across per-owner streams with exact disjoint
   function scopes and per-owner recipes/pass traces. Keep a single original
   logical row record; retain unrelated GP/model dependencies in collectors.
4. Extend ownership/certificate evidence with incoming function parts and fresh
   connected fingerprints. A subset proof must not grant placement to a whole
   collector. Preserve existing L4/L5 pin and fidelity requirements.
5. After negative/regression gates pass, activate E0 with the reviewed source
   and data binding, rerun the full retail/genuine gates and runtime pilot, and
   remove only dependencies proved eliminated. Then use the same mechanism for
   the remaining actual function groups.

The [consumer inventory](evidence/slus_partitions/consumers.md) identifies exact
callsites. Production remains **197 dependencies, 29 GP rows, 19 ownership
units, 873 physical / 884 logical rows**. The separate generic assembler
correction and pass retirement are still pending; this layer changes neither.
