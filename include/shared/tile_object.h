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
/* Static reference sprite/map-location record used for the player view in town and dungeon.
 * initialize_dungeon_actor and initialize_scene_for_mode clear and attach this record to the scene node. */
typedef struct TileObject {
    /* 0x000 */ int unk_000;              /* lw 1 (1 rows) */
    /* 0x004 */ signed char unk_004;      /* lb 1, lbu 1 (2 rows) */
    /* 0x005 */ unsigned char pad_005[0x1];
    /* 0x006 */ unsigned short unk_006;   /* lhu 1, sh 8 (6 rows) */
    /* 0x008 */ int sprite_source; /* sprite command/attachment source consumed by rendering */
    /* 0x00C */ union {
        unsigned int word;
        struct {
            unsigned char color_r; /* red modulation; initialized to 0x80 for neutral color */
            unsigned char color_g; /* green modulation; initialized to 0x80 for neutral color */
            unsigned char color_b; /* blue modulation; initialized to 0x80 for neutral color */
            unsigned char code;
        } parts;
    } primitive_color; /* packed RGB modulation and GPU command byte */
    /* 0x010 */ unsigned short tpage_offset;   /* lhu 1, sh 3 (1 rows) */
    /* 0x012 */ unsigned char pad_012[0x2];
    /* 0x014 */ unsigned short sprite_flags; /* sprite render/animation flags */
    /* 0x016 */ short angle_x; /* sprite X rotation, in GTE angle units (0x1000 per turn) */
    /* 0x018 */ short angle_y; /* sprite Y rotation, in GTE angle units (0x1000 per turn) */
    /* 0x01A */ short angle_z; /* sprite Z rotation, in GTE angle units (0x1000 per turn) */
    /* 0x01C */ short scale_x; /* horizontal sprite scale; 0x1000 = 1.0 */
    /* 0x01E */ short scale_y; /* vertical sprite scale; 0x1000 = 1.0 */
    /* 0x020 */ short unk_020;            /* sh 1 (1 rows) */
    /* 0x022 */ unsigned char pad_022[0x2];
    /* 0x024 */ union {
        unsigned short word;
        struct {
            unsigned char tile_x; /* current map column, in tiles */
            unsigned char tile_y; /* current map row, in tiles */
        } parts;
    } tile_position;
    /* 0x026 */ signed char room_index; /* signed room index for tile_position; -1 denotes no room */
    /* 0x027 */ unsigned char pad_027[0x1];
    /* 0x028 */ int render_attributes; /* loaded sprite-bundle attributes installed by town scene setup */
    /* 0x02C */ int frame_table; /* animation-frame table address, retained in an integer leaf */
    /* 0x030 */ int selected_item;              /* lh 1, lw 42, sw 12 (14 rows) */
    /* 0x034 */ int secondary_item;              /* lw 10, sw 3 (6 rows) */
    /* 0x038 */ int unk_038;              /* lhu 1, lw 1, sw 9 (5 rows) */
    /* 0x03C */ unsigned char pad_03C[0x4];
} TileObject;                             /* 0x40: bounded by the separate table at 0x80082EC0 (below) */

extern TileObject reference_tile_object;

#endif
