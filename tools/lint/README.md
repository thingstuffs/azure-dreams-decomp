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
