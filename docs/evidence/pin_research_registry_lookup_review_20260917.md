# Round 44 review: typed snapshot-registry lookup

## Verdict

`typed_lookup_final.c` is an admissible zero-pin candidate for `dungeon/func_8008E714` (runtime `func_80093E74`). It replaces a manually staged pointer-to-integer address calculation with the ordinary typed lookup `record_table[saved_index]`. The function remains linked-strict byte-exact at the recorded stock recipe, its API and 140-byte copy are unchanged, and the source evidence supports `D_800E3DF0` as an ordinary pointer registry.

The final candidate is the version with the now-unused `record_slot_addr` declaration removed. Its SHA-256 is `d9d14f90649801cadb6ac441ea6c796c5c830beebfbb5679e8089d4ace1c109d`.

## Provenance and verification

- Row: `dungeon/func_8008E714`, runtime entry `func_80093E74`, file offset `0xAE714`, 440 bytes / 110 words.
- Recipe: stock `2.7.2-cdk-G0`; assembler flags `--fill-shadowed-return-delay`.
- Actual checked-in source captured as `base.c`: SHA-256 `a82072ab0182abdc3f2391a3a756b055498694fc62eea619f211855e0f3ad3bc`.
- The row metadata in `row.json` still carries older `src_sha` `e77480fe8074b7d1b09e1a34b0d304cadbd70206f242256ee2c29aecf6a3b127`; the candidate and this review use the actual current-source SHA above as the landing base.
- Retail target SHA-256: `dd25a70f4d6e6239484459a6aceee90653c91b4ad59cde314264a04ebef18813`.

An independent baseline score is exact 110/110 with zero substitutions and zero indels (`base_independent_verify.json`, SHA-256 `4f090123b62471e9a6bdd45c2f2d6608647b11673d9b1d5980493882dcc40e0c`).

The final candidate independently passes the direct compiler oracle in linked-strict mode: 440/440 bytes, 110/110 words, zero substitutions, zero indels, zero positional differences, and no relocation suspicion. It links at the proven runtime base `0x80093E74` in `xfer_dungeon_A3000` (delta `0x7FFE5760`). The strict receipt is `typed_lookup_final_strict.json`, SHA-256 `cac7d9c2d068713a42dcbaba1eb08df076b868d814a0ac7866315c561551d7b7`. The compiler SHA is `7a571911a97cef0c6b7b5d4174e89ac54f9806ce3d4b233c0f8620e3503c672b`; the comparator SHA is `54b4b6488120f2e418f3083080b814a52f7e64be57ef5b07b3fd341343af83ce`.

Generated compiler assembly `typed_lookup_final.s` has SHA-256 `43354178efbb51b15ebbeb69e1cc4f930eb44398abcbd78d2006f09015ecf324`; translated assembly `typed_lookup_final.maspsx.s` has SHA-256 `ddead83bbbcd52a86a84c0dd8e24df6840b7419131b85bd3f1e7ae8c4804bc84`.

## Source change and causal control

The original sequence was:

```c
record_table = D_800E3DF0;
ASM_KEEP(record_table);
record_slot_addr = saved_index << 2;
record_slot_addr += (s32)record_table;
stored_record = *(void **)record_slot_addr;
```

The final sequence is:

```c
record_table = D_800E3DF0;
stored_record = record_table[saved_index];
```

The erasure-only control `erase_only.c` removes `ASM_KEEP` but retains the integer-address staging. It remains 110 words yet is nonexact by five substitutions, all in region R2, with residue class `const-remat`. Its source SHA is `354f203088b631409ed72c38b8bbed08e42926440a416284175b837aa5fae6c4`; its linked-strict receipt `erase_only_strict.json` has SHA-256 `b0fb950cf79d6e62d3a943d704d052a1d7bdf9edd7f18697e7b1fb7f80ab1763`.

The assembly identifies the precise cause. With typed indexing, CDK emits the retail order and register partition:

```asm
lui    $3,%hi(D_800E3DF0)
addiu  $3,$3,%lo(D_800E3DF0)
sll    $2,$19,2
addu   $2,$2,$3
lw     $4,0($2)
```

Erasure alone emits the shift first, assigns the table base to `$v0`, and keeps the combined address in `$v1`:

```asm
sll    $3,$19,2
lui    $2,%hi(D_800E3DF0)
addiu  $2,$2,%lo(D_800E3DF0)
addu   $3,$3,$2
lw     $4,0($3)
```

The repair therefore comes from the compiler RTL address form of a single typed array lookup. It is not a successful bare pin erasure. The subscript naturally makes the registry base the stable operand and the scaled index/result the temporary, replacing the lifetime effect previously imposed by `ASM_KEEP`.

## Registry and index semantics

The function reads `slot_entry->unk_03`, clears bit `0x20` in the stored byte, and derives the index with `flags_index &= 0x1F`. The subsequent `u8` and `s16` assignments preserve a value in the range 0 through 31 without adding any narrowing in the candidate. Both `record_index` and `saved_index` represent that same value.

The function first performs the same typed operation through another local:

```c
source_table = D_800E3DF0;
record_slot = source_table + record_index;
source_record = *record_slot;
```

It may refresh source byte `0x13` from byte `0xA8`, computes `D_800E3E48 + index * 0x8c`, writes that address back through `*record_slot`, and copies the 140-byte `Copy140` prefix there. Reloading `D_800E3DF0[saved_index]` consequently retrieves the just-installed same-index snapshot pointer before clearing bit `0x4000` at record offset `0x14`. The typed replacement expresses exactly that registry lookup.

Independent source users corroborate this contract:

- `func_800B1364` writes `D_800E3DF0[save_slot] = D_800E3E48 + save_slot * 0x8c`, copies a record into that slot, and later reads the table with an entry byte masked by `0x1F` before clearing the same `0x4000` flag.
- `func_8008E8CC` declares `D_800E3DF0` as `DungeonSlot *[]` and reads a typed record flag through an index masked by `0x1F`.
- `func_8009EB38` binds the symbol to `DungeonSlot **` and compares table entries by indexed pointer lookup.
- `func_802833F4` clears `D_800E3E48` as an ordinary `0xAF0`-byte region, exactly 20 snapshot slots of `0x8c` bytes, while the wider source audit documents the same-index registry/snapshot relationship.

These are ordinary mutable RAM objects. There is no volatile, MMIO, or synchronization contract to preserve. The typed lookup also removes the implementation-defined pointer-to-`s32` round trip from the old spelling; it applies pointer scaling directly and remains equivalent on the 32-bit retail target.

The existing `Copy140` assignment is unchanged by this candidate. Its disjoint-or-exact-self copy contract was reviewed separately in `docs/evidence/pin_research_snapshot140_review_20260917.md`; this candidate neither changes its source, destination, extent, ordering, nor qualifications.

## API and caller review

The definition remains:

```c
void func_80093E74(s32 slot_table, void *unused_arg1,
                   void *unused_arg2, S_80093E74_0 *owner)
```

`func_8008DCFC` calls it as `func_80093E74(actor, map, entity, context)` after confirming the context's selected object exists. Its old-style extern does not impose a conflicting return use. `func_80CC2828` declares an explicit four-pointer, `void`-return interface and calls it with the global context and two tables. The first definition parameter is presently spelled `s32` while callers pass an address; on the 32-bit PSX ABI these are the same one-word argument, and the body performs address arithmetic with it. That pre-existing type debt is outside this one-pin change. The candidate does not alter the signature, calling convention, return behavior, or any argument conversion.

## Pin and landing checks

`pin_census.sites_of` reports one live site in the base, `ASM_KEEP(record_table)`, and zero in the final candidate. `hidden_asm` is empty for both. There are no `NON_MATCHING` or `#if 0` arms, so both unscored texts are empty (SHA-256 `e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855`). `landing_refusal` returns `None`, including the port compile/lint check.

All new artifacts are confined to `work/native_lane/r44_snapshot_registry/`. No production source, recipe, configuration, ledger, export, or build-root file was changed.
