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

/* Process eligible entries and set the selected slot state to 4. */
void func_8005B070(s16 slot_index)
{
    S_8005B070_req request;
    u8 *entry;
    register s32 entry_index ASM_REG("$17");   /* MATCH pin: slus-diff */
    s32 *entry_id;
    S_80086C00 *slots;

    entry_index = 0;
    D_80085F98[0] = 1;
    if (D_80073734[0] > 0) {
        entry_id = D_80073740;
        entry = D_80085458;
    loop:
        if (*(u16 *)(entry + 6) < 0x10U) {
            if (*(u16 *)(entry + 0x1A) != 0) {
                s32 request_type;
                request_type = 3;
                request.field_4 = request_type;
                request.field_0 = *entry_id;
                request.field_8 = 0;
                request.field_A = 0;
                func_8005F134(&request);
            }
        }
        entry_id++;
        entry += 0x78;
        {
            s32 entry_count = D_80073734[0];
            entry_index++;
            if (entry_index < entry_count) goto loop;
        }
    }
    slots = D_80086C00;
    slots[slot_index].field_2 = 4;
    D_80085F98[0] = 0;
    D_800737A4[0] = 0;
}
