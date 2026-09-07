#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define DGN_TABLE_PAGE(sym, offset) ((unsigned long)(sym) - (offset))
#else
#define DGN_TABLE_PAGE(sym, offset) 0x80170000UL
#endif

extern void func_80047784();
extern u8 D_80083160[];
extern s16 D_80083228[];
extern u16 D_80083460[];
extern u8 *D_800E3D7C[];
extern void *D_80170838[];
extern u8 D_801710EC[];
extern u8 D_80175EB8[];
extern u8 D_80175EC8[];
extern u8 D_80175ED0[];

typedef struct S_80172480_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x14];
    u16 unk_B0;
    s16 unk_B2;
} S_80172480_0;   /* arg0 in func_80172480 */

typedef struct S_80172480_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
} S_80172480_1;   /* arg3 in func_80172480 */

typedef struct S_80172480_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A[0xBE];
    u16 unk_C8;
} S_80172480_2;   /* base_83160 in func_80172480 */

typedef struct S_80172480_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    M2C_UNK * unk_2C;
} S_80172480_3;   /* arg2 in func_80172480 */

typedef struct S_80172480_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80172480_4;   /* D_800E3D7C[0] in func_80172480 */

void func_80172480(S_80172480_0 *arg0, s32 arg1, S_80172480_3 *arg2, S_80172480_1 *arg3) {
    s32 temp_a0;
    u8 temp_v1;
    u8 *base_83160 = D_80083160;
    unsigned long table_page;
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };

    temp_v1 = arg0->unk_9B;
    if (temp_v1 >= 5) {
        return;
    }
    (void)jt_keep;
    goto *D_80170838[(u32)temp_v1];
jt_c0:
        temp_a0 = arg3->unk_2A & 0xFFF;
        arg3->unk_2A = temp_a0;
        if (((0x400 - ((((S_80172480_2 *)base_83160)->unk_C8 + 0x100) & 0xE00)) & 0xE00) != temp_a0) {
            arg3->unk_2A = temp_a0 + 0x200;
            return;
        }
        goto advance;
jt_c1:
        if (arg0->unk_92 == 0) {
            table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
            goto block_14;
        }
        table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
        ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
        table_page += 0x5EC8;
        if ((arg2->unk_14 & 0x8000) == 0) {
            return;
        }
        goto block_14_ready;
jt_c2:
        if (arg2->unk_14 & 0xE000) {
            table_page = DGN_TABLE_PAGE(D_80175ED0, 0x5ED0);
            ASM_KEEP(table_page);   /* MATCH pin: load-bearing for the whole function shape */
            table_page += 0x5ED0;
            goto block_14_ready;
        }
        goto done;
jt_c3:
        {
            u16 case3_loaded = ((S_80172480_2 *)base_83160)->unk_08;
            if (case3_loaded != 0) {
                table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
                goto block_14;
            }
            if (((S_80172480_4 *)(D_800E3D7C[0]))->unk_9A != 0x17) {
                table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
                goto block_14;
            }
        }
        goto done;
block_14:
        table_page += 0x5EC8;
block_14_ready:
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
        {
            u8 *table;
            table = (u8 *)table_page;
            arg2->unk_2C = table;
            {
                unsigned long entry = (unsigned long)(((s32) (D_80083228[0] + (s16) arg3->unk_2A + 0x100) >> 9) & 7);
                entry += (unsigned long)table;
                func_80047784(arg2, *(u8 *)entry, 0);
            }
        }
advance:
        temp_v1 = arg0->unk_9B + 1;
        arg0->unk_9B = temp_v1;
        return;
jt_c4:
        if (arg2->unk_14 & 0xE000) {
            arg3->unk_1C = (s32) (arg3->unk_1C | 0x40000);
            {
                u8 *table = D_80175EB8;
                arg2->unk_2C = table;
                func_80047784(arg2, table[((s32) (D_80083228[0] + (s16) arg3->unk_2A + 0x100) >> 9) & 7], 0);
            }
            arg0->unk_8C = D_801710EC;
            arg3->unk_2A = (u16) arg0->unk_B0;
            arg0->unk_B2 = 0;
            D_80083460[5] = (u16) (D_80083460[5] - 1);
        }
done:
        return;
}
