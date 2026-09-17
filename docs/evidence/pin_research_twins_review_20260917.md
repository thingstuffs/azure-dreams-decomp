# Independent review: twin item-return candidates

Verdict: no semantic or constraint blocker found for `func_80E9D000_final.c` or `func_80EA3000_final.c`.

The only functional edits are the intended ones. Each candidate removes the synthetic local-epilogue declaration/call, uses the already-declared shared-slot symbol in the two later store paths, returns that slot through the existing `s32` result, and removes three `ASM_KEEP` sites. The old pointer-to-`s32` return transport is unchanged. The first literal-page path and its keep remain, as do the two existing `ASM_REG` bindings. No signature, type, section, bank initializer, compiler recipe, or new constraint changes. This review makes no claim that indirect callers are absent.

The shared addresses are exact: `0x80160000 + 3065 * 4 = 0x80162FE4`, and `0x80160000 - 3079 * 4 = 0x8015CFE4`. The retail last path loads the item word, forms the corresponding shared address in `v0`, stores the word, clears `target+0x48` in the jump delay slot, and enters the restore-only epilogue. Replacing the fake jump with `return (s32)shared_slot` therefore preserves the retail return value. The common epilogue does not modify `v0`.

The 264-byte data prefix is unchanged; the reviewed body is the following 123 words. Current `strict.json` records linked-strict 189/189 whole-row matches with zero substitutions, indels, positional words off, or relocation masking for both twins. It binds directly to final/current source hashes `acb7370849fd75e76a014744431c9bebac577c814fe5ae438fff93466759afc5` and `80db96ed6ee511b3b0b4098e7f640fffbc7d8bc6d716d1bf5df6547ff5d81f85`. Each production source is byte-identical to its corresponding `*_final.c`; both 756-byte covering-window checks in `gates.json` also report `MATCH`.

The negative controls are discriminating. `return_only.c` misses 11 register substitutions; `direct_shared.c` is a four-indel store/jump reorder. The three typed erasures per twin all fail (slot rotation, one-word length drift, and register rename), leaving exactly one keep and two register constraints in each final source.

This was a read-only source and artifact review; no compile was run here. The supplied strict, covering-gate, and host-syntax results cover the current candidate files.

Durable source, check and routing evidence: [round 49 receipt](pin_research_round49_20260917.json).
