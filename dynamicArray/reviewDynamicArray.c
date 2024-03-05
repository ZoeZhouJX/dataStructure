#include "reviewDynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_SIZE 20

static int expandDynamicCapacity(dynamicArray *pArray);
static int shrinkDynamicCapacity(dynamicArray *pArray);

    enum STATUS_CODE {
        ON_SUCCESS,
        NULL_PTR,
        MALLOC_ERROR,
        INVALID_ACCESS,
    };

#define JUDGING_EMPTINESS(pArray)    \
    do{                              \
        if (pArray == NULL)          \
        {                            \
            return NULL_PTR;         \
        }                            \
    } while (0);                     \

#define JUDGING_LEGITIMACY(pos)            \
    do{                                    \
        if (pos < 0 || pos > pArray->len)  \
        {                                  \
            return INVALID_ACCESS;         \
        }                                  \
    } while (0);                           \

//动态数组的初始化
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    JUDGING_EMPTINESS(pArray);

    if (capacity <= 0)
    {
        capacity = DEFAULT_SIZE;
    }

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);

    pArray->len = 0;
    pArray->capacity = capacity;

    return ON_SUCCESS;
}

//动态数组扩容
static int expandDynamicCapacity(dynamicArray *pArray)
{
    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1) ;

    ELEMENTTYPE *tmpPtr = pArray->data;

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needExpandCapacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }

    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }

    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }

    pArray->capacity = needExpandCapacity;

    return 0;
}

//动态数组插入数据，在指定位置插入
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val)
{
    JUDGING_EMPTINESS(pArray);

    JUDGING_LEGITIMACY(pArray);

    if ((pArray->len + (pArray->len >> 1)) >= pArray->capacity)
    {
        expandDynamicCapacity(pArray);
    }

    for (int idx = pArray->len; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }

    pArray->data[pos] = val;

    (pArray->len)++;

    return ON_SUCCESS;
}

//动态数组插入数据(默认插到数组的末尾)
int dynamicArrayInsertData(dynamicArray *pArray, ELEMENTTYPE val)
{
    return dynamicArrayAppointPosInsertData(pArray, pArray->len, val);
}

//动态数组修改指定位置的数据
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, int pos, ELEMENTTYPE val)
{
    JUDGING_EMPTINESS(pArray);

    JUDGING_LEGITIMACY(pArray);

    pArray->data[pos] = val;

    return ON_SUCCESS;
}

//动态数组缩容
static int shrinkDynamicCapacity(dynamicArray *pArray)
{
    int needShrinkDynamicCapacity = pArray->capacity - (pArray->capacity >> 1);

    ELEMENTTYPE *tmpPtr = pArray->data;

    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needShrinkDynamicCapacity);
    JUDGING_EMPTINESS(pArray);

    for (int idx = 0; idx < pArray->len; idx ++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }

    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }

    pArray->capacity = needShrinkDynamicCapacity;

    return ON_SUCCESS;

}

//动态数组删除指定位置数据
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos)
{
    JUDGING_EMPTINESS(pArray);

    JUDGING_LEGITIMACY(pArray);

    if (pArray->capacity >= (pArray->len - pArray->len >> 1))
    {
        shrinkDynamicCapacity(pArray);
    }

    for (int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }

    (pArray->len)--;

    return ON_SUCCESS;

}

//动态数组删除数据（默认情况下删除最后末尾的数据）
int dynamicArrayDeletedata(dynamicArray *pArray)
{
    return dynamicArrayDeleteAppointPosData(pArray, pArray->len - 1);
}

int compareData(void *arg1, void *arg2)
{
    int num1 = *(int *)arg1;
    int num2 = *(int *)arg2;

    return num1 == num2 ? 1 : 0;
}

//动态数组删除指定的元素
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2))
{
    for (int idx = pArray->len - 1; idx >= 0; idx--)
    {
        int ret = compareFunc(val, pArray->data[idx]);
        if (ret == 1)
        dynamicArrayDeleteAppointPosData(pArray, idx);
    }
    return ON_SUCCESS;
}

//动态数组的销毁
int dynamicArrayDestroy(dynamicArray *pArray)
{
    JUDGING_EMPTINESS(pArray);

    if (pArray->data != NULL)
    {
        free(pArray->data);
        pArray->data = NULL;
    }

    return ON_SUCCESS;
}

//获取数组的大小
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize)
{
    JUDGING_EMPTINESS(pArray);

    if (pSize != NULL)
    {
        *pSize = pArray->len;
    }
    return ON_SUCCESS;
}

//获取数组的容量
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity)
{
    JUDGING_EMPTINESS(pArray);

    if (pCapacity != NULL)
    {
        *pCapacity = pArray->capacity;
    }
    return ON_SUCCESS;
}

//获取指定位置的元素数据
int dynamicArrayGetAppointPosVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal)
{
    JUDGING_EMPTINESS(pArray);
    JUDGING_LEGITIMACY(pArray);

    if (pVal)
    {
        *pVal = pArray->data[pos];
    }

    return ON_SUCCESS;
}