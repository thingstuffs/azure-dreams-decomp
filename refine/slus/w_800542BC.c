#include "common.h"

#include "common.h"

/* D_80084850 accessed via %hi/%lo (lui+lw/sw); size > 8 forces non-gp. */
extern s32 D_80084850[3];

extern s32 func_800557C8(void);
extern void func_80054788(s32 a0, s32 a1);
extern void func_80054B08(s32 a0, s32 a1);
extern void func_8005500C(s32 a0, s32 a1);
extern void func_8005552C(s32 a0, s32 a1);
extern void func_800543C8(void);
extern void func_800557BC(void);

/* Dispatch commands by type until a zero code, then finalize processing. */
void func_800542BC(void) {
    s32 command_code;
    s32 command;
    s32 command_type;

    D_80084850[0] += 1;
next_command:
    command = func_800557C8();
    command_code = command & 0xFFFF;
    command_type = command & 0xF00;
    if (command_code != 0) {
        switch (command_type) {
        case 0x0:
            func_80054788(command_code, command);
            break;
        case 0x300:
            func_80054B08(command_code, command);
            break;
        case 0x200:
            func_8005500C(command_code, command);
            break;
        case 0x500:
        case 0x700:
        case 0x800:
        case 0x600:
            func_8005552C(command & 0xFFFF, command);
            break;
        }
        goto next_command;
    }
    func_800543C8();
    func_800557BC();
}
