#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172D1C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172D1C_0;   /* arg0 in func_80172D1C */

typedef struct S_80172D1C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80172D1C_1;   /* obj in func_80172D1C */

typedef struct S_80172D1C_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    union { s32 s; volatile s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
    s32 unk_14;
} S_80172D1C_2;   /* arg1 in func_80172D1C */

typedef struct S_80172D1C_3 {
    u8 pad_00[0x48];
    s16 unk_48;
} S_80172D1C_3;   /* (u8 *)calc_other in func_80172D1C */


typedef struct S_80172D1C_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80172D1C_5;   /* part in func_80172D1C */


typedef struct S_80172D1C_7 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80172D1C_7;   /* global_base in func_80172D1C */

typedef struct S_80172D1C_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172D1C_8;   /* ((S_80172D1C_1 *)obj)->unk_08 in func_80172D1C */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784();
extern s32 rand(void);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern u8 D_80045340[];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_80083498[];
extern u8 D_801711A4[];
extern u8 D_8017406C[];
extern u8 D_8017418C[];
extern u8 D_80174194[];

/* Updates actor movement, emits particles, and settles the actor onto its tile. */
void func_80172D1C(void *actor, void *motion, void *sprite, void *entity) {
    void *particle;
    void *particle_sprite;
    void *particle_update;
    u8 *unused_particle_state;
    u8 *world_state;
    s32 particle_or_dir_index;
    s32 state;
    s32 unused_value;
    s32 unused_value2;
    s32 sprite_flags;
    s32 timer;
    s32 next_timer;
    s16 state_timer;
    s32 velocity_x;
    s32 velocity_y;
    s32 speed_work;
    register s32 component_work ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 part_or_half_speed ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 anim_id ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 anim_frame ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    if (((S_80172D1C_0 *)actor)->unk_9B == 1) {
        particle_or_dir_index = 6;
        particle_update = D_8017406C;
        do {
            particle = func_8003FD64(0x312, D_80083498);
            if (particle != 0) {
                func_8004491C(particle, D_80045340);
                particle_sprite = ((S_80172D1C_1 *)particle)->unk_0C;
                ((S_80172D1C_1 *)particle)->unk_10 = particle_update;

                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_02 =
                    ((S_80172D1C_2 *)motion)->unk_02.s + (rand() & 0xF) - 8;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_06 =
                    ((S_80172D1C_2 *)motion)->unk_06.s + (rand() & 0xF) - 8;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_0A =
                    ((S_80172D1C_2 *)motion)->unk_0A + (rand() & 0xF) - 8;

                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_0C =
                    ((rand() & 0xFF) - 0x80) << 10;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_10 =
                    ((rand() & 0xFF) - 0x80) << 10;
                speed_work = rand();
                part_or_half_speed = (s32)particle_sprite;
                anim_id = 0x2D;
                anim_frame = 0;
                speed_work &= 3;
                component_work = -4;
                component_work -= speed_work;
                component_work <<= 16;
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_14 = component_work;

                component_work = (s32)particle + 0x20;
                ASM_KEEP(component_work);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                ((S_80172D1C_3 *)((u8 *)component_work))->unk_48 = 10;
                sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v;
                ASM_KEEP(sprite_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                component_work = ((S_80172D1C_5 *)particle_sprite)->unk_14;
                ((S_80172D1C_5 *)particle_sprite)->unk_1E = 0x1800;
                ((S_80172D1C_5 *)particle_sprite)->unk_1C = 0x1800;
                component_work |= 0xC;
                ASM_KEEP(component_work);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                ((S_80172D1C_5 *)particle_sprite)->unk_28 = sprite_flags;
                ((S_80172D1C_5 *)particle_sprite)->unk_14 = component_work;
                component_work = ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
                ((S_80172D1C_5 *)particle_sprite)->unk_10 = 0x20;
                ((S_80172D1C_5 *)particle_sprite)->unk_12 = component_work - 0x80;
                func_80047784((void *)part_or_half_speed, anim_id, anim_frame, sprite_flags);
                ((S_80172D1C_5 *)particle_sprite)->unk_0C = 0x808080;
            }
            particle_or_dir_index--;
        } while (particle_or_dir_index >= 0);
    }

    particle_or_dir_index = (((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 9) & 7;
    state = ((S_80172D1C_0 *)actor)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto check_state_2;
    }
    if (state == 0) {
        goto state_0;
    }
    goto end;

check_state_2:
    if (state == 2) {
        goto state_2;
    }
    goto end;

state_0:
    func_800AD4D0(entity);
    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        ((S_80172D1C_2 *)motion)->unk_14 = 0;
        ((S_80172D1C_2 *)motion)->unk_10.s = 0;
        ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
        func_800AAA54(actor, motion, sprite, D_80174194);
        goto end;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172D1C_0 *)actor)->unk_96.s = 0;
        ((S_80172D1C_0 *)actor)->unk_9B = 2;
        goto end;
    }

    ((S_80172D1C_2 *)motion)->unk_0C.s = D_8006CCD8[particle_or_dir_index] << 18;
    ((S_80172D1C_2 *)motion)->unk_10.s = D_8006CCE8[particle_or_dir_index] << 18;
    ((S_80172D1C_0 *)actor)->unk_9B++;
    state_timer = -1;
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x228) {
        state_timer = 8;
    }
    ((S_80172D1C_0 *)actor)->unk_96.s = state_timer;
    velocity_x = ((S_80172D1C_2 *)motion)->unk_0C.s;
    ((S_80172D1C_2 *)motion)->unk_0C.s = velocity_x - velocity_x / 4;
    velocity_y = ((S_80172D1C_2 *)motion)->unk_10.s;
    ((S_80172D1C_2 *)motion)->unk_10.s = velocity_y - velocity_y / 4;
    goto end;

state_1:
    ((S_80172D1C_2 *)motion)->unk_0C.s -= D_8006CCD8[particle_or_dir_index] << 14;
    ((S_80172D1C_2 *)motion)->unk_10.s -= D_8006CCE8[particle_or_dir_index] << 14;
    timer = ((S_80172D1C_0 *)actor)->unk_96.s;
    if (timer > 0) {
        ((S_80172D1C_0 *)actor)->unk_96.s = ((S_80172D1C_0 *)actor)->unk_96.u - 1;
        goto timer_join;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
        ((S_80172D1C_0 *)actor)->unk_96.s = 0;
    }

timer_join:
    if (((S_80172D1C_0 *)actor)->unk_96.s != 0) {
        goto end;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        ((S_80172D1C_0 *)actor)->unk_9B = 0;
        ((S_80172D1C_2 *)motion)->unk_14 = 0;
        ((S_80172D1C_2 *)motion)->unk_10.s = 0;
        ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
        func_800AAA54(actor, motion, sprite, D_80174194);
        goto end;
    }
    ((S_80172D1C_0 *)actor)->unk_96.s = 8;
    ((S_80172D1C_0 *)actor)->unk_9B++;
    goto end;

state_2:
    if (((S_80172D1C_0 *)actor)->unk_96.s != 0) {
        speed_work = ((Rec_D_80082E80 *)sprite)->unk_24;
        component_work = ((S_80172D1C_2 *)motion)->unk_02.u;
        speed_work <<= 6;
        component_work -= 0x20;
        speed_work -= component_work;
        speed_work <<= 15;
        speed_work >>= 1;
        ((S_80172D1C_2 *)motion)->unk_0C.u = speed_work;

        speed_work = ((Rec_D_80082E80 *)sprite)->unk_25;
        component_work = ((S_80172D1C_2 *)motion)->unk_06.u;
        speed_work <<= 6;
        component_work -= 0x20;
        speed_work -= component_work;
        speed_work <<= 15;
        component_work = ((S_80172D1C_2 *)motion)->unk_0C.u;
        speed_work >>= 1;
        ((S_80172D1C_2 *)motion)->unk_10.u = speed_work;
        part_or_half_speed = component_work >> 1;
        component_work = component_work + part_or_half_speed;
        ((S_80172D1C_2 *)motion)->unk_0C.s = component_work;
        component_work = speed_work >> 1;
        speed_work += component_work;
        ((S_80172D1C_2 *)motion)->unk_10.s = speed_work;
    }
    next_timer = ((S_80172D1C_0 *)actor)->unk_96.u - 1;
    ((S_80172D1C_0 *)actor)->unk_96.s = next_timer;
    if ((next_timer << 16) > 0) {
        goto end;
    }
    ((S_80172D1C_2 *)motion)->unk_14 = 0;
    ((S_80172D1C_2 *)motion)->unk_10.s = 0;
    ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    (*(void * *)((u8 *)sprite + 0x2C)) = D_8017418C;
    func_80047784(sprite,
                  D_8017418C[((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                  0);
    world_state = D_80083460;
    if (((S_80172D1C_7 *)world_state)->unk_10 == (s32)((u8 *)entity - 0x20)) {
        ((S_80172D1C_7 *)world_state)->unk_10 &= 0x7FFFFFFF;
    }
    ((S_80172D1C_0 *)actor)->unk_8C = D_801711A4;

end:
    return;
}
