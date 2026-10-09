/* Selector 72, retail file [0x19E092C, 0x19E095C); complete callable clone. */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002612C_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8002612C_1;   /* arg0 in func_8002612C */

typedef struct S_8002612C_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8002612C_2;   /* ((S_8002612C_1 *)arg0)->unk_08 in func_8002612C */


typedef struct S_8002612C_0 {
    s32 unk_00;
} S_8002612C_0;   /* arg0 in func_8002612C */

/* Sets the object entry address using a 22-byte stride. */
void func_8002612C(S_8002612C_0 *object, s16 entry_index) {
    object->unk_00 = (s32) (((S_8002612C_2 *)(((S_8002612C_1 *)object)->unk_08))->unk_0C + (entry_index * 0x16));
}
