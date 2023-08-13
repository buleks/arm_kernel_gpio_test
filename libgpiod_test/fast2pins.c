#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#ifndef	CONSUMER
#define	CONSUMER	"fast test"
#endif

int main(int argc, char **argv)
{
	char *chipname = "gpiochip1";
	unsigned int line_num = 12;	// GPIO Pin PA12
	unsigned int val;
	struct gpiod_chip *chip;
	struct gpiod_line *line12,*line11;
	int i, ret;

	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		perror("Open chip failed\n");
		fflush(stderr);
		goto end;
	}

	line12 = gpiod_chip_get_line(chip, line_num);
	if (!line12) {
		perror("Get line failed\n");
		goto close_chip;
	}
	
	line11 = gpiod_chip_get_line(chip, 11);
	if (!line11) {
		perror("Get line failed\n");
		goto close_chip;
	}

	ret = gpiod_line_request_output(line12, CONSUMER, 0);
	if (ret < 0) {
		perror("Request line as output failed\n");
		goto release_line;
	}

	ret = gpiod_line_request_output(line11, CONSUMER, 0);
	if (ret < 0) {
		perror("Request line as output failed\n");
		goto release_line;
	}

	line12 = gpiod_chip_get_line(chip, line_num);
	if (!line12) {
		perror("Get line failed\n");
		goto close_chip;
	}
	line11 = gpiod_chip_get_line(chip, 11);
	if (!line11) {
		perror("Get line failed\n");
		goto close_chip;
	}

	while(1)
	{
		ret = gpiod_line_set_value(line12, val);
		ret = gpiod_line_set_value(line11, val);
		if (ret < 0) {
			perror("Set line output failed\n");
			goto release_line;
		}
		//printf("Output %u on line #%u\n", val, line_num);
		val = !val;
	}

release_line:
	gpiod_line_release(line12);
	gpiod_line_release(line11);
close_chip:
	gpiod_chip_close(chip);
end:
	return 0;
}
