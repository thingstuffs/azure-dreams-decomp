#include "common.h"
#include "m2c_compat.h"

typedef struct S_800BB044_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x8];
    u16 unk_2C;
} S_800BB044_0;   /* temp_v0 in func_800BB044 */

typedef struct S_800BB044_1 {
    s32 unk_00;
    u8 pad_04[0x3E];
    u16 unk_42;
} S_800BB044_1;   /* arg0 in func_800BB044; pointer addresses record offset 0x18 */


void *func_8003FD64();                  /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_800BAF04;

/* Creates an object linked to the source data and copies its record fields. */
void func_800BB044(void *sourceData) {
    S_800BB044_0 *createdObject;

    createdObject = func_8003FD64(0x202, sourceData - 0x20);
    if (createdObject != NULL) {
        createdObject->unk_10 = &D_800BAF04;
        createdObject->unk_20 = sourceData;
        createdObject->unk_08 = (s32) ((S_800BB044_1 *)((u8 *)sourceData - 0x18))->unk_00;
        createdObject->unk_2C = (u16) ((S_800BB044_1 *)((u8 *)sourceData - 0x18))->unk_42;
        func_800A56E0(0x703);
    }
}
