#!/usr/bin/python

import random, sys
from optparse import OptionParser

class shuf:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def shuffle(self):
        random.shuffle(self.lines)
        return self.lines

def read_in():
    lines = sys.stdin.readlines()
    for i in range(len(lines)):
        lines[i] = lines[i].replace('\n','')
    return lines        

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE\n%prog -e [OPTION]... [ARG]...

Output randomly selected lines from FILE."""

    parser = OptionParser(version=version_msg,
                            usage=usage_msg)
    parser.add_option("-n", "--head-count",
                      action="store", dest="count", type=int,
                      help="Output at most count lines. By default, all input lines are output.")

    parser.add_option("-e", "--echo",
                      action="store_true", dest="echoBool", default=False,
                      help="Treat each command-line operand as an input line")

    parser.add_option("-r", "--repeat",
                      action="store_true", dest="shouldRepeat", default=False,
                      help="Repeat output values, that is, select with replacement. With this option the output is not a permutation of the input; instead, each output line is randomly chosen from all the inputs. This option is typically combined with --head-count; if --head-count is not given, shuf repeats indefinitely.")

    options, args = parser.parse_args(sys.argv[1:])

    if echoBool:
        input_file = read_in()
    else:
        try:
            input_file = args[0]
        except:
            parser.error("Invalid args")

    try:
        words = shuf(input_file)
        generator = words.shuffle()
        if options.count is None:
            count = len(generator)
        else:
            count = int(options.count)
    except:
        parser.error("invalid headcount: {0}".
                     format(options.count))
    if count < 0:
        parser.error("negative count: {0}".
                     format(count))
    if len(args) != 1:
        parser.error("wrong number of operands")

    try:
        for index in range(count):
            if shouldRepeat:
                sys.stdout.write(generator[random.randint(0,count-1)])
            else:
                sys.stdout.write(generator[index])
    except IOError as (errno, strerror):
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()