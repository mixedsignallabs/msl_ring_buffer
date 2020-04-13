#include <stdio.h>
#include <stdlib.h>
#include "msl_ring_buffer/msl_ring_buffer.h"
#include "msl_ring_buffer/msl_err.h"

size_t size_var;
MSL_RB_HANDLE rb_handle;
uint8_t test_buff[10];
size_t write_length;
uint8_t byte_val = 200;

void UT_msl_rb_init(){
    MSL_TEST_BANNER_API(msl_rb_init())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,0,0,NULL),MSL_PARAM_ERROR);
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
}

void UT_msl_rb_is_empty(){
    MSL_TEST_BANNER_API(msl_rb_is_empty())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(msl_rb_is_empty(NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_OK)
}

void UT_msl_rb_get_num_elements(){
    MSL_TEST_BANNER_API(msl_rb_get_num_elements())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(msl_rb_get_num_elements(NULL,NULL),MSL_PARAM_ERROR);
    MSL_TEST_PRINT(msl_rb_get_num_elements(NULL,&size_var),MSL_PARAM_ERROR);
    MSL_TEST_PRINT(msl_rb_get_num_elements(&rb_handle,NULL),MSL_PARAM_ERROR);
    MSL_TEST_PRINT(msl_rb_get_num_elements(&rb_handle,&size_var),MSL_OK);
    MSL_TEST_VAL_PRINT(size_var,0)

    for(uint8_t i=0;i<10;i++){
        __msl_rb_put(&rb_handle,i);
        msl_rb_get_num_elements(&rb_handle,&size_var);
            MSL_TEST_VAL_PRINT(size_var,i+1)
    }

    for(uint8_t i=0;i<2;i++){
        __msl_rb_put(&rb_handle,i+20);
        msl_rb_get_num_elements(&rb_handle,&size_var);
            MSL_TEST_VAL_PRINT(size_var,10)
    }

    uint8_t temp_byte;
    for(uint8_t i=0;i<10;i++){
        __msl_rb_get(&rb_handle,&temp_byte);
        msl_rb_get_num_elements(&rb_handle,&size_var);
            MSL_TEST_VAL_PRINT(size_var,10-i-1)
    }

    msl_rb_get_num_elements(&rb_handle,&size_var);
    MSL_TEST_VAL_PRINT(size_var,0)

    msl_rb_deinit(&rb_handle);
    msl_rb_init(&rb_handle,10,1,(void*)test_buff);
    for(uint8_t i=0;i<10;i++){
        __msl_rb_put_no_overwrite(&rb_handle,i);
        msl_rb_get_num_elements(&rb_handle,&size_var);
            MSL_TEST_VAL_PRINT(size_var,i+1)
    }

    for(uint8_t i=0;i<2;i++){
        __msl_rb_put(&rb_handle,i+20);
        msl_rb_get_num_elements(&rb_handle,&size_var);
            MSL_TEST_VAL_PRINT(size_var,10)
    }
    for(uint8_t i=0;i<10;i++){
        __msl_rb_get(&rb_handle,&temp_byte);
        msl_rb_get_num_elements(&rb_handle,&size_var);
            MSL_TEST_VAL_PRINT(size_var,10-i-1)
    }

    msl_rb_get_num_elements(&rb_handle,&size_var);
    MSL_TEST_VAL_PRINT(size_var,0)

}

typedef struct{
    uint16_t val;
    uint32_t val_2;
}test_element_t;

test_element_t element_list[5];

test_element_t temp_element;

void UT_msl_rb_put_element(){
    MSL_TEST_BANNER_API(msl_rb_put_element())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,5,sizeof(test_element_t),(void*)element_list),MSL_OK);
    MSL_TEST_PRINT(msl_rb_put_element(NULL,NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_put_element(NULL,(void*)test_buff),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_put_element(&rb_handle,NULL),MSL_PARAM_ERROR)
    for(uint8_t idx=0;idx<5;idx++){
        temp_element.val_2 = idx;
        MSL_TEST_PRINT(msl_rb_put_element(&rb_handle,(void*)&temp_element),MSL_OK)
    }

    for(uint8_t idx=0;idx<5;idx++){
        MSL_TEST_PRINT(msl_rb_get_element(&rb_handle,(void*)&temp_element),MSL_OK)
        printf("    expected: %d got: %d\r\n",idx,temp_element.val_2);
    }

    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_TRUE)

    printf("\r\n    over write test    \r\n");
    for(uint8_t idx=0;idx<20;idx++){
        temp_element.val_2 = idx;
        MSL_TEST_PRINT(msl_rb_put_element(&rb_handle,(void*)&temp_element),MSL_OK)
    }
    MSL_TEST_PRINT(msl_rb_is_full(&rb_handle),MSL_TRUE)

    for(uint8_t idx=15;idx<20;idx++){
        MSL_TEST_PRINT(msl_rb_get_element(&rb_handle,(void*)&temp_element),MSL_OK)
        printf("    expected: %d got: %d\r\n",idx,temp_element.val_2);
    }
}

void UT_msl_rb_get_element(){
    MSL_TEST_BANNER_API(msl_rb_get_element())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(msl_rb_get_element(NULL,NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_get_element(NULL,(void*)test_buff),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_get_element(&rb_handle,NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_get_element(&rb_handle,(void*)test_buff),MSL_OK)
}

void UT_msl_rb_put_element_no_overwrite(){
    MSL_TEST_BANNER_API(msl_rb_put_element_no_overwrite())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,5,sizeof(test_element_t),(void*)element_list),MSL_OK);
    MSL_TEST_PRINT(msl_rb_put_element_no_overwrite(NULL,NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_put_element_no_overwrite(NULL,(void*)test_buff),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_put_element_no_overwrite(&rb_handle,NULL),MSL_PARAM_ERROR)
    for(uint8_t idx=0;idx<5;idx++){
        temp_element.val_2 = idx;
        MSL_TEST_PRINT(msl_rb_put_element_no_overwrite(&rb_handle,(void*)&temp_element),MSL_OK)
    }

    for(uint8_t idx=0;idx<5;idx++){
        MSL_TEST_PRINT(msl_rb_get_element(&rb_handle,(void*)&temp_element),MSL_OK)
        printf("    expected: %d got: %d\r\n",idx,temp_element.val_2);
    }

    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_TRUE)

    printf("\r\n    over write test    \r\n");
    for(uint8_t idx=0;idx<20;idx++){
        temp_element.val_2 = idx;
        if(idx<=4){
            MSL_TEST_PRINT(msl_rb_put_element_no_overwrite(&rb_handle,(void*)&temp_element),MSL_OK)
        }else{
            MSL_TEST_PRINT(msl_rb_put_element_no_overwrite(&rb_handle,(void*)&temp_element),MSL_FULL)
        }
    }
    MSL_TEST_PRINT(msl_rb_is_full(&rb_handle),MSL_TRUE)

    for(uint8_t idx=0;idx<5;idx++){
        MSL_TEST_PRINT(msl_rb_get_element(&rb_handle,(void*)&temp_element),MSL_OK)
        printf("    expected: %d got: %d\r\n",idx,temp_element.val_2);
    }
}

void UT___msl_rb_put(){
    MSL_TEST_BANNER_API(__msl_rb_put())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(__msl_rb_put(NULL,byte_val),MSL_PARAM_ERROR)

    for(uint8_t i=0;i<10;i++){
        __msl_rb_put(&rb_handle,i);
    }
    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_FALSE)

    uint8_t temp;
    for(uint8_t i=0;i<10;i++){
        MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_OK)
        MSL_TEST_VAL_PRINT(temp,i)
    }
    printf("\r\r\r\n    overwrite the contents test\r\n\r\n");
    for(uint8_t i=0;i<20;i++){
        __msl_rb_put(&rb_handle,i);
    }
    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_FALSE)

    for(uint8_t i=0;i<10;i++){
        MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_OK)
        MSL_TEST_VAL_PRINT(temp,10+i)
    }

    MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_EMPTY)
    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_TRUE)

}

void UT___msl_rb_get(){
    MSL_TEST_BANNER_API(__msl_rb_get())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(__msl_rb_get(NULL,NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(__msl_rb_get(NULL,&byte_val),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(__msl_rb_get(&rb_handle,NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&byte_val),MSL_EMPTY)
}

void UT___msl_rb_put_no_overwrite(){
    MSL_TEST_BANNER_API(__msl_rb_put_no_overwrite())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(__msl_rb_put_no_overwrite(NULL,byte_val),MSL_PARAM_ERROR)

    for(uint8_t i=0;i<11;i++){
        if(i>9){
        printf("    MSL_FULL TEST");
        MSL_TEST_PRINT(__msl_rb_put_no_overwrite(&rb_handle,i),MSL_FULL)
        }else{
        MSL_TEST_PRINT(__msl_rb_put_no_overwrite(&rb_handle,i),MSL_OK)

        }
    }
    uint8_t temp;
    for(uint8_t i=0;i<10;i++){
        MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_OK)
        MSL_TEST_VAL_PRINT(temp,i)
    }

    MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_EMPTY)

    printf("\r\r\r\n    overwrite the contents test\r\n\r\n");
    for(uint8_t i=0;i<20;i++){
        __msl_rb_put_no_overwrite(&rb_handle,i);
    }
    MSL_TEST_PRINT(msl_rb_is_empty(&rb_handle),MSL_FALSE)

    for(uint8_t i=0;i<10;i++){
        MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_OK)
        MSL_TEST_VAL_PRINT(temp,i)
    }

    MSL_TEST_PRINT(__msl_rb_get(&rb_handle,&temp),MSL_EMPTY)
}

void UT_msl_rb_is_full(){
    MSL_TEST_BANNER_API(msl_rb_is_full())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(msl_rb_is_full(NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_is_full(&rb_handle),MSL_FALSE)

    for(uint8_t i=0;i<10;i++){
        __msl_rb_put(&rb_handle,i);
        if(i<9){
        MSL_TEST_PRINT(msl_rb_is_full(&rb_handle),MSL_FALSE)
        }else{
            MSL_TEST_PRINT(msl_rb_is_full(&rb_handle),MSL_TRUE)
        }
    }

    MSL_TEST_PRINT(msl_rb_is_full(&rb_handle),MSL_TRUE)

}

void UT_msl_rb_deinit(){
    MSL_TEST_BANNER_API(msl_rb_deinit())
    MSL_TEST_PRINT(msl_rb_init(&rb_handle,10,1,(void*)test_buff),MSL_OK);
    MSL_TEST_PRINT(msl_rb_deinit(NULL),MSL_PARAM_ERROR)
    MSL_TEST_PRINT(msl_rb_deinit(&rb_handle),MSL_OK)
}

int main()
{
    UT_msl_rb_init();

    UT_msl_rb_get_element();
    UT_msl_rb_put_element();
    UT_msl_rb_put_element_no_overwrite();

    UT_msl_rb_get_num_elements();

    UT_msl_rb_is_empty();

    UT___msl_rb_put();
    UT___msl_rb_get();
    UT___msl_rb_put_no_overwrite();

    UT_msl_rb_is_full();
    UT_msl_rb_deinit();



}

