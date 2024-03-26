
namespace DSharp_InteropLibrary
{
    public struct CameraFOV
    {
        public float angle;

        public float nearClipping;
        public float farClipping;


        public CameraFOV(float angle, float nearClipping, float farClipping)
        {
            this.angle = angle;

            this.nearClipping = nearClipping;
            this.farClipping = farClipping;
        }

        public CameraFOV()
        {
            this.angle = 0;

            this.nearClipping = 0;
            this.farClipping = 0;
        }
    };
}
