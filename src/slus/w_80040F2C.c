#include "common.h"

typedef void (*S_8006CE80_FuncPtr)(void);

/* Struct pointed to by D_8006CE80[i].handler.
 * offset 0x0: funcs      - null-terminated array of no-arg callback function pointers (this func)
 * offset 0x4: unk4       - opaque pointer, forwarded verbatim to func_8003F9E0() (see func_80041038)
 * offset 0x8: unk8       - opaque pointer, forwarded verbatim to func_8003F8F8() (see func_80040FDC)
 * offset 0xC: argList    - null-terminated array of pointers, each passed as the sole arg
 *                          to func_80041284() (see func_800411FC)
 */
typedef struct S_8006CE80_Handler {
    S_8006CE80_FuncPtr *funcs;
    void *unk4;
    void *unk8;
    void **argList;
} S_8006CE80_Handler;

/* Entry of the D_8006CE80 dispatch table, indexed by a 16-bit id (stride 12 bytes). */
typedef struct S_8006CE80 {
    u16 unk0;
    s16 unk2;
    S_8006CE80_Handler *handler;
    void *unk8;
} S_8006CE80;

extern S_8006CE80 D_8006CE80[];
extern u8 D_80082E60[];

/* Runs the id'th dispatch-table entry's list of no-arg callback functions until one of them
 * sets the flag byte at D_80082E60+0xE, in which case it returns 1 immediately. Returns 0 if
 * there's no handler, no callback array, an empty array, or every callback ran without setting
 * the flag. */
s32 func_80040F2C(u16 a0)
{
    S_8006CE80 *p;
    S_8006CE80_Handler *handler;

    p = D_8006CE80 + a0;
    handler = p->handler;
    if (handler != 0)
    {
        S_8006CE80_FuncPtr *funcs = handler->funcs;
        do
        {
            if (funcs != 0)
            {
                if ((*funcs) != 0)
                {
                    do
                    {
                        (*funcs)();
                        if (D_80082E60[0xE] != 0)
                        {
                            return 1;
                        }
                        funcs++;
                    }
                    while ((*funcs) != 0);
                }
            }
            else
            {
                return 0;
            }
        }
        while (0);
    }
    return 0;
}
