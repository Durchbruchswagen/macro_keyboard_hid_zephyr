/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>
#include <zephyr/sys/util.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>
#include <zephyr/logging/log.h>

#define LOG_LEVEL LOG_LEVL_DBG
LOG_MODULE_REGISTER( main );

#define LED0_NODE DT_ALIAS(led0)

static const struct device *hid_dev;


static const uint8_t hid_report_desc[] = HID_KEYBOARD_REPORT_DESC();

static struct gpio_callback gpio_callbacks[6];

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static enum usb_dc_status_code usb_status;

#define BUTTON0 DT_ALIAS(sw0)
#define BUTTON1 DT_ALIAS(sw1)
#define BUTTON2 DT_ALIAS(sw2)
#define BUTTON3 DT_ALIAS(sw3)
#define BUTTON4 DT_ALIAS(sw4)
#define BUTTON5 DT_ALIAS(sw5)

static const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(BUTTON0, gpios);
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(BUTTON1, gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(BUTTON2, gpios);
static const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(BUTTON3, gpios);
static const struct gpio_dt_spec button4 = GPIO_DT_SPEC_GET(BUTTON4, gpios);
static const struct gpio_dt_spec button5 = GPIO_DT_SPEC_GET(BUTTON5, gpios);


#define DEBOUNCING_TIME 25


uint8_t mod_keys_mask[] = { 0x03, 0x03, 0x06, 0x06, 0x04, 0x04 };
uint8_t button_pressed[] = { 0x0D, 0x0E, 0x28, 0x06, 0x13, 0x05 };
uint8_t empty_report[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


static void send_report_button0( struct k_work *work )
{
	uint8_t report[] = { mod_keys_mask[0], 0x00, button_pressed[0], 0x00,
			     0x00, 0x00, 0x00, 0x00 };
	hid_int_ep_write( hid_dev, report, sizeof( report ), NULL);
	k_msleep( 100 );
	hid_int_ep_write( hid_dev, empty_report, sizeof( empty_report ), NULL);
	
}

static void send_report_button1( struct k_work *work )
{
	uint8_t report[] = { mod_keys_mask[1], 0x00, button_pressed[1], 0x00,
			     0x00, 0x00, 0x00, 0x00 };
	
	hid_int_ep_write( hid_dev, report, sizeof( report ), NULL);
	k_msleep( 100 );
	hid_int_ep_write( hid_dev, empty_report, sizeof( empty_report ), NULL);
	
}

static void send_report_button2( struct k_work *work )
{
	uint8_t report[] = { mod_keys_mask[2], 0x00, button_pressed[2], 0x00,
			     0x00, 0x00, 0x00, 0x00 };
	
	hid_int_ep_write( hid_dev, report, sizeof( report ), NULL);	
	k_msleep( 100 );
	hid_int_ep_write( hid_dev, empty_report, sizeof( empty_report ), NULL);
}

static void send_report_button3( struct k_work *work )
{
	uint8_t report[] = { mod_keys_mask[3], 0x00, button_pressed[3], 0x00,
			     0x00, 0x00, 0x00, 0x00 };

	hid_int_ep_write( hid_dev, report, sizeof( report ), NULL);	
	k_msleep( 100 );
	hid_int_ep_write( hid_dev, empty_report, sizeof( empty_report ), NULL);
}

static void send_report_button4( struct k_work *work )
{
	uint8_t report[] = { mod_keys_mask[4], 0x00, button_pressed[4], 0x00,
			     0x00, 0x00, 0x00, 0x00 };

	hid_int_ep_write( hid_dev, report, sizeof( report ), NULL);	
	k_msleep( 100 );
	hid_int_ep_write( hid_dev, empty_report, sizeof( empty_report ), NULL);
	
}

static void send_report_button5( struct k_work *work )
{
	uint8_t report[] = { mod_keys_mask[5], 0x00, button_pressed[5], 0x00,
			     0x00, 0x00, 0x00, 0x00 };
	
	hid_int_ep_write( hid_dev, report, sizeof( report ), NULL);	
	k_msleep( 100 );
	hid_int_ep_write( hid_dev, empty_report, sizeof( empty_report ), NULL);
}

static K_WORK_DELAYABLE_DEFINE( button0_work, send_report_button0 );
static K_WORK_DELAYABLE_DEFINE( button1_work, send_report_button1 );
static K_WORK_DELAYABLE_DEFINE( button2_work, send_report_button2 );
static K_WORK_DELAYABLE_DEFINE( button3_work, send_report_button3 );
static K_WORK_DELAYABLE_DEFINE( button4_work, send_report_button4 );
static K_WORK_DELAYABLE_DEFINE( button5_work, send_report_button5 );

void button0_pressed( const struct device *dev, struct gpio_callback *cb, uint32_t pins )
{
	k_work_reschedule( &button0_work, K_MSEC( DEBOUNCING_TIME ));
}

void button1_pressed( const struct device *dev, struct gpio_callback *cb, uint32_t pins )
{
	k_work_reschedule( &button1_work, K_MSEC( DEBOUNCING_TIME ));
}

void button2_pressed( const struct device *dev, struct gpio_callback *cb, uint32_t pins )
{
	k_work_reschedule( &button2_work, K_MSEC( DEBOUNCING_TIME ));
}

void button3_pressed( const struct device *dev, struct gpio_callback *cb, uint32_t pins )
{
	k_work_reschedule( &button3_work, K_MSEC( DEBOUNCING_TIME ));
}

void button4_pressed( const struct device *dev, struct gpio_callback *cb, uint32_t pins )
{
	k_work_reschedule( &button4_work, K_MSEC( DEBOUNCING_TIME ));
}

void button5_pressed( const struct device *dev, struct gpio_callback *cb, uint32_t pins )
{
	k_work_reschedule( &button5_work, K_MSEC( DEBOUNCING_TIME ));
}

static void status_cb( enum usb_dc_status_code status, const uint8_t *param )
{
	usb_status = status;
}

int callbacks_configure( const struct gpio_dt_spec *gpio, void ( *handler )( const struct device*, struct gpio_callback*, uint32_t ), struct gpio_callback *callback)
{
	if ( !device_is_ready( gpio->port ) )
	{
		LOG_ERR( "%s: device not ready.", gpio->port->name );
		return -ENODEV;
	}

	gpio_pin_configure_dt( gpio, GPIO_INPUT );
	gpio_init_callback( callback, handler, BIT( gpio->pin ));
	gpio_add_callback( gpio->port, callback );
	gpio_pin_interrupt_configure_dt( gpio, GPIO_INT_EDGE_RISING );	
	return 0;
}

int main(void)
{
	int ret;

	if( !gpio_is_ready_dt( &led ) )
	{
		LOG_ERR( "LED device %s not ready.", led.port->name );
		return 0;
	}
	
	ret = gpio_pin_configure_dt( &led, GPIO_OUTPUT_ACTIVE );
	if( ret < 0 )
	{
		return 0;
	}


	hid_dev = device_get_binding( "HID_0");
	
	if ( hid_dev == NULL )
	{
		
		LOG_ERR( "Cannot get USB HID Device" );
		return 0;
	}
	
	usb_hid_register_device( hid_dev, hid_report_desc, sizeof( hid_report_desc ), NULL );
	usb_hid_init( hid_dev );
	ret = usb_enable( status_cb );

	if( ret != 0 )
	{
		
		gpio_pin_toggle( led.port, led.pin );
		LOG_ERR( "Failed to enable USB" );
		return 0;
	}

	
	if ( callbacks_configure( &button0, &button0_pressed, &gpio_callbacks[0] ) )
	{
		LOG_ERR( "Failed configuring button 0 callback.");
		return 0;
	}

	if ( callbacks_configure( &button1, &button1_pressed, &gpio_callbacks[1] ) )
	{
		LOG_ERR( "Failed configuring button 1 callback.");
		return 0;
	}

	if ( callbacks_configure( &button2, &button2_pressed, &gpio_callbacks[2] ) )
	{
		LOG_ERR( "Failed configuring button 2 callback.");
		return 0;
	}

	if ( callbacks_configure( &button3, &button3_pressed, &gpio_callbacks[3] ) )
	{
		LOG_ERR( "Failed configuring button 3 callback.");
		return 0;
	}

	if ( callbacks_configure( &button4, &button4_pressed, &gpio_callbacks[4] ) )
	{
		LOG_ERR( "Failed configuring button 4 callback.");
		return 0;
	}

	if ( callbacks_configure( &button5, &button5_pressed, &gpio_callbacks[5] ) )
	{
		LOG_ERR( "Failed configuring button 5 callback.");
		return 0;
	}

	while( true )
	{
		gpio_pin_toggle( led.port, led.pin );
		k_msleep(1000);
	}
	
	return 0;
}
