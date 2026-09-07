#include "common.h"

typedef struct S_8009A3A4_0 {
    u8 pad_00[0x44];
    void * unk_44;
} S_8009A3A4_0;   /* arg0 in func_8009A3A4 */

typedef struct S_8009A3A4_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A3A4_1;   /* call_arg0 in func_8009A3A4 */

typedef struct S_8009A3A4_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A3A4_2;   /* ((S_8009A3A4_0 *)arg0)->unk_44 in func_8009A3A4 */



extern s32 func_80094984();
extern s32 func_80098928();
extern u8 D_80082660;

/* Run the object's indexed handler, clear its table flag, and reset its state. */
void func_8009A3A4(S_8009A3A4_0 *object, s32 position, s32 context) {
    register s32 saved_position ASM_REG("$18") = position;   /* MATCH pin: load-bearing for the whole function shape */

    ASM_KEEP(saved_position);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80094984(((S_8009A3A4_2 *)(object->unk_44))->unk_14, object);
    {
        register void *reset_object ASM_REG("$4") = object;   /* MATCH pin: retail schedule: same instructions, different order without it */
        s32 reset_position = saved_position;
        s32 reset_context = context;

        ASM_KEEP(reset_position);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ASM_KEEP(reset_context);   /* MATCH pin: retail schedule: same instructions, different order without it */
        *(&D_80082660 + (((S_8009A3A4_1 *)reset_object)->unk_40 * 8)) = 0;
        func_80098928(reset_object, reset_position, reset_context);
    }
}

/* MECHANISM: The call-spanning arguments are held in retail's s0/s2/s1 roles,
   producing the 0x20 frame and save sequence. Guarded a0/a1/a2 staging precedes
   the byte-table address, whose clear fills the second call's delay slot. */
