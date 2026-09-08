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
} S_8005B16C_req;

extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern s32 D_800737A4[4];
extern u8 D_80085458[0x78 * 64];
extern s32 D_80085F98[4];
extern S_80086C00 D_80086C00[8];

extern void func_8005F134(S_8005B16C_req *arg0);

/* Dispatches type-3 requests for active channels and marks the selected slot active. */
void func_8005B16C(s16 slot_index)
{
    S_8005B16C_req request;
    u8 *channel;
    register s32 channel_index ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it slus-diff; the source shape that makes it unnecessary has not been found */
    s32 *channel_flags;
    S_80086C00 *slots;

    channel_index = 0;
    D_80085F98[0] = 1;
    if (D_80073734[0] > 0) {
        channel_flags = D_80073740;
        channel = D_80085458;
    loop:
        if (*(u16 *)(channel + 6) < 0x10U) {
            if (*(u16 *)(channel + 0x1A) != 0) {
                s32 request_type;
                request_type = 3;
                request.field_4 = request_type;
                request.field_0 = *channel_flags;
                request.field_8 = *(u16 *)(channel + 0x10);
                request.field_A = *(u16 *)(channel + 0x12);
                func_8005F134(&request);
            }
        }
        channel_flags++;
        channel += 0x78;
        {
            s32 channel_count = D_80073734[0];
            channel_index++;
            if (channel_index < channel_count) goto loop;
        }
    }
    slots = D_80086C00;
    slots[slot_index].field_2 = 1;
    D_800737A4[0] = 1;
    D_80085F98[0] = 0;
}
