#include "common.h"

typedef struct {
    u32 words[3];
} __attribute__((packed)) Copy12;

typedef struct {
    u8 pad[0x1C];
    s32 flags;
} Status;

extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0();
extern void func_800A2B04(s32, s32, s32);
extern u8 D_80082E80[];
extern Copy12 D_8016A858[];
extern u8 *D_80174704;

void func_8016E138(s32 arg0) {
    Copy12 copy;
    s32 amount;
    s32 amount2;
    register s32 saved_arg ASM_REG("$20");
    u8 *copy_base;
    register u8 *copy_page ASM_REG("$4");
    register Copy12 *copy_src ASM_REG("$7");
    s16 *delta;
    register s32 handle ASM_REG("$19");
    register u8 *object ASM_REG("$16");
    register u8 *table ASM_REG("$5");
    register u8 *base ASM_REG("$3");
    register Status *status ASM_REG("$18");
    register s32 scaled ASM_REG("$4");
    s32 flags;
    s32 x;
    s32 y;

    saved_arg = arg0;
    ASM_KEEP_NV(saved_arg);
    base = D_80174704;
    ASM_KEEP_NV(base);
#ifdef NON_MATCHING
    copy_page = (u8 *)D_8016A858 + 0x57A8;
#else
    copy_page = (u8 *)0x80170000;
#endif
    ASM_KEEP(copy_page);
    copy_src = (Copy12 *)(copy_page - 0x57A8);
    ASM_KEEP_NV(copy_src);
    copy = *copy_src;
    ASM_KEEP_DEP_NV(copy_src, copy_page);
    amount = 0x3000;
    status = (Status *)base + 1;
    ASM_KEEP_NV(status);
    object = *(u8 **)(base + 0xC);
    handle = *(s32 *)(base + 8);
    *(u16 *)(object + 0x14) &= 0xFF7F;
    x = object[0x24];
    y = object[0x25];
    if (status->flags & 0x2000) {
        amount = 0x300;
    }
    copy_base = (u8 *)&copy;
    func_8009A3D0(x, y, amount, copy_src);
    table = D_80082E80;
    ASM_KEEP_NV(table);
    scaled = saved_arg << 1;
    ASM_KEEP_NV(scaled);
    delta = (s16 *)(copy_base + scaled);
    object[0x24] = table[0x24] + ((u8 *)delta)[0];
    object[0x25] = table[0x25] + ((u8 *)delta)[1];
    func_800A2B04(handle, object[0x24], object[0x25]);
    flags = *(volatile s32 *)&status->flags;
    ASM_SCHED_BARRIER();
    x = object[0x24];
    y = object[0x25];
    amount2 = 0x3000;
    if (flags & 0x2000) {
        amount2 = 0x300;
    }
    func_8009A21C(x, y, amount2);
}
