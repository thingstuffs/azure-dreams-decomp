#include "modules/dungeon_town_map.h"

void func_8008BC58(u8 *object, town_map_7FFEE4F8_S_8008BC58_2 *view_params, void *update_context)
{
    GameWork *input = &gameWork;
    u8 *selection_ids = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_7C;
    u8 *display_record;
    s16 state;

    if (D_800FC418 != 0) {
        ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_68 = (void *)func_8008BED8;
        return;
    }

    state = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_66;
    if (state == 0) {
        u16 input_delay;
        s32 buttons;

        input_delay = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_64 - 1;
        ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_64 = input_delay;
        if ((input_delay << 16) <= 0) {
            ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_64 = 0;
            if (((s32)input->unk_010) & 0x10000000) {
                view_params->unk_0A += 0x10;
            }
            if (((s32)input->unk_010) & 0x40000000) {
                view_params->unk_0A -= 0x10;
            }
            buttons = ((s32)input->unk_010);
            if (buttons & 0x40) {
                D_800FC418 = 1;
                func_80035208(D_80072214);
                return;
            }
            if (buttons & 0x20) {
                D_800FC418 = 1;
                func_80035208(D_80072210);
                return;
            }
        } else {
            return;
        }
    } else if (state == 9) {
        s32 x;
        s32 y;

        func_800478B8(update_context);
        display_record = *(u8 **)object;
        x = D_80083780.x.w.i / 64 - 0x18;
        ((town_map_7FFEE4F8_S_8008BC58_3 *)display_record)->unk_30 = x;
        display_record = *(u8 **)object;
        y = D_80083780.y.w.i / 64 - 0x40;
        ((town_map_7FFEE4F8_S_8008BC58_3 *)display_record)->unk_34 = y;
        return;
    } else if (state == 10) {
        s32 selection_index;
        s32 selection_index_2;
        s32 selection_index_3;
        s32 selection_index_4;
        s32 selection_index_5;
        s32 selection_index_6;
        u8 selection_id;
        u8 *selection_positions;
        s32 buttons;

        func_800478B8(update_context);
        buttons = ((s32)input->unk_010);
        if (buttons & 0x6000) {
            selection_index = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 + 1;
            ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = selection_index;
            if (selection_index >= ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_78) {
                ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = 0;
            }
            func_8008B620(selection_ids[((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74]);
        } else if (buttons & 0x9000) {
            selection_index_2 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 - 1;
            ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = selection_index_2;
            if (selection_index_2 < 0) {
                selection_index_3 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_78 - 1;
                ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74 = selection_index_3;
            }
            func_8008B620(selection_ids[((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74]);
        }

        selection_index_4 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74;
        selection_positions = D_800D2EA4;
        selection_id = selection_ids[selection_index_4];
        ((town_map_7FFEE4F8_S_8008BC58_3 *)(*(u8 **)object))->unk_30 = selection_positions[selection_id * 8] - 0x18;

        selection_index_5 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74;
        selection_id = selection_ids[selection_index_5];
        display_record = *(u8 **)object;
        ((town_map_7FFEE4F8_S_8008BC58_3 *)display_record)->unk_34 = selection_positions[selection_id * 8 + 1] - 0x40;

        selection_index_6 = ((town_map_7FFEE4F8_S_8008BC58_0 *)object)->unk_74;
        selection_id = selection_ids[selection_index_6];
        D_80082ABC = selection_id;
    }

    return;
}
