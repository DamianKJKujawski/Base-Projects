using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Controls;

using DxWindow;
#pragma warning disable CA1416
using DSharp_InteropLibrary;
using DxWindow.ScenesController.Scene_25D;

// Aliases:
using Flag = System.Boolean;




// Hardware Requirements: Works for Windows 7 and newer.
// * DirectX drivers managing scenes should be error-tolerant. This is not the main idea of ​​the program!
// If an error occurs, ignore it! 


namespace SmartHome_Editor
{
    public  partial  class MainWindow : Window
    {

        #region VARIABLES/PROPERTIES:

            [LibraryImport("user32.dll")]
            [return: MarshalAs(UnmanagedType.Bool)]
            private static partial bool SetCursorPos(int x, int y);

        // DIRECTX WINDOW:

            // Scenes:
            private readonly DxWindow_ScenesController scenesController = new ();
            // Interop:
            private DSharp_Interop? dxSharp_interop_;

            // Controll:
            private SizeInt2D renderSize;
            private float renderScale = 1.0f;
            private Flag updateScene = false;

            // Camera settings:
            private CameraFOV cameraFOV = new (35.0f, 0.1f, 6.0f);

            // Mouse:
            private HID_Mouse mouse = new (0.005f);

        #endregion



        #region INIT/DISPOSAL

            public MainWindow()
            {
                InitializeComponent();

                this.Closing += Is_Closing;

                // Synchronizing DirectX with the WPF window is necessary to prevent "stuttering".
                // In this scenario, WPF window is synchronizing with DirectX. When FPS is crucial, using the Rendering Event is necessary:

                if (Init_SharpDx_Interop()) // If platform is supported
                {
                    Init_ContextMenu();

                    // DxHost Events Handlers:
                    CompositionTarget.Rendering += LayoutUpdate_EventHandler;
                    this.Host.Loaded += new RoutedEventHandler(this.Host_Loaded);
                    this.Host.SizeChanged += new SizeChangedEventHandler(this.Host_SizeChanged);

                    // DxHost IO Handlers:
                    ImageDxHost.MouseWheel += ImageHost_MouseWheel;
                    ImageDxHost.MouseDown += ImageHost_MouseDown;
                    ImageDxHost.MouseUp += ImageHost_MouseUp;
                    ImageDxHost.MouseMove += ImageHost_MouseMove;
                } 
            }

            private void Is_Closing(object? sender, CancelEventArgs e)
            {
                CompositionTarget.Rendering -= LayoutUpdate_EventHandler;
                Host.Loaded -= Host_Loaded;
                Host.SizeChanged -= Host_SizeChanged;

                ImageDxHost.MouseWheel -= ImageHost_MouseWheel;
                ImageDxHost.MouseDown -= ImageHost_MouseDown;
                ImageDxHost.MouseUp -= ImageHost_MouseUp;
                ImageDxHost.MouseMove -= ImageHost_MouseMove;

                Closing -= Is_Closing;

                scenesController.Dispose();
            }

        #endregion



        #region INIT - SharpDx:

            private bool Init_SharpDx_Interop()
            {
                bool _initSucceeded = false;

                if (Environment.OSVersion.Platform == PlatformID.Win32NT && Environment.OSVersion.Version.Major >= 6) // Windows 7 or newer
                {
                    dxSharp_interop_ = new DSharp_Interop((IDxWindow)scenesController);
                    _initSucceeded = dxSharp_interop_.Initialize(cameraFOV.angle, cameraFOV.nearClipping, cameraFOV.farClipping);

                    if (!_initSucceeded)
                        MessageBox.Show("Failed to initialize", "WPF D3D Interop: Error", MessageBoxButton.OK, MessageBoxImage.Error);
                    else 
                        _initSucceeded = true;
                }
                else {
                    MessageBox.Show("Error: This software is fully compatible with Windows platforms version 7.0 or newer.");
                }

                return _initSucceeded;
            }

        #endregion



        #region METHODS:

        // INIT:

            private void Init_ContextMenu()
            {
                (string, int)[] _menuInfo = scenesController.Get_Menu();

                if (_menuInfo == null)
                    return;

                foreach (var info in _menuInfo)
                {
                    MenuItem _menuItem = new()
                    {
                        Tag = info.Item2,
                        Header = info.Item1
                    };
                    _menuItem.Click += MenuItem_Click;
                    Host.ContextMenu.Items.Add(_menuItem);
                } 
            }

        // DX RENDER PROCESS:

            private void Request_Render() =>
                updateScene = true;

            private void Handle_MouseMovement()
            {
                // Check if the right mouse button is pressed
                if (Mouse.MiddleButton == MouseButtonState.Pressed)
                {
                    // Hide mouse cursor:
                    Mouse.OverrideCursor = Cursors.None;

                    // Get mouse position:
                    System.Windows.Point _mousePosition = PointToScreen(Mouse.GetPosition(this));
                    // Calculate the change in mouse position:
                    _mousePosition = mouse.Get_MouseShift(_mousePosition);

                    // Update the last mouse position:
                    SetCursorPos((int)mouse.leftButton.position.X, (int)mouse.leftButton.position.Y);
                    // Process mouse movement:
                    scenesController.MouseMovement((float)_mousePosition.X, (float)_mousePosition.Y);

                    Request_Render();
                }
            }

            private void Do_Render(IntPtr surface, bool updateWindow) =>
                Render(surface, updateWindow);

            // CA1416 - Handled in Init();
            // TODO: Create rendering thread!
            private void Render(IntPtr resourcePointer, bool updateWindow) =>
                dxSharp_interop_!.Render(resourcePointer, updateWindow, renderSize.width, renderSize.height);

        #endregion



        #region EVENT HANDLERS:

        // DX WINDOW:

            // Sync between DxWindow and WPF Rendering to avoid Stuttering:
            private void LayoutUpdate_EventHandler(object? sender, EventArgs e)
            {
                if (updateScene == true)
                {
                    InteropDxImage.RequestRender();
                    updateScene = false;
                }
            }

            private void Host_SizeChanged(object sender, SizeChangedEventArgs e)
            {
                var _pixelSize = dxSharp_interop_!.Get_RenderPixelSize(Host);

                HostClip.Rect = new Rect(0, 0, _pixelSize.Item1, _pixelSize.Item2);

                renderSize.width = (int)(_pixelSize.Item1 * renderScale);
                renderSize.height = (int)(_pixelSize.Item2 * renderScale);

                InteropDxImage.SetPixelSize(renderSize.width, renderSize.height);

                Request_Render();
            }

            // Drag Window 
            private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e) {  
                if (e.LeftButton == MouseButtonState.Pressed)
                    DragMove();
            }

            private void Host_Loaded(object sender, RoutedEventArgs e)
            {
                InteropDxImage.WindowOwner = (new System.Windows.Interop.WindowInteropHelper(this)).Handle;
                InteropDxImage.OnRender = Do_Render;

                InteropDxImage.RequestRender();
            }

        // IMAGE HOST:

            private void ImageHost_MouseWheel(object sender, MouseWheelEventArgs e)
            {
                scenesController.MouseWheel((float)e.Delta / 500); // Slow down wheel

                Request_Render();
            }

            private void ImageHost_MouseDown(object sender, MouseButtonEventArgs e)
            {
                if (e.LeftButton == MouseButtonState.Pressed)
                {
                    System.Windows.Point _mousePosition = HID_Mouse.Get_MouseShift_FromHostWindow(sender, e, renderScale);
                    scenesController.MouseClick(_mousePosition, renderSize, MOUSE_SELECTION_STATE.SELECTION_START);
                    Request_Render();
                    mouse.leftButton.selecting = true;
                }

                if (e.MiddleButton == MouseButtonState.Pressed)
                {
                    mouse.leftButton.position = PointToScreen(Mouse.GetPosition(this));
                    mouse.leftButton.pressed = true;
                }
            }

            private void ImageHost_MouseUp(object sender, MouseButtonEventArgs e)
            {
                if (e.MiddleButton == MouseButtonState.Released) {
                    if (mouse.leftButton.pressed)
                        mouse.leftButton.pressed = false;
                }

                if (e.LeftButton == MouseButtonState.Released) {
                    if (mouse.leftButton.selecting)
                    {
                        System.Windows.Point mousePosition = HID_Mouse.Get_MouseShift_FromHostWindow(sender, e, renderScale);
                        scenesController.MouseClick(mousePosition, renderSize, MOUSE_SELECTION_STATE.SELECTION_END);
                        Request_Render();
                        mouse.leftButton.selecting = false;
                    }
                }

                Mouse.OverrideCursor = null;
            }

            private void ImageHost_MouseMove(object sender, MouseEventArgs e)
            {
                if (mouse.leftButton.pressed)
                    Handle_MouseMovement();

                if (mouse.leftButton.selecting)
                {
                    System.Windows.Point _mousePosition = HID_Mouse.Get_MouseShift_FromHostWindow(sender, e, renderScale);
                    scenesController.MouseClick(_mousePosition, renderSize, MOUSE_SELECTION_STATE.SELECTED);
                    Request_Render();
                }
            }

        #endregion



        #region GUI:

        // MENU BUTTONS:

            private void MenuItem_Click(object sender, RoutedEventArgs e)
            {
                int parameter = (int)((MenuItem)sender).Tag;

                scenesController.MenuClick(parameter);
                Request_Render();
            }

            private void ShowMenuButton_Click(object sender, RoutedEventArgs e)
            {
                if(windowGrid.ColumnDefinitions[1].Width == new GridLength(0))
                    windowGrid.ColumnDefinitions[1].Width = new GridLength(305);
                else
                    windowGrid.ColumnDefinitions[1].Width = new GridLength(0);
            }

        // WINDOW BUTTONS:

            private void MaximizeButton_Click(object sender, RoutedEventArgs e)
            {
                if (this.WindowState == WindowState.Maximized)
                    this.WindowState = WindowState.Normal;
                else
                    this.WindowState = WindowState.Maximized;
            }

            private void MinimizeButton_Click(object sender, RoutedEventArgs e) => 
                this.WindowState = WindowState.Minimized;

            private void CloseButton_Click(object sender, RoutedEventArgs e) => 
                Application.Current.Shutdown();

        #endregion

    }
}
