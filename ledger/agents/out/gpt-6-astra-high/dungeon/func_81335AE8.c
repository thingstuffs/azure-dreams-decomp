#include "common.h"

extern u16 D_80013714[5];
extern u8 D_80083460[0x14];
extern u8 *D_800E3D7C[];
extern u8 D_80175392[];

extern void func_800353F4(void *, void *);
extern void func_80164BA4(void *);
extern void func_8016A36C(void);

/* Update shared state and the controller callback, then process and mark linked objects. */
void func_8016CAE8(void *controller, void *unused_1, void *unused_2, u8 *active_object)
{
    s32 object_index;
    u16 update_count;
    u16 state_flags;
    u8 *object_header;
    u8 *object;
    u8 *flags_page;
    u8 *state;

    flags_page = (u8 *)0x80010000;
    state = D_80083460;
    
    state_flags = *(u16 *)(flags_page + 0x3714);
    update_count = *(u16 *)(state + 0xA);
    *(u16 *)(flags_page + 0x3714) = state_flags | 8;
    *(u16 *)(state + 0xA) = update_count + 1;
    if (*(u32 *)(state + 0x10) == (u32)(active_object - 0x20)) {
        *(u32 *)(state + 0x10) &= 0x7FFFFFFF;
    }

    func_800353F4(D_80175392, state);
    object_index = 0;
    active_object[0x6D] = 0;
    ((u8 *)controller)[0x9B] = 0;
    *(void **)((u8 *)controller + 0x8C) = (void *)func_8016A36C;

    do {
        object = *(u8 **)(D_800E3D7C[0] + (object_index * 4) + 0xAC);
        if (object != 0) {
            func_80164BA4(object);
            object_header = *(u8 **)(D_800E3D7C[0] + (object_index * 4) + 0xAC) - 0x20;
            *(u32 *)(object_header + 0x10) |= 0x80000000;
        }
        object_index++;
    } while (object_index < 2);
}
