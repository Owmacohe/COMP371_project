#include "Operation.h"

Operation::Operation(TAPP::RenderModel *r1, TAPP::RenderModel *r2, string op, T3D::TTuple<double, 3> c)
    : rm1(r1), rm2(r2), operation(op), colour(c) { }

void Operation::generate(TAPP::Virtual3DLayer *view) {
    bool union_operation = false;
    bool subtraction_operation = false;
    bool intersection_operation = false;
    bool difference_operation = false;

    if (operation == "+") union_operation = true;
    else if (operation == "-") subtraction_operation = true;
    else if (operation == "|") intersection_operation = true;
    else if (operation == "/") difference_operation = true;

    if (union_operation) {
        rm1->colour = colour;
        rm2->colour = colour;

        view->m_objects.push_back(rm1);
        view->m_objects.push_back(rm2);
    }
    else if (subtraction_operation) subtraction(view);
    else if (intersection_operation) intersection(view);
    else if (difference_operation) difference(view);
}

void Operation::subtraction(TAPP::Virtual3DLayer* view) {
    TAPP::RenderModel *subtract_1_2 = new TAPP::RenderModel("", rm1, colour, rm2, true, false);
    view->m_objects.push_back(subtract_1_2);

    TAPP::RenderModel *subtract_2_1 = new TAPP::RenderModel("", rm2, colour, rm1, false, true);
    view->m_objects.push_back(subtract_2_1);
}

void Operation::intersection(TAPP::Virtual3DLayer* view) {
    TAPP::RenderModel *intersect_1_2 = new TAPP::RenderModel("", rm1, colour, rm2, false, false);
    view->m_objects.push_back(intersect_1_2);

    TAPP::RenderModel *intersect_2_1 = new TAPP::RenderModel("", rm2, colour, rm1, false, false);
    view->m_objects.push_back(intersect_2_1);
}

void Operation::difference(TAPP::Virtual3DLayer* view) {
    TAPP::RenderModel *intersect_1_2 = new TAPP::RenderModel("", rm1, colour, rm2, true, false);
    view->m_objects.push_back(intersect_1_2);

    TAPP::RenderModel *intersect_2_1 = new TAPP::RenderModel("", rm2, colour, rm1, true, false);
    view->m_objects.push_back(intersect_2_1);
}