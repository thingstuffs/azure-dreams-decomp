#include "common.h"

#include "common.h"

typedef struct RuntimeContext {
    u8 pad0[0x1C];
    u8 *read_ptr;
    u8 pad20[0x5C];
    u8 **return_ptr;
    u8 *base;
} RuntimeContext;

extern void func_80039640(RuntimeContext *);
extern void func_8003AD08(s32, u8 *);
extern u8 *D_8006A944[];

/* Processes stream control bytes until the next data byte. */
void func_80038F48(RuntimeContext *ctx) {
    u8 *base;
    u32 target_ptr_addr;
    s8 signed_opcode;
    u8 opcode;
    u8 *command_ptr;
    u8 *operand_ptr;
    u8 *call_ptr;

    opcode = *ctx->read_ptr;
    base = ctx->base;
    while ((u8)(opcode + 3) < 3U || opcode == 0) {
        command_ptr = ctx->read_ptr;
        signed_opcode = *(s8 *)command_ptr;
        if (signed_opcode == -3) {
            *ctx->return_ptr = command_ptr + 2;
            call_ptr = ctx->read_ptr;
            ctx->return_ptr++;
            ctx->read_ptr = call_ptr + 1;
            func_8003AD08(*(s32 *)(base + (call_ptr[1] * 4) + 0x48),
                          ctx->base + 0x14);
            ctx->read_ptr = ctx->base + 0x14;
        } else if (signed_opcode == -2) {
            *ctx->return_ptr = command_ptr + 2;
            command_ptr = ctx->read_ptr;
            ctx->return_ptr++;
            ctx->read_ptr = command_ptr + 1;
            ctx->read_ptr = D_8006A944[command_ptr[1]];
        } else if (signed_opcode == -1) {
            *ctx->return_ptr = command_ptr + 5;
            command_ptr = ctx->read_ptr;
            operand_ptr = command_ptr + 1;
            ctx->return_ptr++;
            ctx->read_ptr = operand_ptr;
            target_ptr_addr = (u32)command_ptr[1] + ((u32)operand_ptr[1] << 8) +
                       ((u32)operand_ptr[2] << 16) + ((u32)operand_ptr[3] << 24);
            ctx->read_ptr = *(u8 **)target_ptr_addr;
        } else {
            func_80039640(ctx);
        }
        opcode = *ctx->read_ptr;
    }
}
