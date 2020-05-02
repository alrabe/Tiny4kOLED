/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */
#ifndef TINY4KOLED_TINYWIREM_H
#define TINY4KOLED_TINYWIREM_H

#include <TinyWireM.h>  // Version with buffer bugfix: https://github.com/adafruit/TinyWireM
#include "Tiny4kOLED_common.h"

#ifndef DATACUTE_I2C_TINYWIREM
#define DATACUTE_I2C_TINYWIREM

static bool datacute_write_tinywirem(uint8_t byte) {
	return TinyWireM.write(byte);
}

static uint8_t datacute_read_tinywirem(void) __attribute__((unused));
static uint8_t datacute_read_tinywirem(void) {
	return TinyWireM.read();
}

static uint8_t datacute_endTransmission_tinywirem(void) {
	return TinyWireM.endTransmission();
}

#endif

static bool tiny4koled_beginTransmission_tinywirem(void) {
	TinyWireM.beginTransmission(SSD1306);
	return true;
}

#ifndef TINY4KOLED_QUICK_BEGIN
static bool tiny4koled_check_tinywirem(void) {
	const uint8_t noError = 0x00;
	tiny4koled_beginTransmission_tinywirem();
	return (datacute_endTransmission_tinywirem()==noError);
}
#endif

static void tiny4koled_begin_tinywirem(void) {
	TinyWireM.begin();
#ifndef TINY4KOLED_QUICK_BEGIN
	while (!tiny4koled_check_tinywirem()) {
		delay(10);
	}
#endif
}

SSD1306Device oled(&tiny4koled_begin_tinywirem, &tiny4koled_beginTransmission_tinywirem, &datacute_write_tinywirem, &datacute_endTransmission_tinywirem);

#endif
