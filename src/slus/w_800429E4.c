#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x14];
    s32 flags;
} InitialStats;

typedef struct {
    u8 pad[0x13];
    u8 id;
    s32 flags;
} Entity;

extern volatile InitialStats initialStatsTable[1];
extern u8 D_8006D160[9];

s32 func_800429E4(Entity *arg0)
{
    s32 flags = arg0->flags;
    s32 ret = 0;

    if (flags & 0x2000) {
        s32 id = arg0->id;
        s32 offset = id << 1;
        s32 bits;
        s32 lowBits;

        offset += id;
        offset <<= 3;
        bits = ((volatile InitialStats *)((volatile u8 *)initialStatsTable + offset))->flags & flags;
        lowBits = bits & 7;

        if (lowBits != 0) {
            u8 *classTable = D_8006D160;
            ret = classTable[lowBits];
            goto done_alt;
        }

        if (flags & 1) {
            ret = 1;
            goto done;
        }
        if (flags & 2) {
            ret = 2;
            goto done;
        }
        if (flags & 4) {
            ret = 3;
        }
    }

done:
    return ret;

done_alt:
    return ret;
}
