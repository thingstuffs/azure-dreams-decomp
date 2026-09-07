/* Bounded site-map pass: D_800DD720 is a pointer object in retail, not an
 * inline byte array.  Preserve that pointer live range for the case-4 path. */
#include "common.h"

typedef struct { u8 unk0; u8 unk1; s8 unk2; u8 unk3; } FuncData;
typedef struct { u8 pad[0x1C]; s32 flags; } FuncState;

extern void *func_8003AD08();
extern void *func_80099194();
extern void *func_800992A8();
extern void *func_800992E8();
extern u8 *D_800DD720;
extern s32 D_800DD72C[];
extern s32 D_800DD784[];
extern FuncState *D_800E3D7C;

u8 *func_80099368(FuncData *arg0, u8 *arg1) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_s1;
    u8 temp_a1;
    u8 temp_a1_2;
    u8 temp_v0;
    u8 *temp_a2;
    u8 *temp_s0;
    u8 *temp_v0_2;
    u8 *var_a2;

    var_a2 = arg1;
    if (!(D_800E3D7C->flags & 0x10)) {
        temp_a1 = arg0->unk1;
        temp_a0 = D_800DD72C[temp_a1];
        if ((temp_a0 != 0) && ((temp_a1 != 0xF) || (arg0->unk0 < 0xEU))) {
            var_a2 = func_80099194(temp_a0, var_a2, var_a2);
        }
    }
    var_a2 = func_800992E8(arg0, var_a2, var_a2);
    if (D_800E3D7C->flags & 0x10) {
        goto return_var_a2;
    }
    temp_a1_2 = arg0->unk1;
    temp_a0_2 = D_800DD784[temp_a1_2];
    if ((temp_a0_2 != 0) && ((temp_a1_2 != 0xF) || (arg0->unk0 < 0xEU))) {
        var_a2 = func_80099194(temp_a0_2, var_a2, var_a2);
    }
    temp_v0 = arg0->unk1;
    switch (temp_v0) {
    case 4:
        if (!(arg0->unk3 & 0x80)) {
            /* Retail loads the pointer object once into the long-lived s0
             * role, then walks both byte streams across the helper call. */
            temp_s0 = D_800DD720;
            var_s1 = arg0->unk2;
            *var_a2++ = *temp_s0++;
            *var_a2 = *temp_s0++;
            temp_v0_2 = func_8003AD08(var_s1, var_a2 + 1, var_a2);
            var_a2 = temp_v0_2;
            *var_a2++ = *temp_s0++;
            *var_a2++ = *temp_s0++;
        }
        break;
    case 14:
    case 18:
    case 19:
    case 21:
        break;
    default:
        if (!(arg0->unk3 & 0x80)) {
            var_s1 = arg0->unk2;
            if (var_s1 != 0) {
                var_a2 = func_800992A8(var_s1, var_a2, var_a2);
                if (var_s1 < 0) var_s1 = -var_s1;
                var_a2 = func_8003AD08(var_s1, var_a2, var_a2);
            }
        }
        break;
    }
return_var_a2:
    return var_a2;
}
