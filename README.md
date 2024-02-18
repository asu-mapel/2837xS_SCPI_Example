# TMS320 2837xS SCPI Example

SCPI is one of the oldest and most common protocols used by test equipment.

This project integrates this open-source [`scpi-parser`](https://github.com/j123b567/scpi-parser/tree/master).


This demo uses two UARTs: SCIA and SCIB. SCIA is used by the SCPI server and SCIB is used for debugging

```
./query.py '*IDN?'
MAPEL,MIGHTY SWIZZLER,EXTRA SPICY,2024-02-18

./query.py 'MEAS:VOLT:DC?'
0
```

## Using it in your project:

1. Configure SCIs 
Check:
- pin definition of SCIA peripherals in `device.h`
- clock speed definition in `device.h`

2. implement commands in `scpi-def.c`