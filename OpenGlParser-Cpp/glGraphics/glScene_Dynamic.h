#ifndef GLSCENES_H
#define GLSCENES_H

#include "glScene.h" 
#include "glDraw.h"

#include <functional>
#include <unordered_map>



class GlScene_Dynamic : public GlScene
{

    private:

        GlDraw* glDrawInstance = GlDraw::Get_Instance();

        std::unordered_map<size_t, std::function<void()>> methodPointers;



    public:

        GlScene_Dynamic() = default;
        ~GlScene_Dynamic() = default;



        void Add_Dot(size_t idx);
        void Add_Line(size_t idx);
        void Add_Text2D(size_t idx);
        
        void Remove_Object(size_t index);

        void Draw() override; 

};

#endif