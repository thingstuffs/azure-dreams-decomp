#include "common.h"

typedef struct S_80024B20_0 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024B20_0;   /* dst in func_80024B20 */

typedef struct S_80024B20_1 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024B20_1;   /* src in func_80024B20 */

typedef struct S_80024B20_2_pre {
    u16 unk_00;
} S_80024B20_2_pre;   /* the 0x2 bytes before arg0 in func_80024B20, addressed as arg0[-1] */

typedef struct S_80024B20_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2A];
    s16 unk_3A;
    u8 pad_3C[0x4];
    union { s16 s; u16 u; } unk_40;   /* accessed as both */
    union { u16 u; s16 s; } unk_42;   /* accessed as both */
} S_80024B20_2;   /* arg0 in func_80024B20 */

typedef struct S_80024B20_3 {
    u8 pad_00[0x12];
    union { volatile u16 v; s16 n; } unk_12;   /* accessed as both */
    s16 unk_14;
} S_80024B20_3;   /* p in func_80024B20 */

typedef struct S_80024B20_4 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_80024B20_4;   /* (u8 *)arg0 + offset in func_80024B20 */

typedef struct S_80024B20_5 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_80024B20_5;   /* page in func_80024B20 */



extern s32 func_800644B8();

void func_80024B20(void *arg0) {
    u16 state;
    {
        register s32 i ASM_REG("$5") = 0;   /* MATCH pin: retail register colouring depends on it */
        s32 scaled;
        do {
            register s32 next ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            s32 index, src_offset, dst_offset;
            u8 *src;
            u8 *dst;
            scaled = i * 2;
            index = scaled + i;
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            next = i + 1;
            ASM_KEEP(next);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            i = next;
            dst_offset = index * 2;
            src_offset = i * 6;
            src = arg0;
            dst = arg0;
            src += src_offset;
            dst += dst_offset;
            ((S_80024B20_0 *)dst)->unk_10 = ((S_80024B20_1 *)src)->unk_10;
        } while (i < 7);
    }

    {
        s32 i = 7;
        volatile u16 *p = (volatile u16 *)((u8 *)arg0 + 0x2A);
        do {
            i--;
            p[9] = p[9] + p[10];
            p -= 3;
        } while (i >= 0);
    }

    ((S_80024B20_2 *)arg0)->unk_42.u--;
    switch (((S_80024B20_2 *)arg0)->unk_40.s) {
    case 0:
        goto mode_zero;
    case 1:
        goto mode_one;
    case 2:
        goto mode_two;
    case 3:
        goto mode_three;
    default:
        goto tail_default;
    }

tail_default:
    goto tail_return;

mode_zero:
    ((S_80024B20_2 *)arg0)->unk_42.u = 0;
    ((S_80024B20_2 *)arg0)->unk_0C = 0;
    ((S_80024B20_2 *)arg0)->unk_40.s = ((S_80024B20_2 *)arg0)->unk_40.u + 1;

mode_one:
    {
        s32 accum = ((S_80024B20_2 *)arg0)->unk_0C;
        s32 call_arg = ((S_80024B20_2 *)arg0)->unk_42.s;
        accum += 0xC0C0C;
        ((S_80024B20_2 *)arg0)->unk_0C = accum;
        ((S_80024B20_2 *)arg0)->unk_3A = func_800644B8(call_arg << 9) >> 7;
        if (((S_80024B20_2 *)arg0)->unk_0C > 0x60605F) {
            register u16 timer ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            state = ((S_80024B20_2 *)arg0)->unk_40.u;
            timer = 0x38;
            ((S_80024B20_2 *)arg0)->unk_42.u = timer;
            goto increment_state;
        }
        return;
    }

mode_two:
    {
        s32 i = 7;
        s32 y = 0xD0;
        u8 *p = (u8 *)arg0 + 0x2A;
        do {
            register s32 square ASM_REG("$8") = i * i;   /* MATCH pin: retail register colouring depends on it */
            s32 value;
            i--;
            value = y - ((S_80024B20_2 *)arg0)->unk_42.u;
            y -= 0x18;
            ((S_80024B20_3 *)p)->unk_14 = value + ((square >> 2) * 0x14);
            ASM_KEEP(square);   /* MATCH pin: load-bearing for the whole function shape */
            p -= 6;
        } while (i >= 0);
    }
    {
        s32 i = 6;
        register s32 limit ASM_REG("$4") = 0x160;   /* MATCH pin: retail delay-slot fill depends on it */
        register u8 *p ASM_REG("$6") = (u8 *)arg0 + 0x24;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        register s32 offset ASM_REG("$7") = 0x2A;   /* MATCH pin: retail register colouring depends on it */
        do {
            u16 current = ((S_80024B20_3 *)p)->unk_12.v;
            if (limit < (((S_80024B20_4 *)((u8 *)arg0 + offset))->unk_12 - ((S_80024B20_3 *)p)->unk_12.n)) {
                ((S_80024B20_3 *)p)->unk_12.n = current + (limit + (limit >> 1));
            }
            limit -= 0x10;
            p -= 6;
            i--;
            offset -= 6;
        } while (i >= 0);
    }
    if (((S_80024B20_2 *)arg0)->unk_42.s < 8) {
        ((S_80024B20_2 *)arg0)->unk_0C += (s32)0xFFF3F3F4;
    }
    if (((S_80024B20_2 *)arg0)->unk_42.s <= 0) {
        state = ((S_80024B20_2 *)arg0)->unk_40.u;
increment_state:
        state++;
        ((S_80024B20_2 *)arg0)->unk_40.u = state;
        goto tail_return;
    }
    goto tail_return;

mode_three:
    {
        register u32 page ASM_REG("$3") = 0x80080000;   /* MATCH pin: retail register colouring depends on it */
        ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ((S_80024B20_2_pre *)arg0)[-1].unk_00 |= 0x8000;
        ((S_80024B20_5 *)page)->unk_14A0 |= 0x8000;
    }
tail_return:
    return;
}
