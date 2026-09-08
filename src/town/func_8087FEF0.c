/* cfail-repair baseline: preserve the selected draft's recovered shape. */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define CARRY 0
#define OVERFLOW(a) (0)

typedef struct {
    u8 pad00[0x68];
    void (*func68)(void *, void *, s32);
} CallbackTable;

extern void func_80700BC4(s32 arg0);
extern void func_80700C54(s32 arg0);
extern s32 func_80700E3C(void);
extern void func_80700E98(void);
extern void func_80701298(s32 arg0, s32 arg1);

extern s32 D_807013A4[];
extern volatile s32 D_807009B0;
extern volatile s32 D_807009B4;
extern CallbackTable *volatile D_807013B4;
extern u8 D_80700B30[];
extern u8 D_80700B44[];

s32 func_8087FEF0(void) {
    s32 *base = D_807013A4;
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

#ifdef NON_MATCHING
    zero = 0;
#endif
    func_80700BC4(base[0]);
    func_80700C54(zero);
    func_80700E98();
    {
        s32 value = func_80700E3C();
        CallbackTable *table = D_807013B4;

        D_807009B0 = value;
        table->func68(D_80700B30, D_80700B44, zero | 0xC9);
    }
    func_80700BC4(base[0]);
    func_80701298(D_807009B0, D_807009B4);
    return D_807009B0;
}
