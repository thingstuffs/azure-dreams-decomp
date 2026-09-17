# Independent landing review: `dungeon/func_813315CC`

## Verdict

`retained_position_binding.c` is semantically admissible as a one-pin whole-C reconstruction at stock `2.7.2-cdk-G0`. It is linked-strict byte-exact for all 210 retail words, removes ten of the current eleven pins, restores the real three-argument `func_8003DB94` call, and represents the 144-byte position table and output table with their actual aggregate shapes.

This is not a zero-pin repair. The candidate deliberately retains the current `effect_position` / `effect_pos` hard binding to `$v1` and the inherited pointer-derived `-1` sentinel conversion. The retained production-style comment identifies that unresolved legacy scaffold. No replacement binding, fake dependency, extra helper argument, new volatile access, literal platform address, or additional pointer/integer round trip was introduced.

Final candidate SHA-256: `56c497f34be4466c8fb60a4d05ea137c4af240a1186d18a62f0535d25f65da91`.

## Whole-source recipe transition

The two verified endpoints use different source and compiler recipes:

| Source | Recipe | Result |
|---|---|---|
| Current production source, SHA `6f115b6841623640bf0600711154404aec9db48eca4acf84a269e50da61fde88` | recorded `2.8.1-G0` | exact 210/210 |
| Reconstructed candidate, SHA `56c497f34be4466c8fb60a4d05ea137c4af240a1186d18a62f0535d25f65da91` | proposed stock `2.7.2-cdk-G0` | exact 210/210 |

The independent current-endpoint receipt is `base_independent_verify.json`, SHA-256 `3951a3c243a21c8176c1f184d252653e372b975798d3b0bfc0fd6c745d7f2d24`. The candidate's direct compiler-oracle receipt is `retained_position_binding_strict.json`, SHA-256 `8b065ace0a9868c38d864152c9ae751f2377ad92ce5b380b8b5677dd1b6ceaa4`. It records linked-strict equality at the proven runtime base `0x801685CC` in `xfer_dungeon_134D800`: 840/840 bytes, 210/210 words, zero substitutions, zero indels, zero positional differences, and no relocation suspicion. Retail SHA-256 is `dea31d5bdf0b909011cb0808a6d2a08954a77ad1fd3904240b94bcf7338f964f`.

The exact candidate assembly `retained_position_binding.s` has SHA-256 `3598d33cb38a268cc1ffbdd6dfbb14d9192344c7399f1a2ac324f35875c456d7`; translated assembly has SHA-256 `298f77e79c24506015acaf24890d24e3a449526f35c388582e825ffe930cfdd0`. Compiler SHA is `7a571911a97cef0c6b7b5d4174e89ac54f9806ce3d4b233c0f8620e3503c672b`; comparator SHA is `54b4b6488120f2e418f3083080b814a52f7e64be57ef5b07b3fd341343af83ce`.

The cross-combinations are diagnostic controls. The current scalar source is nonexact at CDK by total 62, as recorded in `preprobe_recipe_matrix.json`. The final reconstructed source at the old `2.8.1-G0` recipe produces 206/210 words and total 65 (57 substitutions, 8 indels); receipt `candidate_at_old_recipe_strict.json`, SHA-256 `ea4a7608b5c4a7c0d8e454abf56a2c46445c05cc6b90e97943760aaa4a92acb8`. This is the reviewed whole-source transition described by `docs/PIN_RESEARCH_WORKFLOW.md`, not an `apply_candidates --cells` transition. Source and recipe must be exported atomically and journaled as `whole_c_reconstruction`.

`fingerprint.txt` (SHA-256 `7a57f1bad10d3696289dcfc8912b6323752f5c2d1fd41bc3241e14d72a8e7c2e`) records two compiler-filled call delay-slot stores and two two-register split-address sequences. Those signatures are consistent with the CDK/2.8 family and support the proposed reproducible recipe. They do not establish a unique historical compiler release.

At review time, the row metadata carried stale source SHA `a3ce2dc34751873418dfb577ab4774504efa6ba937f2724ccbabb81486452768`; the actual checked-in file and this candidate base are SHA `6f115b...` above. Any hash-bound transition must use the actual live hash.

## Pin and landing checks

`pin_census.sites_of` reports eleven sites in the current source and one in the candidate. The candidate's sole site is:

```c
register Vec3 *effect_position ASM_REG("$3");
```

The candidate has no hidden asm. Neither source has a `NON_MATCHING` or `#if 0` arm, so both unscored texts are empty, with SHA-256 `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`. `landing_refusal` returns `None`, including the port compile/lint check.

The retained local first holds `object->position`, then is set to `(Vec3 *)-1`, converted to the target word type, and stored through two volatile halfword lvalues. Retail reuses `$v1` for that sequence. An ordinary `s32` sentinel control remains at distance six, confined to constant materialization and two stores, while this inherited binding is exact. This is an unresolved allocator/source-shape issue, not evidence that pointer `-1` is the ideal source type. The candidate therefore claims a reduction from eleven pins to one.

## Aggregate and object layouts

`LocalPositionTable` is exactly `8 * 3 * 3 * sizeof(s16) = 144` bytes with 2-byte alignment. CDK lowers the ordinary assignment `positions = D_8016484C` to the exact retail block copy: a runtime source-alignment test, nine 16-byte iterations through aligned or unaligned paths, destination `sp+0x10`, and no tail. Source global and stack destination are distinct. Taking a local snapshot before allocation also preserves the table values across subsequent helper calls.

The table indexes are bounded by the actual caller and source expressions:

- direction is `(source->direction >> 9) & 7`, selecting 0 through 7;
- the sole caller supplies color/mode 0, 1, and 2, selecting the second dimension;
- the three explicit component accesses select 0 through 2.

The candidate's object views match the retail offsets on the 32-bit target:

- `EffectObject.position`, `.render`, and `.callback` are at `0x08`, `0x0C`, and `0x10`; payload begins at `0x20`;
- `RenderState` color bytes are at `0x0C..0x0E`, intensity at `0x10`, flags at `0x14`, and scales at `0x1C/0x1E`;
- `EffectPayload` sizes are at `0x18/0x1A`, mode at `0x1C`, effect data at `0x24`, position words at `0x5C..0x64`, and the vertex array begins at `0x74`.

The allocator `func_8003FC64(0x212)` returns a cleared object node and establishes its position and render pointers in the header. The candidate only dereferences them after the allocation null check. The caller's source state, work/origin record, dungeon object, and `D_80083780` data are pre-existing inputs; the allocated effect object and its payload are distinct. The 144-byte global source, local snapshot, effect payload, and destination `D_80175DD8` are therefore separate objects during their transfers.

`D_80175DD8` is independently declared by `func_81331914` as `s16 [][8][2][3]` and indexed in the same mode/pair/vertex/axis order. The candidate loops exactly eight pairs, two vertices, and three axes, copying 96 bytes from the payload's first two vertices into the selected mode plane. The sole caller bounds the first dimension to 0..2. No partial-overlap case is present.

The candidate retains the current volatile halfword stores at payload offsets `0x74..0x8A` and the volatile reload of the render pointer. Their ordering behavior is unchanged and was not used as a speculative cleanup. The signed scaling expressions and 32-bit pointer layouts are inherited target-C assumptions. In particular, the pointer-derived sentinel remains the one documented portability limitation and the reason this candidate still has one pin.

## Helpers and callback

The recovered SLUS definition of `func_8003DB94` takes exactly three arguments: destination render state, entry table, and signed-short index. Retail prepares only `$a0`, `$a1`, and `$a2`; the candidate's three-argument declaration and call are correct. The old fourth `render` argument was an accidental allocation constraint and is removed.

`func_8004491C` takes exactly two ABI words and returns a status that this caller does not consume. Its recovered definition treats the second word as a registration ID. This site supplies the address-valued ID `&D_80045340`, as the current source and many sibling sites do. The candidate's pointer-compatible local declaration avoids adding a pointer-to-`s32` narrowing cast; return-type and registration-ID spelling remain repository-wide declaration debt, while the two-word call contract is correct.

`func_8003FC64` has one flags argument and returns a node pointer. `D_80167C74` resolves to the same-image three-argument callback `func_80167C74`; storing its address at object offset `0x10` is consistent with the engine object layout.

## Caller review

The only same-image textual caller is `func_81336754.c` / runtime `func_8016D754`. It calls this function three times from one state:

- `state`, whose direction field is read at offset `0x2A`;
- `work`, whose first three words are consumed as the origin vector;
- an otherwise unused dungeon-object pointer;
- `D_80083780`, stored as the payload's effect-data pointer;
- modes 0, the unchanged signed timer value 1, and 2.

These four pointer arguments agree with the candidate's pointer-valued interface and field use. The TU-local structure names differ because each file exposes a narrow view of the same larger records; all four arguments retain one-word pointer ABI values. No new pointer narrowing is introduced.

The current pair has a pre-existing fifth-parameter mismatch: the production callee defines `u16 color_mode`, while the caller declares and passes `s32`. The final candidate resolves it on the callee side without changing the caller ABI:

```c
void func_801685CC(..., s32 input_color_mode)
{
    u16 color_mode;
    color_mode = (u16)input_color_mode;
    /* typed body uses color_mode */
}
```

CDK folds the explicit value conversion into the same retail `lhu $s4, 0xD0($sp)` stack load, so this ABI-consistent spelling remains exact 210/210. The caller continues to pass its existing one-word `s32`; the callee explicitly selects the low unsigned halfword used for field storage, comparisons, and table indexing. For the observed values 0, 1, and 2, the conversion preserves the full value.

The current caller is independently exact 219/219 at its recorded CDK recipe (`caller_base_verify.json`, SHA-256 `a2a91875bdb613361a339bb8a1391805875e8f789988e5ee6ccddb7720a7f9c2`). A scratch-only alternative that instead changes the caller declaration to `u16` is not byte-exact. `caller_u16.c`, SHA-256 `d918d6b98a08e18d2aeb5e3c9904227e759eb068db2ce510935212eea8f98e2c`, remains 219 words but differs by 53 substitutions because the narrower call prototype changes argument conversion and global allocation. Its linked-strict receipt is `caller_u16_strict.json`, SHA-256 `21bc8bb269b1b0c546216b292c8ad36b36ab3cf309deb371b00ddca36f722304`. It must not be exported. The exact source/caller pair is the final `s32`-input callee plus the unchanged production caller.

## Publication requirements

The independent review changed no production source or recipe. The root lane subsequently completed this whole-reconstruction publication route:

1. apply the hash-bound candidate and `2.7.2-cdk-G0` recipe together;
2. journal `whole_c_reconstruction` with both endpoint and cross-control receipts;
3. immediately verify the live callee at the exported recipe;
4. run `dungeon_deep_t8b_1350c74` for the callee and `dungeon_deep_1356` for its sole caller, leaving the caller source unchanged;
5. run the row database check and the normal dungeon publication checks.

If any live verification or required gate fails, restore both the old source and `2.8.1-G0` recipe together and verify the restored endpoint.

Publication completed: live callee exact 210/210; both listed covering windows and SLUS MATCH; row database OK. The source hash above is unchanged. The durable publication receipt is `docs/evidence/pin_research_round45_20260917.json`.
