#ifndef GAME_H
#define GAME_H

/* Reconstructed game types. Data-table names, record sizes and field lists are
 * cross-referenced from the Azure Dreams randomizer's romAddresses/rowLength map
 * (ref/adrando-findings.md) — facts about the binary only (addresses, sizes,
 * names are not copyrightable); no code was copied. Layouts marked "provisional"
 * still need exact field offsets confirmed from the disassembly / ref/adrando. */

/* Global dispatch/callback state record at D_80083178 (unified from the
 * func_8004D0C8 / func_8004D110 accessors). */
struct S_80083178Vector {
    short x;
    short y;
    short z;
    short pad;
};

struct S_80083178State {
    struct S_80083178Vector v[4];
};

struct S_80083178 {
    char pad0[2];
    unsigned short unk2;                 /* 0x2   (func_800C6654: 0x10 state-flag bit) */
    char pad4[6];
    unsigned short unkA;                 /* 0xA   (func_800C6654: dispatch-slot counter) */
    char padC[0x94 - 0xC];
    struct S_80083178State state_94;      /* 0x94: four padded xyz vectors */
    void (*callback)(void);              /* 0xB4 */
    void *field_B8;                      /* 0xB8 */
    char pad_bc[0xD8 - 0xB8 - 4];
    void *ptr;                           /* 0xD8 */
    char pad_dc[0x1C4 - 0xDC];           /* table extends to 0x1C4: 0x44-byte dispatch slots at
                                            0xB4/0xF8/0x13C/0x180 (func_8004D7A8/func_8004D7E8 use byte offsets) */
};

/* Monster initial-stats table  = D_8006D168  (adrando initialStatsTable, 24B/record).
 * Fields (adrando): attack, def, agi, luck, mp, hp, xp, spell1, spell2, spell3,
 * level, id, element, pushable, flying — exact offsets TBD (ref/adrando/monsters.js). */
typedef struct { unsigned char data[24]; } MonsterInitialStats;  /* g_MonsterInitialStats */

/* Trap table = D_80072CD0 (adrando trapTable, 12B/record). */
typedef struct { unsigned char data[12]; } Trap;                 /* g_TrapTable */

/* Stat-growth table (adrando statGrowth, 8B/record; lives in an overlay, D_800DDCBC). */
typedef struct { unsigned char data[8]; } StatGrowth;

#endif /* GAME_H */
