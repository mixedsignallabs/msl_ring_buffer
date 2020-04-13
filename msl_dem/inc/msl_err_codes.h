#include <stdint.h>

#define MSL_FAIL 0U
#define MSL_OK  1U
#define MSL_PASS 1U
#define MSL_TRUE MSL_OK
#define MSL_FALSE MSL_FAIL

#define MSL_PARAM_ERROR 2U /*! input parameters invalid */

#define MSL_ASSERT_SUCCESS 3U
#define MSL_ASSERT_FAIL 4U

#define MSL_TEST_PASS 5U
#define MSL_TEST_FAIL 6U

#define MSL_FULL    7U
#define MSL_EMPTY 8U

#define MSL_SYS_ERR_L0 0XFF00U  /*! System can continue working.Fixable error */
#define MSL_SYS_ERR_L1 0XFF01U  /*! System can continue working with limited functionality */
#define MSL_SYS_ERR_L2 0XFF02U  /*! System cannot continue working */

#define MSL_BUS_LOCK_ACQUIRE_FAIL 0XFD00u /*! Bus is busy. Probably locked/used by another task */
#define MSL_BUS_TX_DRIVER_FAIL 0XFD01u /*! low level TX driver failed */
#define MSL_BUS_RX_DRIVER_FAIL 0XFD02u /*! low level RX driver failed */
#define MSL_BUS_NO_ADDRESS_MATCH 0XFD03u /*! no address match in received frame */
#define MSL_BUS_PDULENERR  0XFD04u /*! pdu length error,frame corroupted */
#define MSL_BUS_CRCERR 0XFD05 /*! crc error, frame corroupted */
#define MSL_BUS_MAXLENERR 0xFD06 /*! received frame length is larger then intended. Frame corroupted */
#define MSL_BUS_MINLENERR 0xFD07 /*! received frame length is smaller then intended. Frame corroupted */
#define MSL_BUS_UNDEFINEDERR 0XFD08 /*! undefined error */
#define MSL_BUS_PID_MISMATCH 0xFD09 /*! pid in received frame doesn't match with expected pid */
#define MSL_BUS_NO_REPLY 0XFD0A /*! the node didn't respond to a command. check connections and power to the node */
#define MSL_BUS_PING_DATA_ERROR 0XFD0B /*! ping data is not same as echoed back data */

#define MSL_ULTRASONIC_LOCK_ACQUIRE_FAIL 0xFE00u /*! Sensor lock acquire time out.Probably sensor locked/used by another task */
#define MSL_ULTRASONIC_START_MEASUREMENT_NO_REPLY 0XFE01u    /*! Sensor didn't respond for start measurement comand */
#define MSL_ULTRASONIC_SENSOR_MEASUREMENT_START_FAIL 0xFE02u /*! Ultrasonic sensor node received the request, but din't start measurement */
#define MSL_ULTRASONIC_MEASUREMENT_PROPERTIES_REGISTRATION_FAIL 0xFE03u /*! Ultrasonic sensor started the measurement, but the measurement properties doesn't match with the requested properties */
#define MSL_ULTRASONIC_MEASUREMENT_PROPERTIES_MISMATCH 0xFE04u /*! parameters in measurement result does not match with measurement request */
#define MSL_ULTRASONIC_MEASUREMENT_TIMEOUT 0xFE05u /*! Required time for measurement has ellapsed, but still ultrasonic node hasn't completed the measurement */
#define MSL_ULTRASONIC_MEASUREMENT_INVALID 0xFE06u /*! Reading from sensor is invalid. Check connections and power to sensor. Pausible loose connection or sensor fault */
#define MSL_ULTRASONIC_SENSOR_RANGE_OVERFLOW 0XFE07u /*! Sensor did not find closing of echo pulse withing range. Indication that the sensor didn't find any obstacle within range or sensor's one transducer is covered by an obstacle. */
#define MSL_ULTRASONIC_GET_STATUS_NO_REPLY 0XFE08u /*! Sensor didn't respond for get status command */
#define MSL_ULTRASONIC_GET_RAW_SAMPLES_NO_REPLY 0XFE09 /*! Sensor didn't respond for get raw samples command */
