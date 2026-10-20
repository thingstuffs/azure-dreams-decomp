#include "modules/control_cd.h"
#include "engine/scene/cd_state.h"

typedef struct EventSource_8003E4FC {
    s32 field0;
    void *field4;
} EventSource_8003E4FC;

extern s32 enqueue_cd_command_record();

/* Dispatch supported event codes and update the associated event state. */
s32 Control_CD(s32 event_code, void *event_data, s32 payload)
{
    s32 result;

    switch (event_code & 0xFF) {
    case 0:
        return enqueue_cd_command_record(0, 0, 0);
    case 2:
    case 10:
        return enqueue_cd_command_record((u8)event_code, event_data, 0);
    case 0xFF:
        return enqueue_cd_command_record(0xFF, event_data, payload);
    case 6:
    case 0xFE:
        cd_event_payload = ((EventSource_8003E4FC *)event_data)->field4;
        return enqueue_cd_command_record((u8)event_code, event_data, payload);
    case 9:
    case 0xFC:
        return enqueue_cd_command_record((u8)event_code, 0, 0);
    case 13:
        cd_retry_counters_pending = 0;
        if (event_data == 0) {
            return enqueue_cd_command_record(13, 0, payload);
        }
        enqueue_cd_command_record(13, 0, payload);
        enqueue_cd_command_record(2, event_data, 0);
        result = enqueue_cd_command_record(27, event_data, 0);
        cd_event_payload = event_data;
        return result;
    case 14:
        return enqueue_cd_command_record(14, 0, payload);
    case 21:
        enqueue_cd_command_record(2, event_data, 0);
        return enqueue_cd_command_record(21, event_data, 0);
    case 27:
        return enqueue_cd_command_record(27, event_data, 0);
    case 1:
    case 4:
    case 8:
    case 11:
    case 12:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 22:
        /* Known event codes that queue no command. */
        return 0;
    }
    return 0;
}
