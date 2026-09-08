#include "common.h"
#include "m2c_compat.h"

void func_8003DB94(void *, void *, s32, void *);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_800BD688;
extern M2C_UNK D_800BD898;
extern M2C_UNK D_800E9E14;

typedef struct {
    s32 words[4];
} Copy16;

typedef struct {
    s32 words[2];
} Copy8;


typedef struct S_800BD980_0 {
    u8 pad_00[0xC];
    volatile u16 unk_0C;
    volatile u16 unk_0E;
    volatile u16 unk_10;
} S_800BD980_0;   /* temp_v1 in func_800BD980 */

typedef struct S_800BD980_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800BD980_1;   /* temp_a3 in func_800BD980 */

typedef struct S_800BD980_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BD980_2;   /* temp_a0 in func_800BD980 */

/* Creates a parent object and two linked render objects offset from the supplied position. */
s32 func_800BD980(void *source) {
    void *source_data;
    s32 child_index;
    s32 x_step;
    S_800BD980_2 *render_state;
    S_800BD980_1 *transform;
    void *object;
    S_800BD980_0 *origin;
    void *child_slot;
    M2C_UNK *child_handler;

    source_data = source;
    child_slot = NULL;
    object = func_8003FD64(0x202, &D_80083498);
    if (object != NULL) {
        child_slot = object + 0x20;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &D_800BD688;
        (*(Copy16 *)((u8 *)object + 0x28)) = (*(Copy16 *)((u8 *)source_data + 0));
        (*(Copy8 *)((u8 *)object + 0x38)) = (*(Copy8 *)((u8 *)source_data + 0x10));
    }
    child_index = 1;
    child_handler = &D_800BD898;
    x_step = 0x300000;
    child_slot = child_slot + 4;
    do {
        object = func_8003FD64(0x312, &D_80083498);
        if (object != NULL) {
            s32 motion_base;
            s32 color;
            u16 source_x_hi;
            u16 source_y_hi;
            s32 x_offset;
            s32 y_offset;
            s32 z_offset;

            func_8004491C(object, &D_80045340);
            motion_base = 0xFFF88000;
            color = 0x800000;
            transform = (*(void **)((u8 *)object + 8));
            color |= 0x8080;
            (*(M2C_UNK **)((u8 *)object + 0x10)) = child_handler;
            *(void **)child_slot = transform;
            render_state = (*(void **)((u8 *)object + 0xC));
            ASM_KEEP(render_state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            source_x_hi = (*(u16 *)((u8 *)source_data + 2));
            origin = object + 0x20;
            origin->unk_0C = source_x_hi;
            source_y_hi = (*(volatile u16 *)((u8 *)source_data + 6));
            origin->unk_0E = source_y_hi;
            origin->unk_10 = (*(volatile u16 *)((u8 *)source_data + 0xA));
            x_offset = x_step + 0x01400000;
            transform->unk_00 = (s32) ((*(s32 *)((u8 *)source_data + 0)) + x_offset);
            {
                s32 source_y;
                source_y = (*(s32 *)((u8 *)source_data + 4));
                y_offset = child_index << 0x15;
                transform->unk_04 = (s32) (source_y + y_offset);
            }
            z_offset = (child_index << 0x13) + 0xFF800000;
            transform->unk_08 = (s32) ((*(s32 *)((u8 *)source_data + 8)) + z_offset);
            ASM_KEEP_NV(motion_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            transform->unk_0C = (s32) (motion_base - (child_index << 0x10));
            render_state->unk_1E = 0x1000;
            render_state->unk_1C = 0x1000;
            render_state->unk_0C = color;
            func_8003DB94(render_state, &D_800E9E14, 0, transform);
        }
        x_step += 0xFFD00000;
        child_index -= 1;
        child_slot = (void *)((s8 *)child_slot - 4);
    } while (child_index >= 0);
    return 0;
}
