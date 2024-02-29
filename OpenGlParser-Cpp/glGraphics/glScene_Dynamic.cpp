#include "glScene_Dynamic.h"



void GlScene_Dynamic::Add_Dot(size_t idx) {
    methodPointers[idx] = [this]() { glDrawInstance->Draw_Dot(Point2D{ 0, 0 }); };
}

void GlScene_Dynamic::Add_Line(size_t idx) {
    methodPointers[idx] = [this]() { glDrawInstance->Draw_Square(Point2D{ 0, 0 }, Size2D{ 55, 55 }); };
}

void GlScene_Dynamic::Add_Text2D(size_t idx) {
    methodPointers[idx] = [this]() { glDrawInstance->Draw_Text("Test", Point2D{ 0, 0 }); };
}



void GlScene_Dynamic::Remove_Object(size_t index) {
    methodPointers.erase(index);
}



void GlScene_Dynamic::Draw()
{
    for (const auto& pair : methodPointers) 
    {
        pair.second();
    }
}