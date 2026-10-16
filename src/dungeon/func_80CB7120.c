#include "modules/dungeon_ovl_cd7000.h"

void func_8014C920(void *effect, void *unused, void *visual)
{
    s16 state;
    s32 fade_brightness;
    u8 brightness;

    state = ((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_1C.s;
    switch (state) {
    case 0:
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_1C += 0x258;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_1E += 0x258;
        brightness = ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0E + 0xC;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0E = brightness;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0D = brightness;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0C = brightness;
        if (((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_1C < 0x1770) {
            break;
        }
        ((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_1C.u++;
        break;
    case 1:
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_10 = 0x20;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0E = 0x50;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0D = 0x50;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0C = 0x50;
        ((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_1C.u++;
        break;
    case 2:
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_10 = 0x60;
        ((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_24.s--;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_1C -= 0x190;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_1E -= 0x190;
        fade_brightness = (((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_24.u << 7) /
                   ((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_26;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0E = fade_brightness;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0D = fade_brightness;
        ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_0C = fade_brightness;
        break;
    }

    ((CL_CD7000_80170920_S_80170920_1 *)visual)->unk_1A += 0x190;
    if (((CL_CD7000_80170920_S_80170920_0 *)effect)->unk_24.u <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
