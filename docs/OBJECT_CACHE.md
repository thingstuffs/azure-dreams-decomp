# Object cache name projections

Object cache schema 2 separates a compile's ordinary content key from its name
lookup witness. An outer key binds the recipe, source and current include walk,
preprocessed output, compiler and tool bytes, environment and executable hashes.
For supported recipes with `name_input`, it omits `config/names.tsv` and the witnessed
`MASPSX_NORETURN_FILE` / `MASPSX_SIBCALL_FILE` config tables. Files also discovered
as raw compiler or assembler inputs retain their whole-file hashes.

Each outer key can hold several variants:

```
<cache>/v2/<outer-sha256>/<variant-sha256>/manifest.json
<cache>/v2/<outer-sha256>/<variant-sha256>/0
...
```

The variant hash binds the outer key and the complete witness. The manifest also
records that witness and hashes every artifact, including the witness artifact.
Lookup never trusts the consuming root's configure-time placeholder. It reads
candidate witnesses from the cache and compares their recorded rows with the
projection of the current table over **all** recorded tokens. Missing lookups
remain in that token set: adding a previously absent mapping changes the
projection and forces a miss. The witness includes the canonical `.ent` lookup
used by section selection. Native compiles merge the sectioning and names-only
passes, preserving the first pass's extra lookups. Native storage witnesses also
record reverse-alias queries by canonical symbol, including empty results and
aliases shadowed in the forward map. Configure refreshes and verifies these
queries too. For config symbol sets, lookup compares membership
of canonicalized tokens in each witnessed file. An absent optional file and an
empty file are equivalent until membership relevant to the compile changes.

Candidates with a different projection are skipped, so older variants remain
available after a table change is reverted. Malformed manifests, witnesses and
artifact checksum failures fail closed. Publication requires a current witness
and complete config evidence. Snapshot hashes guard table edits during a
compile or restore; these hashes are checked for races and are not persistent
key inputs.

The existing global file lock protects candidate lookup, restoration,
publication, LRU access and deletion. Publication copies into a temporary
directory before atomically installing one variant under the lock. Pruning
accounts and removes individual variants, cleans empty outer directories and
also understands flat entries passed to the prune CLI. The `v2` namespace has
its own locks and byte counter: an older lane's flat-cache pruner cannot reset
its accounting. The cap applies to the schema's store; a legacy store can
coexist during migration and can be pruned separately. Point the prune CLI at
`$AZURE_OBJECT_CACHE_DIR/v2` to prune the new store. Cap enforcement keeps the
existing detached prune and low watermark. Verification sampling uses the outer key; a failed
verification removes only the variant actually restored. All restored outputs
except the refreshed proof must compare byte for byte with a sampled rebuild.

Recipes without a lookup witness retain whole-table keys. Native overlay
noreturn/sibcall defaults retain whole-file hashes because their current traces
do not cover every config read. Overlay recipes that already depend on generated
scoped evidence keep those dependencies. These conservative fallbacks can still
miss after unrelated table edits; omitting unobserved inputs would be unsafe.
The volatile macro, debug flag, environment, executable and tool-closure guards
are unchanged. In particular, landing a change to `object_cache.py` changes every
object's tool closure and requires one full recompile.

Run focused tests with:

```
python3 -m unittest tools.build.tests.test_object_cache
python3 -m unittest discover -s tools/build/tests
```

For an independent differential check, select a private `AZURE_OBJECT_CACHE_DIR`,
fill it with a cold build and run `make check`. Retire only aliases absent from
the completed witnesses, regenerate the build and run with
`AZURE_OBJECT_VERIFY=100`. If make correctly skips all unaffected objects, use
`make -j6 -W build/.state/compiletools.ok` to exercise lookup and byte verification
for every object while keeping the stamp's actual content unchanged. Run
`make check` again, restore the alias edit and check the final tree. Keep the
cache and logs outside searched source directories.

## Interpreting a differential replay

Compare builds under the same bound environment, including `LANG`. A locale
change is a legitimate outer-key miss and can hide the benefit of a names-table
edit. Count safety bypasses separately from cacheable hits and misses, and keep
the event log for each attempted run separate; interrupted attempts can leave
valid cache entries without a corresponding completed event.

An assembler recipe that reads `config/names.tsv` as input keeps its whole-file
hash. An unrelated alias edit therefore still misses for that recipe. This is
expected and prevents a false hit: the name witness narrows only the reads made
by the traced name processor. For an exact merge study, compare each missed
output's old and new input maps and retain overlapping causes (source, header
closure, witnessed names or config sets, and tool closure). Count a miss as
explained solely by a shared header only when no other bound input or recipe
field changed. Use a short private build-root path for native replay; genuine
ASPSX has a DOS path-length limit for its temporary input.
