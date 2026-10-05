## Removing scaffolding `volatile`s (round 93: r93_opus_c9858, r93_sonnet_vb1-vb3 - 33 volatiles off 12 of 22 rows)
A `volatile` in decompiled C is usually m2c/lane scaffolding that holds ONE compiler decision. Erase each one alone
first (`erase.py <row> --with-scaffold` lists VOL# sites + cost), read what moved (diff.py), name the pass
(combine.py --insn, why.py --pass cse/sched --deps-table), then pick the real C shape. Keep real ones: PS1 hardware I/O
(0x1F801xxx/0x1F802xxx/0xBF80xxxx) and flags polled in a busy-wait loop.
Shapes that were exact this round:
1. `lbu; sll 24; sra 24` (byte kept unfolded): an s8 byte extended into an s16 target that does NOT span a join
   (duplicate the join stores into each arm); byte loaded into an s8 local set in each arm when sched1 boosts it.
   cdk extendqihi2 writes (subreg:SI (reg:HI)) -> combine's lb merge is NO RECOG. (800C9858, 800CB068, 800C13E0,
   818EC800, 8125192C)
2. Reload after a store through ANOTHER pointer: access both the store and the read as struct members (tiny pad
   typedef) - cse invalidate_memory kills only in_struct entries on a pointer store. (818EC800, 800C13E0)
3. Reload after a store of the same field: put the store in each if-arm (jump2 cross-jumps them back) so the read sits
   after a join label and cse cannot forward the stored value. (w_8004CE68)
4. Loop-test load merged with the body load: `if (c) { do {...} while (c); }` loop shape. (w_800491F4)
5. Loads reordered by a plain read: write the field expressions directly in the condition / compute a shifted value
   once in its own statement / counter loop with `cursor = base + i*4` at the top (register-base giv). (w_8004BDDC,
   8096BCF0, w_80043568, 800BB2E0, 8096D1C4)
6. A volatile that stops jump threading from merging two identical tests: spell the first test the way the loop
   addresses it (8046BBF8 - spelling trade).
7. A `volatile` STACK struct with 8-byte-spaced members reloaded through one scratch register (often with REG pins on
   $8/$9) = m2c imitating reload of SPILLED s16 parameters/locals (.greg 'Spilling reg 8'; reload gives HImode spills
   8-aligned slots): delete the struct and use the s16 variables directly. (819BF9F4: 4 pins + 3 volatiles -> 0)
8. A re-read right after its own store held by volatile/KEEP: move the read after the SIBLING store through the same
   pointer (cse invalidate_from_clobbers drops the stored value on a varying-address store). (8180C3C0)
9. Byte re-read in a min/max arm that post-reload cse would fold: give the arm an HImode destination (reload_cse skips
   a mode mismatch). (819BF9F4)
10. Field RE-READ after its own store / an earlier read (retail reloads, plain C forwards): read it into a FRESH s32
    local (`t = p->f;`) - cse does not forward a zero-extended read (a u8 local IS forwarded); write the field ops as
    compound assignments on the field (flow keeps the earlier store, cse cannot fold the constant). (r93_opus_vb3:
    8096C508 4 volatiles -> 0, 8046C188, 818FA12C)
SLUS rows are scored by object identity vs the pinned TU: replacing a literal page constant with its symbol adds
relocations the target lacks - keep the page macros on slus rows.
11. RELOAD CLASS - a field reload plain C forwards with no store/call between (r93_opus_rl1, 5/5 rows exact). Find
    which gate removes the load: dump the plain text and check the second read after .cse, .combine, .greg.
    (a) cse block: cse continues its table through an `if (c) x = ...;` skip and into a jumped-to else arm; it
        restarts only at a label reached by FALL-THROUGH -> turn the skip into if/else with the next statement in
        BOTH arms (jump2 merges them back). w_8004D294.
    (b) cse table: a store between the reads kills the entry (QImode store, non-struct pointer store); retail's stores
        may have been sunk by sched1 -> write each store right after its computation (compound `f op= expr`). 800A76D4.
    (c) narrow then wide: cse forwards a narrow load from an earlier zero_extend load, never the reverse -> make the
        first access narrow (`(u16)x >= f`, a u8 test, or a store) and the second a widening int read; a u8 `>> k`
        is narrowed and forwarded, `/ 2^k` or an unsigned-int local is not. 8009A3D4, 8096C360.
    (d) post-reload: two loads survive combine but one is gone in .greg -> reload_cse deleted it (same register still
        holds the value): change what writes that register in between (e.g. `t[k * 32]` vs `t[k << 5]` changes expand
        order). 800BB6A8.
    Shape 10 (fresh s32 local after a store) is gate (c) + (d). Never kill an entry with a dead store/load/call
    written only for that - fake dependency.
12. Macro scaffolding: VOL_U32/VOL_PTR/VS16_AT/VPTR_AT-style accessor macros often cost 0 when replaced by their
    plain twins (FIELD_U32, S16_AT ...) - try that first (vb8/vb9: 8187B5A0, 813315CC, 81910EC0).
13. A ladder of m2c temps with volatile on 1-2 members around field RMWs: one compound assignment per field in the
    order retail stores them (permute a handful of natural orders; 8186EDA8, 80921A44).
Open: volatile u8* STORES through an induction pointer (80284068: loop.c biv->giv); volatiles that only order a
read-modify-write triple in sched1 (8105F098); SPU/GPU/CD hardware registers are REAL volatiles; volatiles that only order two
independent loads in sched1 (6-row clone family 80C8D084..80BE5084, 818CE83C, 818F9B98); frame-pad volatile locals (no
evidence for a real local); a dead store combine would merge (8132F204).
