#include "common.h"

typedef struct S_818BDB44_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818BDB44_0;   /* obj in func_818BDB44 */

typedef struct S_818BDB44_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    s16 unk_16;
    s32 unk_18;
} S_818BDB44_1;   /* payload in func_818BDB44 */

typedef struct S_818BDB44_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
} S_818BDB44_2;   /* arg0 in func_818BDB44 */

typedef struct S_818BDB44_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BDB44_3;   /* part in func_818BDB44 */

typedef struct S_818BDB44_4 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_818BDB44_4;   /* arg1 in func_818BDB44 */

typedef struct S_818BDB44_5 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_818BDB44_5;   /* dst in func_818BDB44 */



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

s32 func_818BDB44(S_818BDB44_2 *arg0, S_818BDB44_4 *arg1)
{
    void *obj;
    S_818BDB44_1 *payload;
    S_818BDB44_3 *part;
    s32 first_random;
    s32 random;
    s32 other_flags;
    s32 scale;
    register s32 flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        payload = (u8 *)obj + 0x20;
        ((S_818BDB44_0 *)obj)->unk_10 = D_80024F4C;
        ((S_818BDB44_0 *)obj)->unk_20 = arg0;
        payload->unk_0E = 0;
        payload->unk_10 = 0;

        first_random = rand();
        payload->unk_12 = first_random % 7;
        payload->unk_14 = arg0->unk_12;

        random = rand(first_random / 7);
        payload->unk_16 = random % 0x1000;
        payload->unk_18 = arg0->unk_18;

        part = ((S_818BDB44_0 *)obj)->unk_0C;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
        part->unk_12 = 0x7E01;
        part->unk_08 = D_80025DF8;
        flags = part->unk_14 | 0xC;
        other_flags = part->unk_10 | 0x20;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        part->unk_14 = flags;
        flags |= 0x100;
        part->unk_10 = other_flags;
        part->unk_14 = flags;

        random = rand();
        {
            void *call_obj = obj;

            part->unk_1A = random % 0x1000;
            scale = 0x400;
            part->unk_1E = scale;
            part->unk_1C = scale;
            func_8004491C(call_obj, D_80045340);
        }

        {
            S_818BDB44_5 *dst = ((S_818BDB44_0 *)obj)->unk_08;
            {
                register s32 result ASM_REG("$2") = (s32)obj;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                s32 word4;
                s32 word5;

                *(Copy16 *)dst = *(Copy16 *)arg1;
                word4 = arg1->unk_10;
                word5 = arg1->unk_14;
                ASM_USE_NV(result);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                dst->unk_10 = word4;
                dst->unk_14 = word5;
                func_800254C0();
            }
        }
    }
    {
        s32 result = 0;
        return result;
    }
}
