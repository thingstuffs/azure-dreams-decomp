#include "common.h"

#include "common.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} S_80013564;

typedef struct {
    char unk[0x13];
} S_800133E8;

extern S_80013564 D_80013564[];
extern s32 func_8004A6C0(s32 a0, s32 a1);

S_800133E8 *func_8004A700(s16 arg0, s16 arg1)
{
    S_800133E8 *result = 0;
    s32 i = func_8004A6C0(0, 0);

    if (i < 0x14) {
        result = (S_800133E8 *)0x800133E8 + i;
        D_80013564[i].unk0 = arg0;
        D_80013564[i].unk2 = arg1;
    }

    return result;
}
