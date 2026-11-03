# Guarded pointer-cast routes

Run from a repository root with a seeded production build and a fresh codemap.
These tools use the same spelled-pointer cast sites and BYTES exemptions as
`tools/lint/debt_check.py`. They require only the repository's Python tooling
and MIPS Clang; tests use `unittest`.

```sh
python3 -m unittest discover -s tools/typing/cast_routes -v
nice -n 10 python3 tools/codemap/codemap.py refresh --root . --workers 4
nice -n 10 python3 tools/typing/cast_routes/census.py --root . \
  --out work/cast_routes/census --workers 4 --expected 44128
```

`--expected` is optional: supply the current independent debt count, rather
than copying an old count. The census reconciles every file to debt_check and
records its Git revision. AST caches are keyed by source, headers, recipes and
the extractor. A census is a discovery index, never permission to replay stale
edits. Refresh it after typing changes. Large facts and receipts belong beneath
an ignored output directory; the tools create `.ignore` there.

The unified planner contains four routes:

* `redundant`: exact type, null, or an already accepted object-pointer value
  conversion. Qualifications and function signatures remain intact.
* `node_body`: a pure typed ObjectNodeHeader plus 0x20 in a pointer value
  context becomes NODE_BODY. NODE_HEADER needs a documented ActorRecord or
  PlayerRecord body and minus 0x20. Typed dereference/member/array accesses retain their final pointer cast when needed; unknown reverse ownership stays explicit.
* `numeric_member`: pure, nonvolatile, direct integer members of the same
  MIPS width. An existing nonvolatile integer union member of the exact target type, width and byte offset is preferred when available. Otherwise loads preserve scalar conversion; stores must be complete
  expression statements. Compound statements preserve the original scalar load and store conversions and require a stable integer RHS. Consumed writes, calls and volatile evaluation remain held.
* `qualified_argument`: an unqualified object pointer converted through an
  object-pointer type for a fixed `const void *` argument. Variadic and
  unprototyped calls are excluded.

Macro source locations remain gated. Every edit joins fresh MIPS AST facts to
current debt-matcher spans. `--route` restricts routes; `--file` restricts files; `--reason` isolates an exact guard reason for sampled proofs or recovery after a combined trial fails.
Without `--census`, discovery visits every cast-bearing C file in the folder.
With a census, `--discover-all` broadens discovery beyond candidate categories.

```sh
nice -n 10 python3 tools/typing/cast_routes/guarded_routes.py --root . \
  --folder src/dungeon/effect --out work/cast_routes/effect --workers 4
```

Planning is read-only unless `--apply` is supplied. Application captures raw
objects, canonical assembly, canonical objects and every production variant
before and after. Failing physical streams are restored atomically. This is
only the first gate: a complete batch proof is still required.

The batch runner takes explicit folders in replay order and commits only a
successful production/image, decoded-image, native and per-function debt proof.
Set `AZURE_NATIVE_PORT` to the existing native-port checkout. It writes one
full-index patch per folder against that folder's starting commit, an edit TSV,
holds, identity hashes, proof logs and `replay.tsv`. Failed proof restores the
source, derived ledger, production objects and receipts. `--resume` skips
recorded batches; inspect held rows and use a new output directory to retry.

```sh
nice -n 10 python3 tools/typing/cast_routes/run_batches.py --root . \
  --out work/cast_routes/batches --folder src/dungeon/effect --workers 4
```

When placement copies need a node macro import, `publish_node_header.py --root .
--batch BATCH --source SOURCE` can publish it through the source's existing
private header and add the exact guarded edit to `applied.tsv`. The entire
consumer closure must then pass batch proof. Shared headers require separate
authorization.

`reapply.py BATCH/applied.tsv --root .` checks hashes, spans, bounds and overlap
for every file before writing anything. Add `--apply` to replay source edits;
rerun the full batch proof to derive the ledger and validate the destination.
A stale hash requires a fresh plan; do not force an old edit through new types.
Full-index patches are the preferred exact-base delivery. Source replay and
patch application are alternatives, and neither replaces destination proof.


When a combined file fails identity, `isolate_sites.py --root . --folder FOLDER
--file SOURCE --name BATCH --out OUTPUT --workers 4` trials individual fresh
plans cumulatively against the same production baseline. `--reason` can
restrict guard reasons. It tries the exact union view and the prior scalar
renderer as alternatives, restores every byte-changing trial, then runs full
batch proof and commits only the surviving source subset. It writes the same
replay, patch and proof artifacts as the batch runner. The trial plan may list
alternatives at one span; only `applied.tsv` is a replay input. No candidate is
kept merely because it compiles. The whole physical compilation stream must
retain raw, canonical and all-variant hashes, and the final batch must pass its
production/image, decoded, native and debt gates.

## Byte-cursor classes

`byte_cursor_classify.py --root . --census CENSUS_DIR --out DIR` splits the census
`byte_cursor` category by what the original code most likely was and names the
cheapest route for each class: `stream_reader` (a data-dependent cursor or an
offset read from the same base: legitimate end state candidates), `record_walk`
(a constant-step cursor over records: one typed element pointer per step),
`typed_member` (the code map resolves a member), `layout_gap` (typed base, the
layout lacks the member or has another width), `untyped_record` (void/byte base
read at constant offsets: retype the variable; `alias_of` says where a local gets
its value and `candidates` lists existing records matching every accessed
offset and width), `global_record`, `array_stride` and `other`. It reads the
census and the code map only (no compiler) and writes `groups.tsv` (one row per
function and base variable), per-class worklists and `summary.json` beneath an
ignored output directory. Tests: `test_byte_cursor_classify.py`.
