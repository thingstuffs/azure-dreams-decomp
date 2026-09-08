#include "common.h"

extern void *D_800E3D7C;
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_800E17A1[];
extern u16 D_80083460[];

extern s32 func_8008D330();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800A5F38();
extern void func_800A56E0();
extern void func_80041E70();
extern void func_80099844();
extern void func_80098B38();

/* Apply the level-down item effect to an entity and finish item use. */
s32 func_800C3690(void *entity, s32 item, s16 action)
{
    if (entity == D_800E3D7C) {
        *(s32 *)((u8 *)entity + 0x110) = item;
        func_8008D330(entity, D_80083780, D_80082E80, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, item, action);
        if (func_800AD6FC(entity, (D_800DDE84[*((u8 *)entity + 0x13)] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }

    if (*((u8 *)entity + 0x26) >= 2) {
        func_800A56E0(0x615);
        (*((u8 *)entity + 0x26))--;
        func_80041E70(entity);
        if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
            func_80099844(entity, D_800E17A1);
        }
    }

    func_80098B38(item);
    D_80083460[5]--;
    return 1;
}
