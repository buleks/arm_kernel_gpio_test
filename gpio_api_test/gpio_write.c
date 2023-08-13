// include API header for the new interface

#include <linux/gpio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdlib.h>
#define DEV_NAME "/dev/gpiochip1"
#include <stdio.h>

void main()
{
	int fd, ret;

	fd = open(DEV_NAME, O_RDONLY);
	if (fd < 0)
	{

	    printf("Unabled to open %s: %s",DEV_NAME, strerror(errno));

	    return;

	}

	struct gpiochip_info info;

	struct gpioline_info line_info;

	
	// Query GPIO chip information

	ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &info);

	if (ret == -1)
	{
		printf("Unable to get chip info from ioctl: %s", strerror(errno));
		close(fd);
		return;
	}

	printf("Chip name: %s\n", info.name);
	printf("Chip label: %s\n", info.label);

	printf("Number of lines: %d\n", info.lines);

	struct gpiohandle_request rq;
	rq.lineoffsets[0] = 12;
	rq.lines = 1;

	rq.flags = GPIOHANDLE_REQUEST_OUTPUT;

	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &rq);
	
	if (ret == -1)
	{
		printf("Unable to line handle from ioctl : %s", strerror(errno));
		close(fd);
		return;
	}


	struct gpiohandle_data data;
	while(1)
	{
	//	int c = fgetc(stdin);

	//	if(c == 'q')
	//	{
	//		break;
	//	}

		data.values[0] = 1; 
		ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);

		if (ret == -1)
		{	
	    		printf("Unable to set line value using ioctl : %s", strerror(errno));
		}

		data.values[0] = 0; 
		ret = ioctl(rq.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);

		if (ret == -1)
		{	
	    		printf("Unable to set line value using ioctl : %s", strerror(errno));
		}
	}

	(void)close(fd);
}
