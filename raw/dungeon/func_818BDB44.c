#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s32 words[4];
} Copy16;

extern void *func_8003FC64(s32);
extern s32 rand();
extern void func_8004491C(void *, void *);
extern void func_800254C0() __attribute__((noreturn));

extern u8 D_80024F4C[];
extern u8 D_80025DF8[];
extern u8 D_80045340[];

s32 func_818BDB44(void *arg0, void *arg1)
{
    void *obj;
    void *payload;
    void *part;
    s32 first_random;
    s32 random;
    s32 other_flags;
    s32 scale;
    register s32 flags ASM_REG("$3");

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        payload = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_80024F4C;
        FIELD(obj, void *, 0x20) = arg0;
        FIELD(payload, s16, 0xE) = 0;
        FIELD(payload, s16, 0x10) = 0;

        first_random = rand();
        FIELD(payload, s16, 0x12) = first_random % 7;
        FIELD(payload, u16, 0x14) = FIELD(arg0, u16, 0x12);

        random = rand(first_random / 7);
        FIELD(payload, s16, 0x16) = random % 0x1000;
        FIELD(payload, s32, 0x18) = FIELD(arg0, s32, 0x18);

        part = FIELD(obj, void *, 0xC);
        FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, u8, 0xD) = 0x80;
        FIELD(part, u8, 0xC) = 0x80;
        FIELD(part, s16, 0x12) = 0x7E01;
        FIELD(part, void *, 8) = D_80025DF8;
        flags = FIELD(part, u16, 0x14) | 0xC;
        other_flags = FIELD(part, u16, 0x10) | 0x20;
        ASM_SCHED_BARRIER();
        FIELD(part, u16, 0x14) = flags;
        flags |= 0x100;
        FIELD(part, u16, 0x10) = other_flags;
        ASM_KEEP(flags);
        FIELD(part, u16, 0x14) = flags;

        random = rand();
        {
            register void *call_obj ASM_REG("$4") = obj;

            FIELD(part, s16, 0x1A) = random % 0x1000;
            ASM_KEEP(call_obj);
            scale = 0x400;
            ASM_USE(scale);
            FIELD(part, s16, 0x1E) = scale;
            FIELD(part, s16, 0x1C) = scale;
            func_8004491C(call_obj, D_80045340);
        }

        {
            void *dst = FIELD(obj, void *, 8);
            ASM_KEEP(dst);
            {
                register s32 result ASM_REG("$2") = (s32)obj;
                s32 word4;
                s32 word5;

                ASM_KEEP(result);
                *(Copy16 *)dst = *(Copy16 *)arg1;
                word4 = FIELD(arg1, s32, 0x10);
                word5 = FIELD(arg1, s32, 0x14);
                ASM_USE_NV(result);
                FIELD(dst, s32, 0x10) = word4;
                FIELD(dst, s32, 0x14) = word5;
                func_800254C0();
            }
        }
    }
    {
        register s32 result ASM_REG("$2") = 0;
        ASM_KEEP(result);
        return result;
    }
}
