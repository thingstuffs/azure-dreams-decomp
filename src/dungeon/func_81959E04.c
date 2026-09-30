#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(s32);                         /* extern */
void func_8004491C(void *, void *);                /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
extern M2C_UNK D_80025528;
extern u8 D_800C95C0[12];

typedef struct S_81959E04_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_81959E04_0;   /* obj in func_81959E04 */

typedef struct S_81959E04_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81959E04_1;   /* part in func_81959E04 */

typedef struct S_81959E04_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x28];
    s16 unk_30;
} S_81959E04_2;   /* info in func_81959E04 */

/* Spawn a ring of 32 spark objects around (x, y, z), each with the velocity of its angle step. */
void *func_81959E04(s16 x, s16 y, s16 z) {
    S_81959E04_1 *part;
    void *obj;
    s32 i;
    s32 scale;
    s32 sign_bits;
    S_81959E04_2 *info;

    i = 0;
    sign_bits = -0x800;
    scale = 0x20;
    do {
        obj = func_8003FC64(0x212);
        if (obj != NULL) {
            ((S_81959E04_0 *)obj)->unk_10 = &D_80025528;
            func_8004491C(obj, D_800C95C0);
            part = ((S_81959E04_0 *)obj)->unk_08;
            part->unk_02 = x;
            part->unk_06 = y;
            part->unk_0A = z;
            part->unk_0C = ((func_80064584(i * 0x80) & 0x800) ? (func_80064584(i * 0x80)
                | sign_bits) : (func_80064584(i * 0x80) & 0x7FF)) << 0xB;
            part->unk_10 = ((func_800644B8(i * 0x80) & 0x800) ? (func_800644B8(i * 0x80)
                | sign_bits) : (func_800644B8(i * 0x80) & 0x7FF)) << 0xB;
            part->unk_14 = 0xFFFE0000;
            info = obj + 0x20;
            (*(s16 *)((u8 *)obj + 0x20)) = scale;
            info->unk_02 = scale;
            info->unk_04 = 1;
            info->unk_06 = 0;
            info->unk_30 = scale;
        }
        i += 1;
    } while (i < 0x20);
    return obj;
}
