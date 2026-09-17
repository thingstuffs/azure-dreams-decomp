# Independent review

## Verdict

`v4_index_first.c` is semantically suitable to replace the pinned live source, subject to the normal publication gates. It preserves the entry contract, the allocation and cleanup behavior, the eleven-entry initialization, the signed link-table lookup, the helper argument values, the flag store, and both return values. It removes all four local code-generation constraints and adds none.

The current linked-strict receipt reports `MATCH`, byte-exact `416/416`, at the proven runtime base `0x8008B654`, using compiler SHA-256 `2dfa41a50f60ce63ff82b57cd07701213c3a5e96cd8324b32328d49cd9ccf174`. This is strong function-body evidence. It is not a substitute for the actual `town_scene.overlay.yaml` covering-window gate or the other publication checks; those remain for the landing owner.

## Semantic review

- The allocation loop starts with count zero and advances the object cursor, resource cursor, and count only after both allocations succeed and the resource has been initialized. A successful path therefore records exactly eleven complete object/resource pairs before initialization begins.
- On failure, each cleanup loop predecrements its cursor and walks back to its array base. Every completed object is passed first to `func_8003FFF0` (unlink) and then `func_80040044` (return to the free list); every completed resource is passed to `func_80033C84`. This agrees with the helper implementations and the retail reverse-order loops.
- If resource allocation fails after the current object allocation succeeds, that just-created object has not yet been placed in `objects[]` and is outside rollback. This potentially surprising behavior is inherited deliberately: the live source and retail body do the same thing. The candidate neither creates nor fixes it.
- The success loop resets the two cursors and the reused index, then executes eleven iterations (`index` values 0 through 10). Argument evaluation order in `func_8008B818(index, linked_data, *object_slot++, *resource_slot++)` does not alter values because the two postincrements modify distinct cursor variables and `index` changes only in the following statement.
- `D_800CFC2C` remains `s8[11]`; assignment to `s32 link_index` sign-extends, matching retail's `lb`. A self-link produces zero. Any other entry indexes `objects` and adds byte offset `0x20`, matching retail's signed scale/load path. Like retail, the C has no bounds check, so table validity remains a data invariant rather than a new candidate guarantee.
- The current object state receives zero at `+0x74`, the second entry argument at `+0x78`, and the first at `+0x7c`; `func_8008B818` then receives the index, linked-state pointer or zero, object, and resource. After all eleven calls the candidate clears `D_800FC418` and returns 1; either failure path returns 0.

## Contracts and callers

The candidate keeps `s32 town_map_set(s32, s32)`. `config/names.tsv` maps runtime `func_8008B654` to `town_map_set` and records its indirect town script-table entry; `include/script_symbols.h` exposes the corresponding script IDs. The narrow source census found no direct C call in `src/town`, but that must not be read as absence of indirect callers. The two-argument MIPS32 entry ABI and 0/1 result are unchanged.

The adjacent definition of `func_8008B818` takes `(s32, s32 *, void *, void *)` and uses the second argument as either null or a pointer to linked state, the third as the object, and the fourth as the resource/context. The candidate supplies those same 32-bit values. The allocator definitions confirm `func_8003FC64(s32)` and `func_80033BE4(void)` return pointers; the candidate retains the live source's local `s32` transport for those pointers, and similarly retains scalar local declarations for pointer-taking helpers. That is ABI-equivalent on the target's 32-bit data model and does not change any shared declaration, although it is inherited type debt rather than a portable host interface.

`func_80033C1C` initializes a resource/context, `func_80033C84` clears it, and the object cleanup pair unlinks and then returns an object to the free list. Their implementations agree with the call order and ownership described above.

## Retail-map and evidence notes

The complete `retail.dis` covers 104 instructions from runtime `0x8008B654` through `0x8008B7F0`, including branch and jump delay slots. Its allocation, both rollback loops, signed-byte lookup, eleven-call initialization loop, flag store, shared failure epilogue, and success return all correspond to the candidate.

`SITE_MAP.md` describes those regions correctly by instruction content, but its displayed addresses use the row/file identity range `0x8008DEF4..0x8008E093` rather than the proven linked runtime range `0x8008B654..0x8008B7F3`. That documentation offset should not be used as runtime-address evidence. The linked-strict receipt and `retail.dis` use the proven base.

The historical row `src_sha` is only an older snapshot and has no bearing on this semantic verdict. Publication should bind the actual candidate and run the covering window rather than accepting the hash discrepancy or the scorer's true-base warning as a gate waiver.

## Bound artifacts

| Artifact | SHA-256 |
|---|---|
| `v0_live.c` / current production source at review time | `7958e89933cd45eb1a596f62e5bae2fca8d817756fa1369a388e74e750b70d07` |
| `v4_index_first.c` | `e48038942fc15d880ed9a38bca4d65a77558757f16b965ab74f45f755f384020` |
| `retail.dis` | `0dcd23a915dbb0dda0cd2c02e3530f61b0fcd096912f1f417f852113063e2e12` |
| `SITE_MAP.md` | `57851a59559321c076974c0f6a90c441b1c0994445f74f290b48a0b6b905e8cf` |
| `strict_final.json` | `766b3cea7909d38bebfc1cf3fe568b37401bd41b92237735ba1bf388bb7c7476` |
| `row.json` | `240c17bb47b5dc7aac309b80c5232fbfbc678f9bfeb020b98297be9dc3502093` |
| `src/town/func_8008E0B8.c` (`func_8008B818`) | `2d0c75939dc669234d82c3d1c49e3f6411f3849400e32d2df58987f96724861b` |

Publication addendum: reviewed source is now live unchanged, SHA-256 e48038942fc15d880ed9a38bca4d65a77558757f16b965ab74f45f755f384020. Root reproduced full linked-strict 416/416 bytes; covering town_scene window, host syntax, SLUS and row database pass. Evidence is retained in pin_research_round53_20260917.json.
