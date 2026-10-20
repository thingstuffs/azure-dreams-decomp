#include "common.h"
#include "shared/game_work.h"

struct S_8004D70C_D80083160 {
    char pad0[0xCC];
    char f_CC[0x44];
    char f_110[0x44];
    char f_154[0x44];
    char f_198[0x44];
};

extern void run_view_slot_callback(void *a0, void *a1, s32 a2);
extern void func_8004D4AC(void);

/* Processes two dispatch-slot pairs, then rebuilds matrices. */
void run_view_callbacks(void)
{
    struct S_8004D70C_D80083160 *dispatch_table = ((struct S_8004D70C_D80083160 *)&g_game_work);
    run_view_slot_callback(&dispatch_table->f_CC, &dispatch_table->f_110, 0);
    run_view_slot_callback(&dispatch_table->f_154, &dispatch_table->f_198, 1);
    func_8004D4AC();
}
