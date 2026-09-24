# Web search: a compiler from the 1997-04-12 .. 1997-07-11 window

Search only (2026-09-24). Nothing was downloaded or cloned, and nothing was built. The sources were web
searches, GitHub/archive.org/redump metadata APIs, HEAD requests, and Wayback captures of snsys.com (text only).
Context: `docs/evidence/fidelity_step1b_epilogue.md` and `fidelity_step1c_compiler_inventory.md`. The window is
bounded below by the cygnus-2.7.2-970404 tree, whose newest ChangeLog entry is 1997-04-12, and above by Law's
2.7.2-epilogue deletion. That deletion is gcc-mirror commit `1f2d8f510f4e516803427373e1625991756d4d91`
(r14412, 1997-07-11): mips.c -269 lines, mips.h -16, mips.md +31/-37. Its parent is
`7a49a4fd7b45ce1c15859f6bd4ee46418310d8f1` (r14410, 1997-07-10), the last trunk state that still has the text
epilogue.

## Ranked leads

| # | lead | URL | date / version evidence | size | likelihood it is (or yields) the window compiler | cost |
|---|---|---|---|---|---|---|
| 1 | **FSF gcc2 trunk snapshots in the window, via gcc-mirror codeload tarballs** | `https://codeload.github.com/gcc-mirror/gcc/tar.gz/<sha>` (HEAD on `7a49a4fd…` returns 200, `application/x-gzip`) | 473 commits from 1997-04-04 to 07-11 (r13838-r14412); anchors below. This is the same route that produced the held 970802/970821/971023/971101 tarballs (7.6-10 MB each) | about 8 MB per snapshot. A full clone is about 4.2 GB (GitHub `size` 4,169,206 KB): do not clone | **Medium.** It is the only window source that is certainly obtainable. It is FSF trunk, not Cygnus's devo tree, so it approximates what SN received and does not reproduce it. The 970802 trunk already equals SN 2.8.0 on 181/193 rows, which means trunk codegen tracks SN's closely | 14 weekly anchors: about 120 MB download, plus about 15 builds with the old `build_one.sh` (5 host patches and psx registration). Pre-August trees may need the same host fixes. The 971101 build stopped at `rtl.o` |
| 2 | **SN N64 compiler, build 0006, "cygnus"** (and 0004) | asset `n64_sn272_build0006cygnus.tar.gz` (also named `n64_sn272_0006.tar.gz`) on `https://github.com/decompme/compilers/releases/tag/compilers`; PR `https://github.com/decompme/decomp.me/pull/1489` ("The cygnus builds (0004/6)"); 0004 = `https://github.com/Mr-Wiseguy/pcsx-redux/releases/download/n64/cc1n64.exe` | SN numbers its builds in one series `2.7.2.SN32.3.7.000N` across PSX and N64. N64 0001 was built 1997-02-19. PSX 0002 is on JP 4.0 (disc 1997-05-28). PSX 0004 = cygnus-970404, on JP 4.1 (disc 1997-09-25) and EN 4.1 (Dec 1997). **N64 0006 is the only surviving SN build later than 0004 from the pre-2.8.0 line.** Its version string is not published anywhere I could find | 1.67 MB | **Low to medium, and decisive.** If it prints `cygnus-2.7.2-97MMDD` with MMDD after 0404, that is the snapshot date SN tracked, and lead 1's bisect should aim there. If it still prints `970404`, SN never moved its Cygnus base before 2.8.0, and the 131 rows point at SN-side patches on 970404 rather than a newer FSF snapshot. decompals' SN64-gcc recreation is tagged `gcc-2.7.2-970404` (`https://github.com/decompals/SN64-gcc/releases`), which weakly suggests 970404 persisted | Download 1.67 MB, then `strings cc1n64.exe \| grep -i cygnus`. Optional experiment, not a claim: run it under wibo with `-mips1 -mcpu=3000 -mel -G0` and diff 0004 against 0006 on the 131 rows' sources. That tells whether SN changed target-independent codegen between builds |
| 3 | **US Run-time Library 4.0 "Release 2.0", DTL-S2002** | `https://archive.org/download/ps1_sdks/Programmer%20Tools%20-%20Run-time%20Library%204.0%20(USA)%20(Release%202.0)_DTL-S2002_redump.zip`; redump `http://redump.org/disc/71991/` | PVD 1997-06-20 12:18, inside the window. We hold JP 4.0 (DTL-S2320, PVD 1997-05-28, `2.7.2.SN32.3.7.0002`, per mkst's notes `https://github.com/mkst/esa/releases/tag/psyq-binaries`) and EN 4.1 "Release 2.1 Dec 1997". This June US mastering is not in the step-1c "checked" list | 391.6 MB | **Low.** It most likely carries 0002 again, or possibly a 0003 | One 392 MB download, then list `GNU/` and `COMPILER/` |
| 4 | SN's BBS/ftp "GNU" area (interim builds and GPL source) | Wayback `http://web.archive.org/web/19970521223357/http://www.snsys.com:80/gnu/default.html`, `.../19970521223507/http://www.snsys.com:80/ftpand.htm`, `.../19970521223307/http://www.snsys.com:80/Targets/playstation2.htm` | May 1997 statements by SN: "we provide the source code for our compiler builds on our BBS … in the 'GNU' area"; "If the latest versions have not yet filtered through to SCE, you can obtain them directly from SN Systems"; ftp `bbs.snsys.com` was account-only. May 1998 (`…/19980523231120/…/snsys/default.asp`): "PSX and N64 versions of the Cygnus Experimental compiler are also available", listed as a separate download from 2.8.0/2.8.1 | n/a | **This is where the real compiler lived.** A Konami studio would have received interim builds this way. No public copy of the BBS was found: Wayback has no ftp captures, and no archive.org item exists | Not obtainable from public sources. It would take a developer-kit hoard or an ex-licensee's backup |
| 5 | Cygnus GNUPro 97r1 (and 97r1a) | EE Times announcement, 1997-07-02: `https://www.eetimes.com/cygnus-solutions-announces-gnupro-toolkit-97r1-release/`; GNUPro docs list mips-idt-ecoff as a fully tested configuration | Version string `2.7-97r1` (97r1a seen on an H8/300 kit). The snapshot is probably from about May-June 1997, so inside the window. This is the Cygnus devo line, the same family as 970404 | unknown | **Medium on lineage, near zero on availability.** It shipped only on customer CD-ROMs, and no public source or MIPS binary was found | Only via a second-hand GNUPro 97r1 CD. Not worth pursuing actively |

### Anchor commits for lead 1 (gcc-mirror/gcc; the last commit of each ISO week, and the calibration points)

| date (UTC) | sha | SVN | note |
|---|---|---|---|
| 1997-04-03 23:08 | 8bb196585a6673cb5f3f82d98f89c21281877584 | r13838 | **calibration**: should resemble cygnus-970404 |
| 1997-04-11 21:14 | 51a96571d69e0bf21d9c5aa6c9e9251f3efe6647 | r13861 | **calibration**: cdk ChangeLog ends 04-12 |
| 1997-04-20 22:07 | 388320a5709b08bbeb07d984ffef01a7ddf30fb7 | r13947 | |
| 1997-04-27 19:40 | b835c5b30e5ef49488d634aebc9ffc40e9590121 | r13986 | |
| 1997-05-03 01:50 | 3f76745e0104f5da78cc456ef85464a8e915e25e | r14014 | after Wilson's 05-01 `-m[no-]split-addresses` change |
| 1997-05-09 20:35 | 6f54921d696748515d8875f6c58cb91118ccf9a1 | r14058 | |
| 1997-05-18 20:51 | eaf95893f87d262bbb8ef64272aa3ca56f3f0e33 | r14097 | |
| 1997-05-24 22:06 | 8efc7e64cfc243cde455ecdd4bd955b35e1a28e3 | r14114 | |
| 1997-05-30 18:19 | b1f21e0aef20c7b08785b13d33611370151e1c2b | r14140 | |
| 1997-06-08 21:23 | d75292760db1d1590f6bb03721e7888d0d82cc31 | r14173 | (already listed in `hunt_cygnus97/_mail`) |
| 1997-06-14 18:46 | babae559e20a35de8621284fa6e0712eb47383be | r14247 | |
| 1997-06-22 19:11 | 5a060962811963d7d56f18099ff65596754d807a | r14288 | after Wilson's 06-16/06-20/06-21 mips prologue and block-move changes |
| 1997-06-29 16:13 | 38c1f2d7e6de970a7345b7d7fabe3952f2f7af89 | r14361 | |
| 1997-07-06 22:30 | 114d6a82f062e6bd531afa4e8a7f943538160b67 | r14393 | |
| 1997-07-10 | 7a49a4fd7b45ce1c15859f6bd4ee46418310d8f1 | r14410 | **last text-epilogue trunk state** |

MIPS-backend commits inside the window, from the GitHub API with `path=gcc/config/mips`, are the natural bisect
markers:

- 04-21 Wilson, `TARGET_LIBGCC2_CFLAGS`.
- 04-30 Wilson, paradoxical_extend patterns.
- **05-01 Wilson, `MASK_SPLIT_ADDR` / `TARGET_SPLIT_ADDRESSES` / `-mno-split-addresses`** (`5ef37cd33952`,
  `8acd7d300281`). cdk and PsyQ 4.0/4.1 reject this flag, and 6 of our rows use it. That fits a window compiler
  from after 05-01, but only if the flag on those rows is historical rather than an artefact of the cell.
- 05-12 Law, `move_operand`.
- 06-16 and 06-21 Wilson, `mips_expand_prologue`.
- 06-20 Wilson, `output_block_move`.
- 06-24 Wilson, `movdi_internal` x/J.
- 07-01 Evans, `mips_output_external` .extern handling.
- 07-11 Law, the epilogue change.

The version marker is `toplev.c` `version_string`, because `version.c` does not exist before 1997-08.

## Closed or negative

- **"Psy-Q 4.2".** The archive.org item "Play Station Programmer Tool Runtime Library Version 4.2"
  (`https://archive.org/details/play-station-programmer-tool-runtime-library-version-4.2.7z`) is 397 KB and holds
  libraries only. Redump lists no 4.2 disc. Its Runtime Library series is 2.0, 2.6, 3.0, 3.3, 3.5, 3.6, 4.0,
  4.1, 4.3, 4.4 and 4.6 (`http://redump.org/discs/quicksearch/Runtime/`).
- **The JP 4.0 and JP 4.1 discs are already covered.** mkst lists JP 4.0 DTL-S2320 = `2.7.2.SN32.3.7.0002` +
  ASPSX 2.56, and JP 4.1 DTL-S2330 = `cygnus-2.7.2-970404 SN32.3.7.0004` + ASPSX 2.67. Both binaries are the ones
  we hold. The redump mastering dates are JP 4.0 1997-05-28, JP 4.1 1997-09-25, JP 4.3 1998-05-22 and JP 4.4
  1998-10-12. The JP 4.1 disc is the one a Konami JP team would have had for a November 1997 release, and it
  carries 970404.
- **gcc.gnu.org old-releases** (`https://gcc.gnu.org/pub/gcc/old-releases/gcc-2/`) has nothing between 2.7.2.3
  (1997-08-20, 2.7.2 branch) and 2.8.0 (1998-01-14). FSF trunk snapshots were never published; before egcs, only
  git history survives.
- **Other archives hold nothing from the window.**
  - The decompals old-gcc releases (`https://github.com/decompals/old-gcc/releases`) have cygnus-2.7.2-970404 as
    their only Cygnus snapshot.
  - The decompme/compilers values.yaml has no PS1 compiler between psyq4.1 (970404) and psyq4.3.
  - Cygwin b18 is also 970404.
  - SN64 build 0001 (1997-02-19) is FSF 2.7.2.
  - SN64 2.8.1 (ProDG N64 1.0.0.2) is post-window.
- **psx.arthus.net** (`https://psx.arthus.net/sdk/Psy-Q/`) and archive.org `ps1_sdks` (7.8 GB) hold no disc
  from the window that we do not have, apart from lead 3 above.

## Community statements (item 3)

No public statement names a "missing" SN compiler with 2.8-era code and 2.7.2 epilogues, or says which compiler
Konami used in 1997. The closest are:

- **Wyrelade/GCC-Enhanced** (`https://github.com/Wyrelade/GCC-Enhanced`, from Digimon World 2). It lists "FILL vs
  UNFILL epilogues" among the residual divergences of GCC 2.8.1 from retail, and says "retail was built with a
  specific, often unarchived, GCC 2.x build … none reproduce a private patched build". It handles this with
  rewrite passes and does not identify a compiler.
- **Legend of Mana decomp** (`https://github.com/celophi/lom-decomp`). It mixes gcc 2.8.0-psx, 2.7.2-cdk and
  2.6.0 per file, which shows that per-TU compiler mixtures are common.
- **Other Konami projects.**
  - sotn-decomp (Konami, March 1997) uses a gcc 2.6.3-based `cc1-psx-26` (a different team and era).
  - Vandal Hearts' PC port references PsyQ 3.3's ASPSX 2.21.
  - MGS and Silent Hill say nothing about the compiler.

## Recommendation

1. **First, and cheapest: identify SN N64 build 0006.** This is a 1.67 MB download and one `strings` call, and it
   needs owner approval because it is a download. Its Cygnus date decides between two paths: (a) a newer Cygnus or
   FSF base, which means bisecting trunk near that date, or (b) SN-patched 970404, which means the 131 rows
   come from SN changes and not from a newer snapshot. Where possible, also diff 0004 against 0006 codegen on the
   131 rows' sources.
2. **Then, the only certain route: build FSF trunk snapshots through codeload.** Start with the two calibration
   points (r13838 and r13861). If trunk at 04-11 matches cdk on the 424 cdk-exact rows, trunk is a faithful proxy
   and the weekly anchors can be trusted. Next build r14410 (07-10). If it reproduces a large share of the 131
   helper rows natively (text epilogue with the newer code), bisect backwards through the weekly anchors to the
   earliest snapshot that does. Budget: about 120 MB download and about 15 builds.
3. **Optional and low yield:** the US 4.0 Release 2.0 disc (392 MB) could hold a 0003 build.
4. Do not chase GNUPro 97r1 or the SN BBS. Neither has a public copy.

Expectation: a trunk snapshot close to 07-10 is the best available stand-in. A byte-exact "genuine" window
compiler is unlikely to be found in public archives, because SN distributed interim builds through an
account-only BBS.
