#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 func_80025340();
extern u32 func_80065420();
extern s32 func_80066460();
extern void func_80067F20();
extern u8 D_80080000[];
extern u8 D_80083160[];

s32 func_800252E0(void *arg0, void *arg1, void *arg2) {
    register void *input ASM_REG("$8") = arg1;
    void *arg2use = arg2;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *global_slot = D_80080000 + 0x3160;
    u32 low_mask = 0x00FFFFFF;
    u32 high_mask = 0xFF000000;
    void *p;
    s32 *tag;

    {
        void *global = FIELD(D_80080000, void *, 0x3160);
        void *cursor = FIELD(global, void *, 0x8D0);
        FIELD(scratch, void *, 0x20) = (u8 *)global + 0xB0;
        FIELD(scratch, void *, 0x18) = cursor;
    }
    for (;;) {
        register u16 first_coord ASM_REG("$2") = FIELD(input, u16, 2);
        FIELD(scratch, u16, 0) = first_coord;
        FIELD(scratch, u16, 2) = FIELD(input, u16, 6);
        FIELD(scratch, u16, 4) = FIELD(input, u16, 0xA);
        p = FIELD(scratch, void *, 0x18);
        FIELD(scratch, void *, 0x18) = (u8 *)p + 0xC;
        FIELD(scratch, u32, 0xC0) = func_80065420(
            scratch, (u8 *)p + 8, scratch + 0x90, scratch + 0x94);
        if (FIELD(scratch, u32, 0xC0) < 0x1E0) {
            s32 value = FIELD(arg2use, s32, 0xC);
            FIELD(p, s8, 3) = 2;
            FIELD(p, s32, 4) = value;
            FIELD(p, s8, 7) = 0x6A;
            FIELD(p, u32, 0) = (FIELD(p, u32, 0) & high_mask) |
                (*(s32 *)((FIELD(scratch, u32, 0xC0) << 2) +
                          (u32)FIELD(scratch, void *, 0x20)) & low_mask);
            {
                register u32 tag_offset ASM_REG("$7");
                tag_offset = *(volatile u32 *)(scratch + 0xC0);
                ASM_KEEP_NV(tag_offset);
                tag = (s32 *)((tag_offset << 2) +
                              (u32)*(void * volatile *)(scratch + 0x20));
            }
            *tag = (*tag & high_mask) | ((u32)p & low_mask);
            p = FIELD(scratch, void *, 0x18);
            FIELD(scratch, void *, 0x18) = (u8 *)p + 0xC;
            func_80067F20(p, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            FIELD(p, u32, 0) = (FIELD(p, u32, 0) & high_mask) |
                (*(s32 *)((FIELD(scratch, u32, 0xC0) << 2) +
                          (u32)FIELD(scratch, void *, 0x20)) & low_mask);
            {
                register u32 tag_addr ASM_REG("$3");
                tag_addr = *(volatile u32 *)(scratch + 0xC0);
                ASM_KEEP_NV(tag_addr);
                tag_addr = (tag_addr << 2) +
                           (u32)*(void * volatile *)(scratch + 0x20);
                ASM_KEEP_NV(tag_addr);
                p = (void *)((u32)p & low_mask);
                *(s32 *)tag_addr = (*(s32 *)tag_addr & high_mask) |
                                   (u32)p;
            }
        }
        {
            void *next = FIELD(arg0, void *, -8);
            if (next == NULL) {
                FIELD(FIELD(global_slot, void *, 0), void *, 0x8D0) =
                    FIELD(scratch, void *, 0x18);
                return 0;
            }
            arg0 = (u8 *)next + 0x20;
            input = FIELD(next, void *, 8);
            arg2use = FIELD(next, void *, 0xC);
        }
    }
}
