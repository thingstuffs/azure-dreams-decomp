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

/* Allocate and initialize a randomized object from the source and initial data. */
s32 func_818BDB44(S_818BDB44_2 *source, S_818BDB44_4 *init_data)
{
    void *object;
    S_818BDB44_1 *payload;
    S_818BDB44_3 *part;
    s32 variant_random;
    s32 random_value;
    s32 flags_10;
    s32 scale;
    register s32 flags_14 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    object = func_8003FC64(0x212);
    if (object != 0) {
        payload = (u8 *)object + 0x20;
        ((S_818BDB44_0 *)object)->unk_10 = D_80024F4C;
        ((S_818BDB44_0 *)object)->unk_20 = source;
        payload->unk_0E = 0;
        payload->unk_10 = 0;

        variant_random = rand();
        payload->unk_12 = variant_random % 7;
        payload->unk_14 = source->unk_12;

        random_value = rand(variant_random / 7);
        payload->unk_16 = random_value % 0x1000;
        payload->unk_18 = source->unk_18;

        part = ((S_818BDB44_0 *)object)->unk_0C;
        part->unk_0E = 0x80;
        part->unk_0D = 0x80;
        part->unk_0C = 0x80;
        part->unk_12 = 0x7E01;
        part->unk_08 = D_80025DF8;
        flags_14 = part->unk_14 | 0xC;
        flags_10 = part->unk_10 | 0x20;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        part->unk_14 = flags_14;
        flags_14 |= 0x100;
        part->unk_10 = flags_10;
        part->unk_14 = flags_14;

        random_value = rand();
        {
            void *setup_object = object;

            part->unk_1A = random_value % 0x1000;
            scale = 0x400;
            part->unk_1E = scale;
            part->unk_1C = scale;
            func_8004491C(setup_object, D_80045340);
        }

        {
            S_818BDB44_5 *object_data = ((S_818BDB44_0 *)object)->unk_08;
            {
                register s32 object_addr ASM_REG("$2") = (s32)object;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                s32 init_word_4;
                s32 init_word_5;

                *(Copy16 *)object_data = *(Copy16 *)init_data;
                init_word_4 = init_data->unk_10;
                init_word_5 = init_data->unk_14;
                ASM_USE_NV(object_addr);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                object_data->unk_10 = init_word_4;
                object_data->unk_14 = init_word_5;
                func_800254C0();
            }
        }
    }
    {
        s32 failure_result = 0;
        return failure_result;
    }
}
