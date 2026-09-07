#include "common.h"

typedef struct SceneEntry {
    u8 data[8];
} SceneEntry;

typedef struct RuntimeMethods {
    u8 pad_00[0x64];
    void (*invoke)(s32, SceneEntry *, s32);
} RuntimeMethods;

extern SceneEntry D_80702BA8[];
extern u8 D_80702C00[];
extern RuntimeMethods *D_807030B8;

void func_80878924(s32 arg0)
{
    D_807030B8->invoke(6, &D_80702BA8[D_80702C00[arg0]], 0);
}
