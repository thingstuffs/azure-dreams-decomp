# Row source locations

`tools/gate/source_layout.py` is the only implementation of source location
policy. `tools/source_layout.py` is its public import/CLI facade, and
`common.clean_path(row)` delegates to it. The implementation also travels with
the gate copies in build views. `c_path` remains an immutable lineage token;
`raw_path`, lane `base/`, `out/`, candidate names and object stems stay stable.

`ledger/layout.jsonl` records exactly `{"id": ROW_ID, "path": RELATIVE_C_PATH}`.
The shipped map explicitly records today's locations for every registered row.
An absent ledger or a missing row entry defaults to `src/<container>/<basename>`.
Paths must remain under the same source container and preserve the filename.
Unknown/duplicate IDs, duplicate effective paths, traversal, stem changes and
source symlinks escaping the source tree are rejected. This stage supports one
whole file per row. It does not introduce chunk extraction or merge functions.

Use `row_path(row_or_id, root)`, `row_relative(row_or_id, root)`,
`source_files(container, root)`, `source_items(root)` and
`row_ids_for_paths(paths, root)`. Explicit roots work in isolated checkouts.
The decoded map cache is keyed by device/inode/size/mtime/ctime of the map and
registry; a changed layout is visible on the next lookup. Validators doing a
whole graph read `mapping(root)` once and pass it as `layout=` to row_relative.
This is an invocation-local snapshot, with fresh validation on each invocation.

Overlay module manifests keep explicit canonical `source` and member paths;
the validator compares each member against the resolver. SLUS manifests use
exported build `src/...` tokens; `slus_module_context.source_path` and the SLUS
recipe tool resolve row tokens through the same map. Wrapper paths remain
explicit in manifests. Native packages install at current paths while keeping
basename-keyed staged payload filenames.

`materialize_flat(destination, root, source_root=None)` returns the original
source directory at identity, without writing anything. After a move it builds
a managed symlink projection with the historical row basenames plus nested
wrapper paths. Links see candidate swaps immediately. Overlay and SLUS view
builders use this projection; legacy gate directory discovery keeps its existing
contract. Raw/flat experiments pass through, and nested experiments project
their own bytes. A manually created projection directory is never overwritten.
A changed layout forces a full gate in the package lander. The lander checks
mapped files before graph/index/proof regeneration.

Examples (commands run from a checkout):

```
python3 tools/source_layout.py check
python3 tools/source_layout.py path dungeon/func_8188C800
# Convert git's physical paths to stable ledger IDs:
git diff --name-only -- src | python3 tools/source_layout.py ids
python3 tools/layout_move.py dungeon_ovl_18ac800
python3 tools/layout_move.py dungeon_ovl_18ac800 --package pilot_package
python3 pilot_package/apply.py --root ROOT --live --dry-run
```

The mover is deliberately a separate operation. It accepts a currently certified
physical overlay module, looks up its proposed directory in
`config/layout_proposal.tsv`, checks every destination, then plans row/wrapper
and module-specific header moves. Shared headers remain shared. Quoted includes,
module source/member/header paths and just the affected layout records change
together. Outside include consumers and `__FILE__` need a separate review and
are refused. Ledger-only groups and SLUS partition moves are not supported by
this pilot planner. The default only prints a plan; `--package` exports guarded
payloads and does not edit sources. The generic installer validates every
before/after SHA-256 and outer payload inventory before writing, supports
creation/deletion, rejects partial application, and restores file bytes after
an installation failure. `--live --dry-run` never writes. The canonical-root
contract also requires `--live` for a preview when LAND_LIVE_ROOT is set.

A move package invalidates the old module certificate. Gates and certificate
renewal run in the owning landing transaction; the installer never calls proof
tools. Tool changes in the resolver also invalidate existing certificates which
bind those tools, so the resolver landing must renew affected certificates.
The identity map itself changes neither row locations nor emitted bytes.
