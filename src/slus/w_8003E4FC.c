#include "common.h"

typedef union ResultBox_8003E4FC {
    s32 value;
} ResultBox_8003E4FC;

typedef struct EventSource_8003E4FC {
    s32 field0;
    void *field4;
} EventSource_8003E4FC;

extern s16 D_80080AD4;
extern void *D_80080ADC;
extern s32 func_8003E39C();

/* Dispatch supported event codes and update the associated event state. */
s32 func_8003E4FC(s32 event_code, void *event_data)
{
    ResultBox_8003E4FC result;
    s32 kind;
    s32 call_kind;
    s32 null_kind;
    void *call_arg;

    kind = event_code & 0xFF;
    if (kind < 13) {
        if (kind < 11) {
            if (kind == 4) {
                goto return_zero;
            }
            if (kind < 5) {
                if (kind == 1) {
                    goto return_zero;
                }
                if (kind < 2) {
                    if (kind == 0) {
                        goto case_0;
                    }
                    goto return_zero;
                }
                if (kind == 2) {
                    goto case_2;
                }
                goto return_zero;
            }
            if (kind == 8) {
                goto return_zero;
            }
            if (kind < 9) {
                if (kind == 6) {
                    goto case_6;
                }
                goto return_zero;
            }
            if (kind == 9) {
                goto case_9;
            }
            if (kind == 10) {
                goto case_2;
            }
        }
        goto return_zero;
    }

    if (kind == 21) {
        goto case_21;
    }
    if (kind < 22) {
        if (kind == 14) {
            goto case_14;
        }
        if (kind < 14) {
            goto case_13;
        }
        goto return_zero;
    }
    if (kind == 0xFC) {
        goto case_9;
    }
    if (kind < 0xFD) {
        if (kind == 22) {
            goto return_zero;
        }
        if (kind == 27) {
            goto case_27;
        }
        goto return_zero;
    }
    if (kind == 0xFE) {
        goto case_6;
    }
    if (kind == 0xFF) {
        goto case_ff;
    }
    goto return_zero;

case_0:
    call_kind = 0;
    call_arg = 0;
    goto call_three;

case_2:
    call_kind = (u8)event_code;
    goto call_with_data;

case_ff:
    result.value = func_8003E39C(0xFF, event_data);
    goto done;

case_6:
    call_arg = event_data;
    D_80080ADC = ((EventSource_8003E4FC *)call_arg)->field4;
    result.value = func_8003E39C((u8)event_code, call_arg);
    goto done;

case_9:
    call_kind = (u8)event_code;
    call_arg = 0;
    result = (ResultBox_8003E4FC){ 0 };
    goto call_three;

case_13:
    D_80080AD4 = 0;
    if (event_data == 0) {
        null_kind = 13;
        goto call_null;
    }
    func_8003E39C(13, 0);
    func_8003E39C(2, event_data, 0);
    result.value = func_8003E39C(27, event_data, 0);
    D_80080ADC = event_data;
    goto done;

case_14:
    null_kind = 14;
call_null:
    result.value = func_8003E39C(null_kind, 0);
    goto done;

case_21:
    func_8003E39C(2, event_data, 0);
    call_kind = 21;
    goto call_with_data;

case_27:
    call_kind = 27;
call_with_data:
    call_arg = event_data;
call_three:
    result.value = func_8003E39C(call_kind, call_arg, 0);
    goto done;

return_zero:
    result.value = 0;
done:
    return result.value;
}
