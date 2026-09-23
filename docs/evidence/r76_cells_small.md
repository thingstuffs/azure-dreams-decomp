# Round 76: CPU-only cell scan of the small (1-2-pin) rows

2026-09-23. Scope: every pinned row with `pins_left` in {1,2} in `ledger/levels.jsonl`, excluding `ovmovie` -- 453 rows. Question: is the small-row tail (mostly dungeon) explained by a wrong compiler cell ("cse folds the integer, symbols need a split-address cell"), rather than a real C mechanism?

## Method

1. `python3 tools/pin_probe.py --cells --only <453 ids> --workers 8` -- strips every pin at once and scores the stripped text against all 7 stock cells x {bare, -G0} (14 cfgs) in one scorer call (`ledger/pins_cells.jsonl`, keyed on `in_sha`; already-journalled rows at the same text sha were skipped automatically -- 98 of the 453 were already fresh).

2. `python3 tools/pin_cells_land.py [--apply]` for the rule-1/2 admissible hits (pin-free exact at another cell AND the row's pinned text also exact there -- charter rule 4, no byte evidence lost).

3. A second, targeted pass on the 452-row residue (the rows a bare stock cell did not fix): the same stripped-text, multi-cfg scorer call extended with the one flag the stock grid does not carry, `-mno-split-addresses`, at `2.8.0[-G0]` / `2.8.1[-G0]` (the cells it exists for; `tools/pin_cells_scan.py`'s `SPLIT_ADDRESSES`). This is the literal split-address-cell hypothesis. Script: scratchpad `r76_splitaddr.py` (same `verify()`/`strip_text` machinery as `pin_probe.py --cells`, not checked into `tools/` since it is a one-flag variant of the same call `pin_cells_scan.py scan --flags2` already runs for rows that already carry a flag).

4. Landing: `tools/pin_cells_land.py` and a small companion script for the 3 split-address hits, both under `flock build_ovl/work/land_gap.lock` (the queue lock `land_gap.sh`/`land_finished2.sh` take), then one gate (`mk_ovl_root.sh` + `gate_all.py --workers 8` + `build_slus.sh`). `tools/lanes/land_finished2.sh` kept running throughout (isolated landings in `build_ovl_gate`); the queue lock serialised the two.

## Tooling fixes (this round)

- `tools/pin_probe.py` `probe_cells`: the stock-cell list was `sorted(STOCK_CELLS)` with no regard for the two 1999-only compilers (2.91.66, 2.95.2, "recorded, never built" per `pin_cells_scan.py`). A row exact at both a real cell and a LATE one could have its `cell` field silently land on the LATE one (first-exact-wins). Reordered so LATE cells sort last, and the winning `late` flag is now recorded on the record.

- `tools/pin_cells_land.py`: (a) skips any hit whose winning cell is LATE (2.91.66/2.95.2) -- never lands a 1999-compiler correction; (b) added `--only` to scope a landing run; (c) now appends every landed row to `ledger/recipe_trades.jsonl` (kind `recipe-switch`) *before* `set_row_cfg`, per charter rule 4 -- previously it only wrote `ledger/sweeps/t13_cellfix.jsonl` and the 17 rows landed by earlier runs of this tool were never recorded as trades; (d) moved the exact-at-target verify to before `set_row_cfg` so a refusal never touches the row's recorded cell.

## Results

453 rows scanned. 10 of them were independently landed pin-free during the scan window by the concurrently running `tools/lanes/land_finished2.sh` (unrelated model-lane candidates, not this round's work) and are excluded from the counts below.

| class | rows | landed |
|---|---:|---|
| pin-free at a bare stock cell, rule 1-2 holds | 1 | yes -- `dungeon/func_80B97094` 2.7.2 -> 2.6.3 |
| pin-free at `2.8.0[-G0] -mno-split-addresses`, rule 1-2 holds | 3 | yes (below) |
| pin-free at `2.8.0 -mno-split-addresses`, rule 2 fails AND off the module's own recipe | 1 | no (see note) |
| no cell (stock grid + split-address variant) reproduces the pin-free text | 439 | model-lane target list |

### Landed (4 rows, 4 pins, all kind `recipe-switch`, `ledger/recipe_trades.jsonl`)

| row | pins | cfg from | cfg to |
|---|---:|---|---|
| dungeon/func_80B97094 | 1 | 2.7.2 | 2.6.3 |
| dungeon/func_81811E30 | 1 | 2.7.2-G0 | 2.8.0-G0 -mno-split-addresses |
| dungeon/func_81811E70 | 1 | 2.7.2-G0 | 2.8.0 -mno-split-addresses |
| dungeon/func_800A4DDC | 1 | 2.7.2 | 2.8.0 -mno-split-addresses |

Gate: MATCH (3 windows rebuilt), SLUS SHA-1 gate MATCH. `STATUS.md` after landing: "Pin sites now: 3,686 in 897 rows" (the delta from the round's starting 3,701/902 also includes `land_finished2.sh`'s concurrent, unrelated landings).

### The one rule-2 refusal: `town/func_80874F4C`

Pin-free text is exact at `2.8.0 -mno-split-addresses` (total 0) but the row's *pinned* text is NOT exact there -- rule 2 fails, so this is not a plain cell correction. It is also not an admissible 4b coherence trade: the row's own module (`town/ovl_7f4c9c.c`) has `best_recipe: 2.6.3` in `ledger/module_recipe_census.jsonl`, and the row is already recorded at 2.6.3 -- the row already sits at its module's dominant recipe. Switching it to 2.8.0 would move it *away* from module coherence, not toward it, so charter clause 4b ("a switch toward the row's module census recipe") does not apply. Left pinned; a model-lane candidate, not a recipe question.

## The page-constant hypothesis: mostly refuted for this band

Of 452 rows a bare stock cell did not fix, only 4 (0.9%) resolve under the one flag built for exactly this mechanism (`-mno-split-addresses` at 2.8.x). The dungeon tail's small-pin rows are not, in the main, a recipe/cell problem: 439 of 453 scanned rows (97%) need a real C-level fix. Residue macro census (current pinned text, `pin_census.sites_of`): ASM_REG 315, ASM_KEEP 164, ASM_KEEP_NV 40, ASM_SCHED_BARRIER 33, ASM_USE 10, ASM_MEM_BARRIER 7, ASM_CLOBBER 7, others <=5 each (a row can carry more than one macro). By container: dungeon 290, town 90, slus 46, main 13 -- the dungeon tail is indeed most of the residue, but its pins are colouring/keep-alive/barrier macros, not raw integer-vs-symbol address pins (ASM_KEEP_NV, the constant-splitting macro, is only 40 of 439).

`pins_cells.jsonl` `class` (the scorer's residue class at the best-scoring cell, informational only -- it does not certify a fix) over the 439-row residue:

| class | rows |
|---|---:|
| broad | 75 |
| addressing | 61 |
| length-drift | 48 |
| const-remat | 45 |
| li-expansion | 34 |
| hold-set | 32 |
| reorder-only | 32 |
| slus-diff | 31 |
| reg-rename | 25 |
| slot-rotation | 16 |
| code-motion | 16 |
| block-order | 8 |
| polarity | 7 |
| dead-code-retention | 6 |
| delay-slot | 1 |
| (none) | 2 |

`addressing` (61) + `li-expansion` (34) = 95 rows carry an address/integer-literal residue shape even after the split-address flag failed to fix them -- these are the most promising sub-target for a model lane briefed on the page-constant mechanism specifically (the flag closes the easy 4, a C-level `ASM_KEEP_NV`/symbol-vs-constant rewrite is the lead for the rest).

## Model-lane target list (439 rows, no cell -- stock grid or split-address variant -- reproduces the pin-free text)

```
dungeon/func_7FFE79F4
dungeon/func_7FFEA9D4
dungeon/func_7FFED850
dungeon/func_7FFEDCA8
dungeon/func_80083E28
dungeon/func_8008557C
dungeon/func_80088964
dungeon/func_8008A7B8
dungeon/func_8008C504
dungeon/func_8008D69C
dungeon/func_8008E510
dungeon/func_8008EAA8
dungeon/func_8008F814
dungeon/func_800902B0
dungeon/func_80090C24
dungeon/func_80091258
dungeon/func_800914C4
dungeon/func_80092EB4
dungeon/func_80093898
dungeon/func_80094F0C
dungeon/func_80095658
dungeon/func_80095E4C
dungeon/func_8009612C
dungeon/func_800988D8
dungeon/func_800995D0
dungeon/func_800997A4
dungeon/func_8009A61C
dungeon/func_8009A734
dungeon/func_8009B140
dungeon/func_8009C088
dungeon/func_8009DEFC
dungeon/func_8009E7C8
dungeon/func_8009E94C
dungeon/func_8009F8EC
dungeon/func_800A065C
dungeon/func_800A1020
dungeon/func_800A1984
dungeon/func_800A2FBC
dungeon/func_800A38C4
dungeon/func_800A3A00
dungeon/func_800A5544
dungeon/func_800A76D4
dungeon/func_800A7828
dungeon/func_800A78F8
dungeon/func_800A8254
dungeon/func_800AAF90
dungeon/func_800ABD9C
dungeon/func_800AC914
dungeon/func_800ACC98
dungeon/func_800AD300
dungeon/func_800B34C0
dungeon/func_800B3868
dungeon/func_800B62E0
dungeon/func_800B6C84
dungeon/func_800B73A4
dungeon/func_800B771C
dungeon/func_800B89C0
dungeon/func_800B968C
dungeon/func_800BACA4
dungeon/func_800BB728
dungeon/func_800BD7CC
dungeon/func_800BE5DC
dungeon/func_800BF39C
dungeon/func_800BF6A0
dungeon/func_800BF7C0
dungeon/func_800BFCCC
dungeon/func_800C0848
dungeon/func_800C13E0
dungeon/func_800C2070
dungeon/func_800C29F0
dungeon/func_800C34BC
dungeon/func_800C3578
dungeon/func_800C5028
dungeon/func_800C5448
dungeon/func_800CB9CC
dungeon/func_800CBC58
dungeon/func_800CBFFC
dungeon/func_800CCF04
dungeon/func_800CFE34
dungeon/func_800D1374
dungeon/func_800D53F0
dungeon/func_800D5B7C
dungeon/func_800D6330
dungeon/func_800D64C0
dungeon/func_800D65FC
dungeon/func_80283000
dungeon/func_80283F70
dungeon/func_80284068
dungeon/func_80284480
dungeon/func_80285304
dungeon/func_80285E80
dungeon/func_80286684
dungeon/func_8028AE2C
dungeon/func_8028B18C
dungeon/func_8028BAA4
dungeon/func_8028BC54
dungeon/func_807AE960
dungeon/func_807AF648
dungeon/func_809753B0
dungeon/func_80976434
dungeon/func_80976B7C
dungeon/func_80976E28
dungeon/func_809A079C
dungeon/func_809A10A8
dungeon/func_809A1A8C
dungeon/func_809A3110
dungeon/func_809A38E4
dungeon/func_809C9654
dungeon/func_809CAE20
dungeon/func_809CB224
dungeon/func_809CBB58
dungeon/func_809CF054
dungeon/func_809DB054
dungeon/func_809E1054
dungeon/func_809ED054
dungeon/func_809F33F8
dungeon/func_809F3C00
dungeon/func_809F5574
dungeon/func_809F622C
dungeon/func_809F6D74
dungeon/func_80A1F0C4
dungeon/func_80A2008C
dungeon/func_80A49CB0
dungeon/func_80A4A694
dungeon/func_80A734C0
dungeon/func_80A9B07C
dungeon/func_80AC5470
dungeon/func_80AC5958
dungeon/func_80AC5F28
dungeon/func_80AC7A30
dungeon/func_80AC854C
dungeon/func_80AC88DC
dungeon/func_80AEF73C
dungeon/func_80AF1A80
dungeon/func_80AF3470
dungeon/func_80B1B010
dungeon/func_80B43670
dungeon/func_80B452F8
dungeon/func_80B47980
dungeon/func_80B6F204
dungeon/func_80B91054
dungeon/func_80B9ADE0
dungeon/func_80B9D094
dungeon/func_80BC1BA8
dungeon/func_80BC3AC4
dungeon/func_80BC44D4
dungeon/func_80BD9BA8
dungeon/func_80C17418
dungeon/func_80C180E0
dungeon/func_80C42B74
dungeon/func_80C69880
dungeon/func_80C6B878
dungeon/func_80C9325C
dungeon/func_80C93D90
dungeon/func_80CC2828
dungeon/func_80CEB850
dungeon/func_80D13E4C
dungeon/func_80D3B9B0
dungeon/func_80D3C944
dungeon/func_80D3D3B0
dungeon/func_80D3E260
dungeon/func_80D68D0C
dungeon/func_80D69D94
dungeon/func_80D91070
dungeon/func_80DBA050
dungeon/func_80DBC9D8
dungeon/func_80DE365C
dungeon/func_80DFB054
dungeon/func_80E0EAE4
dungeon/func_80E0EC38
dungeon/func_80E105D4
dungeon/func_80E376E4
dungeon/func_80E37EA4
dungeon/func_80E38914
dungeon/func_80E3B4CC
dungeon/func_80E618E0
dungeon/func_80E61EF4
dungeon/func_80E64FF0
dungeon/func_80E65598
dungeon/func_80E8B8F4
dungeon/func_80E8EC28
dungeon/func_80E9D000
dungeon/func_80EA3000
dungeon/func_80EB7D2C
dungeon/func_80EDF000
dungeon/func_80EDFF18
dungeon/func_80EF1000
dungeon/func_80F0928C
dungeon/func_80F0B2A8
dungeon/func_80F33E3C
dungeon/func_80F3575C
dungeon/func_80F87270
dungeon/func_80F89240
dungeon/func_80FB1000
dungeon/func_80FB35EC
dungeon/func_80FB4C24
dungeon/func_80FB5398
dungeon/func_80FB7000
dungeon/func_80FC3000
dungeon/func_80FDE420
dungeon/func_80FE1000
dungeon/func_80FF9000
dungeon/func_81007034
dungeon/func_810078B4
dungeon/func_8102F674
dungeon/func_810330FC
dungeon/func_81059F68
dungeon/func_8105A724
dungeon/func_8105F098
dungeon/func_81083694
dungeon/func_810860B4
dungeon/func_8108726C
dungeon/func_810876B4
dungeon/func_810ADDF4
dungeon/func_8127C3E0
dungeon/func_812A524C
dungeon/func_8132530C
dungeon/func_81325A04
dungeon/func_81325EF0
dungeon/func_81326794
dungeon/func_813274E4
dungeon/func_81327960
dungeon/func_813284E4
dungeon/func_81329AC4
dungeon/func_8132E2FC
dungeon/func_81330C74
dungeon/func_813315CC
dungeon/func_81332D28
dungeon/func_81335190
dungeon/func_81335C70
dungeon/func_813360FC
dungeon/func_81336754
dungeon/func_813374E8
dungeon/func_81338144
dungeon/func_81338C4C
dungeon/func_81339700
dungeon/func_81339F68
dungeon/func_8180D4D4
dungeon/func_81810198
dungeon/func_81811F04
dungeon/func_81811F54
dungeon/func_81811FA8
dungeon/func_8181214C
dungeon/func_81820DB4
dungeon/func_8182121C
dungeon/func_81832800
dungeon/func_81838800
dungeon/func_8184B130
dungeon/func_81874F58
dungeon/func_818761D8
dungeon/func_8187B9E8
dungeon/func_818818E8
dungeon/func_81888810
dungeon/func_8188E3A0
dungeon/func_8188EAAC
dungeon/func_818B6954
dungeon/func_818BC9CC
dungeon/func_818BD74C
dungeon/func_818C29D4
dungeon/func_818C2FAC
dungeon/func_818C3A3C
dungeon/func_818CE83C
dungeon/func_818E0800
dungeon/func_818E747C
dungeon/func_818F8800
dungeon/func_8190B2D0
dungeon/func_8191CD78
dungeon/func_8192365C
dungeon/func_819411F0
dungeon/func_8194D1E4
dungeon/func_81958878
dungeon/func_8195E81C
dungeon/func_8195F43C
dungeon/func_8196096C
dungeon/func_8196C568
dungeon/func_81976CB0
dungeon/func_81977B40
dungeon/func_81977FB8
dungeon/func_8197CEC0
dungeon/func_81983138
dungeon/func_81984754
dungeon/func_81984BF0
dungeon/func_81988800
dungeon/func_81988E48
dungeon/func_81989320
dungeon/func_819AD81C
dungeon/func_819B2E6C
dungeon/func_819C0000
dungeon/func_819C04E8
dungeon/func_819C0C18
main/func_8000E0F0
main/func_8000E298
main/func_8000F488
main/func_8000F934
main/func_800101E4
main/func_800120E8
main/func_80013128
main/func_80013B18
main/func_80014684
main/func_8001A2B0
main/func_8001BA1C
main/func_8001F2F4
main/func_800219C4
slus/konami_runtime_w_8003BAF8
slus/w_8003DE58
slus/w_8003E758
slus/w_8003F270
slus/w_8003F368
slus/w_8003F6F4
slus/w_800400B8
slus/w_800402F4
slus/w_80041284
slus/w_80041344
slus/w_80041E70
slus/w_80042560
slus/w_80042900
slus/w_80042A80
slus/w_80042BDC
slus/w_80043458
slus/w_80043EB8
slus/w_8004425C
slus/w_80046F88
slus/w_800477F4
slus/w_80047FF4
slus/w_8004878C
slus/w_800492B0
slus/w_800499E8
slus/w_8004AEC4
slus/w_8004CB2C
slus/w_8004CD28
slus/w_8004CECC
slus/w_8004D294
slus/w_8004D828
slus/w_8004DCA8
slus/w_8004DF8C
slus/w_8004E4C0
slus/w_8004F684
slus/w_8004FAA4
slus/w_800500B4
slus/w_800561D8
slus/w_80056654
slus/w_8005914C
slus/w_8005947C
slus/w_800595C0
slus/w_80059DAC
slus/w_80059E94
slus/w_8005A778
slus/w_8005A90C
slus/w_8005E4C4
town/func_8008DCA8
town/func_80090D8C
town/func_80091F04
town/func_80094F38
town/func_80095984
town/func_800980E0
town/func_8009973C
town/func_8009A1CC
town/func_8009BA60
town/func_8009CA88
town/func_8009CCBC
town/func_8009F654
town/func_800A406C
town/func_800A6420
town/func_800A7FDC
town/func_800AC118
town/func_800ADA80
town/func_800AE09C
town/func_800B00C8
town/func_800B0930
town/func_800B0ED0
town/func_800B3874
town/func_800B52D8
town/func_800B8934
town/func_800BB3A0
town/func_800BBB00
town/func_800BE540
town/func_800BEA7C
town/func_800BEE14
town/func_800BF718
town/func_800C0220
town/func_800C1370
town/func_800C1D6C
town/func_800C217C
town/func_800C2284
town/func_800C242C
town/func_800C3800
town/func_800C3ACC
town/func_800C4508
town/func_800C482C
town/func_800C5428
town/func_800C6228
town/func_800C7328
town/func_800CC9D4
town/func_800CF608
town/func_800CF814
town/func_8032BD34
town/func_8032C8B8
town/func_8032DE74
town/func_8032E17C
town/func_8032E8C0
town/func_8032EEE4
town/func_8046A6F8
town/func_8046BD98
town/func_8046C188
town/func_80470F3C
town/func_804D81D0
town/func_8051E954
town/func_8051F4AC
town/func_806D34CC
town/func_806D85A0
town/func_8080E994
town/func_808110CC
town/func_808119EC
town/func_80813368
town/func_808135E0
town/func_80813AB0
town/func_80818F60
town/func_80819B14
town/func_8081A3D8
town/func_8081BBC8
town/func_8081FCE0
town/func_80820AF4
town/func_80820EBC
town/func_808213CC
town/func_80874D84
town/func_80874F4C
town/func_80875060
town/func_8087514C
town/func_80875404
town/func_808786C0
town/func_8087FEF0
town/func_808B2B04
town/func_808B2CB0
town/func_808B2D90
town/func_808B2E74
town/func_808B8184
town/func_80956E6C
town/func_8096AE44
town/func_8096C508
```
