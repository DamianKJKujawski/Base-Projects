using System;
using SharpDX;
using SharpDX.Direct2D1;
using SharpDX.DXGI;



namespace DxWindow.ScenesController.Scene_25D.Graphics2D.DxWindow_Overlay2D_
{
    public class Overlay_2D_Base : IDisposable
    {

        #region VARIABLES:

            // Target Window:
            readonly protected RenderTarget renderTarget2D;

            // Overlay settings:
            readonly protected SharpDX.Direct2D1.Factory factory2D;        

        #endregion



        #region INIT/DISPOSAL:

            protected Overlay_2D_Base(IntPtr hwnd)
            {
                factory2D = new SharpDX.Direct2D1.Factory();

                // DPI setting:
                var _dpi = factory2D.DesktopDpi;
                renderTarget2D = new WindowRenderTarget
                (
                    factory2D,
                    new RenderTargetProperties
                    {
                        DpiX = _dpi.Width,
                        DpiY = _dpi.Height,
                        PixelFormat = new SharpDX.Direct2D1.PixelFormat(Format.Unknown, (SharpDX.Direct2D1.AlphaMode)SharpDX.DXGI.AlphaMode.Premultiplied),
                        Type = RenderTargetType.Default,
                        Usage = RenderTargetUsage.None
                    },
                    new HwndRenderTargetProperties
                    {
                        Hwnd = hwnd,
                        PixelSize = new Size2(1, 1),
                        PresentOptions = PresentOptions.None
                    }
                );
            }

            public virtual void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            public virtual void Dispose(bool disposing)
            {
                if (disposing)
                {
                    renderTarget2D?.Dispose();
                    factory2D?.Dispose();
                }
            }

        #endregion

    }
}
