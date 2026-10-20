#ifndef SHARED_GAME_WORK_H
#define SHARED_GAME_WORK_H

/* ViewSlot: one of four 0x44-byte records at GameView+0xB4 (gameWork+0xCC/0x110/0x154/0x198).  One record type:
 * slus/w_8004D7A8 / w_8004D7E8 move whole records between slot 0 <-> 1 and 2 <-> 3 through func_8004D75C(dst, src);
 * slus/w_80040BB4 clears all four `callback` words.  `callback` (+0x00): code2 func_8004D0C8 / func_8004D110 store a
 * function there together with the record's data (+0x24 / +0x04); w_8004D294 hands &slot[0].unk_04 (position) and
 * &slot[2].unk_04 (rotation) to func_8004D1EC as transition targets.  Field widths are slot 0's retail accesses
 * (slots 1..3 are reached only at +0x00).  Other fields stay unk_. */
typedef struct ViewSlot {
    /* 0x000 */ void * callback;     /* sw 10 (8 rows, slot 0) */
    /* 0x004 */ void * unk_04;       /* sw 4 (4 rows, slot 0) */
    /* 0x008 */ unsigned char pad_08[0x8];
    /* 0x010 */ int unk_10;          /* lw 3, sw 4 (4 rows, slot 0) */
    /* 0x014 */ int unk_14;          /* sw 1 (1 rows, slot 0) */
    /* 0x018 */ int unk_18;          /* lw 3, sw 4 (4 rows, slot 0) */
    /* 0x01C */ int unk_1C;          /* sw 4 (4 rows, slot 0) */
    /* 0x020 */ unsigned char pad_20[0x4];
    /* 0x024 */ void * position_source;       /* lw 1, sw 2 (1 rows, slot 0) */
    /* 0x028 */ short transition_frames_left;        /* lh 1, sh 4 (4 rows, slot 0) */
    /* 0x02A */ short target_view_offset_z;        /* sh 4 (4 rows, slot 0) */
    /* 0x02C */ int unk_2C;          /* sw 3 (3 rows, slot 0) */
    /* 0x030 */ unsigned char pad_30[0x8];
    /* 0x038 */ int unk_38;          /* sw 1 (1 rows, slot 0) */
    /* 0x03C */ unsigned char pad_3C[0x8];
} ViewSlot;

/* GameView: gameWork+0x018..0x1DB (0x1C4 bytes; r78 phase 8, OPEN_ITEMS #2).  A real sub-object: retail keeps its
 * address (%hi(D_80083160+24)) in a register across calls and passes it to func_800997FC / func_80042900
 * (dungeon/func_800C6654, func_800C1E70, func_800B2614: flat gameWork fields miss by 19-63 words), and
 * slus/w_8004D5D0's TU declares it on its own at 0x80083178 (it keeps that local extern, D_80083178).
 * "View": 0x094..0x0B3 are four x,y,z,pad short vectors (8 bytes each; slus/w_80044724 copies them as 8-byte
 * aggregates into D_80083CE8, game.h struct S_80083178State) from which slus/w_8004D4AC builds the GTE view
 * transform (RotMatrix of 0x09C and 0x0AC, RotTrans of 0x094 and of -0x0A4..0x0A8, CompMatrix, SetRotMatrix /
 * SetTransMatrix); w_8004D294 sets position (0x0A4) and rotation (0x0AC, 12-bit angles) targets through the
 * slots; w_8004D5D0 loads 0x0A4..0x0A8 from D_80083780's integer x/y/z.
 *   viewAngle (0x0B0 = vector 3's z = gameWork+0xC8): read-only in C (lh 1,134 sites):
 *   `(viewAngle + obj->angle + 0x100) >> 9 & 7` picks an object's 8-way directional sprite (0x1000 = one turn).
 *   0x090..0x092: three bytes read as an r, g, b triple into primitives and faded in/out by +-2/4 (unnamed).
 * gcc 2.7.2 has no anonymous structs, so every field here is spelled gameWork.view.<field>. */
typedef struct GameView {
    /* 0x000 */ short clip_x;           /* sh 3 (3 rows) */
    /* 0x002 */ short clip_y;           /* sh 3 (3 rows) */
    /* 0x004 */ short clip_width;           /* sh 3 (3 rows) */
    /* 0x006 */ short clip_height;           /* sh 4 (4 rows) */
    /* 0x008 */ short outline_0_x;           /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x00A */ short outline_0_y;           /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x00C */ short outline_0_z;           /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x00E */ unsigned char pad_00E[0x2];
    /* 0x010 */ short outline_1_x;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x012 */ short outline_1_y;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x014 */ short outline_1_z;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x016 */ unsigned char pad_016[0x2];
    /* 0x018 */ short outline_2_x;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x01A */ short outline_2_y;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x01C */ short outline_2_z;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x01E */ unsigned char pad_01E[0x2];
    /* 0x020 */ short outline_3_x;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x022 */ short outline_3_y;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x024 */ short outline_3_z;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x026 */ unsigned char pad_026[0x2];
    /* 0x028 */ short outline_4_x;           /* sh 2 (1 rows) */
    /* 0x02A */ short outline_4_y;           /* sh 1 (1 rows) */
    /* 0x02C */ short outline_4_z;           /* sh 2 (1 rows) */
    /* 0x02E */ unsigned char pad_02E[0xA];
    /* 0x038 */ short light_matrix_00;           /* sh 3 (3 rows) */
    /* 0x03A */ short light_matrix_01;           /* sh 3 (3 rows) */
    /* 0x03C */ short light_matrix_02;           /* sh 3 (3 rows) */
    /* 0x03E */ short light_matrix_10;           /* sh 3 (3 rows) */
    /* 0x040 */ short light_matrix_11;           /* sh 3 (3 rows) */
    /* 0x042 */ short light_matrix_12;           /* sh 3 (3 rows) */
    /* 0x044 */ short light_matrix_20;           /* sh 3 (3 rows) */
    /* 0x046 */ short light_matrix_21;           /* sh 3 (3 rows) */
    /* 0x048 */ short light_matrix_22;           /* sh 3 (3 rows) */
    /* 0x04A */ unsigned char pad_04A[0xE];
    /* 0x058 */ short color_matrix_00;           /* sh 4 (3 rows) */
    /* 0x05A */ short color_matrix_01;           /* sh 3 (3 rows) */
    /* 0x05C */ short color_matrix_02;           /* sh 3 (3 rows) */
    /* 0x05E */ short color_matrix_10;           /* sh 4 (3 rows) */
    /* 0x060 */ short color_matrix_11;           /* sh 3 (3 rows) */
    /* 0x062 */ short color_matrix_12;           /* sh 3 (3 rows) */
    /* 0x064 */ short color_matrix_20;           /* sh 4 (3 rows) */
    /* 0x066 */ short color_matrix_21;           /* sh 3 (3 rows) */
    /* 0x068 */ short color_matrix_22;           /* sh 3 (3 rows) */
    /* 0x06A */ unsigned char pad_06A[0xE];
    /* 0x078 */ int unk_078;             /* sw 3 (3 rows) */
    /* 0x07C */ int unk_07C;             /* sw 3 (3 rows) */
    /* 0x080 */ int unk_080;             /* sw 3 (3 rows) */
    /* 0x084 */ int fog_far;             /* lw 1, sw 3 (4 rows) */
    /* 0x088 */ int projection_distance;             /* lw 8, sw 5 (10 rows) */
    /* 0x08C */ short unk_08C;           /* sh 1 (1 rows) */
    /* 0x08E */ unsigned char pad_08E[0x2];
    /* 0x090 */ union {
        unsigned int word;
        struct {
            unsigned char tint_r;   /* lbu 32, lw 4, sb 31, sw 2 (32 rows) */
            unsigned char tint_g;   /* lbu 31, sb 30 (26 rows) */
            unsigned char tint_b;   /* lbu 31, sb 30 (26 rows) */
            unsigned char unk_93;
        } parts;
    } tint;
    /* 0x094 */ union {
        unsigned int words[2];
        struct {
            short view_offset_x;           /* lh 3, lhu 9, lw 1, sh 7, sw 1 (11 rows) */
            short view_offset_y;           /* lh 2, lhu 8, sh 5 (9 rows) */
            short view_offset_z;           /* lh 6, lhu 6, sh 9, sw 1 (11 rows) */
            unsigned char pad_09A[0x2];
        } parts;
    } view_offset;
    /* 0x09C */ union {
        unsigned int words[2];
        struct {
            short view_rotation_offset_x;           /* lh 1, lhu 1, sh 2 (2 rows) */
            short view_rotation_offset_y;           /* lh 1, lhu 1, sh 2 (2 rows) */
            short view_rotation_offset_z;           /* lh 3, lhu 11, sh 4 (10 rows) */
            unsigned char pad_0A2[0x2];
        } parts;
    } view_rotation_offset;
    /* 0x0A4 */ union {
        unsigned int words[2];
        struct {
            short camera_position_x;           /* lh 6, lhu 10, sh 10 (16 rows) */
            short camera_position_y;           /* lh 5, lhu 10, sh 10 (15 rows) */
            short camera_position_z;           /* lh 8, lhu 7, sh 7 (11 rows) */
            unsigned char pad_0AA[0x2];
        } parts;
    } camera_position;
    /* 0x0AC */ union {
        unsigned int words[2];
        struct {
            short camera_rotation_x;           /* lh 13, lhu 9, sh 9, sw 1 (21 rows) */
            short camera_rotation_y;           /* lh 9, lhu 6, sh 3 (15 rows) */
            short viewAngle;         /* lh 1134, lhu 36, sh 35, sw 1 (634 rows) */
            unsigned char pad_0B2[0x2];
        } parts;
    } camera_rotation;
    /* 0x0B4 */ ViewSlot slot[4];
} GameView;

/* MapGrid: gameWork+0x1DC..0x1FB (0x20 bytes; r78 phase 10), the current map's cell grid.  A real sub-object like
 * `view`: retail forms its address (0x8008333C) as a base register in dungeon, town and SLUS code (func_800A0548,
 * func_80017EBC, ...), and several TUs declared it on their own (`extern ... D_8008333C;`).  The map loader
 * func_80018464 sets shiftX / shiftY from the map data, maskX = (1 << shiftX) - 1, spanX = 64 << shiftX (the same
 * for y); cells are 6 bytes and cell (x, y) is cells + (x + (y << shiftX)) * 6 (func_80017EBC counts free cells,
 * the cell's flags word is at +4); func_800A0548 bounds-checks x < 1 << shiftX and y < 1 << shiftY.  World
 * coordinates are 64 units per cell (EntityRec: tile * 64 + 32), so span is the map size in world units. */
typedef struct MapGrid {
    /* 0x00 */ void * cells;         /* the cell array (6-byte cells, row length 1 << shiftX); lw 48 */
    /* 0x04 */ void * cell_faces;        /* read as a primitive-pointer table by func_800BCB04; lw 13 */
    /* 0x08 */ void * vertices;        /* read as a vertex array by func_800BCB04; lw 13 */
    /* 0x0C */ void * surface_planes;        /* read as a second vertex array (normals) by func_800BCB04; lw 12 */
    /* 0x10 */ int unk_10;           /* lw 1, sw 1 */
    /* 0x14 */ short shiftX;         /* log2 of the map width in cells (row stride); lh 175 */
    /* 0x16 */ short shiftY;         /* log2 of the map height in cells */
    /* 0x18 */ short maskX;          /* (1 << shiftX) - 1 */
    /* 0x1A */ short maskY;          /* (1 << shiftY) - 1 */
    /* 0x1C */ short spanX;          /* 64 << shiftX: the map width in world units */
    /* 0x1E */ short spanY;          /* 64 << shiftY: the map height in world units */
} MapGrid;

/* gameWork: the global work block at 0x80083160 (SLUS .bss), used by every binary (1,095 rows reference an address
 * in 0x80083160..0x8008335F).  ONE object: rows reach offsets 0x000..0x1FC from one lui/addiu base of 0x80083160
 * (census/g83160w.jsonl, r78 phase 3).  Field widths/signs are the retail access widths (lh => signed; an lhu-only
 * slot is unsigned; store-only slots default to signed).  Fields stay unk_ until their meaning is proven.
 *   0x000/0x008/0x010: pointers (lw; 0x000 is the "current state" pointer slus/w_80045340 follows to +0x8D0).
 *   0x018..0x1DB: `view` (GameView above; game.h's old struct S_80083178 described the same bytes).
 *   0x1DC..0x1FB: `map` (MapGrid above); 0x1FC: randSeed.
 *   Union sites (a wider or narrower access than the field; reached through a view at the use): 0x004 (2 lbu),
 *   0x008 (1 lhu), view.0x090 (lw/sw over the three bytes), view.0x094/0x098/0x0AC/0x0B0 (a word copy).
 * Size: at least 0x200 (last access 0x1FC); never small data at any -G. */
typedef struct GameWork {
    /* 0x000 */ void * draw_buffer;          /* lw 523, sw 7 (171 rows) */
    /* 0x004 */ unsigned short unk_004;  /* lbu 2, lhu 15 (14 rows) */
    /* 0x006 */ unsigned char pad_006[0x2];
    /* 0x008 */ int buttons;             /* the controller button bits, PS1 pad layout (r78 phase 10): rows test 0x1000 / 0x2000 /
                                          * 0x4000 / 0x8000 (d-pad up / right / down / left; 0xF000 any direction), 0x10 / 0x20 /
                                          * 0x40 / 0x80 (triangle / circle / cross / square), 0x100 select, 0x800 start, 1 / 2 / 4 / 8
                                          * (shoulder buttons); held vs newly pressed not established.  103 reads cast it to s32
                                          * (it was declared void *); lw 118, lhu 1 (a view), sw 2 (77 rows) */
    /* 0x00C */ int previous_buttons;             /* lw 1, sw 1 (1 rows) */
    /* 0x010 */ void * pressed_buttons;          /* lw 102, sw 1 (66 rows) */
    /* 0x014 */ unsigned char pad_014[0x4];
    /* 0x018 */ GameView view;
    /* 0x1DC */ MapGrid map;
    /* 0x1FC */ int randSeed;            /* lw 2, sw 1: the dungeon overlay's rand() state (func_800A6D30 steps it as
                                          * seed * 0x41C64E6D + 0x3039 and returns (seed >> 16) & 0x7FFF; func_800A6D60
                                          * saves / restores it through D_800DD87C) - r78 phase 10 */
    /* 0x200 */ unsigned char pad_200[0x0];
} GameWork;

extern GameWork g_game_work;

#endif
