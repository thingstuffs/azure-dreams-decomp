#include "modules/dungeon_ovl_19c088c.h"

void func_80024BD0(Row_819A13D0_Work *work, s32 unused, Row_819A13D0_Obj *obj) {
    s32 scaled_count;
    u16 count;
    u16 angle;

    count = work->count - 1;
    scaled_count = (s32)((s32)(count << 16) >> 9) / work->divisor;
    work->count = count;
    angle = obj->angle;
    ((s16 *)D_800261B0)[0] = 1;
    obj->angle = angle + 0x190;
    obj->c2 = scaled_count;
    obj->c1 = scaled_count;
    obj->c0 = scaled_count;
    if ((s16)work->count > 0) {
        return;
    }
    *(u16 *)((u8 *)work - 2) |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
