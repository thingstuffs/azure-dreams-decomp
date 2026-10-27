# Near-match completion: casino setup and Ghosh front attack

Two complete functions left as near-matches by the r124w carve lane are now
byte-exact C. Both were compiled at their attributed recipe (2.7.2-cdk -O2 -G0)
and proved through maspsx and genuine ASPSX 2.79 (-q -G0) with identical complete
units, zero masked relocations and no allocated data sections.

**initialize_casino_minigame** (TOWN +0x79DA98..+0x79DD70, 728 bytes, VMA
0x80020298 in town/ll3a_79d800_7a1c60). The carve lane's candidate emitted 724
bytes because combine folded the betting model's callback-data store into a
node-relative address. In retail the body pointer is taken before the
register_node call: gcc 2.7's combine never merges an address computation into a
use across a call (can_combine_p, `INSN_CUID (insn) < last_call_cuid`), so the
pointer survives and is rematerialized next to its store. Writing
`main = &node->body.main;` before `register_node(...)` reproduces all 728 bytes.
The function returns s32 0 like the other minigame setups: a void version drops
retail's final `move v0, zero`. scr_func_sn_casino now calls it by name; its
object differs only in the relocation symbol name.

**begin_ghosh_front_attack** (DUNGEON +0x1344F20..+0x13450AC, 396 bytes, VMA
0x8016C720 in dungeon/bank_1343000). The body is the twin of Beldo's
try_actor_attack (different action bytes); retail's 0x40 frame reserves the same
eight unused local bytes, reproduced the same way. get_actor_height_difference is
called with an int-returning declaration (an s16 prototype adds a sign-extension
retail lacks). The complete function absorbs the eight-byte terminal row
dungeon/func_813250A4 (its return), which is retired. Both callers
(advance_actor_path in ghosh/get_y_step.c, update_main_actor_action_and_facing)
now call it by name; their objects differ only in the relocation symbol name.
