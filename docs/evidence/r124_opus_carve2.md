# r124 opus_carve2: Manoeva factory and held carve regions

## Manoeva factory (`spawn_manoeva`, DUNGEON +E570B4 and four bank copies)

`src/dungeon/monster/manoeva/spawn_manoeva.c` is the 540-byte Manoeva actor factory at runtime
0x801708B4 (DUNGEON +E570B4). Its ordinary 2.7.2-cdk -O2 -G0 compile links byte-exact over the
complete section. The four other observed copies (+E5D0B4, +E630B4, +E690B4, +E6F0B4) are the same
function in the other Manoeva banks; each is registered as a placement of the home with
address-relocation bindings derived from the complete retail section.

The earlier carve hold (8 register substitutions, tile Y in s6 and position in s5) came from the
statement order of the sprite tile stores. Global allocation ranks pseudos by
`floor_log2(refs) * refs / live_length`; with the tile stores written after the frame-table store,
tile Y lived 23 insns (priority 869) and lost s5 to the position pointer (4 refs over 80 insns,
priority 1000). Writing both tile stores directly after the sprite pointer is loaded (as a 1997
programmer naturally initialises the sprite record) shortens tile Y to <= 20 insns, which gives the
retail roles, while keeping tile X before tile Y so the tile Y store lands in the kind-test delay
slot. No register variables, asm, volatile or goto.

## Troll behaviour copy (DUNGEON +D20CBC)

The 2052-byte region DUNGEON +D20CBC (runtime 0x8015A4BC, bank [0xD1F000,0xD25000), delta 0x7F439800)
is the Troll `update_actor_behavior` body. The existing home `dungeon/func_80CE8CBC`
(`src/dungeon/monster/troll/update_actor_behavior.c`) compiled with its current recipe links
byte-exact over the complete section with 21 bank-local address bindings (all a uniform -0x18000 shift
from the home bank). Its switch jump table (48 bytes, compiler `.rodata`) sits at the bank-start table
slot 0x80158808 (file +D1F008), which the copy's lui/addiu pair addresses; linked at that address the
table contents equal retail. The earlier hold linked only the text section; the table placement is what
closed it. The bank has no bank-wide link list (its rows are separate region views), so this copy gets
its own region view `dungeon/region_d20cbc_d214c0` and a matching per-row rowbase record.

## Flame body-only placements (DUNGEON +A6D07C, +A7307C, +A7907C, +A7F07C)

The Flame module `dungeon_resource06_slot0` (`src/dungeon/monster/flame/flame_actions.c`) owns the
952-byte member `dungeon/func_80A4707C`: a 124-byte entry/switch-table prefix (module `owned_data`,
split record `native_prefix_bytes` 124) followed by the 828-byte body `func_8017087C`. The four other
Flame banks hold only the body at bank +0x7C; their own prefixes are not part of these rows.

Link lists now accept `body_offset` on a home entry. The guard stays exact: a placement of such a home
must be exactly `size - body_offset` bytes, a placement can never carry `body_offset`, and
`row_db.py check` requires the entry's value to equal both the module member's `body_offset` and the
split record's `native_prefix_bytes`, so the prefix remains owned by the module home only. Rule 1 and
the same-image (rule 3) table key the body entry, not the prefix start. New negative fixtures in
`tools/tests/test_linklist.py` (`BodyOffset`) cover wrong body sizes, a copy carrying the key, invalid
offsets, and module/split disagreement.

The home entry is added to `dungeon/bank_a65000` (952 bytes, body_offset 124). The current module
object's `.text.func_8017087C` links byte-exact over each complete 828-byte target with four bank-local
bindings each (the same four recorded by the carve lane's run-5 handoff); the body references no
compiler-local table. Proof scope is the Flame source (module home image plus every placement compiled
from it); no other link entry carries `body_offset`, so the guard change leaves every other image's
inputs unchanged.

Three overlapping bank views, `dungeon/bank_a6d800`, `bank_a73800` and `bank_a79800`, previously ran 0x800
bytes past their own load into the next Flame bank (their delta is that of the bank starting 0x800 below:
0x7F6FD800 for a6d800, matching `img_a6e000_8016b800`, whose proven extent stops at 0xA71FFC). The new
body rows are the first matched rows in those tails, and their retail internal `j` words (for example
0x0805925C at +A7314C = j 0x80164970) carry the next bank's delta (0x7F6F1800 = `img_a74000_80165800`).
Each view therefore now ends at the next bank start (size 0x5800); no entry or proven rowbase lies in the
removed tail.
