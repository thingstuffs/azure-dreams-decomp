# r121_twins2: 8,614 exact C rows / 3,150,852 bytes

Base: `9fe78bff5269271682eeb182c738bdb15d4d8203` (`SCRATCH_HEAD`). No commits. Changes, builds and measurements are in the lane's `staging/root`; the supplied private root is unchanged. Its external toolchain and venv are used read-only.

1. Census grouping: 205 ranked groups, including 49 bank families. `families.tsv` records every window, template lead, file step and link step. Families require a common source lead at the same relative offset, common file stride and opposite link stride. Different window lengths are retained. Lead bytes include untyped gaps and overlapping window views; they are not a coverage total.
2. Automation: `scripts/twins.py run FAMILY ...` performs complete donor-row relocation checks, source generation, body-backed import audit, normal scoring, genuine spimdisasm/m2c generation, normal rowbase promotion, all covering production window gates, baseline measurement and registry/graph checks. `scripts/parallel.py --jobs 6` gives each family worker private mutable files, build views and temporary paths, uses one compile worker per tree, and re-gates admitted windows after merging into the cumulative tree. It refreshes this package after every four families. Each failed bank is rolled back and recorded. Relocated direct-callee declarations are derived from matched callee bodies, with pointer pointees kept opaque across translation units. Unchanged resident declarations preserve the matched template. The bank surveys use complete registered donor extents at the fixed stride. CONTINUE2 also chains fully admitted predecessor banks while retaining the original matched C donor for every new row. Additional census hits remain leads until entry, placement and imports are proved.
3. Delivery: 8,614 new rows / 3,150,852 C bytes; 391 complete production windows MATCH. 49/49 bank families and 156/156 single-window groups processed. The following table distinguishes lead sizes from delivered code.
4. Single-window groups use `scripts/single_plan.py`: a complete matched body must bind to the census entry anchor and an existing complete rowbase region, fit the whole untyped gap, avoid existing extents, and pass the same relocation, import, source/raw and production gates. A broad window's synthetic view address never substitutes for a function's existing rowbase. Solved regions use the normal promotion hook before admission. `scripts/recover_bank_anchors.py --kind all --apply` applies that same policy to remaining gaps after the parallel queues finish, including earlier single-window holds; accepted rows are retained and temporary transactions are archived separately. Alternate masked hits without independent entry evidence remain holds. No source is admitted by masked similarity alone.
5. Included post-queue recovery: 171 census-anchor rows, 1 alternate-layout rows and 113 static direct-callee rows. Direct-callee seeds are frozen from previously admitted callers; newly recovered callees do not expand the survey. Every recovered row passes the same normal admission gates.

| rank | family / window group | banks | lead gap bytes | new rows | new C bytes | windows MATCH | candidate holds | status |
|---:|---|---:|---:|---:|---:|---:|---:|---|
| 1 | dungeon_1830080 | 1 | 190,260 | 2 | 16 | 1/1 | 17 | MATCH |
| 2 | town_52000 | 1 | 184,678 | 0 | 0 | 0/1 | 1 | HOLD |
| 3 | dungeon_e5d2d0 | 6 | 137,760 | 241 | 99,528 | 6/6 | 105 | MATCH |
| 4 | dungeon_e332e8 | 6 | 137,376 | 258 | 106,368 | 6/6 | 126 | MATCH |
| 5 | dungeon_d61284 | 6 | 136,048 | 151 | 70,784 | 6/6 | 188 | MATCH |
| 6 | dungeon_ce32e0 | 6 | 133,344 | 192 | 105,816 | 6/6 | 152 | MATCH |
| 7 | town_5dc000 | 1 | 132,212 | 0 | 0 | 0/1 | 65 | HOLD |
| 8 | dungeon_197ad48 | 1 | 131,996 | 0 | 0 | 0/1 | 7 | HOLD |
| 9 | dungeon_18d08ec | 1 | 129,452 | 0 | 0 | 0/1 | 7 | HOLD |
| 10 | dungeon_b69244 | 6 | 122,256 | 186 | 77,400 | 6/6 | 90 | MATCH |
| 11 | dungeon_d07540 | 1 | 120,932 | 10 | 3,344 | 1/1 | 257 | MATCH |
| 12 | dungeon_9c5294 | 6 | 118,608 | 163 | 58,136 | 6/6 | 208 | MATCH |
| 13 | dungeon_b0f73c | 7 | 115,376 | 198 | 72,688 | 7/7 | 104 | MATCH |
| 14 | dungeon_12cb24c | 6 | 112,636 | 127 | 44,432 | 6/6 | 119 | MATCH |
| 15 | dungeon_cb9120 | 6 | 112,296 | 169 | 57,552 | 6/6 | 135 | MATCH |
| 16 | dungeon_e87060 | 6 | 112,176 | 169 | 54,384 | 6/6 | 93 | MATCH |
| 17 | ovmovie_0 | 1 | 109,932 | 0 | 0 | 0/1 | 8 | HOLD |
| 18 | dungeon_10af284 | 5 | 108,220 | 185 | 75,720 | 5/5 | 85 | MATCH |
| 19 | dungeon_187c98c | 1 | 107,692 | 0 | 0 | 0/1 | 6 | HOLD |
| 20 | dungeon_bbd298 | 6 | 104,832 | 168 | 64,776 | 6/6 | 103 | MATCH |
| 21 | dungeon_ddf7d8 | 6 | 104,232 | 163 | 60,268 | 6/6 | 105 | MATCH |
| 22 | dungeon_c65250 | 6 | 102,168 | 168 | 74,760 | 6/6 | 85 | MATCH |
| 23 | dungeon_d91e5c | 5 | 101,760 | 120 | 53,380 | 5/5 | 80 | MATCH |
| 24 | dungeon_a6e000 | 6 | 98,280 | 156 | 61,152 | 6/6 | 126 | MATCH |
| 25 | dungeon_e03054 | 7 | 98,080 | 199 | 73,788 | 7/7 | 67 | MATCH |
| 26 | dungeon_ac1250 | 6 | 93,952 | 157 | 48,680 | 6/6 | 92 | MATCH |
| 27 | dungeon_d372d0 | 6 | 92,688 | 134 | 38,648 | 6/6 | 148 | MATCH |
| 28 | dungeon_a14000 | 7 | 91,064 | 160 | 68,568 | 7/7 | 58 | MATCH |
| 29 | dungeon_fd2000 | 7 | 89,500 | 154 | 43,876 | 7/7 | 104 | MATCH |
| 30 | dungeon_c0b060 | 7 | 89,484 | 172 | 62,388 | 7/7 | 82 | MATCH |
| 31 | dungeon_c8f060 | 6 | 87,744 | 157 | 53,904 | 6/6 | 78 | MATCH |
| 32 | dungeon_f83060 | 6 | 85,976 | 164 | 74,360 | 6/6 | 28 | MATCH |
| 33 | dungeon_eff6d8 | 7 | 85,296 | 161 | 49,408 | 7/7 | 92 | MATCH |
| 34 | dungeon_edb060 | 6 | 84,632 | 146 | 69,608 | 6/6 | 52 | MATCH |
| 35 | dungeon_1061674 | 4 | 83,648 | 104 | 31,664 | 4/4 | 48 | MATCH |
| 36 | dungeon_be7060 | 6 | 83,520 | 156 | 66,720 | 6/6 | 82 | MATCH |
| 37 | dungeon_fad270 | 6 | 82,004 | 127 | 53,984 | 6/6 | 120 | MATCH |
| 38 | dungeon_a97054 | 6 | 81,024 | 126 | 42,096 | 6/6 | 78 | MATCH |
| 39 | dungeon_10d3054 | 6 | 79,968 | 156 | 76,824 | 6/6 | 12 | MATCH |
| 40 | town_0 | 1 | 79,176 | 151 | 12,472 | 1/1 | 97 | MATCH |
| 41 | dungeon_b93054 | 6 | 79,024 | 152 | 67,504 | 6/6 | 24 | MATCH |
| 42 | dungeon_9ef054 | 6 | 78,192 | 152 | 60,552 | 6/6 | 53 | MATCH |
| 43 | dungeon_f2f054 | 6 | 76,228 | 156 | 59,356 | 6/6 | 41 | MATCH |
| 44 | dungeon_b3f054 | 6 | 75,864 | 150 | 61,536 | 6/6 | 24 | MATCH |
| 45 | dungeon_99b060 | 6 | 75,224 | 152 | 66,968 | 6/6 | 38 | MATCH |
| 46 | dungeon_c36000 | 7 | 74,364 | 149 | 72,516 | 7/7 | 28 | MATCH |
| 47 | dungeon_107f2a4 | 6 | 71,292 | 153 | 65,748 | 6/6 | 29 | MATCH |
| 48 | dungeon_ffb27c | 7 | 70,992 | 156 | 52,200 | 7/7 | 72 | MATCH |
| 49 | dungeon_aeb958 | 6 | 70,936 | 151 | 55,192 | 6/6 | 57 | MATCH |
| 50 | dungeon_1271060 | 7 | 69,012 | 230 | 61,900 | 7/7 | 68 | MATCH |
| 51 | dungeon_f59268 | 4 | 64,912 | 104 | 53,504 | 4/4 | 20 | MATCH |
| 52 | town_3eac60 | 1 | 58,512 | 6 | 1,236 | 1/1 | 416 | MATCH |
| 53 | dungeon_eab2f4 | 5 | 56,524 | 121 | 43,056 | 5/5 | 35 | MATCH |
| 54 | dungeon_a3d258 | 5 | 54,396 | 101 | 32,680 | 5/5 | 46 | MATCH |
| 55 | dungeon_a0000 | 1 | 50,744 | 13 | 800 | 1/1 | 8 | MATCH |
| 56 | dungeon_1025278 | 5 | 47,172 | 97 | 24,924 | 5/5 | 42 | MATCH |
| 57 | dungeon_1055674 | 2 | 41,824 | 53 | 16,744 | 2/2 | 44 | MATCH |
| 58 | dungeon_db5054 | 4 | 39,756 | 90 | 30,956 | 4/4 | 25 | MATCH |
| 59 | dungeon_19c0fc0 | 1 | 36,396 | 0 | 0 | 0/1 | 2 | HOLD |
| 60 | main_25d000 | 1 | 32,544 | 17 | 900 | 1/1 | 148 | MATCH |
| 61 | dungeon_daf23c | 3 | 23,912 | 59 | 18,320 | 3/3 | 17 | MATCH |
| 62 | dungeon_d8b3b8 | 1 | 23,076 | 27 | 12,004 | 1/1 | 21 | MATCH |
| 63 | dungeon_10a9060 | 1 | 22,192 | 36 | 13,908 | 1/1 | 18 | MATCH |
| 64 | main_217fc | 1 | 18,664 | 0 | 0 | 0/1 | 5 | HOLD |
| 65 | dungeon_eb72f4 | 1 | 17,300 | 29 | 14,220 | 1/1 | 5 | MATCH |
| 66 | dungeon_ec92f4 | 1 | 17,300 | 29 | 14,220 | 1/1 | 5 | MATCH |
| 67 | dungeon_51ebf4 | 1 | 17,268 | 33 | 11,388 | 1/1 | 12 | MATCH |
| 68 | dungeon_f6b268 | 1 | 16,228 | 25 | 12,588 | 1/1 | 5 | MATCH |
| 69 | dungeon_1031278 | 1 | 15,768 | 23 | 10,468 | 1/1 | 6 | MATCH |
| 70 | dungeon_1043278 | 1 | 15,768 | 23 | 10,468 | 1/1 | 6 | MATCH |
| 71 | dungeon_a49258 | 1 | 15,752 | 24 | 8,560 | 1/1 | 10 | MATCH |
| 72 | dungeon_a5b258 | 1 | 15,752 | 24 | 8,560 | 1/1 | 10 | MATCH |
| 73 | dungeon_525000 | 1 | 11,652 | 27 | 10,044 | 1/1 | 2 | MATCH |
| 74 | dungeon_f65268 | 1 | 11,608 | 23 | 9,928 | 1/1 | 3 | MATCH |
| 75 | dungeon_12c6000 | 1 | 11,216 | 20 | 6,692 | 1/1 | 8 | MATCH |
| 76 | dungeon_b39228 | 1 | 9,548 | 22 | 7,628 | 1/1 | 6 | MATCH |
| 77 | dungeon_c89880 | 1 | 9,356 | 22 | 7,436 | 1/1 | 6 | MATCH |
| 78 | dungeon_f7d23c | 1 | 9,148 | 22 | 7,228 | 1/1 | 6 | MATCH |
| 79 | dungeon_cb3060 | 1 | 8,716 | 22 | 6,660 | 1/1 | 6 | MATCH |
| 80 | dungeon_f2928c | 1 | 8,608 | 20 | 5,796 | 1/1 | 9 | MATCH |
| 81 | dungeon_b63060 | 1 | 8,544 | 23 | 6,652 | 1/1 | 6 | MATCH |
| 82 | dungeon_cdd2e0 | 1 | 8,148 | 18 | 7,684 | 1/1 | 11 | MATCH |
| 83 | dungeon_d32000 | 1 | 8,068 | 17 | 4,384 | 1/1 | 4 | MATCH |
| 84 | dungeon_f53268 | 1 | 7,980 | 19 | 7,088 | 1/1 | 5 | MATCH |
| 85 | dungeon_c5f060 | 1 | 7,804 | 12 | 4,064 | 1/1 | 5 | MATCH |
| 86 | dungeon_b8d230 | 1 | 7,392 | 19 | 5,472 | 1/1 | 6 | MATCH |
| 87 | dungeon_dd97d8 | 1 | 7,196 | 21 | 5,276 | 1/1 | 6 | MATCH |
| 88 | dungeon_e812fc | 1 | 6,964 | 19 | 4,440 | 1/1 | 8 | MATCH |
| 89 | dungeon_104f674 | 1 | 6,292 | 18 | 4,428 | 1/1 | 4 | MATCH |
| 90 | dungeon_abb060 | 1 | 5,980 | 12 | 3,208 | 1/1 | 6 | MATCH |
| 91 | dungeon_10cd228 | 1 | 5,836 | 18 | 5,680 | 1/1 | 5 | MATCH |
| 92 | dungeon_a91228 | 1 | 5,800 | 17 | 3,880 | 1/1 | 5 | MATCH |
| 93 | dungeon_10792a4 | 1 | 5,680 | 19 | 4,756 | 1/1 | 6 | MATCH |
| 94 | dungeon_ed5364 | 1 | 5,548 | 18 | 5,492 | 1/1 | 4 | MATCH |
| 95 | main_20000 | 1 | 3,956 | 0 | 0 | 0/1 | 4 | HOLD |
| 96 | dungeon_d89000 | 1 | 3,932 | 10 | 2,416 | 1/1 | 1 | MATCH |
| 97 | dungeon_a68000 | 1 | 3,800 | 6 | 3,328 | 1/1 | 1 | MATCH |
| 98 | dungeon_bb9000 | 1 | 3,380 | 15 | 1,624 | 1/1 | 6 | MATCH |
| 99 | dungeon_e572d0 | 1 | 3,380 | 11 | 3,380 | 1/1 | 1 | MATCH |
| 100 | dungeon_abe000 | 1 | 3,344 | 9 | 1,908 | 1/1 | 1 | MATCH |
| 101 | dungeon_ae6000 | 1 | 3,340 | 0 | 0 | 0/1 | 4 | HOLD |
| 102 | dungeon_18b2000 | 1 | 3,320 | 0 | 0 | 0/1 | 2 | HOLD |
| 103 | dungeon_10a5000 | 1 | 3,292 | 16 | 2,960 | 1/1 | 4 | MATCH |
| 104 | town_4cf000 | 1 | 3,220 | 0 | 0 | 0/1 | 12 | HOLD |
| 105 | dungeon_9c1000 | 1 | 3,176 | 11 | 1,196 | 1/1 | 9 | MATCH |
| 106 | dungeon_be19d0 | 1 | 3,112 | 13 | 3,056 | 1/1 | 2 | MATCH |
| 107 | town_8d3000 | 1 | 2,900 | 2 | 312 | 1/1 | 4 | MATCH |
| 108 | dungeon_c62000 | 1 | 2,760 | 9 | 1,908 | 1/1 | 1 | MATCH |
| 109 | dungeon_1274000 | 1 | 2,628 | 0 | 0 | 0/1 | 12 | HOLD |
| 110 | dungeon_1349000 | 1 | 2,624 | 23 | 1,164 | 1/1 | 6 | MATCH |
| 111 | town_2abfe8 | 1 | 2,560 | 19 | 928 | 1/1 | 18 | MATCH |
| 112 | dungeon_f03000 | 1 | 2,532 | 1 | 8 | 1/1 | 5 | MATCH |
| 113 | dungeon_e2e000 | 1 | 2,496 | 1 | 452 | 1/1 | 3 | MATCH |
| 114 | dungeon_bb8000 | 1 | 2,368 | 3 | 780 | 1/1 | 0 | MATCH |
| 115 | dungeon_9c0000 | 1 | 2,352 | 0 | 0 | 0/1 | 6 | HOLD |
| 116 | dungeon_d5d000 | 1 | 2,256 | 7 | 1,088 | 1/1 | 2 | MATCH |
| 117 | dungeon_9ea000 | 1 | 2,244 | 3 | 432 | 1/1 | 1 | MATCH |
| 118 | town_2ab000 | 1 | 2,244 | 2 | 16 | 1/1 | 4 | MATCH |
| 119 | dungeon_18ad004 | 1 | 2,204 | 2 | 388 | 1/1 | 5 | MATCH |
| 120 | town_617000 | 1 | 2,200 | 0 | 0 | 0/1 | 24 | HOLD |
| 121 | dungeon_182e000 | 1 | 2,172 | 0 | 0 | 0/1 | 2 | HOLD |
| 122 | dungeon_10a4000 | 1 | 2,152 | 1 | 1,864 | 1/1 | 2 | MATCH |
| 123 | dungeon_d87000 | 1 | 2,128 | 4 | 580 | 1/1 | 1 | MATCH |
| 124 | dungeon_18c4000 | 1 | 2,092 | 0 | 0 | 0/1 | 2 | HOLD |
| 125 | dungeon_1882000 | 1 | 2,048 | 0 | 0 | 0/1 | 1 | HOLD |
| 126 | dungeon_18d6000 | 1 | 2,048 | 0 | 0 | 0/1 | 1 | HOLD |
| 127 | dungeon_e06000 | 1 | 1,796 | 5 | 324 | 1/1 | 9 | MATCH |
| 128 | dungeon_134c000 | 1 | 1,752 | 1 | 156 | 1/1 | 2 | MATCH |
| 129 | town_49f000 | 1 | 1,680 | 4 | 96 | 1/1 | 18 | MATCH |
| 130 | dungeon_d8a000 | 1 | 1,540 | 0 | 0 | 0/1 | 5 | HOLD |
| 131 | dungeon_ae7000 | 1 | 1,536 | 12 | 1,324 | 1/1 | 1 | MATCH |
| 132 | dungeon_1348000 | 1 | 1,532 | 5 | 876 | 1/1 | 3 | MATCH |
| 133 | dungeon_1357000 | 1 | 1,512 | 7 | 408 | 1/1 | 1 | MATCH |
| 134 | dungeon_d88000 | 1 | 1,500 | 1 | 724 | 1/1 | 1 | MATCH |
| 135 | dungeon_a40000 | 1 | 1,492 | 10 | 1,472 | 1/1 | 1 | MATCH |
| 136 | town_794000 | 1 | 1,484 | 2 | 16 | 1/1 | 8 | MATCH |
| 137 | dungeon_1346004 | 1 | 1,416 | 10 | 564 | 1/1 | 6 | MATCH |
| 138 | town_3e8000 | 1 | 1,360 | 11 | 676 | 1/1 | 9 | MATCH |
| 139 | dungeon_e2f004 | 1 | 1,296 | 11 | 1,184 | 1/1 | 4 | MATCH |
| 140 | town_654000 | 1 | 1,288 | 1 | 8 | 1/1 | 16 | MATCH |
| 141 | dungeon_9eb004 | 1 | 1,276 | 10 | 676 | 1/1 | 3 | MATCH |
| 142 | dungeon_c63000 | 1 | 1,236 | 0 | 0 | 0/1 | 1 | HOLD |
| 143 | town_553000 | 1 | 1,184 | 0 | 0 | 0/1 | 25 | HOLD |
| 144 | town_438000 | 1 | 1,160 | 4 | 60 | 1/1 | 14 | MATCH |
| 145 | dungeon_a16000 | 1 | 1,136 | 9 | 644 | 1/1 | 2 | MATCH |
| 146 | dungeon_190d25c | 1 | 1,084 | 0 | 0 | 0/1 | 8 | HOLD |
| 147 | dungeon_fd7000 | 1 | 1,068 | 0 | 0 | 0/1 | 3 | HOLD |
| 148 | dungeon_fe3000 | 1 | 1,068 | 0 | 0 | 0/1 | 3 | HOLD |
| 149 | dungeon_fe9000 | 1 | 1,068 | 0 | 0 | 0/1 | 3 | HOLD |
| 150 | dungeon_ff5000 | 1 | 1,068 | 0 | 0 | 0/1 | 3 | HOLD |
| 151 | dungeon_a69000 | 1 | 1,064 | 8 | 696 | 1/1 | 1 | MATCH |
| 152 | dungeon_e5b000 | 1 | 996 | 1 | 84 | 1/1 | 1 | MATCH |
| 153 | town_2ac000 | 1 | 972 | 0 | 0 | 0/1 | 11 | HOLD |
| 154 | dungeon_abf000 | 1 | 956 | 0 | 0 | 0/1 | 1 | HOLD |
| 155 | dungeon_d60000 | 1 | 936 | 0 | 0 | 0/1 | 1 | HOLD |
| 156 | dungeon_bb769c | 1 | 932 | 0 | 0 | 0/1 | 1 | HOLD |
| 157 | dungeon_1356000 | 1 | 912 | 5 | 324 | 1/1 | 3 | MATCH |
| 158 | dungeon_1354004 | 1 | 892 | 5 | 336 | 1/1 | 1 | MATCH |
| 159 | dungeon_191e9b0 | 1 | 796 | 0 | 0 | 0/1 | 4 | HOLD |
| 160 | dungeon_134dbc4 | 1 | 780 | 1 | 300 | 1/1 | 2 | MATCH |
| 161 | dungeon_4dae0 | 1 | 708 | 3 | 288 | 1/1 | 9 | MATCH |
| 162 | dungeon_e5a000 | 1 | 688 | 5 | 324 | 1/1 | 3 | MATCH |
| 163 | dungeon_134f000 | 1 | 644 | 3 | 276 | 1/1 | 3 | MATCH |
| 164 | dungeon_1343128 | 1 | 640 | 2 | 348 | 1/1 | 2 | MATCH |
| 165 | dungeon_1357e4c | 1 | 624 | 7 | 624 | 1/1 | 0 | MATCH |
| 166 | dungeon_997000 | 1 | 600 | 9 | 544 | 1/1 | 2 | MATCH |
| 167 | town_83b2b8 | 1 | 596 | 0 | 0 | 0/1 | 4 | HOLD |
| 168 | dungeon_1345000 | 1 | 564 | 4 | 128 | 1/1 | 1 | MATCH |
| 169 | dungeon_129b060 | 7 | 560 | 49 | 1,540 | 7/7 | 65 | MATCH |
| 170 | dungeon_1e0fc | 1 | 556 | 0 | 0 | 0/1 | 2 | HOLD |
| 171 | dungeon_1359000 | 1 | 548 | 1 | 36 | 1/1 | 1 | MATCH |
| 172 | town_801478 | 1 | 484 | 0 | 0 | 0/1 | 5 | HOLD |
| 173 | dungeon_1907000 | 1 | 476 | 0 | 0 | 0/1 | 1 | HOLD |
| 174 | town_552928 | 1 | 452 | 1 | 76 | 1/1 | 5 | MATCH |
| 175 | town_594ac8 | 1 | 448 | 0 | 0 | 0/1 | 8 | HOLD |
| 176 | dungeon_a6b000 | 1 | 416 | 2 | 256 | 1/1 | 2 | MATCH |
| 177 | dungeon_fa9d7c | 1 | 376 | 0 | 0 | 0/1 | 1 | HOLD |
| 178 | dungeon_d86000 | 1 | 356 | 0 | 0 | 0/1 | 1 | HOLD |
| 179 | dungeon_d5d588 | 1 | 324 | 1 | 324 | 1/1 | 0 | MATCH |
| 180 | dungeon_135c000 | 1 | 320 | 0 | 0 | 0/1 | 1 | HOLD |
| 181 | town_2af000 | 1 | 284 | 2 | 92 | 1/1 | 3 | MATCH |
| 182 | dungeon_d5f268 | 1 | 268 | 4 | 268 | 1/1 | 0 | MATCH |
| 183 | dungeon_182f000 | 1 | 244 | 0 | 0 | 0/1 | 1 | HOLD |
| 184 | dungeon_13464c8 | 1 | 196 | 0 | 0 | 0/1 | 2 | HOLD |
| 185 | town_645244 | 1 | 152 | 4 | 152 | 1/1 | 0 | MATCH |
| 186 | dungeon_e32a58 | 1 | 140 | 0 | 0 | 0/1 | 3 | HOLD |
| 187 | dungeon_1913098 | 1 | 132 | 0 | 0 | 0/1 | 4 | HOLD |
| 188 | dungeon_8eb154 | 1 | 128 | 0 | 0 | 0/1 | 1 | HOLD |
| 189 | town_49eda4 | 1 | 120 | 0 | 0 | 0/1 | 2 | HOLD |
| 190 | dungeon_16ae8 | 1 | 108 | 0 | 0 | 0/1 | 2 | HOLD |
| 191 | dungeon_134e4f0 | 1 | 108 | 1 | 108 | 1/1 | 0 | MATCH |
| 192 | dungeon_186a930 | 1 | 108 | 1 | 108 | 1/1 | 0 | MATCH |
| 193 | town_4002bc | 1 | 96 | 0 | 0 | 0/1 | 2 | HOLD |
| 194 | dungeon_10a3060 | 1 | 92 | 0 | 0 | 0/1 | 1 | HOLD |
| 195 | dungeon_d074ec | 1 | 84 | 0 | 0 | 0/1 | 2 | HOLD |
| 196 | dungeon_1942998 | 1 | 84 | 1 | 84 | 1/1 | 0 | MATCH |
| 197 | dungeon_19c0d64 | 1 | 84 | 0 | 0 | 0/1 | 2 | HOLD |
| 198 | town_49ea54 | 1 | 84 | 0 | 0 | 0/1 | 2 | HOLD |
| 199 | town_7f8360 | 1 | 80 | 1 | 8 | 1/1 | 2 | MATCH |
| 200 | town_595268 | 1 | 76 | 0 | 0 | 0/1 | 2 | HOLD |
| 201 | town_2714dc | 1 | 64 | 0 | 0 | 0/1 | 2 | HOLD |
| 202 | dungeon_9411bc | 1 | 60 | 2 | 60 | 1/1 | 0 | MATCH |
| 203 | dungeon_d54c | 1 | 52 | 6 | 52 | 1/1 | 1 | MATCH |
| 204 | dungeon_135a3f0 | 1 | 36 | 1 | 36 | 1/1 | 0 | MATCH |
| 205 | dungeon_10a5c6c | 1 | 8 | 0 | 0 | 0/1 | 0 | HOLD |

Windows may contain retained raw segments. New C totals count only admitted complete bodies. `next.tsv` retains failed-attempt history: `SUPERSEDED_ROW_HOLD` entries now have an identical delivered extent, and `SUPERSEDED_ATTEMPT` marks an older failed attempt in a now-MATCH bank. Continue with the active `ROW_HOLD` and `BANK_HOLD` records. The table counts active candidate holds.

Every admitted source is ordinary C from an existing matched body, renamed using retail address pairs. Differing words are j/jal fields or reaching lui/lo16 pairs, apart from explicit CONTINUE3 literal variants recorded with their original C token and retail word. An independent audit binds every relocation difference to R_MIPS_26, R_MIPS_HI16 or R_MIPS_LO16 in the production compiler object. The source audit refuses pins, asm and volatile; CONTINUE3 sources also refuse goto. Relocation masking is used only for candidate discovery; all final production gates compare complete bytes without masking. Existing rowbase extents and deltas are unchanged; solved regions are upgraded only by the normal `rowbase.py promote` hook. No compiler, flags registry, header, gate or runtime contract is changed. Existing indirect-call declarations and expressions are inherited from the matched source; no dynamic target is asserted.

Direct import records bind each admitted call to a matched definition, a complete retail callee twin, or a consistent existing matched-header declaration for an unchanged resident PsyQ SDK symbol. Declaration-only callee proofs do not contribute to delivered totals. A finite one-hop recovery can admit static callees only after independently checking their caller, existing rowbase, complete gap extent and ABI agreement, followed by every normal source/raw/window gate. Alternate donor layouts require two independent complete anchors or a strict complete-window relocation proof. Missing non-SDK C bodies and conflicting SDK header declarations remain explicit holds. A byte match proves static placement, without asserting runtime reachability.

`delivery_twins2/` contains src/raw pairs, append-only split/registry/baseline/promotion/reverify transactions, changed rowbase records and physical graph, source and raw scores, relocation/import evidence, window receipts, first-pass commands and m2c revision, guards and full before-images. Raw is actual generated output, never copied matched C. Baselines record measured raw outcomes, including build failures. `records/levels_seed_needed.tsv` lists every new row that still needs an integrator ledger/levels.jsonl seed; that ledger is not silently populated. Coverage events are provided for integration.


## CONTINUE2 — tooling hold classes

Start: 1,935 rows / 1,093,992 B. New admissions retain complete original matched BASE donors. Chained placements and inherited callee prototypes have independent body proofs; all source, raw, rowbase, ELF relocation and complete production window gates still apply.

| item | class | additional rows | additional C bytes | remaining class B before | remaining class B latest | status |
|---:|---|---:|---:|---:|---:|---|
| 0 | bank chains | 1,129 | 404,784 | 592,080 | 100,572 | FIXED POINT |
| 1 | callee contract fixed point | 217 | 128,776 | 1,056,028 | 1,229,468 | FIXED POINT |
| 2 | function boundaries | 4,753 | 1,114,532 | 83,780 | 74,584 | DONE |
| 3 | in-place raw split replacement | 0 | 0 | 29,544 | 12,224 | DONE |
| 4 | near-twin handoff, report only | 0 | 0 | — | — | 747 spans; 688 donor comparisons |

Remaining-byte measurements use the supplied remaining.py interval-union algorithm. This private root lacks ledger/coverage_regions.jsonl and ledger/instances.jsonl; its direct output therefore omits most untyped gaps. Both direct results and a clearly marked census supplement are retained under records/continue2/. The supplement adds the original untyped census spans as unported coverage, then subtracts the current matched registry. Bytes are classified once by the tool’s documented priority; these columns are remaining categories, not exclusive attribution of recovered rows. New holds can move remaining bytes between classes, so a category can increase while total remaining coverage falls. The local allocation loop avoids repeated sorting; its complete output was byte-identical to the frozen copied tool on the retained measurement snapshot. The original priority order and interval unions are unchanged; remaining_optimization_provenance.json records both output hashes.

Latest serial global callee pass: round 1: 0 rows / 0 B.

Delivered caller unlocks by local fixed-point round: round 1: 217 rows / 128,776 B. Family workers freeze their inheritance index for each round; the serial global pass checks cross-family closure.

Final cross-class closure (bank chains, callee contracts, then raw replacement): round 1: 6 additional rows; round 2: 0 additional rows. The final zero-admission round establishes closure across the classes.

All 5 boundary families that predated the declaration correction were retried through the normal admission path.

Chain queue: 49/49 families; 67 additional merged rows in this pass.

Overlap audit: already-matched-C-protected: 183. The replacement helper is tested and requires exact tiling of a raw/asm code extent, preserves ledger order, refuses matched C/data, and re-runs the production gates after replacement.

13 delivered rows also append the same proven extents to independent production split ledgers. Existing ledger bytes and active ownership are preserved; historical reruns remain unchanged. These mirrors follow canonical rollback and contribute no duplicate C rows or bytes.

45 static function-value declarations derive from complete matched bodies. Source and target prototypes must agree; the encoded address resolves through an existing complete rowbase region and a whole target-body proof. These records assert no dynamic call or runtime reachability.

The native object audit binds each row to its measured production manifest extent, source hash, compiler recipe and object section before checking every differing word’s relocation. A green window that retained the proposed extent as raw bytes cannot admit that row.

The report-only near-twin table is records/continue2/near_twins/table.tsv, with complete differing-word details in table.json. A missing donor is explicit. Comparisons extending beyond the held span and overlap with delivered C are marked; 20 historical spans are now fully covered by separately bounded admitted C. No near-twin source was ported by CONTINUE2. CONTINUE3 reopens its explicitly authorized classes under separate proofs.

The frozen report-only scope excludes no-whole-body-twin gaps and the exact held nonrelocation/source-score extents from CONTINUE2 admission. A differently bounded complete function is a separate re-anchor candidate, with its own entry and full production proof.

Ordered continuation (original lane, one mutation runner at a time): `nice -n 15 python3 scripts/finish_continue2.py`, then `nice -n 15 python3 scripts/close_continue2.py` after the first driver completes. The second driver retries the workers that predate the declaration fix and iterates cross-class bank/callee/replacement closure before its final package. Both retain explicit resume checkpoints. Individual class commands: `nice -n 15 python3 scripts/recover_continue2.py chain --apply`, then `contracts --apply`, `boundaries --apply`, and `replace --apply`. Repeat chain/contracts after boundary admissions; finish with final_shared_windows.py and package.py. Completed transaction hashes prevent repeated identical compiler attempts. Normal production gates and the base SHA remain unchanged.



## CONTINUE3 — remaining holds

Start: 8,034 rows / 2,742,084 B. SDK declarations are read from existing include/ headers used by matched C. Conflicting declarations remain holds, including disagreements between named SDK functions and address aliases. No SDK C body or runtime contract is invented.

| item | class | additional rows | additional C bytes | unique holds before | frozen holds still uncovered | remaining class B before / latest | status |
|---:|---|---:|---:|---:|---:|---|---|
| 0 | SDK contracts and bank closure | 0 | 0 | 1593 | 1538 | 1,229,468 / 1,244,008 | DELIVERED |
| 1 | source score recovery | 233 | 74,468 | 314 | 74 | 43,484 / 13,492 | DELIVERED |
| 2 | differing-word recovery | 347 | 334,300 | 339 | 96 | 305,472 / 35,104 | DELIVERED |
| 3 | pinned templates and boundary fragments | 0 | 0 | — | — | count only | LEFT |

Hold counts use distinct physical extents in the initial next.tsv; the after column counts those spans not fully covered by delivered C, even when a different complete boundary recovered part of the span. Rows and bytes are credited to the item that admitted them; another item can also reduce a frozen hold class. Remaining bytes use remaining.py with both direct and census-supplement results. Categories can move when new holds become known. Evidence is under records/continue3/.

SDK symbol survey: BOUND: 37, CONFLICT: 23, NO_USABLE_MATCHED_HEADER: 311. `rand` (signed/unsigned return) and `rsin` (signed/unsigned argument) are held because matched headers disagree. Old-style unspecified declarations are also recorded and never silently turned into prototypes.

The completed CONTINUE2 payload contains 98 inherited rows using goto. Their existing sources and proofs are retained. Every new CONTINUE3 admission rejects goto. The inherited inventory is recorded in cumulative_goto_audit.json.

218 callee declarations use 25 independently proved copies of matched C with unused formal parameters or explicit word conversions at the interface. The interface comes from the matched source callee or a matched caller whose complete source callee independently proves that interface. Each word-width interface is independently recompiled at the original recipe and gated over the full window. Original return conversions are retained; unused argument changes additionally require incoming-register proofs for both canonical and encoded callees. Each changed input is unread before overwrite and cannot survive to an external transfer, including through its delay slot. Each C copy has an exact source score and ordinary full production-window proof, archived with its native object. Prototype proofs add no coverage bytes. SDK conflicts remain holds.

2 genuine m2c first passes supply a bounded, owned switch table lying inside the bank window to the normal disassembler as rodata. Table extents use existing rowbases, with the normal solved-to-proven promotion still required before admission, and every entry has the same function-relative destination. Generated assembly and C are unedited. The table witnesses add no C coverage bytes.

1 row spells additional C call arguments using its own incoming word-sized parameters. The existing complete matched callee owns the prototype. At the unique encoded call, both source and target CFG proofs require the same untouched incoming register values, including load and call delay slots. Intervening calls erase all inferred values; unknown and stack values are refused. Switch edges require an explicit bounded selector, a registered source table owned by the caller, proven rowbases for both tables, and every retail entry relocated to the same relative instruction. The source audit independently reconstructs every edit, and each caller passes all normal source/raw/window/native-object gates.

3 rows / 1,212 B recover missing link-base coverage. Each new rowbase record covers exactly one complete function, overlaps no supplied record, and uses two distinct internal jump targets from a complete matched C twin to identify the same link base. The target entry and terminal return are independently checked. Normal source/raw/window admission and the standard solved-to-proven promotion are required; the package audit recomputes the static evidence. Existing region extents and deltas are retained. No runtime-residency claim is added.

The pre-admission classification below counts complete donor comparisons. Six registered data donors are excluded from the function admission path.

| comparison class | spans |
|---|---:|
| unpaired-data-upper | 257 |
| multiple differences | 46 |
| already strict twin | 23 |
| address-low-or-arithmetic | 6 |
| struct-or-stack-offset | 1 |
| registered data | 6 |

Differing-word classification was emitted before admission: unpaired-data-upper: 266, instruction-or-register-change: 9734, address-low-or-arithmetic: 23, struct-or-stack-offset: 13, data-symbol-pointer: 38. Counts include every differing word in complete donor comparisons, including large structural mismatches; a near-twin comparison alone does not establish entry or extent.

Item 0 closure rounds: 1: 0 rows / 0 B; 2: 0 rows / 0 B.

Item 1 closure rounds: 1: 11 rows / 16,388 B; 2: 10 rows / 5,424 B; 3: 0 rows / 0 B; 4: 7 rows / 13,048 B; 5: 0 rows / 0 B; 6: 0 rows / 0 B.

Item 2 closure rounds: 1: 150 rows / 140,552 B; 2: 1 rows / 1,376 B; 3: 2 rows / 2,368 B; 4: 0 rows / 0 B; 5: 0 rows / 0 B.

Cross-class source/word closure: round 1: 0 rows / 0 B. The last round adds neither rows nor new proved interface models.

Left classes (initial unique physical extents): boundary_candidates_held: 2098, census_anchor_not_complete_twin: 171, template has pins/asm/volatile: 35.

Resume the ordered run in the original lane with `nice -n 15 python3 scripts/finish_continue3.py`. After it completes, run `nice -n 15 python3 scripts/close_continue3.py` for cross-class source/word closure. For a specific unfinished item, use `nice -n 15 python3 scripts/continue3_driver.py --item N`. The drivers record completed steps and publish after each item. Only one mutation runner may be active. The package keeps SCRATCH_HEAD guards and all normal source/raw/window/object checks.


## HOW TO CONTINUE

1. At this exact base, run `python3 delivery_twins2/apply.py --root R --live --dry-run`, then `--live`. An immediate second dry-run must print `"files": []`. Dry-run wins when both flags are supplied. Symlink or byte drift refuses before writes; a failed apply rolls back.
2. In R, run registry, row-db check and graph generation. Run every production window listed in `manifest.json` from build_ovl with the normal `overlay_local_gate.py --clean` command. Seed the listed levels rows under the integration policy, then reconcile supplied coverage events.
3. For remaining PENDING groups, run `nice -n 15 python3 scripts/parallel.py --jobs 6` for bank families or add `--kind single-window --refresh` for the single-window phase. One family can use `nice -n 15 python3 scripts/twins.py run FAMILY`. If the table has no PENDING groups, all current ranked groups have checkpoints; continue with the specific proof holds in `next.tsv` and archived anchor transactions. Completed results are resume checkpoints, including failed attempts. The parallel runner packages every four families. Do not start a second runner against the same mutable trees.
4. Use `next.tsv` and per-family evidence for holds. Resolve body-backed import contracts, non-relocation words, existing split ownership or raw switch-table context before reconsidering a held row. For generic windows, prove complete entries and placement before generating source. Do not change gates or add pins to force admission.
5. If any other package lands first, rebuild against the combined tree and rerun proofs, registry, row-db, graph and all affected production windows before regenerating guards. Do not bypass hashes.
6. To resume interrupted post-queue recovery, first finish `scripts/recover_bank_anchors.py --kind all --apply` with no other runner active. `scripts/recover_short_aspsx.py` retries the known ASPSX path holds using a physically short scratch directory inside the lane; gate code, inputs and flags remain unchanged. Then run `scripts/recover_extra_plans.py --dry-run` and `--apply`; default resume retains frozen one-hop seeds, so do not use `--refresh` during an active recovery. After all source mutations finish, run `scripts/final_shared_windows.py` and `scripts/package.py`. Completed transactions are cached. These recovery commands are for the original lane, not the integration target.
