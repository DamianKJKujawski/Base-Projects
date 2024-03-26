using System;
using SharpDX;
using SharpDX.Direct3D11;
using System.Windows;
using SharpDX.Mathematics.Interop;
using DSharp_InteropLibrary;

using DxWindow.ScenesController;
using DxWindow.ScenesController.Scene_25D;



namespace DxWindow
{
    public class DxWindow_ScenesController : IDxWindow, IDisposable
    {
        #region VARIABLES:

            private Device? device_hardwareInterface_;
            private DeviceContext? deviceContext_renderInterface_;

            //Current Scene:
            private IScene_25D? currentScene_; // Window does not need Scene to run!

            // Scenes:
            private Scene_25D_MapEditor? mapEditor_;

        #endregion



        #region INIT/DISPOSAL:

            #region Node - Manage Window Scenes here:
            private void Manage_Scenes(Device? device, DeviceContext? deviceContext)
            {
                if((device == null) || (deviceContext == null)) 
                { 
                    MessageBox.Show("Scenes Controller: The Scene could not be set\n Trying to pass NULLed Device");
                    return;
                }

                mapEditor_ = new Scene_25D_MapEditor(device, deviceContext);
                Set_Scene(mapEditor_); // Disposing last scene 
            }
            #endregion

            public DxWindow_ScenesController() { }

            public void Initialize(Device device, DeviceContext deviceContext)
            {
                if((device == null) || (deviceContext == null)) 
                { 
                    MessageBox.Show("The Scenes Controller could not be initialized\n Trying to pass NULLed Device");
                    return;
                }

                device_hardwareInterface_ = device;
                deviceContext_renderInterface_ = deviceContext;

                Manage_Scenes(device_hardwareInterface_, deviceContext_renderInterface_);
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

                    currentScene_?.Dispose();
                    currentScene_ = null;
                }
            }

        #endregion



        #region PUBLIC:

            // Set new rendered scene:
            public bool Set_Scene(IScene_25D? scene)
            {
                if ((device_hardwareInterface_ == null) || (deviceContext_renderInterface_ == null))
                    return false;

                if (scene == null)
                    return false;


                try 
                {
                    currentScene_?.Dispose();
                    currentScene_ = null;

                    scene.Initialize();
                    currentScene_ = scene;

                    return true;
                }
                catch (Exception e) 
                {
                    MessageBox.Show(e.ToString());

                    return false;
                }
            }

            // IO - Handle Mouse:
            public void MouseWheel(float z) =>
                currentScene_?.Camera_Zoom(z);

            public void MouseMovement(float x, float y, float z = 0) =>
                currentScene_?.Camera_Move(x, y, z);

            public void MouseClick(System.Windows.Point screenPoint, SizeInt2D windowSize, MOUSE_SELECTION_STATE selectionState) =>
                currentScene_?.Set_MouseSelection(screenPoint, windowSize, selectionState);

            // Context Menu:
            public void MenuClick(int textureIndex) =>
                currentScene_?.MouseClick(textureIndex);

            public (string, int)[] Get_Menu()
            {
                if(currentScene_ == null)
                    return Array.Empty<(string, int)>(); // If there is no need to create a context menu, return Empty array

                return currentScene_.Get_TexturesList();
            }


            // Render Scene:
            public void Render(RenderTargetView renderTargetView, Matrix projectionMatrix)
            {
                if ((deviceContext_renderInterface_ == null) || (currentScene_ == null))
                    return;

                deviceContext_renderInterface_.ClearRenderTargetView(renderTargetView, new RawColor4(0.0f, 0.0f, 0.0f, 0.0f));

                currentScene_.Render(projectionMatrix);

                deviceContext_renderInterface_.Flush();
            }

        #endregion
    }
}
