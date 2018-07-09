#!/usr/bin/env python3

import os
from pathlib import Path
import shutil
import sys

def print_usage():
    sys.stderr.write("""\
Usage: %s DEST_DIR

""" % os.path.basename(__file__))

if len(sys.argv) < 2 or len([x for x in sys.argv if x in ('-?', '-h', '--help')]) > 0:
    print_usage()
    sys.exit(1)

samples_root = Path(Path(os.path.realpath(__file__)).parent, "Release" , "P0267_RefImpl" , "Samples")
src_files = []
dest_dir = Path(sys.argv[1])

for sample_dir in samples_root.iterdir():
    if sample_dir.is_dir():
        src_files += sample_dir.glob('*.html')
        src_files += sample_dir.glob('*.wasm')
        src_files += sample_dir.glob('*.js')

sys.stderr.write("Installing samples...\n\tFrom: '%s'\n\t  To: '%s'\n\n" % (samples_root, dest_dir))    # print info to stderr, which is avoided in pipes (by default) 
for src_file in src_files:
    dest_file = Path(dest_dir, src_file.name)   # build dest-file path
    sys.stdout.write("%s\n" % dest_file)        # destination files are printed to stdout, for possible piping to other things
    shutil.copy2(src_file, dest_file)           # 'shutil.copy2' == copy, with attempt to copy file-metadata
