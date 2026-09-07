#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 rand();
extern s32 D_80024DA0;
extern s32 D_80024FF0;

/* Creates an object at a randomized offset from the source and initializes its actor data. */
void func_8187B8B0(
    void *source,
    s16 field_04_value,
    s32 field_00_value,
    s16 paired_value,
    s32 x_offset,
    s32 y_offset,
    s32 z_offset)
{
    register s32 saved_x_offset ASM_REG("$18") = x_offset;   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *source_obj = source;
    register s16 saved_field_04 ASM_REG("$22") = field_04_value;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 saved_field_00 ASM_REG("$23") = field_00_value;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s16 saved_pair ASM_REG("$20") = paired_value;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 saved_y_offset = y_offset;
    s32 saved_z_offset = z_offset;
    void *spawned_obj;
    void *actor_data;
    s32 x_jitter;
    s32 y_jitter;
    s32 z_jitter;
    s32 x_bias;
    s32 y_bias;
    s32 z_bias;
    s32 x_pos;
    s32 y_pos;
    s32 z_pos;
    register void *init_obj ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *init_data;
    void *x_dest;
    void *y_dest;
    void *z_dest;

    spawned_obj = func_8003FD64(0x211, source_obj);
    if (spawned_obj != NULL) {
        FIELD(spawned_obj, s32 *, 0x10) = (s32)&D_80024FF0;
        x_jitter = rand() & 0x1F;
        x_pos = FIELD(FIELD(source_obj, void **, 8), u16 *, 2);
        x_dest = FIELD(spawned_obj, void **, 8);
        x_pos += x_jitter;
        x_bias = saved_x_offset - 0x10;
        x_pos += x_bias;
        FIELD(x_dest, s16 *, 2) = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = FIELD(FIELD(source_obj, void **, 8), u16 *, 6);
        y_dest = FIELD(spawned_obj, void **, 8);
        y_pos += y_jitter;
        y_bias = saved_y_offset - 0x10;
        y_pos += y_bias;
        FIELD(y_dest, s16 *, 6) = (s16)y_pos;

        z_jitter = rand();
        init_obj = spawned_obj;
        init_data = &D_80024DA0;
        ASM_USE2(init_obj, init_data);   /* MATCH pin: retail schedule: same instructions, different order without it */
        z_jitter &= 0x1F;
        z_pos = FIELD(FIELD(source_obj, void **, 8), u16 *, 0xA);
        actor_data = (u8 *)spawned_obj + 0x20;
        z_dest = FIELD(spawned_obj, void **, 8);
        z_pos += z_jitter;
        z_bias = saved_z_offset - 0x10;
        z_pos += z_bias;
        FIELD(z_dest, s16 *, 0xA) = (s16)z_pos;
        ASM_KEEP(saved_x_offset);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(saved_y_offset);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(saved_z_offset);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        FIELD(actor_data, s16 *, 0x4) = saved_field_04;
        ASM_KEEP(saved_field_04);   /* MATCH pin: retail schedule: same instructions, different order without it */
        FIELD(actor_data, s16 *, 0x10) = saved_pair;
        FIELD(actor_data, s16 *, 0x12) = saved_pair;
        func_8004491C(init_obj, init_data, z_dest);
        ASM_KEEP(saved_pair);   /* MATCH pin: retail schedule: same instructions, different order without it */
        FIELD(actor_data, s32 *, 0xB4) = rand() + 0x10000;
        FIELD(spawned_obj, s32 *, 0x20) = saved_field_00;
        ASM_KEEP(saved_field_00);   /* MATCH pin: retail schedule: same instructions, different order without it */
    }
}

