#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

typedef struct S_801721C0_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801721C0_0;   /* arg0 in func_801721C0 */


s32 func_800A4ACC();                     /* extern */
s32 func_800AB1C0();                                /* extern */
void func_800AD594();            /* extern */
s32 func_800AD9B4();                /* extern */
extern M2C_UNK D_80170E54;

/* Updates object state after checking the target and conditionally clears its value. */
void func_801721C0(S_801721C0_0 *object, void *unused, void *check_data, void *target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(check_data, target) << 0x10) > 0) {
            object->unk_8C = &D_80170E54;
            if (dungeonStatus.flags & 0x80) {
                object->unk_90.at02.v = 0;
                object->unk_90.at00.v = 0;
            }
        }
    } else {
        if (dungeonStatus.flags & 0x80) {
            object->unk_90.at02.v = 0;
            object->unk_90.at00.v = 0;
        }
    }
}
