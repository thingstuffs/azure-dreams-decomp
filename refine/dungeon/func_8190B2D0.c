#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    void *owner;
    u32 owner_base;
    register u32 source_pos;
    s32 state;
    register void *effect ASM_REG("$19") = effect_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *motion_or_child = motion_arg;
    void *sprite = sprite_arg;

    ASM_KEEP_NV(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    owner = FIELD(effect, void *, 0);
    capture_rect = D_80024038;
    directions = D_80024064;
    owner_base = (u32)((u8 *)owner - 32);
    source_pos = (u32)FIELD((void *)owner_base, void *, 8);
    state = FIELD(effect, s16, 0xA);

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
        FIELD(sprite, u32, 0xC) = 0x00808080;
        *(Packed12 *)((u8 *)effect + 0x96) = D_80025624;
        FIELD(sprite, void *, 8) = (u8 *)effect + 0x96;
        owner_flags = FIELD(owner, u16, 0x2A);
        D_80025630[0] = 1;
        next_state = FIELD(effect, u16, 0xA);
        FIELD(effect, u16, 0x7E) = (u16)(owner_flags >> 9) & 7;
        next_state++;
        FIELD(effect, u16, 0xA) = next_state;
        offset_ready = func_8003DF74(FIELD(FIELD((void *)owner_base, void *, 0xC), void *, 8),
                           FIELD((void *)owner_base, void *, 0xC), start_offset, 0);
        if (offset_ready == 0 &&
            !(FIELD(FIELD((void *)owner_base, void *, 0xC), u16, 0x14) & 0x8000)) {
            goto done;
        }
    }

state1:
    {
        u16 next_state;
        u16 base_z;
        u16 base_height;
        void *target;
        register void *target_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        void *owner_sprite;
        s32 target_z;
        register s32 height_or_steps ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        FIELD(motion_or_child, u16, 2) = FIELD((void *)source_pos, u16, 2);
        FIELD(motion_or_child, u16, 6) = FIELD((void *)source_pos, u16, 6);
        base_z = FIELD((void *)source_pos, u16, 0xA);
        FIELD(motion_or_child, u16, 0xA) = base_z;
        if (!(FIELD(FIELD((void *)owner_base, void *, 0xC), u16, 0x14) & 0x8000)) {
            FIELD(motion_or_child, u16, 2) += start_offset[0];
            FIELD(motion_or_child, u16, 6) += start_offset[1];
            FIELD(motion_or_child, u16, 0xA) += start_offset[2];
        } else {
            FIELD(motion_or_child, u16, 0xA) =
                (u16)(base_z - 64);
        }

        if (FIELD(FIELD(effect, void *, 4), u16, 0) & 0x80) {
            if (!(FIELD(effect, u8, 0x7A) & 4)) {
                func_8004491C((u8 *)effect - 32, D_80045340);
                FIELD(sprite, u8, 0xE) = 20;
                FIELD(sprite, u8, 0xD) = 20;
                FIELD(sprite, u8, 0xC) = 20;
                FIELD(sprite, u16, 0x14) |= 0xC;
                FIELD(sprite, u16, 0x10) = 0;
                FIELD(sprite, u16, 0x1E) = 0x800;
                FIELD(sprite, u16, 0x1C) = 0x800;
                FIELD(effect, u8, 0x7A) |= 4;
            }
        } else {
            goto done;
        }

        target = FIELD(owner, void *, 0x60);
        if (target != 0) {
            target_pos = FIELD(target, void *, -24);
            height_or_steps = D_800DDC40[FIELD(target, u8, 0x13)] + 32;
            target_z = FIELD(target_pos, u16, 0xA) - height_or_steps;
            FIELD(effect, u16, 0x78) = (u16)target_z;
            owner_sprite = FIELD(owner, void *, -20);
            FIELD(effect, u8, 0xA2) =
                FIELD(owner_sprite, u8, 0x24) +
                D_8006CCD8[(s16)FIELD(effect, s16, 0x7E) * 2];
            FIELD(effect, u8, 0xA3) =
                FIELD(owner_sprite, u8, 0x25) +
                D_8006CCE8[(s16)FIELD(effect, s16, 0x7E) * 2];

            if (FIELD(owner, s8, 0x72) != FIELD(owner_sprite, u8, 0x24)) {
                height_or_steps = FIELD(owner, s8, 0x72) - FIELD(owner_sprite, u8, 0x24);
            } else {
                height_or_steps = FIELD(owner, s8, 0x73);
                height_or_steps -= FIELD(owner_sprite, u8, 0x25);
            }
            if (height_or_steps < 0) {
                height_or_steps = -height_or_steps;
            }
            FIELD(effect, u8, 0x7B) = (u8)((height_or_steps << 1) - 1);
        } else {
            base_height = FIELD(owner, u16, 0x88);
            FIELD(effect, u8, 0x7B) = 32;
            FIELD(effect, u16, 0x78) = (u16)(base_height - 80);
        }

        FIELD(motion_or_child, s32, 0xC) =
            (s32)directions.value[FIELD(effect, s16, 0x7E)].x << 16;
        FIELD(motion_or_child, s32, 0x10) =
            (s32)directions.value[FIELD(effect, s16, 0x7E)].y << 16;
        FIELD(motion_or_child, s32, 0x14) =
            (((s32)FIELD(effect, s16, 0x78) << 16) - FIELD(motion_or_child, s32, 8)) /
            (s8)FIELD(effect, u8, 0x7B);
        FIELD(effect, u16, 0x82) = 0;
        next_state = FIELD(effect, u16, 0xA) + 1;
        FIELD(effect, u16, 0xA) = next_state;
        FIELD(effect, s16, 0x88) = (s16)(s8)FIELD(effect, u8, 0x7B);
        FIELD(effect, s16, 0x8A) =
            (s16)((s8)FIELD(effect, u8, 0x7B) *
                  (s8)FIELD(effect, u8, 0x7B));
        goto done;
    }

state2:
    {
        u32 particle_index;
        u8 frames_left;
        register s32 elapsed_frames ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 collision;
        register void *target_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        particle_index = 0;
        do {
            s32 particle_shade;
            s32 random_bits = func_80069EF8();
            particle_shade = (random_bits & 0xFF) | 0x80;
            func_80024470((u8 *)effect - 32, FIELD(effect, s16, 0x7E),
                          0x00202020, particle_shade, 0, 0, 0);
            particle_index++;
        } while ((s32)particle_index < 4);
        {
            u16 angle = FIELD(sprite, u16, 0x1A) + 400;
            FIELD(sprite, u16, 0x1A) = angle;
            if ((u16)angle >= 0x1001) {
                FIELD(sprite, u16, 0x1A) =
                    (u16)(angle - 4096);
            }
        }
        elapsed_frames = FIELD(effect, s16, 0x88) - FIELD(effect, s8, 0x7B) + 1;
        FIELD(sprite, u8, 0xC) = (u8)((elapsed_frames * elapsed_frames * 108) /
                                    FIELD(effect, s16, 0x8A) + 20);
        elapsed_frames = FIELD(effect, s16, 0x88) - FIELD(effect, s8, 0x7B) + 1;
        FIELD(sprite, u8, 0xD) = (u8)((elapsed_frames * elapsed_frames * 108) /
                                    FIELD(effect, s16, 0x8A) + 20);
        elapsed_frames = FIELD(effect, s16, 0x88) - FIELD(effect, s8, 0x7B) + 1;
        FIELD(sprite, u8, 0xE) = (u8)((elapsed_frames * elapsed_frames * 108) /
                                    FIELD(effect, s16, 0x8A) + 20);
        collision = func_800A4778(FIELD(motion_or_child, u16, 2), FIELD(motion_or_child, u16, 6),
                               FIELD(motion_or_child, s16, 0xA), FIELD(owner, void *, 0x60));
        if ((collision << 16) != 0) {
            FIELD(effect, u16, 0xA) = 8;
            FIELD(effect, u16, 0x82) = 0;
            FIELD(sprite, u8, 0xE) = 0;
            FIELD(sprite, u8, 0xD) = 0;
            FIELD(sprite, u8, 0xC) = 0;
            FIELD(sprite, u16, 0x1E) = 0;
            FIELD(sprite, u16, 0x1C) = 0;
            goto done;
        }
        frames_left = FIELD(effect, u8, 0x7B) - 1;
        FIELD(effect, u8, 0x7B) = frames_left;
        if ((s8)frames_left <= 0) {
            if (FIELD(owner, void *, 0x60) != 0) {
                FIELD(effect, u16, 0xA) = 3;
                FIELD(effect, u16, 0x82) = 0;
                func_800A56E0(0x300);
                FIELD(FIELD(owner, void *, 0x60), u32, 20) |= 0x100000;
                target_pos = FIELD(FIELD(owner, void *, 0x60), void *, -24);
                FIELD(motion_or_child, u16, 2) = FIELD(target_pos, u16, 2);
                FIELD(motion_or_child, u16, 6) = FIELD(target_pos, u16, 6);
                FIELD(motion_or_child, u16, 0xA) = FIELD(effect, u16, 0x78);
                goto done;
            }
            FIELD(effect, u16, 0xA) = 8;
            FIELD(effect, u16, 0x82) = 0;
            FIELD(sprite, u8, 0xE) = 0;
            FIELD(sprite, u8, 0xD) = 0;
            FIELD(sprite, u8, 0xC) = 0;
            FIELD(sprite, u16, 0x1E) = 0;
            FIELD(sprite, u16, 0x1C) = 0;
            goto done;
        }
        FIELD(motion_or_child, s32, 0) += FIELD(motion_or_child, s32, 0xC);
        FIELD(motion_or_child, s32, 4) += FIELD(motion_or_child, s32, 0x10);
        FIELD(motion_or_child, s32, 8) += FIELD(motion_or_child, s32, 0x14);
        goto done;
    }

state3:
    {
        register void *target_pos ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        void *child_pos;
        u32 child_data;
        s32 frame;
        register void *child_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        void *target;
        s32 current_frame;
        u32 spawn_frame;
        {
            u16 angle = FIELD(sprite, u16, 0x1A) + 400;
            FIELD(sprite, u16, 0x1A) = angle;
            if ((u16)angle >= 0x1001) {
                FIELD(sprite, u16, 0x1A) =
                    (u16)(angle - 4096);
            }
        }
        FIELD(effect, u16, 0x82)++;
        frame = FIELD(effect, s16, 0x82);
        if (frame == 1) {
            capture_point.x = capture_rect.x + ((s16)capture_rect.w >> 1);
            capture_point.y = capture_rect.y + 72;
            func_800B8FC8(FIELD(owner, void *, 0x60), &capture_rect, &capture_point, 1,
                          frame);
        }
        spawn_frame = FIELD(effect, s16, 0x82);
        if ((s16)spawn_frame != 4) {
            goto done;
        }
        {
            motion_or_child = func_8003FC64(0x212);
            if (motion_or_child != 0) {
                child_object = motion_or_child;
                child_data = (u32)((u8 *)motion_or_child + 32);
                FIELD((void *)child_data, void *, 44) = owner;
                FIELD((void *)child_data, void *, 48) = FIELD(owner, void *, 0x60);
                FIELD((void *)child_data, void *, 52) = effect;
                FIELD(motion_or_child, void *, 16) = D_800246B4;
                func_8004491C(child_object, D_80045340);
                sprite = FIELD(motion_or_child, void *, 12);
                FIELD(sprite, u16, 16) = 32;
                FIELD(sprite, u16, 6) = 6;
                FIELD(sprite, u16, 20) |= 0xC;
                child_pos = FIELD(motion_or_child, void *, 8);
                FIELD((void *)child_data, u16, 10) = 0;
                FIELD((void *)child_data, u16, 12) = 0;
                target = FIELD(owner, void *, 0x60);
                target_pos = FIELD(target, void *, -24);
                FIELD(child_pos, u32, 0) = FIELD(target_pos, u32, 0);
                FIELD(child_pos, u32, 4) = FIELD(target_pos, u32, 4);
                FIELD(child_pos, u32, 8) = FIELD(target_pos, u32, 8);
                sprite = FIELD(motion_or_child, void *, 12);
                FIELD(sprite, u16, 30) = 0x1000;
                FIELD(sprite, u16, 28) = 0x1000;
                FIELD(sprite, u8, 14) = 0x80;
                FIELD(sprite, u8, 13) = 0x80;
                FIELD(sprite, u8, 12) = 0x80;
                *(Packed12 *)((u8 *)motion_or_child + 64) = D_80025618;
                FIELD(sprite, void *, 8) = (u8 *)motion_or_child + 64;
                FIELD(FIELD(sprite, void *, 8), u16, 4) =
                    GetTPage(2, 1, 0x340, 0x100);
            }
        }
        current_frame = FIELD(effect, s16, 0x82);
        if (current_frame != (s16)spawn_frame) {
            goto done;
        }
        FIELD(effect, u16, 0xA) = current_frame;
        FIELD(effect, u16, 0x82) = 0;
        FIELD(effect, u16, 0x90) = 0;
        goto done;
    }

state4:
    {
        s32 fade_frame;
        s32 green_frame;
        void *target;
        void *target_sprite;
        FIELD(effect, u16, 0x82) = FIELD(effect, u16, 0x82) + 1;
        {
            u16 angle = FIELD(sprite, u16, 0x1A) + 400;
            FIELD(sprite, u16, 0x1A) = angle;
            if ((u16)angle >= 0x1001) {
                FIELD(sprite, u16, 0x1A) =
                    (u16)(angle - 4096);
            }
        }
        if (FIELD(effect, s16, 0x82) < 42) {
            FIELD(motion_or_child, s32, 8) -= 0x20000;
        }
        if (FIELD(effect, s16, 0x82) == 81) {
            FIELD(sprite, u16, 16) = 32;
            FIELD(sprite, u8, 12) = 54;
            FIELD(sprite, u8, 13) = 54;
            FIELD(sprite, u8, 14) = 54;
        }
        if (FIELD(effect, s16, 0x82) >= 81) {
            fade_frame = FIELD(effect, s16, 0x82);
            FIELD(sprite, u8, 12) = (u8)(((100 - fade_frame) * 54) / 20);
            green_frame = FIELD(effect, s16, 0x82);
            FIELD(sprite, u8, 13) = (u8)(((100 - green_frame) * 54) / 20);
            fade_frame = FIELD(effect, s16, 0x82);
            FIELD(sprite, u8, 14) = (u8)(((100 - fade_frame) * 54) / 20);
        }
        if (FIELD(effect, s16, 0x82) >= 0) {
            target = FIELD(owner, void *, 0x60);
            FIELD(target, u32, 28) |= 0x10000000;
            target_sprite = FIELD(target, void *, -20);
            if (FIELD(effect, s16, 0x82) >= 43) {
                if (FIELD(effect, s16, 0x82) < 64) {
                    FIELD(target_sprite, u8, 14) += 3;
                    FIELD(target_sprite, u8, 13) += 3;
                    FIELD(target_sprite, u8, 12) += 3;
                }
            } else {
                if (FIELD(effect, s16, 0x82) == 41) {
                    FIELD(target_sprite, u8, 14) -= 60;
                    FIELD(target_sprite, u8, 13) -= 60;
                    FIELD(target_sprite, u8, 12) -= 60;
                }
            }
        }
        if (FIELD(effect, s16, 0x82) >= 100) {
            void *finished_target;
            u32 clear_tint_mask;
            clear_tint_mask = 0xEFFFFFFF;
            finished_target = FIELD(owner, void *, 0x60);
            FIELD(finished_target, u32, 28) &= clear_tint_mask;
            target_sprite = FIELD(finished_target, void *, -20);
            FIELD(target_sprite, u8, 14) = 128;
            FIELD(target_sprite, u8, 13) = 128;
            FIELD(target_sprite, u8, 12) = 128;
            FIELD(effect, u16, 0xA)++;
        }
        goto done;
    }

state5:
    {
        void *target;
        u8 target_mode;
        u32 clear_effect_mask;
        s32 effect_kind;
        if (FIELD(effect, s16, 0x90) != 0) {
            clear_effect_mask = 0xFFEFFFFF;
            effect_kind = 255;
            target = FIELD(owner, void *, 0x60);
            target_mode = D_800E3D68[0];
            FIELD(target, u32, 20) &= clear_effect_mask;
            if (target_mode != effect_kind) {
                effect_kind = FIELD(effect, u8, 9);
            }
            func_800240AC(FIELD(owner, void *, 0x60), effect_kind, owner);
            FIELD(effect, u16, 0xA) = 8;
            FIELD(effect, u16, 0x82) = 30;
        }
        goto done;
    }

state8:
    {
        s16 old_frame;
        s16 frame;
        s32 cleanup_pending;
        old_frame = FIELD(effect, u16, 0x82);
        frame = old_frame + 1;
        FIELD(effect, u16, 0x82) = frame;
        if ((s16)frame < 31) {
            goto done;
        }
        cleanup_pending = D_80025630[0];
        FIELD(effect, u16, 0x82) = old_frame;
        switch (cleanup_pending) {
        case 0: {
            D_8008346C = 0;
            FIELD(effect, u16, -2) |= 0x8000;
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
