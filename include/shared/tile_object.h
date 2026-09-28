#ifndef SHARED_TILE_OBJECT_H
#define SHARED_TILE_OBJECT_H

/* TileObject: the object at 0x80082E80 (SLUS .bss), 290 rows (dungeon, town).  NOT an EntityRec: the census puts
 * words at 0x28/0x2C/0x30 where EntityRec has bytes, an s16 and padding (r78 phase 5).  What it shares with the
 * entity record is the map-grid position bytes at 0x24/0x25 (lbu 351/353: tile distances, func_8009FB34 map
 * lookups; the 0x24 pair is also read as one u16 - a view).  func_800A08A0 keeps new monster spawns more than 0x20
 * tiles away from it - plausibly the player's own record, not yet proven, so the object keeps its address name.
 * Layout generated from the access census (tools/layout.py); size at least 0x144 (last access 0x140). */
typedef struct TileObject {
    /* 0x000 */ int unk_000;              /* lw 1 (1 rows) */
    /* 0x004 */ signed char unk_004;      /* lb 1, lbu 1 (2 rows) */
    /* 0x005 */ unsigned char pad_005[0x1];
    /* 0x006 */ unsigned short unk_006;   /* lhu 1, sh 8 (6 rows) */
    /* 0x008 */ int unk_008;              /* lw 29 (16 rows) */
    /* 0x00C */ unsigned char unk_00C;    /* lbu 4, lw 1, sb 5, sw 5 (6 rows) */
    /* 0x00D */ unsigned char unk_00D;    /* lbu 1, sb 5 (3 rows) */
    /* 0x00E */ unsigned char unk_00E;    /* lbu 4, sb 5 (3 rows) */
    /* 0x00F */ unsigned char pad_00F[0x1];
    /* 0x010 */ unsigned short unk_010;   /* lhu 1, sh 3 (1 rows) */
    /* 0x012 */ unsigned char pad_012[0x2];
    /* 0x014 */ unsigned short unk_014;   /* lhu 25, sh 4 (20 rows) */
    /* 0x016 */ short unk_016;            /* sh 1 (1 rows) */
    /* 0x018 */ short unk_018;            /* sh 1 (1 rows) */
    /* 0x01A */ short unk_01A;            /* sh 1 (1 rows) */
    /* 0x01C */ short unk_01C;            /* sh 3 (3 rows) */
    /* 0x01E */ short unk_01E;            /* sh 3 (3 rows) */
    /* 0x020 */ short unk_020;            /* sh 1 (1 rows) */
    /* 0x022 */ unsigned char pad_022[0x2];
    /* 0x024 */ unsigned char tileX;      /* lbu 351, lhu 77, sb 2 (164 rows) */
    /* 0x025 */ unsigned char tileY;      /* lbu 353, sb 1 (163 rows) */
    /* 0x026 */ signed char unk_026;      /* lb 32, lbu 1, sb 2 (35 rows) */
    /* 0x027 */ unsigned char pad_027[0x1];
    /* 0x028 */ int unk_028;              /* lw 4, sw 4 (6 rows) */
    /* 0x02C */ int unk_02C;              /* lw 1, sw 4 (4 rows) */
    /* 0x030 */ int unk_030;              /* lh 1, lw 42, sw 12 (14 rows) */
    /* 0x034 */ int unk_034;              /* lw 10, sw 3 (6 rows) */
    /* 0x038 */ int unk_038;              /* lhu 1, lw 1, sw 9 (5 rows) */
    /* 0x03C */ unsigned char pad_03C[0x4];
    /* 0x040 */ int unk_040;              /* sw 1 (1 rows) */
    /* 0x044 */ unsigned char pad_044[0xFC];
    /* 0x140 */ int unk_140;              /* sw 1 (1 rows) */
    /* 0x144 */ unsigned char pad_144[0x0];
} TileObject;

extern TileObject D_80082E80;

#endif
