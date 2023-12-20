#ifndef __REVIEW_DYNAMIC_ARRAY_H_
#define __REVIEW_DYNAMIC_ARRAY_H_

#define ELEMENTTYPE void*

typedef struct dynamicArray
{
    ELEMENTTYPE *data;
    int len;
    int capacity;
} dynamicArray;

//动态数组的初始化
int dynamicArrayInit(dynamicArray *pArray, int capacity);

//动态数组插入数据，在指定位置插入
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val);

// 动态数组插入数据(默认插到数组的末尾)
int dynamicArrayInsertData(dynamicArray *pArray, ELEMENTTYPE val);

// 动态数组修改指定位置的数据
int dynamicArrayModifyAppointPosData(dynamicArray *Array, int pos, ELEMENTTYPE val);

// 动态数组删除指定位置数据
int dynamicArrayDeleteAppointData(dynamicArray *pArray, int pos);

// 动态数组删除数据（默认情况下删除最后末尾的数据）


#endif