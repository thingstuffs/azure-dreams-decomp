#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"




M2C_UNK func_80042B68();             /* extern */
M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
s32 func_800A6D30();                                /* extern */
extern s16 D_80083228;
extern u8 D_800DCFE0[];
extern u8 D_800DCFE8[];
extern u8 D_800E3E41;

void func_8008CAA0(void *arg0, s32 arg1, void *arg2, void *arg3) {
    u8 *table;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_10C = (s16) (((Rec_func_8008ACDC_arg0 *)arg0)->unk_10C & 0xFFFE);
    {
        s32 mask = 0x20000000;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & mask) {
            register u8 *page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            table = D_800DCFE0;
#else
            page = (u8 *) 0x800E0000;
            ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            table = page - 0x3020;
#endif
        } else {
            register u8 *page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            table = D_800DCFE8;
#else
            page = (u8 *) 0x800E0000;
            ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            table = page - 0x3018;
#endif
        }
    }
    (*(u8 **)((u8 *)arg2 + 0x2C)) = table;
    {
        register u8 *entry ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        entry = table + (((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7);
        ASM_KEEP_NV(entry);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        func_80048A44(arg2, *entry, 0, 1);
    }
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_s8 = 7;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
    func_80094E34();
    if (!(func_800A6D30() & 1)) {
        func_80042B68(arg3, 1);
        func_80042B68(arg3, 4);
        func_80042B68(arg3, 2);
    }
    {
        register s32 mask ASM_REG("$3") = 0x20000000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & mask) {
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = (s16) D_800E3E41;
        }
    }
}
