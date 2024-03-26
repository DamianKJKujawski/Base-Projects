using System;
using System.Collections.Generic;
using SharpDX;
using SharpDX.Direct3D11;
using System.Windows;
using System.Linq;

using DxGraphics;
using DxWindow.ScenesController.Scene_25D;
using DxWindow.ScenesController.Scene_25D.IsometricMath_;

// Library Interop:
#pragma warning disable CA1416
using DSharp_InteropLibrary;


namespace DxWindow.ScenesController
{
    public class Scene_25D_MapEditor : Scene_25D_Base, IScene_25D
    {
        #region VARIABLES:

            // RENDER:
            // Textures:
            private DxTexture3D[]? textures_ = Array.Empty<DxTexture3D>();

            private DxTexture_Initializer[]? texturesList_;
            private (Vector3 position, int index)[]? opaqueModels_Initial_;
            private (Vector3 position, int index)[]? transparentModels_Initial_;

            // Models used in scene:
            readonly private List<DxModel2D5> models_opaque_ = new();
            readonly private List<DxModel2D5> models_transparent_ = new();

            // Scene map:
            readonly private Scene2D5 scene_ = new(12, 12);

            // Context Menu objects list info:
            private (string, int)[] texturesInfo_forContextMenu_ = Array.Empty<(string, int)>();

            // IO:
            // Mouse Selection:
            private SelectionData mouseSelection_ = new(new Vector3(0, 0, -1));

            // Camera:
            private DxCamera? camera_;

        #endregion



        #region PRIVATE: ENUM - TEXTURES MANAGEMENT:

            private enum TEXTURES_LIST
            {
                Selection,

                Cloud,
                Tiles,
                Building,
                Sensor,
                Grass,
                Tree,
                Wall,

                Remove
            }

        #endregion



        #region INIT/DISPOSAL:

            #region Node - Manage Scene here:
            private void Initialize_Scene()
            {
                // TODO READ FROM FILE!

                // CONFIGURE !!! to set used textures:
                // Textures list - matrix base:
                // textureScale base is 1x1, but textures are scalable
                texturesList_ = new DxTexture_Initializer[]// If Name is Empty, than it is not going to be added to Context Menu 
                {
                    new DxTexture_Initializer("\\gfx\\selection.png", new Vector2(1, 1), TEXTURES_LIST.Selection.ToString(), TEXTURES_DESTINATION.SKY),
                    new DxTexture_Initializer("\\gfx\\cloud.png", new Vector2(1, 1), TEXTURES_LIST.Cloud.ToString(), TEXTURES_DESTINATION.SKY),
                    new DxTexture_Initializer("\\gfx\\floor1.jpg", new Vector2(1, 1), TEXTURES_LIST.Tiles.ToString(), TEXTURES_DESTINATION.GROUND_EDITABLE),
                    new DxTexture_Initializer("\\gfx\\building1.png", new Vector2(2, 2), TEXTURES_LIST.Building.ToString(), TEXTURES_DESTINATION.GROUND_EDITABLE),
                    new DxTexture_Initializer("\\gfx\\sensor.png", new Vector2(1, 1), TEXTURES_LIST.Sensor.ToString(), TEXTURES_DESTINATION.SKY),
                    new DxTexture_Initializer("\\gfx\\floor2.jpg", new Vector2(1, 1), TEXTURES_LIST.Grass.ToString(), TEXTURES_DESTINATION.GROUND_EDITABLE),
                    new DxTexture_Initializer("\\gfx\\floor3.png", new Vector2(2, 2), TEXTURES_LIST.Tree.ToString(), TEXTURES_DESTINATION.GROUND_EDITABLE),
                    new DxTexture_Initializer("\\gfx\\wall.png", new Vector2(2, 2), TEXTURES_LIST.Wall.ToString(), TEXTURES_DESTINATION.GROUND_EDITABLE)
                };

                opaqueModels_Initial_ = new (Vector3 position, int index)[]  // Ground Models added at the beginning 
    {
                    (new Vector3(0, 0, 0), (int)TEXTURES_LIST.Tiles)
                };

                transparentModels_Initial_ = new (Vector3 position, int index)[] // Sky Models added at the beginning 
                {
                    (new Vector3(0, 0, -0.01f), (int)TEXTURES_LIST.Sensor),
                    (new Vector3(3, 4, -1.00f), (int)TEXTURES_LIST.Cloud),
                    (new Vector3(3, 3, -2.50f), (int)TEXTURES_LIST.Cloud),
                    (new Vector3(2, 3, -2.00f), (int)TEXTURES_LIST.Cloud)
                };
            }
            #endregion

            public Scene_25D_MapEditor(Device device, DeviceContext deviceContext) : base(device, deviceContext) { }

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
                    if(textures_ != null)
                        foreach (var texture in textures_)
                            texture.Dispose();

                    foreach (var model in models_opaque_)
                        model.Dispose();
                    models_opaque_.Clear();

                    foreach (var model in models_transparent_)
                        model.Dispose();
                    models_transparent_.Clear();

                    scene_.Release();
                    mouseSelection_.Release();

                    texturesInfo_forContextMenu_ = Array.Empty<(string, int)>();

                    textures_ = null;
                    texturesList_ = null;
                    camera_ = null; // Set to null to indicate disposal
                }

                base.Dispose(disposing);
            }

            public override bool Initialize()
            {
                if (!base.Initialize())
                    return false;

                camera_ = new DxCamera();
                camera_.Set_Position(0, 0, -5.0f);

                Initialize_Scene();

                try
                {
                    Initialize_Textures();
                    Initialize_OpaqueModels();
                    Initialize_TransparentModels();

                    return true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("The Map Editor scene could not be initialized\nError is '" + ex.Message + "'");
                    return false;
                }
            }

        #endregion



        #region PRIVATE:

            // Textures:
            private void Set_AvailableTexturesList(DxTexture_Initializer[] texturesList)
            {
                texturesInfo_forContextMenu_ = texturesList
                    .Select((texture, index) => (texture.name, index, texture.destination))
                    .Where(tuple => (tuple.destination == TEXTURES_DESTINATION.GROUND_EDITABLE))
                    .Select(tuple => (tuple.name, tuple.index))
                    .ToArray();

                // Remove option:
                texturesInfo_forContextMenu_ = texturesInfo_forContextMenu_
                    .Concat(new[] { (TEXTURES_LIST.Remove.ToString(), (int)TEXTURES_LIST.Remove) })
                    .ToArray();
            }

            private bool Set_Texture(DxModel2D5 model, Vector3 position, DxTexture3D texture, Vector2 size)
            {
                IsometricModelPoints _isometricModelPoints = IsometricMath.Calculate_ModelPoints(position, size);

                if (!model.Initialize
                (
                    base.Device_HardwareInterface,
                    texture,
                    new Vector3(_isometricModelPoints.p0.X, _isometricModelPoints.p0.Y, position.Z),
                    new Vector3(_isometricModelPoints.p1.X, _isometricModelPoints.p1.Y, position.Z),
                    new Vector3(_isometricModelPoints.p2.X, _isometricModelPoints.p2.Y, position.Z),
                    new Vector3(_isometricModelPoints.p3.X, _isometricModelPoints.p3.Y, position.Z)
                ))
                {
                    return false;
                }


                return true;
            }

            private void Set_TextureUsingMatrixIndices(int textureIndex)
            {
                int _startPosition_x = (int)mouseSelection_.position.X;
                int _startPosition_y = (int)mouseSelection_.position.Y;

                int _endPosition_x = (int)(mouseSelection_.position.X + mouseSelection_.size.X);
                int _endPosition_y = (int)(mouseSelection_.position.Y + mouseSelection_.size.Y);

                if ((scene_.map == null) || (textures_ == null))
                    return;

                int _texturesCount = textures_.Length;
                for (int x = _startPosition_x; x < _endPosition_x; x++)
                {
                    for (int y = _startPosition_y; y < _endPosition_y; y++)
                    {
                        if ((x < scene_.size.width) && (y < scene_.size.height) && (x >= 0) && (y >= 0))
                        {
                            if (textureIndex >= _texturesCount)
                                scene_.map[x, y].Dispose();
                            else
                                Set_Texture(scene_.map[x, y], new Vector3(x, y, 0), textures_[textureIndex], textures_[textureIndex].Size);
                        }
                    }
                }
            }
        

            private void Initialize_Textures()
            {
                if (texturesList_ == null)
                    return;

                // Store Textures:
                string _initError = String.Empty;
                string _filePath = AppDomain.CurrentDomain.BaseDirectory;

                textures_ = new DxTexture3D[texturesList_.Length];

                for (int i = 0; i < texturesList_.Length; i++)
                {
                    this.textures_[i] = new DxTexture3D();
                    if (!this.textures_[i].Initialize(base.Device_HardwareInterface, _filePath + texturesList_[i].path, texturesList_[i].textureScale))
                        _initError += '\n' + texturesList_[i].path;
                }

                // Handle Textures Init Error:
                if (_initError != String.Empty)
                {
                    MessageBox.Show("Could not initialize the texture object:" + _initError);
                    return;
                }

                Set_AvailableTexturesList(texturesList_);
            }

            private void Initialize_OpaqueModels()
            {
                if (opaqueModels_Initial_ == null)
                    return;

                if (textures_ == null)
                    return;

                if (scene_.map == null)
                    return;

                // Store Textures:
                for (int i = 0; i < opaqueModels_Initial_.Length; i++)
                {
                    Set_Texture
                        (
                            scene_.map[(int)opaqueModels_Initial_[i].position.X, (int)opaqueModels_Initial_[i].position.Y],
                            opaqueModels_Initial_[i].position,
                            textures_[opaqueModels_Initial_[i].index],
                            textures_[opaqueModels_Initial_[i].index].Size
                        );
                }

                var _sceneArray = scene_.map.Cast<DxModel2D5>().ToArray();
                Array.Reverse(_sceneArray); // Optimization: Allows to remove z-testing
                models_opaque_.AddRange(_sceneArray);
            }

            private void Initialize_TransparentModels()
            {
                if (transparentModels_Initial_ == null)
                    return;

                if (textures_ == null)
                    return;

                //Store textures:
                DxModel2D5[] _transparentmModels = new DxModel2D5[transparentModels_Initial_.Length];

                for (int i = 0; i < _transparentmModels.Length; i++)
                {
                    _transparentmModels[i] = new DxModel2D5();
                    Set_Texture
                        (
                            _transparentmModels[i],
                            transparentModels_Initial_[i].position,
                            textures_[transparentModels_Initial_[i].index],
                            textures_[transparentModels_Initial_[i].index].Size
                        );
                }

                models_transparent_.Add(mouseSelection_.model);
                models_transparent_.AddRange(_transparentmModels);
            }

        #endregion



        #region PUBLIC:

            // Textures list for Context Menu, in this case
            public (string, int)[] Get_TexturesList() {
                return texturesInfo_forContextMenu_;
            }

            // Mouse:
            public void MouseClick(int textureIndex) =>
                Set_TextureUsingMatrixIndices(textureIndex);

            public Vector3 Set_MouseSelection(System.Windows.Point screenPoint, SizeInt2D windowSize, MOUSE_SELECTION_STATE selectionState)
            {
                if (textures_ == null)
                    return new Vector3(-1, -1, -1);

                Vector3 _clickPoint = camera_!.Get_LookAt_OnThePlaneZ0(new Vector2((float)screenPoint.X, (float)screenPoint.Y), windowSize.width, windowSize.height);
                Vector3 _selectedPosition = IsometricMath.Get_MatrixIndicesUsingPoint(_clickPoint.X, _clickPoint.Y);

                if (_selectedPosition.X < 0)
                    _selectedPosition.X = 0;

                if (_selectedPosition.Y < 0)
                    _selectedPosition.Y = 0;

                mouseSelection_.Calculate_Size(_selectedPosition.X, _selectedPosition.Y);


                switch(selectionState)
                {
                    case MOUSE_SELECTION_STATE.SELECTION_END:
                    {
                        if (mouseSelection_.position.X < _selectedPosition.X)
                            _selectedPosition.X = mouseSelection_.position.X;

                        if (mouseSelection_.position.Y < _selectedPosition.Y)
                            _selectedPosition.Y = mouseSelection_.position.Y;

                        Set_Texture(mouseSelection_.model, _selectedPosition, textures_[(int)TEXTURES_LIST.Selection], mouseSelection_.size);

                        mouseSelection_.position = _selectedPosition; // End selecting, but keep red squares
                    }
                    break;

                    case MOUSE_SELECTION_STATE.SELECTED:
                    {
                        if (mouseSelection_.position.X < _selectedPosition.X)
                            _selectedPosition.X = mouseSelection_.position.X;

                        if (mouseSelection_.position.Y < _selectedPosition.Y)
                            _selectedPosition.Y = mouseSelection_.position.Y;

                        Set_Texture(mouseSelection_.model, _selectedPosition, textures_[(int)TEXTURES_LIST.Selection], mouseSelection_.size); // Set 2D array of red squares
                    }
                    break;

                    default:
                    case MOUSE_SELECTION_STATE.SELECTION_START:
                    {
                            Set_Texture(mouseSelection_.model, _selectedPosition, textures_[(int)TEXTURES_LIST.Selection], textures_[(int)TEXTURES_LIST.Selection].Size);

                            mouseSelection_.position = _selectedPosition; // Set first red square 
                    }
                    break;
                }

                return _clickPoint;
            }


            // Camera:
            public void Camera_Reset() =>
                camera_!.Set_Position(0, 0, -5.0f);

            public void Camera_Move(float x, float y, float z = 0) =>
                camera_!.Move_Position(x, y, z);

            public void Camera_Zoom(float z) => camera_!.Zoom_UsingAxisZ(z);


            #region Node - Manage Rendering Process:
            [Obsolete("Do not use Render() without using Initialize()!")]
            public void Render(Matrix projectionMatrix) // Unsafe, but bit faster way
            {
                // Set Camera: 
                camera_!.Render();   
                camera_!.Set_ProjectionMatrix(projectionMatrix);


                // TODO: Switch to Texture Atlas Drawing !

                // Render scene objects:
                base.DeviceContext_RenderInterface.OutputMerger.BlendState = null;
                for (int i = 0; i < models_opaque_.Count; i++)
                {
                    models_opaque_[i].Render(base.DeviceContext_RenderInterface);

                    base.LightShader!.Render(base.DeviceContext_RenderInterface, models_opaque_[i].IndexCount, base.WorldMatrix, camera_.ViewMatrix, projectionMatrix,
                        models_opaque_[i].Texture?.TextureResource, base.Light!.Direction, base.Light.DiffuseColour);
                }

                // Render transparent objects:
                base.DeviceContext_RenderInterface.OutputMerger.BlendState = base.BlendState_Transparent;
                for (int i = 0; i < models_transparent_.Count; i++)
                {
                    models_transparent_[i].Render(base.DeviceContext_RenderInterface);

                    base.LightShader!.Render(base.DeviceContext_RenderInterface, models_transparent_[i].IndexCount, base.WorldMatrix, camera_.ViewMatrix, projectionMatrix,
                    models_transparent_[i].Texture?.TextureResource, base.Light!.Direction, base.Light.DiffuseColour);
                }
            }
            #endregion

        #endregion
    }
}
