#include "common.h"

/* Looks up D_80073740[a0] into a 0x40-byte stack request record (same size/shape as the D_80084918 request struct used by sibling functions), calls func_8005FA34 with it, and copies back the two s16 fields it fills in via the out-pointers a1/a2. Always returns 0. */
extern s32 D_80073740[64];

/* Local request record built on the stack and handed to func_8005FA34.
 * Same overall layout/size (0x40 bytes) as the D_80084918 request struct
 * used by sibling functions (func_800563B0 etc): field0/field4 set here,
 * field8/fieldA read back after the call; remaining bytes are written
 * internally by func_8005FA34 but unused by this caller. */
typedef struct S_8005C710_Req {
    /* 0x00 */ s32 field0;
    /* 0x04 */ s32 field4;
    /* 0x08 */ s16 field8;
    /* 0x0A */ s16 fieldA;
    /* 0x0C */ u8 pad0C[0x40 - 0x0C];
} S_8005C710_Req;

extern s32 func_8005FA34(S_8005C710_Req *arg);

s32 func_8005C710(s16 a0, s16 *a1, s16 *a2) {
    S_8005C710_Req tmp;

    tmp.field4 = 0;
    tmp.field0 = D_80073740[a0];
    func_8005FA34(&tmp);
    *a1 = tmp.field8;
    *a2 = tmp.fieldA;
    return 0;
}
