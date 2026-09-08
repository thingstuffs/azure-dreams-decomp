#include "common.h"
#include "m2c_compat.h"

/* first_pass warm draft: compiles, best score 106 @ 2.7.2 */
#include "common.h"

typedef struct S_800500B4_4 {
    u8 pad_00[0x20];
    void * unk_20;
    void * unk_24;
} S_800500B4_4;   /* arg0 in func_800500B4 */

typedef struct S_800500B4_5 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_800500B4_5;   /* temp_v1 in func_800500B4 */

typedef struct S_800500B4_6 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x18];
    void * unk_20;
    u8 pad_24[0x4];
    void * unk_28;
} S_800500B4_6;   /* var_a3 in func_800500B4 */

typedef struct S_800500B4_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_7;   /* temp_a0 in func_800500B4 */

typedef struct S_800500B4_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_8;   /* ((S_800500B4_4 *)arg0)->unk_20 in func_800500B4 */

typedef struct S_800500B4_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_9;   /* ((S_800500B4_4 *)arg0)->unk_24 in func_800500B4 */

typedef struct S_800500B4_10 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800500B4_10;   /* ((S_800500B4_5 *)temp_v1)->unk_08 in func_800500B4 */

typedef struct S_800500B4_11 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800500B4_11;   /* ((S_800500B4_5 *)temp_v1)->unk_04 in func_800500B4 */

typedef struct S_800500B4_12 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800500B4_12;   /* ((S_800500B4_6 *)var_a3)->unk_20 in func_800500B4 */

typedef struct S_800500B4_13 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_800500B4_13;   /* ((S_800500B4_6 *)var_a3)->unk_04 in func_800500B4 */

typedef struct S_800500B4_14 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_800500B4_14;   /* ((S_800500B4_6 *)var_a3)->unk_28 in func_800500B4 */

typedef struct S_800500B4_15 {
    u8 pad_00[0x2];
    s8 unk_02;
} S_800500B4_15;   /* ((S_800500B4_7 *)temp_a0)->unk_04 in func_800500B4 */

typedef struct S_800500B4_16 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_800500B4_16;   /* ((S_800500B4_8 *)(((S_800500B4_4 *)arg0)->unk_20))->unk_04 in func_800500B4 */

typedef struct S_800500B4_17 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800500B4_17;   /* ((S_800500B4_9 *)(((S_800500B4_4 *)arg0)->unk_24))->unk_04 in func_800500B4 */

typedef struct S_800500B4_18 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_800500B4_18;   /* ((S_800500B4_12 *)(((S_800500B4_6 *)var_a3)->unk_20))->unk_08 in func_800500B4 */

typedef struct S_800500B4_19 {
    u8 pad_00[0x1];
    s8 unk_01;
    u8 pad_02[0x6];
    s16 unk_08;
} S_800500B4_19;   /* ((S_800500B4_13 *)(((S_800500B4_6 *)var_a3)->unk_04))->unk_04 in func_800500B4 */

typedef struct S_800500B4_20 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_800500B4_20;   /* ((S_800500B4_14 *)(((S_800500B4_6 *)var_a3)->unk_28))->unk_04 in func_800500B4 */


typedef struct S_800500B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_800500B4_0;   /* pArg1 in func_800500B4 */

typedef struct S_800500B4_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_800500B4_1;   /* arg0 in func_800500B4 */

typedef struct S_800500B4_2 {
    u8 pad_00[0xA4];
    u8 unk_A4;
} S_800500B4_2;   /* var_a2 in func_800500B4 */

typedef struct S_800500B4_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800500B4_3;   /* var_a3 in func_800500B4 */


/* Animate the selection cursor and the positions and brightness of six entries. */
void func_800500B4(S_800500B4_1 *widgets, void *anim_data) {
    S_800500B4_0 *anim;
    register s32 entry_index ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    register u8 *highlight_ptr ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    s32 start_index;
    s32 target_index;
    s32 frame;
    u8 old_highlight;
    u8 highlight;
    u8 next_highlight;
    S_800500B4_7 *entry_widget;
    S_800500B4_5 *cursor_widget;
    void *highlight_base;
    void *entry_base;
    s32 cursor_offset;

    anim = anim_data;
    start_index = anim->unk_18;
    cursor_offset = (s32) ((anim->unk_1C - start_index) * (anim->unk_14 << 4)) / (s32) anim->unk_10;
    cursor_offset = cursor_offset - 0x28;
    ((S_800500B4_16 *)(((S_800500B4_8 *)(((S_800500B4_4 *)widgets)->unk_20))->unk_04))->unk_0A.s = (s16) ((start_index << 4) + cursor_offset);
    ((S_800500B4_17 *)(((S_800500B4_9 *)(((S_800500B4_4 *)widgets)->unk_24))->unk_04))->unk_0A = (u16) ((S_800500B4_16 *)(((S_800500B4_8 *)(((S_800500B4_4 *)widgets)->unk_20))->unk_04))->unk_0A.u;
    cursor_widget = widgets->unk_20;
    ((S_800500B4_10 *)(cursor_widget->unk_08))->unk_08 = (s16) (((S_800500B4_11 *)(cursor_widget->unk_04))->unk_0A - 2);
    target_index = anim->unk_1C;
    entry_index = 0;
    entry_base = widgets;
    highlight_base = anim;
    ((S_800500B4_18 *)(((S_800500B4_12 *)(((S_800500B4_6 *)entry_base)->unk_20))->unk_08))->unk_04 = (s16) (-(target_index << 9) - ((s32) ((target_index - anim->unk_18) * -(anim->unk_14 << 9)) / (s32) anim->unk_10));
    do {
        highlight_ptr = (u8 *) ((s8 *) highlight_base + 0xA4);
        old_highlight = *highlight_ptr;
        if (entry_index == anim->unk_1C) {
            next_highlight = old_highlight + ((s32) (8 - old_highlight) / (s32) ((anim->unk_10 - anim->unk_14) + 1));
        } else {
            next_highlight = old_highlight;
            if (next_highlight != 0) {
                next_highlight -= 1;
            }
        }
        *highlight_ptr = next_highlight;
        highlight = ((S_800500B4_2 *)highlight_base)->unk_A4;
        ((S_800500B4_19 *)(((S_800500B4_13 *)(((S_800500B4_6 *)entry_base)->unk_04))->unk_04))->unk_08 = (s16) highlight;
        entry_index += 1;
        ((S_800500B4_20 *)(((S_800500B4_14 *)(((S_800500B4_6 *)entry_base)->unk_28))->unk_04))->unk_08 = (s16) (highlight + 0x1E);
        *((S_800500B4_14 *)(((S_800500B4_6 *)entry_base)->unk_28))->unk_04 = (((S_800500B4_2 *)highlight_base)->unk_A4 * 5) + 0x58;
        ((S_800500B4_20 *)(((S_800500B4_14 *)(((S_800500B4_6 *)entry_base)->unk_28))->unk_04))->unk_01 = (s8) ((((S_800500B4_2 *)highlight_base)->unk_A4 * 5) + 0x58);
        ((S_800500B4_20 *)(((S_800500B4_14 *)(((S_800500B4_6 *)entry_base)->unk_28))->unk_04))->unk_02 = (s8) ((((S_800500B4_2 *)highlight_base)->unk_A4 * 5) + 0x58);
        *((S_800500B4_13 *)(((S_800500B4_6 *)entry_base)->unk_04))->unk_04 = (((S_800500B4_2 *)highlight_base)->unk_A4 * 5) + 0x58;
        ((S_800500B4_19 *)(((S_800500B4_13 *)(((S_800500B4_6 *)entry_base)->unk_04))->unk_04))->unk_01 = (s8) ((((S_800500B4_2 *)highlight_base)->unk_A4 * 5) + 0x58);
        entry_widget = ((S_800500B4_3 *)entry_base)->unk_04;
        entry_base += 4;
        ((S_800500B4_15 *)(entry_widget->unk_04))->unk_02 = (s8) ((((S_800500B4_2 *)highlight_base)->unk_A4 * 5) + 0x58);
        highlight_base += 1;
    } while (entry_index < 6);
    frame = anim->unk_14;
    if (frame < anim->unk_10) {
        anim->unk_14 = (s32) (frame + 1);
    }
}
