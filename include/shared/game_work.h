#ifndef SHARED_GAME_WORK_H
#define SHARED_GAME_WORK_H

/* gameWork: the global work block at 0x80083160 (SLUS .bss), used by every binary (1,095 rows reference an address
 * in 0x80083160..0x8008335F).  ONE object: rows reach offsets 0x000..0x1FC from one lui/addiu base of 0x80083160
 * (census/g83160w.jsonl, r78 phase 3) - including 0x0C8, the view angle that 567 rows read on its own.
 * Field widths/signs are the retail access widths (lh => signed; an lhu-only slot is unsigned; store-only slots
 * default to signed).  Fields other than viewAngle stay unk_ until their meaning is proven.
 *   0x000/0x008/0x010: pointers (lw; 0x000 is the "current state" pointer slus/w_80045340 follows to +0x8D0).
 *   0x018..0x1DB: the same bytes game.h calls struct S_80083178 (D_80083178 = gameWork + 0x18: its callback 0xB4,
 *   field_B8 and ptr 0xD8 land on 0x0CC/0x0D0/0x0F0 here).  game.h's provisional state_94 vectors cover 0x0AC..0x0CB,
 *   which retail shows is where viewAngle lives - folding S_80083178 into this type is the next step (D_80083178,
 *   69 rows, stays on its game.h view for now).
 *   viewAngle (0x0C8): read-only in C (lh 1,134 sites): `(viewAngle + obj->angle + 0x100) >> 9 & 7` picks an object's
 *   8-way directional sprite, i.e. the view's rotation (0x1000 = one turn).
 *   Union sites (a wider or narrower access than the field; reached through a view at the use): 0x004 (2 lbu),
 *   0x008 (1 lhu), 0x0A8 (lw/sw over the three bytes), 0x0AC/0x0B0/0x0C4/0x0C8 (a word copy).
 * Size: at least 0x200 (last access 0x1FC); never small data at any -G. */
typedef struct GameWork {
    /* 0x000 */ void * unk_000;         /* lw 523, sw 7 (171 rows) */
    /* 0x004 */ unsigned short unk_004; /* lbu 2, lhu 15 (14 rows) */
    /* 0x006 */ unsigned char pad_006[0x2];
    /* 0x008 */ void * unk_008;         /* lhu 1, lw 118, sw 2 (77 rows) */
    /* 0x00C */ int unk_00C;            /* lw 1, sw 1 (1 rows) */
    /* 0x010 */ void * unk_010;         /* lw 102, sw 1 (66 rows) */
    /* 0x014 */ unsigned char pad_014[0x4];
    /* 0x018 */ short unk_018;          /* sh 3 (3 rows) */
    /* 0x01A */ short unk_01A;          /* sh 3 (3 rows) */
    /* 0x01C */ short unk_01C;          /* sh 3 (3 rows) */
    /* 0x01E */ short unk_01E;          /* sh 4 (4 rows) */
    /* 0x020 */ short unk_020;          /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x022 */ short unk_022;          /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x024 */ short unk_024;          /* lh 1, lhu 3, sh 2 (2 rows) */
    /* 0x026 */ unsigned char pad_026[0x2];
    /* 0x028 */ short unk_028;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x02A */ short unk_02A;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x02C */ short unk_02C;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x02E */ unsigned char pad_02E[0x2];
    /* 0x030 */ short unk_030;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x032 */ short unk_032;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x034 */ short unk_034;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x036 */ unsigned char pad_036[0x2];
    /* 0x038 */ short unk_038;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x03A */ short unk_03A;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x03C */ short unk_03C;          /* lh 1, lhu 2, sh 2 (1 rows) */
    /* 0x03E */ unsigned char pad_03E[0x2];
    /* 0x040 */ short unk_040;          /* sh 2 (1 rows) */
    /* 0x042 */ short unk_042;          /* sh 1 (1 rows) */
    /* 0x044 */ short unk_044;          /* sh 2 (1 rows) */
    /* 0x046 */ unsigned char pad_046[0xA];
    /* 0x050 */ short unk_050;          /* sh 3 (3 rows) */
    /* 0x052 */ short unk_052;          /* sh 3 (3 rows) */
    /* 0x054 */ short unk_054;          /* sh 3 (3 rows) */
    /* 0x056 */ short unk_056;          /* sh 3 (3 rows) */
    /* 0x058 */ short unk_058;          /* sh 3 (3 rows) */
    /* 0x05A */ short unk_05A;          /* sh 3 (3 rows) */
    /* 0x05C */ short unk_05C;          /* sh 3 (3 rows) */
    /* 0x05E */ short unk_05E;          /* sh 3 (3 rows) */
    /* 0x060 */ short unk_060;          /* sh 3 (3 rows) */
    /* 0x062 */ unsigned char pad_062[0xE];
    /* 0x070 */ short unk_070;          /* sh 4 (3 rows) */
    /* 0x072 */ short unk_072;          /* sh 3 (3 rows) */
    /* 0x074 */ short unk_074;          /* sh 3 (3 rows) */
    /* 0x076 */ short unk_076;          /* sh 4 (3 rows) */
    /* 0x078 */ short unk_078;          /* sh 3 (3 rows) */
    /* 0x07A */ short unk_07A;          /* sh 3 (3 rows) */
    /* 0x07C */ short unk_07C;          /* sh 4 (3 rows) */
    /* 0x07E */ short unk_07E;          /* sh 3 (3 rows) */
    /* 0x080 */ short unk_080;          /* sh 3 (3 rows) */
    /* 0x082 */ unsigned char pad_082[0xE];
    /* 0x090 */ int unk_090;            /* sw 3 (3 rows) */
    /* 0x094 */ int unk_094;            /* sw 3 (3 rows) */
    /* 0x098 */ int unk_098;            /* sw 3 (3 rows) */
    /* 0x09C */ int unk_09C;            /* lw 1, sw 3 (4 rows) */
    /* 0x0A0 */ int unk_0A0;            /* lw 8, sw 5 (10 rows) */
    /* 0x0A4 */ short unk_0A4;          /* sh 1 (1 rows) */
    /* 0x0A6 */ unsigned char pad_0A6[0x2];
    /* 0x0A8 */ unsigned char unk_0A8;  /* lbu 32, lw 4, sb 31, sw 2 (32 rows) */
    /* 0x0A9 */ unsigned char unk_0A9;  /* lbu 31, sb 30 (26 rows) */
    /* 0x0AA */ unsigned char unk_0AA;  /* lbu 31, sb 30 (26 rows) */
    /* 0x0AB */ unsigned char pad_0AB[0x1];
    /* 0x0AC */ short unk_0AC;          /* lh 3, lhu 9, lw 1, sh 7, sw 1 (11 rows) */
    /* 0x0AE */ short unk_0AE;          /* lh 2, lhu 8, sh 5 (9 rows) */
    /* 0x0B0 */ short unk_0B0;          /* lh 6, lhu 6, sh 9, sw 1 (11 rows) */
    /* 0x0B2 */ unsigned char pad_0B2[0x2];
    /* 0x0B4 */ short unk_0B4;          /* lh 1, lhu 1, sh 2 (2 rows) */
    /* 0x0B6 */ short unk_0B6;          /* lh 1, lhu 1, sh 2 (2 rows) */
    /* 0x0B8 */ short unk_0B8;          /* lh 3, lhu 11, sh 4 (10 rows) */
    /* 0x0BA */ unsigned char pad_0BA[0x2];
    /* 0x0BC */ short unk_0BC;          /* lh 6, lhu 10, sh 10 (16 rows) */
    /* 0x0BE */ short unk_0BE;          /* lh 5, lhu 10, sh 10 (15 rows) */
    /* 0x0C0 */ short unk_0C0;          /* lh 8, lhu 7, sh 7 (11 rows) */
    /* 0x0C2 */ unsigned char pad_0C2[0x2];
    /* 0x0C4 */ short unk_0C4;          /* lh 13, lhu 9, sh 9, sw 1 (21 rows) */
    /* 0x0C6 */ short unk_0C6;          /* lh 9, lhu 6, sh 3 (15 rows) */
    /* 0x0C8 */ short viewAngle;        /* lh 1134, lhu 36, sh 35, sw 1 (634 rows) */
    /* 0x0CA */ unsigned char pad_0CA[0x2];
    /* 0x0CC */ void * unk_0CC;         /* sw 10 (8 rows) */
    /* 0x0D0 */ void * unk_0D0;         /* sw 4 (4 rows) */
    /* 0x0D4 */ unsigned char pad_0D4[0x8];
    /* 0x0DC */ int unk_0DC;            /* lw 3, sw 4 (4 rows) */
    /* 0x0E0 */ int unk_0E0;            /* sw 1 (1 rows) */
    /* 0x0E4 */ int unk_0E4;            /* lw 3, sw 4 (4 rows) */
    /* 0x0E8 */ int unk_0E8;            /* sw 4 (4 rows) */
    /* 0x0EC */ unsigned char pad_0EC[0x4];
    /* 0x0F0 */ void * unk_0F0;         /* lw 1, sw 2 (1 rows) */
    /* 0x0F4 */ short unk_0F4;          /* lh 1, sh 4 (4 rows) */
    /* 0x0F6 */ short unk_0F6;          /* sh 4 (4 rows) */
    /* 0x0F8 */ int unk_0F8;            /* sw 3 (3 rows) */
    /* 0x0FC */ unsigned char pad_0FC[0x8];
    /* 0x104 */ int unk_104;            /* sw 1 (1 rows) */
    /* 0x108 */ unsigned char pad_108[0x8];
    /* 0x110 */ int unk_110;            /* sw 2 (2 rows) */
    /* 0x114 */ unsigned char pad_114[0x40];
    /* 0x154 */ int unk_154;            /* lw 1, sw 11 (8 rows) */
    /* 0x158 */ unsigned char pad_158[0x40];
    /* 0x198 */ int unk_198;            /* sw 2 (2 rows) */
    /* 0x19C */ unsigned char pad_19C[0x40];
    /* 0x1DC */ int unk_1DC;            /* lw 48, sw 3 (49 rows) */
    /* 0x1E0 */ int unk_1E0;            /* lw 13, sw 1 (14 rows) */
    /* 0x1E4 */ int unk_1E4;            /* lw 13, sw 1 (14 rows) */
    /* 0x1E8 */ int unk_1E8;            /* lw 12, sw 1 (13 rows) */
    /* 0x1EC */ int unk_1EC;            /* lw 1, sw 1 (2 rows) */
    /* 0x1F0 */ short unk_1F0;          /* lh 175, lhu 2, sh 5 (78 rows) */
    /* 0x1F2 */ short unk_1F2;          /* lh 29, sh 5 (24 rows) */
    /* 0x1F4 */ short unk_1F4;          /* lh 2, lhu 10, sh 5 (17 rows) */
    /* 0x1F6 */ short unk_1F6;          /* lh 4, lhu 8, sh 5 (17 rows) */
    /* 0x1F8 */ short unk_1F8;          /* lh 1, lhu 1, sh 5 (6 rows) */
    /* 0x1FA */ short unk_1FA;          /* lh 1, lhu 1, sh 5 (6 rows) */
    /* 0x1FC */ int unk_1FC;            /* lw 2, sw 1 (2 rows) */
    /* 0x200 */ unsigned char pad_200[0x0];
} GameWork;

extern GameWork gameWork;

#endif
