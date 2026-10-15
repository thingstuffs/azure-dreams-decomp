# Landing proof handoff and accounting caches

`land_packages.py` uses incremental window gates unless `full_gate_reasons`
identifies an input outside the window hash. A reviewed package can explicitly
hand a redundant proof to a **complete production transaction**. Standalone
application, `--preflight`, and `--prepare-only` retain their original proofs unless a sealed current canonical receipt discharges that exact proof.
Unknown packages ignore the handoff and keep their current behavior.

## Package integration

Keep all package integrity checks, before/after guards, prerequisite checks,
source/ledger writes, lane receipts and dry-run handling. At an independently
reviewed redundant proof, import the target root's helper:

```python
sys.path.insert(0, str(root / 'tools/lanes'))
from package_proofs import defer_proof
if not defer_proof(root, PACKAGE_DIR, 'overlay-module', module_key,
                   lane_receipts=['scores.json']):
    original_complete_module_proof()
```

Use `overlay-window` with `config/overlays/NAME.overlay.yaml` for an actual
production window; use `slus-image` with `slus` only for the linked image proof;
use `levels` with `ledger/levels.jsonl` only for redundant final accounting.
`run_proof` is a convenience for a proof whose entire original implementation is
`subprocess.run(argv, cwd=root, env=env, check=True)`.

The helper requires both `LAND_SKIP_PACKAGE_PROOF=1` and a fresh lander-created
context bound to the root, package, entry hash and transaction. A bare environment
variable does not defer anything. Its receipt binds immutable lane evidence by
hash and names every deferred obligation. These records do not grant review or
replace production certificates. The lander logs the records after each apply.

The native source-only helper already delegated production proof before this
change. It now registers module/window obligations after an actual source write.
Idempotent applications introduce no extra production work.

Do not defer intermediate levels/registry/graph work whose result is consumed by
a later package guard. A later package may need a newly generated row or improved
ladder level. Do not monkeypatch subprocesses in old immutable deliveries or
reseal their dependency guards without independent review. Existing deliveries
must adopt the explicit call and regenerate their inventory before they benefit.

## Coverage obligations

| Named proof | Required lander step |
|---|---|
| Production overlay window, including its C/assembly rows | `gate-all --require-window CONFIG`: a fresh build and retail MATCH even if the journal was already current. Missing, superseded or out-of-scope configs fail. |
| Native complete TU, placement, owned data, genuine ASPSX and affected windows | Force that module into `certify-all --renew KEY`, or first issue after complete review. Canonical producer and final canonical certificate validation remain required. A module without reviewed certification fails the transaction. |
| Linked SLUS image and pinned build recipe | Both forced SLUS builds remain, with MATCH and identical pinned recipe checks. |
| Redundant final levels accounting | `fast-levels` and post-certification `levels`, followed by the L5 non-decrease check. Certificate readers run fresh. |

Per-row genuine ASPSX checks outside a certified native TU, SLUS member/partition
certification, arbitrary fixture tests, JP/dual-region checks and specialized
source/data proofs are **not** implied by the linked image/window gate. They keep
their original commands. The helper returns false for unknown proof kinds. A
module handoff must name the complete module covering the original claim.

No `PROVED_NO_COMMIT`/commit or `package-proofs-discharged` event is reached after
a required gate, renewal, accounting check or final validation failure.

## Accounting

`ledger/cache/row_facts/{levels,status}.json` stores only source-analysis facts.
Keys include source/raw hashes, the complete row record, semantic slices of
configuration and ledgers, shared module source context, scoped raw noreturn
names, cross-row callee arities and the implementations of these scans. Symbol
and void-definition indexes are rebuilt per invocation. Source/body changes do
not invalidate unrelated rows; callee signature changes invalidate callers.
Ladder placement comes from freshly checked certificates on every invocation.

`AZURE_ROW_CACHE=0` disables cache reads and writes. Malformed, stale or corrupt
entries become misses. Entries preserve mapping order, including Counter ties
and output JSON field order; writes publish an atomic complete generation.
`AZURE_ROW_CACHE_STATS=PATH` records hit/miss counts and phase wall/CPU times
without changing ordinary stdout. `STATUS.md` retains its normal current-time
header; equivalence tests hold that clock constant.

Accounting shares the existing certificate worker implementation, asking for
full canonical status records. `AZURE_ACCOUNTING_WORKERS=1` selects the serial
reader. The lander passes its certificate-worker budget to accounting; standalone
CLIs cap their default at twelve. The parallel path performs the same fresh
`certificate_reason` call and retains the canonical exception policy. It caches
no verdict. Its process group is isolated before using the batch cancellation
policy. Default certificate batch results retain their original compact shape.

The lander still quarantines generated caches at transaction entry. Row facts
can be reused within a transaction and between direct accounting commands;
existing generated caches are restored on rollback.

## Gate inputs and cooperative CPUs

Global compiler/gate tools retain the full-gate fallback, including the
tracked tools/build targets of gate tool symlinks. Sources, headers, symbols
and assembler flags now use complete per-window dependency hashes. Baseline recipe discovery records custom symbol-file
paths. Native source changes, ordinary row C and unrelated accounting tools keep
incremental mode. New private headers retain the existing preprocessor closure
check. Rowbase hashes now bind complete selected records, including link delta
and proof confidence, rather than only region identity/noreturn names. This
input-schema change causes a one-time journal refresh.

`python3 tools/lanes/reserve_cores.py -- command ...` restricts a cooperating
lane to the low-numbered CPUs in its inherited affinity. All cooperating lanes
must start with the same parent affinity. `--role landing` uses the reserved
high-numbered CPUs; default reservation is eight, reduced to leave one lane CPU
on smaller machines. With no command the helper prints both sets. This is a
cooperative convention and changes no other process or system cpuset.

## Proof-carrying packages (owner-direction extension)

`tools/lanes/proof_receipts.py` defines `azure-proof-receipt.v1`. A receipt names
one `kind` and `target`, a successful exact result, the full structured input
projection and its canonical SHA-256, and an immutable artifact inventory.
The verifier **rediscovers** the input projection using the live target. It does
not trust the receipt's list of dependencies. The package's `proofs.json` lists
`{kind,target,directory}` records; both that index and every receipt/artifact must
appear in the reviewed `package.sha256.json`.

The trusted boundary is the reviewed package and canonical producer. These are
content-addressed evidence records, not cryptographic signatures. A hand-written
MATCH, a diagnostic native score, or a historical journal entry never acquires
complete certificate authority through a changed label.

The window projection binds YAML bytes and values, selected canonical split and
registry records, assignments, actual compiler `-M` plus literal transitive
includes at the production recipe, assembly `include`/`incbin` dependencies,
header namespaces, source-local include shadows, scoped raw noreturn evidence,
symbol/flags/ownership/rowbase inputs, native module fingerprints, tool and
compiler bytes, Python/YAML identities, and retail container and slice hashes.
Compiler/include environment overrides are rejected. Volatile compiler-time
macros and unsupported inline assembler file imports in C require a separate
proof adapter and fail closed; assembly-kind include/incbin closures are modeled. Unsupported dependency
layouts fail closed. Currently some inputs are conservative: shared headers,
family ownership/rowbase catalogs and the full retail container may invalidate
more windows than the minimal semantic dependency set.

Canonical producers and consumers:

* `gate_all.py --portable-output NEW_DIRECTORY` exports only freshly successful
  window builds while holding the normal window lock, with equal before/after
  input projections and window bytes equal to retail.
* `certify_overlay_module.py ... --portable-output NEW_DIRECTORY` exports the
  full canonical certificate and durable proof directories after certification.
  `proof_receipts.py --root ROOT export-module KEY NEW_DIRECTORY` exports an
  existing certificate only after canonical validation.
* `native_package.py ... --proof-root POST_APPLY_ROOT` includes full proofs from
  a separately prepared, canonically certified root. The immutable artifacts
  live under the sealed diagnostics directory so embedded compiler origin paths
  survive generic package lint without rewriting proof bytes. Its selected source hashes
  must equal the package's after hashes. The ordinary admission/guards stay.
* `verify.py ROW CURRENT_SOURCE --proof-receipt NEW_DIRECTORY` records an exact
  canonical overlay row score. `native_member.score_batch(...,
  receipt_output=NEW_DIRECTORY)` records a canonical native diagnostic. These
  diagnostic kinds never replace a production window or complete certificate;
  candidate-only or SLUS contexts still need their existing proof adapters.

The lander checks inventoried evidence immediately after each package applies,
therefore observing all earlier packages, and again after all packages,
reviews, registry and graph generation. A current complete module certificate
is copied to its guarded durable proof paths and independently checked by the
unchanged canonical reader. Its exact affected windows can satisfy window
obligations too. Stale receipts request fresh proofs. The gate verifies carried
windows again rather than trusting the lander's decision, and the final tree
is checked again before the transaction can succeed. Tests include a later
package invalidating the first package's initially current proof.

`gate_all.inputs_sha` now uses this complete projection for ordinary windows as
well as modules. Legacy v3 hashes cannot be promoted: migration rebuilds each
window lacking a current carried proof once. `legacy_inputs_sha` remains solely
as a tested historical oracle, with no CLI selector. Headers, assembly, custom
symbols and family flag changes use dependency hashes; global tool/compiler
changes retain the explicit full-gate fallback. The previous unconditional two
large timing-window builds are removed; requested `timing_windows` still run.

Existing packages adopt the explicit handoff and a sealed proof index under
review. Immutable old packages are not edited or silently reinterpreted.
Bare skip flags, dry runs and unsupported proof kinds retain the existing
behavior. Standalone/preflight applies can reuse a sealed current canonical
receipt too; without one they retain their original commands. Guard drift still stops an apply; receipt fallback
does not weaken package guards. Groups whose guard contexts conflict must be
rebased or combined and proved together.

## Asynchronous full audit

`tools/audit_full.py` is an independent quiet-time worker. After a successful
commit the lander writes only queue metadata, normally every ten landings
(`audit_every` in the plan). It never launches or waits for the worker. Queue
errors are logged as holds after commit, rather than rolling back a committed
landing. An operator should monitor queue age and `async-audit-enqueue` holds.

Run the worker from an authorized schedule, for example every thirty minutes
with `nice -n 15 python3 tools/audit_full.py --root ROOT --workers 8 --drain`.
No system schedule is installed by this package. `--once COMMIT --output NEW_DIR`
runs an explicit audit; `--record COMMIT --every N` only enqueues it.

The worker archives the immutable commit into a disposable root outside the
source checkout (configure an external private `TMPDIR`). Child logs also stay
outside the source while commands run, then copy into the persistent report.
This prevents the live lander from treating audit cwd/log descriptors as live
gate activity. Each stage owns a cancellable process group. The worker shares only
read-only toolchain/retail resources, builds SLUS, runs a full window gate,
rebuilds all recorded module proofs, validates all certificates, runs cold
levels/status with the row cache disabled, and checks row_db before and after.
It never changes the live checkout, index or HEAD. Internal tracked tool shims stay inside the snapshot. Absolute/external tracked
links are unsupported and reported as infrastructure errors. Missing historical ephemeral
artifacts are reconstructed rather than classified as a bad source commit.

A failed audit bisects against the last successful first-parent ancestor and
then verifies the entire earlier prefix, so repaired/nonmonotone histories do
not produce a false “first bad” claim. Missing endpoints or infrastructure errors
produce a hold. Per-stage logs, JSON, cold reports and `REPORT.md` are retained.
The worker reports the bad commit; it does not reset or revert live history.
A real git-backed audit/rollback exercise remains a deployment check when the
lane root intentionally has no git metadata.

Scoped certificate fingerprints bind the native tool universe, so a global
window-gate reason retains `--invalid-only` certificate renewal in scoped mode.
Current certificates still pass the canonical reader; changed certificate or
artifact bytes and explicit unsatisfied module obligations remain forced.
Legacy fingerprint mode keeps the conservative global-tool fallback.

Audit snapshots use the audited commit's `tools/maspsx` source behind their
private toolchain facade, while sharing compiler/genuine binaries read-only.
Before bisection the worker re-audits the last good endpoint in the current
environment; an endpoint failure becomes a hold instead of falsely blaming a
source commit for external toolchain drift.

The synchronous `proof_scope.py` check is mandatory even when every journal
record is current. V1 permits canonical include lookup and deterministic
compiler recipes: path-sensitive builtins (`__FILE__`, `__BASE_FILE__`) and
custom include/profile inputs require a new dependency adapter first. Scope
policy edits force a full gate; extend the input model with the policy rather
than simply weakening the screen. The public receipt verifier is not a landing
authority without this scope check and the rest of the production transaction.
