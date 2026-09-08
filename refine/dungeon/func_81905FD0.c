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

/* Updates effect movement, animation, spawned objects, and cleanup. */
void func_81905FD0(void *effect_data, void *effect_coords, void *effect_render)
{
    void *effect = effect_data;
    register void *motion ASM_REG("$18") = effect_coords;
    void *render = effect_render;
    void *target_render;
    u8 scratch[56];
    s32 index;
    s32 result;
    s32 random_bits;
    s32 state;
    u8 target_type;
    u8 shade;
    register u8 *rect ASM_REG("$20");
    u8 *rect_template = D_80024004;

    void *owner;
    void *owner_object;
    void *owner_coords;
    ASM_KEEP(effect);
    owner = FIELD(effect, void *, 0);
    *(Copy8 *)(scratch + 8) = *(Copy8 *)rect_template;
    *(Copy32 *)(scratch + 24) = *(Copy32 *)D_80024014;
    state = *(s16 *)((u8 *)effect + 0xA);
    owner_object = (u8 *)owner - 0x20;
    owner_coords = FIELD(owner_object, void *, 8);

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
            u16 height;

            FIELD(motion, u16, 2) = FIELD(owner_coords, u16, 2);
            FIELD(motion, u16, 6) = FIELD(owner_coords, u16, 6);
            height = FIELD(owner_coords, u16, 0xA);
            FIELD(motion, u16, 0xA) = height;
            if ((FIELD(FIELD(owner_object, void *, 0xC), u16, 0x14) & 0x8000) == 0) {
                u16 next_height;

                FIELD(motion, u16, 2) += FIELD(scratch, u16, 0);
                FIELD(motion, u16, 6) += FIELD(scratch, u16, 2);
                next_height = FIELD(motion, u16, 0xA) + FIELD(scratch, u16, 4);
                FIELD(motion, u16, 0xA) = next_height;
            } else {
                FIELD(motion, u16, 0xA) = height - 0x40;
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
                register void *target_coords ASM_REG("$7");
                void *owner_render;
                register s32 tile_distance ASM_REG("$2");

                s32 target_height;

                target_coords = FIELD(target, void *, -0x18);
                target_type = FIELD(target, u8, 0x13);
                target_height = D_800DDC40[target_type] + 64;
                FIELD(effect, u16, 0x78) = FIELD(target_coords, u16, 0xA) - target_height;
                owner_render = FIELD(owner, void *, -0x14);
                FIELD(effect, u8, 0xBA) = FIELD(owner_render, u8, 0x24) +
                    D_8006CCD8[FIELD(effect, s16, 0x7E) * 2];
                FIELD(effect, u8, 0xBB) = FIELD(owner_render, u8, 0x25) +
                    D_8006CCE8[FIELD(effect, s16, 0x7E) * 2];
                {
                    s32 owner_tile;
                    s32 current_tile;

                    owner_tile = FIELD(owner, s8, 0x72);
                    current_tile = FIELD(owner_render, u8, 0x24);
                    if (owner_tile == current_tile) {
                        owner_tile = FIELD(owner, s8, 0x73);
                        current_tile = FIELD(owner_render, u8, 0x25);
                        tile_distance = owner_tile - current_tile;
                    } else {
                        tile_distance = owner_tile - current_tile;
                    }
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                FIELD(effect, u8, 0x7B) = tile_distance * 2 - 1;
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
        goto done;

    case 2:
        index = 0;
        do {
            register void *object_arg ASM_REG("$4");
            register s32 particle_color ASM_REG("$6");
            register s32 particle_shade ASM_REG("$7");

            index++;
            random_bits = func_80069EF8();
            object_arg = (u8 *)effect - 0x20;
            particle_color = 0xE02020;
            ASM_KEEP_NV(particle_color);
            particle_shade = (random_bits & 0xFF) | 0x80;
            ASM_KEEP_NV(particle_shade);
            func_80025080(object_arg, FIELD(effect, s16, 0x7E), particle_color, particle_shade, 0, 0, 0);
        } while (index < 4);
        result = func_800A4778(FIELD(motion, u16, 2), FIELD(motion, u16, 6),
                               FIELD(motion, s16, 0xA), FIELD(owner, void *, 0x60));
        if ((s16)result != 0) {
            goto reset_state8;
        }
        {
            u16 old_angle = FIELD(render, u16, 0x1A);
            u16 angle = old_angle + 0x190;
            FIELD(render, u16, 0x1A) = angle;
            if (angle >= 0x1001) {
                FIELD(render, u16, 0x1A) = old_angle - 0xE70;
            }
        }
        if (FIELD(effect, s16, 0x90) == 0) {
            u16 next_scale;

            FIELD(render, u16, 0x1C) += FIELD(effect, u16, 0x96);
            next_scale = FIELD(render, u16, 0x1E) + FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) = next_scale;
        } else {
            FIELD(render, u16, 0x1C) -= FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) -= FIELD(effect, u16, 0x96);
        }
        {
            u16 scale_tick = FIELD(effect, u16, 0x92) + 1;
            FIELD(effect, u16, 0x92) = scale_tick;
            if ((s16)scale_tick >= FIELD(effect, s16, 0x94)) {
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
            target_type = FIELD(target, u8, 0x13);
            target_render = FIELD(target, void *, -0x14);
            if ((u32)(target_type - 0x33) >= 4) {
                FIELD(target_render, u16, 0x14) |= 0x800;
                FIELD(FIELD(owner, void *, 0x60), u32, 0x14) |= 0x100000;
            }
        }
        {
            register void *target_coords ASM_REG("$7");

            target_coords = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
            FIELD(motion, u16, 2) = FIELD(target_coords, u16, 2);
            FIELD(motion, u16, 6) = FIELD(target_coords, u16, 6);
        }
        FIELD(motion, u16, 0xA) = FIELD(effect, u16, 0x78);
        goto done;

    reset_state8:
        FIELD(effect, u16, 0xA) = 8;
        FIELD(effect, u16, 0x82) = 0;
        FIELD(render, u8, 0xE) = 0;
        FIELD(render, u8, 0xD) = 0;
        FIELD(render, u8, 0xC) = 0;
        goto done;

    update_coords:
        FIELD(motion, u32, 0) += FIELD(motion, u32, 0xC);
        FIELD(motion, u32, 4) += FIELD(motion, u32, 0x10);
        FIELD(motion, u32, 8) += FIELD(motion, u32, 0x14);
        goto done;

    case 3: {
        {
            u16 old_angle = FIELD(render, u16, 0x1A);
            u16 angle = old_angle + 0x190;
            FIELD(render, u16, 0x1A) = angle;
            if (angle >= 0x1001) {
                FIELD(render, u16, 0x1A) = old_angle - 0xE70;
            }
        }
        if (FIELD(effect, s16, 0x90) == 0) {
            u16 next_scale;

            FIELD(render, u16, 0x1C) += FIELD(effect, u16, 0x96);
            next_scale = FIELD(render, u16, 0x1E) + FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) = next_scale;
        } else {
            FIELD(render, u16, 0x1C) -= FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) -= FIELD(effect, u16, 0x96);
        }
        {
            u16 scale_tick = FIELD(effect, u16, 0x92) + 1;
            FIELD(effect, u16, 0x92) = scale_tick;
            if ((s16)scale_tick >= FIELD(effect, s16, 0x94)) {
                FIELD(effect, u16, 0x92) = 0;
                FIELD(effect, u16, 0x90) = FIELD(effect, u16, 0x90) ^ 1;
            }
        }
        {
            s16 phase;
            register u8 *copy_dest ASM_REG("$19");

            FIELD(effect, u16, 0x82) = FIELD(effect, u16, 0x82) + 1;
            phase = (s16)FIELD(effect, u16, 0x82);
            if (phase == 1) {
                s32 rect_value;
                register void *rect_arg ASM_REG("$5");
                register void *dest_arg ASM_REG("$6");
                s32 dest_x;
                s32 rect_height;
                s32 rect_x;

                rect = scratch + 8;
                rect_arg = rect;
                copy_dest = scratch + 16;
                dest_arg = copy_dest;
                ASM_SET(rect_x);
                rect_x = 832;
                rect_value = 340;
                FIELD(scratch, s16, 10) = rect_value;
                rect_value = 96;
                ASM_SET(rect_height);
                rect_height = 84;
                ASM_SET(dest_x);
                dest_x = 880;
                FIELD(scratch, s16, 12) = rect_value;
                rect_value = 410;
                FIELD(scratch, s16, 8) = rect_x;
                FIELD(scratch, s16, 14) = rect_height;
                FIELD(scratch, s16, 16) = dest_x;
                FIELD(scratch, s16, 18) = rect_value;
                func_800B8FC8(FIELD(owner, void *, 0x60), rect_arg,
                              dest_arg, 1, phase);
                rect_arg = rect;
                ASM_KEEP_NV(rect_arg);
                dest_arg = copy_dest;
                ASM_KEEP_NV(dest_arg);
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
                              dest_arg, 1, phase);
            }
            if (FIELD(effect, s16, 0x82) != 4) {
                goto done;
            }
        }
        {
            register void *first_object ASM_REG("$22");
            void *second_object;
            void *third_object;
            register void *controller ASM_REG("$17");
            void *object_data;
            register void *object_render ASM_REG("$16");
            void *object_coords;

            first_object = func_8003FC64(0x212);
            if (first_object != 0) {
                object_data = (u8 *)first_object + 0x20;
                FIELD(object_data, s16, 2) = 120;
                FIELD(first_object, void *, 0x10) = D_80025294;
                func_8004491C(first_object, D_80045340);
                object_render = FIELD(first_object, void *, 0xC);
                FIELD(object_render, u16, 6) = 0;
                {
                    register u16 render_flags ASM_REG("$2");
                    register u16 flags ASM_REG("$3");

                    render_flags = FIELD(object_render, u16, 0x14) | 0xC;
                    FIELD(object_render, u16, 0x14) = render_flags;
                    ASM_SCHED_BARRIER();
                    flags = render_flags;
                    ASM_KEEP(flags);
                    FIELD(object_render, u16, 0x10) = 64;
                    FIELD(object_render, u16, 0x14) = flags | 0x80;
                }
                object_coords = FIELD(first_object, void *, 8);
                FIELD(object_data, u16, 0xA) = 0;
                FIELD(object_data, u16, 0xC) = 0;
                {
                    register void *copy_source ASM_REG("$7");

                    copy_source = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(object_coords, u32, 0) = FIELD(copy_source, u32, 0);
                    FIELD(object_coords, u32, 4) = FIELD(copy_source, u32, 4);
                    FIELD(object_coords, u32, 8) = FIELD(copy_source, u32, 8);
                }
                object_render = FIELD(first_object, void *, 0xC);
                FIELD(object_render, s16, 0x1C) = 4100;
                FIELD(object_render, s16, 0x1E) = 4100;
                {
                    u8 target_height = D_800DDC40[FIELD(FIELD(owner, void *, 0x60), u8, 0x13)];

                    FIELD(object_render, u8, 0xE) = 128;
                    FIELD(object_render, u8, 0xD) = 128;
                    FIELD(object_render, u8, 0xC) = 128;
                    FIELD(object_render, s16, 0x22) = (-target_height) / 2;
                }
                *(Copy12 *)((u8 *)first_object + 0x40) = *(Copy12 *)D_8002676C;
                FIELD(object_render, void *, 8) = (u8 *)first_object + 0x40;
                FIELD(FIELD(object_render, void *, 8), u16, 4) =
                    func_80066460(2, 1, 832, 340);
            }
            second_object = func_8003FC64(0x212);
            if (second_object != 0) {
                object_data = (u8 *)second_object + 0x20;
                FIELD(object_data, s16, 2) = 140;
                FIELD(second_object, void *, 0x10) = D_800252E4;
                func_8004491C(second_object, D_80045340);
                object_render = FIELD(second_object, void *, 0xC);
                FIELD(object_render, u16, 0x14) &= 0xFFF3;
                FIELD(object_render, s16, 0x10) = 32;
                FIELD(object_render, u16, 0x14) |= 0x80;
                FIELD(object_data, void *, 0x38) = owner;
                FIELD(object_data, void *, 0x3C) = FIELD(owner, void *, 0x60);
                FIELD(object_data, void *, 0x40) = effect;
                FIELD(object_render, u16, 6) = 0;
                object_coords = FIELD(second_object, void *, 8);
                FIELD(object_data, u16, 0xA) = 0;
                FIELD(object_data, u16, 0xC) = 0;
                {
                    register void *copy_source ASM_REG("$7");

                    copy_source = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(object_coords, u32, 0) = FIELD(copy_source, u32, 0);
                    FIELD(object_coords, u32, 4) = FIELD(copy_source, u32, 4);
                    FIELD(object_coords, u32, 8) = FIELD(copy_source, u32, 8);
                }
                object_render = FIELD(second_object, void *, 0xC);
                FIELD(object_render, s16, 0x1E) = 4096;
                FIELD(object_render, s16, 0x1C) = 4096;
                FIELD(object_render, u8, 0xE) = 128;
                FIELD(object_render, u8, 0xD) = 128;
                FIELD(object_render, u8, 0xC) = 128;
                *(Copy12 *)((u8 *)second_object + 0x40) = *(Copy12 *)D_80026778;
                FIELD(object_render, void *, 8) = (u8 *)second_object + 0x40;
                FIELD(FIELD(object_render, void *, 8), u16, 4) =
                    func_80066460(2, 1, 832, 424);
            }
            third_object = func_8003FC64(0x212);
            if (third_object != 0) {
                object_data = (u8 *)third_object + 0x20;
                FIELD(object_data, s16, 2) = 120;
                FIELD(third_object, void *, 0x10) = D_800251A0;
                func_8004491C(third_object, D_80045340);
                object_render = FIELD(third_object, void *, 0xC);
                FIELD(object_render, u16, 6) = 0;
                {
                    register u16 render_flags ASM_REG("$2");
                    register u16 flags ASM_REG("$3");

                    render_flags = FIELD(object_render, u16, 0x14) & 0xFFF3;
                    FIELD(object_render, u16, 0x14) = render_flags;
                    ASM_SCHED_BARRIER();
                    flags = render_flags;
                    ASM_KEEP(flags);
                    FIELD(object_render, s16, 0x10) = 32;
                    FIELD(object_render, u16, 0x14) = flags | 0x80;
                }
                object_coords = FIELD(third_object, void *, 8);
                FIELD(object_data, u16, 0xA) = 0;
                FIELD(object_data, u16, 0xC) = 0;
                index = 0;
                {
                    register void *copy_source ASM_REG("$7");

                    copy_source = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(object_coords, u32, 0) = FIELD(copy_source, u32, 0);
                    FIELD(object_coords, u32, 4) = FIELD(copy_source, u32, 4);
                    FIELD(object_coords, u32, 8) = FIELD(copy_source, u32, 8);
                }
                object_render = FIELD(third_object, void *, 0xC);
                FIELD(object_render, s16, 0x1C) = 4096;
                FIELD(object_render, s16, 0x1E) = 4096;
                FIELD(object_render, u8, 0xE) = 128;
                FIELD(object_render, u8, 0xD) = 128;
                FIELD(object_render, u8, 0xC) = 128;
                {
                    u8 *copy_source = D_80026784;
                    u8 *copy_target = object_data;

                    do {
                        *(Copy12 *)(copy_target + 0x20) = *(Copy12 *)copy_source;
                        copy_source += 12;
                        copy_target += 12;
                        index++;
                    } while (index < 2);
                }
                {
                    s16 *angle_slot;

                    index = 1;
                    angle_slot = (s16 *)((u8 *)object_data + 2);
                    do {
                        angle_slot[40] = index << 9;
                        index++;
                        angle_slot++;
                    } while (index < 9);
                }
                FIELD(object_render, void *, 8) = (u8 *)object_data + 0x20;
            }
            controller = func_8003FC64(0x212);
            if (controller != 0) {
                register void *object_arg ASM_REG("$4");
                void *render_setup;
                void *controller_script;
                void *target;

                object_data = (u8 *)controller + 0x20;
                object_arg = controller;
                render_setup = D_80045340;
                ASM_KEEP_NV(render_setup);
                FIELD(object_data, void *, 0x38) = owner;
                target = FIELD(owner, void *, 0x60);
                FIELD(object_data, void *, 0x44) = (u8 *)first_object + 0x20;
                FIELD(object_data, void *, 0x48) = (u8 *)third_object + 0x20;
                FIELD(object_data, void *, 0x4C) = (u8 *)second_object + 0x20;
                ASM_KEEP(first_object);
                controller_script = D_80025408;
                FIELD(object_data, void *, 0x40) = effect;
                FIELD(object_data, void *, 0x3C) = target;
                FIELD(controller, void *, 0x10) = controller_script;
                func_8004491C(object_arg, render_setup);
                object_render = FIELD(controller, void *, 0xC);
                FIELD(object_render, u16, 6) = 0;
                {
                    register u16 render_flags ASM_REG("$2");
                    register u16 flags ASM_REG("$3");

                    render_flags = FIELD(object_render, u16, 0x14) | 0xC;
                    FIELD(object_render, u16, 0x14) = render_flags;
                    ASM_SCHED_BARRIER();
                    flags = render_flags;
                    ASM_KEEP(flags);
                    FIELD(object_render, s16, 0x10) = 32;
                    FIELD(object_render, u16, 0x14) = flags | 0x80;
                }
                object_coords = FIELD(controller, void *, 8);
                FIELD(object_data, u16, 0xA) = 0;
                FIELD(object_data, u16, 0xC) = 0;
                {
                    register void *copy_source ASM_REG("$7");

                    copy_source = FIELD(FIELD(owner, void *, 0x60), void *, -0x18);
                    FIELD(object_coords, u32, 0) = FIELD(copy_source, u32, 0);
                    FIELD(object_coords, u32, 4) = FIELD(copy_source, u32, 4);
                    FIELD(object_coords, u32, 8) = FIELD(copy_source, u32, 8);
                }
                object_render = FIELD(controller, void *, 0xC);
                FIELD(object_render, s16, 0x1E) = 4096;
                FIELD(object_render, s16, 0x1C) = 4096;
                FIELD(object_render, u8, 0xE) = 128;
                FIELD(object_render, u8, 0xD) = 128;
                FIELD(object_render, u8, 0xC) = 128;
                *(Copy12 *)((u8 *)controller + 0x40) = *(Copy12 *)D_80026760;
                FIELD(object_render, void *, 8) = (u8 *)controller + 0x40;
                ASM_KEEP(controller);
            }
            if (FIELD(effect, s16, 0x82) == 4) {
                FIELD(effect, u16, 0xA) = 4;
                FIELD(effect, u16, 0x82) = 0;
                FIELD(effect, u16, 0x9C) = 0;
                goto done;
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
            u16 old_angle = FIELD(render, u16, 0x1A);
            u16 angle = old_angle + 0x190;
            FIELD(render, u16, 0x1A) = angle;
            if (angle >= 0x1001) {
                FIELD(render, u16, 0x1A) = old_angle - 0xE70;
            }
        }
        if (FIELD(effect, s16, 0x90) == 0) {
            u16 next_scale;

            FIELD(render, u16, 0x1C) += FIELD(effect, u16, 0x96);
            next_scale = FIELD(render, u16, 0x1E) + FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) = next_scale;
        } else {
            FIELD(render, u16, 0x1C) -= FIELD(effect, u16, 0x96);
            FIELD(render, u16, 0x1E) -= FIELD(effect, u16, 0x96);
        }
        {
            u16 scale_tick = FIELD(effect, u16, 0x92) + 1;
            FIELD(effect, u16, 0x92) = scale_tick;
            if ((s16)scale_tick >= FIELD(effect, s16, 0x94)) {
                FIELD(effect, u16, 0x92) = 0;
                FIELD(effect, u16, 0x90) = FIELD(effect, u16, 0x90) ^ 1;
            }
        }
        if ((u32)(FIELD(effect, u16, 0x82) - 11) < 20) {
            shade = FIELD(render, u8, 0xE) - 3;
            FIELD(render, u8, 0xE) = shade;
            FIELD(render, u8, 0xD) = shade;
            FIELD(render, u8, 0xC) = shade;
        }
        if (FIELD(effect, s16, 0x82) >= 100 && FIELD(render, u8, 0xC) >= 6) {
            shade = FIELD(render, u8, 0xE) - 4;
            FIELD(render, u8, 0xE) = shade;
            FIELD(render, u8, 0xD) = shade;
            FIELD(render, u8, 0xC) = shade;
        }
        if (FIELD(effect, s16, 0x82) >= 120) {
            goto advance_state;
        }
        goto done;

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
        goto done;

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
        goto done;

    case 8: {
        u16 old_frame = FIELD(effect, u16, 0x82);
        u16 frame = old_frame + 1;

        FIELD(effect, u16, 0x82) = frame;
        if ((s16)frame < 31) {
            goto done;
        }
        {
            s32 pending_flag = FIELD(D_800267B8, s16, 0);

            FIELD(effect, u16, 0x82) = old_frame;
            if (pending_flag != 0) {
                goto clear_flag;
            }
        }
        D_8008346C = 0;
        FIELD(effect, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto done;
    }

    clear_flag:
        FIELD(D_800267B8, u16, 0) = 0;

    case 7:
    default:
    done:
        return;
    }
}
