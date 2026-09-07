#include "common.h"

typedef struct Info80046E38 {
    s32 *data;
    u16 count;
} Info80046E38;

typedef struct Pair80046E38 {
    s32 first;
    s32 second;
} Pair80046E38;

typedef struct State80046E38 {
    u8 pad[10];
    u8 mode;
    u8 tail;
} State80046E38;

extern s32 DrawSync(s32);
extern void func_8003E4FC(s32, s32 *, s32);
extern void func_8003F320(void);
extern void func_8003F6D4(s32, s32, s32 *, s32);
extern u8 *func_8004068C(u8 *, u8 *);
extern void func_80046D64(u8 *, s16);

extern Info80046E38 *D_8006E7F0[];
extern s32 D_80080A7C;
extern u8 *D_80081480;
extern u8 *D_8008148C[3];
extern State80046E38 D_80082E60;

void func_80046E38(s16 arg0, u8 *arg1)
{
    Pair80046E38 pair;
    u8 *state;
    u8 *original;
    s32 saved_align;
    s32 cursor;
    s32 count;
    register u8 *slot_base ASM_REG("$2");
    s32 index;
    s32 tmp;
    Info80046E38 **slot;
    Info80046E38 *info;
    s32 *data;

    state = arg1;
    ASM_KEEP_NV(state);
    original = arg1;
    D_80081480 = D_8008148C[0];
    saved_align = (s32)D_8008148C[0];
    DrawSync(0);

    tmp = arg0 << 16;
    ASM_KEEP_NV(tmp);
    slot_base = (u8 *)D_8006E7F0;
    index = tmp >> 14;
    slot = (Info80046E38 **)(index + (u32)slot_base);
    data = (*slot)->data;
    pair = *(Pair80046E38 *)data;
    info = *slot;
    count = info->count;
    cursor = info->data[1];

    if (count > 0) {
        do {
            func_8003E4FC(6, (s32 *)&pair, 0);
            cursor += 0x10;
            func_8003F320();
            state = func_8004068C(D_8008148C[-3], state);
            count--;
            func_8003F6D4(0x10, 0, (s32 *)&pair, cursor);
        } while (count > 0);
    }

    func_80046D64(original, arg0);
    {
        register s32 mode ASM_REG("$3");
        register u32 page ASM_REG("$2");

        page = 0x80080000;
        ASM_KEEP_NV(page);
        mode = *(u8 *)(page + 0x2E6A);
        ASM_KEEP_NV(mode);
        {
            s32 out;

            out = 2;
            if (mode != out) {
                out = 0x8000;
            } else {
                out = 0x4000;
            }
            D_80080A7C = out;
        }
    }
    D_80081480 = (u8 *)((saved_align + 3) & ~3);
}
