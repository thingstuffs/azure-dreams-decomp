#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008CAA0_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x70];
    u16 unk_10C;
} S_8008CAA0_0;   /* arg0 in func_8008CAA0 */

typedef struct S_8008CAA0_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8008CAA0_1;   /* arg3 in func_8008CAA0 */


M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_8008CAEC();                      /* extern */
M2C_UNK func_80094E34();                            /* extern */
s32 func_800A6D30();                                /* extern */
extern s16 D_80083228;
extern u8 D_800DCFE0[];
extern u8 D_800DCFE8[];
extern u8 D_800E3E41;

void func_8008CAA0(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *table;
    ((S_8008CAA0_0 *)arg0)->unk_10C = (s16) (((S_8008CAA0_0 *)arg0)->unk_10C & 0xFFFE);
    {
        s32 mask = 0x20000000;
        if (((S_8008CAA0_1 *)arg3)->unk_1C & mask) {
            register u8 *page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
            func_8008CAEC(arg2, D_800DCFE0);
#else
            page = (u8 *) 0x800E0000;
            ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
            func_8008CAEC(arg2, page - 0x3020);
#endif
            return;
        }
    }
    {
        register u8 *page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
        table = D_800DCFE8;
#else
        page = (u8 *) 0x800E0000;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        table = page - 0x3018;
#endif
    }
    (*(u8 **)((u8 *)arg2 + 0x2C)) = table;
    {
        register u8 *entry ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        entry = table + (((s32) (D_80083228 + ((S_8008CAA0_1 *)arg3)->unk_2A + 0x100) >> 9) & 7);
        ASM_KEEP_NV(entry);   /* MATCH pin: keeps a statement from moving across a call/branch */
        func_80048A44(arg2, *entry, 0, 1);
    }
    ((S_8008CAA0_0 *)arg0)->unk_9A = 7;
    ((S_8008CAA0_0 *)arg0)->unk_9B = 0;
    ((S_8008CAA0_0 *)arg0)->unk_8C = 0;
    func_80094E34();
    if (!(func_800A6D30() & 1)) {
        func_80042B68(arg3, 1);
        func_80042B68(arg3, 4);
        func_80042B68(arg3, 2);
    }
    {
        register s32 mask ASM_REG("$3") = 0x20000000;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        if (((S_8008CAA0_1 *)arg3)->unk_1C & mask) {
            ((S_8008CAA0_0 *)arg0)->unk_96 = (s16) D_800E3E41;
        }
    }
}
