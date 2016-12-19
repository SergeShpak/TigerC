#!/usr/bin/python

import sys
import os
import os.path
import subprocess


LEXER_RUN_RESULT_FILE = "tokens.txt"


def get_tiger_files(some_dir):
    tiger_files = []
    for root, subdirs, files in os.walk(some_dir):
        new_files = [os.path.join(root, f) for f in files
                     if ".tig" == os.path.splitext(f)[1]]
        tiger_files.extend(new_files)
    return tiger_files


def main():
    if len(sys.argv) < 4:
        print("Too few arguments")
        return
    tiger_lexer_exe = sys.argv[1]
    tiger_files_dir = sys.argv[2]
    dest_file = sys.argv[3]
    open(dest_file, "w").close()
    tiger_files = get_tiger_files(tiger_files_dir)
    for f in tiger_files:
        p = subprocess.Popen([tiger_lexer_exe, f], stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)
        out, err = p.communicate()
        strings_to_write = []
        if (not out and not err):
            continue
        strings_to_write.append("File: " + f)
        if (out):
            strings_to_write.append("Out: \n" + out)
        if (err):
            strings_to_write.append("Errors: \n" + err)
        strings_to_write.append("\n")
        dest = open(dest_file, "a+")
        dest.writelines(strings_to_write)
        dest.close()
    if (os.path.isfile(LEXER_RUN_RESULT_FILE)):
        os.remove(LEXER_RUN_RESULT_FILE)


if __name__ == "__main__":
    main()
