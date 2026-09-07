#include "common.h"
#include "m2c_compat.h"

typedef struct S_80815160_0_pre {
    u16 unk_00;
} S_80815160_0_pre;   /* the 0x2 bytes before arg0 in func_80815160, addressed as arg0[-1] */

typedef struct S_80815160_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_80815160_0;   /* arg0 in func_80815160 */

typedef struct S_80815160_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80815160_1;   /* temp_s1 in func_80815160 */


M2C_UNK func_80058588();               /* extern */
s32 func_80071424();                             /* extern */
extern s32 D_80084D5C;

void func_80815160(void *arg0) {
    void *temp_s1;

    temp_s1 = ((S_80815160_0 *)arg0)->unk_0C;
    if (((S_80815160_0 *)arg0)->unk_00 == 0) {
        func_80058588(*((S_80815160_0 *)arg0)->unk_08, func_80071424(((S_80815160_0 *)arg0)->unk_04), ((S_80815160_0 *)arg0)->unk_04);
        if (((S_80815160_1 *)temp_s1)->unk_1A & 8) {
            (*(u16 *)((u8 *)arg0 + -2)) = (u16) (((S_80815160_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_80084D5C |= 0x8000;
        }
    }
}
