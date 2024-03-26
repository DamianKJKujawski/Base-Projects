using System;
using SharpDX;
using SharpDX.Direct2D1;
using SharpDX.DirectWrite;
using SharpDX.Mathematics.Interop;

using DxWindow.ScenesController.Scene_25D.DxWindow_Overlay2D_;
using DxWindow.ScenesController.Scene_25D.Graphics2D.DxWindow_Overlay2D_;




namespace DxWindow.ScenesController.Scene_25D
{
    public class DxWindow_Overlay2D : Overlay_2D_Base, IOverlay_2D
    {

        #region VARIABLES:

            // Scene Resources:
            readonly private SolidColorBrush solidColorBrush2D_;
            readonly private TextFormat textFormat2D_;

        #endregion



        #region INIT/DISPOSAL:

            public DxWindow_Overlay2D(IntPtr hwnd) : base(hwnd)
            {
                solidColorBrush2D_ = new SolidColorBrush(base.renderTarget2D, Color4.White);
                textFormat2D_ = new TextFormat(new SharpDX.DirectWrite.Factory(), "Arial", 16);
            }

            public override void Dispose()
            {
                Dispose(true);
                base.Dispose();

                GC.SuppressFinalize(this);
            }

            public override void Dispose(bool disposing)
            {
                if (disposing)
                {
                    solidColorBrush2D_?.Dispose();
                    textFormat2D_?.Dispose();
                }

                base.Dispose(disposing);
            }

        #endregion



        #region PUBLIC:

            #region Node - Manage Rendering Process:
            public void Render()
            {
                // Begin:
                base.renderTarget2D.BeginDraw();
                base.renderTarget2D.Clear(new Color4(0, 0, 0, 0));

                // Drawing scene:
                base.renderTarget2D.DrawText("2D Overlay", textFormat2D_, new RawRectangleF(10, 10, 300, 50), solidColorBrush2D_);

                // End:
                base.renderTarget2D.EndDraw();
            }
            #endregion

        #endregion

    }
}
