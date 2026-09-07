#include "common.h"

typedef struct S_8004B854 {
    u8 a2;
    u8 code;
} S_8004B854;

extern void func_8004B834(void);
extern void func_8003F320(void);
extern void func_8002537C(int a0, int a1, int a2, S_8004B854 *a3, int a4);

/* Dispatches record data with an entry byte and command code 0x13. */
void func_8004B854(int dispatch_arg, int record_addr, int entry_value)
{
    S_8004B854 command;
    int zero = 0;

    func_8004B834();
    command.a2 = (u8)entry_value;
    command.code = 0x13;
    func_8003F320();
    func_8002537C(dispatch_arg, zero, zero, &command, record_addr);
}
