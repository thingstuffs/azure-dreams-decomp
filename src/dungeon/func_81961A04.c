#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_FIELD_V(expr, type_ptr, offset) (*(volatile type_ptr)((s8 *)(expr) + (offset)))

void func_800272BC(void) __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80026DE4;
extern M2C_UNK D_800273B0;
extern M2C_UNK D_800CEEFC;

typedef struct S_81961A04_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_81961A04_0;   /* temp_v0 in func_81961A04 */

typedef struct S_81961A04_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81961A04_1;   /* temp_s3 in func_81961A04 */

typedef struct S_81961A04_2 {
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
} S_81961A04_2;   /* temp_v1 in func_81961A04 */

typedef struct S_81961A04_3 {
    u8 pad_00[0x38];
    u16 unk_38;
    u16 unk_3A;
    u16 unk_3C;
    u8 pad_3E[0xE];
    s16 unk_4C;
    u8 pad_4E[0x6];
    s16 unk_54;
} S_81961A04_3;   /* temp_a2 in func_81961A04 */

typedef struct S_81961A04_4 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s8 unk_0C;
    u8 pad_0D[0xF];
    u16 unk_1C;
    u16 unk_1E;
} S_81961A04_4;   /* temp_a1 in func_81961A04 */

/* Allocates and initializes objects at the supplied position across nine slots. */
void *func_81961A04(void *position)
{
    S_81961A04_1 *source_pos;
    s32 slot;
    M2C_UNK *object_handler;
    M2C_UNK *control_handler;
    register s32 last_slot ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    void *object;
    s32 slot_offset;
    register s32 control_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 control_scale ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    S_81961A04_4 *control;
    S_81961A04_3 *state;
    S_81961A04_2 *positions;

    source_pos = position;
    slot = 0;
    object_handler = &D_80026DE4;
    control_handler = &D_800273B0;
    last_slot = 8;
allocate_slot:
    object = func_8003FC64(2);
    if (object != NULL) {
        ((S_81961A04_0 *)object)->unk_10 = object_handler;
        func_8004491C(object, &D_800CEEFC);
        positions = ((S_81961A04_0 *)object)->unk_08;
        pos_x = source_pos->unk_02;
        state = object + 0x20;
        positions->unk_02 = pos_x;
        positions->unk_0E = pos_x;
        state->unk_38 = pos_x;
        pos_y = source_pos->unk_06;
        positions->unk_06 = pos_y;
        positions->unk_12 = pos_y;
        state->unk_3A = pos_y;
        pos_z = source_pos->unk_0A;
        positions->unk_0A = pos_z;
        positions->unk_16 = pos_z;
        state->unk_3C = pos_z;
        control = ((S_81961A04_0 *)object)->unk_0C;
        control->unk_08 = control_handler;
        if (slot != last_slot) {
            slot_offset = 0x200;
            ASM_TAILSLOT_PIN(slot_offset);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_800272BC();
            return (void *)0x200;
        }
        ASM_KEEP(last_slot);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        do { control->unk_1E = 0x800U; } while (0);
        slot_offset = (last_slot - slot) * 4;
        control_value = -0x80 - slot_offset;
        control_scale = M2C_FIELD_V(control, u16 *, 0x1E);
        control->unk_0C = (s8)control_value;
        control->unk_1C = control_scale;
        state->unk_54 = slot;
        if (slot == last_slot) {
            state->unk_54 = 7;
        }
        state->unk_4C = last_slot;
        goto next_slot;
    }
next_slot:
    slot += 1;
    if (slot < 9) {
        goto allocate_slot;
    }
    return object;
}
