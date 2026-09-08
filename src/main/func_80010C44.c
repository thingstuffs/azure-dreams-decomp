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

/* Initialize four message slots with their data and command parameters. */
void func_80023C44(void *slot_owner) {
    s32 data_buffer[2];
    Slot80010C44 *slot;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x270);
    slot->msg->cmd = 0x70;
    slot->msg->arg = 0x10;
    slot->data = &D_80078FD0;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x260);
    slot->data = (void *) func_8004DA74((u8 *) slot_owner + 8, D_80083EA4 + (*(s32 *) slot_owner << 7), 1);
    slot->msg->cmd = 0xF0;
    slot->msg->arg = 0x91;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x26C);
    func_8004E5A0((void *) *(s32 *) (D_80083EA4 + (*(s32 *) slot_owner << 7) + 0x20), 4, data_buffer);
    func_8004E69C(data_buffer);
    slot->data = (void *) func_8004E298((u8 *) slot_owner + 0x104, data_buffer, 1);
    slot->msg->cmd = 0x147;
    slot->msg->arg = 0x91;

    slot = *(Slot80010C44 **) ((u8 *) slot_owner + 0x278);
    slot->data = (u8 *) slot_owner + 0x134;
    slot->msg->cmd = 0xAE;
    slot->msg->arg = 0x18;
}
