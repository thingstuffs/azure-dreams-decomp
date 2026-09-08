#include "common.h"
#include "records/Rec_func_800B15B8_arg0.h"





typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004E99C();


typedef struct S_800B15B8_1 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x24];
    s32 * unk_38;
    u8 pad_3C[0x10];
    s32 * unk_4C;
    u8 pad_50[0x10];
    s32 * unk_60;
} S_800B15B8_1;   /* var_s0 in func_800B15B8 */

/* Resets five slots and clears their associated resource handles. */
void func_800B15B8(Rec_func_800B15B8_arg0 *owner) {
    register void *slot_cursor ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 slot_index;

    slot_index = 0;
    slot_cursor = owner->unk_CC;
    do {
        *((S_800B15B8_1 *)slot_cursor)->unk_10 = 0;
        slot_index += 1;
        func_8004E99C(*((S_800B15B8_1 *)slot_cursor)->unk_38);
        *((S_800B15B8_1 *)slot_cursor)->unk_38 = 0;
        func_8004E99C(*((S_800B15B8_1 *)slot_cursor)->unk_4C);
        *((S_800B15B8_1 *)slot_cursor)->unk_4C = 0;
        func_8004E99C(*((S_800B15B8_1 *)slot_cursor)->unk_60);
        *((S_800B15B8_1 *)slot_cursor)->unk_60 = 0;
        slot_cursor += 4;
    } while (slot_index < 5);
}
