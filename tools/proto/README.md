# Recovering function prototypes

`prototypes.py` scans only `src/` and `include/`, using the repository's C
scanner and type model. It recovers parameter and return types from definitions,
including default promotions for old-style definitions. An empty definition
has zero parameters; the resulting declaration uses `(void)`.

Run from the checkout root:

```sh
python3 tools/proto/prototypes.py --check --out work/prototype_count
python3 tools/proto/prototypes.py --scope src/town --out work/prototype_plan
python3 tools/proto/prototypes.py --scope src/town --apply --out work/prototype_batch
```

The default is a dry run. `--apply` requires an output directory and writes its
replay map before modifying sources. `--check` exits 1 when the count exceeds
`--max-remaining` (zero by default). Its TSV identifies every remaining direct
function declaration, including identifier-list declarations. Calls, definitions,
macro bodies, assembler statements and function-pointer slots are not counted
as direct declarations. Function-pointer slots have a separate census column
and TSV. `--check --baseline remaining.tsv` refuses any new site even when
other declarations have disappeared. A smaller count alone is not an accuracy proof.

Names present in `config/names.tsv` resolve exactly like their numeric spellings.
Unmapped names resolve within the caller's container, then resident SLUS.
Address names and readable aliases resolve through each loading image in `config/link/`, the public
projection of `config/link_graph/`, using the linker's own six rebinding rules:
self entry, explicit caller bindings, same-image homes, layout displacement,
image symbols and unchanged resident references. The callee is looked up first
in that image at the resulting VMA. Unmapped names with several definitions are
selected independently in each consumer image. When a sparse image omits a named
import, a signature-only consensus considers every registered candidate at that
address in the consumer container and resident SLUS. It requires an exact name
or explicit alias and agreement among all candidates; evidence labels this as
`signature_consensus`, without claiming an outside body owns the call. The same signature-only rule
can cover an unplaced named consumer; its evidence explicitly starts with
`unplaced_consumer`. It does not create a placement or prove a runtime load. The pinned SLUS symbol map and registered
resident C homes supply resident
owners. Every placement must resolve to compatible signatures. A coincident
address in an unrelated overlay is never a fallback. Registered own-file rows
inside a proven load region link without rebinding and participate through their
physical intervals. A partial window can import an owner from its containing
load region only when both use the same file-to-VMA displacement. No link graph
shards are changed. Header declarations must
agree across all source consumers. Missing definitions and ambiguous ownership
remain in `holds.tsv`.

Native SLUS rows also enumerate resident entry points in `defs` when `func`
is null. These entries resolve only to matching definitions in that row's
registered source home. Different callees across placements or header
consumers may share one prototype when every signature and shared record-type
owner agrees. Conflicting signatures and private record identities remain held.
Qualifier comparison expands typedef names while preserving struct, union and
enum tag names, pointer levels and qualifiers.
Registered targets in overlapping windows are visible through physical
containment and the containing region's load base. This extends target lookup
without adding unrebound caller placements for rows with explicit bindings.
The scanner also recognizes definitions whose return type starts with a
struct, union or enum tag.

Historical numeric calls can use site-specific documented identity evidence in
`ledger/prototype_identities.jsonl`. Each `azure-clean.prototype-identity.v1`
record names `file`, `symbol`, `contract_file`, `contract_symbol`, the exact
canonical `contract` declaration, and a `docs/evidence/` review with its
`evidence_sha256`. The review must establish callee identity independently of
the coincident US address. The resolver copies only the signature and keeps
the numeric call symbol. It creates no linker binding or execution claim.
Duplicate records, changed contracts and stale review hashes are refusals.

Imports in a merged TU are checked against its identified members that reference
them. A sibling member that does not reference the import cannot veto the
binding of the member that does. Unknown member identities, macro uses and
file-scope initializers remain conservative, including uses hidden in included
headers. Unresolved targets and include forms outside the quoted-header model
also retain every placement.
If no member use is identified,
the resolver retains the original complete placement set.

If a compatible prototype is already in the owning folder header or an established
ancestor folder header, the tool
removes the local declaration and includes that header. A folder header may
re-export a shared feature header below its own directory; the helper imports
the feature that actually owns the matching declaration. Collector-header
declarations can also import the owner, provided that creates no include cycle. Otherwise it replaces
the declaration in place, preserving suffix attributes and assembler aliases.
Shared type headers and file-scope tag declarations make recovered parameter
types visible. Private anonymous types require a separate type-ownership change.
Imported headers are inserted before the first declaration or definition, even
when a concatenated TU has later include blocks. A required owner header already
included after earlier declarations is moved into that leading include block. No per-function headers or casts
are generated.

A definition may include a shared feature API without re-exporting it from the
broad folder header. Such an API is also eligible when it is below the owning
folder, declares at least two named contracts, and is in the definition's include
closure. A header with a corresponding source file is a collector and is excluded
from this additional search. Unincluded headers and single-function headers are
not selected. The same exact-signature and include-cycle checks still apply.

For a reviewed site whose owning-header import is blocked by unrelated type
ownership or compiler-stream changes, `--in-place` derives the same callee
contract at the existing declaration. Necessary type headers and tag declarations
are still recovered. The default continues to prefer the owning folder header;
the in-place result needs the same complete-TU and scoped proof.

Compilation may expose wrong calls or incompatible legacy declarations.
Narrow arguments, corrected return types and included headers can change code.
Take a complete-TU before snapshot before applying; compare raw objects,
canonical assembly and canonical objects afterwards, and use `prove_scope.sh`
on accepted source changes. Resolve every diagnostic against the retail call
and callee. A failed proof is a hold, not permission to keep changed bytes.

`replay.tsv` records file, symbol, original declaration anchor, replacement,
owning/type headers, forward tags, definition and binding evidence. Anchors
are statements rather than line numbers. `--skip holds.tsv` preserves reviewed
exceptions; `--wide-only` defers narrow scalar and aggregate parameters. Rerun
the census on the landing checkout because other changes can alter ownership.
`--symbols NAME...` restricts a proposal batch to selected callees.

Regression tests:

```sh
python3 -m unittest tools.proto.test_prototypes -v
python3 -m unittest tools.proto.test_probe_sources tools.proto.test_inputs -v
```

The source/header probe helpers and `transaction.py` reject missing input maps.
A manual transaction with no edits is also refused, so an incorrect map path
cannot produce a successful empty proof. `transaction.py` checks every registered
physical consumer of a changed header and rolls the complete transaction back
if identity or native diagnostics fail.
