#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[8];
} Copy8;

typedef struct {
    u8 bytes[12];
} Copy12;

typedef struct {
    u8 bytes[32];
} Copy32;

typedef struct {
    s16 a;
    s16 b;
    s16 c;
} Vec3;

__asm__(".set D_80024004, 0x80024004");
__asm__(".set D_80024014, 0x80024014");
__asm__(".set D_800251A0, 0x800251A0");
__asm__(".set D_80025294, 0x80025294");
__asm__(".set D_800252E4, 0x800252E4");
__asm__(".set D_80025408, 0x80025408");
__asm__(".set D_80026760, 0x80026760");
__asm__(".set D_8002676C, 0x8002676C");
__asm__(".set D_80026778, 0x80026778");
__asm__(".set D_80026784, 0x80026784");
__asm__(".set D_800267A8, 0x800267A8");
__asm__(".set D_800267B8, 0x800267B8");
__asm__(".set D_800DDC40, 0x800DDC40");
__asm__(".set D_800E3D68, 0x800E3D68");
__asm__(".set D_8006CCD8, 0x8006CCD8");
__asm__(".set D_8006CCE8, 0x8006CCE8");

extern u8 D_80024004[9];
extern u8 D_80024014[32];
extern u8 D_800251A0[12];
extern u8 D_80025294[12];
extern u8 D_800252E4[12];
extern u8 D_80025408[12];
extern u8 D_80026760[12];
extern u8 D_8002676C[12];
extern u8 D_80026778[12];
extern u8 D_80026784[24];
extern u8 D_800267A8[12];
extern u8 D_800267B8[9];
extern u8 D_800DDC40[];
extern u8 D_800E3D68[1];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_8008346C;
extern s32 D_800814A0;
extern u8 D_80045340[];

extern s32 func_8003DF74(void *, void *, Vec3 *, s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_80025080(void *, s32, s32, s32, s32, s32, s32);
extern s32 func_800A4778(u16, u16, s16, void *);
extern void func_800A56E0(s32);
extern void *func_8003FC64(s32);
extern void func_800B8FC8(void *, void *, void *, s32, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8002405C(void *, s32, void *);

extern void func_80025A14(void) __attribute__((noreturn));
extern void func_80025B70(void) __attribute__((noreturn));
extern void func_80025D08(void) __attribute__((noreturn));
extern void func_80025EC4(void) __attribute__((noreturn));
extern void func_8002652C(void) __attribute__((noreturn));
extern void func_80026730(void) __attribute__((noreturn));

/* Updates a traveling effect, its target animation, and its cleanup state. */
void func_81905FD0(void *effect_data, void *motion_data, void *render_data)
{
    void *effect = effect_data;
    register void *motion ASM_REG("$18") = motion_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *render = render_data;
    void *target_render;
    u8 scratch[56];
    s32 index;
    s32 result;
    s32 random_bits;
    s32 state;
    u8 kind_or_shade;
    register u8 *tex_rect ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *rect_template = D_80024004;

    void *owner;
    void *owner_object;
    void *owner_motion;
    ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    owner = FIELD(effect, void *, 0);
    *(Copy8 *)(scratch + 8) = *(Copy8 *)rect_template;
    *(Copy32 *)(scratch + 24) = *(Copy32 *)D_80024014;
    state = *(s16 *)((u8 *)effect + 0xA);
    owner_object = (u8 *)owner - 0x20;
    owner_motion = FIELD(owner_object, void *, 8);

    switch (state) {
    case 0:
        FIELD(render, u32, 0xC) = 0x00808080;
        *(Copy12 *)((u8 *)effect + 0xA2) = *(Copy12 *)D_800267A8;
        FIELD(render, void *, 8) = (u8 *)effect + 0xA2;
        {
            u16 direction = (FIELD(owner, u16, 0x2A) >> 9) & 7;
            FIELD(D_800267B8, u16, 0) = 1;
            FIELD(effect, u16, 0x7E) = direction;
        }
        FIELD(effect, u16, 0xA)++;

    case 1:
        result = func_8003DF74(FIELD(FIELD(owner_object, void *, 0xC), void *, 8),
                               FIELD(owner_object, void *, 0xC),
                               (Vec3 *)scratch, 0);
        if (result == 0) {
            if ((FIELD(FIELD(owner_object, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
                goto done;
            }
        }
        {
            u16 owner_height;

            FIELD(motion, u16, 2) = FIELD(owner_motion, u16, 2);
            FIELD(motion, u16, 6) = FIELD(owner_motion, u16, 6);
            owner_height = FIELD(owner_motion, u16, 0xA);
            FIELD(motion, u16, 0xA) = owner_height;
            if ((FIELD(FIELD(owner_object, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
                u16 next_height;

                FIELD(motion, u16, 2) += FIELD(scratch, u16, 0);
                FIELD(motion, u16, 6) += FIELD(scratch, u16, 2);
                next_height = FIELD(motion, u16, 0xA) + FIELD(scratch, u16, 4);
                ASM_TAILSLOT_PIN(next_height);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80025A14();
            } else {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                FIELD(motion, u16, 0xA) = owner_height - 0x40;
            }
        }
        if ((FIELD(FIELD(effect, void *, 4), u16, 0) & 0x80) == 0) {
            goto done;
        }
        if ((FIELD(effect, u8, 0x7A) & 4) == 0) {
            func_8004491C((u8 *)effect - 0x20, D_80045340);
            FIELD(render, u16, 0x10) = 32;
            FIELD(render, u8, 0xE) = 128;
            FIELD(render, u8, 0xD) = 128;
            FIELD(render, u8, 0xC) = 128;
            FIELD(render, u16, 0x1E) = 2000;
            FIELD(render, u16, 0x1C) = 2000;
            FIELD(render, u16, 0x14) |= 0xC;
            FIELD(effect, u8, 0x7A) |= 4;
        }
        {
            void *target = FIELD(owner, void *, 0x60);
            if (target != 0) {
                register void *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                void *owner_info;
                register s32 tile_distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                s32 target_height;

                target_motion = FIELD(target, void *, -0x18);
                kind_or_shade = FIELD(target, u8, 0x13);
                target_height = D_800DDC40[kind_or_shade] + 64;
                FIELD(effect, u16, 0x78) = FIELD(target_motion, u16, 0xA) - target_height;
                owner_info = FIELD(owner, void *, -0x14);
                FIELD(effect, u8, 0xBA) = FIELD(owner_info, u8, 0x24) +
                    D_8006CCD8[FIELD(effect, s16, 0x7E) * 2];
                FIELD(effect, u8, 0xBB) = FIELD(owner_info, u8, 0x25) +
                    D_8006CCE8[FIELD(effect, s16, 0x7E) * 2];
                {
                    s32 owner_tile;
                    s32 target_tile;

                    owner_tile = FIELD(owner, s8, 0x72);
                    target_tile = FIELD(owner_info, u8, 0x24);
                    if (owner_tile == target_tile) {
                        owner_tile = FIELD(owner, s8, 0x73);
                        target_tile = FIELD(owner_info, u8, 0x25);
                        tile_distance = owner_tile - target_tile;
                    } else {
                        tile_distance = owner_tile - target_tile;
                    }
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                FIELD(effect, u8, 0x7B) = tile_distance * 2 - 1;
                func_80025B70();
            } else {
                u16 owner_height = FIELD(owner, u16, 0x88);

                FIELD(effect, u8, 0x7B) = 32;
                FIELD(effect, u16, 0x78) = owner_height - 80;
            }
        }
        {
            u8 *direction_steps = scratch + 24;
            u8 *x_step;
            u8 *y_step;

            x_step = direction_steps + FIELD(effect, s16, 0x7E) * 4;
            FIELD(motion, u32, 0xC) = (s32)FIELD(x_step, s16, 0) << 16;
            y_step = direction_steps + FIELD(effect, s16, 0x7E) * 4;
            FIELD(motion, u32, 0x10) = (s32)FIELD(y_step, u16, 2) << 16;
        }
        FIELD(motion, s32, 0x14) =
            (((s32)FIELD(effect, s16, 0x78) << 16) - FIELD(motion, s32, 8)) /
            (s8)FIELD(effect, u8, 0x7B);
        FIELD(effect, u16, 0x82) = 0;
        FIELD(effect, u16, 0x90) = 0;
        FIELD(effect, u16, 0x92) = 0;
        FIELD(effect, u16, 0x94) = 5;
        FIELD(effect, u16, 0x96) = 200;
        FIELD(effect, u16, 0xA)++;
        FIELD(effect, u16, 0x88) = (s8)FIELD(effect, u8, 0x7B);
        FIELD(effect, u16, 0x8A) =
            (s8)FIELD(effect, u8, 0x7B) * (s8)FIELD(effect, u8, 0x7B);
        func_80026730();

    case 2:
        index = 0;
        do {
            register void *effect_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 particle_color ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            register s32 particle_shade ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            index++;
            random_bits = func_80069EF8();
            effect_object = (u8 *)effect - 0x20;
            particle_color = 0xE02020;
            ASM_KEEP_NV(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            particle_shade = (random_bits & 0xFF) | 0x80;
            ASM_KEEP_NV(particle_shade);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            func_80025080(effect_object, FIELD(effect, s16, 0x7E), particle_color, particle_shade, 0, 0, 0);
        } while (index < 4);
        result = func_800A4778(FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                               FIELD(motion, s16, 0xA), FIELD(owner, void *, 0x60));
        if ((s16)result != 0) {
            goto reset_state8;
        }
        {
            u16 previous_angle = FIELD(render, u16, 0x1A);
            u16 angle = previous_angle + 0x190;
            FIELD(render, u16, 0x1A) = angle;
            if (angle >= 0x1001) {
                FIELD(render, u16, 0x1A) = previous_angle - 0xE70;
            }
        }
        if (FIELD(effect, s16, 0x90) == 0) {
            u16 next_scale;

            FIELD(render, u16, 0x1C) += FIELD(effect, u16, 0x96);
            next_scale = FIELD(render, u16, 0x1E) + FIELD(effect, u16, 0x96);
            ASM_TAILSLOT_PIN(next_scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025D08();
        } else {
            FIELD(render, u16, 0x1C) -= FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) -= FIELD(effect, u16, 0x96);
        }
        {
            u16 timer = FIELD(effect, u16, 0x92) + 1;
            FIELD(effect, u16, 0x92) = timer;
            if ((s16)timer >= FIELD(effect, s16, 0x94)) {
                FIELD(effect, u16, 0x92) = 0;
                FIELD(effect, u16, 0x90) = FIELD(effect, u16, 0x90) ^ 1;
            }
        }
        FIELD(effect, u8, 0x7B) = FIELD(effect, u8, 0x7B) - 1;
        if ((s8)FIELD(effect, u8, 0x7B) > 0) {
            goto update_coords;
        }
        if (FIELD(owner, void *, 0x60) == 0) {
            goto reset_state8;
        }
        FIELD(effect, u16, 0xA) = 3;
        FIELD(effect, u16, 0x82) = 0;
        func_800A56E0(0x300);
        {
            void *target = FIELD(owner, void *, 0x60);
            kind_or_shade = FIELD(target, u8, 0x13);
            target_render = FIELD(target, void *, -0x14);
            if ((u32)(kind_or_shade - 0x33) >= 4) {
                FIELD(target_render, u16, 0x14) |= 0x800;
                FIELD(FIELD(owner, void *, 0x60), u32, 0x14) |= 0x100000;
            }
        }
        {
            register void *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            target_motion = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
            FIELD(motion, u16, 2) = FIELD(target_motion, u16, 2);
            FIELD(motion, u16, 6) = FIELD(target_motion, u16, 6);
        }
        FIELD(motion, u16, 0xA) = FIELD(effect, u16, 0x78);
        func_80026730();

    reset_state8:
        FIELD(effect, u16, 0xA) = 8;
        FIELD(effect, u16, 0x82) = 0;
        FIELD(render, u8, 0xE) = 0;
        FIELD(render, u8, 0xD) = 0;
        FIELD(render, u8, 0xC) = 0;
        func_80026730();

    update_coords:
        FIELD(motion, u32, 0) += FIELD(motion, u32, 0xC);
        FIELD(motion, u32, 4) += FIELD(motion, u32, 0x10);
        FIELD(motion, u32, 8) += FIELD(motion, u32, 0x14);
        func_80026730();

    case 3: {
        {
            u16 previous_angle = FIELD(render, u16, 0x1A);
            u16 angle = previous_angle + 0x190;
            FIELD(render, u16, 0x1A) = angle;
            if (angle >= 0x1001) {
                FIELD(render, u16, 0x1A) = previous_angle - 0xE70;
            }
        }
        if (FIELD(effect, s16, 0x90) == 0) {
            u16 next_scale;

            FIELD(render, u16, 0x1C) += FIELD(effect, u16, 0x96);
            next_scale = FIELD(render, u16, 0x1E) + FIELD(effect, u16, 0x96);
            ASM_TAILSLOT_PIN(next_scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025EC4();
        } else {
            FIELD(render, u16, 0x1C) -= FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) -= FIELD(effect, u16, 0x96);
        }
        {
            u16 timer = FIELD(effect, u16, 0x92) + 1;
            FIELD(effect, u16, 0x92) = timer;
            if ((s16)timer >= FIELD(effect, s16, 0x94)) {
                FIELD(effect, u16, 0x92) = 0;
                FIELD(effect, u16, 0x90) = FIELD(effect, u16, 0x90) ^ 1;
            }
        }
        {
            s16 frame;
            register u8 *tex_dest ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

            FIELD(effect, u16, 0x82) = FIELD(effect, u16, 0x82) + 1;
            frame = (s16)FIELD(effect, u16, 0x82);
            if (frame == 1) {
                s32 rect_value;
                register void *rect_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                register void *dest_arg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                s32 dest_x;
                s32 rect_height;
                s32 rect_x;

                tex_rect = scratch + 8;
                rect_arg = tex_rect;
                tex_dest = scratch + 16;
                dest_arg = tex_dest;
                ASM_SET(rect_x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                rect_x = 832;
                rect_value = 340;
                FIELD(scratch, s16, 10) = rect_value;
                rect_value = 96;
                ASM_SET(rect_height);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                rect_height = 84;
                ASM_SET(dest_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                dest_x = 880;
                FIELD(scratch, s16, 12) = rect_value;
                rect_value = 410;
                FIELD(scratch, s16, 8) = rect_x;
                FIELD(scratch, s16, 14) = rect_height;
                FIELD(scratch, s16, 16) = dest_x;
                FIELD(scratch, s16, 18) = rect_value;
                func_800B8FC8(FIELD(owner, void *, 0x60), rect_arg,
                              dest_arg, 1, frame);
                rect_arg = tex_rect;
                ASM_KEEP_NV(rect_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                dest_arg = tex_dest;
                ASM_KEEP_NV(dest_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                rect_value = 424;
                FIELD(scratch, s16, 10) = rect_value;
                rect_value = 96;
                FIELD(scratch, s16, 12) = rect_value;
                rect_value = 495;
                FIELD(scratch, s16, 8) = rect_x;
                FIELD(scratch, s16, 14) = rect_height;
                FIELD(scratch, s16, 16) = dest_x;
                FIELD(scratch, s16, 18) = rect_value;
                func_800B8FC8(FIELD(owner, void *, 0x60), rect_arg,
                              dest_arg, 1, frame);
            }
            if (FIELD(effect, s16, 0x82) != 4) {
                goto done;
            }
        }
        {
            register void *upper_effect ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            void *lower_effect;
            void *ring_effect;
            register void *control_effect ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            void *child_data;
            register void *child_render ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            void *child_motion;

            upper_effect = func_8003FC64(0x212);
            if (upper_effect != 0) {
                child_data = (u8 *)upper_effect + 0x20;
                FIELD(child_data, s16, 2) = 120;
                FIELD(upper_effect, void *, 0x10) = D_80025294;
                func_8004491C(upper_effect, D_80045340);
                child_render = FIELD(upper_effect, void *, 0xC);
                FIELD(child_render, u16, 6) = 0;
                {
                    register u16 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register u16 saved_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    render_flags = FIELD(child_render, u16, 0x14) | 0xC;
                    FIELD(child_render, u16, 0x14) = render_flags;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    saved_flags = render_flags;
                    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    FIELD(child_render, u16, 0x10) = 64;
                    FIELD(child_render, u16, 0x14) = saved_flags | 0x80;
                }
                child_motion = FIELD(upper_effect, void *, 8);
                FIELD(child_data, u16, 0xA) = 0;
                FIELD(child_data, u16, 0xC) = 0;
                {
                    register void *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(child_motion, u32, 0) = FIELD(target_motion, u32, 0);
                    FIELD(child_motion, u32, 4) = FIELD(target_motion, u32, 4);
                    FIELD(child_motion, u32, 8) = FIELD(target_motion, u32, 8);
                }
                child_render = FIELD(upper_effect, void *, 0xC);
                FIELD(child_render, s16, 0x1C) = 4100;
                FIELD(child_render, s16, 0x1E) = 4100;
                {
                    u8 target_height = D_800DDC40[FIELD(FIELD(owner, void *, 0x60), u8, 0x13)];

                    FIELD(child_render, u8, 0xE) = 128;
                    FIELD(child_render, u8, 0xD) = 128;
                    FIELD(child_render, u8, 0xC) = 128;
                    FIELD(child_render, s16, 0x22) = (-target_height) / 2;
                }
                *(Copy12 *)((u8 *)upper_effect + 0x40) = *(Copy12 *)D_8002676C;
                FIELD(child_render, void *, 8) = (u8 *)upper_effect + 0x40;
                FIELD(FIELD(child_render, void *, 8), u16, 4) =
                    func_80066460(2, 1, 832, 340);
            }
            lower_effect = func_8003FC64(0x212);
            if (lower_effect != 0) {
                child_data = (u8 *)lower_effect + 0x20;
                FIELD(child_data, s16, 2) = 140;
                FIELD(lower_effect, void *, 0x10) = D_800252E4;
                func_8004491C(lower_effect, D_80045340);
                child_render = FIELD(lower_effect, void *, 0xC);
                FIELD(child_render, u16, 0x14) &= 0xFFF3;
                FIELD(child_render, s16, 0x10) = 32;
                FIELD(child_render, u16, 0x14) |= 0x80;
                FIELD(child_data, void *, 0x38) = owner;
                FIELD(child_data, void *, 0x3C) = FIELD(owner, void *, 0x60);
                FIELD(child_data, void *, 0x40) = effect;
                FIELD(child_render, u16, 6) = 0;
                child_motion = FIELD(lower_effect, void *, 8);
                FIELD(child_data, u16, 0xA) = 0;
                FIELD(child_data, u16, 0xC) = 0;
                {
                    register void *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(child_motion, u32, 0) = FIELD(target_motion, u32, 0);
                    FIELD(child_motion, u32, 4) = FIELD(target_motion, u32, 4);
                    FIELD(child_motion, u32, 8) = FIELD(target_motion, u32, 8);
                }
                child_render = FIELD(lower_effect, void *, 0xC);
                FIELD(child_render, s16, 0x1E) = 4096;
                FIELD(child_render, s16, 0x1C) = 4096;
                FIELD(child_render, u8, 0xE) = 128;
                FIELD(child_render, u8, 0xD) = 128;
                FIELD(child_render, u8, 0xC) = 128;
                *(Copy12 *)((u8 *)lower_effect + 0x40) = *(Copy12 *)D_80026778;
                FIELD(child_render, void *, 8) = (u8 *)lower_effect + 0x40;
                FIELD(FIELD(child_render, void *, 8), u16, 4) =
                    func_80066460(2, 1, 832, 424);
            }
            ring_effect = func_8003FC64(0x212);
            if (ring_effect != 0) {
                child_data = (u8 *)ring_effect + 0x20;
                FIELD(child_data, s16, 2) = 120;
                FIELD(ring_effect, void *, 0x10) = D_800251A0;
                func_8004491C(ring_effect, D_80045340);
                child_render = FIELD(ring_effect, void *, 0xC);
                FIELD(child_render, u16, 6) = 0;
                {
                    register u16 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register u16 saved_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    render_flags = FIELD(child_render, u16, 0x14) & 0xFFF3;
                    FIELD(child_render, u16, 0x14) = render_flags;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    saved_flags = render_flags;
                    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    FIELD(child_render, s16, 0x10) = 32;
                    FIELD(child_render, u16, 0x14) = saved_flags | 0x80;
                }
                child_motion = FIELD(ring_effect, void *, 8);
                FIELD(child_data, u16, 0xA) = 0;
                FIELD(child_data, u16, 0xC) = 0;
                index = 0;
                {
                    register void *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(child_motion, u32, 0) = FIELD(target_motion, u32, 0);
                    FIELD(child_motion, u32, 4) = FIELD(target_motion, u32, 4);
                    FIELD(child_motion, u32, 8) = FIELD(target_motion, u32, 8);
                }
                child_render = FIELD(ring_effect, void *, 0xC);
                FIELD(child_render, s16, 0x1C) = 4096;
                FIELD(child_render, s16, 0x1E) = 4096;
                FIELD(child_render, u8, 0xE) = 128;
                FIELD(child_render, u8, 0xD) = 128;
                FIELD(child_render, u8, 0xC) = 128;
                {
                    u8 *descriptor_src = D_80026784;
                    u8 *descriptor_dest = child_data;

                    do {
                        *(Copy12 *)(descriptor_dest + 0x20) = *(Copy12 *)descriptor_src;
                        descriptor_src += 12;
                        descriptor_dest += 12;
                        index++;
                    } while (index < 2);
                }
                {
                    s16 *angle_slot;

                    index = 1;
                    angle_slot = (s16 *)((u8 *)child_data + 2);
                    do {
                        angle_slot[40] = index << 9;
                        index++;
                        angle_slot++;
                    } while (index < 9);
                }
                FIELD(child_render, void *, 8) = (u8 *)child_data + 0x20;
            }
            control_effect = func_8003FC64(0x212);
            if (control_effect != 0) {
                register void *effect_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *render_template;
                void *control_script;
                void *owner_target;

                child_data = (u8 *)control_effect + 0x20;
                effect_object = control_effect;
                render_template = D_80045340;
                ASM_KEEP_NV(render_template);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                FIELD(child_data, void *, 0x38) = owner;
                owner_target = FIELD(owner, void *, 0x60);
                FIELD(child_data, void *, 0x44) = (u8 *)upper_effect + 0x20;
                FIELD(child_data, void *, 0x48) = (u8 *)ring_effect + 0x20;
                FIELD(child_data, void *, 0x4C) = (u8 *)lower_effect + 0x20;
                ASM_KEEP(upper_effect);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                control_script = D_80025408;
                FIELD(child_data, void *, 0x40) = effect;
                FIELD(child_data, void *, 0x3C) = owner_target;
                FIELD(control_effect, void *, 0x10) = control_script;
                func_8004491C(effect_object, render_template);
                child_render = FIELD(control_effect, void *, 0xC);
                FIELD(child_render, u16, 6) = 0;
                {
                    register u16 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register u16 saved_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    render_flags = FIELD(child_render, u16, 0x14) | 0xC;
                    FIELD(child_render, u16, 0x14) = render_flags;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    saved_flags = render_flags;
                    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    FIELD(child_render, s16, 0x10) = 32;
                    FIELD(child_render, u16, 0x14) = saved_flags | 0x80;
                }
                child_motion = FIELD(control_effect, void *, 8);
                FIELD(child_data, u16, 0xA) = 0;
                FIELD(child_data, u16, 0xC) = 0;
                {
                    register void *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(child_motion, u32, 0) = FIELD(target_motion, u32, 0);
                    FIELD(child_motion, u32, 4) = FIELD(target_motion, u32, 4);
                    FIELD(child_motion, u32, 8) = FIELD(target_motion, u32, 8);
                }
                child_render = FIELD(control_effect, void *, 0xC);
                FIELD(child_render, s16, 0x1E) = 4096;
                FIELD(child_render, s16, 0x1C) = 4096;
                FIELD(child_render, u8, 0xE) = 128;
                FIELD(child_render, u8, 0xD) = 128;
                FIELD(child_render, u8, 0xC) = 128;
                *(Copy12 *)((u8 *)control_effect + 0x40) = *(Copy12 *)D_80026760;
                FIELD(child_render, void *, 8) = (u8 *)control_effect + 0x40;
                ASM_KEEP(control_effect);
            }
            if (FIELD(effect, s16, 0x82) == 4) {
                FIELD(effect, u16, 0xA) = 4;
                FIELD(effect, u16, 0x82) = 0;
                FIELD(effect, u16, 0x9C) = 0;
                func_80026730();
            }
        }
        goto done;
    }

    case 4:
        FIELD(effect, u16, 0x82)++;
        index = 4;
        do {
            index--;
        } while (index >= 0);
        index++;
        {
            u16 previous_angle = FIELD(render, u16, 0x1A);
            u16 angle = previous_angle + 0x190;
            FIELD(render, u16, 0x1A) = angle;
            if (angle >= 0x1001) {
                FIELD(render, u16, 0x1A) = previous_angle - 0xE70;
            }
        }
        if (FIELD(effect, s16, 0x90) == 0) {
            u16 next_scale;

            FIELD(render, u16, 0x1C) += FIELD(effect, u16, 0x96);
            next_scale = FIELD(render, u16, 0x1E) + FIELD(effect, u16, 0x96);
            ASM_TAILSLOT_PIN(next_scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8002652C();
        } else {
            FIELD(render, u16, 0x1C) -= FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) -= FIELD(effect, u16, 0x96);
        }
        {
            u16 timer = FIELD(effect, u16, 0x92) + 1;
            FIELD(effect, u16, 0x92) = timer;
            if ((s16)timer >= FIELD(effect, s16, 0x94)) {
                FIELD(effect, u16, 0x92) = 0;
                FIELD(effect, u16, 0x90) = FIELD(effect, u16, 0x90) ^ 1;
            }
        }
        if ((u32)(FIELD(effect, u16, 0x82) - 11) < 20) {
            kind_or_shade = FIELD(render, u8, 0xE) - 3;
            FIELD(render, u8, 0xE) = kind_or_shade;
            FIELD(render, u8, 0xD) = kind_or_shade;
            FIELD(render, u8, 0xC) = kind_or_shade;
        }
        if (FIELD(effect, s16, 0x82) >= 100 && FIELD(render, u8, 0xC) >= 6) {
            kind_or_shade = FIELD(render, u8, 0xE) - 4;
            FIELD(render, u8, 0xE) = kind_or_shade;
            FIELD(render, u8, 0xD) = kind_or_shade;
            FIELD(render, u8, 0xC) = kind_or_shade;
        }
        if (FIELD(effect, s16, 0x82) >= 120) {
            goto advance_state;
        }
        func_80026730();

    case 5:
        if (FIELD(effect, s16, 0x9C) == 0) {
            goto done;
        }
        result = 0xFF;
        if (FIELD(D_800E3D68, u8, 0) != result) {
            result = FIELD(effect, u8, 9);
        }
        func_8002405C(FIELD(owner, void *, 0x60), result, owner);

    advance_state:
        FIELD(effect, u16, 0x82) = 0;
        FIELD(effect, u16, 0xA) = FIELD(effect, u16, 0xA) + 1;
        func_80026730();

    case 6:
        FIELD(effect, u16, 0x82) = FIELD(effect, u16, 0x82) + 1;
        if (FIELD(effect, s16, 0x82) < 11) {
            goto done;
        }
        target_render = FIELD(FIELD(owner, void *, 0x60), void *, -0x14);
        FIELD(target_render, u16, 0x14) &= 0xF7FF;
        FIELD(FIELD(owner, void *, 0x60), u32, 0x14) &= 0xFFEFFFFF;
        FIELD(FIELD(owner, void *, 0x60), u32, 0x1C) &= 0xEFFFFFFF;
        FIELD(target_render, u8, 0xE) = 128;
        FIELD(target_render, u8, 0xD) = 128;
        FIELD(target_render, u8, 0xC) = 128;
        FIELD(effect, u16, 0xA) = 8;
        FIELD(effect, u16, 0x82) = 30;
        func_80026730();

    case 8: {
        u16 previous_timer = FIELD(effect, u16, 0x82);
        u16 timer = previous_timer + 1;

        FIELD(effect, u16, 0x82) = timer;
        if ((s16)timer < 31) {
            goto done;
        }
        {
            s32 active_flag = FIELD(D_800267B8, s16, 0);

            FIELD(effect, u16, 0x82) = previous_timer;
            if (active_flag != 0) {
                goto clear_flag;
            }
        }
        D_8008346C = 0;
        FIELD(effect, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_80026730();
    }

    clear_flag:
        FIELD(D_800267B8, u16, 0) = 0;

    case 7:
    default:
    done:
        return;
    }
}
