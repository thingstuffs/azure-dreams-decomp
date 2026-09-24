#include "slus/cd_cohort_types.h"
u8 D_800814D0 = 0;
u8 D_800814D4 = 0;
u32 D_800814CC = 0;
SlusCdResult D_80081450 = {0};
u8 D_80080AD0 = 0;
u16 D_80080AD2 = 0;
u16 D_80080AD4 = 0;
s32 D_80080AD8 = 0;
void *D_80080ADC = 0;
s32 D_800814B0 = 0;
s32 D_800814B4 = 0;

extern u8 D_800814D3[2];

/* e34c_driver_view.c */
#include "slus/cd_cohort_types.h"

/* Reset the global state fields and initialize the status bytes to 2 and 255. */
void func_8003E34C(void) {
    *(u8 *)0x800814D2 = 2;
    *(u8 *)0x800814D3 = 0xFF;
    D_80083958[0].unk0 = 0;
    D_800814D0 = 0;
    *(u8 *)0x800814D1 = 0;
    D_80083958[0].unk4 = 0;
    D_80083958[0].unk5 = 0;
    D_80080AD0 = 0;
    D_80080ADC = 0;
    D_80080AD4 = 0;
    D_80083958[0].counter1 = 0;
    D_80083958[0].counter2 = 0;
}

/* w_8003E4FC_owned.c */
#include "slus/cd_state.h"

typedef union ResultBox_8003E4FC {
    s32 value;
} ResultBox_8003E4FC;

typedef struct EventSource_8003E4FC {
    s32 field0;
    void *field4;
} EventSource_8003E4FC;

extern s32 func_8003E39C();

/* Dispatch supported event codes and update the associated event state. */
s32 Control_CD(s32 event_code, void *event_data)
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

/* e758_prefix_view.c */
#include "slus/cd_cohort_types.h"



typedef struct S_80083164 {
    u16 unk0; /* Observed prefix; enclosing extent is unknown. */
} S_80083164;


/* RETAIL jump table for the state==1 dispatch: an ABSOLUTE in
 * config/generated/slus_006.14.undefined_syms.txt (0x8002D5C0, 28 entries,
 * live cases 0/6/9/0x15/0x1B, every other index -> the `tail` block).
 * Dispatching through it means this TU emits NO compiler-generated jump table
 * into .text-referenced .rodata, which is what makes the object LINK. */
extern void *jtbl_8002D5C0[];

extern u8  D_800814D1[1];    /* Observed tail-index byte view; no storage ownership. */
    /* driver state byte: %hi/%lo; head via [-3] */
extern u8  D_800814D8[16];    /* %hi/%lo CdReadSync buffer */
extern u8  D_80081438[0x20];  /* neighbour: &D_80081438[0x18]==&D_80081450 (%hi/%lo) */
extern u32 D_80081480[8];     /* %hi/%lo */
extern S_80083164 D_80083164[];

extern int  CdSync(int mode, u8 *result);
extern int  CdControl(u8 com, u8 *param, u8 *result);
extern int  CdControlF(u8 com, u8 *param);
extern int  CdRead(int count, u32 *buf, int mode);
extern int  CdRead2(int mode);
extern int  CdReadSync(int mode, u8 *result);
extern int  CdReset(int mode);
extern void StUnSetRing(void);

extern void func_8003E70C(void);
extern void func_8003F5EC(void);
extern void func_8003F624(void);
extern void CdIntToPos(u32 lba, u8 *loc);
extern u8  D_800814D3_1[1] __asm__("D_800814D3");
extern u8  D_800814D3_2[1] __asm__("D_800814D3");
extern u8  D_800814D3_3[1] __asm__("D_800814D3");
extern u8  D_800814D3_8[1] __asm__("D_800814D3");
extern u8  D_800814D3_9[1] __asm__("D_800814D3");
extern u8  D_800814D3_10[1] __asm__("D_800814D3");
extern u8  D_800814D3_11[1] __asm__("D_800814D3");
extern u8  D_800814D3_12[1] __asm__("D_800814D3");
extern u8  D_800814D3_13[1] __asm__("D_800814D3");
extern u8  D_800814D3_14[1] __asm__("D_800814D3");
extern u8  D_800814D3_15[1] __asm__("D_800814D3");
extern u8  D_800814D3_24[1] __asm__("D_800814D3");
extern u8  D_800814D2[1];
extern u8  D_800814D2_P[1] __asm__("D_800814D2");
extern u8  D_800814D2_R[1] __asm__("D_800814D2");

#define CDBUF (&D_80081438[0x18])   /* == &D_80081450, %hi/%lo addressing */

/* Processes queued CD commands and advances pending reads and drive operations. */
void func_8003E758(void)
{
    SlusCdDriverPrefix *driver;
    SlusCdQueueEntry *queue, *command, *active_queue, *active_command;
    int state;
    int sync_result, retries;
    u8  status;
    int head_index;
    int head_stride;
    u8  location[8];
    u8  sync_status[8];

process_queue:
    driver = &D_80083958[0];
    driver->flags &= 0xFFFE;

    if (D_800814D0 == D_800814D1[0])
        goto queue_empty;

    driver->flags |= 1;
    state = D_800814D3_1[0];

    if (state == 0xFF) {
        queue = D_80083968;
        head_index = D_800814D0;
        /* head_index*24 SPLIT into two carriers (head_index*3, then <<3): one 4-ref temp for
         * the whole chain outranks the address %hi in local-alloc
         * (floor_log2(4)*4/5 vs floor_log2(2)*2/4) and steals $v0; two 2-ref
         * carriers do not, so the %hi keeps retail's $v0.  Same 3 insns. */
        head_stride = head_index * 3;
        switch (*((u8 *)queue + head_stride * 8)) {
        case 0:
            D_800814D3_2[0] = 0xFF;
            driver->unk4 = 0;
            D_800814D2[0] = 0;
            D_800814D0 = (head_index + 1) & 0x1F;
            goto process_queue;

        case 1:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 2;
            driver->unk4 = 2;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 2:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            CdIntToPos(command->unk04, location);
            if (CdControl(2, location, CDBUF) == 0) goto finish;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 6: {
            u32 *read_info;
            u32 read_word, read_addr, sector_count;
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            read_info = (u32 *)command->unk04;
            read_word = read_info[0];
            read_addr = read_word & 0x7FFFFF;
            if (read_addr == 0)
                read_addr = D_80081480[0];
            else
                read_addr = read_addr | 0x80000000;
            sector_count = read_info[0] >> 23;
            if (sector_count == 0) {
                u8 *state_ptr = &D_800814D3_3[0];
                D_800814D3[0] = 0xFF;
                state_ptr[-3] += 1;
                goto finish;
            }
            D_800814CC = (read_addr + (sector_count << 11)) - 4;
            D_800814D4 = 0x80;
            if (CdControl(0xE, &D_800814D3[1], 0) == 0) return;
            sync_result = CdSync(1, sync_status);
            if (sync_result != 0) {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) {
                    func_8003E70C();
                    return;
                }
            }
            CdIntToPos(read_info[1], location);
            if (CdControl(2, location, 0) == 0) return;
            sync_result = CdSync(1, sync_status);
            if (sync_result != 0) {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) {
                    func_8003E70C();
                    return;
                }
            }
            if (CdRead(sector_count, (u32 *)read_addr, 0x80) == 0) return;
            goto mark_pending;
        }

        case 9:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            if (CdControl(9, 0, CDBUF) == 0) goto finish;
            goto mark_pending;

        case 0xD:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            {
                int command_offset = D_800814D0 * 24;
                u8 *params = queue->unk08;
                if (CdControl(0xD, command_offset + params, CDBUF) == 0) goto finish;
            }
            D_800814D3_8[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0xE:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            {
                int command_offset = D_800814D0 * 24;
                u8 *params = queue->unk08;
                if (CdControl(0xE, command_offset + params, CDBUF) == 0) goto finish;
            }
            D_800814D3_9[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0x15:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            CdIntToPos(command->unk04, location);
            if (CdControlF(0x15, location) == 0) goto finish;
            goto mark_pending;

        case 0x1B:
            sync_result = CdSync(1, sync_status);
            if (sync_result == 0) goto finish;
            {
                int disk_error;
                disk_error = 5;
                if (sync_result == disk_error) func_8003E70C();
            }
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            command = &queue[D_800814D0];
            CdIntToPos(command->unk04, location);
            retries = 0x10;
            if (CdControl(2, location, 0) == 0) return;
            {
                int disk_error = 5;
                for (;;) {
                    sync_result = CdSync(1, sync_status);
                    retries--;
                    if (sync_result == 0) goto wait_stream_seek;
                    retries = 0x10;
                    if (sync_result != disk_error) goto start_stream;
                stream_error:
                    func_8003E70C();
                    return;
                wait_stream_seek:
                    if (retries != 0) continue;
                    goto stream_error;
                start_stream:
                    for (;;) {
                        if (CdRead2(0xC8) != 0) break;
                        if (--retries == 0) goto stream_error;
                    }
                    D_80083958[0].unk4 = 0;
                mark_pending:
                    D_800814D3_11[0] = 1;
                    goto finish;
                }
            }

        case 0xA:
            D_800814D2[0] = 0;
            driver->unk4 = 0;
            retries = 0x10;
            for (;;) {
                if (CdReset(0) != 0) break;
                if (--retries == 0) goto stream_error;
            }
            D_800814D3[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0xFF:
            (*(void (*)(u32))queue[head_index].unk04)(*(u32 *)D_80083968[D_800814D0].unk08);
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0xFC:
            StUnSetRing();
            D_800814D0 = D_800814D0 + 1;
            goto finish;

        case 0x4:
        case 0x8:
        case 0xB:
        case 0xC:
        case 0x10:
        case 0x16:
        default:
            goto finish;
        }
    } else if (state == 1) {
        /* `dispatch_labels` exists only to stop gcc deleting the case labels; it lands
         * in .rodata but is unreferenced from .text, so the linker discards it.
         * Idiom from src/w_800595C0.c / w_8004CECC.c / w_80042BDC.c. */
        static void *const dispatch_labels[] = {
            &&complete_noop, &&complete_read, &&complete_pause, &&complete_seek, &&complete_stream
        };
        u32 opcode;
        int completion_offset;
        (void)dispatch_labels;
        active_queue = D_80083968;
        head_index = D_800814D0;
        /* Keep one byte-offset accumulator for this completion lookup. */
        completion_offset = head_index << 1;
        completion_offset += head_index;
        completion_offset <<= 3;
        active_command = (SlusCdQueueEntry *)((u8 *)active_queue + completion_offset);
        opcode = active_command->unk00;
        if (opcode >= 0x1C) goto finish;
        goto *jtbl_8002D5C0[opcode];
        {
            complete_noop: {
                u8 *state_ptr;
                s16 idle_state;
                int old_head;
                idle_state = 0xFF;
                D_800814D3_14[0] = idle_state;
                state_ptr = &D_800814D3_13[0];
                old_head = state_ptr[-3];
                D_80083958[0].unk4 = 0;
                D_800814D2[0] = 0;
                state_ptr[-3] = (old_head + 1) & 0x1F;
                goto process_queue;
            }

            complete_read:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0) goto finish;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error) goto command_failed;
                }
                D_80080AD8 = CdReadSync(1, D_800814D8);
                if (D_80080AD8 > 0) goto finish;
                if (D_80080AD8 != 0) goto read_failed;
                if (D_80080AD0 == 0) goto read_complete;
                if ((*(u32 *)D_800814CC & 0xFFFF0000) == 0x10120000) goto finish;
                func_8003E70C();
                D_800814D2[0] = 0;
                D_80080AD2 = D_80080AD2 + 1;
                if ((D_80080AD2 & 3) == 3) {
                    CdReset(0);
                    func_8003F5EC();
                }
                D_800814D3[0] = 0xFF;
                goto finish;
            read_complete:
                {
                    u8 *state_ptr = &D_800814D3_15[0];
                    SlusCdDriverPrefix *read_driver = &D_80083958[0];
                    D_800814D3[0] = 0xFF;
                    read_driver->unk4 = 2;
                    state_ptr[-3] += 1;
                    D_800814D2[0] = D_800814D2_R[0] | 1;
                    read_driver->unk5 = read_driver->unk5 + 1;
                    goto finish;
                }
            read_failed:
                if (D_80080AD8 >= 0) goto finish;
                goto command_failed;

            complete_pause:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0) goto finish;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error) goto command_failed;
                }
                goto check_drive_status;

            complete_seek:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0) goto finish;
                if (sync_result != 5) goto check_drive_status;
                goto command_failed;

            command_failed:
                func_8003E70C();
                D_800814D3[0] = 0xFF;
                D_80083958[0].unk4 = 0;
                D_800814D2[0] = 0;
                goto finish;

            check_drive_status:
                if (CdControl(1, 0, CDBUF) == 0) goto finish;
                if ((D_80081450.bytes[0] & 0xFD) != 0) goto finish;
                D_80083958[0].unk4 = 2;
                D_800814D3[0] = 0xFF;
                D_800814D0 = D_800814D0 + 1;
                goto finish;

            complete_stream:
                if (CdSync(1, CDBUF) == 5) {
                    D_800814D3[0] = 0xFF;
                    goto finish;
                }
                retries = 0x10;
                for (;;) {
                    if (CdControl(1, 0, CDBUF) != 0) break;
                    if (--retries == 0) {
                        func_8003E70C();
                        D_800814D3[0] = 0xFF;
                        return;
                    }
                }
                status = D_80081450.bytes[0];
                if (status & 0x40) goto finish;
                if (status & 0x20) {
                    u8 *status_ptr = &D_800814D2_P[0];
                    register SlusCdQueueEntry *stream_queue ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    SlusCdQueueEntry *stream_command;
                    stream_command = 0xFF;
                    stream_queue = D_80083968;
                    ASM_KEEP_NV(status_ptr);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    D_800814D2[0] = 0;
                    D_800814D3[0] = stream_command;
                    head_index = status_ptr[-2];
                    stream_command = &stream_queue[head_index];
                    if (stream_command->unk17 != 0xFF) {
                        D_80083958[0].unk4 = 4;
                        D_80080AD4 = 1;
                    }
                    status_ptr[-2] += 1;
                    goto finish;
                }
                if (status & 0x80) D_800814D3[0] = 0xFF;
                goto finish;

        }
    }

    goto finish;

queue_empty:
    if (CdSync(1, 0) == 5) {
        if ((func_8003F240() & 0xFF) == 0x1B) {
            D_800814D3_24[0] = 0xFF;
            if (D_800814D0 != 0)
                D_800814D0 = D_800814D0 - 1;
            else
                D_800814D0 = 0x1F;
            func_8003F624();
        } else {
            CdControl(1, 0, 0);
        }
    }

finish:
    if ((D_80083164[0].unk0 & 0x7FFF) == 0)
        D_80083958[0].counter1 = 0;
    D_800814D0 = D_800814D0 & 0x1F;
}

/* f240_owned.c */
#include "slus/cd_cohort_types.h"

u8 func_8003F240(void) {
    return D_80083968[(D_800814D0 + 0x1F) & 0x1F].unk00;
}

/* f2a4_queue_view.c */
#include "slus/cd_cohort_types.h"

/* Two adjacent scalar globals (loaded/stored individually via $gp) that are
 * also treated as one small struct when their combined address is taken. */

/* >8B neighbour spanning 0x800814AC..0x800814B7 (established in w_8003D5A4.c),
 * used to synthesize the hi/lo address-of D_800814B0 (offset 4 into it) per
 * the dual-access-global split-declaration technique. */
extern u8 D_800814AC[12];

typedef struct {
    s32 f0;
    s32 f4;
} S_8003F2A4_pair;

/* Copy a type 6 ring-head entry's pair to globals and repoint it there, or clear the entry's type. */
void func_8003F2A4(SlusCdQueueEntry *entry) {
    if (entry->unk00 != 6 ||
        entry != &D_80083968[D_800814D0]) {
        entry->unk00 = 0;
        return;
    }
    D_800814B0 = ((S_8003F2A4_pair *)(*(u32 *)((u8 *)entry + 4)))->f0;
    D_800814B4 = ((S_8003F2A4_pair *)(*(u32 *)((u8 *)entry + 4)))->f4;
    (*(u32 *)((u8 *)entry + 4)) = (u32)&D_800814AC[4];
}

/* f368_address_views.c */
#include "slus/cd_state.h"


extern u8 D_80081451[2];
extern u8 D_80081452[1];

extern s32 CdSync(s32 mode, u8 *result);
extern s32 CdControl(u8 com, u8 *param, u8 *result);
extern s32 CdPosToInt(u8 *loc);
extern void func_8003E70C(void);
extern void func_8003F624(void);
extern s32 func_8003F688(u8 val);

/* Reads and validates the CD location, returning its sector position or zero. */
s32 func_8003F368(void)
{
    u32 saved_loc;
    u8 cd_loc[4];
    u8 sync_result[8]; /* CdSync copies eight result bytes. */
    s32 retries_left;
    s32 sector_pos;
    u8 index_is_zero;
    u8 *recovery_state;

    saved_loc = D_80081450.first_word;
    D_80081450.first_word = 0;

    if (CdSync(1, sync_result) != 2) {
        return 0;
    }

    retries_left = 0x10;

L8003F3A4:
    for (;;) {
        if (CdControl(0x10, 0, (u8 *)((u32)D_80081451 - 1)) == 1) {
            break;
        }
        if (--retries_left == 0) {
            func_8003E70C();
            retries_left = 0x10;
            func_8003F624();
        }
    }

    retries_left = 0x10;
    recovery_state = D_800814D3;
    while (CdSync(1, (u8 *)((u32)D_80081451 - 1)) != 2) {
        if (--retries_left != 0) {
            continue;
        }
        func_8003E70C();
        if ((func_8003F240() & 0xFF) == 0x1B) {
            index_is_zero = ((*(u8 *)((u32)recovery_state - 3)) == 0);
            D_800814D3[0] = 0xFF;
            if (!index_is_zero) {
                D_800814D0 -= 1;
            } else {
                (*(u8 *)((u32)recovery_state - 3)) = 0x1F;
            }
            D_800814D0 &= 0x1F;
            retries_left = 0x10;
            func_8003F624();
            goto L8003F3A4;
        }
        D_80081450.first_word = saved_loc;
        retries_left = 0x10;
    }

    cd_loc[0] = D_80081450.bytes[0];
    cd_loc[1] = D_80081451[0];
    cd_loc[2] = D_80081452[0];
    sector_pos = CdPosToInt(cd_loc);

    if (func_8003F688(D_80081450.bytes[0]) >= 0x4B) {
        return 0;
    }
    {
        register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */

        if (func_8003F688((*(u8 *)((u32)D_80081452 - 1))) < 0x3C) {
            s32 sector_valid;
            sector_valid = func_8003F688(D_80081451[1]) < 0x4B;
            result = 0;
            if (!sector_valid) {
                return result;
            }
            result = sector_pos;
            if (sector_pos > 0) {
                return result;
            }
        }
        result = 0;
        return result;
    }
}

/* f5ac_driver_view.c */
#include "slus/cd_cohort_types.h"


/* Returns the stored flags with bit 2 set when D_80080AD4 is nonzero. */
s32 func_8003F5AC(void) {
    s32 flags = D_80083958[0].unk4;

    if (D_80080AD4 != 0) {
        flags |= 4;
    } else {
        flags &= 0xFF;
    }
    return flags;
}

/* w_8003F624_owned.c */
#include "slus/cd_state.h"

/* dual-access global: sb-store of D_800814D4 via $gp scalar, but address-of
 * (for CdControlB's param pointer) goes through a >8B neighbour symbol
 * D_800814D3[1] == &D_800814D4, forcing hi/lo codegen for the address-of. */

extern int CdControlB(u8 com, u8 *param, u8 *result);
extern void func_8003E70C(void);
extern void func_8003F5EC(void);

/* Tries CD mode 0x84 up to 16 times, increments retry counters on failure, then waits. */
void func_8003F624(void) {
    int attempts_left;

    D_800814D4 = 0x84;
    for (attempts_left = 0x10; attempts_left != 0; attempts_left--) {
        if (CdControlB(0xE, &D_800814D3[1], 0) != 0) {
            goto done;
        }
    }
    func_8003E70C();
done:
    func_8003F5EC();
}

