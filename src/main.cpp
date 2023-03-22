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

    int current = 0;

    std::string model1 = argv[1];
    float model1_scale = stof(argv[2]);

    bool show_model1 = false;
    std::string temp1 = argv[3];

    if (temp1 == "-o") {
        show_model1 = true;
        current++;
    }

    std::string model2 = argv[current + 3];
    float model2_scale = stof(argv[current + 4]);

    bool show_model2 = false;
    std::string temp2 = argv[current + 5];

    if (temp2 == "-o") {
        show_model2 = true;
        current++;
    }

    std::string operation = argv[current + 5];

    bool hide = false;

    if (argc > current + 6) {
        std::string hide_string = argv[current + 6];
        hide = hide_string == "-h";
    }

    // u = everything
    // s = first subtract the second
    // i = contained between the two
    // d = everything not intersecting
    if (operation == "-u" || operation == "-s" || operation == "-d") {
        if (model1 == "sphere") model1 = "sp";

        if (!hide) {
            if (operation != "-u")
                view->m_objects.push_back(new RenderModel(
                    "../assets/" + model1 + ".obj",
                    model1_scale,
                    T3D::TTuple<double, 3>(1, 0.5f, 0),
                    model2,
                    model2_scale,
                    operation == "-d"
                ));
            else
                view->m_objects.push_back(new RenderModel(
                    "../assets/" + model1 + ".obj",
                    model1_scale,
                    T3D::TTuple<double, 3>(1, 0.5f, 0)
                ));
        }

        if (operation == "-u" || operation == "-d") {
            if (model1 == "sp") model1 = "sphere";
            if (model2 == "sphere") model2 = "sp";

            if (!hide) {
                if (operation != "-u")
                    view->m_objects.push_back(new RenderModel(
                        "../assets/" + model2 + ".obj",
                        model2_scale,
                        T3D::TTuple<double, 3>(1, 0.5f, 0),
                        model1,
                        model1_scale,
                        operation == "-d"
                    ));
                else
                    view->m_objects.push_back(new RenderModel(
                        "../assets/" + model2 + ".obj",
                        model2_scale,
                        T3D::TTuple<double, 3>(1, 0.5f, 0)
                    ));
            }
        }

        if (show_model1) {
            if (model1 == "sphere") model1 = "sp";

            view->m_objects.push_back(new RenderModel(
                "../assets/" + model1 + ".obj",
                model1_scale,
                T3D::TTuple<double, 3>(1, 1, 0)
            ));
        }

        if (show_model2) {
            if (model2 == "sphere") model2 = "sp";

            view->m_objects.push_back(new RenderModel(
                "../assets/" + model2 + ".obj",
                model2_scale,
                T3D::TTuple<double, 3>(1, 0, 0)
            ));
        }
    }

    gapp.run();
    gapp.release();

	return 0;
}