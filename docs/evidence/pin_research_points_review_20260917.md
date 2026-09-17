# Independent review: `dungeon/func_819A764C`

Verdict: the reconstruction passes source semantics and interface review and removes three genuine pins without adding constraints. It is a valid `whole_c_reconstruction` positive candidate, not an automatic compiler-cell correction. It is not ready for publication while the rowbase remains `solved` and the source still defines the synthetic name; promotion or a runtime-backed rename is required before the covering gate.

## Bound identity and endpoint evidence

- Live/base source: `base.c`, SHA-256 `060076f5de8fb24367104c6ad2bbf3dcf8f111d70c06a35267d3aa91dc15bbf8`; byte-identical to current `src/dungeon/func_819A764C.c`.
- Reviewed candidate: `candidate_final.c`, SHA-256 `37ce7b2e0a1275e095eef0358df9d1c59520ec16fa140c842fd49a85ce3406d4`.
- Retail row: file offset `0x19C764C`, solved base `0x80024E4C`, 520 bytes / 130 words, SHA-256 `1863f0ead0916ed71e975671e02b9d69fc457c12bd6a95f7615964c90d744d66`.
- Identity receipt: `identity.json`, SHA-256 `43bf418d0cfa5695937af865aea777d7dbfc32b50a55864d749c6995ea61e9a8`.

The recorded endpoints are complete 130/130-word exact matches: the base at `2.7.2 -fno-strength-reduce`, and the reconstructed source at `2.7.2-cdk -fno-strength-reduce`. The scored `globals.c` source has SHA-256 `17cad028314ffc0c05aad6ab3f24ad1a2d1f207f78717d68135f0954d5a26615`; it differs from the reviewed candidate only by whitespace. The diagnostic cross-combinations reject: base under CDK has distance 5, while reconstructed globals under plain 2.7.2 have distance 13. This is the two-valid-endpoint case described by `docs/PIN_RESEARCH_WORKFLOW.md`; neither cross-combination is a publication gate.

## Semantic review

All 130 retail words were reviewed. The three old calls to `func_80025038` encode direct jumps at `0x80024FA0`, `0x80024FB4`, and `0x80025010` to the restore-only epilogue at `0x80025038`. Replacing them with ordinary `return` statements preserves the state dispatch and the `void` result. State 0 still calls the message helper and falls through to state 1 work; state 1 returns after incrementing the state; state 2 performs both flag updates and falls through to the epilogue; unsupported negative or high states return immediately.

`D_80024B20` is the same address previously manufactured as `D_80020000 + 0x4B20`. `D_800814A0[0]` is the word previously addressed as page `0x80080000` plus `0x14A0`. Replacing the old `u32` field view with an `s32` declaration does not narrow the access: both are one aligned 32-bit word, and bitwise OR with positive mask `0x8000` preserves every existing bit while setting bit 15. Current dungeon sources commonly treat this object as a 32-bit flag word and perform the same OR.

The recipe change has a concrete emission mechanism. CDK can split the natural global addresses so the `D_800814A0` high half occupies the branch delay slot and the low half for `D_80024B20` occupies the call delay slot. Plain 2.7.2 does not place the same natural address formation there, matching the failed cross-control.

The fingerprint's lineage conflict is not probative. The four retail delay-slot stores are to object-local fields (three call slots and the local epilogue jump slot), and the retained plain-2.7.2 `local_store_probe.s` independently emits an ordinary local store in a call delay slot. That feature does not uniquely identify CDK; the exact endpoint and address-lowering controls justify the reproducible recipe without claiming a historical compiler lineage.

## Pins and interface

The candidate removes the fake epilogue declaration, the fake page symbol and its keep, and the literal page-base register binding and keep. It retains only the existing `$s2` self binding and its keep: five pins become two. The erasure controls reject removal of either retained site, and no asm, volatile access, fake dependency, ABI shortcut, or replacement constraint was added.

The interface remains `void func_819A764C(void *)`; no argument or return transport changes. A current dungeon-source search finds no direct C call outside this definition. That does not exclude indirect callers, but the unchanged ABI makes their call contract consistent with the candidate.

No compiler, export, gate, production source, recipe, ledger, or rowbase mutation was run as part of this review.

## Publication addendum (root, after independent review)

The accepted live source is `src/dungeon/func_819A764C.c`, SHA-256 `b971d27cfb7a10748b9dfabf7bba834855b626ffe055f45f4ba44051a7b64927`. The sole change after review is the proven runtime definition spelling `func_80024E4C`; rowbase promotion and clean-ledger true-name registration are complete. Fresh full verification, linked-strict bytes, all covering windows, host syntax, SLUS and row database pass. The durable source pair, complete controls and gate records are in [the round-50 receipt](pin_research_round50_20260917.json). Earlier references to live/base source and pending gates describe the pre-publication review snapshot.

## Round 51 semantic naming clarification

The earlier message terminology is inaccurate. The resident definition in
`src/slus/w_8004491C.c` registers a node under a 32-bit identifier; it does not
consume message text. The same-bank `D_80024B20` address corresponds to the
adjacent renderer. This corrects the interpretation, not the reviewed exact
address substitution or source hashes. Cross-file callback typing remains
open; round 51 introduces no source or prototype change. The original round 50
receipt is preserved as historical evidence.
