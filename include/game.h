#ifndef GAME_H
#define GAME_H

/* Reconstructed game types. Data-table names, record sizes and field lists are
 * cross-referenced from the Azure Dreams randomizer's romAddresses/rowLength map
 * (ref/adrando-findings.md) — facts about the binary only (addresses, sizes,
 * names are not copyrightable); no code was copied. Layouts marked "provisional"
 * still need exact field offsets confirmed from the disassembly / ref/adrando. */

/* Four x,y,z,pad short vectors: the layout of gameWork.view.unk_094..0x0B3 (include/shared/game_work.h,
 * GameView); D_80083CE8 (globals.h) is a saved copy of them (slus/w_80044724 compares and copies them).
 * The old struct S_80083178 (the whole gameWork+0x18 block) is shared/game_work.h's GameView since r78 phase 8. */
/* One integer camera vector in a saved copy of GameView; camera state comparison copies these vectors. */
struct S_80083178Vector {
    short x; /* first signed vector component */
    short y; /* second signed vector component */
    short z; /* third signed vector component */
    short pad;
};

/* Saved four-vector camera state compared and refreshed by the camera matrix update. */
struct S_80083178State {
    struct S_80083178Vector v[4]; /* copies of view offset, rotation offset, camera position and camera rotation, in that order */
};

/* Twenty-four-byte species template at D_8006D168. init_monster_from_stats
 * copies +0..+0x13 to the actor and ORs the flag word at +0x14. The level-up
 * readers use the first six bytes and the signed EXP-reward halfword; ability
 * updates use three ID/effective/stored-level triples at +8..+0x10.
 * Initial zeroes at +7, +0xB..+0x10 and +0x17 are live field bytes, not padding. */
typedef struct MonsterInitialStats {
    /* 0x00 */ unsigned char attack;
    /* 0x01 */ unsigned char defense;
    /* 0x02 */ unsigned char agility;
    /* 0x03 */ unsigned char luck;
    /* 0x04 */ unsigned char mp;
    /* 0x05 */ unsigned char hp;
    /* 0x06 */ short exp_reward;
    /* 0x08 */ struct {
        unsigned char id;
        unsigned char effective_level;
        unsigned char stored_level;
    } abilities[3];
    /* 0x11 */ unsigned char level;
    /* 0x12 */ unsigned char unk_12;
    /* 0x13 */ unsigned char unk_13; /* replaced with species ID by initialization */
    /* 0x14 */ unsigned int flags;
} MonsterInitialStats;

/* Trap table = D_80072CD0 (adrando trapTable, 12B/record). */
typedef struct { unsigned char data[12]; } Trap;                 /* g_TrapTable */

/* Stat-growth table (adrando statGrowth, 8B/record; lives in an overlay, D_800DDCBC). */
typedef struct { unsigned char data[8]; } StatGrowth;

#endif /* GAME_H */
