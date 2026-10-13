# Single-input compiler oracles

These tools produce counterfactual compiler evidence. They do not produce C
candidates, remove pins, change recipes, certify functions, or authorize landing.
Run from a lane and keep outputs there. Use a private scratch checkout when
other lanes or landings are active. The prerequisite r114 pin-tools package
provides alloc_oracle.py, sncheck.py and value_luid.py.

`pass_oracle.py ROW TEXT --discover --families sched,combine,cse,alias,loop,dead,reload,reorg,jump,frame,refs,global --keep DIR --json FILE`
observes real executed sites. TEXT is `erased`, `pinned`, or a candidate path.
`--change` instead takes one JSON object, or a COMPOSITE: a JSON list of 2..4
distinct changes applied together in one compiler run (or `@FILE`). It rechecks the
uninjected debugger against plain cc1. Failed, absent, ambiguous and no-op
interventions remain invalid; a composite is invalid unless EVERY member applied
(`applied_changes` lists the member indexes that wrote something). Save a baseline
discovery first to select UIDs. `--families ''` records nothing: hooks come from the
change kinds alone, which is what search trials use (5-10x faster than recording).
When more than one family is requested, discovery runs the same independently
calibrated groups used by oracle_search instead of installing every breakpoint in
one GDB process. `family_runs` and `hook_counts` profile the groups and breakpoint
calls. `--hook-cap N` disables a discovery breakpoint after N active calls; the
result is marked truncated and `skipped_hooks` reports the hook, cap, first skipped
call, and that the remaining count is unknown. Null reorg thread/candidate pointers
are non-selectable sites and appear in `skipped_sites` rather than being dereferenced.

| Kind | Required selectors / forced input | Timing / meaning |
|---|---|---|
| sched-priority | uid, phase, value | Override one instruction's priority after adjust_priority; affects ready sorting, not dependency edges. |
| sched-birth | uid, phase, value=0 or 1 | Override birthing_insn_p's result inside the target instruction's adjust_priority. |
| sched-luid | uid, phase, value | Override one LUID immediately after sched_analyze. |
| combine-veto | uids=[i3,i2,i1] | Refuse the exact try_combine tuple; i1=0 means a two-insn attempt. |
| combine-crosses | uids=[i3,i2,i1] | Force use_crosses_set_p true inside that named attempt. |
| cse-copy-swap | uid | Skip the complete adjacent-copy rewrite and its note changes; site derived from disassembly, never a fixed address. |
| cse-substitution | uid, occurrence | Veto one validate_change from cse_insn. Occurrence is zero based for that UID. |
| alias | uids=[store,load], phase, value | Force true_dependence for a uniquely identified, oriented MEM pair. Aliased/reused MEM pointers fail closed. |
| loop-hoist | uid | Set the named movable's done bit before move_movables. This skips its processing; it can also affect dependent movables. |
| loop-biv | uid, pseudo | Refuse basic_induction_var for the named destination and insn. |
| keep-dead | uid | Veto deletion of a register SET in the dead/jump deletion paths and flow's dead predicate. Preserving RTL alone does not ensure a retail hard register or lifetime. |
| reload-equiv | uid, occurrence | Replace one find_equiv_reg result with null. |
| reload-cse | uid | Skip simplification and veto noop removal for that instruction. |
| reload-reuse | uid, occurrence, value | Toggle an executed find_equiv_reg reuse. Forcing an absent result fails closed because no register RTX exists; veto is fully supported. |
| reload-noop | uid, value | Toggle reload_cse_noop_set_p, directly controlling the named reload-CSE no-op deletion decision. |
| reorg-fill | uid, candidate_uid, value | Toggle eligible_for_delay for one executed delay insn/candidate pair. This supports both force and forbid. |
| reorg-merge | uid, thread_uid, value=0 | Skip one executed try_merge_delay_insns scan before it can delete the duplicate thread instruction. |
| reorg-delete | uid, value=0 | Veto an actually executed delete_insn whose caller is try_merge_delay_insns; this distinguishes destructive merges from harmless scans. |
| jump-cross | uids=[tail1,tail2], value | Veto find_cross_jump's selected tails, or force only when a conservative backward scan finds `minimum` exactly equal RTL patterns. Otherwise force fails closed. |
| frame-offset | occurrence, value | Set frame_offset immediately before one executed assign_stack_local call; the real allocator still performs alignment, sizing and slot bookkeeping. |
| cse-eqv-head | new, old, occurrence, head | After one executed make_regs_eqv, move an observed member to the equivalence-list head while preserving both links. canon_reg consumes the ordinary list. |
| global-avoid | pseudo, hardreg | global.c: add `hardreg` to the pseudo's allocno hard-register conflict set at prune_preferences entry (conflicts complete, preferences not yet pruned). The `global` discovery family records every allocated pseudo's colour at reload entry (allocno -1 = local). |
| alloc | pseudo, input | The prerequisite allocator inputs (refs, refs-add, live, global, local, qty-refs, qty-life, qty-rank), written exactly where alloc_oracle_gdb writes them. Inside pass_oracle this is what lets an allocator input join a composite; single alloc trials still use alloc_oracle on the cdk and 2.6.3 cells. Cross-checked raw-exact against alloc_oracle on 818B6AFC (global), 80D68308 (refs-add) and 808119EC (2.6.3 qty-refs). |

`phase` is `sched1` or `sched2`. One named intervention may meet the same selector
more than once, such as a repeated combine attempt or several deletion passes.
All actual writes/return overrides are recorded. The tool never calls compiler
functions from GDB. Emitted assembly is replayed through the ordinary scratch
assembler/linker; receipts retain generated and retail binaries and SHA-256
hashes. `raw_equal` is literal byte equality, with no relocation masking.

Cells: 2.7.2-cdk, 2.7.2, 2.6.3 and 2.8.0. Every hooked function has the same
signature in the four gcc-src trees, struct movable is identical, and symbols are
unique in each cc1. Differences handled: 2.6.3/2.7.2 have no reload_cse_* (those
hooks are absent, so reload-cse sites never appear); first pseudo is 67 (2.6.3),
68 (2.7.2), 76 (cdk, 2.8.0); 2.8.0 keeps flow facts in `reg_n_info` (struct
reg_info_def: refs +16, deaths +20, live +24, block +32, stride 40 - checked against
the 2.8.0 `.flow` dump on 80DE48EC p84: 7 refs / 8 insns / 2 deaths). On 2.8.0 the
local-alloc qty path is verified for symbol resolution only. Grouped SLUS contexts
and other cells fail closed. Overlay native members remain valid standalone oracle
inputs; their raw replay uses the ordinary native-member scorer. A failed pinned
raw-byte control holds a search row.
If a native module compile contains several `.ent` bodies, search extracts the
source function's true-name body for pinned calibration. If the fast extractor
instead finds no body after a native-symbol rename, search falls back to an
uninjected pass-oracle compile of the same pinned text; that fallback still proves
debugger/plain-cc1 assembly identity.

Raw replay. Overlay rows: emitted assembly through the ordinary scratch
assembler/linker; `raw_equal` is literal linked-byte equality, no relocation
masking. SLUS rows (receipt kind `COUNTERFACTUAL_OBJECT_VS_CERTIFIED_PINNED_SLUS`):
the stream is assembled exactly as verify._compile_slus_source does (ccproc names,
maspsx 2.79 -G8) and compared, allocated sections plus symbolic relocations, with
the production object of the row's PINNED text (verify.compile_slus). The pinned
text is certified by the SLUS full-image SHA-1 gate, so equality means the same
linked bytes; it is object equivalence, not a link. The pinned control is replayed
the same way first and must be equal (calibration). `aligned_distance` is the word
edit distance after alignment (an inserted instruction costs 1, not every later word).

## Search and validation

`oracle_search.py --validate validation_inputs.json --out DIR --trials 128 --composites 24 --workers 6 --timeout 30`
requires exactly 800AED64, 81844F2C, 8028906C, 818B6AFC and 80D68308. The manifest
contains only row IDs and erased/pre-solution input paths, never interventions or
solved text. Search discovers opportunities from the selected input and orders them
in two tiers. Tier A (cheap, targeted): global-avoid and allocator inputs on FOCUS
pseudos - those coloured with a dominant wrong register in the aligned diff of the
baseline against retail (register-field-only word differences) - and COMBINE
CLASSES: one composite vetoing (or forcing use_crosses_set_p at) every successful
combine whose anonymised pattern is identical, e.g. a fold the source repeats per
block (800AED64: two lhu+sll+sra -> lh sites). Tier B: every family interleaved. If
no single is raw-exact, up to `--composites` composites are built from the six best
distinct singles that moved the aligned distance below the baseline (pairs, plus
triples of the best three; at most 4 members). Raw-exact results rank first, then
aligned distance, then size. It is a bounded
sample of the enumerated space, not a proof of impossibility. All candidates and
actual trials are retained. Discovery runs independent calibrated family observers
with timeout max(--timeout, 60 x plain compile, 240 s); trials get max(--timeout,
25 x plain compile). A family timeout is recorded and the other families continue.
Non-exact trials keep receipts, out.s and the trace but not pass dumps (size). Debugger timeouts kill the entire process
group and preserve available artifacts. Thread concurrency is bounded by workers.
The CLI process is nice'd so prerequisite allocator children inherit niceness too.
`--discovery-hook-cap N` applies the same explicit cap to search discovery and is
part of the resumability signature; zero means uncapped.

`oracle_search.py --all --gate DIR/validation.json --out SWEEP --trials 192 --composites 32 --workers 6`
censuses live pin sites in registered source rows at the scratch base. A failed
five-row gate refuses routing. `--diagnostic` permits an evidence-only sweep with
`routing_trusted=false`. Every row gets either exact-making interventions, none
found within its trial budget, or an explicit calibration/discovery hold. A held
row did not complete its requested trials. Resume requires identical text, cfg,
compiler, tool hashes and budget (state.json after discovery; each finished trial is
reused, timed-out trials rerun), so an interrupted row continues where it stopped.
Choose a new output after any of those change.
Each row retains a JSON and Markdown minimal-change report, a complete candidate
space, per-trial mutation/byte receipts, and debugger artifacts.

The five new discovery families are interleaved ahead of broad allocator trials:
executed reorg merges, jump2 tail pairs, reload reuses/no-op decisions, stack-slot
occurrences, and CSE equivalence-chain alternatives. No selector is fabricated
from a solved source. A force that cannot be represented by an observed compiler
object is an invalid no-op trial.

## Divergence attribution and mutation crossing

`attribute.py ROW TEXT --out DIR` aligns generated and retail words, maps each
generated word to `-dap`'s UID annotation, and follows that UID across the `-da`
snapshots with value_luid provenance. Register-field-only differences are owned
by local/global allocation or reload, stack-base displacement differences by
assign_stack_local, and delay words by reorg; every other word names the last
observed pass that created, rewrote, removed, or moved its deciding UID. The JSON
contains every differing word, its instruction/history/source evidence, and a
per-pass histogram. Retail-only words use the aligned neighboring UID and say so.

`mutate_search.py ROW TEXT --out DIR --mutations 8 --oracle-trials 24 --discovery-hook-cap 256` enumerates
bounded candidates from sweep transform modules t36..t87 plus perturb_basic and
perturb_struct. Every distinct admissible, compiling mutation receives a fresh
observed-site oracle search. A hit means that mutation exposes a raw-exact single
intervention; composites are intentionally disabled. Its default 256-call cap
bounds every discovery hook on large functions. Each per-mutation record retains
`discovery_skipped_hooks` and the closest trial's aligned generated/retail word
diff, so capped tails and one-word insertions are visible rather than reduced to
counts. Generator refusals and failures remain in the report rather than disappearing.

## Source references and 2.6.3

`source_refs.py ROW TEXT --out DIR` measures actual loop-depth-weighted reg_n_refs
changes around outer flow set/use calls. Nested calls are aggregated once. It
reports contributing UIDs, source statements, weight, actual post-sched1 live
length, and any residual against the allocator total. Source attribution requires
an instruction-identical -g twin with matching UID and RTL. Unknown sites remain
unknown. These are locations to investigate for fewer refs; recompilation is
required to measure any source edit or longer life. Use `--pseudo NUMBER --fewer-refs N --life-at-least X` to focus on a requested
reference/life goal and rank the counted source sites by their weight.
Global priority includes the
compiler's floor_log2(refs) factor. Local qty priorities may have tied pseudos and
are a different statistic.

`alloc263_oracle.py ROW TEXT --pseudo NUMBER --change '{"kind":"refs","value":14}' --out DIR`
extends the prerequisite allocator runner without overwriting it. The 2.6.3 array
and sort ABI was checked against source and actual 808119EC runs. Numeric targets
are required there; DECL_RTL name observation is not verified. The adapter runs
baseline and forced cc1, checks the baseline against plain cc1, calibrates the
pinned raw-byte control, and retains raw-byte results. Changes use the existing
allocator kinds: refs, refs-add, live, global, local, qty-refs, qty-life, qty-rank.
An intervention consists of its exact fields only; no additional overrides.
