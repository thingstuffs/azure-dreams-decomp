#!/usr/bin/env python3
"""Fail-closed recipe envelope for portable v1 proofs and incremental journals.

The adapter models canonical include search and deterministic compilation.
Location-sensitive builtins and custom include/profile inputs require a new
adapter before they can enter this landing path, even if a prior journal exists.
"""
import argparse
import json
from pathlib import Path
import re
import shlex
import sys

ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/gate')]


def check(root):
    from gate import overlay_module_gate as G
    import overlay_scoped_fingerprint as S
    root=Path(root);files=0;recipes=set()
    folders=[p for p in (root/'src').iterdir() if p.is_dir() and p.name!='slus'] if (root/'src').exists() else []
    for folder in folders:
        for path in [*folder.rglob('*.c'),*folder.rglob('*.h')]:
            if re.search(r'\b__(?:FILE|BASE_FILE)__\b',path.read_text()):
                raise ValueError('path-sensitive C requires a proof adapter: '+str(path.relative_to(root)))
            files+=1
    for path in (root/'include').rglob('*.h'):
        if re.search(r'\b__(?:FILE|BASE_FILE)__\b',path.read_text()):
            raise ValueError('path-sensitive header requires a proof adapter: '+str(path.relative_to(root)))
        files+=1
    for family in ('main','town','dungeon','dungeon_engine','ovmovie'):
        path=root/'ledger/splits'/f'{family}.jsonl'
        if not path.exists():continue
        for line in path.read_text().splitlines():
            if not line.strip() or line.lstrip().startswith('#'):continue
            row=json.loads(line)
            if row.get('result')!='MATCH' or row.get('rerun') or row.get('source_kind','c')!='c':continue
            version,flags=S.parse_config_label(root,row.get('config') or '2.7.2',G)
            recipes.add((version,flags))
    for version,flags in recipes:
        for flag in shlex.split(flags):
            if (flag.startswith(('-I','-i','-nostdinc','-fprofile','-fbranch-probabilities',
                                 '-B','-specs','--specs','--sysroot','-wrapper')) or
                    re.search(r'\b__(?:FILE|BASE_FILE|DATE|TIME|TIMESTAMP)__\b',flag)):
                raise ValueError('noncanonical compiler input requires a proof adapter: '+version+' '+flags)
    return dict(result='PASS',files=files,recipes=len(recipes))


def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--root',type=Path,required=True)
    a=ap.parse_args();print(json.dumps(check(a.root.resolve()),sort_keys=True))

if __name__=='__main__':main()
