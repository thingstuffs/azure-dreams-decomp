#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                      /* extern */
s16 func_800C2AE8();                          /* extern */
M2C_UNK func_800C4174();        /* extern */
typedef struct S_800C86EC_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C86EC_0;   /* arg1 in func_800C86EC */

/* extern */

/* Advance the object's position and stop its movement when it exceeds the limit. */
void func_800C86EC(s32 context, S_800C86EC_0 *object, M2C_UNK finish_arg) {
    object->unk_08.at00.v = (s32) (object->unk_08.at00.v + object->unk_14);
    if (func_800C2AE8(object) < object->unk_08.at02.v) {
        object->unk_08.at02.v = func_800C2AE8(object);
        object->unk_14 = 0;
        func_800C4174(context, object, finish_arg);
        return;
    }
    func_80095388(object);
}
