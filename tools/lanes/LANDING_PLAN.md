Landing process contract
========================

A plan requires version=1, reviewer, commit_message and a nonempty list of dotted
unit_modules. commit=false permits reviewer=pending. Every package/review entry
must exist before replay; package source files may install new unit modules.
Review keys must be in the current roster or a package's modules.entries.json.
Missing installed keys and mismatched review-script reviewers fail before builds.

`--preflight` runs the same mutation, review, dotted and discovery test steps as
the live transaction, then registry/index, production-window/census invariants,
levels, graph, status and scrub. It creates no landing authority. Tests execute
from the canonical tools/tests layout, with sibling imports available under both
entry points. `unit_timeout` defaults to 60 seconds; plans that intentionally run
the entire repository suite may set a larger test timeout. Byte-gate and
certification checks retain their own timeouts and MATCH requirements.

Package preflight automatically discovers tests installed by files.json under
tools/tests/test_*.py. tests.json can declare additional unit_modules and
discover_patterns. A Python audit hook blocks accidental canonical-root reads,
writes and subprocess commands, including errors a test catches. Shared
compiler/venv/baserom/bin inputs remain readable. This guard is for trusted tests;
it is not a sandbox for adversarial native code. Pending packages which guard
the same complete file are rejected before replay. Append-only records do not
conflict merely because they append to one ledger. Package bytes and the pending
queue must remain unchanged throughout the screen.

The final transaction uses incremental gate_all by default. `gate_all: "full"`
or a changed gate/compiler/fingerprint/build input forces --all. raw and rowbase
changes are hashed by inputs_sha and do not force --all. Both modes log elapsed
time and reasons. Every recorded certificate renews once, using its own recorded
reviewer. SLUS retains the forced full-image SHA-1 and pinned-recipe checks.

Batches
-------

A plan may include packages, coherence cells and promotion bodies together:

    "coherence": [{"tag": "round112", "lane": "../lane_with_cells"}],
    "promotions": [{"id": "dungeon/func_XXXXXXXX",
                    "body": "candidate.c", "before": "64 hex SHA256",
                    "source": "batch"}]

Coherence lanes contain cells.jsonl and out/<container>/<function>.c plus its
.c.base_sha. Promotion before hashes bind current source bytes. These input
stages use a private canonical-layout clone so legacy verify.py and
common.set_row_cfg never operate on live scorer roots. Coherence uses the same
retail verifier, landing_refusal and recipe-switch rule-2 check as the standalone
script; every requested cell must complete. Already-landed identical inputs are
no-ops. Promotions use unchanged promote_text, including its window gates. A
refusal rolls back the entire outer transaction, including earlier packages.
The outer lander then runs all production gates and one certificate renewal.
No stage grants byte or review authority on its own.

Standalone land_coherence always rebuilds EXP=gate before its production gate.
--transaction-inputs is an internal protocol for the private batch clone; do not
invoke it as a standalone live landing. It intentionally does not certify or
commit. All production validation comes from the enclosing transaction.

Isolation
---------

`--live --isolated` (or plan isolated=true) leaves build_ovl in place even during
rollback, and builds only build_ovl_gate. Existing tool lanes qualify automatically when lane.pid matches the codex pid
and BRIEF.md explicitly says both "work ONLY there" and "Prove everything in a
lane-owned scratch tree". This uses the owner-provided task scope, plus the same
descendant checks below. For other launchers, a lane may be attested with
work/native_lane/<lane>/isolation.json:

    {"version": 1, "pid": 12345,
     "roots": ["work/native_lane/<lane>/b"]}

The pid must be that live codex process, and each root must be a nonsymlink
scratch directory inside the lane (the lane directory itself may be declared for
editor/tooling processes). Codex -C REPO launchers are identified through
their -o/--output-last-message lane output. All current descendants' cwd and open
file descriptors are checked for shared scorer/gate use. Stale explicit receipts,
missing pid-bound scope evidence, and live scorer/gate activity remain busy. Launchers must
maintain the isolation contract for the entire landing; a cwd alone is not one.
