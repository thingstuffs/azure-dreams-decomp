#include "modules/dungeon_ovl_7f0f7800_p07.h"

/* Kill the actor: clear its flags, fire the burst at its tile and post its death message. */
void func_80173AD4(void *work_in, void *part_a, void *part_b_in, void *actor) {
    s32 burst;
    s32 handle;
    s32 msg;
    void *msg_actor;
    s32 msg_handle;
    u8 flags71;
    u8 call_a0;
    u8 call_a1;
    s32 call_flags;
    void *work;
    void *part_b;

    flags71 = ((T_80173AD4_S_80173AD4_0 *)actor)->unk_71;
    work = work_in;
    ((T_80173AD4_S_80173AD4_0 *)actor)->unk_71 = flags71 & 0x7F;
    part_b = part_b_in;
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2BDC(actor) << 0x10) == 0)) {
        ((T_80173AD4_S_80173AD4_2 *)work)->unk_8C = 0;
        ((T_80173AD4_S_80173AD4_2 *)work)->unk_9A = 0x17;
        ((T_80173AD4_S_80173AD4_2 *)work)->unk_9B = 0;
        ((T_80173AD4_S_80173AD4_2 *)work)->unk_96 = 0;
        if (!(((T_80173AD4_S_80173AD4_2 *)work)->unk_98 & 0x8000)) {
            ((T_80173AD4_S_80173AD4_2 *)work)->unk_A6 = (u16) ((T_80173AD4_S_80173AD4_3 *)part_b)->unk_12;
            ((T_80173AD4_S_80173AD4_2 *)work)->unk_AA = (s16) (((T_80173AD4_S_80173AD4_0 *)actor)->unk_14 & 7);
        }
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) + 1);
        ((T_80173AD4_S_80173AD4_0 *)actor)->unk_6D = (u8) (((T_80173AD4_S_80173AD4_0 *)actor)->unk_6D - 1);
        call_flags = ((T_80173AD4_S_80173AD4_0 *)actor)->unk_1C & 0x2000;
        call_a0 = ((T_80173AD4_S_80173AD4_3 *)part_b)->unk_24;
        call_a1 = ((T_80173AD4_S_80173AD4_3 *)part_b)->unk_25;
        burst = 0x3000;
        if (call_flags) {
            burst = 0x300;
        }
        func_8009A3D0(call_a0, call_a1, burst);
        ((T_80173AD4_S_80173AD4_0 *)actor)->unk_1C = (s32) (((T_80173AD4_S_80173AD4_0 *)actor)->unk_1C & ~0x2000);
        func_8009A21C(((T_80173AD4_S_80173AD4_3 *)part_b)->unk_24, ((T_80173AD4_S_80173AD4_3 *)part_b)->unk_25, 0x3000);
        (*(u8 **)((u8 *)part_b + 0x2C)) = D_80173FD0;
        func_80047784(part_b, D_80173FD0[((gameWork.view.viewAngle + ((T_80173AD4_S_80173AD4_0 *)actor)->unk_2A + 0x100)
            >> 9) & 7], 0);
        msg = func_800990FC();
        msg_actor = actor;
        msg_handle = msg;
        msg = func_80099734(msg_actor, msg_handle);
        handle = msg_handle;
        func_80099290(func_80099194(&D_80170854, msg));
        func_800A5720(handle);
    }
}
