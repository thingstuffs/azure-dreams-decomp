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

Comments and quoted contents do not count. Cast density is the ratio of
pointer casts to nonexempt C tokens, compared by exact cross multiplication.
The TSV prints casts per 1,000 tokens for inspection. A reduction in function
size can increase this density even if its cast count stays constant; review
that change explicitly.

`--baseline FILE` defaults to `tools/lint/debt_baseline.json`. `--check` fails
on any increased class total, file class count, or function class count, and on
increased file/function cast density. Improvements in another class, file or
function cannot pay for new debt. New scopes start at zero debt; removed scopes
are allowed. A definition/file rename retaining debt needs an explicitly reviewed
baseline key migration. The sparse baseline records only files and scopes with
nonzero debt. An absent file, function or class count means zero. The TSV census
still includes every file and function. Invalid baseline records, unmatched
delimiters and malformed markers fail closed.

Baseline schema 2 groups `by_file` by directory, then filename. A file record is
`[total_tokens, scopes]`; each scope is `[tokens, counts...]` in the order listed
in `classes`, with trailing zero counts omitted. File class counts are the sum
of its retained scopes; `by_class` retains the totals for all six classes.
Zero-debt scopes (including `<global>`) need no record, but their tokens remain
in `total_tokens` so file cast-density comparisons stay exact. Keys are sorted,
with one physical file per line and no source line numbers. This avoids storing
paths and file/scope totals twice while keeping the baseline below 600 KB.

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
The bundled `soundness_gcc_baseline.json` records the reviewed 6,004-TU GCC
callback census (24 diagnostic groups, 29 occurrences); it is not an LTO or Clang baseline.


### Aggregate header type checks

Run `python3 tools/lint/header_types.py --out build/header_types.json` to compile
reviewed owner headers together with their imported data declarations under both
32-bit GCC and Clang. Every group in `header_type_groups.json` must compile with
zero errors; the reviewed baseline is a clean group list, not an allowlist of
conflicting declarations. The first group joins resident window, message and VM
owners with `slus/data.h`. It guards ten repaired function-as-data declarations,
including three unused extern conflicts that the LTO census did not emit.
Existing owner prototypes supply all types; this tool synthesizes no prototypes.
Warnings remain the responsibility of `lint_build.py` and the callback census.
This check covers the listed aggregates, not every declaration in the game.

Run `python3 -m unittest discover -s tools/tests -p test_header_types.py -v` for a
real-compiler regression that rejects an unused function/data disagreement and
accepts a separate data symbol. New groups must first compile cleanly under both
compilers. Do not add a conflicting declaration to an exception baseline.
