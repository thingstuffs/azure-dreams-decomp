#include "common.h"
#include "m2c_compat.h"

s32 func_80056F14();
extern M2C_UNK D_80082FF4;
extern M2C_UNK D_80083060;
extern M2C_UNK D_8008306C;

typedef struct S_8001C698_0 {
    u8 pad_00[0x1B8];
    s32 * unk_1B8;
    M2C_UNK ** unk_1BC;
} S_8001C698_0;   /* arg0 in func_8001C698 */

typedef struct S_8001C698_1 {
    u8 pad_00[0x1C0];
    void ** unk_1C0;
    u8 pad_1C4[0xC];
    void ** unk_1D0;
    u8 pad_1D4[0xC];
    void ** unk_1E0;
    u8 pad_1E4[0xC];
    void ** unk_1F0;
} S_8001C698_1;   /* var_a0 in func_8001C698 */

/* Initializes an object's value and four sets of shared and per-entry pointers. */
void func_8001C698(void *object) {
    s32 entry_offset;
    s32 slot_index;
    void *shared_data_a;
    void *shared_data_b;
    void *object_data;
    void *slot_cursor;

    *((S_8001C698_0 *)object)->unk_1B8 = func_80056F14(4);
    *((S_8001C698_0 *)object)->unk_1BC = &D_80082FF4;
    slot_index = 0;
    shared_data_a = &D_80083060;
    shared_data_b = &D_8008306C;
    object_data = object + 4;
    entry_offset = 0x90;
    slot_cursor = object;
    do {
        *((S_8001C698_1 *)slot_cursor)->unk_1C0 = shared_data_a;
        *((S_8001C698_1 *)slot_cursor)->unk_1D0 = shared_data_b;
        *((S_8001C698_1 *)slot_cursor)->unk_1E0 = object_data;
        *((S_8001C698_1 *)slot_cursor)->unk_1F0 = object + entry_offset;
        entry_offset += 0x3C;
        slot_index += 1;
        slot_cursor += 4;
    } while (slot_index < 4);
}
