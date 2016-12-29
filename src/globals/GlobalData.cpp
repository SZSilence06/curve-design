#include "GlobalData.h"

GlobalData* GlobalData::instance = nullptr;

GlobalData::GlobalData()
{

}

GlobalData::~GlobalData()
{

}

GlobalData* GlobalData::getInstance()
{
    if(instance == nullptr)
    {
        instance = new GlobalData();
    }
    return instance;
}
