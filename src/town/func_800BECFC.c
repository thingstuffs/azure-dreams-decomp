#include "common.h"

typedef struct {
    u32 word0;
    u32 word4;
} __attribute__((packed)) Copy8;

extern void *func_8003FC64(s32 arg0);
extern void func_8004491C(void *arg0, void *arg1);
extern void *func_8004DA74(void *arg0, void *arg1, s32 arg2);
extern void func_8004E9E4(void);
extern void func_800BC1DC(void *arg0, void *arg1, void *arg2);

extern s32 D_80053A88;
extern u8 D_800782EC[8];
extern Copy8 D_8008961C;
extern u8 D_800BC290[8];
extern u8 D_800BC390[8];
extern u8 D_80111FB0[8];

/* Builds two display entries and initializes a display object. */
void func_800BC45C(s32 data_id, s32 position_offset)
{
    Copy8 layout;
    void *display_obj;
    u8 *display_data;

    layout = D_8008961C;
    func_8004E9E4();
    *(u16 *)&layout.word0 += (s32)(position_offset << 16) >> 14;
    func_800BC1DC(&layout, D_800BC290,
                  func_8004DA74(D_80111FB0, (void *)data_id, 0));
    func_800BC1DC((u8 *)&layout + 4, D_800BC290, D_800782EC);

    display_obj = func_8003FC64(1);
    if (display_obj != 0) {
        *(void **)((u8 *)display_obj + 0x10) = D_800BC390;
        display_data = (u8 *)display_obj + 0x20;
        func_8004491C(display_obj, &D_80053A88);
        *(s16 *)(display_data + 0xC) = 0x64;
        *(s16 *)(display_data + 0xE) = 0x34;
        *(s16 *)(display_data + 0x10) = 0x7C;
        *(s16 *)(display_data + 0x12) = 0x18;
        *(s16 *)(display_data + 0x16) = 1;
        *(s32 *)(display_data + 8) = 0x402020;
        *(s16 *)(display_data + 2) = 0x1E;
    }
}
