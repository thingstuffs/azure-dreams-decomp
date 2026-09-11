/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_808B3620_4 {
    u8 pad_00[0x64];
    union { M2C_UNK (*s)(u8 *, u8 *, s32, s8 *); M2C_UNK (*u)(u8 *, u8 *, s32); } unk_64;   /* accessed as both */
} S_808B3620_4;   /* *(volatile void **)(D_A0700000 + 0xF58) in func_808B3620 */


typedef struct S_808B3620_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_808B3620_0;   /* var_a2 in func_808B3620 */

typedef struct S_808B3620_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_808B3620_1;   /* var_a3 in func_808B3620 */

typedef struct S_808B3620_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_808B3620_2;   /* held_arg0 in func_808B3620 */

typedef struct S_808B3620_3 {
    u8 pad_00[0x6C];
    M2C_UNK (*unk_6C)(s32);
} S_808B3620_3;   /* *(volatile void **)(D_A0700000 + 0xF58) in func_808B3620 */

extern u8 D_A0700000[];
extern u8 D_A0700150[];
extern u8 D_A0700158[];
extern u8 D_A0700168[];
extern u8 D_A070017C[];

/* Copies overlay state into ov_work, prints both kinds, and emits a source mark. */
void func_808B3620(s8 *overlay_state) {
    s8 *kind_format;
    s8 *p = overlay_state;
    s32 *dst_words = (s32 *)(D_A0700000 + 0xF40);
    s32 *src_words = (s32 *)p;
    s32 *chunk_end = (s32 *)p + 12;
    s32 word_0;
    s32 word_1;
    register s32 word_2 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 word_3;

    do {
        ASM_KEEP_NV(dst_words);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        word_0 = ((S_808B3620_0 *)src_words)->unk_00;
        ASM_KEEP(word_0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        word_1 = ((S_808B3620_0 *)src_words)->unk_04;
        ASM_KEEP(word_1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        word_2 = ((S_808B3620_0 *)src_words)->unk_08;
        word_3 = ((S_808B3620_0 *)src_words)->unk_0C;
        ((S_808B3620_1 *)dst_words)->unk_00 = word_0;
        ((S_808B3620_1 *)dst_words)->unk_04 = word_1;
        ((S_808B3620_1 *)dst_words)->unk_08 = word_2;
        ((S_808B3620_1 *)dst_words)->unk_0C = word_3;
        do {
            src_words += 4;
        } while (0);
        ASM_KEEP(src_words);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        dst_words += 4;
    } while (src_words != chunk_end);
    do {
        ((S_808B3620_1 *)dst_words)->unk_00 = ((S_808B3620_0 *)src_words)->unk_00;
    } while (0);
    kind_format = D_A0700000 + 0x144;
    ((S_808B3620_4 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_64.s(kind_format, D_A0700150, ((S_808B3620_2 *)p)->unk_08, dst_words);
    ((S_808B3620_4 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_64.u(kind_format, D_A0700158, *(s32 *)(D_A0700000 + 0xF48));
    ((S_808B3620_4 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_64.u(D_A0700168, D_A070017C, 0x30);
    ((S_808B3620_3 *)(*(volatile void **)(D_A0700000 + 0xF58)))->unk_6C(0);
}
