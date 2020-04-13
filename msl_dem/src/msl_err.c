#include "../inc/msl_err_codes.h"
#include "../inc/msl_err.h"

typedef struct{
    msl_err_t err_code;
    const char* err_code_string;
}msl_err_code_to_string_map_t;

static const char* MSL_ERR_CODE_UNDEFINED = "no defined err codes found";

const msl_err_code_to_string_map_t err_code_to_string_map_table[] = {
{
    MSL_FAIL,"MSL_FAIL"
},
{
    MSL_OK,"MSL_OK"
},
{
    MSL_PARAM_ERROR,"MSL_PARAM_ERROR: input parameters invalid"
},
{
    MSL_TEST_PASS,"PASS"
},
{
    MSL_TEST_FAIL,"+++++++++++++ FAIL !!!!! ++++++++++++"
},
{
    MSL_ULTRASONIC_LOCK_ACQUIRE_FAIL,"MSL_ULTRASONIC_LOCK_ACQUIRE_FAIL: Sensor lock acquire time out.Probably sensor locked/used by another task"
},
{
    MSL_ULTRASONIC_START_MEASUREMENT_NO_REPLY,"MSL_ULTRASONIC_START_MEASUREMENT_NO_REPLY: Sensor didn't respond for start measurement comand.Make sure the device is connected and check device connections and power."
},
{
    MSL_ULTRASONIC_SENSOR_MEASUREMENT_START_FAIL,"MSL_ULTRASONIC_SENSOR_MEASUREMENT_START_FAIL: Ultrasonic sensor node received the request, but din't start measurement"
},
{
    MSL_ULTRASONIC_MEASUREMENT_PROPERTIES_REGISTRATION_FAIL,"MSL_ULTRASONIC_MEASUREMENT_PROPERTIES_REGISTRATION_FAIL: Ultrasonic sensor started the measurement, but the measurement properties doesn't match with the requested properties"
},
{
    MSL_ULTRASONIC_MEASUREMENT_PROPERTIES_MISMATCH,"MSL_ULTRASONIC_MEASUREMENT_PROPERTIES_MISMATCH: parameters in measurement result does not match with measurement request. Pausible race codition in issuing commands"
},
{
    MSL_ULTRASONIC_MEASUREMENT_TIMEOUT,"MSL_ULTRASONIC_MEASUREMENT_TIMEOUT: Required time for measurement has ellapsed, but still ultrasonic node hasn't completed the measurement. Pausible sensor fault, try restarting."
},
{
    MSL_ULTRASONIC_MEASUREMENT_INVALID,"MSL_ULTRASONIC_MEASUREMENT_INVALID: Reading from sensor is invalid. Check connections and power to sensor. Pausible loose connection or sensor fault"
},
{
    MSL_ULTRASONIC_SENSOR_RANGE_OVERFLOW,"MSL_ULTRASONIC_SENSOR_RANGE_OVERFLOW: Sensor did not find closing of echo pulse withing range. Indication that the sensor didn't find any obstacle within range or sensor's one transducer is covered by an obstacle."
},
{
    MSL_ULTRASONIC_GET_STATUS_NO_REPLY,"MSL_ULTRASONIC_GET_STATUS_NO_REPLY: Sensor didn't respond for get status command"
},
{
    MSL_ULTRASONIC_GET_RAW_SAMPLES_NO_REPLY,"MSL_ULTRASONIC_GET_RAW_SAMPLES_NO_REPLY: Sensor didn't respond for get raw samples command"
},
{
    MSL_BUS_LOCK_ACQUIRE_FAIL,"MSL_BUS_LOCK_ACQUIRE_FAIL:  Bus is busy. Probably locked/used by another task "
},
{
    MSL_BUS_TX_DRIVER_FAIL,"MSL_BUS_TX_DRIVER_FAIL: low level TX driver failed"
},
{
    MSL_BUS_RX_DRIVER_FAIL,"MSL_BUS_RX_DRIVER_FAIL: low level RX driver failed"
},
{
    MSL_BUS_NO_ADDRESS_MATCH,"MSL_BUS_NO_ADDRESS_MATCH: no address match in received frame"
},
{
    MSL_BUS_PDULENERR,"MSL_BUS_PDULENERR: pdu length error,frame corroupted"
},
{
    MSL_BUS_CRCERR,"MSL_BUS_CRCERR: crc error, frame corroupted"
},
{
    MSL_BUS_MAXLENERR,"MSL_BUS_MAXLENERR: received frame length is larger then intended"
},
{
    MSL_BUS_MINLENERR,"MSL_BUS_MINLENERR: received frame length is smaller then intended. Frame corroupted"
},
{
    MSL_BUS_UNDEFINEDERR,"MSL_BUS_UNDEFINEDERR: undefined error"
},
{
    MSL_BUS_PID_MISMATCH,"MSL_BUS_PID_MISMATCH: pid in received frame doesn't match with expected pid"
},
{
    MSL_BUS_NO_REPLY,"MSL_BUS_NO_REPLY: the node didn't respond to a command. check connections and power to the node"
},
{
    MSL_BUS_PING_DATA_ERROR,"MSL_BUS_PING_DATA_ERROR: ping data is not same as echoed back data"
}
};

const char* msl_err_code_to_string(msl_err_t code){
    char* ret_val = (char*) MSL_ERR_CODE_UNDEFINED;
    for(uint32_t idx=0;idx< (sizeof(err_code_to_string_map_table)/sizeof(msl_err_code_to_string_map_t));idx++){
        if(err_code_to_string_map_table[idx].err_code == code){
            ret_val = (char*) err_code_to_string_map_table[idx].err_code_string;
            break;
        }
    }
    return (const char*)ret_val;
}
