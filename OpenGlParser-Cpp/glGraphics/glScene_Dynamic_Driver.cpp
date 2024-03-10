#include "GlScene_Dynamic_Driver.h"



void GlScene_Dynamic_Driver::Add_Dot(size_t idx, Point2D_t position)
{
    methodPointers[idx] = [this, position]() -> bool 
    { 
        glDrawInstance->Draw_Dot(position); 

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_Line(size_t idx, Point2D_t point1, Point2D_t point2)
{
    methodPointers[idx] = [this, point1, point2]() -> bool 
    { 
        glDrawInstance->Draw_Line(point1, point2); 

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_Square(size_t idx, Point2D_t position, Size2D size)
{
    methodPointers[idx] = [this, position, size]() -> bool 
    { 
        glDrawInstance->Draw_Square(position, size);

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_Array(size_t idx, const std::vector<float>& array, Point2D_t position)
{
    methodPointers[idx] = [this, array, position]() -> bool
    {
        glDrawInstance->Draw_Array(array, position);

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_Text2D(size_t idx, const std::string text, Point2D_t position)
{
    methodPointers[idx] = [this, text, position]() -> bool 
    { 
        glDrawInstance->Draw_Text(text, position); 

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_DrawTexture(size_t idx, GLuint& textureID, Point3D position, Size2D textureSize)
{
    methodPointers[idx] = [this, &textureID, position, textureSize]() -> bool
    {
        glDrawInstance->DrawTexture(textureID, position, textureSize);

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, Point3D& position, Size2D textureSize)
{
    methodPointers[idx] = [this, &textureID, filename, &position, textureSize]() -> bool 
    {
        glDrawInstance->DrawTexture(textureID, filename, position, textureSize);

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_DrawTexture(size_t idx, const char* filename, GLuint& textureID, const Point3D& position, Size2D textureSize)
{
    methodPointers[idx] = [this, &textureID, filename, position, textureSize]() -> bool
    {
        glDrawInstance->DrawTexture(textureID, filename, position, textureSize);

        return false;
    };
}

void GlScene_Dynamic_Driver::Add_LoadTexture(size_t idx, const char* filename, GLuint& textureID)
{
    methodPointers[idx] = [this, &textureID, filename, idx]() -> bool 
    {
        if (glDrawInstance->LoadTexture(filename, textureID)) 
        {
            this->Remove_Object(idx);

            return true;
        }
        return false;
    };
}



void GlScene_Dynamic_Driver::Remove_Object(size_t index)
{
    methodPointers.erase(index);
}



void GlScene_Dynamic_Driver::Draw(float cameraPositionX, float cameraPositionY)
{
    glDrawInstance->Set_CameraShift(Point2D_t{ cameraPositionX , cameraPositionY });

    for (const auto& pair : methodPointers) 
    {
        if (pair.second())
            break;
    }
}