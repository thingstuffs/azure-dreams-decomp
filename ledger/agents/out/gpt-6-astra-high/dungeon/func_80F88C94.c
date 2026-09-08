#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80172494_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    s8 unk_6D;
} S_80172494_0;   /* arg3_reg in func_80172494 */

typedef struct S_80172494_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172494_1;   /* arg0 in func_80172494 */


typedef struct S_80172494_3 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172494_3;   /* arg1 in func_80172494 */

typedef struct S_80172494_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80172494_4;   /* temp_v0_2 in func_80172494 */

typedef struct S_80172494_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u8 pad_1A[0x2E];
    s16 unk_48;
} S_80172494_5;   /* temp_s0_2 in func_80172494 */

typedef struct S_80172494_6 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80172494_6;   /* temp_s1 in func_80172494 */

typedef struct S_80172494_7 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80172494_7;   /* temp_fp in func_80172494 */

typedef struct S_80172494_8 {
    u8 pad_00[0x3DE8];
    void * unk_3DE8;
} S_80172494_8;   /* (void *)temp_v1 in func_80172494 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern u8 D_80045340;
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern s32 D_80083498;
extern u8 D_800DEC28[];
extern void *D_800E3DE8;
extern u8 D_80171138[];
extern u8 D_80173F0C[];
extern u8 D_80174AD4[];
extern u8 D_80174AE4[];

/* Updates a staged movement action, spawns particles, and restores the actor when finished. */
void func_80172494(void *action, void *motion, void *map_actor, void *actor_arg) {
    s32 particle_offset_x;
    s32 direction_x;
    register s32 direction_y ASM_REG("$22");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 setup_value ASM_REG("$4");   /* MATCH pin: retail immediate-load split depends on it */
    register s32 result ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 velocity_x;
    s32 velocity_z;
    register s32 operand ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    s32 index;
    s32 state;
    void *particle_motion;
    void *particle_sprite;
    void *particle;
    u8 *particle_texture;
    register void *actor ASM_REG("$23");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *direction_x_table;
    u8 *direction_y_table;

    actor = actor_arg;
    index = ((S_80172494_0 *)actor)->unk_2A.s >> 8;
    setup_value = index & 0xE;
    direction_x_table = (u8 *)&D_8006CCD8;
    direction_x_table += setup_value;
    direction_y_table = (u8 *)&D_8006CCE8;
    direction_x = *(s16 *)direction_x_table;
    direction_y = *(s16 *)(direction_y_table + setup_value);
    state = ((S_80172494_1 *)action)->unk_9B;
    ((S_80172494_1 *)action)->unk_96.s = ((S_80172494_1 *)action)->unk_96.s - 1;

    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172494_1 *)action)->unk_9B = 0xFF;
            ((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v |= 0x6000;
            func_8009C12C(actor, map_actor, ((S_80172494_0 *)actor)->unk_2A.u, 1);
            goto action_end;
        }
        setup_value = 0xF7FFFFFF;
        operand = 0xFFFBFFFF;
        result = -direction_x;
        result <<= 18;
        ((S_80172494_3 *)motion)->unk_0C = result;
        result = -direction_y;
        result <<= 18;
        ((S_80172494_3 *)motion)->unk_10 = result;
        ((S_80172494_1 *)action)->unk_98 |= 8;
        result = ((S_80172494_0 *)actor)->unk_1C;
        result &= setup_value;
        result &= operand;
        ((S_80172494_0 *)actor)->unk_1C = result;
        ((S_80172494_1 *)action)->unk_96.s = 4;
        ((S_80172494_3 *)motion)->unk_14 = 0xFFFD0000;
        goto advance_state;

    case 1:
        result = ((S_80172494_3 *)motion)->unk_14;
        ((S_80172494_3 *)motion)->unk_14 = result + (result >> 2);
        if (((S_80172494_1 *)action)->unk_96.u > 0) {
            goto action_end;
        }
        result = ((S_80172494_1 *)action)->unk_9B;
        ((S_80172494_1 *)action)->unk_96.s = 8;
        goto store_next_state;

    case 2:
        velocity_x = ((S_80172494_3 *)motion)->unk_0C;
        operand = ((S_80172494_3 *)motion)->unk_10;
        ((S_80172494_3 *)motion)->unk_0C = velocity_x - (velocity_x >> 3);
        velocity_z = ((S_80172494_3 *)motion)->unk_14;
        ((S_80172494_3 *)motion)->unk_10 = operand - (operand >> 3);
        ((S_80172494_3 *)motion)->unk_14 = velocity_z - (velocity_z >> 3);
        if ((((S_80172494_1 *)action)->unk_96.u == 4) ||
            (((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x8000)) {
            ((S_80172494_3 *)motion)->unk_0C = 0;
            ((S_80172494_3 *)motion)->unk_10 = 0;
            ((S_80172494_3 *)motion)->unk_14 = 0;
            (*(void * *)((u8 *)map_actor + 0x2C)) = D_80174AE4;
            result = (D_80083228 + ((S_80172494_0 *)actor)->unk_2A.u + 0x100) >> 9;
            func_80047784(map_actor, D_80174AE4[result & 7], 0);
        }
        if (((S_80172494_1 *)action)->unk_96.u > 0) {
            goto action_end;
        }
        if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0xE000)) {
            goto action_end;
        }
        ((S_80172494_1 *)action)->unk_96.s = 4;
        ((S_80172494_3 *)motion)->unk_0C = (direction_x << 18) + (direction_x << 17);
        ((S_80172494_3 *)motion)->unk_10 = (direction_y << 18) + (direction_y << 17);
        func_800A56E0(0x80E);
        ASM_USE(direction_y);   /* MATCH pin: load-bearing for the whole function shape */
        goto advance_state;

    case 3:
        ((S_80172494_1 *)action)->unk_90 += 0x80000;
        ((S_80172494_3 *)motion)->unk_0C += direction_x << 18;
        ((S_80172494_3 *)motion)->unk_10 += direction_y << 18;
        ASM_USE(direction_y);   /* MATCH pin: load-bearing for the whole function shape */
        if (((S_80172494_1 *)action)->unk_96.u > 0) {
            goto action_end;
        }
        func_800A56E0(0x808);
        func_8009C12C(actor, map_actor, ((S_80172494_0 *)actor)->unk_2A.u, 1);

advance_state:
        result = ((S_80172494_1 *)action)->unk_9B;
store_next_state:
        ((S_80172494_1 *)action)->unk_9B = result + 1;
        goto action_end;

    case 4:
        ((S_80172494_1 *)action)->unk_90 += 0x80000;
        if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0xE000)) {
            goto action_end;
        }
        ((S_80172494_3 *)motion)->unk_14 = 0;
        ((S_80172494_1 *)action)->unk_98 &= 0xFFF7;
        ((S_80172494_0 *)actor)->unk_1C |= 0x40000;
        ((S_80172494_0 *)actor)->unk_1C |= 0x08000000;
        ((S_80172494_1 *)action)->unk_96.s = state;
        ((S_80172494_1 *)action)->unk_9B = 0xFF;
        goto action_end;

    case 0xFF:
        result = ((Rec_D_80082E80 *)map_actor)->unk_24 << 6;
        operand = ((S_80172494_3 *)motion)->unk_02.s - 0x20;
        result -= operand;
        result = (result << 15) >> 1;
        ((S_80172494_3 *)motion)->unk_0C = result;
        ASM_USE(result);   /* MATCH pin: retail schedule: same instructions, different order without it */
        result = ((Rec_D_80082E80 *)map_actor)->unk_25 << 6;
        operand = ((S_80172494_3 *)motion)->unk_06.s - 0x20;
        result -= operand;
        result = (result << 15) >> 1;
        ((S_80172494_3 *)motion)->unk_10 = result;
        if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x8000) &&
            (((S_80172494_1 *)action)->unk_96.u != 0)) {
            index = 9;
            particle_offset_x = direction_x * 0x28;
            particle_texture = D_800DEC28;
            do {
                particle = func_8003FD64(0x312, &D_80083498);
                if (particle != NULL) {
                    func_8004491C(particle, &D_80045340);
                    particle_motion = (u8 *)particle + 0x20;
                    ((S_80172494_4 *)particle)->unk_10 = D_80173F0C;
                    particle_sprite = ((S_80172494_4 *)particle)->unk_0C;
                    ((S_80172494_5 *)particle_motion)->unk_0C =
                        ((S_80172494_3 *)motion)->unk_02.u - particle_offset_x;
                    ((S_80172494_5 *)particle_motion)->unk_0E =
                        ((S_80172494_3 *)motion)->unk_06.u - (direction_y * 0x28);
                    ((S_80172494_5 *)particle_motion)->unk_10 = ((S_80172494_3 *)motion)->unk_0A;
                    ((S_80172494_5 *)particle_motion)->unk_04 = rand() & 0xF;
                    ((S_80172494_5 *)particle_motion)->unk_06 = 0;
                    ((S_80172494_5 *)particle_motion)->unk_08 = (rand() & 0xF) + 8;
                    result = rand();
                    setup_value = 0xC00000;
                    ((S_80172494_5 *)particle_motion)->unk_14 = result;
                    operand = ((S_80172494_0 *)actor)->unk_2A.s;
                    ((S_80172494_5 *)particle_motion)->unk_48 = 5;
                    ((S_80172494_5 *)particle_motion)->unk_18 = operand;
                    operand = ((S_80172494_6 *)particle_sprite)->unk_14;
                    ((S_80172494_6 *)particle_sprite)->unk_1E = 0x1000;
                    ((S_80172494_6 *)particle_sprite)->unk_1C = 0x1000;
                    ((S_80172494_6 *)particle_sprite)->unk_10 = 0x60;
                    ((S_80172494_6 *)particle_sprite)->unk_00 = particle_texture;
                    ((S_80172494_6 *)particle_sprite)->unk_14 = operand | 0xC;
                    result = ((S_80172494_7 *)particle_texture)->unk_04;
                    setup_value |= 0xC0C0;
                    ((S_80172494_6 *)particle_sprite)->unk_04 = 0;
                    ((S_80172494_6 *)particle_sprite)->unk_05 = 0;
                    ((S_80172494_6 *)particle_sprite)->unk_0C = setup_value;
                    ((S_80172494_6 *)particle_sprite)->unk_08 = result;
                }
                index--;
            } while (index >= 0);
        }
        if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0xE000)) {
            goto action_end;
        }
        ((S_80172494_3 *)motion)->unk_10 = 0;
        ((S_80172494_3 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)map_actor)->unk_24,
                      ((Rec_D_80082E80 *)map_actor)->unk_25);
        func_800AD594(actor, 0x100);
        ((S_80172494_1 *)action)->unk_8C = D_80171138;
        D_8008346C = 0;
        (*(void * *)((u8 *)map_actor + 0x2C)) = D_80174AD4;
        result = (D_80083228 + ((S_80172494_0 *)actor)->unk_2A.u + 0x100) >> 9;
        func_80047784(map_actor, D_80174AD4[result & 7], 0);
        func_800A4ACC(actor);
        if (((S_80172494_0 *)actor)->unk_6D == 0) {
            ((S_80172494_0 *)actor)->unk_46 &= 0x7FFF;
            goto action_end;
        }
        operand = (s32)((u8 *)&D_800E3DE8 - 0x3DE8);
        result = (s32)((u8 *)actor - 0x20);
        ((S_80172494_8 *)((void *)operand))->unk_3DE8 = (void *)result;
        goto action_end;

    default:
        goto action_end;
    }

action_end:
    return;
}
