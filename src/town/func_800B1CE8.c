#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF448_0 {
    void * unk_00;
    u8 pad_04[0xA4];
    void * unk_A8;
} S_800AF448_0;   /* arg0 in func_800AF448 */

typedef struct S_800AF448_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800AF448_1;   /* ((S_800AF448_0 *)arg0)->unk_00 in func_800AF448 */

typedef struct S_800AF448_2 {
    u8 pad_00[0x10];
    s32 unk_10;
    M2C_UNK ** unk_14;
} S_800AF448_2;   /* ((S_800AF448_0 *)arg0)->unk_A8 in func_800AF448 */




M2C_UNK func_8004CBFC();      /* extern */
extern M2C_UNK D_80071244;
extern M2C_UNK D_800792DC;


/* Update an enabled object's data and reset its referenced pointer. */
void func_800AF448(void *object) {
    if (((S_800AF448_1 *)(((S_800AF448_0 *)object)->unk_00))->unk_1C != 0) {
        func_8004CBFC(object + 0x1C, &D_800792DC, ((S_800AF448_2 *)(((S_800AF448_0 *)object)->unk_A8))->unk_10);
        *((S_800AF448_2 *)(((S_800AF448_0 *)object)->unk_A8))->unk_14 = &D_80071244;
    }
}
