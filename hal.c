
#include "driverlib.h"
#include "device.h"

#include <stdio.h>
#include <file.h>
#include <stdint.h>
#include <stdbool.h>

//#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"
#include "hal.h"
//#include "board.h"
//#include "sci_io.h"

FILE _scia = {0}, _scib = {0};
FILE *scia = &_scia;
FILE *scib = &_scib;

void HAL_Init() {
    Device_init();
    Device_initGPIO();

    // SCIA setup
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDA, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    Interrupt_initModule();
    Interrupt_initVectorTable();
    SCI_performSoftwareReset(SCIA_BASE);
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, 115200, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIA_BASE);
    SCI_resetRxFIFO(SCIA_BASE);
    SCI_resetTxFIFO(SCIA_BASE);
    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableFIFO(SCIA_BASE);
    SCI_enableModule(SCIA_BASE);
    SCI_performSoftwareReset(SCIA_BASE);

    // SCIB setup
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCITXDB, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDB);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDB, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDB, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDB, GPIO_QUAL_ASYNC);

    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCIRXDB, GPIO_CORE_CPU1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDB);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDB, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDB, GPIO_QUAL_ASYNC);

    Interrupt_initModule();
    Interrupt_initVectorTable();
    SCI_performSoftwareReset(SCIB_BASE);
    SCI_setConfig(SCIB_BASE, DEVICE_LSPCLK_FREQ, 115200, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_resetChannels(SCIB_BASE);
    SCI_resetRxFIFO(SCIB_BASE);
    SCI_resetTxFIFO(SCIB_BASE);
    SCI_clearInterruptStatus(SCIB_BASE, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableFIFO(SCIB_BASE);
    SCI_enableModule(SCIB_BASE);
    SCI_performSoftwareReset(SCIB_BASE);
}

int fputc(int c, FILE *stream) {

    if (stream == scia) {
        SCI_writeCharArray(SCIA_BASE, (uint16_t*)&c, 1);
    } else if (stream == scib) {
        SCI_writeCharArray(SCIB_BASE, (uint16_t*)&c, 1);
    }
    return c;
}

int fputs(const char *s, FILE *stream) {
    while (*s != '\0') {
        fputc(*s++, stream);
    }

    return 0;
}



//int fgetc(FILE *stream){
//    int c = 0;
//    if (stream == scia) {
//        SCI_readCharArray(SCIA_BASE, (uint16_t*)&c, 1);
//    } else if (stream == scib) {
//        SCI_readCharArray(SCIB_BASE, (uint16_t*)&c, 1);
//    }
//    return c;
//}

//char *fgets(char *s, int size, FILE *stream) {
//    int c;
//    char *cs;
//    cs = s;
//    while (--size > 0 && (c = fgetc(stream)) != EOF) {
//        if ((*cs++ = c) == '\n') {
//            break;
//        }
//    }
//    *cs = '\0';
//    return (c == EOF && cs == s) ? NULL : s;
//}


// Use SCI_readCharArray directly, don't use fgetc
char *fgets(char *s, int size, FILE *stream) {
    int c;
    char *cs;
    cs = s;
    while (--size > 0) {
        if (stream == scia) {
            SCI_readCharArray(SCIA_BASE, (uint16_t*)&c, 1);
        } else if (stream == scib) {
            SCI_readCharArray(SCIB_BASE, (uint16_t*)&c, 1);
        }
        if (c == EOF) {
            break;
        }
        if ((*cs++ = c) == '\n') {
            break;
        }
    }
    *cs = '\0';
    return (cs == s) ? NULL : s;
}
