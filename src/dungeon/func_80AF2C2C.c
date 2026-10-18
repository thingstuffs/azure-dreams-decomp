#include "modules/dungeon_resource10_slot0.h"

void resolve_linked_attack_hits_and_particle_bursts(void *node, s32 target_x, s32 target_y, s32 target_height)
{
    R10_8017442C_OffsetTable offsets = (*(R10_8017442C_OffsetTable *)&D_80170854);
    void *head = node;
    register void *owner = head;
    s32 match_x = target_x;
    s32 match_y;
    register void *owner_data = ((R10_8017442C_S_801745BC_0_pre *)head)[-1].unk_04;
    void *next_link = ((R10_8017442C_S_801745BC_0 *)head)->unk_5C;
    void *position = ((R10_8017442C_S_801745BC_0_pre *)head)[-1].unk_00;
    u16 height_arg = target_height;
    s32 center_height;
    s32 low_height;

    node = (u8 *)next_link + 0x20;
    match_y = target_y;

    if (node != head) {
        center_height = (s32)(height_arg << 16) >> 16;
        low_height = center_height - 0x40;
        do {
            R10_8017442C_S_801745BC_2 *node_data = ((R10_8017442C_S_801745BC_1_pre *)node)[-1].unk_04;
            R10_8017442C_S_801745BC_3 *node_position = ((R10_8017442C_S_801745BC_1_pre *)node)[-1].unk_00;
            s32 height;

            if ((node_data->unk_24 == (match_x & 0xFFFF)) &&
                (node_data->unk_25 == (match_y & 0xFFFF))) {
                height = node_position->unk_0A;
                if (((center_height + 0x40) >= height) && (low_height < height)) {
                    if ((u32)(((R10_8017442C_S_801745BC_1 *)node)->unk_13 - 0x33) < 4U) {
                        u16 angle;
                        R10_8017442C_OffsetPair *offset;

                        ((R10_8017442C_S_801745BC_1 *)node)->unk_28 = 0;
                        ((R10_8017442C_S_801745BC_1 *)node)->unk_64 = -1;
                        func_800419EC((u16)(6), 0xC);
                        target_y = 0x601;
                        if (((R10_8017442C_S_801745BC_1 *)node)->unk_13 == 0x34) {
                            target_y = 0x80B;
                        }
                        play_sound_if_enabled(target_y);

                        angle = ((R10_8017442C_S_801745BC_4 *)owner)->unk_2A;
                        offset = (R10_8017442C_OffsetPair *)((u8 *)&offsets +
                            (((s16)angle >> 7) & 0x1C));
                        spawn_radial_particle_burst((s16)((s16)(((R10_8017442C_S_801745BC_5 *)position)->unk_02 + (offset->x * 32))),(s16)((s16)(((R10_8017442C_S_801745BC_5 *)position)->unk_06 +
                                  ((s32)(offset->y << 16) >> 11))),(s16)((s16)(((R10_8017442C_S_801745BC_5 *)position)->unk_0A - 0x20)),(s16)(((R10_8017442C_S_801745BC_4 *)owner)->unk_14),
                            (s32)(s16)angle);
                    } else {
                        resolve_attack_damage_and_effects(owner, owner_data,(s16)((s16)((R10_8017442C_S_801745BC_4 *)owner)->unk_2A),(s16)(1));
                    }
                }
            }
            node = (u8 *)((R10_8017442C_S_801745BC_1 *)node)->unk_5C + 0x20;
        } while (node != head);
    }

}
