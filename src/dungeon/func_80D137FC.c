#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172FFC_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172FFC_0;   /* arg0 in func_80172FFC */



typedef struct S_80172FFC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FFC_3;   /* arg1 in func_80172FFC */

typedef struct S_80172FFC_4 {
    u8 pad_00[0x94];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    u8 pad_A0[0x8];
    void * unk_A8;
    u8 pad_AC[0x8];
    s32 unk_B4;
} S_80172FFC_4;   /* temp_s2 in func_80172FFC */

typedef struct S_80172FFC_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80172FFC_5;   /* temp_v0_3 in func_80172FFC */

typedef struct S_80172FFC_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80172FFC_6;   /* temp_s1 in func_80172FFC */

typedef struct S_80172FFC_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172FFC_7;   /* temp_s0 in func_80172FFC */

typedef struct S_80172FFC_8 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80172FFC_8;   /* sp50 in func_80172FFC */

typedef struct S_80172FFC_9 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80172FFC_9;   /* temp_a1_2 in func_80172FFC */

typedef struct S_80172FFC_10 {
    s16 unk_00;
    u16 unk_02;
} S_80172FFC_10;   /* &sp60[((u16) ((S_80172FFC_4 *)temp_s2)->unk_94 >> 7) & 0x1C] in func_80172FFC */


typedef struct {
    u8 bytes[32];
} __attribute__((packed)) Packed32;

typedef struct {
    s64 out18;
    Packed32 copy;
} WorkMid;

typedef struct {
    s32 words[4];
} Copy16;

s32 func_8003DE58();     /* extern */
void *func_8003FD64();            /* extern */
M2C_UNK func_8004491C(); /* extern */
M2C_UNK func_80047784();         /* extern */
s32 func_80065420(); /* extern */
s32 rand();                                /* extern */
M2C_UNK func_8009C12C(); /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A56E0();                     /* extern */
void func_800AD594(void *, s32);  /* extern */
extern M2C_UNK D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80083498;
extern s8 D_800DCECC[];
extern Packed32 D_80170838;
extern M2C_UNK D_80170874;
extern M2C_UNK D_80171760;
extern u8 D_80174E90[];
extern u8 D_80174EB8[];
extern u8 D_80174EC0;

/* Advance the action animation and spawn pairs of effects with randomized velocities. */
void func_80172FFC(void *action, void *motion, void *sprite, void *actor) {
    u16 spawn_offset[3];
    u16 position[3];
    WorkMid effect_work;
    M2C_UNK projection_aux;
    M2C_UNK projection_flags;
    void *owner;
    u16 spawn_count;                                       /* compiler-managed */
    u8 *directions;
    u16 *position_ptr;
    M2C_UNK *screen_pos;
    s16 next_count;
    s32 effect_depth;
    s32 random_value;
    s32 velocity_base;
    register s32 vertical_speed ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 effect_tick;
    u16 wait_tick;
    u16 spawn_tick;
    u8 animation;
    s32 state;
    void *owner_sprite;
    void *effect_motion;
    void *effect_sprite;
    void *effect_data;
    void *effect;
    Copy16 *copy_dst;
    Copy16 *copy_src;
    Copy16 *copy_end;
    Packed32 *direction_source = &D_80170838;

    effect_work.copy = *direction_source;
    owner = action - 0x20;
    state = ((S_80172FFC_0 *)action)->unk_9B;
    if (state == 1) {
        goto wait;
    }
    if ((s32) state < 2) {
        if (state == 0) {
            goto init;
        }
        goto done;
    }
    if (state == 2) {
        goto emit;
    }
    if (state == 3) {
        goto finish;
    }
    goto done;

init:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172FFC_0 *)action)->unk_9B = 3U;
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x6000);
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
        goto done;
    }
    ((S_80172FFC_3 *)motion)->unk_14 = 0;
    ((S_80172FFC_3 *)motion)->unk_10 = 0;
    ((S_80172FFC_3 *)motion)->unk_0C = 0;
    goto advance;

wait:
    wait_tick = ((S_80172FFC_0 *)action)->unk_96 + 1;
    ((S_80172FFC_0 *)action)->unk_96 = wait_tick;
    if (((s16) wait_tick != 4) && !(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174EB8;
    func_80047784(sprite, D_80174EB8[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);

advance:
    ASM_KEEP_NV(action);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ((S_80172FFC_0 *)action)->unk_96 = 0U;
    ((S_80172FFC_0 *)action)->unk_9B = (u8) (((S_80172FFC_0 *)action)->unk_9B + 1);
    goto done;

emit:
    effect_tick = ((S_80172FFC_0 *)action)->unk_96 + 1;
    ((S_80172FFC_0 *)action)->unk_96 = effect_tick;
    if (((s16) effect_tick == 0x11) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        ((S_80172FFC_0 *)action)->unk_96 = 0U;
        ((S_80172FFC_0 *)action)->unk_9B = (u8) (((S_80172FFC_0 *)action)->unk_9B + 1);
    }
    if (((s16) ((S_80172FFC_0 *)action)->unk_96 == 0xB) || (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1);
    }
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80174E90;
        func_80047784(sprite, D_80174E90[((s32) (D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
    }
    spawn_tick = ((S_80172FFC_0 *)action)->unk_96;
    if ((u32) (spawn_tick - 9) < 5U) {
        if ((s16) spawn_tick == 9) {
            func_800A56E0(0x810);
        }
        directions = (u8 *)&effect_work.copy;
        position_ptr = &position;
        spawn_count = 0;
        screen_pos = (M2C_UNK *)&effect_work.out18;
        do {
            effect = func_8003FD64(0x112, &D_80083498);
            effect_data = effect + 0x20;
            if (effect != NULL) {
                ((S_80172FFC_4 *)effect_data)->unk_96 = 0x19;
                ((S_80172FFC_4 *)effect_data)->unk_9E = 0x19;
                ((S_80172FFC_5 *)effect)->unk_10 = &D_80170874;
                ((S_80172FFC_4 *)effect_data)->unk_A8 = motion;
                copy_src = (Copy16 *)sprite;
                copy_end = (Copy16 *)sprite + 3;
                ((S_80172FFC_4 *)effect_data)->unk_94 = (u16) ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16;
                effect_sprite = ((S_80172FFC_5 *)effect)->unk_0C;
                copy_dst = (Copy16 *)effect_sprite;
                do {
                    *copy_dst = *copy_src;
                    copy_src++;
                    copy_dst++;
                } while (copy_src != copy_end);
                ((S_80172FFC_6 *)effect_sprite)->unk_1E = 0;
                ((S_80172FFC_6 *)effect_sprite)->unk_1C = 0;
                ((S_80172FFC_6 *)effect_sprite)->unk_0E = 0x80;
                ((S_80172FFC_6 *)effect_sprite)->unk_0D = 0x80;
                ((S_80172FFC_6 *)effect_sprite)->unk_0C = 0x80;
                func_8004491C(effect, &D_80045340, copy_dst, copy_src);
                animation = D_80174EC0;
                ((S_80172FFC_6 *)effect_sprite)->unk_2C = &D_80174EC0;
                func_80047784(effect_sprite, animation, 0);
                effect_motion = ((S_80172FFC_5 *)effect)->unk_08;
                ((S_80172FFC_7 *)effect_motion)->unk_02 = (u16) ((S_80172FFC_3 *)motion)->unk_02;
                ((S_80172FFC_7 *)effect_motion)->unk_06 = (u16) ((S_80172FFC_3 *)motion)->unk_06;
                ((S_80172FFC_7 *)effect_motion)->unk_0A = (u16) ((S_80172FFC_3 *)motion)->unk_0A;
                owner_sprite = ((S_80172FFC_8 *)owner)->unk_0C;
                if (func_8003DE58(((S_80172FFC_9 *)owner_sprite)->unk_08, owner_sprite, spawn_offset, 0) != 0) {
                    ((S_80172FFC_7 *)effect_motion)->unk_02 = (u16) (((S_80172FFC_7 *)effect_motion)->unk_02 + spawn_offset[0]);
                    ((S_80172FFC_7 *)effect_motion)->unk_06 = (u16) (((S_80172FFC_7 *)effect_motion)->unk_06 + spawn_offset[1]);
                    ((S_80172FFC_7 *)effect_motion)->unk_0A = (u16) (((S_80172FFC_7 *)effect_motion)->unk_0A + spawn_offset[2]);
                }
                ((S_80172FFC_7 *)effect_motion)->unk_14 = (s32) (((0xD - (s16) ((S_80172FFC_0 *)action)->unk_96) << 0x11) + 0xFFE80000);
                ((S_80172FFC_4 *)effect_data)->unk_B4 = 0xC000;
                ((S_80172FFC_7 *)effect_motion)->unk_0C = (s32) (((S_80172FFC_10 *)(&directions[((u16) ((S_80172FFC_4 *)effect_data)->unk_94 >> 7) & 0x1C]))->unk_00 << 0x11);
                ((S_80172FFC_7 *)effect_motion)->unk_10 = (s32) (((S_80172FFC_10 *)(&directions[((u16) ((S_80172FFC_4 *)effect_data)->unk_94 >> 7) & 0x1C]))->unk_02 << 0x11);
                random_value = rand();
                velocity_base = ((S_80172FFC_7 *)effect_motion)->unk_0C + 0xFFFE0000;
                velocity_base += (random_value & 0x3FFF) << 4;
                ((S_80172FFC_7 *)effect_motion)->unk_0C = velocity_base;
                random_value = rand();
                velocity_base = ((S_80172FFC_7 *)effect_motion)->unk_10 + 0xFFFE0000;
                velocity_base += (random_value & 0x3FFF) << 4;
                ((S_80172FFC_7 *)effect_motion)->unk_10 = velocity_base;
                random_value = rand();
                velocity_base = 0xFFF80000;
                vertical_speed = ((S_80172FFC_7 *)effect_motion)->unk_14;
                vertical_speed += velocity_base;
                vertical_speed += (random_value & 0x3FFF) << 6;
                ((S_80172FFC_7 *)effect_motion)->unk_14 = vertical_speed;
                position[0] = ((S_80172FFC_7 *)effect_motion)->unk_02;
                position[1] = ((S_80172FFC_7 *)effect_motion)->unk_06;
                position[2] = ((S_80172FFC_7 *)effect_motion)->unk_0A;
                effect_depth = func_80065420(position_ptr, screen_pos, &projection_aux, &projection_flags);
                position[0] = ((S_80172FFC_3 *)motion)->unk_02;
                position[1] = ((S_80172FFC_3 *)motion)->unk_06;
                position[2] = ((S_80172FFC_3 *)motion)->unk_0A;
                ((S_80172FFC_6 *)effect_sprite)->unk_06 = (s16) ((effect_depth - func_80065420(position_ptr, screen_pos, &projection_aux, &projection_flags)) - (D_800DCECC[((s32) (D_80083228 + (s16) ((S_80172FFC_4 *)effect_data)->unk_94 + 0x100) >> 9) & 7] * 2));
            }
            next_count = spawn_count + 1;
            spawn_count = next_count;
        } while (next_count < 2);
    }
    goto done;

finish:
    if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(actor, 0x100);
        ((S_80172FFC_0 *)action)->unk_8C = &D_80171760;
        D_8008346C = 0;
        func_800A4ACC(actor);
        ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v = (u16) (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x7FFF);
    }

done:
    return;
}
