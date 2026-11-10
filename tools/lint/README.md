# Native C lint

Requires Python 3.10+, modern GCC with **both** 32-bit and 64-bit development
headers (`gcc-multilib` on Debian/Ubuntu), and a private port clone. `--port`
points to the clone's directory containing `tools/build.py` and `include/`
(usually its `port/` subdirectory). The tool reads that clone without changing it.
No disc, port executable, generated adapters or MIPS build is needed.

From the game repository:

```sh
JOBS=4 nice -n 10 python3 tools/lint/lint_build.py --port "$PORT" --summary --check
```

`--root` defaults to this repository; `--out` defaults to `work/lint`, relative
to the working directory. Jobs are capped at four and each compiler runs at
niceness 10. Both widths always run a syntax pass and an `-O1 -S -o /dev/null`
pass: GCC needs optimization/code generation to diagnose many uninitialized
reads and bounds errors; `-fsyntax-only` alone cannot do that. Nothing is linked.
Every invocation recompiles its selected units; no previous census is trusted.

The TU list follows the port builder: `source_layout.registry` and
`row_relative`, existing physical homes, deduplicated, skipping `source_row`
placements. Flags are extracted from its top-level `CFLAGS` assignment and
appends without importing or executing the builder. Conditional coverage flags
are excluded. `-w` and the fixed pointer width are removed; the generated
header include path is replaced with the original game `include/` path.
Other flags/include order are preserved and `-O1` is enforced. No port source
or header repairs are applied. Diagnostics use the C locale.

Checks: pointer/integer conversions and casts, incompatible pointers, return
values, shadowing, uninitialized reads, implicit function declarations, array
bounds and suspicious `sizeof(pointer)` memory operations. These are warning
detectors, not a proof of correct types, callback arity, table extents or retail
byte identity. Findings still need source/retail triage before changing C.

Outputs:

- `lint_units.tsv`: selected TUs and registry rows.
- `lint_findings.tsv`: stable IDs, locations/messages, widths, phases and TU counts.
- `lint_counts.tsv`: per-class/per-subsystem counts, also printed by `--summary`.
- `lint_summary.json`: all counts, compiler, normalized flags and census metadata.
- `lint_compile_failures.tsv` and `failed_logs/`: every failed job, including
  failures outside game headers. Logs replace checkout paths with `$ROOT`/`$PORT`.
  Only logs named in the current failure TSV belong to the current census.

A finding is one **(file, function, warning class)** group, unioned across TUs,
pointer widths and phases. Global declarations use `<global>`; a header belongs
to its path's subsystem. `count` counts distinct observations, not finding groups.
Repeated syntax/flow observations are counted once. Width counts overlap.
`--summary` prints the subsystem columns and their totals, including zero classes.

`--baseline FILE` selects a baseline (default: the bundled `baseline.json`).
`--check` exits 1 if **any class's group count increases**, or if compiler jobs
fail. It also rejects changed compiler versions, flags or census size, since
those can conceal warnings. Reductions in one class cannot offset another's
increase. Ordinary runs also exit 1 on compiler failures; argument/input errors
exit 2. A successful run with existing warnings exits 0.

For a focused diagnosis, pass `--only src/subsystem/file.c` (multiple paths are
accepted). Partial runs are marked and cannot check or write a baseline.
To update the baseline after reviewing fixes, compiler upgrades or TU changes:

```sh
nice -n 10 python3 tools/lint/lint_build.py --port "$PORT" --summary \
  --baseline tools/lint/baseline.json --write-baseline
python3 -m unittest discover -s tools/tests -p 'test_lint_build.py' -v
```

Only a complete, failure-free run may write a baseline. Review its diff before
committing; do not raise counts just to silence a regression. The bundled
baseline was measured with the compiler/flags recorded in that file.

### Change closure lint (pre-landing)

Linting only the touched TUs misses a retyped prototype in a header making an
untouched caller pass an incompatible pointer. `lint_closure.py` lints every TU a
change can affect, on BASE and on HEAD, and fails on any new warning site:

```sh
nice -n 10 python3 tools/lint/lint_closure.py BASE [HEAD] --port "$PORT" --plan   # closure only
nice -n 10 python3 tools/lint/lint_closure.py BASE [HEAD] --port "$PORT" --jobs 2
```

The closure is: changed registered TUs (and the TUs that `#include` a changed `.c`
fragment); TUs that include a changed header, transitively (one scan of `src/` and
`include/`); and TUs that reference (call, install, take the address of) any function
whose declaration or definition text changed, including users of header macros or
inline bodies that name it. A header whose include closure is larger than `--cap`
(default 300) contributes only the includers that reference an identifier its
changed lines declare (function, field, typedef or macro name); the output says
which headers were capped, and `--full` covers the rest. HEAD defaults to the
`--root` working tree; a named HEAD revision that differs from it is extracted with
`git archive` (only `src/` and `include/`), as BASE always is. The TU list comes from
the `--root` registry, and renamed files are compared under their new names.

Both sides compile the same closure with `lint_build.py`'s flags. Findings group by
(file, function, warning class) as above; the gate compares the number of distinct
warning **sites** in each group, so a header warning seen through one more including
TU is not a regression, while one more bad argument in the same function is. Exit 1
lists each group with new sites, and any compiler failure HEAD has that BASE did not.
Renaming a function moves its warnings to a new group, so a rename also fails; the
output then prints a `hint: possibly OLD renamed` line when a BASE group of the same
file, class and site count vanished; a confirmed rename is not a regression.

`--full --base-census DIR` runs the complete census on the `--root` checkout instead
and compares it with a saved BASE census (the `lint_findings.tsv` and
`lint_summary.json` of an earlier run; compiler, flags, modes and phases must
match). `--save-census DIR` stores this run's census when it passes, as the base
for the next landing. A full census takes about four minutes at four jobs.

### Union ledger integrity

`ledger_integrity.py BASE` checks `ledger/unions.jsonl` against BASE:

- **loads** (always gating): the number of rows with non-zero per-member `loads`
  must not drop, and no row with non-zero loads on BASE may become all-zero (what a
  regeneration that drops the field does). A missing field counts as zero.
- **retired_to_cast sites**, over the whole ledger: each `path:line[,n] CAST ...`
  entry must name an existing line that contains CAST (whitespace ignored). CAST is
  the first cast spelling after the location: `(s16)`, `(u16 *)`, `(S_x *)` or
  `*(u8 *)&`. `,n` with n greater than the line is a second line, which must hold
  CAST too; a smaller n is a span of n lines from the line. `{site, cast}` objects are
  checked the same way. Entries without `path:line` (`path (former member sites)`,
  `path (u16) (cast gone)`) are notes; `path:line` without a cast only needs the
  line.
- **field rule**, on every entry that holds its cast: the cited span (the line or
  lines, the `,n` lines, plus the next line after a pointer cast or a cast that ends
  its line) must reference the row's field, `->field` or `.field` for the last
  component of the row's path. Accepted classes: `field`; `alias` (a named member of
  the row such as GridPoint `x`/`y`, or a field in the same declarator list as the
  row's, `u16 angle_x, angle_y, angle_z;`); `named` (the entry's own text names the
  referenced member: `(u16) value cast of y`, `(s16)effect->ticks_left`, a dict
  entry's `to`); `renamed` (the path is `unk_XX`/`field_XX` and the cast applies to a
  member that a record of the cited file, per clang record layouts, places at offset
  XX); `typedef` (a typedef or variable row, path == owner, whose span names the
  owner or a member declared with that type). Reported only: `renamed?` (a
  differently named member whose offset could not be checked), `typedef?`, `nofield`
  (the cast applies to a local, an array element or a call). Failing: `wrong`, a cast
  of another member stands on the line, the row's field and its aliases are nowhere
  in the span, and no rename is possible (every cast is on an `unk_XX` member, the
  owner's record in the row's file still declares the field, or the layouts place
  the member elsewhere). `--no-layouts` skips clang; renames are then `renamed?`.
- `--fail-new` fails on entries stale or `wrong` on HEAD that were neither on BASE
  (same entry, BASE text, HEAD's record layouts); `--fail-all` fails on every stale
  or `wrong` entry; with neither, sites are reported only. `--list` also prints the
  report-only classes.
- **weak evidence** (report only): retired rows with load data, by how many mapped
  loads (lb, lbu, lh, lhu, lw; stores never vote) they rest on: fewer than 5, and
  exactly 1, for the whole ledger and for rows newly retired since BASE.

`--rederive` proposes current lines for stale and `wrong` entries: it follows each
file's history from the newest commit where the entry held (cast and field), through
the diff to the current text, or else takes the nearest line holding that cast; a
line that fails the field rule is never chosen. When no such line is left (for
example a retype removed the cast), the line number is dropped and the entry ends
`(cast gone)`. Each proposal is labelled (`history`, `history-renamed` when the line
passes only through a proven rename, `history+field`, `field`, `gone`) for review;
`--write` applies them. Only `retired_to_cast` changes.

```sh
python3 tools/lint/ledger_integrity.py BASE --fail-new
python3 tools/lint/ledger_integrity.py BASE --rederive          # review, then --write
python3 -m unittest tools.lint.test_lint_closure tools.lint.test_ledger_integrity
```

### Recommended landing order

1. In the batch finalize step, after the layout, debt and union checks: run
   `lint_closure.py BASE --port "$PORT"` on the batch root (BASE = the master commit
   the batch lands on), then `ledger_integrity.py BASE --fail-new` (it replaces a
   check limited to the rows a batch changed, and also guards `loads`). Re-derive
   stale lines with `--rederive` on the batch tree; line numbers recorded on a branch do not
   survive merges.
2. After each landing (or batch of landings): `lint_closure.py BASE --full
   --base-census PREV --save-census NEXT --port "$PORT" --jobs 4`, which catches
   anything a capped closure skipped and leaves the base for the next landing.
3. `lint_build.py --check` against `baseline.json` is the long-term ratchet. It
   fails until a reviewed `--write-baseline` records the current counts; until then
   the per-landing no-increase gates above are what stop warning growth.

## Readability debt ratchet

`debt_check.py` is a dependency-free lexical census of every physical
`src/**/*.c` file, including merged translation units and unregistered source
fragments. It shares the function, token and pointer-cast recognizers from
`tools/readability/score.py`; it does not compile or preprocess C. Header
ownership and layout equivalence still require review.

```sh
nice -n 10 python3 tools/lint/debt_check.py --summary --check
python3 -m unittest discover -s tools/tests -p 'test_debt_check.py' -v
```

Each `(file, definition symbol, occurrence)` has a separate record. File-scope
code uses `<global>`. The classes are:

| Class | Unit |
| --- | --- |
| `local_externs` | Explicit `extern` declarations in C files, including block scope, plus bare file-scope function prototypes. Each declaration counts once; static prototypes, typedefs and definitions do not. These are decision-74 folder-header ownership candidates. |
| `generated_layouts` | Distinct `S_XXXXXXXX` or `S_XXXXXXXX_suffix` names per scope, including `S_func_XXXXXXXX` variants. A struct tag and typedef alias for the same view count once in that scope. |
| `m2c_macros` | `M2C_` identifier occurrences, plus actual `#define M2C_...` directives. |
| `goto` | `goto` tokens. |
| `volatile` | `volatile` tokens. |
| `pointer_casts` | Spelled pointer casts recognized by the existing readability lexer. |
| `sign_views` | Lexical source member accesses named `s`, `u`, `as_s8/u8/s16/u16/s32/u32`, `whole`, `signed_whole`, `signed_byte`, `halves`, or `signed_bytes`. These are candidates; a member name alone does not prove a signedness pun. |

Comments and quoted contents do not count. Cast density is the ratio of
pointer casts to nonexempt C tokens. The TSV prints casts per 1,000 tokens for
inspection; density never fails a check. Removing declarations or other tokens
may increase density while the absolute cast count stays constant or decreases.

`--summary` also reports pointer casts contributed by file-local macro bodies
and by macros from reachable `include/` headers, beside the lexical
`pointer_casts` class. `--macro-casts` requests the same two reports without
printing all class totals. `debt_macro_casts.tsv` and
`debt_header_macro_casts.tsv` give the use sites. Header includes are followed
transitively; conditional `#if` branches are not evaluated, so these are
lexical exposure counts. A local redefinition or `#undef` masks a header
macro at later sites. Both macro totals are recorded in `report_counts` in
the baseline, but remain report-only: `--check` does not ratchet them. Do not
add the three counts into a single debt number.

The summary splits `sign_views` into `s_u`, `as_signedness`, and
`other_width_views`. It also reports unions in `src/` and `include/` with
immediate signed and unsigned integer members of the same width. The union
count and the total of all braced union definitions are no-growth ratchets in
`--check`. `debt_signedness_unions.tsv` lists the signedness sites.
`debt_bad_label_unions.tsv` lists simple union members with an unsigned `s`,
a signed `u`, a pointer or function pointer given an `s` or `u` label without
matching pointee signedness, two distinct pointer member types, or duplicate
declared types. The baseline records those site
identities; `--check` rejects a new bad-label site while allowing a known one
to be repaired. A site is keyed by file, trailing union field name, and its
ordinal among that file's same-named unions. Inspect the finding before
relabeling: lexical types and labels do not establish the original data model.
For a batch that changes a union member access, run
`python3 tools/typing/union_relabel_check.py --base HEAD` before committing.
It reports old member spellings left elsewhere in each edited file for a
whole-file audit. For two-way `s`/`u` swaps, it checks unchanged access lines;
an inline union declaration swap without a corresponding use-site edit is
also reported.

The summary inventories braced struct/union typedef aliases as well. It counts
unique non-`S_` aliases containing an eight-digit hexadecimal address across
`src/` and `include/`, and named non-address typedef declarations in `.c`
files used by exactly one function in that file. `debt_view_inventory.tsv`
shows each source typedef and its function users. These report-only counts
do not judge whether a named local view is appropriate.

### Readability and prototype-gap counts (report only)

`debt_check.py --summary` also prints nine report-only lines computed by
`tools/lint/readcounts.py`. They have no baseline and `--check` never fails on
them; they say how far the tree is from one canonical signature per function
and from code a reader can follow. Comments and string contents never count.
Per-file facts and the whole aggregate are cached under the report cache
(`readcounts/`), keyed by content hashes of every `src/**/*.[ch]` and
`include/**/*.h` file plus the two tool files, so an unchanged tree costs one
read-and-hash pass. The item lists land in `build/readcounts/` (or
`--readcounts-out DIR`), never in the tracked tree or `work/`:

| Summary line | Meaning | List |
| --- | --- | --- |
| `prototype names multi-signature` | Declared function names (non-static, every prototype, block-scope extern and definition in `src/` and `include/`) with more than one distinct signature after `decl_agreement` normalisation (`()` is skipped, as it agrees with anything); the declaration sites of those names; how many also disagree beyond `()` and `void *`. | `signature_conflicts.tsv` |
| `declaration sites per declared name` | Mean declaration-plus-definition sites per name, names in more than one site, and the top five names. | `signature_conflicts.tsv` |
| `duplicate function definitions` | Non-static names defined more than once, split into identical bodies (same normalised head and body text) and differing bodies. Placed copies in different overlays are legitimate; the differing count is the one to triage. | `duplicate_definitions.tsv` |
| `address-named tokens` | `func_8xxxxxxx` and `D_8xxxxxxx` identifier tokens in code (and distinct names), plus how many more sit in comments. | `address_func_tokens.tsv`, `address_data_tokens.tsv` |
| `unk_/pad_ member tokens` | Identifier tokens starting `unk_` and `pad_`. | `unk_tokens_by_file.tsv`, `pad_tokens_by_file.tsv` |
| `struct typedefs in .c files` | `typedef struct [tag] { ... } Name;` in `.c` files, copies sharing an exactly equal body, and type names carrying several different bodies. | `struct_duplicate_bodies.tsv`, `struct_names_with_several_bodies.tsv` |
| `duplicate #include lines` | Extra copies of the same `#include` within one file. | `duplicate_includes.tsv` |
| `stale tool comments` | Comments carrying lane or tool stamps (`cfail-repair`/`tf7-phase`, evidence banners, tool-written header notes, cohort/group ids, lane receipts, review pending, `MECHANISM:`); a comment counts once per tag. | `stale_tool_comments.tsv` |
| `placeholder identifiers` | `argN`, `var_*` and `temp_*` identifier tokens in code, and how many are named only in comments. | `placeholder_identifiers_by_file.tsv` |

Unit tests: `python3 -m unittest tools/lint/test_readcounts.py`.

### Bridge-cast ledger (decision 75)

`ledger/bridge_casts.jsonl` preserves 264 rows from the four legacy TSV
layouts. Each row has a stable `site_id`, physical `file`, `function`,
`cast_text`, same-text `ordinal` in that function, `reason`, `evidence`,
`status` (`open` or `retired`), and `retired_by`. Run
`python3 tools/lint/debt_check.py --bridges` to verify that every open literal
still occurs in the named function at least as many times as its ordinal.
This check is independent of the full debt census.

Decision 75 retires a *cast site* when the spelling is absent from its current
function; the row stays in the ledger with a reason. A missing spelling does
not prove its underlying type or callback contract was repaired. The import
marks these rows `retirement_kind: literal_absence` and
`semantic_status: unresolved`. Legacy rows that explicitly described an
initializer mismatch with no cast are retained as
`retirement_kind: conceptual_no_cast`; they also leave the semantic question
unresolved. A later owner may change `semantic_status` only with source and
byte evidence. The original line and status remain as historical fields, not
as current-line assertions. A new bridge is `open` until its exact text is
removed; retirement keeps its row and records what removed it.

### Prototype consistency

`python3 tools/lint/debt_check.py --prototypes --check --out OUT_DIR` reports each
uniquely defined function with a declaration that disagrees in canonical
return type or explicit arity. The scan uses the header planner's typedef
visibility and container binding, so `s16`/`short`, `s32`/`int`, and
`struct X *`/`X *` aliases compare equally. Unprototyped `()` declarations
do not assert an arity. `include/modules/`, `include/sdk/`, and names already
recorded in `ledger/prototype_floors.jsonl` are excluded. The separate
`proto_baseline.json` records known site IDs; `--check` rejects a new one.
`--prototypes --write-baseline` updates the known set after a reviewed change. The report
also inventories names with multiple definitions. Equal canonical signatures
and equal masked bodies are marked `same_body_copies`; different signatures
are `different_contracts`; equal signatures with different bodies remain
`identity_review` until creator/caller evidence can classify them. Counts are
triage leads, not permission to change a call ABI without byte proof.

`--baseline FILE` defaults to `tools/lint/debt_baseline.json`. `--check` fails
on any increased class total, file class count, or function class count.
Improvements in another class, file or
function cannot pay for new debt. New scopes start at zero debt; removed scopes
are allowed. A definition/file rename retaining debt needs an explicitly reviewed
baseline key migration. The sparse baseline records only files and scopes with
nonzero debt. An absent file, function or class count means zero. The TSV census
still includes every file and function. Invalid baseline records, unmatched
delimiters and malformed markers fail closed.

Baseline schema 3 groups `by_file` by directory, then filename. A file record is
`[total_tokens, scopes]`; each scope is `[tokens, counts...]` in the order listed
in `classes`, with trailing zero counts omitted. File class counts are the sum
of its retained scopes; `by_class` retains the totals for all seven classes.
Zero-debt scopes (including `<global>`) need no record, but their tokens remain
in `total_tokens` to preserve the census denominators. Keys are sorted,
with one physical file per line and no source line numbers. `bad_label_sites`
stores the existing union findings, and `report_counts` stores macro casts,
signedness-union totals, the all-union total, and view inventory totals. The
two union totals are ratcheted.
The packed scopes avoid storing paths and file/scope totals twice.

A comment of the exact form `/* BYTES: <one-line reason> */` exempts its adjacent
code site. A leading marker covers the following statement, declaration or
braced control arm; a trailing marker on a statement's line covers that
statement. A marked `do { ... } while (0);` exempts the wrapper shell; its body remains
measured so ordinary debt inside a recorded scheduling fence stays visible.
The enclosing function remains checked; a marker on a whole definition is
refused. Only add markers where recorded retail
evidence supplies the reason; the marker itself does not establish evidence.
Exempt tokens are removed from both cast numerator and density denominator.

`--root` defaults to the repository; `--out` defaults to `work/debt`. Outputs
are `debt_functions.tsv` (per-function PASS/FAIL with `--check`),
`debt_files.tsv`, and `debt_summary.json`. `--only src/path.c ...` is a focused
census and cannot check or write a baseline. Source reads are capped at 4 MiB
and source symlinks are refused. No work directory is scanned.

After reviewing reductions or an intentional baseline key migration:

```sh
nice -n 10 python3 tools/lint/debt_check.py --summary \
  --baseline tools/lint/debt_baseline.json --write-baseline
```

Only a complete census without parse/marker errors may write a baseline.
Review its diff; raising a count to silence a failure defeats the ratchet.

`tools/land_make.sh` runs this complete baseline check after applying patches
and the existing changed-source debt scan, before layout checks and configure.
Failures leave the applied tree and `build/landing/debt-baseline.log` for review;
no build or commit follows a failed check.

## Callback and cross-unit soundness

`soundness_check.py` shares this tool's TU census and original-header flag
extraction. It never imports the private builder or repairs game source.
Use a private port checkout at the version recorded with your baseline:

```sh
nice -n 10 python3 tools/lint/soundness_check.py --port "$PORT" \
  --out work/soundness-gcc --mode callbacks --cc gcc
nice -n 10 python3 tools/lint/soundness_check.py --port "$PORT" \
  --out work/soundness-clang --mode callbacks --cc clang
nice -n 10 python3 tools/lint/soundness_check.py --port "$PORT" \
  --out work/soundness-lto --mode lto --cc gcc
```

Both modes use 32-bit pointers, `-fwrapv`, at most four compiler workers and
niceness 10. GCC enables `-Wcast-function-type`; Clang additionally enables
`-Wincompatible-function-pointer-types` and `-Wcast-function-type-strict`.
LTO compiles every selected unit and materializes a relocatable GCC LTO link
with `-Wlto-type-mismatch -Wodr`. Undefined externals may remain unresolved;
duplicate definitions and compilation/link failures fail the run. Overlay
namespace conflicts require triage; the tool never suppresses them. This is
a type diagnostic link, not a runnable port or proof of retail byte identity.

Each run writes findings, failures, sanitized logs and a summary. Keep the
output ignored and private: it includes objects. `--only PATH...` is diagnostic
and cannot check or establish a baseline. Add `--baseline FILE --check` to
ratchet a reviewed full run; use `--write-baseline` to record it. Failed runs
cannot write a baseline. Baselines pin compiler, flags and selected TU paths;
every new diagnostic identity fails even if the total count stays equal. Schema 2
also pins occurrence counts for each identity, so another identical bad cast in
the same function fails. Reductions remain allowed.
A missing baseline is an error, never an implicit clean starting point.
Run `python3 -m unittest discover -s tools/tests -p test_soundness_check.py -v`
for ratchet and real 32-bit LTO detection tests.

Clang uses explicit `-Wno-error=` settings for the pre-existing GCC diagnostic
classes (integer/pointer conversions, implicit declarations and return types).
Those warnings remain in logs; the existing lint census owns their ratchet.
Callback warnings remain enabled. Other Clang errors still fail the census.
Clang function ownership is recovered with the existing C declaration scanner,
so identical warnings in different functions retain separate identities.
`lto-symbol-kind` also records GCC errors that redeclare a function as data or
vice versa. Raw logs are preserved in full beneath the ignored output directory.
The header-group manifest also records eight reviewed code-address aliases.
The native compilers require each target to be a function and each alias to have
a compatible function type, catching arity, return and parameter regressions even
when both names are unused. `test_header_types.py` exercises valid pairs and
wrong arity, return, parameter and function/data pairs with GCC and Clang.

The flag reader accepts both legacy literal `CFLAGS` lists and the shared
`native_units.cflags` API. It selects GCC or Clang flags for the requested compiler,
with O1, sanitizers off and coverage off; pointer-width and diagnostic options
remain owned by the lint commands. Only the flag function is evaluated: builder
startup, module startup and disc extraction are not executed. Compiler, flags,
TU selection and diagnostic occurrence pins remain enforced by the existing baseline.
Run `python3 -m unittest discover -s tools/tests -p test_native_flag_api.py -v`
for compatibility and startup-side-effect regression checks.

The bundled `soundness_gcc_baseline.json` records the reviewed 6,013-TU GCC
callback census (24 diagnostic groups, 29 occurrences); it is not an LTO or Clang baseline.


### Aggregate header type checks

Run `python3 tools/lint/header_types.py --out build/header_types.json` to compile
reviewed owner headers together with their imported data declarations under both
32-bit GCC and Clang. Every group in `header_type_groups.json` must compile with
zero errors; the reviewed baseline is a clean group list, not an allowlist of
conflicting declarations. The first group joins resident window, message, menu and VM
owners with `slus/data.h`. It guards eleven repaired function-as-data declarations,
including three unused extern conflicts that the LTO census did not emit.
Existing owner prototypes supply all types; this tool synthesizes no prototypes.
Warnings remain the responsibility of `lint_build.py` and the callback census.
This check covers the listed aggregates, not every declaration in the game.

Run `python3 -m unittest discover -s tools/tests -p test_header_types.py -v` for a
real-compiler regression that rejects an unused function/data disagreement and
accepts a separate data symbol. New groups must first compile cleanly under both
compilers. Do not add a conflicting declaration to an exception baseline.

The `town_callback_owners` group joins the map, person and player callback
owners, including five registered code-address aliases. Each alias has the
same prototype as its registered handler; no data object is implied by an
address spelling. The LTO link honors `--jobs` as well as the compile phase,
with a maximum of four workers.

The `audio_command_owners` group joins the command FIFO feature with its audio
and entity imports. The owner declares one count halfword and 32 payload
halfwords. `test_resident_bit_return.py` compiles a real result-using caller
with GCC O0, GCC O2 and Clang O2 to guard the resident-bit query return contract.

## Declaration agreement

`tools/lint/decl_agreement.py BASE [HEAD] --fail-new` compares every declaration of
each function whose declaration or definition changed (file-scope prototypes, block-scope
`extern` lines, other headers) with the HEAD definition, after normalising whitespace,
parameter names, `struct` tags, scalar typedefs and array parameters. A disagreement that
did not exist on BASE fails. The warning census cannot catch this case: a stale local
prototype leaves the same GCC diagnostic at the same site. `lint_closure.py` runs the check
after its warning gate (`--no-decl-check` skips it). Tests: `python3 -m unittest
tools.lint.test_decl_agreement`.

Data objects get the same pass. Every `extern` object declaration (file scope and block
scope) and every non-static file-scope definition of a name under `src/` and `include/` is
grouped by name; raw address names (`D_80123456`) group per overlay directory because every
overlay reuses the addresses. Element type and dimensions compare after the same
normalisation (`T x[]` agrees with `T x[N]`, qualifiers and `struct` tags do not matter, an
extent that is an expression is not evaluated). Classes: `incompatible type` (different
element, pointer against array, different rank), `size mismatch` (same element, different
known extent, or an extent that differs from the size in `config/slus_006.14.symbols.txt`,
the only per-object size source: other objects have no recorded size, so only declarations
are compared with each other) and `element type only` (same width, opposite sign). A name
fails `--fail-new` (and `lint_closure.py`) when it disagrees on HEAD and did not on BASE, or
gained a declared type BASE lacked; `--no-data` skips the pass. `decl_agreement.py
--data-census` lists every disagreeing name in the checkout, writes `build/decl_data.tsv`
(name, address from `config/names.tsv`, class, then every declaration site, definition and
symbol size with its type) and prints the top names; `debt_check.py --summary` prints the
count as the report-only `data_decl_disagreements` line.

Tool notes (landing-review gaps): `debt_check.py --summary` keeps its report cache under
`build/debt_report_cache` (or `$XDG_CACHE_HOME/debt_check/...`, or `--cache-dir`), never `out/`, and `/out/` is
git-ignored so a stray `out/` cannot fail the lander's clean-worktree check.  Sign-view counting includes named
`unsigned_*`/`signed_*` member views (`unsigned_parts`, `signed_halves`, ...) as `named_sign_views`.
`decl_agreement.py` reports `void_pointer_stale` (a `void *` declaration of a record-pointer definition) and fails on
it only with `--fail-void`; `lint_closure.py` reuses its BASE tree for the check.  `ledger_integrity.py --rederive`
moves lines by `git diff` hunk offsets before any text search.

Sign decisions (R17): raw lbu/lhu counts are a biased vote because a signed field also compiles to lbu/lhu in
increments, masks, same-width copies and shifts.  `tools/typing/sign_trial.py include/x.h::Record.field` flips the
declared sign, strips the casts to the new type on that field and recompiles the users through the recipe's
compiler cell, reporting per function identical or differs plus the recommendation (FLIP_CLEAN, FLIP_BETTER, TIE,
KEEP); `--check-removal` removes each minority cast alone and lists the NO-OP ones (`--identity` adds casts to the
declared type itself, `--stores` casts on the whole stored value of a plain store).  Casts are found on any base the
resolver can type, including cast chains `(s16)((T *)p)->field` and stacked casts `(u16) (s16)r->field`, and a field
spec may name a member of nested anonymous structs and unions (`Record.word.parts.high`).  `--place` counts the casts
the opposite declaration needs: it flips the field, strips every 8/16-bit cast on it, restores the old meaning in each
function whose code differs (uncast reads take a cast to the old type) and prunes those casts one at a time while the
code stays identical (`--apply` leaves the flipped tree written when every function is identical); compare its count
with the casts `--check-removal` keeps under the current declaration.  Run it in a private clone with
`--build-root` pointing at a tree that holds build/.state and toolchain/ (a run takes minutes on a busy box).
`union_census.load_check` now votes per access width (a byte view's lbu no longer counts for a halfword) and reports
`biased` when an unsigned declaration's lead rests on lbu/lhu loads with no unsigned-only consumer (access_sites.tsv
gains a `compound` column).  `ledger_integrity.py --list` shows evidence prose load numbers that differ from the row's `loads`.
