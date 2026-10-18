#include "common.h"
#include "shared/object_node.h"


typedef void (*Callback)(void);

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, Callback);
extern void func_80045340(void);
extern s32 generate_random_value(void);
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern void D_8016AAA4(void);
extern void D_8016DFB8(void);
extern void D_8016E000(void);
extern void D_8016AF68(void);


typedef struct S_8016A898_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    union { u32 u32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_8016A898_0;   /* result in copy_part_state */

typedef struct S_8016A898_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8016A898_1;   /* motion in copy_part_state */

typedef struct S_8016A898_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8016A898_2;   /* tail_entity in copy_part_state */

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *copy_part_state(s16 spawn_flags, s16 param_a, s16 param_b, s32 param_c)
{
    register void *result;
    void *object;
    S_8016A898_1 *motion;
    s8 held_a;
    s16 held_b;
    s32 held_c;
    void *tail_actor;
    void *state_data;
    S_8016A898_2 *tail_entity;
    void *part_data;
    s32 value;
    u16 tail_flags;

    held_a = param_a;
    result = 0;
    held_c = param_c;
    held_b = param_b;
    object = func_8003FD64(0x112, ((s32 *)(&D_80083498)));
    if (object != 0) {
        result = (u8 *)object + 0x20;
        (*(Callback *)((u8 *)object + 0x10)) = D_8016AAA4;
        ((S_8016A898_0 *)result)->unk_13 = 0x2B;
        func_8004491C(object, func_80045340);

        motion = (*(void * *)((u8 *)object + 8));
        motion->unk_0A = held_c;
        part_data = (*(void * *)((u8 *)object + 0xC));
        (*(u8 *)((u8 *)((void *)part_data) + 0x25)) = held_b;
        (*(Callback *)((u8 *)((void *)part_data) + 0x2C)) = D_8016DFB8;
        (*(u8 *)((u8 *)((void *)part_data) + 0x24)) = held_a;
        state_data = result;

        if ((spawn_flags & 3) == 1) {
            ((S_8016A898_0 *)result)->unk_14.u32 |= 0x6000;
            ((S_8016A898_0 *)result)->unk_1C |= 0x6000;
            ((S_8016A898_0 *)result)->unk_98 |= 0x4000;
        } else {
            if ((spawn_flags & 3) >= 2) {
                ((S_8016A898_0 *)result)->unk_14.u32 |= 0x2000;
                ((S_8016A898_0 *)result)->unk_1C |= 0x2000;
                ((S_8016A898_0 *)result)->unk_98 |= 0x4000;
            } else {
                if (((spawn_flags & -4) << 16) == 0 &&
                    !(((S_8016A898_0 *)result)->unk_14.u32 & 0x200)) {
                    if (generate_random_value() & 1) {
                        ((S_8016A898_0 *)result)->unk_1C |= 0x200;
                        value = generate_random_value();
                        set_or_clear_actor_status_slot(result, 1, (value & 0x3F) | 0x20);
                        (*(Callback *)((u8 *)((void *)part_data) + 0x2C)) = D_8016E000;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, motion, (void *)part_data, spawn_flags);

        tail_actor = state_data;
        (*(u8 *)((u8 *)tail_actor + 0x9A)) = 0xFF;
        (*(s8 *)((u8 *)tail_actor + 0x9C)) = -1;
        (*(Callback *)((u8 *)tail_actor + 0x8C)) = D_8016AF68;
        tail_flags = (*(u16 *)((u8 *)((void *)part_data) + 0x14));
        tail_entity = (void *)part_data;
        tail_flags |= 0xC;
        tail_entity->unk_14 = tail_flags;
        (*(s16 *)((u8 *)tail_actor + 0xAA)) = ((S_8016A898_0 *)result)->unk_14.u16 & 7;
        try_move_actor_to_valid_position(tail_actor, motion, tail_entity, result);
    }
    return result;
}
