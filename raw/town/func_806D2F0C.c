#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800161EC(u32, s32);
extern void func_80016510(s32, s32);
extern s32 func_80016654(s32);
extern void func_80016CCC(s32);

s32 func_8001670C(u32 records, s32 optional, u32 ctx, s32 arg3)
{
    s32 index;
    u32 pair;

    index = func_800161EC(records, arg3);
    pair = (FIELD(index * 8 + records, s16, 2) * 4)
         + FIELD(ctx, u32, 0x14);
    func_80016510(FIELD(pair, s16, 0), FIELD(pair, s16, 2));
    if (optional != 0 && func_80016654(optional) != 0) {
        func_80016CCC(FIELD(ctx, s16, 0x18));
    }
    return FIELD(index * 8 + records, s32, 4);
}
