#include "common.h"

extern u8 *D_80174710;
extern s32 D_800814A0;

extern void func_800A32A4(void *arg0);
extern void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2);
extern void func_8009A028(void *arg0);

/* Updates the active object, triggers its positional effect, and clears its slot. */
void func_81254248(void) {
    u8 **active_slot;
    u8 *active_obj;

    active_slot = &D_80174710;
    active_obj = *active_slot;
    if (active_obj != 0) {
        u8 *obj_state = active_obj + 0x20;
        u8 *obj_data = *(u8 **)(active_obj + 0xC);
        s32 sound_x;
        s32 sound_y;
        s32 effect_id;

        func_800A32A4(obj_state);
        sound_x = obj_data[0x24];
        sound_y = obj_data[0x25];
        effect_id = 0x3000;
        if (*(u32 *)(obj_state + 0x1C) & 0x2000) {
            effect_id = 0x300;
        }
        func_8009A3D0(sound_x, sound_y, effect_id);
        func_8009A028(obj_state);
        *(u16 *)(obj_state - 2) |= 0x8000;
        *active_slot = 0;
        D_800814A0 |= 0x8000;
    }
}
