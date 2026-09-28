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
    /* 0x024 */ void * unk_24;       /* lw 1, sw 2 (1 rows, slot 0) */
    /* 0x028 */ short unk_28;        /* lh 1, sh 4 (4 rows, slot 0) */
    /* 0x02A */ short unk_2A;        /* sh 4 (4 rows, slot 0) */
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
    /* 0x000 */ short unk_000;           /* sh 3 (3 rows) */
    /* 0x002 */ short unk_002;           /* sh 3 (3 rows) */
    /* 0x004 */ short unk_004;           /* sh 3 (3 rows) */
    /* 0x006 */ short unk_006;           /* sh 4 (4 rows) */
    /* 0x008 */ short unk_008;           /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x00A */ short unk_00A;           /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x00C */ short unk_00C;           /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x00E */ unsigned char pad_00E[0x2];
    /* 0x010 */ short unk_010;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x012 */ short unk_012;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x014 */ short unk_014;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x016 */ unsigned char pad_016[0x2];
    /* 0x018 */ short unk_018;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x01A */ short unk_01A;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x01C */ short unk_01C;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x01E */ unsigned char pad_01E[0x2];
    /* 0x020 */ short unk_020;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x022 */ short unk_022;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x024 */ short unk_024;           /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x026 */ unsigned char pad_026[0x2];
    /* 0x028 */ short unk_028;           /* sh 2 (1 rows) */
    /* 0x02A */ short unk_02A;           /* sh 1 (1 rows) */
    /* 0x02C */ short unk_02C;           /* sh 2 (1 rows) */
    /* 0x02E */ unsigned char pad_02E[0xA];
    /* 0x038 */ short unk_038;           /* sh 3 (3 rows) */
    /* 0x03A */ short unk_03A;           /* sh 3 (3 rows) */
    /* 0x03C */ short unk_03C;           /* sh 3 (3 rows) */
    /* 0x03E */ short unk_03E;           /* sh 3 (3 rows) */
    /* 0x040 */ short unk_040;           /* sh 3 (3 rows) */
    /* 0x042 */ short unk_042;           /* sh 3 (3 rows) */
    /* 0x044 */ short unk_044;           /* sh 3 (3 rows) */
    /* 0x046 */ short unk_046;           /* sh 3 (3 rows) */
    /* 0x048 */ short unk_048;           /* sh 3 (3 rows) */
    /* 0x04A */ unsigned char pad_04A[0xE];
    /* 0x058 */ short unk_058;           /* sh 4 (3 rows) */
    /* 0x05A */ short unk_05A;           /* sh 3 (3 rows) */
    /* 0x05C */ short unk_05C;           /* sh 3 (3 rows) */
    /* 0x05E */ short unk_05E;           /* sh 4 (3 rows) */
    /* 0x060 */ short unk_060;           /* sh 3 (3 rows) */
    /* 0x062 */ short unk_062;           /* sh 3 (3 rows) */
    /* 0x064 */ short unk_064;           /* sh 4 (3 rows) */
    /* 0x066 */ short unk_066;           /* sh 3 (3 rows) */
    /* 0x068 */ short unk_068;           /* sh 3 (3 rows) */
    /* 0x06A */ unsigned char pad_06A[0xE];
    /* 0x078 */ int unk_078;             /* sw 3 (3 rows) */
    /* 0x07C */ int unk_07C;             /* sw 3 (3 rows) */
    /* 0x080 */ int unk_080;             /* sw 3 (3 rows) */
    /* 0x084 */ int unk_084;             /* lw 1, sw 3 (4 rows) */
    /* 0x088 */ int unk_088;             /* lw 8, sw 5 (10 rows) */
    /* 0x08C */ short unk_08C;           /* sh 1 (1 rows) */
    /* 0x08E */ unsigned char pad_08E[0x2];
    /* 0x090 */ unsigned char unk_090;   /* lbu 32, lw 4, sb 31, sw 2 (32 rows) */
    /* 0x091 */ unsigned char unk_091;   /* lbu 31, sb 30 (26 rows) */
    /* 0x092 */ unsigned char unk_092;   /* lbu 31, sb 30 (26 rows) */
    /* 0x093 */ unsigned char pad_093[0x1];
    /* 0x094 */ short unk_094;           /* lh 3, lhu 9, lw 1, sh 7, sw 1 (11 rows) */
    /* 0x096 */ short unk_096;           /* lh 2, lhu 8, sh 5 (9 rows) */
    /* 0x098 */ short unk_098;           /* lh 6, lhu 6, sh 9, sw 1 (11 rows) */
    /* 0x09A */ unsigned char pad_09A[0x2];
    /* 0x09C */ short unk_09C;           /* lh 1, lhu 1, sh 2 (2 rows) */
    /* 0x09E */ short unk_09E;           /* lh 1, lhu 1, sh 2 (2 rows) */
    /* 0x0A0 */ short unk_0A0;           /* lh 3, lhu 11, sh 4 (10 rows) */
    /* 0x0A2 */ unsigned char pad_0A2[0x2];
    /* 0x0A4 */ short unk_0A4;           /* lh 6, lhu 10, sh 10 (16 rows) */
    /* 0x0A6 */ short unk_0A6;           /* lh 5, lhu 10, sh 10 (15 rows) */
    /* 0x0A8 */ short unk_0A8;           /* lh 8, lhu 7, sh 7 (11 rows) */
    /* 0x0AA */ unsigned char pad_0AA[0x2];
    /* 0x0AC */ short unk_0AC;           /* lh 13, lhu 9, sh 9, sw 1 (21 rows) */
    /* 0x0AE */ short unk_0AE;           /* lh 9, lhu 6, sh 3 (15 rows) */
    /* 0x0B0 */ short viewAngle;         /* lh 1134, lhu 36, sh 35, sw 1 (634 rows) */
    /* 0x0B2 */ unsigned char pad_0B2[0x2];
    /* 0x0B4 */ ViewSlot slot[4];
} GameView;

/* gameWork: the global work block at 0x80083160 (SLUS .bss), used by every binary (1,095 rows reference an address
 * in 0x80083160..0x8008335F).  ONE object: rows reach offsets 0x000..0x1FC from one lui/addiu base of 0x80083160
 * (census/g83160w.jsonl, r78 phase 3).  Field widths/signs are the retail access widths (lh => signed; an lhu-only
 * slot is unsigned; store-only slots default to signed).  Fields stay unk_ until their meaning is proven.
 *   0x000/0x008/0x010: pointers (lw; 0x000 is the "current state" pointer slus/w_80045340 follows to +0x8D0).
 *   0x018..0x1DB: `view` (GameView above; game.h's old struct S_80083178 described the same bytes).
 *   Union sites (a wider or narrower access than the field; reached through a view at the use): 0x004 (2 lbu),
 *   0x008 (1 lhu), view.0x090 (lw/sw over the three bytes), view.0x094/0x098/0x0AC/0x0B0 (a word copy).
 * Size: at least 0x200 (last access 0x1FC); never small data at any -G. */
typedef struct GameWork {
    /* 0x000 */ void * unk_000;          /* lw 523, sw 7 (171 rows) */
    /* 0x004 */ unsigned short unk_004;  /* lbu 2, lhu 15 (14 rows) */
    /* 0x006 */ unsigned char pad_006[0x2];
    /* 0x008 */ void * unk_008;          /* lhu 1, lw 118, sw 2 (77 rows) */
    /* 0x00C */ int unk_00C;             /* lw 1, sw 1 (1 rows) */
    /* 0x010 */ void * unk_010;          /* lw 102, sw 1 (66 rows) */
    /* 0x014 */ unsigned char pad_014[0x4];
    /* 0x018 */ GameView view;
    /* 0x1DC */ int unk_1DC;             /* lw 48, sw 3 (49 rows) */
    /* 0x1E0 */ int unk_1E0;             /* lw 13, sw 1 (14 rows) */
    /* 0x1E4 */ int unk_1E4;             /* lw 13, sw 1 (14 rows) */
    /* 0x1E8 */ int unk_1E8;             /* lw 12, sw 1 (13 rows) */
    /* 0x1EC */ int unk_1EC;             /* lw 1, sw 1 (2 rows) */
    /* 0x1F0 */ short unk_1F0;           /* lh 175, lhu 2, sh 5 (78 rows) */
    /* 0x1F2 */ short unk_1F2;           /* lh 29, sh 5 (24 rows) */
    /* 0x1F4 */ short unk_1F4;           /* lh 2, lhu 10, sh 5 (17 rows) */
    /* 0x1F6 */ short unk_1F6;           /* lh 4, lhu 8, sh 5 (17 rows) */
    /* 0x1F8 */ short unk_1F8;           /* lh 1, lhu 1, sh 5 (6 rows) */
    /* 0x1FA */ short unk_1FA;           /* lh 1, lhu 1, sh 5 (6 rows) */
    /* 0x1FC */ int unk_1FC;             /* lw 2, sw 1 (2 rows) */
    /* 0x200 */ unsigned char pad_200[0x0];
} GameWork;

extern GameWork gameWork;

#endif
