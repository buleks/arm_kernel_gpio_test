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

	
	for (int i = 0; i < info.lines; i++)
	{
		line_info.line_offset = i;
		ret = ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &line_info);

		if (ret == -1)
		{
			 printf("Unable to get line info from offset %d: %s", i, strerror(errno));
		}

		printf("offset: %d, name: %s, consumer: %s. Flags:\t[%s]\t[%s]\t[%s]\t[%s]\t[%s]\n",
				i,
				line_info.name,
				line_info.consumer,
				(line_info.flags & GPIOLINE_FLAG_IS_OUT) ? "OUTPUT" : "INPUT",
				(line_info.flags & GPIOLINE_FLAG_ACTIVE_LOW) ? "ACTIVE_LOW" : "ACTIVE_HIGHT",
				(line_info.flags & GPIOLINE_FLAG_OPEN_DRAIN) ? "OPEN_DRAIN" : "...",
				(line_info.flags & GPIOLINE_FLAG_OPEN_SOURCE) ? "OPENSOURCE" : "...",
				(line_info.flags & GPIOLINE_FLAG_KERNEL) ? "KERNEL" : "");

	}
	(void)close(fd);
}
