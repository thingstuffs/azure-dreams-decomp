#include "common.h"

typedef struct S_80024130_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_80024130_0;   /* temp_v0 in func_80024130 */

typedef struct S_80024130_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xB];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024130_1;   /* temp_s0 in func_80024130 */

typedef struct S_80024130_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024130_2;   /* temp_v1_2 in func_80024130 */

typedef struct S_80024130_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024130_3;   /* arg1 in func_80024130 */



extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 rand();
extern u8 D_80024048[9];
extern u8 D_80045340[9];
extern u8 D_800DE8E8[9];

/* Creates an object with the given context and position and randomized rotation. */
s32 func_80024130(s32 context, S_80024130_3 *position)
{
    s32 random_value;
    s32 rounded_value;
    S_80024130_1 *visual;
    S_80024130_0 *object;
    S_80024130_2 *object_pos;
    s32 pos_z;
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */

    object = func_8003FC64(0x212);
    if (object != 0) {
        object->unk_10 = D_80024048;
        visual = object->unk_0C;
        object->unk_2C = context;
        visual->unk_0E = 0x80;
        visual->unk_0D = 0x80;
        visual->unk_0C = 0x80;
        func_8003DB94(visual, D_800DE8E8, 0);
        visual->unk_1E = 0x1000;
        visual->unk_1C = 0x1000;
        rounded_value = rand();
        random_value = rounded_value;
        if (random_value < 0) {
            rounded_value = random_value + 0xFFF;
        }
        visual->unk_1A = random_value - ((rounded_value >> 0xC) << 0xC);
        func_8004491C(object, D_80045340);
        object_pos = object->unk_08;
        object_pos->unk_02 = position->unk_02;
        object_pos->unk_06 = position->unk_06;
        pos_z = position->unk_0A;
        result = object;
        object_pos->unk_0A = pos_z;
    } else {
        result = 0;
    }
    return (s32)result;
}
