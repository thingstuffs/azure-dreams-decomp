#include "common.h"

typedef struct {
    u8 pad0[0x10];
    s32 *field_10;
    u8 pad14[0x0C];
    s32 *field_20;
} TownContext;

typedef struct {
    u8 pad0[0x0C];
    s32 field_C;
    s32 field_10;
} TownState;

typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    u8 pad6[0x16];
    void *field_1C;
} TownObject;

extern s32 D_8006ADD4;
extern TownContext D_80083498;
extern s32 D_800A5440;
extern s32 D_800A549C;
extern s32 D_800A54FC;
extern s32 D_800A5638;
extern s32 D_800A58CC;
extern s32 D_800A5A98;
extern TownState D_80100D98;

extern s32 func_800352FC(void);
extern s32 func_8003BD84(s32, s32);

void func_800A5340(TownObject *arg0)
{
    if ((D_80083498.field_10 == &D_800A5638) &&
        ((D_80083498.field_20 == &D_800A5A98) ||
         (D_80083498.field_20 == &D_800A58CC))) {
        arg0->field_2 = 0x80;
        arg0->field_4 = 0x300;
        arg0->field_1C = &D_800A5440;
        return;
    }

    if ((func_8003BD84(D_80100D98.field_C,
                       D_80100D98.field_10) > 0xDFFFF) &&
        ((s16)D_8006ADD4 != 0xC)) {
        arg0->field_4 = 0x448;
        arg0->field_1C = &D_800A549C;
        return;
    }

    if (func_800352FC() != 0) {
        if (D_8006ADD4 == 0x38000C) {
            arg0->field_4 = 0x448;
        } else {
            arg0->field_4 = 0x380;
        }
        arg0->field_1C = &D_800A54FC;
    }
}
