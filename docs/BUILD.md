# Make build and landing proof

Provision the pinned toolchain and extract your own disc using the repository
setup instructions, then run from the checkout root:

```sh
make configure
make -j8
make check
```

GNU Make 4.3+, the existing Python environment, pinned GCC cells, maspsx, MIPS
GNU binutils and Ninja (for the existing SLUS configuration tooling) are needed.
Nothing in the delivery contains game binaries or SDK payloads; `build/` is
ignored by Git.

## What is built

`make configure` creates the existing build views (`build_slus/`, `build_ovl/`)
and `tools/build/mkbuild.py` projects the registered recipes into
`build/build.mk`. SLUS commands come from the existing generated Ninja recipe,
including its partition-coverage and data-piece verification edges, which are
prerequisites of the SLUS link. Overlay recipes use the production source, flag,
evidence and placement selectors. Each full physical recipe compiles once;
registered flag/evidence variants remain distinct. A placement whose home was
inlined into a module TU compiles the gate's member projection of that span; the
projection is re-derived from the owner TU at compile time and fails closed when
`ledger/layout_inline.jsonl` no longer matches the text. The make jobserver
controls every compile and link job, and each output uses one generated GNU
linker script.

The 402 load/file outputs are the SLUS EXE, MAIN, OVMOVIE, two resident engines,
60 town views and 337 dungeon banks. Additional `check_<recipe>` images cover
every compiled recipe absent from those extents, and `check_place_<id>` layouts
cover registered placements whose shared recipe passed elsewhere; each is
compared with its exact disc slice. They are diagnostic placements, not runtime
load claims (`build/.state/outside_recipes.json`, `placement_checks.json`). The
checker refuses any compiled recipe or registered overlay row left outside a
matched image. No dead-code retirement is inferred from exclusion.

Explicit `.incbin` gaps import bytes that no source produces yet, so those bytes
match by construction; origin receipts count object, assembly and imported bytes
separately. Compiler-local switch tables are linked address-only (NOLOAD), so
their image bytes are imports too: every placed table is therefore re-linked
alone with the table loaded and its contents compared with the disc, exactly as
the window gate does (`local_table_mismatches`); any difference fails the image
and names the row. Matching these images does not prove complete C
reconstruction, historical linker recovery or runtime overlay exclusivity.

## What `make check` proves

`make check` rebuilds what is out of date, then:

- verifies each of the five disc files against its committed size and SHA-1
  (`config/link_graph/files.000.jsonl`) and compares every image with its slice;
- re-hashes the header, pipeline (build/gate/link tools, maspsx) and link-input
  (`config/overlays`, `config/link`, `config/link_graph`, `config/*.txt`)
  stamps, which are content digests, and refuses a stamp that no longer matches
  its inputs;
- refuses an object whose proof (recipe, every input including included `.c`
  files and the owner TU of a projection, object hash) is stale;
- refuses an image that was not linked from the current objects and link
  inputs (`build/.state/origins/<image>.json`);
- refuses an omitted image, an unconsumed recipe, a registered overlay row
  outside a matched image, or inputs changing during the check;
- prints one line per image (`MATCH ... assemblers=` or `DIFF <image>
  offset= disc= symbol=`) and writes `build/check.json`, the content-bound proof
  read by quality accounting.

Native TUs use the **canonical native build**, including its whole-TU genuine
ASPSX 2.79 comparison, when the SDK and wibo are installed
(`tools/setup.sh --psyq DIR`); otherwise configuration records `maspsx_only` and
never labels the run genuine. Changing the SDK requires `make configure`.
`make configure` also refreshes the live source/layout attestation; a changed
compiler cell or placement extent fails instead of being silently blessed.

Incremental rebuilds: a source edit rebuilds its recipe and consuming images;
a header edit rebuilds recipes whose include closures consume it, including
SLUS assembly includes. The complete header and pipeline digests are still
checked independently. Compiler tools invalidate objects; linker tools
invalidate images. The compiler stamp follows imports reachable from the compile
entry points, plus the shell and file-loaded compiler/assembler helpers. It binds both source authorities and the executed gate-view copies, refusing
a stale exported copy. It does
not enumerate maspsx tests or unrelated fidelity commands. Local Python imports
observed by a real compile must belong to this closure; an unregistered import
fails the compile. GCC driver/cc1/cpp inputs are bound to each TU's compiler cell,
including SLUS TUs. Changes to landing/accounting tools or ordinary documentation
do not invalidate either. A content-identical regenerated ledger or stamp keeps
its mtime. An edit under `config/overlays` or `config/link` regenerates the
projection and relinks images when the link-input content digest changes.
Adding or removing files needs `make configure`.

Build-view tool exports and source-view symlinks also preserve identical bytes
and targets. The flat gate tool view copies `name_inputs.py` from its build
authority; the source tree needs no gate symlink or duplicate helper. Retired
exports are removed. The configure CLI verifies bootstrap
inputs on every run; configure and check independently compare exported tools
with their source authorities, including their expected file/directory inventory.

Name-table changes use per-product witnesses in `build/.state/name-inputs/`.
`ccproc` records identifiers from GCC's actual assembly before canonicalization,
including unsuccessful lookups; this handles identifiers created by macros and
token pasting. String directives remain opaque, as in canonicalization itself.
Configure projects the effective name table onto that vocabulary and writes the
witness only when its content changes. Thus adding a formerly absent mapping
invalidates its consumers, while changing an unused row or an evidence comment
does not invalidate their objects. Both ordinary and native `--names-only`
compiles record witnesses. SLUS explicitly selects this checkout's default
noreturn/sibcall tables and binds only their rows whose canonical symbols occur
in the assembly vocabulary, including membership misses.
Link witnesses record the alias lookups actually made
by `symbol_addr`, including misses. The whole name table stays in the independent
pipeline witness, but is not an object/link tool prerequisite.

These are compile/link products, separate from configure checkpoints. Object
proofs hash the exact name witness; image origins bind their link witness. SLUS
C commands now also write content-bound object proofs. `make check` independently
reprojects every name witness against the current table, then checks the product
proofs. Refreshing a witness cannot refresh a stale object proof.

SLUS object rules consume a manifest containing only their selected module row;
retail spans are materialized from the authority root before writing the slice.
The registered full manifest remains validated during configuration. Inline
member projections bind their own provenance record instead of the entire inline
ledger, and still rederive/validate the member from its owner at compile time.

Recipes, frozen evidence, projected source, image JSON and make fragments preserve
their mtimes when their bytes are unchanged. The makefile includes a digest of its
remake inputs, so a real metadata change acknowledges itself through changed
content rather than an unconditional timestamp touch. A successful compile/link
acknowledges the publication time of its own new witness on its object/image;
this is separate from configure's content-preserving output writes.

`make configure` verifies content snapshots of the input trees and generated
files before reusing the build views and make projection. A changed input or a
missing/edited generated file runs the corresponding generator again. These
snapshots are private build caches, never gate receipts. Edits to existing
source/header files reuse unaffected selection records, native recipes, include
closures and image layouts. Each record binds its source reads by content,
including inline owners and reviewed storage sources. The shared guard binds
all authority/configuration inputs, the complete input name/presence set,
environment and symlink destinations. Adding a local header that shadows an
include therefore forces fresh resolution. Metadata/tool changes or missing or
edited generated files discard the checkpoints. Live graph source hashes are
refreshed on every changed-input configuration.

Bootstrap also reuses verified views for body edits outside its conservative
module/partition source read set. Include scans share reads within one generation;
file and resolution probes are checked again before it completes. Projected
source spans retain the production inline provenance checks. Configuration reuse
does not replace the compiler, image or `make check` proofs.

For a fresh enumeration without deleting the build, run
`python3 tools/build/mkbuild.py generate full`. To assert that the current scoped
projection emits the same generated files and `build.mk` bytes, run:

```sh
AZURE_MAKE_SCOPED_EQUIVALENCE=1 PYTHONPATH=tools:tools/tests:. \
  python3 -m unittest -v tools.tests.test_recipe_cache.ProductionEqualityTests
```

The comparison excludes only the private configure checkpoint and its receipt.
The regular make unit suite also exercises same-mtime edits, changed include
closures/cycles, local header shadowing, source symlinks, owner/review reads,
authority/environment changes, corrupt outputs and inputs changing mid-generation.

Regression tests for these properties: `tools/tests/test_make_negative.py`
(synthetic parts always run; `AZURE_MAKE_NEGATIVE=1` mutates a built checkout:
overlay/SLUS constants, comment-only edit, tampered image/object, unlinked image,
switch-table swap, included-file and projected-span edits, header edit with an
old mtime; `=full` adds the linker-catalog and shared-header edits).

## Quality levels

The default `tools/levels.py` rule uses current image proof and registered module
membership with a consumed shared header. L4 additionally retains all existing
lower-level requirements, zero pins, zero tail jumps, no assembler imitation and
the compiler cell predicates. L5 adds the unchanged fidelity-site, computed-goto,
inline asm, NON_MATCHING and compiler-model predicates. A SHA-1 match alone grants
neither. `tools/status.py` reports this image proof without validating module
certificates. Missing or stale make proof fails quality regeneration.

For the transition comparison the old rule remains available:

```sh
python3 tools/levels.py --legacy-certificates --output build/levels_legacy.jsonl
python3 tools/status.py --legacy-certificates
```

## Landing

```sh
tools/land_make.sh --incremental --jobs 8 --message 'Describe change' patch.diff
```

The lander requires a clean worktree/index, checks and applies the patch series,
then runs the steps below, stopping before any commit on the first failure (the
applied tree is kept for diagnosis; logs and timings in `build/landing/`):

1. privacy scrub of every changed/new file, refusing symlinks and binary files;
2. "no new debt": changed `src/`/`include/` C may not add inline asm, volatile,
   NON_MATCHING, `#pragma`, goto or `M2C_` tokens beyond its HEAD version
   (comments and strings ignored; `--allow-debt CATEGORY` records an accepted
   exception, never for asm; report in `build/landing/debt.json`);
3. source layout check, registry, physical graph and source index regeneration;
4. `make configure`, a **cold** clean of every object, link product and image
   unless `--incremental` is given, `make -jN`, `make check`;
5. genuine ASPSX required (`--allow-maspsx-only` to accept a maspsx-only run);
6. content-bound levels and status regeneration (skipped only when their inputs
   and outputs are unchanged and the current make proof verifies), the make/lander unit tests
   (`--test-module` adds more), a final scrub and a freshness re-check of the
   image proof;
7. exactly one commit (`--no-commit` performs every proof without it).

The default remains cold: omit `--incremental` for the first landing in a
checkout or when deliberately requesting a complete rebuild. Once `build/` is
current, `--incremental` is the normal landing mode; every landing still runs
`make check`, unit tests and the final proof freshness check. After successful
configuration, the lander acknowledges the generated Makefile's timestamp so
an orchestration-tool mtime does not repeat the verified generator during the
following build and check. Input digest stamps advance with content changes. Accounting reuse
also verifies its output bytes, so a manually edited levels ledger or status
page is regenerated.

Historical measurements before content-bound configure reuse, at -j12: configure 4-9 min, cold build
20-24 min, `make check` 20-25 s, no-op make under 1 s, one-file C edit about 8 s
plus the check; a cold comment-only landing took 33 min.

## Retirement of the window gate and certificates

The one-time dual proof (cold make check and the full window gate on one commit,
row cross-check, negative suite, certificate renewal and legacy/default levels
diff) is recorded with the landing that adopts this path. After the owner's
decision:

| Current step | Disposition | Successor / retained purpose |
| --- | --- | --- |
| `gate_all` window loop and receipt collection in landing | REPLACED BY `make check` | Complete images, extra recipe/placement layouts and table-content probes; keep `overlay_local_gate` for candidate diagnostics |
| `certify_batch` certificates and renewals | RETIRE as a landing requirement | Canonical native whole-TU/genuine checks run inside make; image proof supplies placement bytes; keep manifest membership/type/ownership validation |
| Certificate `--validate-only` | RETIRE | `make_evidence.checked_receipt` rechecks current inputs and outputs after accounting |
| Per-window fingerprints and `inputs_sha` | REPLACED BY make compile/image proofs and content-digest stamps | |
| Source-layout, registry, source-index, physical graph regeneration | STILL NEEDED | Before configure |
| L4/L5 certificate dependency | RETIRE after the owner rules on the L4 definition | Current checked image + module shared header, then all pin/tail/fidelity predicates |
| Privacy scrub, debt scan, unit tests, patch admission, one commit | STILL NEEDED | In `land_make` |
| SLUS image gate | REPLACED BY the SLUS EXE in `make check` | Keep partition/data/allocation validators used by SLUS configuration |
| Portable certificate packages | RETIRE from landing | Optional future work |

Do not delete the compiler wrappers, native allocation validators, source quality
predicates, layout/registry data or disc import accounting.
