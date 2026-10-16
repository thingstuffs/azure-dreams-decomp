#include "modules/dungeon_ovl_7f469800_p01.h"

/* Creates an effect at an offset position with randomized attributes and motion. */
void func_80171790(void *source, void *position) {
    T_80171790_S_80171790_5 *source_obj;
    T_80171790_S_80171790_4 *source_pos;
    s32 obj_or_angle;
    s32 data_or_speed;
    T_80171790_S_80171790_0 *effect_state;
    void *init_obj;
    T_80171790_S_80171790_3 *effect_pos;
    u8 random_byte_1;
    u8 random_byte_2;

    source_obj = source;
    source_pos = position;
    obj_or_angle = (s32) func_8003FC64(0x212);
    if (obj_or_angle != 0) {
        init_obj = (void *) obj_or_angle;
        effect_state = (void *) obj_or_angle + 0x20;
        effect_state->unk_18 = 6;
        effect_state->unk_1A = 6;
        ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_10 = &func_80170E2C;
        func_8004491C(init_obj, ((s32 *)func_80170CEC));
        data_or_speed = (s32) ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_10 = 0x60;
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_14 =
            (u16) (((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_14 | 0xC);
        effect_pos = ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_08;
        effect_pos->unk_02 = source_pos->unk_02;
        effect_pos->unk_06 = source_pos->unk_06;
        effect_pos->unk_0A =
            (s16) (source_pos->unk_0A - 0x50);
        data_or_speed = (s32) ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_0C;
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_1E = 0x1000;
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_1C = 0x1000;
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_0C = rand();
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_0D = rand();
        ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_0E = rand();
        ((T_80171790_S_80171790_1 *)((void *) obj_or_angle))->unk_20 =
            ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_0C;
        random_byte_1 = ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_0D;
        effect_state->unk_01 = random_byte_1;
        random_byte_2 = ((T_80171790_S_80171790_2 *)((void *) data_or_speed))->unk_0E;
        effect_state->unk_60 = 0;
        effect_state->unk_5C = 0;
        effect_state->unk_58 = 0;
        effect_state->unk_02 = random_byte_2;
        obj_or_angle = rand() & 0xFFF;
        data_or_speed =
            (source_obj->unk_AE * func_80064584(obj_or_angle)) >> 0xC;
        effect_state->unk_62 =
            (source_obj->unk_AE * func_800644B8(obj_or_angle)) >> 0xC;
        obj_or_angle = rand() & 0xFFF;
        effect_state->unk_5A =
            (data_or_speed * func_80064584(obj_or_angle)) >> 0xC;
        effect_state->unk_5E =
            (data_or_speed * func_800644B8(obj_or_angle)) >> 0xC;
    }
}

/* MECHANISM: The fixed s0/s1/s2 object roles leave natural argument holds to allocate as s4/s3,
   reproducing the 0x28 frame and prologue schedule; s0 holds object+0x20 across the body.
   Two scheduler seams retain the random_byte_1 load-delay nop,
       while a split random_byte_2 live range hoists its lbu. */
