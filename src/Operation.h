#pragma once

#include "TOGLApp.h"
#include "Virtual3DLayer.h"
#include "RenderModel.h"

class Operation {
public:
    Operation(TAPP::RenderModel*, TAPP::RenderModel*, string, T3D::TTuple<double, 3>);

    void generate(TAPP::Virtual3DLayer*);
private:
    void subtraction(TAPP::Virtual3DLayer*);
    void intersection(TAPP::Virtual3DLayer*);
    void difference(TAPP::Virtual3DLayer*);

    TAPP::RenderModel *rm1, *rm2;
    string operation;
    T3D::TTuple<double, 3> colour;
};