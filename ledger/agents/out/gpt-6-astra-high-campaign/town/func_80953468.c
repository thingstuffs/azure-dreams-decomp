#include "common.h"
#include "m2c_compat.h"

typedef struct S_80020468_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80020468_1;   /* arg0 in func_80020468 */

typedef struct S_80020468_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80020468_2;   /* ((S_80020468_1 *)arg0)->unk_04 in func_80020468 */


typedef struct S_80020468_0 {
    u16 unk_00;
} S_80020468_0;   /* arg0 in func_80020468; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

/* Propagate bit 15 from the linked record to the record and global flags. */
void func_80020468(void *record) {
    if (((S_80020468_2 *)(((S_80020468_1 *)record)->unk_04))->unk_04 & 0x8000) {
        ((S_80020468_0 *)((u8 *)record - 0x2))->unk_00 = (u16) (((S_80020468_0 *)((u8 *)record - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
