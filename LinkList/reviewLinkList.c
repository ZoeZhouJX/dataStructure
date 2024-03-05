#include "reviewLinkList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// 状态码 
enum STATUS_CODE 
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

static int LinkListAccordAppointValGetPos(LinkList *pList, ELEMENTTYPE val, int *pPos, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));


// 链表初始化
int LinkListInit(LinkList **pList)
{
    LinkList *list = (LinkList *)malloc(sizeof(LinkList) * 1);
    if (list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(LinkList) * 1);

    list->head = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(LinkNode) * 1);

    list->head->data = 0;
    list->head->next = NULL;

    list->tail = list->head;

    list->len = 0;

    *pList = list;

    return ON_SUCCESS;
}

// 链表指定位置插入
int LinkListAppointPosInsert(LinkList *pList, int pos, ELEMENTTYPE val)
{
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(LinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;

    newNode->data = val;

    LinkNode *travelNode = pList->head;

    int flag = 0;
    if (pos == pList->len)
    {
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
    }
    newNode->next = travelNode->next;
    travelNode->next = newNode;

    if (flag)
    {
        pList->tail = newNode;
    }

    (pList->len)++;

    return ON_SUCCESS;
}

// 链表头插
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, 0, val);
}

// 链表尾插
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE val)
{
    return LinkListAppointPosInsert(pList, pList->len, val);
}

// 链表指定位置删
int LinkListDeleteAppointPos(LinkList *pList, int pos)
{
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    LinkNode * travelNode = pList->head;

    LinkNode *needDelNode = NULL;

    int flat = 0;
    if (pos == pList->len)
    {
        flat = 1;
    }

    while (--pos)
    {
        travelNode = travelNode->next;
    }

    needDelNode = travelNode->next;
    travelNode->next = needDelNode->next;

    if (flat)
    {
        pList->tail = travelNode;
    }

    if (needDelNode == NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    (pList->len)--;

    return ON_SUCCESS;

}

// 链表头删
int LinkListHeadDelete(LinkList *pList)
{
    return LinkListDeleteAppointPos(pList, 1);
}

// 链表尾删
int LinkListTailDelete(LinkList *pList)
{
    return LinkListDeleteAppointPos(pList, pList->len);
}

// 根据指定的元素得到在链表中所在的位置
static int LinkListAccordAppointValGetPos(LinkList *pList, ELEMENTTYPE val, int *pPos, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    int pos = 1;
    LinkNode *travelNode = pList->head->next;

    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = compareFunc(val, travelNode->data);
        if (cmp == 1)
        {
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }

    *pPos = NOT_FIND;

    return NOT_FIND;
}

// 链表删除指定的数据
int LinkListDeleteAppointData(LinkList *pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    int pos = 0;
    int size = 0;
    
    while (LinkListGetLength(pList, &size) && pos != NOT_FIND)
    {
        LinkListAccordAppointValGetPos(pList, val, &pos, compareFunc);
        LinkListDeleteAppointPos(pList, pos);
    }

    return ON_SUCCESS;
}

// 获取链表的长度
int LinkListGetLength(LinkList *pList, int *pSize)
{
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    if (pSize)
    {
        *pSize = pList->len;
    }

    return pList->len;
}

// 链表的销毁
int LinkListDestroy(LinkList *pList)
{
    int size = 0;
    while (LinkListGetLength(pList, &size))
    {
        LinkListHeadDelete(pList);
    }

    if (pList->head != NULL)
    {
        free(pList->head);
        pList->head = NULL;
        pList->tail = NULL;
    }

    return ON_SUCCESS;
}

// 链表遍历接口
int LinkListForeach(LinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    if (pList == NULL)
    {
        return NULL_PTR;
    }

    LinkNode *travelNode = pList->head->next;

    while (travelNode != NULL)
    {
        printFunc(travelNode->data);
        travelNode = travelNode->next;
    }

    return ON_SUCCESS;
}