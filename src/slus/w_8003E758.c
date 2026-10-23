#include "engine/scene/cd_cohort_types.h"





/* RETAIL jump table for the state==1 dispatch: an ABSOLUTE in
 * config/generated/slus_006.14.undefined_syms.txt (0x8002D5C0, 28 entries,
 * live cases 0/6/9/0x15/0x1B, every other index -> the `tail` block).
 * Dispatching through it means this TU emits NO compiler-generated jump table
 * into .text-referenced .rodata, which is what makes the object LINK. */

extern u8  cd_command_write_index[1];    /* Observed tail-index byte view; no storage ownership. */
extern u8  cd_read_status_bytes[8];     /* CdReadSync buffer (retail extent 8: small data at -G8) */
extern u32 gpu_scratch_write_pointer[1];     /* retail extent 5: small data at -G8 */
extern u16 D_80083164[];

extern int  CdSync(int mode, u8 *result);
extern int  CdControl(u8 com, u8 *param, u8 *result);
extern int  CdControlF(u8 com, u8 *param);
extern int  CdRead(int count, u32 *buf, int mode);
extern int  CdRead2(int mode);
extern int  CdReadSync(int mode, u8 *result);
extern int  CdReset(int mode);
extern void StUnSetRing(void);

extern void func_8003E70C(void);
extern void wait_512_vertical_syncs(void);
extern void cd_set_mode_with_retry(void);
extern void CdIntToPos(u32 lba, u8 *loc);
extern u8  cd_command_phase[2];   /* CD driver state byte (+0); +1 is the byte at D_800814D4 */
extern u8  cd_command_status_flags[1];

#define CDBUF (cd_command_result.bytes)

/* Processes queued CD commands and advances pending reads and drive operations. */
void service_cd_command_queue(void)
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
    driver = &cd_driver_prefix[0];
    driver->flags &= 0xFFFE;

    if (cd_command_read_index != cd_command_write_index[0]) {

        driver->flags |= 1;
        state = cd_command_phase[0];

        if (state == 0xFF) {
            queue = cd_command_records;
            head_index = cd_command_read_index;
                            /* head_index*24 SPLIT into two carriers (head_index*3, then <<3): one 4-ref temp for
             * the whole chain outranks the address %hi in local-alloc
             * (floor_log2(4)*4/5 vs floor_log2(2)*2/4) and steals $v0; two 2-ref
             * carriers do not, so the %hi keeps retail's $v0.  Same 3 insns. */
            head_stride = head_index * 3;
            switch (*((u8 *)queue + head_stride * 8)) {
            case 0:
                cd_command_phase[0] = 0xFF;
                driver->unk4 = 0;
                cd_command_status_flags[0] = 0;
                cd_command_read_index = (head_index + 1) & 0x1F;
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
                cd_command_status_flags[0] = 2;
                driver->unk4 = 2;
                cd_command_read_index = cd_command_read_index + 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                command = &queue[cd_command_read_index];
                CdIntToPos(command->unk04, location);
                if (CdControl(2, location, CDBUF) == 0)
                    break;
                cd_command_read_index = cd_command_read_index + 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                command = &queue[cd_command_read_index];
                read_info = (u32 *)command->unk04;
                read_word = read_info[0];
                read_addr = read_word & 0x7FFFFF;
                if (read_addr == 0)
                    read_addr = gpu_scratch_write_pointer[0];
                else
                    read_addr = read_addr | 0x80000000;
                sector_count = read_info[0] >> 23;
                if (sector_count == 0) {
                    u8 *state_ptr = &cd_command_phase[0];
                    cd_command_phase[0] = 0xFF;
                    state_ptr[-3] += 1;
                    break;
                }
                cd_read_tail_word_address = (read_addr + (sector_count << 11)) - 4;
                cd_command_mode_byte = 0x80;
                if (CdControl(0xE, &cd_command_phase[1], 0) == 0)
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
                cd_command_phase[0] = 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                if (CdControl(9, 0, CDBUF) == 0)
                    break;
                cd_command_phase[0] = 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                {
                    int command_offset = cd_command_read_index * 24;
                    u8 *params = queue->unk08;
                    if (CdControl(0xD, command_offset + params, CDBUF) == 0)
                        break;
                }
                cd_command_phase[0] = 0xFF;
                cd_command_read_index = cd_command_read_index + 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                {
                    int command_offset = cd_command_read_index * 24;
                    u8 *params = queue->unk08;
                    if (CdControl(0xE, command_offset + params, CDBUF) == 0)
                        break;
                }
                cd_command_phase[0] = 0xFF;
                cd_command_read_index = cd_command_read_index + 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                command = &queue[cd_command_read_index];
                CdIntToPos(command->unk04, location);
                if (CdControlF(0x15, location) == 0)
                    break;
                cd_command_phase[0] = 1;
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
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                command = &queue[cd_command_read_index];
                CdIntToPos(command->unk04, location);
                retries = 0x10;
                if (CdControl(2, location, 0) == 0)
                    return;
                {
                    int disk_error = 5;
                    for (;;) {
                        sync_result = CdSync(1, sync_status);
                        retries--;
                        if (sync_result != 0) {
                            retries = 0x10;
                            if (sync_result != disk_error)
                                break;
                            func_8003E70C();
                            return;
                        }
                        if (retries == 0) {
                            func_8003E70C();
                            return;
                        }
                    }
                }
                for (;;) {
                    if (CdRead2(0xC8) != 0)
                        break;
                    if (--retries == 0) {
                        func_8003E70C();
                        return;
                    }
                }
                cd_driver_prefix[0].unk4 = 0;
                cd_command_phase[0] = 1;
                break;

            case 0xA:
                cd_command_status_flags[0] = 0;
                driver->unk4 = 0;
                retries = 0x10;
                for (;;) {
                    if (CdReset(0) != 0)
                        break;
                    if (--retries == 0) {
                        func_8003E70C();
                        return;
                    }
                }
                cd_command_phase[0] = 0xFF;
                cd_command_read_index = cd_command_read_index + 1;
                break;

            case 0xFF:
                (*(void (*)(u32))queue[head_index].unk04)(*(u32 *)cd_command_records[cd_command_read_index].unk08);
                cd_command_read_index = cd_command_read_index + 1;
                break;

            case 0xFC:
                StUnSetRing();
                cd_command_read_index = cd_command_read_index + 1;
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
            active_queue = cd_command_records;
            head_index = cd_command_read_index;
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
                    cd_command_phase[0] = idle_state;
                    state_ptr = &cd_command_phase[0];
                    old_head = state_ptr[-3];
                    cd_driver_prefix[0].unk4 = 0;
                    cd_command_status_flags[0] = 0;
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
                    if (sync_result == disk_error) {
                        func_8003E70C();
                        cd_command_phase[0] = 0xFF;
                        cd_driver_prefix[0].unk4 = 0;
                        cd_command_status_flags[0] = 0;
                        break;
                    }
                }
                cd_read_sync_result = CdReadSync(1, cd_read_status_bytes);
                if (cd_read_sync_result > 0)
                    break;
                if (cd_read_sync_result == 0) {
                    if (D_80080AD0 != 0) {
                        if ((*(u32 *)cd_read_tail_word_address & 0xFFFF0000) == 0x10120000)
                            break;
                        func_8003E70C();
                        cd_command_status_flags[0] = 0;
                        cd_command_poll_ticks = cd_command_poll_ticks + 1;
                        if ((cd_command_poll_ticks & 3) == 3) {
                            CdReset(0);
                            wait_512_vertical_syncs();
                        }
                        cd_command_phase[0] = 0xFF;
                        break;
                    }
                    {
                        u8 *state_ptr = &cd_command_phase[0];
                        SlusCdDriverPrefix *read_driver = &cd_driver_prefix[0];
                        cd_command_phase[0] = 0xFF;
                        read_driver->unk4 = 2;
                        state_ptr[-3] += 1;
                        cd_command_status_flags[0] = cd_command_status_flags[0] | 1;
                        read_driver->unk5 = read_driver->unk5 + 1;
                        break;
                    }
                }
                if (cd_read_sync_result >= 0)
                    break;
                {
                    func_8003E70C();
                    cd_command_phase[0] = 0xFF;
                    cd_driver_prefix[0].unk4 = 0;
                    cd_command_status_flags[0] = 0;
                    break;
                }

            case 9:
                sync_result = CdSync(1, CDBUF);
                if (sync_result == 0)
                    break;
                {
                    int disk_error;
                    disk_error = 5;
                    if (sync_result == disk_error) {
                        do {
                            func_8003E70C();
                            cd_command_phase[0] = 0xFF;
                            cd_driver_prefix[0].unk4 = 0;
                            cd_command_status_flags[0] = 0;
                        } while (0);
                        break;
                    }
                }
                {
                    if (CdControl(1, 0, CDBUF) == 0)
                        break;
                    if ((cd_command_result.bytes[0] & 0xFD) != 0)
                        break;
                    cd_driver_prefix[0].unk4 = 2;
                    cd_command_phase[0] = 0xFF;
                    cd_command_read_index = cd_command_read_index + 1;
                    break;
                }

            case 0x15:
                sync_result = CdSync(1, sync_status);
                if (sync_result == 0)
                    break;
                if (sync_result == 5) {
                    func_8003E70C();
                    cd_command_phase[0] = 0xFF;
                    cd_driver_prefix[0].unk4 = 0;
                    cd_command_status_flags[0] = 0;
                    break;
                }

                if (CdControl(1, 0, CDBUF) == 0)
                    break;
                if ((cd_command_result.bytes[0] & 0xFD) != 0)
                    break;
                cd_driver_prefix[0].unk4 = 2;
                cd_command_phase[0] = 0xFF;
                cd_command_read_index = cd_command_read_index + 1;
                break;

            case 0x1B:
                if (CdSync(1, CDBUF) == 5) {
                    cd_command_phase[0] = 0xFF;
                    break;
                }
                retries = 0x10;
                for (;;) {
                    if (CdControl(1, 0, CDBUF) != 0)
                        break;
                    if (--retries == 0) {
                        func_8003E70C();
                        cd_command_phase[0] = 0xFF;
                        return;
                    }
                }
                status = cd_command_result.bytes[0];
                if (status & 0x40)
                    break;
                if (status & 0x20) {
                    u8 *status_ptr = &cd_command_status_flags[0];
                    SlusCdQueueEntry *stream_queue;
                    SlusCdQueueEntry *stream_command;
                    s32 stream_head;
                    stream_command = 0xFF;
                    stream_queue = cd_command_records;
                    cd_command_status_flags[0] = 0;
                    cd_command_phase[0] = stream_command;
                    stream_head = status_ptr[-2];
                    stream_command = &stream_queue[stream_head];
                    if (stream_command->unk17 != 0xFF) {
                        cd_driver_prefix[0].unk4 = 4;
                        cd_retry_counters_pending = 1;
                    }
                    status_ptr[-2] += 1;
                    break;
                }
                if (status & 0x80)
                    cd_command_phase[0] = 0xFF;
                break;

            }
        }
    } else {
        if (CdSync(1, 0) == 5) {
            if ((get_previous_cd_command_byte() & 0xFF) == 0x1B) {
                cd_command_phase[0] = 0xFF;
                if (cd_command_read_index != 0)
                    cd_command_read_index = cd_command_read_index - 1;
                else
                    cd_command_read_index = 0x1F;
                cd_set_mode_with_retry();
            } else {
                CdControl(1, 0, 0);
            }
        }
    }

finish:
    if ((D_80083164[0] & 0x7FFF) == 0)
        cd_driver_prefix[0].counter1 = 0;
    cd_command_read_index = cd_command_read_index & 0x1F;
}
