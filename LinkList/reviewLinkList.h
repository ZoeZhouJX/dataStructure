#ifndef __REVIEW_LINK_LIST_H_
#define __REVIEW_LINK_LIST_H_

#define ELEMENTTYPE void*

typedef struct LinkNode
{
    ELEMENTTYPE data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList
{
    LinkNode * head;
    LinkNode * tail;
    int len;
} LinkList;

// 链表初始化
int LinkListInit(LinkList **pList);

// 链表指定位置插入
int LinkListAppointPosInsert(LinkList *pList, int pos, ELEMENTTYPE val);

// 链表头插
int LinkListHeadInsert(LinkList *pList, ELEMENTTYPE val);

// 链表尾插
int LinkListTailInsert(LinkList *pList, ELEMENTTYPE val);

// 链表指定位置删
int LinkListDeleteAppointPos(LinkList *pList, int pos);

// 链表头删
int LinkListHeadDelete(LinkList *pList);

// 链表尾删
int LinkListTailDelete(LinkList *pList);

// 链表删除指定的数据
int LinkListDeleteAppointData(LinkList *pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

// 获取链表的长度
int LinkListGetLength(LinkList *pList, int *pSize);

// 链表的销毁
int LinkListDestroy(LinkList *pList);

// 链表遍历接口
int LinkListForeach(LinkList *pList, int (*printFunc)(ELEMENTTYPE));
#endif