#include "common.h"
#include "m2c_compat.h"

typedef struct S_80099CE0_1 {
    u8 pad_00[0x44];
    void * unk_44;
} S_80099CE0_1;   /* arg0 in func_80099CE0 */

typedef struct S_80099CE0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80099CE0_2;   /* ((S_80099CE0_1 *)arg0)->unk_44 in func_80099CE0 */




M2C_UNK func_80094984();                 /* extern */
extern u8 D_80082660;
extern M2C_UNK D_80099790;

typedef struct S_80099CE0_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_80099CE0_0;   /* arg0 in func_80099CE0 */

/* Updates the object using its linked data, clears its slot flag, and resets its state. */
void func_80099CE0(S_80099CE0_0 *object) {
    func_80094984(((S_80099CE0_2 *)(((S_80099CE0_1 *)object)->unk_44))->unk_08, object);
    *((object->unk_40 * 8) + &D_80082660) = 0;
    object->unk_04 = &D_80099790;
    object->unk_0A = 0x20;
}
