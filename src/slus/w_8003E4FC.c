#include "modules/control_cd.h"
#include "slus/cd_state.h"

typedef union ResultBox_8003E4FC {
    s32 value;
} ResultBox_8003E4FC;

typedef struct EventSource_8003E4FC {
    s32 field0;
    void *field4;
} EventSource_8003E4FC;

extern s32 enqueue_cd_command_record();

/* Dispatch supported event codes and update the associated event state. */
s32 Control_CD(s32 event_code, void *event_data, s32 payload)
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
                    result.value = 0;
                    return result.value;
                }
                if (kind < 2) {
                    if (kind == 0) {
                        goto case_0;
                    }
                    result.value = 0;
                    return result.value;
                }
                if (kind == 2) {
                    goto case_2;
                }
                result.value = 0;
                return result.value;
            }
            if (kind == 8) {
                result.value = 0;
                return result.value;
            }
            if (kind < 9) {
                if (kind == 6) {
                    goto case_6;
                }
                result.value = 0;
                return result.value;
            }
            if (kind == 9) {
                goto case_9;
            }
            if (kind == 10) {
                goto case_2;
            }
        }
        result.value = 0;
        return result.value;
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
        result.value = 0;
        return result.value;
    }
    if (kind == 0xFC) {
        goto case_9;
    }
    if (kind < 0xFD) {
        if (kind == 22) {
            result.value = 0;
            return result.value;
        }
        if (kind == 27) {
            goto case_27;
        }
        result.value = 0;
        return result.value;
    }
    if (kind == 0xFE) {
        goto case_6;
    }
    if (kind == 0xFF) {
        goto case_ff;
    }
    result.value = 0;
    return result.value;

case_0:
    call_kind = 0;
    call_arg = 0;
    result.value = enqueue_cd_command_record(call_kind, call_arg, 0);
    return result.value;

case_2:
    call_kind = (u8)event_code;
    call_arg = event_data;
    result.value = enqueue_cd_command_record(call_kind, call_arg, 0);
    return result.value;

case_ff:
    result.value = enqueue_cd_command_record(0xFF, event_data, payload);
    return result.value;

case_6:
    call_arg = event_data;
    D_80080ADC = ((EventSource_8003E4FC *)call_arg)->field4;
    result.value = enqueue_cd_command_record((u8)event_code, call_arg, payload);
    return result.value;

case_9:
    call_kind = (u8)event_code;
    call_arg = 0;
    result = (ResultBox_8003E4FC) {
        0
    };
    result.value = enqueue_cd_command_record(call_kind, call_arg, 0);
    return result.value;

case_13:
    D_80080AD4 = 0;
    if (event_data == 0) {
        null_kind = 13;
        result.value = enqueue_cd_command_record(null_kind, 0, payload);
        return result.value;
    }
    enqueue_cd_command_record(13, 0, payload);
    enqueue_cd_command_record(2, event_data, 0);
    result.value = enqueue_cd_command_record(27, event_data, 0);
    D_80080ADC = event_data;
    return result.value;

case_14:
    null_kind = 14;
    result.value = enqueue_cd_command_record(null_kind, 0, payload);
    return result.value;

case_21:
    enqueue_cd_command_record(2, event_data, 0);
    call_kind = 21;
    call_arg = event_data;
    result.value = enqueue_cd_command_record(call_kind, call_arg, 0);
    return result.value;

case_27:
    call_kind = 27;
    call_arg = event_data;
    result.value = enqueue_cd_command_record(call_kind, call_arg, 0);
    goto done;

return_zero:
    result.value = 0;
done:
    return result.value;
}
