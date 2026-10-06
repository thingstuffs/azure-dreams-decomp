#include "slus/cd_cohort_types.h"


typedef struct S_80083164 {
    u16 unk0; /* Observed prefix; enclosing extent is unknown. */
} S_80083164;


/* RETAIL jump table for the state==1 dispatch: an ABSOLUTE in
 * config/generated/slus_006.14.undefined_syms.txt (0x8002D5C0, 28 entries,
 * live cases 0/6/9/0x15/0x1B, every other index -> the `tail` block).
 * Dispatching through it means this TU emits NO compiler-generated jump table
 * into .text-referenced .rodata, which is what makes the object LINK. */

extern u8  D_800814D1[1];    /* Observed tail-index byte view; no storage ownership. */
extern u8  D_800814D8[8];     /* CdReadSync buffer (retail extent 8: small data at -G8) */
extern u32 D_80081480[1];     /* retail extent 5: small data at -G8 */
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
extern u8  D_800814D3[2];   /* CD driver state byte (+0); +1 is the byte at D_800814D4 */
extern u8  D_800814D2[1];

#define CDBUF (D_80081450.bytes)

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

    if (D_800814D0 != D_800814D1[0]) {

        driver->flags |= 1;
        state = D_800814D3[0];

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
                D_800814D3[0] = 0xFF;
                driver->unk4 = 0;
                D_800814D2[0] = 0;
                D_800814D0 = (head_index + 1) & 0x1F;
                goto process_queue;

            case 1:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 2;
                driver->unk4 = 2;
                D_800814D0 = D_800814D0 + 1;
                break;

            case 2:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                command = &queue[D_800814D0];
                CdIntToPos(command->unk04, location);
                if (CdControl(2, location, CDBUF) == 0)
                    break;
                D_800814D0 = D_800814D0 + 1;
                break;

            case 6:
            {
                u32 *read_info;
                u32 read_word, read_addr, sector_count;
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
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
                    u8 *state_ptr = &D_800814D3[0];
                    D_800814D3[0] = 0xFF;
                    state_ptr[-3] += 1;
                    break;
                }
                D_800814CC = (read_addr + (sector_count << 11)) - 4;
                D_800814D4 = 0x80;
                if (CdControl(0xE, &D_800814D3[1], 0) == 0)
                    return;
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
                if (CdControl(2, location, 0) == 0)
                    return;
                sync_result = CdSync(1, sync_status);
                if (sync_result != 0) {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error) {
                        func_8003E70C();
                        return;
                    }
                }
                if (CdRead(sector_count, (u32 *)read_addr, 0x80) == 0)
                    return;
                D_800814D3[0] = 1;
                break;
            }

            case 9:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                if (CdControl(9, 0, CDBUF) == 0)
                    break;
                D_800814D3[0] = 1;
                break;

            case 0xD:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                {
                    int command_offset = D_800814D0 * 24;
                    u8 *params = queue->unk08;
                    if (CdControl(0xD, command_offset + params, CDBUF) == 0)
                        break;
                }
                D_800814D3[0] = 0xFF;
                D_800814D0 = D_800814D0 + 1;
                break;

            case 0xE:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                {
                    int command_offset = D_800814D0 * 24;
                    u8 *params = queue->unk08;
                    if (CdControl(0xE, command_offset + params, CDBUF) == 0)
                        break;
                }
                D_800814D3[0] = 0xFF;
                D_800814D0 = D_800814D0 + 1;
                break;

            case 0x15:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                command = &queue[D_800814D0];
                CdIntToPos(command->unk04, location);
                if (CdControlF(0x15, location) == 0)
                    break;
                D_800814D3[0] = 1;
                break;

            case 0x1B:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        func_8003E70C();
                }
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                command = &queue[D_800814D0];
                CdIntToPos(command->unk04, location);
                retries = 0x10;
                if (CdControl(2, location, 0) == 0)
                    return;
                {
                    int disk_error = 5;
                    for (;;) {
                        sync_result = CdSync(1, sync_status);
                        retries--;
                        if (sync_result == 0)
                            goto wait_stream_seek;
                        retries = 0x10;
                        if (sync_result != disk_error)
                            goto start_stream;
    stream_error:
                        func_8003E70C();
                        return;
    wait_stream_seek:
                        if (retries != 0)
                            continue;
                        goto stream_error;
    start_stream:
                        for (;;) {
                            if (CdRead2(0xC8) != 0)
                                break;
                            if (--retries == 0)
                                goto stream_error;
                        }
                        D_80083958[0].unk4 = 0;
                        D_800814D3[0] = 1;
                        goto finish;
                    }
                }

            case 0xA:
                D_800814D2[0] = 0;
                driver->unk4 = 0;
                retries = 0x10;
                for (;;) {
                    if (CdReset(0) != 0)
                        break;
                    if (--retries == 0)
                        goto stream_error;
                }
                D_800814D3[0] = 0xFF;
                D_800814D0 = D_800814D0 + 1;
                break;

            case 0xFF:
                (*(void (*)(u32))queue[head_index].unk04)(*(u32 *)D_80083968[D_800814D0].unk08);
                D_800814D0 = D_800814D0 + 1;
                break;

            case 0xFC:
                StUnSetRing();
                D_800814D0 = D_800814D0 + 1;
                break;

            case 0x4:
            case 0x8:
            case 0xB:
            case 0xC:
            case 0x10:
            case 0x16:
            default:
                break;
            }
        } else if (state == 1) {
            u32 opcode;
            int completion_offset;
            active_queue = D_80083968;
            head_index = D_800814D0;
                            /* Keep one byte-offset accumulator for this completion lookup. */
            completion_offset = head_index << 1;
            completion_offset += head_index;
            completion_offset <<= 3;
            active_command = (SlusCdQueueEntry *)((u8 *)active_queue + completion_offset);
            opcode = active_command->unk00;
            switch (opcode) {
            case 0:
                {
                    u8 *state_ptr;
                    s16 idle_state;
                    int old_head;
                    idle_state = 0xFF;
                    D_800814D3[0] = idle_state;
                    state_ptr = &D_800814D3[0];
                    old_head = state_ptr[-3];
                    D_80083958[0].unk4 = 0;
                    D_800814D2[0] = 0;
                    state_ptr[-3] = (old_head + 1) & 0x1F;
                    goto process_queue;
                }

            case 6:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        goto command_failed;
                }
                D_80080AD8 = CdReadSync(1, D_800814D8);
                if (D_80080AD8 > 0)
                    break;
                if (D_80080AD8 == 0) {
                    if (D_80080AD0 != 0) {
                        if ((*(u32 *)D_800814CC & 0xFFFF0000) == 0x10120000)
                            break;
                        func_8003E70C();
                        D_800814D2[0] = 0;
                        D_80080AD2 = D_80080AD2 + 1;
                        if ((D_80080AD2 & 3) == 3) {
                            CdReset(0);
                            func_8003F5EC();
                        }
                        D_800814D3[0] = 0xFF;
                        break;
                    }
                    {
                        u8 *state_ptr = &D_800814D3[0];
                        SlusCdDriverPrefix *read_driver = &D_80083958[0];
                        D_800814D3[0] = 0xFF;
                        read_driver->unk4 = 2;
                        state_ptr[-3] += 1;
                        D_800814D2[0] = D_800814D2[0] | 1;
                        read_driver->unk5 = read_driver->unk5 + 1;
                        break;
                    }
                }
                if (D_80080AD8 >= 0)
                    break;
                goto command_failed;

            case 9:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error)
                        goto command_failed;
                }
                goto check_drive_status;

            case 0x15:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                if (sync_result != 5)
                    goto check_drive_status;
    command_failed:
                func_8003E70C();
                D_800814D3[0] = 0xFF;
                D_80083958[0].unk4 = 0;
                D_800814D2[0] = 0;
                break;

    check_drive_status:
                if (CdControl(1, 0, CDBUF) == 0)
                    break;
                if ((D_80081450.bytes[0] & 0xFD) != 0)
                    break;
                D_80083958[0].unk4 = 2;
                D_800814D3[0] = 0xFF;
                D_800814D0 = D_800814D0 + 1;
                break;

            case 0x1B:
                if (CdSync(1, CDBUF) == 5) {
                    D_800814D3[0] = 0xFF;
                    break;
                }
                retries = 0x10;
                for (;;) {
                    if (CdControl(1, 0, CDBUF) != 0)
                        break;
                    if (--retries == 0) {
                        func_8003E70C();
                        D_800814D3[0] = 0xFF;
                        return;
                    }
                }
                status = D_80081450.bytes[0];
                if (status & 0x40)
                    break;
                if (status & 0x20) {
                    u8 *status_ptr = &D_800814D2[0];
                    SlusCdQueueEntry *stream_queue;
                    SlusCdQueueEntry *stream_command;
                    s32 stream_head;
                    stream_command = 0xFF;
                    stream_queue = D_80083968;
                    D_800814D2[0] = 0;
                    D_800814D3[0] = stream_command;
                    stream_head = status_ptr[-2];
                    stream_command = &stream_queue[stream_head];
                    if (stream_command->unk17 != 0xFF) {
                        D_80083958[0].unk4 = 4;
                        D_80080AD4 = 1;
                    }
                    status_ptr[-2] += 1;
                    break;
                }
                if (status & 0x80)
                    D_800814D3[0] = 0xFF;
                break;

            }
        }
    } else {
        if (CdSync(1, 0) == 5) {
            if ((func_8003F240() & 0xFF) == 0x1B) {
                D_800814D3[0] = 0xFF;
                if (D_800814D0 != 0)
                    D_800814D0 = D_800814D0 - 1;
                else
                    D_800814D0 = 0x1F;
                func_8003F624();
            } else {
                CdControl(1, 0, 0);
            }
        }
    }

finish:
    if ((D_80083164[0].unk0 & 0x7FFF) == 0)
        D_80083958[0].counter1 = 0;
    D_800814D0 = D_800814D0 & 0x1F;
}
