#include "common.h"

typedef struct S_8009DA50_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8009DA50_0;   /* var_s1 in func_8009DA50 */

typedef struct S_8009DA50_1 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u16 unk_12;
    u8 pad_14[0x4];
    u16 unk_18;
    u16 unk_1A;
} S_8009DA50_1;   /* var_s4 in func_8009DA50 */

typedef struct S_8009DA50_2 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_8009DA50_2;   /* var_s0 in func_8009DA50 */


#ifdef NON_MATCHING
#define KEEP_PAIR(a, b) ((void)0)
#define KEEP_VALUE(v) ((void)0)
#else
#define KEEP_PAIR(a, b) __asm__("" : : "r"(a), "r"(b))
#define KEEP_VALUE(v) __asm__("" : : "r"(v))
#endif

extern s32 func_80033B2C();
extern s32 func_8008CC90();
extern s32 func_8009D424();
extern s16 D_8006ADD4;

/* Process eligible entries and mark those handled successfully as active. */
void func_8009DA50(u8 *entries, void *bounds, s32 origin_x, s32 origin_y)
{
    register s32 test_x ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 test_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 entry_x;
    register s32 entry_y ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *entry_data;
    register u8 *entry ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *quad ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 base_y;
    s32 base_x;
    register s32 flags ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    entry = entries;
    quad = bounds;
    base_x = origin_x;
    base_y = origin_y;
    flags = ((S_8009DA50_0 *)entry)->unk_01;
    if ((flags & 0xC0) != 0x80) {
        entry_data = entries + 1;
check_entry:
        if (*entry == 0) {
            if (!(flags & 1)) {
                if (func_80033B2C((*(s16 *)((u8 *)entry_data + 1)), flags) == 0) {
                    entry_data += 0x14;
                    flags = *entry_data;
                    entry += 0x14;
                    if ((flags & 0xC0) != 0x80) {
                        goto check_entry;
                    }
                    return;
                }
                goto process_entry;
            }
            if (func_80033B2C((*(s16 *)((u8 *)entry_data + 1)), flags) != 1) {
process_entry:
                test_x = base_x + (*(u16 *)((u8 *)entry_data + 0xF));
                test_y = base_y + (*(u16 *)((u8 *)entry_data + 0x11));
                entry_x = test_x;
                entry_y = test_y;
                if ((func_8008CC90(
                         (s16)(((S_8009DA50_1 *)quad)->unk_00 - test_x),
                         (s16)(((S_8009DA50_1 *)quad)->unk_02 - test_y),
                         (s16)(((S_8009DA50_1 *)quad)->unk_08 - test_x),
                         (s16)(((S_8009DA50_1 *)quad)->unk_0A - test_y),
                         (s16)(((S_8009DA50_1 *)quad)->unk_10 - test_x),
                         (s16)(((S_8009DA50_1 *)quad)->unk_12 - test_y),
                         (s16)(((S_8009DA50_1 *)quad)->unk_18 - test_x),
                         (s16)(((S_8009DA50_1 *)quad)->unk_1A - test_y)) != 0) ||
                    (D_8006ADD4 == 0xC) ||
                    (((S_8009DA50_2 *)entry_data)->unk_00 & 0x10)) {
                    if (func_8009D424(
                            (*(s32 *)((u8 *)entry_data + 0xB)),
                            ((S_8009DA50_2 *)entry_data)->unk_03,
                            ((S_8009DA50_2 *)entry_data)->unk_04,
                            ((S_8009DA50_2 *)entry_data)->unk_05,
                            ((S_8009DA50_2 *)entry_data)->unk_06,
                            ((S_8009DA50_2 *)entry_data)->unk_00 & 0x20,
                            (*(s32 *)((u8 *)entry_data + 7)),
                            (s16)entry_x,
                            (s16)entry_y,
                            entry) != 0) {
                        *entry = 1;
                    }
                    KEEP_PAIR(entry_x, entry_y);
                    if (!(((S_8009DA50_2 *)entry_data)->unk_00 & 0xC0)) {
                        do {
                            entry_data += 0x14;
                            entry += 0x14;
                        } while (!(((S_8009DA50_2 *)entry_data)->unk_00 & 0xC0));
                    }
                }
            }
            goto next_entry;
        }
next_entry:
        entry_data += 0x14;
        flags = *entry_data;
        entry += 0x14;
        if ((flags & 0xC0) != 0x80) {
            goto check_entry;
        }
    }
}
