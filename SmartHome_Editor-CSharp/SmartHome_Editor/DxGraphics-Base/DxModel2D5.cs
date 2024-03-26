using System;
using SharpDX;
using SharpDX.Direct3D;
using SharpDX.Direct3D11;
using SharpDX.DXGI;

// DxModel25D:
using DxGraphics.DxModel2D5_Base_;



namespace DxGraphics
{
    public class DxModel2D5 : IDisposable // Flag 2.5D Model, for an isometric view
    {

        #region VARIABLES:

        // Properties:
        private SharpDX.Direct3D11.Buffer? vertexBuffer_;
        private SharpDX.Direct3D11.Buffer? indexBuffer_;

        private DxModelFormat[]? modelObject_;

        // Texture:
        public DxTexture3D? Texture { get; private set; }

        // Parameters:
        public const int vertexCount = 6;
        public int IndexCount { get; } = vertexCount;

        #endregion



        #region INIT/DISPOSAL:

        public DxModel2D5() { }

        public bool Initialize(SharpDX.Direct3D11.Device device, DxTexture3D texture, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4)
        {
            if (!Load_Model(p1, p2, p3, p4))
                return false;

            if (!Initialize_Buffers(device))
                return false;

            Texture = texture; // Assign the shared texture

            return true;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                Release_Texture();

                vertexBuffer_?.Dispose();
                indexBuffer_?.Dispose();
            }
        }

        #endregion



        #region PRIVATE:

        private bool Load_Model(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4)
        {
            modelObject_ = new DxModelFormat[]
            {
                new DxModelFormat() { x = p1.X, y = p1.Y, z = p1.Z, tu = 0, tv = 1 },
                new DxModelFormat() { x = p2.X, y = p2.Y, z = p2.Z, tu = 0, tv = 0 },
                new DxModelFormat() { x = p4.X, y = p4.Y, z = p4.Z, tu = 1, tv = 0 },
                new DxModelFormat() { x = p1.X, y = p1.Y, z = p1.Z, tu = 0, tv = 1 },
                new DxModelFormat() { x = p4.X, y = p4.Y, z = p4.Z, tu = 1, tv = 0 },
                new DxModelFormat() { x = p3.X, y = p3.Y, z = p3.Z, tu = 1, tv = 1 }
            };

            return true;
        }

        private bool Initialize_Buffers(SharpDX.Direct3D11.Device device)
        {
            if (modelObject_ == null)
                return false;

            var vertices = new DxVertex[vertexCount];
            var indices = new int[IndexCount];

            try
            {
                for (var i = 0; i < vertexCount; i++)
                {
                    vertices[i] = new DxVertex()
                    {
                        position = new Vector3(modelObject_[i].x, modelObject_[i].y, modelObject_[i].z),
                        texture = new Vector2(modelObject_[i].tu, modelObject_[i].tv),
                        normal = new Vector3(0, 0, -1),
                        color = new Color4(0, 0, 0, 0) // Alpha channel (transparency)
                    };

                    indices[i] = i;
                }

                vertexBuffer_ = SharpDX.Direct3D11.Buffer.Create(device, BindFlags.VertexBuffer, vertices);
                indexBuffer_ = SharpDX.Direct3D11.Buffer.Create(device, BindFlags.IndexBuffer, indices);

                return true;
            }
            catch
            {
                return false;
            }
        }

        #endregion



        #region PUBLIC:

        public void Set_Texture(DxTexture3D texture) =>
            Texture = texture;

        public void Release_Texture() =>
            Texture = null; // The Class stores a Reference to a Texture.

        public void Render(DeviceContext deviceContext)
        {
            deviceContext.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer_, Utilities.SizeOf<DxVertex>(), 0));
            deviceContext.InputAssembler.SetIndexBuffer(indexBuffer_, Format.R32_UInt, 0);
            deviceContext.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
        }

        #endregion

    }
}