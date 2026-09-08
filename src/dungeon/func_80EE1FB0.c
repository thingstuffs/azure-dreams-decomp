#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef s32 Any;

typedef struct S_801737B0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737B0_0;   /* arg0 in func_801737B0 */


typedef struct S_801737B0_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_801737B0_2_pre;   /* the 0x14 bytes before ptr in func_801737B0, addressed as ptr[-1] */

typedef struct S_801737B0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737B0_3;   /* desc in func_801737B0 */



typedef struct S_801737B0_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801737B0_6;   /* global in func_801737B0 */


extern void *D_80170888[];
extern void *D_801708A0[];
extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80171CE8[];
extern u8 D_80174EB8[];

extern s32 func_8003F270();
extern Any func_80047784();
extern s32 func_80069EF8();
extern void *func_800A05A4();
extern Any func_800A2B04();
extern Any func_800A4ACC();
extern Any func_800A56E0();
extern s32 func_800A94A0();
extern Any func_80171498();

/* Updates an actor action through targeting, particle effects, and recovery. */
void func_801737B0(void *action, void *motion, void *sprite, void *actor) {
    static void *const state_jt[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    static void *const kind_jt[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_bad,
        &&kind_5, &&kind_6, &&kind_7
    };
    s32 use_player_target;
    register s32 particle_count ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 facing_x;
    s32 offset_z;
    s32 direction;
    s32 action_kind;
    register s32 particle_zero ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 particle_color ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 offset_x ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 offset_y ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 timer;
    u16 sprite_flags;
    u16 raw_kind;
    u32 kind_index;
    u8 state;
    u8 *action_data;
    u8 *effect_state;
    u8 *particle_origin;
    register void *target ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

    state = ((S_801737B0_0 *)action)->unk_9B;
    use_player_target = 0;
    if ((u32)state >= 5U) {
        goto done;
    }
    (void)state_jt;
    goto *D_80170888[(u32)state];

state_0:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x2000) {
        raw_kind = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
        kind_index = raw_kind - 1;
        if (kind_index >= 7U) {
            goto kind_bad;
        }
        (void)kind_jt;
        goto *D_801708A0[kind_index];
kind_7:
        use_player_target = 1;
        goto kind_3;
kind_6:
        use_player_target = 1;
        goto kind_2;
kind_5:
        use_player_target = 1;
        goto kind_1;
    }

    action_kind = ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x3FFF;
    if (action_kind == 2) {
        goto kind_2;
    }
    if (action_kind < 3) {
        action_data = 0;
        if (action_kind == 1) {
            goto kind_1;
        }
        goto kind_ready;
    }
    action_data = 0;
    if (action_kind == 3) {
        goto kind_3;
    }
    goto kind_ready;

kind_3:
    action_data = (u8 *)actor + 0xE;
    goto kind_ready;
kind_2:
    action_data = (u8 *)actor + 0xB;
    goto kind_ready;
kind_1:
    action_data = (u8 *)actor + 8;
    goto kind_ready;
kind_bad:
    action_data = 0;

kind_ready:
    if (*action_data == 0) {
        goto remove_actor;
    }

    ((S_801737B0_0 *)action)->unk_98 &= 0xFF7F;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    target = (void *)use_player_target;
    if (target != 0) {
        target = D_800814A8;
        ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = target;
        goto copy_facing;
    }

    if (D_8006DE24[*action_data * 0x14 + 0x12] == 2) {
        target = ((Rec_D_800E3D7C *)actor)->unk_60.as_pv;
        if (target != 0) {
copy_facing:
            {
                u8 *target_sprite;
                u8 facing;

                target_sprite = ((S_801737B0_2_pre *)target)[-1].unk_00;
                ASM_USE(target);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                facing = ((S_801737B0_3 *)target_sprite)->unk_24;
                ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = facing;
                facing = ((S_801737B0_3 *)target_sprite)->unk_25;
                ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = facing;
            }
        }
    } else {
        s32 facing_y;

        ((Rec_D_800E3D7C *)actor)->unk_60.as_pv = func_800A05A4(
            actor,
            ((Rec_D_80082E80 *)sprite)->unk_24,
            ((Rec_D_80082E80 *)sprite)->unk_25,
            ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16,
            0x10);
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        facing_x = ((Rec_D_800E3D7C *)actor)->unk_72.as_s8;
        facing_y = ((Rec_D_800E3D7C *)actor)->unk_73.as_s8;
        if (facing_x < 0) {
            facing_x = -facing_x;
        }
        if (facing_y < 0) {
            facing_y = -facing_y;
        }
        ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = facing_x;
        ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = facing_y;
    }

    if (func_800A94A0(actor, action_data, use_player_target, (u8 *)action + 0x98) == 0) {
        goto done;
    }
    ((S_801737B0_0 *)action)->unk_9B++;
    goto done;

remove_actor:
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(actor);
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
    ((S_801737B0_0 *)action)->unk_8C = D_80171CE8;
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    goto done;

state_1:
    if (func_8003F270(motion) != 0) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x800;
        goto done;
    }
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    ((S_801737B0_0 *)action)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
    if (sprite_flags & 0x8000) {
        ((S_801737B0_0 *)action)->unk_96.s = 0;
        ((S_801737B0_0 *)action)->unk_9B++;
        ((S_801737B0_0 *)action)->unk_98 |= 0x80;
        goto done;
    }

    if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 2) && (sprite_flags & 0x1000)) {
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = sprite_flags | 0x800;
        ((S_801737B0_0 *)action)->unk_96.s = 0x16;
    }
    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 < 2) {
        goto done;
    }

    timer = ((S_801737B0_0 *)action)->unk_96.s - 1;
    ((S_801737B0_0 *)action)->unk_96.s = timer;
    if ((s16)timer <= 0) {
        ((S_801737B0_0 *)action)->unk_96.s = 0;
        ((S_801737B0_0 *)action)->unk_9B++;
    }
    if (((S_801737B0_0 *)action)->unk_96.u == 2) {
        ((S_801737B0_0 *)action)->unk_98 |= 0x80;
    }
    if (((S_801737B0_0 *)action)->unk_96.u < 0xA) {
        goto done;
    }

    particle_count = 0;
particle_loop:
    particle_count++;
    offset_x = func_80069EF8() & 0x3F;
    offset_x -= 0x20;
    offset_x = (s16)offset_x;
    offset_y = func_80069EF8() & 0x3F;
    offset_y -= 0x20;
    offset_y = (s16)offset_y;
    offset_z = func_80069EF8();
    particle_origin = (u8 *)action - 0x20;
    ASM_USE(particle_origin);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    particle_zero = 0;
    particle_color = 0xC0C0C0;
    ASM_USE(particle_color);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    offset_z = (s16)((offset_z & 0x3F) - 0x20);
    func_80171498(
        particle_origin,
        particle_zero,
        particle_color,
        (s16)(((S_801737B0_0 *)action)->unk_96.s - 2),
        offset_x,
        offset_y,
        offset_z);
    if ((u32)(particle_count & 0xFFFF) >= 3U) {
        goto done;
    }
    goto particle_loop;

state_3:
    ((S_801737B0_0 *)action)->unk_96.s = 0x14;
    ((S_801737B0_0 *)action)->unk_9B++;

state_4:
    effect_state = (u8 *)&D_80083460;
    if (((S_801737B0_6 *)effect_state)->unk_0C == 0) {
        ((S_801737B0_0 *)action)->unk_96.s = 0;
    }
    timer = ((S_801737B0_0 *)action)->unk_96.s - 1;
    ((S_801737B0_0 *)action)->unk_96.s = timer;
    if ((s16)timer <= 0) {
        ((S_801737B0_0 *)action)->unk_96.s = 0;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xF7FF;
    }
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pv != D_80174EB8) {
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174EB8;
        direction = ((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        func_80047784(sprite, D_80174EB8[direction], 0);
    }
    if (((S_801737B0_6 *)effect_state)->unk_0C != 0) {
        goto done;
    }

    ((S_801737B0_6 *)effect_state)->unk_0A--;
    ((S_801737B0_0 *)action)->unk_8C = D_80171CE8;
    func_800A4ACC(actor);
    ((Rec_D_800E3D7C *)actor)->unk_73.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_72.as_s8 = 0;
    ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
    ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
    func_800A56E0(0xB4);

done:
    return;
}
