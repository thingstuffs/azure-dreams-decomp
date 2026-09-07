#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_800BF72C_3 {
    u8 pad_00[0xA0];
    void * unk_A0;
} S_800BF72C_3;   /* arg0 in func_800BF72C */

typedef struct S_800BF72C_4 {
    u8 pad_00[0x68];
    u16 unk_68;
} S_800BF72C_4;   /* ((S_800BF72C_3 *)arg0)->unk_A0 in func_800BF72C */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800BC574(void *, s32);
extern s32 D_80012D5C;
extern void *D_80089930[];

/* The final state reset is coupled to the non-overflow path.  This is a
 * defined source-level guard whose natural branch leader is the epilogue. */
typedef struct S_800BF72C_0 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_800BF72C_0;   /* arg0 in func_800BF72C */

typedef struct S_800BF72C_1 {
    s32 unk_00;
    s32 unk_04;
} S_800BF72C_1;   /* arg1 in func_800BF72C */

typedef struct S_800BF72C_2 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_800BF72C_2;   /* clock in func_800BF72C */

/* Advance the object through bounded movement phases and trigger a timed event. */
void func_800BF72C(S_800BF72C_0 *object, S_800BF72C_1 *position) {
    static void *const state_labels[] = {
        &&block_0, &&block_1, &&block_2, &&block_3, &&block_4
    };
    s32 event_pos[6];
    s16 move_state;
    s32 increased_x;
    s32 decreased_x;
    s32 decreased_y;
    s32 increased_y;
    s32 event_z;
    u16 linked_state;
    u32 state_index;
    u32 *clock_base;
    u32 ticks;

    linked_state = ((S_800BF72C_4 *)(((S_800BF72C_3 *)object)->unk_A0))->unk_68;
    if ((linked_state & 1) && object->unk_68 == 0)
        object->unk_68 = (s16)linked_state;
    move_state = object->unk_68;
    state_index = move_state;
    if (state_index >= 5) goto block_0;
    (void)state_labels;
    goto *D_80089930[state_index];

block_1:
    increased_y = position->unk_04 + 0x40000;
    position->unk_04 = increased_y;
    if (increased_y > 0x023FFFFF) {
        position->unk_04 = 0x02400000;
        goto block_15;
    }
    goto block_0;

block_2:
    increased_x = position->unk_00 + 0x40000;
    position->unk_00 = increased_x;
    if (increased_x == 0x10000000) {
        clock_base = (u32 *)0x80010000;
        ticks = ((S_800BF72C_2 *)clock_base)->unk_2D5C;
        if ((ticks % 1000U) == 777U) {
            event_pos[0] = 0x0FA00000;
            event_z = 0xFFF80000;
            event_pos[1] = position->unk_04;
            event_pos[2] = event_z;
            func_800BC574(event_pos, 0x200);
        }
    }
    if (position->unk_00 > 0x105FFFFF) {
        position->unk_00 = 0x10600000;
        goto block_18;
    }
    goto block_0;

block_3:
    decreased_x = position->unk_00 + 0xFFFC0000;
    position->unk_00 = decreased_x;
    if (decreased_x <= 0x0FA00000) {
        position->unk_00 = 0x0FA00000;
        goto block_15;
    }
    goto block_0;

block_15:
    object->unk_68 =
        (s16)((u16)object->unk_68 + 1);
    goto block_0;

block_4:
    decreased_y = position->unk_04 + 0xFFFC0000;
    position->unk_04 = decreased_y;
    if (decreased_y > 0x02300000)
        goto block_0;
    position->unk_04 = 0x02300000;
    object->unk_68 = 0;
    goto block_0;
block_18:
    object->unk_68 = 0;
block_0:
    return;
}
