#include "common.h"

typedef s32 Callback(s32);

typedef struct S_8001B828_0 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 pad_05[0x1B];
    void * unk_20;
} S_8001B828_0;   /* obj in func_8001B828 */

typedef struct S_8001B828_1 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_8001B828_1;   /* final_obj in func_8001B828 */


extern void func_80019730(s32, void *);
extern s8 func_8001A4F0(void);
extern s32 func_8001A58C(s32);
extern void *func_8001B6E4(s32);
extern void *func_8001B6F8();
extern void func_8001E5F0(s32);

extern void *D_80016000;
extern s32 D_8001601C;
extern u8 D_80017774[];
extern u8 D_8001914C[];
extern u8 *D_8001E950;

/* Dispatches requests by mode, refreshing the state code before selecting a response. */
void *func_8001B828(s32 request, void *data, s32 mode) {
    register s32 call_request ASM_REG("$4") = request;
    register void *call_data ASM_REG("$5") = data;
    register s32 state_code ASM_REG("$2");
    u8 new_code;
    s32 status;
    void *context;
    S_8001B828_1 *state;
    void *response;

    if (mode == 0) {
        func_8001E5F0(0x402);
        context = D_8001E950;
        status = func_8001A58C(((S_8001B828_0 *)context)->unk_04);
        if (status == 0) {
            context = D_80016000;
            context = ((S_8001B828_0 *)context)->unk_20;
            status = (*(Callback **)((u8 *)context + 0x2D4))(0);
            if (status != 2) {
                return D_8001914C;
            }
            new_code = func_8001A4F0();
            D_8001E950[4] = new_code;
        }
        state = D_8001E950;
        state_code = state->unk_04;
        ASM_KEEP(state);
        if (state_code != 0) {
            return func_8001B6E4(state_code);
        }
        return D_8001914C;
    }
    if (mode == 1) {
        func_80019730(call_request, call_data);
        return func_8001B6F8(request, data, 1);
    }
    if (mode == 5) {
        return D_80017774;
    }
    if (mode == 4) {
        goto mode_4;
    }
    response = func_8001B6F8(request, data);
    goto done;
mode_4:
    response = &D_8001601C;
done:
    return response;
}
