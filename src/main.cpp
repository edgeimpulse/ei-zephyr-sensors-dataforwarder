
/* The Clear BSD License
 *
 * Copyright (c) 2025 EdgeImpulse Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 *   * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/uart.h>
#include <stdio.h>
#include <stdlib.h>

static int64_t time_between_samples_us = (1000000 / (CONFIG_SAMPLING_FREQUENCY_HZ - 1));
const struct device *sensor;

int main() {
    // output immediately without buffering
    setvbuf(stdout, NULL, _IONBF, 0);

    if (strlen(CONFIG_SENSOR_NAME) > 0) {
        printk("Sensor name: %s\n", CONFIG_SENSOR_ALIAS_NAME);
        sensor = device_get_binding(CONFIG_SENSOR_NAME);
    }
    else if (strlen(CONFIG_SENSOR_ALIAS_NAME) > 0) {
        printk("Using sensor alias name: %s\n", CONFIG_SENSOR_ALIAS_NAME);
        if (DT_HAS_ALIAS(accel0)) { // check if alias exists
            sensor = DEVICE_DT_GET_OR_NULL(DT_ALIAS(accel0));
        }
    }
    else {
        printk("No sensor name or alias name provided. Please set SENSOR_NAME or SENSOR_ALIAS_NAME in prj.conf\n");
        return 1;
    }

    if (sensor == NULL) {
        printk("Could not get sensor device driver\n");
        return 1;
    }

    printk("Trying to init %s\n", sensor->name);
    if (!device_is_ready(sensor)) {
        printk("Could not init sensor device driver\n");
        return false;
    }
    printk("%s intialized successfully\n", sensor->name);

    struct sensor_value array_sensor_value[CONFIG_SENSOR_CHAN_NUMBER];

    while (1) {
        // start a timer that expires when we need to grab the next value
        struct k_timer next_val_timer;
        k_timer_init(&next_val_timer, NULL, NULL);
        k_timer_start(&next_val_timer, K_USEC(time_between_samples_us), K_NO_WAIT);

        // read data from the sensor
        if (sensor_sample_fetch(sensor) < 0) {
            printk("Sensor sample update error\n");
            return 1;
        }

        sensor_channel_get(sensor, sensor_channel(CONFIG_SENSOR_CHAN_READ), array_sensor_value);

        for (int i = 0; i < CONFIG_SENSOR_CHAN_NUMBER; i++) {
            if (i != 0) {
                printk(",");
            }
            printk("%.3f", sensor_value_to_double(&array_sensor_value[i]));
        }
        printk("\r\n");

        // busy loop until next value should be grabbed
        while (k_timer_status_get(&next_val_timer) <= 0);
    }
}
