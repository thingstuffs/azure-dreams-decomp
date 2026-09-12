#include "common.h"

typedef struct S_80171D64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80171D64_0;   /* created in func_80171D64 */

typedef struct S_80171D64_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x1];
    s8 unk_4B;
} S_80171D64_1;   /* result in func_80171D64 */

typedef struct S_80171D64_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80171D64_2;   /* position in func_80171D64 */

typedef struct S_80171D64_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80171D64_3;   /* (void *)reused_arg3 in func_80171D64 */

typedef struct S_80171D64_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80171D64_4;   /* (void *)reused_arg2 in func_80171D64 */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_80047784();
extern void func_800A48F0();
extern s32 func_800A6D30();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern s16 D_80083228;
extern u8 D_80083498[];
extern s8 D_800E2968;
extern u8 D_801720B4[];
extern u8 D_801724BC[];
extern u8 D_80175E24[];
extern u8 D_80175E2C[];
extern u8 D_80175E34[];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];

/* Creates an object and initializes its position, flags, and directional frame table. */
void *func_80171D64(s32 spawn_flags, s32 sprite_x, s32 sprite_y, s32 height)
{
    s32 saved_flags;
    void *result;
    s32 saved_x;
    s32 height_or_sprite;
    register s32 y_or_state ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 init_flags;
    void *object;
    register void *position ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 mode_or_object ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 kind_or_position;
    s32 alternate_kind;
    s32 state_flags;
    void *new_frames;
    s32 kind;
    u32 global_kind;
    u32 branch_flags;
    void *current_frames;
    void *default_frames;
    u8 *frame_table;
    s32 direction_index;

    saved_flags = spawn_flags;
    result = 0;
    mode_or_object = 0x112;
    saved_x = sprite_x;
    ASM_KEEP_DEP_NV(saved_x, mode_or_object);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    kind_or_position = (s32)D_80083498;
    ASM_KEEP_DEP_NV(kind_or_position, saved_x);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    height_or_sprite = height;
    ASM_KEEP_DEP_NV(height_or_sprite, kind_or_position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    y_or_state = sprite_y;
    object = func_8003FD64(mode_or_object, (void *)kind_or_position);
    init_flags = saved_flags;
    if (object == 0) {
        goto done;
    }

    result = (u8 *)object + 0x20;
    ((S_80171D64_0 *)object)->unk_10 = D_801720B4;
    ((S_80171D64_1 *)result)->unk_13 = 0x16;
    func_8004491C(object, &D_80045340);

    default_frames = D_80175E24;
    kind_or_position = 0xE;
    position = ((S_80171D64_0 *)object)->unk_08;
    alternate_kind = 0xF;
    ((S_80171D64_2 *)position)->unk_0A = height_or_sprite;
    height_or_sprite = (s32)((S_80171D64_0 *)object)->unk_0C;
    ASM_KEEP(height_or_sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    mode_or_object = saved_flags & 3;
    ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C = default_frames;
    ASM_KEEP(default_frames);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    state_flags = 0x20;
    ASM_KEEP(state_flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80171D64_3 *)((void *)height_or_sprite))->unk_25 = y_or_state;
    y_or_state = (s32)result;
    ((S_80171D64_3 *)((void *)height_or_sprite))->unk_24 = saved_x;
    ((S_80171D64_1 *)result)->unk_4B = state_flags;
    ((S_80171D64_1 *)result)->unk_48 = kind_or_position;
    ((S_80171D64_1 *)result)->unk_49 = alternate_kind;

    if (mode_or_object == 1) {
        (*(u32 *)((u8 *)result + 0x14)) |= 0x6000;
        branch_flags = ((S_80171D64_1 *)result)->unk_1C;
        global_kind = (u8)D_800E2968;
        ((S_80171D64_1 *)result)->unk_1C = branch_flags | 0x6000;
        if (global_kind >= 0xA) {
            if (global_kind < 0xD) {
                ((S_80171D64_1 *)result)->unk_48 = alternate_kind;
            } else {
                ((S_80171D64_1 *)result)->unk_48 = 0xD;
            }
        }
        goto setup;
    }

    if (mode_or_object >= 2) {
        ASM_KEEP(mode_or_object);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ((S_80171D64_1 *)result)->unk_14 |= 0x2000;
        ((S_80171D64_1 *)result)->unk_1C |= 0x2000;
        goto setup;
    }

    global_kind = (u8)D_800E2968;
    if (global_kind < 0xA) {
        ((S_80171D64_1 *)result)->unk_48 = kind_or_position;
    } else if (global_kind < 0xD) {
        ((S_80171D64_1 *)result)->unk_48 = alternate_kind;
    } else {
        ((S_80171D64_1 *)result)->unk_48 = 0xD;
    }

    if (((init_flags & ~3) << 16) == 0) {
        mode_or_object = (s32)object;
        ASM_KEEP_NV(mode_or_object);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (!(((S_80171D64_1 *)result)->unk_14 & 0x200)) {
            kind_or_position = (s32)position;
            ASM_KEEP(kind_or_position);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            state_flags = func_800A6D30((void *)mode_or_object, (void *)kind_or_position);
            mode_or_object = (s32)object;
            if (state_flags & 1) {
                func_800A48F0(result, 1,
                    (func_800A6D30((void *)mode_or_object) & 0x3F) | 0x20);
                kind = ((S_80171D64_1 *)result)->unk_48;
                if (kind == 0xE) {
                    goto callback_e;
                }
                if (kind < 0xF) {
                    if (kind == 0xD) {
                        goto callback_d;
                    }
                    goto setup;
                }
                if (kind == 0xF) {
                    goto callback_f;
                }
                goto setup;

callback_d:
                current_frames = ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C;
                new_frames = D_80175E54;
                goto callback_compare;
callback_e:
                current_frames = ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C;
                new_frames = D_80175E5C;
                goto callback_compare;
callback_f:
                current_frames = ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C;
                new_frames = D_80175E64;
callback_compare:
                if (current_frames != new_frames) {
                    ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C = new_frames;
                }
            } else {
                goto setup_args_ready;
            }
        } else {
            kind_or_position = (s32)position;
            goto setup_args2_ready;
        }
    }

setup:
    mode_or_object = (s32)object;
setup_args_ready:
    kind_or_position = (s32)position;
setup_args2_ready:
    func_800A9C18((void *)mode_or_object, (void *)kind_or_position, (void *)height_or_sprite,
        (s16)init_flags);
    ((S_80171D64_4 *)((void *)y_or_state))->unk_9A = 0xFF;
    ((S_80171D64_4 *)((void *)y_or_state))->unk_9C = -1;
    ((S_80171D64_4 *)((void *)y_or_state))->unk_8C = D_801724BC;
    func_800AA36C((void *)y_or_state, position, (void *)height_or_sprite, result);

    kind = ((S_80171D64_1 *)result)->unk_48;
    if (kind == 0xE) {
        goto select_e;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto select_d;
        }
        return result;
    }
    if (kind == 0xF) {
        goto select_f;
    }
    return result;

select_d:
    current_frames = ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C;
    frame_table = D_80175E24;
    if (current_frames == frame_table) {
        goto done;
    }
    goto table_store;
select_e:
    current_frames = ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C;
    frame_table = D_80175E2C;
    if (current_frames == frame_table) {
        goto done;
    }
    goto table_store;
select_f:
    current_frames = ((S_80171D64_3 *)((void *)height_or_sprite))->unk_2C;
    frame_table = D_80175E34;
    if (current_frames == frame_table) {
        goto done;
    }
table_store:
    (*(void * *)((u8 *)((void *)height_or_sprite) + 0x2C)) = frame_table;
    direction_index = ((D_80083228 + ((S_80171D64_1 *)result)->unk_2A + 0x100) >> 9) & 7;
    func_80047784((void *)height_or_sprite,
        *(u8 *)((u32)direction_index + (u32)frame_table),
        0);
done:
    return result;
}
