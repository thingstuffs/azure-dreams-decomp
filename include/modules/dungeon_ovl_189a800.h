#ifndef DUNGEON_OVL_189A800_H
#define DUNGEON_OVL_189A800_H
#include "modules/dungeon_native_abi.h"

/* Record views shared by the mesh renderer and linked-record walker. */
typedef struct S_func_800241A8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_func_800241A8_2;

typedef struct S_func_800241A8_3 {
    u8 pad_00[0x8];
    void * unk_08;
    union {
        u32 as_u32_0C;
        struct {
            u8 pad_0C[0x3];
            u8 unk_0F;
        } as_u8_0F;
    } unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_func_800241A8_3;

typedef struct S_func_800241A8_4 {
    u8 pad_00[0x4E];
    u8 unk_4E;
    u8 pad_4F[0x9];
    union {
        s16 as_s16_58;
        u16 as_u16_58;
    } unk_58;
    union {
        s16 as_s16_5A;
        u16 as_u16_5A;
    } unk_5A;
    union {
        s16 as_s16_5C;
        u16 as_u16_5C;
    } unk_5C;
    union {
        s16 as_s16_5E;
        u16 as_u16_5E;
    } unk_5E;
    union {
        s16 as_s16_60;
        u16 as_u16_60;
    } unk_60;
    union {
        s16 as_s16_62;
        u16 as_u16_62;
    } unk_62;
    union {
        s16 as_s16_64;
        u16 as_u16_64;
    } unk_64;
    union {
        s16 as_s16_66;
        u16 as_u16_66;
    } unk_66;
    union {
        s16 as_s16_68;
        u16 as_u16_68;
    } unk_68;
    union {
        s16 as_s16_6A;
        u16 as_u16_6A;
    } unk_6A;
    union {
        s16 as_s16_6C;
        u16 as_u16_6C;
    } unk_6C;
    union {
        s16 as_s16_6E;
        u16 as_u16_6E;
    } unk_6E;
} S_func_800241A8_4;

void transform_and_queue_mesh_primitives(S_func_800241A8_4 *, S_func_800241A8_2 *, S_func_800241A8_3 *, s32);
/* Bank callbacks whose definitions precede their users in the native TU. */
void func_80024D40(void *object, s32 unused, void *target);
void advance_fading_effect_animation(void *effect_data, s32 unused_arg, void *color_data);
struct S_8187BE9C_1;
void create_object_offset(void *effect, s32 unused, struct S_8187BE9C_1 *primitive);
s32 decrement_object_counter(void *record, void *context, void *data);
s32 project_shaded_points_to_ordering_table(u8 *points, u8 *position, u8 *orientation);
void initialize_star_effect_sequence(void *state_data, void *source_data);
#endif
