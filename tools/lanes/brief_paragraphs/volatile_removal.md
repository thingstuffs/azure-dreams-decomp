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
Open (no exact shape yet): retail reloads a field that plain C forwards from the previous load with no store/call
between (800A76D4, 8096C360, 8096C290, 800BB6A8, 8080EEC4, 81334230); volatile u8* STORES through an induction pointer
(80284068: biv -> giv); a reload that post-reload cse deletes because the register already holds it (w_800565D8).
