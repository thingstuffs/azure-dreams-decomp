> Research checkpoint, 2026-09-17. Experiment paths below are relative to
> `work/native_lane/r39_assembler`. This snapshot preserves findings and unresolved
> next experiments; ongoing lane work may add newer results.

# `slus/w_80041CBC` delay-slot provenance checkpoint

## Scope and fixed input

- Row: `slus/w_80041CBC`
- Production cell: GCC `2.8.1 -G0`, followed by `ccproc`, `maspsx`, and the normal assembler/link path.
- Current/base source SHA-256: `01159e8a631c4096f086d2d7148ca528fd96a2a590efb368c7f4b30b2f8500ef`
- Baseline object SHA-256: `0004548aa77d173510f5279f1a818bad4ff2aa28a60ceb33fa72cc2cb9fd0766`
- Extracted retail function SHA-256: `f7dabf47df313b56836eb6d4e04c450d67b9e675e1735f11ed6e873e88ef69eb`
- Baseline verifies exactly at 122/122 score units. The source under test is preserved in `base/w_80041CBC.c`; no production source or tool was changed.

## Corrected owner of the missing delay `nop`

Removing the empty `ASM_KEEP(zero)` changes GCC's own raw assembly before either `ccproc` or `maspsx` runs.

Pinned raw GCC output at the relevant branch:

```asm
andi $3,$3,2
bne $3,$0,$L5
 #APP
 #NO_APP
lui $2,%hi(D_80080A85)
```

Pinless raw GCC output:

```asm
andi $3,$3,2
.set noreorder
.set nomacro
bne $3,$0,$L5
lui $2,%hi(D_80080A85)
.set macro
.set reorder
```

The directives are emitted by GCC because its delayed-branch pass has already selected the symbolic `HIGH` instruction for the slot. `ccproc` leaves the decision intact. `maspsx` emits the pinned branch with a `nop`, and preserves the pinless `lui` fill. Therefore the one-instruction loss is not an assembler convention/version failure or lost assembler metadata.

The final RTL confirms the decision:

- Pinned `.dbr`: asm insn 198 precedes symbolic `HIGH` insn 200 and creates an output dependency; there is no delay-slot `SEQUENCE`.
- Pinless `.dbr`: insn 304 is a `SEQUENCE` containing branch insn 195 and symbolic `HIGH` insn 198.
- GCC 2.8.1 `reorg.c` permits a safe, nontrapping fallthrough instruction to fill the branch slot. `mips_check_split` has split the byte-symbol access into `HIGH`/`LO_SUM`, making its `HIGH` independently movable.

Evidence: `stages/base/raw.s`, `stages/pinless/raw.s`, `dumps/base/w_80041CBC.c.dbr`, `dumps/pinless/w_80041CBC.c.dbr`. Raw hashes are respectively `49f3b83f2770e58b6f7eef1c7e3db7dc32d239a6fdc31136567137bb7c575c68` and `98de8ff60df345c0fe8d72a62465ad78c91063850c3057bd47f1a76171944e52`; `.dbr` hashes are `a0b6d2b35558e4eceb94f394c471a4a0522c4ff11bf3e15311a327ccb7eb01a6` and `b9b58b5dd70017a632e4c619e39c1f5cfc9dd37f081c0260d62404a98166766c`.

## Independent and genuine-tool controls

- A small isolated control (`repro2/probe2.c`) reproduces the ownership boundary. An empty asm at the fallthrough head gives `bne; nop; lui`; no asm gives `bne; lui` in the delay slot. Moving the asm earlier changes unrelated allocation but leaves the branch filled. The dependency must exist at the fallthrough head.
- The compatible genuine SN pipeline reproduces the same branch choice: genuine GCC 2.8.1 emits the pinned `nop` case and the pinless filled-`HIGH` case; genuine ASPSX 2.67 preserves both. Its unrelated `jr` delay-slot behavior differs from the production object, so whole-object assembler comparisons must not be interpreted as this site's cause.
- The exact `--production-cc1` wrapper is a negative compatibility control, saved as `stages/genuine_production_base.json` and `stages/genuine_production_pinless.json`. That mode ignores the row's extra cc1 flags, emits GP-relative code, and is broadly incompatible with this TU; it is not evidence for the branch site.
- A seven-compiler stock sweep is in `stages/sweep_results.json`; the nine named-cell scores are in `stages/named_scores.json`. The split-address CDK/2.8 family makes the same pinned-versus-pinless delay decision. Older 2.6.3/2.7.2 cells keep the byte load as a multiword assembler macro, which cannot occupy one delay slot, but those cells are far from the retail function. No pinless stock cell is exact.
- `stages/filled_high_controls.tsv` records 15 currently exact SLUS controls where a symbolic `HIGH` legitimately occupies a branch delay slot. A global assembler/adapter rule that suppresses this pattern would regress known retail matches, and the raw syntax contains no target-specific metadata that could distinguish this site.
- The proposed `-fno-delayed-branch` + genuine-ASPSX ownership handoff is already closed for the recovered tool versions and documented driver mode by genuine-tool receipts, so it was not recompiled here. Bare recovered ASPSX exposes no optimization option; the captured production driver invokes only `aspsx -q`. The PSY-Q 4.1 validation tested ASPSX 2.56/2.67/2.77/2.79/2.86 across reorder, noreorder, and native SN-cc1 streams: none schedules delay slots. In reorder mode they only insert protective nops; in noreorder mode they emit literally. Thus disabling cc1 delayed-branch scheduling under these recovered pipelines would lose the currently correct call/argument fills and ASPSX would not restore them. See sibling evidence `docs/process_notes_wall_deconstruction.md` step 8, `docs/one_to_one_program.md` around the production pipeline proof, and `tools/compiler_notes.md` under “4.1 sweep + ASPSX provenance experiments.”

## Natural full-source results

Six local symbolic/control-flow reconstructions—local skip state, combined condition, common-tail `goto`, `do`/`break`, explicit `else`, and `switch`—all compile like the pinless source: 121/122 and total diff 26, with the symbolic `HIGH` moved into the branch slot. A volatile symbolic byte read is also separable: GCC moves its nontrapping `HIGH` before the volatile load. Results are in `natural/results.json`.

A full natural symbolic reconstruction that removes all register/page/address pins is `natural/full_symbolic.c` (SHA-256 `db156e2b61decb3586be011d32603362feda8c6f8e0d588e7c37715c66400f54`). It was tested across the nine named stock cells and compatible genuine pipelines. No cell is exact: older macro-emitting cells produce 98-instruction or larger shapes; split-address CDK/2.8 cells produce 89 instructions against retail's 91 and fill two symbolic `HIGH`s. Scores are in `natural/full_stock_scores.json`; genuine runs are `natural/genuine_*.json`.

A grouped-object reconstruction is `natural/full_grouped.c` (SHA-256 `14e53d2ff17a65e1d98cb49130c54513a7923e4840ad2fad80b6deb204b5a563`). It holds and reuses the timer-page base, but GCC then fills the branch with the grouped object's `addiu` low half. Its scores are worse and it does not recover the retail schedule. Raw output is `natural/grouped_capture/raw.s`.

These failures establish the present source-shape boundary; they do not establish that natural C is impossible.

## Literal-address diagnostic, rejected as a repair

`natural/absolute_read` changes the byte read to `*(u8 *)0x80080A85`. GCC emits a single assembler macro-form load instead of split `HIGH`/`LO_SUM`; because the macro expands to multiple words, it cannot be used as the single delay instruction and the assembler leaves the required `nop`. Linked at the exact SLUS VMA, `natural/absolute_read/linked.bin` is byte-identical to retail, with SHA-256 `f7dabf47df313b56836eb6d4e04c450d67b9e675e1735f11ed6e873e88ef69eb`.

This is causal proof, not an acceptable pin removal. It replaces a relocatable symbol with a hardcoded PS1 address, moves the platform binding into ordinary C, drops the symbol's HI16/LO16 relocations, and harms the port arm's semantics. The result is therefore rejected even though its linked bytes are exact. Candidate source SHA-256: `986bf3f6bac5ee349bc79c2bebcf00fb8db4f1a5926cdb9fcbe370409fbc832e`. The current mechanical `pin_census.landing_refusal` returns `None` (`natural/absolute_read/landing_refusal.txt`), so this semantic portability rejection is also a concrete lint-coverage finding; it is not evidence that the candidate is landable.

## Next bounded source experiment

The three value-lifetime probes are complete and negative (`reuse/results.json`). Reusing `zero`, `frame_ticks`, or `sync_flags` for the byte read does not create the needed scheduling dependency. All three `.dbr` files still wrap the branch and symbolic `HIGH` in one delay `SEQUENCE`. `reuse_zero` is object-identical to the pinless candidate (121/122, total 26); the other two add allocation drift (totals 31 and 27). Sources and dumps are under `reuse/reuse_*`.

Same-image source gives a concrete declaration clue: several SLUS TUs declare `D_80080A84` as a 16-byte object, while this target TU declares the bytes at offsets 0, 1, and 3 separately. Two focused reconstructions use the authentic 16-byte extent, once as an array and once as a fielded struct, while retaining every other matching arm and pin. Both emit `%hi(D_80080A84+1)` in the branch slot and are identical 121/122 negatives (total 26). Results and `.dbr` dumps are under `context/`; this closes the declaration spelling by itself, without rejecting a richer original object-use context.

The next tracked experiment is a provenance search for that richer context: identify the defining TU/linker declaration and any original update/read sequence for the 16-byte frame-sync object, then reproduce only a semantically real cross-field dependency at this tail. A successful source must retain symbolic relocations and port behavior, emit no extra runtime instruction, keep the `HIGH` out of the delay `SEQUENCE`, and preserve all 91 linked retail instructions. If no authentic relationship supplies such a dependency, inspect the recovered GCC/SN cc1 delayed-branch implementation for a site-specific candidate-selection difference against the rebuilt 2.8.1 pass. Existing retail controls rule out a global branch-unfill policy, and recovered genuine ASPSX receipts rule out handing scheduling to the assembler. The natural C cause remains unresolved rather than impossible.
