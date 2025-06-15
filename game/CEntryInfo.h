#pragma once

class CEntryInfoNode
{
public:
    void* list;
    void* listnode;
    void* sector;
    CEntryInfoNode* prev;
    CEntryInfoNode* next;
};

class CEntryInfoList
{
public:
    CEntryInfoNode* first;
};