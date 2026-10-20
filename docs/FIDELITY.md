# Fidelity limitations

Matching bytes and recovering natural source are separate goals. A function
can match while relying on register pins, pseudo-calls, assembler rewrites or
a model of an unavailable compiler. The [quality levels](PLAN.md) and
[generated status](../STATUS.md) keep these dependencies visible.

## What to examine

| Residue | Question to resolve |
|---|---|
| Register, keep or scheduling pin | Which real source lifetime, dependency or declaration explains the required emission? |
| Call spelling used for a jump | Is it a real call, an inter-image transfer or a mis-split block inside one function? |
| Empty argument list | Which argument registers does the callee actually read? Caller-side register liveness alone is not a signature. |
| Address/page constant | Is the declared storage, compiler recipe and aggregate base supported by retail address formation? |
| Assembler compatibility pass | Does genuine ASPSX produce this expansion, or is the pass compensating for source/compiler differences? |
| Computed goto, inline assembly or `NON_MATCHING` | What behavior remains to be reconstructed in ordinary C? |

Do not add unused computations or false prototypes just to influence register
allocation. A successful scorer result does not prove the inferred signature
or storage owner. Preserve measured limitations until a supported replacement
passes the relevant retail gate.

## Compiler and assembler evidence

`ledger/split_fingerprint_rows.jsonl` records compiler address-formation evidence;
`ledger/maspsx_dependence.jsonl` records compatibility dependencies. The evaluator
distinguishes source-driven imitation (an L4 blocker) from an accepted model of
an unavailable historical compiler (an L5 blocker). These are not permissions
to call all exact rows fully reconstructed.

The [compiler investigation](evidence/fidelity_lost_compiler_case.md) explains
the accepted model and the evidence limits. The
[small-data production transition](evidence/gp_partition_only/production_transition/README.md)
records the completed correction that superseded earlier pending plans.
Neither result proves that every remaining compatibility pass can be removed.

Genuine-assembler measurements require the contributor's own Psy-Q installation;
the current module proof uses the pinned version documented in
[TOOLCHAIN_PSYQ.md](TOOLCHAIN_PSYQ.md). Historical investigations of other
assembler versions are evidence, not additional setup requirements.

## Tail transfers and split audits

A jump to an address-named symbol does not automatically prove a separate
function. `ledger/split_audit.jsonl` records the reviewed boundary. Unresolved
or intra-function pseudo-call dependencies block L3. L4 requires no remaining
tail-jump scaffolding. A byte-verified real `jal` with no assembler rewrite may
be counted as a real call when its audit supports that conclusion.

For a proposed repair, state the source mechanism, compile at the evidenced
recipe, compare the affected object/retail bytes and run its window or image
gate. Recheck shared TU siblings and placements. Current residue fields and
status supply the counts; historical pilot yields are not current coverage.
