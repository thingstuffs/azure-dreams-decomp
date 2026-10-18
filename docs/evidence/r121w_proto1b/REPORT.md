# r121w_proto1b delivery

Baseline: the lane's initial B13 snapshot, recorded by `SCRATCH_HEAD` as
`ddc07bc5949684593cdc45a67e378a1f18324318`. This private root has no Git metadata.
`original/src/` preserves all 436 queued source files before any edit, and the patch
is generated against those bytes. No commits or ref moves were made.

## Per-item status

Every entry in `refs/queue.tsv` has exactly one entry in `results.tsv`.

| Status | Files | Meaning |
| --- | ---: | --- |
| COMPLETE | 140 | All file-local scaffolding removed; requested declaration work has no recorded hold |
| PARTIAL | 244 | Verified changes delivered; at least one data/signature/ownership question remains |
| HOLD | 46 | Original bytes retained because the file's requested work lacks sufficient evidence |
| SKIP_COPY | 6 | Original relink/hand-copy bytes retained, as required by the LL4 exclusion |
| Total | 436 | Entire fixed queue assessed |

384 queued C files change. No canonical C source outside the queue changes. No shared header
changes; the requested list of shared-header additions is therefore empty.

File-local `M2C_*` occurrences decrease from **1,093 to 346**, a reduction of
**747 (68.3%)**. 225 queued files now contain no `M2C_*` tokens. Of the remaining
346 tokens, 314 are unresolved scalar extern-data declarations in home sources;
32 belong to the six excluded copies. File-local token counts do not count tokens
inside included headers, and zero tokens alone does not mean a signature is fully
resolved: such cases retain explicit holds.

## Deliveries

- `delivery.patch`: 384 queued C files only, relative `a/src/...` / `b/src/...` paths.
- `results.tsv`: per-file before/after token counts, status, changed flag, row proof,
  hold reasons, and final source SHA-256.
- `holds.tsv`: one explicit line per unresolved symbol/reason, with source evidence
  and the retained declaration where applicable.
- `signature_evidence.tsv`: definition-derived prototypes, concept declarations,
  caller-derived contracts, and signature conflicts.
- `signature_mismatches.json`: the rejected definition signatures and retained
  working declarations, including the separate bank-identity cases.
- `resident_alias_evidence.tsv`: 14 resident SDK alias hints for continuation.
- `touched_windows.txt`: the exact 104-window production gate scope, including
  windows containing placements of edited homes.
- `gate.log`, `gate_journal.jsonl`, `gate_run.json`: the single scoped gate result.
- `final_row_checks.json`: 384 final source hashes and references to exact row checks.
- `audit.json`, `patch_check.log`: scope/body audit and successful patch dry run.
- `baseline_sources.sha256`: exact initial bytes of all 436 queued sources.
- `MANIFEST.sha256`: hashes of the portable delivery and evidence files.

The supporting scripts and small check logs remain in this lane. The large symbol
index is isolated in `scratch/` behind `.ignore`; it is not a delivery receipt.
No binary or retail payload is included in the delivery patch or portable evidence.

## Changes and limits

Extern functions with a unique usable C definition receive that definition's
signature, including return type, pointer types, argument count, and narrow integer
parameters. Existing tagged types are forward-declared where sufficient. For
anonymous callee types needed by a prototype, the existing defining layout is
reproduced locally; no new tag is invented to impersonate an anonymous type.
Definition provenance is listed in `signature_evidence.tsv`.

Where no C definition or SDK declaration is available, observed caller arguments
supply explicit parameter lists where the body permits them. The original signed
word return representation is retained unless an established standard pointer/void
contract applies. Those declarations remain partial signature work in `holds.tsv`;
removing an alias is not claimed as recovery of an unobserved callee contract.
Address-only callbacks retain unspecified parameters when there is no call evidence.
The two symbols observed with different caller arities, `func_8001E578` and
`func_800197D8`, retain a first signed word parameter and a variadic tail.

Fourteen scalar extern occurrences use concrete declarations already recorded in
concept headers. Sixteen explicit extern pointer objects retain their pointer level
and use a signed-word pointee view; their semantic pointee types remain held.
Unknown scalar storage is not assigned a guessed four-byte allocation or an
invented array bound.

Local aliases are replaced by their exact signed widths from `m2c_compat.h`, unused
compatibility definitions are removed, and the existing packed one-word copy type
is named `PackedItemWord`. `m2c_compat.h` is removed from every edited file that no
longer contains a `M2C_*` token. Where it had supplied `NULL`, the existing exact
expansion `0` is used. No casts are added, and no pins, asm, volatile,
`NON_MATCHING`, pragmas, gotos, or masks are introduced.

## Signature mismatches: original-prototype evidence

Applying these found definition signatures made the caller fail to compile.
The retained caller contracts all pass byte-exact row checks. These discrepancies
are evidence of a different original caller declaration or a stale/ambiguous
binding; they are not grounds to change a callee outside the assigned queue.

| Caller source | Symbol | Found definition | Retained caller contract |
| --- | --- | --- | --- |
| `src/main/func_800109B0.c` | `func_8004E994` | `void(void)` in `src/slus/code.c` | `void(s32)` |
| `src/town/func_80095ED8.c` | `func_800352FC` | `void(void)` in its SLUS home | `s32(s32, s32, s32, s32)`; caller tests the result |
| `src/town/func_800C6A14.c` | `install_object_handler_and_clear_slot_flag` | `void(void *)` | `void(void *, s32, s32)` |
| `src/town/func_802EE4E8.c` | `card_build_selected_slot_details` | `void(void *)` in its MAIN home | `s32(void)` |
| `src/town/func_804B7CE8.c` | `call_helper_with_fixed_id_0x118a` | `s32(void)` in `src/town/func_8070F854.c` | `s32(s32)` |
| `src/town/func_804B81A0.c` | same helper | same definition | `s32(s32)` |
| `src/town/func_804B8384.c` | same helper | same definition | `s32(s32)` |

There are **seven conflict sites involving five symbols**. The three helper sites
also require checking bank-specific alias ownership before inferring a shared
original function.

Two additional apparent mismatches were excluded from that count:
`func_80017744` in `src/town/func_806F1A40.c`, and `func_80017724` in
`src/town/func_80761C28.c`. A matching low-address spelling exists in another
bank. Its definition is not sufficient identity evidence for the caller's bank;
both retain explicit one-word caller signatures and bank-identity holds.

## Holds by reason

Counts below are symbol/reason occurrences; a file can have several holds.

| Reason | Occurrences | Needed evidence |
| --- | ---: | --- |
| DATA_NO_DEFINITION | 308 | Home object definition, matching typed data row, or trustworthy concept declaration and storage bound |
| DATA_TYPE_CONFLICT | 6 | Bank-qualified object identity and a unique concrete view |
| NO_C_CALLEE_DEFINITION | 142 | Matching SDK/asm ABI evidence or recovered home C signature |
| POINTEE_TYPE_UNKNOWN | 16 | Semantic record/pointee definition for an already explicit pointer object |
| SIGNATURE_MISMATCH | 7 | Original caller declaration and alias/binding audit |
| CALLEE_BANK_IDENTITY | 2 | Callee identity in the caller's load image |
| CROSS_CONTAINER_IDENTITY | 2 | Ownership/binding proof for the dungeon definition found from another container |
| NON_HOME_COPY | 6 | LL4 handling; leave these source copies unchanged |

Exact entries, including the unchanged 46 files, are in `holds.tsv`.

## Validation

Every changed source has an exact row check at its registered recipe:
**340 overlay source rows** score byte-exact against their retail slices;
**44 SLUS source rows** produce entire production objects with identical SHA-256
against the preserved B13 source. All 44 use full object identity; none relies on
a metadata-only or disassembly-only comparison. The canonical compiler, ccproc and maspsx pipeline
is used. No per-row window-gate fallback was invoked. `final_row_checks.json` selects
the final exact record for each changed source; the staged check journals also
retain earlier rejected candidates and compiler diagnostics.

The normalized function-body audit verifies that changes inside bodies are confined
to the exact signed-width aliases, the existing `NULL = 0` expansion, and the name
of the existing packed type. This also checks that calls and control flow remain
present. All six excluded copies retain their original SHA-256. The patch changes
only queued C files, contains no absolute home paths, and passes
`patch -p1 --dry-run --batch -d original -i ../delivery.patch`.

The one final scoped production gate uses `--workers 4` and one `--only-window`
argument per entry in `touched_windows.txt`. The directly affected set contains **432 overlay rows**:
340 changed home rows and **92 additional placement rows** that compile those homes.
The enclosing windows also verify unchanged neighboring rows; the main
`town_scene` window alone contains 1,765 registered rows.
Overlapping active windows are included; production-superseded seed windows are
excluded using the production policy. No shared header requires a broader scope.

**Final gate: 104/104 MATCH, exit code 0**, using four workers in one scoped
invocation (1791.71 seconds including the final input-currentness audit).
Every requested active window has a fresh MATCH record. `gate.log` contains the
production output and `gate_journal.jsonl` retains the input-bound verdicts.
The 44 SLUS objects were verified per row; no additional whole-SLUS gate was run.

## HOW TO CONTINUE

`check_rows.py --paths <relative-source-list> --out <fresh-check-log.jsonl>`
checks a subsequent explicit source subset with four workers. The original queue
and `original/` are immutable evidence. `apply_initial.py` and `apply_second.py`
are the historical staged rewrite scripts, not an idempotent continuation command;
do not rerun them over additional manual fixes. Use the delivered patch and the
current final source hashes as the continuation point.

1. Start from `results.tsv` and select a hold reason in `holds.tsv`. The unchanged
   HOLD files are useful first targets because they consist entirely of unresolved
   storage declarations. Do not search `work/` or the repository root recursively.
2. Resolve data by the caller's bank and physical offset, then use its home C/data
   definition or a reviewed concept header. The contextual link-map/data-row lookup
   found no exact defining objects for these held declarations. Do not infer an
   object's allocation size solely from the next named address or a partial read.
3. For missing library signatures, use `resident_alias_evidence.tsv` first. It maps
   representative addresses to `EnterCriticalSection`, `ExitCriticalSection`,
   `StartRCnt`, `SetGeomOffset`, `SetGeomScreen`, `TransMatrix`, `ScaleMatrix`,
   `SetRotMatrix`, `SetTransMatrix`, `RotTrans`, `RotMatrix`, `SetDispMask`, `rsin`,
   and `LoadTPage`. Obtain the corresponding SDK types/prototypes before replacing
   caller-width views with stronger semantic signatures.
4. Audit the seven conflict sites and two bank-identity cases in
   `signature_mismatches.json`. Confirm alias ownership before treating same-spelled
   functions in different load images as one callee. Keep the verified caller
   contracts until stronger original-prototype evidence is available.
5. Leave the six `SKIP_COPY` sources for LL4. Do not move their work onto another
   C file in this lane. Any shared header needed later may only gain declarations,
   and must be listed in that delivery.
6. For a subsequent source change, check each affected row first, then compute its
   full placement scope. This delivery has already consumed its single final scoped
   gate; any new edit needs a new reviewed verification batch. The current patch is
   the concrete verified partial delivery, not a claim that the remaining types
   have been recovered.
