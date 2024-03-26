using SharpDX.WIC;



namespace DxGraphics.DxTexture3D_
{
    public static class DxBitmap
    {
        public static BitmapSource Load(ImagingFactory factory, string filename)
        {
            var _bitmapDecoder = new BitmapDecoder(
                factory,
                filename,
                DecodeOptions.CacheOnDemand
            );

            var _result = new FormatConverter(factory);

            _result.Initialize(
                _bitmapDecoder.GetFrame(0),
                SharpDX.WIC.PixelFormat.Format32bppPRGBA,
                BitmapDitherType.None,
                null,
                0.0,
                BitmapPaletteType.Custom
            );

            return _result;
        }
    }
}
