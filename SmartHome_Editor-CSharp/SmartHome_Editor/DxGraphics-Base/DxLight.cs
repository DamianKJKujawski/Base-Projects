using SharpDX;



namespace DxGraphics
{
    public class DxLight
    {

        #region VARIABLES:

        public Vector4 DiffuseColour { get; private set; }
        public Vector3 Direction { get; private set; }

        #endregion



        #region PUBLIC:

        public void Set_DiffuseColour(float red, float green, float blue, float alpha) =>
            DiffuseColour = new Vector4(red, green, blue, alpha);

        public void Set_Direction(float x, float y, float z) =>
            Direction = new Vector3(x, y, z);

        #endregion

    }
}