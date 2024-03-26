using System;
using System.Windows;
using SharpDX;
using SharpDX.D3DCompiler;
using SharpDX.Direct3D11;

// Light Shader:
using DxWindow.ScenesController.Scene_25D.DxLightShader_;



namespace DxWindow.ScenesController.Scene_25D
{
    public class DxLightShader : IDisposable
    {

        #region VARIABLES:

        // Layout:
        private InputLayout? layout_;

        // Shaders:
        private VertexShader? vertexShader_;
        private PixelShader? pixelShader_;

        // Buffer:
        private SharpDX.Direct3D11.Buffer? constantMatrixBuffer_;
        private SharpDX.Direct3D11.Buffer? constantLightBuffer_;

        // Sampler:
        private SamplerState? samplerState_;

        #endregion



        #region INIT/DISPOSAL:

        public DxLightShader() { }

        public bool Initialize(Device device)
        {
            return Initialize_Shader(device, null, null);
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
                layout_?.Dispose();
                vertexShader_?.Dispose();
                pixelShader_?.Dispose();
                constantLightBuffer_?.Dispose();
                constantMatrixBuffer_?.Dispose();
                samplerState_?.Dispose();
            }
        }

        #endregion



        #region PRIVATE:

        private bool Initialize_Shader(Device device, string? vsFileName, string? psFileName)
        {
            try
            {
                ShaderBytecode _vertexShaderByteCode;
                ShaderBytecode _pixelShaderByteCode;


                if (psFileName == null) {
                    _vertexShaderByteCode = ShaderBytecode.Compile(DxShader_ExeDefinitions.LightVertexShader, "LightVertexShader", "vs_4_0", ShaderFlags.None, EffectFlags.None);
                }
                else {
                    vsFileName = Global.Config.FilePath.shader + vsFileName;
                    _vertexShaderByteCode = ShaderBytecode.CompileFromFile(vsFileName, "LightVertexShader", "vs_4_0", ShaderFlags.None, EffectFlags.None);
                }

                if (psFileName == null) {
                    _pixelShaderByteCode = ShaderBytecode.Compile(DxShader_ExeDefinitions.LightPixelShader, "LightPixelShader", "ps_4_0", ShaderFlags.None, EffectFlags.None);
                }
                else
                {
                    psFileName = Global.Config.FilePath.shader + psFileName;
                    _pixelShaderByteCode = ShaderBytecode.CompileFromFile(psFileName, "LightPixelShader", "ps_4_0", ShaderFlags.None, EffectFlags.None);
                }


                // Create the Vertex & Pixel Shaders from the buffer:
                vertexShader_ = new VertexShader(device, _vertexShaderByteCode);
                pixelShader_ = new PixelShader(device, _pixelShaderByteCode);

                // Set layout of the data that goes into the shader:
                InputElement[] inputElements = new InputElement[] 
                {
                    new InputElement()
                    {
                        SemanticName = "POSITION",
                        SemanticIndex = 0,
                        Format = SharpDX.DXGI.Format.R32G32B32_Float,
                        Slot = 0,
                        AlignedByteOffset = 0,
                        Classification = InputClassification.PerVertexData,
                        InstanceDataStepRate = 0
                    },
                    new InputElement()
                    {
                        SemanticName = "TEXCOORD",
                        SemanticIndex = 0,
                        Format = SharpDX.DXGI.Format.R32G32_Float,
                        Slot = 0,
                        AlignedByteOffset = InputElement.AppendAligned,
                        Classification = InputClassification.PerVertexData,
                        InstanceDataStepRate = 0
                    },
                    new InputElement()
                    {
                        SemanticName = "NORMAL",
                        SemanticIndex = 0,
                        Format = SharpDX.DXGI.Format.R32G32B32_Float,
                        Slot = 0,
                        AlignedByteOffset = InputElement.AppendAligned,
                        Classification = InputClassification.PerVertexData,
                        InstanceDataStepRate = 0
                    }
                };

                // Create the vertex input:
                layout_ = new InputLayout(device, ShaderSignature.GetInputSignature(_vertexShaderByteCode), inputElements);

                // Release the vertex and pixel shader buffers:
                _vertexShaderByteCode.Dispose();
                _pixelShaderByteCode.Dispose();


                // Create a texture sampler state description:
                SamplerStateDescription samplerDesc = new()
                {
                    Filter = Filter.MinMagMipLinear,
                    AddressU = TextureAddressMode.Wrap,
                    AddressV = TextureAddressMode.Wrap,
                    AddressW = TextureAddressMode.Wrap,
                    MipLodBias = 0,
                    MaximumAnisotropy = 1,
                    ComparisonFunction = Comparison.Always,
                    BorderColor = new Color4(0, 0, 0, 0),  // Black Border.
                    MinimumLod = 0,
                    MaximumLod = float.MaxValue
                };

                // Create the texture sampler state:
                samplerState_ = new SamplerState(device, samplerDesc);

                // Setup the description of the dynamic matrix constant Matrix buffer:
                BufferDescription matrixBufferDescription = new()
                {
                    Usage = ResourceUsage.Dynamic,
                    SizeInBytes = Utilities.SizeOf<DxMatrixBuffer>(),
                    BindFlags = BindFlags.ConstantBuffer,
                    CpuAccessFlags = CpuAccessFlags.Write,
                    OptionFlags = ResourceOptionFlags.None,
                    StructureByteStride = 0
                };

                // Create the constant buffer pointer to access the vertex shader within this class:
                constantMatrixBuffer_ = new SharpDX.Direct3D11.Buffer(device, matrixBufferDescription);

                // Setup the description of the light dynamic constant bufffer that is in the pixel shader:
                // (ByteWidth alwalys needs to be a multiple of the 16)!
                BufferDescription lightBufferDesc = new()
                {
                    Usage = ResourceUsage.Dynamic,
                    SizeInBytes = Utilities.SizeOf<DxLightBuffer>(), // (Must be divisable by 16 bytes)
                    BindFlags = BindFlags.ConstantBuffer,
                    CpuAccessFlags = CpuAccessFlags.Write,
                    OptionFlags = ResourceOptionFlags.None,
                   StructureByteStride = 0
                };

                // Create the constant buffer pointer to access the vertex shader constant buffer from within class.
                constantLightBuffer_ = new SharpDX.Direct3D11.Buffer(device, lightBufferDesc);

                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show("SHADER: Error during initialization: " + ex.Message,"Error");

                return false;
            }
        }

        private bool Set_ShaderParameters(DeviceContext deviceContext, Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix, ShaderResourceView? texture, Vector3 lightDirection, Vector4 diffuseColour)
        {
            try
            {
                // Transpose the Matrices to prepare them for shader:
                worldMatrix.Transpose();
                viewMatrix.Transpose();
                projectionMatrix.Transpose();

                // Lock the constant buffer:
                deviceContext.MapSubresource(constantMatrixBuffer_, MapMode.WriteDiscard, MapFlags.None, out DataStream mappedResource);

                // Copy the passed-in-matrices into the constant buffer:
                DxMatrixBuffer matrixBuffer = new()
                {
                    world = worldMatrix,
                    view = viewMatrix,
                    projection = projectionMatrix
                };
                mappedResource.Write(matrixBuffer);

                // Unlock the constant buffer:
                deviceContext.UnmapSubresource(constantMatrixBuffer_, 0);

                // Set the position of the constant buffer in the vertex shader:
                int bufferPositionNumber = 0;

                // Set the constant buffer in the vertex shader with the updated values:
                deviceContext.VertexShader.SetConstantBuffer(0, constantMatrixBuffer_);

                // Set shader resource in the pixel shader:
                deviceContext.PixelShader.SetShaderResource(0, texture);

                /// Lighting Shader:
                // Lock the light constant buffer:
                deviceContext.MapSubresource(constantLightBuffer_, MapMode.WriteDiscard, MapFlags.None, out DataStream mappedResourceLight);

                // Copy the lighting variables into the constant buffer:
                DxLightBuffer lightBuffer = new()
                {
                    diffuseColor = diffuseColour,
                    lightDirection = lightDirection,
                    rr = 0
                };
                mappedResourceLight.Write(lightBuffer);

                // Unlock the constant buffer:
                deviceContext.UnmapSubresource(constantLightBuffer_, 0);

                // Set the position of the light constant buffer in the pixel shader:
                bufferPositionNumber = 0;

                // Set the light constant buffer in the pixel shader with the updated values:
                deviceContext.PixelShader.SetConstantBuffer(bufferPositionNumber, constantLightBuffer_);

                return true;
            }
            catch
            {
                return false;
            }
        }

        private void Render_Shader(DeviceContext deviceContext, int indexCount)
        {
            // Set the vertex input layout:
            deviceContext.InputAssembler.InputLayout = layout_;

            // Set the vertex and pixel shaders that will be used to render this triangle:
            deviceContext.VertexShader.Set(vertexShader_);
            deviceContext.PixelShader.Set(pixelShader_);

            // Set the sampler state in the pixel shader:
            deviceContext.PixelShader.SetSampler(0, samplerState_);

            // Render the triangle:
            deviceContext.DrawIndexed(indexCount, 0, 0);
        }

        #endregion



        #region PUBLIC:

        public bool Render(DeviceContext deviceContext, int indexCount, Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix, ShaderResourceView? texture, Vector3 lightDirection, Vector4 diffuseColour)
        {
            // Shader parameters:
            if (!Set_ShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuseColour))
                return false;

            // Render the prepared buffers with the shader:
            Render_Shader(deviceContext, indexCount);

            return true;
        }

        #endregion

    }
}