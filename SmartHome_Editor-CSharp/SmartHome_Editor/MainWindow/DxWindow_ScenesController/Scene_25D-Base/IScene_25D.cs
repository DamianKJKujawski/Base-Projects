using SharpDX;
using DSharp_InteropLibrary;



namespace DxWindow.ScenesController.Scene_25D
{
    public interface IScene_25D
    {
        // Init:
        bool Initialize();

        // Dispose Scene:
        void Dispose();
        void Dispose(bool disposing);

        // Context Menu Info:
        (string, int)[] Get_TexturesList();

        // Mouse:
        void MouseClick(int textureIndex);
        Vector3 Set_MouseSelection(System.Windows.Point screenPoint, SizeInt2D windowSize, MOUSE_SELECTION_STATE selectionState); // Handle Click and move

        // Camera:
        void Camera_Reset();
        void Camera_Move(float x, float y, float z = 0);
        void Camera_Zoom(float z);

        // Render Scene:
        void Render(Matrix projectionMatrix);
    }
}
