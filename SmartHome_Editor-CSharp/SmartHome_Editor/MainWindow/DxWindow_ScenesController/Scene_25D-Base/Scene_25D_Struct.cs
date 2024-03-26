using System;
using SharpDX;

#pragma warning disable CA1416
using DSharp_InteropLibrary;

// Dx Base:
using DxGraphics;



namespace DxWindow.ScenesController.Scene_25D
{
    // Initialize textures in Scene:
    public struct DxTexture_Initializer
    {
        public string path;
        public string name;

        public Vector2 textureScale;

        public TEXTURES_DESTINATION destination;

        public DxTexture_Initializer(string path, Vector2 textureScale, string name, TEXTURES_DESTINATION destination)
        {
            this.path = path;
            this.name = name;
            this.textureScale = textureScale;
            this.destination = destination;
        }
    }


    // Scene Indices Selection:
    public struct SelectionData
    {
        public DxModel2D5 model;

        public Vector3 position;
        public Vector2 size;


        public SelectionData(Vector3 position)
        {
            this.model = new();

            this.position = position;
            this.size = new Vector2(0, 0);
        }

        public void Calculate_Size(float position_x, float position_y)
        {
            size.X = Math.Abs(position.X - position_x) + 1;
            size.Y = Math.Abs(position.Y - position_y) + 1;
        }

        public readonly void Release() // IDE0251*
        {
            model?.Dispose();
        }
    };


    // Scene Matrix:
    public struct Scene2D5
    {
        public readonly SizeInt2D size;
        public DxModel2D5[,] ?map;

        
        public Scene2D5(int width, int height)
        {
            this.size = new SizeInt2D(width, height);

            this.map = new DxModel2D5[width, height];

            for (int i = 0; i < size.height; i++)
            {
                for (int j = 0; j < size.width; j++) {
                    this.map[i, j] = new DxModel2D5();
                }
            }
        }

        public void Release()
        {
            if (map == null)
                return;

            for (int i = 0; i < map.GetLength(0); i++)
            {
                for (int j = 0; j < map.GetLength(1); j++)
                    map[i, j]?.Dispose();
            }

            map = null;
        }
    };
            
}
