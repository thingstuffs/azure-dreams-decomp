#include "common.h"

extern int get_cd_command_queue_depth(void);
extern void func_8003CB08(void);
extern void func_80044618(int);
extern void func_8003E758(void);

/* Repeat the update sequence while get_cd_command_queue_depth reports pending work. */
void drain_cd_command_queue(void)
{
    while (get_cd_command_queue_depth()) {
        func_8003CB08();
        func_80044618(2);
        func_8003E758();
    }
}
