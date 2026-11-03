#!/usr/bin/env python3
"""Publish a node macro dependency through a source's existing private header.

Use after a guarded plan and a placement-copy diagnostic. This changes only
the header named after the edited source, records its exact replay edit, and
requires complete batch proof over every consumer before accepting it.
"""
import argparse
import csv
import hashlib
import json
from pathlib import Path

ROOT=Path(__file__).resolve().parents[3]


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root',type=Path,default=ROOT)
    ap.add_argument('--batch',type=Path,required=True)
    ap.add_argument('--source',required=True)
    args=ap.parse_args()
    root=args.root.resolve()
    batch=args.batch.resolve()
    assert batch.is_relative_to(root)
    assert args.source.startswith('src/') and '..' not in Path(args.source).parts
    applied=batch/'applied.tsv'
    with applied.open() as input_file:
        reader=csv.DictReader(input_file,delimiter='\t');fields=reader.fieldnames;rows=list(reader)
    assert any(p['file']==args.source and p['new'].startswith(('NODE_HEADER(','NODE_BODY(')) for p in rows)
    relative=Path(args.source).relative_to('src').with_suffix('.h')
    header=Path('include')/relative
    assert header.parts[1]!='shared', 'use the existing source-private header'
    assert '#include "'+relative.as_posix()+'"' in (root/args.source).read_text()
    path=root/header
    original=path.read_text()
    assert '"shared/object_node.h"' not in original, 'dependency already directly published'
    position=original.rfind('#endif')
    assert position>=0
    addition='#include "shared/object_node.h"\n\n'
    path.write_text(original[:position]+addition+original[position:])
    rows.append(dict(file=header.as_posix(),function='<header>',line=original.count('\n',0,position)+1,
                     route='header_dependency',start=position,end=position,old='',new=addition,casts=0,
                     reason='node_macro_import_for_placement_copies',source_sha256=hashlib.sha256(original.encode()).hexdigest(),tu=args.source))
    with applied.open('w',newline='') as output:
        writer=csv.DictWriter(output,fields,delimiter='\t',lineterminator='\n');writer.writeheader();writer.writerows(rows)
    summary=json.loads((batch/'summary.json').read_text())
    summary.setdefault('published_headers',[]).append(header.as_posix())
    (batch/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('Published guarded dependency:',header.as_posix(),'; full batch proof required')


if __name__=='__main__':
    main()
