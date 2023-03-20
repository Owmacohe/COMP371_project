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
    
    std::string name = "OGL Viewer";
    
    if (!gapp.initialize(w, h, name)) {
        cout << "Unable to initialize!" << endl;
        return -1;
    }
    
    Virtual3DLayer* view = new Virtual3DLayer(w, h);
    gapp.m_window.m_layers.push_back(view);

    string primitives[] = { "cube", "sphere", "monkey" };

    std::string model1_name = argv[1];
    std::string model2_name = argv[3];
    std::string operation = argv[2];

    for (int j = 0; j < 3; j++) {
        if (model1_name == primitives[j]) {
            model1_name = "../assets/" + model1_name + ".obj";
        }

        if (model2_name == primitives[j]) {
            model2_name = "../assets/" + model2_name + ".obj";
        }
    }

    RenderModel* model2 = new RenderModel(model2_name);
    RenderModel* model1 = new RenderModel(model1_name, operation, model2);

    view->m_objects.push_back(model1);
    //view->m_objects.push_back(model2);

    gapp.run();
    gapp.release();

	return 0;
}