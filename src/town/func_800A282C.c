#include "common.h"

typedef struct {
    u8 pad0[6];
    u8 result;
    u8 pad7[9];
    s16 x;
    s16 y;
} TownRecord;

typedef struct {
    u16 x;
    u16 y;
    u8 pad4[8];
    void *recordsOwner;
} TownState;

extern s32 func_8003BD84(s32, s32);
extern s32 D_800D0728[];
extern TownState *D_80100900;

s32 func_8009FF8C(s32 arg0, void *arg1)
{
    TownRecord *records;
    register TownRecord *record ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    u8 *flagBase;
    register u8 *argPtr ASM_REG("$23");   /* MATCH pin: retail immediate-load split depends on it */
    s32 count;
    s32 best;
    register s32 bestIndex ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 i;
    s32 baseX;
    s32 baseY;
    s32 distance;
    s32 result;
    u16 rawX;
    u16 rawY;

    argPtr = arg1;
    ASM_KEEP_NV(argPtr);   /* MATCH pin: retail schedule: same instructions, different order without it */
    best = 0x7FFFFFFF;
    i = 0;
    count = D_800D0728[arg0];
    records = *(TownRecord **)((u8 *)D_80100900->recordsOwner + 4);
    rawX = D_80100900->x;
    rawY = D_80100900->y;
    bestIndex = i;
    if (count > 0) {
        baseX = (s16)rawX;
        baseY = (s16)rawY;
        record = records;
        flagBase = (u8 *)0x80010000;
        do {
            if (flagBase[0x981] == 0) {
                distance = func_8003BD84(
                    ((record->x + baseX) - *(s16 *)(argPtr + 2)) << 16,
                    ((record->y + baseY) - *(s16 *)(argPtr + 6)) << 16);
                if (distance < best) {
                    best = distance;
                    bestIndex = i;
                }
            }
            record++;
            i++;
            flagBase += 4;
        } while (i < count);
    }
    if (best == 0x7FFFFFFF) {
        goto no_best;
    }
    result = records[bestIndex].result;
    goto done;
no_best:
    result = -1;
done:
    return result;
}

/* MECHANISM: Recover the true-space tail as a local return join, retain bestIndex,
   and use 20-byte records plus the held 0x80010000 flag-page base. Keep structural
   roles pinned, but leave s32 baseX/baseY natural so cdk assigns fp/s6 and emits
   both sign extensions before loading the record and flag bases. */
