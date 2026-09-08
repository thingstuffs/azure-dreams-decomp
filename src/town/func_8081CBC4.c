#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026BC4_0_pre {
    u16 unk_00;
} S_80026BC4_0_pre;   /* the 0x2 bytes before arg0 in func_80026BC4, addressed as arg0[-1] */

typedef struct S_80026BC4_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_80026BC4_0;   /* arg0 in func_80026BC4 */

typedef struct S_80026BC4_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80026BC4_1;   /* temp_s1 in func_80026BC4 */


M2C_UNK func_800537D0();               /* extern */
s32 strlen();                             /* extern */
extern s32 D_800814A0[3];

/* Submits text for a zero-state entry and sets flags when requested by its configuration. */
void func_80026BC4(void *text_entry) {
    S_80026BC4_1 *text_config;

    text_config = ((S_80026BC4_0 *)text_entry)->unk_0C;
    if (((S_80026BC4_0 *)text_entry)->unk_00 == 0) {
        func_800537D0(*((S_80026BC4_0 *)text_entry)->unk_08, strlen(((S_80026BC4_0 *)text_entry)->unk_04), ((S_80026BC4_0 *)text_entry)->unk_04);
        if (text_config->unk_1A & 8) {
            ((S_80026BC4_0_pre *)text_entry)[-1].unk_00 = (u16) (((S_80026BC4_0_pre *)text_entry)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }
}
