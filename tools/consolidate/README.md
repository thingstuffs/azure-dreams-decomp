# Type consolidation tools

The reusable T0 extension runs directly from the private repository root. It does
not depend on the historical drivers' lane-relative paths.

```sh
python3 tools/consolidate/consolidate.py --root ROOT census --out OUT/census
python3 tools/consolidate/consolidate.py --root ROOT census \
  --module dungeon/boss_helpers.c --out OUT/boss_census
python3 tools/consolidate/consolidate.py --root ROOT generate \
  --row dungeon/func_81327960 --select selections.json --out OUT/package
python3 OUT/package/apply.py --root ROOT --live --dry-run
python3 OUT/package/apply.py --root ROOT --live
```

`generate` also accepts repeated `--module container/module.c`. `--limit` limits
source files scanned, not the number of matching typedefs. `--select` is a JSON
object mapping `row/id|S_<addr>_N` (or an unqualified local type name) to an existing
shared type. For example:

```json
{"dungeon/func_81327960|S_8016F160_0": "ProjectileObject"}
```

The API is `consolidate.fold_types(text, typefold.Catalog(root), row_id, choices)`;
it returns `(text, folds, holds)` and never writes the source tree. Reuse a Catalog
across rows. Existing object-rewrite and pointer-fold APIs remain unchanged.

## What constitutes a match

The parser models the 32-bit PS1/o32 ABI, preserving primitive identity, signedness,
qualifiers, pointer pointees and function signatures, array dimensions, offsets,
size and alignment. Integer bounds use a restricted constant-expression evaluator.
Comments, strings and preprocessor lines are masked without losing source offsets.
Named and inline structs/unions and named by-value dependencies are supported.

A view and destination must have the same aggregate kind, size and alignment.
Every non-union named leaf needs an identical destination leaf at the same offset;
the reverse check rejects additional named destination fields over source padding.
Different padding spellings are allowed when the typed layout is unchanged.
Union alternatives are matched independently. A destination may resolve an unused
alternative away; accessing that alternative, taking a whole union value, or
accessing padding refuses the fold. No sign-changing or pointer-changing casts are
invented. A union destination cannot introduce named storage over source padding.

Member paths are edited at their original positions through explicit casts, simple
typed pointers, parenthesized dereferences and outer array indexing. Scalar array
members retain their bounds and dynamic indices. Ambiguous/shadowed declarations,
by-value local type uses, attributes/bitfields, conditional members, duplicate local
typedefs, typedef dependencies, and expressions whose changed member base cannot
be resolved produce holds. This is deliberately a restricted C reader; compile
proof is required even for a successful structural match.

Layout equality does not establish an object's role. An unambiguous record target
with the same merged provenance class may be selected automatically. Other targets
require an explicit `--select`, even when only one layout matches. Multiple record
targets in the same class also need selection. The pilot's selections reuse existing
type names after checking the source's role; they introduce no new names.

## Census

`census` scans only `src/{dungeon,town,main,slus,ovmovie}/*.c`, reads the existing
`ledger/struct_census{,_structs}.json`, `ledger/records.json`, and module/row ledgers,
and writes:

- `classes.tsv`: ranked merged classes, current local type and row counts, eligible
  local types, candidate and unambiguous row counts, historical hard conflicts,
  target counts, module counts and refusal counts.
- `candidates.jsonl`: per-local source provenance, size/alignment, candidate field
  maps, unused union alternatives, selection authority and refusal reasons.
- `summary.json`: totals and catalog parser holds.

`unclassified:*` means the current row/type pair has no historical census entry;
these are never assigned a fabricated merged class. Historical local/parameter
classes are kept verbatim. Candidate counts describe layout compatibility, not
approved semantic selections or byte-exact migrations. `.ignore` protects the
potentially large details from recursive agent searches.

## Semantic record header names

```sh
python3 tools/consolidate/consolidate.py --root ROOT rename-record \
  Rec_D_80000000 SemanticName --evidence knowledge/path/to/evidence.md \
  --confidence medium --out OUT/record_package
```

The evidence file must exist inside ROOT. Type names must be PascalCase and unused.
The package creates `include/records/SemanticName.h`, replaces the old header with
an include shim and macro alias, preserves both typedef and `struct Rec_D_...` uses
in either include order, updates the existing record metadata without discarding
its class/member-path evidence, and appends `ledger/type_unification.jsonl`.
The macro lives only in the legacy shim; new consumers include the canonical header.
This changes C type spellings, not linker symbols, so `config/names.tsv` is untouched.

`tools/gen_records.py` preflights the journal and preserves semantic records and
shims. It refuses changed canonical/shim hashes before writing any generated header.
Human changes must reconcile the stored metadata before record regeneration.

## Guarded packages and validation

`apply.py --root ROOT` defaults to dry-run. `--live --dry-run` is accepted and remains
a dry-run. Every payload and destination has a SHA-256 guard; dependencies are guarded
too. All guards are checked before mutation. Application is idempotent, refuses path
escapes and symlink destinations, and restores prior bytes if a replacement fails.
Generated packages are candidates, not automatic proof or landing authorization.

Run `python3 -m unittest discover -s tools/tests -p test_typefold.py -v`. Before
landing a content package, run `tools/verify.py` on every changed row, the standard
`tools/build/gate_all.py` checks on affected windows in an isolated gate build, the
SLUS SHA-1 gate if SLUS sources/shared header contents change, and the existing
level/pin checks. Certified members require certificate renewal in the transaction.
The T0 pilot's receipts and continuation instructions are in its lane REPORT.md.

---

# Historical object-consolidation drivers (round 78)

Run from a LANE COPY, not in place: the drivers treat `Path(__file__).parent.parent` as their lane directory
(outputs, candidates and census go there). To start a new consolidation lane:

    mkdir -p work/native_lane/<lane> && cp -r tools/consolidate work/native_lane/<lane>/tools \
      && cp -r tools/consolidate/objects work/native_lane/<lane>/objects

| file | role |
|---|---|
| consolidate.py | rewrite a row onto a shared object: `S[k]`, scalar `S`, `*S`, `&S`, local view-typedef members -> fields (`emit_field`); m2c's `u8 *s = &var; ((V *)s)->m` idiom -> direct or typed access (`rewrite_pointers`); data-declared code addresses -> the function name (`rewrite_funcaddr`) |
| layout.py | field layout from an access census (widths, signedness from lh/lhu, union sites) |
| drive3.py | several objects' rewrites in one text, verified once per plan (fold first, then plain) |
| drive_ptr.py | the pointer-fold driver |
| pins2.py | erase each pin alone and all together on migrated text (pin effect check) |
| objects/<var>.json | one spec per object: address, size, type, field names with evidence |

Landing: an `apply*.sh` in the lane (see work/native_lane/r78_types_pilot/apply3.sh): land.lock, sha check,
refuses pin/scaffolding growth, verify.py every row, gate_all (isolated build_ovl_gate) + SLUS SHA-1, restores
everything on any failure, resumable. Land a cross-binary sample first.
