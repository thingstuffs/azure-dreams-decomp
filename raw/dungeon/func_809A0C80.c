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

void func_80172480(void *arg0, s32 arg1, void *arg2, void *arg3) {
    s32 temp_a0;
    u8 temp_v1;
    u8 *base_83160 = D_80083160;
    register unsigned long table_page ASM_REG("$5");
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 5) {
        return;
    }
    (void)jt_keep;
    goto *D_80170838[(u32)temp_v1];
jt_c0:
        temp_a0 = M2C_FIELD(arg3, u16 *, 0x2A) & 0xFFF;
        M2C_FIELD(arg3, u16 *, 0x2A) = temp_a0;
        if (((0x400 - ((M2C_FIELD(base_83160, u16 *, 0xC8) + 0x100) & 0xE00)) & 0xE00) != temp_a0) {
            M2C_FIELD(arg3, u16 *, 0x2A) = temp_a0 + 0x200;
            return;
        }
        goto advance;
jt_c1:
        if (M2C_FIELD(arg0, s16 *, 0x92) == 0) {
            table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
            goto block_14;
        }
        table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
        ASM_KEEP(table_page);
        table_page += 0x5EC8;
        if ((M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) == 0) {
            return;
        }
        goto block_14_ready;
jt_c2:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            table_page = DGN_TABLE_PAGE(D_80175ED0, 0x5ED0);
            ASM_KEEP(table_page);
            table_page += 0x5ED0;
            goto block_14_ready;
        }
        goto done;
jt_c3:
        {
            u16 case3_loaded = M2C_FIELD(base_83160, u16 *, 8);
            if (case3_loaded != 0) {
                table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
                goto block_14;
            }
            if (M2C_FIELD(D_800E3D7C[0], u8 *, 0x9A) != 0x17) {
                table_page = DGN_TABLE_PAGE(D_80175EC8, 0x5EC8);
                goto block_14;
            }
        }
        goto done;
block_14:
        ASM_KEEP(table_page);
        table_page += 0x5EC8;
block_14_ready:
        ASM_SCHED_BARRIER();
        {
            u8 *table;
            table = (u8 *)table_page;
            M2C_FIELD(arg2, M2C_UNK **, 0x2C) = table;
            {
                register unsigned long entry ASM_REG("$2") = (unsigned long)(((s32) (D_80083228[0] + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7);
                ASM_KEEP(entry);
                entry += (unsigned long)table;
                ASM_KEEP(entry);
                func_80047784(arg2, *(u8 *)entry, 0);
            }
        }
advance:
        temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B) + 1;
        M2C_FIELD(arg0, u8 *, 0x9B) = temp_v1;
        return;
jt_c4:
        if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
            M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000);
            {
                u8 *table = D_80175EB8;
                M2C_FIELD(arg2, M2C_UNK **, 0x2C) = table;
                func_80047784(arg2, table[((s32) (D_80083228[0] + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
            }
            M2C_FIELD(arg0, M2C_UNK **, 0x8C) = D_801710EC;
            M2C_FIELD(arg3, u16 *, 0x2A) = (u16) M2C_FIELD(arg0, u16 *, 0xB0);
            M2C_FIELD(arg0, s16 *, 0xB2) = 0;
            D_80083460[5] = (u16) (D_80083460[5] - 1);
        }
done:
        return;
}
