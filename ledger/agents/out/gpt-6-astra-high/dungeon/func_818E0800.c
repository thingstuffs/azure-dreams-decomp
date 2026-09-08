#include "common.h"

typedef struct S_818E0800_0_pre {
    u16 unk_00;
} S_818E0800_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */

typedef struct S_818E0800_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x44];
    union { u16 s; s16 u; } unk_50;   /* accessed as both */
    union { s16 s; u16 u; } unk_52;   /* accessed as both */
} S_818E0800_0;   /* arg0 in BODY_NAME */

typedef struct S_818E0800_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818E0800_1_pre;   /* the 0x14 bytes before object in BODY_NAME, addressed as object[-1] */

typedef struct S_818E0800_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union { u8 s; s8 u; } unk_72;   /* accessed as both */
    union { u8 s; s8 u; } unk_73;   /* accessed as both */
} S_818E0800_1;   /* object in BODY_NAME */

typedef struct S_818E0800_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_10;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_818E0800_2;   /* arg1 in BODY_NAME */

typedef struct S_818E0800_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_818E0800_3;   /* base in BODY_NAME */

typedef struct S_818E0800_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818E0800_4;   /* alternate in BODY_NAME */

typedef struct S_818E0800_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x2E];
    u16 unk_48;
    u8 pad_4A[0x2];
    u16 unk_4C;
} S_818E0800_5;   /* work in BODY_NAME */

typedef struct S_818E0800_6 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_818E0800_6;   /* state in BODY_NAME */

typedef struct S_818E0800_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_818E0800_7;   /* page in BODY_NAME */

typedef struct S_818E0800_8 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_818E0800_8;   /* header in BODY_NAME */

typedef struct S_818E0800_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818E0800_9_pre;   /* the 0x14 bytes before result in BODY_NAME, addressed as result[-1] */

typedef struct S_818E0800_10 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818E0800_10;   /* arg2 in BODY_NAME */

typedef struct S_818E0800_11 {
    u8 unk_00;
} S_818E0800_11;   /* D_800E3D68 in BODY_NAME */

typedef struct S_818E0800_12 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818E0800_12;   /* ((S_818E0800_3 *)base)->unk_08 in BODY_NAME */

typedef struct S_818E0800_13 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818E0800_13;   /* ((S_818E0800_4 *)alternate)->unk_08 in BODY_NAME */

typedef struct S_818E0800_14 {
    u16 unk_00;
} S_818E0800_14;   /* ((S_818E0800_0 *)arg0)->unk_04 in BODY_NAME */

typedef struct S_818E0800_15 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_818E0800_15;   /* ((S_818E0800_1 *)object)->unk_60 in BODY_NAME */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(void);
extern void func_800240EC(void) __attribute__((noreturn));
extern void func_800242C8(void) __attribute__((noreturn));
extern void func_80024430(void) __attribute__((noreturn));
extern void func_80024504() __attribute__((noreturn));
extern void func_80024560(void) __attribute__((noreturn));
extern void func_80024784(void *, s32);
extern void func_800419EC(s32, s32);
extern void *func_800A05A4();
extern s32 func_800A3820(s32);
extern s32 func_8009D218(void *, s32, void *);
extern void func_800A56E0(s32);
extern s32 func_800BCB04(s32, s32, s32);
extern void func_800C8900(void *, s32, s32);

extern u8 D_80083498[];
extern u8 D_80045340[];
extern u8 D_800DEC28[];
extern u8 D_800E3D68[];
extern s32 D_8008346C[];
extern s32 D_800814A0[];
extern void func_80024594(void);

#ifdef __mips__
void func_818E0800(void);
static const u32 split_prefix[] __asm__("func_818E0800")
    __attribute__((section(".text.func_818E0800"), aligned(4))) = {
    0x8002401C, 0x10001000, 0x14000E10, 0x18000D48,
    0x0FA01000, 0x0DAC1800, 0x0BB82000,
};
__asm__(".globl func_818E0800\n"
        ".size func_818E0800, 1428");
#define BODY_NAME func_818E081C
#else
#define BODY_NAME func_818E0800
#endif

/* Updates target-directed movement, spawns particles, and advances the effect state. */
void BODY_NAME(void *effect_arg, void *motion_arg, S_818E0800_10 *actor_state)
{
    void *effect = effect_arg;
    void *motion = motion_arg;
    register void *actor ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs actor_base+offset) depends on it */
    void *actor_base;
    void *entity;
    void *target;
    void *render_state;
    void *particle;
    register void *sprite_set;
    s32 particles_left;
    register void *actor_data;
    register s32 timer;
    s32 initial_state;
    s32 dispatch_state;
    s32 ground_z;
    s32 found_target;
    s32 hit_effect;

    actor = ((S_818E0800_0 *)effect)->unk_00;
    timer = ((S_818E0800_0 *)effect)->unk_50.s;
    actor_data = ((S_818E0800_1_pre *)actor)[-1].unk_00;
    timer -= 1;
    initial_state = ((S_818E0800_0 *)effect)->unk_0A.s;
    ((S_818E0800_0 *)effect)->unk_50.s = timer;
    actor_base = (u8 *)actor - 0x20;

    if (initial_state == 2) {
        target = ((S_818E0800_1 *)actor)->unk_60;
        if (target == 0) {
            ((S_818E0800_2 *)motion)->unk_00.at00.v =
                ((S_818E0800_12 *)(((S_818E0800_3 *)actor_base)->unk_08))->unk_00.at00.v;
            ((S_818E0800_2 *)motion)->unk_04.at00.v =
                ((S_818E0800_12 *)(((S_818E0800_3 *)actor_base)->unk_08))->unk_04.at00.v;
            target = ((S_818E0800_3 *)actor_base)->unk_08;
            ASM_KEEP(target);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            return func_800240EC();
        }
        entity = (u8 *)target - 0x20;
        ((S_818E0800_2 *)motion)->unk_00.at00.v = ((S_818E0800_13 *)(((S_818E0800_4 *)entity)->unk_08))->unk_00;
        ((S_818E0800_2 *)motion)->unk_04.at00.v = ((S_818E0800_13 *)(((S_818E0800_4 *)entity)->unk_08))->unk_04;
        ((S_818E0800_2 *)motion)->unk_08.at00.v = ((S_818E0800_13 *)(((S_818E0800_4 *)entity)->unk_08))->unk_08;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */

        particles_left = 5;
        sprite_set = D_800DEC28;
        do {
            entity = func_8003FD64(0x312, D_80083498);
            if (entity != 0) {
                func_8004491C(entity, &D_80045340);
                render_state = ((S_818E0800_4 *)entity)->unk_0C;
                ((S_818E0800_4 *)entity)->unk_10 = func_80024594;
                particle = (u8 *)entity + 0x20;
                ((S_818E0800_5 *)particle)->unk_0C = ((S_818E0800_2 *)motion)->unk_00.at02.v;
                ((S_818E0800_5 *)particle)->unk_0E = ((S_818E0800_2 *)motion)->unk_04.at02.v;
                {
                    s32 particle_z;
                    particle_z = ((S_818E0800_2 *)motion)->unk_08.at02.v;
                    ((S_818E0800_5 *)particle)->unk_48 = 0;
                    ((S_818E0800_5 *)particle)->unk_16 = 0;
                    ((S_818E0800_5 *)particle)->unk_14 = 0;
                    particle_z += 0x10;
                    ((S_818E0800_5 *)particle)->unk_10 = particle_z;
                }
                ((S_818E0800_5 *)particle)->unk_18 = func_80069EF8();
                ((S_818E0800_6 *)render_state)->unk_1E = 0x1000;
                ((S_818E0800_6 *)render_state)->unk_1C = 0x1000;
                ((S_818E0800_6 *)render_state)->unk_10 = 0x60;
                ((S_818E0800_6 *)render_state)->unk_00 = sprite_set;
                ((S_818E0800_6 *)render_state)->unk_14 |= 0xC;
                ((S_818E0800_6 *)render_state)->unk_08 = ((S_818E0800_7 *)sprite_set)->unk_04;
                ((S_818E0800_6 *)render_state)->unk_04 = 0;
                ((S_818E0800_6 *)render_state)->unk_05 = 0;
                ((S_818E0800_4 *)entity)->unk_20 = effect;
                ((S_818E0800_5 *)particle)->unk_4C = 0;
            }
            particles_left -= 1;
        } while (particles_left >= 0);
    }

    dispatch_state = ((S_818E0800_0 *)effect)->unk_0A.s;
    if (dispatch_state == 2) {
        goto dispatch_case_2;
    }
    if (dispatch_state >= 3) {
        goto dispatch_high;
    }
    if (dispatch_state == 0) {
        goto dispatch_case_0;
    }
    if (dispatch_state == 1) {
        goto dispatch_case_1;
    }
    return func_80024560();

dispatch_high:
    if (dispatch_state == 0xF0) {
        goto dispatch_case_f0;
    }
    if (dispatch_state == 0xFF) {
        goto dispatch_case_ff;
    }
    return func_80024560();

dispatch_case_0:
        if (!(((S_818E0800_14 *)(((S_818E0800_0 *)effect)->unk_04))->unk_00 & 0x80)) {
            return;
        }
        found_target = (s32)func_800A05A4(
            actor, ((S_818E0800_8 *)actor_data)->unk_24, ((S_818E0800_8 *)actor_data)->unk_25,
            ((S_818E0800_1 *)actor)->unk_2A,
            (s16)func_800A3820(0x23));
        ((S_818E0800_1 *)actor)->unk_60 = found_target;
        if (found_target == 0) {
            ((S_818E0800_1 *)actor)->unk_72.s = ((S_818E0800_8 *)actor_data)->unk_24;
            ((S_818E0800_1 *)actor)->unk_73.s = ((S_818E0800_8 *)actor_data)->unk_25;
            return func_800242C8();
        }

        render_state = ((S_818E0800_9_pre *)found_target)[-1].unk_00;
        if (((S_818E0800_6 *)render_state)->unk_14 & 0x8000) {
            if (actor_state->unk_14 & 0x8000) {
                goto state_f0;
            }
        }
        ((S_818E0800_1 *)actor)->unk_72.s = ((S_818E0800_6 *)render_state)->unk_24;
        ((S_818E0800_1 *)actor)->unk_73.s = ((S_818E0800_6 *)render_state)->unk_25;
        ((S_818E0800_2 *)motion)->unk_00.at02.v =
            ((S_818E0800_12 *)(((S_818E0800_3 *)actor_base)->unk_08))->unk_00.at02.v;
        ((S_818E0800_2 *)motion)->unk_04.at02.v =
            ((S_818E0800_12 *)(((S_818E0800_3 *)actor_base)->unk_08))->unk_04.at02.v;
        ((S_818E0800_2 *)motion)->unk_08.at02.v =
            ((S_818E0800_12 *)(((S_818E0800_3 *)actor_base)->unk_08))->unk_0A;
        ((S_818E0800_0 *)effect)->unk_50.s = 8;

        {
            s32 delta_x = ((S_818E0800_1 *)actor)->unk_72.u;
            s32 origin_x = ((S_818E0800_2 *)motion)->unk_00.at02.v;
            delta_x <<= 6;
            origin_x -= 0x20;
            delta_x -= origin_x;
            ((S_818E0800_2 *)motion)->unk_0C.at02.v = delta_x;
        }
        ((S_818E0800_2 *)motion)->unk_0C.at00.v /= ((S_818E0800_0 *)effect)->unk_50.u;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        {
            s32 delta_y = ((S_818E0800_1 *)actor)->unk_73.u;
            s32 origin_y = ((S_818E0800_2 *)motion)->unk_04.at02.v;
            delta_y <<= 6;
            origin_y -= 0x20;
            delta_y -= origin_y;
            ((S_818E0800_2 *)motion)->unk_10.at02.v = delta_y;
        }
        ((S_818E0800_2 *)motion)->unk_10.at00.v /= ((S_818E0800_0 *)effect)->unk_50.u;
        ground_z = (s16)(((S_818E0800_12 *)(((S_818E0800_3 *)actor_base)->unk_08))->unk_0A - 0x30);
        ground_z = func_800BCB04(((S_818E0800_2 *)motion)->unk_00.at02.v, ((S_818E0800_2 *)motion)->unk_04.at02.v, ground_z);
        ((S_818E0800_2 *)motion)->unk_14.at02.v = ground_z - ((S_818E0800_2 *)motion)->unk_08.at02.v;
        ((S_818E0800_2 *)motion)->unk_14.at00.v /= ((S_818E0800_0 *)effect)->unk_50.u;
        func_800A56E0(0x300);
        {
            s32 next_state;
            next_state = ((S_818E0800_0 *)effect)->unk_0A.u;
            next_state += 1;
            ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail delay-slot fill depends on it */
            return func_80024430();
        }

dispatch_case_1: {
        s32 next_timer;
        ((S_818E0800_2 *)motion)->unk_00.at00.v += ((S_818E0800_2 *)motion)->unk_0C.at00.v;
        ((S_818E0800_2 *)motion)->unk_04.at00.v += ((S_818E0800_2 *)motion)->unk_10.at00.v;
        ((S_818E0800_2 *)motion)->unk_08.at00.v += ((S_818E0800_2 *)motion)->unk_14.at00.v;
        if (((S_818E0800_0 *)effect)->unk_50.u > 0) {
            return;
        }
        if (((S_818E0800_1 *)actor)->unk_60 != 0) {
            next_timer = 24;
        } else {
            next_timer = 10;
        }
        ((S_818E0800_0 *)effect)->unk_50.u = next_timer;
        ((S_818E0800_0 *)effect)->unk_0A.u += 1;
        return func_80024560();
    }

dispatch_case_2: {
        register s32 sound_id ASM_REG("$4");   /* MATCH pin: retail basic-block layout depends on it */
        void *active_target;
        if (((S_818E0800_0 *)effect)->unk_50.u > 0) {
            return;
        }
        active_target = ((S_818E0800_1 *)actor)->unk_60;
        sound_id = 8;
        if (active_target == 0) {
            ((S_818E0800_0 *)effect)->unk_50.u = 10;
            return func_80024504(sound_id);
        }
        func_800419EC(sound_id, 0x10);
        ((S_818E0800_0 *)effect)->unk_50.u = 6;
state_f0:
        ((S_818E0800_0 *)effect)->unk_0A.u = 0xF0;
        return func_80024560();
    }

dispatch_case_f0:
        func_80024784(((S_818E0800_1 *)actor)->unk_60, ((S_818E0800_0 *)effect)->unk_50.u);
        if (((S_818E0800_0 *)effect)->unk_50.u == 2 &&
            !func_8009D218(((S_818E0800_1 *)actor)->unk_60, 2, actor)) {
            if (((S_818E0800_15 *)(((S_818E0800_1 *)actor)->unk_60))->unk_14 & 1) {
                if (((S_818E0800_1 *)actor)->unk_60 != 0) {
                    hit_effect = (((S_818E0800_11 *)D_800E3D68)->unk_00 == 0xFF) ? 0xFF : 0x10;
                    func_800C8900(((S_818E0800_1 *)actor)->unk_60, hit_effect, 2);
                }
            }
        }
        if (((S_818E0800_0 *)effect)->unk_50.u > 0) {
            return;
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ((S_818E0800_0 *)effect)->unk_0A.u = 0xFF;
        return func_80024560();

dispatch_case_ff:
        if (((S_818E0800_0 *)effect)->unk_52.s & 0x8000) {
            ((S_818E0800_0 *)effect)->unk_52.u &= 0x7FFF;
            return func_80024560();
        }
        if (((S_818E0800_0 *)effect)->unk_50.u > 0) {
            return;
        }
        D_8008346C[0] = 0;
        ((S_818E0800_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;

}
