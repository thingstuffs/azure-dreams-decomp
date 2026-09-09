#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024224;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE8E8;

typedef struct S_800242A0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_800242A0_0;   /* temp_v0 in func_800242A0 */

typedef struct S_800242A0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800242A0_1;   /* temp_s0 in func_800242A0 */

typedef struct S_800242A0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800242A0_2;   /* temp_v1 in func_800242A0 */

typedef struct S_800242A0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800242A0_3;   /* arg1 in func_800242A0 */

/* Allocate and initialize an object with the supplied value and coordinates. */
void *func_800242A0(s32 object_value, S_800242A0_3 *source_coords) {
    S_800242A0_1 *sprite;
    S_800242A0_0 *object;
    S_800242A0_2 *coords;
    register void *result ASM_REG("$2"); /* MATCH: Merge both return values in retail's v0 register. */

    object = func_8003FC64(0x212);
    if (object == NULL) {
        result = NULL;
    } else {
        object->unk_10 = &D_80024224;
        sprite = object->unk_0C;
        object->unk_2C = object_value;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        func_8003DB94(sprite, &D_800DE8E8, 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        func_8004491C(object, &D_80045340);
        coords = object->unk_08;
        coords->unk_02 = (u16)source_coords->unk_02;
        coords->unk_06 = (u16)source_coords->unk_06;
        coords->unk_0A = (u16)source_coords->unk_0A;
        result = object;
    }
    return result;
}
