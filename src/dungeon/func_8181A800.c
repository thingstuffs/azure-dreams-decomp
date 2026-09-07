#include "common.h"

typedef struct S_8181A800_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
} S_8181A800_0;   /* arg0 in BODY_NAME; pointer addresses record offset 0x2 */


typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef __mips__
static const u32 func_8181A800_bank[] __asm__("func_8181A800")
    __attribute__((section(".text.func_8181A800"), aligned(4))) = {
    0x80024BE8, 0x00000020, 0x00200020, 0x00200000,
    0x0020FFE0, 0x0000FFE0, 0xFFE0FFE0, 0xFFE00000,
    0xFFE00020, 0x00000000, 0x80024CE8, 0x80024D54,
    0x80024F94, 0x8002540C, 0x80025490, 0x800256E4,
    0x800257E8, 0x80025880, 0x8002581C,
};
__asm__(".globl func_8181A800\n.size func_8181A800, 192");
#define BODY_NAME func_8181A84C
#else
#define BODY_NAME func_8181A800
#endif

extern void func_800478B8(void *);
extern s16 D_80025914[9];
extern s32 D_800814A0[3];

#ifdef __mips__
static void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_8181A84C")));
#endif

static void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    s16 count;
    volatile s16 *flag;

    flag = D_80025914;
    count = (s16)((S_8181A800_0 *)((u8 *)arg0 - 0x2))->unk_04 - 1;
    flag[0] = 1;
    ((S_8181A800_0 *)((u8 *)arg0 - 0x2))->unk_04 = count;
    func_800478B8(arg2);
    if (((S_8181A800_0 *)((u8 *)arg0 - 0x2))->unk_04 <= 0) {
        ((S_8181A800_0 *)((u8 *)arg0 - 0x2))->unk_00 =
            (u16)(((S_8181A800_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] |= 0x8000;
    }
}
