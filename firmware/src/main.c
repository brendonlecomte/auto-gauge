#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <usb/usb_device.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(test, LOG_LEVEL_INF);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

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

void main(void)
{
	const struct device *dev;
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

	ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		LOG_ERR("LED pin configure failed");
		return;
	}

	int i =0;
	while (1) {
		gpio_pin_set(dev, PIN, (int)led_is_on);
		led_is_on = !led_is_on;
		k_msleep(SLEEP_TIME_MS);
		LOG_INF("testing %d", i);
		i++;
	}
}
