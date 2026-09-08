#include "common.h"
#include "records/Rec_func_80025D28_arg0.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


/* Initialize the packet fields with payload 0xB8C8 and set flag 0x80. */
void func_80025D28(Rec_func_80025D28_arg0 *packet) {
    volatile s32 initial_payload;
    s32 payload;
    u8 flags;

    initial_payload = 0xB8C8;
    packet->unk_01 = 0x28;
    payload = initial_payload;
    flags = packet->unk_00;
    packet->unk_02 = 2;
    packet->unk_03 = 2;
    packet->unk_0A = 0xC;
    packet->unk_0B = 0xC;
    packet->unk_04 = payload;
    packet->unk_00 = (u8)(flags | 0x80);
}
