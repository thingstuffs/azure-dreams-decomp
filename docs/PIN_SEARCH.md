# Durable mechanical pin search

`tools/pin_search.py` replaces the ad-hoc T27 sharded launcher for new work. It makes no
model calls. Search produces staged candidates; publication is a separate checked command.
The historical T27 implementation remains the comparison control and is available as
`--mode baseline` (the default). The family-directed search is `--mode targeted`.
Two 60-row comparisons did not establish a throughput advantage for targeted search, so
it remains an optional research mode rather than the production default.

## Run and resume

```sh
python3 tools/pin_search.py prepare --tag pins_next --mode baseline
python3 tools/pin_search.py start --tag pins_next --workers 4
python3 tools/pin_search.py status --tag pins_next
```

`start` detaches the controller into a new session, with closed stdin, a durable log, and
low process priority. Closing the launching client does not stop it. `status` compares the
recorded process identity with `/proc`, so an old “searching” file cannot impersonate a live
job. The log is `work/pin_search/<tag>/controller.log`.

If interrupted, use `start` again with the same tag. Each successful candidate is saved
immediately, and workers write atomic per-row result files before reporting completion.
Interrupted rows restart from their frozen inputs and reuse the compilation cache; saved
successes are reverified and retained. This is deterministic row replay, not serialized
beam-frontier continuation. Completed rows are reused only with the same per-row query
fingerprint; unrelated rows changing does not invalidate that reuse.

The fingerprint binds source and row configuration, tool/header/compiler/target inputs,
search implementation, census evidence and settings. A changed tool, budget or input requires
a new tag. Do not carry the old `(row, source hash)`-only T27 “done” entries into this controller.
Budget exhaustion is explicitly reported; it is not a claim that no fix exists. A larger-budget
tag can reconsider selected exhausted rows using `--ids <comma-or-newline-separated-file>`.

Defaults are 1,200 screen requests, 12 full-verifier calls, and 40 process-plus-child CPU
seconds per row. These are bounded search limits; a single in-progress tool call can take
the run slightly past the CPU threshold. Compiler screening also has a 30-second timeout.
Generated C that does not compile is a rejected mutation, not grounds to repeat the whole row.
Reference-build failures and worker exceptions remain retryable. A timeout compiling a
generated variant ends that row with `compiler-timeout`, retaining any independently verified
win and saving the variant under `timeouts/<mode>/`. This is another bounded stop, not proof
the variant cannot compile. No timed-out compilation is cached as a negative result. Inspect
that evidence before spending another identical timeout budget on the row.

## Search and acceptance

The targeted engine uses allocation, scheduling, address-form and mixed-residue families to
choose generators before generating candidates. It keeps proven general shapes and limited
exploration, distributes the row budget across groups, and defers assembler-only marker groups
so their deceptively cheap residues do not starve ordinary C pins. Fresh measured linkage
groups remain preferred; singles and nearby pairs are the fallback when the census is stale.

The cc1 assembly screen ranks candidates. Different listings can assemble to identical bytes,
so a small allowance verifies promising nonzero residues. Full verification remains mandatory
for every accepted candidate. Historical replay currently measures one such screen miss in
280 exact source pairs. Pin removal cannot add fences or detected fake dependencies, and
unscored C arms and native-source checks retain their existing protections.

Successful assembly results are compressed in SQLite caches under ignored
`work/pin_search/cache/`. The key binds the recipe, row and complete candidate text. Failures
are not persisted as negative assembly cache entries. Production tags share caches; each
pilot tag has separate cold caches for its two arms. Distinct C states are retained even if
they currently emit the same assembly, because later transformations can behave differently.

## Joint pin erasures

`--mode erasures` tests pin removal without generating C-shape mutations. Through eight
live pins it enumerates all nonempty subsets, largest first. Above eight, it tries the full
set, groups sharing a variable, each macro family, every pair and singles, subject to
the same row budgets. Variable groups include distant register/keep pairs that a
near-line pair scan misses. Successful
byte verification restarts the walk from the smaller source. The assembly screen filters
costly verification; up to two very near nonzero erasures also receive full verification.
No screen result can publish source. Existing checkpoint, identity and transactional gates
apply. Near misses are saved for mechanism research.

```sh
python3 tools/pin_search.py prepare --tag erase_next --mode erasures --ids selected_ids.txt --screens 512 --verifies 12 --cpu-seconds 20
python3 tools/pin_search.py start --tag erase_next --workers 4
python3 tools/pin_search.py publish --tag erase_next --mode erasures --workers 4
```

This is an experiment in joint-removal coverage, not a replacement for baseline search.
T2 tests singles; baseline T27 can exhaust its budget in shape search before reaching
larger subsets or distant pairs. Read the manifest and stopping reason before calling a
row exhaustive. The first batch selects small functions with 2–8 pins and incomplete
current-source subset records; historical records are scheduling evidence, not new proof.

## Fence search

Use `--mode fences` for scored scheduling fences, including functions with no ASM pins:

```sh
python3 tools/pin_search.py prepare --tag fences_next --mode fences --ids selected_ids.txt --verifies 24 --cpu-seconds 40
python3 tools/pin_search.py start --tag fences_next --workers 4
python3 tools/pin_search.py status --tag fences_next
python3 tools/pin_search.py publish --tag fences_next --mode fences --workers 4
```

The manifest fixes the mode and acceptance objective. This arm runs bounded T20 full-byte
verification directly; assembly-screen counts and cache hits therefore stay zero. It does
not call a model. Pins, fences and detected fake dependencies must each stay nonincreasing,
and pins plus fences must strictly fall. The same acceptance policy protects recovered
checkpoints and publication. Verified partial wins survive CPU/verify limits; summaries
report both pin and fence reductions. T20 settings and the added generator menu are restored
after each worker row, leaving the original baseline, targeted and standalone T20 menus intact.

The dedicated menu includes the measured `loop_test_increment` rule, which moves an
unconditional local counter increment into a do-loop comparison. It rejects control flow,
escaped or volatile locals, unknown scalar typedefs, and dependent crossed updates. Only one
of 16 measured source examples matched; this remains a narrow rule. See
[PIN_MECHANISMS_20260912.md](PIN_MECHANISMS_20260912.md).

## Publish checked source

```sh
python3 tools/pin_search.py publish --tag pins_next --mode baseline --workers 4
```

Publication refuses stale source/candidates and unfinished or retryable-error rows. An explicitly
named error can be left unresolved with repeatable `--defer <container/function>` arguments;
the publication receipt records its ID, source hash and error, and its source is not published.
Missing, stale or completed results cannot be deferred. The default remains strict.
Publication permits search-code updates since the run, but the frozen manifest and results
must retain their original identity and the compilation recipe must still match. It reruns
the candidate verifier and source checks, saves rollback copies, writes a durable transaction,
and requires the overlay and SLUS gates to succeed. Gate failure restores the transaction's
source; restart can recover an interrupted publication. Recovery refuses to overwrite a
concurrent source edit. A completed publication writes `ledger/pin_runs/<tag>.json`.

`tools/build/gate_all.py` now returns failure if any requested/current window lacks a fresh
MATCH, including a cached failure. Scripts must check command return codes. Refresh census,
levels and status after publication; apply the standing bounded T2/T20 follow-up to affected
rows and re-gate any further changes before committing them.

## Controlled comparison and family research

```sh
python3 tools/pin_search.py prepare --tag pilot60 --pilot --sample 60
python3 tools/pin_search.py start --tag pilot60 --workers 4
python3 tools/pin_search.py gate-pilot --tag pilot60 --workers 4
python3 tools/pin_search.py packets --tag pilot60 --mode targeted
```

The pilot freezes 12 historical recovery controls plus 48 rows sampled across compiler and
pin-count strata. Both arms receive identical sources and limits. Results and timing data
are in `summary.json`; physical window gates run against isolated copies of the source tree.
Pilot sources cannot be published through the production command. Changed SLUS candidates
also pass an isolated full-executable build with the pinned Ninja recipe and an explicit
final-image SHA-1 check. The baseline and targeted overlay gates have separate source/output
roots and can run concurrently within the requested worker limit.

Family packets contain at most three representatives per unresolved mechanism, compiler/extent
identity, frozen inputs, attempted shapes, stopping reasons and candidate diffs. Models should
work from these packets to identify a mechanism and build a reusable, conservatively guarded
generator with negative cases. Verify it on held-out examples, then apply it mechanically.
No model is needed for each candidate, ordinary failure, or progress poll.

Validation:

```sh
python3 -m unittest discover -s tools/tests -p 'test_pin_search*.py'
nice -n 10 python3 tools/tests/replay_pin_screen.py
```

Recovery results are in [PIN_RECOVERY_20260912.md](PIN_RECOVERY_20260912.md); the original
review and rationale are in [PIN_CLEANUP_REVIEW_20260912.md](PIN_CLEANUP_REVIEW_20260912.md).
