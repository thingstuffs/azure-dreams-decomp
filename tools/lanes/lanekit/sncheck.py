#!/usr/bin/env python3
"""Compare our cc1 with the genuine SN compiler on the kit's SAME preprocessed input.

sncheck.py ROW {candidate.c,erased,pinned} [--cfg CFG] [--json FILE] [--keep DIR]
IDENTICAL is assembly identity after CRLF, comments and whitespace normalisation,
inside .ent/.end functions. Instructions, labels and semantic directives are kept.
It is neither a retail byte score nor permission to change a row's recipe.
"""
from __future__ import annotations
import argparse
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import kitlib

# Verified from the version strings in the genuine PE binaries (see README).
GENERATIONS = {'2.7.2-cdk': ('4.1', 'cygnus-2.7.2-970404 SN32.3.7.0004'),
               '2.8.0': ('4.4', '2.8.1 SN32 BUILD 4.0.0010'),
               '2.8.1': ('4.4', '2.8.1 SN32 BUILD 4.0.0010'),
               '2.95.2': ('4.6', '2.95.2 19991024 BUILD 4.0.0030')}

def generation(cell):
    if cell not in GENERATIONS:
        raise ValueError('no verified SN generation for '+cell)
    return GENERATIONS[cell]

def normalize(src):
    """Keep function bodies, including .set/.mask/etc; no register/label rewriting."""
    out=[]; inside=False
    for line in src.splitlines():
        # GCC assembly strings can contain '#': strip only comments outside quotes.
        quoted=False; escaped=False; kept=[]
        for c in line:
            if c=='#' and not quoted: break
            kept.append(c)
            if escaped: escaped=False
            elif c=='\\' and quoted: escaped=True
            elif c=='"': quoted=not quoted
        s=''.join(kept).strip()
        if re.match(r'\.ent\s',s): inside=True
        if inside and s:
            # Compress formatting whitespace outside quoted assembly strings.
            pieces=re.split(r'("(?:\\.|[^"\\])*")',s)
            out.append(''.join(p if i%2 else re.sub(r'\s+',' ',p) for i,p in enumerate(pieces)))
        if re.match(r'\.end\s',s): inside=False
    return out

def input_text(spec, row, lane):
    base=kitlib.base_text(row,lane)
    return base if spec=='pinned' else kitlib.erased_text(base) if spec=='erased' else Path(spec).read_text()

def preprocess(row, text, directory, timeout=60):
    """Exactly screen.compile_s's cpp recipe, reused by the allocator oracle."""
    kitlib.add_paths()
    from common import parse_cfg
    cell,flags=parse_cfg(row['cfg']); cc=kitlib.ROOT/'toolchain/compilers'/('gcc-'+cell)
    d=Path(directory); (d/'f.c').write_text(text)
    cmd=[str(cc/'gcc'),'-B'+str(cc)+'/', '-E','-O2',*flags,'-I'+str(kitlib.ROOT/'include'),'-w','f.c','-o','in.i']
    run=subprocess.run(cmd,cwd=d,capture_output=True,text=True,timeout=timeout)
    if run.returncode: raise RuntimeError('cpp failed: '+(run.stderr or run.stdout)[-2000:])
    return cc,flags,cmd

def check(row, text, timeout=120, keep=None):
    kitlib.add_paths()
    from common import parse_cfg
    cell,_=parse_cfg(row['cfg']); psyq,version=generation(cell)
    sn=kitlib.ROOT/'toolchain/genuine/psyq'/('psyq'+psyq)/'CC1PSX.EXE'
    wibo=kitlib.ROOT/'toolchain/genuine/bin/wibo'
    for p in (sn,wibo):
        if not p.is_file(): raise RuntimeError('missing tool: '+str(p))
    # Check the binary itself, without depending on a journal or provenance label.
    if version.encode() not in sn.read_bytes(): raise RuntimeError('SN version string differs from verified mapping')
    with tempfile.TemporaryDirectory(prefix='sncheck_') as td:
        d=Path(td); cc,flags,cpp=preprocess(row,text,d,timeout)
        common=['in.i','-quiet','-O2',*flags,'-w']
        commands=[cpp,[str(cc/'cc1'),*common,'-o','ours.s'],[str(wibo),str(sn),*common,'-o','sn.s']]
        env=dict(os.environ,TMPDIR=str(d),TMP=str(d),TEMP=str(d))
        for cmd in commands[1:]:
            p=subprocess.run(cmd,cwd=d,env=env,capture_output=True,text=True,errors='replace',timeout=timeout)
            output=d/cmd[-1]
            if p.returncode or not output.is_file():
                raise RuntimeError('cc1 failed: '+(p.stderr+p.stdout)[-2000:])
        a=normalize((d/'ours.s').read_text()); b=normalize((d/'sn.s').read_text())
        if not a or not b: raise RuntimeError('cc1 emitted no .ent/.end function bodies')
        diff=list(difflib.unified_diff(a,b,fromfile='our cc1',tofile='genuine SN cc1',lineterm=''))
        rec={'row':row['id'],'cfg':row['cfg'],'cell':cell,'psyq':psyq,'sn_version':version,
             'sn_sha256':hashlib.sha256(sn.read_bytes()).hexdigest(),
             'input_sha256':hashlib.sha256((d/'in.i').read_bytes()).hexdigest(),
             'identical':a==b,'differing_lines':sum(l[:1] in ('+','-') and not l.startswith(('+++','---')) for l in diff),
             'diff':diff,'commands':commands}
        if keep:
            target=Path(keep).resolve(); lane=kitlib.lane_dir()
            if not target.is_relative_to(lane): raise ValueError('--keep must be inside this lane')
            target.mkdir(parents=True,exist_ok=True)
            for f in d.iterdir():
                if f.is_file(): shutil.copy2(f,target/f.name)
            (target/'result.json').write_text(json.dumps(rec,indent=2)+'\n')
        return rec

def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__); ap.add_argument('row'); ap.add_argument('text')
    ap.add_argument('--cfg'); ap.add_argument('--json'); ap.add_argument('--keep'); ap.add_argument('--timeout',type=float,default=120)
    a=ap.parse_args(argv); lane=kitlib.bootstrap(); row=kitlib.row_of(a.row)
    if a.cfg: row=kitlib.row_at_cfg(row,a.cfg)
    try: r=check(row,input_text(a.text,row,lane),a.timeout,a.keep)
    except (ValueError,RuntimeError,OSError,subprocess.TimeoutExpired) as e: ap.exit(2,'sncheck: '+str(e)+'\n')
    print('# '+r['sn_version']+' (psyq'+r['psyq']+') vs '+r['cell'])
    print('IDENTICAL' if r['identical'] else '\n'.join(r['diff']))
    if a.json: Path(a.json).write_text(json.dumps(r,indent=2)+'\n')
    return 0 if r['identical'] else 1
if __name__=='__main__': raise SystemExit(main())
