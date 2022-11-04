#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glut.h>

struct color
{
    std::string material;
    int r, g, b;
};

struct vertex
{
    float x, y, z;
};

struct poly
{
    std::vector<int> comp;
};

struct miniObj
{
    color c;
    std::string name;
    std::vector<poly> faces;
};

struct object
{
    std::vector<vertex> vertices;
    std::vector<miniObj> minO;
};

std::vector<color> materiales;
void loadColors(char *fname)
{
    std::ifstream my_file;
    my_file.open(fname);
    
    std::string line;
    color aux;
    float r, g, b;
    
    while (my_file >> line)
    {
        if (line == "newmtl")
        {
            my_file >> line;
            aux.material = line;
        }
        if (line == "Kd")
        {
            my_file >> r >> g >> b;
            aux.r = r * 255;
            aux.g = g * 255;
            aux.b = b * 255;
            materiales.push_back(aux);
        }
    }
    my_file.close();
}

GLuint loadObj(char *fname, char *mname)
{
    object obj;
    std::ifstream my_file;
    my_file.open(fname);

    GLuint objGL = glGenLists(1);
    glPointSize(2.0);

    std::string line;
    float x, y, z;
    vertex vr;
    int i1, i2, i3, i4;
    int contador = -1;
    miniObj aux;
    vertex auxV;
    poly auxP;
    loadColors(mname);
    while (my_file >> line)
    {
        if (line == "g")
        {
            my_file >> line;
            aux.name = line;
            obj.minO.push_back(aux);
            contador++;
        }
        if (line == "v")
        {
            my_file >> x >> y >> z;
            auxV.x = x;
            auxV.y = y;
            auxV.z = z;
            obj.vertices.push_back(auxV);
        }
        if (line == "f")
        {
            my_file >> i1 >> i2 >> i3;
            auxP.comp.push_back(i1);
            auxP.comp.push_back(i2);
            auxP.comp.push_back(i3);
            obj.minO[contador].faces.push_back(auxP);
            auxP.comp.clear();
        }
        if (line == "usemtl")
        {
            my_file >> line;
            for (auto cl : materiales)
            {
                if (cl.material == line)
                {
                    obj.minO[contador].c = cl;
                }
            }
        }
    }
    my_file.close();
    glNewList(objGL, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_TRIANGLES);
        for (auto mO : obj.minO)
        {
            glColor3ub(mO.c.r, mO.c.g, mO.c.b);
            for (auto f : mO.faces)
            {
                for (auto p : f.comp)
                {
                    glVertex3f(obj.vertices[p - 1].x, obj.vertices[p - 1].y, obj.vertices[p - 1].z);
                }
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    materiales.clear();
    return objGL;
}