#include "common.h"

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

typedef struct S_func_81905FD0_1 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16;
        u16 u16;
    } unk_0A;
    u8 pad_0C[0x6C];
    union {
        s16 s16;
        u16 u16;
    } unk_78;
    u8 unk_7A;
    u8 unk_7B;
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
    u16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_90;
    u16 unk_92;
    union {
        s16 s16;
        u16 u16;
    } unk_94;
    u16 unk_96;
    u8 pad_98[0x4];
    union {
        s16 s16;
        u16 u16;
    } unk_9C;
    u8 pad_9E[0x1C];
    u8 unk_BA;
    u8 unk_BB;
} S_func_81905FD0_1;

typedef struct S_func_81905FD0_2 {
    union {
        u32 u32;
        struct {
            u8 pad_00[0x2];
            u16 unk_02;
        } u16_02;
    } unk_00;
    union {
        u32 u32;
        struct {
            u8 pad_04[0x2];
            u16 unk_06;
        } u16_06;
    } unk_04;
    union {
        s32 s32;
        u32 u32;
        struct {
            u8 pad_08[0x2];
            s16 unk_0A;
        } s16_0A;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } u16_0A;
    } unk_08;
    u32 unk_0C;
    u32 unk_10;
    union {
        s32 s32;
        u32 u32;
    } unk_14;
} S_func_81905FD0_2;

typedef struct S_func_81905FD0_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    union {
        u32 u32;
        u8 u8;
        struct {
            u8 pad_0C[0x1];
            u8 unk_0D;
        } u8_0D;
        struct {
            u8 pad_0C[0x2];
            u8 unk_0E;
        } u8_0E;
    } unk_0C;
    union {
        s16 s16;
        u16 u16;
    } unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    union {
        s16 s16;
        u16 u16;
    } unk_1C;
    union {
        s16 s16;
        u16 u16;
    } unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 unk_24;
    u8 unk_25;
} S_func_81905FD0_3;

typedef struct S_func_81905FD0_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_func_81905FD0_4;

typedef struct S_func_81905FD0_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_func_81905FD0_5;

typedef struct S_func_81905FD0_6 {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_func_81905FD0_6;

typedef struct S_func_81905FD0_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2A];
    void * unk_38;
    void * unk_3C;
    void * unk_40;
    void * unk_44;
    void * unk_48;
    void * unk_4C;
} S_func_81905FD0_7;

typedef struct S_func_81905FD0_8 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_func_81905FD0_8;

typedef struct S_func_81905FD0_9 {
    s16 unk_00;
    u16 unk_02;
} S_func_81905FD0_9;

typedef struct S_func_81905FD0_10 {
    union {
        s16 s16;
        u16 u16;
    } unk_00;
} S_func_81905FD0_10;

typedef struct S_func_81905FD0_11 {
    u8 unk_00;
} S_func_81905FD0_11;

typedef struct S_func_81905FD0_12 {
    u16 unk_00;
} S_func_81905FD0_12;

typedef struct S_func_81905FD0_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_func_81905FD0_13;

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
    S_func_81905FD0_1 *effect = effect_data;
    register S_func_81905FD0_2 *motion ASM_REG("$18") = motion_data;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_func_81905FD0_3 *render = render_data;
    S_func_81905FD0_3 *target_render;
    u8 scratch[56];
    s32 index;
    s32 result;
    s32 random_bits;
    s32 state;
    u8 kind_or_shade;
    register u8 *tex_rect ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *rect_template = D_80024004;

    S_func_81905FD0_4 *owner;
    S_func_81905FD0_5 *owner_object;
    S_func_81905FD0_2 *owner_motion;
    ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    owner = effect->unk_00;
    *(Copy8 *)(scratch + 8) = *(Copy8 *)rect_template;
    *(Copy32 *)(scratch + 24) = *(Copy32 *)D_80024014;
    state = effect->unk_0A.s16;
    owner_object = (S_func_81905FD0_5 *)((u8 *)owner - 0x20);
    owner_motion = owner_object->unk_08;

    switch (state) {
    case 0:
        render->unk_0C.u32 = 0x00808080;
        *(Copy12 *)((u8 *)effect + 0xA2) = *(Copy12 *)D_800267A8;
        render->unk_08 = (u8 *)effect + 0xA2;
        {
            u16 direction = (owner->unk_2A >> 9) & 7;
            ((S_func_81905FD0_10 *)D_800267B8)->unk_00.u16 = 1;
            effect->unk_7E.u16 = direction;
        }
        effect->unk_0A.u16++;

    case 1:
        result = func_8003DF74(((S_func_81905FD0_3 *)owner_object->unk_0C)->unk_08,
                               owner_object->unk_0C,
                               (Vec3 *)scratch, 0);
        if (result == 0) {
            if ((((S_func_81905FD0_3 *)owner_object->unk_0C)->unk_14 & 0x8000) == 0) {
                goto done;
            }
        }
        {
            u16 owner_height;

            motion->unk_00.u16_02.unk_02 = owner_motion->unk_00.u16_02.unk_02;
            motion->unk_04.u16_06.unk_06 = owner_motion->unk_04.u16_06.unk_06;
            owner_height = owner_motion->unk_08.u16_0A.unk_0A;
            motion->unk_08.u16_0A.unk_0A = owner_height;
            if ((((S_func_81905FD0_3 *)owner_object->unk_0C)->unk_14 & 0x8000) == 0) {
                u16 next_height;

                motion->unk_00.u16_02.unk_02 += ((S_func_81905FD0_8 *)scratch)->unk_00;
                motion->unk_04.u16_06.unk_06 += ((S_func_81905FD0_8 *)scratch)->unk_02;
                next_height = motion->unk_08.u16_0A.unk_0A + ((S_func_81905FD0_8 *)scratch)->unk_04;
                ASM_TAILSLOT_PIN(next_height);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                func_80025A14();
            } else {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                motion->unk_08.u16_0A.unk_0A = owner_height - 0x40;
            }
        }
        if ((((S_func_81905FD0_12 *)effect->unk_04)->unk_00 & 0x80) == 0) {
            goto done;
        }
        if ((effect->unk_7A & 4) == 0) {
            func_8004491C((u8 *)effect - 0x20, D_80045340);
            render->unk_10.u16 = 32;
            render->unk_0C.u8_0E.unk_0E = 128;
            render->unk_0C.u8_0D.unk_0D = 128;
            render->unk_0C.u8 = 128;
            render->unk_1E.u16 = 2000;
            render->unk_1C.u16 = 2000;
            render->unk_14 |= 0xC;
            effect->unk_7A |= 4;
        }
        {
            S_func_81905FD0_6 *target = owner->unk_60;
            if (target != 0) {
                register S_func_81905FD0_2 *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                S_func_81905FD0_3 *owner_info;
                register s32 tile_distance ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                s32 target_height;

                target_motion = ((S_func_81905FD0_5 *)((u8 *)target - 0x20))->unk_08;
                kind_or_shade = target->unk_13;
                target_height = D_800DDC40[kind_or_shade] + 64;
                effect->unk_78.u16 = target_motion->unk_08.u16_0A.unk_0A - target_height;
                owner_info = ((S_func_81905FD0_5 *)((u8 *)owner - 0x20))->unk_0C;
                effect->unk_BA = owner_info->unk_24 +
                    D_8006CCD8[effect->unk_7E.s16 * 2];
                effect->unk_BB = owner_info->unk_25 +
                    D_8006CCE8[effect->unk_7E.s16 * 2];
                {
                    s32 owner_tile;
                    s32 target_tile;

                    owner_tile = owner->unk_72;
                    target_tile = owner_info->unk_24;
                    if (owner_tile == target_tile) {
                        owner_tile = owner->unk_73;
                        target_tile = owner_info->unk_25;
                        tile_distance = owner_tile - target_tile;
                    } else {
                        tile_distance = owner_tile - target_tile;
                    }
                }
                if (tile_distance < 0) {
                    tile_distance = -tile_distance;
                }
                effect->unk_7B = tile_distance * 2 - 1;
                func_80025B70();
            } else {
                u16 owner_height = owner->unk_88;

                effect->unk_7B = 32;
                effect->unk_78.u16 = owner_height - 80;
            }
        }
        {
            u8 *direction_steps = scratch + 24;
            u8 *x_step;
            u8 *y_step;

            x_step = direction_steps + effect->unk_7E.s16 * 4;
            motion->unk_0C = (s32)((S_func_81905FD0_9 *)x_step)->unk_00 << 16;
            y_step = direction_steps + effect->unk_7E.s16 * 4;
            motion->unk_10 = (s32)((S_func_81905FD0_9 *)y_step)->unk_02 << 16;
        }
        motion->unk_14.s32 =
            (((s32)effect->unk_78.s16 << 16) - motion->unk_08.s32) /
            (s8)effect->unk_7B;
        effect->unk_82.u16 = 0;
        effect->unk_90.u16 = 0;
        effect->unk_92 = 0;
        effect->unk_94.u16 = 5;
        effect->unk_96 = 200;
        effect->unk_0A.u16++;
        effect->unk_88 = (s8)effect->unk_7B;
        effect->unk_8A =
            (s8)effect->unk_7B * (s8)effect->unk_7B;
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
            func_80025080(effect_object, effect->unk_7E.s16, particle_color, particle_shade, 0, 0, 0);
        } while (index < 4);
        result = func_800A4778(motion->unk_00.u16_02.unk_02, motion->unk_04.u16_06.unk_06,
                               motion->unk_08.s16_0A.unk_0A, owner->unk_60);
        if ((s16)result != 0) {
            goto reset_state8;
        }
        {
            u16 previous_angle = render->unk_1A;
            u16 angle = previous_angle + 0x190;
            render->unk_1A = angle;
            if (angle >= 0x1001) {
                render->unk_1A = previous_angle - 0xE70;
            }
        }
        if (effect->unk_90.s16 == 0) {
            u16 next_scale;

            render->unk_1C.u16 += effect->unk_96;
            next_scale = render->unk_1E.u16 + effect->unk_96;
            ASM_TAILSLOT_PIN(next_scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025D08();
        } else {
            render->unk_1C.u16 -= effect->unk_96;
            render->unk_1E.u16 -= effect->unk_96;
        }
        {
            u16 timer = effect->unk_92 + 1;
            effect->unk_92 = timer;
            if ((s16)timer >= effect->unk_94.s16) {
                effect->unk_92 = 0;
                effect->unk_90.u16 = effect->unk_90.u16 ^ 1;
            }
        }
        effect->unk_7B = effect->unk_7B - 1;
        if ((s8)effect->unk_7B > 0) {
            goto update_coords;
        }
        if (owner->unk_60 == 0) {
            goto reset_state8;
        }
        effect->unk_0A.u16 = 3;
        effect->unk_82.u16 = 0;
        func_800A56E0(0x300);
        {
            S_func_81905FD0_6 *target = owner->unk_60;
            kind_or_shade = target->unk_13;
            target_render = ((S_func_81905FD0_5 *)((u8 *)target - 0x20))->unk_0C;
            if ((u32)(kind_or_shade - 0x33) >= 4) {
                target_render->unk_14 |= 0x800;
                ((S_func_81905FD0_6 *)owner->unk_60)->unk_14 |= 0x100000;
            }
        }
        {
            register S_func_81905FD0_2 *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            target_motion = ((S_func_81905FD0_5 *)((u8 *)owner->unk_60 - 0x20))->unk_08;
            motion->unk_00.u16_02.unk_02 = target_motion->unk_00.u16_02.unk_02;
            motion->unk_04.u16_06.unk_06 = target_motion->unk_04.u16_06.unk_06;
        }
        motion->unk_08.u16_0A.unk_0A = effect->unk_78.u16;
        func_80026730();

    reset_state8:
        effect->unk_0A.u16 = 8;
        effect->unk_82.u16 = 0;
        render->unk_0C.u8_0E.unk_0E = 0;
        render->unk_0C.u8_0D.unk_0D = 0;
        render->unk_0C.u8 = 0;
        func_80026730();

    update_coords:
        motion->unk_00.u32 += motion->unk_0C;
        motion->unk_04.u32 += motion->unk_10;
        motion->unk_08.u32 += motion->unk_14.u32;
        func_80026730();

    case 3: {
        {
            u16 previous_angle = render->unk_1A;
            u16 angle = previous_angle + 0x190;
            render->unk_1A = angle;
            if (angle >= 0x1001) {
                render->unk_1A = previous_angle - 0xE70;
            }
        }
        if (effect->unk_90.s16 == 0) {
            u16 next_scale;

            render->unk_1C.u16 += effect->unk_96;
            next_scale = render->unk_1E.u16 + effect->unk_96;
            ASM_TAILSLOT_PIN(next_scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025EC4();
        } else {
            render->unk_1C.u16 -= effect->unk_96;
            render->unk_1E.u16 -= effect->unk_96;
        }
        {
            u16 timer = effect->unk_92 + 1;
            effect->unk_92 = timer;
            if ((s16)timer >= effect->unk_94.s16) {
                effect->unk_92 = 0;
                effect->unk_90.u16 = effect->unk_90.u16 ^ 1;
            }
        }
        {
            s16 frame;
            register u8 *tex_dest ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

            effect->unk_82.u16 = effect->unk_82.u16 + 1;
            frame = (s16)effect->unk_82.u16;
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
                ((S_func_81905FD0_8 *)scratch)->unk_0A = rect_value;
                rect_value = 96;
                ASM_SET(rect_height);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                rect_height = 84;
                ASM_SET(dest_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                dest_x = 880;
                ((S_func_81905FD0_8 *)scratch)->unk_0C = rect_value;
                rect_value = 410;
                ((S_func_81905FD0_8 *)scratch)->unk_08 = rect_x;
                ((S_func_81905FD0_8 *)scratch)->unk_0E = rect_height;
                ((S_func_81905FD0_8 *)scratch)->unk_10 = dest_x;
                ((S_func_81905FD0_8 *)scratch)->unk_12 = rect_value;
                func_800B8FC8(owner->unk_60, rect_arg,
                              dest_arg, 1, frame);
                rect_arg = tex_rect;
                ASM_KEEP_NV(rect_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                dest_arg = tex_dest;
                ASM_KEEP_NV(dest_arg);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                rect_value = 424;
                ((S_func_81905FD0_8 *)scratch)->unk_0A = rect_value;
                rect_value = 96;
                ((S_func_81905FD0_8 *)scratch)->unk_0C = rect_value;
                rect_value = 495;
                ((S_func_81905FD0_8 *)scratch)->unk_08 = rect_x;
                ((S_func_81905FD0_8 *)scratch)->unk_0E = rect_height;
                ((S_func_81905FD0_8 *)scratch)->unk_10 = dest_x;
                ((S_func_81905FD0_8 *)scratch)->unk_12 = rect_value;
                func_800B8FC8(owner->unk_60, rect_arg,
                              dest_arg, 1, frame);
            }
            if (effect->unk_82.s16 != 4) {
                goto done;
            }
        }
        {
            register S_func_81905FD0_5 *upper_effect ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            S_func_81905FD0_5 *lower_effect;
            S_func_81905FD0_5 *ring_effect;
            register S_func_81905FD0_5 *control_effect ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            S_func_81905FD0_7 *child_data;
            register S_func_81905FD0_3 *child_render ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            S_func_81905FD0_2 *child_motion;

            upper_effect = func_8003FC64(0x212);
            if (upper_effect != 0) {
                child_data = (S_func_81905FD0_7 *)((u8 *)upper_effect + 0x20);
                child_data->unk_02 = 120;
                upper_effect->unk_10 = D_80025294;
                func_8004491C(upper_effect, D_80045340);
                child_render = upper_effect->unk_0C;
                child_render->unk_06 = 0;
                {
                    register u16 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register u16 saved_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    render_flags = child_render->unk_14 | 0xC;
                    child_render->unk_14 = render_flags;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    saved_flags = render_flags;
                    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    child_render->unk_10.u16 = 64;
                    child_render->unk_14 = saved_flags | 0x80;
                }
                child_motion = upper_effect->unk_08;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                {
                    register S_func_81905FD0_2 *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = ((S_func_81905FD0_5 *)((u8 *)owner->unk_60 - 0x20))->unk_08;
                    child_motion->unk_00.u32 = target_motion->unk_00.u32;
                    child_motion->unk_04.u32 = target_motion->unk_04.u32;
                    child_motion->unk_08.u32 = target_motion->unk_08.u32;
                }
                child_render = upper_effect->unk_0C;
                child_render->unk_1C.s16 = 4100;
                child_render->unk_1E.s16 = 4100;
                {
                    u8 target_height = D_800DDC40[((S_func_81905FD0_6 *)owner->unk_60)->unk_13];

                    child_render->unk_0C.u8_0E.unk_0E = 128;
                    child_render->unk_0C.u8_0D.unk_0D = 128;
                    child_render->unk_0C.u8 = 128;
                    child_render->unk_22 = (-target_height) / 2;
                }
                *(Copy12 *)((u8 *)upper_effect + 0x40) = *(Copy12 *)D_8002676C;
                child_render->unk_08 = (u8 *)upper_effect + 0x40;
                ((S_func_81905FD0_13 *)child_render->unk_08)->unk_04 =
                    func_80066460(2, 1, 832, 340);
            }
            lower_effect = func_8003FC64(0x212);
            if (lower_effect != 0) {
                child_data = (S_func_81905FD0_7 *)((u8 *)lower_effect + 0x20);
                child_data->unk_02 = 140;
                lower_effect->unk_10 = D_800252E4;
                func_8004491C(lower_effect, D_80045340);
                child_render = lower_effect->unk_0C;
                child_render->unk_14 &= 0xFFF3;
                child_render->unk_10.s16 = 32;
                child_render->unk_14 |= 0x80;
                child_data->unk_38 = owner;
                child_data->unk_3C = owner->unk_60;
                child_data->unk_40 = effect;
                child_render->unk_06 = 0;
                child_motion = lower_effect->unk_08;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                {
                    register S_func_81905FD0_2 *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = ((S_func_81905FD0_5 *)((u8 *)owner->unk_60 - 0x20))->unk_08;
                    child_motion->unk_00.u32 = target_motion->unk_00.u32;
                    child_motion->unk_04.u32 = target_motion->unk_04.u32;
                    child_motion->unk_08.u32 = target_motion->unk_08.u32;
                }
                child_render = lower_effect->unk_0C;
                child_render->unk_1E.s16 = 4096;
                child_render->unk_1C.s16 = 4096;
                child_render->unk_0C.u8_0E.unk_0E = 128;
                child_render->unk_0C.u8_0D.unk_0D = 128;
                child_render->unk_0C.u8 = 128;
                *(Copy12 *)((u8 *)lower_effect + 0x40) = *(Copy12 *)D_80026778;
                child_render->unk_08 = (u8 *)lower_effect + 0x40;
                ((S_func_81905FD0_13 *)child_render->unk_08)->unk_04 =
                    func_80066460(2, 1, 832, 424);
            }
            ring_effect = func_8003FC64(0x212);
            if (ring_effect != 0) {
                child_data = (S_func_81905FD0_7 *)((u8 *)ring_effect + 0x20);
                child_data->unk_02 = 120;
                ring_effect->unk_10 = D_800251A0;
                func_8004491C(ring_effect, D_80045340);
                child_render = ring_effect->unk_0C;
                child_render->unk_06 = 0;
                {
                    register u16 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register u16 saved_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    render_flags = child_render->unk_14 & 0xFFF3;
                    child_render->unk_14 = render_flags;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    saved_flags = render_flags;
                    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    child_render->unk_10.s16 = 32;
                    child_render->unk_14 = saved_flags | 0x80;
                }
                child_motion = ring_effect->unk_08;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                index = 0;
                {
                    register S_func_81905FD0_2 *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = ((S_func_81905FD0_5 *)((u8 *)owner->unk_60 - 0x20))->unk_08;
                    child_motion->unk_00.u32 = target_motion->unk_00.u32;
                    child_motion->unk_04.u32 = target_motion->unk_04.u32;
                    child_motion->unk_08.u32 = target_motion->unk_08.u32;
                }
                child_render = ring_effect->unk_0C;
                child_render->unk_1C.s16 = 4096;
                child_render->unk_1E.s16 = 4096;
                child_render->unk_0C.u8_0E.unk_0E = 128;
                child_render->unk_0C.u8_0D.unk_0D = 128;
                child_render->unk_0C.u8 = 128;
                {
                    u8 *descriptor_src = D_80026784;
                    u8 *descriptor_dest = (u8 *)child_data;

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
                child_render->unk_08 = (u8 *)child_data + 0x20;
            }
            control_effect = func_8003FC64(0x212);
            if (control_effect != 0) {
                register void *effect_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                void *render_template;
                void *control_script;
                void *owner_target;

                child_data = (S_func_81905FD0_7 *)((u8 *)control_effect + 0x20);
                effect_object = control_effect;
                render_template = D_80045340;
                ASM_KEEP_NV(render_template);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                child_data->unk_38 = owner;
                owner_target = owner->unk_60;
                child_data->unk_44 = (u8 *)upper_effect + 0x20;
                child_data->unk_48 = (u8 *)ring_effect + 0x20;
                child_data->unk_4C = (u8 *)lower_effect + 0x20;
                ASM_KEEP(upper_effect);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                control_script = D_80025408;
                child_data->unk_40 = effect;
                child_data->unk_3C = owner_target;
                control_effect->unk_10 = control_script;
                func_8004491C(effect_object, render_template);
                child_render = control_effect->unk_0C;
                child_render->unk_06 = 0;
                {
                    register u16 render_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    register u16 saved_flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                    render_flags = child_render->unk_14 | 0xC;
                    child_render->unk_14 = render_flags;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    saved_flags = render_flags;
                    ASM_KEEP(saved_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    child_render->unk_10.s16 = 32;
                    child_render->unk_14 = saved_flags | 0x80;
                }
                child_motion = control_effect->unk_08;
                child_data->unk_0A = 0;
                child_data->unk_0C = 0;
                {
                    register S_func_81905FD0_2 *target_motion ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                    target_motion = ((S_func_81905FD0_5 *)((u8 *)owner->unk_60 - 0x20))->unk_08;
                    child_motion->unk_00.u32 = target_motion->unk_00.u32;
                    child_motion->unk_04.u32 = target_motion->unk_04.u32;
                    child_motion->unk_08.u32 = target_motion->unk_08.u32;
                }
                child_render = control_effect->unk_0C;
                child_render->unk_1E.s16 = 4096;
                child_render->unk_1C.s16 = 4096;
                child_render->unk_0C.u8_0E.unk_0E = 128;
                child_render->unk_0C.u8_0D.unk_0D = 128;
                child_render->unk_0C.u8 = 128;
                *(Copy12 *)((u8 *)control_effect + 0x40) = *(Copy12 *)D_80026760;
                child_render->unk_08 = (u8 *)control_effect + 0x40;
                ASM_KEEP(control_effect);
            }
            if (effect->unk_82.s16 == 4) {
                effect->unk_0A.u16 = 4;
                effect->unk_82.u16 = 0;
                effect->unk_9C.u16 = 0;
                func_80026730();
            }
        }
        goto done;
    }

    case 4:
        effect->unk_82.u16++;
        index = 4;
        do {
            index--;
        } while (index >= 0);
        index++;
        {
            u16 previous_angle = render->unk_1A;
            u16 angle = previous_angle + 0x190;
            render->unk_1A = angle;
            if (angle >= 0x1001) {
                render->unk_1A = previous_angle - 0xE70;
            }
        }
        if (effect->unk_90.s16 == 0) {
            u16 next_scale;

            render->unk_1C.u16 += effect->unk_96;
            next_scale = render->unk_1E.u16 + effect->unk_96;
            ASM_TAILSLOT_PIN(next_scale);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_8002652C();
        } else {
            render->unk_1C.u16 -= effect->unk_96;
            render->unk_1E.u16 -= effect->unk_96;
        }
        {
            u16 timer = effect->unk_92 + 1;
            effect->unk_92 = timer;
            if ((s16)timer >= effect->unk_94.s16) {
                effect->unk_92 = 0;
                effect->unk_90.u16 = effect->unk_90.u16 ^ 1;
            }
        }
        if ((u32)(effect->unk_82.u16 - 11) < 20) {
            kind_or_shade = render->unk_0C.u8_0E.unk_0E - 3;
            render->unk_0C.u8_0E.unk_0E = kind_or_shade;
            render->unk_0C.u8_0D.unk_0D = kind_or_shade;
            render->unk_0C.u8 = kind_or_shade;
        }
        if (effect->unk_82.s16 >= 100 && render->unk_0C.u8 >= 6) {
            kind_or_shade = render->unk_0C.u8_0E.unk_0E - 4;
            render->unk_0C.u8_0E.unk_0E = kind_or_shade;
            render->unk_0C.u8_0D.unk_0D = kind_or_shade;
            render->unk_0C.u8 = kind_or_shade;
        }
        if (effect->unk_82.s16 >= 120) {
            goto advance_state;
        }
        func_80026730();

    case 5:
        if (effect->unk_9C.s16 == 0) {
            goto done;
        }
        result = 0xFF;
        if (((S_func_81905FD0_11 *)D_800E3D68)->unk_00 != result) {
            result = effect->unk_09;
        }
        func_8002405C(owner->unk_60, result, owner);

    advance_state:
        effect->unk_82.u16 = 0;
        effect->unk_0A.u16 = effect->unk_0A.u16 + 1;
        func_80026730();

    case 6:
        effect->unk_82.u16 = effect->unk_82.u16 + 1;
        if (effect->unk_82.s16 < 11) {
            goto done;
        }
        target_render = ((S_func_81905FD0_5 *)((u8 *)owner->unk_60 - 0x20))->unk_0C;
        target_render->unk_14 &= 0xF7FF;
        ((S_func_81905FD0_6 *)owner->unk_60)->unk_14 &= 0xFFEFFFFF;
        ((S_func_81905FD0_6 *)owner->unk_60)->unk_1C &= 0xEFFFFFFF;
        target_render->unk_0C.u8_0E.unk_0E = 128;
        target_render->unk_0C.u8_0D.unk_0D = 128;
        target_render->unk_0C.u8 = 128;
        effect->unk_0A.u16 = 8;
        effect->unk_82.u16 = 30;
        func_80026730();

    case 8: {
        u16 previous_timer = effect->unk_82.u16;
        u16 timer = previous_timer + 1;

        effect->unk_82.u16 = timer;
        if ((s16)timer < 31) {
            goto done;
        }
        {
            s32 active_flag = ((S_func_81905FD0_10 *)D_800267B8)->unk_00.s16;

            effect->unk_82.u16 = previous_timer;
            if (active_flag != 0) {
                goto clear_flag;
            }
        }
        D_8008346C = 0;
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_80026730();
    }

    clear_flag:
        ((S_func_81905FD0_10 *)D_800267B8)->unk_00.u16 = 0;

    case 7:
    default:
    done:
        return;
    }
}
