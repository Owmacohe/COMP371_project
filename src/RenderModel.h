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
        
        RenderModel(std::string filename, std::string n, T3D::TTuple<double, 3> c, float s, T3D::TVector o)
                : RUIObject(), file_name(filename), name(n), colour(c), scale(s), offset(o), perform_operation(false) {
            Load(m_obj, filename.c_str());
        }

        RenderModel(std::string n, RenderModel *rm1, T3D::TTuple<double, 3> c, RenderModel *rm2, bool inside, bool flip)
                : RUIObject(), file_name(rm1->file_name), name(n),
                colour(c), scale(rm1->scale), offset(rm1->offset),
                operation_model(rm2), remove_inside(inside), flip_normals(flip), perform_operation(true) {
            Load(m_obj, rm1->file_name.c_str());
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

        string name;
        string file_name;

        float scale;
        T3D::TVector offset;
        T3D::TTuple<double, 3> colour;

        RenderModel *operation_model;

        bool invalid;
        bool perform_operation;
        bool remove_inside;
        bool flip_normals;

        void to_string(T3D::TTuple<double, 3>);
        void to_string(vector<int>);
        void to_string(vector<float>);
        T3D::TPoint projection_on_plane(
            T3D::TPoint plane_point, T3D::TVector plane_normal,
            T3D::TPoint point_origin, T3D::TVector point_direction);
        bool is_on_right(T3D::TPoint check, T3D::TPoint p1, T3D::TPoint p2, T3D::TVector n);
        bool hit_triangle(T3D::TPoint check, T3D::TPoint p1, T3D::TPoint p2, T3D::TPoint p3, T3D::TVector n);
        bool is_point_inside(T3D::TPoint p, RenderModel *r);
};


}
#endif // TOGLAPP_H
