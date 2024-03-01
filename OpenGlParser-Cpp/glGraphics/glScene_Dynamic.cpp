#include "glScene_Dynamic.h"



void GlScene_Dynamic::Add_Dot(size_t idx, Point2D position) {
    methodPointers[idx] = [this, position]() { glDrawInstance->Draw_Dot(position); };
}

void GlScene_Dynamic::Add_Line(size_t idx, Point2D point1, Point2D point2) {
    methodPointers[idx] = [this, point1, point2]() { glDrawInstance->Draw_Line(point1, point2); };
}

void GlScene_Dynamic::Add_Square(size_t idx, Point2D position, Size2D size) {
    methodPointers[idx] = [this, position, size]() { glDrawInstance->Draw_Square(position, size); };
}

void GlScene_Dynamic::Add_Text2D(size_t idx, const char* text, Point2D position) {
    methodPointers[idx] = [this, text, position]() { glDrawInstance->Draw_Text(text, position); };
}



void GlScene_Dynamic::Add_DrawTexture(size_t idx, const char* filename, GLuint &textureID, Point2D position, Size2D textureSize, GLfloat z)
{
    methodPointers[idx] = [this, &textureID, filename, position, textureSize, z]() { glDrawInstance->DrawTexture(textureID, filename, position, textureSize, z); };
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