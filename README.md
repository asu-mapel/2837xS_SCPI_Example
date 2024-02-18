# TMS320 2837xS SCPI Example

SCPI is one of the oldest and most common protocols used by test equipment. This project ports an open-source [`scpi-parser`](https://github.com/j123b567/scpi-parser/tree/master) on to the TMS320. Use this as a template to implement a custom SCPI interface for your firmware project.

This demo uses two UARTs: SCIA and SCIB. SCIA is used by the SCPI server and SCIB is used for debugging. You should dedicate one UART exclusively to SCPI.

## Example

An example SCPI server implementation is in `scpi-def.c`

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

2. implement your custom commands in `scpi-def.c`