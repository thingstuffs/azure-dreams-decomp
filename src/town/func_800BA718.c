#include "common.h"

extern u16 D_80111FA8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern void *D_800893A0[];

extern void LoadImage(void *, void *);

void func_800B7E78(u16 *arg0) {
    u16 value;
    s32 index;
    s32 page; /* MATCH: ASM_KEEP preserves the page value used by the shared tail. */
    void *rect;
    register void *data ASM_REG("$5"); /* MATCH: form the merged image argument in a1 before each tail jump. */
    static void *const keepalive[] = { &&L0, &&L4, &&L8, &&L12 };

    value = *arg0 + 1;
    *arg0 = value;
    if ((s16)value >= 24) {
        *arg0 = 0;
    }

    index = (s16)*arg0 % 24;
    if ((u32)index >= 21) {
        return;
    }
    goto *D_800893A0[index];

L0:
    page = (s32)0x80110000;
    ASM_KEEP(page);
    rect = (void *)(page + 0x1FA8);
    data = D_80110EC8;
    goto tail;

L4:
    page = (s32)0x80110000;
    ASM_KEEP(page);
    rect = (void *)(page + 0x1FA8);
    data = D_801110C8;
    goto tail;

L8:
    page = (s32)0x80110000;
    ASM_KEEP(page);
    rect = (void *)(page + 0x1FA8);
    data = D_801112C8;
    goto tail;

L12:
    page = (s32)0x80110000;
    ASM_KEEP(page);
    rect = (void *)(page + 0x1FA8);
    data = D_801114C8;

tail:
    (*(u16 *)(page + 0x1FA8)) = 808;
    ((u16 *)rect)[1] = 128;
    ((u16 *)rect)[2] = 8;
    ((u16 *)rect)[3] = 32;
    LoadImage(rect, data);
}
