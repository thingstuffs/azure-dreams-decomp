#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A6994_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x24];
    u16 unk_38;
} S_800A6994_0;   /* temp_a0 in func_800A6994 */

typedef struct S_800A6994_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A6994_1;   /* arg2 in func_800A6994 */

typedef struct S_800A6994_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A6994_2;   /* temp_v0 in func_800A6994 */

typedef struct S_800A6994_3 {
    u8 pad_00[0x72];
    u16 unk_72;
} S_800A6994_3;   /* arg0 in func_800A6994 */

typedef struct S_800A6994_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800A6994_4;   /* temp_v0_2 in func_800A6994 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8009BFD8();
M2C_UNK func_800A6328();
M2C_UNK func_800A6A6C();
M2C_UNK func_800C2E84();
extern u8 D_80083498[];
extern s32 D_80083780;
extern M2C_UNK D_800A5638;
extern s32 D_800D0C78;
extern M2C_UNK D_800D0D54;
extern s32 D_80100E24;

void func_800A6994(void *arg0, M2C_UNK arg1, void *arg2, M2C_UNK arg3) {
    u32 tail_value;
    u8 *temp_a0;
    s32 *temp_v0;
    s32 *temp_v0_2;

    temp_a0 = D_80083498;
    if (((S_800A6994_0 *)temp_a0)->unk_10 != &D_800A5638) {
        func_800A6328(&D_800D0D54, 0);
        D_800D0C78 = ((S_800A6994_1 *)arg2)->unk_00;
        temp_v0 = &D_800D0C78;
        (*(s32 *)((u8 *)temp_v0 + 4)) = ((S_800A6994_1 *)arg2)->unk_04;
        ((S_800A6994_2 *)temp_v0)->unk_08 = (*(s32 *)((u8 *)arg2 + 8));
        func_800C2E84(arg0, arg3, D_80100E24);
        func_8009BFD8(arg0, arg1, arg2, arg3);
        tail_value = ((S_800A6994_3 *)arg0)->unk_72;
        tail_value += 0x200;
        tail_value &= 0xFC00;
        ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800A6A6C();
        return;
    }
    temp_v0_2 = &D_80083780;
    ((S_800A6994_1 *)arg2)->unk_00 = D_80083780;
    ((S_800A6994_1 *)arg2)->unk_04 = ((S_800A6994_4 *)temp_v0_2)->unk_04;
    ((S_800A6994_1 *)arg2)->unk_08 = ((S_800A6994_4 *)temp_v0_2)->unk_08;
    ((S_800A6994_3 *)arg0)->unk_72 = ((S_800A6994_0 *)temp_a0)->unk_38;
}

/* MECHANISM: A held byte-pointer base for D_80083498 forces the retail two-register la,
   schedules the ra save and arg3-to-s2 move in their exact prologue/branch slots.
   A guarded v0 tail value plus ASM_TAILSLOT_PIN preserves the dead lhu/addiu/andi chain
   and sinks the mask into the func_800A6A6C sibcall delay slot. */
