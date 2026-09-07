#include "common.h"

#include "common.h"

typedef struct {
    s8 pad00[0x10];
    s32 f10;
    s8 pad14[0x10];
    u16 f24;
    s8 pad26[6];
    s32 f2c;
    s8 pad30[0xC];
    s32 f3c;
    s8 pad40[0x10];
} Entity;

extern s32 D_800869B4[3];
extern Entity D_80085FA8[];
extern s32 D_800737C4[4];
extern s32 D_800737C8[4];
extern void func_8005947C(Entity *);
extern s32 func_800595C0(Entity *);
extern s32 func_80058A04(Entity *);
extern void func_80059814(Entity *);

s32 func_80059BC4(void)
{
    unsigned int i;
    Entity *p;
    s32 v1;
    s32 tmp;
    s32 amount;

    i = 0;
    if (D_800869B4[0] == 0) {
        return 0;
    }
    p = D_80085FA8;
    do {
        if (p->f2c != 0) {
            goto next;
        }
        amount = p->f24;
        v1 = p->f3c;
        v1 = v1 + amount;
        p->f3c = v1;
        if ((unsigned int)v1 < 0x100) {
            goto next;
        }
        tmp = p->f10;
        p->f3c = v1 & 0xFF;
        if (tmp == 0) {

loop_top:
            if (D_800737C8[0] == 2) {
                goto decode_check;
            }
            func_8005947C(p);
            goto decode;

decode_check:
            if ((func_800595C0(p) & 0xFF) != 0) {
                goto decode_nonzero;
            }
decode:
            if (p->f2c != 0) {
                goto after_loop;
            }
            p->f10 = func_80058A04(p);
            goto post_decode;
decode_nonzero:
            if (p->f2c != 0) {
                goto after_loop;
            }
post_decode:
            if (p->f10 == 0) {
                goto loop_top;
            }
            if (D_800737C4[0] != 0) {
                func_80059814(p);
            }
            if (p->f10 == 0) {
                goto loop_top;
            }
after_loop:
            if (p->f10 != 0) {
                p->f10 -= 1;
            }
        } else {
            p->f10 = tmp - 1;
        }
next:
        amount = D_800869B4[0];
        i++;
        p++;
    } while (i < (unsigned int)amount);
    return 0;
}
