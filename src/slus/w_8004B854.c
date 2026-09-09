#include "common.h"

typedef struct S_8004B854 {
    u8 a2;
    u8 code;
} S_8004B854;

extern void load_bin_nametwin(void);
extern void func_8003F320(void);
extern void func_8002537C(int a0, int a1, int a2, S_8004B854 *a3, int a4);

/* Sends a packet containing the entry byte and command code 0x13 to the target. */
void func_8004B854(int target, int record_addr, int entry_value)
{
    S_8004B854 local_packet;
    int zero = 0;

    load_bin_nametwin();
    local_packet.a2 = (u8)entry_value;
    local_packet.code = 0x13;
    func_8003F320();
    func_8002537C(target, zero, zero, &local_packet, record_addr);
}
