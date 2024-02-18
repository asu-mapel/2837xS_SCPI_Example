#!/usr/bin/env python3

import pyvisa
import argparse

rm = pyvisa.ResourceManager()
inst = rm.open_resource('ASRL/dev/ttyUSB1::INSTR', baud_rate=115200)
inst.write_termination = '\r\n'
inst.read_termination = '\r\n'

parser = argparse.ArgumentParser(description='Send command to the device')
parser.add_argument('command', type=str, help='Command')

args = parser.parse_args()

if '?' in args.command:
    print(inst.query(args.command))
else:
    inst.write(args.command)

