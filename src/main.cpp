#include <iostream>
#include "TOGLApp.h"

#include "Virtual3DLayer.h"

#include "RenderModel.h"

using namespace TAPP;
using namespace std;

std::string global_path;

int main(int argc, char* argv[]) {
    if (argc == 0) {
        cout << "Usage: " << argv[0] << " objname.obj (as many objs as wanted)" << endl;
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
    RenderModel* lastModel;
    string lastOperation = "";

    RenderModel* models[2];

    for (int i = 1; i < argc; i++) {
        string argument = argv[i];

        if (argument == "-" && lastModel != NULL) {
            lastOperation = argument;
        }
        else if (argument != "-") {
            for (int j = 0; j < 3; j++) {
                if (argument == primitives[j]) {
                    argument = "../assets/" + argument + ".obj";
                    break;
                }
            }

            RenderModel* sp1 = new RenderModel(argument);

            view->m_objects.push_back(sp1);

            lastModel = sp1;
        }
    }

    gapp.run();
    gapp.release();

	return 0;
}