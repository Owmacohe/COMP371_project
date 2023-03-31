#include <iostream>
#include "TOGLApp.h"

#include "Virtual3DLayer.h"

#include "RenderModel.h"

using namespace TAPP;
using namespace std;

std::string global_path;

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

    std::string model1 = argv[1];
    float model1_scale = stof(argv[2]);

    bool show_model1 = false;
    std::string show_temp1 = argv[3];

    if (show_temp1 == "-o") {
        show_model1 = true;
        current++;
    }

    std::string model2 = argv[current + 3];
    float model2_scale = stof(argv[current + 4]);

    bool show_model2 = false;
    std::string show_temp2 = argv[current + 5];

    if (show_temp2 == "-o") {
        show_model2 = true;
        current++;
    }

    std::string operation = argv[current + 5];
    bool u, s, i, d;

    if (operation == "-u") u = true;
    if (operation == "-s") s = true;
    if (operation == "-i") i = true;
    if (operation == "-d") d = true;

    RenderModel *rm1 = new RenderModel("../assets/" + model1 + ".obj", {1, 0, 0}, model1_scale);
    RenderModel *rm2 = new RenderModel("../assets/" + model2 + ".obj", {1, 1, 0}, model2_scale);

    // u = everything
    // s = first subtract the second
    // i = contained between the two
    // d = everything not intersecting
    if (s) {
        RenderModel *subtract_1_2 = new RenderModel(
            "../assets/" + model1 + ".obj",
            {1, 0.5, 0},
            model1_scale,
            rm2,
            true
        );

        view->m_objects.push_back(subtract_1_2);
    }

    if (show_model1) view->m_objects.push_back(rm1);
    if (show_model2) view->m_objects.push_back(rm2);

    gapp.run();
    gapp.release();

	return 0;
}