#include "common.h"

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

typedef struct {
    s16 x;
    u16 y;
} Coord;

typedef struct {
    Coord value[8];
} __attribute__((packed)) CoordTable;

typedef struct {
    u32 word[3];
} __attribute__((packed)) Packed12;

extern Rect D_80024038;
extern CoordTable D_80024064;
extern void *jtbl_80024088[9];
__asm__(".set jtbl_80024088, 0x80024088");

extern Packed12 D_80025618;
extern Packed12 D_80025624;
extern s16 D_80025630[8];
extern void *D_800246B4[3];
extern u8 D_80045340[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_800DDC40[];
extern u8 D_800E3D68[];
extern s32 D_8008346C;
extern s32 D_800814A0[3];

extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_80024470(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(s32, s32, s32, void *);
extern void func_800A56E0(s32);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern void *func_8003FC64(s32);
extern u16 GetTPage(s32, s32, s32, s32);
extern void func_800240AC(void *, s32, void *);

typedef struct S_func_8190B2D0_0 {
    void * unk_0;
    void * unk_4;
    u8 pad_8[0x1];
    u8 unk_9;
    union {
        s16 s16;
        u16 u16;
    } unk_A;
    u8 pad_C[0x6C];
    union {
        s16 s16;
        u16 u16;
    } unk_78;
    u8 unk_7A;
    union {
        s8 s8;
        u8 u8;
    } unk_7B;
    u8 pad_7C[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_7E;
    u8 pad_80[0x2];
    union {
        s16 s16;
        u16 u16;
    } unk_82;
    u8 pad_84[0x4];
    s16 unk_88;
    s16 unk_8A;
    u8 pad_8C[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_90;
    u8 pad_92[0x4];
    Packed12 unk_96;
    u8 unk_A2;
    u8 unk_A3;
} S_func_8190B2D0_0;

typedef struct S_func_8190B2D0_1 {
    u8 pad_0[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_func_8190B2D0_1;

typedef struct S_func_8190B2D0_2 {
    u8 pad_0[0x8];
    void * unk_8;
    void * unk_C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_func_8190B2D0_2;

typedef struct S_func_8190B2D0_3 {
    union {
        u32 u32;
        struct {
            u8 pad_0[0x2];
            u16 unk_2;
        } at_2_u16;
    } unk_0;
    union {
        u32 u32;
        struct {
            u8 pad_4[0x2];
            u16 unk_6;
        } at_6_u16;
    } unk_4;
    union {
        u32 u32;
        struct {
            u8 pad_8[0x2];
            u16 unk_A;
        } at_A_u16;
    } unk_8;
} S_func_8190B2D0_3;

typedef struct S_func_8190B2D0_4 {
    union {
        s32 s32;
        struct {
            u8 pad_0[0x2];
            u16 unk_2;
        } at_2_u16;
    } unk_0;
    union {
        s32 s32;
        struct {
            u8 pad_4[0x2];
            u16 unk_6;
        } at_6_u16;
    } unk_4;
    union {
        s32 s32;
        void * ptr;
        struct {
            u8 pad_8[0x2];
            s16 unk_A;
        } at_A_s16;
        struct {
            u8 pad_8[0x2];
            u16 unk_A;
        } at_A_u16;
    } unk_8;
    union {
        s32 s32;
        void * ptr;
    } unk_C;
    union {
        s32 s32;
        void * ptr;
    } unk_10;
    s32 unk_14;
    u8 pad_18[0x28];
    Packed12 unk_40;
} S_func_8190B2D0_4;

typedef struct S_func_8190B2D0_5 {
    u8 pad_0[0x6];
    u16 unk_6;
    void * unk_8;
    union {
        u32 u32;
        u8 u8;
        struct {
            u8 pad_C[0x1];
            u8 unk_D;
        } at_D_u8;
        struct {
            u8 pad_C[0x2];
            u8 unk_E;
        } at_E_u8;
    } unk_C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_func_8190B2D0_5;

typedef struct S_func_8190B2D0_6 {
    u8 pad_0[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_func_8190B2D0_6;

typedef struct S_func_8190B2D0_7 {
    u8 pad_0[0xA];
    u16 unk_A;
    u16 unk_C;
    u8 pad_E[0x1E];
    void * unk_2C;
    void * unk_30;
    void * unk_34;
} S_func_8190B2D0_7;

typedef struct S_func_8190B2D0_8 {
    u16 unk_0;
} S_func_8190B2D0_8;

typedef struct S_func_8190B2D0_9 {
    u8 pad_0[0x4];
    u16 unk_4;
} S_func_8190B2D0_9;

/* Updates a moving effect, its target animation, and cleanup state. */
void func_80024AD0(void *effect_arg, void *motion_arg, void *sprite_arg)
{
    static void *const state_labels[] = {
        &&state0, &&state1, &&state2, &&state3, &&state4,
        &&state5, &&done, &&done, &&state8
    };
    s16 start_offset[3];
    Rect capture_rect;
    Point capture_point;
    CoordTable directions;
    S_func_8190B2D0_1 *owner;
    u32 owner_base;
    register u32 source_pos;
    s32 state;
    register S_func_8190B2D0_0 *effect ASM_REG("$19") = effect_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_func_8190B2D0_4 *motion_or_child = motion_arg;
    S_func_8190B2D0_5 *sprite = sprite_arg;

    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    owner = effect->unk_0;
    capture_rect = D_80024038;
    directions = D_80024064;
    owner_base = (u32)((u8 *)owner - 32);
    source_pos = (u32)((S_func_8190B2D0_2 *)owner_base)->unk_8;
    state = effect->unk_A.s16;

    if ((u32)state >= 9U) {
        goto done;
    }
    (void)state_labels;
    goto *jtbl_80024088[(u32)state];

state0:
    {
        s16 owner_flags;
        u16 next_state;
        s32 offset_ready;
        sprite->unk_C.u32 = 0x00808080;
        effect->unk_96 = D_80025624;
        sprite->unk_8 = (u8 *)effect + 0x96;
        owner_flags = owner->unk_2A;
        D_80025630[0] = 1;
        next_state = effect->unk_A.u16;
        effect->unk_7E.u16 = (u16)(owner_flags >> 9) & 7;
        next_state++;
        effect->unk_A.u16 = next_state;
        offset_ready = func_8003DF74(((S_func_8190B2D0_5 *)((S_func_8190B2D0_2 *)owner_base)->unk_C)->unk_8,
                           ((S_func_8190B2D0_2 *)owner_base)->unk_C, start_offset, 0);
        if (offset_ready == 0 &&
            !(((S_func_8190B2D0_5 *)((S_func_8190B2D0_2 *)owner_base)->unk_C)->unk_14 & 0x8000)) {
            goto done;
        }
    }

state1:
    {
        u16 next_state;
        u16 base_z;
        u16 base_height;
        S_func_8190B2D0_6 *target;
        register S_func_8190B2D0_3 *target_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        S_func_8190B2D0_5 *owner_sprite;
        s32 target_z;
        register s32 height_or_steps ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        motion_or_child->unk_0.at_2_u16.unk_2 = ((S_func_8190B2D0_3 *)source_pos)->unk_0.at_2_u16.unk_2;
        motion_or_child->unk_4.at_6_u16.unk_6 = ((S_func_8190B2D0_3 *)source_pos)->unk_4.at_6_u16.unk_6;
        base_z = ((S_func_8190B2D0_3 *)source_pos)->unk_8.at_A_u16.unk_A;
        motion_or_child->unk_8.at_A_u16.unk_A = base_z;
        if (!(((S_func_8190B2D0_5 *)((S_func_8190B2D0_2 *)owner_base)->unk_C)->unk_14 & 0x8000)) {
            motion_or_child->unk_0.at_2_u16.unk_2 += start_offset[0];
            motion_or_child->unk_4.at_6_u16.unk_6 += start_offset[1];
            motion_or_child->unk_8.at_A_u16.unk_A += start_offset[2];
        } else {
            motion_or_child->unk_8.at_A_u16.unk_A =
                (u16)(base_z - 64);
        }

        if (((S_func_8190B2D0_8 *)effect->unk_4)->unk_0 & 0x80) {
            if (!(effect->unk_7A & 4)) {
                func_8004491C((u8 *)effect - 32, D_80045340);
                sprite->unk_C.at_E_u8.unk_E = 20;
                sprite->unk_C.at_D_u8.unk_D = 20;
                sprite->unk_C.u8 = 20;
                sprite->unk_14 |= 0xC;
                sprite->unk_10 = 0;
                sprite->unk_1E = 0x800;
                sprite->unk_1C = 0x800;
                effect->unk_7A |= 4;
            }
        } else {
            goto done;
        }

        target = owner->unk_60;
        if (target != 0) {
            target_pos = ((S_func_8190B2D0_2 *)((u8 *)target - 32))->unk_8;
            height_or_steps = D_800DDC40[target->unk_13] + 32;
            target_z = target_pos->unk_8.at_A_u16.unk_A - height_or_steps;
            effect->unk_78.u16 = (u16)target_z;
            owner_sprite = ((S_func_8190B2D0_2 *)((u8 *)owner - 32))->unk_C;
            effect->unk_A2 =
                owner_sprite->unk_24 +
                D_8006CCD8[(s16)effect->unk_7E.s16 * 2];
            effect->unk_A3 =
                owner_sprite->unk_25 +
                D_8006CCE8[(s16)effect->unk_7E.s16 * 2];

            if (owner->unk_72 != owner_sprite->unk_24) {
                height_or_steps = owner->unk_72 - owner_sprite->unk_24;
            } else {
                height_or_steps = owner->unk_73;
                height_or_steps -= owner_sprite->unk_25;
            }
            if (height_or_steps < 0) {
                height_or_steps = -height_or_steps;
            }
            effect->unk_7B.u8 = (u8)((height_or_steps << 1) - 1);
        } else {
            base_height = owner->unk_88;
            effect->unk_7B.u8 = 32;
            effect->unk_78.u16 = (u16)(base_height - 80);
        }

        motion_or_child->unk_C.s32 =
            (s32)directions.value[effect->unk_7E.s16].x << 16;
        motion_or_child->unk_10.s32 =
            (s32)directions.value[effect->unk_7E.s16].y << 16;
        motion_or_child->unk_14 =
            (((s32)effect->unk_78.s16 << 16) - motion_or_child->unk_8.s32) /
            (s8)effect->unk_7B.u8;
        effect->unk_82.u16 = 0;
        next_state = effect->unk_A.u16 + 1;
        effect->unk_A.u16 = next_state;
        effect->unk_88 = (s16)(s8)effect->unk_7B.u8;
        effect->unk_8A =
            (s16)((s8)effect->unk_7B.u8 *
                  (s8)effect->unk_7B.u8);
        goto done;
    }

state2:
    {
        u32 particle_index;
        u8 frames_left;
        register s32 elapsed_frames ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 collision;
        register S_func_8190B2D0_3 *target_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        particle_index = 0;
        do {
            s32 particle_shade;
            s32 random_bits = func_80069EF8();
            particle_shade = (random_bits & 0xFF) | 0x80;
            func_80024470((u8 *)effect - 32, effect->unk_7E.s16,
                          0x00202020, particle_shade, 0, 0, 0);
            particle_index++;
        } while ((s32)particle_index < 4);
        {
            u16 angle = sprite->unk_1A + 400;
            sprite->unk_1A = angle;
            if ((u16)angle >= 0x1001) {
                sprite->unk_1A =
                    (u16)(angle - 4096);
            }
        }
        elapsed_frames = effect->unk_88 - effect->unk_7B.s8 + 1;
        sprite->unk_C.u8 = (u8)((elapsed_frames * elapsed_frames * 108) /
                                    effect->unk_8A + 20);
        elapsed_frames = effect->unk_88 - effect->unk_7B.s8 + 1;
        sprite->unk_C.at_D_u8.unk_D = (u8)((elapsed_frames * elapsed_frames * 108) /
                                    effect->unk_8A + 20);
        elapsed_frames = effect->unk_88 - effect->unk_7B.s8 + 1;
        sprite->unk_C.at_E_u8.unk_E = (u8)((elapsed_frames * elapsed_frames * 108) /
                                    effect->unk_8A + 20);
        collision = func_800A4778(motion_or_child->unk_0.at_2_u16.unk_2, motion_or_child->unk_4.at_6_u16.unk_6,
                               motion_or_child->unk_8.at_A_s16.unk_A, owner->unk_60);
        if ((collision << 16) != 0) {
            effect->unk_A.u16 = 8;
            effect->unk_82.u16 = 0;
            sprite->unk_C.at_E_u8.unk_E = 0;
            sprite->unk_C.at_D_u8.unk_D = 0;
            sprite->unk_C.u8 = 0;
            sprite->unk_1E = 0;
            sprite->unk_1C = 0;
            goto done;
        }
        frames_left = effect->unk_7B.u8 - 1;
        effect->unk_7B.u8 = frames_left;
        if ((s8)frames_left <= 0) {
            if (owner->unk_60 != 0) {
                effect->unk_A.u16 = 3;
                effect->unk_82.u16 = 0;
                func_800A56E0(0x300);
                ((S_func_8190B2D0_6 *)owner->unk_60)->unk_14 |= 0x100000;
                target_pos = ((S_func_8190B2D0_2 *)((u8 *)owner->unk_60 - 32))->unk_8;
                motion_or_child->unk_0.at_2_u16.unk_2 = target_pos->unk_0.at_2_u16.unk_2;
                motion_or_child->unk_4.at_6_u16.unk_6 = target_pos->unk_4.at_6_u16.unk_6;
                motion_or_child->unk_8.at_A_u16.unk_A = effect->unk_78.u16;
                goto done;
            }
            effect->unk_A.u16 = 8;
            effect->unk_82.u16 = 0;
            sprite->unk_C.at_E_u8.unk_E = 0;
            sprite->unk_C.at_D_u8.unk_D = 0;
            sprite->unk_C.u8 = 0;
            sprite->unk_1E = 0;
            sprite->unk_1C = 0;
            goto done;
        }
        motion_or_child->unk_0.s32 += motion_or_child->unk_C.s32;
        motion_or_child->unk_4.s32 += motion_or_child->unk_10.s32;
        motion_or_child->unk_8.s32 += motion_or_child->unk_14;
        goto done;
    }

state3:
    {
        register S_func_8190B2D0_3 *target_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        S_func_8190B2D0_3 *child_pos;
        u32 child_data;
        s32 frame;
        void *child_object;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        S_func_8190B2D0_6 *target;
        s32 current_frame;
        u32 spawn_frame;
        {
            u16 angle = sprite->unk_1A + 400;
            sprite->unk_1A = angle;
            if ((u16)angle >= 0x1001) {
                sprite->unk_1A =
                    (u16)(angle - 4096);
            }
        }
        effect->unk_82.u16++;
        frame = effect->unk_82.s16;
        if (frame == 1) {
            capture_point.x = capture_rect.x + ((s16)capture_rect.w >> 1);
            capture_point.y = capture_rect.y + 72;
            func_800B8FC8(owner->unk_60, &capture_rect, &capture_point, 1,
                          frame);
        }
        spawn_frame = effect->unk_82.s16;
        if ((s16)spawn_frame != 4) {
            goto done;
        }
        {
            motion_or_child = func_8003FC64(0x212);
            if (motion_or_child != 0) {
                child_object = motion_or_child;
                child_data = (u32)((u8 *)motion_or_child + 32);
                ((S_func_8190B2D0_7 *)child_data)->unk_2C = owner;
                ((S_func_8190B2D0_7 *)child_data)->unk_30 = owner->unk_60;
                ((S_func_8190B2D0_7 *)child_data)->unk_34 = effect;
                motion_or_child->unk_10.ptr = D_800246B4;
                func_8004491C(child_object, D_80045340);
                sprite = motion_or_child->unk_C.ptr;
                sprite->unk_10 = 32;
                sprite->unk_6 = 6;
                sprite->unk_14 |= 0xC;
                child_pos = motion_or_child->unk_8.ptr;
                ((S_func_8190B2D0_7 *)child_data)->unk_A = 0;
                ((S_func_8190B2D0_7 *)child_data)->unk_C = 0;
                target = owner->unk_60;
                target_pos = ((S_func_8190B2D0_2 *)((u8 *)target - 32))->unk_8;
                child_pos->unk_0.u32 = target_pos->unk_0.u32;
                child_pos->unk_4.u32 = target_pos->unk_4.u32;
                child_pos->unk_8.u32 = target_pos->unk_8.u32;
                sprite = motion_or_child->unk_C.ptr;
                sprite->unk_1E = 0x1000;
                sprite->unk_1C = 0x1000;
                sprite->unk_C.at_E_u8.unk_E = 0x80;
                sprite->unk_C.at_D_u8.unk_D = 0x80;
                sprite->unk_C.u8 = 0x80;
                motion_or_child->unk_40 = D_80025618;
                sprite->unk_8 = (u8 *)motion_or_child + 64;
                ((S_func_8190B2D0_9 *)sprite->unk_8)->unk_4 =
                    GetTPage(2, 1, 0x340, 0x100);
            }
        }
        current_frame = effect->unk_82.s16;
        if (current_frame != (s16)spawn_frame) {
            goto done;
        }
        effect->unk_A.u16 = current_frame;
        effect->unk_82.u16 = 0;
        effect->unk_90.u16 = 0;
        goto done;
    }

state4:
    {
        s32 fade_frame;
        s32 green_frame;
        S_func_8190B2D0_6 *target;
        S_func_8190B2D0_5 *target_sprite;
        effect->unk_82.u16 = effect->unk_82.u16 + 1;
        {
            u16 angle = sprite->unk_1A + 400;
            sprite->unk_1A = angle;
            if ((u16)angle >= 0x1001) {
                sprite->unk_1A =
                    (u16)(angle - 4096);
            }
        }
        if (effect->unk_82.s16 < 42) {
            motion_or_child->unk_8.s32 -= 0x20000;
        }
        if (effect->unk_82.s16 == 81) {
            sprite->unk_10 = 32;
            sprite->unk_C.u8 = 54;
            sprite->unk_C.at_D_u8.unk_D = 54;
            sprite->unk_C.at_E_u8.unk_E = 54;
        }
        if (effect->unk_82.s16 >= 81) {
            fade_frame = effect->unk_82.s16;
            sprite->unk_C.u8 = (u8)(((100 - fade_frame) * 54) / 20);
            green_frame = effect->unk_82.s16;
            sprite->unk_C.at_D_u8.unk_D = (u8)(((100 - green_frame) * 54) / 20);
            fade_frame = effect->unk_82.s16;
            sprite->unk_C.at_E_u8.unk_E = (u8)(((100 - fade_frame) * 54) / 20);
        }
        if (effect->unk_82.s16 >= 0) {
            target = owner->unk_60;
            target->unk_1C |= 0x10000000;
            target_sprite = ((S_func_8190B2D0_2 *)((u8 *)target - 32))->unk_C;
            if (effect->unk_82.s16 >= 43) {
                if (effect->unk_82.s16 < 64) {
                    target_sprite->unk_C.at_E_u8.unk_E += 3;
                    target_sprite->unk_C.at_D_u8.unk_D += 3;
                    target_sprite->unk_C.u8 += 3;
                }
            } else {
                if (effect->unk_82.s16 == 41) {
                    target_sprite->unk_C.at_E_u8.unk_E -= 60;
                    target_sprite->unk_C.at_D_u8.unk_D -= 60;
                    target_sprite->unk_C.u8 -= 60;
                }
            }
        }
        if (effect->unk_82.s16 >= 100) {
            S_func_8190B2D0_6 *finished_target;
            u32 clear_tint_mask;
            clear_tint_mask = 0xEFFFFFFF;
            finished_target = owner->unk_60;
            finished_target->unk_1C &= clear_tint_mask;
            target_sprite = ((S_func_8190B2D0_2 *)((u8 *)finished_target - 32))->unk_C;
            target_sprite->unk_C.at_E_u8.unk_E = 128;
            target_sprite->unk_C.at_D_u8.unk_D = 128;
            target_sprite->unk_C.u8 = 128;
            effect->unk_A.u16++;
        }
        goto done;
    }

state5:
    {
        S_func_8190B2D0_6 *target;
        u8 target_mode;
        u32 clear_effect_mask;
        s32 effect_kind;
        if (effect->unk_90.s16 != 0) {
            clear_effect_mask = 0xFFEFFFFF;
            effect_kind = 255;
            target = owner->unk_60;
            target_mode = D_800E3D68[0];
            target->unk_14 &= clear_effect_mask;
            if (target_mode != effect_kind) {
                effect_kind = effect->unk_9;
            }
            func_800240AC(owner->unk_60, effect_kind, owner);
            effect->unk_A.u16 = 8;
            effect->unk_82.u16 = 30;
        }
        goto done;
    }

state8:
    {
        s16 old_frame;
        s16 frame;
        s32 cleanup_pending;
        old_frame = effect->unk_82.u16;
        frame = old_frame + 1;
        effect->unk_82.u16 = frame;
        if ((s16)frame < 31) {
            goto done;
        }
        cleanup_pending = D_80025630[0];
        effect->unk_82.u16 = old_frame;
        switch (cleanup_pending) {
        case 0: {
            D_8008346C = 0;
            *(u16 *)((u8 *)effect - 2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            break;
        }
        default:
            D_80025630[0] = 0;
            break;
        }
    }

done:
    return;
}
