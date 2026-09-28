#ifndef SHARED_DUNGEON_STATUS_H
#define SHARED_DUNGEON_STATUS_H

/* dungeonStatus: the global block at 0x80083460 (SLUS .bss; read and written by the DUNGEON overlay and by
 * the SLUS dungeon-entity helper slus/w_80042BDC).  One object: 527 of the 836 rows that touch
 * 0x80083460..0x8008347F form ONE lui/addiu base at 0x80083460 and reach every field below from it
 * (r78 types pilot census, work/native_lane/r78_types_pilot/census/).  Nothing between 0x80083480 and the
 * next object (0x80083498, passed around by address) is accessed, so the size stops at 0x20.
 * Retail's lui/addiu (not $gp) in slus/w_80042BDC, compiled -G16, shows the original declaration was
 * larger than 16 bytes.  Widths/signedness are the retail access widths (lh = signed, lhu = unsigned;
 * the minority of the other kind are casts at the use).  Names: only what the accesses prove. */
typedef struct DungeonGlobalStatus {
    /* 0x00 */ short unk_00;            /* lh / sh */
    /* 0x02 */ unsigned short flags;    /* lhu only; every use is a bit test or bit set (0x2000, 0x1000, 0x80, 0x8, ...) */
    /* 0x04 */ short unk_04;            /* lh 21, lhu 10, sh 28 */
    /* 0x06 */ short unk_06;            /* lhu 1, sh 3 (sign unproven) */
    /* 0x08 */ short unk_08;            /* lh 66, lhu 75, sh 77 (slus/w_80042BDC subtracts from it) */
    /* 0x0A */ short unk_0A;            /* a counter (+1 / -1).  s16, not u16: every lhu site is a load-modify-store (exact either way) and 42 sites read it with lh; declared u16, 11 rows miss by that one lh (r78 A/B: 797 vs 786 exact) */
    /* 0x0C */ void *unk_0C;            /* lw / sw; cleared to 0, compared with a target entity pointer (func_80087A70) */
    /* 0x10 */ void *unk_10;            /* lw / sw; holds an entity pointer (func_800CED34: state - 0x20) */
    /* 0x14 */ short unk_14;            /* lh 5, lhu 6, sh 8 */
    /* 0x16 */ short unk_16;            /* never accessed */
    /* 0x18 */ unsigned char *unk_18;   /* lw only: a pointer to a byte table (spawn table, func_8009B140) */
    /* 0x1C */ short unk_1C;            /* lh 4, lhu 7, sh 4 */
    /* 0x1E */ unsigned short unk_1E;   /* lhu 15, sh 2 */
} DungeonGlobalStatus;

extern DungeonGlobalStatus dungeonStatus;

#endif
