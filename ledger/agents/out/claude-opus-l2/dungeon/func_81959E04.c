#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(s32);                         /* extern */
void func_8004491C(void *, void *);                /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
extern M2C_UNK D_80025528;
extern u8 D_800C95C0[12];

typedef struct S_81959E04_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_81959E04_0;   /* obj in func_81959E04 */

typedef struct S_81959E04_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81959E04_1;   /* part in func_81959E04 */

typedef struct S_81959E04_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x28];
    s16 unk_30;
} S_81959E04_2;   /* info in func_81959E04 */

/* Spawn a ring of 32 spark objects around (x, y, z), each with the velocity of its angle step. */
void *func_81959E04(s16 x, s16 y, s16 z) {
    s32 angle;
    register S_81959E04_1 *part ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *obj;
    s32 i;
    s32 scale;
    register s32 sign_bits ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 pos_x ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 pos_y ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s16 pos_z;
    S_81959E04_2 *info;
    void *call_arg1;

    pos_x = x;
    pos_y = y;
    pos_z = z;
    i = 0;
    sign_bits = -0x800;
    scale = 0x20;
    angle = i;
spawn_next:
    obj = func_8003FC64(0x212);
    if (obj != NULL) {
        register void *call_arg0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register void *field_ptr ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        call_arg1 = D_800C95C0;
#else
        call_arg1 = (void *)0x800D0000;
        call_arg1 = D_800C95C0;
#endif
        call_arg0 = obj;
        field_ptr = &D_80025528;
        ((S_81959E04_0 *)obj)->unk_10 = field_ptr;
        func_8004491C(call_arg0, call_arg1);
        part = ((S_81959E04_0 *)obj)->unk_08;
        part->unk_02 = pos_x;
        part->unk_06 = pos_y;
        part->unk_0A = pos_z;
        if (func_80064584(angle) & 0x800) {
            part->unk_0C = (s32) ((func_80064584(angle) | sign_bits) << 0xB);
        } else {
            part->unk_0C = (s32) ((func_80064584(angle) & 0x7FF) << 0xB);
        }
        if (func_800644B8(angle) & 0x800) {
            part->unk_10 = (s32) ((func_800644B8(angle) | sign_bits) << 0xB);
        } else {
            part->unk_10 = (s32) ((func_800644B8(angle) & 0x7FF) << 0xB);
        }
        part->unk_14 = 0xFFFE0000;
        info = obj + 0x20;
        (*(s16 *)((u8 *)obj + 0x20)) = scale;
        info->unk_02 = scale;
        info->unk_04 = 1;
        info->unk_06 = 0;
        info->unk_30 = scale;
        goto next;
    }
next:
    i += 1;
    angle += 0x80;
    if (i >= 0x20) {
        return obj;
    }
    goto spawn_next;
}
/* MECHANISM: The 0x38 frame comes from ten held roles: s6/s7/fp args, s3/s0 loop state,
   s5/s4 constants, and s2/s1 object bases; a kept s3 preserves move s0,s3.
   Tied tail-slot pins sink both dead v0|s5 values into noreturn j delays.
   A kept a1 page/low split plus fixed a0/a3 emits the call setup in retail order. */
