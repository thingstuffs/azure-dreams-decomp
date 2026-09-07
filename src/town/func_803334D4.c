#include "common.h"


extern void func_8001ACA0(s16 *result);
extern void *D_80016000[3];
extern u8 D_8001F244[];
extern u8 D_8001F288[];

typedef s32 (*TownCallback)(s32, u8, s32, s32);

typedef struct S_803334D4_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_803334D4_0;   /* D_80016000[0] in func_803334D4 */


void func_803334D4(s32 arg0)
{
    s16 result[2];
    u8 index;
    u8 *entry;
    u8 mode;
    s32 x;
    s32 y;

    0 >> 0;
    index = D_8001F244[arg0];
    if (index != 0x1C) {
        u8 *base = D_8001F288;
        entry = &base[index * 3];
        if (entry[2] != 0) {
            func_8001ACA0(result);
            mode = entry[1];
            x = (entry[0] << 6) + result[0] + 0x20;
            y = result[1] - 0x40;
            (*(TownCallback *)((u8 *)(((S_803334D4_0 *)(D_80016000[0]))->unk_20) + 0x264))(
                0xF,
                mode,
                x,
                y);
        }
    }
}
