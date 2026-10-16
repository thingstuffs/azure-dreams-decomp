# r121_twins2: 1,935 exact C rows / 1,093,992 bytes

Base: `9fe78bff5269271682eeb182c738bdb15d4d8203` (`SCRATCH_HEAD`). No commits. Changes, builds and measurements are in the lane's `staging/root`; the supplied private root is unchanged. Its external toolchain and venv are used read-only.

1. Census grouping: 205 ranked groups, including 49 bank families. `families.tsv` records every window, template lead, file step and link step. Families require a common source lead at the same relative offset, common file stride and opposite link stride. Different window lengths are retained. Lead bytes include untyped gaps and overlapping window views; they are not a coverage total.
2. Automation: `scripts/twins.py run FAMILY ...` performs complete donor-row relocation checks, source generation, body-backed import audit, normal scoring, genuine spimdisasm/m2c generation, normal rowbase promotion, all covering production window gates, baseline measurement and registry/graph checks. `scripts/parallel.py --jobs 6` gives each family worker private mutable files, build views and temporary paths, uses one compile worker per tree, and re-gates admitted windows after merging into the cumulative tree. It refreshes this package after every four families. Each failed bank is rolled back and recorded. Relocated direct-callee declarations are derived from matched callee bodies, with pointer pointees kept opaque across translation units. Unchanged resident declarations preserve the matched template. The bank implementation conservatively uses registered complete extents in the first bank's preceding current-link donor. Additional census hits remain leads.
3. Delivery: 1,935 new rows / 1,093,992 C bytes; 311 complete production windows MATCH. 49/49 bank families and 156/156 single-window groups processed. The following table distinguishes lead sizes from delivered code.
4. Single-window groups use `scripts/single_plan.py`: a complete matched body must bind to the census entry anchor and an existing complete rowbase region, fit the whole untyped gap, avoid existing extents, and pass the same relocation, import, source/raw and production gates. A broad window's synthetic view address never substitutes for a function's existing rowbase. Solved regions use the normal promotion hook before admission. `scripts/recover_bank_anchors.py --kind all --apply` applies that same policy to remaining gaps after the parallel queues finish, including earlier single-window holds; accepted rows are retained and temporary transactions are archived separately. Alternate masked hits without independent entry evidence remain holds. No source is admitted by masked similarity alone.
5. Included post-queue recovery: 171 census-anchor rows, 1 alternate-layout rows and 113 static direct-callee rows. Direct-callee seeds are frozen from previously admitted callers; newly recovered callees do not expand the survey. Every recovered row passes the same normal admission gates.

| rank | family / window group | banks | lead gap bytes | new rows | new C bytes | windows MATCH | candidate holds | status |
|---:|---|---:|---:|---:|---:|---:|---:|---|
| 1 | dungeon_1830080 | 1 | 190,260 | 0 | 0 | 0/1 | 13 | HOLD |
| 2 | town_52000 | 1 | 184,678 | 0 | 0 | 0/1 | 1 | HOLD |
| 3 | dungeon_e5d2d0 | 6 | 137,760 | 132 | 71,736 | 6/6 | 36 | MATCH |
| 4 | dungeon_e332e8 | 6 | 137,376 | 162 | 78,376 | 6/6 | 51 | MATCH |
| 5 | dungeon_d61284 | 6 | 136,048 | 73 | 55,948 | 6/6 | 65 | MATCH |
| 6 | dungeon_ce32e0 | 6 | 133,344 | 87 | 54,220 | 6/6 | 53 | MATCH |
| 7 | town_5dc000 | 1 | 132,212 | 0 | 0 | 0/1 | 10 | HOLD |
| 8 | dungeon_197ad48 | 1 | 131,996 | 0 | 0 | 0/1 | 7 | HOLD |
| 9 | dungeon_18d08ec | 1 | 129,452 | 0 | 0 | 0/1 | 7 | HOLD |
| 10 | dungeon_b69244 | 6 | 122,256 | 49 | 32,616 | 6/6 | 29 | MATCH |
| 11 | dungeon_d07540 | 1 | 120,932 | 5 | 2,544 | 1/1 | 34 | MATCH |
| 12 | dungeon_9c5294 | 6 | 118,608 | 68 | 27,104 | 6/6 | 70 | MATCH |
| 13 | dungeon_b0f73c | 7 | 115,376 | 3 | 540 | 1/7 | 30 | PARTIAL |
| 14 | dungeon_12cb24c | 6 | 112,636 | 1 | 672 | 1/6 | 35 | PARTIAL |
| 15 | dungeon_cb9120 | 6 | 112,296 | 37 | 19,412 | 6/6 | 47 | MATCH |
| 16 | dungeon_e87060 | 6 | 112,176 | 55 | 28,304 | 6/6 | 35 | MATCH |
| 17 | ovmovie_0 | 1 | 109,932 | 0 | 0 | 0/1 | 8 | HOLD |
| 18 | dungeon_10af284 | 5 | 108,220 | 0 | 0 | 0/5 | 5 | HOLD |
| 19 | dungeon_187c98c | 1 | 107,692 | 0 | 0 | 0/1 | 6 | HOLD |
| 20 | dungeon_bbd298 | 6 | 104,832 | 57 | 45,360 | 6/6 | 39 | MATCH |
| 21 | dungeon_ddf7d8 | 6 | 104,232 | 43 | 24,172 | 6/6 | 28 | MATCH |
| 22 | dungeon_c65250 | 6 | 102,168 | 25 | 21,244 | 6/6 | 29 | MATCH |
| 23 | dungeon_d91e5c | 5 | 101,760 | 5 | 11,540 | 5/5 | 5 | MATCH |
| 24 | dungeon_a6e000 | 6 | 98,280 | 61 | 32,552 | 6/6 | 47 | MATCH |
| 25 | dungeon_e03054 | 7 | 98,080 | 18 | 17,520 | 7/7 | 8 | MATCH |
| 26 | dungeon_ac1250 | 6 | 93,952 | 24 | 16,944 | 6/6 | 30 | MATCH |
| 27 | dungeon_d372d0 | 6 | 92,688 | 28 | 11,304 | 6/6 | 50 | MATCH |
| 28 | dungeon_a14000 | 7 | 91,064 | 1 | 324 | 1/7 | 9 | PARTIAL |
| 29 | dungeon_fd2000 | 7 | 89,500 | 4 | 588 | 1/7 | 9 | PARTIAL |
| 30 | dungeon_c0b060 | 7 | 89,484 | 4 | 1,660 | 1/7 | 16 | PARTIAL |
| 31 | dungeon_c8f060 | 6 | 87,744 | 12 | 6,504 | 6/6 | 18 | MATCH |
| 32 | dungeon_f83060 | 6 | 85,976 | 44 | 33,872 | 6/6 | 4 | MATCH |
| 33 | dungeon_eff6d8 | 7 | 85,296 | 10 | 5,660 | 5/7 | 18 | PARTIAL |
| 34 | dungeon_edb060 | 6 | 84,632 | 34 | 26,312 | 6/6 | 25 | MATCH |
| 35 | dungeon_1061674 | 4 | 83,648 | 0 | 0 | 0/4 | 4 | HOLD |
| 36 | dungeon_be7060 | 6 | 83,520 | 64 | 33,068 | 6/6 | 45 | MATCH |
| 37 | dungeon_fad270 | 6 | 82,004 | 72 | 10,488 | 6/6 | 90 | MATCH |
| 38 | dungeon_a97054 | 6 | 81,024 | 18 | 11,496 | 6/6 | 30 | MATCH |
| 39 | dungeon_10d3054 | 6 | 79,968 | 49 | 42,136 | 6/6 | 5 | MATCH |
| 40 | town_0 | 1 | 79,176 | 50 | 5,412 | 1/1 | 82 | MATCH |
| 41 | dungeon_b93054 | 6 | 79,024 | 31 | 24,416 | 6/6 | 10 | MATCH |
| 42 | dungeon_9ef054 | 6 | 78,192 | 63 | 42,432 | 6/6 | 22 | MATCH |
| 43 | dungeon_f2f054 | 6 | 76,228 | 32 | 22,020 | 6/6 | 10 | MATCH |
| 44 | dungeon_b3f054 | 6 | 75,864 | 18 | 15,768 | 6/6 | 0 | MATCH |
| 45 | dungeon_99b060 | 6 | 75,224 | 88 | 53,344 | 6/6 | 26 | MATCH |
| 46 | dungeon_c36000 | 7 | 74,364 | 2 | 1,032 | 1/7 | 10 | PARTIAL |
| 47 | dungeon_107f2a4 | 6 | 71,292 | 44 | 35,888 | 6/6 | 17 | MATCH |
| 48 | dungeon_ffb27c | 7 | 70,992 | 10 | 7,956 | 7/7 | 28 | MATCH |
| 49 | dungeon_aeb958 | 6 | 70,936 | 76 | 38,992 | 6/6 | 42 | MATCH |
| 50 | dungeon_1271060 | 7 | 69,012 | 7 | 5,548 | 5/7 | 20 | PARTIAL |
| 51 | dungeon_f59268 | 4 | 64,912 | 29 | 24,596 | 4/4 | 7 | MATCH |
| 52 | town_3eac60 | 1 | 58,512 | 0 | 0 | 0/1 | 73 | HOLD |
| 53 | dungeon_eab2f4 | 5 | 56,524 | 11 | 7,144 | 5/5 | 15 | MATCH |
| 54 | dungeon_a3d258 | 5 | 54,396 | 7 | 6,040 | 5/5 | 14 | MATCH |
| 55 | dungeon_a0000 | 1 | 50,744 | 0 | 0 | 0/1 | 10 | HOLD |
| 56 | dungeon_1025278 | 5 | 47,172 | 3 | 580 | 1/5 | 11 | PARTIAL |
| 57 | dungeon_1055674 | 2 | 41,824 | 17 | 8,088 | 2/2 | 15 | MATCH |
| 58 | dungeon_db5054 | 4 | 39,756 | 29 | 16,328 | 4/4 | 16 | MATCH |
| 59 | dungeon_19c0fc0 | 1 | 36,396 | 0 | 0 | 0/1 | 2 | HOLD |
| 60 | main_25d000 | 1 | 32,544 | 10 | 788 | 1/1 | 80 | MATCH |
| 61 | dungeon_daf23c | 3 | 23,912 | 6 | 3,684 | 3/3 | 9 | MATCH |
| 62 | dungeon_d8b3b8 | 1 | 23,076 | 1 | 2,308 | 1/1 | 0 | MATCH |
| 63 | dungeon_10a9060 | 1 | 22,192 | 0 | 0 | 0/1 | 1 | HOLD |
| 64 | main_217fc | 1 | 18,664 | 0 | 0 | 0/1 | 3 | HOLD |
| 65 | dungeon_eb72f4 | 1 | 17,300 | 1 | 1,936 | 1/1 | 1 | MATCH |
| 66 | dungeon_ec92f4 | 1 | 17,300 | 1 | 1,936 | 1/1 | 1 | MATCH |
| 67 | dungeon_51ebf4 | 1 | 17,268 | 0 | 0 | 0/1 | 1 | HOLD |
| 68 | dungeon_f6b268 | 1 | 16,228 | 0 | 0 | 0/1 | 1 | HOLD |
| 69 | dungeon_1031278 | 1 | 15,768 | 1 | 2,476 | 1/1 | 1 | MATCH |
| 70 | dungeon_1043278 | 1 | 15,768 | 1 | 2,476 | 1/1 | 1 | MATCH |
| 71 | dungeon_a49258 | 1 | 15,752 | 0 | 0 | 0/1 | 1 | HOLD |
| 72 | dungeon_a5b258 | 1 | 15,752 | 0 | 0 | 0/1 | 1 | HOLD |
| 73 | dungeon_525000 | 1 | 11,652 | 4 | 2,508 | 1/1 | 1 | MATCH |
| 74 | dungeon_f65268 | 1 | 11,608 | 2 | 2,284 | 1/1 | 1 | MATCH |
| 75 | dungeon_12c6000 | 1 | 11,216 | 2 | 1,164 | 1/1 | 3 | MATCH |
| 76 | dungeon_b39228 | 1 | 9,548 | 1 | 100 | 1/1 | 2 | MATCH |
| 77 | dungeon_c89880 | 1 | 9,356 | 1 | 100 | 1/1 | 2 | MATCH |
| 78 | dungeon_f7d23c | 1 | 9,148 | 3 | 1,324 | 1/1 | 2 | MATCH |
| 79 | dungeon_cb3060 | 1 | 8,716 | 2 | 400 | 1/1 | 5 | MATCH |
| 80 | dungeon_f2928c | 1 | 8,608 | 1 | 56 | 1/1 | 3 | MATCH |
| 81 | dungeon_b63060 | 1 | 8,544 | 5 | 2,252 | 1/1 | 4 | MATCH |
| 82 | dungeon_cdd2e0 | 1 | 8,148 | 6 | 3,732 | 1/1 | 4 | MATCH |
| 83 | dungeon_d32000 | 1 | 8,068 | 2 | 552 | 1/1 | 2 | MATCH |
| 84 | dungeon_f53268 | 1 | 7,980 | 2 | 864 | 1/1 | 3 | MATCH |
| 85 | dungeon_c5f060 | 1 | 7,804 | 1 | 56 | 1/1 | 1 | MATCH |
| 86 | dungeon_b8d230 | 1 | 7,392 | 2 | 1,168 | 1/1 | 2 | MATCH |
| 87 | dungeon_dd97d8 | 1 | 7,196 | 3 | 1,856 | 1/1 | 4 | MATCH |
| 88 | dungeon_e812fc | 1 | 6,964 | 3 | 608 | 1/1 | 3 | MATCH |
| 89 | dungeon_104f674 | 1 | 6,292 | 3 | 808 | 1/1 | 2 | MATCH |
| 90 | dungeon_abb060 | 1 | 5,980 | 2 | 1,124 | 1/1 | 2 | MATCH |
| 91 | dungeon_10cd228 | 1 | 5,836 | 3 | 608 | 1/1 | 2 | MATCH |
| 92 | dungeon_a91228 | 1 | 5,800 | 4 | 1,676 | 1/1 | 2 | MATCH |
| 93 | dungeon_10792a4 | 1 | 5,680 | 3 | 980 | 1/1 | 4 | MATCH |
| 94 | dungeon_ed5364 | 1 | 5,548 | 2 | 112 | 1/1 | 2 | MATCH |
| 95 | main_20000 | 1 | 3,956 | 0 | 0 | 0/1 | 2 | HOLD |
| 96 | dungeon_d89000 | 1 | 3,932 | 2 | 1,164 | 1/1 | 1 | MATCH |
| 97 | dungeon_a68000 | 1 | 3,800 | 1 | 324 | 1/1 | 1 | MATCH |
| 98 | dungeon_bb9000 | 1 | 3,380 | 2 | 356 | 1/1 | 2 | MATCH |
| 99 | dungeon_e572d0 | 1 | 3,380 | 3 | 676 | 1/1 | 2 | MATCH |
| 100 | dungeon_abe000 | 1 | 3,344 | 1 | 300 | 1/1 | 1 | MATCH |
| 101 | dungeon_ae6000 | 1 | 3,340 | 0 | 0 | 0/1 | 3 | HOLD |
| 102 | dungeon_18b2000 | 1 | 3,320 | 0 | 0 | 0/1 | 2 | HOLD |
| 103 | dungeon_10a5000 | 1 | 3,292 | 1 | 100 | 1/1 | 3 | MATCH |
| 104 | town_4cf000 | 1 | 3,220 | 0 | 0 | 0/1 | 4 | HOLD |
| 105 | dungeon_9c1000 | 1 | 3,176 | 3 | 256 | 1/1 | 2 | MATCH |
| 106 | dungeon_be19d0 | 1 | 3,112 | 4 | 612 | 1/1 | 1 | MATCH |
| 107 | town_8d3000 | 1 | 2,900 | 1 | 164 | 1/1 | 2 | MATCH |
| 108 | dungeon_c62000 | 1 | 2,760 | 1 | 300 | 1/1 | 1 | MATCH |
| 109 | dungeon_1274000 | 1 | 2,628 | 0 | 0 | 0/1 | 4 | HOLD |
| 110 | dungeon_1349000 | 1 | 2,624 | 5 | 256 | 1/1 | 3 | MATCH |
| 111 | town_2abfe8 | 1 | 2,560 | 7 | 680 | 1/1 | 14 | MATCH |
| 112 | dungeon_f03000 | 1 | 2,532 | 0 | 0 | 0/1 | 2 | HOLD |
| 113 | dungeon_e2e000 | 1 | 2,496 | 0 | 0 | 0/1 | 1 | HOLD |
| 114 | dungeon_bb8000 | 1 | 2,368 | 2 | 680 | 1/1 | 0 | MATCH |
| 115 | dungeon_9c0000 | 1 | 2,352 | 0 | 0 | 0/1 | 2 | HOLD |
| 116 | dungeon_d5d000 | 1 | 2,256 | 2 | 824 | 1/1 | 2 | MATCH |
| 117 | dungeon_9ea000 | 1 | 2,244 | 2 | 424 | 1/1 | 1 | MATCH |
| 118 | town_2ab000 | 1 | 2,244 | 0 | 0 | 0/1 | 4 | HOLD |
| 119 | dungeon_18ad004 | 1 | 2,204 | 1 | 268 | 1/1 | 1 | MATCH |
| 120 | town_617000 | 1 | 2,200 | 0 | 0 | 0/1 | 5 | HOLD |
| 121 | dungeon_182e000 | 1 | 2,172 | 0 | 0 | 0/1 | 2 | HOLD |
| 122 | dungeon_10a4000 | 1 | 2,152 | 0 | 0 | 0/1 | 2 | HOLD |
| 123 | dungeon_d87000 | 1 | 2,128 | 2 | 424 | 1/1 | 1 | MATCH |
| 124 | dungeon_18c4000 | 1 | 2,092 | 0 | 0 | 0/1 | 2 | HOLD |
| 125 | dungeon_1882000 | 1 | 2,048 | 0 | 0 | 0/1 | 1 | HOLD |
| 126 | dungeon_18d6000 | 1 | 2,048 | 0 | 0 | 0/1 | 1 | HOLD |
| 127 | dungeon_e06000 | 1 | 1,796 | 1 | 100 | 1/1 | 2 | MATCH |
| 128 | dungeon_134c000 | 1 | 1,752 | 1 | 156 | 1/1 | 1 | MATCH |
| 129 | town_49f000 | 1 | 1,680 | 1 | 72 | 1/1 | 6 | MATCH |
| 130 | dungeon_d8a000 | 1 | 1,540 | 0 | 0 | 0/1 | 2 | HOLD |
| 131 | dungeon_ae7000 | 1 | 1,536 | 3 | 356 | 1/1 | 1 | MATCH |
| 132 | dungeon_1348000 | 1 | 1,532 | 1 | 136 | 1/1 | 3 | MATCH |
| 133 | dungeon_1357000 | 1 | 1,512 | 2 | 216 | 1/1 | 2 | MATCH |
| 134 | dungeon_d88000 | 1 | 1,500 | 1 | 724 | 1/1 | 1 | MATCH |
| 135 | dungeon_a40000 | 1 | 1,492 | 2 | 112 | 1/1 | 1 | MATCH |
| 136 | town_794000 | 1 | 1,484 | 0 | 0 | 0/1 | 6 | HOLD |
| 137 | dungeon_1346004 | 1 | 1,416 | 2 | 256 | 1/1 | 1 | MATCH |
| 138 | town_3e8000 | 1 | 1,360 | 4 | 388 | 1/1 | 8 | MATCH |
| 139 | dungeon_e2f004 | 1 | 1,296 | 2 | 256 | 1/1 | 2 | MATCH |
| 140 | town_654000 | 1 | 1,288 | 0 | 0 | 0/1 | 7 | HOLD |
| 141 | dungeon_9eb004 | 1 | 1,276 | 2 | 256 | 1/1 | 1 | MATCH |
| 142 | dungeon_c63000 | 1 | 1,236 | 0 | 0 | 0/1 | 1 | HOLD |
| 143 | town_553000 | 1 | 1,184 | 0 | 0 | 0/1 | 9 | HOLD |
| 144 | town_438000 | 1 | 1,160 | 1 | 36 | 1/1 | 7 | MATCH |
| 145 | dungeon_a16000 | 1 | 1,136 | 3 | 312 | 1/1 | 0 | MATCH |
| 146 | dungeon_190d25c | 1 | 1,084 | 0 | 0 | 0/1 | 2 | HOLD |
| 147 | dungeon_fd7000 | 1 | 1,068 | 0 | 0 | 0/1 | 1 | HOLD |
| 148 | dungeon_fe3000 | 1 | 1,068 | 0 | 0 | 0/1 | 1 | HOLD |
| 149 | dungeon_fe9000 | 1 | 1,068 | 0 | 0 | 0/1 | 1 | HOLD |
| 150 | dungeon_ff5000 | 1 | 1,068 | 0 | 0 | 0/1 | 1 | HOLD |
| 151 | dungeon_a69000 | 1 | 1,064 | 2 | 256 | 1/1 | 1 | MATCH |
| 152 | dungeon_e5b000 | 1 | 996 | 0 | 0 | 0/1 | 2 | HOLD |
| 153 | town_2ac000 | 1 | 972 | 0 | 0 | 0/1 | 8 | HOLD |
| 154 | dungeon_abf000 | 1 | 956 | 0 | 0 | 0/1 | 1 | HOLD |
| 155 | dungeon_d60000 | 1 | 936 | 0 | 0 | 0/1 | 1 | HOLD |
| 156 | dungeon_bb769c | 1 | 932 | 0 | 0 | 0/1 | 0 | HOLD |
| 157 | dungeon_1356000 | 1 | 912 | 2 | 156 | 1/1 | 1 | MATCH |
| 158 | dungeon_1354004 | 1 | 892 | 2 | 172 | 1/1 | 1 | MATCH |
| 159 | dungeon_191e9b0 | 1 | 796 | 0 | 0 | 0/1 | 1 | HOLD |
| 160 | dungeon_134dbc4 | 1 | 780 | 0 | 0 | 0/1 | 1 | HOLD |
| 161 | dungeon_4dae0 | 1 | 708 | 0 | 0 | 0/1 | 5 | HOLD |
| 162 | dungeon_e5a000 | 1 | 688 | 2 | 156 | 1/1 | 1 | MATCH |
| 163 | dungeon_134f000 | 1 | 644 | 1 | 108 | 1/1 | 4 | MATCH |
| 164 | dungeon_1343128 | 1 | 640 | 2 | 348 | 1/1 | 1 | MATCH |
| 165 | dungeon_1357e4c | 1 | 624 | 2 | 396 | 1/1 | 0 | MATCH |
| 166 | dungeon_997000 | 1 | 600 | 4 | 288 | 1/1 | 0 | MATCH |
| 167 | town_83b2b8 | 1 | 596 | 0 | 0 | 0/1 | 2 | HOLD |
| 168 | dungeon_1345000 | 1 | 564 | 1 | 56 | 1/1 | 1 | MATCH |
| 169 | dungeon_129b060 | 7 | 560 | 0 | 0 | 0/7 | 7 | HOLD |
| 170 | dungeon_1e0fc | 1 | 556 | 0 | 0 | 0/1 | 2 | HOLD |
| 171 | dungeon_1359000 | 1 | 548 | 1 | 36 | 1/1 | 1 | MATCH |
| 172 | town_801478 | 1 | 484 | 0 | 0 | 0/1 | 1 | HOLD |
| 173 | dungeon_1907000 | 1 | 476 | 0 | 0 | 0/1 | 1 | HOLD |
| 174 | town_552928 | 1 | 452 | 1 | 76 | 1/1 | 1 | MATCH |
| 175 | town_594ac8 | 1 | 448 | 0 | 0 | 0/1 | 2 | HOLD |
| 176 | dungeon_a6b000 | 1 | 416 | 1 | 172 | 1/1 | 2 | MATCH |
| 177 | dungeon_fa9d7c | 1 | 376 | 0 | 0 | 0/1 | 1 | HOLD |
| 178 | dungeon_d86000 | 1 | 356 | 0 | 0 | 0/1 | 1 | HOLD |
| 179 | dungeon_d5d588 | 1 | 324 | 1 | 324 | 1/1 | 0 | MATCH |
| 180 | dungeon_135c000 | 1 | 320 | 0 | 0 | 0/1 | 1 | HOLD |
| 181 | town_2af000 | 1 | 284 | 1 | 84 | 1/1 | 3 | MATCH |
| 182 | dungeon_d5f268 | 1 | 268 | 1 | 100 | 1/1 | 0 | MATCH |
| 183 | dungeon_182f000 | 1 | 244 | 0 | 0 | 0/1 | 1 | HOLD |
| 184 | dungeon_13464c8 | 1 | 196 | 0 | 0 | 0/1 | 1 | HOLD |
| 185 | town_645244 | 1 | 152 | 1 | 40 | 1/1 | 0 | MATCH |
| 186 | dungeon_e32a58 | 1 | 140 | 0 | 0 | 0/1 | 1 | HOLD |
| 187 | dungeon_1913098 | 1 | 132 | 0 | 0 | 0/1 | 2 | HOLD |
| 188 | dungeon_8eb154 | 1 | 128 | 0 | 0 | 0/1 | 1 | HOLD |
| 189 | town_49eda4 | 1 | 120 | 0 | 0 | 0/1 | 1 | HOLD |
| 190 | dungeon_16ae8 | 1 | 108 | 0 | 0 | 0/1 | 2 | HOLD |
| 191 | dungeon_134e4f0 | 1 | 108 | 1 | 108 | 1/1 | 0 | MATCH |
| 192 | dungeon_186a930 | 1 | 108 | 1 | 108 | 1/1 | 0 | MATCH |
| 193 | town_4002bc | 1 | 96 | 0 | 0 | 0/1 | 1 | HOLD |
| 194 | dungeon_10a3060 | 1 | 92 | 0 | 0 | 0/1 | 1 | HOLD |
| 195 | dungeon_d074ec | 1 | 84 | 0 | 0 | 0/1 | 1 | HOLD |
| 196 | dungeon_1942998 | 1 | 84 | 0 | 0 | 0/1 | 1 | HOLD |
| 197 | dungeon_19c0d64 | 1 | 84 | 0 | 0 | 0/1 | 1 | HOLD |
| 198 | town_49ea54 | 1 | 84 | 0 | 0 | 0/1 | 1 | HOLD |
| 199 | town_7f8360 | 1 | 80 | 0 | 0 | 0/1 | 2 | HOLD |
| 200 | town_595268 | 1 | 76 | 0 | 0 | 0/1 | 1 | HOLD |
| 201 | town_2714dc | 1 | 64 | 0 | 0 | 0/1 | 1 | HOLD |
| 202 | dungeon_9411bc | 1 | 60 | 1 | 52 | 1/1 | 1 | MATCH |
| 203 | dungeon_d54c | 1 | 52 | 0 | 0 | 0/1 | 2 | HOLD |
| 204 | dungeon_135a3f0 | 1 | 36 | 1 | 36 | 1/1 | 0 | MATCH |
| 205 | dungeon_10a5c6c | 1 | 8 | 0 | 0 | 0/1 | 1 | HOLD |

Windows may contain retained raw segments. New C totals count only admitted complete bodies. `next.tsv` retains failed-attempt history: `SUPERSEDED_ROW_HOLD` entries now have an identical delivered extent, and `SUPERSEDED_ATTEMPT` marks an older failed attempt in a now-MATCH bank. Continue with the active `ROW_HOLD` and `BANK_HOLD` records. The table counts active candidate holds.

Every admitted source is ordinary C from an existing matched body, renamed using retail address pairs. Every differing word is a j/jal field or a reaching lui/lo16 pair. An independent audit binds every changed word to a R_MIPS_26, R_MIPS_HI16 or R_MIPS_LO16 relocation in the production compiler object. The source audit refuses pins, asm and volatile. Relocation masking is used only for candidate discovery; all final production gates compare complete bytes without masking. Existing rowbase extents and deltas are unchanged; solved regions are upgraded only by the normal `rowbase.py promote` hook. No compiler, flags registry, header, gate or runtime contract is changed. Existing indirect-call declarations and expressions are inherited from the matched source; no dynamic target is asserted.

Direct import records bind each admitted call to a matched definition or a complete retail callee twin. Prototype-only callee proofs do not contribute to delivered totals. A finite one-hop recovery can admit those static callees only after independently checking their caller, existing rowbase, complete gap extent and ABI agreement, followed by every normal source/raw/window gate. Alternate donor layouts require two independent complete anchors or a strict complete-window relocation proof. Missing C bodies, including SDK assembly-only callees, remain explicit row holds. A byte match proves static placement, without asserting runtime reachability.

`delivery_twins2/` contains src/raw pairs, append-only split/registry/baseline/promotion/reverify transactions, changed rowbase records and physical graph, source and raw scores, relocation/import evidence, window receipts, first-pass commands and m2c revision, guards and full before-images. Raw is actual generated output, never copied matched C. Baselines record measured raw outcomes, including build failures. `records/levels_seed_needed.tsv` lists every new row that still needs an integrator ledger/levels.jsonl seed; that ledger is not silently populated. Coverage events are provided for integration.

## HOW TO CONTINUE

1. At this exact base, run `python3 delivery_twins2/apply.py --root R --live --dry-run`, then `--live`. An immediate second dry-run must print `"files": []`. Dry-run wins when both flags are supplied. Symlink or byte drift refuses before writes; a failed apply rolls back.
2. In R, run registry, row-db check and graph generation. Run every production window listed in `manifest.json` from build_ovl with the normal `overlay_local_gate.py --clean` command. Seed the listed levels rows under the integration policy, then reconcile supplied coverage events.
3. For remaining PENDING groups, run `nice -n 15 python3 scripts/parallel.py --jobs 6` for bank families or add `--kind single-window --refresh` for the single-window phase. One family can use `nice -n 15 python3 scripts/twins.py run FAMILY`. If the table has no PENDING groups, all current ranked groups have checkpoints; continue with the specific proof holds in `next.tsv` and archived anchor transactions. Completed results are resume checkpoints, including failed attempts. The parallel runner packages every four families. Do not start a second runner against the same mutable trees.
4. Use `next.tsv` and per-family evidence for holds. Resolve body-backed import contracts, non-relocation words, existing split ownership or raw switch-table context before reconsidering a held row. For generic windows, prove complete entries and placement before generating source. Do not change gates or add pins to force admission.
5. If any other package lands first, rebuild against the combined tree and rerun proofs, registry, row-db, graph and all affected production windows before regenerating guards. Do not bypass hashes.
6. To resume interrupted post-queue recovery, first finish `scripts/recover_bank_anchors.py --kind all --apply` with no other runner active. `scripts/recover_short_aspsx.py` retries the known ASPSX path holds using a physically short scratch directory inside the lane; gate code, inputs and flags remain unchanged. Then run `scripts/recover_extra_plans.py --dry-run` and `--apply`; default resume retains frozen one-hop seeds, so do not use `--refresh` during an active recovery. After all source mutations finish, run `scripts/final_shared_windows.py` and `scripts/package.py`. Completed transactions are cached. These recovery commands are for the original lane, not the integration target.
