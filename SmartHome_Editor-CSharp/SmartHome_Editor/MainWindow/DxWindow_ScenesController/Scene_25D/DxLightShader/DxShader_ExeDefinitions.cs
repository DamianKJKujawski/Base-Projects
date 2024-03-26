
namespace DxWindow.ScenesController.Scene_25D.DxLightShader_
{
    public static class DxShader_ExeDefinitions
    {
        // Vertex Shader
        public static string LightVertexShader =>  
            @"
            ///////////////////////
            ////   GLOBALS
            ///////////////////////
            cbuffer MatrixBuffer
            {
	            matrix worldMatrix;
	            matrix viewMatrix;
	            matrix projectionMatrix;
            };

            //////////////////////
            ////   TYPES
            //////////////////////
            struct VertexInputType
            {
	            float4 position : POSITION;
	            float2 tex : TEXCOORD0;
	            float3 normal : NORMAL;
            };

            struct PixelInputType
            {
	            float4 position : SV_POSITION;
	            float2 tex : TEXCOORD0;
	            float3 normal : NORMAL;
            };

            /////////////////////////////////////
            /////   Vertex Shader
            /////////////////////////////////////
            PixelInputType LightVertexShader(VertexInputType input)
            {
	            PixelInputType output;

	            // Change the position vector to be 4 units for proper matrix calculations.
	            input.position.w = 1.0f;

	            // Calculate the position of the vertex against the world, view, and projection matrices.
	            output.position = mul(input.position, worldMatrix);
	            output.position = mul(output.position, viewMatrix);
	            output.position = mul(output.position, projectionMatrix);

	            // Store the texture coordinates for the pixel shader.
	            output.tex = input.tex;

	            // Calculate the normal vector against the world matrix only.
	            output.normal = mul(input.normal, (float3x3)worldMatrix);

	            // Normalize the normal vector.
	            output.normal = normalize(output.normal);

	            return output;
            }";

        // Pixel Shader
        public static string LightPixelShader => 
            @"
            Texture2D shaderTexture;
            SamplerState SampleType;

            cbuffer LightBuffer
            {
                float4 diffuseColor;
                float3 lightDirection;
                float padding;
            };

            struct PixelInputType
            {
                float4 position : SV_POSITION;
                float2 tex : TEXCOORD0;
                float3 normal : NORMAL;
            };

            float4 LightPixelShader(PixelInputType input) : SV_TARGET
            {
                float4 textureColor;
                float3 lightDir;
                float lightIntensity;
                float4 color;

                // Sample the pixel color from the texture using the sampler at this texture coordinate location.
                textureColor = shaderTexture.Sample(SampleType, input.tex);

                // Invert the light direction for calculations.
                lightDir = -lightDirection;

                // Calculate the amount of light on this pixel.
                lightIntensity = saturate(dot(input.normal, lightDir));

                // Determine the final diffuse color based on the diffuse color combined with the light intensity.
                color.rgb = saturate(diffuseColor.rgb * lightIntensity);

                // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
                color.rgb *= textureColor.rgb;

                // Set the alpha channel from the texture's alpha channel.
                color.a = textureColor.a;

                // Discard pixels with an alpha value of 0
                if (color.a < 0.5)
                    discard;

                return color;
            }";
    }
}