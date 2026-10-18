# LL6 supplied leftovers evidence: metadata summary

Source: owner-supplied LL6 leftovers analysis, preserved here with the
lane brief. SHA-256: `a4d645547735f9fb390c98451f85c19101978ff96a7cbcf77e6a0ce4ae64bd3e`;
length: 13515 bytes. This summary omits dialogue, symbol-dump contents,
source fragments, raw descriptor words and all other retail payloads.
The cited investigation was static; it did not run the game in an emulator.

## Scene records and zero-base builds

The TOWN scene table at file offset `0x564A0` contains 25 eight-byte load
descriptors. Their records lie within `0x7EF000..0x87C000` and contain drafts
linked at `0x80700000`. The shipped dialogue instead resides in module message
banks. The report found no shipped US or JP script calls of the draft dispatcher
`S_flgtst`; the matching optional descriptor consumers also had no callers.
Runtime CD-read confirmation remains open. The masked descriptor address is
`0x16000`; the matched resident loader derives its sector count by shifting the
first word right 23 bits. See `src/slus/w_8003E758.c` case 6 and
`src/town/func_800C374C.c`.

The report found 24 of 25 zero-base twins. Complete per-twin extents and relocation
comparisons were not supplied. A starts `0x834800`, B `0x83A800`, C `0x844000`.
Decision 52 admits these alternate builds as static code with runtime placement
unproven; it does not establish identical TUs for every alternate. Other units
at `0x83C000` and `0x85C000` were only skimmed. LL6 maps only the three bounded
prefixes corroborated by existing MATCH rows; full twins remain held.

## Debug NPC and test shop

The report identifies debug-NPC units at TOWN `0x84E000` / `0x868000`, and shop
units at `0x80B800` / `0x84C000`. LL6 independently verifies equality of the
2048-byte slices at each pair of starts. An optional SLUS descriptor selects one
unit in each pair; the supplied static analysis found no callers of its loading
functions. Slice equality does not establish complete unit boundaries or a
compiled shared TU. The report mentions four shop copies but supplies only these
two starts; the other placements and four-copy claim remain held.

## Developer residue

The report identifies a symbol dump at `0x80C000..0x82B914`, a developer path table
at `0x7F877C..0x7F8894`, debug struct/type tables at `0x862B00..0x863900`, assembler
source text starting `0x82E800`, and a link line at `0x832838`. LL6 bounds the two
text anchors only through the first NUL within 16 KiB. Detailed types stay pending.
The continuation validates two 36-byte record arrays (678 and 2,909 records),
separated by an opaque 168-byte region. This reconciles all 3,587 records and the
129,300-byte extent without calling the separator padding. Exact region hashes
and optional-descriptor bounds are in `link/leftovers/evidence/audit.json`; the independent
whole-TOWN slice search finds two occurrences for each optional 2,048-byte unit.

## Limits

Japanese material in shipped modules 3/4 and adjacent module 50 banks is not
classified as unused: the report leaves runtime loading open. Shifted or old
images elsewhere are not leftovers merely because they differ from the resident
build. Static reachability, identity hashing, C compilation and runtime loading
are separate claims. No missing span, type or shared-source identity is invented.
