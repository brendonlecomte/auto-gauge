#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/led_strip.h>

#include <usb/usb_device.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(test, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

#define LED_RING DT_LABEL(DT_NODELABEL(led_strip))

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_NODELABEL(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

const struct led_rgb red = { .r = 0xf, .g = 0x0, .b = 0x0, };
struct led_rgb pixels[12] = {0};

void main(void)
{
	const struct device *dev;
	const struct device *strip;
	bool led_is_on = true;
	int ret = 0;

	ret = usb_enable(NULL);

	if(ret != 0){
		LOG_ERR("USB enable failed");
		return;
	}

	dev = device_get_binding(LED0);
	if (dev == NULL) {
		LOG_ERR("LED init failed");
		return;
	}

	strip = device_get_binding(LED_RING);

	if(strip == NULL) {
		LOG_ERR("Bad strip");
	}

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		LOG_ERR("LED pin configure failed");
		return;
	}

	int i =0;
	int x = 0;
	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("testing %d", i);
		int err = led_strip_update_rgb(strip,
					&pixels,
					12);
		if(err) {
			LOG_ERR("LED update: %d", err);
		}
		memcpy(&pixels[x], &red, sizeof(struct led_rgb));
		i++;
		x++;
		if(x >= 12) x =0;
	}
}
