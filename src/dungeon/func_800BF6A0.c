#include "common.h"
typedef struct {u16 unk00;} Pre; typedef struct {u8 pad[8];u16 unk08;s16 unk0A;s16 unk0C;} State;
typedef struct {u8 pad[0xC];u16 unk0C;u8 pad2[6];} Entry;
extern void func_800997FC(void *); extern s32 D_800814A0; extern u16 D_80083462; extern s32 D_800E18C8; extern Entry D_800E2970[];
void func_800C4E00(void *state){s32 countdown; s32 entry_index; register u32 addr_or_flags ASM_REG("$2");
if(D_80083462&0x10){countdown=((State*)state)->unk08-1;((State*)state)->unk08=countdown;if((countdown<<16)<=0){if(((State*)state)->unk0A==1){func_800997FC(&D_800E18C8);entry_index=((State*)state)->unk0C;D_800E2970[entry_index].unk0C=D_800E2970[entry_index].unk0C&0xFFFD;}addr_or_flags=((Pre*)state)[-1].unk00;addr_or_flags|=0x8000;((Pre*)state)[-1].unk00=addr_or_flags;addr_or_flags=D_800814A0;addr_or_flags|=0x8000;D_800814A0=addr_or_flags;}}}
