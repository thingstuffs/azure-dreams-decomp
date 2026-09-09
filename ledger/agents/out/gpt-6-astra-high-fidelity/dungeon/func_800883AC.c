#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"


typedef struct S_8008DB0C_1 {
    u8 pad_00[0x8A];
    s16 unk_8A;
} S_8008DB0C_1;   /* call_obj in func_8008DB0C */



extern void func_80048A44(void *, u8, s32, s32);
extern s32 func_80098C80(s32);
extern void func_8009F644(void *, s32, s16, s32);

extern s32 D_80082EB0;
extern s16 D_80083228;
extern u8 D_800DD130[];

void func_8008DB0C(void *arg0, s32 arg1, void *arg2, s32 arg3, u16 arg4) {
    u8 *table = D_800DD130;
    s32 value;
    register s32 held3 ASM_REG("$16") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_s8 = 0x26;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
    func_80048A44(
        arg2,
        table[((D_80083228 + ((Rec_func_8008ACDC_arg0 *)arg0)->unk_2A + 0x100) >> 9) & 7],
        0,
        1);

    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_72 = held3;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_73 = (s8)arg4;

    {
        s32 call_kind;
        register void *call_obj ASM_REG("$4");   /* MATCH: retain the seed a0 role for the arm-local field loads. */
        s32 call_field;
        register s32 zero_arg ASM_REG("$7");   /* MATCH: retain the seed a3 role through the shared call. */

        if (D_80082EB0 != 0) {
            value = func_80098C80(D_80082EB0);
            call_obj = arg0;
            call_kind = 0x68;
            call_field = ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8A;
            zero_arg = (s16)value;
        } else {
            call_kind = 0x88;
            ASM_KEEP(call_kind);   /* MATCH: retain the seed call-kind materialization in the branch delay slot. */
            call_obj = arg0;
            call_field = ((S_8008DB0C_1 *)call_obj)->unk_8A;
            zero_arg = 0;
            ASM_USE2(call_field, zero_arg);   /* MATCH: retain the seed argument ordering and nop call delay slot. */
        }
        func_8009F644(call_obj, call_kind, call_field, zero_arg);
    }
}

/* MECHANISM: The seed already held the 0x20 frame and s2/s1/s0 roles exactly.
   Final-call register locals materialize a0/a2/a3 in retail order; ASM_USE2
   keeps a2/a3 before jal so the required call delay slot remains a nop. */
