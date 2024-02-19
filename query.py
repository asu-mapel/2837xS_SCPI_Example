#!/usr/bin/env python3

import pyvisa
import argparse

rm = pyvisa.ResourceManager()
listR = rm.list_resources()
for li in listR:
    try:
        inst = rm.open_resource(li, baud_rate=115200 )
        inst.write_termination = '\r\n'
        inst.read_termination = '\r\n'

        # parser = argparse.ArgumentParser(description='Send command to the device')
        # parser.add_argument('command', type=str, help='Command')

        # args = parser.parse_args()
        print(inst.query("*IDN?"))
    except Exception as e:
        print(li, e)
    # if '?' in args.command:
    #     print(inst.query(args.command))
    # else:
    #     inst.write(args.command)

