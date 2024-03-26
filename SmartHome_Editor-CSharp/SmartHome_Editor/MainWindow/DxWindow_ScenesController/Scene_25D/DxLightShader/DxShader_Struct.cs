using SharpDX;
using System.Runtime.InteropServices;



namespace DxWindow.ScenesController.Scene_25D.DxLightShader_
{ 
    [StructLayout(LayoutKind.Sequential)]
    public struct DxMatrixBuffer
    {
        public Matrix world;
        public Matrix view;
        public Matrix projection;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct DxLightBuffer
    {
        public Vector4 diffuseColor;
        public Vector3 lightDirection;
        public float rr; // Optimization: Remove additional masking
    }
}
