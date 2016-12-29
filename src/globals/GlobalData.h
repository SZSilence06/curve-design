#pragma once

#include <zjucad/matrix/matrix.h>
#include <vector>
#include "../alg/Mesh.h"

using namespace zjucad::matrix;

class GlobalData
{
public:
    std::vector<size_t> control_points_;

private:
    static GlobalData* instance;

public:
    GlobalData();
    virtual ~GlobalData();

    static GlobalData* getInstance();
};
