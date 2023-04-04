#include <iostream>
#include <sstream>
#include "TOGLApp.h"

#include "Virtual3DLayer.h"
#include "RenderModel.h"

#include "json.hpp"
#include "Operation.h"

using namespace TAPP;
using namespace std;

std::string global_path;

void set_bounds(TAPP::RenderModel *rm) {
    for (int i = 0; i < rm->m_obj.vertex.size(); i++) {
        T3D::TPoint v = rm->m_obj.vertex[i] * rm->scale + rm->offset;

        if (v[0] > rm->bounds_x[0]) rm->bounds_x[0] = v[0];
        if (v[0] < rm->bounds_x[1]) rm->bounds_x[1] = v[0];

        if (v[1] > rm->bounds_y[0]) rm->bounds_y[0] = v[1];
        if (v[1] < rm->bounds_y[1]) rm->bounds_y[1] = v[1];

        if (v[2] > rm->bounds_z[0]) rm->bounds_z[0] = v[2];
        if (v[2] < rm->bounds_z[1]) rm->bounds_z[1] = v[2];
    }
}

TAPP::RenderModel* find_model(vector<TAPP::RenderModel*> rms, string n) {
    for (RenderModel *rm : rms)
        if (rm->name == n)
            return rm;

    return NULL;
}

vector<Operation*> parse(nlohmann::json j, Virtual3DLayer *view) {
    vector<Operation*> temp;
    vector<RenderModel*> models;

    int offset = 0;

    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++) {
        RenderModel *rm = new RenderModel(
            "../assets/" + (string)(*itr)["filename"] + ".obj",
            (string)(*itr)["name"],
            T3D::TTuple<double, 3>((*itr)["colour"][0], (*itr)["colour"][1], (*itr)["colour"][2]),
            (*itr)["scale"],
            T3D::TVector((*itr)["offset"][0], (*itr)["offset"][1], (*itr)["offset"][2]),
            offset
        );

        set_bounds(rm);

        offset += rm->m_obj.vertex.size();

        models.push_back(rm);

        if ((*itr)["show"]) view->m_objects.push_back(rm);
    }

    for (auto itr = j["operations"].begin(); itr!= j["operations"].end(); itr++) {
        if ((*itr)["show"]) {
            RenderModel *rm1 = find_model(models, (*itr)["model1"]);

            RenderModel *rm2 = find_model(models, (*itr)["model2"]);

            Operation *operation = new Operation(
                (string)(*itr)["name"],
                rm1,
                rm2,
                (*itr)["operation"],
                T3D::TTuple<double, 3>((*itr)["colour"][0], (*itr)["colour"][1], (*itr)["colour"][2]),
                (*itr)["save"]
            );

            temp.push_back(operation);
        }
    }

    return temp;
}

int main(int argc, char* argv[]) {
    int w = 1024;
    int h = 768;

    if (argc != 2) {
        cout << "Please include the path to a valid JSON!" << endl;
        return -1;
    }
    
    std::string name = "Owen Hellum - COMP 371 CSG Project";
    
    if (!gapp.initialize(w, h, name)) {
        cout << "Unable to initialize!" << endl;
        return -1;
    }
    
    Virtual3DLayer* view = new Virtual3DLayer(w, h);
    gapp.m_window.m_layers.push_back(view);

    std::ifstream t(argv[1]);
    if (!t) {
        cout << "File " << argv[1] << " does not exist!" << endl;
        return -1;
    }

    std::stringstream buffer;
    buffer << t.rdbuf();

    nlohmann::json j = nlohmann::json::parse(buffer.str());
    vector<Operation*> operations = parse(j, view);
    for (Operation *operation : operations) operation->generate(view);

    gapp.run();

    for (Operation *operation : operations) operation->save_obj();

    gapp.release();

	return 0;
}