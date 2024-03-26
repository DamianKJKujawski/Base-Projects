
namespace DSharp_InteropLibrary
{
    public struct SizeInt2D
    {
        public int width;
        public int height;


        public SizeInt2D(int width = 0, int height = 0) =>
            (this.width, this.height) = (width, height);
    };
}
