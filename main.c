#include "driverlib.h"
#include "device.h"
#include <string.h>
#include "scpi/scpi.h"
#include "scpi-def.h"
#include "hal.h"

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    (void) context;
    fputs(data, SCPI_SCI);
    return len;
}

scpi_result_t SCPI_Flush(scpi_t * context) {
    (void) context;
    fputs("\r\n", SCPI_SCI);
    return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
    (void) context;

    fprintf(DBG_SCI, "**ERROR: %d, \"%s\"\r\n", (int16_t) err, SCPI_ErrorTranslate(err));
    return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
    (void) context;

    if (SCPI_CTRL_SRQ == ctrl) {
        fprintf(DBG_SCI, "**SRQ: 0x%X (%d)\r\n", val, val);
    } else {
        fprintf(DBG_SCI, "**CTRL %02x: 0x%X (%d)\r\n", ctrl, val, val);
    }
    return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context) {
    (void) context;

    fprintf(DBG_SCI, "**Reset\r\n");
    return SCPI_RES_OK;
}

scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context) {
    (void) context;
    return SCPI_RES_ERR;
}

/*
 *
 */
int main() {
    HAL_Init();
    SCPI_Init(&scpi_context,
            scpi_commands,
            &scpi_interface,
            scpi_units_def,
            SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
            scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
            scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

    fprintf(DBG_SCI, "SCPI Interactive demo\r\n\0");
    char smbuffer[10];
    while (1) {
        if (NULL == fgets(smbuffer, 10, SCPI_SCI)) {
            break;
        }
        SCPI_Input(&scpi_context, smbuffer, strlen(smbuffer));
    }

}


