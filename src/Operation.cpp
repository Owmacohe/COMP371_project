#include "Operation.h"

Operation::Operation(string n, TAPP::RenderModel *r1, TAPP::RenderModel *r2, string op, T3D::TTuple<double, 3> c, bool s)
    : name(n), rm1(r1), rm2(r2), operation(op), colour(c), save(s)  { }

void Operation::generate(TAPP::Virtual3DLayer *view) {
    bool union_operation = false;
    bool subtraction_operation = false;
    bool intersection_operation = false;
    bool difference_operation = false;

    if (operation == "+") union_operation = true;
    else if (operation == "-") subtraction_operation = true;
    else if (operation == "|") intersection_operation = true;
    else if (operation == "\\") difference_operation = true;

    if (union_operation) {
        rm1->colour = colour;
        rm2->colour = colour;

        result1 = rm1;
        view->m_objects.push_back(result1);

        result2 = rm2;
        view->m_objects.push_back(result2);
    }
    else if (subtraction_operation) subtraction(view);
    else if (intersection_operation) intersection(view);
    else if (difference_operation) difference(view);
}

void Operation::save_obj() {
    if (save) {
        ofstream myfile;
        myfile.open (name + ".obj");

        for (string v1 : result1->vertex_list) myfile << v1 << "\n";
        for (string v2 : result2->vertex_list) myfile << v2 << "\n";
        for (string f1 : result1->face_list) myfile << f1 << "\n";
        for (string f2 : result2->face_list) myfile << f2 << "\n";

        myfile.close();
    }
}

void Operation::subtraction(TAPP::Virtual3DLayer* view) {
    result1 = new TAPP::RenderModel("", rm1, colour, rm2, true, false, 0);
    view->m_objects.push_back(result1);

    result2 = new TAPP::RenderModel("", rm2, colour, rm1, false, true, rm1->m_obj.vertex.size());
    view->m_objects.push_back(result2);
}

void Operation::intersection(TAPP::Virtual3DLayer* view) {
    result1 = new TAPP::RenderModel("", rm1, colour, rm2, false, false, 0);
    view->m_objects.push_back(result1);

    result2 = new TAPP::RenderModel("", rm2, colour, rm1, false, false, rm1->m_obj.vertex.size());
    view->m_objects.push_back(result2);
}

void Operation::difference(TAPP::Virtual3DLayer* view) {
    result1 = new TAPP::RenderModel("", rm1, colour, rm2, true, false, 0);
    view->m_objects.push_back(result1);

    result2 = new TAPP::RenderModel("", rm2, colour, rm1, true, false, rm1->m_obj.vertex.size());
    view->m_objects.push_back(result2);
}