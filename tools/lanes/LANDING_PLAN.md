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

Both preflight commands inspect source-tree dirt before cloning. Untracked agent
outputs, staged bookkeeping and other live refusals are reported together; a
clean disposable tree cannot conceal them. They recheck source dirt at the end.
Known and explicitly declared bookkeeping may grow by appending bytes. Original
bytes must remain a prefix; rewrites, truncation, removal and aliases fail. These
files stay unstaged. Rollback preserves valid appenders in place, including their
open file descriptors, while restoring every other managed input and the index.

Package preflight automatically discovers tests installed by files.json under
tools/tests/test_*.py. tests.json can declare additional unit_modules and
discover_patterns. A Python audit hook blocks accidental canonical-root reads,
writes and subprocess commands, including errors a test catches. Shared
compiler/venv/baserom/bin inputs remain readable. This guard is for trusted tests;
it is not a sandbox for adversarial native code. Pending packages which guard
the same complete file are rejected before replay. Append-only records do not
conflict merely because they append to one ledger. Package bytes and the pending
queue must remain unchanged throughout the screen.

Preflight logs package-order hints for protected inputs and declared proof-tool
aliases (protected_links uses readlink text; protected_aliases uses repository
relative target paths). A reader of old inputs must precede their writer; a
reader explicitly guarding a writer's output follows it. Two full-file writers
and dependency cycles require a combined reviewed package. Hints grant no guard
override: actual package dry runs and applications must still pass in order.
Manifest mutates may declare record-applier targets without full-file guards.
For older Python appliers, bounded static write-path hints also name rowbase and
configure dependencies absent from files.json. Those inferred hints are advisory
and never bypass a guard or authorize a write.

The final transaction uses incremental gate_all by default. `gate_all: "full"`
or a changed gate/compiler/fingerprint/build input forces --all. raw and rowbase
changes are hashed by inputs_sha and do not force --all. Both modes log elapsed
time and reasons. Every recorded certificate is validated through module_status;
reader-invalid certificates renew, using their own recorded reviewers. New or
byte-changed certificates and changes to their referenced generated proof
directories force renewal even when the reader accepts them. The transaction's
pre-quarantine snapshot binds those bytes; identical proof copies are retained.
Non-include full-gate reasons force renewal of every certificate, covering tool
and build inputs outside either fingerprint. Include paths and the dependency
closure-unavailable reason retain selective renewal even with --all. All are
validated after renewal and again after final regeneration. L5-drop, certificate
roster and final validation refusals remain. This uses the same reader interface
under legacy and overlay-module-scoped-v2. SLUS retains the forced full-image
SHA-1 and pinned-recipe checks.

Quarantine copies each recorded certificate's durable proof directories into
the new generated tree, keeping the originals untouched for rollback. Otherwise
moving the generated tree would itself invalidate every retained certificate.
Build caches and exported tools are regenerated. Missing or aliased proof
artifacts are not copied and must pass normal renewal/validation.

An include file present before the transaction always forces --all. For a new
include file, capture existing production source recipes before mutation and
compute their actual compiler -M dependency closure afterward. Observe updated
recipes for existing TUs too; new TUs and per-row compiles retired by grouping
into them are excluded. Included member bodies are observed through their TU's
actual preprocessor dependencies. Assembly include paths
are conservatively traversed. Failure to compute the closure forces --all.
Generated assembly may be unavailable during the early preflight screen; the
transaction rechecks after the SLUS split and fresh gate-view export, before
choosing gate_all's mode. A new module's private header therefore keeps an
incremental gate when existing sources do not depend on it.

workers defaults to two thirds of the process CPU affinity, capped at 16 (24
available CPUs -> 16); a positive plan workers value overrides that default.
certificate_workers defaults to min(4, workers/4), at least one. Each certificate
has a separate log and retains the 7,200-second module timeout; window gates
retain the hard 1,800-second timeout. Cancellation stops the entire helper and
compiler process group before rollback. Shared certification window clean/copy
operations are locked so overlapping modules cannot destroy each other's proof.

gate_all publishes a new transaction-token-bound receipt directory only after
its final current-MATCH audit passes. Only windows actually built in that run
appear, never cached journal hits. Native-module artifacts and the real gate
output are snapshotted under the gate's window lock. Certification reuses a
snapshot only when the authority/view/token/tool and current inputs_sha match,
and all artifact hashes are intact. Missing or stale-input windows are gated
normally; altered receipt artifacts fail. Retail comparison, genuine whole-TU
builds and the complete existing certificate validator always run. Durable
certificate schema and authoritative validation are unchanged. There is no
general persistent certificate cache or journal-only shortcut.

Land gate/compiler/fingerprint tool packages separately from ordinary source
packages. Their one full gate repopulates incremental inputs; bundling unrelated
ordinary work with them makes that work pay the cold full-gate cost too. This
original follow-up tool package itself needed a full gate and all renewals.
The selective-renewal follow-up is a separate guarded package. Its landing order
is headers and sdk2, then certfp with its scoped selector, then landproc. Those
packages share one transaction and one renewal pass. The landproc package writes
no certfp-owned file; changing the lander during a transaction takes effect on
the next invocation, while the migration already invalidates all old-schema
certificates and requires their normal renewal in the combined transaction.

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
