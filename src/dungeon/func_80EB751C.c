#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

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
    union { s32 s; s32 u; } unk_0C;   /* accessed as both */
    union { s32 s; s32 u; } unk_10;   /* accessed as both */
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
extern void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants);
extern void func_800AD4D0(void *);

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
    s32 component_work;
    s32 component_work_2;
    u8 *particle_work;

    if (((S_80172D1C_0 *)actor)->unk_9B == 1) {
        particle_or_dir_index = 6;
        particle_update = D_8017406C;
        do {
            particle = func_8003FD64(0x312, ((u8 *)(&D_80083498)));
            if (particle != 0) {
                particle_work = (u8 *)particle + 0x20;
                func_8004491C(particle, func_80045340);
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
                ((S_80172D1C_8 *)(((S_80172D1C_1 *)particle)->unk_08))->unk_14 = (-4 - (rand() & 3)) << 16;

                ((S_80172D1C_3 *)particle_work)->unk_48 = 10;
                sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v;
                component_work = ((S_80172D1C_5 *)particle_sprite)->unk_14 | 0xC;
                ((S_80172D1C_5 *)particle_sprite)->unk_1E = 0x1800;
                ((S_80172D1C_5 *)particle_sprite)->unk_1C = 0x1800;
                ((S_80172D1C_5 *)particle_sprite)->unk_28 = sprite_flags;
                ((S_80172D1C_5 *)particle_sprite)->unk_14 = component_work;
                component_work_2 = ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
                ((S_80172D1C_5 *)particle_sprite)->unk_10 = 0x20;
                ((S_80172D1C_5 *)particle_sprite)->unk_12 = component_work_2 - 0x80;
                func_80047784(particle_sprite, 0x2D, 0);
                ((S_80172D1C_5 *)particle_sprite)->unk_0C = 0x808080;
            }
            particle_or_dir_index--;
        } while (particle_or_dir_index >= 0);
    }

    particle_or_dir_index = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    state = ((S_80172D1C_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(entity);
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((S_80172D1C_2 *)motion)->unk_14 = 0;
            ((S_80172D1C_2 *)motion)->unk_10.s = 0;
            ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
            func_800AAA54(actor, motion, sprite, D_80174194);
            break;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172D1C_0 *)actor)->unk_96.s = 0;
            ((S_80172D1C_0 *)actor)->unk_9B = 2;
            break;
        }

        ((S_80172D1C_2 *)motion)->unk_0C.s = dirStepX[particle_or_dir_index] << 18;
        ((S_80172D1C_2 *)motion)->unk_10.s = dirStepY[particle_or_dir_index] << 18;
        ((S_80172D1C_0 *)actor)->unk_9B++;
        state_timer = -1;
        if (((EntityRec *)entity)->flags1C & 0x228) {
            state_timer = 8;
        }
        ((S_80172D1C_0 *)actor)->unk_96.s = state_timer;
        velocity_x = ((S_80172D1C_2 *)motion)->unk_0C.s;
        ((S_80172D1C_2 *)motion)->unk_0C.s = velocity_x - velocity_x / 4;
        velocity_y = ((S_80172D1C_2 *)motion)->unk_10.s;
        ((S_80172D1C_2 *)motion)->unk_10.s = velocity_y - velocity_y / 4;
        break;

    case 1:
        ((S_80172D1C_2 *)motion)->unk_0C.s -= dirStepX[particle_or_dir_index] << 14;
        ((S_80172D1C_2 *)motion)->unk_10.s -= dirStepY[particle_or_dir_index] << 14;
        timer = ((S_80172D1C_0 *)actor)->unk_96.s;
        if (timer > 0) {
            ((S_80172D1C_0 *)actor)->unk_96.s = ((S_80172D1C_0 *)actor)->unk_96.u - 1;
        } else {
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
                ((S_80172D1C_0 *)actor)->unk_96.s = 0;
            }
        }
        if (((S_80172D1C_0 *)actor)->unk_96.s != 0) {
            break;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((S_80172D1C_0 *)actor)->unk_9B = 0;
            ((S_80172D1C_2 *)motion)->unk_14 = 0;
            ((S_80172D1C_2 *)motion)->unk_10.s = 0;
            ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
            func_800AAA54(actor, motion, sprite, D_80174194);
            break;
        }
        ((S_80172D1C_0 *)actor)->unk_96.s = 8;
        ((S_80172D1C_0 *)actor)->unk_9B++;
        break;

    case 2:
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
            velocity_y = component_work >> 1;
            component_work = component_work + velocity_y;
            ((S_80172D1C_2 *)motion)->unk_0C.s = component_work;
            component_work = speed_work >> 1;
            speed_work += component_work;
            ((S_80172D1C_2 *)motion)->unk_10.s = speed_work;
        }
        next_timer = ((S_80172D1C_0 *)actor)->unk_96.u - 1;
        ((S_80172D1C_0 *)actor)->unk_96.s = next_timer;
        if ((next_timer << 16) <= 0) {
            ((S_80172D1C_2 *)motion)->unk_14 = 0;
            ((S_80172D1C_2 *)motion)->unk_10.s = 0;
            ((S_80172D1C_2 *)motion)->unk_0C.s = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(void * *)((u8 *)sprite + 0x2C)) = D_8017418C;
            func_80047784(sprite,
                          D_8017418C[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                          0);
            if (((s32)dungeonStatus.unk_10) == (s32)((u8 *)entity - 0x20)) {
                *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
            }
            ((S_80172D1C_0 *)actor)->unk_8C = D_801711A4;
        }
    }
}
