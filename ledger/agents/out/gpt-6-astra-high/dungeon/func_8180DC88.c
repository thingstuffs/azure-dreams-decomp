#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 words[3];
} TableEntry;

extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_80026680[3];
extern TableEntry D_80028820[];
extern s32 D_80083498[3];
extern s32 D_800CEEFC[3];
extern u8 D_800DDC40[9];

typedef struct S_80026C88_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80026C88_0;   /* callee_arg in func_80026C88 */

typedef struct S_80026C88_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80026C88_1;   /* temp_v0 in func_80026C88 */

typedef struct S_80026C88_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xE];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x42];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
} S_80026C88_2;   /* temp_a3 in func_80026C88 */

typedef struct S_80026C88_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80026C88_3;   /* temp_a2 in func_80026C88 */

typedef struct S_80026C88_4 {
    u8 pad_00[0x8];
    TableEntry * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026C88_4;   /* temp_a0 in func_80026C88 */

typedef struct S_80026C88_5 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_80026C88_5;   /* var_a1 in func_80026C88 */

/* Create and link up to six objects with source-relative positions and initialized render data. */
void *func_80026C88(u16 x, u16 y, s32 z, void *source)
{
    u16 position_offset[3];
    s32 *callback;
    TableEntry *table_entry;
    s32 object_index;
    register S_80026C88_4 *render_data ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    S_80026C88_3 *coords;
    void *object;
    register void *point_cursor ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    S_80026C88_0 *source_object;   /* MATCH pin: load-bearing for the whole function shape */
    u16 *offset_ptr;
    register s32 saved_z ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    void *list_head;

    saved_z = z;
    list_head = NULL;
    source_object = source;
    offset_ptr = position_offset;
    position_offset[0] = position_offset[1] = 0;
    if (func_8003DE58(source_object->unk_08, source_object, offset_ptr, 0) == 0) {
        position_offset[2] = (0 - D_800DDC40[0]) + 0x10;
    }
    callback = D_80026680;
    object_index = 0;
    do { table_entry = D_80028820; } while (0);
    do {
        object = func_8003FD64(0x212, D_80083498);
        if (object != NULL) {
            s32 point_index;
            S_80026C88_2 *state;
            void *self_link;

            ((S_80026C88_1 *)object)->unk_10 = callback;
            func_8004491C(object, D_800CEEFC);
            state = object + 0x20;
            state->unk_1A = (s16) (x + position_offset[0]);
            state->unk_1E = (s16) (y + position_offset[1]);
            point_index = 0;
            state->unk_22 = (s16) (saved_z + position_offset[2]);
            coords = ((S_80026C88_1 *)object)->unk_08;
            coords->unk_02 = x;
            coords->unk_0E = x;
            coords->unk_06 = y;
            coords->unk_12 = y;
            coords->unk_0A = saved_z - 0x100;
            coords->unk_16 = saved_z - 0x100;
            render_data = ((S_80026C88_1 *)object)->unk_0C;
            point_cursor = state;
            render_data->unk_1E = 0x1000;
            render_data->unk_1C = 0x1000;
            self_link = object + 0x38;
            render_data->unk_08 = table_entry;
            render_data->unk_14 = (u16) (render_data->unk_14 | 0xC);
            ((S_80026C88_1 *)object)->unk_20 = self_link;
            state->unk_66 = 0x20;
            state->unk_6E = object_index;
            do {
                ((S_80026C88_5 *)point_cursor)->unk_24 = (u16) coords->unk_02;
                ((S_80026C88_5 *)point_cursor)->unk_26 = (u16) coords->unk_06;
                point_index += 1;
                ((S_80026C88_5 *)point_cursor)->unk_28 = (u16) coords->unk_0A;
                point_cursor += 8;
            } while (point_index < 8);
            state->unk_08 = list_head;
            list_head = object;
        }
        object_index += 1;
        table_entry += 1;
    } while (object_index < 6);
    ASM_KEEP(saved_z);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return object;
}

/* MECHANISM: position[3] owns the three halfword stack slots; s5/s6 hold arg2/list head.
   Guarded ABI/block pins preserve a1/a2 call setup and a3/t0/a0/a1 copy-loop roles.
   A split self_link computation and direct arg2-0x100 stores prevent unwanted hoisting. */
