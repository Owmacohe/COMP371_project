#ifndef VSPHERE_H
#define VSPHERE_H
#include <GL/glew.h>

#include "RUIObject.h"
#include <vector>
#include <random>


#include "ObjModel.h"



namespace TAPP {
    
    class RenderModel :public RUIObject {
    public:
        
        RenderModel()
        :RUIObject(){
        
    }
        
        RenderModel(std::string filename, float s, T3D::TTuple<double, 3> c)
        :RUIObject(), scale(s), colour(c), perform_operation(false){
            Load(m_obj, filename.c_str());
        }

        RenderModel(std::string filename, float s, T3D::TTuple<double, 3> c, RenderModel *m, float ms, bool inside)
        :RUIObject(), scale(s), colour(c), model(m), model_scale(ms), remove_inside(inside), perform_operation(true){
            Load(m_obj, filename.c_str());
        }

        RenderModel(std::string filename, float s, T3D::TTuple<double, 3> c, std::string p, float ms, bool inside)
        :RUIObject(), scale(s), colour(c), primitive(p), model_scale(ms), remove_inside(inside), perform_operation(true){
            Load(m_obj, filename.c_str());
        }
        
    
        
        // Uniform variables
        
        GLuint shaderMVP;
        GLuint shaderV;
        GLuint shaderLight;
        GLuint shaderDiffuse;//diffuse color
        
        GLuint wireMVP;
        GLuint wireV;
        GLuint wireDiffuse;//diffuse color
        
        // shader program
        GLuint programPhong;
        GLuint programWire;
        void load_shader();
        
        
       // Geometric data buffers
        
        // vertex array
        unsigned int m_VAO;
        
        // vertex buffer
        unsigned int m_VBO;
        
        // normal buffer
        unsigned int m_NBO;
        
        // element buffer object - holds the triangle indices
        unsigned int m_EBO;
        
        void load_geometry();
        
        
        
        ObjModel m_obj;
        
        virtual void init();
        virtual void release();
        virtual void hover(double  x, double y, int mods);
        virtual void grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/);
        virtual void drag(double x, double y, int mods) ;
        virtual void resize(double x, double y);
        
        virtual void render() ;
        
        void render_general(int mode);
        
        
        virtual void render_pick_select(PickDataback& ) ; // to see if we selected this object
        virtual void render_pick_detail(PickDataback& ); // to see if we selected a certain primitive

        T3D::TTuple<double, 3> colour;
        bool perform_operation;
        bool remove_inside;
        float scale, model_scale;
        RenderModel *model;
        std::string primitive;

        /*
        bool is_on_right(T3D::TPoint check, T3D::TPoint p1, T3D::TPoint p2, T3D::TVector n);
        bool hit_triangle(T3D::TPoint check, T3D::TPoint p1, T3D::TPoint p2, T3D::TPoint p3, T3D::TVector n);
        bool is_point_inside(T3D::TPoint p, RenderModel *r);
        */
};


}
#endif // TOGLAPP_H
