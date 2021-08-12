#include "turnstile_manager.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
send_serial_test send_serial_cb;
recived_serial_test recived_serial_cb;
#define MTT 0x1021 /* crc-ccitt mask */
static unsigned short updateCRC(unsigned short crc, uint16_t karakter)
{
    karakter <<= 8;
    int i;
    for (i = 0; i < 8; i++)
    {
        if ((crc ^ karakter) & 0x8000)
            crc = (crc << 1) ^ MTT;
        else
            crc <<= 1;
        karakter <<= 1;
    }

    return crc;
}

static unsigned short computeCRC16(uint8_t* array, int length)
{
    unsigned short CRC16 = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        CRC16 = updateCRC(CRC16, (uint16_t)array[i]);
    }

    return CRC16;
}
void data_read(const char * data);

const char* recived_serial_port(void){
    return recived_serial_cb();
}

int send_serial_port(const char* control_data,size_t size) {
    return send_serial_cb(control_data, size);
}

int turnstile_set_mode(uint8_t operating_mode, uint8_t input_mode,uint8_t output_mode, uint8_t timeout, uint8_t fotosel, uint8_t serial_pass_num) { // 0x11 CMD
    uint8_t buf[11] = { 0x01,0x07,0x11,operating_mode,input_mode,output_mode,timeout,fotosel,serial_pass_num };
    uint16_t crc_16 = computeCRC16(buf, sizeof (buf)-2);
    buf[9] = (uint8_t)(crc_16);
    buf[10] = (uint8_t)crc_16 >> 8;
    return send_serial_port((const char*)buf, 11);
}

int edit_timeout(uint16_t time) {   // 0X16 CMD
    uint8_t buf[7] = { 0x01,0x03,0x16,};
    buf[3]=(uint8_t)time>>8;
    buf[4]=(uint8_t)time;
    uint16_t crc_16 = computeCRC16(buf, sizeof(buf)-2);
    buf[5] = (uint8_t)crc_16;
    buf[6] = (uint8_t)crc_16 >> 8;
    return send_serial_port((const char*)buf, sizeof (buf));
}

int date_time_settings(uint8_t d, uint8_t m, uint8_t y, uint8_t h, uint8_t min, uint8_t sec) {
    // d,m,y,h,min,sec ??
    uint8_t buf[11] = { 0x01,0x07,0x17,d,m,y,h,min,sec};
    uint16_t crc_16 = computeCRC16(buf, sizeof(buf)-2);
    buf[9] =(uint8_t)(crc_16);
    buf[10]=(uint8_t)crc_16 >> 8;
    return send_serial_port((const char*)buf, sizeof (buf));
}
int transparent_mode(uint8_t flap_state, uint8_t input_led, uint8_t output_led) {
    // flap_state,input_led,output_led ???
    uint8_t buf[11] = { 0x01,0x07,0x18,flap_state,input_led,output_led};
    uint16_t crc_16 = computeCRC16(buf, sizeof (buf)-2);
    buf[9] = (uint8_t)(crc_16);
    buf[10] = (uint8_t)crc_16 >> 8;
    return send_serial_port((const char*)buf, sizeof(buf));
}
int send_packet(turnstile_event data) {
        uint8_t data_t=(uint8_t)data;
        if(data_t==0x12){
            uint8_t pass_type = 0x01;
            uint8_t buf[6] = { 0x01,0x01,0x12,pass_type, };
            uint16_t crc_16 = computeCRC16(buf, sizeof(buf)-2);
            buf[4] = (uint8_t)(crc_16);
            buf[5] = (uint8_t)crc_16 >> 8;
            return send_serial_port((const char*)buf, sizeof (buf));
        }
        else {
            uint8_t buf[5] = { 0x01,0x01,data_t,};
            uint16_t crc_16 = computeCRC16(buf, sizeof(buf)-2);  // (sizeof(buf) / sizeof(buf[0]))
            buf[3] = (uint8_t)crc_16 & 0xff; // LOW NIBBLE  (uint8_t)crc_16
            buf[4] = (uint8_t)(crc_16 << 8 | crc_16 >> 8); // HIGH NIBBLE  (uint8_t)crc_16>>8;
            return send_serial_port((const char*)buf, sizeof(buf));
        }
    }
