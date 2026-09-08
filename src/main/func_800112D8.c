#include "common.h"
#include "m2c_compat.h"

typedef struct S_800242D8_0 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x2];
    s16 unk_04;
    s16 unk_06;
} S_800242D8_0;   /* arg0 in func_800242D8 */

typedef struct S_800242D8_1_pre {
    s8 unk_00;
} S_800242D8_1_pre;   /* the 0x1 bytes before var_v1 in func_800242D8, addressed as var_v1[-1] */

typedef struct S_800242D8_1 {
    s8 unk_00;
} S_800242D8_1;   /* var_v1 in func_800242D8 */


__asm__(".set D_80027FD0, 0x80027FD0");
extern u8 D_80027FD0[];

void *func_800242D8(u8 *arg0, u32 arg1, u32 arg2) {
    s32 var_a3;
    u8 *temp_v0;
    void *var_v1;
    s8 tag;
    s32 magicA;
    s32 magicB;
    register u8 *tableBase ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 half1;
    s32 half2;

    ((S_800242D8_0 *)arg0)->unk_01 = 0x81;
    ((S_800242D8_0 *)arg0)->unk_04 = 0x20;
    ((S_800242D8_0 *)arg0)->unk_06 = 0;
    arg0 = arg0 + 0xC;
    var_a3 = 0;
    tag = 0x38;
    magicA = 0x9CBCBC;
    magicB = 0x8C9C9C;
    half1 = (s32) ((arg1 >> 0x1F) + arg1) >> 1;
    half2 = (s32) ((arg2 >> 0x1F) + arg2) >> 1;
    __asm__("lui $2, %%hi(D_80027FD0)\n\taddiu %0, $2, %%lo(D_80027FD0)" : "=r"(tableBase));
    var_v1 = arg0 + 0xB;
    do {
        temp_v0 = (u8 *) (var_a3 + (s32) tableBase);
        var_a3 += 1;
        (*(s8 *)((u8 *)var_v1 + -0xA)) = tag;
        (*(s32 *)((u8 *)var_v1 + -7)) = magicA;
        (*(s32 *)((u8 *)var_v1 + 1)) = magicA;
        (*(s32 *)((u8 *)var_v1 + 5)) = magicA;
        (*(s32 *)((u8 *)var_v1 + 9)) = magicB;
        ((S_800242D8_1_pre *)var_v1)[-1].unk_00 = half1;
        ((S_800242D8_1 *)var_v1)->unk_00 = half2;
        var_v1 += 0x18;
        *arg0 = *temp_v0;
        arg0 += 0x18;
    } while (var_a3 < 4);
    ((S_800242D8_0 *)arg0)->unk_01 = 0x81;
    ((S_800242D8_0 *)arg0)->unk_04 = 0x20;
    ((S_800242D8_0 *)arg0)->unk_06 = 1;
    ((S_800242D8_0 *)arg0)->unk_00 = 0x80;
    return arg0 + 0xC;
}
