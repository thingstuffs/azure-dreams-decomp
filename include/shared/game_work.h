#ifndef SHARED_GAME_WORK_H
#define SHARED_GAME_WORK_H

/* ViewSlot: one of four 0x44-byte records at GameView+0xB4 (gameWork+0xCC/0x110/0x154/0x198).  One record type:
 * slus/w_8004D7A8 / w_8004D7E8 move whole records between slot 0 <-> 1 and 2 <-> 3 through func_8004D75C(dst, src);
 * slus/w_80040BB4 clears all four `callback` words.  `callback` (+0x00): code2 func_8004D0C8 / func_8004D110 store a
 * function there together with the record's data (+0x24 / +0x04); w_8004D294 hands &slot[0].unk_04 (position) and
 * &slot[2].unk_04 (rotation) to func_8004D1EC as transition targets.  Field widths are slot 0's retail accesses
 * (slots 1..3 are reached only at +0x00).  Other fields stay unk_. */
/* Embedded camera callback work: slots 0/2 run position/rotation, slots 1/3 hold queued records.
 * move_view_record transfers all 0x44 bytes and clears the source callback; no separate allocation. */
typedef struct ViewSlot {
    /* 0x000 */ void * callback; /* active view callback, called with the address of unk_04; null when idle */
    /* 0x004 */ void * unk_04; /* callback-specific data; interpolation stores the destination vector pointer here, with deltas in the following bytes */
    /* 0x008 */ unsigned char pad_08[0x8];
    /* 0x010 */ int unk_10; /* packed target X/Y halfwords in three-component interpolation mode */
    /* 0x014 */ int unk_14; /* target Z halfword at +0x14 in three-component interpolation mode */
    /* 0x018 */ int unk_18; /* three-component interpolation progress, initialized to 0; callback clamps completion at 0x1000 */
    /* 0x01C */ int unk_1C; /* interpolation step: 0x400 / duration when nonzero, otherwise 0x1000; duration is not a direct frame count */
    /* 0x020 */ unsigned char pad_20[0x4];
    /* 0x024 */ void * position_source; /* position source read at +2/+6/+0xA by copy_view_halfword_triplet */
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
/* Camera/projection/lighting work embedded in resident GameWork, reused across scene setup.
 * init_dungeon_view sets render defaults; reset_camera_transition_fields clears transitions and binds the position source. */
typedef struct GameView {
    /* 0x000 */ short clip_x; /* horizontal origin of the render clipping rectangle, in screen coordinates */
    /* 0x002 */ short clip_y; /* vertical origin of the render clipping rectangle, in screen coordinates */
    /* 0x004 */ short clip_width; /* horizontal extent of the render clipping rectangle */
    /* 0x006 */ short clip_height; /* vertical extent of the render clipping rectangle */
    /* 0x008 */ short outline_0_x; /* view outline corner 0, X world component */
    /* 0x00A */ short outline_0_y; /* view outline corner 0, Y world component */
    /* 0x00C */ short outline_0_z; /* view outline corner 0, Z world component */
    /* 0x00E */ unsigned char pad_00E[0x2];
    /* 0x010 */ short outline_1_x; /* view outline corner 1, X world component */
    /* 0x012 */ short outline_1_y; /* view outline corner 1, Y world component */
    /* 0x014 */ short outline_1_z; /* view outline corner 1, Z world component */
    /* 0x016 */ unsigned char pad_016[0x2];
    /* 0x018 */ short outline_2_x; /* view outline corner 2, X world component */
    /* 0x01A */ short outline_2_y; /* view outline corner 2, Y world component */
    /* 0x01C */ short outline_2_z; /* view outline corner 2, Z world component */
    /* 0x01E */ unsigned char pad_01E[0x2];
    /* 0x020 */ short outline_3_x; /* view outline corner 3, X world component */
    /* 0x022 */ short outline_3_y; /* view outline corner 3, Y world component */
    /* 0x024 */ short outline_3_z; /* view outline corner 3, Z world component */
    /* 0x026 */ unsigned char pad_026[0x2];
    /* 0x028 */ short outline_4_x; /* closing outline point, copied from corner 0 (X component) */
    /* 0x02A */ short outline_4_y; /* closing outline point, copied from corner 0 (Y component) */
    /* 0x02C */ short outline_4_z; /* closing outline point, copied from corner 0 (Z component) */
    /* 0x02E */ unsigned char pad_02E[0xA];
    /* 0x038 */ short light_matrix_00; /* light direction matrix coefficient [0][0], passed to the GTE matrix setter */
    /* 0x03A */ short light_matrix_01; /* light direction matrix coefficient [0][1], passed to the GTE matrix setter */
    /* 0x03C */ short light_matrix_02; /* light direction matrix coefficient [0][2], passed to the GTE matrix setter */
    /* 0x03E */ short light_matrix_10; /* light direction matrix coefficient [1][0], passed to the GTE matrix setter */
    /* 0x040 */ short light_matrix_11; /* light direction matrix coefficient [1][1], passed to the GTE matrix setter */
    /* 0x042 */ short light_matrix_12; /* light direction matrix coefficient [1][2], passed to the GTE matrix setter */
    /* 0x044 */ short light_matrix_20; /* light direction matrix coefficient [2][0], passed to the GTE matrix setter */
    /* 0x046 */ short light_matrix_21; /* light direction matrix coefficient [2][1], passed to the GTE matrix setter */
    /* 0x048 */ short light_matrix_22; /* light direction matrix coefficient [2][2], passed to the GTE matrix setter */
    /* 0x04A */ unsigned char pad_04A[0xE];
    /* 0x058 */ short color_matrix_00; /* light color matrix coefficient [0][0], passed to the GTE matrix setter */
    /* 0x05A */ short color_matrix_01; /* light color matrix coefficient [0][1], passed to the GTE matrix setter */
    /* 0x05C */ short color_matrix_02; /* light color matrix coefficient [0][2], passed to the GTE matrix setter */
    /* 0x05E */ short color_matrix_10; /* light color matrix coefficient [1][0], passed to the GTE matrix setter */
    /* 0x060 */ short color_matrix_11; /* light color matrix coefficient [1][1], passed to the GTE matrix setter */
    /* 0x062 */ short color_matrix_12; /* light color matrix coefficient [1][2], passed to the GTE matrix setter */
    /* 0x064 */ short color_matrix_20; /* light color matrix coefficient [2][0], passed to the GTE matrix setter */
    /* 0x066 */ short color_matrix_21; /* light color matrix coefficient [2][1], passed to the GTE matrix setter */
    /* 0x068 */ short color_matrix_22; /* light color matrix coefficient [2][2], passed to the GTE matrix setter */
    /* 0x06A */ unsigned char pad_06A[0xE];
    /* 0x078 */ int unk_078;             /* sw 3 (3 rows) */
    /* 0x07C */ int unk_07C;             /* sw 3 (3 rows) */
    /* 0x080 */ int unk_080;             /* sw 3 (3 rows) */
    /* 0x084 */ int fog_far; /* far depth-cue parameter; dungeon initialization sets 0x1000 */
    /* 0x088 */ int projection_distance; /* GTE projection distance; dungeon initialization sets 0x200 */
    /* 0x08C */ short unk_08C;           /* sh 1 (1 rows) */
    /* 0x08E */ unsigned char pad_08E[0x2];
    /* 0x090 */ union {
        unsigned int word;
        struct {
            unsigned char tint_r; /* view red modulation byte; gray-level updates use 0, 0x40 or 0x80 */
            unsigned char tint_g; /* view green modulation byte; gray-level updates use 0, 0x40 or 0x80 */
            unsigned char tint_b; /* view blue modulation byte; gray-level updates use 0, 0x40 or 0x80 */
            unsigned char unk_93;
        } parts;
    } tint;
    /* 0x094 */ union {
        unsigned int words[2];
        struct {
            short view_offset_x; /* X view-translation offset component, composed with the camera transform */
            short view_offset_y; /* Y view-translation offset component, composed with the camera transform */
            short view_offset_z; /* Z view-translation offset component, composed with the camera transform */
            unsigned char pad_09A[0x2];
        } parts;
    } view_offset;
    /* 0x09C */ union {
        unsigned int words[2];
        struct {
            short view_rotation_offset_x; /* X rotation offset composed with the camera rotation */
            short view_rotation_offset_y; /* Y rotation offset composed with the camera rotation */
            short view_rotation_offset_z; /* Z rotation offset composed with the camera rotation */
            unsigned char pad_0A2[0x2];
        } parts;
    } view_rotation_offset;
    /* 0x0A4 */ union {
        unsigned int words[2];
        struct {
            short camera_position_x; /* camera X target component, in integer world units */
            short camera_position_y; /* camera Y target component, in integer world units */
            short camera_position_z; /* camera height target component, in integer world units */
            unsigned char pad_0AA[0x2];
        } parts;
    } camera_position;
    /* 0x0AC */ union {
        unsigned int words[2];
        struct {
            short camera_rotation_x; /* camera X rotation; 0x1000 units per turn */
            short camera_rotation_y; /* camera Y rotation; 0x1000 units per turn */
            short viewAngle; /* camera azimuth used for eight-way sprite selection; 0x1000 units per turn */
            unsigned char pad_0B2[0x2];
        } parts;
    } camera_rotation;
    /* 0x0B4 */ ViewSlot slot[4]; /* position active/queued pair [0,1] and rotation active/queued pair [2,3]; runner restores queued work when active is idle */
} GameView;

/* MapGrid: gameWork+0x1DC..0x1FB (0x20 bytes; r78 phase 10), the current map's cell grid.  A real sub-object like
 * `view`: retail forms its address (0x8008333C) as a base register in dungeon, town and SLUS code (func_800A0548,
 * func_80017EBC, ...), and several TUs declared it on their own (`extern ... D_8008333C;`).  The map loader
 * func_80018464 sets shiftX / shiftY from the map data, maskX = (1 << shiftX) - 1, spanX = 64 << shiftX (the same
 * for y); cells are 6 bytes and cell (x, y) is cells + (x + (y << shiftX)) * 6 (func_80017EBC counts free cells,
 * the cell's flags word is at +4); func_800A0548 bounds-checks x < 1 << shiftX and y < 1 << shiftY.  World
 * coordinates are 64 units per cell (EntityRec: tile * 64 + 32), so span is the map size in world units. */
/* Current map descriptor embedded in GameWork; scene setup binds its borrowed cell/geometry data.
 * Width/height shifts give cell bounds; cells span 64 world units and use a six-byte stride. */
typedef struct MapGrid {
    /* 0x00 */ void * cells; /* borrowed six-byte map cells; index = x + (y << shiftX), flag halfword at byte +4 (see dungeon/level/tile_flags.h) */
    /* 0x04 */ void * cell_faces; /* table of face-list pointers indexed by a map cell */
    /* 0x08 */ void * vertices; /* map vertex table used for surface-height queries */
    /* 0x0C */ void * surface_planes; /* surface-normal vectors indexed by map faces */
    /* 0x10 */ int unk_10;           /* lw 1, sw 1 */
    /* 0x14 */ short shiftX; /* log2 of the map width in cells; also the row-stride shift */
    /* 0x16 */ short shiftY; /* log2 of the map height in cells */
    /* 0x18 */ short maskX; /* map column mask, (1 << shiftX) - 1 */
    /* 0x1A */ short maskY; /* map row mask, (1 << shiftY) - 1 */
    /* 0x1C */ short spanX; /* map width in world units, 64 << shiftX */
    /* 0x1E */ short spanY; /* map height in world units, 64 << shiftY */
} MapGrid;

/* gameWork: the global work block at 0x80083160 (SLUS .bss), used by every binary (1,095 rows reference an address
 * in 0x80083160..0x8008335F).  ONE object: rows reach offsets 0x000..0x1FC from one lui/addiu base of 0x80083160
 * (census/g83160w.jsonl, r78 phase 3).  Field widths/signs are the retail access widths (lh => signed; an lhu-only
 * slot is unsigned; store-only slots default to signed).  Fields stay unk_ until their meaning is proven.
 *   0x000: draw-context pointer (slus/w_80045340 follows it to +0x8D0).
 *   0x008/0x00C/0x010: held, previous and newly pressed controller words.
 *   0x018..0x1DB: `view` (GameView above; game.h's old struct S_80083178 described the same bytes).
 *   0x1DC..0x1FB: `map` (MapGrid above); 0x1FC: randSeed.
 *   Union sites (a wider or narrower access than the field; reached through a view at the use): 0x004 (2 lbu),
 *   0x008 (1 lhu), view.0x090 (lw/sw over the three bytes), view.0x094/0x098/0x0AC/0x0B0 (a word copy).
 * Size: at least 0x200 (last access 0x1FC); never small data at any -G. */
/* Resident singleton shared by overlays; scene setup rebinds its draw/map pointers and embedded view.
 * Controller polling replaces input samples, frame rendering selects the current draw context. */
typedef struct GameWork {
    /* 0x000 */ void * draw_buffer; /* borrowed current frame draw context; packet allocation advances its +0x8D0 cursor */
    /* 0x004 */ unsigned short unk_004; /* texture-pack generation token; narrow/wide VRAM packers reset their cursors when their cached token differs */
    /* 0x006 */ unsigned char pad_006[0x2];
    /* 0x008 */ int buttons; /* currently held controller buttons, in the PS1 pad bit layout */
    /* 0x00C */ int previous_buttons; /* previous held-button sample saved before polling the controller */
    /* 0x010 */ int pressed_buttons; /* newly pressed controller bits, (buttons ^ previous_buttons) & buttons */
    /* 0x014 */ unsigned char pad_014[0x4];
    /* 0x018 */ GameView view; /* camera, lighting, clipping and view-transition state */
    /* 0x1DC */ MapGrid map; /* current map cell grid and geometry tables */
    /* 0x1FC */ int randSeed; /* dungeon random-generator state, stepped by seed * 0x41C64E6D + 0x3039 */
    /* 0x200 */ unsigned char pad_200[0x0];
} GameWork;

extern GameWork g_game_work;

#endif
