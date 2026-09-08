#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
extern M2C_UNK D_80025014;
extern M2C_UNK D_80079444;

typedef struct S_80025170_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80025170_0;   /* temp_v0 in func_80025170 */

typedef struct S_80025170_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80025170_1;   /* temp_s0 in func_80025170 */

/* Allocates an object and initializes its sprite and user data. */
void *func_80025170(s32 user_data) {
    S_80025170_1 *sprite;
    S_80025170_0 *object;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        sprite = object->unk_0C;
        object->unk_10 = &D_80025014;
        func_8003DB94(sprite, &D_80079444, 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0C = 0x2C808080;
        sprite->unk_10 = 0x20;
        sprite->unk_14 = (u16) (sprite->unk_14 | 0xC);
        object->unk_20 = user_data;
    }
    return object;
}
