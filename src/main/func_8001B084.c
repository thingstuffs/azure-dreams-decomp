#include "common.h"

extern void func_80401BF4(void *arg0, s32 arg1);
extern void func_8007CAD8(void *arg0, void *arg1);
extern void func_80401F98(s32 arg0);
extern s32 func_80401D28(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_80401ED4(s32 arg0, s32 arg1);
extern u8 D_8009DDD8[];

/* Processes an entry using its table value and a temporary slot-5 buffer. */
s32 func_8001B084(s32 entry_id, s32 request_id) {
    u8 entry_buffer[32];
    u8 work_buffer[32];
    s32 entry_offset;
    s32 result;

    func_80401BF4(entry_buffer, entry_id);
    func_80401BF4(work_buffer, 5);
    entry_offset = entry_id << 7;
    if (*(s32 *)(D_8009DDD8 + entry_offset) != 0) {
        func_8007CAD8(entry_buffer, work_buffer);
    }
    func_80401F98(request_id);
    result = func_80401D28(work_buffer, request_id, 0xC0, 0, *(s32 *)(D_8009DDD8 + entry_offset));
    if (result != 0) {
        func_80401ED4(entry_id, request_id);
    }
    func_8007CAD8(work_buffer, entry_buffer);
    return result;
}
