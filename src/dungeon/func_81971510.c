#include "common.h"

#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern void *D_80024008[];
extern s16 D_80025FF4;
extern s32 D_800814A0;
extern void func_80024D80(void) __attribute__((noreturn));

void func_81971510(void *arg0, s32 arg1, void *arg2)
{
    u8 *arg1_ptr;
    u16 counter;
    s32 index;
    register u8 *page ASM_REG("$4");   /* MATCH pin: keeps a constant in a register as retail does */
    u8 *arg2_ptr;
    u8 *table_page;
    u8 *flags_page;
    u16 value;
    s32 temp_v0;
    static void *const jt_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_default
    };

    arg1_ptr = (u8 *)arg0;
    arg2_ptr = (u8 *)arg2;
#ifdef NON_MATCHING
    page = (u8 *)&D_80025FF4 - 0x5FF4;
#else
    page = (u8 *)0x80020000;
#endif
    ASM_KEEP(page);   /* MATCH pin: retail delay-slot fill depends on it */
    counter = U16_AT(arg1_ptr, 0x38);
    *(s16 *)(page + 0x5FF4) = 1;
    counter--;
    U16_AT(arg1_ptr, 0x38) = counter;
    index = (u32)(s16)counter;
    if ((u32)index >= 20U) {
        goto case_default;
    }
    table_page = (u8 *)D_80024008;
    (void)jt_keep;
    goto *((void **)table_page)[(u32)index];

case_0:
    temp_v0 = 0x20;
    ASM_TAILSLOT_PIN_TIED(temp_v0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80024D80();
case_1:
    temp_v0 = 0x35;
    ASM_TAILSLOT_PIN_TIED(temp_v0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80024D80();
case_2:
    temp_v0 = 0x50;
    ASM_TAILSLOT_PIN_TIED(temp_v0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80024D80();
case_3:
    temp_v0 = 0x65;
    ASM_TAILSLOT_PIN_TIED(temp_v0);   /* MATCH pin: retail delay-slot contents depend on it */
    func_80024D80();
case_4:
    value = 0x80;
    U8_AT(arg2_ptr, 0x0E) = value;
    U8_AT(arg2_ptr, 0x0D) = value;
    U8_AT(arg2_ptr, 0x0C) = value;

case_default:
    value = U16_AT(arg2_ptr, 0x1A) + 400;
    U16_AT(arg2_ptr, 0x1A) = value;
    if (S16_AT(arg1_ptr, 0x38) > 0) {
        return;
    }
#ifdef NON_MATCHING
    flags_page = (u8 *)&D_800814A0 - 0x14A0;
#else
    flags_page = (u8 *)0x80080000;
#endif
    value = U16_AT((u8 *)arg1_ptr - 2, 0) | 0x8000;
    U16_AT((u8 *)arg1_ptr - 2, 0) = value;
    *(u32 *)(flags_page + 0x14A0) |= 0x8000;
}
