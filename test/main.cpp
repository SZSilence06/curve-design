 #include "../src/alg/CurveGenerator.h"
#include <fstream>

void generate_test_data_1(std::vector<CurveGenerator::Point>& a, std::vector<CurveGenerator::Point>& b,
                        std::vector<CurveGenerator::Point>& c, std::vector<bool>& result)
{
    //test case 0
    CurveGenerator::Point a1,b1,c1;
    a1.a = 0;
    a1.b = -1;
    a1.t = 1;
    a.push_back(a1);

    b1.a = 1;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 2;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(true);

    //test case 1
    a1.a = 0;
    a1.b = -1;
    a1.t = 1;
    a.push_back(a1);

    b1.a = 1;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 5;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(false);

    //test case 2
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.5;
    a.push_back(a1);

    b1.a = 1;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 2;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(true);

    //test case 3
    a1.a = 0;
    a1.b = -1;
    a1.t = 1;
    a.push_back(a1);

    b1.a = 1;
    b1.b = 2;
    b1.t = 0.7;
    b.push_back(b1);

    c1.a = 0;
    c1.b = 2;
    c1.t = 0.5;
    c.push_back(c1);

    result.push_back(true);

    //test case 4
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.3;
    a.push_back(a1);

    b1.a = 0;
    b1.b = 2;
    b1.t = 0.6;
    b.push_back(b1);

    c1.a = 1;
    c1.b = 2;
    c1.t = 0.3;
    c.push_back(c1);

    result.push_back(true);

    //test case 5
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.3;
    a.push_back(a1);

    b1.a = 0;
    b1.b = 1;
    b1.t = 0.6;
    b.push_back(b1);

    c1.a = 1;
    c1.b = 2;
    c1.t = 0.3;
    c.push_back(c1);

    result.push_back(true);

    //test case 6
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.5;
    a.push_back(a1);

    b1.a = 0;
    b1.b = 1;
    b1.t = 0.6;
    b.push_back(b1);

    c1.a = 0;
    c1.b = 1;
    c1.t = 0.3;
    c.push_back(c1);

    result.push_back(true);

    //test case 7
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.3;
    a.push_back(a1);

    b1.a = 0;
    b1.b = 2;
    b1.t = 0.6;
    b.push_back(b1);

    c1.a = 1;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(true);

    //test case 8
    a1.a = 1;
    a1.b = -1;
    a1.t = 1;
    a.push_back(a1);

    b1.a = 0;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 0;
    c1.b = 1;
    c1.t = 0.3;
    c.push_back(c1);

    result.push_back(true);

    //test case 9
    a1.a = 1;
    a1.b = 2;
    a1.t = 0.5;
    a.push_back(a1);

    b1.a = 1;
    b1.b = 0;
    b1.t = 0.5;
    b.push_back(b1);

    c1.a = 1;
    c1.b = 5;
    c1.t = 0.5;
    c.push_back(c1);

    result.push_back(false);

    //test case 10
    a1.a = 1;
    a1.b = 2;
    a1.t = 0.5;
    a.push_back(a1);

    b1.a = 1;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 1;
    c1.b = 5;
    c1.t = 0.5;
    c.push_back(c1);

    result.push_back(false);

    //test case 11
    a1.a = 2;
    a1.b = -1;
    a1.t = 1;
    a.push_back(a1);

    b1.a = 1;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 5;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(false);

    //test case 12
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.5;
    a.push_back(a1);

    b1.a = 1;
    b1.b = -1;
    b1.t = 1;
    b.push_back(b1);

    c1.a = 5;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(false);

    //test case 13
    a1.a = 0;
    a1.b = 1;
    a1.t = 0.5;
    a.push_back(a1);

    b1.a = 0;
    b1.b = 1;
    b1.t = 0.4;
    b.push_back(b1);

    c1.a = 5;
    c1.b = -1;
    c1.t = 1;
    c.push_back(c1);

    result.push_back(false);
}

void test_inSameFace(CurveGenerator& generator)
{
    std::vector<CurveGenerator::Point> a, b, c;
    std::vector<bool> result;
    generate_test_data_1(a, b, c, result);

    for(int i = 0; i < a.size(); i++)
    {
        if(generator.inSameFace(a[i], b[i], c[i]) == result[i])
        {
            std::cout << "Test case " << i << " passed." << std::endl;
        }
        else
        {
            std::cout << "Test case " << i << " failed!" << std::endl;
        }
    }
}

void test_howManyRing(const Mesh& mesh)
{
    assert(mesh.howManyRing(0,3) == 2);
    assert(mesh.howManyRing(0,1) == 1);
    assert(mesh.howManyRing(0,0) == 0);
    assert(mesh.howManyRing(0,8) == 4);
}

int main()
{
    matrixr_t vertices;
    matrixs_t faces;
    jtf::mesh::load_obj("/home/zju/Desktop/sphere.obj", faces, vertices);

    Mesh mesh(vertices, faces);
    CurveGenerator generator(mesh);

    //test_inSameFace(generator);

    test_howManyRing(mesh);

    return 0;
}
