#include "common.h"

typedef struct S_8001B960_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001B960_0;   /* obj in func_8001B960 */

typedef struct S_8001B960_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001B960_1;   /* (index * 0x10) + ((S_8001B960_0 *)obj)->unk_10 in func_8001B960 */



extern u8 *D_8001E950;
extern s32 func_8001A73C(void);

/* Store the current handler in the object's table slot unless the global gate is set. */
s32 func_8001B960(S_8001B960_0 *obj, s32 index) {
    if (D_8001E950[5] == 0) {
        ((S_8001B960_1 *)((index * 0x10) + obj->unk_10))->unk_08 =
            func_8001A73C();
        return 0;
    }
    return 1;
}
