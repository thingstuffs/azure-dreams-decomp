#include "common.h"

/* Unaligned 4-byte copy → lwl/lwr + swl/swr */
typedef struct {
    u32 v;
} __attribute__((packed)) UA32;

extern UA32 D_80028064;

s32 func_80025E54(void *arg0, s32 arg1, s32 arg2, void *arg3);
s32 func_80025ECC(void);
void func_80025F0C(void *arg0, s32 arg1);
void func_80025FFC(void *arg0, s32 arg1);

/*
 * Retail materializes &D_80028064 as lui $v0,0x8003 / addiu $a3,$v0,-32668
 * (two-reg la), keeps that pointer in $a3 for the unaligned copy and as the
 * 4th arg to func_80025E54, and leaves a0/a1 live so the call is effectively
 * func_80025E54(buffer, config, (mode==2), &D_80028064). Page base 0x80010000
 * is held in $s0 (lui only). The $a2 pin + ASM_KEEP after the copy stops
 * the (mode==2) xori/sltiu from floating above the unaligned block.
 */
/* Copies the initial word into the buffer and initializes state for the selected mode. */
void func_80026128(UA32 *buffer, s32 config, s32 mode) {
    register u32 source_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    UA32 *initial_word;
    s32 saved_mode;
    u8 *state_base;
    s16 is_mode_two;

    /* &D_80028064 == 0x80030000 - 32668 */
    source_page = 0x80030000;
    ASM_KEEP(source_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    initial_word = (UA32 *)(source_page - 32668);
    ASM_KEEP(initial_word);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    *buffer = *initial_word;

    saved_mode = mode;
    do {
        state_base = (u8 *)0x80010000;
    } while (0);
    is_mode_two = (saved_mode == 2);
    *(s16 *)(state_base + 0x208) = is_mode_two;
    *(s16 *)(state_base + 0x20A) = is_mode_two;
    *(s32 *)(state_base + 0x224) = *(s32 *)(state_base + 0x2D5C);
    *(s32 *)(state_base + 0x230) = func_80025E54(buffer, config, is_mode_two, initial_word);
    *(s32 *)(state_base + 0x228) = func_80025ECC();
    func_80025F0C(buffer, config);
    func_80025FFC(buffer, config);
}
