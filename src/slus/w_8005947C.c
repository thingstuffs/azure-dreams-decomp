#include "common.h"

#include "common.h"

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3c;
    s32 f40;
    s32 f44;
    s8 f48;
    u8 f49;
    u8 f4a;
    s8 f4b;
    s8 f4c;
    s8 f4d[3];
} S_80085FA8;

extern s32 D_800737DC[16];
extern s32 func_800589B8(S_80085FA8 *a0);
extern void func_80058E64(void);
extern void func_80058E6C(S_80085FA8 *a0, s32 a1);
extern void func_800590E0(S_80085FA8 *a0);
extern s32 func_8005914C(S_80085FA8 *a0, s32 a1, s32 a2, s32 a3);

/* Read and dispatch the next event, reusing the previous status when needed. */
s32 func_8005947C(S_80085FA8 *stream)
{
    s16 status;
    register s32 first_data ASM_REG("$18");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 second_data;
    register s32 data_count ASM_REG("$19");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 input_byte;
    register s32 event_byte ASM_REG("$4");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u32 status_group;
    s32 subcommand;

    second_data = 0;
    input_byte = func_800589B8(stream);
    event_byte = input_byte;
    if (!(input_byte & 0x80)) {
        status = stream->f4a;
        stream->f49 = 1;
    } else {
        status = input_byte;
        if ((event_byte & 0xFF) != 0xFF) {
            stream->f4a = input_byte;
        }
        stream->f49 = 0;
    }
    status_group = (u32)status >> 4;
    data_count = D_800737DC[status_group & 0xF];
    if (data_count != 0) {
        if (stream->f49 != 0) {
            first_data = event_byte;
        } else {
            first_data = func_800589B8(stream);
        }
        if (data_count == 2) {
            second_data = func_800589B8(stream);
        }
        func_8005914C(stream, status & 0xFF, first_data & 0xFF, second_data & 0xFF);
        return 0;
    }
    if ((event_byte & 0xFF) == 0xF0) {
        goto case_f0;
    }
    if ((event_byte & 0xFF) != 0xFF) {
        goto otherwise;
    }
    {
        subcommand = func_800589B8(stream);
        func_80058E6C(stream, subcommand & 0xFF);
        return 0;
    }
case_f0:
    func_800590E0(stream);
    return 0;
otherwise:
    func_80058E64();
    return 0;
}
