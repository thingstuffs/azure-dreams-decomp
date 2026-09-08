#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2B38();                          /* extern */
M2C_UNK func_800C4174();        
typedef struct S_800C3EAC_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C3EAC_0;   /* arg1 in func_800C3EAC */

/* extern */

/* Advance the object's fixed-point value and clamp it when it exceeds the limit. */
void func_800C3EAC(s32 context, S_800C3EAC_0 *object, M2C_UNK update_data) {
    object->unk_08.at00.v = (s32) (object->unk_08.at00.v + object->unk_14);
    if (func_800C2B38(object) < object->unk_08.at02.v) {
        object->unk_08.at02.v = func_800C2B38(object);
        func_800C4174(context, object, update_data);
        return;
    }
    func_80095388(object);
}
