#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
 
#define MAP(x, desc) [x ... x] = desc

char *type_desc[] = {
    MAP(EV_SYN, "EV_SYN"),
    MAP(EV_KEY, "EV_KEY"),
    MAP(EV_REL, "EV_REL"),
    MAP(EV_ABS, "EV_ABS"),
    MAP(EV_MSC, "EV_MSC"),
    MAP(EV_SW , "EV_SW "),
    MAP(EV_LED, "EV_LED"),
    MAP(EV_SND, "EV_SND"),
    MAP(EV_REP, "EV_REP"),
    MAP(EV_FF , "EV_FF "),
    MAP(EV_PWR, "EV_PWR"),
    MAP(EV_FF_STATUS, "EV_FF_STATUS")
};

char * abs_code_desc[] = {
	MAP(ABS_X,					"ABS_X"),
	MAP(ABS_Y,                  "ABS_Y"),
	MAP(ABS_Z,                  "ABS_Z"),
	MAP(ABS_RX,                 "ABS_RX"),
	MAP(ABS_RY,                 "ABS_RY"),
	MAP(ABS_RZ,                 "ABS_RZ"),
	MAP(ABS_THROTTLE,           "ABS_THROTTLE"),
	MAP(ABS_RUDDER,             "ABS_RUDDER"),
	MAP(ABS_WHEEL,              "ABS_WHEEL"),
	MAP(ABS_GAS,                "ABS_GAS"),
	MAP(ABS_BRAKE,              "ABS_BRAKE"),
	MAP(ABS_HAT0X,              "ABS_HAT0X"),
	MAP(ABS_HAT0Y,              "ABS_HAT0Y"),
	MAP(ABS_HAT1X,              "ABS_HAT1X"),
	MAP(ABS_HAT1Y,              "ABS_HAT1Y"),
	MAP(ABS_HAT2X,              "ABS_HAT2X"),
	MAP(ABS_HAT2Y,              "ABS_HAT2Y"),
	MAP(ABS_HAT3X,              "ABS_HAT3X"),
	MAP(ABS_HAT3Y,              "ABS_HAT3Y"),
	MAP(ABS_PRESSURE,           "ABS_PRESSURE"),
	MAP(ABS_DISTANCE,           "ABS_DISTANCE"),
	MAP(ABS_TILT_X,             "ABS_TILT_X"),
	MAP(ABS_TILT_Y,             "ABS_TILT_Y"),
	MAP(ABS_TOOL_WIDTH,         "ABS_TOOL_WIDTH"),
	MAP(ABS_VOLUME,             "ABS_VOLUME"),
	MAP(ABS_MISC,               "ABS_MISC"),
	MAP(ABS_MT_SLOT,            "ABS_MT_SLOT"),
	MAP(ABS_MT_TOUCH_MAJOR,     "ABS_MT_TOUCH_MAJOR"),
	MAP(ABS_MT_TOUCH_MINOR,     "ABS_MT_TOUCH_MINOR"),
	MAP(ABS_MT_WIDTH_MAJOR,     "ABS_MT_WIDTH_MAJOR"),
	MAP(ABS_MT_WIDTH_MINOR,     "ABS_MT_WIDTH_MINOR"),
	MAP(ABS_MT_ORIENTATION,     "ABS_MT_ORIENTATION"),
	MAP(ABS_MT_POSITION_X,      "ABS_MT_POSITION_X"),
	MAP(ABS_MT_POSITION_Y,      "ABS_MT_POSITION_Y"),
	MAP(ABS_MT_TOOL_TYPE,       "ABS_MT_TOOL_TYPE"),
	MAP(ABS_MT_BLOB_ID,         "ABS_MT_BLOB_ID"),
	MAP(ABS_MT_TRACKING_ID,     "ABS_MT_TRACKING_ID"),
	MAP(ABS_MT_PRESSURE,        "ABS_MT_PRESSURE"),
	MAP(ABS_MT_DISTANCE,        "ABS_MT_DISTANCE"),
	MAP(ABS_MT_TOOL_X,          "ABS_MT_TOOL_X"),
	MAP(ABS_MT_TOOL_Y,          "ABS_MT_TOOL_Y")
};

int report_event( void )
{
	int	fd;
	fd_set	rds;
	int	ret;
	struct input_event	event;
	struct timeval		time;

	fd = open( "/dev/input/event0", O_RDONLY );

	if ( fd < 0 ) {
		perror( "/dev/input/event0" );
		return(-1);
	}

	while ( 1 ) {
		FD_ZERO( &rds );
		FD_SET( fd, &rds );

		/*调用select检查是否能够从/dev/input/event0设备读取数据*/
		ret = select( fd + 1, &rds, NULL, NULL, NULL );
		if ( ret < 0 ) {
			perror( "select" );
			return(-1);
		}
		/*能够读取到数据*/
		else if ( FD_ISSET( fd, &rds ) ) {
			ret	 = read( fd, &event, sizeof(struct input_event) );
			time = event.time;
			printf( "timeS = %d, timeUS = %d ", time.tv_sec, time.tv_usec);
			printf( "type = 0x%02x (%s), ", event.type, type_desc[event.type]);
            if (event.type == EV_ABS) {
			    printf( "code = 0x%02x (%s), value = 0x%02x (%d)\n", event.code, abs_code_desc[event.code], event.value, event.value);
            } else {
			    printf( "code = 0x%02x, value = 0x%02x \n", event.code, event.value);
            }
		}
	}
	/*关闭设备文件句柄*/
	close( fd );
	return(0);

}

int main()
{
    struct input_absinfo absI;
    int ret;
    int fd=-1;
    fd = open("/dev/input/event0",O_RDONLY);
    if(fd<0){
       perror("/dev/input/event0"); 
       return -1;
    }

   //得到X轴的abs信息
    ioctl(fd,EVIOCGABS(ABS_X),&absI);
    printf("x abs lastest value=%d\n",absI.value);
    printf("x abs min=%d\n",absI.minimum);
    printf("x abs max=%d\n",absI.maximum);

   //得到y轴的abs信息
    ioctl(fd,EVIOCGABS(ABS_Y),&absI);
    printf("y abs lastest value=%d\n",absI.value);
    printf("y abs min=%d\n",absI.minimum);
    printf("y abs max=%d\n",absI.maximum);

   //得到按压轴的abs信息
    ioctl(fd,EVIOCGABS(ABS_PRESSURE),&absI);
    printf("pressure abs lastest value=%d\n",absI.value);
    printf("pressure abs min=%d\n",absI.minimum);
    printf("pressure abs max=%d\n",absI.maximum);

    close(fd);

    report_event();

    return 0;
}
