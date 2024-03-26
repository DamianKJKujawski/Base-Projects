
using SmartHome_Editor.HID_Mouse_;



namespace SmartHome_Editor
{
    public class HID_Mouse
    {

        #region VARIABLES:

            public MouseButton leftButton;

            private readonly float sensitivity_;

        #endregion



        #region INIT/DISPOSAL:

            public HID_Mouse(float sensitivity) 
            {
                this.sensitivity_ = sensitivity;
            }

        #endregion



        #region PUBLIC:

            public System.Windows.Point Get_MouseShift(in System.Windows.Point mousePosition)
            {
                System.Windows.Point _mousePosition;

                _mousePosition.X = -(float)(mousePosition.X - leftButton.position.X) * sensitivity_;
                _mousePosition.Y = (float)(mousePosition.Y - leftButton.position.Y) * sensitivity_;

                return _mousePosition;
            }

            public static System.Windows.Point Get_MouseShift_FromHostWindow(object sender, System.Windows.Input.MouseEventArgs e, float hostScale)
            {
                System.Windows.Point _mousePosition = e.GetPosition((System.Windows.IInputElement)sender);

                _mousePosition.X *= hostScale;
                _mousePosition.Y *= hostScale;

                return _mousePosition;
            }

        #endregion

    }
}
