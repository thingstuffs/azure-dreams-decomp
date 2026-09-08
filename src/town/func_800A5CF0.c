#include "common.h"

typedef struct S_800A3450_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800A3450_0;   /* object in func_800A3450 */

typedef struct S_800A3450_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A3450_1;   /* copy in func_800A3450 */

typedef struct S_800A3450_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A3450_2;   /* arg0 in func_800A3450 */

typedef struct S_800A3450_3 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x1E];
    s16 unk_42;
} S_800A3450_3;   /* result in func_800A3450 */


extern void *func_8003FD64(s32, void *);
extern u8 D_80083498[];
extern u8 D_800A34E0[];
extern u8 D_800A3508[];


void *func_800A3450(S_800A3450_2 *arg0, s16 arg1)
{
    S_800A3450_0 *object;
    S_800A3450_1 *copy;
    register void *result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    object = func_8003FD64(0x136, D_80083498);
    result = 0;
    if (object != 0) {
        copy = object->unk_08;
        copy->unk_00 = arg0->unk_00;
        copy->unk_04 = arg0->unk_04;
        result = object;
        copy->unk_08 = arg0->unk_08;
        ((S_800A3450_3 *)result)->unk_10 = D_800A34E0;
        ((S_800A3450_3 *)result)->unk_20 = D_800A3508;
        ((S_800A3450_3 *)result)->unk_42 = arg1;
    }
    return result;
}
