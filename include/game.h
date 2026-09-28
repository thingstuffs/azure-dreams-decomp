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
struct S_80083178Vector {
    short x;
    short y;
    short z;
    short pad;
};

struct S_80083178State {
    struct S_80083178Vector v[4];
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
