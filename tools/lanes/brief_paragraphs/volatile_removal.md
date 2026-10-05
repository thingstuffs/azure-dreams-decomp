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
14. LOAD-ORDER volatiles (r93_opus_so1, 8/8 rows, 16 volatiles). Erasing the volatile swaps two independent memory ops
    in one block; plain C has no edge between them, so look for what ELSE decided the order:
    (a) birthing-boost tie at a block head (both prio 1): `why.py <row> --pass sched --block bN --trace --variant
        plain.c` shows the load that retail emits FIRST being picked `[launched: birthing boost]` at a later tick than
        the other. cdk schedules backwards, so the boosted load is emitted LATER: give the load that must come SECOND a
        single-set destination. Typical cause: m2c reuses one pointer for two objects (`packet = scratch->current;` at the
        loop head and again for the draw-mode packet) - one variable per object fixes it (6 clones 80C8D084..80BE5084,
        818CE83C). A fresh temp on the load that must come FIRST does nothing (it is already single-set). Signature:
        `*(T * volatile *)&s->f` / `*(volatile u16 *)&p[k]` at a loop head where the assigned variable is set again later.
    (b) store vs later load, disjoint offsets of one base, right after an if/else join whose arms both end in the same
        read (`} else { x = p->f; }` - m2c's copy of a jump2 cross-jump): the store belongs IN BOTH ARMS next to that
        read; jump2 merges the tail back in front of the join and sched1 never sees the store and the load in one block
        (818F9B98). Struct/non-struct spellings cannot help here: same base + disjoint offsets has no alias edge.
    Never order them with a dead load/store or a fake dependency.
15. m2c's rotated loop `if (*p != 0) { x = *p; do { ...; x = *++p; } while (x); }` with a volatile on the read: write the
    plain `while (*p != 0) { *dst = *p; p++; dst++; }` - gcc's own loop rotation emits retail's test + reload (r93_sonnet_vb11,
    slus/w_80049004, 2 volatiles -> 0; converting only one of two loops = dist 1).
16. Volatile cursors walking parallel arrays in a counted do-while: an indexed `for (i = 0; i < N; i++)` over `A[i]`/`B[i]`
    (plain-pointer loops stayed dist 31; r93_sonnet_vb15 dungeon/func_80099818).
17. `x = *(volatile u16 *)p; ... p->f = x + 1;` snapshot-then-store: the compound `p->f++;` (4/5 exact; the snapshot local
    and any one-trip block around it go too - town/func_809533D8, 8081CC54, 8081AA30, 8081617C).
18. A volatile that forces a RELOAD of a global struct's pointer after a store through it (e.g. `*(u8 **)((u8 *)&gameWork)`
    re-read after `->unk_B0 = ..`): cse invalidates only in_struct entries on a struct store, and the raw-cast reads are not
    struct reads. Spell EVERY read of that pointer, from the first one to the volatile site, as the member
    (`gameWork.unk_000`) and drop the volatile; changing only the last read stays off (r93_sonnet_vb14, 4/4: 80C96640,
    81922998, 819A088C, 81970800).
19. RMW then reload of the same field (`f += x; f = f & 0xFFF;` held by volatile): a fresh s32 local read between the two
    stores (`f += x; t = f; f = t & 0xFFF;`) (r93_sonnet_vb18, 2/2: town/func_800BC77C, 800BC238).
20. `*(volatile s32 *)&G[0]`-style reads of a global vector: declare G as its struct (`Vec3`) and read members (8009D610).
21. Two stores to the SAME field in a row (`f = x | 0xC; f = f | 2;`, or `f &= ~7; f |= m;`) held by a volatile: flow.c
    (last_mem_set, cygnus dje/8176) deletes the first store when no memory op sits between them in SOURCE order, and cse
    folds the two ors. Write one independent memory op (a sibling-field store OR a load of another field) BETWEEN them; sched1 moves it back to retail's place
    (r93_sonnet_vb24/vb25, 5/5: 81251350, 80B9ADE0, 8092192C, 80B47980, 80A4B678; vb26 +4 incl. a load between: 8180E7F4, 800B73A4).
    NOT this class: a second store deleted by reload_cse_noop_set_p (reload1.c, "register known equal to memory") -
    8180A990, open.
22. A `volatile s32` stack PARAMETER (5th+ argument) copied into a local used once: make the parameter `s16` (its real
    width) and use it directly, drop the copy - local-alloc update_equiv_regs otherwise moves the single-use load down
    to its use (r93_sonnet_vb27, 4/4: 80095658, 800B3868, 800A3714, 800A2EA8).
Open: volatile u8* STORES through an induction pointer (80284068: loop.c biv->giv); volatiles that only order a
read-modify-write triple in sched1 (8105F098); SPU/GPU/CD hardware registers are REAL volatiles, and so is library state shared with an interrupt handler (written
inside EnterCriticalSection, a callback pointer reloaded between test and call) - ledger/real_volatiles.jsonl lists the
classified sites; check a global's writers (`git grep -n 'D_X\s*=' -- src`) before working one; frame-pad volatile locals (no
evidence for a real local); a dead store combine would merge (8132F204).
