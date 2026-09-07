#include "common.h"

typedef struct Data {
    u16 pad0;
    u16 x;
    u16 pad4;
    u16 y;
    u16 pad8;
    u16 z;
} Data;

typedef struct Object {
    u8 pad0[8];
    Data *data;
    u8 padC[4];
    void *callback;
} Object;

extern Object *func_8003FD64();
extern s32 rand(void);
extern void func_8004491C(Object *, void *, Data *);
extern u8 D_800244E4[];
extern u8 D_80024734[];

/* Spawn and initialize an object at a randomized offset from its parent. */
void func_80024798(Object *source, s32 state_14_value, s32 state_08_value, s32 state_32_value,
                   s32 x_offset, s32 y_offset, s32 z_offset) {
    Object *parent = source;
    register s32 held_x_offset ASM_REG("$18") = x_offset;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 held_y_offset = y_offset;
    s32 held_z_offset = z_offset;
    s32 state_14 = state_14_value;
    register s32 state_08 ASM_REG("$23") = state_08_value;   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 state_32 ASM_REG("$22") = state_32_value;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    Object *spawned;
    Data *position;
    u8 *state;
    s32 jitter;

    spawned = func_8003FD64(0x211, parent);
    if (spawned != 0) {
        spawned->callback = D_80024734;
        jitter = rand();
        spawned->data->x =
            parent->data->x +
            (jitter & 0xF) + (held_x_offset - 8);
        jitter = rand();
        spawned->data->y =
            parent->data->y +
            (jitter & 0xF) + (held_y_offset - 8);
        state = (u8 *)spawned + 0x20;
        jitter = rand();
        position = spawned->data;
        position->z =
            parent->data->z +
            (jitter & 0x1F) + (held_z_offset - 0x10);
        *(s16 *)(state + 0x14) = state_14;
        *(s16 *)(state + 0x32) = state_32;
        func_8004491C(spawned, D_800244E4, position);
        *(s32 *)(state + 8) = state_08;
        ASM_KEEP(state_08);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(state_32);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(held_x_offset);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(held_y_offset);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(held_z_offset);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    }
}
