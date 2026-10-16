# r121_nodonor evidence: no-donor decompilation rows

Lane r121_nodonor (Opus), base c5a0a9c (B3 content). 294 new exact C rows / 69328 bytes, all TOWN. Receipt: `docs/evidence/r121_nodonor.receipt.json`.

Every row: raw/ = genuine spimdisasm singleFileDisasm -> m2c (rev 708d2d2) first pass (commands and sha in the receipt), src/ = hand C,
scored exact (tools/verify.verify_overlay, total 0) at the recipe in the split record, production window gate MATCH with the row compiled
as a C segment. No inline asm, volatile, NON_MATCHING, pragma, goto or m2c leftovers in src/.

## Placement (rowbase) evidence

- p1/p2/t1 rows sit in existing `proven` rowbase regions.
- p3: TOWN script modules (docs/evidence/town_script_modules.json) load at 0x80016000; the module header file offset plus the loader
  descriptor sector count (docs/evidence/town_scene_loader_receipt.json) bound the loaded extent; each row lies inside it (same proof
  class as the r121c2 records). delta = 0x80016000 - header file offset.
- p4: 0x80700000-linked devkit images: the row's own `j` lands on its epilogue `lw ra` only at one 0x800-aligned delta, and every
  direct jal target lands on a registered row start or complete entry at that delta (0 at +/-0x800, +/-0x1000), agreeing with the
  neighbouring proven regions. 0x2D3E94 lies inside the authenticated CD bank map of r121_town_2d3f0c (file 0x2D2000..0x2D4000 ->
  0x8001DCD0).
- p5: 0x800194 has no j/jal; its five lui/addiu operands land on string starts ("%s = %d\n", "p->kind", "ov_work.kind",
  "mark: %s line %d\n", "sn_main.c") only at delta 0x7FF01000 (the r121li devkit header base).

## Recipe evidence

- Town script-module code: 2.7.2-cdk-G0 (module neighbours). Copies of the module-0 helper TU (townResolveEntryFlag /
  townFindEligibleEntry / townRecordValueTableContains): 2.7.2-cdk-G0 -O1, as their module-0 twins.
- Devkit images: 2.6.3 / 2.6.3-G0 / 2.7.2-G0 as the neighbouring rows. Four rows carry the per-row as-flag `--aspsx-version=2.40`
  (retail `ori rX,$zero,K` li expansion; config/overlays/town.as_flags.jsonl): each is exact with the dial and differs only at the li
  words without it; tools/fidelity/aspsx_diff.py --old-aspsx on: genuine ASPSX 2.34 exact and maspsx == retail for all four
  (work/native_lane/r121_nodonor/evidence/aspsx/).

## Notable source facts

- Two functions call a zero-argument helper: retail `move a0,s0` sits in the beq slot (stolen from the target) and the helper call
  has a nop slot; both helpers overwrite $a0 before reading it (func_80016A78, func_800178D0, func_80016CD8).
- func_80016244/80016280: the first store is a plain `*(s32 *)` store (it aliases D_80016000, which is reloaded), the next two are
  TownPositionState field stores (MEM_IN_STRUCT_P: no reload).
- func_80701194 is devkit debug code from sn_main.c (line 48 trace) that copies the overlay work record and prints p->kind / ov_work.kind.
- TownServiceTable slot 0x2D8 is still padding in include/shared/town_services.h; func_8001FB64 uses a local view (header tidy item).

## Rows

| batch | row | true name | file | size | recipe | window |
|---|---|---|---|---:|---|---|
| p1 | town/func_80477270 | func_80018270 | 0x3F7270 | 56 | 2.7.2-cdk-G0 | town_deep_t8_03ea.overlay.yaml |
| p1 | town/func_8047BA70 | func_80018270 | 0x3FBA70 | 56 | 2.7.2-cdk-G0 | town_deep_t8_03ea.overlay.yaml |
| p1 | town/func_8047B970 | func_80018170 | 0x3FB970 | 64 | 2.7.2-cdk-G0 | town_deep_t8_03ea.overlay.yaml |
| p1 | town/func_8047B9B0 | func_800181B0 | 0x3FB9B0 | 64 | 2.7.2-cdk-G0 | town_deep_t8_03ea.overlay.yaml |
| p1 | town/func_8047B9F0 | func_800181F0 | 0x3FB9F0 | 64 | 2.7.2-cdk-G0 | town_deep_t8_03ea.overlay.yaml |
| p1 | town/func_80476FAC | func_80017FAC | 0x3F6FAC | 108 | 2.7.2-cdk-G0 | town_deep_t8_03ea.overlay.yaml |
| p2 | town/func_8046A0DC | func_8001B0DC | 0x3EA0DC | 108 | 2.7.2-cdk-G0 | town_r121nd_3EA0DC_true_8001B0DC.overlay.yaml |
| p2 | town/func_8046A24C | func_8001B24C | 0x3EA24C | 104 | 2.7.2-cdk-G0 | town_r121nd_3EA24C_true_8001B24C.overlay.yaml |
| p2 | town/func_8046A308 | func_8001B308 | 0x3EA308 | 108 | 2.7.2-cdk-G0 | town_r121nd_3EA308_true_8001B308.overlay.yaml |
| p2 | town/func_8046A4C4 | func_8001B4C4 | 0x3EA4C4 | 104 | 2.7.2-cdk-G0 | town_r121nd_3EA4C4_true_8001B4C4.overlay.yaml |
| p2 | town/func_80480244 | func_80016244 | 0x400244 | 60 | 2.7.2-cdk-G0 | town_r121nd_400244_true_80016244.overlay.yaml |
| p2 | town/func_80480280 | func_80016280 | 0x400280 | 60 | 2.7.2-cdk-G0 | town_r121nd_400280_true_80016280.overlay.yaml |
| p2 | town/func_80500178 | func_80016178 | 0x480178 | 56 | 2.7.2-cdk-G0 | town_r121nd_480178_true_80016178.overlay.yaml |
| p2 | town/func_80579188 | func_80016188 | 0x4F9188 | 112 | 2.7.2-cdk-G0 | town_r121nd_4F9188_true_80016188.overlay.yaml |
| p2 | town/func_8064713C | func_8001613C | 0x5C713C | 84 | 2.7.2-cdk-G0 | town_r121nd_5C713C_true_8001613C.overlay.yaml |
| p2 | town/func_806C5B5C | func_80016B5C | 0x645B5C | 140 | 2.7.2-cdk-G0 | town_r121nd_645B5C_true_80016B5C.overlay.yaml |
| p2 | town/func_806C5C20 | func_80016C20 | 0x645C20 | 76 | 2.7.2-cdk-G0 | town_r121nd_645C20_true_80016C20.overlay.yaml |
| p2 | town/func_806C5D40 | func_80016D40 | 0x645D40 | 100 | 2.7.2-cdk-G0 | town_r121nd_645D40_true_80016D40.overlay.yaml |
| p2 | town/func_806C5DDC | func_80016DDC | 0x645DDC | 100 | 2.7.2-cdk-G0 | town_r121nd_645DDC_true_80016DDC.overlay.yaml |
| p2 | town/func_806C5E78 | func_80016E78 | 0x645E78 | 100 | 2.7.2-cdk-G0 | town_r121nd_645E78_true_80016E78.overlay.yaml |
| p2 | town/func_806C92F0 | func_800162F0 | 0x6492F0 | 84 | 2.7.2-cdk-G0 | town_r121nd_6492F0_true_800162F0.overlay.yaml |
| p2 | town/func_806D80EC | func_800168EC | 0x6580EC | 84 | 2.7.2-cdk-G0 | town_r121nd_6580EC_true_800168EC.overlay.yaml |
| p2 | town/func_806D8140 | func_80016940 | 0x658140 | 188 | 2.7.2-cdk-G0 | town_r121nd_658140_true_80016940.overlay.yaml |
| p2 | town/func_806D8324 | func_80016B24 | 0x658324 | 56 | 2.7.2-cdk-G0 | town_r121nd_658324_true_80016B24.overlay.yaml |
| p2 | town/func_8070F1B4 | func_800181B4 | 0x68F1B4 | 56 | 2.7.2-cdk-G0 | town_r121nd_68F1B4_true_800181B4.overlay.yaml |
| p2 | town/func_8070F1EC | func_800181EC | 0x68F1EC | 56 | 2.7.2-cdk-G0 | town_r121nd_68F1EC_true_800181EC.overlay.yaml |
| p2 | town/func_8070F224 | func_80018224 | 0x68F224 | 56 | 2.7.2-cdk-G0 | town_r121nd_68F224_true_80018224.overlay.yaml |
| p3 | town/func_8050E220 | func_80016220 | 0x48E220 | 56 | 2.7.2-cdk-G0 | town_r121nd_48E220_true_80016220.overlay.yaml |
| p3 | town/func_8059EAC4 | func_80016AC4 | 0x51EAC4 | 56 | 2.7.2-cdk-G0 | town_r121nd_51EAC4_true_80016AC4.overlay.yaml |
| p3 | town/func_8059EAFC | func_80016AFC | 0x51EAFC | 56 | 2.7.2-cdk-G0 | town_r121nd_51EAFC_true_80016AFC.overlay.yaml |
| p3 | town/func_806011F0 | func_800161F0 | 0x5811F0 | 56 | 2.7.2-cdk-G0 | town_r121nd_5811F0_true_800161F0.overlay.yaml |
| p3 | town/func_80632280 | func_80016280 | 0x5B2280 | 56 | 2.7.2-cdk-G0 | town_r121nd_5B2280_true_80016280.overlay.yaml |
| p3 | town/func_8070F678 | func_80018678 | 0x68F678 | 68 | 2.7.2-cdk-G0 | town_r121nd_68F678_true_80018678.overlay.yaml |
| p3 | town/func_8070F8B4 | func_800188B4 | 0x68F8B4 | 56 | 2.7.2-cdk-G0 | town_r121nd_68F8B4_true_800188B4.overlay.yaml |
| p3 | town/func_80761D50 | func_80016550 | 0x6E1D50 | 84 | 2.7.2-cdk-G0 | town_r121nd_6E1D50_true_80016550.overlay.yaml |
| p4 | town/func_80875518 | func_80701518 | 0x7F5518 | 148 | 2.6.3 | town_r121nd_7F5518_true_80701518.overlay.yaml |
| p4 | town/func_808831E0 | func_807009E0 | 0x8031E0 | 152 | 2.6.3-G0 | town_r121nd_8031E0_true_807009E0.overlay.yaml |
| p4 | town/func_80883198 | func_80700998 | 0x803198 | 72 | 2.6.3-G0 | town_r121nd_803198_true_80700998.overlay.yaml |
| p4 | town/func_808B3220 | func_80700A20 | 0x833220 | 140 | 2.7.2-G0 | town_r121nd_833220_true_80700A20.overlay.yaml |
| p4 | town/func_80353E94 | func_8001FB64 | 0x2D3E94 | 56 | 2.7.2-cdk-G0 | town_r121nd_2D3E94_true_8001FB64.overlay.yaml |
| p5 | town/func_80880194 | func_80701194 | 0x800194 | 224 | 2.6.3-G0 | town_r121nd_800194_true_80701194.overlay.yaml |
| t1 | town/func_80330880 | func_8001B080 | 0x2B0880 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_2B0880_true_8001B080.overlay.yaml |
| t1 | town/func_804D1290 | func_80016A90 | 0x451290 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_451290_true_80016A90.overlay.yaml |
| t1 | town/func_804D1484 | func_80016C84 | 0x451484 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_451484_true_80016C84.overlay.yaml |
| t1 | town/func_804F0B88 | func_80016B88 | 0x470B88 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_470B88_true_80016B88.overlay.yaml |
| t1 | town/func_804F0D7C | func_80016D7C | 0x470D7C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_470D7C_true_80016D7C.overlay.yaml |
| t1 | town/func_80500A6C | func_80016A6C | 0x480A6C | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_480A6C_true_80016A6C.overlay.yaml |
| t1 | town/func_80500C60 | func_80016C60 | 0x480C60 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_480C60_true_80016C60.overlay.yaml |
| t1 | town/func_80559A00 | func_80016A00 | 0x4D9A00 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_4D9A00_true_80016A00.overlay.yaml |
| t1 | town/func_80559BF4 | func_80016BF4 | 0x4D9BF4 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_4D9BF4_true_80016BF4.overlay.yaml |
| t1 | town/func_80579AB4 | func_80016AB4 | 0x4F9AB4 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_4F9AB4_true_80016AB4.overlay.yaml |
| t1 | town/func_80579CA8 | func_80016CA8 | 0x4F9CA8 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_4F9CA8_true_80016CA8.overlay.yaml |
| t1 | town/func_80647C08 | func_80016C08 | 0x5C7C08 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_5C7C08_true_80016C08.overlay.yaml |
| t1 | town/func_80647DFC | func_80016DFC | 0x5C7DFC | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_5C7DFC_true_80016DFC.overlay.yaml |
| t1 | town/func_8064890C | func_8001790C | 0x5C890C | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_5C890C_true_8001790C.overlay.yaml |
| t1 | town/func_8067F52C | func_8001652C | 0x5FF52C | 56 | 2.7.2-cdk-G0 | town_r121nd_5FF52C_true_8001652C.overlay.yaml |
| t1 | town/func_806A9A24 | func_80016A24 | 0x629A24 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_629A24_true_80016A24.overlay.yaml |
| t1 | town/func_806A9C18 | func_80016C18 | 0x629C18 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_629C18_true_80016C18.overlay.yaml |
| t1 | town/func_806C9C58 | func_80016C58 | 0x649C58 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_649C58_true_80016C58.overlay.yaml |
| t1 | town/func_806C9E4C | func_80016E4C | 0x649E4C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_649E4C_true_80016E4C.overlay.yaml |
| t1 | town/func_806CBC54 | func_80016C54 | 0x64BC54 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_64BC54_true_80016C54.overlay.yaml |
| t1 | town/func_806CBE48 | func_80016E48 | 0x64BE48 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_64BE48_true_80016E48.overlay.yaml |
| t1 | town/func_806CFA60 | func_80016A60 | 0x64FA60 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_64FA60_true_80016A60.overlay.yaml |
| t1 | town/func_806CFC54 | func_80016C54 | 0x64FC54 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_64FC54_true_80016C54.overlay.yaml |
| t1 | town/func_806D19D0 | func_800169D0 | 0x6519D0 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6519D0_true_800169D0.overlay.yaml |
| t1 | town/func_806D1BC4 | func_80016BC4 | 0x651BC4 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_651BC4_true_80016BC4.overlay.yaml |
| t1 | town/func_8079A240 | func_80016240 | 0x71A240 | 56 | 2.7.2-cdk-G0 | town_r121nd_71A240_true_80016240.overlay.yaml |
| t1 | town/func_8079AB34 | func_80016B34 | 0x71AB34 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_71AB34_true_80016B34.overlay.yaml |
| t1 | town/func_8079AD28 | func_80016D28 | 0x71AD28 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_71AD28_true_80016D28.overlay.yaml |
| t1 | town/func_8096D1FC | func_80125694 | 0x8ED1FC | 56 | 2.7.2-cdk-G0 | town_r121nd_8ED1FC_true_80125694.overlay.yaml |
| t2 | dungeon/func_80A4DC0C | func_8016B40C | 0xA6DC0C | 1368 | 2.7.2-cdk-G0 | dungeon_r121nd_A6DC0C_true_8016B40C.overlay.yaml |
| t2 | dungeon/func_80A53C0C | func_8016540C | 0xA73C0C | 1368 | 2.7.2-cdk-G0 | dungeon_r121nd_A73C0C_true_8016540C.overlay.yaml |
| t2 | dungeon/func_80A59C0C | func_8015F40C | 0xA79C0C | 1368 | 2.7.2-cdk-G0 | dungeon_r121nd_A79C0C_true_8015F40C.overlay.yaml |
| t2 | dungeon/func_80A5FC0C | func_8015940C | 0xA7FC0C | 1368 | 2.7.2-cdk-G0 | dungeon_r121nd_A7FC0C_true_8015940C.overlay.yaml |
| t2 | dungeon/func_80A65C0C | func_8015340C | 0xA85C0C | 1368 | 2.7.2-cdk-G0 | dungeon_r121nd_A85C0C_true_8015340C.overlay.yaml |
| t2 | dungeon/func_80A6BC0C | func_8014D40C | 0xA8BC0C | 1368 | 2.7.2-cdk-G0 | dungeon_r121nd_A8BC0C_true_8014D40C.overlay.yaml |
| t2 | dungeon/func_80AA9F20 | func_80167720 | 0xAC9F20 | 1220 | 2.7.2-cdk-G0 | dungeon_deep_ac7250_truebase_80164a50.overlay.yaml |
| t2 | dungeon/func_80AAFF20 | func_80161720 | 0xACFF20 | 1220 | 2.7.2-cdk-G0 | dungeon_deep_acd250_truebase_8015ea50.overlay.yaml |
| t2 | dungeon/func_80AB5F20 | func_8015B720 | 0xAD5F20 | 1220 | 2.7.2-cdk-G0 | dungeon_deep_ad3250_truebase_80158a50.overlay.yaml |
| t2 | dungeon/func_80ABBF20 | func_80155720 | 0xADBF20 | 1220 | 2.7.2-cdk-G0 | dungeon_deep_ad9250_truebase_80152a50.overlay.yaml |
| t2 | dungeon/func_80AC1F20 | func_8014F720 | 0xAE1F20 | 1220 | 2.7.2-cdk-G0 | dungeon_deep_adf250_truebase_8014ca50.overlay.yaml |
| t2 | dungeon/func_80C213B8 | func_80164BB8 | 0xC413B8 | 2032 | 2.7.2-cdk-G0 | dungeon_r121nd_C413B8_true_80164BB8.overlay.yaml |
| t2 | dungeon/func_80C333B8 | func_80152BB8 | 0xC533B8 | 2032 | 2.7.2-cdk-G0 | dungeon_r121nd_C533B8_true_80152BB8.overlay.yaml |
| t2 | dungeon/func_80C5167C | func_8015EE7C | 0xC7167C | 1380 | 2.7.2-cdk-G0 | dungeon_deep_c71250_truebase_8015ea50.overlay.yaml |
| t2 | dungeon/func_80C5767C | func_80158E7C | 0xC7767C | 1380 | 2.7.2-cdk-G0 | dungeon_deep_c77250_truebase_80158a50.overlay.yaml |
| t2 | dungeon/func_80C5D67C | func_80152E7C | 0xC7D67C | 1380 | 2.7.2-cdk-G0 | dungeon_deep_c7d250_truebase_80152a50.overlay.yaml |
| t2 | dungeon/func_80C6367C | func_8014CE7C | 0xC8367C | 1380 | 2.7.2-cdk-G0 | dungeon_deep_c83250_truebase_8014ca50.overlay.yaml |
| t2 | dungeon/func_80D3234C | func_80155B4C | 0xD5234C | 792 | 2.7.2-cdk-G0 | dungeon_deep_d4f2d0_truebase_80152ad0.overlay.yaml |
| t2 | dungeon/func_80FBD340 | func_80164B40 | 0xFDD340 | 1068 | 2.7.2-cdk-G0 | dungeon_r121nd_FDD340_true_80164B40.overlay.yaml |
| t2 | dungeon/func_80FCF340 | func_80152B40 | 0xFEF340 | 1068 | 2.7.2-cdk-G0 | dungeon_r121nd_FEF340_true_80152B40.overlay.yaml |
| t2 | dungeon/func_81060C04 | func_8016C404 | 0x1080C04 | 868 | 2.7.2-cdk-G0 | dungeon_deep_107f2a4_truebase_8016aaa4.overlay.yaml |
| t2 | dungeon/func_81066C04 | func_80166404 | 0x1086C04 | 868 | 2.7.2-cdk-G0 | dungeon_deep_10852a4_truebase_80164aa4.overlay.yaml |
| t2 | dungeon/func_81078C04 | func_80154404 | 0x1098C04 | 868 | 2.7.2-cdk-G0 | dungeon_deep_10972a4_truebase_80152aa4.overlay.yaml |
| t2 | dungeon/func_812AA06C | func_8017586C | 0x12CA06C | 248 | 2.7.2-cdk-G0 | dungeon_r121nd_12CA06C_true_8017586C.overlay.yaml |
| t2 | dungeon/func_812C806C | func_8015786C | 0x12E806C | 248 | 2.7.2-cdk-G0 | dungeon_r121nd_12E806C_true_8015786C.overlay.yaml |
| t2 | town/func_8046D7E4 | func_8001E7E4 | 0x3ED7E4 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_3ED7E4_true_8001E7E4.overlay.yaml |
| t2 | town/func_804737B0 | func_8001A7B0 | 0x3F37B0 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_3F37B0_true_8001A7B0.overlay.yaml |
| t2 | town/func_80478A44 | func_80019A44 | 0x3F8A44 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_3F8A44_true_80019A44.overlay.yaml |
| t2 | town/func_8047D244 | func_80019A44 | 0x3FD244 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_3FD244_true_80019A44.overlay.yaml |
| t2 | town/func_80481B84 | func_80017B84 | 0x401B84 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_401B84_true_80017B84.overlay.yaml |
| t2 | town/func_80481D78 | func_80017D78 | 0x401D78 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_401D78_true_80017D78.overlay.yaml |
| t2 | town/func_804827DC | func_800187DC | 0x4027DC | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_4027DC_true_800187DC.overlay.yaml |
| t2 | town/func_804B79F0 | func_800161F0 | 0x4379F0 | 56 | 2.7.2-cdk-G0 | town_r121nd_4379F0_true_800161F0.overlay.yaml |
| t2 | town/func_804B7A88 | func_80016288 | 0x437A88 | 56 | 2.7.2-cdk-G0 | town_r121nd_437A88_true_80016288.overlay.yaml |
| t2 | town/func_804B97E8 | func_80017FE8 | 0x4397E8 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_4397E8_true_80017FE8.overlay.yaml |
| t2 | town/func_804B99DC | func_800181DC | 0x4399DC | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_4399DC_true_800181DC.overlay.yaml |
| t2 | town/func_804D8B64 | func_80016B64 | 0x458B64 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_458B64_true_80016B64.overlay.yaml |
| t2 | town/func_804D8D58 | func_80016D58 | 0x458D58 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_458D58_true_80016D58.overlay.yaml |
| t2 | town/func_804D9868 | func_80017868 | 0x459868 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_459868_true_80017868.overlay.yaml |
| t2 | town/func_8050EB14 | func_80016B14 | 0x48EB14 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_48EB14_true_80016B14.overlay.yaml |
| t2 | town/func_8050ED08 | func_80016D08 | 0x48ED08 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_48ED08_true_80016D08.overlay.yaml |
| t2 | town/func_805207CC | func_80017FCC | 0x4A07CC | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_4A07CC_true_80017FCC.overlay.yaml |
| t2 | town/func_805209C0 | func_800181C0 | 0x4A09C0 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_4A09C0_true_800181C0.overlay.yaml |
| t2 | town/func_805504B4 | func_80016CB4 | 0x4D04B4 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_4D04B4_true_80016CB4.overlay.yaml |
| t2 | town/func_805506A8 | func_80016EA8 | 0x4D06A8 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_4D06A8_true_80016EA8.overlay.yaml |
| t2 | town/func_8059FE80 | func_80017E80 | 0x51FE80 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_51FE80_true_80017E80.overlay.yaml |
| t2 | town/func_805A0074 | func_80018074 | 0x520074 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_520074_true_80018074.overlay.yaml |
| t2 | town/func_805D4750 | func_80018750 | 0x554750 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_554750_true_80018750.overlay.yaml |
| t2 | town/func_805D4944 | func_80018944 | 0x554944 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_554944_true_80018944.overlay.yaml |
| t2 | town/func_8060259C | func_8001759C | 0x58259C | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_58259C_true_8001759C.overlay.yaml |
| t2 | town/func_80602790 | func_80017790 | 0x582790 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_582790_true_80017790.overlay.yaml |
| t2 | town/func_8061696C | func_8001816C | 0x59696C | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_59696C_true_8001816C.overlay.yaml |
| t2 | town/func_80616B60 | func_80018360 | 0x596B60 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_596B60_true_80018360.overlay.yaml |
| t2 | town/func_80632B74 | func_80016B74 | 0x5B2B74 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_5B2B74_true_80016B74.overlay.yaml |
| t2 | town/func_80632D68 | func_80016D68 | 0x5B2D68 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_5B2D68_true_80016D68.overlay.yaml |
| t2 | town/func_8063364C | func_8001764C | 0x5B364C | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_5B364C_true_8001764C.overlay.yaml |
| t2 | town/func_80680AB0 | func_80017AB0 | 0x600AB0 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_600AB0_true_80017AB0.overlay.yaml |
| t2 | town/func_80680CA4 | func_80017CA4 | 0x600CA4 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_600CA4_true_80017CA4.overlay.yaml |
| t2 | town/func_80698B80 | func_80017B80 | 0x618B80 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_618B80_true_80017B80.overlay.yaml |
| t2 | town/func_80698D74 | func_80017D74 | 0x618D74 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_618D74_true_80017D74.overlay.yaml |
| t2 | town/func_806997D8 | func_800187D8 | 0x6197D8 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_6197D8_true_800187D8.overlay.yaml |
| t2 | town/func_806C5130 | func_80016130 | 0x645130 | 56 | 2.7.2-cdk-G0 | town_r121nd_645130_true_80016130.overlay.yaml |
| t2 | town/func_806C7288 | func_80018288 | 0x647288 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_647288_true_80018288.overlay.yaml |
| t2 | town/func_806C747C | func_8001847C | 0x64747C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_64747C_true_8001847C.overlay.yaml |
| t2 | town/func_806CDBFC | func_80016BFC | 0x64DBFC | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_64DBFC_true_80016BFC.overlay.yaml |
| t2 | town/func_806CDDF0 | func_80016DF0 | 0x64DDF0 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_64DDF0_true_80016DF0.overlay.yaml |
| t2 | town/func_806D5904 | func_80017904 | 0x655904 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_655904_true_80017904.overlay.yaml |
| t2 | town/func_806D5AF8 | func_80017AF8 | 0x655AF8 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_655AF8_true_80017AF8.overlay.yaml |
| t2 | town/func_806D6800 | func_80018800 | 0x656800 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_656800_true_80018800.overlay.yaml |
| t2 | town/func_806D92B0 | func_80017AB0 | 0x6592B0 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6592B0_true_80017AB0.overlay.yaml |
| t2 | town/func_806D94A4 | func_80017CA4 | 0x6594A4 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6594A4_true_80017CA4.overlay.yaml |
| t2 | town/func_806D9FB4 | func_800187B4 | 0x659FB4 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_659FB4_true_800187B4.overlay.yaml |
| t2 | town/func_806DBA78 | func_80016A78 | 0x65BA78 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_65BA78_true_80016A78.overlay.yaml |
| t2 | town/func_806DBC6C | func_80016C6C | 0x65BC6C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_65BC6C_true_80016C6C.overlay.yaml |
| t2 | town/func_806F1AA8 | func_800162A8 | 0x671AA8 | 56 | 2.7.2-cdk-G0 | town_r121nd_671AA8_true_800162A8.overlay.yaml |
| t2 | town/func_806F24AC | func_80016CAC | 0x6724AC | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6724AC_true_80016CAC.overlay.yaml |
| t2 | town/func_806F26A0 | func_80016EA0 | 0x6726A0 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6726A0_true_80016EA0.overlay.yaml |
| t2 | town/func_8070F7E4 | func_800187E4 | 0x68F7E4 | 56 | 2.7.2-cdk-G0 | town_r121nd_68F7E4_true_800187E4.overlay.yaml |
| t2 | town/func_8070F81C | func_8001881C | 0x68F81C | 56 | 2.7.2-cdk-G0 | town_r121nd_68F81C_true_8001881C.overlay.yaml |
| t2 | town/func_80710B68 | func_80019B68 | 0x690B68 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_690B68_true_80019B68.overlay.yaml |
| t2 | town/func_80710D5C | func_80019D5C | 0x690D5C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_690D5C_true_80019D5C.overlay.yaml |
| t2 | town/func_807118EC | func_8001A8EC | 0x6918EC | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_6918EC_true_8001A8EC.overlay.yaml |
| t2 | town/func_8072A328 | func_80016328 | 0x6AA328 | 56 | 2.7.2-cdk-G0 | town_r121nd_6AA328_true_80016328.overlay.yaml |
| t2 | town/func_8072A360 | func_80016360 | 0x6AA360 | 56 | 2.7.2-cdk-G0 | town_r121nd_6AA360_true_80016360.overlay.yaml |
| t2 | town/func_8072AE18 | func_80016E18 | 0x6AAE18 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6AAE18_true_80016E18.overlay.yaml |
| t2 | town/func_8072B00C | func_8001700C | 0x6AB00C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6AB00C_true_8001700C.overlay.yaml |
| t2 | town/func_8074D25C | func_80016A5C | 0x6CD25C | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6CD25C_true_80016A5C.overlay.yaml |
| t2 | town/func_8074D450 | func_80016C50 | 0x6CD450 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6CD450_true_80016C50.overlay.yaml |
| t2 | town/func_807626B8 | func_80016EB8 | 0x6E26B8 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6E26B8_true_80016EB8.overlay.yaml |
| t2 | town/func_807628AC | func_800170AC | 0x6E28AC | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6E28AC_true_800170AC.overlay.yaml |
| t2 | town/func_80763190 | func_80017990 | 0x6E3190 | 72 | 2.7.2-cdk-G0 -O1 | town_r121nd_6E3190_true_80017990.overlay.yaml |
| t2 | town/func_807701B4 | func_800169B4 | 0x6F01B4 | 56 | 2.7.2-cdk-G0 | town_r121nd_6F01B4_true_800169B4.overlay.yaml |
| t2 | town/func_80770AA8 | func_800172A8 | 0x6F0AA8 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6F0AA8_true_800172A8.overlay.yaml |
| t2 | town/func_80770C9C | func_8001749C | 0x6F0C9C | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6F0C9C_true_8001749C.overlay.yaml |
| t2 | town/func_80775210 | func_80016A10 | 0x6F5210 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6F5210_true_80016A10.overlay.yaml |
| t2 | town/func_80775404 | func_80016C04 | 0x6F5404 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6F5404_true_80016C04.overlay.yaml |
| t2 | town/func_80777A10 | func_80016A10 | 0x6F7A10 | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6F7A10_true_80016A10.overlay.yaml |
| t2 | town/func_80777C04 | func_80016C04 | 0x6F7C04 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6F7C04_true_80016C04.overlay.yaml |
| t2 | town/func_8077DC98 | func_80016498 | 0x6FDC98 | 56 | 2.7.2-cdk-G0 | town_r121nd_6FDC98_true_80016498.overlay.yaml |
| t2 | town/func_8077E58C | func_80016D8C | 0x6FE58C | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_6FE58C_true_80016D8C.overlay.yaml |
| t2 | town/func_8077E780 | func_80016F80 | 0x6FE780 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_6FE780_true_80016F80.overlay.yaml |
| t2 | town/func_80785218 | func_80016218 | 0x705218 | 56 | 2.7.2-cdk-G0 | town_r121nd_705218_true_80016218.overlay.yaml |
| t2 | town/func_80785B0C | func_80016B0C | 0x705B0C | 92 | 2.7.2-cdk-G0 -O1 | town_r121nd_705B0C_true_80016B0C.overlay.yaml |
| t2 | town/func_80785D00 | func_80016D00 | 0x705D00 | 176 | 2.7.2-cdk-G0 -O1 | town_r121nd_705D00_true_80016D00.overlay.yaml |
| t2 | town/func_80874D54 | func_80700D54 | 0x7F4D54 | 48 | 2.6.3 | town_r121nd_7F4D54_true_80700D54.overlay.yaml |
| t2 | town/func_8087568C | func_8070168C | 0x7F568C | 236 | 2.6.3 | town_r121nd_7F568C_true_8070168C.overlay.yaml |
| t2 | town/func_808832D4 | func_80700AD4 | 0x8032D4 | 88 | 2.6.3-G0 | town_r121nd_8032D4_true_80700AD4.overlay.yaml |
| t2 | town/func_80883380 | func_80700B80 | 0x803380 | 88 | 2.6.3-G0 | town_r121nd_803380_true_80700B80.overlay.yaml |
| t2 | town/func_80883548 | func_80700D48 | 0x803548 | 236 | 2.6.3-G0 | town_r121nd_803548_true_80700D48.overlay.yaml |
| t2 | town/func_808B2AD4 | func_807002D4 | 0x832AD4 | 48 | 2.6.3 | town_r121nd_832AD4_true_807002D4.overlay.yaml |
| t2 | town/func_808B2F24 | func_80700724 | 0x832F24 | 52 | 2.6.3 | town_r121nd_832F24_true_80700724.overlay.yaml |
| t2 | town/func_808B310C | func_8070090C | 0x83310C | 236 | 2.6.3 | town_r121nd_83310C_true_8070090C.overlay.yaml |
| t2 | town/func_808B337C | func_80700B7C | 0x83337C | 236 | 2.6.3 | town_r121nd_83337C_true_80700B7C.overlay.yaml |
| v0 | town/func_808B7ED8 | func_800036D8 | 0x837ED8 | 72 | 2.6.3-G0 | town_r121nd_837ED8_true_800036D8.overlay.yaml |
| v0 | town/func_808B8014 | func_80003814 | 0x838014 | 88 | 2.6.3-G0 | town_r121nd_838014_true_80003814.overlay.yaml |
| v0 | town/func_808B806C | func_8000386C | 0x83806C | 76 | 2.6.3-G0 | town_r121nd_83806C_true_8000386C.overlay.yaml |
| v0 | town/func_808B7DD4 | func_800035D4 | 0x837DD4 | 148 | 2.6.3-G0 | town_r121nd_837DD4_true_800035D4.overlay.yaml |
| v0 | town/func_808B7E68 | func_80003668 | 0x837E68 | 112 | 2.6.3-G0 | town_r121nd_837E68_true_80003668.overlay.yaml |
| v0 | town/func_808B7F20 | func_80003720 | 0x837F20 | 152 | 2.6.3-G0 | town_r121nd_837F20_true_80003720.overlay.yaml |
| v0 | town/func_808B7FB8 | func_800037B8 | 0x837FB8 | 92 | 2.6.3-G0 | town_r121nd_837FB8_true_800037B8.overlay.yaml |
| v0 | town/func_808B80B8 | func_800038B8 | 0x8380B8 | 80 | 2.6.3-G0 | town_r121nd_8380B8_true_800038B8.overlay.yaml |
| v0 | town/func_808B82E0 | func_80003AE0 | 0x8382E0 | 52 | 2.6.3-G0 | town_r121nd_8382E0_true_80003AE0.overlay.yaml |
| v0 | town/func_808B8314 | func_80003B14 | 0x838314 | 52 | 2.6.3-G0 | town_r121nd_838314_true_80003B14.overlay.yaml |
| v0 | town/func_808B83CC | func_80003BCC | 0x8383CC | 80 | 2.6.3 | town_r121nd_8383CC_true_80003BCC.overlay.yaml |
| v0 | town/func_808B841C | func_80003C1C | 0x83841C | 84 | 2.6.3 | town_r121nd_83841C_true_80003C1C.overlay.yaml |
| v0 | town/func_808B8470 | func_80003C70 | 0x838470 | 96 | 2.6.3 | town_r121nd_838470_true_80003C70.overlay.yaml |
| v0 | town/func_808B85CC | func_80003DCC | 0x8385CC | 36 | 2.6.3-G0 | town_r121nd_8385CC_true_80003DCC.overlay.yaml |
| v0 | town/func_808BAF54 | func_80000754 | 0x83AF54 | 148 | 2.6.3-G0 | town_r121nd_83AF54_true_80000754.overlay.yaml |
| v0 | town/func_808BAFE8 | func_800007E8 | 0x83AFE8 | 112 | 2.6.3-G0 | town_r121nd_83AFE8_true_800007E8.overlay.yaml |
| v0 | town/func_808BB238 | func_80000A38 | 0x83B238 | 128 | 2.6.3-G0 | town_r121nd_83B238_true_80000A38.overlay.yaml |
| v0 | town/func_808C47F0 | func_800007F0 | 0x8447F0 | 148 | 2.6.3-G0 | town_r121nd_8447F0_true_800007F0.overlay.yaml |
| v0 | town/func_808C4884 | func_80000884 | 0x844884 | 112 | 2.6.3-G0 | town_r121nd_844884_true_80000884.overlay.yaml |
| v0 | town/func_808C49D4 | func_800009D4 | 0x8449D4 | 92 | 2.6.3-G0 | town_r121nd_8449D4_true_800009D4.overlay.yaml |
| v0 | town/func_808C4A30 | func_80000A30 | 0x844A30 | 88 | 2.6.3-G0 | town_r121nd_844A30_true_80000A30.overlay.yaml |
| v0 | town/func_808C4ADC | func_80000ADC | 0x844ADC | 100 | 2.6.3-G0 | town_r121nd_844ADC_true_80000ADC.overlay.yaml |
| v0 | town/func_808C4B40 | func_80000B40 | 0x844B40 | 80 | 2.6.3 | town_r121nd_844B40_true_80000B40.overlay.yaml |
| v0 | town/func_808C4B90 | func_80000B90 | 0x844B90 | 84 | 2.6.3 | town_r121nd_844B90_true_80000B90.overlay.yaml |
| v0 | town/func_808C4BE4 | func_80000BE4 | 0x844BE4 | 96 | 2.6.3 | town_r121nd_844BE4_true_80000BE4.overlay.yaml |
| v0 | town/func_808C4C44 | func_80000C44 | 0x844C44 | 72 | 2.6.3-G0 | town_r121nd_844C44_true_80000C44.overlay.yaml |
| v0 | town/func_808C4C8C | func_80000C8C | 0x844C8C | 36 | 2.6.3-G0 | town_r121nd_844C8C_true_80000C8C.overlay.yaml |
| v0 | town/func_808C4CB0 | func_80000CB0 | 0x844CB0 | 236 | 2.7.2 | town_r121nd_844CB0_true_80000CB0.overlay.yaml |
| v0 | town/func_808B7D44 | func_80003544 | 0x837D44 | 144 | 2.6.3-G0 | town_r121nd_837D44_true_80003544.overlay.yaml |
| v0 | town/func_808BAEC4 | func_800006C4 | 0x83AEC4 | 144 | 2.6.3-G0 | town_r121nd_83AEC4_true_800006C4.overlay.yaml |
| v0 | town/func_808C4760 | func_80000760 | 0x844760 | 144 | 2.6.3-G0 | town_r121nd_844760_true_80000760.overlay.yaml |
| v0 | town/func_808C493C | func_8000093C | 0x84493C | 152 | 2.6.3-G0 | town_r121nd_84493C_true_8000093C.overlay.yaml |
| v0 | town/func_808BB0A0 | func_800008A0 | 0x83B0A0 | 152 | 2.6.3-G0 | town_r121nd_83B0A0_true_800008A0.overlay.yaml |
| v0 | town/func_808C48F4 | func_800008F4 | 0x8448F4 | 72 | 2.6.3-G0 | town_r121nd_8448F4_true_800008F4.overlay.yaml |
| v0 | town/func_808B8254 | func_80003A54 | 0x838254 | 88 | 2.6.3-G0 | town_r121nd_838254_true_80003A54.overlay.yaml |
| v0 | town/func_808B84D0 | func_80003CD0 | 0x8384D0 | 252 | 2.6.3-G0 | town_r121nd_8384D0_true_80003CD0.overlay.yaml |
| v0 | town/func_808C4A88 | func_80000A88 | 0x844A88 | 84 | 2.6.3-G0 | town_r121nd_844A88_true_80000A88.overlay.yaml |
| t2 | town/func_8088332C | func_80700B2C | 0x80332C | 84 | 2.6.3-G0 | town_r121nd_80332C_true_80700B2C.overlay.yaml |
| t3 | dungeon/func_809AA57C | func_8016FD7C | 0x9CA57C | 196 | 2.7.2-cdk-G0 | dungeon_r121nd_9CA57C_true_8016FD7C.overlay.yaml |
| t3 | dungeon/func_809B057C | func_80169D7C | 0x9D057C | 196 | 2.7.2-cdk-G0 | dungeon_r121nd_9D057C_true_80169D7C.overlay.yaml |
| t3 | dungeon/func_809B657C | func_80163D7C | 0x9D657C | 196 | 2.7.2-cdk-G0 | dungeon_r121nd_9D657C_true_80163D7C.overlay.yaml |
| t3 | dungeon/func_809BC57C | func_8015DD7C | 0x9DC57C | 196 | 2.7.2-cdk-G0 | dungeon_r121nd_9DC57C_true_8015DD7C.overlay.yaml |
| t3 | dungeon/func_809C857C | func_80151D7C | 0x9E857C | 196 | 2.7.2-cdk-G0 | dungeon_r121nd_9E857C_true_80151D7C.overlay.yaml |
| t3 | dungeon/func_80ACB5DC | func_8016ADDC | 0xAEB5DC | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_AEB5DC_true_8016ADDC.overlay.yaml |
| t3 | dungeon/func_80AD15DC | func_80164DDC | 0xAF15DC | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_AF15DC_true_80164DDC.overlay.yaml |
| t3 | dungeon/func_80AD75DC | func_8015EDDC | 0xAF75DC | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_AF75DC_true_8015EDDC.overlay.yaml |
| t3 | dungeon/func_80ADD5DC | func_80158DDC | 0xAFD5DC | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_AFD5DC_true_80158DDC.overlay.yaml |
| t3 | dungeon/func_80AE35DC | func_80152DDC | 0xB035DC | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B035DC_true_80152DDC.overlay.yaml |
| t3 | dungeon/func_80AE95DC | func_8014CDDC | 0xB095DC | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B095DC_true_8014CDDC.overlay.yaml |
| t3 | dungeon/func_80AF54F8 | func_8016ACF8 | 0xB154F8 | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B154F8_true_8016ACF8.overlay.yaml |
| t3 | dungeon/func_80AFB4F8 | func_80164CF8 | 0xB1B4F8 | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B1B4F8_true_80164CF8.overlay.yaml |
| t3 | dungeon/func_80B014F8 | func_8015ECF8 | 0xB214F8 | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B214F8_true_8015ECF8.overlay.yaml |
| t3 | dungeon/func_80B074F8 | func_80158CF8 | 0xB274F8 | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B274F8_true_80158CF8.overlay.yaml |
| t3 | dungeon/func_80B0D4F8 | func_80152CF8 | 0xB2D4F8 | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B2D4F8_true_80152CF8.overlay.yaml |
| t3 | dungeon/func_80B134F8 | func_8014CCF8 | 0xB334F8 | 580 | 2.7.2-cdk-G0 | dungeon_r121nd_B334F8_true_8014CCF8.overlay.yaml |
| t3 | dungeon/func_812B006C | func_8016F86C | 0x12D006C | 248 | 2.7.2-cdk-G0 | dungeon_r121nd_12D006C_true_8016F86C.overlay.yaml |
| t3 | dungeon/func_812B606C | func_8016986C | 0x12D606C | 248 | 2.7.2-cdk-G0 | dungeon_r121nd_12D606C_true_8016986C.overlay.yaml |
| t3 | dungeon/func_812BC06C | func_8016386C | 0x12DC06C | 248 | 2.7.2-cdk-G0 | dungeon_r121nd_12DC06C_true_8016386C.overlay.yaml |
| t3 | dungeon/func_812C206C | func_8015D86C | 0x12E206C | 248 | 2.7.2-cdk-G0 | dungeon_r121nd_12E206C_true_8015D86C.overlay.yaml |
| t3 | town/func_8067F770 | func_80016770 | 0x5FF770 | 44 | 2.7.2-cdk-G0 | town_r121nd_5FF770_true_80016770.overlay.yaml |
| t3 | town/func_8067F79C | func_8001679C | 0x5FF79C | 44 | 2.7.2-cdk-G0 | town_r121nd_5FF79C_true_8001679C.overlay.yaml |
| t3 | town/func_8067F7C8 | func_800167C8 | 0x5FF7C8 | 40 | 2.7.2-cdk-G0 | town_r121nd_5FF7C8_true_800167C8.overlay.yaml |
| t3 | town/func_8067F7F0 | func_800167F0 | 0x5FF7F0 | 40 | 2.7.2-cdk-G0 | town_r121nd_5FF7F0_true_800167F0.overlay.yaml |
| t3 | town/func_8067F818 | func_80016818 | 0x5FF818 | 40 | 2.7.2-cdk-G0 | town_r121nd_5FF818_true_80016818.overlay.yaml |
| t3 | town/func_8067F840 | func_80016840 | 0x5FF840 | 16 | 2.7.2-cdk-G0 | town_r121nd_5FF840_true_80016840.overlay.yaml |
| t3 | town/func_80353EE4 | func_8001FBB4 | 0x2D3EE4 | 8 | 2.7.2-cdk-G0 | town_r121nd_2D3EE4_true_8001FBB4.overlay.yaml |
| t3 | town/func_80353F04 | func_8001FBD4 | 0x2D3F04 | 8 | 2.7.2-cdk-G0 | town_r121nd_2D3F04_true_8001FBD4.overlay.yaml |
| t3 | town/func_8080E594 | func_80529194 | 0x78E594 | 8 | 2.7.2-cdk-G0 | town_r121nd_78E594_true_80529194.overlay.yaml |
| t3 | town/func_80875510 | func_80701510 | 0x7F5510 | 8 | 2.7.2-cdk-G0 | town_r121nd_7F5510_true_80701510.overlay.yaml |
| t3 | town/func_80875798 | func_80701798 | 0x7F5798 | 8 | 2.7.2-cdk-G0 | town_r121nd_7F5798_true_80701798.overlay.yaml |
| t3 | town/func_80875800 | func_80701800 | 0x7F5800 | 8 | 2.7.2-cdk-G0 | town_r121nd_7F5800_true_80701800.overlay.yaml |
| t3 | town/func_80880090 | func_80701090 | 0x800090 | 80 | 2.6.3 | town_r121nd_800090_true_80701090.overlay.yaml |
| t3 | town/func_808800E0 | func_807010E0 | 0x8000E0 | 84 | 2.6.3 | town_r121nd_8000E0_true_807010E0.overlay.yaml |
| t3 | town/func_808833D8 | func_80700BD8 | 0x8033D8 | 80 | 2.6.3 | town_r121nd_8033D8_true_80700BD8.overlay.yaml |
| t3 | town/func_80883428 | func_80700C28 | 0x803428 | 84 | 2.6.3 | town_r121nd_803428_true_80700C28.overlay.yaml |
| t3 | town/func_808B2E6C | func_8070066C | 0x832E6C | 8 | 2.7.2-cdk-G0 | town_r121nd_832E6C_true_8070066C.overlay.yaml |
| t3 | town/func_808B3218 | func_80700A18 | 0x833218 | 8 | 2.7.2-cdk-G0 | town_r121nd_833218_true_80700A18.overlay.yaml |
| t3 | town/func_808B96AC | func_A07006AC | 0x8396AC | 80 | 2.6.3 | town_r121nd_8396AC_true_A07006AC.overlay.yaml |
| t3 | town/func_808B96FC | func_A07006FC | 0x8396FC | 84 | 2.6.3 | town_r121nd_8396FC_true_A07006FC.overlay.yaml |
| t3 | town/func_8094D4D8 | func_800164D8 | 0x8CD4D8 | 88 | 2.7.2-G0 | town_r121nd_8CD4D8_true_800164D8.overlay.yaml |
| t3 | town/func_8094E4D8 | func_800164D8 | 0x8CE4D8 | 88 | 2.7.2-G0 | town_r121nd_8CE4D8_true_800164D8.overlay.yaml |
| t3 | town/func_8094F4D4 | func_800164D4 | 0x8CF4D4 | 88 | 2.7.2-G0 | town_r121nd_8CF4D4_true_800164D4.overlay.yaml |
| t3 | town/func_809504D4 | func_800164D4 | 0x8D04D4 | 88 | 2.7.2-G0 | town_r121nd_8D04D4_true_800164D4.overlay.yaml |
| t3 | town/func_809514D4 | func_800164D4 | 0x8D14D4 | 88 | 2.7.2-G0 | town_r121nd_8D14D4_true_800164D4.overlay.yaml |
| t3 | town/func_80956E64 | func_80023E64 | 0x8D6E64 | 8 | 2.7.2-cdk-G0 | town_r121nd_8D6E64_true_80023E64.overlay.yaml |
| t3 | town/func_808B97B0 | func_A07007B0 | 0x8397B0 | 252 | 2.7.2-G0 | town_r121nd_8397B0_true_A07007B0.overlay.yaml |
| v0 | town/func_808B8720 | func_80003F20 | 0x838720 | 48 | 2.6.3 | town_r121nd_838720_true_80003F20.overlay.yaml |
| v0 | town/func_808BB6D8 | func_80000ED8 | 0x83B6D8 | 48 | 2.6.3 | town_r121nd_83B6D8_true_80000ED8.overlay.yaml |
| t3 | town/func_8035A5AC | func_8001EA7C | 0x2DA5AC | 56 | 2.7.2-cdk-G0 | town_r121nd_2DA5AC_true_8001EA7C.overlay.yaml |
| t3 | town/func_808817C4 | func_80700FC4 | 0x8017C4 | 48 | 2.6.3 | town_r121nd_8017C4_true_80700FC4.overlay.yaml |
| t3 | town/func_808B2AA4 | func_807002A4 | 0x832AA4 | 48 | 2.6.3 | town_r121nd_832AA4_true_807002A4.overlay.yaml |
| t3 | town/func_808B3488 | func_80700C88 | 0x833488 | 8 | 2.7.2-cdk-G0 | town_r121nd_833488_true_80700C88.overlay.yaml |
| t3 | town/func_808B356C | func_80700D6C | 0x83356C | 84 | 2.6.3 | town_r121nd_83356C_true_80700D6C.overlay.yaml |
| t3 | town/func_808B98D0 | func_A07008D0 | 0x8398D0 | 260 | 2.6.3-G0 | town_r121nd_8398D0_true_A07008D0.overlay.yaml |
| t3 | town/func_80952598 | func_80016598 | 0x8D2598 | 88 | 2.7.2-G0 | town_r121nd_8D2598_true_80016598.overlay.yaml |
| t3 | dungeon/func_80D71810 | func_80165010 | 0xD91810 | 460 | 2.7.2-cdk-G0 | dungeon_r121nd_D91810_true_80165010.overlay.yaml |
| t3 | dungeon/func_80D71C5C | func_8016545C | 0xD91C5C | 512 | 2.7.2-cdk-G0 | dungeon_r121nd_D91C5C_true_8016545C.overlay.yaml |
| t3 | dungeon/func_80D77810 | func_8015F010 | 0xD97810 | 460 | 2.7.2-cdk-G0 | dungeon_r121nd_D97810_true_8015F010.overlay.yaml |
| t3 | dungeon/func_80D77C5C | func_8015F45C | 0xD97C5C | 512 | 2.7.2-cdk-G0 | dungeon_r121nd_D97C5C_true_8015F45C.overlay.yaml |
| t3 | dungeon/func_80D7D810 | func_80159010 | 0xD9D810 | 460 | 2.7.2-cdk-G0 | dungeon_r121nd_D9D810_true_80159010.overlay.yaml |
| t3 | dungeon/func_80D7DC5C | func_8015945C | 0xD9DC5C | 512 | 2.7.2-cdk-G0 | dungeon_r121nd_D9DC5C_true_8015945C.overlay.yaml |
| t3 | dungeon/func_80D83810 | func_80153010 | 0xDA3810 | 460 | 2.7.2-cdk-G0 | dungeon_r121nd_DA3810_true_80153010.overlay.yaml |
| t3 | dungeon/func_80D83C5C | func_8015345C | 0xDA3C5C | 512 | 2.7.2-cdk-G0 | dungeon_r121nd_DA3C5C_true_8015345C.overlay.yaml |
| t3 | dungeon/func_80D89810 | func_8014D010 | 0xDA9810 | 460 | 2.7.2-cdk-G0 | dungeon_r121nd_DA9810_true_8014D010.overlay.yaml |
| t3 | dungeon/func_80D89C5C | func_8014D45C | 0xDA9C5C | 512 | 2.7.2-cdk-G0 | dungeon_r121nd_DA9C5C_true_8014D45C.overlay.yaml |
| t3 | dungeon/func_80E42C80 | func_80170480 | 0xE62C80 | 336 | 2.7.2-cdk-G0 | dungeon_r121nd_E62C80_true_80170480.overlay.yaml |
| t3 | dungeon/func_80E48C80 | func_8016A480 | 0xE68C80 | 336 | 2.7.2-cdk-G0 | dungeon_r121nd_E68C80_true_8016A480.overlay.yaml |
| t3 | dungeon/func_80E4EC80 | func_80164480 | 0xE6EC80 | 336 | 2.7.2-cdk-G0 | dungeon_r121nd_E6EC80_true_80164480.overlay.yaml |
| t3 | dungeon/func_80E54C80 | func_8015E480 | 0xE74C80 | 336 | 2.7.2-cdk-G0 | dungeon_r121nd_E74C80_true_8015E480.overlay.yaml |
| t3 | dungeon/func_80E5AC80 | func_80158480 | 0xE7AC80 | 336 | 2.7.2-cdk-G0 | dungeon_r121nd_E7AC80_true_80158480.overlay.yaml |
| t3 | dungeon/func_80E60C80 | func_80152480 | 0xE80C80 | 336 | 2.7.2-cdk-G0 | dungeon_r121nd_E80C80_true_80152480.overlay.yaml |

Batches: p1 = in production window town_deep_t8_03ea (proven w4t2 bank regions); p2 = proven rowbase region, minted per-row true-base window; p3 = new rowbase record from the TOWN script-module loader evidence (module header + descriptor sectors); p4 = new rowbase record from in-row local j + jal entry witnesses / authenticated bank map; p5 = new rowbase record from string-operand witnesses in the devkit image (sn_main.c); t1 = near-twin sample: copies of module-0 helpers / siblings with field or constant differences.

## Continuation (coordinator items 1, 2 and the link-at-0 images)

- Instance tranche: 7 fresh strict instance links (ledger/instances.jsonl, superseding the stale/partial records) made with the
  r121_instances prover unchanged (vendored copy); receipts, objects and link scripts in docs/evidence/r121_nodonor_instances/.
  The other 49 byte-identical copies stay partial: placement-invariant bytes, no base evidence at this standard.
- t2 relinks: the twin's CURRENT source is compiled at the twin's recipe and linked at the copy's base with external bindings
  inferred only at real ELF relocation sites (prover.infer_bindings); byte equality is required before the source is renamed
  (func_/D_<addr> per binding, declarations copied from the twin's headers). Copies that differ at non-relocation words are written
  from family templates read from their own retail words, or from the twin text plus a stated edit (each edit is named in the file
  header and re-checked by the same byte comparison). Placement: existing proven regions, TOWN module loader extents, in-row j
  solves (>= 2 distinct targets, or 1 with a jal witness / agreeing proven neighbour), or no-j rows with jal witnesses agreeing with
  a proven neighbour (the r121nd_803198 standard). A minted region never overlaps an existing one (clipped at a same-delta region).
  Jump-table functions get their first pass from spimdisasm --file-splits over the function and each table (m2c -f).
- Link-at-0 devkit images A (base file 0x834800), B (0x83A800), C (0x844000): records carry address_domain
  "unrelocated-object-code-projection", runtime_placement "unproven" and coverage_class "devkit object-coordinate image, not loaded
  by retail (unproven)" - filter on these to show coverage with and without. Evidence per image: string-operand base equation
  (A 9/15, B 11/14, C 5/9 at the base, 0 at +/-0x800), 0x800 alignment, every jal / j of the image code on an entry or the
  caller's own body (A 46, B 46, C 31, 0 exceptions), byte-exact recompile; negative control (link at base+0x800 without bindings):
  15 of 37 rows break (in-row j), 22 are link-placement-invariant and rest on the image-level evidence. Code starts one function
  earlier than the census heuristic (0x837D44 / 0x83AEC4 / 0x844760, jal-called entries right after the .rodata strings); the three
  data_segment split views covering them are shortened to end there (evidence_note on each).

## Placement pass 2 (holds of the continuation)

- Bank-grid: a DUNGEON census run laid out on a 0x6000 file grid, each cell holding one PROVEN per-floor image; the rule (every
  proven region inside a cell carries that cell's K) is checked on all proven regions of the run (0 disagree, 0 crossing a cell
  boundary, >= 2 outside the census image extents) before any record is minted.
- Twin-stride: the floor-bank family repeats every 0x6000 file bytes and links 0x6000 lower per bank, so a copy i banks after a
  proven twin derives delta_twin - i*0xC000; admitted only when that equals the K of the adjacent PROVEN census image (two
  independent sources); checked on the independently proven i=1 member of the D8B family.
- Town: bracketing by same-delta proven regions within 0x400 bytes on both sides of one jr-ra code run; unreferenced TOWN module
  headers 0x8CD000..0x8D2000 bounded by the next header; the authenticated CD bank map 0x2D9800..0x2DA800; devkit image headers
  (word 0 = entry pointer onto a complete entry, extent to the next header, KSEG0/KSEG1 aliases of one link base).
- 0x5FF770 verdict (decision 51): module 24 (header 0x5FF000, 6 sectors to 0x602000) owns 0x5FF770..0x5FF850 at base 0x7FA17000;
  module 23 (header 0x5DB800, 5 sectors) ends at 0x5DE000. The jal to 0x80016A4C lands on a prologue only at 0x7FA17000, the
  stored word 0x800188C8 lies inside module 24. The six r121_remnant_5FF7xx records are corrected (corrected_by: r121_nodonor),
  their wrong-base NOMATCH split views dropped, and three stale load_base fields (0x5FF4A0/C0/E0) fixed.
