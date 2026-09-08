#include "common.h"

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

/* Processes the indexed table entry and copies the two request results to the output pointers. */
s32 func_8005C710(s16 entry_index, s16 *out_first_value, s16 *out_second_value) {
    S_8005C710_Req request;

    request.field4 = 0;
    request.field0 = D_80073740[entry_index];
    func_8005FA34(&request);
    *out_first_value = request.field8;
    *out_second_value = request.fieldA;
    return 0;
}
