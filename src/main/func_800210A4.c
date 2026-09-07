#include "common.h"

extern void func_80400948(void);
extern s32 func_804016D0(void);
extern void func_804018FC(void);
extern s32 func_804010E0(void);
extern void func_8040311C(void *left, void *right);
extern void func_8003FA78(void *descriptor, s32 value, s32 item);
extern s32 D_801379A8;
extern s32 D_801379B0;
extern u8 D_80400848[];
extern u8 D_804081AC[];
extern s32 D_804090C8[];
extern s32 D_804090E0[];

void func_804080A4(void *arg0)
{
    s32 *object;
    s32 index;
    s32 offset;
    s32 callback;

    object = arg0;
    if ((D_801379A8 != 0) && ((D_801379B0 & 0x40) != 0)) {
        func_80400948();
        object[14] = 0;
        object[-4] = (s32)(unsigned long)D_804081AC;
        return;
    }

    index = func_804016D0();
    offset = index * 4;
    func_8003FA78(D_80400848, object[3], D_804090C8[index]);
    func_804018FC();
    if (index != 0) {
        object[14] = 0;
        object[12] = index;
        callback = D_804090E0[index];
        object[13] = index;
        object[-4] = callback;
        return;
    }
    if ((func_804010E0() == 3) && (object[14] == 0)) {
        func_8040311C((u8 *)object - 0x20, (u8 *)object + 0x38);
        object[14] = 1;
    }
    (void)offset;
}
