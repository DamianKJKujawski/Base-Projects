using System;
using SharpDX.Direct3D11;
using SharpDX.WIC;
using SharpDX;

// DxTexture25D:
using DxGraphics.DxTexture3D_;



namespace DxGraphics
{
    public class DxTexture3D : IDisposable
    {

        #region VARIABLES:

            public ShaderResourceView? TextureResource { get; private set; }
            public Vector2 Size { get; private set; }

        #endregion



        #region INIT/DISPOSAL:

            public DxTexture3D() { }

            public bool Initialize(Device device, string fileName, Vector2 size)
            {
                try
                {
                    if (size.X < 1 || size.Y < 1)
                        throw new ArgumentException("Size of the texture cannot be 0 or less");

                    this.Size = size;
                    using var _texture = Load_FromFile(device, new ImagingFactory(), fileName);

                    ShaderResourceViewDescription srvDesc = new()
                    {
                        Format = _texture.Description.Format,
                        Dimension = SharpDX.Direct3D.ShaderResourceViewDimension.Texture2D,
                        Texture2D = { MipLevels = 1 }
                    };

                    this.TextureResource = new ShaderResourceView(device, _texture, srvDesc);
                    device.ImmediateContext.GenerateMips(this.TextureResource);

                    return true;
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Failed to initialize texture: {ex.Message}");
                    return false;
                }
            }

            public void Dispose()
            {
                Dispose(true);
                GC.SuppressFinalize(this);
            }

            public void Dispose(bool disposing)
            {
                if (disposing) {
                    TextureResource?.Dispose();
                }
            }

        #endregion



        #region PUBLIC:

        public static Texture2D Load_FromFile(Device device, ImagingFactory factory, string fileName)
        {
            using var _bitmap = DxBitmap.Load(factory, fileName);

            return Create_Texture3DFromBitmap(device, _bitmap);
        }

        public static Texture2D Create_Texture3DFromBitmap(Device device, BitmapSource bitmapSource)
        {
            int _stride = bitmapSource.Size.Width * 4;
            using var _buffer = new SharpDX.DataStream(bitmapSource.Size.Height * _stride, true, true);

            bitmapSource.CopyPixels(_stride, _buffer);

            var _textureDescription = new Texture2DDescription
            {
                Width = bitmapSource.Size.Width,
                Height = bitmapSource.Size.Height,
                ArraySize = 1,
                BindFlags = BindFlags.ShaderResource,
                Usage = ResourceUsage.Default,
                CpuAccessFlags = CpuAccessFlags.None,
                Format = SharpDX.DXGI.Format.R8G8B8A8_UNorm, // Use a format with alpha channel
                MipLevels = 1,
                OptionFlags = ResourceOptionFlags.None,
                SampleDescription = new SharpDX.DXGI.SampleDescription(1, 0),
            };

            return new Texture2D(device, _textureDescription, new SharpDX.DataRectangle(_buffer.DataPointer, _stride));
        }

        #endregion

    }
}
