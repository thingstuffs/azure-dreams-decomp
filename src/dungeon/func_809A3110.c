#include "common.h"
#include "m2c_compat.h"

typedef struct S_80174910_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174910_6;   /* arg0 in func_80174910 */

typedef struct S_80174910_7 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80174910_7;   /* temp_v0 in func_80174910 */

typedef struct S_80174910_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174910_8;   /* ((S_80174910_6 *)arg0)->unk_08 in func_80174910 */

typedef struct S_80174910_9 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_80174910_9;   /* ((S_80174910_6 *)arg0)->unk_0C in func_80174910 */

typedef struct S_80174910_10 {
    u8 pad_00[0x10];
    s16 unk_10;
} S_80174910_10;   /* ((S_80174910_7 *)temp_v0)->unk_0C in func_80174910 */




void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_800672D8();              /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_801747B8;

typedef struct S_80174910_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
} S_80174910_0;   /* temp_v0 in func_80174910 */

typedef struct S_80174910_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x8];
    void * unk_18;
    void * unk_1C;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
} S_80174910_1;   /* temp_v1 in func_80174910 */

typedef struct S_80174910_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174910_2;   /* arg0 in func_80174910 */

typedef struct S_80174910_3 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_80174910_3;   /* temp_v1_2 in func_80174910 */

typedef struct S_80174910_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80174910_4;   /* var_v1 in func_80174910 */

typedef struct S_80174910_5 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80174910_5;   /* temp_v1_3 in func_80174910 */

/* Creates three linked objects and initializes their shared palette data. */
void func_80174910(S_80174910_2 *source, s32 effect_param) {
    u16 palette_rect[4];                                    /* compiler-managed */
    s16 next_palette_x;
    s32 object_index;
    u16 first_component;
    u16 second_component;
    u16 third_component;
    u16 clut_id;
    u8 entry_flags;
    u8 *texture_entry;
    void *object;
    S_80174910_1 *object_data;
    S_80174910_3 *scale_state;
    S_80174910_5 *render_state;
    void *object_callback;
    u8 *callback_page;

    object_index = 0;
    object_callback = &D_801747B8;
    callback_page = (u8 *) 0x80170000;
    do {
        object = func_8003FD64(0x12, source);
        object_data = object + 0x20;
        if (object != NULL) {
            ((S_80174910_0 *)object)->unk_10 = object_callback;
            object_data->unk_18 = (void *) source->unk_0C;
            object_data->unk_1C = (void *) source->unk_08;
            first_component = ((S_80174910_8 *)(((S_80174910_6 *)source)->unk_08))->unk_02;
            object_data->unk_24 = first_component;
            object_data->unk_22 = first_component;
            object_data->unk_20 = first_component;
            second_component = ((S_80174910_8 *)(((S_80174910_6 *)source)->unk_08))->unk_06;
            object_data->unk_2A = second_component;
            object_data->unk_28 = second_component;
            object_data->unk_26 = second_component;
            third_component = ((S_80174910_8 *)(((S_80174910_6 *)source)->unk_08))->unk_0A;
            object_data->unk_0C = effect_param;
            object_data->unk_34 = object_index;
            object_data->unk_30 = third_component;
            object_data->unk_2E = third_component;
            object_data->unk_2C = third_component;
            scale_state = ((S_80174910_0 *)object)->unk_0C;
            scale_state->unk_1E = 0x1000;
            scale_state->unk_1C = 0x1000;
            func_8004491C(object, &D_80045340);
            if (object_index == 0) {
                texture_entry = ((S_80174910_9 *)(((S_80174910_6 *)source)->unk_0C))->unk_08;
                do {
                    entry_flags = *texture_entry;
                    texture_entry += 0xC;
                } while (entry_flags & 0x20);
                texture_entry -= 0xC;
                ASM_KEEP(texture_entry);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                clut_id = ((S_80174910_4 *)texture_entry)->unk_06;
                palette_rect[3] = 1;
                palette_rect[2] = 0x10;
                palette_rect[0] = 0;
                palette_rect[1] = (s16) ((u32) (((clut_id & 0xFFC0) - 0x40) & 0xFFFF) >> 6);
                do {
                    func_800672D8((s16 *) palette_rect, callback_page + 0x5F70);
                    next_palette_x = palette_rect[0] + 0x10;
                    palette_rect[0] = next_palette_x;
                } while (next_palette_x < 0x100);
            }
            render_state = ((S_80174910_0 *)object)->unk_0C;
            render_state->unk_12 = (u16) (render_state->unk_12 - 0x40);
            ((S_80174910_10 *)(((S_80174910_7 *)object)->unk_0C))->unk_10 = 0x20;
        }
        object_index += 1;
    } while (object_index < 3);
}

/* MECHANISM: Explicit object and 0x80170000 page bases restore the s4/s3 holds
   and the exact 0x38 frame; one four-halfword array preserves every call-visible slot.
   A 32-bit outer counter removes sign extensions, and ASM_KEEP at the pointer
   decrement prevents lhu -6 folding, emitting retail's addiu -0xC; lhu +6 seam. */
