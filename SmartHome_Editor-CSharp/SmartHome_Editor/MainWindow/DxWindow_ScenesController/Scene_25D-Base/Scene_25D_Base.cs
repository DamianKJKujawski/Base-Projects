using System;
using System.Windows;
using SharpDX;
using SharpDX.Direct3D11;

// Dx Base:
using DxGraphics;



namespace DxWindow.ScenesController.Scene_25D
{
    // Each scene has different graphics settings:
    public abstract class Scene_25D_Base : IDisposable
    {
        #region VARIABLES:

            // Graphical Interface:
            protected Device Device_HardwareInterface { get; private set; }
            protected DeviceContext DeviceContext_RenderInterface { get; private set; }

            // Blend State:
            protected BlendState? BlendState_Transparent { get; private set; }

            // Lighting:
            protected DxLightShader? LightShader { get; private set; }
            protected DxLight? Light { get; private set; }

            // World Matrix:
            protected Matrix WorldMatrix { get; private set; }

        #endregion



        #region INIT/DISPOSAL:

            protected Scene_25D_Base(Device device, DeviceContext deviceContext)
            {
                Device_HardwareInterface = device;
                DeviceContext_RenderInterface = deviceContext;
            }

            public virtual bool Initialize()
            {
                try
                {
                    Initialize_Light();
                    Initialize_WorldMatrix();
                    Initialize_Shader();
                    Initialize_BlendState();

                    return true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("The scene Graphics could not be initialized\nError is '" + ex.Message + "'");

                    return false;
                }
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
                    Light = null;

                    LightShader?.Dispose();
                    BlendState_Transparent?.Dispose();
                }
            }

        #endregion



        #region PROTECTED:

            private void Initialize_Light()
            {
                Light = new DxLight();
                Light.Set_DiffuseColour(1, 1, 1, 1);
                Light.Set_Direction(0, 0, 1);
            }

            private void Initialize_WorldMatrix()
            {
                WorldMatrix = Matrix.Identity;
            }

            private void Initialize_Shader()
            {
                if (Device_HardwareInterface == null)
                    return;

                LightShader = new DxLightShader();

                if (!LightShader.Initialize(Device_HardwareInterface))
                    MessageBox.Show("Could not initialize the texture shader object.");
            }

            private void Initialize_BlendState()
            {
                BlendStateDescription _initialBlendStateDescription = new()
                {
                    AlphaToCoverageEnable = false,
                    IndependentBlendEnable = false
                };

                _initialBlendStateDescription.RenderTarget[0] = new RenderTargetBlendDescription
                {
                    IsBlendEnabled = true,
                    SourceBlend = BlendOption.SourceAlpha,
                    DestinationBlend = BlendOption.InverseSourceAlpha,
                    BlendOperation = BlendOperation.Add,
                    SourceAlphaBlend = BlendOption.One,
                    DestinationAlphaBlend = BlendOption.Zero,
                    AlphaBlendOperation = BlendOperation.Add,
                    RenderTargetWriteMask = ColorWriteMaskFlags.All
                };

                BlendState_Transparent = new BlendState(DeviceContext_RenderInterface?.Device, _initialBlendStateDescription);
            }

        #endregion
    }
}
