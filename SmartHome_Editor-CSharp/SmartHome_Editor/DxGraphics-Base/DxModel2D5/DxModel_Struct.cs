using SharpDX;
using System.Runtime.InteropServices;



namespace DxGraphics.DxModel2D5_Base_
{
    [StructLayout(LayoutKind.Sequential)]
    public struct DxModelFormat
    {
        public float x, y, z;
        public float tu, tv;
        public float nx, ny, nz;

        // TODO: Optimization: To optimize, it is advisable to adjust the size of the structure to multiples of 2
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct DxVertex
    {
        public Vector3 position;
        public Vector2 texture;
        public Vector3 normal;
        public Color4 color;
    }
}