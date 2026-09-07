#include "common.h"

/* initialStatsTable: monster initial-stats record table, 24 bytes/record
 * (game.h: MonsterInitialStats, adrando-verified at RAM 0x8006d168). Declared
 * with a provisional size > 8 so the compiler/assembler emit a direct
 * %hi/%lo access rather than $gp small-data. */
extern u8 initialStatsTable[24];

/* D_8006D6D8: word array indexed by monster id (used to seed obj+0x54). */
extern s32 D_8006D6D8[4];

/* func_80041E70: post-init fixup on the struct just filled in (still
 * nonmatching elsewhere; only the arg setup here needs to match). */
extern void func_80041E70(void *arg0);

/* 16-byte block (4 words) used to copy the first 4 record fields into the
 * object in one shot, matching retail's load-x4/store-x4 grouping. */
typedef struct {
    u32 w0, w1, w2, w3;
} S_80042640_Block16;

/* Initializes a monster-object struct (arg0) from initialStatsTable[arg1],
 * ORs the record's flag word into the object's existing flags, tags the
 * object with its monster id, seeds a couple of fixed/derived byte fields,
 * pulls a per-id word from D_8006D6D8 into obj+0x54, then runs the
 * func_80041E70 post-processing pass on the object. */
void initMonsterFromStats(void *arg0, s16 arg1)
{
    u8 *dst = (u8 *)arg0;
    u8 *rec = initialStatsTable + (s32)arg1 * 24;
    s32 *d6d8 = &D_8006D6D8[arg1];
    u32 oldFlags, recFlags;

    *(S_80042640_Block16 *)(dst + 0x00) = *(S_80042640_Block16 *)(rec + 0x00);
    *(u32 *)(dst + 0x10) = *(u32 *)(rec + 0x10);

    oldFlags = *(u32 *)(dst + 0x14);
    recFlags = *(u32 *)(rec + 0x14);
    dst[0x13] = (u8)arg1;
    *(u32 *)(dst + 0x14) = oldFlags | recFlags;

    dst[0x28] = rec[0x05];
    dst[0x25] = rec[0x04];
    dst[0x24] = 0xFF;
    dst[0x26] = rec[0x00];
    dst[0x27] = rec[0x01];
    dst[0x45] = 6;
    dst[0x42] = 0;
    dst[0x41] = 0;
    *(u32 *)(dst + 0x54) = *d6d8;
    func_80041E70(arg0);
}
