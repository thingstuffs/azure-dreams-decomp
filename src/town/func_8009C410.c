#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388();                 /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80098928();        /* extern */
extern M2C_UNK D_800FE488;


typedef struct S_80099B70_0 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80099B70_0;   /* arg1 in func_80099B70 */

/* Advance the object's position and handle crossing the sampled limit. */
void func_80099B70(s32 context, S_80099B70_0 *object, M2C_UNK update_data) {
    s16 limit;

    object->unk_08.at00.v = (s32) (object->unk_08.at00.v + object->unk_14);
    limit = func_80095978(object, &D_800FE488);
    if (limit < object->unk_08.at02.v) {
        func_80095A94(object, limit, &D_800FE488);
        func_80098928(context, object, update_data);
        return;
    }
    func_80095388(object, limit);
}
