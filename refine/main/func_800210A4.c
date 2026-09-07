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

/* Updates the object's state and callback and performs a one-time transition. */
void func_804080A4(void *object_data)
{
    s32 *object;
    s32 state_index;
    s32 table_offset;
    s32 next_callback;

    object = object_data;
    if ((D_801379A8 != 0) && ((D_801379B0 & 0x40) != 0)) {
        func_80400948();
        object[14] = 0;
        object[-4] = (s32)(unsigned long)D_804081AC;
        return;
    }

    state_index = func_804016D0();
    table_offset = state_index * 4;
    func_8003FA78(D_80400848, object[3], D_804090C8[state_index]);
    func_804018FC();
    if (state_index != 0) {
        object[14] = 0;
        object[12] = state_index;
        next_callback = D_804090E0[state_index];
        object[13] = state_index;
        object[-4] = next_callback;
        return;
    }
    if ((func_804010E0() == 3) && (object[14] == 0)) {
        func_8040311C((u8 *)object - 0x20, (u8 *)object + 0x38);
        object[14] = 1;
    }
    (void)table_offset;
}
