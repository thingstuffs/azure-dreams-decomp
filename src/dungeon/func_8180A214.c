#include "modules/dungeon_ovl_1829800.h"

void dungeonUpdateDirectionalObjectFade(void *state_arg, void *buffer_arg, void *obj_arg)
{
    void *state;
    u16 update_count;
    s32 fade_ticks;
    void *buffer = buffer_arg;
    u16 render_flags;
    s8 phase;
    u8 fade_in_value;
    u8 fade_in_value_2;
    u8 fade_out_value;
    u8 current_phase;
    s16 unit_scale;
    s16 direction;
    void *owner;

    update_count = (*(u16 *)D_8002715C);
    state = state_arg;
    update_count++;
    (*(u16 *)D_8002715C) = update_count;
    phase = ((S_80025A14_0 *)state)->unk_72.s;
    switch (phase) {
    case 0:
        unit_scale = 0x1000;
        ((S_80025A14_1 *)buffer)->unk_02 = 0;
        ((S_80025A14_1 *)buffer)->unk_06 = 0;
        ((S_80025A14_1 *)buffer)->unk_0A = 0;
        ((S_80025A14_2 *)obj_arg)->unk_1E = unit_scale;
        ((S_80025A14_2 *)obj_arg)->unk_1C = unit_scale;
        ((S_80025A14_2 *)obj_arg)->unk_0E = 0;
        ((S_80025A14_2 *)obj_arg)->unk_0D = 0;
        ((S_80025A14_2 *)obj_arg)->unk_0C = 0;
        ((S_80025A14_2 *)obj_arg)->unk_28 = D_80082E80.unk_028;
        ((S_80025A14_2 *)obj_arg)->unk_14 = D_80082E80.unk_014 & 0xFFFC;
        ((S_80025A14_2 *)obj_arg)->unk_2C = D_800DD008;
        ((S_80025A14_2 *)obj_arg)->unk_14 |= 0x200;
        ((S_80025A14_0 *)state)->unk_73.s = 8;
        ((S_80025A14_0 *)state)->unk_72.s = ((S_80025A14_0 *)state)->unk_72.u + 1;
                        /* fall through */
    case 1:
        fade_ticks = (s32)((S_80025A14_0 *)state)->unk_73.s;
        if (fade_ticks != 0) {
            fade_in_value = ((S_80025A14_2 *)obj_arg)->unk_0E;
            fade_in_value += (0x40 - fade_in_value) / fade_ticks;
            ((S_80025A14_2 *)obj_arg)->unk_0E = fade_in_value;
            ((S_80025A14_2 *)obj_arg)->unk_0D = fade_in_value;
            ((S_80025A14_2 *)obj_arg)->unk_0C = fade_in_value;
        }
        fade_in_value_2 = ((S_80025A14_0 *)state)->unk_73.u - 1;
        ((S_80025A14_0 *)state)->unk_73.u = fade_in_value_2;
        if ((s8)fade_in_value_2 <= 0) {
            ((S_80025A14_2 *)obj_arg)->unk_0E = 0x40;
            ((S_80025A14_2 *)obj_arg)->unk_0D = 0x40;
            ((S_80025A14_2 *)obj_arg)->unk_0C = 0x40;
            current_phase = ((S_80025A14_0 *)state)->unk_72.u;
            ((S_80025A14_0 *)state)->unk_73.u = 0;
            ((S_80025A14_0 *)state)->unk_72.u = current_phase + 1;
        }
                        /* fall through */
    case 2:
        if (D_8002715A != 0) {
            ((S_80025A14_0 *)state)->unk_73.u = 8;
            ((S_80025A14_1 *)buffer)->unk_16 = 8;
            current_phase = ((S_80025A14_0 *)state)->unk_72.u;
            ((S_80025A14_0 *)state)->unk_72.u = current_phase + 1;
        }
        break;
    case 3:
        fade_ticks = (s32)((S_80025A14_0 *)state)->unk_73.s;
        if (fade_ticks != 0) {
            fade_out_value = ((S_80025A14_2 *)obj_arg)->unk_0E;
            fade_out_value += (0 - fade_out_value) / fade_ticks;
            ((S_80025A14_2 *)obj_arg)->unk_0E = fade_out_value;
            ((S_80025A14_2 *)obj_arg)->unk_0D = fade_out_value;
            ((S_80025A14_2 *)obj_arg)->unk_0C = fade_out_value;
        }
        fade_out_value = ((S_80025A14_0 *)state)->unk_73.u - 1;
        ((S_80025A14_0 *)state)->unk_73.u = fade_out_value;
        if ((s8)fade_out_value <= 0) {
            current_phase = ((S_80025A14_0 *)state)->unk_72.u;
            ((S_80025A14_0 *)state)->unk_72.u = current_phase + 1;
        }
        break;
    default:
        return;
    }

    owner = ((S_80025A14_0 *)state)->unk_58;
    owner = ((S_80025A14_4_pre *)owner)[-1].unk_00;
    direction = ((((S_80025A14_4 *)owner)->unk_1A + 0x500) >> 9) & 7;
    if (((S_80025A14_0 *)state)->unk_46 != direction) {
        ((S_80025A14_0 *)state)->unk_46 = direction;
        textureHandleInstallsSelectedAnimationFrameSecondaryPointerUpdatesAnimationFlags(obj_arg, ((u8 *)((S_80025A14_2 *)obj_arg)->unk_2C)[direction],
                      ((S_80025A14_2 *)obj_arg)->unk_04, 2);
    }
    func_80048AC8(obj_arg, 2);
    if (dirSpriteFlag[direction] != 0) {
        render_flags = ((S_80025A14_2 *)obj_arg)->unk_14 | 1;
    } else {
        render_flags = ((S_80025A14_2 *)obj_arg)->unk_14 & 0xFFFE;
    }
    ((S_80025A14_2 *)obj_arg)->unk_14 = render_flags;
    return;
}
