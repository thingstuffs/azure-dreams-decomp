# Round 96 decisions (orchestrator, under the owner's 10-06 delegation: decide on best evidence, flag SECOND LOOK)

1. **town/func_800A56D0 fake dependency -> sibling two-sided clamp (ACCEPTED).** r96_opus_fd replaced
   `packet + depth_or_page - depth_or_page` (a refused fake dependency since r93_opus_fd1) with the two-sided otz clamp the
   row's siblings carry verbatim (`if (otz >= 0x1E0) otz = 0x1DF; if (otz < 0) otz = 0;` - func_800A3BF4:160-163,
   func_800AC9AC:149-152, func_800A5398:82-87). The `otz = 0` arm is dead (flow deletes its store); its compare keeps the
   first clamp's `otz = 479` live, which is what retail emits. Admissible because it is a copied block a human wrote in three
   sibling functions (owner 09-29: copied blocks OK), not cancelling arithmetic, volatile or a dead memory access.
   Evidence: work/native_lane/r96_opus_fd/MECHANISM.md. SECOND LOOK: yes (dead source code kept for its compiler effect,
   though copied from siblings). If refused: revert the row to the fake and record it in ledger/oddities.jsonl review.
2. **kitlib fake-dependency detector extended** (`x = x;`, `d += h; d -= h;`): tree scan finds exactly the census's sites
   plus slus/w_80043568 `slot = slot;` (new, in r96_sonnet_ot4). SECOND LOOK: no.
3. **dungeon/func_807B08F0 parameters s32 -> s16** (r96_sonnet_ot3, removes a one-trip): no in-tree caller; the third
   parameter was already s16 and the body sign-extends both. SECOND LOOK: no.
4. **81329AC4 is not an oddity candidate:** the empty-fence test is negative (hard basket `next` updated). SECOND LOOK: no.
