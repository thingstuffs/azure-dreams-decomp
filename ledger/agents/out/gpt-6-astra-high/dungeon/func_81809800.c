#include "common.h"
#include "m2c_compat.h"

typedef struct S_81809800_0 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_81809800_0;   /* temp_v1 in BODY_NAME */

typedef struct S_81809800_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81809800_1;   /* ((index * 4) + temp_v1) in BODY_NAME */

typedef struct S_81809800_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_81809800_2;   /* arg1 in BODY_NAME */

typedef struct S_81809800_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81809800_3;   /* temp_a2_base in BODY_NAME */

typedef struct S_81809800_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_81809800_4;   /* temp_a2 in BODY_NAME */

typedef struct S_81809800_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_81809800_5;   /* arg0 in BODY_NAME */

typedef struct S_81809800_6 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81809800_6;   /* arg2 in BODY_NAME */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_8002715C[5];
extern s16 D_80027156;
extern void func_800478B8(void *, s16, void *, void *);

#ifdef __mips__
void func_80025000(void *, void *, void *);
static const u32 prefix_words[] __asm__("func_80025000")
    __attribute__((section(".text.func_80025000"), aligned(4))) = {
    0x8002527C, 0x800252C0, 0x800253B4, 0x800257F0, 0x80025844,
};
__asm__(
    ".globl func_80025000\n"
    ".type func_80025000,@function\n"
    ".size func_80025000,368\n");
#define BODY_NAME func_80025014
#else
#define BODY_NAME func_80025000
#endif

void BODY_NAME(void *motion_state, void *position, void *draw_state)
    __attribute__((section(".text.func_80025000")));
/* Move the position toward the selected target and update the blink flag. */
void BODY_NAME(void *motion_state, void *position, void *draw_state) {
    s16 move_ticks;
    s32 target_y;
    s16 ticks_left;
    void *target_pos;
    void *target_node;
    void *owner;
    s32 current_y;
    s32 node_index;
    s16 *update_counts;
    s16 blink_ticks;
    u16 blink_remaining;

    owner = (*(void **)((u8 *)motion_state + 0));
    node_index = ((S_81809800_0 *)owner)->unk_26;
    update_counts = D_8002715C;
    target_node = ((S_81809800_1 *)(((node_index * 4) + owner)))->unk_0C;
    current_y = ((S_81809800_2 *)position)->unk_00.at02.v;
    target_pos = ((S_81809800_3 *)target_node)->unk_08;
    target_y = ((S_81809800_4 *)target_pos)->unk_00.at02.v;
    update_counts[0] = (s16) ((u16) update_counts[0] + 1);
    if ((target_y != current_y) || (((S_81809800_4 *)target_pos)->unk_04.at02.v != ((S_81809800_2 *)position)->unk_04.at02.v)) {
        ((S_81809800_5 *)motion_state)->unk_0A = 2;
    }
    move_ticks = ((S_81809800_5 *)motion_state)->unk_0A;
    if (move_ticks != 0) {
        ((S_81809800_2 *)position)->unk_00.at00.v = (s32) (((S_81809800_2 *)position)->unk_00.at00.v + ((s32) (((S_81809800_4 *)target_pos)->unk_00.at00.v - ((S_81809800_2 *)position)->unk_00.at00.v) / move_ticks));
        ((S_81809800_2 *)position)->unk_04.at00.v = (s32) (((S_81809800_2 *)position)->unk_04.at00.v + ((s32) (((S_81809800_4 *)target_pos)->unk_04.at00.v - ((S_81809800_2 *)position)->unk_04.at00.v) / (s16) ((S_81809800_5 *)motion_state)->unk_0A));
        ticks_left = (u16) ((S_81809800_5 *)motion_state)->unk_0A - 1;
        ((S_81809800_5 *)motion_state)->unk_0A = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            ((S_81809800_2 *)position)->unk_00.at02.v = (s16) (u16) ((S_81809800_4 *)target_pos)->unk_00.at02.v;
            ((S_81809800_2 *)position)->unk_04.at02.v = (s16) (u16) ((S_81809800_4 *)target_pos)->unk_04.at02.v;
            ((S_81809800_5 *)motion_state)->unk_0A = 0;
        }
    }
    func_800478B8(draw_state, target_y, target_pos, position);
    blink_ticks = D_80027156;
    blink_remaining = *(u16 *)&D_80027156;
    if (blink_ticks != 0) {
        *(u16 *)&D_80027156 = (u16) (blink_remaining - 1);
    }
    if ((*(u16 *)&D_80027156) & 1) {
        ((S_81809800_6 *)draw_state)->unk_14 = (u16) (((S_81809800_6 *)draw_state)->unk_14 | 0x80);
    } else {
        ((S_81809800_6 *)draw_state)->unk_14 = (u16) (((S_81809800_6 *)draw_state)->unk_14 & 0xFF7F);
    }
}
