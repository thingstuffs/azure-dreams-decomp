#include "common.h"



typedef s32 M2C_UNK;
typedef struct Copy24 {
    s32 words[6];
} Copy24;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8003DB94();
void *func_8003FD64();
M2C_UNK func_8004491C();
extern M2C_UNK D_8002457C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEC50;

typedef struct S_80024600_0 {
    u8 pad_00[0x8];
    Copy24 * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_80024600_0;   /* temp_v0 in func_80024600 */

typedef struct S_80024600_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024600_1;   /* temp_s0 in func_80024600 */

void *func_80024600(s32 *arg0, Copy24 *arg1) {
    s32 temp_arg0;
    S_80024600_1 *temp_s0;
    S_80024600_0 *temp_v0;
    Copy24 *temp_v1;
    register void *tail_result ASM_REG("$2"); /* MATCH: Keep the merged return value in v0 for the shared epilogue. */

    temp_v0 = func_8003FD64(0x212, (s8 *) arg0 - 0x20);
    if (temp_v0 == NULL) {
        tail_result = NULL;
    } else {
        temp_v0->unk_10 = &D_8002457C;
        temp_arg0 = *arg0;
        temp_s0 = temp_v0->unk_0C;
        temp_v0->unk_24 = 0;
        temp_v0->unk_20 = temp_arg0;
        temp_s0->unk_0C = 0x808080;
        temp_s0->unk_12 = 0x7DCF;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x60);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        func_8003DB94(temp_s0, &D_800DEC50, 0);
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = temp_v0->unk_08;
        *temp_v1 = *arg1;
        tail_result = temp_v0;
    }
    return tail_result;
}

/* MECHANISM: The seed already matched the 0x20 frame and s0/s2/s1 save order.
   A guarded tied $v0 zero stays live on the noreturn failure edge.
   LEAD 28 sinks its move into the converted j delay slot, closing word 14. */
