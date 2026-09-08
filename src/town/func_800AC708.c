#include "common.h"

typedef struct {
    u8 pad0[8];
    s16 field8;
    s16 fieldA;
    u8 padC[4];
    s32 field10;
    s32 field14;
    s32 field18;
} TownRecord;

extern TownRecord D_800D1178;
extern TownRecord D_800D119C;
extern u16 D_80100D18;
extern u16 D_80100D40;
extern u16 D_80100D42;

extern void func_800A2AF8();
extern void func_800AA10C();

void func_800A9E68(s32 arg0, s32 arg1)
{
    s32 value;
    s32 value2;

    func_800A2AF8(arg1, arg0);

    value = (s16)D_80100D18 / 2;
    D_800D1178.field10 = value;
    D_800D1178.field14 = value;
    D_800D1178.field18 = value;
    D_800D1178.fieldA = -D_80100D40;
    func_800AA10C(&D_800D1178, arg0);

    value2 = (s16)D_80100D18;
    D_800D119C.field10 = value2;
    D_800D119C.field14 = value2;
    D_800D119C.field18 = value2;
    D_800D119C.field8 = D_80100D42;
    func_800AA10C(&D_800D119C, arg0);
}
