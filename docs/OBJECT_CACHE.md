# Object cache projections

The object cache reuses a previously compiled object when its bound inputs
match. For C headers, declaration-use projection can keep the key unchanged
after an unused declaration changes. The first hit with a new complete
preprocessed expansion still recompiles the object and checks its bytes against
the cached object. Later hits for that expansion restore it without a compile,
apart from verification sampling. This means a one-off prototype edit does not
save its first round of compiles; repeated builds with the same edit can. A
cache hit refreshes its proof for the current tree. The landing's image check
remains the final byte-exact guard for linked outputs. Schema 3 adds
declaration-use projection for cacheable C compiles. The selected
compiler still supplies the live include walk and preprocessed text. Clang
partitions that text into complete top-level declarations; all function and
object definitions, static declarations and side-effecting or unclassified text
remain. A lexical
reachability walk retains every prototype, extern object declaration, typedef,
record and enum whose spelling appears in retained text, directly or through
another retained declaration. Lexical matching deliberately keeps some extra
declarations when spellings coincide. Kept declarations remain in their
original order. If Clang cannot parse or fully partition the text, or sees a
directive, the whole preprocessed text and raw header hashes are used.

When every source in a recipe projects successfully, the outer key binds
compiler-discovered C header paths and presence instead of their raw bytes.
All source files, non-C inputs, tool closure, compiler binaries, assembly
inputs and name witnesses retain their existing bindings. A header also read
by an emitted assembler include keeps its raw hash even when the C compiler
included it. Clang's binary hash
is bound for projected recipes. Debug flags already bypass the object cache;
unused type declarations can therefore be omitted without changing emitted
debug information. Each entry records every byte-verified set of complete
expanded-text SHA-256 digests. A projected-key hit with a new complete expansion
is rebuilt and compared byte for byte, even when `AZURE_OBJECT_VERIFY=0`;
a successful comparison adds the expansion to that entry. Returning to any
recorded expansion can hit without rebuilding. Sampling a new expansion would
let an unproven projection restore an object before the image check, so the
first use remains a mandatory comparison. In the run 2 header probes, all
836 unused-prototype hits and 1,432 prototype-move hits were byte-identical
under `AZURE_OBJECT_VERIFY=100`. Those comparisons cost 1,255.2 and 2,368.8
cumulative object seconds, respectively. Sampling only one percent of new
expansions would save about 99 percent of those compile seconds on a repeat of
the same probes, but any single incorrect projection would have only a one
percent chance of being caught at this gate on its first use. The image check
does not cover objects that are not linked. These probes do not establish that
every future declaration projection is safe, so new expansions continue to
require a comparison. `AZURE_OBJECT_VERIFY` samples previously
verified expansions using
fresh random salt on each lookup. The default one percent floor applies even
when `AZURE_OBJECT_VERIFY=0`, so a key cannot remain permanently outside the
sample; `AZURE_OBJECT_VERIFY_FLOOR=0` is available for deterministic tests.
Symbolic allocation source and header contracts are validated
before a cached object is restored. Schema 3 uses a separate `v3` directory so v2 entries
remain untouched.

Schema 3 retains schema 2's separation of a compile's content key from its name
lookup witness. The outer key binds the recipe, source and current include walk,
projected preprocessed output, compiler and tool bytes, environment and executable
hashes. Recipes that fail projection bind the whole preprocessed output and raw
header hashes.
For supported recipes with `name_input`, it omits `config/names.tsv` and the witnessed
`MASPSX_NORETURN_FILE` / `MASPSX_SIBCALL_FILE` config tables. Files also discovered
as raw compiler or assembler inputs retain their whole-file hashes, except for
projected C headers as described above.

Each outer key can hold several variants:

```
<cache>/v3/<outer-sha256>/<variant-sha256>/manifest.json
<cache>/v3/<outer-sha256>/<variant-sha256>/0
...
```

The variant hash binds the outer key and the complete witness. The manifest also
records that witness, every byte-verified complete expansion, and hashes
every artifact, including the witness artifact.
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
also understands flat entries passed to the prune CLI. The `v3` namespace has
its own locks and byte counter: an older lane's flat-cache pruner cannot reset
its accounting. The cap applies to the schema's store; a legacy store can
coexist during migration and can be pruned separately. Point the prune CLI at
`$AZURE_OBJECT_CACHE_DIR/v3` to prune the new store. Cap enforcement keeps the
existing detached prune and low watermark. Verification sampling salts the outer key per lookup; a failed
verification removes only the variant actually restored. All restored outputs
except the refreshed proof must compare byte for byte with a sampled rebuild.

Recipes without a lookup witness retain whole-table keys. Native overlay
noreturn/sibcall defaults retain whole-file hashes because their current traces
do not cover every config read. Overlay recipes that already depend on generated
scoped evidence keep those dependencies. These conservative fallbacks can still
miss after unrelated table edits; omitting unobserved inputs would be unsafe.
The volatile macro, debug flag, environment and executable guards are
unchanged. Tool closure bytes remain bound except for `mkbuild.py`: its parsed
Python syntax is hashed for the compile stamp and object key, so comment and
format-only edits do not invalidate objects. A syntax change or parse failure
changes that hash. In particular, landing a change to `object_cache.py`
changes every object's tool closure and requires one full recompile.

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
cache and logs in an ignored private directory.

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
