#include "common.h"

typedef struct S_801720EC_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} S_801720EC_0;   /* entity in func_801720EC */

typedef struct S_801720EC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801720EC_1;   /* arg2 in func_801720EC */

typedef struct S_801720EC_2 {
    u8 pad_00[0x8C];
    volatile s32 unk_8C;
    u8 pad_90[0xA];
    volatile s8 unk_9A;
    volatile s8 unk_9B;
} S_801720EC_2;   /* output in func_801720EC */



extern s32 func_80047784();
extern s32 func_8009B4B0();
extern s32 func_800A2B5C();
extern s32 func_800A44E0();
extern s32 func_800A4ACC();
extern s32 func_800A5690();
extern s16 func_800BCB04();
extern s32 func_800C77D0();
extern s32 func_800C7930();

extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174558[];

/* Checks the tile ahead and updates the entity's action when the height permits. */
s32 func_801720EC(void *action_state, s32 update_arg, void *sprite, void *actor)
{
    struct local_state {
        void *saved_ptr;
        volatile u8 pad[20];
    } state;
    register s32 kept_result ASM_REG("$23") = 0;   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register void *entity ASM_REG("$17") = actor;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u16 flags;
    s32 direction;
    u16 base_x;
    register u16 base_y ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 delta_offset;
    s16 x;
    s16 y;
    u16 *y_delta;
    u16 *x_delta;
    u8 *x_steps;
    s16 height;

    ((S_801720EC_0 *)entity)->unk_71 &= 0x7f;
    flags = D_80083462;
    if (flags & 0x2000) {
        return -1;
    }

    if (!(((S_801720EC_0 *)entity)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((s16)func_800A2B5C(entity) != 0) {
        return -1;
    }

    {
        register void *entity_base ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        entity_base = (u8 *)entity - 0x20;
        state.saved_ptr = entity_base;
        func_800C7930(entity_base, update_arg, 8, 0x300);
    }
    if ((s16)func_800A2B5C(entity) != 0) {
        return -1;
    }

    base_x = ((S_801720EC_1 *)sprite)->unk_24;
    base_y = ((S_801720EC_1 *)sprite)->unk_25;
    x = base_x;
    y = base_y;
    direction = (((S_801720EC_0 *)entity)->unk_2A.s >> 9) & 7;
    if ((s16)func_800A44E0(x << 6, y << 6, ((S_801720EC_0 *)entity)->unk_88.s, direction << 9) != 0) {
        return 0;
    }

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    x_steps = (u8 *)&D_8006CCD8;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    delta_offset = direction << 1;
    x_delta = (u16 *)(x_steps + delta_offset);
    ASM_KEEP_NV(delta_offset);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    y_delta = (u16 *)((u8 *)&D_8006CCE8 + delta_offset);
    {
        s32 step_x;
        register s32 step_y ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        step_x = *x_delta;
        step_y = *y_delta;
        if (func_8009B4B0(entity, (base_x + step_x) & 0xffff,
                          (base_y + step_y) & 0xffff) != 0) {
            return 0;
        }
    }

    if ((s16)func_800A5690() == 0) {
        return 0;
    }

    height = func_800BCB04((((x + (s16)*x_delta) << 6) + 0x20) & 0xffe0,
                           (((y + (s16)*y_delta) << 6) + 0x20) & 0xffe0,
                           (s16)(((S_801720EC_0 *)entity)->unk_88.u - 0x20));
    if (height >= 0x201) {
        return 0;
    }
    if ((s16)(height - ((S_801720EC_0 *)entity)->unk_88.u) >= -0x3f) {
        register void *output ASM_REG("$8") = action_state;   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        ((S_801720EC_2 *)output)->unk_9B = 0;
        ((S_801720EC_2 *)output)->unk_8C = 0;
        ((S_801720EC_2 *)output)->unk_9A = 0x17;
        (*(u8 * *)((u8 *)sprite + 0x2c)) = D_80174558;
        func_80047784(sprite,
                      D_80174558[((D_80083228 + ((S_801720EC_0 *)entity)->unk_2A.u + 0x100) >> 9) & 7],
                      0);
        func_800A4ACC(entity);
        {
            register s32 update_mode ASM_REG("$6") = 8;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            register s32 update_flags ASM_REG("$7") = 0x300;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            void *entity_base = state.saved_ptr;
            ASM_KEEP_NV(update_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(update_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP_NV(entity_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ((S_801720EC_0 *)entity)->unk_6D--;
            func_800C77D0(entity_base, update_arg, update_mode, update_flags);
        }
        ASM_USE_NV(kept_result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        return 1;
    }
    return 0;
}
