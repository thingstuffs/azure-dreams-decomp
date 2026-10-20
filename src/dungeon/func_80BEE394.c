#include "modules/dungeon_resource16_slot0.h"

void fade_entity_colors_to_neutral(void *entity_data, void *unused, void *source_data)
{
    u8 *entity = entity_data;
    u8 *source = source_data;
    GameWork *colors = &g_game_work;
    u16 ticks;
    u16 fade_left;

    if (entity[0x9A] == 0) {
        (*(s32 *)D_801742E8) = *(s32 *)(source + 8);
        func_800478B8(source);

        if (*(u16 *)(source + 0x14) & 0xE000) {
            unlink_node(entity - 0x20);
            *(u16 *)(entity + 0x96) = 0x10;
            entity[0x9A]++;
        }

        ticks = *(u16 *)(entity + 0x96);
        *(u16 *)(entity + 0x96) = ticks + 1;
        if ((ticks & 3) == 0) {
            (*(u16 *)D_801742E0)--;
            return;
        }
    } else {
        colors->view.unk_090 += (0x80 - colors->view.unk_090) / *(s16 *)(entity + 0x96);
        colors->view.unk_091 += (0x80 - colors->view.unk_091) / *(s16 *)(entity + 0x96);
        colors->view.unk_092 += (0x80 - colors->view.unk_092) / *(s16 *)(entity + 0x96);

        fade_left = *(u16 *)(entity + 0x96) - 1;
        *(u16 *)(entity + 0x96) = fade_left;
        if ((fade_left << 16) <= 0) {
            *(u16 *)(entity - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
