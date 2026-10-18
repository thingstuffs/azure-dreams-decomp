#include "modules/dungeon_ovl_cb3000.h"

void expand_then_shrink_effect(void *effect, void *unused, void *visual)
{
    s16 state;
    s32 fade_brightness;
    u8 brightness;

    state = ((CB_80170920_S_80170920_0 *)effect)->unk_1C.s;
    switch (state) {
    case 0:
        ((CB_80170920_S_80170920_1 *)visual)->unk_1C += 0x258;
        ((CB_80170920_S_80170920_1 *)visual)->unk_1E += 0x258;
        brightness = ((CB_80170920_S_80170920_1 *)visual)->unk_0E + 0xC;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0E = brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0D = brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0C = brightness;
        if (((CB_80170920_S_80170920_1 *)visual)->unk_1C < 0x1770) {
            break;
        }
        ((CB_80170920_S_80170920_0 *)effect)->unk_1C.u++;
        break;
    case 1:
        ((CB_80170920_S_80170920_1 *)visual)->unk_10 = 0x20;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0E = 0x50;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0D = 0x50;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0C = 0x50;
        ((CB_80170920_S_80170920_0 *)effect)->unk_1C.u++;
        break;
    case 2:
        ((CB_80170920_S_80170920_1 *)visual)->unk_10 = 0x60;
        ((CB_80170920_S_80170920_0 *)effect)->unk_24.s--;
        ((CB_80170920_S_80170920_1 *)visual)->unk_1C -= 0x190;
        ((CB_80170920_S_80170920_1 *)visual)->unk_1E -= 0x190;
        fade_brightness = (((CB_80170920_S_80170920_0 *)effect)->unk_24.u << 7) /
                   ((CB_80170920_S_80170920_0 *)effect)->unk_26;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0E = fade_brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0D = fade_brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0C = fade_brightness;
        break;
    }

    ((CB_80170920_S_80170920_1 *)visual)->unk_1A += 0x190;
    if (((CB_80170920_S_80170920_0 *)effect)->unk_24.u <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
