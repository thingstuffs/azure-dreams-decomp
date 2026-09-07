#include "common.h"
#include "m2c_compat.h"

void func_80024650(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_8003DB94(); /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_80024340;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DECF8;

typedef struct S_818A4CA0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818A4CA0_0;   /* temp_v0 in func_818A4CA0 */

typedef struct S_818A4CA0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
} S_818A4CA0_1;   /* arg0 in func_818A4CA0 */

typedef struct S_818A4CA0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4CA0_2;   /* arg1 in func_818A4CA0 */

typedef struct S_818A4CA0_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818A4CA0_3;   /* temp_s0 in func_818A4CA0 */

typedef struct S_818A4CA0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818A4CA0_4;   /* temp_s3 in func_818A4CA0 */

s32 func_818A4CA0(S_818A4CA0_1 *arg0, S_818A4CA0_2 *arg1, s16 arg2, s16 arg3) {
    register s32 result ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s16 temp_s0_2;
    u16 temp_v1;
    s32 shifted_arg3;
    s32 temp_v0_2;
    s32 var_s0;
    void *callback;
    S_818A4CA0_3 *temp_s0;
    S_818A4CA0_4 *temp_s3;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        callback = &D_80024340;
        ASM_KEEP(callback);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_818A4CA0_0 *)temp_v0)->unk_20 = arg0;
        arg0 = temp_v0 + 0x20;
        ((S_818A4CA0_0 *)temp_v0)->unk_10 = callback;
        arg0->unk_04 = arg2;
        arg0->unk_06 = (s16) (-6 - (rand() % 5));
        arg0->unk_08 = (u16) arg1->unk_02;
        arg0->unk_0A = (u16) arg1->unk_06;
        arg0->unk_0C = (u16) (arg1->unk_0A + 0x20);
        temp_s0 = ((S_818A4CA0_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x60;
        temp_s0->unk_0D = 0x60;
        temp_s0->unk_0C = 0x60;
        temp_s0->unk_12 = 0x7E07;
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x60);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        shifted_arg3 = (s32)arg3 << 0x10;
        func_8003DB94(temp_s0, &D_800DECF8, (s16) ((shifted_arg3 >> 0x10) % 5), shifted_arg3 >> 0x1F);
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        temp_s3 = ((S_818A4CA0_0 *)temp_v0)->unk_08;
        temp_v0_2 = rand();
        var_s0 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_s0 = temp_v0_2 + 0xFFF;
        }
        temp_s0_2 = temp_v0_2 - ((var_s0 >> 0xC) << 0xC);
        temp_s3->unk_02 = (s16) (arg0->unk_08 + ((s32) (func_800644B8(temp_s0_2) * 2) >> 8));
        temp_s3->unk_06 = (s16) (arg0->unk_0A + ((s32) (func_80064584(temp_s0_2) * 2) >> 8));
        temp_v1 = arg0->unk_0C;
        ASM_KEEP(temp_v1);   /* MATCH pin: retail keeps a computation the compiler would drop */
        result = (s32)temp_v0;
        ASM_KEEP(result);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_s3->unk_0A = (s16)temp_v1;
        func_80024650();
    }
    result = 0;
    return result;
}

/* MECHANISM: Reuse arg0 as the +0x20 base and pin only the allocated object in s2,
   giving the retail 0x28 frame and saved-role order; split shifted arg3 drives a3/a2.
   Value fences place the callback low half and tail lhu/move, while noreturn LEAD 18
   plus the failure-only s2 clobber preserves the object tail return and literal zero. */
