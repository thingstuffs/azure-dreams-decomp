# Pin research round 54: ordinary zeroes and one controlled GCSE repair

Round 54 removed 12 artificial pin sites from 10 exact rows. Eleven removals are ordinary C zero initializers in nine rows. The remaining removal is a redundant `ASM_KEEP_NV` in `town/func_800BAE88`, paired with a narrowly controlled `-fno-gcse` recipe. The campaign count moved from 6,024 pins in 1,270 rows to 6,012 pins in 1,269 rows, 91 pins below the 6,103 starting point. This count follows the established campaign scope and excludes the owner-parked `ovmovie` rows; the all-source count is 6,019 pins in 1,271 rows.

The publication gate is complete. All ten covering windows matched, including the 393,216-byte `dungeon_engine` window and the 335,872-byte `town_scene` window. The other eight deep windows also matched. All ten linked strict row checks were byte exact, host syntax checks passed, the 884-TU SLUS recipe gate matched, the row database check passed, and the status report recorded zero unverified rows. The machine-readable receipt is `docs/evidence/pin_research_round54_20260917.json`.

## Nine ordinary-zero repairs

The nine repairs replace eleven declarations of the form `register s32 value ASM_REG("$0")` with ordinary initialized locals, `s32 value = 0`. The existing uses, branches, calls, interfaces, and `NON_MATCHING` arms remain unchanged. On the old MIPS path, the fixed `$0` binding always supplied the integer value zero. Source review found no nonzero assignment, unknown inline-assembly output, address escape, or use requiring a chosen register in any accepted binding. Existing assignments in the affected paths assign zero. The two `func_80F90E88` sites also preserve the zero-to-null conversion and the separate tied `ASM_KEEP(endpoint)` contract.

| row | removals | pins | recipe | exact words | final source SHA-256 |
|---|---:|---:|---|---:|---|
| `dungeon/func_800AAF90` | 1 | 6 -> 5 | `2.7.2-cdk-G0` | 316/316 | `66dfcc568f437a367728e68aa1145b497fcdbb8cb7f0f9a12aa655509afeba41` |
| `dungeon/func_80AE9000` | 1 | 13 -> 12 | `2.7.2-cdk-G0` | 161/161 | `777967bc3ac0edcd80a8a07f99194486e8031431db82f277c6c9b91d3f2c7e06` |
| `dungeon/func_8187B1F4` | 1 | 13 -> 12 | `2.7.2-cdk-G0` | 211/211 | `f011eeb9802e7191c19814884075b537b59d0000b9a3ba8f52f8ccd80b6f046e` |
| `town/func_80878714` | 2 | 2 -> 0 | `2.7.2` | 24/24 | `88b3ef95eebfbca365007f83aa0b5bc544aa88879a32377e5794e16d19462706` |
| `dungeon/func_807B0B3C` | 1 | 50 -> 49 | `2.7.2-cdk -fno-rerun-cse-after-loop` | 415/415 | `7564d2dff31a93e1a91283f6671b7db7ba06d73c2d1dc590e2d2738910ea525b` |
| `dungeon/func_80ADD000` | 1 | 9 -> 8 | `2.7.2-cdk-G0` | 161/161 | `dadde8bc36b82f0a40cb0f119dfc585eda7fc6ae014fdda7c0ef357059a94641` |
| `dungeon/func_80AEF12C` | 1 | 17 -> 16 | `2.7.2-cdk-G0` | 120/120 | `fd153c0bdd204f073e5b438709d584f63b3605d2806c521c9a9c4eb3f5189c29` |
| `dungeon/func_80F90E88` | 2 | 22 -> 20 | `2.8.1-G0 -mno-split-addresses` | 245/245 | `6b94c776ef9dfbf4d39017811e9519e65e9dbb3fb559e4e0285d0b613f08f921` |
| `dungeon/func_80AD7000` | 1 | 9 -> 8 | `2.7.2-cdk-G0` | 161/161 | `c9f4ac5f0583a70960016c52195515695cd008ee69bbcfa6223b58dc54c39b9e` |

The final source hashes bind the published, comment-clean sources. Eight final files differ from their screened candidates only by deleting obsolete unresolved-pin comments; their C token streams are identical. `func_807B0B3C` required no comment cleanup. Fresh linked strict checks cover the final files rather than relying on the earlier screen.

The bounded screen measured 18 exact baselines at their recorded recipes. Nine candidates were exact, four were one substitution away, and five had larger or indel residuals. Those observations are routing evidence only; they do not prove the remaining cohort or any row impossible.

The reusable `tools/xform/zero_init.py` guard admits live direct local zero-register declarations with defined ordinary-zero behavior. It refuses unsafe writes, macro/call arguments, asm outputs, address escape, ambiguous shadows, and control-flow entries that can skip the new initializer. All 27 unit tests pass, including exact reproduction of the nine frozen winner hashes. The recognizer is conservative; future candidates still require exact bytes, independent source/caller review and covering publication gates. The production sources were independently reviewed before this reusable tool was added. Independent review binds the final tool, tests and fixture hashes and confirms all 27 tests pass.

## `func_800BAE88`: keep erasure under controlled GCSE

`town/func_800BAE88` loses only the standalone `ASM_KEEP_NV(filter_entry)` after `filter_entry = selected_entry`. Its interface, data flow, branches, table access, and calls are unchanged. The final source SHA-256 is `c6406b3efcf678c438b3d6a0bfb670961f135957531aa5f6f51e6cb5d69fbe18`; pins move from 11 to 10. The row's true runtime identity is `0x800B85E8`, so the source filename is not used as a runtime-address claim.

The unchanged baseline is exact at both `2.91.66-G0` and `2.91.66-G0 -fno-gcse`. After the keep erasure, the original recipe scores 146/147 generated/target words with nine substitutions and one indel, while the controlled recipe is exact at 147/147 with zero substitutions and indels. The row recipe therefore changes only to `2.91.66-G0 -fno-gcse`.

The saved compiler dumps identify the mechanism. In the erased source, CSE UID 166 copies pseudo 104 to pseudo 105, and UID 190 still consumes pseudo 105. The normal GCSE dump then reports `COPY-PROP: Replacing reg 105 in insn 190 with reg 104`; the consumer changes to pseudo 104 and the retail pointer move disappears. The original keep creates an inline-assembly barrier, while `-fno-gcse` retains the ordinary assignment without that artificial barrier. This is a controlled reconstruction recipe; the evidence does not assert which pass setting built retail.

Three independent rows were checked for transfer. No erasure became exact: `dungeon/func_8180B71C` retained two indels at both recipes; `dungeon/func_810330FC` stopped because its unchanged `-fno-gcse` baseline was nonexact; and all three `town/func_8081822C` erasures remained nonexact. Round 54 therefore claims no general `-fno-gcse` transfer rule.

## Backend ownership and bounded negatives

The saved GCC 2.8.1 trace for row `dungeon/func_800B89C0`, whose true runtime name is `func_800BE120`, attributes its inherited literal-zero substitution to `reload_cse_simplify_set`: at UID 42, the SI zero source is replaced by register 16 because the cached `s0` value compares equal. The reconstruction worker's `SITE_MAP.md` labels the same 144-word snapshot in row address space beginning at `0x800B89C0`; the trace's `retail.dis` and row identity provide the runtime-name scope. The comparison is over the same instruction stream and does not treat the site-map labels as runtime addresses. `rest_of_compilation` invokes this reload CSE step after the `greg` dump, resolving the earlier dump-boundary ambiguity. The traced and normal assemblies are byte identical. A typed boolean probe is semantically legal but remains five substitutions away, and a literal-zero control remains one substitution away; neither was published.

The bounded four-hypothesis reconstruction of the same row also stayed nonexact. Its best unpinned sources score 141/144 words with 12 substitutions and seven indels. This result narrows the remaining lifetime and return-value shape without supporting an impossibility claim.

For `dungeon/func_81988C1C`, an external Gemini analysis ended at its four-minute print timeout and produced no operation, return-contract, or C-hypothesis analysis. Its raw prompt is preserved as input rather than treated as evidence; in particular, the prompt did not adequately qualify that the screened `READ_ZERO` macro overwrites its output. The two stdout lines and invocation metadata form an incomplete checkpoint, not a negative result. A separate evidence-driven probe replaced the final hardware-zero/`READ_ZERO` wrapper with an ordinary `return 0` and removed the unused macro. That source preserves the straight-zero return semantics and generates 139/139 words, but remains one register substitution away: `move v0,a0` instead of retail's `move v0,zero`. The loaded `next_node` in `a0` is known to be zero on loop exit, but the pass that reuses this fact has not been traced and is not equated with the separately traced cached-`s0` owner. The candidate was not published. The row's `0x81988C1C` address is synthetic row space and is not asserted as a runtime address.

These receipts establish the twelve published removals and their current build contracts. The screen, transfer checks, and backend trace remain bounded evidence rather than a proof about all zero-register or keep sites. The next useful work is to continue guarded mechanical families, bounded whole-function reconstruction, and direct investigation of actual compiler uncertainty; the remaining pin count should not be treated as thousands of unrelated one-off problems.
