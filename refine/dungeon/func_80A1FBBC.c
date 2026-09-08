#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801733BC_0 {
    u8 pad_00[0xC];
    union { u32 u32; u8 u8; } unk_0C;   /* accessed as both */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u32 unk_28;
} S_801733BC_0;   /* arg2 in func_801733BC */

typedef struct S_801733BC_1 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { u16 u; s16 s; } unk_A8;   /* accessed as both */
} S_801733BC_1;   /* arg0 in func_801733BC */

typedef struct S_801733BC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_801733BC_2;   /* object in func_801733BC */

typedef struct S_801733BC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801733BC_3;   /* arg1 in func_801733BC */

typedef struct S_801733BC_4 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    u32 unk_A4;
} S_801733BC_4;   /* effectPart in func_801733BC */

typedef struct S_801733BC_5 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x8];
    u32 unk_28;
} S_801733BC_5;   /* objectPart in func_801733BC */

typedef struct S_801733BC_6 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801733BC_6;   /* D_80083460 in func_801733BC */


typedef struct S_801733BC_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u16 unk_18;
} S_801733BC_8;   /* projectilePart in func_801733BC */

typedef struct S_801733BC_9 {
    u8 pad_00[0x10];
    union { void * p; u32 i; } unk_10;   /* accessed as both */
} S_801733BC_9;   /* effectList in func_801733BC */

typedef struct S_801733BC_10 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801733BC_10;   /* ((S_801733BC_2 *)object)->unk_08 in func_801733BC */



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

extern s32 D_80045340;
extern s32 D_800814A0;
extern u8 D_80083460[];
extern u8 D_80083498[];
extern Rect D_80170874;
extern u8 D_801740FC[];
extern u8 D_801741A4[];
extern u8 D_80174228[];

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32, s32);
extern s32 func_80069EF8(void);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);
extern void func_800B8FC8(void *, Rect *, Point *, s32, s32);

/* Updates an entity's particles, projectile, and fade-out sequence before removing it. */
void func_801733BC(void *effect_state, void *position, void *render_part, void *entity)
{
    Rect rect;
    Point center;
    s32 particles_left;
    void *spawned_object;
    void *particle_callback;
    void *particle_state;
    void *particle_render;
    void *projectile_state;
    void *projectile_callback;
    u8 *effect_list;
    s32 random_offset;
    u16 frames_left;
    u16 projectile_y;
    u16 projectile_z;

    rect = D_80170874;

    if (!(((S_801733BC_0 *)render_part)->unk_14 & 0x8000) &&
        ((S_801733BC_1 *)effect_state)->unk_9B == 1) {
        particles_left = 3;
        particle_callback = D_801740FC;
        ((S_801733BC_1 *)effect_state)->unk_A8.u += 0x12;
        do {
            spawned_object = func_8003FD64(0x112, D_80083498);
            if (spawned_object != 0) {
                func_8004491C(spawned_object, &D_80045340);
                ((S_801733BC_2 *)spawned_object)->unk_10 = particle_callback;

                random_offset = func_80069EF8();
                ((S_801733BC_10 *)(((S_801733BC_2 *)spawned_object)->unk_08))->unk_02 =
                    ((S_801733BC_3 *)position)->unk_02 + (random_offset & 0x3F) - 0x20;

                random_offset = func_80069EF8();
                ((S_801733BC_10 *)(((S_801733BC_2 *)spawned_object)->unk_08))->unk_06 =
                    ((S_801733BC_3 *)position)->unk_06 + (random_offset & 0x3F) - 0x20;

                random_offset = func_80069EF8();
                {
                    u32 owner;
                    u16 source_z;
                    register u32 fade_color ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
                    register u16 render_flags ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
                    u16 particle_flags;
                    register u16 particle_size ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
                    register s32 draw_command ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
                    register s32 draw_zero ASM_REG("$6");   /* MATCH pin: retail delay-slot fill depends on it */
                    u32 particle_color;   /* MATCH pin: retail delay-slot fill depends on it */
                    register u16 draw_param ASM_REG("$7");   /* MATCH pin: retail delay-slot fill depends on it */

                    random_offset %= ((S_801733BC_1 *)effect_state)->unk_A8.s + 0x60;
                    fade_color = 0x00040404;
                    particle_color = 0x00500000;
                    source_z = ((S_801733BC_3 *)position)->unk_0A;
                    particle_color |= 0x5050;
                    ((S_801733BC_10 *)(((S_801733BC_2 *)spawned_object)->unk_08))->unk_0A =
                        source_z - random_offset - 0x10;

                    particle_state = (u8 *)spawned_object + 0x20;
                    ((S_801733BC_4 *)particle_state)->unk_A4 = fade_color;
                    ((S_801733BC_4 *)particle_state)->unk_96 = 6;

                    particle_render = ((S_801733BC_2 *)spawned_object)->unk_0C;
                    owner = ((S_801733BC_0 *)render_part)->unk_28;
                    draw_command = 0x2E;
                    ((S_801733BC_5 *)particle_render)->unk_28 = owner;
                    ((S_801733BC_5 *)particle_render)->unk_1E = 0x1000;
                    ((S_801733BC_5 *)particle_render)->unk_1C = 0x1000;
                    render_flags = ((S_801733BC_0 *)render_part)->unk_14;
                    draw_zero = 0;
                    ((S_801733BC_5 *)particle_render)->unk_14 = render_flags;
                    ASM_USE(render_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
                    particle_flags = render_flags;
                    particle_size = 0x20;
                    draw_param = ((S_801733BC_0 *)render_part)->unk_12;
                    particle_flags |= 0xC;
                    ((S_801733BC_5 *)particle_render)->unk_10 = particle_size;
                    ((S_801733BC_5 *)particle_render)->unk_0C = particle_color;
                    ((S_801733BC_5 *)particle_render)->unk_14 = particle_flags;
                    ((S_801733BC_5 *)particle_render)->unk_12 = draw_param;
                    func_80047784(particle_render, draw_command, draw_zero, draw_param);
                }
            }
            particles_left--;
        } while (particles_left >= 0);
    }

    switch (((S_801733BC_1 *)effect_state)->unk_9B) {
    case 0:
        if (((S_801733BC_6 *)D_80083460)->unk_0A != 0) {
            break;
        }
        if (((Rec_D_80082E80 *)entity)->unk_14.at00_u32.v & 0x4000) {
            if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u32.v & 0x20000000)) {
                func_800ACF88(entity);
            }
        }
        ((S_801733BC_1 *)effect_state)->unk_9B++;
        /* fallthrough */
    case 1:
        if (!(((S_801733BC_0 *)render_part)->unk_14 & 0xE000)) {
            break;
        }
        ((S_801733BC_1 *)effect_state)->unk_A8.u = 0;
        {
            register void *center_object ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
            Rect *rect_ptr;
            Point *center_ptr;
            s16 center_y;

            center_object = effect_state;
            rect_ptr = &rect;
            center_ptr = &center;
            ASM_USE(center_ptr);   /* MATCH pin: keeps a statement from moving across a call/branch */
            center.x = rect.x + ((s16)rect.w >> 1);
            center_y = rect.y + ((s16)rect.h >> 1);
            ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
            center.y = center_y;
            func_800B8FC8(center_object, rect_ptr, center_ptr, 1, 0);
        }

        ((Rec_D_80082E80 *)entity)->unk_1C.at00_u32.v |= 0x10000000;
        ((S_801733BC_0 *)render_part)->unk_10 = 0x60;
        ((S_801733BC_0 *)render_part)->unk_0C.u32 = 0x00C0C0C0;
        ((S_801733BC_0 *)render_part)->unk_14 |= 0xC;
        ((S_801733BC_0 *)render_part)->unk_12 -= 0x80;
        ((S_801733BC_1 *)effect_state)->unk_9B++;
        func_800A56E0(0x806);

        spawned_object = func_8003FD64(0x12, D_80083498);
        if (spawned_object == 0) {
            break;
        }
        func_8004491C(spawned_object, D_80174228);
        projectile_callback = D_801741A4;
        ASM_KEEP(projectile_callback);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_801733BC_2 *)spawned_object)->unk_10 = projectile_callback;
        ((S_801733BC_2 *)spawned_object)->unk_20 = ((S_801733BC_3 *)position)->unk_02;
        projectile_y = ((S_801733BC_3 *)position)->unk_06;
        projectile_state = (u8 *)spawned_object + 0x20;
        ((S_801733BC_8 *)projectile_state)->unk_02 = projectile_y;
        projectile_z = ((S_801733BC_3 *)position)->unk_0A;
        ((S_801733BC_8 *)projectile_state)->unk_10 = 0xFFFC0000;
        ((S_801733BC_8 *)projectile_state)->unk_0C = 0;
        ((S_801733BC_8 *)projectile_state)->unk_14 = 0xFFFE8000;
        ((S_801733BC_8 *)projectile_state)->unk_18 = 0x14;
        ((S_801733BC_8 *)projectile_state)->unk_08 = 0;
        ((S_801733BC_8 *)projectile_state)->unk_04 = projectile_z;
        break;

    case 2:
        ((Rec_D_80082E80 *)entity)->unk_1C.at00_u32.v |= 0x10000000;
        ((S_801733BC_0 *)render_part)->unk_0C.u32 += 0xFFEFEFF0;
        if (((S_801733BC_0 *)render_part)->unk_0C.u8 < 0x11) {
            ((S_801733BC_1 *)effect_state)->unk_96 = 10;
            ((S_801733BC_1 *)effect_state)->unk_9B++;
        }
        break;

    case 3:
        frames_left = ((S_801733BC_1 *)effect_state)->unk_96 - 1;
        ((S_801733BC_1 *)effect_state)->unk_96 = frames_left;
        if ((s16)frames_left > 0) {
            break;
        }
        effect_list = D_80083460;
        if (((S_801733BC_9 *)effect_list)->unk_10.p == (u8 *)entity - 0x20) {
            ((S_801733BC_9 *)effect_list)->unk_10.i &= 0x7FFFFFFF;
        }
        func_800A2FE0(entity);
        func_800A32A4(entity);
        func_8009A3D0(((S_801733BC_0 *)render_part)->unk_24, ((S_801733BC_0 *)render_part)->unk_25,
            (((Rec_D_80082E80 *)entity)->unk_1C.at00_u32.v & 0x2000) ? 0x300 : 0x3000);
        func_8009A028(entity);
        (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}
