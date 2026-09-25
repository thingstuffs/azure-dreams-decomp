# SLUS source modules

This workflow groups related SLUS rows into one compiler translation unit while
keeping every canonical row fragment and its ledger identity. A grouped source
module is a build organization supported by current evidence; it does not, by
itself, recover the retail source filename or prove that retail used the same
translation-unit boundary. For example, `runtime_directory` is explicitly an
inferred cluster in [its review](evidence/runtime_directory_module.md), not a
claim about the original source file.

Module placement follows the evidence rules in [PLAN.md](PLAN.md) and
[EVIDENCE.md](EVIDENCE.md): honor an asserted source file when one exists;
otherwise a call-graph cluster and address range can support an inferred
membership. Record the rationale, members, shared declarations, known data
ownership, and boundaries in a review under `docs/evidence/`. Name only what the
evidence supports. A partial cluster may leave callers, callees, and other users
outside the module; say so explicitly.

## Source and manifest model

Keep the canonical source fragment for each row at its existing row path. Do not
move the function body into the aggregator or replace the row's ID. Add an
ordinary C aggregator as the one physical compiler input. It includes the shared
header, defines any module-owned initialized data once, then includes every
canonical row fragment exactly once, in the chosen retail order. The shared
header owns the common prototypes, typed global declarations, and each shared
struct declaration once. The fragments remain the editable source of their
individual functions; the aggregator provides the real shared compilation
context used for verification.

Declare modules in the optional version-1 `config/slus_modules.json` manifest.
Paths below are build-root-relative. Each member's row ID must match the stem of
its member source (`slus/<stem>` and `src/<stem>.c`). The aggregator's C includes
must match the manifest's member list and order exactly.

```json
{
  "version": 1,
  "modules": [
    {
      "name": "runtime_directory",
      "source": "src/konami_runtime_directory.c",
      "members": [
        {
          "id": "slus/konami_runtime_w_8003C634",
          "source": "src/konami_runtime_w_8003C634.c",
          "functions": ["func_8003C634"]
        },
        {
          "id": "slus/konami_runtime_w_8003C758",
          "source": "src/konami_runtime_w_8003C758.c",
          "functions": ["func_8003C758"]
        },
        {
          "id": "slus/konami_runtime_w_8003C920",
          "source": "src/konami_runtime_w_8003C920.c",
          "functions": ["func_8003C920"]
        }
      ],
      "headers": ["include/common.h", "include/slus/runtime_directory.h"],
      "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
      "data": [
        {
          "symbol": "D_80080A6C",
          "asset": "assets/54240.bin",
          "offset": 44,
          "size": 4,
          "vram": 2148010604,
          "bytes": "04000000",
          "section": ".sdata"
        }
      ],
      "evidence": "docs/evidence/runtime_directory_module.md"
    }
  ]
}
```

The example's membership and ownership rationale are documented in the linked
review; use the module's actual evidence and current recipe when preparing a
manifest. The loader rejects duplicate module/source/object stems, row IDs,
functions, and data symbols, unsupported paths or sections, and malformed data
records (`tools/build/slus_modules.py:load_manifest`). The reviewed evidence
document must be under `docs/evidence/`.

## Data storage and link placement

Put data in the manifest only when its exact owner, bytes, extent, address, and
section are established. For each definition record the source asset, offset,
size, VMA, storage bytes, and section. Support covers initialized `.sdata` and
zero-only `.sbss`. It checks the bytes against the asset and the VMA against the
PS-X EXE mapping. Definitions within each input section must form one contiguous,
ordered interval in one asset. Distinct sections may occupy separate intervals.
The record size is the carved span, including ordinary alignment before the next
symbol; it does not redefine the C type's size. The helper replaces only each registered asset interval with the
module object's section; untouched prefixes and suffixes remain asset chunks.
The ordered linker script must contain one unambiguous slot for the original
asset, and owned absolute symbol assignments must have the declared address.
When a new internal carve boundary is not aligned to the containing output
section's `SUBALIGN`, the rewrite uses `SUBALIGN(1)` there to prevent inserted
padding between exact byte chunks. Word-aligned carves preserve the directive.
Unsupported, overlapping, changed, or ambiguous ownership is a build error,
not permission to widen a carve (`tools/build/slus_modules.py:plan_asset_carves`,
`rewrite_ordered_linker_script`, `filter_owned_symbols`).

`tools/fidelity/prove_slus_ownership.py` checks actual object section identity,
length and bytes, symbol offsets/bindings, linked addresses and final image bytes.
For NOBITS `.sbss`, the ELF section size supplies zero storage; an absent section
cannot pass as an empty binary dump. COMMON and absolute symbols cannot stand
in for allocated storage. Schema-2 ownership receipts group data proofs by section.

Direct genuine-ASPSX equality remains the ownership prover's default. For a
member that retains the already accepted missing-compiler epilogue model, name
that row explicitly with `--compiler-model-row ROW`. This selects only the
`t272` model and produces a schema-3 receipt: the original direct discrepancy
stays in `rows`, while `modeled_rows` separately proves a fresh compiler stream,
rewritten only for the selected member's functions, through genuine ASPSX 2.79
against both the pipeline object and retail without masks. The model code is
fingerprinted before and after. Unknown/unselected row IDs, unexplained failures,
and a missing or masked direct measurement are refused. This option certifies
data ownership with a declared compiler-model dependency; it neither grants
module placement nor removes the dependency from the ladder. The placement
certificate's direct-genuine requirement remains unchanged.


### Scattered small-data pieces

An owner whose ordinary assembler small-data layout differs from retail may opt
into `data_pieces`. Each entry names one existing `data` symbol, its original
`.sdata` or `.sbss` section, and its alignment:

```json
"data_pieces": [
  {"symbol": "D_80080A6C", "source_section": ".sdata", "alignment": 4}
]
```

For this form, the corresponding `data.section` is `.sdata.D_80080A6C` and its
size is the explicit object span, excluding padding between objects. Every
`data` entry must have exactly one piece. Definitions remain ordinary C globals
in the original small-data section; naming sections directly in C changes the
historical assembler's address selection and is not equivalent.

`tools/build/slus_data_pieces.py` appends named ELF sections and moves only the
selected global symbols' section and offset. It preserves all instruction bytes,
relocation entries and symbol indices. Every non-section label in a selected
source section must belong to a piece; discarded gaps must contain only zero
alignment bytes and have no relocation targets. Section-base targets, relocations
originating in moved data, and out-of-span addends are refused. This validates the
selected source sections, not a census of every data symbol in the object.

Normal compilation retains `.unsplit.o` and `.data-pieces.json` sidecars. Linking
requires a stamp from independently repeating the transformation and comparing
all output bytes and the receipt. Missing or stale sidecars fail verification;
rebuild the owner object to regenerate them. Candidate compilation and restoration
use the same checks. No opted-in owner means the generated Ninja graph is unchanged.

The genuine-ASPSX object remains read-only. Its verified data spans are projected
onto the same symbol identities for comparison. Proof requires the complete
owner's emitted function set and unmasked genuine/retail equality, in addition
to the full-image and actual storage checks. Transformation hashes are part of
ownership and placement evidence. A layout proof does not establish shared C
types, an original allocation boundary, or historical module membership.
See [the implementation and integration evidence](evidence/gp_data_pieces.md).


## Recipes and row accounting

All member rows and the aggregator must use the same `ccver`, `ccflags`, and
`asflags`. Configure checks the manifest against each member's current stock
recipe and refuses a mismatch or a conflict with the aggregator's registered
recipe (`tools/build/configure.py`). A grouped row cannot be moved with the
per-row recipe lander: `require_individual_recipe` refuses it and directs the
change to the whole module cohort (`tools/fidelity/land_recipe_move.py`). The
module gate also refuses conflicting recipes and requires every member to be
included in a recipe-change trial. Treat recipe changes as one cohort operation
and re-run the full module proof; do not update one member in isolation.

The SLUS registry and split ledger continue to represent **884 logical rows**.
For a three-row module, configure compiles the aggregator once instead of three
row files, reducing the physical C compile-edge count by two (884 logical rows,
882 physical C edges for this grouping alone; later groups reduce that count
further). `logical_edges` expands the physical
module edge back into the original per-row source, object name, and recipe
records, and rejects missing, duplicate, overlapping, or recipe-mismatched
edges (`tools/build/slus_modules.py:logical_edges`). Do not collapse or rename
the member rows in `ledger/rows.jsonl` or the logical split records.

## Build, verify, and certify

1. Review the module boundary against row evidence. Resolve any hard source-file
   assertion first; otherwise document the call-graph/address-range basis and
   state that membership is inferred. Record excluded callers/callees and avoid
   semantic names or data extents that the evidence does not prove.
2. Add or update the shared header, aggregator, canonical row fragments, and
   manifest. Keep member includes in manifest order and shared declarations in
   one header. Under the shared landing lock, regenerate `build_slus/build.ninja` with
   `python3 tools/configure.py` from `build_slus/`. Check that `row_db.slus_edges`
   expands it to exactly `ledger/splits/slus.jsonl`, review the topology change,
   and update `ledger/splits/slus.build.ninja` to that generated recipe. Run
   `bash tools/build/build_slus.sh -j 4` and `python3 tools/row_db.py check`.
   Restore the coordinated source/manifest/recipe changes if validation fails.
3. Check the **whole image**, not only the edited function. Grouped-row
   verification compiles a candidate in the real module context and compares
   the resulting complete SLUS image to retail; it rejects a sibling function
   or owned-data regression even if the target row remains exact
   (`tools/verify.py:verify_slus_module`, `tools/fidelity/slus_iso.py:SlusView.gate`).
   Confirm that configuration still expands back to the complete logical row
   edge set.
4. After the membership, header, types, globals, and names have been reviewed,
   write the placement certificate under the shared landing lock. Replace the
   reviewer placeholder with the responsible review identity or record:

   ```sh
   flock build_ovl/work/land.lock \
     python3 tools/fidelity/certify_slus_module.py runtime_directory \
       --reviewer 'Reviewer name or review record' --write
   ```

   The certificate command builds a fresh view, requires the full image and
   pinned build recipe to match, then verifies every declared member against
   genuine ASPSX 2.79 and retail with no masked relocations. It writes
   `ledger/modules/<module>.json` only after all checks pass. A stale or failed
   check is a refusal; do not hand-edit the certificate.
5. Refresh the derived level and status views:

   ```sh
   python3 tools/levels.py
   python3 tools/status.py
   ```

The certificate supplies reviewed, fresh **module placement only**. L4 still
requires the complete L3 criteria, an appropriate shared header, each struct
declared once, typed globals, names and module membership consistent with row
evidence, zero remaining pins, and zero tail-jump dependencies. L5 still
requires no fidelity sites of any class, computed-goto table, inline assembly,
or `NON_MATCHING` guard, with remaining fidelity/toolchain residues recorded.
Module grouping grants no exemption from either level's criteria
([PLAN.md](PLAN.md#layers-and-sequencing), `tools/levels.py:evaluate_row`).

## Freshness

The certificate is valid only for the exact reviewed inputs. Its module
fingerprint covers the manifest entry, aggregator, every member fragment, and
shared headers. It separately records the review-document hash, verifier/tool
fingerprint, pinned build-recipe hash, and retail image hash
(`tools/slus_module_context.py:fingerprint`,
`tools/slus_module_evidence.py:certificate_reason`). Changing any of those
inputs makes placement unproved. Rebuild and rerun the certificate after the
change; `tools/status.py` reports a missing or stale certificate. The unchanged
level ladder then decides L4/L5 from the current row source and residue checks.

## Owners made entirely from collector fragments

A module may explicitly opt into `"partition_only": true` with `"members": []`
when every function comes from the existing `config/slus_partitions.json` plan.
The flag must be exactly true, and it cannot be combined with whole-row members.
Ordinary modules still require a nonempty member list. This option does not add a
logical row for the aggregator: the original collector retains each function's
identity and its complete coverage denominator.

Declare one or more nonempty incoming parts, keep the frozen collector recipe
and source hash in the plan, and include only those generated fragments in the
aggregator. The normal connected-context checks enforce the complete physical
function set and reject duplicate or missing coverage. Configuration, isolated
builds, and registry validation reject a part-only owner with no incoming part,
including when the optional partition plan is absent.

Use `tools/fidelity/prove_slus_ownership.py <module> --output <receipt>` to prove
its data. The prover measures the real collector rows, checks their entire
pipeline/retail scope, and requires direct genuine-ASPSX equality plus zero-mask
retail equality for the selected owner's entire physical TU. Receipt schema 5
records the selected partition-only modules, full collector measurements and
physical contributors. Genuine debt in a different collector stream remains
visible and does not become an assertion about the selected owner.

This option supplies data ownership and physical build organization. It grants
no whole-row placement credit to a collector: `certify_slus_module.py` refuses
partition-only placement certificates, and status grants no collector placement
from these fragment proofs. The normal shared-header and source-quality criteria
continue to apply to whole-row module cleanup certificates.

The motivating [collector-only rehearsal](evidence/gp_partition_only.md) shows
two small owners at their original compiler recipes, a complete retail-exact
SLUS link, and preserved collector remainders. Treat the recorded ownership
boundaries as supported build organization; they do not recover a retail source
filename or automatically identify adjacent data as part of the same allocation.
