#ifndef SHARED_TILE_OBJECT_H
#define SHARED_TILE_OBJECT_H

/* TileObject: the object at 0x80082E80 (SLUS .bss), 290 rows (dungeon, town).  NOT an EntityRec: the census puts
 * words at 0x28/0x2C/0x30 where EntityRec has bytes, an s16 and padding (r78 phase 5).  What it shares with the
 * entity record is the map-grid position bytes at 0x24/0x25 (lbu 351/353: tile distances, func_8009FB34 map
 * lookups; the 0x24 pair is also read as one u16 - a view).  func_800A08A0 keeps new monster spawns more than 0x20
 * tiles away from it - plausibly the player's own record, not yet proven, so the object keeps its address name.
 * Layout generated from the access census (tools/layout.py).  Size 0x40 (r78 phase 6): the next object is the
 * 128-word table D_80082EC0 (0x80082EC0..0x800830C0; slus code2 func_8003F7E4 clears all 128 words, w_8003D8B0
 * passes it with count 0x80, w_8003F80C stores (addr & 0xFFFFFF) | (width << 24) into it) - a separate SLUS
 * object with its own D_ declaration, not a TileObject member (phase 5's unk_040 / unk_140 were that table's
 * stores seen through the census address range).  No TileObject row reaches past 0x38. */
typedef struct TileObject {
    /* 0x000 */ int unk_000;              /* lw 1 (1 rows) */
    /* 0x004 */ signed char unk_004;      /* lb 1, lbu 1 (2 rows) */
    /* 0x005 */ unsigned char pad_005[0x1];
    /* 0x006 */ unsigned short unk_006;   /* lhu 1, sh 8 (6 rows) */
    /* 0x008 */ int sprite_source;              /* lw 29 (16 rows) */
    /* 0x00C */ union {
        unsigned int word;
        struct {
            unsigned char color_r;    /* lbu 4, lw 1, sb 5, sw 5 (6 rows) */
            unsigned char color_g;    /* lbu 1, sb 5 (3 rows) */
            unsigned char color_b;    /* lbu 4, sb 5 (3 rows) */
            unsigned char code;
        } parts;
    } primitive_color;
    /* 0x010 */ unsigned short tpage_offset;   /* lhu 1, sh 3 (1 rows) */
    /* 0x012 */ unsigned char pad_012[0x2];
    /* 0x014 */ unsigned short sprite_flags;   /* lhu 25, sh 4 (20 rows) */
    /* 0x016 */ short angle_x;            /* sh 1 (1 rows) */
    /* 0x018 */ short angle_y;            /* sh 1 (1 rows) */
    /* 0x01A */ short angle_z;            /* sh 1 (1 rows) */
    /* 0x01C */ short scale_x;            /* sh 3 (3 rows) */
    /* 0x01E */ short scale_y;            /* sh 3 (3 rows) */
    /* 0x020 */ short unk_020;            /* sh 1 (1 rows) */
    /* 0x022 */ unsigned char pad_022[0x2];
    /* 0x024 */ union {
        unsigned short word;
        struct {
            unsigned char tile_x;      /* lbu 351, lhu 77, sb 2 (164 rows) */
            unsigned char tile_y;      /* lbu 353, sb 1 (163 rows) */
        } parts;
    } tile_position;
    /* 0x026 */ signed char room_index;      /* lb 32, lbu 1, sb 2 (35 rows) */
    /* 0x027 */ unsigned char pad_027[0x1];
    /* 0x028 */ int render_attributes;              /* lw 4, sw 4 (6 rows) */
    /* 0x02C */ int frame_table;              /* lw 1, sw 4 (4 rows) */
    /* 0x030 */ int selected_item;              /* lh 1, lw 42, sw 12 (14 rows) */
    /* 0x034 */ int secondary_item;              /* lw 10, sw 3 (6 rows) */
    /* 0x038 */ int unk_038;              /* lhu 1, lw 1, sw 9 (5 rows) */
    /* 0x03C */ unsigned char pad_03C[0x4];
} TileObject;                             /* 0x40: bounded by the separate table at 0x80082EC0 (below) */

extern TileObject reference_tile_object;

#endif
