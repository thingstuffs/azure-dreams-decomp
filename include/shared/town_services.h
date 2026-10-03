#ifndef SHARED_TOWN_SERVICES_H
#define SHARED_TOWN_SERVICES_H

/* Indirect-call table reached through the town root at +0x20.
 * Observed extent: through the word at +0x344; total allocation size unknown.
 * callback_XXX names state only the demonstrated calling role and byte offset.
 * Empty parameter lists preserve the incomplete prototype evidence. Most return
 * values are unused; int preserves the existing M2C_UNK word-return convention.
 * +0x74 returns a record pointer. Per-use casts may retain stricter prototypes
 * or a noreturn attribute where the caller needs it. See phase-12 DESIGN.md. */
typedef struct TownServiceTable {
    /* 0x000 */ unsigned char pad_000[0x44];
    /* 0x044 */ int (*callback_044)();
    /* 0x048 */ unsigned char pad_048[0x4];
    /* 0x04C */ int (*callback_04C)();
    /* 0x050 */ int (*callback_050)();
    /* 0x054 */ int (*callback_054)();
    /* 0x058 */ unsigned char pad_058[0x10];
    /* 0x068 */ int (*callback_068)();
    /* 0x06C */ unsigned char pad_06C[0x8];
    /* 0x074 */ void *(*callback_074)();
    /* 0x078 */ int (*callback_078)();
    /* 0x07C */ unsigned char pad_07C[0xC];
    /* 0x088 */ int (*callback_088)();
    /* 0x08C */ unsigned char pad_08C[0xDC];
    /* 0x168 */ int (*callback_168)();
    /* 0x16C */ unsigned char pad_16C[0x8];
    /* 0x174 */ int (*callback_174)();
    /* 0x178 */ unsigned char pad_178[0x18];
    /* 0x190 */ int (*callback_190)();
    /* 0x194 */ unsigned char pad_194[0x54];
    /* 0x1E8 */ int (*callback_1E8)();
    /* 0x1EC */ unsigned char pad_1EC[0x4];
    /* 0x1F0 */ int (*callback_1F0)();
    /* 0x1F4 */ int (*callback_1F4)();
    /* 0x1F8 */ unsigned char pad_1F8[0x10];
    /* 0x208 */ int (*callback_208)();
    /* 0x20C */ unsigned char pad_20C[0x10];
    /* 0x21C */ int (*callback_21C)();
    /* 0x220 */ int (*callback_220)();
    /* 0x224 */ int (*callback_224)();
    /* 0x228 */ unsigned char pad_228[0x8];
    /* 0x230 */ int (*callback_230)();
    /* 0x234 */ unsigned char pad_234[0x4];
    /* 0x238 */ int (*callback_238)();
    /* 0x23C */ unsigned char pad_23C[0x8];
    /* 0x244 */ int (*callback_244)();
    /* 0x248 */ int (*callback_248)();
    /* 0x24C */ unsigned char pad_24C[0xC];
    /* 0x258 */ int (*callback_258)();
    /* 0x25C */ unsigned char pad_25C[0x8];
    /* 0x264 */ int (*callback_264)();
    /* 0x268 */ unsigned char pad_268[0x8];
    /* 0x270 */ int (*callback_270)();
    /* 0x274 */ unsigned char pad_274[0x4];
    /* 0x278 */ int (*callback_278)();
    /* 0x27C */ unsigned char pad_27C[0x4];
    /* 0x280 */ int (*callback_280)();
    /* 0x284 */ unsigned char pad_284[0x8];
    /* 0x28C */ int (*callback_28C)();
    /* 0x290 */ unsigned char pad_290[0x30];
    /* 0x2C0 */ int (*callback_2C0)();
    /* 0x2C4 */ unsigned char pad_2C4[0xC];
    /* 0x2D0 */ int (*callback_2D0)();
    /* 0x2D4 */ int (*callback_2D4)();
    /* 0x2D8 */ unsigned char pad_2D8[0x20];
    /* 0x2F8 */ int (*callback_2F8)();
    /* 0x2FC */ unsigned char pad_2FC[0x10];
    /* 0x30C */ int (*callback_30C)();
    /* 0x310 */ int (*callback_310)();
    /* 0x314 */ unsigned char pad_314[0x1C];
    /* 0x330 */ int (*callback_330)();
    /* 0x334 */ int (*callback_334)();
    /* 0x338 */ unsigned char pad_338[0xC];
    /* 0x344 */ int (*callback_344)();
} TownServiceTable;

#endif
