using System;
using System.Windows.Controls;

using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;



using Device = SharpDX.Direct3D11.Device;
using DeviceContext = SharpDX.Direct3D11.DeviceContext;
using FeatureLevel = SharpDX.Direct3D.FeatureLevel;
using Resource = SharpDX.DXGI.Resource;



namespace DSharp_InteropLibrary
{
    // Bridge between WPF and SharpDX

    public class DSharp_Interop : IDisposable       
    {

        #region VARIABLES/PROPERTIES:

            // Device Interfaces:
            private readonly Device? device_hardwareInterface_;
            private readonly DeviceContext? deviceContext_renderInterface_;

            // Render:
            private Matrix projectionMatrix_;
            private SizeInt2D renderSize_;

            private RenderTargetView? frontBufferView_;
            private IDxWindow? dxWindowGraphics_;

            // Used Window:
            private IntPtr? resourcePointer_ = IntPtr.Zero;

            // Camera:
            private CameraFOV cameraFOV_ = new();

        #endregion



        #region INIT/DISPOSAL:

            public DSharp_Interop(IDxWindow graphics)
            {
                try
                {
                    device_hardwareInterface_ = Initialize_D3D11Device();
                    deviceContext_renderInterface_ = device_hardwareInterface_.ImmediateContext;
                    dxWindowGraphics_ = graphics;
                }
                catch (Exception e) {
                    throw new Exception("Could not create SharpDx Interop object" + e.Message);
                }
            }

            public bool Initialize(float angleOfViewDegrees, float nearClip, float farClip)
            {
                if((device_hardwareInterface_ == null) || (deviceContext_renderInterface_ == null) || (dxWindowGraphics_ == null))
                {
                    System.Windows.MessageBox.Show("Could not initialize SharpDx Interop");

                    return false;
                }

                angleOfViewDegrees = angleOfViewDegrees * (float)Math.PI / 180f;
                cameraFOV_ = new(angleOfViewDegrees, nearClip, farClip);

                dxWindowGraphics_.Initialize(device_hardwareInterface_, deviceContext_renderInterface_);

                return true;
            }

            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            public void Dispose(bool disposing)
            {
                if (disposing)
                {
                    device_hardwareInterface_?.Dispose();
                    deviceContext_renderInterface_?.Dispose();

                    frontBufferView_ = null;
                    dxWindowGraphics_ = null;
                }
            }

        #endregion



        #region PRIVATE:

        // INITIALIZE:

            private static Device Initialize_D3D11Device()
            {
                Device? _device;

                try
                {
                    const DeviceCreationFlags _deviceFlags = DeviceCreationFlags.BgraSupport;
                    FeatureLevel[] _featureLevels = { FeatureLevel.Level_11_1 };
                    _device = new Device(DriverType.Hardware, _deviceFlags, _featureLevels);
                }
                catch (Exception e)
                {
                    throw new Exception("Could not create a Direct3D 10/11 device. " + e.Message);
                }

                return _device;
            }

            private void Initialize_Viewport(int width, int height)
            {
                renderSize_.width = width;
                renderSize_.height = height;

                ViewportF vp = new()
                {
                    Width = width,
                    Height = height,
                    MinDepth = 0,
                    MaxDepth = 1,
                    X = 0,
                    Y = 0
                };

                deviceContext_renderInterface_!.Rasterizer.SetViewport(viewport: vp);

                // Initialize the projection matrix:
                projectionMatrix_ = Matrix.PerspectiveFovLH(cameraFOV_.angle, width / (float)height, cameraFOV_.nearClipping, cameraFOV_.farClipping);
            }

            private void Create_RenderTargetView(IntPtr resourcePointer)
            {
                if (deviceContext_renderInterface_ == null)
                    return;

                using Resource _d3dResource = (Resource)resourcePointer;
                IntPtr renderTextureHandle = _d3dResource.QueryInterface<Resource>().SharedHandle;

                using SharpDX.Direct3D11.Resource _d3d11Resource1 = device_hardwareInterface_!.OpenSharedResource<SharpDX.Direct3D11.Resource>(renderTextureHandle);
                var _texture2DFront = (Texture2D)_d3d11Resource1.NativePointer;
                var _texture2DBack = new Texture2D(device_hardwareInterface_, _texture2DFront.Description);

                RenderTargetViewDescription _targetDescription = new()
                {
                    Format = SharpDX.DXGI.Format.B8G8R8A8_UNorm,
                    Dimension = RenderTargetViewDimension.Texture2D
                };
                _targetDescription.Texture2D.MipSlice = 0;

                frontBufferView_ = new RenderTargetView(device_hardwareInterface_, _texture2DFront, _targetDescription);

                deviceContext_renderInterface_.OutputMerger.SetRenderTargets(frontBufferView_);
            }

        #endregion



        #region PUBLIC:

            public Tuple<int, int> Get_RenderPixelSize(Panel host)
            {
                renderSize_.width = (int)(host.ActualWidth);
                renderSize_.height = (int)(host.ActualHeight);
                var pixelSize = new Tuple<int, int>(renderSize_.width, renderSize_.height);

                return pixelSize;
            }


            public void Render(IntPtr resourcePointer, bool updateWindow, int width, int height)
            {
                if (resourcePointer != resourcePointer_)
                {
                    resourcePointer_ = resourcePointer;

                    updateWindow = true;
                }

                if (updateWindow)
                {
                    renderSize_.height = height;
                    renderSize_.width = width;

                    Create_RenderTargetView(resourcePointer);
                    Initialize_Viewport(renderSize_.width, renderSize_.height);
                }

                dxWindowGraphics_!.Render(frontBufferView_!, projectionMatrix_);
            }

        #endregion

    }
}