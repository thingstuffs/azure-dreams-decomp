#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800BB030;
extern M2C_UNK D_800BB218;

typedef struct S_800BB4A0_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800BB4A0_0;   /* temp_a0 in func_800BB4A0 */

typedef struct S_800BB4A0_1 {
    u8 pad_00[0x66];
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    u8 pad_6E[0x29];
    s8 unk_97;
} S_800BB4A0_1;   /* arg0 in func_800BB4A0 */

typedef struct S_800BB4A0_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800BB4A0_2;   /* arg1 in func_800BB4A0 */

/* Initializes an object's header and state, including its associated state value. */
void func_800BB4A0(void *objectState, S_800BB4A0_2 *associatedState) {
    S_800BB4A0_0 *objectHeader;

    objectHeader = objectState - 0x20;
    objectHeader->unk_10 = &D_800BB030;
    func_8004491C(objectHeader, &D_800BB218);
    ((S_800BB4A0_1 *)objectState)->unk_97 = 0x48;
    ((S_800BB4A0_1 *)objectState)->unk_68 = 0;
    ((S_800BB4A0_1 *)objectState)->unk_6C = 0;
    ((S_800BB4A0_1 *)objectState)->unk_66 = 0;
    associatedState->unk_08 = 0xFFA00000;
}
