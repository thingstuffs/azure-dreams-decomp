#include "common.h"

extern s32 func_8004DA74(void *a0, void *a1, s32 a2);
extern s32 func_8004E298(void *a0, void *a1, s32 a2);
extern void func_8004E5A0(void *a0, s32 a1, void *a2);
extern void func_8004E69C(void *a0);

extern u8 D_80078FD0[16];
extern u8 D_80083EA4[0x8000];

typedef struct {
    u8 pad[8];
    s16 cmd;
    s16 arg;
} Msg80010C44;

typedef struct {
    void *data;
    Msg80010C44 *msg;
} Slot80010C44;

void func_80023C44(void *arg0) {
    s32 sp10[2];
    Slot80010C44 *slot;

    slot = *(Slot80010C44 **) ((u8 *) arg0 + 0x270);
    slot->msg->cmd = 0x70;
    slot->msg->arg = 0x10;
    slot->data = &D_80078FD0;

    slot = *(Slot80010C44 **) ((u8 *) arg0 + 0x260);
    slot->data = (void *) func_8004DA74((u8 *) arg0 + 8, D_80083EA4 + (*(s32 *) arg0 << 7), 1);
    slot->msg->cmd = 0xF0;
    slot->msg->arg = 0x91;

    slot = *(Slot80010C44 **) ((u8 *) arg0 + 0x26C);
    func_8004E5A0((void *) *(s32 *) (D_80083EA4 + (*(s32 *) arg0 << 7) + 0x20), 4, sp10);
    func_8004E69C(sp10);
    slot->data = (void *) func_8004E298((u8 *) arg0 + 0x104, sp10, 1);
    slot->msg->cmd = 0x147;
    slot->msg->arg = 0x91;

    slot = *(Slot80010C44 **) ((u8 *) arg0 + 0x278);
    slot->data = (u8 *) arg0 + 0x134;
    slot->msg->cmd = 0xAE;
    slot->msg->arg = 0x18;
}
