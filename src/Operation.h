#pragma once

#include "TOGLApp.h"
#include "Virtual3DLayer.h"
#include "RenderModel.h"

class Operation {
public:
    Operation(string, TAPP::RenderModel*, TAPP::RenderModel*, string, T3D::TTuple<double, 3>, bool);

    void generate(TAPP::Virtual3DLayer*);
    void save_obj();
private:
    void subtraction(TAPP::Virtual3DLayer*);
    void intersection(TAPP::Virtual3DLayer*);
    void difference(TAPP::Virtual3DLayer*);

    string name;
    bool save;
    TAPP::RenderModel *rm1, *rm2, *result1, *result2;
    string operation;
    T3D::TTuple<double, 3> colour;
};