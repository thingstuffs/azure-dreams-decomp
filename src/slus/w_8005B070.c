#include "common.h"

#include "common.h"

typedef struct {
    s16 field_0;
    s16 field_2;
    s32 field_4;
    u16 field_8;
    u16 field_A;
} S_80086C00;

typedef struct {
    s32 field_0;
    s32 field_4;
    u16 field_8;
    u16 field_A;
    u8 pad0C[0x40 - 0x0C];
} S_8005B070_req;

extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern s32 D_800737A4[4];
extern u8 D_80085458[0x78 * 64];
extern s32 D_80085F98[4];
extern S_80086C00 D_80086C00[8];

extern void func_8005F134(S_8005B070_req *arg0);

void func_8005B070(s16 arg0)
{
    S_8005B070_req req;
    u8 *p;
    register s32 i ASM_REG("$17");   /* MATCH pin: slus-diff */
    s32 *q;
    S_80086C00 *base;

    i = 0;
    D_80085F98[0] = 1;
    if (D_80073734[0] > 0) {
        q = D_80073740;
        p = D_80085458;
    loop:
        if (*(u16 *)(p + 6) < 0x10U) {
            if (*(u16 *)(p + 0x1A) != 0) {
                s32 three;
                three = 3;
                req.field_4 = three;
                req.field_0 = *q;
                req.field_8 = 0;
                req.field_A = 0;
                func_8005F134(&req);
            }
        }
        q++;
        p += 0x78;
        {
            s32 lim = D_80073734[0];
            i++;
            if (i < lim) goto loop;
        }
    }
    base = D_80086C00;
    base[arg0].field_2 = 4;
    D_80085F98[0] = 0;
    D_800737A4[0] = 0;
}
