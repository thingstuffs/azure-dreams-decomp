# Interrupted T27 recovery — 2026-09-12

The T27 process stopped after its last journal record at 08:21:20 UTC. No T27 workers
were running when checked. The original launch and sharded restart were incomplete.

Recovered **27 changed functions, 49 pins removed, one newly pin-free function**, with
no added scheduling fences or detected fake dependencies. The abandoned run accounted
for 48 removals; a bounded T2/T20 cleanup on those rows removed one more pin. Three
source changes had been written before their journal entries:

- `dungeon/func_80083E28`
- `dungeon/func_8008EB10`
- `town/func_8096E26C`

All 27 original recovered candidates passed independent per-row exact verification and
the landing source checks. After T2/T20, all 16 changed overlay windows passed; all
2,172 current window proofs are MATCH. The 884-TU SLUS SHA-1 gate also passed. Source
hashes and debt counts are recorded in `ledger/sweeps/t27_recovered.jsonl`; the original
371-record T27 journal is retained separately and must not be mistaken for exhaustive
coverage under the improved search settings.

The patch, pre-cleanup sources, original journal, launcher scripts, logs and verification
results are preserved in ignored `work/pin_recovery_20260912/`. Thirty-four abandoned
`/tmp/screen_*` directories from the two interrupted launches were copied and hash-checked
before removing the stale originals. Their 33 C files contained 32 potential improvements
relative to current source; all 32 were checked and none was exact. They remain archived
under `interrupted_screens/`, with results, as failure evidence. Active compiler directories
and unrelated temporary files were left alone.

A separate historical screen replay checked 280 source pairs across three landing commits:
no compilation errors and one nonzero screen difference whose before/after sources both
independently verified exact (`dungeon/func_8187BB80`, difference 2). The report and assembly
listings are in `work/pin_recovery_20260912/screen_replay.json`. The regression replay script
is `tools/tests/replay_pin_screen.py`.

Source recovery and search-tool changes are separate commits. The replacement controller
stages candidate files and writes each result atomically before notifying its parent;
it does not depend on a live Claude/Codex session for continued execution.
