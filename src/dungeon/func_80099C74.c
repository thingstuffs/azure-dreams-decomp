#include "common.h"
#include "m2c_compat.h"

extern u8 D_8008333C[32];
extern s32 D_800E296C[3];

void *func_8003FC64();
M2C_UNK func_80064BC0();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_80065420();
M2C_UNK func_80065820();
extern M2C_UNK D_8009F21C;
extern M2C_UNK D_800DD824;

/* Creates an object at transformed coordinates and initializes its rendering and state. */
void *func_8009F3D4(s32 x, s32 y, s32 initial_value, s32 update_param, s32 mode) {
    s32 alloc_flags;
    void *position;
    void *object;
    void *render_data;
    void *state;
    u8 *scratchpad;
    u8 *view_config;
    u8 *camera_config;

    alloc_flags = 2;
    view_config = D_8008333C;
    camera_config = view_config - 0x1C4;
    scratchpad = (u8 *)0x1F800000;
    if (mode != 0) {
        alloc_flags = 0x202;
    }
    object = func_8003FC64(alloc_flags);
    if (object != NULL) {
        position = *(void **)((u8 *)object + 8);
        *(M2C_UNK **)((u8 *)object + 0x10) = &D_8009F21C;
        *(u16 *)(scratchpad + 0x98) = 0;
        *(u16 *)(scratchpad + 0x9A) = 0;
        *(u32 *)(scratchpad + 0x34) = 0x1800;
        *(u32 *)(scratchpad + 0x30) = 0x1800;
        *(u32 *)(scratchpad + 0x38) = 0;
        *(u16 *)(scratchpad + 0x9C) = *(u16 *)(camera_config + 0xB0);
        func_80065820((void *)0x1F800098, (void *)0x1F8000D0);
        func_80064BC0((void *)0x1F8000D0, (void *)0x1F800030);
        *(u32 *)(scratchpad + 0xE4) = 0;
        *(u32 *)(scratchpad + 0xE8) = 0;
        *(u32 *)(scratchpad + 0xEC) = 0;
        func_80064CF0((void *)0x1F8000D0);
        func_80064D80((void *)0x1F8000D0);
        *(u16 *)(scratchpad + 0x74) = 0;
        *(u16 *)(scratchpad + 0x70) = x - ((s32)(1 << *(s16 *)(view_config + 0x14)) / 2);
        *(u16 *)(scratchpad + 0x72) = y - ((s32)(1 << *(s16 *)(view_config + 0x16)) / 2);
        func_80065420((void *)0x1F800070, (void *)0x1F8000F0,
                      (void *)0x1F800090, (void *)0x1F800094);
        *(u16 *)((u8 *)position + 2) = *(u16 *)(scratchpad + 0xF0);
        *(u16 *)((u8 *)position + 6) = *(u16 *)(scratchpad + 0xF2);
        render_data = *(void **)((u8 *)object + 0xC);
        *(s16 *)((u8 *)render_data + 0x14) = 0xC;
        *(M2C_UNK **)((u8 *)render_data + 8) = &D_800DD824;
        *(s16 *)((u8 *)render_data + 0x1E) = 0x2000;
        *(s16 *)((u8 *)render_data + 0x1C) = 0x2000;
        state = (u8 *)object + 0x20;
        *(s16 *)((u8 *)state + 0x1C) = 8;
        *(s32 *)((u8 *)object + 0x20) = initial_value;
        *(s32 *)((u8 *)state + 0x28) = update_param;
        *(s16 *)((u8 *)state + 0x2E) = (s16)mode;
        if (mode == 0) {
            D_800E296C[0] |= 0x40000;
        }
    }
    return object;
}
