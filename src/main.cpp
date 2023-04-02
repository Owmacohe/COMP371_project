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

TAPP::RenderModel* find_model(vector<TAPP::RenderModel*> rms, string n) {
    for (RenderModel *rm : rms)
        if (rm->name == n)
            return rm;

    return NULL;
}

vector<Operation*> parse(nlohmann::json j) {
    vector<Operation*> temp;
    vector<RenderModel*> models;

    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++) {
        RenderModel *rm = new RenderModel(
            "../assets/" + (string)(*itr)["filename"] + ".obj",
            (string)(*itr)["name"],
            T3D::TTuple<double, 3>((*itr)["colour"][0], (*itr)["colour"][1], (*itr)["colour"][2]),
            (*itr)["scale"],
            T3D::TVector((*itr)["offset"][0], (*itr)["offset"][1], (*itr)["offset"][2])
        );

        models.push_back(rm);
    }

    for (auto itr = j["operations"].begin(); itr!= j["operations"].end(); itr++) {
        Operation *operation = new Operation(
            find_model(models, (*itr)["model1"]),
            find_model(models, (*itr)["model2"]),
            (*itr)["operation"],
            T3D::TTuple<double, 3>((*itr)["colour"][0], (*itr)["colour"][1], (*itr)["colour"][2])
        );

        temp.push_back(operation);
    }

    return temp;
}

int main(int argc, char* argv[]) {
    int w = 1024;
    int h = 768;
    
    std::string name = "Owen Hellum - COMP 371 CSG Project";
    
    if (!gapp.initialize(w, h, name)) {
        cout << "Unable to initialize!" << endl;
        return -1;
    }
    
    Virtual3DLayer* view = new Virtual3DLayer(w, h);
    gapp.m_window.m_layers.push_back(view);

    std::ifstream t(argv[1]);
    if (!t) {
        cout<<"File "<<argv[1]<<" does not exist!"<<endl;
        return -1;
    }

    std::stringstream buffer;
    buffer << t.rdbuf();

    nlohmann::json j = nlohmann::json::parse(buffer.str());
    vector<Operation*> operations = parse(j);
    for (Operation *operation : operations) operation->generate(view);

    gapp.run();
    gapp.release();

	return 0;
}