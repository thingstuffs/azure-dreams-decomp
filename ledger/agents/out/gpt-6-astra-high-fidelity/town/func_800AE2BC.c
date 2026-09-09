#include "common.h"

extern int rand(void);
#ifndef NON_MATCHING
extern void *D_80089140[15];
#endif

typedef struct {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s8 unk2;
    /* 0x3 */ s8 unk3;
} Struct800AE2BC;

void func_800ABA1C(Struct800AE2BC *arg0) {
    register s32 s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 s1;
    register Struct800AE2BC *self = arg0;
    s32 value;
#ifndef NON_MATCHING
    u32 index;
    static void *const keepalive[4] = {
        &&case_4, &&case_15, &&case_18, &&case_14
    };
#endif

    s0 = s1 = 0;
#ifndef NON_MATCHING
    index = self->unk1 - 4;
    if (index >= 15) {
        goto done;
    }
    goto *D_80089140[index];
#else
    switch (self->unk1) {
    case 4:
#endif
case_4:
        s0 = (rand() & 7) | 4;
        goto done;
#ifdef NON_MATCHING
    case 15:
    case 16:
    case 17:
#endif
case_15:
        s1 = -128;
        if ((rand() & 3) != 0) {
            goto done;
        }
        value = (rand() & 3) - 1;
        s0 = value;
        if (value >= 0) {
            goto done;
        }
        s1 = -64;
        goto done;
#ifdef NON_MATCHING
    case 18:
#endif
case_18:
        s0 = rand() % 40 + 60;
        goto done;
#ifdef NON_MATCHING
    case 14:
#endif
case_14:
        s0 = 1;
        s1 = 0;
#ifdef NON_MATCHING
        break;
    }
#endif
done:
    self->unk2 = s0;
    self->unk3 = s1;
}
