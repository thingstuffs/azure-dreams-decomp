#include "modules/dungeon_ovl_1829800.h"

void func_80025014(void *motion_state, void *position, void *draw_state) {
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
    if ((target_y != current_y) || (((S_81809800_4 *)target_pos)->unk_04.at02.v
        != ((S_81809800_2 *)position)->unk_04.at02.v)) {
        ((EntityRec *)motion_state)->z.w.i = 2;
    }
    move_ticks = ((EntityRec *)motion_state)->z.w.i;
    if (move_ticks != 0) {
        ((S_81809800_2 *)position)->unk_00.at00.v = (s32) (((S_81809800_2 *)position)->unk_00.at00.v
            + ((s32) (((S_81809800_4 *)target_pos)->unk_00.at00.v
            - ((S_81809800_2 *)position)->unk_00.at00.v) / move_ticks));
        ((S_81809800_2 *)position)->unk_04.at00.v = (s32) (((S_81809800_2 *)position)->unk_04.at00.v
            + ((s32) (((S_81809800_4 *)target_pos)->unk_04.at00.v
            - ((S_81809800_2 *)position)->unk_04.at00.v) / (s16) ((EntityRec *)motion_state)->z.w.i));
        ticks_left = (u16) ((EntityRec *)motion_state)->z.w.i - 1;
        ((EntityRec *)motion_state)->z.w.i = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            ((S_81809800_2 *)position)->unk_00.at02.v = (s16) (u16) ((S_81809800_4 *)target_pos)->unk_00.at02.v;
            ((S_81809800_2 *)position)->unk_04.at02.v = (s16) (u16) ((S_81809800_4 *)target_pos)->unk_04.at02.v;
            ((EntityRec *)motion_state)->z.w.i = 0;
        }
    }
    func_800478B8(draw_state, target_y, target_pos, position);
    blink_ticks = (*(s16 *)D_80027156);
    blink_remaining = *(u16 *)&(*(s16 *)D_80027156);
    if (blink_ticks != 0) {
        *(u16 *)&(*(s16 *)D_80027156) = (u16) (blink_remaining - 1);
    }
    if ((*(u16 *)&(*(s16 *)D_80027156)) & 1) {
        ((S_81809800_6 *)draw_state)->unk_14 = (u16) (((S_81809800_6 *)draw_state)->unk_14 | 0x80);
    } else {
        ((S_81809800_6 *)draw_state)->unk_14 = (u16) (((S_81809800_6 *)draw_state)->unk_14 & 0xFF7F);
    }
}
