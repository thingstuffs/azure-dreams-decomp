#ifndef SHARED_OBJECT_FLAGS_H
#define SHARED_OBJECT_FLAGS_H

/* objectFlagBlock: the global at 0x800814A0 (SLUS .bss), used by SLUS, MAIN, TOWN and DUNGEON code (1,083 rows).
 * `flags` is written almost only as `flags |= 0x8000`, right after an object's own header word gets its 0x8000
 * mark (`entity[-1] |= 0x8000; D_800814A0 |= 0x8000;` when a countdown or motion finishes), so bit 0x8000 records
 * that some object carries the mark.  No C row tests it yet; the reader is still asm.
 * Declaration evidence (r78 phase 2, per-row A/B against retail):
 *   - an AGGREGATE of 9..16 bytes: -G8 split rows reach it with lui/%lo, never $gp (4/8 bytes miss, 12/16 exact);
 *     -G16 SLUS rows use the bare macro form (20 bytes / unknown size miss); and declared as a scalar `int`, 196
 *     rows miss (the aggregate's MEM_IN_STRUCT alias class moves the schedule) - 681 rows are exact as below;
 *   - but 22 rows (SLUS stock 2.7.2 -G0, MAIN, TOWN) were compiled against a SCALAR int: every aggregate spelling
 *     turns their direct `lw D`/`sw D` into `la` + 0($r).  They keep `extern int D_800814A0;` (REPORT phase 2).
 *   - 0x08..0x0B are the bytes of D_800814A8, a pointer (228 rows) that retail declares SEPARATELY: as a field
 *     here, 23 of 38 functions using both hold a shared base register and miss.  unk_08 only reserves the bytes. */
typedef struct ObjectFlagBlock {
    /* 0x00 */ int flags;               /* lw 725 / sw 723 sites (677 rows); |= 0x8000 at almost every one */
    /* 0x04 */ unsigned char unk_04;    /* lbu/sb: slus + main only (D_800814A4) */
    /* 0x05 */ unsigned char pad_05[3]; /* never accessed */
    /* 0x08 */ unsigned char unk_08[4]; /* = D_800814A8, declared separately in retail (a pointer; not migrated) */
    /* 0x0C */ unsigned char unk_0C;    /* lbu/sb: slus + main only (D_800814AC) */
    /* 0x0D */ unsigned char pad_0D[3]; /* never accessed */
} ObjectFlagBlock;

extern ObjectFlagBlock objectFlagBlock;

#endif
