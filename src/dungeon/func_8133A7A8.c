#include "common.h"

typedef struct {
    u8 pad_00[0x12];
    s16 state;
    u8 pad_14[4];
    s16 timer;
    u8 pad_1A[2];
    s16 phase;
} Entity;

typedef struct {
    u8 pad_00[2];
    s16 x;
    u8 pad_04[2];
    s16 y;
    u8 pad_08[2];
    u16 z;
} Actor;

typedef struct {
    s16 values[8];
} __attribute__((packed)) PhaseHeights;

extern PhaseHeights D_80164A54;
extern void *D_80164A68[];
extern u8 *D_80175D50;
extern u16 D_800DCE60[4];
extern s16 D_801760E0[4];
extern s16 D_801760E8[4];
extern u8 D_80083160[];
extern s16 D_80083780[];

extern void func_8004D294(void *, void *, s32);
extern void func_8004D7A8(s32);
extern s16 func_8016F4FC(void *);

/* Update camera focus and height through timed entity states and phases. */
void func_801717A8(Entity *entity) {
    PhaseHeights heights = D_80164A54;
    Actor *actor = *(Actor **)(D_80175D50 + 8);
    s16 phase_slot;
    s16 height_slot;
    s32 state = entity->state;
    register void *focus_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *offset_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 transition_ticks;
    u16 previous_state;
    register s32 coord_sum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 camera_mode ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 *camera_offset ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s16 *focus_pos ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 focus_y ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    static void *const state_labels[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_exit,
        &&jt_c4, &&jt_exit, &&jt_c6, &&jt_exit,
        &&jt_exit, &&jt_exit, &&jt_exit, &&jt_exit,
        &&jt_exit, &&jt_exit, &&jt_exit, &&jt_exit,
        &&jt_exit, &&jt_exit, &&jt_exit, &&jt_exit,
        &&jt_c20, &&jt_exit
    };

    (void)state_labels;
    if ((u32)state < 22) {
        goto *D_80164A68[state];
    }
    goto jt_exit;

jt_c0: {
    u16 offset_x;
    u16 offset_y;
    u16 offset_z;

    camera_mode = 1;
    entity->timer = 0;
    entity->phase = 2;
    entity->state++;
    offset_x = D_800DCE60[0];
    *(volatile s16 *)&D_801760E0[0] = offset_x;
    offset_y = D_800DCE60[1];
    offset_z = D_800DCE60[2];
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    camera_offset = D_801760E0;
    camera_offset[1] = offset_y;
    camera_offset[2] = offset_z - 0x600;
    D_801760E8[0] = actor->x;
    focus_pos = D_801760E8;
    focus_y = (u16)actor->y - 0x100;
    goto jt_case0_tail;
}

jt_c1:
    entity->timer++;
    if (entity->timer < 0x28) {
        goto jt_exit;
    }
    focus_arg = D_801760E8;
    offset_arg = D_801760E0;
    previous_state = entity->state;
    transition_ticks = 0x14;
    goto jt_call_common;

jt_c2:
    entity->timer++;
    if (entity->timer < 0x28) {
        goto jt_exit;
    }
    focus_arg = 0;
    offset_arg = D_800DCE60;
    previous_state = entity->state;
    transition_ticks = 0xA;

jt_call_common:
    entity->timer = 0;
    ASM_KEEP(transition_ticks);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    entity->state = previous_state + 1;
    func_8004D294(focus_arg, offset_arg, transition_ticks);
    goto jt_exit;

jt_c4: {
    s16 *camera;
    s16 *height_base;
    s16 *height;
    u8 *globals;

    entity->timer = 0;
    entity->state++;
    phase_slot = func_8016F4FC(actor);
    height_slot = phase_slot + 3;
    D_801760E0[0] = D_800DCE60[0];
    D_801760E0[1] = D_800DCE60[1];
    if (height_slot >= 8) {
        height_slot = phase_slot - 5;
    }
    camera_offset = D_801760E0;
    height_base = heights.values - 8;
    height = &height_base[height_slot];
    ASM_KEEP_NV(height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    camera_mode = 1;
    ASM_KEEP(camera_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    camera_offset[2] = height[8] * 0x200;
    camera = D_80083780;
    coord_sum = actor->x;
    coord_sum += camera[1];
    D_801760E8[0] = coord_sum / 2;
    focus_y = actor->y;
    focus_y += camera[3];
    focus_pos = D_801760E8;
    focus_y /= 2;
jt_case0_tail:
    *(volatile s16 *)&focus_pos[1] = focus_y;
    focus_pos[2] = actor->z;
    globals = D_80083160;
    *(s32 *)(globals + 0x154) = 0;
    *(s32 *)(globals + 0xCC) = 0;
    func_8004D7A8(camera_mode);
    func_8004D7A8(0);
    func_8004D294(focus_pos, camera_offset, 0xA);
    goto jt_exit;
}

jt_c6: {
    s16 *camera;
    s16 *height_base;
    s16 *height;
    u8 *globals;

    entity->timer = 0;
    entity->state++;
    phase_slot = func_8016F4FC(actor);
    height_slot = phase_slot + 2;
    D_801760E0[0] = D_800DCE60[0];
    D_801760E0[1] = D_800DCE60[1];
    if (height_slot >= 8) {
        height_slot = phase_slot - 6;
    }
    height_base = heights.values - 8;
    height = &height_base[height_slot];
    ASM_KEEP_NV(height);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    camera_mode = 1;
    ASM_KEEP(camera_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    D_801760E0[2] = height[8] * 0x200;
    camera = D_80083780;
    coord_sum = actor->x;
    coord_sum += camera[1];
    D_801760E8[0] = coord_sum / 2;
    coord_sum = actor->y;
    coord_sum += camera[3];
    D_801760E8[1] = coord_sum / 2;
    D_801760E8[2] = actor->z;
    globals = D_80083160;
    *(s32 *)(globals + 0x154) = 0;
    *(s32 *)(globals + 0xCC) = 0;
    func_8004D7A8(camera_mode);
    func_8004D7A8(0);
    func_8004D294(D_801760E8, D_801760E0, 2);
    goto jt_exit;
}

jt_c20: {
    s16 *camera;
    s16 *height_base;
    s16 *height;
    register s16 selected_slot ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *globals;

    if ((entity->timer & 0xF) == 0) {
        height_slot = func_8016F4FC(actor);
        D_801760E0[0] = D_800DCE60[0];
        D_801760E0[1] = D_800DCE60[1];
        entity->phase++;
        phase_slot = height_slot + entity->phase;
        selected_slot = phase_slot;
        if (phase_slot >= 8) {
            selected_slot = phase_slot - 8;
        }
        height_base = heights.values - 8;
        height = &height_base[selected_slot];
        ASM_KEEP_DEP_NV(height, selected_slot);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        camera_mode = 1;
        ASM_KEEP(camera_mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        D_801760E0[2] = height[8] * 0x200;
        camera = D_80083780;
        coord_sum = actor->x;
        coord_sum += camera[1];
        D_801760E8[0] = coord_sum / 2;
        coord_sum = actor->y;
        coord_sum += camera[3];
        D_801760E8[1] = coord_sum / 2;
        D_801760E8[2] = actor->z;
        globals = D_80083160;
        *(s32 *)(globals + 0x154) = 0;
        *(s32 *)(globals + 0xCC) = 0;
        func_8004D7A8(camera_mode);
        func_8004D7A8(0);
        func_8004D294(D_801760E8, D_801760E0, 4);
    }
}

jt_progress:
    entity->timer++;
    if (entity->timer >= 0x79) {
        entity->timer = 0;
        entity->phase = 0;
        entity->state++;
    }

jt_exit:
    return;
}
