/*
 * Copyright (c) 2021 Arm Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdio.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "tfm_ns_interface.h"
#include "psa/protected_storage.h"
#include "serial.h"
#include "blink_task.h"
#include "ml_interface.h"

enum {
    LED1    = 1 << 0,
    LED_YES = LED1,
    LED2    = 1 << 1,
    LED_GO  = LED2, 
    LED3    = 1 << 2,
    LED_UP  = LED3,
    LED4    = 1 << 3,
    LED_LEFT = LED4,
    LED5    = 1 << 4,
    LED_ON = LED5,
    LED6    = 1 << 5,
    LED_ALIVE = LED6,
    LED7    = 1 << 6,
    LED8    = 1 << 7,
    LED9    = 1 << 8,
    LED10   = 1 << 9,
    LED_ALL = 0xFF
};

static uint32_t *fpgaio_leds = (uint32_t *)0x49302000;

// Events 
typedef enum {
    UI_EVENT_BLINK,
    UI_EVENT_ML_STATE_CHANGE
} ui_state_event_t;

typedef struct { 
    ui_state_event_t event;
} ui_msg_t;

static ui_msg_t blink_event = {
    UI_EVENT_BLINK
};

static ui_msg_t ml_state_change_event = { 
    UI_EVENT_ML_STATE_CHANGE
};

// Message queue 
static QueueHandle_t ui_msg_queue = NULL;

// Blinking timer 
TimerHandle_t blink_timer;

void led_on(uint8_t bits)
{
    *fpgaio_leds |= bits;
}

void led_off(uint8_t bits)
{
    *fpgaio_leds &= ~bits;
}

void led_toggle(uint8_t bits)
{
    *fpgaio_leds ^= bits;
}

static void blink_timer_cb( TimerHandle_t xTimer ) {
    // Schedule blink of the led in the event queue 
    xQueueSend(ui_msg_queue, (void*) &blink_event, 0);
}

/*
 * Blink task.
 *
 * Blinks LEDs.
 * 
 * LED1 on and LED2 off       => heard YES
 * LED1 off and LED2 off      => heard NO
 * LED1 off and LED2 blinking => no/unknown input
 */
void blink_task(void *pvParameters)
{
    printf("Blink task started\r\n");

    // Create the ui event queue 
    ui_msg_queue = xQueueCreate(
        10,                 // In practive at most two items (blink and ml state change) should be in the queue.  
        sizeof(ui_msg_t)
    );

    // Configure the timer 
    blink_timer = xTimerCreate( 
        "Blink Timer",
        portTICK_PERIOD_MS * 25,  // timeout
        pdTRUE,                   // auto reload
        ( void * ) 0,             // initial value
        blink_timer_cb      
    );

    // Setup blinking event 
    led_off(LED_ALL);

    // start the blinking timer 
    xTimerStart(blink_timer, portMAX_DELAY);

    while (1) {
        ui_msg_t msg; 
        if(xQueueReceive(ui_msg_queue, &msg, portMAX_DELAY) != pdPASS ) {
           continue; 
        }

        switch (msg.event)
        {
            case UI_EVENT_BLINK:
                led_toggle(LED_ALL);
                break;

            default:
                break;
        }
    }
}
