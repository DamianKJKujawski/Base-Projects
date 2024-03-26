using Device = SharpDX.Direct3D11.Device;
using DeviceContext = SharpDX.Direct3D11.DeviceContext;



namespace DSharp_InteropLibrary
{
    public interface IDxWindow
    {

        public void Initialize (
                Device device, 
                DeviceContext deviceContext
            );

        public void Render (
                SharpDX.Direct3D11.RenderTargetView renderTargetView, 
                SharpDX.Matrix projectionMatrix
            );

    }
}
