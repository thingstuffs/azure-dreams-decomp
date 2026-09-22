#include "common.h"
#include "m2c_compat.h"

typedef struct S_80173AD4_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80173AD4_0;   /* actor in func_80173AD4 */

typedef struct S_80173AD4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173AD4_1;   /* state in func_80173AD4 */

typedef struct S_80173AD4_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x2];
    s16 unk_AA;
} S_80173AD4_2;   /* work in func_80173AD4 */

typedef struct S_80173AD4_3 {
    u8 pad_00[0x12];
    u16 unk_12;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
} S_80173AD4_3;   /* part_b in func_80173AD4 */


M2C_UNK func_80047784();         /* extern */
s32 func_800990FC();                                /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                         /* extern */
s32 func_80099734();                     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_80170854[];
extern u8 D_80173FD0[];

/* Kill the actor: clear its flags, fire the burst at its tile and post its death message. */
void func_80173AD4(void *work_in, void *part_a, void *part_b_in, void *actor) {
    M2C_UNK burst;
    s32 handle;
    s32 msg;
    void *msg_actor;
    s32 msg_handle;
    u8 flags71;
    u8 call_a0;
    u8 call_a1;
    s32 call_flags;
    void *work;
    void *part_b;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *state;

    flags71 = ((S_80173AD4_0 *)actor)->unk_71;
    work = work_in;
    ((S_80173AD4_0 *)actor)->unk_71 = flags71 & 0x7F;
    state = (u8 *)&D_80083460;
    part_b = part_b_in;
    if (!(((S_80173AD4_1 *)state)->unk_02 & 0x2000) && ((func_800A2BDC(actor) << 0x10) == 0)) {
        ((S_80173AD4_2 *)work)->unk_8C = 0;
        ((S_80173AD4_2 *)work)->unk_9A = 0x17;
        ((S_80173AD4_2 *)work)->unk_9B = 0;
        ((S_80173AD4_2 *)work)->unk_96 = 0;
        if (!(((S_80173AD4_2 *)work)->unk_98 & 0x8000)) {
            ((S_80173AD4_2 *)work)->unk_A6 = (u16) ((S_80173AD4_3 *)part_b)->unk_12;
            ((S_80173AD4_2 *)work)->unk_AA = (s16) (((S_80173AD4_0 *)actor)->unk_14 & 7);
        }
        ((S_80173AD4_1 *)state)->unk_0A = (u16) (((S_80173AD4_1 *)state)->unk_0A + 1);
        ((S_80173AD4_0 *)actor)->unk_6D = (u8) (((S_80173AD4_0 *)actor)->unk_6D - 1);
        call_flags = ((S_80173AD4_0 *)actor)->unk_1C & 0x2000;
        call_a0 = ((S_80173AD4_3 *)part_b)->unk_24;
        call_a1 = ((S_80173AD4_3 *)part_b)->unk_25;
        burst = 0x3000;
        if (call_flags) {
            burst = 0x300;
        }
        func_8009A3D0(call_a0, call_a1, burst);
        ((S_80173AD4_0 *)actor)->unk_1C = (s32) (((S_80173AD4_0 *)actor)->unk_1C & ~0x2000);
        func_8009A21C(((S_80173AD4_3 *)part_b)->unk_24, ((S_80173AD4_3 *)part_b)->unk_25, 0x3000);
        (*(u8 **)((u8 *)part_b + 0x2C)) = D_80173FD0;
        func_80047784(part_b, D_80173FD0[((D_80083228 + ((S_80173AD4_0 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
        msg = func_800990FC();
        msg_actor = actor;
        msg_handle = msg;
        msg = func_80099734(msg_actor, msg_handle);
        handle = msg_handle;
        func_80099290(func_80099194(&D_80170854, msg));
        func_800A5720(handle);
    }
}
