#include <iostream>
#include "TOGLApp.h"

#include "Virtual3DLayer.h"

#include "RenderModel.h"

using namespace TAPP;
using namespace std;

std::string global_path;

void subtraction(RenderModel *rm1, RenderModel *rm2, T3D::TTuple<double, 3> colour, Virtual3DLayer* view) {
    RenderModel *subtract_1_2 = new RenderModel(rm1, colour, rm2, true, false);
    view->m_objects.push_back(subtract_1_2);

    RenderModel *subtract_2_1 = new RenderModel(rm2, colour, rm1, false, true);
    view->m_objects.push_back(subtract_2_1);
}

void intersection(RenderModel *rm1, RenderModel *rm2, T3D::TTuple<double, 3> colour, Virtual3DLayer* view) {
    RenderModel *intersect_1_2 = new RenderModel(rm1, colour, rm2, false, false);
    view->m_objects.push_back(intersect_1_2);

    RenderModel *intersect_2_1 = new RenderModel(rm2, colour, rm1, false, false);
    view->m_objects.push_back(intersect_2_1);
}

void difference(RenderModel *rm1, RenderModel *rm2, T3D::TTuple<double, 3> colour, Virtual3DLayer* view) {
    RenderModel *intersect_1_2 = new RenderModel(rm1, colour, rm2, true, false);
    view->m_objects.push_back(intersect_1_2);

    RenderModel *intersect_2_1 = new RenderModel(rm2, colour, rm1, true, false);
    view->m_objects.push_back(intersect_2_1);
}

int main(int argc, char* argv[]) {
    if (argc == 0) {
        cout << "Usage: " << argv[0] << " objname.obj" << endl;
        return -1;
    }
    
    int w = 1024;
    int h = 768;
    
    std::string name = "Owen Hellum - COMP 371 CSG Project";
    
    if (!gapp.initialize(w, h, name)) {
        cout << "Unable to initialize!" << endl;
        return -1;
    }
    
    Virtual3DLayer* view = new Virtual3DLayer(w, h);
    gapp.m_window.m_layers.push_back(view);

    int current = 0;
    int params = argc - 1;

    std::string model1 = argv[1];
    float model1_scale = stof(argv[2]);

    T3D::TVector model1_offset(stof(argv[3]), stof(argv[4]), stof(argv[5]));

    bool show_model1 = false;
    std::string show_temp1 = argv[6];

    if (show_temp1 == "show") {
        show_model1 = true;
        current++;
    }

    std::string operation = argv[current + 6];
    if (operation == "+" || operation == "-" || operation == "|" || operation == "/") current++;

    std::string model2 = argv[current + 6];
    float model2_scale = stof(argv[current + 7]);

    T3D::TVector model2_offset(stof(argv[current + 8]), stof(argv[current + 9]), stof(argv[current + 10]));

    bool show_model2 = false;

    if (current + 11 <= params) {
        std::string show_temp2 = argv[current + 11];

        if (show_temp2 == "show") {
            show_model2 = true;
            current++;
        }
    }

    bool union_operation = false;
    bool subtraction_operation = false;
    bool intersection_operation = false;
    bool difference_operation = false;

    if (operation == "+") union_operation = true;
    else if (operation == "-") subtraction_operation = true;
    else if (operation == "|") intersection_operation = true;
    else if (operation == "/") difference_operation = true;

    T3D::TTuple<double, 3> operation_colour(1, 0.5, 0);
    T3D::TTuple<double, 3> rm1_colour = union_operation ? operation_colour : T3D::TTuple<double, 3>(1, 0, 0);
    T3D::TTuple<double, 3> rm2_colour = union_operation ? operation_colour : T3D::TTuple<double, 3>(1, 1, 0);

    RenderModel *rm1 = new RenderModel(
        "../assets/" + model1 + ".obj",
        rm1_colour,
        model1_scale,
        model1_offset
    );

    RenderModel *rm2 = new RenderModel(
        "../assets/" + model2 + ".obj",
        rm2_colour,
        model2_scale,
        model2_offset
    );

    if (union_operation) {
        show_model1 = true;
        show_model2 = true;
    }
    else if (subtraction_operation) subtraction(rm1, rm2, operation_colour, view);
    else if (intersection_operation) intersection(rm1, rm2, operation_colour, view);
    else if (difference_operation) difference(rm1, rm2, operation_colour, view);

    if (show_model1) view->m_objects.push_back(rm1);
    if (show_model2) view->m_objects.push_back(rm2);

    gapp.run();
    gapp.release();

	return 0;
}