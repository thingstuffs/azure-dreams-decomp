#include "common.h"

typedef struct S_80098864_0 {
    s32 unk_00;
    u8 pad_04[0x3A];
    s16 unk_3E;
    u8 pad_40[0x34];
    void * unk_74;
} S_80098864_0;   /* arg1 in func_80098864; pointer addresses record offset 0x14 */

typedef struct S_80098864_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_80098864_1;   /* temp_a0 in func_80098864 */


typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80098B38();
M2C_UNK func_800990C8();
s32 func_8009C12C();
M2C_UNK func_8009C93C();
extern u16 D_80083460[];
extern s32 D_800E3D7C;

/* Processes a record and updates its linked state on success. */
s32 func_80098864(s32 request, void *record_data) {
    s32 record_id;
    S_80098864_1 *linked_record;

    D_80083460[5]--;
    record_id = ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_00;
    func_800990C8(record_data, request);
    func_8009C93C(record_data, record_id, ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_3E, 0, 0);
    if (func_8009C12C(record_data, record_id, ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_3E, 0) == 0) {
        return 0;
    }
    linked_record = ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_74;
    if (linked_record != 0) {
        linked_record->unk_60 = (s32) D_800E3D7C;
    }
    func_80098B38(request);
    return 1;
}
